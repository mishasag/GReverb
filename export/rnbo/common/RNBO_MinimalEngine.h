//
//  RNBO_MinimalEngine.h
//  baremetal
//
//  Created by Stefan Brunner on 15.04.24.
//

#ifndef RNBO_MinimalEngine_h
#define RNBO_MinimalEngine_h

#include "RNBO_EngineInterface.h"

namespace RNBO {


enum InternalEventType {
	Parameter,
	ParameterBang,
	Clock,
	ClockWithValue,
	DataRefUpdate
};

const ParameterIndex UNUSEDPARAMINDEX = 0;
const ClockId UNUSEDCLOCKINDEX = 0;

enum EventState {
	DELETED,
	INVALID,
	READY
};

struct InternalEvent {
public:
	InternalEventType	type;
	MillisecondTime time;
	ParameterValue value;
	ClockId	clockId;
	ParameterIndex index;
	EventTarget* eventTarget;
	EventState state;
};

#ifndef RNBO_MINENGINEQUEUESIZE
#define RNBO_MINENGINEQUEUESIZE 128
#endif


template <size_t SIZE = RNBO_MINENGINEQUEUESIZE>
class MinimalEngine : public EngineInterface
{
private:
	class EventProceesingGuard {
	public:
		EventProceesingGuard(MinimalEngine& engine)
		: _engine(engine)
		{
			_engine._isInEventProcessing = true;;
		}

		~EventProceesingGuard() {
			_engine._isInEventProcessing = false;
		}

	private:
		MinimalEngine& _engine;
	};

public:

	MinimalEngine(PatcherInterface* patcher)
	: _patcher(patcher)
	{
        _patcher->setEngineAndPatcher(this, nullptr);
		for (size_t i = 0; i < SIZE; i++) {
			_queue[i].state = DELETED;
		}
	}

    // override to get a notification if a parameter has changed
    void notifyParameterValueChanged(ParameterIndex index, ParameterValue value, bool ignoreSource) override {}

	// override to get MIDI events sent out from the patcher
	void sendMidiEvent(int port, int b1, int b2, int b3, MillisecondTime time = 0.0) override {}
	void sendMidiEventList(int port, const list& data, MillisecondTime time = 0.0) override {}

    // oerride to get time events sent out form the patcher
	void sendTempoEvent(Tempo tempo) override {}
	void sendTransportEvent(TransportState state) override {}
	void sendBeatTimeEvent(BeatTime beattime) override {}
	void sendTimeSignatureEvent(int numerator, int denominator) override {}

    // override to get messages being sent out from the patcher
	void sendNumMessage(MessageTag tag, MessageTag objectId, number payload, MillisecondTime time) override {}
	void sendListMessage(MessageTag tag, MessageTag objectId, const list& payload, MillisecondTime time) override {}
	void sendBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) override {}

    // get the engine time
	MillisecondTime getCurrentTime() override { return _currentTime; }

    // override to get a notification if the current preset has been changed
	void presetTouched() override {}


    // ---------- from here on for internal use only !!! -----------

    void scheduleClockEvent(EventTarget* eventTarget, ClockId clockIndex, MillisecondTime time) override {
        insertEvent({ Clock, time, 0, clockIndex, UNUSEDPARAMINDEX, eventTarget, READY });
    }

    void scheduleClockEventWithValue(EventTarget* eventTarget, ClockId clockIndex, MillisecondTime time, ParameterValue value) override {
        insertEvent({ ClockWithValue, time, value, clockIndex, UNUSEDPARAMINDEX, eventTarget, READY });
    }

    // schedule a parameter change event
    void scheduleParameterChange(ParameterIndex index, ParameterValue value, MillisecondTime offset) override {
        insertEvent({ Parameter, getCurrentTime() + offset, value, UNUSEDCLOCKINDEX, index, nullptr, READY });
    }

    void scheduleParameterBang(ParameterIndex index, MillisecondTime offset) override {
        insertEvent({ ParameterBang, getCurrentTime() + offset, 0, UNUSEDCLOCKINDEX, index, nullptr, READY });
    }

    // remove all clock events from the scheduler, optionally executing the clocks
    void flushClockEvents(EventTarget* eventTarget, ClockId clockIndex, bool execute) override {
        for (size_t i = 0; i < SIZE; i++) {
            auto& event = _queue[i];
            if (event.type == Clock
                && event.state == READY
                && event.clockId == clockIndex
                && event.eventTarget == eventTarget
            ) {
                event.state = INVALID;
                if (execute) executeEvent(event);
            }
        }
    }

    void flushClockEventsWithValue(EventTarget* eventTarget, ClockId clockIndex, ParameterValue value, bool execute) override {
        for (size_t i = 0; i < SIZE; i++) {
            auto& event = _queue[i];
            if (event.type == Clock
                && event.clockId == clockIndex
                && event.state == READY
                && event.eventTarget == eventTarget
                && event.value == value
            ) {
                event.state = INVALID;
                if (execute) executeEvent(event);
            }
        }

    }

    void sendDataRefUpdated(DataRefIndex index) override {
        if (_isInEventProcessing)
            _patcher->processDataViewUpdate(index, _patcher->getPatcherTime());
        else
            insertEvent({ DataRefUpdate, _patcher->getPatcherTime(), 0, index, UNUSEDPARAMINDEX, nullptr, READY });
    }

	void processEventsUntil(MillisecondTime time) {
		if (_isInEventProcessing) return;

		EventProceesingGuard guard(*this);
		bool hasProcessed = false;

		for (size_t i = 0; i < SIZE; i++) {
			auto& event = _queue[i];
			if (event.state == DELETED || event.time > time) break;
			const bool wasReady = event.state == READY;
			event.state = INVALID; // invalidate before excuting, since we could alway schedule a new one

			if (wasReady) {
				executeEvent(event);
			}

			hasProcessed = true;
		}

		if (hasProcessed) cleanUpQueue();
	}

	void advanceTime(MillisecondTime offset) {
		_currentTime += offset;
	}

    // since the patcher cannot change, we do not need to implement these
    void updatePatcherEventTarget(const EventTarget*, PatcherEventTarget*) override {}
    void rescheduleEventTarget(const EventTarget*) override {}

    void sendOutlet(EngineLink* sender, OutletIndex index, ParameterValue value, SampleOffset sampleOffset = 0) override {}

private:

    void executeEvent(const InternalEvent& event) {
        switch (event.type) {
            case Parameter:
                _patcher->processParameterEvent(event.index, event.value, event.time);
                break;
            case ParameterBang:
                _patcher->processParameterBangEvent(event.index, event.time);
                break;
            case Clock:
                _patcher->processClockEvent(event.time, event.clockId, false, 0);
                break;
            case ClockWithValue:
                _patcher->processClockEvent(event.time, event.clockId, true, event.value);
                break;
            case DataRefUpdate:
                _patcher->processDataViewUpdate(event.clockId, event.time);
                break;
        }
    }

	void cleanUpQueue() {
		size_t firstValid = 0;
		for (; firstValid < SIZE; firstValid++) {
			const auto eventState = _queue[firstValid].state;
			if (eventState == INVALID) _queue[firstValid].state = DELETED;
			else if (eventState == READY) break;
		}

		if (firstValid < SIZE && firstValid > 0) {
			size_t lastValid = 0;
			do {
				_queue[lastValid] = _queue[firstValid];
				_queue[firstValid].state = DELETED;
				lastValid++;
				firstValid++;
			}
			while (firstValid < SIZE && _queue[firstValid].state == READY);
		}
	}

	void insertEvent(const InternalEvent& event) {
		bool inserted = false;
		for (long i = 0; i < SIZE; i++) {
			auto& eventAtPlace = _queue[i];
			if (eventAtPlace.state == DELETED) {
				// empty slot, since it is DELETED and not INVALID this could only be 
				// the end of the queue, just put the event in
				eventAtPlace = event;
				inserted = true;
				break;
			}
			else if (eventAtPlace.time > event.time) {
				// we need to make place
				long j = i;
				while (j < SIZE && _queue[j].state > DELETED) j++;
				if (j >= SIZE) break;
				j--;
				while (j >= i) {
					_queue[j + 1] = _queue[j];
					j--;
				}

				eventAtPlace = event;
				inserted = true;
				break;
			}
		}

		if (!inserted) {
			Platform::errorOrDefault(RuntimeError::QueueOverflow, "Queue overflow !", false /*unused*/);
		}
	}

	PatcherInterface* _patcher;
	
	bool _isInEventProcessing = false;
	MillisecondTime	_currentTime = 0;

	InternalEvent	_queue[SIZE];

};

using INTERNALENGINE = MinimalEngine<RNBO_MINENGINEQUEUESIZE>;


} // RNBO

#endif /* RNBO_MinimalEngine_h */
