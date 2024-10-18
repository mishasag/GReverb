/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

class RNBOSubpatcher_188 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_188()
    {
    }
    
    ~RNBOSubpatcher_188()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
    }
    
    inline number safemod(number f, number m) {
        if (m != 0) {
            Int f_trunc = (Int)(trunc(f));
            Int m_trunc = (Int)(trunc(m));
    
            if (f == f_trunc && m == m_trunc) {
                f = f_trunc % m_trunc;
            } else {
                if (m < 0) {
                    m = -m;
                }
    
                if (f >= m) {
                    if (f >= m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f -= m;
                    }
                } else if (f <= -m) {
                    if (f <= -m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f += m;
                    }
                }
            }
        } else {
            f = 0.0;
        }
    
        return f;
    }
    
    inline number safesqrt(number num) {
        return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
        const SampleValue * in4 = (numInputs >= 4 && inputs[3] ? inputs[3] : this->zeroBuffer);
        const SampleValue * in5 = (numInputs >= 5 && inputs[4] ? inputs[4] : this->zeroBuffer);
        this->xfade_tilde_01_perform(in5, in1, in3, out1, n);
        this->xfade_tilde_02_perform(in5, in2, in4, out2, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        RNBO_UNUSED(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 5;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {}
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
    void xfade_tilde_01_perform(
        const Sample * pos,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] * this->xfade_tilde_01_func_next(pos[(Index)i], 0) + in2[(Index)i] * this->xfade_tilde_01_func_next(pos[(Index)i], 1);
        }
    }
    
    void xfade_tilde_02_perform(
        const Sample * pos,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] * this->xfade_tilde_02_func_next(pos[(Index)i], 0) + in2[(Index)i] * this->xfade_tilde_02_func_next(pos[(Index)i], 1);
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    number xfade_tilde_01_func_next(number pos, int channel) {
        {
            {
                number nchan_1 = 2 - 1;
    
                {
                    pos = pos * nchan_1;
                }
    
                {
                    if (pos > nchan_1)
                        pos = nchan_1;
                    else if (pos < 0)
                        pos = 0;
                }
    
                pos = pos - channel;
    
                if (pos > -1 && pos < 1) {
                    {
                        return rnbo_cos(1.57079632679489661923 * pos);
                    }
                } else {
                    return 0;
                }
            }
        }
    }
    
    void xfade_tilde_01_func_reset() {}
    
    number xfade_tilde_02_func_next(number pos, int channel) {
        {
            {
                number nchan_1 = 2 - 1;
    
                {
                    pos = pos * nchan_1;
                }
    
                {
                    if (pos > nchan_1)
                        pos = nchan_1;
                    else if (pos < 0)
                        pos = 0;
                }
    
                pos = pos - channel;
    
                if (pos > -1 && pos < 1) {
                    {
                        return rnbo_cos(1.57079632679489661923 * pos);
                    }
                } else {
                    return 0;
                }
            }
        }
    }
    
    void xfade_tilde_02_func_reset() {}
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        xfade_tilde_01_pos = 0;
        xfade_tilde_02_pos = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number xfade_tilde_01_pos;
        number xfade_tilde_02_pos;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_189 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_189()
    {
    }
    
    ~RNBOSubpatcher_189()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -62043057, false);
    }
    
    inline number safediv(number num, number denom) {
        return (denom == 0.0 ? 0.0 : num / denom);
    }
    
    number safepow(number base, number exponent) {
        return fixnan(rnbo_pow(base, exponent));
    }
    
    number scale(
        number x,
        number lowin,
        number hiin,
        number lowout,
        number highout,
        number pow
    ) {
        auto inscale = this->safediv(1., hiin - lowin);
        number outdiff = highout - lowout;
        number value = (x - lowin) * inscale;
    
        if (pow != 1) {
            if (value > 0)
                value = this->safepow(value, pow);
            else
                value = -this->safepow(-value, pow);
        }
    
        value = value * outdiff + lowout;
        return value;
    }
    
    SampleIndex currentsampletime() {
        return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
    }
    
    number mstosamps(MillisecondTime ms) {
        return ms * this->sr * 0.001;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        this->linetilde_01_perform(this->signals[0], n);
        this->dspexpr_02_perform(in2, this->signals[0], out2, n);
        this->dspexpr_01_perform(in1, this->signals[0], out1, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 1; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        RNBO_UNUSED(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -62043057:
            {
            this->linetilde_01_target_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("preq_Level~/number_obj-7") == objectId)
                this->numberobj_01_valin_set(payload);
    
            if (TAG("preq_Level~/number_obj-14") == objectId)
                this->numberobj_02_valin_set(payload);
    
            if (TAG("preq_Level~/number_obj-5") == objectId)
                this->numberobj_03_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("preq_Level~/number_obj-7") == objectId)
                this->numberobj_01_format_set(payload);
    
            if (TAG("preq_Level~/number_obj-14") == objectId)
                this->numberobj_02_format_set(payload);
    
            if (TAG("preq_Level~/number_obj-5") == objectId)
                this->numberobj_03_format_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("preq_Level~/number_obj-7"):
            {
            return "preq_Level~/number_obj-7";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("preq_Level~/number_obj-14"):
            {
            return "preq_Level~/number_obj-14";
            }
        case TAG("preq_Level~/number_obj-5"):
            {
            return "preq_Level~/number_obj-5";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void numberobj_01_valin_set(number v) {
        this->numberobj_01_value_set(v);
    }
    
    void numberobj_01_format_set(number v) {
        this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_02_valin_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void numberobj_02_format_set(number v) {
        this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_03_valin_set(number v) {
        this->numberobj_03_value_set(v);
    }
    
    void numberobj_03_format_set(number v) {
        this->numberobj_03_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_01_out1_bang_bang() {
        this->numberobj_02_value_bang();
    }
    
    void eventinlet_01_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_02_value_set(converted);
        }
    }
    
    void linetilde_01_target_bang() {}
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->numberobj_01_init();
        this->numberobj_02_init();
        this->numberobj_03_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
    void linetilde_01_time_set(number v) {
        this->linetilde_01_time = v;
    }
    
    void linetilde_01_segments_set(const list& v) {
        this->linetilde_01_segments = jsCreateListCopy(v);
    
        if ((bool)(v->length)) {
            if (v->length == 1 && this->linetilde_01_time == 0) {
                this->linetilde_01_activeRamps->length = 0;
                this->linetilde_01_currentValue = v[0];
            } else {
                auto currentTime = this->currentsampletime();
                number lastRampValue = this->linetilde_01_currentValue;
                number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;
    
                for (Index i = 0; i < this->linetilde_01_activeRamps->length; i += 3) {
                    rampEnd = this->linetilde_01_activeRamps[(Index)(i + 2)];
    
                    if (rampEnd > currentTime) {
                        this->linetilde_01_activeRamps[(Index)(i + 2)] = currentTime;
                        number diff = rampEnd - currentTime;
                        number valueDiff = diff * this->linetilde_01_activeRamps[(Index)(i + 1)];
                        lastRampValue = this->linetilde_01_activeRamps[(Index)i] - valueDiff;
                        this->linetilde_01_activeRamps[(Index)i] = lastRampValue;
                        this->linetilde_01_activeRamps->length = i + 3;
                        rampEnd = currentTime;
                    } else {
                        lastRampValue = this->linetilde_01_activeRamps[(Index)i];
                    }
                }
    
                if (rampEnd < currentTime) {
                    this->linetilde_01_activeRamps->push(lastRampValue);
                    this->linetilde_01_activeRamps->push(0);
                    this->linetilde_01_activeRamps->push(currentTime);
                }
    
                number lastRampEnd = currentTime;
    
                for (Index i = 0; i < v->length; i += 2) {
                    number destinationValue = v[(Index)i];
                    number inc = 0;
                    number rampTimeInSamples;
    
                    if (v->length > i + 1) {
                        rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);
    
                        if ((bool)(this->linetilde_01_keepramp)) {
                            this->linetilde_01_time_set(v[(Index)(i + 1)]);
                        }
                    } else {
                        rampTimeInSamples = this->mstosamps(this->linetilde_01_time);
                    }
    
                    if (rampTimeInSamples <= 0) {
                        rampTimeInSamples = 1;
                    }
    
                    inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                    lastRampEnd += rampTimeInSamples;
                    this->linetilde_01_activeRamps->push(destinationValue);
                    this->linetilde_01_activeRamps->push(inc);
                    this->linetilde_01_activeRamps->push(lastRampEnd);
                    lastRampValue = destinationValue;
                }
            }
        }
    }
    
    void numberobj_01_output_set(number v) {
        {
            list converted = {v};
            this->linetilde_01_segments_set(converted);
        }
    }
    
    void numberobj_01_value_set(number v) {
        this->numberobj_01_value_setter(v);
        v = this->numberobj_01_value;
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("preq_Level~/number_obj-7"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_01_output_set(localvalue);
    }
    
    void expr_01_out1_set(number v) {
        this->expr_01_out1 = v;
        this->numberobj_01_value_set(this->expr_01_out1);
    }
    
    void expr_01_in1_set(number in1) {
        this->expr_01_in1 = in1;
        this->expr_01_out1_set(rnbo_pow(10, this->expr_01_in1 * 0.05));//#map:preq_Level~/dbtoa_obj-3:1
    }
    
    void numberobj_03_output_set(number v) {
        this->expr_01_in1_set(v);
    }
    
    void numberobj_03_value_set(number v) {
        this->numberobj_03_value_setter(v);
        v = this->numberobj_03_value;
        number localvalue = v;
    
        if (this->numberobj_03_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("preq_Level~/number_obj-5"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_03_output_set(localvalue);
    }
    
    void scale_01_out_set(const list& v) {
        this->scale_01_out = jsCreateListCopy(v);
    
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_03_value_set(converted);
        }
    }
    
    void scale_01_input_set(const list& v) {
        this->scale_01_input = jsCreateListCopy(v);
        list tmp = {};
    
        for (Index i = 0; i < v->length; i++) {
            tmp->push(this->scale(
                v[(Index)i],
                this->scale_01_inlow,
                this->scale_01_inhigh,
                this->scale_01_outlow,
                this->scale_01_outhigh,
                this->scale_01_power
            ));
        }
    
        this->scale_01_out_set(tmp);
    }
    
    void numberobj_02_output_set(number v) {
        {
            list converted = {v};
            this->scale_01_input_set(converted);
        }
    }
    
    void numberobj_02_value_set(number v) {
        this->numberobj_02_value_setter(v);
        v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("preq_Level~/number_obj-14"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_02_output_set(localvalue);
    }
    
    void eventinlet_01_out1_number_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void numberobj_02_value_bang() {
        number v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("preq_Level~/number_obj-14"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_02_output_set(localvalue);
    }
    
    void linetilde_01_perform(SampleValue * out, Index n) {
        auto __linetilde_01_time = this->linetilde_01_time;
        auto __linetilde_01_keepramp = this->linetilde_01_keepramp;
        auto __linetilde_01_currentValue = this->linetilde_01_currentValue;
        Index i = 0;
    
        if ((bool)(this->linetilde_01_activeRamps->length)) {
            while ((bool)(this->linetilde_01_activeRamps->length) && i < n) {
                number destinationValue = this->linetilde_01_activeRamps[0];
                number inc = this->linetilde_01_activeRamps[1];
                number rampTimeInSamples = this->linetilde_01_activeRamps[2] - this->audioProcessSampleCount - i;
                number val = __linetilde_01_currentValue;
    
                while (rampTimeInSamples > 0 && i < n) {
                    out[(Index)i] = val;
                    val += inc;
                    i++;
                    rampTimeInSamples--;
                }
    
                if (rampTimeInSamples <= 0) {
                    val = destinationValue;
                    this->linetilde_01_activeRamps->splice(0, 3);
    
                    if ((bool)(!(bool)(this->linetilde_01_activeRamps->length))) {
                        this->getEngine()->scheduleClockEventWithValue(
                            this,
                            -62043057,
                            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                            0
                        );;
    
                        if ((bool)(!(bool)(__linetilde_01_keepramp))) {
                            __linetilde_01_time = 0;
                        }
                    }
                }
    
                __linetilde_01_currentValue = val;
            }
        }
    
        while (i < n) {
            out[(Index)i] = __linetilde_01_currentValue;
            i++;
        }
    
        this->linetilde_01_currentValue = __linetilde_01_currentValue;
        this->linetilde_01_time = __linetilde_01_time;
    }
    
    void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void numberobj_01_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_01_value = localvalue;
    }
    
    void numberobj_02_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_02_value = localvalue;
    }
    
    void numberobj_03_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_03_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_03_value = localvalue;
    }
    
    void numberobj_01_init() {
        this->numberobj_01_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("preq_Level~/number_obj-7"), 1, this->_currentTime);
    }
    
    void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_01_value;
    }
    
    void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_01_value_set(preset["value"]);
    }
    
    void numberobj_02_init() {
        this->numberobj_02_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("preq_Level~/number_obj-14"), 1, this->_currentTime);
    }
    
    void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_02_value;
    }
    
    void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_02_value_set(preset["value"]);
    }
    
    void numberobj_03_init() {
        this->numberobj_03_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("preq_Level~/number_obj-5"), 1, this->_currentTime);
    }
    
    void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_03_value;
    }
    
    void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_03_value_set(preset["value"]);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        dspexpr_01_in1 = 0;
        dspexpr_01_in2 = 0;
        dspexpr_02_in1 = 0;
        dspexpr_02_in2 = 0;
        numberobj_01_value = 0;
        numberobj_01_value_setter(numberobj_01_value);
        numberobj_02_value = 0;
        numberobj_02_value_setter(numberobj_02_value);
        scale_01_inlow = -100;
        scale_01_inhigh = 100;
        scale_01_outlow = -18;
        scale_01_outhigh = 18;
        scale_01_power = 1;
        numberobj_03_value = 0;
        numberobj_03_value_setter(numberobj_03_value);
        expr_01_in1 = 0;
        expr_01_out1 = 0;
        linetilde_01_time = 10;
        linetilde_01_keepramp = 1;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        numberobj_01_currentFormat = 6;
        numberobj_01_lastValue = 0;
        numberobj_02_currentFormat = 6;
        numberobj_02_lastValue = 0;
        numberobj_03_currentFormat = 6;
        numberobj_03_lastValue = 0;
        linetilde_01_currentValue = 1;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number dspexpr_01_in1;
        number dspexpr_01_in2;
        number dspexpr_02_in1;
        number dspexpr_02_in2;
        number numberobj_01_value;
        number numberobj_02_value;
        list scale_01_input;
        number scale_01_inlow;
        number scale_01_inhigh;
        number scale_01_outlow;
        number scale_01_outhigh;
        number scale_01_power;
        list scale_01_out;
        number numberobj_03_value;
        number expr_01_in1;
        number expr_01_out1;
        list linetilde_01_segments;
        number linetilde_01_time;
        number linetilde_01_keepramp;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[1];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Int numberobj_01_currentFormat;
        number numberobj_01_lastValue;
        Int numberobj_02_currentFormat;
        number numberobj_02_lastValue;
        Int numberobj_03_currentFormat;
        number numberobj_03_lastValue;
        list linetilde_01_activeRamps;
        number linetilde_01_currentValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_190 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_190()
    {
    }
    
    ~RNBOSubpatcher_190()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -62043057, false);
    }
    
    SampleIndex currentsampletime() {
        return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
    }
    
    number mstosamps(MillisecondTime ms) {
        return ms * this->sr * 0.001;
    }
    
    inline number safesqrt(number num) {
        return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
    }
    
    Index vectorsize() const {
        return this->vs;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        this->linetilde_02_perform(this->signals[0], n);
    
        this->filtercoeff_01_perform(
            this->signals[0],
            this->filtercoeff_01_gain,
            this->filtercoeff_01_q,
            this->signals[1],
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->signals[5],
            n
        );
    
        this->biquad_tilde_02_perform(
            in2,
            this->signals[1],
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->signals[5],
            out2,
            n
        );
    
        this->biquad_tilde_01_perform(
            in1,
            this->signals[1],
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->signals[5],
            out1,
            n
        );
    
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 6; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->filtercoeff_01_dspsetup(forceDSPSetup);
        this->biquad_tilde_02_dspsetup(forceDSPSetup);
        this->biquad_tilde_01_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -62043057:
            {
            this->linetilde_02_target_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("LowCut~/number_obj-37") == objectId)
                this->numberobj_04_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("LowCut~/number_obj-37") == objectId)
                this->numberobj_04_format_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("LowCut~/number_obj-37"):
            {
            return "LowCut~/number_obj-37";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void numberobj_04_valin_set(number v) {
        this->numberobj_04_value_set(v);
    }
    
    void numberobj_04_format_set(number v) {
        this->numberobj_04_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_02_out1_bang_bang() {
        this->numberobj_04_value_bang();
    }
    
    void eventinlet_02_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_04_value_set(converted);
        }
    }
    
    void linetilde_02_target_bang() {}
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->numberobj_04_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
    void linetilde_02_time_set(number v) {
        this->linetilde_02_time = v;
    }
    
    void linetilde_02_segments_set(const list& v) {
        this->linetilde_02_segments = jsCreateListCopy(v);
    
        if ((bool)(v->length)) {
            if (v->length == 1 && this->linetilde_02_time == 0) {
                this->linetilde_02_activeRamps->length = 0;
                this->linetilde_02_currentValue = v[0];
            } else {
                auto currentTime = this->currentsampletime();
                number lastRampValue = this->linetilde_02_currentValue;
                number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;
    
                for (Index i = 0; i < this->linetilde_02_activeRamps->length; i += 3) {
                    rampEnd = this->linetilde_02_activeRamps[(Index)(i + 2)];
    
                    if (rampEnd > currentTime) {
                        this->linetilde_02_activeRamps[(Index)(i + 2)] = currentTime;
                        number diff = rampEnd - currentTime;
                        number valueDiff = diff * this->linetilde_02_activeRamps[(Index)(i + 1)];
                        lastRampValue = this->linetilde_02_activeRamps[(Index)i] - valueDiff;
                        this->linetilde_02_activeRamps[(Index)i] = lastRampValue;
                        this->linetilde_02_activeRamps->length = i + 3;
                        rampEnd = currentTime;
                    } else {
                        lastRampValue = this->linetilde_02_activeRamps[(Index)i];
                    }
                }
    
                if (rampEnd < currentTime) {
                    this->linetilde_02_activeRamps->push(lastRampValue);
                    this->linetilde_02_activeRamps->push(0);
                    this->linetilde_02_activeRamps->push(currentTime);
                }
    
                number lastRampEnd = currentTime;
    
                for (Index i = 0; i < v->length; i += 2) {
                    number destinationValue = v[(Index)i];
                    number inc = 0;
                    number rampTimeInSamples;
    
                    if (v->length > i + 1) {
                        rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);
    
                        if ((bool)(this->linetilde_02_keepramp)) {
                            this->linetilde_02_time_set(v[(Index)(i + 1)]);
                        }
                    } else {
                        rampTimeInSamples = this->mstosamps(this->linetilde_02_time);
                    }
    
                    if (rampTimeInSamples <= 0) {
                        rampTimeInSamples = 1;
                    }
    
                    inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                    lastRampEnd += rampTimeInSamples;
                    this->linetilde_02_activeRamps->push(destinationValue);
                    this->linetilde_02_activeRamps->push(inc);
                    this->linetilde_02_activeRamps->push(lastRampEnd);
                    lastRampValue = destinationValue;
                }
            }
        }
    }
    
    void numberobj_04_output_set(number v) {
        {
            list converted = {v};
            this->linetilde_02_segments_set(converted);
        }
    }
    
    void numberobj_04_value_set(number v) {
        this->numberobj_04_value_setter(v);
        v = this->numberobj_04_value;
        number localvalue = v;
    
        if (this->numberobj_04_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("LowCut~/number_obj-37"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_04_output_set(localvalue);
    }
    
    void eventinlet_02_out1_number_set(number v) {
        this->numberobj_04_value_set(v);
    }
    
    void numberobj_04_value_bang() {
        number v = this->numberobj_04_value;
        number localvalue = v;
    
        if (this->numberobj_04_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("LowCut~/number_obj-37"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_04_output_set(localvalue);
    }
    
    void linetilde_02_perform(SampleValue * out, Index n) {
        auto __linetilde_02_time = this->linetilde_02_time;
        auto __linetilde_02_keepramp = this->linetilde_02_keepramp;
        auto __linetilde_02_currentValue = this->linetilde_02_currentValue;
        Index i = 0;
    
        if ((bool)(this->linetilde_02_activeRamps->length)) {
            while ((bool)(this->linetilde_02_activeRamps->length) && i < n) {
                number destinationValue = this->linetilde_02_activeRamps[0];
                number inc = this->linetilde_02_activeRamps[1];
                number rampTimeInSamples = this->linetilde_02_activeRamps[2] - this->audioProcessSampleCount - i;
                number val = __linetilde_02_currentValue;
    
                while (rampTimeInSamples > 0 && i < n) {
                    out[(Index)i] = val;
                    val += inc;
                    i++;
                    rampTimeInSamples--;
                }
    
                if (rampTimeInSamples <= 0) {
                    val = destinationValue;
                    this->linetilde_02_activeRamps->splice(0, 3);
    
                    if ((bool)(!(bool)(this->linetilde_02_activeRamps->length))) {
                        this->getEngine()->scheduleClockEventWithValue(
                            this,
                            -62043057,
                            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                            0
                        );;
    
                        if ((bool)(!(bool)(__linetilde_02_keepramp))) {
                            __linetilde_02_time = 0;
                        }
                    }
                }
    
                __linetilde_02_currentValue = val;
            }
        }
    
        while (i < n) {
            out[(Index)i] = __linetilde_02_currentValue;
            i++;
        }
    
        this->linetilde_02_currentValue = __linetilde_02_currentValue;
        this->linetilde_02_time = __linetilde_02_time;
    }
    
    void filtercoeff_01_perform(
        const Sample * frequency,
        number gain,
        number q,
        SampleValue * a0,
        SampleValue * a1,
        SampleValue * a2,
        SampleValue * b1,
        SampleValue * b2,
        Index n
    ) {
        RNBO_UNUSED(q);
        RNBO_UNUSED(gain);
        auto __filtercoeff_01_activeResamp = this->filtercoeff_01_activeResamp;
        auto __filtercoeff_01_resamp_counter = this->filtercoeff_01_resamp_counter;
        auto __filtercoeff_01_K_EPSILON = this->filtercoeff_01_K_EPSILON;
    
        for (Index i = 0; i < n; i++) {
            number local_q = 1;
            number local_gain = 1;
    
            if (local_gain < 0)
                local_gain = 0;
    
            number local_frequency = frequency[(Index)i];
    
            if (local_q < __filtercoeff_01_K_EPSILON)
                local_q = __filtercoeff_01_K_EPSILON;
    
            local_frequency = (local_frequency > this->sr * 0.5 ? this->sr * 0.5 : (local_frequency < 1 ? 1 : local_frequency));
            __filtercoeff_01_resamp_counter--;
    
            if (__filtercoeff_01_resamp_counter <= 0) {
                __filtercoeff_01_resamp_counter = __filtercoeff_01_activeResamp;
                this->filtercoeff_01_updateTerms(local_frequency, local_gain, local_q);
            }
    
            a0[(Index)i] = this->filtercoeff_01_la0;
            a1[(Index)i] = this->filtercoeff_01_la1;
            a2[(Index)i] = this->filtercoeff_01_la2;
            b1[(Index)i] = this->filtercoeff_01_lb1;
            b2[(Index)i] = this->filtercoeff_01_lb2;
        }
    
        this->filtercoeff_01_resamp_counter = __filtercoeff_01_resamp_counter;
    }
    
    void biquad_tilde_02_perform(
        const Sample * x,
        const Sample * a0,
        const Sample * a1,
        const Sample * a2,
        const Sample * b1,
        const Sample * b2,
        SampleValue * out1,
        Index n
    ) {
        auto __biquad_tilde_02_y2 = this->biquad_tilde_02_y2;
        auto __biquad_tilde_02_y1 = this->biquad_tilde_02_y1;
        auto __biquad_tilde_02_x2 = this->biquad_tilde_02_x2;
        auto __biquad_tilde_02_x1 = this->biquad_tilde_02_x1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_02_x1 * a1[(Index)i] + __biquad_tilde_02_x2 * a2[(Index)i] - (__biquad_tilde_02_y1 * b1[(Index)i] + __biquad_tilde_02_y2 * b2[(Index)i]);
            __biquad_tilde_02_x2 = __biquad_tilde_02_x1;
            __biquad_tilde_02_x1 = x[(Index)i];
            __biquad_tilde_02_y2 = __biquad_tilde_02_y1;
            __biquad_tilde_02_y1 = tmp;
            out1[(Index)i] = tmp;
        }
    
        this->biquad_tilde_02_x1 = __biquad_tilde_02_x1;
        this->biquad_tilde_02_x2 = __biquad_tilde_02_x2;
        this->biquad_tilde_02_y1 = __biquad_tilde_02_y1;
        this->biquad_tilde_02_y2 = __biquad_tilde_02_y2;
    }
    
    void biquad_tilde_01_perform(
        const Sample * x,
        const Sample * a0,
        const Sample * a1,
        const Sample * a2,
        const Sample * b1,
        const Sample * b2,
        SampleValue * out1,
        Index n
    ) {
        auto __biquad_tilde_01_y2 = this->biquad_tilde_01_y2;
        auto __biquad_tilde_01_y1 = this->biquad_tilde_01_y1;
        auto __biquad_tilde_01_x2 = this->biquad_tilde_01_x2;
        auto __biquad_tilde_01_x1 = this->biquad_tilde_01_x1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_01_x1 * a1[(Index)i] + __biquad_tilde_01_x2 * a2[(Index)i] - (__biquad_tilde_01_y1 * b1[(Index)i] + __biquad_tilde_01_y2 * b2[(Index)i]);
            __biquad_tilde_01_x2 = __biquad_tilde_01_x1;
            __biquad_tilde_01_x1 = x[(Index)i];
            __biquad_tilde_01_y2 = __biquad_tilde_01_y1;
            __biquad_tilde_01_y1 = tmp;
            out1[(Index)i] = tmp;
        }
    
        this->biquad_tilde_01_x1 = __biquad_tilde_01_x1;
        this->biquad_tilde_01_x2 = __biquad_tilde_01_x2;
        this->biquad_tilde_01_y1 = __biquad_tilde_01_y1;
        this->biquad_tilde_01_y2 = __biquad_tilde_01_y2;
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void numberobj_04_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_04_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_04_value = localvalue;
    }
    
    void biquad_tilde_01_reset() {
        this->biquad_tilde_01_x1 = 0;
        this->biquad_tilde_01_x2 = 0;
        this->biquad_tilde_01_y1 = 0;
        this->biquad_tilde_01_y2 = 0;
    }
    
    void biquad_tilde_01_dspsetup(bool force) {
        if ((bool)(this->biquad_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->biquad_tilde_01_reset();
        this->biquad_tilde_01_setupDone = true;
    }
    
    void biquad_tilde_02_reset() {
        this->biquad_tilde_02_x1 = 0;
        this->biquad_tilde_02_x2 = 0;
        this->biquad_tilde_02_y1 = 0;
        this->biquad_tilde_02_y2 = 0;
    }
    
    void biquad_tilde_02_dspsetup(bool force) {
        if ((bool)(this->biquad_tilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->biquad_tilde_02_reset();
        this->biquad_tilde_02_setupDone = true;
    }
    
    void numberobj_04_init() {
        this->numberobj_04_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("LowCut~/number_obj-37"), 1, this->_currentTime);
    }
    
    void numberobj_04_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_04_value;
    }
    
    void numberobj_04_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_04_value_set(preset["value"]);
    }
    
    array<number, 5> filtercoeff_01_localop_next(number frequency, number q, number gain, number type) {
        number omega = frequency * this->filtercoeff_01_localop_twopi_over_sr;
        this->filtercoeff_01_localop_cs = rnbo_cos(omega);
        this->filtercoeff_01_localop_sn = rnbo_sin(omega);
        this->filtercoeff_01_localop_one_over_gain = (gain >= 0 ? (number)1 / gain : 0.0);
        this->filtercoeff_01_localop_one_over_q = (number)1 / q;
        this->filtercoeff_01_localop_alpha = this->filtercoeff_01_localop_sn * 0.5 * this->filtercoeff_01_localop_one_over_q;
    
        switch ((int)type) {
        case 5:
            {
            this->filtercoeff_01_localop_A = this->safesqrt(gain);
    
            this->filtercoeff_01_localop_beta = this->safesqrt(
                (this->filtercoeff_01_localop_A * this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_one_over_q - (this->filtercoeff_01_localop_A - 1.) * (this->filtercoeff_01_localop_A - 1.)
            );
    
            this->filtercoeff_01_localop_b0 = (number)1 / (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn);
            break;
            }
        case 6:
            {
            this->filtercoeff_01_localop_A = this->safesqrt(gain);
    
            this->filtercoeff_01_localop_beta = this->safesqrt(
                (this->filtercoeff_01_localop_A * this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_one_over_q - (this->filtercoeff_01_localop_A - 1.) * (this->filtercoeff_01_localop_A - 1.)
            );
    
            this->filtercoeff_01_localop_b0 = (number)1 / (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn);
            break;
            }
        case 4:
            {
            this->filtercoeff_01_localop_A = this->safesqrt(gain);
            this->filtercoeff_01_localop_one_over_a = (this->filtercoeff_01_localop_A == 0 ? 0 : (number)1 / this->filtercoeff_01_localop_A);
            this->filtercoeff_01_localop_b0 = (number)1 / (1. + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_a);
            break;
            }
        case 9:
        case 10:
        case 11:
        case 13:
        case 14:
            {
            this->filtercoeff_01_localop_b0 = (number)1 / (1. + this->filtercoeff_01_localop_alpha);
            this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
            break;
            }
        default:
            {
            this->filtercoeff_01_localop_b0 = (number)1 / (1. + this->filtercoeff_01_localop_alpha);
            break;
            }
        }
    
        switch ((int)type) {
        case 0:
            {
            this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. - this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la1 = (1. - this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
            break;
            }
        case 1:
            {
            this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. + this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la1 = -(1. + this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
            break;
            }
        case 2:
            {
            this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la1 = 0.;
            this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
            break;
            }
        case 7:
            {
            this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * q * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la1 = 0.;
            this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * q * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
            break;
            }
        case 3:
            {
            this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_b0;
            break;
            }
        case 8:
            {
            this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = this->filtercoeff_01_localop_la0 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la2 = 1.0;
            break;
            }
        case 4:
            {
            this->filtercoeff_01_localop_la0 = (1. + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_A) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la2 = (1. - this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_A) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_a) * this->filtercoeff_01_localop_b0;
            break;
            }
        case 5:
            {
            this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la1 = 2. * this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A - 1 - (this->filtercoeff_01_localop_A + 1) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb1 = -2. * (this->filtercoeff_01_localop_A - 1. + (this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
            break;
            }
        case 6:
            {
            this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la1 = -2. * this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A - 1. + (this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb1 = 2. * (this->filtercoeff_01_localop_A - 1. - (this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
            break;
            }
        case 9:
            {
            this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
            this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. - this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0g;
            this->filtercoeff_01_localop_la1 = (1. - this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0g;
            this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
            break;
            }
        case 10:
            {
            this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
            this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. + this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0g;
            this->filtercoeff_01_localop_la1 = -(1. + this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0g;
            this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
            break;
            }
        case 11:
            {
            this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * gain * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la1 = 0.;
            this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * gain * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
            break;
            }
        case 13:
            {
            this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * gain * q * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la1 = 0.;
            this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * gain * q * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
            break;
            }
        case 12:
            {
            this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
            this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs;
            this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la1 *= this->filtercoeff_01_localop_b0g;
            this->filtercoeff_01_localop_lb1 *= this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_b0g;
            this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_b0g;
            break;
            }
        case 14:
            {
            this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
            this->filtercoeff_01_localop_la0 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0g;
            this->filtercoeff_01_localop_la1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0g;
            this->filtercoeff_01_localop_la2 = gain;
            this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
            this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
            break;
            }
        case 15:
            {
            this->filtercoeff_01_localop_la0 = 1;
            this->filtercoeff_01_localop_la1 = 0;
            this->filtercoeff_01_localop_la2 = 0;
            this->filtercoeff_01_localop_lb1 = 0;
            this->filtercoeff_01_localop_lb2 = 0;
            }
        default:
            {
            break;
            }
        }
    
        return {
            this->filtercoeff_01_localop_la0,
            this->filtercoeff_01_localop_la1,
            this->filtercoeff_01_localop_la2,
            this->filtercoeff_01_localop_lb1,
            this->filtercoeff_01_localop_lb2
        };
    }
    
    void filtercoeff_01_localop_dspsetup() {
        this->filtercoeff_01_localop_twopi_over_sr = (number)6.283185307179586 / this->sr;
    }
    
    void filtercoeff_01_localop_reset() {
        this->filtercoeff_01_localop_twopi_over_sr = 0;
        this->filtercoeff_01_localop_cs = 0;
        this->filtercoeff_01_localop_sn = 0;
        this->filtercoeff_01_localop_one_over_gain = 0;
        this->filtercoeff_01_localop_one_over_q = 0;
        this->filtercoeff_01_localop_alpha = 0;
        this->filtercoeff_01_localop_beta = 0;
        this->filtercoeff_01_localop_b0 = 0;
        this->filtercoeff_01_localop_b0g = 0;
        this->filtercoeff_01_localop_A = 0;
        this->filtercoeff_01_localop_one_over_a = 0;
        this->filtercoeff_01_localop_la0 = 0;
        this->filtercoeff_01_localop_la1 = 0;
        this->filtercoeff_01_localop_la2 = 0;
        this->filtercoeff_01_localop_lb1 = 0;
        this->filtercoeff_01_localop_lb2 = 0;
    }
    
    void filtercoeff_01_updateTerms(number local_frequency, number local_gain, number local_q) {
        if ((bool)(this->filtercoeff_01_force_update) || local_frequency != this->filtercoeff_01_last_frequency || local_q != this->filtercoeff_01_last_q || local_gain != this->filtercoeff_01_last_gain || this->filtercoeff_01_type != this->filtercoeff_01_last_type) {
            array<number, 5> tmp = this->filtercoeff_01_localop_next(local_frequency, local_q, local_gain, this->filtercoeff_01_type);
            this->filtercoeff_01_la0 = tmp[0];
            this->filtercoeff_01_la1 = tmp[1];
            this->filtercoeff_01_la2 = tmp[2];
            this->filtercoeff_01_lb1 = tmp[3];
            this->filtercoeff_01_lb2 = tmp[4];
            this->filtercoeff_01_last_frequency = local_frequency;
            this->filtercoeff_01_last_q = local_q;
            this->filtercoeff_01_last_gain = local_gain;
            this->filtercoeff_01_last_type = this->filtercoeff_01_type;
            this->filtercoeff_01_force_update = false;
        }
    }
    
    void filtercoeff_01_dspsetup(bool force) {
        if ((bool)(this->filtercoeff_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        {
            this->filtercoeff_01_activeResamp = this->vectorsize();
        }
    
        this->filtercoeff_01_resamp_counter = 0;
        this->filtercoeff_01_la0 = 0.;
        this->filtercoeff_01_la1 = 0.;
        this->filtercoeff_01_la2 = 0.;
        this->filtercoeff_01_lb1 = 0.;
        this->filtercoeff_01_lb2 = 0.;
        this->filtercoeff_01_last_frequency = -1.;
        this->filtercoeff_01_last_q = -1.;
        this->filtercoeff_01_last_gain = -1.;
        this->filtercoeff_01_last_type = this->filtercoeff_01_type;
        this->filtercoeff_01_force_update = true;
        this->filtercoeff_01_setupDone = true;
        this->filtercoeff_01_localop_dspsetup();
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        biquad_tilde_01_x = 0;
        biquad_tilde_01_a0 = 0;
        biquad_tilde_01_a1 = 0;
        biquad_tilde_01_a2 = 0;
        biquad_tilde_01_b1 = 0;
        biquad_tilde_01_b2 = 0;
        biquad_tilde_02_x = 0;
        biquad_tilde_02_a0 = 0;
        biquad_tilde_02_a1 = 0;
        biquad_tilde_02_a2 = 0;
        biquad_tilde_02_b1 = 0;
        biquad_tilde_02_b2 = 0;
        numberobj_04_value = 0;
        numberobj_04_value_setter(numberobj_04_value);
        linetilde_02_time = 10;
        linetilde_02_keepramp = 1;
        filtercoeff_01_frequency = 1000;
        filtercoeff_01_gain = 1;
        filtercoeff_01_q = 1;
        filtercoeff_01_type = 1;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        signals[4] = nullptr;
        signals[5] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        biquad_tilde_01_x1 = 0;
        biquad_tilde_01_x2 = 0;
        biquad_tilde_01_y1 = 0;
        biquad_tilde_01_y2 = 0;
        biquad_tilde_01_setupDone = false;
        biquad_tilde_02_x1 = 0;
        biquad_tilde_02_x2 = 0;
        biquad_tilde_02_y1 = 0;
        biquad_tilde_02_y2 = 0;
        biquad_tilde_02_setupDone = false;
        numberobj_04_currentFormat = 6;
        numberobj_04_lastValue = 0;
        linetilde_02_currentValue = 20;
        filtercoeff_01_K_EPSILON = 1e-9;
        filtercoeff_01_setupDone = false;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number biquad_tilde_01_x;
        number biquad_tilde_01_a0;
        number biquad_tilde_01_a1;
        number biquad_tilde_01_a2;
        number biquad_tilde_01_b1;
        number biquad_tilde_01_b2;
        number biquad_tilde_02_x;
        number biquad_tilde_02_a0;
        number biquad_tilde_02_a1;
        number biquad_tilde_02_a2;
        number biquad_tilde_02_b1;
        number biquad_tilde_02_b2;
        number numberobj_04_value;
        list linetilde_02_segments;
        number linetilde_02_time;
        number linetilde_02_keepramp;
        number filtercoeff_01_frequency;
        number filtercoeff_01_gain;
        number filtercoeff_01_q;
        Int filtercoeff_01_type;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[6];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number biquad_tilde_01_x1;
        number biquad_tilde_01_x2;
        number biquad_tilde_01_y1;
        number biquad_tilde_01_y2;
        bool biquad_tilde_01_setupDone;
        number biquad_tilde_02_x1;
        number biquad_tilde_02_x2;
        number biquad_tilde_02_y1;
        number biquad_tilde_02_y2;
        bool biquad_tilde_02_setupDone;
        Int numberobj_04_currentFormat;
        number numberobj_04_lastValue;
        list linetilde_02_activeRamps;
        number linetilde_02_currentValue;
        number filtercoeff_01_resamp_counter;
        number filtercoeff_01_activeResamp;
        number filtercoeff_01_K_EPSILON;
        number filtercoeff_01_la0;
        number filtercoeff_01_la1;
        number filtercoeff_01_la2;
        number filtercoeff_01_lb1;
        number filtercoeff_01_lb2;
        number filtercoeff_01_last_frequency;
        number filtercoeff_01_last_q;
        number filtercoeff_01_last_gain;
        Int filtercoeff_01_last_type;
        bool filtercoeff_01_force_update;
        number filtercoeff_01_localop_twopi_over_sr;
        number filtercoeff_01_localop_cs;
        number filtercoeff_01_localop_sn;
        number filtercoeff_01_localop_one_over_gain;
        number filtercoeff_01_localop_one_over_q;
        number filtercoeff_01_localop_alpha;
        number filtercoeff_01_localop_beta;
        number filtercoeff_01_localop_b0;
        number filtercoeff_01_localop_b0g;
        number filtercoeff_01_localop_A;
        number filtercoeff_01_localop_one_over_a;
        number filtercoeff_01_localop_la0;
        number filtercoeff_01_localop_la1;
        number filtercoeff_01_localop_la2;
        number filtercoeff_01_localop_lb1;
        number filtercoeff_01_localop_lb2;
        bool filtercoeff_01_setupDone;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_191 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_191()
    {
    }
    
    ~RNBOSubpatcher_191()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -62043057, false);
    }
    
    SampleIndex currentsampletime() {
        return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
    }
    
    number mstosamps(MillisecondTime ms) {
        return ms * this->sr * 0.001;
    }
    
    inline number safesqrt(number num) {
        return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
    }
    
    Index vectorsize() const {
        return this->vs;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        this->linetilde_03_perform(this->signals[0], n);
    
        this->filtercoeff_02_perform(
            this->signals[0],
            this->filtercoeff_02_gain,
            this->filtercoeff_02_q,
            this->signals[1],
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->signals[5],
            n
        );
    
        this->biquad_tilde_04_perform(
            in2,
            this->signals[1],
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->signals[5],
            out2,
            n
        );
    
        this->biquad_tilde_03_perform(
            in1,
            this->signals[1],
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->signals[5],
            out1,
            n
        );
    
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 6; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->filtercoeff_02_dspsetup(forceDSPSetup);
        this->biquad_tilde_04_dspsetup(forceDSPSetup);
        this->biquad_tilde_03_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -62043057:
            {
            this->linetilde_03_target_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("HighCut~/number_obj-37") == objectId)
                this->numberobj_05_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("HighCut~/number_obj-37") == objectId)
                this->numberobj_05_format_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("HighCut~/number_obj-37"):
            {
            return "HighCut~/number_obj-37";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void numberobj_05_valin_set(number v) {
        this->numberobj_05_value_set(v);
    }
    
    void numberobj_05_format_set(number v) {
        this->numberobj_05_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_03_out1_bang_bang() {
        this->numberobj_05_value_bang();
    }
    
    void eventinlet_03_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_05_value_set(converted);
        }
    }
    
    void linetilde_03_target_bang() {}
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->numberobj_05_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
    void linetilde_03_time_set(number v) {
        this->linetilde_03_time = v;
    }
    
    void linetilde_03_segments_set(const list& v) {
        this->linetilde_03_segments = jsCreateListCopy(v);
    
        if ((bool)(v->length)) {
            if (v->length == 1 && this->linetilde_03_time == 0) {
                this->linetilde_03_activeRamps->length = 0;
                this->linetilde_03_currentValue = v[0];
            } else {
                auto currentTime = this->currentsampletime();
                number lastRampValue = this->linetilde_03_currentValue;
                number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;
    
                for (Index i = 0; i < this->linetilde_03_activeRamps->length; i += 3) {
                    rampEnd = this->linetilde_03_activeRamps[(Index)(i + 2)];
    
                    if (rampEnd > currentTime) {
                        this->linetilde_03_activeRamps[(Index)(i + 2)] = currentTime;
                        number diff = rampEnd - currentTime;
                        number valueDiff = diff * this->linetilde_03_activeRamps[(Index)(i + 1)];
                        lastRampValue = this->linetilde_03_activeRamps[(Index)i] - valueDiff;
                        this->linetilde_03_activeRamps[(Index)i] = lastRampValue;
                        this->linetilde_03_activeRamps->length = i + 3;
                        rampEnd = currentTime;
                    } else {
                        lastRampValue = this->linetilde_03_activeRamps[(Index)i];
                    }
                }
    
                if (rampEnd < currentTime) {
                    this->linetilde_03_activeRamps->push(lastRampValue);
                    this->linetilde_03_activeRamps->push(0);
                    this->linetilde_03_activeRamps->push(currentTime);
                }
    
                number lastRampEnd = currentTime;
    
                for (Index i = 0; i < v->length; i += 2) {
                    number destinationValue = v[(Index)i];
                    number inc = 0;
                    number rampTimeInSamples;
    
                    if (v->length > i + 1) {
                        rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);
    
                        if ((bool)(this->linetilde_03_keepramp)) {
                            this->linetilde_03_time_set(v[(Index)(i + 1)]);
                        }
                    } else {
                        rampTimeInSamples = this->mstosamps(this->linetilde_03_time);
                    }
    
                    if (rampTimeInSamples <= 0) {
                        rampTimeInSamples = 1;
                    }
    
                    inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                    lastRampEnd += rampTimeInSamples;
                    this->linetilde_03_activeRamps->push(destinationValue);
                    this->linetilde_03_activeRamps->push(inc);
                    this->linetilde_03_activeRamps->push(lastRampEnd);
                    lastRampValue = destinationValue;
                }
            }
        }
    }
    
    void numberobj_05_output_set(number v) {
        {
            list converted = {v};
            this->linetilde_03_segments_set(converted);
        }
    }
    
    void numberobj_05_value_set(number v) {
        this->numberobj_05_value_setter(v);
        v = this->numberobj_05_value;
        number localvalue = v;
    
        if (this->numberobj_05_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("HighCut~/number_obj-37"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_05_output_set(localvalue);
    }
    
    void eventinlet_03_out1_number_set(number v) {
        this->numberobj_05_value_set(v);
    }
    
    void numberobj_05_value_bang() {
        number v = this->numberobj_05_value;
        number localvalue = v;
    
        if (this->numberobj_05_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("HighCut~/number_obj-37"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_05_output_set(localvalue);
    }
    
    void linetilde_03_perform(SampleValue * out, Index n) {
        auto __linetilde_03_time = this->linetilde_03_time;
        auto __linetilde_03_keepramp = this->linetilde_03_keepramp;
        auto __linetilde_03_currentValue = this->linetilde_03_currentValue;
        Index i = 0;
    
        if ((bool)(this->linetilde_03_activeRamps->length)) {
            while ((bool)(this->linetilde_03_activeRamps->length) && i < n) {
                number destinationValue = this->linetilde_03_activeRamps[0];
                number inc = this->linetilde_03_activeRamps[1];
                number rampTimeInSamples = this->linetilde_03_activeRamps[2] - this->audioProcessSampleCount - i;
                number val = __linetilde_03_currentValue;
    
                while (rampTimeInSamples > 0 && i < n) {
                    out[(Index)i] = val;
                    val += inc;
                    i++;
                    rampTimeInSamples--;
                }
    
                if (rampTimeInSamples <= 0) {
                    val = destinationValue;
                    this->linetilde_03_activeRamps->splice(0, 3);
    
                    if ((bool)(!(bool)(this->linetilde_03_activeRamps->length))) {
                        this->getEngine()->scheduleClockEventWithValue(
                            this,
                            -62043057,
                            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                            0
                        );;
    
                        if ((bool)(!(bool)(__linetilde_03_keepramp))) {
                            __linetilde_03_time = 0;
                        }
                    }
                }
    
                __linetilde_03_currentValue = val;
            }
        }
    
        while (i < n) {
            out[(Index)i] = __linetilde_03_currentValue;
            i++;
        }
    
        this->linetilde_03_currentValue = __linetilde_03_currentValue;
        this->linetilde_03_time = __linetilde_03_time;
    }
    
    void filtercoeff_02_perform(
        const Sample * frequency,
        number gain,
        number q,
        SampleValue * a0,
        SampleValue * a1,
        SampleValue * a2,
        SampleValue * b1,
        SampleValue * b2,
        Index n
    ) {
        RNBO_UNUSED(q);
        RNBO_UNUSED(gain);
        auto __filtercoeff_02_activeResamp = this->filtercoeff_02_activeResamp;
        auto __filtercoeff_02_resamp_counter = this->filtercoeff_02_resamp_counter;
        auto __filtercoeff_02_K_EPSILON = this->filtercoeff_02_K_EPSILON;
    
        for (Index i = 0; i < n; i++) {
            number local_q = 1;
            number local_gain = 1;
    
            if (local_gain < 0)
                local_gain = 0;
    
            number local_frequency = frequency[(Index)i];
    
            if (local_q < __filtercoeff_02_K_EPSILON)
                local_q = __filtercoeff_02_K_EPSILON;
    
            local_frequency = (local_frequency > this->sr * 0.5 ? this->sr * 0.5 : (local_frequency < 1 ? 1 : local_frequency));
            __filtercoeff_02_resamp_counter--;
    
            if (__filtercoeff_02_resamp_counter <= 0) {
                __filtercoeff_02_resamp_counter = __filtercoeff_02_activeResamp;
                this->filtercoeff_02_updateTerms(local_frequency, local_gain, local_q);
            }
    
            a0[(Index)i] = this->filtercoeff_02_la0;
            a1[(Index)i] = this->filtercoeff_02_la1;
            a2[(Index)i] = this->filtercoeff_02_la2;
            b1[(Index)i] = this->filtercoeff_02_lb1;
            b2[(Index)i] = this->filtercoeff_02_lb2;
        }
    
        this->filtercoeff_02_resamp_counter = __filtercoeff_02_resamp_counter;
    }
    
    void biquad_tilde_04_perform(
        const Sample * x,
        const Sample * a0,
        const Sample * a1,
        const Sample * a2,
        const Sample * b1,
        const Sample * b2,
        SampleValue * out1,
        Index n
    ) {
        auto __biquad_tilde_04_y2 = this->biquad_tilde_04_y2;
        auto __biquad_tilde_04_y1 = this->biquad_tilde_04_y1;
        auto __biquad_tilde_04_x2 = this->biquad_tilde_04_x2;
        auto __biquad_tilde_04_x1 = this->biquad_tilde_04_x1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_04_x1 * a1[(Index)i] + __biquad_tilde_04_x2 * a2[(Index)i] - (__biquad_tilde_04_y1 * b1[(Index)i] + __biquad_tilde_04_y2 * b2[(Index)i]);
            __biquad_tilde_04_x2 = __biquad_tilde_04_x1;
            __biquad_tilde_04_x1 = x[(Index)i];
            __biquad_tilde_04_y2 = __biquad_tilde_04_y1;
            __biquad_tilde_04_y1 = tmp;
            out1[(Index)i] = tmp;
        }
    
        this->biquad_tilde_04_x1 = __biquad_tilde_04_x1;
        this->biquad_tilde_04_x2 = __biquad_tilde_04_x2;
        this->biquad_tilde_04_y1 = __biquad_tilde_04_y1;
        this->biquad_tilde_04_y2 = __biquad_tilde_04_y2;
    }
    
    void biquad_tilde_03_perform(
        const Sample * x,
        const Sample * a0,
        const Sample * a1,
        const Sample * a2,
        const Sample * b1,
        const Sample * b2,
        SampleValue * out1,
        Index n
    ) {
        auto __biquad_tilde_03_y2 = this->biquad_tilde_03_y2;
        auto __biquad_tilde_03_y1 = this->biquad_tilde_03_y1;
        auto __biquad_tilde_03_x2 = this->biquad_tilde_03_x2;
        auto __biquad_tilde_03_x1 = this->biquad_tilde_03_x1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_03_x1 * a1[(Index)i] + __biquad_tilde_03_x2 * a2[(Index)i] - (__biquad_tilde_03_y1 * b1[(Index)i] + __biquad_tilde_03_y2 * b2[(Index)i]);
            __biquad_tilde_03_x2 = __biquad_tilde_03_x1;
            __biquad_tilde_03_x1 = x[(Index)i];
            __biquad_tilde_03_y2 = __biquad_tilde_03_y1;
            __biquad_tilde_03_y1 = tmp;
            out1[(Index)i] = tmp;
        }
    
        this->biquad_tilde_03_x1 = __biquad_tilde_03_x1;
        this->biquad_tilde_03_x2 = __biquad_tilde_03_x2;
        this->biquad_tilde_03_y1 = __biquad_tilde_03_y1;
        this->biquad_tilde_03_y2 = __biquad_tilde_03_y2;
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void numberobj_05_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_05_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_05_value = localvalue;
    }
    
    void biquad_tilde_03_reset() {
        this->biquad_tilde_03_x1 = 0;
        this->biquad_tilde_03_x2 = 0;
        this->biquad_tilde_03_y1 = 0;
        this->biquad_tilde_03_y2 = 0;
    }
    
    void biquad_tilde_03_dspsetup(bool force) {
        if ((bool)(this->biquad_tilde_03_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->biquad_tilde_03_reset();
        this->biquad_tilde_03_setupDone = true;
    }
    
    void biquad_tilde_04_reset() {
        this->biquad_tilde_04_x1 = 0;
        this->biquad_tilde_04_x2 = 0;
        this->biquad_tilde_04_y1 = 0;
        this->biquad_tilde_04_y2 = 0;
    }
    
    void biquad_tilde_04_dspsetup(bool force) {
        if ((bool)(this->biquad_tilde_04_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->biquad_tilde_04_reset();
        this->biquad_tilde_04_setupDone = true;
    }
    
    void numberobj_05_init() {
        this->numberobj_05_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("HighCut~/number_obj-37"), 1, this->_currentTime);
    }
    
    void numberobj_05_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_05_value;
    }
    
    void numberobj_05_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_05_value_set(preset["value"]);
    }
    
    array<number, 5> filtercoeff_02_localop_next(number frequency, number q, number gain, number type) {
        number omega = frequency * this->filtercoeff_02_localop_twopi_over_sr;
        this->filtercoeff_02_localop_cs = rnbo_cos(omega);
        this->filtercoeff_02_localop_sn = rnbo_sin(omega);
        this->filtercoeff_02_localop_one_over_gain = (gain >= 0 ? (number)1 / gain : 0.0);
        this->filtercoeff_02_localop_one_over_q = (number)1 / q;
        this->filtercoeff_02_localop_alpha = this->filtercoeff_02_localop_sn * 0.5 * this->filtercoeff_02_localop_one_over_q;
    
        switch ((int)type) {
        case 5:
            {
            this->filtercoeff_02_localop_A = this->safesqrt(gain);
    
            this->filtercoeff_02_localop_beta = this->safesqrt(
                (this->filtercoeff_02_localop_A * this->filtercoeff_02_localop_A + 1.) * this->filtercoeff_02_localop_one_over_q - (this->filtercoeff_02_localop_A - 1.) * (this->filtercoeff_02_localop_A - 1.)
            );
    
            this->filtercoeff_02_localop_b0 = (number)1 / (this->filtercoeff_02_localop_A + 1. + (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs + this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn);
            break;
            }
        case 6:
            {
            this->filtercoeff_02_localop_A = this->safesqrt(gain);
    
            this->filtercoeff_02_localop_beta = this->safesqrt(
                (this->filtercoeff_02_localop_A * this->filtercoeff_02_localop_A + 1.) * this->filtercoeff_02_localop_one_over_q - (this->filtercoeff_02_localop_A - 1.) * (this->filtercoeff_02_localop_A - 1.)
            );
    
            this->filtercoeff_02_localop_b0 = (number)1 / (this->filtercoeff_02_localop_A + 1. - (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs + this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn);
            break;
            }
        case 4:
            {
            this->filtercoeff_02_localop_A = this->safesqrt(gain);
            this->filtercoeff_02_localop_one_over_a = (this->filtercoeff_02_localop_A == 0 ? 0 : (number)1 / this->filtercoeff_02_localop_A);
            this->filtercoeff_02_localop_b0 = (number)1 / (1. + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_a);
            break;
            }
        case 9:
        case 10:
        case 11:
        case 13:
        case 14:
            {
            this->filtercoeff_02_localop_b0 = (number)1 / (1. + this->filtercoeff_02_localop_alpha);
            this->filtercoeff_02_localop_b0g = (number)1 / (this->filtercoeff_02_localop_one_over_gain + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_gain);
            break;
            }
        default:
            {
            this->filtercoeff_02_localop_b0 = (number)1 / (1. + this->filtercoeff_02_localop_alpha);
            break;
            }
        }
    
        switch ((int)type) {
        case 0:
            {
            this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_la2 = (1. - this->filtercoeff_02_localop_cs) * 0.5 * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la1 = (1. - this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
            break;
            }
        case 1:
            {
            this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_la2 = (1. + this->filtercoeff_02_localop_cs) * 0.5 * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la1 = -(1. + this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
            break;
            }
        case 2:
            {
            this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la1 = 0.;
            this->filtercoeff_02_localop_la2 = -this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
            break;
            }
        case 7:
            {
            this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_alpha * q * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la1 = 0.;
            this->filtercoeff_02_localop_la2 = -this->filtercoeff_02_localop_alpha * q * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
            break;
            }
        case 3:
            {
            this->filtercoeff_02_localop_la1 = this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_la2 = this->filtercoeff_02_localop_b0;
            break;
            }
        case 8:
            {
            this->filtercoeff_02_localop_la1 = this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = this->filtercoeff_02_localop_la0 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la2 = 1.0;
            break;
            }
        case 4:
            {
            this->filtercoeff_02_localop_la0 = (1. + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_A) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la1 = this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la2 = (1. - this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_A) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_a) * this->filtercoeff_02_localop_b0;
            break;
            }
        case 5:
            {
            this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_A * (this->filtercoeff_02_localop_A + 1. - (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs + this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la1 = 2. * this->filtercoeff_02_localop_A * (this->filtercoeff_02_localop_A - 1 - (this->filtercoeff_02_localop_A + 1) * this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la2 = this->filtercoeff_02_localop_A * (this->filtercoeff_02_localop_A + 1. - (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs - this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb1 = -2. * (this->filtercoeff_02_localop_A - 1. + (this->filtercoeff_02_localop_A + 1.) * this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = (this->filtercoeff_02_localop_A + 1. + (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs - this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn) * this->filtercoeff_02_localop_b0;
            break;
            }
        case 6:
            {
            this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_A * (this->filtercoeff_02_localop_A + 1. + (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs + this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la1 = -2. * this->filtercoeff_02_localop_A * (this->filtercoeff_02_localop_A - 1. + (this->filtercoeff_02_localop_A + 1.) * this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la2 = this->filtercoeff_02_localop_A * (this->filtercoeff_02_localop_A + 1. + (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs - this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb1 = 2. * (this->filtercoeff_02_localop_A - 1. - (this->filtercoeff_02_localop_A + 1.) * this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = (this->filtercoeff_02_localop_A + 1. - (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs - this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn) * this->filtercoeff_02_localop_b0;
            break;
            }
        case 9:
            {
            this->filtercoeff_02_localop_b0g = (number)1 / (this->filtercoeff_02_localop_one_over_gain + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_gain);
            this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_la2 = (1. - this->filtercoeff_02_localop_cs) * 0.5 * this->filtercoeff_02_localop_b0g;
            this->filtercoeff_02_localop_la1 = (1. - this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0g;
            this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
            break;
            }
        case 10:
            {
            this->filtercoeff_02_localop_b0g = (number)1 / (this->filtercoeff_02_localop_one_over_gain + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_gain);
            this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_la2 = (1. + this->filtercoeff_02_localop_cs) * 0.5 * this->filtercoeff_02_localop_b0g;
            this->filtercoeff_02_localop_la1 = -(1. + this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0g;
            this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
            break;
            }
        case 11:
            {
            this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_alpha * gain * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la1 = 0.;
            this->filtercoeff_02_localop_la2 = -this->filtercoeff_02_localop_alpha * gain * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
            break;
            }
        case 13:
            {
            this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_alpha * gain * q * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la1 = 0.;
            this->filtercoeff_02_localop_la2 = -this->filtercoeff_02_localop_alpha * gain * q * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
            break;
            }
        case 12:
            {
            this->filtercoeff_02_localop_b0g = (number)1 / (this->filtercoeff_02_localop_one_over_gain + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_gain);
            this->filtercoeff_02_localop_la1 = this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs;
            this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la1 *= this->filtercoeff_02_localop_b0g;
            this->filtercoeff_02_localop_lb1 *= this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_b0g;
            this->filtercoeff_02_localop_la2 = this->filtercoeff_02_localop_b0g;
            break;
            }
        case 14:
            {
            this->filtercoeff_02_localop_b0g = (number)1 / (this->filtercoeff_02_localop_one_over_gain + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_gain);
            this->filtercoeff_02_localop_la0 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0g;
            this->filtercoeff_02_localop_la1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0g;
            this->filtercoeff_02_localop_la2 = gain;
            this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
            this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
            break;
            }
        case 15:
            {
            this->filtercoeff_02_localop_la0 = 1;
            this->filtercoeff_02_localop_la1 = 0;
            this->filtercoeff_02_localop_la2 = 0;
            this->filtercoeff_02_localop_lb1 = 0;
            this->filtercoeff_02_localop_lb2 = 0;
            }
        default:
            {
            break;
            }
        }
    
        return {
            this->filtercoeff_02_localop_la0,
            this->filtercoeff_02_localop_la1,
            this->filtercoeff_02_localop_la2,
            this->filtercoeff_02_localop_lb1,
            this->filtercoeff_02_localop_lb2
        };
    }
    
    void filtercoeff_02_localop_dspsetup() {
        this->filtercoeff_02_localop_twopi_over_sr = (number)6.283185307179586 / this->sr;
    }
    
    void filtercoeff_02_localop_reset() {
        this->filtercoeff_02_localop_twopi_over_sr = 0;
        this->filtercoeff_02_localop_cs = 0;
        this->filtercoeff_02_localop_sn = 0;
        this->filtercoeff_02_localop_one_over_gain = 0;
        this->filtercoeff_02_localop_one_over_q = 0;
        this->filtercoeff_02_localop_alpha = 0;
        this->filtercoeff_02_localop_beta = 0;
        this->filtercoeff_02_localop_b0 = 0;
        this->filtercoeff_02_localop_b0g = 0;
        this->filtercoeff_02_localop_A = 0;
        this->filtercoeff_02_localop_one_over_a = 0;
        this->filtercoeff_02_localop_la0 = 0;
        this->filtercoeff_02_localop_la1 = 0;
        this->filtercoeff_02_localop_la2 = 0;
        this->filtercoeff_02_localop_lb1 = 0;
        this->filtercoeff_02_localop_lb2 = 0;
    }
    
    void filtercoeff_02_updateTerms(number local_frequency, number local_gain, number local_q) {
        if ((bool)(this->filtercoeff_02_force_update) || local_frequency != this->filtercoeff_02_last_frequency || local_q != this->filtercoeff_02_last_q || local_gain != this->filtercoeff_02_last_gain || this->filtercoeff_02_type != this->filtercoeff_02_last_type) {
            array<number, 5> tmp = this->filtercoeff_02_localop_next(local_frequency, local_q, local_gain, this->filtercoeff_02_type);
            this->filtercoeff_02_la0 = tmp[0];
            this->filtercoeff_02_la1 = tmp[1];
            this->filtercoeff_02_la2 = tmp[2];
            this->filtercoeff_02_lb1 = tmp[3];
            this->filtercoeff_02_lb2 = tmp[4];
            this->filtercoeff_02_last_frequency = local_frequency;
            this->filtercoeff_02_last_q = local_q;
            this->filtercoeff_02_last_gain = local_gain;
            this->filtercoeff_02_last_type = this->filtercoeff_02_type;
            this->filtercoeff_02_force_update = false;
        }
    }
    
    void filtercoeff_02_dspsetup(bool force) {
        if ((bool)(this->filtercoeff_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        {
            this->filtercoeff_02_activeResamp = this->vectorsize();
        }
    
        this->filtercoeff_02_resamp_counter = 0;
        this->filtercoeff_02_la0 = 0.;
        this->filtercoeff_02_la1 = 0.;
        this->filtercoeff_02_la2 = 0.;
        this->filtercoeff_02_lb1 = 0.;
        this->filtercoeff_02_lb2 = 0.;
        this->filtercoeff_02_last_frequency = -1.;
        this->filtercoeff_02_last_q = -1.;
        this->filtercoeff_02_last_gain = -1.;
        this->filtercoeff_02_last_type = this->filtercoeff_02_type;
        this->filtercoeff_02_force_update = true;
        this->filtercoeff_02_setupDone = true;
        this->filtercoeff_02_localop_dspsetup();
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        biquad_tilde_03_x = 0;
        biquad_tilde_03_a0 = 0;
        biquad_tilde_03_a1 = 0;
        biquad_tilde_03_a2 = 0;
        biquad_tilde_03_b1 = 0;
        biquad_tilde_03_b2 = 0;
        biquad_tilde_04_x = 0;
        biquad_tilde_04_a0 = 0;
        biquad_tilde_04_a1 = 0;
        biquad_tilde_04_a2 = 0;
        biquad_tilde_04_b1 = 0;
        biquad_tilde_04_b2 = 0;
        numberobj_05_value = 0;
        numberobj_05_value_setter(numberobj_05_value);
        linetilde_03_time = 10;
        linetilde_03_keepramp = 1;
        filtercoeff_02_frequency = 1000;
        filtercoeff_02_gain = 1;
        filtercoeff_02_q = 1;
        filtercoeff_02_type = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        signals[4] = nullptr;
        signals[5] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        biquad_tilde_03_x1 = 0;
        biquad_tilde_03_x2 = 0;
        biquad_tilde_03_y1 = 0;
        biquad_tilde_03_y2 = 0;
        biquad_tilde_03_setupDone = false;
        biquad_tilde_04_x1 = 0;
        biquad_tilde_04_x2 = 0;
        biquad_tilde_04_y1 = 0;
        biquad_tilde_04_y2 = 0;
        biquad_tilde_04_setupDone = false;
        numberobj_05_currentFormat = 6;
        numberobj_05_lastValue = 0;
        linetilde_03_currentValue = 20000;
        filtercoeff_02_K_EPSILON = 1e-9;
        filtercoeff_02_setupDone = false;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number biquad_tilde_03_x;
        number biquad_tilde_03_a0;
        number biquad_tilde_03_a1;
        number biquad_tilde_03_a2;
        number biquad_tilde_03_b1;
        number biquad_tilde_03_b2;
        number biquad_tilde_04_x;
        number biquad_tilde_04_a0;
        number biquad_tilde_04_a1;
        number biquad_tilde_04_a2;
        number biquad_tilde_04_b1;
        number biquad_tilde_04_b2;
        number numberobj_05_value;
        list linetilde_03_segments;
        number linetilde_03_time;
        number linetilde_03_keepramp;
        number filtercoeff_02_frequency;
        number filtercoeff_02_gain;
        number filtercoeff_02_q;
        Int filtercoeff_02_type;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[6];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number biquad_tilde_03_x1;
        number biquad_tilde_03_x2;
        number biquad_tilde_03_y1;
        number biquad_tilde_03_y2;
        bool biquad_tilde_03_setupDone;
        number biquad_tilde_04_x1;
        number biquad_tilde_04_x2;
        number biquad_tilde_04_y1;
        number biquad_tilde_04_y2;
        bool biquad_tilde_04_setupDone;
        Int numberobj_05_currentFormat;
        number numberobj_05_lastValue;
        list linetilde_03_activeRamps;
        number linetilde_03_currentValue;
        number filtercoeff_02_resamp_counter;
        number filtercoeff_02_activeResamp;
        number filtercoeff_02_K_EPSILON;
        number filtercoeff_02_la0;
        number filtercoeff_02_la1;
        number filtercoeff_02_la2;
        number filtercoeff_02_lb1;
        number filtercoeff_02_lb2;
        number filtercoeff_02_last_frequency;
        number filtercoeff_02_last_q;
        number filtercoeff_02_last_gain;
        Int filtercoeff_02_last_type;
        bool filtercoeff_02_force_update;
        number filtercoeff_02_localop_twopi_over_sr;
        number filtercoeff_02_localop_cs;
        number filtercoeff_02_localop_sn;
        number filtercoeff_02_localop_one_over_gain;
        number filtercoeff_02_localop_one_over_q;
        number filtercoeff_02_localop_alpha;
        number filtercoeff_02_localop_beta;
        number filtercoeff_02_localop_b0;
        number filtercoeff_02_localop_b0g;
        number filtercoeff_02_localop_A;
        number filtercoeff_02_localop_one_over_a;
        number filtercoeff_02_localop_la0;
        number filtercoeff_02_localop_la1;
        number filtercoeff_02_localop_la2;
        number filtercoeff_02_localop_lb1;
        number filtercoeff_02_localop_lb2;
        bool filtercoeff_02_setupDone;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_192 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_192()
    {
    }
    
    ~RNBOSubpatcher_192()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -62043057, false);
        getEngine()->flushClockEvents(this, -1621164530, false);
    }
    
    inline number safediv(number num, number denom) {
        return (denom == 0.0 ? 0.0 : num / denom);
    }
    
    number safepow(number base, number exponent) {
        return fixnan(rnbo_pow(base, exponent));
    }
    
    number scale(
        number x,
        number lowin,
        number hiin,
        number lowout,
        number highout,
        number pow
    ) {
        auto inscale = this->safediv(1., hiin - lowin);
        number outdiff = highout - lowout;
        number value = (x - lowin) * inscale;
    
        if (pow != 1) {
            if (value > 0)
                value = this->safepow(value, pow);
            else
                value = -this->safepow(-value, pow);
        }
    
        value = value * outdiff + lowout;
        return value;
    }
    
    SampleIndex currentsampletime() {
        return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
    }
    
    number mstosamps(MillisecondTime ms) {
        return ms * this->sr * 0.001;
    }
    
    inline number safesqrt(number num) {
        return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
    }
    
    Index vectorsize() const {
        return this->vs;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        this->linetilde_04_perform(this->signals[0], n);
        this->linetilde_05_perform(this->signals[1], n);
    
        this->filtercoeff_03_perform(
            this->signals[0],
            this->signals[1],
            this->filtercoeff_03_q,
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->signals[5],
            this->signals[6],
            n
        );
    
        this->biquad_tilde_06_perform(
            in2,
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->signals[5],
            this->signals[6],
            out2,
            n
        );
    
        this->biquad_tilde_05_perform(
            in1,
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->signals[5],
            this->signals[6],
            out1,
            n
        );
    
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 7; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->filtercoeff_03_dspsetup(forceDSPSetup);
        this->biquad_tilde_06_dspsetup(forceDSPSetup);
        this->biquad_tilde_05_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -62043057:
            {
            this->linetilde_04_target_bang();
            break;
            }
        case -1621164530:
            {
            this->linetilde_05_target_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("HighMid~/number_obj-17") == objectId)
                this->numberobj_06_valin_set(payload);
    
            if (TAG("HighMid~/number_obj-7") == objectId)
                this->numberobj_07_valin_set(payload);
    
            if (TAG("HighMid~/number_obj-23") == objectId)
                this->numberobj_08_valin_set(payload);
    
            if (TAG("HighMid~/number_obj-3") == objectId)
                this->numberobj_09_valin_set(payload);
    
            if (TAG("HighMid~/number_obj-4") == objectId)
                this->numberobj_10_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("HighMid~/number_obj-17") == objectId)
                this->numberobj_06_format_set(payload);
    
            if (TAG("HighMid~/number_obj-7") == objectId)
                this->numberobj_07_format_set(payload);
    
            if (TAG("HighMid~/number_obj-23") == objectId)
                this->numberobj_08_format_set(payload);
    
            if (TAG("HighMid~/number_obj-3") == objectId)
                this->numberobj_09_format_set(payload);
    
            if (TAG("HighMid~/number_obj-4") == objectId)
                this->numberobj_10_format_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("HighMid~/number_obj-17"):
            {
            return "HighMid~/number_obj-17";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("HighMid~/number_obj-7"):
            {
            return "HighMid~/number_obj-7";
            }
        case TAG("HighMid~/number_obj-23"):
            {
            return "HighMid~/number_obj-23";
            }
        case TAG("HighMid~/number_obj-3"):
            {
            return "HighMid~/number_obj-3";
            }
        case TAG("HighMid~/number_obj-4"):
            {
            return "HighMid~/number_obj-4";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void numberobj_06_valin_set(number v) {
        this->numberobj_06_value_set(v);
    }
    
    void numberobj_06_format_set(number v) {
        this->numberobj_06_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_04_out1_bang_bang() {
        this->numberobj_06_value_bang();
    }
    
    void eventinlet_04_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_06_value_set(converted);
        }
    }
    
    void numberobj_07_valin_set(number v) {
        this->numberobj_07_value_set(v);
    }
    
    void numberobj_07_format_set(number v) {
        this->numberobj_07_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_08_valin_set(number v) {
        this->numberobj_08_value_set(v);
    }
    
    void numberobj_08_format_set(number v) {
        this->numberobj_08_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_05_out1_bang_bang() {
        this->numberobj_08_value_bang();
    }
    
    void eventinlet_05_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_08_value_set(converted);
        }
    }
    
    void numberobj_09_valin_set(number v) {
        this->numberobj_09_value_set(v);
    }
    
    void numberobj_09_format_set(number v) {
        this->numberobj_09_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_10_valin_set(number v) {
        this->numberobj_10_value_set(v);
    }
    
    void numberobj_10_format_set(number v) {
        this->numberobj_10_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void linetilde_04_target_bang() {}
    
    void linetilde_05_target_bang() {}
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->numberobj_06_init();
        this->numberobj_07_init();
        this->numberobj_08_init();
        this->numberobj_09_init();
        this->numberobj_10_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
    void linetilde_05_time_set(number v) {
        this->linetilde_05_time = v;
    }
    
    void linetilde_05_segments_set(const list& v) {
        this->linetilde_05_segments = jsCreateListCopy(v);
    
        if ((bool)(v->length)) {
            if (v->length == 1 && this->linetilde_05_time == 0) {
                this->linetilde_05_activeRamps->length = 0;
                this->linetilde_05_currentValue = v[0];
            } else {
                auto currentTime = this->currentsampletime();
                number lastRampValue = this->linetilde_05_currentValue;
                number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;
    
                for (Index i = 0; i < this->linetilde_05_activeRamps->length; i += 3) {
                    rampEnd = this->linetilde_05_activeRamps[(Index)(i + 2)];
    
                    if (rampEnd > currentTime) {
                        this->linetilde_05_activeRamps[(Index)(i + 2)] = currentTime;
                        number diff = rampEnd - currentTime;
                        number valueDiff = diff * this->linetilde_05_activeRamps[(Index)(i + 1)];
                        lastRampValue = this->linetilde_05_activeRamps[(Index)i] - valueDiff;
                        this->linetilde_05_activeRamps[(Index)i] = lastRampValue;
                        this->linetilde_05_activeRamps->length = i + 3;
                        rampEnd = currentTime;
                    } else {
                        lastRampValue = this->linetilde_05_activeRamps[(Index)i];
                    }
                }
    
                if (rampEnd < currentTime) {
                    this->linetilde_05_activeRamps->push(lastRampValue);
                    this->linetilde_05_activeRamps->push(0);
                    this->linetilde_05_activeRamps->push(currentTime);
                }
    
                number lastRampEnd = currentTime;
    
                for (Index i = 0; i < v->length; i += 2) {
                    number destinationValue = v[(Index)i];
                    number inc = 0;
                    number rampTimeInSamples;
    
                    if (v->length > i + 1) {
                        rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);
    
                        if ((bool)(this->linetilde_05_keepramp)) {
                            this->linetilde_05_time_set(v[(Index)(i + 1)]);
                        }
                    } else {
                        rampTimeInSamples = this->mstosamps(this->linetilde_05_time);
                    }
    
                    if (rampTimeInSamples <= 0) {
                        rampTimeInSamples = 1;
                    }
    
                    inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                    lastRampEnd += rampTimeInSamples;
                    this->linetilde_05_activeRamps->push(destinationValue);
                    this->linetilde_05_activeRamps->push(inc);
                    this->linetilde_05_activeRamps->push(lastRampEnd);
                    lastRampValue = destinationValue;
                }
            }
        }
    }
    
    void numberobj_09_output_set(number v) {
        {
            list converted = {v};
            this->linetilde_05_segments_set(converted);
        }
    }
    
    void numberobj_09_value_set(number v) {
        this->numberobj_09_value_setter(v);
        v = this->numberobj_09_value;
        number localvalue = v;
    
        if (this->numberobj_09_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("HighMid~/number_obj-3"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_09_output_set(localvalue);
    }
    
    void expr_02_out1_set(number v) {
        this->expr_02_out1 = v;
        this->numberobj_09_value_set(this->expr_02_out1);
    }
    
    void expr_02_in1_set(number in1) {
        this->expr_02_in1 = in1;
        this->expr_02_out1_set(rnbo_pow(10, this->expr_02_in1 * 0.05));//#map:HighMid~/dbtoa_obj-9:1
    }
    
    void numberobj_10_output_set(number v) {
        this->expr_02_in1_set(v);
    }
    
    void numberobj_10_value_set(number v) {
        this->numberobj_10_value_setter(v);
        v = this->numberobj_10_value;
        number localvalue = v;
    
        if (this->numberobj_10_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("HighMid~/number_obj-4"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_10_output_set(localvalue);
    }
    
    void scale_03_out_set(const list& v) {
        this->scale_03_out = jsCreateListCopy(v);
    
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_10_value_set(converted);
        }
    }
    
    void scale_03_input_set(const list& v) {
        this->scale_03_input = jsCreateListCopy(v);
        list tmp = {};
    
        for (Index i = 0; i < v->length; i++) {
            tmp->push(this->scale(
                v[(Index)i],
                this->scale_03_inlow,
                this->scale_03_inhigh,
                this->scale_03_outlow,
                this->scale_03_outhigh,
                this->scale_03_power
            ));
        }
    
        this->scale_03_out_set(tmp);
    }
    
    void numberobj_08_output_set(number v) {
        {
            list converted = {v};
            this->scale_03_input_set(converted);
        }
    }
    
    void numberobj_08_value_set(number v) {
        this->numberobj_08_value_setter(v);
        v = this->numberobj_08_value;
        number localvalue = v;
    
        if (this->numberobj_08_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("HighMid~/number_obj-23"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_08_output_set(localvalue);
    }
    
    void eventinlet_05_out1_number_set(number v) {
        this->numberobj_08_value_set(v);
    }
    
    void linetilde_04_time_set(number v) {
        this->linetilde_04_time = v;
    }
    
    void linetilde_04_segments_set(const list& v) {
        this->linetilde_04_segments = jsCreateListCopy(v);
    
        if ((bool)(v->length)) {
            if (v->length == 1 && this->linetilde_04_time == 0) {
                this->linetilde_04_activeRamps->length = 0;
                this->linetilde_04_currentValue = v[0];
            } else {
                auto currentTime = this->currentsampletime();
                number lastRampValue = this->linetilde_04_currentValue;
                number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;
    
                for (Index i = 0; i < this->linetilde_04_activeRamps->length; i += 3) {
                    rampEnd = this->linetilde_04_activeRamps[(Index)(i + 2)];
    
                    if (rampEnd > currentTime) {
                        this->linetilde_04_activeRamps[(Index)(i + 2)] = currentTime;
                        number diff = rampEnd - currentTime;
                        number valueDiff = diff * this->linetilde_04_activeRamps[(Index)(i + 1)];
                        lastRampValue = this->linetilde_04_activeRamps[(Index)i] - valueDiff;
                        this->linetilde_04_activeRamps[(Index)i] = lastRampValue;
                        this->linetilde_04_activeRamps->length = i + 3;
                        rampEnd = currentTime;
                    } else {
                        lastRampValue = this->linetilde_04_activeRamps[(Index)i];
                    }
                }
    
                if (rampEnd < currentTime) {
                    this->linetilde_04_activeRamps->push(lastRampValue);
                    this->linetilde_04_activeRamps->push(0);
                    this->linetilde_04_activeRamps->push(currentTime);
                }
    
                number lastRampEnd = currentTime;
    
                for (Index i = 0; i < v->length; i += 2) {
                    number destinationValue = v[(Index)i];
                    number inc = 0;
                    number rampTimeInSamples;
    
                    if (v->length > i + 1) {
                        rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);
    
                        if ((bool)(this->linetilde_04_keepramp)) {
                            this->linetilde_04_time_set(v[(Index)(i + 1)]);
                        }
                    } else {
                        rampTimeInSamples = this->mstosamps(this->linetilde_04_time);
                    }
    
                    if (rampTimeInSamples <= 0) {
                        rampTimeInSamples = 1;
                    }
    
                    inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                    lastRampEnd += rampTimeInSamples;
                    this->linetilde_04_activeRamps->push(destinationValue);
                    this->linetilde_04_activeRamps->push(inc);
                    this->linetilde_04_activeRamps->push(lastRampEnd);
                    lastRampValue = destinationValue;
                }
            }
        }
    }
    
    void numberobj_07_output_set(number v) {
        {
            list converted = {v};
            this->linetilde_04_segments_set(converted);
        }
    }
    
    void numberobj_07_value_set(number v) {
        this->numberobj_07_value_setter(v);
        v = this->numberobj_07_value;
        number localvalue = v;
    
        if (this->numberobj_07_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("HighMid~/number_obj-7"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_07_output_set(localvalue);
    }
    
    void scale_02_out_set(const list& v) {
        this->scale_02_out = jsCreateListCopy(v);
    
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_07_value_set(converted);
        }
    }
    
    void scale_02_input_set(const list& v) {
        this->scale_02_input = jsCreateListCopy(v);
        list tmp = {};
    
        for (Index i = 0; i < v->length; i++) {
            tmp->push(this->scale(
                v[(Index)i],
                this->scale_02_inlow,
                this->scale_02_inhigh,
                this->scale_02_outlow,
                this->scale_02_outhigh,
                this->scale_02_power
            ));
        }
    
        this->scale_02_out_set(tmp);
    }
    
    void numberobj_06_output_set(number v) {
        {
            list converted = {v};
            this->scale_02_input_set(converted);
        }
    }
    
    void numberobj_06_value_set(number v) {
        this->numberobj_06_value_setter(v);
        v = this->numberobj_06_value;
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("HighMid~/number_obj-17"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_06_output_set(localvalue);
    }
    
    void eventinlet_04_out1_number_set(number v) {
        this->numberobj_06_value_set(v);
    }
    
    void numberobj_06_value_bang() {
        number v = this->numberobj_06_value;
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("HighMid~/number_obj-17"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_06_output_set(localvalue);
    }
    
    void numberobj_08_value_bang() {
        number v = this->numberobj_08_value;
        number localvalue = v;
    
        if (this->numberobj_08_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("HighMid~/number_obj-23"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_08_output_set(localvalue);
    }
    
    void linetilde_04_perform(SampleValue * out, Index n) {
        auto __linetilde_04_time = this->linetilde_04_time;
        auto __linetilde_04_keepramp = this->linetilde_04_keepramp;
        auto __linetilde_04_currentValue = this->linetilde_04_currentValue;
        Index i = 0;
    
        if ((bool)(this->linetilde_04_activeRamps->length)) {
            while ((bool)(this->linetilde_04_activeRamps->length) && i < n) {
                number destinationValue = this->linetilde_04_activeRamps[0];
                number inc = this->linetilde_04_activeRamps[1];
                number rampTimeInSamples = this->linetilde_04_activeRamps[2] - this->audioProcessSampleCount - i;
                number val = __linetilde_04_currentValue;
    
                while (rampTimeInSamples > 0 && i < n) {
                    out[(Index)i] = val;
                    val += inc;
                    i++;
                    rampTimeInSamples--;
                }
    
                if (rampTimeInSamples <= 0) {
                    val = destinationValue;
                    this->linetilde_04_activeRamps->splice(0, 3);
    
                    if ((bool)(!(bool)(this->linetilde_04_activeRamps->length))) {
                        this->getEngine()->scheduleClockEventWithValue(
                            this,
                            -62043057,
                            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                            0
                        );;
    
                        if ((bool)(!(bool)(__linetilde_04_keepramp))) {
                            __linetilde_04_time = 0;
                        }
                    }
                }
    
                __linetilde_04_currentValue = val;
            }
        }
    
        while (i < n) {
            out[(Index)i] = __linetilde_04_currentValue;
            i++;
        }
    
        this->linetilde_04_currentValue = __linetilde_04_currentValue;
        this->linetilde_04_time = __linetilde_04_time;
    }
    
    void linetilde_05_perform(SampleValue * out, Index n) {
        auto __linetilde_05_time = this->linetilde_05_time;
        auto __linetilde_05_keepramp = this->linetilde_05_keepramp;
        auto __linetilde_05_currentValue = this->linetilde_05_currentValue;
        Index i = 0;
    
        if ((bool)(this->linetilde_05_activeRamps->length)) {
            while ((bool)(this->linetilde_05_activeRamps->length) && i < n) {
                number destinationValue = this->linetilde_05_activeRamps[0];
                number inc = this->linetilde_05_activeRamps[1];
                number rampTimeInSamples = this->linetilde_05_activeRamps[2] - this->audioProcessSampleCount - i;
                number val = __linetilde_05_currentValue;
    
                while (rampTimeInSamples > 0 && i < n) {
                    out[(Index)i] = val;
                    val += inc;
                    i++;
                    rampTimeInSamples--;
                }
    
                if (rampTimeInSamples <= 0) {
                    val = destinationValue;
                    this->linetilde_05_activeRamps->splice(0, 3);
    
                    if ((bool)(!(bool)(this->linetilde_05_activeRamps->length))) {
                        this->getEngine()->scheduleClockEventWithValue(
                            this,
                            -1621164530,
                            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                            0
                        );;
    
                        if ((bool)(!(bool)(__linetilde_05_keepramp))) {
                            __linetilde_05_time = 0;
                        }
                    }
                }
    
                __linetilde_05_currentValue = val;
            }
        }
    
        while (i < n) {
            out[(Index)i] = __linetilde_05_currentValue;
            i++;
        }
    
        this->linetilde_05_currentValue = __linetilde_05_currentValue;
        this->linetilde_05_time = __linetilde_05_time;
    }
    
    void filtercoeff_03_perform(
        const Sample * frequency,
        const Sample * gain,
        number q,
        SampleValue * a0,
        SampleValue * a1,
        SampleValue * a2,
        SampleValue * b1,
        SampleValue * b2,
        Index n
    ) {
        RNBO_UNUSED(q);
        auto __filtercoeff_03_activeResamp = this->filtercoeff_03_activeResamp;
        auto __filtercoeff_03_resamp_counter = this->filtercoeff_03_resamp_counter;
        auto __filtercoeff_03_K_EPSILON = this->filtercoeff_03_K_EPSILON;
    
        for (Index i = 0; i < n; i++) {
            number local_q = 0.5;
            number local_gain = gain[(Index)i];
    
            if (local_gain < 0)
                local_gain = 0;
    
            number local_frequency = frequency[(Index)i];
    
            if (local_q < __filtercoeff_03_K_EPSILON)
                local_q = __filtercoeff_03_K_EPSILON;
    
            local_frequency = (local_frequency > this->sr * 0.5 ? this->sr * 0.5 : (local_frequency < 1 ? 1 : local_frequency));
            __filtercoeff_03_resamp_counter--;
    
            if (__filtercoeff_03_resamp_counter <= 0) {
                __filtercoeff_03_resamp_counter = __filtercoeff_03_activeResamp;
                this->filtercoeff_03_updateTerms(local_frequency, local_gain, local_q);
            }
    
            a0[(Index)i] = this->filtercoeff_03_la0;
            a1[(Index)i] = this->filtercoeff_03_la1;
            a2[(Index)i] = this->filtercoeff_03_la2;
            b1[(Index)i] = this->filtercoeff_03_lb1;
            b2[(Index)i] = this->filtercoeff_03_lb2;
        }
    
        this->filtercoeff_03_resamp_counter = __filtercoeff_03_resamp_counter;
    }
    
    void biquad_tilde_06_perform(
        const Sample * x,
        const Sample * a0,
        const Sample * a1,
        const Sample * a2,
        const Sample * b1,
        const Sample * b2,
        SampleValue * out1,
        Index n
    ) {
        auto __biquad_tilde_06_y2 = this->biquad_tilde_06_y2;
        auto __biquad_tilde_06_y1 = this->biquad_tilde_06_y1;
        auto __biquad_tilde_06_x2 = this->biquad_tilde_06_x2;
        auto __biquad_tilde_06_x1 = this->biquad_tilde_06_x1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_06_x1 * a1[(Index)i] + __biquad_tilde_06_x2 * a2[(Index)i] - (__biquad_tilde_06_y1 * b1[(Index)i] + __biquad_tilde_06_y2 * b2[(Index)i]);
            __biquad_tilde_06_x2 = __biquad_tilde_06_x1;
            __biquad_tilde_06_x1 = x[(Index)i];
            __biquad_tilde_06_y2 = __biquad_tilde_06_y1;
            __biquad_tilde_06_y1 = tmp;
            out1[(Index)i] = tmp;
        }
    
        this->biquad_tilde_06_x1 = __biquad_tilde_06_x1;
        this->biquad_tilde_06_x2 = __biquad_tilde_06_x2;
        this->biquad_tilde_06_y1 = __biquad_tilde_06_y1;
        this->biquad_tilde_06_y2 = __biquad_tilde_06_y2;
    }
    
    void biquad_tilde_05_perform(
        const Sample * x,
        const Sample * a0,
        const Sample * a1,
        const Sample * a2,
        const Sample * b1,
        const Sample * b2,
        SampleValue * out1,
        Index n
    ) {
        auto __biquad_tilde_05_y2 = this->biquad_tilde_05_y2;
        auto __biquad_tilde_05_y1 = this->biquad_tilde_05_y1;
        auto __biquad_tilde_05_x2 = this->biquad_tilde_05_x2;
        auto __biquad_tilde_05_x1 = this->biquad_tilde_05_x1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_05_x1 * a1[(Index)i] + __biquad_tilde_05_x2 * a2[(Index)i] - (__biquad_tilde_05_y1 * b1[(Index)i] + __biquad_tilde_05_y2 * b2[(Index)i]);
            __biquad_tilde_05_x2 = __biquad_tilde_05_x1;
            __biquad_tilde_05_x1 = x[(Index)i];
            __biquad_tilde_05_y2 = __biquad_tilde_05_y1;
            __biquad_tilde_05_y1 = tmp;
            out1[(Index)i] = tmp;
        }
    
        this->biquad_tilde_05_x1 = __biquad_tilde_05_x1;
        this->biquad_tilde_05_x2 = __biquad_tilde_05_x2;
        this->biquad_tilde_05_y1 = __biquad_tilde_05_y1;
        this->biquad_tilde_05_y2 = __biquad_tilde_05_y2;
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void numberobj_06_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_06_value = localvalue;
    }
    
    void numberobj_07_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_07_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_07_value = localvalue;
    }
    
    void numberobj_08_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_08_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_08_value = localvalue;
    }
    
    void numberobj_09_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_09_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_09_value = localvalue;
    }
    
    void numberobj_10_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_10_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_10_value = localvalue;
    }
    
    void biquad_tilde_05_reset() {
        this->biquad_tilde_05_x1 = 0;
        this->biquad_tilde_05_x2 = 0;
        this->biquad_tilde_05_y1 = 0;
        this->biquad_tilde_05_y2 = 0;
    }
    
    void biquad_tilde_05_dspsetup(bool force) {
        if ((bool)(this->biquad_tilde_05_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->biquad_tilde_05_reset();
        this->biquad_tilde_05_setupDone = true;
    }
    
    void biquad_tilde_06_reset() {
        this->biquad_tilde_06_x1 = 0;
        this->biquad_tilde_06_x2 = 0;
        this->biquad_tilde_06_y1 = 0;
        this->biquad_tilde_06_y2 = 0;
    }
    
    void biquad_tilde_06_dspsetup(bool force) {
        if ((bool)(this->biquad_tilde_06_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->biquad_tilde_06_reset();
        this->biquad_tilde_06_setupDone = true;
    }
    
    void numberobj_06_init() {
        this->numberobj_06_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("HighMid~/number_obj-17"), 1, this->_currentTime);
    }
    
    void numberobj_06_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_06_value;
    }
    
    void numberobj_06_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_06_value_set(preset["value"]);
    }
    
    void numberobj_07_init() {
        this->numberobj_07_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("HighMid~/number_obj-7"), 1, this->_currentTime);
    }
    
    void numberobj_07_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_07_value;
    }
    
    void numberobj_07_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_07_value_set(preset["value"]);
    }
    
    array<number, 5> filtercoeff_03_localop_next(number frequency, number q, number gain, number type) {
        number omega = frequency * this->filtercoeff_03_localop_twopi_over_sr;
        this->filtercoeff_03_localop_cs = rnbo_cos(omega);
        this->filtercoeff_03_localop_sn = rnbo_sin(omega);
        this->filtercoeff_03_localop_one_over_gain = (gain >= 0 ? (number)1 / gain : 0.0);
        this->filtercoeff_03_localop_one_over_q = (number)1 / q;
        this->filtercoeff_03_localop_alpha = this->filtercoeff_03_localop_sn * 0.5 * this->filtercoeff_03_localop_one_over_q;
    
        switch ((int)type) {
        case 5:
            {
            this->filtercoeff_03_localop_A = this->safesqrt(gain);
    
            this->filtercoeff_03_localop_beta = this->safesqrt(
                (this->filtercoeff_03_localop_A * this->filtercoeff_03_localop_A + 1.) * this->filtercoeff_03_localop_one_over_q - (this->filtercoeff_03_localop_A - 1.) * (this->filtercoeff_03_localop_A - 1.)
            );
    
            this->filtercoeff_03_localop_b0 = (number)1 / (this->filtercoeff_03_localop_A + 1. + (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs + this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn);
            break;
            }
        case 6:
            {
            this->filtercoeff_03_localop_A = this->safesqrt(gain);
    
            this->filtercoeff_03_localop_beta = this->safesqrt(
                (this->filtercoeff_03_localop_A * this->filtercoeff_03_localop_A + 1.) * this->filtercoeff_03_localop_one_over_q - (this->filtercoeff_03_localop_A - 1.) * (this->filtercoeff_03_localop_A - 1.)
            );
    
            this->filtercoeff_03_localop_b0 = (number)1 / (this->filtercoeff_03_localop_A + 1. - (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs + this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn);
            break;
            }
        case 4:
            {
            this->filtercoeff_03_localop_A = this->safesqrt(gain);
            this->filtercoeff_03_localop_one_over_a = (this->filtercoeff_03_localop_A == 0 ? 0 : (number)1 / this->filtercoeff_03_localop_A);
            this->filtercoeff_03_localop_b0 = (number)1 / (1. + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_a);
            break;
            }
        case 9:
        case 10:
        case 11:
        case 13:
        case 14:
            {
            this->filtercoeff_03_localop_b0 = (number)1 / (1. + this->filtercoeff_03_localop_alpha);
            this->filtercoeff_03_localop_b0g = (number)1 / (this->filtercoeff_03_localop_one_over_gain + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_gain);
            break;
            }
        default:
            {
            this->filtercoeff_03_localop_b0 = (number)1 / (1. + this->filtercoeff_03_localop_alpha);
            break;
            }
        }
    
        switch ((int)type) {
        case 0:
            {
            this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_la2 = (1. - this->filtercoeff_03_localop_cs) * 0.5 * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la1 = (1. - this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
            break;
            }
        case 1:
            {
            this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_la2 = (1. + this->filtercoeff_03_localop_cs) * 0.5 * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la1 = -(1. + this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
            break;
            }
        case 2:
            {
            this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la1 = 0.;
            this->filtercoeff_03_localop_la2 = -this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
            break;
            }
        case 7:
            {
            this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_alpha * q * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la1 = 0.;
            this->filtercoeff_03_localop_la2 = -this->filtercoeff_03_localop_alpha * q * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
            break;
            }
        case 3:
            {
            this->filtercoeff_03_localop_la1 = this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_la2 = this->filtercoeff_03_localop_b0;
            break;
            }
        case 8:
            {
            this->filtercoeff_03_localop_la1 = this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = this->filtercoeff_03_localop_la0 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la2 = 1.0;
            break;
            }
        case 4:
            {
            this->filtercoeff_03_localop_la0 = (1. + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_A) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la1 = this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la2 = (1. - this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_A) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_a) * this->filtercoeff_03_localop_b0;
            break;
            }
        case 5:
            {
            this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_A * (this->filtercoeff_03_localop_A + 1. - (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs + this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la1 = 2. * this->filtercoeff_03_localop_A * (this->filtercoeff_03_localop_A - 1 - (this->filtercoeff_03_localop_A + 1) * this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la2 = this->filtercoeff_03_localop_A * (this->filtercoeff_03_localop_A + 1. - (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs - this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb1 = -2. * (this->filtercoeff_03_localop_A - 1. + (this->filtercoeff_03_localop_A + 1.) * this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = (this->filtercoeff_03_localop_A + 1. + (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs - this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn) * this->filtercoeff_03_localop_b0;
            break;
            }
        case 6:
            {
            this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_A * (this->filtercoeff_03_localop_A + 1. + (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs + this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la1 = -2. * this->filtercoeff_03_localop_A * (this->filtercoeff_03_localop_A - 1. + (this->filtercoeff_03_localop_A + 1.) * this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la2 = this->filtercoeff_03_localop_A * (this->filtercoeff_03_localop_A + 1. + (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs - this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb1 = 2. * (this->filtercoeff_03_localop_A - 1. - (this->filtercoeff_03_localop_A + 1.) * this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = (this->filtercoeff_03_localop_A + 1. - (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs - this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn) * this->filtercoeff_03_localop_b0;
            break;
            }
        case 9:
            {
            this->filtercoeff_03_localop_b0g = (number)1 / (this->filtercoeff_03_localop_one_over_gain + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_gain);
            this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_la2 = (1. - this->filtercoeff_03_localop_cs) * 0.5 * this->filtercoeff_03_localop_b0g;
            this->filtercoeff_03_localop_la1 = (1. - this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0g;
            this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
            break;
            }
        case 10:
            {
            this->filtercoeff_03_localop_b0g = (number)1 / (this->filtercoeff_03_localop_one_over_gain + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_gain);
            this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_la2 = (1. + this->filtercoeff_03_localop_cs) * 0.5 * this->filtercoeff_03_localop_b0g;
            this->filtercoeff_03_localop_la1 = -(1. + this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0g;
            this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
            break;
            }
        case 11:
            {
            this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_alpha * gain * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la1 = 0.;
            this->filtercoeff_03_localop_la2 = -this->filtercoeff_03_localop_alpha * gain * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
            break;
            }
        case 13:
            {
            this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_alpha * gain * q * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la1 = 0.;
            this->filtercoeff_03_localop_la2 = -this->filtercoeff_03_localop_alpha * gain * q * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
            break;
            }
        case 12:
            {
            this->filtercoeff_03_localop_b0g = (number)1 / (this->filtercoeff_03_localop_one_over_gain + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_gain);
            this->filtercoeff_03_localop_la1 = this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs;
            this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la1 *= this->filtercoeff_03_localop_b0g;
            this->filtercoeff_03_localop_lb1 *= this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_b0g;
            this->filtercoeff_03_localop_la2 = this->filtercoeff_03_localop_b0g;
            break;
            }
        case 14:
            {
            this->filtercoeff_03_localop_b0g = (number)1 / (this->filtercoeff_03_localop_one_over_gain + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_gain);
            this->filtercoeff_03_localop_la0 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0g;
            this->filtercoeff_03_localop_la1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0g;
            this->filtercoeff_03_localop_la2 = gain;
            this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
            this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
            break;
            }
        case 15:
            {
            this->filtercoeff_03_localop_la0 = 1;
            this->filtercoeff_03_localop_la1 = 0;
            this->filtercoeff_03_localop_la2 = 0;
            this->filtercoeff_03_localop_lb1 = 0;
            this->filtercoeff_03_localop_lb2 = 0;
            }
        default:
            {
            break;
            }
        }
    
        return {
            this->filtercoeff_03_localop_la0,
            this->filtercoeff_03_localop_la1,
            this->filtercoeff_03_localop_la2,
            this->filtercoeff_03_localop_lb1,
            this->filtercoeff_03_localop_lb2
        };
    }
    
    void filtercoeff_03_localop_dspsetup() {
        this->filtercoeff_03_localop_twopi_over_sr = (number)6.283185307179586 / this->sr;
    }
    
    void filtercoeff_03_localop_reset() {
        this->filtercoeff_03_localop_twopi_over_sr = 0;
        this->filtercoeff_03_localop_cs = 0;
        this->filtercoeff_03_localop_sn = 0;
        this->filtercoeff_03_localop_one_over_gain = 0;
        this->filtercoeff_03_localop_one_over_q = 0;
        this->filtercoeff_03_localop_alpha = 0;
        this->filtercoeff_03_localop_beta = 0;
        this->filtercoeff_03_localop_b0 = 0;
        this->filtercoeff_03_localop_b0g = 0;
        this->filtercoeff_03_localop_A = 0;
        this->filtercoeff_03_localop_one_over_a = 0;
        this->filtercoeff_03_localop_la0 = 0;
        this->filtercoeff_03_localop_la1 = 0;
        this->filtercoeff_03_localop_la2 = 0;
        this->filtercoeff_03_localop_lb1 = 0;
        this->filtercoeff_03_localop_lb2 = 0;
    }
    
    void filtercoeff_03_updateTerms(number local_frequency, number local_gain, number local_q) {
        if ((bool)(this->filtercoeff_03_force_update) || local_frequency != this->filtercoeff_03_last_frequency || local_q != this->filtercoeff_03_last_q || local_gain != this->filtercoeff_03_last_gain || this->filtercoeff_03_type != this->filtercoeff_03_last_type) {
            array<number, 5> tmp = this->filtercoeff_03_localop_next(local_frequency, local_q, local_gain, this->filtercoeff_03_type);
            this->filtercoeff_03_la0 = tmp[0];
            this->filtercoeff_03_la1 = tmp[1];
            this->filtercoeff_03_la2 = tmp[2];
            this->filtercoeff_03_lb1 = tmp[3];
            this->filtercoeff_03_lb2 = tmp[4];
            this->filtercoeff_03_last_frequency = local_frequency;
            this->filtercoeff_03_last_q = local_q;
            this->filtercoeff_03_last_gain = local_gain;
            this->filtercoeff_03_last_type = this->filtercoeff_03_type;
            this->filtercoeff_03_force_update = false;
        }
    }
    
    void filtercoeff_03_dspsetup(bool force) {
        if ((bool)(this->filtercoeff_03_setupDone) && (bool)(!(bool)(force)))
            return;
    
        {
            this->filtercoeff_03_activeResamp = this->vectorsize();
        }
    
        this->filtercoeff_03_resamp_counter = 0;
        this->filtercoeff_03_la0 = 0.;
        this->filtercoeff_03_la1 = 0.;
        this->filtercoeff_03_la2 = 0.;
        this->filtercoeff_03_lb1 = 0.;
        this->filtercoeff_03_lb2 = 0.;
        this->filtercoeff_03_last_frequency = -1.;
        this->filtercoeff_03_last_q = -1.;
        this->filtercoeff_03_last_gain = -1.;
        this->filtercoeff_03_last_type = this->filtercoeff_03_type;
        this->filtercoeff_03_force_update = true;
        this->filtercoeff_03_setupDone = true;
        this->filtercoeff_03_localop_dspsetup();
    }
    
    void numberobj_08_init() {
        this->numberobj_08_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("HighMid~/number_obj-23"), 1, this->_currentTime);
    }
    
    void numberobj_08_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_08_value;
    }
    
    void numberobj_08_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_08_value_set(preset["value"]);
    }
    
    void numberobj_09_init() {
        this->numberobj_09_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("HighMid~/number_obj-3"), 1, this->_currentTime);
    }
    
    void numberobj_09_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_09_value;
    }
    
    void numberobj_09_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_09_value_set(preset["value"]);
    }
    
    void numberobj_10_init() {
        this->numberobj_10_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("HighMid~/number_obj-4"), 1, this->_currentTime);
    }
    
    void numberobj_10_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_10_value;
    }
    
    void numberobj_10_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_10_value_set(preset["value"]);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        biquad_tilde_05_x = 0;
        biquad_tilde_05_a0 = 0;
        biquad_tilde_05_a1 = 0;
        biquad_tilde_05_a2 = 0;
        biquad_tilde_05_b1 = 0;
        biquad_tilde_05_b2 = 0;
        biquad_tilde_06_x = 0;
        biquad_tilde_06_a0 = 0;
        biquad_tilde_06_a1 = 0;
        biquad_tilde_06_a2 = 0;
        biquad_tilde_06_b1 = 0;
        biquad_tilde_06_b2 = 0;
        scale_02_inlow = -100;
        scale_02_inhigh = 100;
        scale_02_outlow = 300;
        scale_02_outhigh = 6000;
        scale_02_power = 2.025;
        numberobj_06_value = 0;
        numberobj_06_value_setter(numberobj_06_value);
        numberobj_07_value = 0;
        numberobj_07_value_setter(numberobj_07_value);
        linetilde_04_time = 10;
        linetilde_04_keepramp = 1;
        filtercoeff_03_frequency = 1000;
        filtercoeff_03_gain = 1;
        filtercoeff_03_q = 0.5;
        filtercoeff_03_type = 4;
        scale_03_inlow = -100;
        scale_03_inhigh = 100;
        scale_03_outlow = -18;
        scale_03_outhigh = 18;
        scale_03_power = 1;
        numberobj_08_value = 0;
        numberobj_08_value_setter(numberobj_08_value);
        numberobj_09_value = 0;
        numberobj_09_value_setter(numberobj_09_value);
        numberobj_10_value = 0;
        numberobj_10_value_setter(numberobj_10_value);
        expr_02_in1 = 0;
        expr_02_out1 = 0;
        linetilde_05_time = 10;
        linetilde_05_keepramp = 1;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        signals[4] = nullptr;
        signals[5] = nullptr;
        signals[6] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        biquad_tilde_05_x1 = 0;
        biquad_tilde_05_x2 = 0;
        biquad_tilde_05_y1 = 0;
        biquad_tilde_05_y2 = 0;
        biquad_tilde_05_setupDone = false;
        biquad_tilde_06_x1 = 0;
        biquad_tilde_06_x2 = 0;
        biquad_tilde_06_y1 = 0;
        biquad_tilde_06_y2 = 0;
        biquad_tilde_06_setupDone = false;
        numberobj_06_currentFormat = 6;
        numberobj_06_lastValue = 0;
        numberobj_07_currentFormat = 6;
        numberobj_07_lastValue = 0;
        linetilde_04_currentValue = 1700;
        filtercoeff_03_K_EPSILON = 1e-9;
        filtercoeff_03_setupDone = false;
        numberobj_08_currentFormat = 6;
        numberobj_08_lastValue = 0;
        numberobj_09_currentFormat = 6;
        numberobj_09_lastValue = 0;
        numberobj_10_currentFormat = 6;
        numberobj_10_lastValue = 0;
        linetilde_05_currentValue = 1;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number biquad_tilde_05_x;
        number biquad_tilde_05_a0;
        number biquad_tilde_05_a1;
        number biquad_tilde_05_a2;
        number biquad_tilde_05_b1;
        number biquad_tilde_05_b2;
        number biquad_tilde_06_x;
        number biquad_tilde_06_a0;
        number biquad_tilde_06_a1;
        number biquad_tilde_06_a2;
        number biquad_tilde_06_b1;
        number biquad_tilde_06_b2;
        list scale_02_input;
        number scale_02_inlow;
        number scale_02_inhigh;
        number scale_02_outlow;
        number scale_02_outhigh;
        number scale_02_power;
        list scale_02_out;
        number numberobj_06_value;
        number numberobj_07_value;
        list linetilde_04_segments;
        number linetilde_04_time;
        number linetilde_04_keepramp;
        number filtercoeff_03_frequency;
        number filtercoeff_03_gain;
        number filtercoeff_03_q;
        Int filtercoeff_03_type;
        list scale_03_input;
        number scale_03_inlow;
        number scale_03_inhigh;
        number scale_03_outlow;
        number scale_03_outhigh;
        number scale_03_power;
        list scale_03_out;
        number numberobj_08_value;
        number numberobj_09_value;
        number numberobj_10_value;
        number expr_02_in1;
        number expr_02_out1;
        list linetilde_05_segments;
        number linetilde_05_time;
        number linetilde_05_keepramp;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[7];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number biquad_tilde_05_x1;
        number biquad_tilde_05_x2;
        number biquad_tilde_05_y1;
        number biquad_tilde_05_y2;
        bool biquad_tilde_05_setupDone;
        number biquad_tilde_06_x1;
        number biquad_tilde_06_x2;
        number biquad_tilde_06_y1;
        number biquad_tilde_06_y2;
        bool biquad_tilde_06_setupDone;
        Int numberobj_06_currentFormat;
        number numberobj_06_lastValue;
        Int numberobj_07_currentFormat;
        number numberobj_07_lastValue;
        list linetilde_04_activeRamps;
        number linetilde_04_currentValue;
        number filtercoeff_03_resamp_counter;
        number filtercoeff_03_activeResamp;
        number filtercoeff_03_K_EPSILON;
        number filtercoeff_03_la0;
        number filtercoeff_03_la1;
        number filtercoeff_03_la2;
        number filtercoeff_03_lb1;
        number filtercoeff_03_lb2;
        number filtercoeff_03_last_frequency;
        number filtercoeff_03_last_q;
        number filtercoeff_03_last_gain;
        Int filtercoeff_03_last_type;
        bool filtercoeff_03_force_update;
        number filtercoeff_03_localop_twopi_over_sr;
        number filtercoeff_03_localop_cs;
        number filtercoeff_03_localop_sn;
        number filtercoeff_03_localop_one_over_gain;
        number filtercoeff_03_localop_one_over_q;
        number filtercoeff_03_localop_alpha;
        number filtercoeff_03_localop_beta;
        number filtercoeff_03_localop_b0;
        number filtercoeff_03_localop_b0g;
        number filtercoeff_03_localop_A;
        number filtercoeff_03_localop_one_over_a;
        number filtercoeff_03_localop_la0;
        number filtercoeff_03_localop_la1;
        number filtercoeff_03_localop_la2;
        number filtercoeff_03_localop_lb1;
        number filtercoeff_03_localop_lb2;
        bool filtercoeff_03_setupDone;
        Int numberobj_08_currentFormat;
        number numberobj_08_lastValue;
        Int numberobj_09_currentFormat;
        number numberobj_09_lastValue;
        Int numberobj_10_currentFormat;
        number numberobj_10_lastValue;
        list linetilde_05_activeRamps;
        number linetilde_05_currentValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_193 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_193()
    {
    }
    
    ~RNBOSubpatcher_193()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -62043057, false);
    }
    
    inline number safediv(number num, number denom) {
        return (denom == 0.0 ? 0.0 : num / denom);
    }
    
    number safepow(number base, number exponent) {
        return fixnan(rnbo_pow(base, exponent));
    }
    
    number scale(
        number x,
        number lowin,
        number hiin,
        number lowout,
        number highout,
        number pow
    ) {
        auto inscale = this->safediv(1., hiin - lowin);
        number outdiff = highout - lowout;
        number value = (x - lowin) * inscale;
    
        if (pow != 1) {
            if (value > 0)
                value = this->safepow(value, pow);
            else
                value = -this->safepow(-value, pow);
        }
    
        value = value * outdiff + lowout;
        return value;
    }
    
    SampleIndex currentsampletime() {
        return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
    }
    
    number mstosamps(MillisecondTime ms) {
        return ms * this->sr * 0.001;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        this->linetilde_06_perform(this->signals[0], n);
        this->dspexpr_04_perform(in2, this->signals[0], out2, n);
        this->dspexpr_03_perform(in1, this->signals[0], out1, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 1; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        RNBO_UNUSED(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -62043057:
            {
            this->linetilde_06_target_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("preq_Level~[1]/number_obj-7") == objectId)
                this->numberobj_11_valin_set(payload);
    
            if (TAG("preq_Level~[1]/number_obj-14") == objectId)
                this->numberobj_12_valin_set(payload);
    
            if (TAG("preq_Level~[1]/number_obj-5") == objectId)
                this->numberobj_13_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("preq_Level~[1]/number_obj-7") == objectId)
                this->numberobj_11_format_set(payload);
    
            if (TAG("preq_Level~[1]/number_obj-14") == objectId)
                this->numberobj_12_format_set(payload);
    
            if (TAG("preq_Level~[1]/number_obj-5") == objectId)
                this->numberobj_13_format_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("preq_Level~[1]/number_obj-7"):
            {
            return "preq_Level~[1]/number_obj-7";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("preq_Level~[1]/number_obj-14"):
            {
            return "preq_Level~[1]/number_obj-14";
            }
        case TAG("preq_Level~[1]/number_obj-5"):
            {
            return "preq_Level~[1]/number_obj-5";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void numberobj_11_valin_set(number v) {
        this->numberobj_11_value_set(v);
    }
    
    void numberobj_11_format_set(number v) {
        this->numberobj_11_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_12_valin_set(number v) {
        this->numberobj_12_value_set(v);
    }
    
    void numberobj_12_format_set(number v) {
        this->numberobj_12_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_13_valin_set(number v) {
        this->numberobj_13_value_set(v);
    }
    
    void numberobj_13_format_set(number v) {
        this->numberobj_13_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_06_out1_bang_bang() {
        this->numberobj_12_value_bang();
    }
    
    void eventinlet_06_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_12_value_set(converted);
        }
    }
    
    void linetilde_06_target_bang() {}
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->numberobj_11_init();
        this->numberobj_12_init();
        this->numberobj_13_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
    void linetilde_06_time_set(number v) {
        this->linetilde_06_time = v;
    }
    
    void linetilde_06_segments_set(const list& v) {
        this->linetilde_06_segments = jsCreateListCopy(v);
    
        if ((bool)(v->length)) {
            if (v->length == 1 && this->linetilde_06_time == 0) {
                this->linetilde_06_activeRamps->length = 0;
                this->linetilde_06_currentValue = v[0];
            } else {
                auto currentTime = this->currentsampletime();
                number lastRampValue = this->linetilde_06_currentValue;
                number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;
    
                for (Index i = 0; i < this->linetilde_06_activeRamps->length; i += 3) {
                    rampEnd = this->linetilde_06_activeRamps[(Index)(i + 2)];
    
                    if (rampEnd > currentTime) {
                        this->linetilde_06_activeRamps[(Index)(i + 2)] = currentTime;
                        number diff = rampEnd - currentTime;
                        number valueDiff = diff * this->linetilde_06_activeRamps[(Index)(i + 1)];
                        lastRampValue = this->linetilde_06_activeRamps[(Index)i] - valueDiff;
                        this->linetilde_06_activeRamps[(Index)i] = lastRampValue;
                        this->linetilde_06_activeRamps->length = i + 3;
                        rampEnd = currentTime;
                    } else {
                        lastRampValue = this->linetilde_06_activeRamps[(Index)i];
                    }
                }
    
                if (rampEnd < currentTime) {
                    this->linetilde_06_activeRamps->push(lastRampValue);
                    this->linetilde_06_activeRamps->push(0);
                    this->linetilde_06_activeRamps->push(currentTime);
                }
    
                number lastRampEnd = currentTime;
    
                for (Index i = 0; i < v->length; i += 2) {
                    number destinationValue = v[(Index)i];
                    number inc = 0;
                    number rampTimeInSamples;
    
                    if (v->length > i + 1) {
                        rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);
    
                        if ((bool)(this->linetilde_06_keepramp)) {
                            this->linetilde_06_time_set(v[(Index)(i + 1)]);
                        }
                    } else {
                        rampTimeInSamples = this->mstosamps(this->linetilde_06_time);
                    }
    
                    if (rampTimeInSamples <= 0) {
                        rampTimeInSamples = 1;
                    }
    
                    inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                    lastRampEnd += rampTimeInSamples;
                    this->linetilde_06_activeRamps->push(destinationValue);
                    this->linetilde_06_activeRamps->push(inc);
                    this->linetilde_06_activeRamps->push(lastRampEnd);
                    lastRampValue = destinationValue;
                }
            }
        }
    }
    
    void numberobj_11_output_set(number v) {
        {
            list converted = {v};
            this->linetilde_06_segments_set(converted);
        }
    }
    
    void numberobj_11_value_set(number v) {
        this->numberobj_11_value_setter(v);
        v = this->numberobj_11_value;
        number localvalue = v;
    
        if (this->numberobj_11_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("preq_Level~[1]/number_obj-7"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_11_output_set(localvalue);
    }
    
    void expr_03_out1_set(number v) {
        this->expr_03_out1 = v;
        this->numberobj_11_value_set(this->expr_03_out1);
    }
    
    void expr_03_in1_set(number in1) {
        this->expr_03_in1 = in1;
        this->expr_03_out1_set(rnbo_pow(10, this->expr_03_in1 * 0.05));//#map:preq_Level~[1]/dbtoa_obj-3:1
    }
    
    void numberobj_13_output_set(number v) {
        this->expr_03_in1_set(v);
    }
    
    void numberobj_13_value_set(number v) {
        this->numberobj_13_value_setter(v);
        v = this->numberobj_13_value;
        number localvalue = v;
    
        if (this->numberobj_13_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("preq_Level~[1]/number_obj-5"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_13_output_set(localvalue);
    }
    
    void scale_04_out_set(const list& v) {
        this->scale_04_out = jsCreateListCopy(v);
    
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_13_value_set(converted);
        }
    }
    
    void scale_04_input_set(const list& v) {
        this->scale_04_input = jsCreateListCopy(v);
        list tmp = {};
    
        for (Index i = 0; i < v->length; i++) {
            tmp->push(this->scale(
                v[(Index)i],
                this->scale_04_inlow,
                this->scale_04_inhigh,
                this->scale_04_outlow,
                this->scale_04_outhigh,
                this->scale_04_power
            ));
        }
    
        this->scale_04_out_set(tmp);
    }
    
    void numberobj_12_output_set(number v) {
        {
            list converted = {v};
            this->scale_04_input_set(converted);
        }
    }
    
    void numberobj_12_value_set(number v) {
        this->numberobj_12_value_setter(v);
        v = this->numberobj_12_value;
        number localvalue = v;
    
        if (this->numberobj_12_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("preq_Level~[1]/number_obj-14"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_12_output_set(localvalue);
    }
    
    void eventinlet_06_out1_number_set(number v) {
        this->numberobj_12_value_set(v);
    }
    
    void numberobj_12_value_bang() {
        number v = this->numberobj_12_value;
        number localvalue = v;
    
        if (this->numberobj_12_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("preq_Level~[1]/number_obj-14"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_12_output_set(localvalue);
    }
    
    void linetilde_06_perform(SampleValue * out, Index n) {
        auto __linetilde_06_time = this->linetilde_06_time;
        auto __linetilde_06_keepramp = this->linetilde_06_keepramp;
        auto __linetilde_06_currentValue = this->linetilde_06_currentValue;
        Index i = 0;
    
        if ((bool)(this->linetilde_06_activeRamps->length)) {
            while ((bool)(this->linetilde_06_activeRamps->length) && i < n) {
                number destinationValue = this->linetilde_06_activeRamps[0];
                number inc = this->linetilde_06_activeRamps[1];
                number rampTimeInSamples = this->linetilde_06_activeRamps[2] - this->audioProcessSampleCount - i;
                number val = __linetilde_06_currentValue;
    
                while (rampTimeInSamples > 0 && i < n) {
                    out[(Index)i] = val;
                    val += inc;
                    i++;
                    rampTimeInSamples--;
                }
    
                if (rampTimeInSamples <= 0) {
                    val = destinationValue;
                    this->linetilde_06_activeRamps->splice(0, 3);
    
                    if ((bool)(!(bool)(this->linetilde_06_activeRamps->length))) {
                        this->getEngine()->scheduleClockEventWithValue(
                            this,
                            -62043057,
                            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                            0
                        );;
    
                        if ((bool)(!(bool)(__linetilde_06_keepramp))) {
                            __linetilde_06_time = 0;
                        }
                    }
                }
    
                __linetilde_06_currentValue = val;
            }
        }
    
        while (i < n) {
            out[(Index)i] = __linetilde_06_currentValue;
            i++;
        }
    
        this->linetilde_06_currentValue = __linetilde_06_currentValue;
        this->linetilde_06_time = __linetilde_06_time;
    }
    
    void dspexpr_04_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_03_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void numberobj_11_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_11_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_11_value = localvalue;
    }
    
    void numberobj_12_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_12_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_12_value = localvalue;
    }
    
    void numberobj_13_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_13_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_13_value = localvalue;
    }
    
    void numberobj_11_init() {
        this->numberobj_11_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("preq_Level~[1]/number_obj-7"), 1, this->_currentTime);
    }
    
    void numberobj_11_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_11_value;
    }
    
    void numberobj_11_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_11_value_set(preset["value"]);
    }
    
    void numberobj_12_init() {
        this->numberobj_12_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("preq_Level~[1]/number_obj-14"), 1, this->_currentTime);
    }
    
    void numberobj_12_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_12_value;
    }
    
    void numberobj_12_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_12_value_set(preset["value"]);
    }
    
    void numberobj_13_init() {
        this->numberobj_13_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("preq_Level~[1]/number_obj-5"), 1, this->_currentTime);
    }
    
    void numberobj_13_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_13_value;
    }
    
    void numberobj_13_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_13_value_set(preset["value"]);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        dspexpr_03_in1 = 0;
        dspexpr_03_in2 = 0;
        dspexpr_04_in1 = 0;
        dspexpr_04_in2 = 0;
        numberobj_11_value = 0;
        numberobj_11_value_setter(numberobj_11_value);
        numberobj_12_value = 0;
        numberobj_12_value_setter(numberobj_12_value);
        scale_04_inlow = -100;
        scale_04_inhigh = 100;
        scale_04_outlow = -18;
        scale_04_outhigh = 18;
        scale_04_power = 1;
        numberobj_13_value = 0;
        numberobj_13_value_setter(numberobj_13_value);
        expr_03_in1 = 0;
        expr_03_out1 = 0;
        linetilde_06_time = 10;
        linetilde_06_keepramp = 1;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        numberobj_11_currentFormat = 6;
        numberobj_11_lastValue = 0;
        numberobj_12_currentFormat = 6;
        numberobj_12_lastValue = 0;
        numberobj_13_currentFormat = 6;
        numberobj_13_lastValue = 0;
        linetilde_06_currentValue = 1;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number dspexpr_03_in1;
        number dspexpr_03_in2;
        number dspexpr_04_in1;
        number dspexpr_04_in2;
        number numberobj_11_value;
        number numberobj_12_value;
        list scale_04_input;
        number scale_04_inlow;
        number scale_04_inhigh;
        number scale_04_outlow;
        number scale_04_outhigh;
        number scale_04_power;
        list scale_04_out;
        number numberobj_13_value;
        number expr_03_in1;
        number expr_03_out1;
        list linetilde_06_segments;
        number linetilde_06_time;
        number linetilde_06_keepramp;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[1];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Int numberobj_11_currentFormat;
        number numberobj_11_lastValue;
        Int numberobj_12_currentFormat;
        number numberobj_12_lastValue;
        Int numberobj_13_currentFormat;
        number numberobj_13_lastValue;
        list linetilde_06_activeRamps;
        number linetilde_06_currentValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_194 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_194()
    {
    }
    
    ~RNBOSubpatcher_194()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -62043057, false);
    }
    
    SampleIndex currentsampletime() {
        return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
    }
    
    number mstosamps(MillisecondTime ms) {
        return ms * this->sr * 0.001;
    }
    
    inline number safesqrt(number num) {
        return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
    }
    
    Index vectorsize() const {
        return this->vs;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        this->linetilde_07_perform(this->signals[0], n);
    
        this->filtercoeff_04_perform(
            this->signals[0],
            this->filtercoeff_04_gain,
            this->filtercoeff_04_q,
            this->signals[1],
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->signals[5],
            n
        );
    
        this->biquad_tilde_08_perform(
            in2,
            this->signals[1],
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->signals[5],
            out2,
            n
        );
    
        this->biquad_tilde_07_perform(
            in1,
            this->signals[1],
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->signals[5],
            out1,
            n
        );
    
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 6; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->filtercoeff_04_dspsetup(forceDSPSetup);
        this->biquad_tilde_08_dspsetup(forceDSPSetup);
        this->biquad_tilde_07_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -62043057:
            {
            this->linetilde_07_target_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("preq_LowCut~/toggle_obj-42") == objectId)
                this->toggle_01_valin_set(payload);
    
            if (TAG("preq_LowCut~/number_obj-37") == objectId)
                this->numberobj_14_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("preq_LowCut~/number_obj-37") == objectId)
                this->numberobj_14_format_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("preq_LowCut~/toggle_obj-42"):
            {
            return "preq_LowCut~/toggle_obj-42";
            }
        case TAG("preq_LowCut~/number_obj-37"):
            {
            return "preq_LowCut~/number_obj-37";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void toggle_01_valin_set(number v) {
        this->toggle_01_value_number_set(v);
    }
    
    void numberobj_14_valin_set(number v) {
        this->numberobj_14_value_set(v);
    }
    
    void numberobj_14_format_set(number v) {
        this->numberobj_14_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_07_out1_bang_bang() {
        this->toggle_01_value_bang_bang();
    }
    
    void eventinlet_07_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->toggle_01_value_number_set(converted);
        }
    }
    
    void linetilde_07_target_bang() {}
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->numberobj_14_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
    void linetilde_07_time_set(number v) {
        this->linetilde_07_time = v;
    }
    
    void linetilde_07_segments_set(const list& v) {
        this->linetilde_07_segments = jsCreateListCopy(v);
    
        if ((bool)(v->length)) {
            if (v->length == 1 && this->linetilde_07_time == 0) {
                this->linetilde_07_activeRamps->length = 0;
                this->linetilde_07_currentValue = v[0];
            } else {
                auto currentTime = this->currentsampletime();
                number lastRampValue = this->linetilde_07_currentValue;
                number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;
    
                for (Index i = 0; i < this->linetilde_07_activeRamps->length; i += 3) {
                    rampEnd = this->linetilde_07_activeRamps[(Index)(i + 2)];
    
                    if (rampEnd > currentTime) {
                        this->linetilde_07_activeRamps[(Index)(i + 2)] = currentTime;
                        number diff = rampEnd - currentTime;
                        number valueDiff = diff * this->linetilde_07_activeRamps[(Index)(i + 1)];
                        lastRampValue = this->linetilde_07_activeRamps[(Index)i] - valueDiff;
                        this->linetilde_07_activeRamps[(Index)i] = lastRampValue;
                        this->linetilde_07_activeRamps->length = i + 3;
                        rampEnd = currentTime;
                    } else {
                        lastRampValue = this->linetilde_07_activeRamps[(Index)i];
                    }
                }
    
                if (rampEnd < currentTime) {
                    this->linetilde_07_activeRamps->push(lastRampValue);
                    this->linetilde_07_activeRamps->push(0);
                    this->linetilde_07_activeRamps->push(currentTime);
                }
    
                number lastRampEnd = currentTime;
    
                for (Index i = 0; i < v->length; i += 2) {
                    number destinationValue = v[(Index)i];
                    number inc = 0;
                    number rampTimeInSamples;
    
                    if (v->length > i + 1) {
                        rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);
    
                        if ((bool)(this->linetilde_07_keepramp)) {
                            this->linetilde_07_time_set(v[(Index)(i + 1)]);
                        }
                    } else {
                        rampTimeInSamples = this->mstosamps(this->linetilde_07_time);
                    }
    
                    if (rampTimeInSamples <= 0) {
                        rampTimeInSamples = 1;
                    }
    
                    inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                    lastRampEnd += rampTimeInSamples;
                    this->linetilde_07_activeRamps->push(destinationValue);
                    this->linetilde_07_activeRamps->push(inc);
                    this->linetilde_07_activeRamps->push(lastRampEnd);
                    lastRampValue = destinationValue;
                }
            }
        }
    }
    
    void numberobj_14_output_set(number v) {
        {
            list converted = {v};
            this->linetilde_07_segments_set(converted);
        }
    }
    
    void numberobj_14_value_set(number v) {
        this->numberobj_14_value_setter(v);
        v = this->numberobj_14_value;
        number localvalue = v;
    
        if (this->numberobj_14_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("preq_LowCut~/number_obj-37"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_14_output_set(localvalue);
    }
    
    void listlookup_01_out_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_14_value_set(converted);
        }
    }
    
    void listlookup_01_input_set(const list& v) {
        this->listlookup_01_input = jsCreateListCopy(v);
        list tmp = list();
    
        for (Index i = 0; i < v->length; i++) {
            long j = (long)(rnbo_fround(v[(Index)i] * 1 / (number)1) * 1);
    
            if (j >= 0 && (Index)(j) < this->listlookup_01_lookup->length)
                tmp->push(this->listlookup_01_lookup[(Index)j]);
        }
    
        if ((bool)(tmp->length))
            this->listlookup_01_out_set(tmp);
    }
    
    void toggle_01_output_set(number v) {
        {
            list converted = {v};
            this->listlookup_01_input_set(converted);
        }
    }
    
    void toggle_01_value_number_set(number v) {
        this->toggle_01_value_number_setter(v);
        v = this->toggle_01_value_number;
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("preq_LowCut~/toggle_obj-42"), v, this->_currentTime);
        this->toggle_01_output_set(v);
    }
    
    void eventinlet_07_out1_number_set(number v) {
        this->toggle_01_value_number_set(v);
    }
    
    void toggle_01_value_bang_bang() {
        number val = (this->toggle_01_value_number == 1 ? 0 : 1);
        this->toggle_01_value_number_set(val);
    }
    
    void linetilde_07_perform(SampleValue * out, Index n) {
        auto __linetilde_07_time = this->linetilde_07_time;
        auto __linetilde_07_keepramp = this->linetilde_07_keepramp;
        auto __linetilde_07_currentValue = this->linetilde_07_currentValue;
        Index i = 0;
    
        if ((bool)(this->linetilde_07_activeRamps->length)) {
            while ((bool)(this->linetilde_07_activeRamps->length) && i < n) {
                number destinationValue = this->linetilde_07_activeRamps[0];
                number inc = this->linetilde_07_activeRamps[1];
                number rampTimeInSamples = this->linetilde_07_activeRamps[2] - this->audioProcessSampleCount - i;
                number val = __linetilde_07_currentValue;
    
                while (rampTimeInSamples > 0 && i < n) {
                    out[(Index)i] = val;
                    val += inc;
                    i++;
                    rampTimeInSamples--;
                }
    
                if (rampTimeInSamples <= 0) {
                    val = destinationValue;
                    this->linetilde_07_activeRamps->splice(0, 3);
    
                    if ((bool)(!(bool)(this->linetilde_07_activeRamps->length))) {
                        this->getEngine()->scheduleClockEventWithValue(
                            this,
                            -62043057,
                            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                            0
                        );;
    
                        if ((bool)(!(bool)(__linetilde_07_keepramp))) {
                            __linetilde_07_time = 0;
                        }
                    }
                }
    
                __linetilde_07_currentValue = val;
            }
        }
    
        while (i < n) {
            out[(Index)i] = __linetilde_07_currentValue;
            i++;
        }
    
        this->linetilde_07_currentValue = __linetilde_07_currentValue;
        this->linetilde_07_time = __linetilde_07_time;
    }
    
    void filtercoeff_04_perform(
        const Sample * frequency,
        number gain,
        number q,
        SampleValue * a0,
        SampleValue * a1,
        SampleValue * a2,
        SampleValue * b1,
        SampleValue * b2,
        Index n
    ) {
        RNBO_UNUSED(q);
        RNBO_UNUSED(gain);
        auto __filtercoeff_04_activeResamp = this->filtercoeff_04_activeResamp;
        auto __filtercoeff_04_resamp_counter = this->filtercoeff_04_resamp_counter;
        auto __filtercoeff_04_K_EPSILON = this->filtercoeff_04_K_EPSILON;
    
        for (Index i = 0; i < n; i++) {
            number local_q = 1;
            number local_gain = 1;
    
            if (local_gain < 0)
                local_gain = 0;
    
            number local_frequency = frequency[(Index)i];
    
            if (local_q < __filtercoeff_04_K_EPSILON)
                local_q = __filtercoeff_04_K_EPSILON;
    
            local_frequency = (local_frequency > this->sr * 0.5 ? this->sr * 0.5 : (local_frequency < 1 ? 1 : local_frequency));
            __filtercoeff_04_resamp_counter--;
    
            if (__filtercoeff_04_resamp_counter <= 0) {
                __filtercoeff_04_resamp_counter = __filtercoeff_04_activeResamp;
                this->filtercoeff_04_updateTerms(local_frequency, local_gain, local_q);
            }
    
            a0[(Index)i] = this->filtercoeff_04_la0;
            a1[(Index)i] = this->filtercoeff_04_la1;
            a2[(Index)i] = this->filtercoeff_04_la2;
            b1[(Index)i] = this->filtercoeff_04_lb1;
            b2[(Index)i] = this->filtercoeff_04_lb2;
        }
    
        this->filtercoeff_04_resamp_counter = __filtercoeff_04_resamp_counter;
    }
    
    void biquad_tilde_08_perform(
        const Sample * x,
        const Sample * a0,
        const Sample * a1,
        const Sample * a2,
        const Sample * b1,
        const Sample * b2,
        SampleValue * out1,
        Index n
    ) {
        auto __biquad_tilde_08_y2 = this->biquad_tilde_08_y2;
        auto __biquad_tilde_08_y1 = this->biquad_tilde_08_y1;
        auto __biquad_tilde_08_x2 = this->biquad_tilde_08_x2;
        auto __biquad_tilde_08_x1 = this->biquad_tilde_08_x1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_08_x1 * a1[(Index)i] + __biquad_tilde_08_x2 * a2[(Index)i] - (__biquad_tilde_08_y1 * b1[(Index)i] + __biquad_tilde_08_y2 * b2[(Index)i]);
            __biquad_tilde_08_x2 = __biquad_tilde_08_x1;
            __biquad_tilde_08_x1 = x[(Index)i];
            __biquad_tilde_08_y2 = __biquad_tilde_08_y1;
            __biquad_tilde_08_y1 = tmp;
            out1[(Index)i] = tmp;
        }
    
        this->biquad_tilde_08_x1 = __biquad_tilde_08_x1;
        this->biquad_tilde_08_x2 = __biquad_tilde_08_x2;
        this->biquad_tilde_08_y1 = __biquad_tilde_08_y1;
        this->biquad_tilde_08_y2 = __biquad_tilde_08_y2;
    }
    
    void biquad_tilde_07_perform(
        const Sample * x,
        const Sample * a0,
        const Sample * a1,
        const Sample * a2,
        const Sample * b1,
        const Sample * b2,
        SampleValue * out1,
        Index n
    ) {
        auto __biquad_tilde_07_y2 = this->biquad_tilde_07_y2;
        auto __biquad_tilde_07_y1 = this->biquad_tilde_07_y1;
        auto __biquad_tilde_07_x2 = this->biquad_tilde_07_x2;
        auto __biquad_tilde_07_x1 = this->biquad_tilde_07_x1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_07_x1 * a1[(Index)i] + __biquad_tilde_07_x2 * a2[(Index)i] - (__biquad_tilde_07_y1 * b1[(Index)i] + __biquad_tilde_07_y2 * b2[(Index)i]);
            __biquad_tilde_07_x2 = __biquad_tilde_07_x1;
            __biquad_tilde_07_x1 = x[(Index)i];
            __biquad_tilde_07_y2 = __biquad_tilde_07_y1;
            __biquad_tilde_07_y1 = tmp;
            out1[(Index)i] = tmp;
        }
    
        this->biquad_tilde_07_x1 = __biquad_tilde_07_x1;
        this->biquad_tilde_07_x2 = __biquad_tilde_07_x2;
        this->biquad_tilde_07_y1 = __biquad_tilde_07_y1;
        this->biquad_tilde_07_y2 = __biquad_tilde_07_y2;
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void toggle_01_value_number_setter(number v) {
        this->toggle_01_value_number = (v != 0 ? 1 : 0);
    }
    
    void numberobj_14_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_14_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_14_value = localvalue;
    }
    
    void biquad_tilde_07_reset() {
        this->biquad_tilde_07_x1 = 0;
        this->biquad_tilde_07_x2 = 0;
        this->biquad_tilde_07_y1 = 0;
        this->biquad_tilde_07_y2 = 0;
    }
    
    void biquad_tilde_07_dspsetup(bool force) {
        if ((bool)(this->biquad_tilde_07_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->biquad_tilde_07_reset();
        this->biquad_tilde_07_setupDone = true;
    }
    
    void biquad_tilde_08_reset() {
        this->biquad_tilde_08_x1 = 0;
        this->biquad_tilde_08_x2 = 0;
        this->biquad_tilde_08_y1 = 0;
        this->biquad_tilde_08_y2 = 0;
    }
    
    void biquad_tilde_08_dspsetup(bool force) {
        if ((bool)(this->biquad_tilde_08_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->biquad_tilde_08_reset();
        this->biquad_tilde_08_setupDone = true;
    }
    
    void toggle_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->toggle_01_value_number;
    }
    
    void toggle_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->toggle_01_value_number_set(preset["value"]);
    }
    
    void numberobj_14_init() {
        this->numberobj_14_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("preq_LowCut~/number_obj-37"), 1, this->_currentTime);
    }
    
    void numberobj_14_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_14_value;
    }
    
    void numberobj_14_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_14_value_set(preset["value"]);
    }
    
    array<number, 5> filtercoeff_04_localop_next(number frequency, number q, number gain, number type) {
        number omega = frequency * this->filtercoeff_04_localop_twopi_over_sr;
        this->filtercoeff_04_localop_cs = rnbo_cos(omega);
        this->filtercoeff_04_localop_sn = rnbo_sin(omega);
        this->filtercoeff_04_localop_one_over_gain = (gain >= 0 ? (number)1 / gain : 0.0);
        this->filtercoeff_04_localop_one_over_q = (number)1 / q;
        this->filtercoeff_04_localop_alpha = this->filtercoeff_04_localop_sn * 0.5 * this->filtercoeff_04_localop_one_over_q;
    
        switch ((int)type) {
        case 5:
            {
            this->filtercoeff_04_localop_A = this->safesqrt(gain);
    
            this->filtercoeff_04_localop_beta = this->safesqrt(
                (this->filtercoeff_04_localop_A * this->filtercoeff_04_localop_A + 1.) * this->filtercoeff_04_localop_one_over_q - (this->filtercoeff_04_localop_A - 1.) * (this->filtercoeff_04_localop_A - 1.)
            );
    
            this->filtercoeff_04_localop_b0 = (number)1 / (this->filtercoeff_04_localop_A + 1. + (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs + this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn);
            break;
            }
        case 6:
            {
            this->filtercoeff_04_localop_A = this->safesqrt(gain);
    
            this->filtercoeff_04_localop_beta = this->safesqrt(
                (this->filtercoeff_04_localop_A * this->filtercoeff_04_localop_A + 1.) * this->filtercoeff_04_localop_one_over_q - (this->filtercoeff_04_localop_A - 1.) * (this->filtercoeff_04_localop_A - 1.)
            );
    
            this->filtercoeff_04_localop_b0 = (number)1 / (this->filtercoeff_04_localop_A + 1. - (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs + this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn);
            break;
            }
        case 4:
            {
            this->filtercoeff_04_localop_A = this->safesqrt(gain);
            this->filtercoeff_04_localop_one_over_a = (this->filtercoeff_04_localop_A == 0 ? 0 : (number)1 / this->filtercoeff_04_localop_A);
            this->filtercoeff_04_localop_b0 = (number)1 / (1. + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_a);
            break;
            }
        case 9:
        case 10:
        case 11:
        case 13:
        case 14:
            {
            this->filtercoeff_04_localop_b0 = (number)1 / (1. + this->filtercoeff_04_localop_alpha);
            this->filtercoeff_04_localop_b0g = (number)1 / (this->filtercoeff_04_localop_one_over_gain + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_gain);
            break;
            }
        default:
            {
            this->filtercoeff_04_localop_b0 = (number)1 / (1. + this->filtercoeff_04_localop_alpha);
            break;
            }
        }
    
        switch ((int)type) {
        case 0:
            {
            this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_la2 = (1. - this->filtercoeff_04_localop_cs) * 0.5 * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la1 = (1. - this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
            break;
            }
        case 1:
            {
            this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_la2 = (1. + this->filtercoeff_04_localop_cs) * 0.5 * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la1 = -(1. + this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
            break;
            }
        case 2:
            {
            this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la1 = 0.;
            this->filtercoeff_04_localop_la2 = -this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
            break;
            }
        case 7:
            {
            this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_alpha * q * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la1 = 0.;
            this->filtercoeff_04_localop_la2 = -this->filtercoeff_04_localop_alpha * q * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
            break;
            }
        case 3:
            {
            this->filtercoeff_04_localop_la1 = this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_la2 = this->filtercoeff_04_localop_b0;
            break;
            }
        case 8:
            {
            this->filtercoeff_04_localop_la1 = this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = this->filtercoeff_04_localop_la0 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la2 = 1.0;
            break;
            }
        case 4:
            {
            this->filtercoeff_04_localop_la0 = (1. + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_A) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la1 = this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la2 = (1. - this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_A) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_a) * this->filtercoeff_04_localop_b0;
            break;
            }
        case 5:
            {
            this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_A * (this->filtercoeff_04_localop_A + 1. - (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs + this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la1 = 2. * this->filtercoeff_04_localop_A * (this->filtercoeff_04_localop_A - 1 - (this->filtercoeff_04_localop_A + 1) * this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la2 = this->filtercoeff_04_localop_A * (this->filtercoeff_04_localop_A + 1. - (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs - this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb1 = -2. * (this->filtercoeff_04_localop_A - 1. + (this->filtercoeff_04_localop_A + 1.) * this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = (this->filtercoeff_04_localop_A + 1. + (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs - this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn) * this->filtercoeff_04_localop_b0;
            break;
            }
        case 6:
            {
            this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_A * (this->filtercoeff_04_localop_A + 1. + (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs + this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la1 = -2. * this->filtercoeff_04_localop_A * (this->filtercoeff_04_localop_A - 1. + (this->filtercoeff_04_localop_A + 1.) * this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la2 = this->filtercoeff_04_localop_A * (this->filtercoeff_04_localop_A + 1. + (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs - this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb1 = 2. * (this->filtercoeff_04_localop_A - 1. - (this->filtercoeff_04_localop_A + 1.) * this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = (this->filtercoeff_04_localop_A + 1. - (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs - this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn) * this->filtercoeff_04_localop_b0;
            break;
            }
        case 9:
            {
            this->filtercoeff_04_localop_b0g = (number)1 / (this->filtercoeff_04_localop_one_over_gain + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_gain);
            this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_la2 = (1. - this->filtercoeff_04_localop_cs) * 0.5 * this->filtercoeff_04_localop_b0g;
            this->filtercoeff_04_localop_la1 = (1. - this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0g;
            this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
            break;
            }
        case 10:
            {
            this->filtercoeff_04_localop_b0g = (number)1 / (this->filtercoeff_04_localop_one_over_gain + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_gain);
            this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_la2 = (1. + this->filtercoeff_04_localop_cs) * 0.5 * this->filtercoeff_04_localop_b0g;
            this->filtercoeff_04_localop_la1 = -(1. + this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0g;
            this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
            break;
            }
        case 11:
            {
            this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_alpha * gain * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la1 = 0.;
            this->filtercoeff_04_localop_la2 = -this->filtercoeff_04_localop_alpha * gain * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
            break;
            }
        case 13:
            {
            this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_alpha * gain * q * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la1 = 0.;
            this->filtercoeff_04_localop_la2 = -this->filtercoeff_04_localop_alpha * gain * q * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
            break;
            }
        case 12:
            {
            this->filtercoeff_04_localop_b0g = (number)1 / (this->filtercoeff_04_localop_one_over_gain + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_gain);
            this->filtercoeff_04_localop_la1 = this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs;
            this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la1 *= this->filtercoeff_04_localop_b0g;
            this->filtercoeff_04_localop_lb1 *= this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_b0g;
            this->filtercoeff_04_localop_la2 = this->filtercoeff_04_localop_b0g;
            break;
            }
        case 14:
            {
            this->filtercoeff_04_localop_b0g = (number)1 / (this->filtercoeff_04_localop_one_over_gain + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_gain);
            this->filtercoeff_04_localop_la0 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0g;
            this->filtercoeff_04_localop_la1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0g;
            this->filtercoeff_04_localop_la2 = gain;
            this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
            this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
            break;
            }
        case 15:
            {
            this->filtercoeff_04_localop_la0 = 1;
            this->filtercoeff_04_localop_la1 = 0;
            this->filtercoeff_04_localop_la2 = 0;
            this->filtercoeff_04_localop_lb1 = 0;
            this->filtercoeff_04_localop_lb2 = 0;
            }
        default:
            {
            break;
            }
        }
    
        return {
            this->filtercoeff_04_localop_la0,
            this->filtercoeff_04_localop_la1,
            this->filtercoeff_04_localop_la2,
            this->filtercoeff_04_localop_lb1,
            this->filtercoeff_04_localop_lb2
        };
    }
    
    void filtercoeff_04_localop_dspsetup() {
        this->filtercoeff_04_localop_twopi_over_sr = (number)6.283185307179586 / this->sr;
    }
    
    void filtercoeff_04_localop_reset() {
        this->filtercoeff_04_localop_twopi_over_sr = 0;
        this->filtercoeff_04_localop_cs = 0;
        this->filtercoeff_04_localop_sn = 0;
        this->filtercoeff_04_localop_one_over_gain = 0;
        this->filtercoeff_04_localop_one_over_q = 0;
        this->filtercoeff_04_localop_alpha = 0;
        this->filtercoeff_04_localop_beta = 0;
        this->filtercoeff_04_localop_b0 = 0;
        this->filtercoeff_04_localop_b0g = 0;
        this->filtercoeff_04_localop_A = 0;
        this->filtercoeff_04_localop_one_over_a = 0;
        this->filtercoeff_04_localop_la0 = 0;
        this->filtercoeff_04_localop_la1 = 0;
        this->filtercoeff_04_localop_la2 = 0;
        this->filtercoeff_04_localop_lb1 = 0;
        this->filtercoeff_04_localop_lb2 = 0;
    }
    
    void filtercoeff_04_updateTerms(number local_frequency, number local_gain, number local_q) {
        if ((bool)(this->filtercoeff_04_force_update) || local_frequency != this->filtercoeff_04_last_frequency || local_q != this->filtercoeff_04_last_q || local_gain != this->filtercoeff_04_last_gain || this->filtercoeff_04_type != this->filtercoeff_04_last_type) {
            array<number, 5> tmp = this->filtercoeff_04_localop_next(local_frequency, local_q, local_gain, this->filtercoeff_04_type);
            this->filtercoeff_04_la0 = tmp[0];
            this->filtercoeff_04_la1 = tmp[1];
            this->filtercoeff_04_la2 = tmp[2];
            this->filtercoeff_04_lb1 = tmp[3];
            this->filtercoeff_04_lb2 = tmp[4];
            this->filtercoeff_04_last_frequency = local_frequency;
            this->filtercoeff_04_last_q = local_q;
            this->filtercoeff_04_last_gain = local_gain;
            this->filtercoeff_04_last_type = this->filtercoeff_04_type;
            this->filtercoeff_04_force_update = false;
        }
    }
    
    void filtercoeff_04_dspsetup(bool force) {
        if ((bool)(this->filtercoeff_04_setupDone) && (bool)(!(bool)(force)))
            return;
    
        {
            this->filtercoeff_04_activeResamp = this->vectorsize();
        }
    
        this->filtercoeff_04_resamp_counter = 0;
        this->filtercoeff_04_la0 = 0.;
        this->filtercoeff_04_la1 = 0.;
        this->filtercoeff_04_la2 = 0.;
        this->filtercoeff_04_lb1 = 0.;
        this->filtercoeff_04_lb2 = 0.;
        this->filtercoeff_04_last_frequency = -1.;
        this->filtercoeff_04_last_q = -1.;
        this->filtercoeff_04_last_gain = -1.;
        this->filtercoeff_04_last_type = this->filtercoeff_04_type;
        this->filtercoeff_04_force_update = true;
        this->filtercoeff_04_setupDone = true;
        this->filtercoeff_04_localop_dspsetup();
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        biquad_tilde_07_x = 0;
        biquad_tilde_07_a0 = 0;
        biquad_tilde_07_a1 = 0;
        biquad_tilde_07_a2 = 0;
        biquad_tilde_07_b1 = 0;
        biquad_tilde_07_b2 = 0;
        biquad_tilde_08_x = 0;
        biquad_tilde_08_a0 = 0;
        biquad_tilde_08_a1 = 0;
        biquad_tilde_08_a2 = 0;
        biquad_tilde_08_b1 = 0;
        biquad_tilde_08_b2 = 0;
        toggle_01_value_number = 0;
        toggle_01_value_number_setter(toggle_01_value_number);
        numberobj_14_value = 0;
        numberobj_14_value_setter(numberobj_14_value);
        listlookup_01_lookup = { 20, 45 };
        linetilde_07_time = 10;
        linetilde_07_keepramp = 1;
        filtercoeff_04_frequency = 1000;
        filtercoeff_04_gain = 1;
        filtercoeff_04_q = 1;
        filtercoeff_04_type = 1;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        signals[4] = nullptr;
        signals[5] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        biquad_tilde_07_x1 = 0;
        biquad_tilde_07_x2 = 0;
        biquad_tilde_07_y1 = 0;
        biquad_tilde_07_y2 = 0;
        biquad_tilde_07_setupDone = false;
        biquad_tilde_08_x1 = 0;
        biquad_tilde_08_x2 = 0;
        biquad_tilde_08_y1 = 0;
        biquad_tilde_08_y2 = 0;
        biquad_tilde_08_setupDone = false;
        toggle_01_lastValue = 0;
        numberobj_14_currentFormat = 6;
        numberobj_14_lastValue = 0;
        linetilde_07_currentValue = 20;
        filtercoeff_04_K_EPSILON = 1e-9;
        filtercoeff_04_setupDone = false;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number biquad_tilde_07_x;
        number biquad_tilde_07_a0;
        number biquad_tilde_07_a1;
        number biquad_tilde_07_a2;
        number biquad_tilde_07_b1;
        number biquad_tilde_07_b2;
        number biquad_tilde_08_x;
        number biquad_tilde_08_a0;
        number biquad_tilde_08_a1;
        number biquad_tilde_08_a2;
        number biquad_tilde_08_b1;
        number biquad_tilde_08_b2;
        number toggle_01_value_number;
        number numberobj_14_value;
        list listlookup_01_input;
        list listlookup_01_lookup;
        list linetilde_07_segments;
        number linetilde_07_time;
        number linetilde_07_keepramp;
        number filtercoeff_04_frequency;
        number filtercoeff_04_gain;
        number filtercoeff_04_q;
        Int filtercoeff_04_type;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[6];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number biquad_tilde_07_x1;
        number biquad_tilde_07_x2;
        number biquad_tilde_07_y1;
        number biquad_tilde_07_y2;
        bool biquad_tilde_07_setupDone;
        number biquad_tilde_08_x1;
        number biquad_tilde_08_x2;
        number biquad_tilde_08_y1;
        number biquad_tilde_08_y2;
        bool biquad_tilde_08_setupDone;
        number toggle_01_lastValue;
        Int numberobj_14_currentFormat;
        number numberobj_14_lastValue;
        list linetilde_07_activeRamps;
        number linetilde_07_currentValue;
        number filtercoeff_04_resamp_counter;
        number filtercoeff_04_activeResamp;
        number filtercoeff_04_K_EPSILON;
        number filtercoeff_04_la0;
        number filtercoeff_04_la1;
        number filtercoeff_04_la2;
        number filtercoeff_04_lb1;
        number filtercoeff_04_lb2;
        number filtercoeff_04_last_frequency;
        number filtercoeff_04_last_q;
        number filtercoeff_04_last_gain;
        Int filtercoeff_04_last_type;
        bool filtercoeff_04_force_update;
        number filtercoeff_04_localop_twopi_over_sr;
        number filtercoeff_04_localop_cs;
        number filtercoeff_04_localop_sn;
        number filtercoeff_04_localop_one_over_gain;
        number filtercoeff_04_localop_one_over_q;
        number filtercoeff_04_localop_alpha;
        number filtercoeff_04_localop_beta;
        number filtercoeff_04_localop_b0;
        number filtercoeff_04_localop_b0g;
        number filtercoeff_04_localop_A;
        number filtercoeff_04_localop_one_over_a;
        number filtercoeff_04_localop_la0;
        number filtercoeff_04_localop_la1;
        number filtercoeff_04_localop_la2;
        number filtercoeff_04_localop_lb1;
        number filtercoeff_04_localop_lb2;
        bool filtercoeff_04_setupDone;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    delete this->p_01;
    delete this->p_02;
    delete this->p_03;
    delete this->p_04;
    delete this->p_05;
    delete this->p_06;
    delete this->p_07;
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, -62043057, false);
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

inline number safediv(number num, number denom) {
    return (denom == 0.0 ? 0.0 : num / denom);
}

number safepow(number base, number exponent) {
    return fixnan(rnbo_pow(base, exponent));
}

number scale(
    number x,
    number lowin,
    number hiin,
    number lowout,
    number highout,
    number pow
) {
    auto inscale = this->safediv(1., hiin - lowin);
    number outdiff = highout - lowout;
    number value = (x - lowin) * inscale;

    if (pow != 1) {
        if (value > 0)
            value = this->safepow(value, pow);
        else
            value = -this->safepow(-value, pow);
    }

    value = value * outdiff + lowout;
    return value;
}

inline number linearinterp(number frac, number x, number y) {
    return x + (y - x) * frac;
}

inline number cubicinterp(number a, number w, number x, number y, number z) {
    number a1 = 1. + a;
    number aa = a * a1;
    number b = 1. - a;
    number b1 = 2. - a;
    number bb = b * b1;
    number fw = -.1666667 * bb * a;
    number fx = .5 * bb * a1;
    number fy = .5 * aa * b1;
    number fz = -.1666667 * aa * b;
    return w * fw + x * fx + y * fy + z * fz;
}

inline number fastcubicinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = z - y - w + x;
    number f1 = w - x - f0;
    number f2 = y - w;
    number f3 = x;
    return f0 * a * a2 + f1 * a2 + f2 * a + f3;
}

inline number splineinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = -0.5 * w + 1.5 * x - 1.5 * y + 0.5 * z;
    number f1 = w - 2.5 * x + 2 * y - 0.5 * z;
    number f2 = -0.5 * w + 0.5 * y;
    return f0 * a * a2 + f1 * a2 + f2 * a + x;
}

inline number spline6interp(number a, number y0, number y1, number y2, number y3, number y4, number y5) {
    number ym2py2 = y0 + y4;
    number ym1py1 = y1 + y3;
    number y2mym2 = y4 - y0;
    number y1mym1 = y3 - y1;
    number sixthym1py1 = (number)1 / (number)6.0 * ym1py1;
    number c0 = (number)1 / (number)120.0 * ym2py2 + (number)13 / (number)60.0 * ym1py1 + (number)11 / (number)20.0 * y2;
    number c1 = (number)1 / (number)24.0 * y2mym2 + (number)5 / (number)12.0 * y1mym1;
    number c2 = (number)1 / (number)12.0 * ym2py2 + sixthym1py1 - (number)1 / (number)2.0 * y2;
    number c3 = (number)1 / (number)12.0 * y2mym2 - (number)1 / (number)6.0 * y1mym1;
    number c4 = (number)1 / (number)24.0 * ym2py2 - sixthym1py1 + (number)1 / (number)4.0 * y2;
    number c5 = (number)1 / (number)120.0 * (y5 - y0) + (number)1 / (number)24.0 * (y1 - y4) + (number)1 / (number)12.0 * (y3 - y2);
    return ((((c5 * a + c4) * a + c3) * a + c2) * a + c1) * a + c0;
}

inline number cosT8(number r) {
    number t84 = 56.0;
    number t83 = 1680.0;
    number t82 = 20160.0;
    number t81 = 2.4801587302e-05;
    number t73 = 42.0;
    number t72 = 840.0;
    number t71 = 1.9841269841e-04;

    if (r < 0.785398163397448309615660845819875721 && r > -0.785398163397448309615660845819875721) {
        number rr = r * r;
        return 1.0 - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
    } else if (r > 0.0) {
        r -= 1.57079632679489661923132169163975144;
        number rr = r * r;
        return -r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    } else {
        r += 1.57079632679489661923132169163975144;
        number rr = r * r;
        return r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    }
}

inline number cosineinterp(number frac, number x, number y) {
    number a2 = (1.0 - this->cosT8(frac * 3.14159265358979323846)) / (number)2.0;
    return x * (1.0 - a2) + y * a2;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number samplerate() const {
    return this->sr;
}

Index vectorsize() const {
    return this->vs;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

number wrap(number x, number low, number high) {
    number lo;
    number hi;

    if (low == high)
        return low;

    if (low > high) {
        hi = low;
        lo = high;
    } else {
        lo = low;
        hi = high;
    }

    number range = hi - lo;

    if (x >= lo && x < hi)
        return x;

    if (range <= 0.000000001)
        return lo;

    long numWraps = (long)(trunc((x - lo) / range));
    numWraps = numWraps - ((x < lo ? 1 : 0));
    number result = x - range * numWraps;

    if (result >= hi)
        return result - range;
    else
        return result;
}

Index voice() {
    return this->_voiceIndex;
}

number random(number low, number high) {
    number range = high - low;
    return globalrandom() * range + low;
}

inline number intnum(const number value) {
    return trunc(value);
}

inline number safemod(number f, number m) {
    if (m != 0) {
        Int f_trunc = (Int)(trunc(f));
        Int m_trunc = (Int)(trunc(m));

        if (f == f_trunc && m == m_trunc) {
            f = f_trunc % m_trunc;
        } else {
            if (m < 0) {
                m = -m;
            }

            if (f >= m) {
                if (f >= m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f -= m;
                }
            } else if (f <= -m) {
                if (f <= -m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f += m;
                }
            }
        }
    } else {
        f = 0.0;
    }

    return f;
}

SampleIndex currentsampletime() {
    return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
}

ParameterValue fromnormalized(ParameterIndex index, ParameterValue normalizedValue) {
    return this->convertFromNormalizedParameterValue(index, normalizedValue);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time);
    this->ctlin_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_02_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_03_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_04_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_05_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_06_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_07_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_08_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
    this->p_07_perform(in1, in2, this->signals[0], this->signals[1], n);
    this->p_06_perform(this->signals[0], this->signals[1], this->signals[2], this->signals[3], n);

    this->gen_02_perform(
        this->signals[2],
        this->signals[3],
        this->gen_02_pre_del,
        this->gen_02_lfo1_bw,
        this->gen_02_fb1,
        this->gen_02_lp,
        this->gen_02_decay2,
        this->gen_02_lpf,
        this->gen_02_x_fb,
        this->gen_02_lfo1_rate,
        this->gen_02_diff_gain,
        this->gen_02_apf_g,
        this->gen_02_mixfdn,
        this->gen_02_diff_num,
        this->signals[1],
        this->signals[0],
        this->dummyBuffer,
        n
    );

    this->gen_01_perform(
        this->signals[1],
        this->signals[0],
        this->gen_01_dry_wet,
        this->gen_01_lfo1_bw,
        this->gen_01_lpf,
        this->gen_01_fbc,
        this->gen_01_emphasis,
        this->gen_01_ptch,
        this->gen_01_decay,
        this->gen_01_ptch_ratio,
        this->gen_01_InGain,
        this->gen_01_modulation,
        this->gen_01_lfo1_rate,
        this->gen_01_d1,
        this->gen_01_g1,
        this->gen_01_d2,
        this->gen_01_g2,
        this->gen_01_d3,
        this->gen_01_g3,
        this->gen_01_d4,
        this->gen_01_g4,
        this->gen_01_d5,
        this->gen_01_g5,
        this->gen_01_d6,
        this->gen_01_d7,
        this->gen_01_d8,
        this->gen_01_d9,
        this->gen_01_d10,
        this->gen_01_g10,
        this->gen_01_d11,
        this->gen_01_g11,
        this->gen_01_damp,
        this->gen_01_dL1,
        this->gen_01_gL1,
        this->gen_01_dL2,
        this->gen_01_gL2,
        this->gen_01_dL3,
        this->gen_01_gL3,
        this->gen_01_dL4,
        this->gen_01_gL4,
        this->gen_01_dL5,
        this->gen_01_gL5,
        this->gen_01_dL6,
        this->gen_01_dL7,
        this->gen_01_dL8,
        this->gen_01_dL9,
        this->gen_01_dL10,
        this->gen_01_gL10,
        this->gen_01_dL11,
        this->gen_01_gL11,
        this->gen_01_dampL,
        this->signals[3],
        this->signals[2],
        n
    );

    this->p_03_perform(this->signals[3], this->signals[2], this->signals[0], this->signals[1], n);
    this->p_05_perform(this->signals[0], this->signals[1], this->signals[2], this->signals[3], n);
    this->p_04_perform(this->signals[2], this->signals[3], this->signals[1], this->signals[0], n);
    this->p_02_perform(this->signals[1], this->signals[0], this->signals[3], this->signals[2], n);
    this->linetilde_08_perform(this->signals[0], n);

    this->p_01_perform(
        in1,
        in2,
        this->signals[3],
        this->signals[2],
        this->signals[0],
        this->signals[1],
        this->signals[4],
        n
    );

    this->dspexpr_05_perform(this->signals[1], this->dspexpr_05_in2, this->dspexpr_05_in3, out1, n);
    this->dspexpr_06_perform(this->signals[4], this->dspexpr_06_in2, this->dspexpr_06_in3, out2, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 5; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->gen_02_dspsetup(forceDSPSetup);
    this->gen_01_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);
    this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_03->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_04->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_05->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_06->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_07->prepareToProcess(sampleRate, maxBlockSize, force);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->gen_01_delay_1_bufferobj);
        break;
        }
    case 1:
        {
        return addressOf(this->gen_01_delay_2_bufferobj);
        break;
        }
    case 2:
        {
        return addressOf(this->gen_01_delay_5_bufferobj);
        break;
        }
    case 3:
        {
        return addressOf(this->gen_01_DL1_bufferobj);
        break;
        }
    case 4:
        {
        return addressOf(this->gen_01_DL2_bufferobj);
        break;
        }
    case 5:
        {
        return addressOf(this->gen_01_DL3_bufferobj);
        break;
        }
    case 6:
        {
        return addressOf(this->gen_01_DL4_bufferobj);
        break;
        }
    case 7:
        {
        return addressOf(this->gen_01_DL5_bufferobj);
        break;
        }
    case 8:
        {
        return addressOf(this->gen_01_DL6_bufferobj);
        break;
        }
    case 9:
        {
        return addressOf(this->gen_01_DL7_bufferobj);
        break;
        }
    case 10:
        {
        return addressOf(this->gen_01_DL8_bufferobj);
        break;
        }
    case 11:
        {
        return addressOf(this->gen_01_DL9_bufferobj);
        break;
        }
    case 12:
        {
        return addressOf(this->gen_01_DL10_bufferobj);
        break;
        }
    case 13:
        {
        return addressOf(this->gen_01_DL11_bufferobj);
        break;
        }
    case 14:
        {
        return addressOf(this->gen_01_DL12_bufferobj);
        break;
        }
    case 15:
        {
        return addressOf(this->gen_01_DL13_bufferobj);
        break;
        }
    case 16:
        {
        return addressOf(this->gen_01_delay_9_bufferobj);
        break;
        }
    case 17:
        {
        return addressOf(this->gen_01_dlL1_bufferobj);
        break;
        }
    case 18:
        {
        return addressOf(this->gen_01_dlL2_bufferobj);
        break;
        }
    case 19:
        {
        return addressOf(this->gen_01_dlL3_bufferobj);
        break;
        }
    case 20:
        {
        return addressOf(this->gen_01_dlL4_bufferobj);
        break;
        }
    case 21:
        {
        return addressOf(this->gen_01_dlL5_bufferobj);
        break;
        }
    case 22:
        {
        return addressOf(this->gen_01_dlL6_bufferobj);
        break;
        }
    case 23:
        {
        return addressOf(this->gen_01_dlL7_bufferobj);
        break;
        }
    case 24:
        {
        return addressOf(this->gen_01_dlL8_bufferobj);
        break;
        }
    case 25:
        {
        return addressOf(this->gen_01_dlL9_bufferobj);
        break;
        }
    case 26:
        {
        return addressOf(this->gen_01_dlL10_bufferobj);
        break;
        }
    case 27:
        {
        return addressOf(this->gen_01_dlL11_bufferobj);
        break;
        }
    case 28:
        {
        return addressOf(this->gen_01_dlL12_bufferobj);
        break;
        }
    case 29:
        {
        return addressOf(this->gen_01_dlL13_bufferobj);
        break;
        }
    case 30:
        {
        return addressOf(this->RNBODefaultSinus);
        break;
        }
    case 31:
        {
        return addressOf(this->gen_02_delay_1_bufferobj);
        break;
        }
    case 32:
        {
        return addressOf(this->gen_02_delay_2_bufferobj);
        break;
        }
    case 33:
        {
        return addressOf(this->gen_02_delay_3_bufferobj);
        break;
        }
    case 34:
        {
        return addressOf(this->gen_02_delay_4_bufferobj);
        break;
        }
    case 35:
        {
        return addressOf(this->gen_02_delay_5_bufferobj);
        break;
        }
    case 36:
        {
        return addressOf(this->gen_02_delay_6_bufferobj);
        break;
        }
    case 37:
        {
        return addressOf(this->gen_02_delay_7_bufferobj);
        break;
        }
    case 38:
        {
        return addressOf(this->gen_02_delay_8_bufferobj);
        break;
        }
    case 39:
        {
        return addressOf(this->gen_02_delay_9_bufferobj);
        break;
        }
    case 40:
        {
        return addressOf(this->gen_02_delay_10_bufferobj);
        break;
        }
    case 41:
        {
        return addressOf(this->gen_02_delay_11_bufferobj);
        break;
        }
    case 42:
        {
        return addressOf(this->gen_02_delay_12_bufferobj);
        break;
        }
    case 43:
        {
        return addressOf(this->gen_02_delay_13_bufferobj);
        break;
        }
    case 44:
        {
        return addressOf(this->gen_02_delay_14_bufferobj);
        break;
        }
    case 45:
        {
        return addressOf(this->gen_02_delay_15_bufferobj);
        break;
        }
    case 46:
        {
        return addressOf(this->gen_02_delay_17_bufferobj);
        break;
        }
    case 47:
        {
        return addressOf(this->gen_02_delay_18_bufferobj);
        break;
        }
    case 48:
        {
        return addressOf(this->gen_02_delay_19_bufferobj);
        break;
        }
    case 49:
        {
        return addressOf(this->gen_02_delay_20_bufferobj);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 50;
}

void fillRNBODefaultSinus(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        buffer[i] = rnbo_cos(i * 3.14159265358979323846 * 2. / bufsize);
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 30:
        {
        this->fillRNBODefaultSinus(ref);
        break;
        }
    }
}

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time);

    if (index == 0) {
        this->gen_01_delay_1_buffer = new Float64Buffer(this->gen_01_delay_1_bufferobj);
    }

    if (index == 1) {
        this->gen_01_delay_2_buffer = new Float64Buffer(this->gen_01_delay_2_bufferobj);
    }

    if (index == 2) {
        this->gen_01_delay_5_buffer = new Float64Buffer(this->gen_01_delay_5_bufferobj);
    }

    if (index == 3) {
        this->gen_01_DL1_buffer = new Float64Buffer(this->gen_01_DL1_bufferobj);
    }

    if (index == 4) {
        this->gen_01_DL2_buffer = new Float64Buffer(this->gen_01_DL2_bufferobj);
    }

    if (index == 5) {
        this->gen_01_DL3_buffer = new Float64Buffer(this->gen_01_DL3_bufferobj);
    }

    if (index == 6) {
        this->gen_01_DL4_buffer = new Float64Buffer(this->gen_01_DL4_bufferobj);
    }

    if (index == 7) {
        this->gen_01_DL5_buffer = new Float64Buffer(this->gen_01_DL5_bufferobj);
    }

    if (index == 8) {
        this->gen_01_DL6_buffer = new Float64Buffer(this->gen_01_DL6_bufferobj);
    }

    if (index == 9) {
        this->gen_01_DL7_buffer = new Float64Buffer(this->gen_01_DL7_bufferobj);
    }

    if (index == 10) {
        this->gen_01_DL8_buffer = new Float64Buffer(this->gen_01_DL8_bufferobj);
    }

    if (index == 11) {
        this->gen_01_DL9_buffer = new Float64Buffer(this->gen_01_DL9_bufferobj);
    }

    if (index == 12) {
        this->gen_01_DL10_buffer = new Float64Buffer(this->gen_01_DL10_bufferobj);
    }

    if (index == 13) {
        this->gen_01_DL11_buffer = new Float64Buffer(this->gen_01_DL11_bufferobj);
    }

    if (index == 14) {
        this->gen_01_DL12_buffer = new Float64Buffer(this->gen_01_DL12_bufferobj);
    }

    if (index == 15) {
        this->gen_01_DL13_buffer = new Float64Buffer(this->gen_01_DL13_bufferobj);
    }

    if (index == 16) {
        this->gen_01_delay_9_buffer = new Float64Buffer(this->gen_01_delay_9_bufferobj);
    }

    if (index == 17) {
        this->gen_01_dlL1_buffer = new Float64Buffer(this->gen_01_dlL1_bufferobj);
    }

    if (index == 18) {
        this->gen_01_dlL2_buffer = new Float64Buffer(this->gen_01_dlL2_bufferobj);
    }

    if (index == 19) {
        this->gen_01_dlL3_buffer = new Float64Buffer(this->gen_01_dlL3_bufferobj);
    }

    if (index == 20) {
        this->gen_01_dlL4_buffer = new Float64Buffer(this->gen_01_dlL4_bufferobj);
    }

    if (index == 21) {
        this->gen_01_dlL5_buffer = new Float64Buffer(this->gen_01_dlL5_bufferobj);
    }

    if (index == 22) {
        this->gen_01_dlL6_buffer = new Float64Buffer(this->gen_01_dlL6_bufferobj);
    }

    if (index == 23) {
        this->gen_01_dlL7_buffer = new Float64Buffer(this->gen_01_dlL7_bufferobj);
    }

    if (index == 24) {
        this->gen_01_dlL8_buffer = new Float64Buffer(this->gen_01_dlL8_bufferobj);
    }

    if (index == 25) {
        this->gen_01_dlL9_buffer = new Float64Buffer(this->gen_01_dlL9_bufferobj);
    }

    if (index == 26) {
        this->gen_01_dlL10_buffer = new Float64Buffer(this->gen_01_dlL10_bufferobj);
    }

    if (index == 27) {
        this->gen_01_dlL11_buffer = new Float64Buffer(this->gen_01_dlL11_bufferobj);
    }

    if (index == 28) {
        this->gen_01_dlL12_buffer = new Float64Buffer(this->gen_01_dlL12_bufferobj);
    }

    if (index == 29) {
        this->gen_01_dlL13_buffer = new Float64Buffer(this->gen_01_dlL13_bufferobj);
    }

    if (index == 30) {
        this->gen_01_cycle_6_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_01_cycle_11_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_01_cycle_16_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_01_cycle_21_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_01_cycle_26_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_01_cycle_31_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_01_cycle_36_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_01_cycle_41_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_01_cycle_46_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_01_cycle_54_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_02_cycle_43_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_02_cycle_50_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_02_cycle_63_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_02_cycle_118_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_02_cycle_135_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_02_cycle_144_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_02_cycle_161_buffer = new Float64Buffer(this->RNBODefaultSinus);
        this->gen_02_cycle_186_buffer = new Float64Buffer(this->RNBODefaultSinus);
    }

    if (index == 31) {
        this->gen_02_delay_1_buffer = new Float64Buffer(this->gen_02_delay_1_bufferobj);
    }

    if (index == 32) {
        this->gen_02_delay_2_buffer = new Float64Buffer(this->gen_02_delay_2_bufferobj);
    }

    if (index == 33) {
        this->gen_02_delay_3_buffer = new Float64Buffer(this->gen_02_delay_3_bufferobj);
    }

    if (index == 34) {
        this->gen_02_delay_4_buffer = new Float64Buffer(this->gen_02_delay_4_bufferobj);
    }

    if (index == 35) {
        this->gen_02_delay_5_buffer = new Float64Buffer(this->gen_02_delay_5_bufferobj);
    }

    if (index == 36) {
        this->gen_02_delay_6_buffer = new Float64Buffer(this->gen_02_delay_6_bufferobj);
    }

    if (index == 37) {
        this->gen_02_delay_7_buffer = new Float64Buffer(this->gen_02_delay_7_bufferobj);
    }

    if (index == 38) {
        this->gen_02_delay_8_buffer = new Float64Buffer(this->gen_02_delay_8_bufferobj);
    }

    if (index == 39) {
        this->gen_02_delay_9_buffer = new Float64Buffer(this->gen_02_delay_9_bufferobj);
    }

    if (index == 40) {
        this->gen_02_delay_10_buffer = new Float64Buffer(this->gen_02_delay_10_bufferobj);
    }

    if (index == 41) {
        this->gen_02_delay_11_buffer = new Float64Buffer(this->gen_02_delay_11_bufferobj);
    }

    if (index == 42) {
        this->gen_02_delay_12_buffer = new Float64Buffer(this->gen_02_delay_12_bufferobj);
    }

    if (index == 43) {
        this->gen_02_delay_13_buffer = new Float64Buffer(this->gen_02_delay_13_bufferobj);
    }

    if (index == 44) {
        this->gen_02_delay_14_buffer = new Float64Buffer(this->gen_02_delay_14_bufferobj);
    }

    if (index == 45) {
        this->gen_02_delay_15_buffer = new Float64Buffer(this->gen_02_delay_15_bufferobj);
    }

    if (index == 46) {
        this->gen_02_delay_17_buffer = new Float64Buffer(this->gen_02_delay_17_bufferobj);
    }

    if (index == 47) {
        this->gen_02_delay_18_buffer = new Float64Buffer(this->gen_02_delay_18_bufferobj);
    }

    if (index == 48) {
        this->gen_02_delay_19_buffer = new Float64Buffer(this->gen_02_delay_19_bufferobj);
    }

    if (index == 49) {
        this->gen_02_delay_20_buffer = new Float64Buffer(this->gen_02_delay_20_bufferobj);
    }

    this->p_01->processDataViewUpdate(index, time);
    this->p_02->processDataViewUpdate(index, time);
    this->p_03->processDataViewUpdate(index, time);
    this->p_04->processDataViewUpdate(index, time);
    this->p_05->processDataViewUpdate(index, time);
    this->p_06->processDataViewUpdate(index, time);
    this->p_07->processDataViewUpdate(index, time);
}

void initialize() {
    this->gen_01_delay_1_bufferobj = initDataRef("gen_01_delay_1_bufferobj", true, nullptr, "buffer~");
    this->gen_01_delay_2_bufferobj = initDataRef("gen_01_delay_2_bufferobj", true, nullptr, "buffer~");
    this->gen_01_delay_5_bufferobj = initDataRef("gen_01_delay_5_bufferobj", true, nullptr, "buffer~");
    this->gen_01_DL1_bufferobj = initDataRef("gen_01_DL1_bufferobj", true, nullptr, "buffer~");
    this->gen_01_DL2_bufferobj = initDataRef("gen_01_DL2_bufferobj", true, nullptr, "buffer~");
    this->gen_01_DL3_bufferobj = initDataRef("gen_01_DL3_bufferobj", true, nullptr, "buffer~");
    this->gen_01_DL4_bufferobj = initDataRef("gen_01_DL4_bufferobj", true, nullptr, "buffer~");
    this->gen_01_DL5_bufferobj = initDataRef("gen_01_DL5_bufferobj", true, nullptr, "buffer~");
    this->gen_01_DL6_bufferobj = initDataRef("gen_01_DL6_bufferobj", true, nullptr, "buffer~");
    this->gen_01_DL7_bufferobj = initDataRef("gen_01_DL7_bufferobj", true, nullptr, "buffer~");
    this->gen_01_DL8_bufferobj = initDataRef("gen_01_DL8_bufferobj", true, nullptr, "buffer~");
    this->gen_01_DL9_bufferobj = initDataRef("gen_01_DL9_bufferobj", true, nullptr, "buffer~");
    this->gen_01_DL10_bufferobj = initDataRef("gen_01_DL10_bufferobj", true, nullptr, "buffer~");
    this->gen_01_DL11_bufferobj = initDataRef("gen_01_DL11_bufferobj", true, nullptr, "buffer~");
    this->gen_01_DL12_bufferobj = initDataRef("gen_01_DL12_bufferobj", true, nullptr, "buffer~");
    this->gen_01_DL13_bufferobj = initDataRef("gen_01_DL13_bufferobj", true, nullptr, "buffer~");
    this->gen_01_delay_9_bufferobj = initDataRef("gen_01_delay_9_bufferobj", true, nullptr, "buffer~");
    this->gen_01_dlL1_bufferobj = initDataRef("gen_01_dlL1_bufferobj", true, nullptr, "buffer~");
    this->gen_01_dlL2_bufferobj = initDataRef("gen_01_dlL2_bufferobj", true, nullptr, "buffer~");
    this->gen_01_dlL3_bufferobj = initDataRef("gen_01_dlL3_bufferobj", true, nullptr, "buffer~");
    this->gen_01_dlL4_bufferobj = initDataRef("gen_01_dlL4_bufferobj", true, nullptr, "buffer~");
    this->gen_01_dlL5_bufferobj = initDataRef("gen_01_dlL5_bufferobj", true, nullptr, "buffer~");
    this->gen_01_dlL6_bufferobj = initDataRef("gen_01_dlL6_bufferobj", true, nullptr, "buffer~");
    this->gen_01_dlL7_bufferobj = initDataRef("gen_01_dlL7_bufferobj", true, nullptr, "buffer~");
    this->gen_01_dlL8_bufferobj = initDataRef("gen_01_dlL8_bufferobj", true, nullptr, "buffer~");
    this->gen_01_dlL9_bufferobj = initDataRef("gen_01_dlL9_bufferobj", true, nullptr, "buffer~");
    this->gen_01_dlL10_bufferobj = initDataRef("gen_01_dlL10_bufferobj", true, nullptr, "buffer~");
    this->gen_01_dlL11_bufferobj = initDataRef("gen_01_dlL11_bufferobj", true, nullptr, "buffer~");
    this->gen_01_dlL12_bufferobj = initDataRef("gen_01_dlL12_bufferobj", true, nullptr, "buffer~");
    this->gen_01_dlL13_bufferobj = initDataRef("gen_01_dlL13_bufferobj", true, nullptr, "buffer~");
    this->RNBODefaultSinus = initDataRef("RNBODefaultSinus", true, nullptr, "buffer~");
    this->gen_02_delay_1_bufferobj = initDataRef("gen_02_delay_1_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_2_bufferobj = initDataRef("gen_02_delay_2_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_3_bufferobj = initDataRef("gen_02_delay_3_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_4_bufferobj = initDataRef("gen_02_delay_4_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_5_bufferobj = initDataRef("gen_02_delay_5_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_6_bufferobj = initDataRef("gen_02_delay_6_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_7_bufferobj = initDataRef("gen_02_delay_7_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_8_bufferobj = initDataRef("gen_02_delay_8_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_9_bufferobj = initDataRef("gen_02_delay_9_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_10_bufferobj = initDataRef("gen_02_delay_10_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_11_bufferobj = initDataRef("gen_02_delay_11_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_12_bufferobj = initDataRef("gen_02_delay_12_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_13_bufferobj = initDataRef("gen_02_delay_13_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_14_bufferobj = initDataRef("gen_02_delay_14_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_15_bufferobj = initDataRef("gen_02_delay_15_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_17_bufferobj = initDataRef("gen_02_delay_17_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_18_bufferobj = initDataRef("gen_02_delay_18_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_19_bufferobj = initDataRef("gen_02_delay_19_bufferobj", true, nullptr, "buffer~");
    this->gen_02_delay_20_bufferobj = initDataRef("gen_02_delay_20_bufferobj", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->gen_01_delay_1_bufferobj->setIndex(0);
    this->gen_01_delay_1_buffer = new Float64Buffer(this->gen_01_delay_1_bufferobj);
    this->gen_01_delay_2_bufferobj->setIndex(1);
    this->gen_01_delay_2_buffer = new Float64Buffer(this->gen_01_delay_2_bufferobj);
    this->gen_01_delay_5_bufferobj->setIndex(2);
    this->gen_01_delay_5_buffer = new Float64Buffer(this->gen_01_delay_5_bufferobj);
    this->gen_01_DL1_bufferobj->setIndex(3);
    this->gen_01_DL1_buffer = new Float64Buffer(this->gen_01_DL1_bufferobj);
    this->gen_01_DL2_bufferobj->setIndex(4);
    this->gen_01_DL2_buffer = new Float64Buffer(this->gen_01_DL2_bufferobj);
    this->gen_01_DL3_bufferobj->setIndex(5);
    this->gen_01_DL3_buffer = new Float64Buffer(this->gen_01_DL3_bufferobj);
    this->gen_01_DL4_bufferobj->setIndex(6);
    this->gen_01_DL4_buffer = new Float64Buffer(this->gen_01_DL4_bufferobj);
    this->gen_01_DL5_bufferobj->setIndex(7);
    this->gen_01_DL5_buffer = new Float64Buffer(this->gen_01_DL5_bufferobj);
    this->gen_01_DL6_bufferobj->setIndex(8);
    this->gen_01_DL6_buffer = new Float64Buffer(this->gen_01_DL6_bufferobj);
    this->gen_01_DL7_bufferobj->setIndex(9);
    this->gen_01_DL7_buffer = new Float64Buffer(this->gen_01_DL7_bufferobj);
    this->gen_01_DL8_bufferobj->setIndex(10);
    this->gen_01_DL8_buffer = new Float64Buffer(this->gen_01_DL8_bufferobj);
    this->gen_01_DL9_bufferobj->setIndex(11);
    this->gen_01_DL9_buffer = new Float64Buffer(this->gen_01_DL9_bufferobj);
    this->gen_01_DL10_bufferobj->setIndex(12);
    this->gen_01_DL10_buffer = new Float64Buffer(this->gen_01_DL10_bufferobj);
    this->gen_01_DL11_bufferobj->setIndex(13);
    this->gen_01_DL11_buffer = new Float64Buffer(this->gen_01_DL11_bufferobj);
    this->gen_01_DL12_bufferobj->setIndex(14);
    this->gen_01_DL12_buffer = new Float64Buffer(this->gen_01_DL12_bufferobj);
    this->gen_01_DL13_bufferobj->setIndex(15);
    this->gen_01_DL13_buffer = new Float64Buffer(this->gen_01_DL13_bufferobj);
    this->gen_01_delay_9_bufferobj->setIndex(16);
    this->gen_01_delay_9_buffer = new Float64Buffer(this->gen_01_delay_9_bufferobj);
    this->gen_01_dlL1_bufferobj->setIndex(17);
    this->gen_01_dlL1_buffer = new Float64Buffer(this->gen_01_dlL1_bufferobj);
    this->gen_01_dlL2_bufferobj->setIndex(18);
    this->gen_01_dlL2_buffer = new Float64Buffer(this->gen_01_dlL2_bufferobj);
    this->gen_01_dlL3_bufferobj->setIndex(19);
    this->gen_01_dlL3_buffer = new Float64Buffer(this->gen_01_dlL3_bufferobj);
    this->gen_01_dlL4_bufferobj->setIndex(20);
    this->gen_01_dlL4_buffer = new Float64Buffer(this->gen_01_dlL4_bufferobj);
    this->gen_01_dlL5_bufferobj->setIndex(21);
    this->gen_01_dlL5_buffer = new Float64Buffer(this->gen_01_dlL5_bufferobj);
    this->gen_01_dlL6_bufferobj->setIndex(22);
    this->gen_01_dlL6_buffer = new Float64Buffer(this->gen_01_dlL6_bufferobj);
    this->gen_01_dlL7_bufferobj->setIndex(23);
    this->gen_01_dlL7_buffer = new Float64Buffer(this->gen_01_dlL7_bufferobj);
    this->gen_01_dlL8_bufferobj->setIndex(24);
    this->gen_01_dlL8_buffer = new Float64Buffer(this->gen_01_dlL8_bufferobj);
    this->gen_01_dlL9_bufferobj->setIndex(25);
    this->gen_01_dlL9_buffer = new Float64Buffer(this->gen_01_dlL9_bufferobj);
    this->gen_01_dlL10_bufferobj->setIndex(26);
    this->gen_01_dlL10_buffer = new Float64Buffer(this->gen_01_dlL10_bufferobj);
    this->gen_01_dlL11_bufferobj->setIndex(27);
    this->gen_01_dlL11_buffer = new Float64Buffer(this->gen_01_dlL11_bufferobj);
    this->gen_01_dlL12_bufferobj->setIndex(28);
    this->gen_01_dlL12_buffer = new Float64Buffer(this->gen_01_dlL12_bufferobj);
    this->gen_01_dlL13_bufferobj->setIndex(29);
    this->gen_01_dlL13_buffer = new Float64Buffer(this->gen_01_dlL13_bufferobj);
    this->RNBODefaultSinus->setIndex(30);
    this->gen_01_cycle_6_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_01_cycle_11_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_01_cycle_16_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_01_cycle_21_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_01_cycle_26_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_01_cycle_31_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_01_cycle_36_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_01_cycle_41_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_01_cycle_46_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_01_cycle_54_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_02_cycle_43_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_02_cycle_50_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_02_cycle_63_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_02_cycle_118_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_02_cycle_135_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_02_cycle_144_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_02_cycle_161_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_02_cycle_186_buffer = new Float64Buffer(this->RNBODefaultSinus);
    this->gen_02_delay_1_bufferobj->setIndex(31);
    this->gen_02_delay_1_buffer = new Float64Buffer(this->gen_02_delay_1_bufferobj);
    this->gen_02_delay_2_bufferobj->setIndex(32);
    this->gen_02_delay_2_buffer = new Float64Buffer(this->gen_02_delay_2_bufferobj);
    this->gen_02_delay_3_bufferobj->setIndex(33);
    this->gen_02_delay_3_buffer = new Float64Buffer(this->gen_02_delay_3_bufferobj);
    this->gen_02_delay_4_bufferobj->setIndex(34);
    this->gen_02_delay_4_buffer = new Float64Buffer(this->gen_02_delay_4_bufferobj);
    this->gen_02_delay_5_bufferobj->setIndex(35);
    this->gen_02_delay_5_buffer = new Float64Buffer(this->gen_02_delay_5_bufferobj);
    this->gen_02_delay_6_bufferobj->setIndex(36);
    this->gen_02_delay_6_buffer = new Float64Buffer(this->gen_02_delay_6_bufferobj);
    this->gen_02_delay_7_bufferobj->setIndex(37);
    this->gen_02_delay_7_buffer = new Float64Buffer(this->gen_02_delay_7_bufferobj);
    this->gen_02_delay_8_bufferobj->setIndex(38);
    this->gen_02_delay_8_buffer = new Float64Buffer(this->gen_02_delay_8_bufferobj);
    this->gen_02_delay_9_bufferobj->setIndex(39);
    this->gen_02_delay_9_buffer = new Float64Buffer(this->gen_02_delay_9_bufferobj);
    this->gen_02_delay_10_bufferobj->setIndex(40);
    this->gen_02_delay_10_buffer = new Float64Buffer(this->gen_02_delay_10_bufferobj);
    this->gen_02_delay_11_bufferobj->setIndex(41);
    this->gen_02_delay_11_buffer = new Float64Buffer(this->gen_02_delay_11_bufferobj);
    this->gen_02_delay_12_bufferobj->setIndex(42);
    this->gen_02_delay_12_buffer = new Float64Buffer(this->gen_02_delay_12_bufferobj);
    this->gen_02_delay_13_bufferobj->setIndex(43);
    this->gen_02_delay_13_buffer = new Float64Buffer(this->gen_02_delay_13_bufferobj);
    this->gen_02_delay_14_bufferobj->setIndex(44);
    this->gen_02_delay_14_buffer = new Float64Buffer(this->gen_02_delay_14_bufferobj);
    this->gen_02_delay_15_bufferobj->setIndex(45);
    this->gen_02_delay_15_buffer = new Float64Buffer(this->gen_02_delay_15_bufferobj);
    this->gen_02_delay_17_bufferobj->setIndex(46);
    this->gen_02_delay_17_buffer = new Float64Buffer(this->gen_02_delay_17_bufferobj);
    this->gen_02_delay_18_bufferobj->setIndex(47);
    this->gen_02_delay_18_buffer = new Float64Buffer(this->gen_02_delay_18_bufferobj);
    this->gen_02_delay_19_bufferobj->setIndex(48);
    this->gen_02_delay_19_buffer = new Float64Buffer(this->gen_02_delay_19_bufferobj);
    this->gen_02_delay_20_bufferobj->setIndex(49);
    this->gen_02_delay_20_buffer = new Float64Buffer(this->gen_02_delay_20_bufferobj);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {
    this->p_01 = new RNBOSubpatcher_188();
    this->p_01->setEngineAndPatcher(this->getEngine(), this);
    this->p_01->initialize();
    this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
    this->p_02 = new RNBOSubpatcher_189();
    this->p_02->setEngineAndPatcher(this->getEngine(), this);
    this->p_02->initialize();
    this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
    this->p_03 = new RNBOSubpatcher_190();
    this->p_03->setEngineAndPatcher(this->getEngine(), this);
    this->p_03->initialize();
    this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
    this->p_04 = new RNBOSubpatcher_191();
    this->p_04->setEngineAndPatcher(this->getEngine(), this);
    this->p_04->initialize();
    this->p_04->setParameterOffset(this->getParameterOffset(this->p_04));
    this->p_05 = new RNBOSubpatcher_192();
    this->p_05->setEngineAndPatcher(this->getEngine(), this);
    this->p_05->initialize();
    this->p_05->setParameterOffset(this->getParameterOffset(this->p_05));
    this->p_06 = new RNBOSubpatcher_193();
    this->p_06->setEngineAndPatcher(this->getEngine(), this);
    this->p_06->initialize();
    this->p_06->setParameterOffset(this->getParameterOffset(this->p_06));
    this->p_07 = new RNBOSubpatcher_194();
    this->p_07->setEngineAndPatcher(this->getEngine(), this);
    this->p_07->initialize();
    this->p_07->setParameterOffset(this->getParameterOffset(this->p_07));
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "diff_num"));
    this->param_02_getPresetValue(getSubState(preset, "pre_del"));
    this->param_03_getPresetValue(getSubState(preset, "fb1"));
    this->param_04_getPresetValue(getSubState(preset, "x_fb"));
    this->param_05_getPresetValue(getSubState(preset, "apf_g"));
    this->param_06_getPresetValue(getSubState(preset, "Size"));
    this->param_07_getPresetValue(getSubState(preset, "lowcut"));
    this->param_08_getPresetValue(getSubState(preset, "post_level"));
    this->param_09_getPresetValue(getSubState(preset, "preq_level"));
    this->param_10_getPresetValue(getSubState(preset, "mix"));
    this->param_11_getPresetValue(getSubState(preset, "low_cut"));
    this->param_12_getPresetValue(getSubState(preset, "himid_lev"));
    this->param_13_getPresetValue(getSubState(preset, "himidfq"));
    this->param_14_getPresetValue(getSubState(preset, "high_cut"));
    this->param_15_getPresetValue(getSubState(preset, "lfo1_bw"));
    this->param_16_getPresetValue(getSubState(preset, "r_Feedback"));
    this->param_18_getPresetValue(getSubState(preset, "lfo1_rate"));
    this->param_19_getPresetValue(getSubState(preset, "r_Damp"));
    this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "Full_Mix~"));
    this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "preq_Level~"));
    this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "LowCut~"));
    this->p_04->getPreset(getSubState(getSubState(preset, "__sps"), "HighCut~"));
    this->p_05->getPreset(getSubState(getSubState(preset, "__sps"), "HighMid~"));
    this->p_06->getPreset(getSubState(getSubState(preset, "__sps"), "preq_Level~[1]"));
    this->p_07->getPreset(getSubState(getSubState(preset, "__sps"), "preq_LowCut~"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_01_setPresetValue(getSubState(preset, "diff_num"));
    this->param_02_setPresetValue(getSubState(preset, "pre_del"));
    this->param_03_setPresetValue(getSubState(preset, "fb1"));
    this->param_04_setPresetValue(getSubState(preset, "x_fb"));
    this->param_05_setPresetValue(getSubState(preset, "apf_g"));
    this->param_06_setPresetValue(getSubState(preset, "Size"));
    this->param_15_setPresetValue(getSubState(preset, "lfo1_bw"));
    this->param_16_setPresetValue(getSubState(preset, "r_Feedback"));
    this->param_18_setPresetValue(getSubState(preset, "lfo1_rate"));
    this->param_19_setPresetValue(getSubState(preset, "r_Damp"));
    this->param_07_setPresetValue(getSubState(preset, "lowcut"));
    this->param_11_setPresetValue(getSubState(preset, "low_cut"));
    this->param_13_setPresetValue(getSubState(preset, "himidfq"));
    this->param_10_setPresetValue(getSubState(preset, "mix"));
    this->param_12_setPresetValue(getSubState(preset, "himid_lev"));
    this->param_14_setPresetValue(getSubState(preset, "high_cut"));
    this->param_08_setPresetValue(getSubState(preset, "post_level"));
    this->param_09_setPresetValue(getSubState(preset, "preq_level"));
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_07_value_set(v);
        break;
        }
    case 1:
        {
        this->param_11_value_set(v);
        break;
        }
    case 2:
        {
        this->param_08_value_set(v);
        break;
        }
    case 3:
        {
        this->param_09_value_set(v);
        break;
        }
    case 4:
        {
        this->param_16_value_set(v);
        break;
        }
    case 5:
        {
        this->param_17_value_set(v);
        break;
        }
    case 6:
        {
        this->param_18_value_set(v);
        break;
        }
    case 7:
        {
        this->param_19_value_set(v);
        break;
        }
    case 8:
        {
        this->param_05_value_set(v);
        break;
        }
    case 9:
        {
        this->param_10_value_set(v);
        break;
        }
    case 10:
        {
        this->param_01_value_set(v);
        break;
        }
    case 11:
        {
        this->param_02_value_set(v);
        break;
        }
    case 12:
        {
        this->param_03_value_set(v);
        break;
        }
    case 13:
        {
        this->param_04_value_set(v);
        break;
        }
    case 14:
        {
        this->param_06_value_set(v);
        break;
        }
    case 15:
        {
        this->param_12_value_set(v);
        break;
        }
    case 16:
        {
        this->param_13_value_set(v);
        break;
        }
    case 17:
        {
        this->param_14_value_set(v);
        break;
        }
    case 18:
        {
        this->param_15_value_set(v);
        break;
        }
    default:
        {
        index -= 19;

        if (index < this->p_01->getNumParameters())
            this->p_01->setParameterValue(index, v, time);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            this->p_02->setParameterValue(index, v, time);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            this->p_03->setParameterValue(index, v, time);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            this->p_04->setParameterValue(index, v, time);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            this->p_05->setParameterValue(index, v, time);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            this->p_06->setParameterValue(index, v, time);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            this->p_07->setParameterValue(index, v, time);

        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_07_value;
        }
    case 1:
        {
        return this->param_11_value;
        }
    case 2:
        {
        return this->param_08_value;
        }
    case 3:
        {
        return this->param_09_value;
        }
    case 4:
        {
        return this->param_16_value;
        }
    case 5:
        {
        return this->param_17_value;
        }
    case 6:
        {
        return this->param_18_value;
        }
    case 7:
        {
        return this->param_19_value;
        }
    case 8:
        {
        return this->param_05_value;
        }
    case 9:
        {
        return this->param_10_value;
        }
    case 10:
        {
        return this->param_01_value;
        }
    case 11:
        {
        return this->param_02_value;
        }
    case 12:
        {
        return this->param_03_value;
        }
    case 13:
        {
        return this->param_04_value;
        }
    case 14:
        {
        return this->param_06_value;
        }
    case 15:
        {
        return this->param_12_value;
        }
    case 16:
        {
        return this->param_13_value;
        }
    case 17:
        {
        return this->param_14_value;
        }
    case 18:
        {
        return this->param_15_value;
        }
    default:
        {
        index -= 19;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterValue(index);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterValue(index);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->getParameterValue(index);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterValue(index);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterValue(index);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->getParameterValue(index);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            return this->p_07->getParameterValue(index);

        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 19 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "lowcut";
        }
    case 1:
        {
        return "low_cut";
        }
    case 2:
        {
        return "post_level";
        }
    case 3:
        {
        return "preq_level";
        }
    case 4:
        {
        return "r_Feedback";
        }
    case 5:
        {
        return "r_InGain";
        }
    case 6:
        {
        return "lfo1_rate";
        }
    case 7:
        {
        return "r_Damp";
        }
    case 8:
        {
        return "apf_g";
        }
    case 9:
        {
        return "mix";
        }
    case 10:
        {
        return "diff_num";
        }
    case 11:
        {
        return "pre_del";
        }
    case 12:
        {
        return "fb1";
        }
    case 13:
        {
        return "x_fb";
        }
    case 14:
        {
        return "Size";
        }
    case 15:
        {
        return "himid_lev";
        }
    case 16:
        {
        return "himidfq";
        }
    case 17:
        {
        return "high_cut";
        }
    case 18:
        {
        return "lfo1_bw";
        }
    default:
        {
        index -= 19;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterName(index);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterName(index);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->getParameterName(index);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterName(index);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterName(index);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->getParameterName(index);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            return this->p_07->getParameterName(index);

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "lowcut";
        }
    case 1:
        {
        return "low_cut";
        }
    case 2:
        {
        return "post_level";
        }
    case 3:
        {
        return "preq_level";
        }
    case 4:
        {
        return "r_Feedback";
        }
    case 5:
        {
        return "r_InGain";
        }
    case 6:
        {
        return "lfo1_rate";
        }
    case 7:
        {
        return "r_Damp";
        }
    case 8:
        {
        return "apf_g";
        }
    case 9:
        {
        return "mix";
        }
    case 10:
        {
        return "diff_num";
        }
    case 11:
        {
        return "pre_del";
        }
    case 12:
        {
        return "fb1";
        }
    case 13:
        {
        return "x_fb";
        }
    case 14:
        {
        return "Size";
        }
    case 15:
        {
        return "himid_lev";
        }
    case 16:
        {
        return "himidfq";
        }
    case 17:
        {
        return "high_cut";
        }
    case 18:
        {
        return "lfo1_bw";
        }
    default:
        {
        index -= 19;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterId(index);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterId(index);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->getParameterId(index);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->getParameterId(index);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->getParameterId(index);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->getParameterId(index);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            return this->p_07->getParameterId(index);

        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal0[] = {"0", "1"};
            info->enumValues = eVal0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "preq_LowCut";
            info->unit = "On/Off";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 20;
            info->min = 10;
            info->max = 1500;
            info->exponent = 2.25;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "LowCut";
            info->unit = "Hz";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 50;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "post_Level";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -100;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "preq_Level";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 50;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 90;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 6:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.3;
            info->min = 0;
            info->max = 5;
            info->exponent = 0.1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 7:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 20;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 8:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.535;
            info->min = -0.99;
            info->max = 0.99;
            info->exponent = 0.1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 9:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 50;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "full_Mix";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 10:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 4;
            info->min = 1;
            info->max = 4;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 11:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 20;
            info->min = 0;
            info->max = 500;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 12:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.1;
            info->min = 0;
            info->max = 0.9;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 13:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.1;
            info->min = 0;
            info->max = 0.9;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 14:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 60;
            info->min = 0;
            info->max = 100;
            info->exponent = 0.25;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 15:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -100;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "HighMid";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 16:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -100;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "HighMidFreq";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 17:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 8000;
            info->min = 300;
            info->max = 20000;
            info->exponent = 2.25;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "high_cut";
            info->unit = "Hz";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 18:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.3;
            info->min = 0;
            info->max = 2;
            info->exponent = 0.1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        default:
            {
            index -= 19;

            if (index < this->p_01->getNumParameters())
                this->p_01->getParameterInfo(index, info);

            index -= this->p_01->getNumParameters();

            if (index < this->p_02->getNumParameters())
                this->p_02->getParameterInfo(index, info);

            index -= this->p_02->getNumParameters();

            if (index < this->p_03->getNumParameters())
                this->p_03->getParameterInfo(index, info);

            index -= this->p_03->getNumParameters();

            if (index < this->p_04->getNumParameters())
                this->p_04->getParameterInfo(index, info);

            index -= this->p_04->getNumParameters();

            if (index < this->p_05->getNumParameters())
                this->p_05->getParameterInfo(index, info);

            index -= this->p_05->getNumParameters();

            if (index < this->p_06->getNumParameters())
                this->p_06->getParameterInfo(index, info);

            index -= this->p_06->getNumParameters();

            if (index < this->p_07->getNumParameters())
                this->p_07->getParameterInfo(index, info);

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->p_01)
        return 19;

    if (subpatcher == this->p_02)
        return 19 + this->p_01->getNumParameters();

    if (subpatcher == this->p_03)
        return 19 + this->p_01->getNumParameters() + this->p_02->getNumParameters();

    if (subpatcher == this->p_04)
        return 19 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters();

    if (subpatcher == this->p_05)
        return 19 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters();

    if (subpatcher == this->p_06)
        return 19 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters();

    if (subpatcher == this->p_07)
        return 19 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters();

    return 0;
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);

            {
                normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 2);
            }

            return normalizedValue;
        }
        }
    case 18:
        {
        {
            value = (value < 0 ? 0 : (value > 2 ? 2 : value));
            ParameterValue normalizedValue = (value - 0) / (2 - 0);

            {
                if (normalizedValue != 0.0) {
                    normalizedValue = rnbo_exp(
                        rnbo_log((normalizedValue <= 0.0000000001 ? 0.0000000001 : normalizedValue)) * 1. / (number)0.1
                    );
                }
            }

            return normalizedValue;
        }
        }
    case 6:
        {
        {
            value = (value < 0 ? 0 : (value > 5 ? 5 : value));
            ParameterValue normalizedValue = (value - 0) / (5 - 0);

            {
                if (normalizedValue != 0.0) {
                    normalizedValue = rnbo_exp(
                        rnbo_log((normalizedValue <= 0.0000000001 ? 0.0000000001 : normalizedValue)) * 1. / (number)0.1
                    );
                }
            }

            return normalizedValue;
        }
        }
    case 2:
    case 4:
    case 5:
    case 7:
    case 9:
        {
        {
            value = (value < 0 ? 0 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0) / (100 - 0);
            return normalizedValue;
        }
        }
    case 14:
        {
        {
            value = (value < 0 ? 0 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0) / (100 - 0);

            {
                if (normalizedValue != 0.0) {
                    normalizedValue = rnbo_exp(
                        rnbo_log((normalizedValue <= 0.0000000001 ? 0.0000000001 : normalizedValue)) * 1. / (number)0.25
                    );
                }
            }

            return normalizedValue;
        }
        }
    case 11:
        {
        {
            value = (value < 0 ? 0 : (value > 500 ? 500 : value));
            ParameterValue normalizedValue = (value - 0) / (500 - 0);
            return normalizedValue;
        }
        }
    case 12:
    case 13:
        {
        {
            value = (value < 0 ? 0 : (value > 0.9 ? 0.9 : value));
            ParameterValue normalizedValue = (value - 0) / (0.9 - 0);
            return normalizedValue;
        }
        }
    case 10:
        {
        {
            value = (value < 1 ? 1 : (value > 4 ? 4 : value));
            ParameterValue normalizedValue = (value - 1) / (4 - 1);
            return normalizedValue;
        }
        }
    case 1:
        {
        {
            value = (value < 10 ? 10 : (value > 1500 ? 1500 : value));
            ParameterValue normalizedValue = (value - 10) / (1500 - 10);

            {
                if (normalizedValue != 0.0) {
                    normalizedValue = rnbo_exp(
                        rnbo_log((normalizedValue <= 0.0000000001 ? 0.0000000001 : normalizedValue)) * 1. / (number)2.25
                    );
                }
            }

            return normalizedValue;
        }
        }
    case 17:
        {
        {
            value = (value < 300 ? 300 : (value > 20000 ? 20000 : value));
            ParameterValue normalizedValue = (value - 300) / (20000 - 300);

            {
                if (normalizedValue != 0.0) {
                    normalizedValue = rnbo_exp(
                        rnbo_log((normalizedValue <= 0.0000000001 ? 0.0000000001 : normalizedValue)) * 1. / (number)2.25
                    );
                }
            }

            return normalizedValue;
        }
        }
    case 3:
    case 15:
    case 16:
        {
        {
            value = (value < -100 ? -100 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - -100) / (100 - -100);
            return normalizedValue;
        }
        }
    case 8:
        {
        {
            value = (value < -0.99 ? -0.99 : (value > 0.99 ? 0.99 : value));
            ParameterValue normalizedValue = (value - -0.99) / (0.99 - -0.99);

            {
                if (normalizedValue != 0.0) {
                    normalizedValue = rnbo_exp(
                        rnbo_log((normalizedValue <= 0.0000000001 ? 0.0000000001 : normalizedValue)) * 1. / (number)0.1
                    );
                }
            }

            return normalizedValue;
        }
        }
    default:
        {
        index -= 19;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertToNormalizedParameterValue(index, value);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->convertToNormalizedParameterValue(index, value);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->convertToNormalizedParameterValue(index, value);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->convertToNormalizedParameterValue(index, value);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->convertToNormalizedParameterValue(index, value);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->convertToNormalizedParameterValue(index, value);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            return this->p_07->convertToNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 0:
        {
        {
            {
                value = this->applyStepsToNormalizedParameterValue(value, 2);
            }

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 18:
        {
        {
            {
                if (value == 0.0) {
                    return 0;
                } else {
                    return 0 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 0.1) * (2 - 0);
                }
            }
        }
        }
    case 6:
        {
        {
            {
                if (value == 0.0) {
                    return 0;
                } else {
                    return 0 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 0.1) * (5 - 0);
                }
            }
        }
        }
    case 2:
    case 4:
    case 5:
    case 7:
    case 9:
        {
        {
            {
                return 0 + value * (100 - 0);
            }
        }
        }
    case 14:
        {
        {
            {
                if (value == 0.0) {
                    return 0;
                } else {
                    return 0 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 0.25) * (100 - 0);
                }
            }
        }
        }
    case 11:
        {
        {
            {
                return 0 + value * (500 - 0);
            }
        }
        }
    case 12:
    case 13:
        {
        {
            {
                return 0 + value * (0.9 - 0);
            }
        }
        }
    case 10:
        {
        {
            {
                return 1 + value * (4 - 1);
            }
        }
        }
    case 1:
        {
        {
            {
                if (value == 0.0) {
                    return 10;
                } else {
                    return 10 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 2.25) * (1500 - 10);
                }
            }
        }
        }
    case 17:
        {
        {
            {
                if (value == 0.0) {
                    return 300;
                } else {
                    return 300 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 2.25) * (20000 - 300);
                }
            }
        }
        }
    case 3:
    case 15:
    case 16:
        {
        {
            {
                return -100 + value * (100 - -100);
            }
        }
        }
    case 8:
        {
        {
            {
                if (value == 0.0) {
                    return -0.99;
                } else {
                    return -0.99 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 0.1) * (0.99 - -0.99);
                }
            }
        }
        }
    default:
        {
        index -= 19;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertFromNormalizedParameterValue(index, value);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->convertFromNormalizedParameterValue(index, value);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->convertFromNormalizedParameterValue(index, value);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->convertFromNormalizedParameterValue(index, value);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->convertFromNormalizedParameterValue(index, value);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->convertFromNormalizedParameterValue(index, value);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            return this->p_07->convertFromNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_07_value_constrain(value);
        }
    case 1:
        {
        return this->param_11_value_constrain(value);
        }
    case 2:
        {
        return this->param_08_value_constrain(value);
        }
    case 3:
        {
        return this->param_09_value_constrain(value);
        }
    case 4:
        {
        return this->param_16_value_constrain(value);
        }
    case 5:
        {
        return this->param_17_value_constrain(value);
        }
    case 6:
        {
        return this->param_18_value_constrain(value);
        }
    case 7:
        {
        return this->param_19_value_constrain(value);
        }
    case 8:
        {
        return this->param_05_value_constrain(value);
        }
    case 9:
        {
        return this->param_10_value_constrain(value);
        }
    case 10:
        {
        return this->param_01_value_constrain(value);
        }
    case 11:
        {
        return this->param_02_value_constrain(value);
        }
    case 12:
        {
        return this->param_03_value_constrain(value);
        }
    case 13:
        {
        return this->param_04_value_constrain(value);
        }
    case 14:
        {
        return this->param_06_value_constrain(value);
        }
    case 15:
        {
        return this->param_12_value_constrain(value);
        }
    case 16:
        {
        return this->param_13_value_constrain(value);
        }
    case 17:
        {
        return this->param_14_value_constrain(value);
        }
    case 18:
        {
        return this->param_15_value_constrain(value);
        }
    default:
        {
        index -= 19;

        if (index < this->p_01->getNumParameters())
            return this->p_01->constrainParameterValue(index, value);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->constrainParameterValue(index, value);

        index -= this->p_02->getNumParameters();

        if (index < this->p_03->getNumParameters())
            return this->p_03->constrainParameterValue(index, value);

        index -= this->p_03->getNumParameters();

        if (index < this->p_04->getNumParameters())
            return this->p_04->constrainParameterValue(index, value);

        index -= this->p_04->getNumParameters();

        if (index < this->p_05->getNumParameters())
            return this->p_05->constrainParameterValue(index, value);

        index -= this->p_05->getNumParameters();

        if (index < this->p_06->getNumParameters())
            return this->p_06->constrainParameterValue(index, value);

        index -= this->p_06->getNumParameters();

        if (index < this->p_07->getNumParameters())
            return this->p_07->constrainParameterValue(index, value);

        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(value);
    RNBO_UNUSED(hasValue);
    this->updateTime(time);

    switch (index) {
    case -62043057:
        {
        this->linetilde_08_target_bang();
        break;
        }
    }
}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    this->updateTime(time);

    switch (tag) {
    case TAG("valin"):
        {
        if (TAG("number_obj-145") == objectId)
            this->numberobj_15_valin_set(payload);

        if (TAG("number_obj-11") == objectId)
            this->numberobj_16_valin_set(payload);

        if (TAG("toggle_obj-37") == objectId)
            this->toggle_02_valin_set(payload);

        if (TAG("number_obj-87") == objectId)
            this->numberobj_17_valin_set(payload);

        if (TAG("number_obj-68") == objectId)
            this->numberobj_18_valin_set(payload);

        if (TAG("number_obj-136") == objectId)
            this->numberobj_19_valin_set(payload);

        if (TAG("number_obj-139") == objectId)
            this->numberobj_20_valin_set(payload);

        if (TAG("number_obj-24") == objectId)
            this->numberobj_21_valin_set(payload);

        if (TAG("number_obj-103") == objectId)
            this->numberobj_22_valin_set(payload);

        if (TAG("number_obj-105") == objectId)
            this->numberobj_23_valin_set(payload);

        if (TAG("number_obj-6") == objectId)
            this->numberobj_24_valin_set(payload);

        break;
        }
    case TAG("format"):
        {
        if (TAG("number_obj-145") == objectId)
            this->numberobj_15_format_set(payload);

        if (TAG("number_obj-11") == objectId)
            this->numberobj_16_format_set(payload);

        if (TAG("number_obj-87") == objectId)
            this->numberobj_17_format_set(payload);

        if (TAG("number_obj-68") == objectId)
            this->numberobj_18_format_set(payload);

        if (TAG("number_obj-136") == objectId)
            this->numberobj_19_format_set(payload);

        if (TAG("number_obj-139") == objectId)
            this->numberobj_20_format_set(payload);

        if (TAG("number_obj-24") == objectId)
            this->numberobj_21_format_set(payload);

        if (TAG("number_obj-103") == objectId)
            this->numberobj_22_format_set(payload);

        if (TAG("number_obj-105") == objectId)
            this->numberobj_23_format_set(payload);

        if (TAG("number_obj-6") == objectId)
            this->numberobj_24_format_set(payload);

        break;
        }
    }

    this->p_01->processNumMessage(tag, objectId, time, payload);
    this->p_02->processNumMessage(tag, objectId, time, payload);
    this->p_03->processNumMessage(tag, objectId, time, payload);
    this->p_04->processNumMessage(tag, objectId, time, payload);
    this->p_05->processNumMessage(tag, objectId, time, payload);
    this->p_06->processNumMessage(tag, objectId, time, payload);
    this->p_07->processNumMessage(tag, objectId, time, payload);
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_01->processListMessage(tag, objectId, time, payload);
    this->p_02->processListMessage(tag, objectId, time, payload);
    this->p_03->processListMessage(tag, objectId, time, payload);
    this->p_04->processListMessage(tag, objectId, time, payload);
    this->p_05->processListMessage(tag, objectId, time, payload);
    this->p_06->processListMessage(tag, objectId, time, payload);
    this->p_07->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_01->processBangMessage(tag, objectId, time);
    this->p_02->processBangMessage(tag, objectId, time);
    this->p_03->processBangMessage(tag, objectId, time);
    this->p_04->processBangMessage(tag, objectId, time);
    this->p_05->processBangMessage(tag, objectId, time);
    this->p_06->processBangMessage(tag, objectId, time);
    this->p_07->processBangMessage(tag, objectId, time);
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("valout"):
        {
        return "valout";
        }
    case TAG("number_obj-145"):
        {
        return "number_obj-145";
        }
    case TAG("setup"):
        {
        return "setup";
        }
    case TAG("number_obj-11"):
        {
        return "number_obj-11";
        }
    case TAG("toggle_obj-37"):
        {
        return "toggle_obj-37";
        }
    case TAG("number_obj-87"):
        {
        return "number_obj-87";
        }
    case TAG("number_obj-68"):
        {
        return "number_obj-68";
        }
    case TAG("number_obj-136"):
        {
        return "number_obj-136";
        }
    case TAG("number_obj-139"):
        {
        return "number_obj-139";
        }
    case TAG("number_obj-24"):
        {
        return "number_obj-24";
        }
    case TAG("number_obj-103"):
        {
        return "number_obj-103";
        }
    case TAG("number_obj-105"):
        {
        return "number_obj-105";
        }
    case TAG("number_obj-6"):
        {
        return "number_obj-6";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    case TAG("format"):
        {
        return "format";
        }
    }

    auto subpatchResult_0 = this->p_01->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    auto subpatchResult_1 = this->p_02->resolveTag(tag);

    if (subpatchResult_1)
        return subpatchResult_1;

    auto subpatchResult_2 = this->p_03->resolveTag(tag);

    if (subpatchResult_2)
        return subpatchResult_2;

    auto subpatchResult_3 = this->p_04->resolveTag(tag);

    if (subpatchResult_3)
        return subpatchResult_3;

    auto subpatchResult_4 = this->p_05->resolveTag(tag);

    if (subpatchResult_4)
        return subpatchResult_4;

    auto subpatchResult_5 = this->p_06->resolveTag(tag);

    if (subpatchResult_5)
        return subpatchResult_5;

    auto subpatchResult_6 = this->p_07->resolveTag(tag);

    if (subpatchResult_6)
        return subpatchResult_6;

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(0, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }

    this->toggle_02_value_number_set(v);
}

void param_11_value_set(number v) {
    v = this->param_11_value_constrain(v);
    this->param_11_value = v;
    this->sendParameter(1, false);

    if (this->param_11_value != this->param_11_lastValue) {
        this->getEngine()->presetTouched();
        this->param_11_lastValue = this->param_11_value;
    }

    this->numberobj_21_value_set(v);
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(2, false);

    if (this->param_08_value != this->param_08_lastValue) {
        this->getEngine()->presetTouched();
        this->param_08_lastValue = this->param_08_value;
    }

    this->numberobj_17_value_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(3, false);

    if (this->param_09_value != this->param_09_lastValue) {
        this->getEngine()->presetTouched();
        this->param_09_lastValue = this->param_09_value;
    }

    this->numberobj_18_value_set(v);
}

void param_16_value_set(number v) {
    v = this->param_16_value_constrain(v);
    this->param_16_value = v;
    this->sendParameter(4, false);

    if (this->param_16_value != this->param_16_lastValue) {
        this->getEngine()->presetTouched();
        this->param_16_lastValue = this->param_16_value;
    }

    {
        list converted = {v};
        this->scale_06_input_set(converted);
    }
}

void param_17_value_set(number v) {
    v = this->param_17_value_constrain(v);
    this->param_17_value = v;
    this->sendParameter(5, false);

    if (this->param_17_value != this->param_17_lastValue) {
        this->getEngine()->presetTouched();
        this->param_17_lastValue = this->param_17_value;
    }

    {
        list converted = {v};
        this->scale_07_input_set(converted);
    }
}

void param_18_value_set(number v) {
    v = this->param_18_value_constrain(v);
    this->param_18_value = v;
    this->sendParameter(6, false);

    if (this->param_18_value != this->param_18_lastValue) {
        this->getEngine()->presetTouched();
        this->param_18_lastValue = this->param_18_value;
    }

    this->gen_01_lfo1_rate_set(v);
    this->gen_02_lfo1_rate_set(v);
}

void param_19_value_set(number v) {
    v = this->param_19_value_constrain(v);
    this->param_19_value = v;
    this->sendParameter(7, false);

    if (this->param_19_value != this->param_19_lastValue) {
        this->getEngine()->presetTouched();
        this->param_19_lastValue = this->param_19_value;
    }

    {
        list converted = {v};
        this->scale_08_input_set(converted);
    }
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(8, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->gen_02_apf_g_set(v);
}

void param_10_value_set(number v) {
    v = this->param_10_value_constrain(v);
    this->param_10_value = v;
    this->sendParameter(9, false);

    if (this->param_10_value != this->param_10_lastValue) {
        this->getEngine()->presetTouched();
        this->param_10_lastValue = this->param_10_value;
    }

    this->numberobj_20_value_set(v);
}

void param_01_value_set(number v) {
    v = this->param_01_value_constrain(v);
    this->param_01_value = v;
    this->sendParameter(10, false);

    if (this->param_01_value != this->param_01_lastValue) {
        this->getEngine()->presetTouched();
        this->param_01_lastValue = this->param_01_value;
    }

    this->gen_02_diff_num_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(11, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    this->gen_02_pre_del_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(12, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->gen_02_fb1_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(13, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->gen_02_x_fb_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(14, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }

    {
        list converted = {v};
        this->scale_05_input_set(converted);
    }
}

void param_12_value_set(number v) {
    v = this->param_12_value_constrain(v);
    this->param_12_value = v;
    this->sendParameter(15, false);

    if (this->param_12_value != this->param_12_lastValue) {
        this->getEngine()->presetTouched();
        this->param_12_lastValue = this->param_12_value;
    }

    this->numberobj_22_value_set(v);
}

void param_13_value_set(number v) {
    v = this->param_13_value_constrain(v);
    this->param_13_value = v;
    this->sendParameter(16, false);

    if (this->param_13_value != this->param_13_lastValue) {
        this->getEngine()->presetTouched();
        this->param_13_lastValue = this->param_13_value;
    }

    this->numberobj_23_value_set(v);
}

void param_14_value_set(number v) {
    v = this->param_14_value_constrain(v);
    this->param_14_value = v;
    this->sendParameter(17, false);

    if (this->param_14_value != this->param_14_lastValue) {
        this->getEngine()->presetTouched();
        this->param_14_lastValue = this->param_14_value;
    }

    this->numberobj_24_value_set(v);
}

void param_15_value_set(number v) {
    v = this->param_15_value_constrain(v);
    this->param_15_value = v;
    this->sendParameter(18, false);

    if (this->param_15_value != this->param_15_lastValue) {
        this->getEngine()->presetTouched();
        this->param_15_lastValue = this->param_15_value;
    }

    this->gen_01_lfo1_bw_set(v);
    this->gen_02_lfo1_bw_set(v);
}

void numberobj_15_valin_set(number v) {
    this->numberobj_15_value_set(v);
}

void numberobj_15_format_set(number v) {
    this->numberobj_15_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_16_valin_set(number v) {
    this->numberobj_16_value_set(v);
}

void numberobj_16_format_set(number v) {
    this->numberobj_16_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void toggle_02_valin_set(number v) {
    this->toggle_02_value_number_set(v);
}

void numberobj_17_valin_set(number v) {
    this->numberobj_17_value_set(v);
}

void numberobj_17_format_set(number v) {
    this->numberobj_17_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_18_valin_set(number v) {
    this->numberobj_18_value_set(v);
}

void numberobj_18_format_set(number v) {
    this->numberobj_18_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_19_valin_set(number v) {
    this->numberobj_19_value_set(v);
}

void numberobj_19_format_set(number v) {
    this->numberobj_19_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_20_valin_set(number v) {
    this->numberobj_20_value_set(v);
}

void numberobj_20_format_set(number v) {
    this->numberobj_20_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_21_valin_set(number v) {
    this->numberobj_21_value_set(v);
}

void numberobj_21_format_set(number v) {
    this->numberobj_21_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_22_valin_set(number v) {
    this->numberobj_22_value_set(v);
}

void numberobj_22_format_set(number v) {
    this->numberobj_22_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_23_valin_set(number v) {
    this->numberobj_23_value_set(v);
}

void numberobj_23_format_set(number v) {
    this->numberobj_23_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_24_valin_set(number v) {
    this->numberobj_24_value_set(v);
}

void numberobj_24_format_set(number v) {
    this->numberobj_24_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void linetilde_08_target_bang() {}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 2;
}

Index getNumOutputChannels() const {
    return 2;
}

void allocateDataRefs() {
    this->p_01->allocateDataRefs();
    this->p_02->allocateDataRefs();
    this->p_03->allocateDataRefs();
    this->p_04->allocateDataRefs();
    this->p_05->allocateDataRefs();
    this->p_06->allocateDataRefs();
    this->p_07->allocateDataRefs();
    this->gen_01_cycle_6_buffer->requestSize(16384, 1);
    this->gen_01_cycle_6_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_11_buffer->requestSize(16384, 1);
    this->gen_01_cycle_11_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_16_buffer->requestSize(16384, 1);
    this->gen_01_cycle_16_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_21_buffer->requestSize(16384, 1);
    this->gen_01_cycle_21_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_26_buffer->requestSize(16384, 1);
    this->gen_01_cycle_26_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_31_buffer->requestSize(16384, 1);
    this->gen_01_cycle_31_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_36_buffer->requestSize(16384, 1);
    this->gen_01_cycle_36_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_41_buffer->requestSize(16384, 1);
    this->gen_01_cycle_41_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_46_buffer->requestSize(16384, 1);
    this->gen_01_cycle_46_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_54_buffer->requestSize(16384, 1);
    this->gen_01_cycle_54_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_43_buffer->requestSize(16384, 1);
    this->gen_02_cycle_43_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_50_buffer->requestSize(16384, 1);
    this->gen_02_cycle_50_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_63_buffer->requestSize(16384, 1);
    this->gen_02_cycle_63_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_118_buffer->requestSize(16384, 1);
    this->gen_02_cycle_118_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_135_buffer->requestSize(16384, 1);
    this->gen_02_cycle_135_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_144_buffer->requestSize(16384, 1);
    this->gen_02_cycle_144_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_161_buffer->requestSize(16384, 1);
    this->gen_02_cycle_161_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_186_buffer->requestSize(16384, 1);
    this->gen_02_cycle_186_buffer->setSampleRate(this->sr);
    this->gen_01_delay_1_buffer = this->gen_01_delay_1_buffer->allocateIfNeeded();

    if (this->gen_01_delay_1_bufferobj->hasRequestedSize()) {
        if (this->gen_01_delay_1_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_delay_1_bufferobj);

        this->getEngine()->sendDataRefUpdated(0);
    }

    this->gen_01_delay_2_buffer = this->gen_01_delay_2_buffer->allocateIfNeeded();

    if (this->gen_01_delay_2_bufferobj->hasRequestedSize()) {
        if (this->gen_01_delay_2_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_delay_2_bufferobj);

        this->getEngine()->sendDataRefUpdated(1);
    }

    this->gen_01_delay_5_buffer = this->gen_01_delay_5_buffer->allocateIfNeeded();

    if (this->gen_01_delay_5_bufferobj->hasRequestedSize()) {
        if (this->gen_01_delay_5_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_delay_5_bufferobj);

        this->getEngine()->sendDataRefUpdated(2);
    }

    this->gen_01_DL1_buffer = this->gen_01_DL1_buffer->allocateIfNeeded();

    if (this->gen_01_DL1_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL1_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL1_bufferobj);

        this->getEngine()->sendDataRefUpdated(3);
    }

    this->gen_01_DL2_buffer = this->gen_01_DL2_buffer->allocateIfNeeded();

    if (this->gen_01_DL2_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL2_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL2_bufferobj);

        this->getEngine()->sendDataRefUpdated(4);
    }

    this->gen_01_DL3_buffer = this->gen_01_DL3_buffer->allocateIfNeeded();

    if (this->gen_01_DL3_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL3_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL3_bufferobj);

        this->getEngine()->sendDataRefUpdated(5);
    }

    this->gen_01_DL4_buffer = this->gen_01_DL4_buffer->allocateIfNeeded();

    if (this->gen_01_DL4_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL4_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL4_bufferobj);

        this->getEngine()->sendDataRefUpdated(6);
    }

    this->gen_01_DL5_buffer = this->gen_01_DL5_buffer->allocateIfNeeded();

    if (this->gen_01_DL5_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL5_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL5_bufferobj);

        this->getEngine()->sendDataRefUpdated(7);
    }

    this->gen_01_DL6_buffer = this->gen_01_DL6_buffer->allocateIfNeeded();

    if (this->gen_01_DL6_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL6_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL6_bufferobj);

        this->getEngine()->sendDataRefUpdated(8);
    }

    this->gen_01_DL7_buffer = this->gen_01_DL7_buffer->allocateIfNeeded();

    if (this->gen_01_DL7_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL7_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL7_bufferobj);

        this->getEngine()->sendDataRefUpdated(9);
    }

    this->gen_01_DL8_buffer = this->gen_01_DL8_buffer->allocateIfNeeded();

    if (this->gen_01_DL8_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL8_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL8_bufferobj);

        this->getEngine()->sendDataRefUpdated(10);
    }

    this->gen_01_DL9_buffer = this->gen_01_DL9_buffer->allocateIfNeeded();

    if (this->gen_01_DL9_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL9_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL9_bufferobj);

        this->getEngine()->sendDataRefUpdated(11);
    }

    this->gen_01_DL10_buffer = this->gen_01_DL10_buffer->allocateIfNeeded();

    if (this->gen_01_DL10_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL10_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL10_bufferobj);

        this->getEngine()->sendDataRefUpdated(12);
    }

    this->gen_01_DL11_buffer = this->gen_01_DL11_buffer->allocateIfNeeded();

    if (this->gen_01_DL11_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL11_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL11_bufferobj);

        this->getEngine()->sendDataRefUpdated(13);
    }

    this->gen_01_DL12_buffer = this->gen_01_DL12_buffer->allocateIfNeeded();

    if (this->gen_01_DL12_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL12_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL12_bufferobj);

        this->getEngine()->sendDataRefUpdated(14);
    }

    this->gen_01_DL13_buffer = this->gen_01_DL13_buffer->allocateIfNeeded();

    if (this->gen_01_DL13_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL13_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL13_bufferobj);

        this->getEngine()->sendDataRefUpdated(15);
    }

    this->gen_01_delay_9_buffer = this->gen_01_delay_9_buffer->allocateIfNeeded();

    if (this->gen_01_delay_9_bufferobj->hasRequestedSize()) {
        if (this->gen_01_delay_9_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_delay_9_bufferobj);

        this->getEngine()->sendDataRefUpdated(16);
    }

    this->gen_01_dlL1_buffer = this->gen_01_dlL1_buffer->allocateIfNeeded();

    if (this->gen_01_dlL1_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL1_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL1_bufferobj);

        this->getEngine()->sendDataRefUpdated(17);
    }

    this->gen_01_dlL2_buffer = this->gen_01_dlL2_buffer->allocateIfNeeded();

    if (this->gen_01_dlL2_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL2_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL2_bufferobj);

        this->getEngine()->sendDataRefUpdated(18);
    }

    this->gen_01_dlL3_buffer = this->gen_01_dlL3_buffer->allocateIfNeeded();

    if (this->gen_01_dlL3_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL3_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL3_bufferobj);

        this->getEngine()->sendDataRefUpdated(19);
    }

    this->gen_01_dlL4_buffer = this->gen_01_dlL4_buffer->allocateIfNeeded();

    if (this->gen_01_dlL4_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL4_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL4_bufferobj);

        this->getEngine()->sendDataRefUpdated(20);
    }

    this->gen_01_dlL5_buffer = this->gen_01_dlL5_buffer->allocateIfNeeded();

    if (this->gen_01_dlL5_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL5_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL5_bufferobj);

        this->getEngine()->sendDataRefUpdated(21);
    }

    this->gen_01_dlL6_buffer = this->gen_01_dlL6_buffer->allocateIfNeeded();

    if (this->gen_01_dlL6_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL6_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL6_bufferobj);

        this->getEngine()->sendDataRefUpdated(22);
    }

    this->gen_01_dlL7_buffer = this->gen_01_dlL7_buffer->allocateIfNeeded();

    if (this->gen_01_dlL7_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL7_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL7_bufferobj);

        this->getEngine()->sendDataRefUpdated(23);
    }

    this->gen_01_dlL8_buffer = this->gen_01_dlL8_buffer->allocateIfNeeded();

    if (this->gen_01_dlL8_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL8_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL8_bufferobj);

        this->getEngine()->sendDataRefUpdated(24);
    }

    this->gen_01_dlL9_buffer = this->gen_01_dlL9_buffer->allocateIfNeeded();

    if (this->gen_01_dlL9_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL9_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL9_bufferobj);

        this->getEngine()->sendDataRefUpdated(25);
    }

    this->gen_01_dlL10_buffer = this->gen_01_dlL10_buffer->allocateIfNeeded();

    if (this->gen_01_dlL10_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL10_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL10_bufferobj);

        this->getEngine()->sendDataRefUpdated(26);
    }

    this->gen_01_dlL11_buffer = this->gen_01_dlL11_buffer->allocateIfNeeded();

    if (this->gen_01_dlL11_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL11_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL11_bufferobj);

        this->getEngine()->sendDataRefUpdated(27);
    }

    this->gen_01_dlL12_buffer = this->gen_01_dlL12_buffer->allocateIfNeeded();

    if (this->gen_01_dlL12_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL12_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL12_bufferobj);

        this->getEngine()->sendDataRefUpdated(28);
    }

    this->gen_01_dlL13_buffer = this->gen_01_dlL13_buffer->allocateIfNeeded();

    if (this->gen_01_dlL13_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL13_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL13_bufferobj);

        this->getEngine()->sendDataRefUpdated(29);
    }

    this->gen_01_cycle_6_buffer = this->gen_01_cycle_6_buffer->allocateIfNeeded();
    this->gen_01_cycle_11_buffer = this->gen_01_cycle_11_buffer->allocateIfNeeded();
    this->gen_01_cycle_16_buffer = this->gen_01_cycle_16_buffer->allocateIfNeeded();
    this->gen_01_cycle_21_buffer = this->gen_01_cycle_21_buffer->allocateIfNeeded();
    this->gen_01_cycle_26_buffer = this->gen_01_cycle_26_buffer->allocateIfNeeded();
    this->gen_01_cycle_31_buffer = this->gen_01_cycle_31_buffer->allocateIfNeeded();
    this->gen_01_cycle_36_buffer = this->gen_01_cycle_36_buffer->allocateIfNeeded();
    this->gen_01_cycle_41_buffer = this->gen_01_cycle_41_buffer->allocateIfNeeded();
    this->gen_01_cycle_46_buffer = this->gen_01_cycle_46_buffer->allocateIfNeeded();
    this->gen_01_cycle_54_buffer = this->gen_01_cycle_54_buffer->allocateIfNeeded();
    this->gen_02_cycle_43_buffer = this->gen_02_cycle_43_buffer->allocateIfNeeded();
    this->gen_02_cycle_50_buffer = this->gen_02_cycle_50_buffer->allocateIfNeeded();
    this->gen_02_cycle_63_buffer = this->gen_02_cycle_63_buffer->allocateIfNeeded();
    this->gen_02_cycle_118_buffer = this->gen_02_cycle_118_buffer->allocateIfNeeded();
    this->gen_02_cycle_135_buffer = this->gen_02_cycle_135_buffer->allocateIfNeeded();
    this->gen_02_cycle_144_buffer = this->gen_02_cycle_144_buffer->allocateIfNeeded();
    this->gen_02_cycle_161_buffer = this->gen_02_cycle_161_buffer->allocateIfNeeded();
    this->gen_02_cycle_186_buffer = this->gen_02_cycle_186_buffer->allocateIfNeeded();

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(30);
    }

    this->gen_02_delay_1_buffer = this->gen_02_delay_1_buffer->allocateIfNeeded();

    if (this->gen_02_delay_1_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_1_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_1_bufferobj);

        this->getEngine()->sendDataRefUpdated(31);
    }

    this->gen_02_delay_2_buffer = this->gen_02_delay_2_buffer->allocateIfNeeded();

    if (this->gen_02_delay_2_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_2_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_2_bufferobj);

        this->getEngine()->sendDataRefUpdated(32);
    }

    this->gen_02_delay_3_buffer = this->gen_02_delay_3_buffer->allocateIfNeeded();

    if (this->gen_02_delay_3_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_3_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_3_bufferobj);

        this->getEngine()->sendDataRefUpdated(33);
    }

    this->gen_02_delay_4_buffer = this->gen_02_delay_4_buffer->allocateIfNeeded();

    if (this->gen_02_delay_4_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_4_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_4_bufferobj);

        this->getEngine()->sendDataRefUpdated(34);
    }

    this->gen_02_delay_5_buffer = this->gen_02_delay_5_buffer->allocateIfNeeded();

    if (this->gen_02_delay_5_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_5_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_5_bufferobj);

        this->getEngine()->sendDataRefUpdated(35);
    }

    this->gen_02_delay_6_buffer = this->gen_02_delay_6_buffer->allocateIfNeeded();

    if (this->gen_02_delay_6_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_6_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_6_bufferobj);

        this->getEngine()->sendDataRefUpdated(36);
    }

    this->gen_02_delay_7_buffer = this->gen_02_delay_7_buffer->allocateIfNeeded();

    if (this->gen_02_delay_7_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_7_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_7_bufferobj);

        this->getEngine()->sendDataRefUpdated(37);
    }

    this->gen_02_delay_8_buffer = this->gen_02_delay_8_buffer->allocateIfNeeded();

    if (this->gen_02_delay_8_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_8_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_8_bufferobj);

        this->getEngine()->sendDataRefUpdated(38);
    }

    this->gen_02_delay_9_buffer = this->gen_02_delay_9_buffer->allocateIfNeeded();

    if (this->gen_02_delay_9_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_9_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_9_bufferobj);

        this->getEngine()->sendDataRefUpdated(39);
    }

    this->gen_02_delay_10_buffer = this->gen_02_delay_10_buffer->allocateIfNeeded();

    if (this->gen_02_delay_10_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_10_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_10_bufferobj);

        this->getEngine()->sendDataRefUpdated(40);
    }

    this->gen_02_delay_11_buffer = this->gen_02_delay_11_buffer->allocateIfNeeded();

    if (this->gen_02_delay_11_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_11_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_11_bufferobj);

        this->getEngine()->sendDataRefUpdated(41);
    }

    this->gen_02_delay_12_buffer = this->gen_02_delay_12_buffer->allocateIfNeeded();

    if (this->gen_02_delay_12_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_12_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_12_bufferobj);

        this->getEngine()->sendDataRefUpdated(42);
    }

    this->gen_02_delay_13_buffer = this->gen_02_delay_13_buffer->allocateIfNeeded();

    if (this->gen_02_delay_13_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_13_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_13_bufferobj);

        this->getEngine()->sendDataRefUpdated(43);
    }

    this->gen_02_delay_14_buffer = this->gen_02_delay_14_buffer->allocateIfNeeded();

    if (this->gen_02_delay_14_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_14_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_14_bufferobj);

        this->getEngine()->sendDataRefUpdated(44);
    }

    this->gen_02_delay_15_buffer = this->gen_02_delay_15_buffer->allocateIfNeeded();

    if (this->gen_02_delay_15_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_15_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_15_bufferobj);

        this->getEngine()->sendDataRefUpdated(45);
    }

    this->gen_02_delay_17_buffer = this->gen_02_delay_17_buffer->allocateIfNeeded();

    if (this->gen_02_delay_17_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_17_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_17_bufferobj);

        this->getEngine()->sendDataRefUpdated(46);
    }

    this->gen_02_delay_18_buffer = this->gen_02_delay_18_buffer->allocateIfNeeded();

    if (this->gen_02_delay_18_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_18_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_18_bufferobj);

        this->getEngine()->sendDataRefUpdated(47);
    }

    this->gen_02_delay_19_buffer = this->gen_02_delay_19_buffer->allocateIfNeeded();

    if (this->gen_02_delay_19_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_19_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_19_bufferobj);

        this->getEngine()->sendDataRefUpdated(48);
    }

    this->gen_02_delay_20_buffer = this->gen_02_delay_20_buffer->allocateIfNeeded();

    if (this->gen_02_delay_20_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_20_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_20_bufferobj);

        this->getEngine()->sendDataRefUpdated(49);
    }
}

void initializeObjects() {
    this->numberobj_15_init();
    this->numberobj_16_init();
    this->gen_01_delay_1_init();
    this->gen_01_delay_2_init();
    this->gen_01_history_3_init();
    this->gen_01_history_4_init();
    this->gen_01_delay_5_init();
    this->gen_01_history_6_init();
    this->gen_01_DL1_init();
    this->gen_01_DL2_init();
    this->gen_01_DL3_init();
    this->gen_01_DL4_init();
    this->gen_01_DL5_init();
    this->gen_01_DL6_init();
    this->gen_01_DL7_init();
    this->gen_01_DL8_init();
    this->gen_01_DL9_init();
    this->gen_01_DL10_init();
    this->gen_01_DL11_init();
    this->gen_01_DL12_init();
    this->gen_01_DL13_init();
    this->gen_01_feedback_init();
    this->gen_01_filterOutput_init();
    this->gen_01_history_7_init();
    this->gen_01_history_8_init();
    this->gen_01_delay_9_init();
    this->gen_01_history_10_init();
    this->gen_01_dlL1_init();
    this->gen_01_dlL2_init();
    this->gen_01_dlL3_init();
    this->gen_01_dlL4_init();
    this->gen_01_dlL5_init();
    this->gen_01_dlL6_init();
    this->gen_01_dlL7_init();
    this->gen_01_dlL8_init();
    this->gen_01_dlL9_init();
    this->gen_01_dlL10_init();
    this->gen_01_dlL11_init();
    this->gen_01_dlL12_init();
    this->gen_01_dlL13_init();
    this->gen_01_feedbackL_init();
    this->gen_01_filterOutputL_init();
    this->gen_01_history_11_init();
    this->gen_01_history_12_init();
    this->gen_01_noise_78_init();
    this->gen_01_noise_84_init();
    this->gen_01_noise_90_init();
    this->gen_01_noise_96_init();
    this->gen_01_noise_238_init();
    this->gen_01_noise_244_init();
    this->gen_01_noise_250_init();
    this->gen_01_noise_256_init();
    this->gen_02_delay_1_init();
    this->gen_02_delay_2_init();
    this->gen_02_delay_3_init();
    this->gen_02_delay_4_init();
    this->gen_02_delay_5_init();
    this->gen_02_delay_6_init();
    this->gen_02_delay_7_init();
    this->gen_02_delay_8_init();
    this->gen_02_delay_9_init();
    this->gen_02_delay_10_init();
    this->gen_02_delay_11_init();
    this->gen_02_delay_12_init();
    this->gen_02_delay_13_init();
    this->gen_02_delay_14_init();
    this->gen_02_delay_15_init();
    this->gen_02_history_16_init();
    this->gen_02_delay_17_init();
    this->gen_02_delay_18_init();
    this->gen_02_delay_19_init();
    this->gen_02_delay_20_init();
    this->gen_02_history_21_init();
    this->gen_02_history_22_init();
    this->gen_02_history_23_init();
    this->gen_02_history_24_init();
    this->gen_02_history_25_init();
    this->numberobj_17_init();
    this->numberobj_18_init();
    this->numberobj_19_init();
    this->numberobj_20_init();
    this->numberobj_21_init();
    this->numberobj_22_init();
    this->numberobj_23_init();
    this->numberobj_24_init();
    this->p_01->initializeObjects();
    this->p_02->initializeObjects();
    this->p_03->initializeObjects();
    this->p_04->initializeObjects();
    this->p_05->initializeObjects();
    this->p_06->initializeObjects();
    this->p_07->initializeObjects();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());
    this->p_01->startup();
    this->p_02->startup();
    this->p_03->startup();
    this->p_04->startup();
    this->p_05->startup();
    this->p_06->startup();
    this->p_07->startup();

    {
        this->scheduleParamInit(0, 1);
    }

    {
        this->scheduleParamInit(1, 1);
    }

    {
        this->scheduleParamInit(2, 9);
    }

    {
        this->scheduleParamInit(3, 9);
    }

    {
        this->scheduleParamInit(4, 0);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    {
        this->scheduleParamInit(6, 0);
    }

    {
        this->scheduleParamInit(7, 0);
    }

    {
        this->scheduleParamInit(8, 0);
    }

    {
        this->scheduleParamInit(9, 6);
    }

    {
        this->scheduleParamInit(10, 0);
    }

    {
        this->scheduleParamInit(11, 0);
    }

    {
        this->scheduleParamInit(12, 0);
    }

    {
        this->scheduleParamInit(13, 0);
    }

    {
        this->scheduleParamInit(14, 0);
    }

    {
        this->scheduleParamInit(15, 6);
    }

    {
        this->scheduleParamInit(16, 5);
    }

    {
        this->scheduleParamInit(17, 7);
    }

    {
        this->scheduleParamInit(18, 0);
    }

    this->processParamInitEvents();
}

number param_07_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep;
    }

    return v;
}

void p_07_in3_number_set(number v) {
    this->p_07->updateTime(this->_currentTime);
    this->p_07->eventinlet_07_out1_number_set(v);
}

void toggle_02_output_set(number v) {
    this->p_07_in3_number_set(v);
}

void toggle_02_value_number_set(number v) {
    this->toggle_02_value_number_setter(v);
    v = this->toggle_02_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-37"), v, this->_currentTime);
    this->toggle_02_output_set(v);
}

number param_11_value_constrain(number v) const {
    v = (v > 1500 ? 1500 : (v < 10 ? 10 : v));
    return v;
}

void p_03_in3_number_set(number v) {
    this->p_03->updateTime(this->_currentTime);
    this->p_03->eventinlet_02_out1_number_set(v);
}

void numberobj_21_output_set(number v) {
    this->p_03_in3_number_set(v);
}

void numberobj_21_value_set(number v) {
    this->numberobj_21_value_setter(v);
    v = this->numberobj_21_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 10) {
        localvalue = 10;
    }

    if ((bool)(true) && localvalue > 1500) {
        localvalue = 1500;
    }

    if (this->numberobj_21_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-24"), localvalue, this->_currentTime);
    this->numberobj_21_output_set(localvalue);
}

number param_08_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void p_02_in3_number_set(number v) {
    this->p_02->updateTime(this->_currentTime);
    this->p_02->eventinlet_01_out1_number_set(v);
}

void numberobj_17_output_set(number v) {
    this->p_02_in3_number_set(v);
}

void numberobj_17_value_set(number v) {
    this->numberobj_17_value_setter(v);
    v = this->numberobj_17_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_17_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-87"), localvalue, this->_currentTime);
    this->numberobj_17_output_set(localvalue);
}

number param_09_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < -100 ? -100 : v));
    return v;
}

void p_06_in3_number_set(number v) {
    this->p_06->updateTime(this->_currentTime);
    this->p_06->eventinlet_06_out1_number_set(v);
}

void numberobj_18_output_set(number v) {
    this->p_06_in3_number_set(v);
}

void numberobj_18_value_set(number v) {
    this->numberobj_18_value_setter(v);
    v = this->numberobj_18_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_18_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-68"), localvalue, this->_currentTime);
    this->numberobj_18_output_set(localvalue);
}

number param_16_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_fbc_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 0.99)
        v = 0.99;

    return v;
}

void gen_01_fbc_set(number v) {
    v = this->gen_01_fbc_constrain(v);
    this->gen_01_fbc = v;
}

void scale_06_out_set(const list& v) {
    this->scale_06_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gen_01_fbc_set(converted);
    }
}

void scale_06_input_set(const list& v) {
    this->scale_06_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_06_inlow,
            this->scale_06_inhigh,
            this->scale_06_outlow,
            this->scale_06_outhigh,
            this->scale_06_power
        ));
    }

    this->scale_06_out_set(tmp);
}

number param_17_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_InGain_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_InGain_set(number v) {
    v = this->gen_01_InGain_constrain(v);
    this->gen_01_InGain = v;
}

void scale_07_out_set(const list& v) {
    this->scale_07_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gen_01_InGain_set(converted);
    }
}

void scale_07_input_set(const list& v) {
    this->scale_07_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_07_inlow,
            this->scale_07_inhigh,
            this->scale_07_outlow,
            this->scale_07_outhigh,
            this->scale_07_power
        ));
    }

    this->scale_07_out_set(tmp);
}

number param_18_value_constrain(number v) const {
    v = (v > 5 ? 5 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_lfo1_rate_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 10)
        v = 10;

    return v;
}

void gen_01_lfo1_rate_set(number v) {
    v = this->gen_01_lfo1_rate_constrain(v);
    this->gen_01_lfo1_rate = v;
}

number gen_02_lfo1_rate_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 10)
        v = 10;

    return v;
}

void gen_02_lfo1_rate_set(number v) {
    v = this->gen_02_lfo1_rate_constrain(v);
    this->gen_02_lfo1_rate = v;
}

number param_19_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_lpf_constrain(number v) const {
    if (v < 200)
        v = 200;

    if (v > 12000)
        v = 12000;

    return v;
}

void gen_01_lpf_set(number v) {
    v = this->gen_01_lpf_constrain(v);
    this->gen_01_lpf = v;
}

number gen_02_lpf_constrain(number v) const {
    if (v < 200)
        v = 200;

    if (v > 12000)
        v = 12000;

    return v;
}

void gen_02_lpf_set(number v) {
    v = this->gen_02_lpf_constrain(v);
    this->gen_02_lpf = v;
}

void scale_08_out_set(const list& v) {
    this->scale_08_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gen_01_lpf_set(converted);
    }

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gen_02_lpf_set(converted);
    }
}

void scale_08_input_set(const list& v) {
    this->scale_08_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_08_inlow,
            this->scale_08_inhigh,
            this->scale_08_outlow,
            this->scale_08_outhigh,
            this->scale_08_power
        ));
    }

    this->scale_08_out_set(tmp);
}

number param_05_value_constrain(number v) const {
    v = (v > 0.99 ? 0.99 : (v < -0.99 ? -0.99 : v));
    return v;
}

number gen_02_apf_g_constrain(number v) const {
    if (v < -1)
        v = -1;

    if (v > 1)
        v = 1;

    return v;
}

void gen_02_apf_g_set(number v) {
    v = this->gen_02_apf_g_constrain(v);
    this->gen_02_apf_g = v;
}

number param_10_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void linetilde_08_time_set(number v) {
    this->linetilde_08_time = v;
}

void linetilde_08_segments_set(const list& v) {
    this->linetilde_08_segments = jsCreateListCopy(v);

    if ((bool)(v->length)) {
        if (v->length == 1 && this->linetilde_08_time == 0) {
            this->linetilde_08_activeRamps->length = 0;
            this->linetilde_08_currentValue = v[0];
        } else {
            auto currentTime = this->currentsampletime();
            number lastRampValue = this->linetilde_08_currentValue;
            number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;

            for (Index i = 0; i < this->linetilde_08_activeRamps->length; i += 3) {
                rampEnd = this->linetilde_08_activeRamps[(Index)(i + 2)];

                if (rampEnd > currentTime) {
                    this->linetilde_08_activeRamps[(Index)(i + 2)] = currentTime;
                    number diff = rampEnd - currentTime;
                    number valueDiff = diff * this->linetilde_08_activeRamps[(Index)(i + 1)];
                    lastRampValue = this->linetilde_08_activeRamps[(Index)i] - valueDiff;
                    this->linetilde_08_activeRamps[(Index)i] = lastRampValue;
                    this->linetilde_08_activeRamps->length = i + 3;
                    rampEnd = currentTime;
                } else {
                    lastRampValue = this->linetilde_08_activeRamps[(Index)i];
                }
            }

            if (rampEnd < currentTime) {
                this->linetilde_08_activeRamps->push(lastRampValue);
                this->linetilde_08_activeRamps->push(0);
                this->linetilde_08_activeRamps->push(currentTime);
            }

            number lastRampEnd = currentTime;

            for (Index i = 0; i < v->length; i += 2) {
                number destinationValue = v[(Index)i];
                number inc = 0;
                number rampTimeInSamples;

                if (v->length > i + 1) {
                    rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);

                    if ((bool)(this->linetilde_08_keepramp)) {
                        this->linetilde_08_time_set(v[(Index)(i + 1)]);
                    }
                } else {
                    rampTimeInSamples = this->mstosamps(this->linetilde_08_time);
                }

                if (rampTimeInSamples <= 0) {
                    rampTimeInSamples = 1;
                }

                inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                lastRampEnd += rampTimeInSamples;
                this->linetilde_08_activeRamps->push(destinationValue);
                this->linetilde_08_activeRamps->push(inc);
                this->linetilde_08_activeRamps->push(lastRampEnd);
                lastRampValue = destinationValue;
            }
        }
    }
}

void numberobj_19_output_set(number v) {
    {
        list converted = {v};
        this->linetilde_08_segments_set(converted);
    }
}

void numberobj_19_value_set(number v) {
    this->numberobj_19_value_setter(v);
    v = this->numberobj_19_value;
    number localvalue = v;

    if (this->numberobj_19_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-136"), localvalue, this->_currentTime);
    this->numberobj_19_output_set(localvalue);
}

void expr_07_out1_set(number v) {
    this->expr_07_out1 = v;
    this->numberobj_19_value_set(this->expr_07_out1);
}

void expr_07_in1_set(number in1) {
    this->expr_07_in1 = in1;

    this->expr_07_out1_set(
        (this->expr_07_in2 == 0 ? 0 : (this->expr_07_in2 == 0. ? 0. : this->expr_07_in1 / this->expr_07_in2))
    );//#map:/_obj-137:1
}

void numberobj_20_output_set(number v) {
    this->expr_07_in1_set(v);
}

void numberobj_20_value_set(number v) {
    this->numberobj_20_value_setter(v);
    v = this->numberobj_20_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_20_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-139"), localvalue, this->_currentTime);
    this->numberobj_20_output_set(localvalue);
}

number param_01_value_constrain(number v) const {
    v = (v > 4 ? 4 : (v < 1 ? 1 : v));
    return v;
}

number gen_02_diff_num_constrain(number v) const {
    if (v < 1)
        v = 1;

    if (v > 4)
        v = 4;

    return v;
}

void gen_02_diff_num_set(number v) {
    v = this->gen_02_diff_num_constrain(v);
    this->gen_02_diff_num = v;
}

number param_02_value_constrain(number v) const {
    v = (v > 500 ? 500 : (v < 0 ? 0 : v));
    return v;
}

number gen_02_pre_del_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 500)
        v = 500;

    return v;
}

void gen_02_pre_del_set(number v) {
    v = this->gen_02_pre_del_constrain(v);
    this->gen_02_pre_del = v;
}

number param_03_value_constrain(number v) const {
    v = (v > 0.9 ? 0.9 : (v < 0 ? 0 : v));
    return v;
}

number gen_02_fb1_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 0.9)
        v = 0.9;

    return v;
}

void gen_02_fb1_set(number v) {
    v = this->gen_02_fb1_constrain(v);
    this->gen_02_fb1 = v;
}

number param_04_value_constrain(number v) const {
    v = (v > 0.9 ? 0.9 : (v < 0 ? 0 : v));
    return v;
}

number gen_02_x_fb_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 0.9)
        v = 0.9;

    return v;
}

void gen_02_x_fb_set(number v) {
    v = this->gen_02_x_fb_constrain(v);
    this->gen_02_x_fb = v;
}

number param_06_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void numberobj_16_output_set(number ) {}

void numberobj_16_value_set(number v) {
    this->numberobj_16_value_setter(v);
    v = this->numberobj_16_value;
    number localvalue = v;

    if (this->numberobj_16_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-11"), localvalue, this->_currentTime);
    this->numberobj_16_output_set(localvalue);
}

number gen_01_decay_constrain(number v) const {
    if (v < 0.5)
        v = 0.5;

    if (v > 2)
        v = 2;

    return v;
}

void gen_01_decay_set(number v) {
    v = this->gen_01_decay_constrain(v);
    this->gen_01_decay = v;
}

number gen_02_decay2_constrain(number v) const {
    if (v < 0.2)
        v = 0.2;

    if (v > 2)
        v = 2;

    return v;
}

void gen_02_decay2_set(number v) {
    v = this->gen_02_decay2_constrain(v);
    this->gen_02_decay2 = v;
}

void scale_05_out_set(const list& v) {
    this->scale_05_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_16_value_set(converted);
    }

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gen_01_decay_set(converted);
    }

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gen_02_decay2_set(converted);
    }
}

void scale_05_input_set(const list& v) {
    this->scale_05_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_05_inlow,
            this->scale_05_inhigh,
            this->scale_05_outlow,
            this->scale_05_outhigh,
            this->scale_05_power
        ));
    }

    this->scale_05_out_set(tmp);
}

number param_12_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < -100 ? -100 : v));
    return v;
}

void p_05_in4_number_set(number v) {
    this->p_05->updateTime(this->_currentTime);
    this->p_05->eventinlet_05_out1_number_set(v);
}

void numberobj_22_output_set(number v) {
    this->p_05_in4_number_set(v);
}

void numberobj_22_value_set(number v) {
    this->numberobj_22_value_setter(v);
    v = this->numberobj_22_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_22_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-103"), localvalue, this->_currentTime);
    this->numberobj_22_output_set(localvalue);
}

number param_13_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < -100 ? -100 : v));
    return v;
}

void p_05_in3_number_set(number v) {
    this->p_05->updateTime(this->_currentTime);
    this->p_05->eventinlet_04_out1_number_set(v);
}

void numberobj_23_output_set(number v) {
    this->p_05_in3_number_set(v);
}

void numberobj_23_value_set(number v) {
    this->numberobj_23_value_setter(v);
    v = this->numberobj_23_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_23_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-105"), localvalue, this->_currentTime);
    this->numberobj_23_output_set(localvalue);
}

number param_14_value_constrain(number v) const {
    v = (v > 20000 ? 20000 : (v < 300 ? 300 : v));
    return v;
}

void p_04_in3_number_set(number v) {
    this->p_04->updateTime(this->_currentTime);
    this->p_04->eventinlet_03_out1_number_set(v);
}

void numberobj_24_output_set(number v) {
    this->p_04_in3_number_set(v);
}

void numberobj_24_value_set(number v) {
    this->numberobj_24_value_setter(v);
    v = this->numberobj_24_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 300) {
        localvalue = 300;
    }

    if ((bool)(true) && localvalue > 20000) {
        localvalue = 20000;
    }

    if (this->numberobj_24_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-6"), localvalue, this->_currentTime);
    this->numberobj_24_output_set(localvalue);
}

number param_15_value_constrain(number v) const {
    v = (v > 2 ? 2 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_lfo1_bw_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 10)
        v = 10;

    return v;
}

void gen_01_lfo1_bw_set(number v) {
    v = this->gen_01_lfo1_bw_constrain(v);
    this->gen_01_lfo1_bw = v;
}

number gen_02_lfo1_bw_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 10)
        v = 10;

    return v;
}

void gen_02_lfo1_bw_set(number v) {
    v = this->gen_02_lfo1_bw_constrain(v);
    this->gen_02_lfo1_bw = v;
}

void numberobj_15_output_set(number v) {
    this->param_05_value_set(v);
}

void numberobj_15_value_set(number v) {
    this->numberobj_15_value_setter(v);
    v = this->numberobj_15_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < -1) {
        localvalue = -1;
    }

    if ((bool)(true) && localvalue > 1) {
        localvalue = 1;
    }

    if (this->numberobj_15_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-145"), localvalue, this->_currentTime);
    this->numberobj_15_output_set(localvalue);
}

void ctlin_01_outchannel_set(number ) {}

void ctlin_01_outcontroller_set(number ) {}

void fromnormalized_01_output_set(number v) {
    this->param_07_value_set(v);
}

void fromnormalized_01_input_set(number v) {
    this->fromnormalized_01_output_set(this->fromnormalized(0, v));
}

void expr_04_out1_set(number v) {
    this->expr_04_out1 = v;
    this->fromnormalized_01_input_set(this->expr_04_out1);
}

void expr_04_in1_set(number in1) {
    this->expr_04_in1 = in1;
    this->expr_04_out1_set(this->expr_04_in1 * this->expr_04_in2);//#map:expr_04:1
}

void ctlin_01_value_set(number v) {
    this->expr_04_in1_set(v);
}

void ctlin_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_01_channel || this->ctlin_01_channel == -1) && (data[1] == this->ctlin_01_controller || this->ctlin_01_controller == -1)) {
        this->ctlin_01_outchannel_set(channel);
        this->ctlin_01_outcontroller_set(data[1]);
        this->ctlin_01_value_set(data[2]);
        this->ctlin_01_status = 0;
    }
}

void ctlin_02_outchannel_set(number ) {}

void ctlin_02_outcontroller_set(number ) {}

void fromnormalized_02_output_set(number v) {
    this->param_08_value_set(v);
}

void fromnormalized_02_input_set(number v) {
    this->fromnormalized_02_output_set(this->fromnormalized(2, v));
}

void expr_05_out1_set(number v) {
    this->expr_05_out1 = v;
    this->fromnormalized_02_input_set(this->expr_05_out1);
}

void expr_05_in1_set(number in1) {
    this->expr_05_in1 = in1;
    this->expr_05_out1_set(this->expr_05_in1 * this->expr_05_in2);//#map:expr_05:1
}

void ctlin_02_value_set(number v) {
    this->expr_05_in1_set(v);
}

void ctlin_02_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_02_channel || this->ctlin_02_channel == -1) && (data[1] == this->ctlin_02_controller || this->ctlin_02_controller == -1)) {
        this->ctlin_02_outchannel_set(channel);
        this->ctlin_02_outcontroller_set(data[1]);
        this->ctlin_02_value_set(data[2]);
        this->ctlin_02_status = 0;
    }
}

void ctlin_03_outchannel_set(number ) {}

void ctlin_03_outcontroller_set(number ) {}

void fromnormalized_03_output_set(number v) {
    this->param_09_value_set(v);
}

void fromnormalized_03_input_set(number v) {
    this->fromnormalized_03_output_set(this->fromnormalized(3, v));
}

void expr_06_out1_set(number v) {
    this->expr_06_out1 = v;
    this->fromnormalized_03_input_set(this->expr_06_out1);
}

void expr_06_in1_set(number in1) {
    this->expr_06_in1 = in1;
    this->expr_06_out1_set(this->expr_06_in1 * this->expr_06_in2);//#map:expr_06:1
}

void ctlin_03_value_set(number v) {
    this->expr_06_in1_set(v);
}

void ctlin_03_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_03_channel || this->ctlin_03_channel == -1) && (data[1] == this->ctlin_03_controller || this->ctlin_03_controller == -1)) {
        this->ctlin_03_outchannel_set(channel);
        this->ctlin_03_outcontroller_set(data[1]);
        this->ctlin_03_value_set(data[2]);
        this->ctlin_03_status = 0;
    }
}

void ctlin_04_outchannel_set(number ) {}

void ctlin_04_outcontroller_set(number ) {}

void fromnormalized_04_output_set(number v) {
    this->param_10_value_set(v);
}

void fromnormalized_04_input_set(number v) {
    this->fromnormalized_04_output_set(this->fromnormalized(9, v));
}

void expr_08_out1_set(number v) {
    this->expr_08_out1 = v;
    this->fromnormalized_04_input_set(this->expr_08_out1);
}

void expr_08_in1_set(number in1) {
    this->expr_08_in1 = in1;
    this->expr_08_out1_set(this->expr_08_in1 * this->expr_08_in2);//#map:expr_08:1
}

void ctlin_04_value_set(number v) {
    this->expr_08_in1_set(v);
}

void ctlin_04_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_04_channel || this->ctlin_04_channel == -1) && (data[1] == this->ctlin_04_controller || this->ctlin_04_controller == -1)) {
        this->ctlin_04_outchannel_set(channel);
        this->ctlin_04_outcontroller_set(data[1]);
        this->ctlin_04_value_set(data[2]);
        this->ctlin_04_status = 0;
    }
}

void ctlin_05_outchannel_set(number ) {}

void ctlin_05_outcontroller_set(number ) {}

void fromnormalized_05_output_set(number v) {
    this->param_11_value_set(v);
}

void fromnormalized_05_input_set(number v) {
    this->fromnormalized_05_output_set(this->fromnormalized(1, v));
}

void expr_09_out1_set(number v) {
    this->expr_09_out1 = v;
    this->fromnormalized_05_input_set(this->expr_09_out1);
}

void expr_09_in1_set(number in1) {
    this->expr_09_in1 = in1;
    this->expr_09_out1_set(this->expr_09_in1 * this->expr_09_in2);//#map:expr_09:1
}

void ctlin_05_value_set(number v) {
    this->expr_09_in1_set(v);
}

void ctlin_05_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_05_channel || this->ctlin_05_channel == -1) && (data[1] == this->ctlin_05_controller || this->ctlin_05_controller == -1)) {
        this->ctlin_05_outchannel_set(channel);
        this->ctlin_05_outcontroller_set(data[1]);
        this->ctlin_05_value_set(data[2]);
        this->ctlin_05_status = 0;
    }
}

void ctlin_06_outchannel_set(number ) {}

void ctlin_06_outcontroller_set(number ) {}

void fromnormalized_06_output_set(number v) {
    this->param_12_value_set(v);
}

void fromnormalized_06_input_set(number v) {
    this->fromnormalized_06_output_set(this->fromnormalized(15, v));
}

void expr_10_out1_set(number v) {
    this->expr_10_out1 = v;
    this->fromnormalized_06_input_set(this->expr_10_out1);
}

void expr_10_in1_set(number in1) {
    this->expr_10_in1 = in1;
    this->expr_10_out1_set(this->expr_10_in1 * this->expr_10_in2);//#map:expr_10:1
}

void ctlin_06_value_set(number v) {
    this->expr_10_in1_set(v);
}

void ctlin_06_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_06_channel || this->ctlin_06_channel == -1) && (data[1] == this->ctlin_06_controller || this->ctlin_06_controller == -1)) {
        this->ctlin_06_outchannel_set(channel);
        this->ctlin_06_outcontroller_set(data[1]);
        this->ctlin_06_value_set(data[2]);
        this->ctlin_06_status = 0;
    }
}

void ctlin_07_outchannel_set(number ) {}

void ctlin_07_outcontroller_set(number ) {}

void fromnormalized_07_output_set(number v) {
    this->param_13_value_set(v);
}

void fromnormalized_07_input_set(number v) {
    this->fromnormalized_07_output_set(this->fromnormalized(16, v));
}

void expr_11_out1_set(number v) {
    this->expr_11_out1 = v;
    this->fromnormalized_07_input_set(this->expr_11_out1);
}

void expr_11_in1_set(number in1) {
    this->expr_11_in1 = in1;
    this->expr_11_out1_set(this->expr_11_in1 * this->expr_11_in2);//#map:expr_11:1
}

void ctlin_07_value_set(number v) {
    this->expr_11_in1_set(v);
}

void ctlin_07_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_07_channel || this->ctlin_07_channel == -1) && (data[1] == this->ctlin_07_controller || this->ctlin_07_controller == -1)) {
        this->ctlin_07_outchannel_set(channel);
        this->ctlin_07_outcontroller_set(data[1]);
        this->ctlin_07_value_set(data[2]);
        this->ctlin_07_status = 0;
    }
}

void ctlin_08_outchannel_set(number ) {}

void ctlin_08_outcontroller_set(number ) {}

void fromnormalized_08_output_set(number v) {
    this->param_14_value_set(v);
}

void fromnormalized_08_input_set(number v) {
    this->fromnormalized_08_output_set(this->fromnormalized(17, v));
}

void expr_12_out1_set(number v) {
    this->expr_12_out1 = v;
    this->fromnormalized_08_input_set(this->expr_12_out1);
}

void expr_12_in1_set(number in1) {
    this->expr_12_in1 = in1;
    this->expr_12_out1_set(this->expr_12_in1 * this->expr_12_in2);//#map:expr_12:1
}

void ctlin_08_value_set(number v) {
    this->expr_12_in1_set(v);
}

void ctlin_08_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_08_channel || this->ctlin_08_channel == -1) && (data[1] == this->ctlin_08_controller || this->ctlin_08_controller == -1)) {
        this->ctlin_08_outchannel_set(channel);
        this->ctlin_08_outcontroller_set(data[1]);
        this->ctlin_08_value_set(data[2]);
        this->ctlin_08_status = 0;
    }
}

void p_07_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: preq_LowCut~
    ConstSampleArray<2> ins = {in1, in2};

    SampleArray<2> outs = {out1, out2};
    this->p_07->process(ins, 2, outs, 2, n);
}

void p_06_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: preq_Level~
    ConstSampleArray<2> ins = {in1, in2};

    SampleArray<2> outs = {out1, out2};
    this->p_06->process(ins, 2, outs, 2, n);
}

void gen_02_perform(
    const Sample * in1,
    const Sample * in2,
    number pre_del,
    number lfo1_bw,
    number fb1,
    number lp,
    number decay2,
    number lpf,
    number x_fb,
    number lfo1_rate,
    number diff_gain,
    number apf_g,
    number mixfdn,
    number diff_num,
    SampleValue * out1,
    SampleValue * out2,
    SampleValue * out3,
    Index n
) {
    RNBO_UNUSED(mixfdn);
    RNBO_UNUSED(diff_gain);
    RNBO_UNUSED(lp);
    auto __gen_02_history_21_value = this->gen_02_history_21_value;
    auto __gen_02_history_16_value = this->gen_02_history_16_value;
    auto __gen_02_history_25_value = this->gen_02_history_25_value;
    auto __gen_02_history_24_value = this->gen_02_history_24_value;
    auto __gen_02_history_23_value = this->gen_02_history_23_value;
    auto __gen_02_history_22_value = this->gen_02_history_22_value;
    number mul_36_10 = 1 * apf_g;
    number mul_37_11 = 1 * apf_g;
    number abs_38_12 = rnbo_abs(lpf);
    number mul_39_13 = (this->samplerate() == 0. ? 0. : abs_38_12 * -6.28318530717958647692 / this->samplerate());
    number exp_40_14 = rnbo_exp(mul_39_13);
    auto mstosamps_52_26 = this->mstosamps(pre_del);
    number clamp_105_82 = (mul_37_11 > 1 ? 1 : (mul_37_11 < -1 ? -1 : mul_37_11));
    number neg_106_83 = -clamp_105_82;
    number clamp_113_90 = (mul_37_11 > 1 ? 1 : (mul_37_11 < -1 ? -1 : mul_37_11));
    number neg_114_91 = -clamp_113_90;
    number clamp_131_108 = (mul_36_10 > 1 ? 1 : (mul_36_10 < -1 ? -1 : mul_36_10));
    number neg_132_109 = -clamp_131_108;
    number clamp_150_127 = (mul_36_10 > 1 ? 1 : (mul_36_10 < -1 ? -1 : mul_36_10));
    number neg_151_128 = -clamp_150_127;
    number clamp_176_153 = (mul_36_10 > 1 ? 1 : (mul_36_10 < -1 ? -1 : mul_36_10));
    number neg_177_154 = -clamp_176_153;
    number clamp_193_170 = (mul_37_11 > 1 ? 1 : (mul_37_11 < -1 ? -1 : mul_37_11));
    number neg_194_171 = -clamp_193_170;
    number clamp_201_178 = (mul_37_11 > 1 ? 1 : (mul_37_11 < -1 ? -1 : mul_37_11));
    number neg_202_179 = -clamp_201_178;
    number clamp_216_193 = (mul_36_10 > 1 ? 1 : (mul_36_10 < -1 ? -1 : mul_36_10));
    number neg_217_194 = -clamp_216_193;
    number clamp_224_201 = (mul_36_10 > 1 ? 1 : (mul_36_10 < -1 ? -1 : mul_36_10));
    number neg_225_202 = -clamp_224_201;
    number clamp_232_209 = (mul_36_10 > 1 ? 1 : (mul_36_10 < -1 ? -1 : mul_36_10));
    number neg_233_210 = -clamp_232_209;
    number clamp_240_217 = (mul_36_10 > 1 ? 1 : (mul_36_10 < -1 ? -1 : mul_36_10));
    number neg_241_218 = -clamp_240_217;
    number clamp_248_225 = (mul_36_10 > 1 ? 1 : (mul_36_10 < -1 ? -1 : mul_36_10));
    number neg_249_226 = -clamp_248_225;
    number clamp_266_245 = (mul_37_11 > 1 ? 1 : (mul_37_11 < -1 ? -1 : mul_37_11));
    number neg_267_246 = -clamp_266_245;
    number clamp_274_253 = (mul_37_11 > 1 ? 1 : (mul_37_11 < -1 ? -1 : mul_37_11));
    number neg_275_254 = -clamp_274_253;
    number clamp_282_261 = (mul_37_11 > 1 ? 1 : (mul_37_11 < -1 ? -1 : mul_37_11));
    number neg_283_262 = -clamp_282_261;
    number clamp_290_269 = (mul_37_11 > 1 ? 1 : (mul_37_11 < -1 ? -1 : mul_37_11));
    number neg_291_270 = -clamp_290_269;
    Index i;

    for (i = 0; i < n; i++) {
        out3[(Index)i] = 0;
        number float_26_0 = float(0.99);
        number mix_27_1 = __gen_02_history_22_value + float_26_0 * (1 - __gen_02_history_22_value);
        number float_28_2 = float(0.99);
        number mix_29_3 = __gen_02_history_23_value + float_28_2 * (1 - __gen_02_history_23_value);
        number float_30_4 = float(0.99);
        number mix_31_5 = __gen_02_history_24_value + float_30_4 * (1 - __gen_02_history_24_value);
        number float_32_6 = float(0.99);
        number mix_33_7 = __gen_02_history_25_value + float_32_6 * (1 - __gen_02_history_25_value);
        number outL_34_8 = in2[(Index)i];
        number outR_35_9 = in1[(Index)i];
        number float_41_15 = float(3.3);
        number float_42_16 = float(4.1);
        number float_43_17 = float(70.13);
        number mul_44_18 = float_43_17 * decay2;
        number float_45_19 = float(73.69);
        number mul_46_20 = float_45_19 * decay2;
        number float_47_21 = float(62.1);
        number mul_48_22 = float_47_21 * decay2;
        number float_49_23 = float(65.03);
        number mul_50_24 = float_49_23 * decay2;
        number add_51_25 = in1[(Index)i] + in2[(Index)i];
        this->gen_02_delay_1_write(add_51_25);
        number tap_53_27 = this->gen_02_delay_1_read(mstosamps_52_26, 1);
        number mul_54_28 = tap_53_27 * 0.2;
        number float_55_29 = float(36.15);
        number mul_56_30 = float_55_29 * decay2;
        number float_57_31 = float(46.4);
        number mul_58_32 = float_57_31 * decay2;
        number float_59_33 = float(57.72);
        number mul_60_34 = float_59_33 * decay2;
        number float_61_35 = float(55.75);
        number mul_62_36 = float_61_35 * decay2;
        number float_63_37 = float(35.45);
        number mul_64_38 = float_63_37 * decay2;
        number float_65_39 = float(43.57);
        number mul_66_40 = float_65_39 * decay2;
        number phasor_67_42 = this->gen_02_phasor_41_next(lfo1_rate, 0);
        number cycle_68 = 0;
        number cycleindex_69 = 0;
        array<number, 2> result_44 = this->gen_02_cycle_43_next(phasor_67_42, 0);
        cycleindex_69 = result_44[1];
        cycle_68 = result_44[0];
        auto scale_70_45 = this->scale(cycle_68, -1, 1, 0, 1, 1);
        number mul_71_46 = scale_70_45 * lfo1_bw;
        number add_72_47 = mul_46_20 + mul_71_46;
        auto mstosamps_73_48 = this->mstosamps(add_72_47);
        number add_74_49 = phasor_67_42 + 0.5;
        number cycle_75 = 0;
        number cycleindex_76 = 0;
        array<number, 2> result_51 = this->gen_02_cycle_50_next(add_74_49, 0);
        cycleindex_76 = result_51[1];
        cycle_75 = result_51[0];
        auto scale_77_52 = this->scale(cycle_75, -1, 1, 0, 1, 1);
        number mul_78_53 = scale_77_52 * lfo1_bw;
        number add_79_54 = float_41_15 + mul_78_53;
        auto mstosamps_80_55 = this->mstosamps(add_79_54);
        number tap_81_56 = this->gen_02_delay_2_read(mstosamps_80_55, 0);
        number mul_82_57 = tap_81_56 * x_fb;
        number dcblock_83_59 = this->gen_02_dcblock_58_next(mul_82_57, 0.9997);
        number add_84_60 = mul_44_18 + mul_78_53;
        auto mstosamps_85_61 = this->mstosamps(add_84_60);
        number add_86_62 = phasor_67_42 + 0.46;
        number cycle_87 = 0;
        number cycleindex_88 = 0;
        array<number, 2> result_64 = this->gen_02_cycle_63_next(add_86_62, 0);
        cycleindex_88 = result_64[1];
        cycle_87 = result_64[0];
        auto scale_89_65 = this->scale(cycle_87, -1, 1, 0, 1, 1);
        number mul_90_66 = scale_89_65 * lfo1_bw;
        number add_91_67 = float_42_16 + mul_90_66;
        auto mstosamps_92_68 = this->mstosamps(add_91_67);
        number tap_93_69 = this->gen_02_delay_3_read(mstosamps_92_68, 0);
        number mul_94_70 = tap_93_69 * x_fb;
        number dcblock_95_72 = this->gen_02_dcblock_71_next(mul_94_70, 0.9997);
        number add_96_73 = mul_48_22 + mul_90_66;
        auto mstosamps_97_74 = this->mstosamps(add_96_73);
        number add_98_75 = mul_56_30 + mul_90_66;
        auto mstosamps_99_76 = this->mstosamps(add_98_75);
        number float_100_77 = float(32.87);
        number mul_101_78 = float_100_77 * decay2;
        number add_102_79 = mul_101_78 + mul_78_53;
        auto mstosamps_103_80 = this->mstosamps(add_102_79);
        number tap_104_81 = this->gen_02_delay_4_read(mstosamps_103_80, 1);
        number mul_107_84 = tap_104_81 * clamp_105_82;
        number add_108_85 = mul_54_28 + __gen_02_history_22_value + __gen_02_history_25_value + mul_107_84;
        number mul_109_86 = add_108_85 * neg_106_83;
        number add_110_87 = tap_104_81 + mul_109_86;
        number gen_111_88 = add_110_87;
        number tap_112_89 = this->gen_02_delay_5_read(mstosamps_99_76, 1);
        number mul_115_92 = tap_112_89 * clamp_113_90;
        number add_116_93 = gen_111_88 + mul_115_92;
        number mul_117_94 = add_116_93 * neg_114_91;
        number add_118_95 = tap_112_89 + mul_117_94;
        number gen_119_96 = add_118_95;
        number float_120_97 = float(41.72);
        number mul_121_98 = float_120_97 * decay2;
        number float_122_99 = float(52.45);
        number mul_123_100 = float_122_99 * decay2;
        number float_124_101 = float(49.33);
        number mul_125_102 = float_124_101 * decay2;
        number float_126_103 = float(30.59);
        number mul_127_104 = float_126_103 * decay2;
        number add_128_105 = mul_127_104 + mul_71_46;
        auto mstosamps_129_106 = this->mstosamps(add_128_105);
        number tap_130_107 = this->gen_02_delay_6_read(mstosamps_129_106, 1);
        number mul_133_110 = tap_130_107 * clamp_131_108;
        number add_134_111 = mul_54_28 + __gen_02_history_23_value + __gen_02_history_24_value + mul_133_110;
        number mul_135_112 = add_134_111 * neg_132_109;
        number add_136_113 = tap_130_107 + mul_135_112;
        number gen_137_114 = add_136_113;
        number float_138_115 = float(38.11);
        number mul_139_116 = float_138_115 * decay2;
        number add_140_117 = phasor_67_42 + 0.12;
        number cycle_141 = 0;
        number cycleindex_142 = 0;
        array<number, 2> result_119 = this->gen_02_cycle_118_next(add_140_117, 0);
        cycleindex_142 = result_119[1];
        cycle_141 = result_119[0];
        auto scale_143_120 = this->scale(cycle_141, -1, 1, 0, 1, 1);
        number mul_144_121 = scale_143_120 * lfo1_bw;
        number add_145_122 = mul_50_24 + mul_144_121;
        auto mstosamps_146_123 = this->mstosamps(add_145_122);
        number add_147_124 = mul_64_38 + mul_144_121;
        auto mstosamps_148_125 = this->mstosamps(add_147_124);
        number tap_149_126 = this->gen_02_delay_7_read(mstosamps_148_125, 1);
        number mul_152_129 = tap_149_126 * clamp_150_127;
        number add_153_130 = gen_137_114 + mul_152_129;
        number mul_154_131 = add_153_130 * neg_151_128;
        number add_155_132 = tap_149_126 + mul_154_131;
        number gen_156_133 = add_155_132;
        number add_157_134 = phasor_67_42 + 0.32;
        number cycle_158 = 0;
        number cycleindex_159 = 0;
        array<number, 2> result_136 = this->gen_02_cycle_135_next(add_157_134, 0);
        cycleindex_159 = result_136[1];
        cycle_158 = result_136[0];
        auto scale_160_137 = this->scale(cycle_158, -1, 1, 0, 1, 1);
        number mul_161_138 = scale_160_137 * lfo1_bw;
        number add_162_139 = mul_58_32 + mul_161_138;
        auto mstosamps_163_140 = this->mstosamps(add_162_139);
        number add_164_141 = mul_125_102 + mul_161_138;
        auto mstosamps_165_142 = this->mstosamps(add_164_141);
        number add_166_143 = phasor_67_42 + 0.18;
        number cycle_167 = 0;
        number cycleindex_168 = 0;
        array<number, 2> result_145 = this->gen_02_cycle_144_next(add_166_143, 0);
        cycleindex_168 = result_145[1];
        cycle_167 = result_145[0];
        auto scale_169_146 = this->scale(cycle_167, -1, 1, 0, 1, 1);
        number mul_170_147 = scale_169_146 * lfo1_bw;
        number add_171_148 = mul_60_34 + mul_170_147;
        auto mstosamps_172_149 = this->mstosamps(add_171_148);
        number add_173_150 = mul_139_116 + mul_170_147;
        auto mstosamps_174_151 = this->mstosamps(add_173_150);
        number tap_175_152 = this->gen_02_delay_8_read(mstosamps_174_151, 1);
        number mul_178_155 = tap_175_152 * clamp_176_153;
        number add_179_156 = gen_156_133 + mul_178_155;
        number mul_180_157 = add_179_156 * neg_177_154;
        number add_181_158 = tap_175_152 + mul_180_157;
        number gen_182_159 = add_181_158;
        number add_183_160 = phasor_67_42 + 0.4;
        number cycle_184 = 0;
        number cycleindex_185 = 0;
        array<number, 2> result_162 = this->gen_02_cycle_161_next(add_183_160, 0);
        cycleindex_185 = result_162[1];
        cycle_184 = result_162[0];
        auto scale_186_163 = this->scale(cycle_184, -1, 1, 0, 1, 1);
        number mul_187_164 = scale_186_163 * lfo1_bw;
        number add_188_165 = mul_62_36 + mul_187_164;
        auto mstosamps_189_166 = this->mstosamps(add_188_165);
        number add_190_167 = mul_121_98 + mul_187_164;
        auto mstosamps_191_168 = this->mstosamps(add_190_167);
        number tap_192_169 = this->gen_02_delay_9_read(mstosamps_191_168, 1);
        number mul_195_172 = tap_192_169 * clamp_193_170;
        number add_196_173 = gen_119_96 + mul_195_172;
        number mul_197_174 = add_196_173 * neg_194_171;
        number add_198_175 = tap_192_169 + mul_197_174;
        number gen_199_176 = add_198_175;
        number tap_200_177 = this->gen_02_delay_10_read(mstosamps_163_140, 1);
        number mul_203_180 = tap_200_177 * clamp_201_178;
        number add_204_181 = gen_199_176 + mul_203_180;
        number mul_205_182 = add_204_181 * neg_202_179;
        number add_206_183 = tap_200_177 + mul_205_182;
        number gen_207_184 = add_206_183;
        number add_208_185 = phasor_67_42 + 0.25;
        number cycle_209 = 0;
        number cycleindex_210 = 0;
        array<number, 2> result_187 = this->gen_02_cycle_186_next(add_208_185, 0);
        cycleindex_210 = result_187[1];
        cycle_209 = result_187[0];
        auto scale_211_188 = this->scale(cycle_209, -1, 1, 0, 1, 1);
        number mul_212_189 = scale_211_188 * lfo1_bw;
        number add_213_190 = mul_66_40 + mul_212_189;
        auto mstosamps_214_191 = this->mstosamps(add_213_190);
        number tap_215_192 = this->gen_02_delay_11_read(mstosamps_214_191, 1);
        number mul_218_195 = tap_215_192 * clamp_216_193;
        number add_219_196 = gen_182_159 + mul_218_195;
        number mul_220_197 = add_219_196 * neg_217_194;
        number add_221_198 = tap_215_192 + mul_220_197;
        number gen_222_199 = add_221_198;
        number tap_223_200 = this->gen_02_delay_12_read(mstosamps_165_142, 1);
        number mul_226_203 = tap_223_200 * clamp_224_201;
        number add_227_204 = gen_222_199 + mul_226_203;
        number mul_228_205 = add_227_204 * neg_225_202;
        number add_229_206 = tap_223_200 + mul_228_205;
        number gen_230_207 = add_229_206;
        number tap_231_208 = this->gen_02_delay_13_read(mstosamps_189_166, 1);
        number mul_234_211 = tap_231_208 * clamp_232_209;
        number add_235_212 = gen_230_207 + mul_234_211;
        number mul_236_213 = add_235_212 * neg_233_210;
        number add_237_214 = tap_231_208 + mul_236_213;
        number gen_238_215 = add_237_214;
        number tap_239_216 = this->gen_02_delay_14_read(mstosamps_97_74, 1);
        number mul_242_219 = tap_239_216 * clamp_240_217;
        number add_243_220 = gen_238_215 + mul_242_219;
        number mul_244_221 = add_243_220 * neg_241_218;
        number add_245_222 = tap_239_216 + mul_244_221;
        number gen_246_223 = add_245_222;
        number tap_247_224 = this->gen_02_delay_15_read(mstosamps_85_61, 1);
        number mul_250_227 = tap_247_224 * clamp_248_225;
        number add_251_228 = gen_246_223 + mul_250_227;
        number mul_252_229 = add_251_228 * neg_249_226;
        number add_253_230 = tap_247_224 + mul_252_229;
        number gen_254_231 = add_253_230;
        number mul_255_232 = gen_254_231 * fb1;
        number dcblock_256_234 = this->gen_02_dcblock_233_next(mul_255_232, 0.9997);
        number selector_257_235 = (diff_num >= 4 ? gen_254_231 : (diff_num >= 3 ? gen_238_215 : (diff_num >= 2 ? gen_222_199 : (diff_num >= 1 ? gen_156_133 : 0))));
        number mix_258_236 = selector_257_235 + exp_40_14 * (__gen_02_history_16_value - selector_257_235);
        number gen_259_237 = mix_258_236;
        number history_16_next_260_238 = fixdenorm(mix_258_236);
        number dcblock_261_240 = this->gen_02_dcblock_239_next(gen_259_237, 0.9997);
        number mix_262_241 = outR_35_9 + 1 * (dcblock_261_240 - outR_35_9);
        out1[(Index)i] = mix_262_241;
        number add_263_242 = mul_123_100 + mul_212_189;
        auto mstosamps_264_243 = this->mstosamps(add_263_242);
        number tap_265_244 = this->gen_02_delay_17_read(mstosamps_264_243, 1);
        number mul_268_247 = tap_265_244 * clamp_266_245;
        number add_269_248 = gen_207_184 + mul_268_247;
        number mul_270_249 = add_269_248 * neg_267_246;
        number add_271_250 = tap_265_244 + mul_270_249;
        number gen_272_251 = add_271_250;
        number tap_273_252 = this->gen_02_delay_18_read(mstosamps_172_149, 1);
        number mul_276_255 = tap_273_252 * clamp_274_253;
        number add_277_256 = gen_272_251 + mul_276_255;
        number mul_278_257 = add_277_256 * neg_275_254;
        number add_279_258 = tap_273_252 + mul_278_257;
        number gen_280_259 = add_279_258;
        number tap_281_260 = this->gen_02_delay_19_read(mstosamps_146_123, 1);
        number mul_284_263 = tap_281_260 * clamp_282_261;
        number add_285_264 = gen_280_259 + mul_284_263;
        number mul_286_265 = add_285_264 * neg_283_262;
        number add_287_266 = tap_281_260 + mul_286_265;
        number gen_288_267 = add_287_266;
        number tap_289_268 = this->gen_02_delay_20_read(mstosamps_73_48, 1);
        number mul_292_271 = tap_289_268 * clamp_290_269;
        number add_293_272 = gen_288_267 + mul_292_271;
        number mul_294_273 = add_293_272 * neg_291_270;
        number add_295_274 = tap_289_268 + mul_294_273;
        number gen_296_275 = add_295_274;
        number mul_297_276 = gen_296_275 * fb1;
        number dcblock_298_278 = this->gen_02_dcblock_277_next(mul_297_276, 0.9997);
        number selector_299_279 = (diff_num >= 4 ? gen_296_275 : (diff_num >= 3 ? gen_280_259 : (diff_num >= 2 ? gen_207_184 : (diff_num >= 1 ? gen_119_96 : 0))));
        number mix_300_280 = selector_299_279 + exp_40_14 * (__gen_02_history_21_value - selector_299_279);
        number gen_301_281 = mix_300_280;
        number history_21_next_302_282 = fixdenorm(mix_300_280);
        number dcblock_303_284 = this->gen_02_dcblock_283_next(gen_301_281, 0.9997);
        number mix_304_285 = outL_34_8 + 1 * (dcblock_303_284 - outL_34_8);
        out2[(Index)i] = mix_304_285;
        number history_22_next_305_286 = fixdenorm(mix_27_1 + dcblock_83_59);
        number history_23_next_306_287 = fixdenorm(mix_29_3 + dcblock_95_72);
        number history_24_next_307_288 = fixdenorm(mix_31_5 + dcblock_256_234);
        number history_25_next_308_289 = fixdenorm(mix_33_7 + dcblock_298_278);
        this->gen_02_delay_2_write(gen_254_231);
        __gen_02_history_25_value = history_25_next_308_289;
        __gen_02_history_24_value = history_24_next_307_288;
        __gen_02_history_23_value = history_23_next_306_287;
        __gen_02_history_22_value = history_22_next_305_286;
        __gen_02_history_21_value = history_21_next_302_282;
        this->gen_02_delay_20_write(add_293_272);
        this->gen_02_delay_19_write(add_285_264);
        this->gen_02_delay_18_write(add_277_256);
        this->gen_02_delay_17_write(add_269_248);
        __gen_02_history_16_value = history_16_next_260_238;
        this->gen_02_delay_15_write(add_251_228);
        this->gen_02_delay_14_write(add_243_220);
        this->gen_02_delay_13_write(add_235_212);
        this->gen_02_delay_12_write(add_227_204);
        this->gen_02_delay_11_write(add_219_196);
        this->gen_02_delay_10_write(add_204_181);
        this->gen_02_delay_9_write(add_196_173);
        this->gen_02_delay_8_write(add_179_156);
        this->gen_02_delay_7_write(add_153_130);
        this->gen_02_delay_6_write(add_134_111);
        this->gen_02_delay_5_write(add_116_93);
        this->gen_02_delay_4_write(add_108_85);
        this->gen_02_delay_3_write(gen_296_275);
        this->gen_02_delay_1_step();
        this->gen_02_delay_2_step();
        this->gen_02_delay_3_step();
        this->gen_02_delay_4_step();
        this->gen_02_delay_5_step();
        this->gen_02_delay_6_step();
        this->gen_02_delay_7_step();
        this->gen_02_delay_8_step();
        this->gen_02_delay_9_step();
        this->gen_02_delay_10_step();
        this->gen_02_delay_11_step();
        this->gen_02_delay_12_step();
        this->gen_02_delay_13_step();
        this->gen_02_delay_14_step();
        this->gen_02_delay_15_step();
        this->gen_02_delay_17_step();
        this->gen_02_delay_18_step();
        this->gen_02_delay_19_step();
        this->gen_02_delay_20_step();
    }

    this->gen_02_history_22_value = __gen_02_history_22_value;
    this->gen_02_history_23_value = __gen_02_history_23_value;
    this->gen_02_history_24_value = __gen_02_history_24_value;
    this->gen_02_history_25_value = __gen_02_history_25_value;
    this->gen_02_history_16_value = __gen_02_history_16_value;
    this->gen_02_history_21_value = __gen_02_history_21_value;
}

void gen_01_perform(
    const Sample * in1,
    const Sample * in2,
    number dry_wet,
    number lfo1_bw,
    number lpf,
    number fbc,
    number emphasis,
    number ptch,
    number decay,
    number ptch_ratio,
    number InGain,
    number modulation,
    number lfo1_rate,
    number d1,
    number g1,
    number d2,
    number g2,
    number d3,
    number g3,
    number d4,
    number g4,
    number d5,
    number g5,
    number d6,
    number d7,
    number d8,
    number d9,
    number d10,
    number g10,
    number d11,
    number g11,
    number damp,
    number dL1,
    number gL1,
    number dL2,
    number gL2,
    number dL3,
    number gL3,
    number dL4,
    number gL4,
    number dL5,
    number gL5,
    number dL6,
    number dL7,
    number dL8,
    number dL9,
    number dL10,
    number gL10,
    number dL11,
    number gL11,
    number dampL,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    RNBO_UNUSED(dampL);
    RNBO_UNUSED(gL11);
    RNBO_UNUSED(dL11);
    RNBO_UNUSED(gL10);
    RNBO_UNUSED(dL10);
    RNBO_UNUSED(dL9);
    RNBO_UNUSED(dL8);
    RNBO_UNUSED(dL7);
    RNBO_UNUSED(dL6);
    RNBO_UNUSED(gL5);
    RNBO_UNUSED(dL5);
    RNBO_UNUSED(gL4);
    RNBO_UNUSED(dL4);
    RNBO_UNUSED(gL3);
    RNBO_UNUSED(dL3);
    RNBO_UNUSED(gL2);
    RNBO_UNUSED(dL2);
    RNBO_UNUSED(gL1);
    RNBO_UNUSED(dL1);
    RNBO_UNUSED(damp);
    RNBO_UNUSED(g11);
    RNBO_UNUSED(d11);
    RNBO_UNUSED(g10);
    RNBO_UNUSED(d10);
    RNBO_UNUSED(d9);
    RNBO_UNUSED(d8);
    RNBO_UNUSED(d7);
    RNBO_UNUSED(d6);
    RNBO_UNUSED(g5);
    RNBO_UNUSED(d5);
    RNBO_UNUSED(g4);
    RNBO_UNUSED(d4);
    RNBO_UNUSED(g3);
    RNBO_UNUSED(d3);
    RNBO_UNUSED(g2);
    RNBO_UNUSED(d2);
    RNBO_UNUSED(g1);
    RNBO_UNUSED(d1);
    RNBO_UNUSED(modulation);
    RNBO_UNUSED(ptch_ratio);
    RNBO_UNUSED(ptch);
    RNBO_UNUSED(emphasis);
    RNBO_UNUSED(dry_wet);
    auto __gen_01_history_11_value = this->gen_01_history_11_value;
    auto __gen_01_history_10_value = this->gen_01_history_10_value;
    auto __gen_01_history_8_value = this->gen_01_history_8_value;
    auto __gen_01_history_7_value = this->gen_01_history_7_value;
    auto __gen_01_filterOutput_value = this->gen_01_filterOutput_value;
    auto __gen_01_history_6_value = this->gen_01_history_6_value;
    auto __gen_01_history_4_value = this->gen_01_history_4_value;
    auto __gen_01_history_3_value = this->gen_01_history_3_value;
    auto __gen_01_history_12_value = this->gen_01_history_12_value;
    number mul_57_45 = 1 * 200;
    number mul_64_52 = 1 * 200;
    number mul_70_59 = 1 * 4;
    number mul_71_60 = 1 * lpf;
    number abs_72_61 = rnbo_abs(mul_71_60);
    number mul_73_62 = (this->samplerate() == 0. ? 0. : abs_72_61 * -6.28318530717958647692 / this->samplerate());
    number exp_74_63 = rnbo_exp(mul_73_62);
    number mul_75_64 = 1 * 4;
    auto scale_76_65 = this->scale(0, 1, 0, 0.9, 0.995, 1);
    auto int_85_75 = this->intnum(430);
    auto mstosamps_86_76 = this->mstosamps(int_85_75);
    number rsub_108_102 = 1 - mul_75_64;
    number mul_109_103 = rsub_108_102 * 1000;
    number div_110_104 = (int_85_75 == 0. ? 0. : mul_109_103 / int_85_75);
    number size_172 = decay;
    number alpha_213 = 1 - rnbo_exp((this->samplerate() == 0. ? 0. : -15079.644737231041 / this->samplerate()));
    auto int_183_235 = this->intnum(430);
    auto mstosamps_184_236 = this->mstosamps(int_183_235);
    number rsub_206_262 = 1 - mul_70_59;
    number mul_207_263 = rsub_206_262 * 1000;
    number div_208_264 = (int_183_235 == 0. ? 0. : mul_207_263 / int_183_235);
    Index i;

    for (i = 0; i < n; i++) {
        number mul_13_0 = in1[(Index)i] * InGain;
        number mul_14_1 = in2[(Index)i] * InGain;
        number expr_15_2 = 0.70710678118655 * (mul_13_0 + mul_14_1);
        number expr_16_3 = 0.70710678118655 * (mul_13_0 - mul_14_1);
        number phasor_17_5 = this->gen_01_phasor_4_next(lfo1_rate, 0);
        number cycle_18 = 0;
        number cycleindex_19 = 0;
        array<number, 2> result_7 = this->gen_01_cycle_6_next(phasor_17_5, 0);
        cycleindex_19 = result_7[1];
        cycle_18 = result_7[0];
        auto scale_20_8 = this->scale(cycle_18, -1, 1, 0, 1, 1);
        number mul_21_9 = scale_20_8 * lfo1_bw;
        number add_22_10 = phasor_17_5 + 0.12;
        number cycle_23 = 0;
        number cycleindex_24 = 0;
        array<number, 2> result_12 = this->gen_01_cycle_11_next(add_22_10, 0);
        cycleindex_24 = result_12[1];
        cycle_23 = result_12[0];
        auto scale_25_13 = this->scale(cycle_23, -1, 1, 0, 1, 1);
        number mul_26_14 = scale_25_13 * lfo1_bw;
        number add_27_15 = phasor_17_5 + 0.18;
        number cycle_28 = 0;
        number cycleindex_29 = 0;
        array<number, 2> result_17 = this->gen_01_cycle_16_next(add_27_15, 0);
        cycleindex_29 = result_17[1];
        cycle_28 = result_17[0];
        auto scale_30_18 = this->scale(cycle_28, -1, 1, 0, 1, 1);
        number mul_31_19 = scale_30_18 * lfo1_bw;
        number add_32_20 = phasor_17_5 + 0.25;
        number cycle_33 = 0;
        number cycleindex_34 = 0;
        array<number, 2> result_22 = this->gen_01_cycle_21_next(add_32_20, 0);
        cycleindex_34 = result_22[1];
        cycle_33 = result_22[0];
        auto scale_35_23 = this->scale(cycle_33, -1, 1, 0, 1, 1);
        number mul_36_24 = scale_35_23 * lfo1_bw;
        number add_37_25 = phasor_17_5 + 0.32;
        number cycle_38 = 0;
        number cycleindex_39 = 0;
        array<number, 2> result_27 = this->gen_01_cycle_26_next(add_37_25, 0);
        cycleindex_39 = result_27[1];
        cycle_38 = result_27[0];
        auto scale_40_28 = this->scale(cycle_38, -1, 1, 0, 1, 1);
        number mul_41_29 = scale_40_28 * lfo1_bw;
        number add_42_30 = phasor_17_5 + 0.4;
        number cycle_43 = 0;
        number cycleindex_44 = 0;
        array<number, 2> result_32 = this->gen_01_cycle_31_next(add_42_30, 0);
        cycleindex_44 = result_32[1];
        cycle_43 = result_32[0];
        auto scale_45_33 = this->scale(cycle_43, -1, 1, 0, 1, 1);
        number mul_46_34 = scale_45_33 * lfo1_bw;
        number add_47_35 = phasor_17_5 + 0.46;
        number cycle_48 = 0;
        number cycleindex_49 = 0;
        array<number, 2> result_37 = this->gen_01_cycle_36_next(add_47_35, 0);
        cycleindex_49 = result_37[1];
        cycle_48 = result_37[0];
        auto scale_50_38 = this->scale(cycle_48, -1, 1, 0, 1, 1);
        number mul_51_39 = scale_50_38 * lfo1_bw;
        number add_52_40 = phasor_17_5 + 0.5;
        number cycle_53 = 0;
        number cycleindex_54 = 0;
        array<number, 2> result_42 = this->gen_01_cycle_41_next(add_52_40, 0);
        cycleindex_54 = result_42[1];
        cycle_53 = result_42[0];
        auto scale_55_43 = this->scale(cycle_53, -1, 1, 0, 1, 1);
        number mul_56_44 = scale_55_43 * lfo1_bw;
        number cycle_58 = 0;
        number cycleindex_59 = 0;
        array<number, 2> result_47 = this->gen_01_cycle_46_next(0.4, 0);
        cycleindex_59 = result_47[1];
        cycle_58 = result_47[0];
        auto scale_60_48 = this->scale(cycle_58, -1, 1, 0, mul_57_45, 1);
        number gen_61_49 = scale_60_48;
        number tap_62_50 = this->gen_01_delay_1_read(scale_60_48, 0);
        number gen_63_51 = tap_62_50;
        number cycle_65 = 0;
        number cycleindex_66 = 0;
        array<number, 2> result_55 = this->gen_01_cycle_54_next(0.2, 0);
        cycleindex_66 = result_55[1];
        cycle_65 = result_55[0];
        auto scale_67_56 = this->scale(cycle_65, -1, 1, 0, mul_64_52, 1);
        number tap_68_57 = this->gen_01_delay_2_read(scale_67_56, 0);
        number gen_69_58 = tap_68_57;
        number mix_77_66 = __gen_01_history_12_value + scale_76_65 * (__gen_01_history_3_value - __gen_01_history_12_value);
        number mix_78_67 = mix_77_66 + scale_76_65 * (__gen_01_history_4_value - mix_77_66);
        number sub_79_68 = mix_77_66 - mix_78_67;
        number slide_80_70 = this->gen_01_slide_69_next(sub_79_68, 2, 2);
        number gen_81_71 = slide_80_70;
        number history_3_next_82_72 = fixdenorm(mix_77_66);
        number history_4_next_83_73 = fixdenorm(mix_78_67);
        number mul_84_74 = gen_81_71 * 0;
        number float_87_77 = float(0.006);
        number noise_88_79 = this->gen_01_noise_78_next();
        number abs_89_80 = rnbo_abs(noise_88_79);
        number mul_90_81 = abs_89_80 * float_87_77;
        number add_91_82 = mul_90_81 + 1;
        number mul_92_83 = add_91_82 * mstosamps_86_76;
        number noise_93_85 = this->gen_01_noise_84_next();
        number abs_94_86 = rnbo_abs(noise_93_85);
        number mul_95_87 = abs_94_86 * float_87_77;
        number add_96_88 = mul_95_87 + 1;
        number mul_97_89 = add_96_88 * mstosamps_86_76;
        number noise_98_91 = this->gen_01_noise_90_next();
        number abs_99_92 = rnbo_abs(noise_98_91);
        number mul_100_93 = abs_99_92 * float_87_77;
        number add_101_94 = mul_100_93 + 1;
        number mul_102_95 = add_101_94 * mstosamps_86_76;
        number noise_103_97 = this->gen_01_noise_96_next();
        number abs_104_98 = rnbo_abs(noise_103_97);
        number mul_105_99 = abs_104_98 * float_87_77;
        number add_106_100 = mul_105_99 + 1;
        number mul_107_101 = add_106_100 * mstosamps_86_76;
        number phasor_111_106 = this->gen_01_phasor_105_next(div_110_104, 0);
        number add_112_107 = phasor_111_106 + 0;
        number mod_113_108 = this->safemod(add_112_107, 1);
        number delta_114_110 = this->gen_01_delta_109_next(mod_113_108);
        number sah_115_112 = this->gen_01_sah_111_next(mul_92_83, delta_114_110, 0);
        number mul_116_113 = sah_115_112 * mod_113_108;
        number sub_117_114 = mod_113_108 - 0.5;
        number mul_118_115 = sub_117_114 * 3.14159265358979323846;
        number cos_119_116 = rnbo_cos(mul_118_115);
        number mul_120_117 = cos_119_116 * cos_119_116;
        number add_121_118 = phasor_111_106 + 0.25;
        number mod_122_119 = this->safemod(add_121_118, 1);
        number delta_123_121 = this->gen_01_delta_120_next(mod_122_119);
        number sah_124_123 = this->gen_01_sah_122_next(mul_97_89, delta_123_121, 0);
        number mul_125_124 = sah_124_123 * mod_122_119;
        number sub_126_125 = mod_122_119 - 0.5;
        number mul_127_126 = sub_126_125 * 3.14159265358979323846;
        number cos_128_127 = rnbo_cos(mul_127_126);
        number mul_129_128 = cos_128_127 * cos_128_127;
        number add_130_129 = phasor_111_106 + 0.5;
        number mod_131_130 = this->safemod(add_130_129, 1);
        number delta_132_132 = this->gen_01_delta_131_next(mod_131_130);
        number sah_133_135 = this->gen_01_sah_134_next(mul_102_95, delta_132_132, 0);
        number mul_134_136 = sah_133_135 * mod_131_130;
        number sub_135_137 = mod_131_130 - 0.5;
        number mul_136_138 = sub_135_137 * 3.14159265358979323846;
        number cos_137_139 = rnbo_cos(mul_136_138);
        number mul_138_140 = cos_137_139 * cos_137_139;
        number add_139_141 = phasor_111_106 + 0.75;
        number mod_140_142 = this->safemod(add_139_141, 1);
        number delta_141_144 = this->gen_01_delta_143_next(mod_140_142);
        number sah_142_146 = this->gen_01_sah_145_next(mul_107_101, delta_141_144, 0);
        number mul_143_147 = sah_142_146 * mod_140_142;
        number tap_144_148 = this->gen_01_delay_5_read(mul_116_113, 0);
        number tap_145_149 = this->gen_01_delay_5_read(mul_125_124, 0);
        number tap_146_150 = this->gen_01_delay_5_read(mul_134_136, 0);
        number tap_147_151 = this->gen_01_delay_5_read(mul_143_147, 0);
        number mul_148_152 = tap_144_148 * mul_120_117;
        number mul_149_153 = tap_145_149 * mul_129_128;
        number mul_150_154 = tap_146_150 * mul_138_140;
        number sub_151_155 = mod_140_142 - 0.5;
        number mul_152_156 = sub_151_155 * 3.14159265358979323846;
        number cos_153_157 = rnbo_cos(mul_152_156);
        number mul_154_158 = cos_153_157 * cos_153_157;
        number mul_155_159 = tap_147_151 * mul_154_158;
        number mul_156_160 = (mul_155_159 + mul_150_154 + mul_149_153 + mul_148_152) * 0.5;
        number gen_157_161 = mul_156_160;
        number mul_158_162 = gen_157_161 * 0.9;
        number add_159_163 = gen_69_58 + mul_158_162;
        number mix_160_164 = add_159_163 + exp_74_63 * (__gen_01_history_6_value - add_159_163);
        number gen_161_165 = mix_160_164;
        number history_6_next_162_166 = fixdenorm(mix_160_164);
        number add_163_167 = expr_15_2 + gen_161_165;
        number lfo1_168 = mul_21_9;
        number lfo2_169 = mul_26_14;
        number lfo3_170 = mul_31_19;
        number lfo5_171 = mul_41_29;
        number d1mod_173 = 120 * size_172 + lfo1_168;
        number d2mod_174 = 76 * size_172 + lfo2_169;
        number d3mod_175 = 30 * size_172 + lfo3_170;
        number d4mod_176 = 8 * size_172 + mul_36_24;
        number d5mod_177 = 12 * size_172 + lfo5_171;
        number d6mod_178 = 4 * size_172 + mul_46_34;
        number d7mod_179 = 17 * size_172 + mul_51_39;
        number d8mod_180 = 31 * size_172 + mul_56_44;
        number d9mod_181 = 3 * size_172 + lfo5_171;
        number d10mod_182 = 87 * size_172 + mul_46_34;
        number d11mod_183 = 62 * size_172 + mul_51_39;
        number ds1_184 = d1mod_173 * this->samplerate() / (number)1000;
        number ds2_185 = d2mod_174 * this->samplerate() / (number)1000;
        number ds3_186 = d3mod_175 * this->samplerate() / (number)1000;
        number ds4_187 = d4mod_176 * this->samplerate() / (number)1000;
        number ds5_188 = d5mod_177 * this->samplerate() / (number)1000;
        number ds6_189 = d6mod_178 * this->samplerate() / (number)1000;
        number ds7_190 = d7mod_179 * this->samplerate() / (number)1000;
        number ds8_191 = d8mod_180 * this->samplerate() / (number)1000;
        number ds9_192 = d9mod_181 * this->samplerate() / (number)1000;
        number ds10_193 = d10mod_182 * this->samplerate() / (number)1000;
        number ds11_194 = d11mod_183 * this->samplerate() / (number)1000;
        number apf1out_195 = -0.3 * add_163_167 + this->gen_01_DL4_read(ds4_187, 1);
        this->gen_01_DL4_write(add_163_167 + 0.3 * apf1out_195);
        number apf2out_196 = -0.3 * apf1out_195 + this->gen_01_DL5_read(ds5_188, 1);
        this->gen_01_DL5_write(apf1out_195 + 0.3 * apf2out_196);
        this->gen_01_DL6_write(apf2out_196);
        number dl6out_197 = this->gen_01_DL6_read(ds6_189, 1);
        number expr_164_198 = dl6out_197 * 0.34;
        this->gen_01_DL7_write(dl6out_197);
        number dl7out_199 = this->gen_01_DL7_read(ds7_190, 1);
        number napf1out_200 = this->gen_01_DL10_read(ds10_193, 1) - 0.5 * dl7out_199;
        this->gen_01_DL10_write(dl7out_199 + 0.5 * napf1out_200);
        number allPassOut2_201 = this->gen_01_DL11_read(ds11_194, 1) - 0.25 * napf1out_200;
        this->gen_01_DL11_write(napf1out_200 + 0.25 * allPassOut2_201);
        this->gen_01_DL8_write(allPassOut2_201);
        number dl8out_202 = this->gen_01_DL8_read(ds8_191, 1);
        number expr_165_203 = dl8out_202 * 0.14;
        this->gen_01_DL9_write(dl8out_202);
        number dl9out_204 = this->gen_01_DL9_read(ds9_192, 1);
        number x5_205 = dl9out_204;
        number y1_206 = -0.5 * x5_205 + this->gen_01_DL1_read(ds1_184, 1);
        this->gen_01_DL1_write(x5_205 + 0.5 * y1_206);
        number delayAddr1_207 = ds1_184 - ds2_185;
        number y2_208 = -0.25 * y1_206 + this->gen_01_DL2_read(delayAddr1_207, 1);
        this->gen_01_DL2_write(y1_206 + 0.25 * y2_208);
        number delayAddr2_209 = ds1_184 - ds3_186;
        number y3_210 = -0.25 * y2_208 + this->gen_01_DL3_read(delayAddr2_209, 1);
        this->gen_01_DL3_write(y2_208 + 0.25 * y3_210);
        number y_211 = -0.5 * x5_205 + this->gen_01_DL1_read(ds1_184, 1);
        this->gen_01_DL1_write(x5_205 + 0.5 * y_211);
        number tolp_212 = y3_210;
        number inlp_214 = tolp_212;
        number lowpass_215 = (1 - alpha_213) * __gen_01_filterOutput_value + alpha_213 * inlp_214;
        __gen_01_filterOutput_value = lowpass_215;
        number expr_166_216 = y3_210 * 0.14;
        number expr_167_217 = y3_210;
        number mul_168_218 = expr_167_217 * fbc;
        number add_169_219 = expr_164_198 + expr_165_203;
        number add_170_220 = expr_166_216 + 0;
        number add_171_221 = add_169_219 + add_170_220;
        number outL_172_222 = add_171_221;
        number dcblock_173_224 = this->gen_01_dcblock_223_next(outL_172_222, 0.9997);
        number clamp_174_225 = (dcblock_173_224 > 1 ? 1 : (dcblock_173_224 < -1 ? -1 : dcblock_173_224));
        out1[(Index)i] = clamp_174_225;
        number mix_175_226 = expr_167_217 + scale_76_65 * (__gen_01_history_7_value - expr_167_217);
        number mix_176_227 = mix_175_226 + scale_76_65 * (__gen_01_history_8_value - mix_175_226);
        number sub_177_228 = mix_175_226 - mix_176_227;
        number slide_178_230 = this->gen_01_slide_229_next(sub_177_228, 2, 2);
        number gen_179_231 = slide_178_230;
        number history_7_next_180_232 = fixdenorm(mix_175_226);
        number history_8_next_181_233 = fixdenorm(mix_176_227);
        number mul_182_234 = gen_179_231 * 0;
        number float_185_237 = float(0.006);
        number noise_186_239 = this->gen_01_noise_238_next();
        number abs_187_240 = rnbo_abs(noise_186_239);
        number mul_188_241 = abs_187_240 * float_185_237;
        number add_189_242 = mul_188_241 + 1;
        number mul_190_243 = add_189_242 * mstosamps_184_236;
        number noise_191_245 = this->gen_01_noise_244_next();
        number abs_192_246 = rnbo_abs(noise_191_245);
        number mul_193_247 = abs_192_246 * float_185_237;
        number add_194_248 = mul_193_247 + 1;
        number mul_195_249 = add_194_248 * mstosamps_184_236;
        number noise_196_251 = this->gen_01_noise_250_next();
        number abs_197_252 = rnbo_abs(noise_196_251);
        number mul_198_253 = abs_197_252 * float_185_237;
        number add_199_254 = mul_198_253 + 1;
        number mul_200_255 = add_199_254 * mstosamps_184_236;
        number noise_201_257 = this->gen_01_noise_256_next();
        number abs_202_258 = rnbo_abs(noise_201_257);
        number mul_203_259 = abs_202_258 * float_185_237;
        number add_204_260 = mul_203_259 + 1;
        number mul_205_261 = add_204_260 * mstosamps_184_236;
        number phasor_209_266 = this->gen_01_phasor_265_next(div_208_264, 0);
        number add_210_267 = phasor_209_266 + 0;
        number mod_211_268 = this->safemod(add_210_267, 1);
        number delta_212_270 = this->gen_01_delta_269_next(mod_211_268);
        number sah_213_272 = this->gen_01_sah_271_next(mul_190_243, delta_212_270, 0);
        number mul_214_273 = sah_213_272 * mod_211_268;
        number sub_215_274 = mod_211_268 - 0.5;
        number mul_216_275 = sub_215_274 * 3.14159265358979323846;
        number cos_217_276 = rnbo_cos(mul_216_275);
        number mul_218_277 = cos_217_276 * cos_217_276;
        number add_219_278 = phasor_209_266 + 0.25;
        number mod_220_279 = this->safemod(add_219_278, 1);
        number delta_221_281 = this->gen_01_delta_280_next(mod_220_279);
        number sah_222_283 = this->gen_01_sah_282_next(mul_195_249, delta_221_281, 0);
        number mul_223_284 = sah_222_283 * mod_220_279;
        number sub_224_285 = mod_220_279 - 0.5;
        number mul_225_286 = sub_224_285 * 3.14159265358979323846;
        number cos_226_287 = rnbo_cos(mul_225_286);
        number mul_227_288 = cos_226_287 * cos_226_287;
        number add_228_289 = phasor_209_266 + 0.5;
        number mod_229_290 = this->safemod(add_228_289, 1);
        number delta_230_292 = this->gen_01_delta_291_next(mod_229_290);
        number sah_231_294 = this->gen_01_sah_293_next(mul_200_255, delta_230_292, 0);
        number mul_232_295 = sah_231_294 * mod_229_290;
        number sub_233_296 = mod_229_290 - 0.5;
        number mul_234_297 = sub_233_296 * 3.14159265358979323846;
        number cos_235_298 = rnbo_cos(mul_234_297);
        number mul_236_299 = cos_235_298 * cos_235_298;
        number add_237_300 = phasor_209_266 + 0.75;
        number mod_238_301 = this->safemod(add_237_300, 1);
        number delta_239_303 = this->gen_01_delta_302_next(mod_238_301);
        number sah_240_305 = this->gen_01_sah_304_next(mul_205_261, delta_239_303, 0);
        number mul_241_306 = sah_240_305 * mod_238_301;
        number tap_242_307 = this->gen_01_delay_9_read(mul_214_273, 0);
        number tap_243_308 = this->gen_01_delay_9_read(mul_223_284, 0);
        number tap_244_309 = this->gen_01_delay_9_read(mul_232_295, 0);
        number tap_245_310 = this->gen_01_delay_9_read(mul_241_306, 0);
        number mul_246_311 = tap_242_307 * mul_218_277;
        number mul_247_312 = tap_243_308 * mul_227_288;
        number mul_248_313 = tap_244_309 * mul_236_299;
        number sub_249_314 = mod_238_301 - 0.5;
        number mul_250_315 = sub_249_314 * 3.14159265358979323846;
        number cos_251_316 = rnbo_cos(mul_250_315);
        number mul_252_317 = cos_251_316 * cos_251_316;
        number mul_253_318 = tap_245_310 * mul_252_317;
        number mul_254_319 = (mul_253_318 + mul_248_313 + mul_247_312 + mul_246_311) * 0.5;
        number gen_255_320 = mul_254_319;
        number mul_256_321 = gen_255_320 * 0.9;
        number add_257_322 = gen_63_51 + mul_256_321;
        number mix_258_323 = add_257_322 + exp_74_63 * (__gen_01_history_10_value - add_257_322);
        number gen_259_324 = mix_258_323;
        number history_10_next_260_325 = fixdenorm(mix_258_323);
        number add_261_326 = expr_16_3 + gen_259_324;
        number d1mod_262_327 = 111 * decay + mul_21_9;
        number d2mod_263_328 = 37 * decay + mul_26_14;
        number d3mod_264_329 = 15 * decay + mul_31_19;
        number d4mod_265_330 = 8 * decay + mul_36_24;
        number d5mod_266_331 = 12 * decay + mul_41_29;
        number d6mod_267_332 = 3.9 * decay + mul_46_34;
        number d7mod_268_333 = 31 * decay + mul_51_39;
        number d8mod_269_334 = 17 * decay + mul_56_44;
        number d9mod_270_335 = 8 * decay + mul_41_29;
        number d10mod_271_336 = 43 * decay + mul_46_34;
        number d11mod_272_337 = 44 * decay + mul_51_39;
        number ds_273_338 = d1mod_262_327 * this->samplerate() / (number)1000;
        number ds_274_339 = d2mod_263_328 * this->samplerate() / (number)1000;
        number ds_275_340 = d3mod_264_329 * this->samplerate() / (number)1000;
        number ds_276_341 = d4mod_265_330 * this->samplerate() / (number)1000;
        number ds_277_342 = d5mod_266_331 * this->samplerate() / (number)1000;
        number ds_278_343 = d6mod_267_332 * this->samplerate() / (number)1000;
        number ds_279_344 = d7mod_268_333 * this->samplerate() / (number)1000;
        number ds_280_345 = d8mod_269_334 * this->samplerate() / (number)1000;
        number ds_281_346 = d9mod_270_335 * this->samplerate() / (number)1000;
        number ds_282_347 = d10mod_271_336 * this->samplerate() / (number)1000;
        number ds_283_348 = d11mod_272_337 * this->samplerate() / (number)1000;
        number apf1out_284_349 = -0.3 * add_261_326 + this->gen_01_dlL4_read(ds_276_341, 1);
        this->gen_01_dlL4_write(add_261_326 + 0.3 * apf1out_284_349);
        number apf2out_285_350 = -0.3 * apf1out_284_349 + this->gen_01_dlL5_read(ds_277_342, 1);
        this->gen_01_dlL5_write(apf1out_284_349 + 0.3 * apf2out_285_350);
        this->gen_01_dlL6_write(apf2out_285_350);
        number dl6out_286_351 = this->gen_01_dlL6_read(ds_278_343, 1);
        number expr_287_352 = dl6out_286_351 * 0.34;
        this->gen_01_dlL7_write(dl6out_286_351);
        number dl7out_288_353 = this->gen_01_dlL7_read(ds_279_344, 1);
        number napf1out_289_354 = this->gen_01_dlL10_read(ds_282_347, 1) - 0.5 * dl7out_288_353;
        this->gen_01_dlL10_write(dl7out_288_353 + 0.5 * napf1out_289_354);
        number allPassOut_290_355 = this->gen_01_dlL11_read(ds_283_348, 1) - 0.25 * napf1out_289_354;
        this->gen_01_dlL11_write(napf1out_289_354 + 0.25 * allPassOut_290_355);
        this->gen_01_dlL8_write(allPassOut_290_355);
        number dl8out_291_356 = this->gen_01_dlL8_read(ds_280_345, 1);
        number expr_292_357 = dl8out_291_356 * 0.14;
        this->gen_01_dlL9_write(dl8out_291_356);
        number dl9out_293_358 = this->gen_01_dlL9_read(ds_281_346, 1);
        number y_294_359 = -0.5 * dl9out_293_358 + this->gen_01_dlL1_read(ds_273_338, 1);
        this->gen_01_dlL1_write(dl9out_293_358 + 0.5 * y_294_359);
        number delayAddr_295_360 = ds_273_338 - ds_274_339;
        number y_296_361 = -0.25 * y_294_359 + this->gen_01_dlL2_read(delayAddr_295_360, 1);
        this->gen_01_dlL2_write(y_294_359 + 0.25 * y_296_361);
        number delayAddr_297_362 = ds_273_338 - ds_275_340;
        number y_298_363 = -0.25 * y_296_361 + this->gen_01_dlL3_read(delayAddr_297_362, 1);
        this->gen_01_dlL3_write(y_296_361 + 0.25 * y_298_363);
        number y_299_364 = -0.5 * dl9out_293_358 + this->gen_01_dlL1_read(ds_273_338, 1);
        this->gen_01_dlL1_write(dl9out_293_358 + 0.5 * y_299_364);
        number expr_300_365 = y_298_363 * 0.14;
        number expr_301_366 = y_298_363;
        number mul_302_367 = expr_301_366 * fbc;
        number add_303_368 = expr_287_352 + expr_292_357;
        number add_304_369 = expr_300_365 + 0;
        number add_305_370 = add_303_368 + add_304_369;
        number outR_306_371 = add_305_370;
        number dcblock_307_373 = this->gen_01_dcblock_372_next(outR_306_371, 0.9997);
        number clamp_308_374 = (dcblock_307_373 > 1 ? 1 : (dcblock_307_373 < -1 ? -1 : dcblock_307_373));
        out2[(Index)i] = clamp_308_374;
        number history_11_next_309_375 = fixdenorm(mul_168_218);
        number history_12_next_310_376 = fixdenorm(mul_302_367);
        this->gen_01_delay_1_write(__gen_01_history_11_value);
        __gen_01_history_12_value = history_12_next_310_376;
        __gen_01_history_11_value = history_11_next_309_375;
        __gen_01_history_10_value = history_10_next_260_325;
        this->gen_01_delay_9_write(mul_182_234);
        __gen_01_history_8_value = history_8_next_181_233;
        __gen_01_history_7_value = history_7_next_180_232;
        __gen_01_history_6_value = history_6_next_162_166;
        this->gen_01_delay_5_write(mul_84_74);
        __gen_01_history_4_value = history_4_next_83_73;
        __gen_01_history_3_value = history_3_next_82_72;
        this->gen_01_delay_2_write(__gen_01_history_12_value);
        this->gen_01_delay_1_step();
        this->gen_01_delay_2_step();
        this->gen_01_delay_5_step();
        this->gen_01_DL1_step();
        this->gen_01_DL2_step();
        this->gen_01_DL3_step();
        this->gen_01_DL4_step();
        this->gen_01_DL5_step();
        this->gen_01_DL6_step();
        this->gen_01_DL7_step();
        this->gen_01_DL8_step();
        this->gen_01_DL9_step();
        this->gen_01_DL10_step();
        this->gen_01_DL11_step();
        this->gen_01_DL12_step();
        this->gen_01_DL13_step();
        this->gen_01_delay_9_step();
        this->gen_01_dlL1_step();
        this->gen_01_dlL2_step();
        this->gen_01_dlL3_step();
        this->gen_01_dlL4_step();
        this->gen_01_dlL5_step();
        this->gen_01_dlL6_step();
        this->gen_01_dlL7_step();
        this->gen_01_dlL8_step();
        this->gen_01_dlL9_step();
        this->gen_01_dlL10_step();
        this->gen_01_dlL11_step();
        this->gen_01_dlL12_step();
        this->gen_01_dlL13_step();
    }

    this->gen_01_history_12_value = __gen_01_history_12_value;
    this->gen_01_history_3_value = __gen_01_history_3_value;
    this->gen_01_history_4_value = __gen_01_history_4_value;
    this->gen_01_history_6_value = __gen_01_history_6_value;
    this->gen_01_filterOutput_value = __gen_01_filterOutput_value;
    this->gen_01_history_7_value = __gen_01_history_7_value;
    this->gen_01_history_8_value = __gen_01_history_8_value;
    this->gen_01_history_10_value = __gen_01_history_10_value;
    this->gen_01_history_11_value = __gen_01_history_11_value;
}

void p_03_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: LowCut~
    ConstSampleArray<2> ins = {in1, in2};

    SampleArray<2> outs = {out1, out2};
    this->p_03->process(ins, 2, outs, 2, n);
}

void p_05_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: HighMid~
    ConstSampleArray<2> ins = {in1, in2};

    SampleArray<2> outs = {out1, out2};
    this->p_05->process(ins, 2, outs, 2, n);
}

void p_04_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: HighCut~
    ConstSampleArray<2> ins = {in1, in2};

    SampleArray<2> outs = {out1, out2};
    this->p_04->process(ins, 2, outs, 2, n);
}

void p_02_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: preq_Level~
    ConstSampleArray<2> ins = {in1, in2};

    SampleArray<2> outs = {out1, out2};
    this->p_02->process(ins, 2, outs, 2, n);
}

void linetilde_08_perform(SampleValue * out, Index n) {
    auto __linetilde_08_time = this->linetilde_08_time;
    auto __linetilde_08_keepramp = this->linetilde_08_keepramp;
    auto __linetilde_08_currentValue = this->linetilde_08_currentValue;
    Index i = 0;

    if ((bool)(this->linetilde_08_activeRamps->length)) {
        while ((bool)(this->linetilde_08_activeRamps->length) && i < n) {
            number destinationValue = this->linetilde_08_activeRamps[0];
            number inc = this->linetilde_08_activeRamps[1];
            number rampTimeInSamples = this->linetilde_08_activeRamps[2] - this->audioProcessSampleCount - i;
            number val = __linetilde_08_currentValue;

            while (rampTimeInSamples > 0 && i < n) {
                out[(Index)i] = val;
                val += inc;
                i++;
                rampTimeInSamples--;
            }

            if (rampTimeInSamples <= 0) {
                val = destinationValue;
                this->linetilde_08_activeRamps->splice(0, 3);

                if ((bool)(!(bool)(this->linetilde_08_activeRamps->length))) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -62043057,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;

                    if ((bool)(!(bool)(__linetilde_08_keepramp))) {
                        __linetilde_08_time = 0;
                    }
                }
            }

            __linetilde_08_currentValue = val;
        }
    }

    while (i < n) {
        out[(Index)i] = __linetilde_08_currentValue;
        i++;
    }

    this->linetilde_08_currentValue = __linetilde_08_currentValue;
    this->linetilde_08_time = __linetilde_08_time;
}

void p_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    const SampleValue * in4,
    const SampleValue * in5,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: Full_Mix~
    ConstSampleArray<5> ins = {in1, in2, in3, in4, in5};

    SampleArray<2> outs = {out1, out2};
    this->p_01->process(ins, 5, outs, 2, n);
}

void dspexpr_05_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < -1 ? -1 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void dspexpr_06_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < -1 ? -1 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void numberobj_15_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < -1) {
        localvalue = -1;
    }

    if ((bool)(true) && localvalue > 1) {
        localvalue = 1;
    }

    if (this->numberobj_15_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_15_value = localvalue;
}

void numberobj_16_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_16_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_16_value = localvalue;
}

void toggle_02_value_number_setter(number v) {
    this->toggle_02_value_number = (v != 0 ? 1 : 0);
}

void numberobj_17_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_17_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_17_value = localvalue;
}

void numberobj_18_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_18_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_18_value = localvalue;
}

void numberobj_19_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_19_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_19_value = localvalue;
}

void numberobj_20_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_20_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_20_value = localvalue;
}

void numberobj_21_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 10) {
        localvalue = 10;
    }

    if ((bool)(true) && localvalue > 1500) {
        localvalue = 1500;
    }

    if (this->numberobj_21_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_21_value = localvalue;
}

void numberobj_22_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_22_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_22_value = localvalue;
}

void numberobj_23_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_23_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_23_value = localvalue;
}

void numberobj_24_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 300) {
        localvalue = 300;
    }

    if ((bool)(true) && localvalue > 20000) {
        localvalue = 20000;
    }

    if (this->numberobj_24_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_24_value = localvalue;
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

void numberobj_15_init() {
    this->numberobj_15_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-145"), 1, this->_currentTime);
}

void numberobj_15_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_15_value;
}

void numberobj_15_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_15_value_set(preset["value"]);
}

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
}

void numberobj_16_init() {
    this->numberobj_16_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-11"), 1, this->_currentTime);
}

void numberobj_16_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_16_value;
}

void numberobj_16_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_16_value_set(preset["value"]);
}

void gen_01_delay_1_step() {
    this->gen_01_delay_1_reader++;

    if (this->gen_01_delay_1_reader >= (int)(this->gen_01_delay_1_buffer->getSize()))
        this->gen_01_delay_1_reader = 0;
}

number gen_01_delay_1_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        number r = (int)(this->gen_01_delay_1_buffer->getSize()) + this->gen_01_delay_1_reader - ((size > this->gen_01_delay_1__maxdelay ? this->gen_01_delay_1__maxdelay : (size < (this->gen_01_delay_1_reader != this->gen_01_delay_1_writer) ? this->gen_01_delay_1_reader != this->gen_01_delay_1_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_delay_1_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_delay_1_wrap))
        ), this->gen_01_delay_1_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_delay_1_wrap))
        ));
    }

    number r = (int)(this->gen_01_delay_1_buffer->getSize()) + this->gen_01_delay_1_reader - ((size > this->gen_01_delay_1__maxdelay ? this->gen_01_delay_1__maxdelay : (size < (this->gen_01_delay_1_reader != this->gen_01_delay_1_writer) ? this->gen_01_delay_1_reader != this->gen_01_delay_1_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_delay_1_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_delay_1_wrap))
    );
}

void gen_01_delay_1_write(number v) {
    this->gen_01_delay_1_writer = this->gen_01_delay_1_reader;
    this->gen_01_delay_1_buffer[(Index)this->gen_01_delay_1_writer] = v;
}

number gen_01_delay_1_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_delay_1__maxdelay : size);
    number val = this->gen_01_delay_1_read(effectiveSize, 0);
    this->gen_01_delay_1_write(v);
    this->gen_01_delay_1_step();
    return val;
}

array<Index, 2> gen_01_delay_1_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_delay_1_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_delay_1_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_delay_1_init() {
    auto result = this->gen_01_delay_1_calcSizeInSamples();
    this->gen_01_delay_1__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_delay_1_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_delay_1_wrap = requestedSizeInSamples - 1;
}

void gen_01_delay_1_clear() {
    this->gen_01_delay_1_buffer->setZero();
}

void gen_01_delay_1_reset() {
    auto result = this->gen_01_delay_1_calcSizeInSamples();
    this->gen_01_delay_1__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_delay_1_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_delay_1_buffer);
    this->gen_01_delay_1_wrap = this->gen_01_delay_1_buffer->getSize() - 1;
    this->gen_01_delay_1_clear();

    if (this->gen_01_delay_1_reader >= this->gen_01_delay_1__maxdelay || this->gen_01_delay_1_writer >= this->gen_01_delay_1__maxdelay) {
        this->gen_01_delay_1_reader = 0;
        this->gen_01_delay_1_writer = 0;
    }
}

void gen_01_delay_1_dspsetup() {
    this->gen_01_delay_1_reset();
}

number gen_01_delay_1_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_01_delay_1_size() {
    return this->gen_01_delay_1__maxdelay;
}

void gen_01_delay_2_step() {
    this->gen_01_delay_2_reader++;

    if (this->gen_01_delay_2_reader >= (int)(this->gen_01_delay_2_buffer->getSize()))
        this->gen_01_delay_2_reader = 0;
}

number gen_01_delay_2_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        number r = (int)(this->gen_01_delay_2_buffer->getSize()) + this->gen_01_delay_2_reader - ((size > this->gen_01_delay_2__maxdelay ? this->gen_01_delay_2__maxdelay : (size < (this->gen_01_delay_2_reader != this->gen_01_delay_2_writer) ? this->gen_01_delay_2_reader != this->gen_01_delay_2_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_delay_2_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_delay_2_wrap))
        ), this->gen_01_delay_2_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_delay_2_wrap))
        ));
    }

    number r = (int)(this->gen_01_delay_2_buffer->getSize()) + this->gen_01_delay_2_reader - ((size > this->gen_01_delay_2__maxdelay ? this->gen_01_delay_2__maxdelay : (size < (this->gen_01_delay_2_reader != this->gen_01_delay_2_writer) ? this->gen_01_delay_2_reader != this->gen_01_delay_2_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_delay_2_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_delay_2_wrap))
    );
}

void gen_01_delay_2_write(number v) {
    this->gen_01_delay_2_writer = this->gen_01_delay_2_reader;
    this->gen_01_delay_2_buffer[(Index)this->gen_01_delay_2_writer] = v;
}

number gen_01_delay_2_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_delay_2__maxdelay : size);
    number val = this->gen_01_delay_2_read(effectiveSize, 0);
    this->gen_01_delay_2_write(v);
    this->gen_01_delay_2_step();
    return val;
}

array<Index, 2> gen_01_delay_2_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_delay_2_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_delay_2_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_delay_2_init() {
    auto result = this->gen_01_delay_2_calcSizeInSamples();
    this->gen_01_delay_2__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_delay_2_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_delay_2_wrap = requestedSizeInSamples - 1;
}

void gen_01_delay_2_clear() {
    this->gen_01_delay_2_buffer->setZero();
}

void gen_01_delay_2_reset() {
    auto result = this->gen_01_delay_2_calcSizeInSamples();
    this->gen_01_delay_2__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_delay_2_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_delay_2_buffer);
    this->gen_01_delay_2_wrap = this->gen_01_delay_2_buffer->getSize() - 1;
    this->gen_01_delay_2_clear();

    if (this->gen_01_delay_2_reader >= this->gen_01_delay_2__maxdelay || this->gen_01_delay_2_writer >= this->gen_01_delay_2__maxdelay) {
        this->gen_01_delay_2_reader = 0;
        this->gen_01_delay_2_writer = 0;
    }
}

void gen_01_delay_2_dspsetup() {
    this->gen_01_delay_2_reset();
}

number gen_01_delay_2_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_01_delay_2_size() {
    return this->gen_01_delay_2__maxdelay;
}

number gen_01_history_3_getvalue() {
    return this->gen_01_history_3_value;
}

void gen_01_history_3_setvalue(number val) {
    this->gen_01_history_3_value = val;
}

void gen_01_history_3_reset() {
    this->gen_01_history_3_value = 0;
}

void gen_01_history_3_init() {
    this->gen_01_history_3_value = 0;
}

number gen_01_history_4_getvalue() {
    return this->gen_01_history_4_value;
}

void gen_01_history_4_setvalue(number val) {
    this->gen_01_history_4_value = val;
}

void gen_01_history_4_reset() {
    this->gen_01_history_4_value = 0;
}

void gen_01_history_4_init() {
    this->gen_01_history_4_value = 0;
}

void gen_01_delay_5_step() {
    this->gen_01_delay_5_reader++;

    if (this->gen_01_delay_5_reader >= (int)(this->gen_01_delay_5_buffer->getSize()))
        this->gen_01_delay_5_reader = 0;
}

number gen_01_delay_5_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        number r = (int)(this->gen_01_delay_5_buffer->getSize()) + this->gen_01_delay_5_reader - ((size > this->gen_01_delay_5__maxdelay ? this->gen_01_delay_5__maxdelay : (size < (this->gen_01_delay_5_reader != this->gen_01_delay_5_writer) ? this->gen_01_delay_5_reader != this->gen_01_delay_5_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_delay_5_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_delay_5_wrap))
        ), this->gen_01_delay_5_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_delay_5_wrap))
        ));
    }

    number r = (int)(this->gen_01_delay_5_buffer->getSize()) + this->gen_01_delay_5_reader - ((size > this->gen_01_delay_5__maxdelay ? this->gen_01_delay_5__maxdelay : (size < (this->gen_01_delay_5_reader != this->gen_01_delay_5_writer) ? this->gen_01_delay_5_reader != this->gen_01_delay_5_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_delay_5_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_delay_5_wrap))
    );
}

void gen_01_delay_5_write(number v) {
    this->gen_01_delay_5_writer = this->gen_01_delay_5_reader;
    this->gen_01_delay_5_buffer[(Index)this->gen_01_delay_5_writer] = v;
}

number gen_01_delay_5_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_delay_5__maxdelay : size);
    number val = this->gen_01_delay_5_read(effectiveSize, 0);
    this->gen_01_delay_5_write(v);
    this->gen_01_delay_5_step();
    return val;
}

array<Index, 2> gen_01_delay_5_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_delay_5_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_delay_5_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_delay_5_init() {
    auto result = this->gen_01_delay_5_calcSizeInSamples();
    this->gen_01_delay_5__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_delay_5_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_delay_5_wrap = requestedSizeInSamples - 1;
}

void gen_01_delay_5_clear() {
    this->gen_01_delay_5_buffer->setZero();
}

void gen_01_delay_5_reset() {
    auto result = this->gen_01_delay_5_calcSizeInSamples();
    this->gen_01_delay_5__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_delay_5_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_delay_5_buffer);
    this->gen_01_delay_5_wrap = this->gen_01_delay_5_buffer->getSize() - 1;
    this->gen_01_delay_5_clear();

    if (this->gen_01_delay_5_reader >= this->gen_01_delay_5__maxdelay || this->gen_01_delay_5_writer >= this->gen_01_delay_5__maxdelay) {
        this->gen_01_delay_5_reader = 0;
        this->gen_01_delay_5_writer = 0;
    }
}

void gen_01_delay_5_dspsetup() {
    this->gen_01_delay_5_reset();
}

number gen_01_delay_5_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return 88200;
}

number gen_01_delay_5_size() {
    return this->gen_01_delay_5__maxdelay;
}

number gen_01_history_6_getvalue() {
    return this->gen_01_history_6_value;
}

void gen_01_history_6_setvalue(number val) {
    this->gen_01_history_6_value = val;
}

void gen_01_history_6_reset() {
    this->gen_01_history_6_value = 0;
}

void gen_01_history_6_init() {
    this->gen_01_history_6_value = 0;
}

void gen_01_DL1_step() {
    this->gen_01_DL1_reader++;

    if (this->gen_01_DL1_reader >= (int)(this->gen_01_DL1_buffer->getSize()))
        this->gen_01_DL1_reader = 0;
}

number gen_01_DL1_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_DL1_buffer->getSize()) + this->gen_01_DL1_reader - ((size > this->gen_01_DL1__maxdelay ? this->gen_01_DL1__maxdelay : (size < (1 + this->gen_01_DL1_reader != this->gen_01_DL1_writer) ? 1 + this->gen_01_DL1_reader != this->gen_01_DL1_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(
                frac,
                this->gen_01_DL1_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL1_wrap))),
                this->gen_01_DL1_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL1_wrap))),
                this->gen_01_DL1_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL1_wrap))),
                this->gen_01_DL1_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL1_wrap)))
            );
        }
    }

    number r = (int)(this->gen_01_DL1_buffer->getSize()) + this->gen_01_DL1_reader - ((size > this->gen_01_DL1__maxdelay ? this->gen_01_DL1__maxdelay : (size < (this->gen_01_DL1_reader != this->gen_01_DL1_writer) ? this->gen_01_DL1_reader != this->gen_01_DL1_writer : size)));
    long index1 = (long)(rnbo_floor(r));
    return this->gen_01_DL1_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL1_wrap)));
}

void gen_01_DL1_write(number v) {
    this->gen_01_DL1_writer = this->gen_01_DL1_reader;
    this->gen_01_DL1_buffer[(Index)this->gen_01_DL1_writer] = v;
}

number gen_01_DL1_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_DL1__maxdelay : size);
    number val = this->gen_01_DL1_read(effectiveSize, 0);
    this->gen_01_DL1_write(v);
    this->gen_01_DL1_step();
    return val;
}

array<Index, 2> gen_01_DL1_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_DL1_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_DL1_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_DL1_init() {
    auto result = this->gen_01_DL1_calcSizeInSamples();
    this->gen_01_DL1__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL1_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_DL1_wrap = requestedSizeInSamples - 1;
}

void gen_01_DL1_clear() {
    this->gen_01_DL1_buffer->setZero();
}

void gen_01_DL1_reset() {
    auto result = this->gen_01_DL1_calcSizeInSamples();
    this->gen_01_DL1__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL1_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_DL1_buffer);
    this->gen_01_DL1_wrap = this->gen_01_DL1_buffer->getSize() - 1;
    this->gen_01_DL1_clear();

    if (this->gen_01_DL1_reader >= this->gen_01_DL1__maxdelay || this->gen_01_DL1_writer >= this->gen_01_DL1__maxdelay) {
        this->gen_01_DL1_reader = 0;
        this->gen_01_DL1_writer = 0;
    }
}

void gen_01_DL1_dspsetup() {
    this->gen_01_DL1_reset();
}

number gen_01_DL1_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_DL1_size() {
    return this->gen_01_DL1__maxdelay;
}

void gen_01_DL2_step() {
    this->gen_01_DL2_reader++;

    if (this->gen_01_DL2_reader >= (int)(this->gen_01_DL2_buffer->getSize()))
        this->gen_01_DL2_reader = 0;
}

number gen_01_DL2_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_DL2_buffer->getSize()) + this->gen_01_DL2_reader - ((size > this->gen_01_DL2__maxdelay ? this->gen_01_DL2__maxdelay : (size < (1 + this->gen_01_DL2_reader != this->gen_01_DL2_writer) ? 1 + this->gen_01_DL2_reader != this->gen_01_DL2_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(
                frac,
                this->gen_01_DL2_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL2_wrap))),
                this->gen_01_DL2_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL2_wrap))),
                this->gen_01_DL2_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL2_wrap))),
                this->gen_01_DL2_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL2_wrap)))
            );
        }
    }

    number r = (int)(this->gen_01_DL2_buffer->getSize()) + this->gen_01_DL2_reader - ((size > this->gen_01_DL2__maxdelay ? this->gen_01_DL2__maxdelay : (size < (this->gen_01_DL2_reader != this->gen_01_DL2_writer) ? this->gen_01_DL2_reader != this->gen_01_DL2_writer : size)));
    long index1 = (long)(rnbo_floor(r));
    return this->gen_01_DL2_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL2_wrap)));
}

void gen_01_DL2_write(number v) {
    this->gen_01_DL2_writer = this->gen_01_DL2_reader;
    this->gen_01_DL2_buffer[(Index)this->gen_01_DL2_writer] = v;
}

number gen_01_DL2_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_DL2__maxdelay : size);
    number val = this->gen_01_DL2_read(effectiveSize, 0);
    this->gen_01_DL2_write(v);
    this->gen_01_DL2_step();
    return val;
}

array<Index, 2> gen_01_DL2_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_DL2_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_DL2_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_DL2_init() {
    auto result = this->gen_01_DL2_calcSizeInSamples();
    this->gen_01_DL2__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL2_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_DL2_wrap = requestedSizeInSamples - 1;
}

void gen_01_DL2_clear() {
    this->gen_01_DL2_buffer->setZero();
}

void gen_01_DL2_reset() {
    auto result = this->gen_01_DL2_calcSizeInSamples();
    this->gen_01_DL2__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL2_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_DL2_buffer);
    this->gen_01_DL2_wrap = this->gen_01_DL2_buffer->getSize() - 1;
    this->gen_01_DL2_clear();

    if (this->gen_01_DL2_reader >= this->gen_01_DL2__maxdelay || this->gen_01_DL2_writer >= this->gen_01_DL2__maxdelay) {
        this->gen_01_DL2_reader = 0;
        this->gen_01_DL2_writer = 0;
    }
}

void gen_01_DL2_dspsetup() {
    this->gen_01_DL2_reset();
}

number gen_01_DL2_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_DL2_size() {
    return this->gen_01_DL2__maxdelay;
}

void gen_01_DL3_step() {
    this->gen_01_DL3_reader++;

    if (this->gen_01_DL3_reader >= (int)(this->gen_01_DL3_buffer->getSize()))
        this->gen_01_DL3_reader = 0;
}

number gen_01_DL3_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_DL3_buffer->getSize()) + this->gen_01_DL3_reader - ((size > this->gen_01_DL3__maxdelay ? this->gen_01_DL3__maxdelay : (size < (1 + this->gen_01_DL3_reader != this->gen_01_DL3_writer) ? 1 + this->gen_01_DL3_reader != this->gen_01_DL3_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(
                frac,
                this->gen_01_DL3_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL3_wrap))),
                this->gen_01_DL3_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL3_wrap))),
                this->gen_01_DL3_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL3_wrap))),
                this->gen_01_DL3_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL3_wrap)))
            );
        }
    }

    number r = (int)(this->gen_01_DL3_buffer->getSize()) + this->gen_01_DL3_reader - ((size > this->gen_01_DL3__maxdelay ? this->gen_01_DL3__maxdelay : (size < (this->gen_01_DL3_reader != this->gen_01_DL3_writer) ? this->gen_01_DL3_reader != this->gen_01_DL3_writer : size)));
    long index1 = (long)(rnbo_floor(r));
    return this->gen_01_DL3_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL3_wrap)));
}

void gen_01_DL3_write(number v) {
    this->gen_01_DL3_writer = this->gen_01_DL3_reader;
    this->gen_01_DL3_buffer[(Index)this->gen_01_DL3_writer] = v;
}

number gen_01_DL3_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_DL3__maxdelay : size);
    number val = this->gen_01_DL3_read(effectiveSize, 0);
    this->gen_01_DL3_write(v);
    this->gen_01_DL3_step();
    return val;
}

array<Index, 2> gen_01_DL3_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_DL3_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_DL3_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_DL3_init() {
    auto result = this->gen_01_DL3_calcSizeInSamples();
    this->gen_01_DL3__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL3_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_DL3_wrap = requestedSizeInSamples - 1;
}

void gen_01_DL3_clear() {
    this->gen_01_DL3_buffer->setZero();
}

void gen_01_DL3_reset() {
    auto result = this->gen_01_DL3_calcSizeInSamples();
    this->gen_01_DL3__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL3_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_DL3_buffer);
    this->gen_01_DL3_wrap = this->gen_01_DL3_buffer->getSize() - 1;
    this->gen_01_DL3_clear();

    if (this->gen_01_DL3_reader >= this->gen_01_DL3__maxdelay || this->gen_01_DL3_writer >= this->gen_01_DL3__maxdelay) {
        this->gen_01_DL3_reader = 0;
        this->gen_01_DL3_writer = 0;
    }
}

void gen_01_DL3_dspsetup() {
    this->gen_01_DL3_reset();
}

number gen_01_DL3_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_DL3_size() {
    return this->gen_01_DL3__maxdelay;
}

void gen_01_DL4_step() {
    this->gen_01_DL4_reader++;

    if (this->gen_01_DL4_reader >= (int)(this->gen_01_DL4_buffer->getSize()))
        this->gen_01_DL4_reader = 0;
}

number gen_01_DL4_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_DL4_buffer->getSize()) + this->gen_01_DL4_reader - ((size > this->gen_01_DL4__maxdelay ? this->gen_01_DL4__maxdelay : (size < (1 + this->gen_01_DL4_reader != this->gen_01_DL4_writer) ? 1 + this->gen_01_DL4_reader != this->gen_01_DL4_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(
                frac,
                this->gen_01_DL4_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL4_wrap))),
                this->gen_01_DL4_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL4_wrap))),
                this->gen_01_DL4_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL4_wrap))),
                this->gen_01_DL4_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL4_wrap)))
            );
        }
    }

    number r = (int)(this->gen_01_DL4_buffer->getSize()) + this->gen_01_DL4_reader - ((size > this->gen_01_DL4__maxdelay ? this->gen_01_DL4__maxdelay : (size < (this->gen_01_DL4_reader != this->gen_01_DL4_writer) ? this->gen_01_DL4_reader != this->gen_01_DL4_writer : size)));
    long index1 = (long)(rnbo_floor(r));
    return this->gen_01_DL4_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL4_wrap)));
}

void gen_01_DL4_write(number v) {
    this->gen_01_DL4_writer = this->gen_01_DL4_reader;
    this->gen_01_DL4_buffer[(Index)this->gen_01_DL4_writer] = v;
}

number gen_01_DL4_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_DL4__maxdelay : size);
    number val = this->gen_01_DL4_read(effectiveSize, 0);
    this->gen_01_DL4_write(v);
    this->gen_01_DL4_step();
    return val;
}

array<Index, 2> gen_01_DL4_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_DL4_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_DL4_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_DL4_init() {
    auto result = this->gen_01_DL4_calcSizeInSamples();
    this->gen_01_DL4__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL4_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_DL4_wrap = requestedSizeInSamples - 1;
}

void gen_01_DL4_clear() {
    this->gen_01_DL4_buffer->setZero();
}

void gen_01_DL4_reset() {
    auto result = this->gen_01_DL4_calcSizeInSamples();
    this->gen_01_DL4__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL4_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_DL4_buffer);
    this->gen_01_DL4_wrap = this->gen_01_DL4_buffer->getSize() - 1;
    this->gen_01_DL4_clear();

    if (this->gen_01_DL4_reader >= this->gen_01_DL4__maxdelay || this->gen_01_DL4_writer >= this->gen_01_DL4__maxdelay) {
        this->gen_01_DL4_reader = 0;
        this->gen_01_DL4_writer = 0;
    }
}

void gen_01_DL4_dspsetup() {
    this->gen_01_DL4_reset();
}

number gen_01_DL4_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_DL4_size() {
    return this->gen_01_DL4__maxdelay;
}

void gen_01_DL5_step() {
    this->gen_01_DL5_reader++;

    if (this->gen_01_DL5_reader >= (int)(this->gen_01_DL5_buffer->getSize()))
        this->gen_01_DL5_reader = 0;
}

number gen_01_DL5_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_DL5_buffer->getSize()) + this->gen_01_DL5_reader - ((size > this->gen_01_DL5__maxdelay ? this->gen_01_DL5__maxdelay : (size < (1 + this->gen_01_DL5_reader != this->gen_01_DL5_writer) ? 1 + this->gen_01_DL5_reader != this->gen_01_DL5_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(
                frac,
                this->gen_01_DL5_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL5_wrap))),
                this->gen_01_DL5_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL5_wrap))),
                this->gen_01_DL5_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL5_wrap))),
                this->gen_01_DL5_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL5_wrap)))
            );
        }
    }

    number r = (int)(this->gen_01_DL5_buffer->getSize()) + this->gen_01_DL5_reader - ((size > this->gen_01_DL5__maxdelay ? this->gen_01_DL5__maxdelay : (size < (this->gen_01_DL5_reader != this->gen_01_DL5_writer) ? this->gen_01_DL5_reader != this->gen_01_DL5_writer : size)));
    long index1 = (long)(rnbo_floor(r));
    return this->gen_01_DL5_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL5_wrap)));
}

void gen_01_DL5_write(number v) {
    this->gen_01_DL5_writer = this->gen_01_DL5_reader;
    this->gen_01_DL5_buffer[(Index)this->gen_01_DL5_writer] = v;
}

number gen_01_DL5_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_DL5__maxdelay : size);
    number val = this->gen_01_DL5_read(effectiveSize, 0);
    this->gen_01_DL5_write(v);
    this->gen_01_DL5_step();
    return val;
}

array<Index, 2> gen_01_DL5_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_DL5_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_DL5_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_DL5_init() {
    auto result = this->gen_01_DL5_calcSizeInSamples();
    this->gen_01_DL5__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL5_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_DL5_wrap = requestedSizeInSamples - 1;
}

void gen_01_DL5_clear() {
    this->gen_01_DL5_buffer->setZero();
}

void gen_01_DL5_reset() {
    auto result = this->gen_01_DL5_calcSizeInSamples();
    this->gen_01_DL5__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL5_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_DL5_buffer);
    this->gen_01_DL5_wrap = this->gen_01_DL5_buffer->getSize() - 1;
    this->gen_01_DL5_clear();

    if (this->gen_01_DL5_reader >= this->gen_01_DL5__maxdelay || this->gen_01_DL5_writer >= this->gen_01_DL5__maxdelay) {
        this->gen_01_DL5_reader = 0;
        this->gen_01_DL5_writer = 0;
    }
}

void gen_01_DL5_dspsetup() {
    this->gen_01_DL5_reset();
}

number gen_01_DL5_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_DL5_size() {
    return this->gen_01_DL5__maxdelay;
}

void gen_01_DL6_step() {
    this->gen_01_DL6_reader++;

    if (this->gen_01_DL6_reader >= (int)(this->gen_01_DL6_buffer->getSize()))
        this->gen_01_DL6_reader = 0;
}

number gen_01_DL6_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_DL6_buffer->getSize()) + this->gen_01_DL6_reader - ((size > this->gen_01_DL6__maxdelay ? this->gen_01_DL6__maxdelay : (size < (1 + this->gen_01_DL6_reader != this->gen_01_DL6_writer) ? 1 + this->gen_01_DL6_reader != this->gen_01_DL6_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(
                frac,
                this->gen_01_DL6_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL6_wrap))),
                this->gen_01_DL6_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL6_wrap))),
                this->gen_01_DL6_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL6_wrap))),
                this->gen_01_DL6_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL6_wrap)))
            );
        }
    }

    number r = (int)(this->gen_01_DL6_buffer->getSize()) + this->gen_01_DL6_reader - ((size > this->gen_01_DL6__maxdelay ? this->gen_01_DL6__maxdelay : (size < (this->gen_01_DL6_reader != this->gen_01_DL6_writer) ? this->gen_01_DL6_reader != this->gen_01_DL6_writer : size)));
    long index1 = (long)(rnbo_floor(r));
    return this->gen_01_DL6_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL6_wrap)));
}

void gen_01_DL6_write(number v) {
    this->gen_01_DL6_writer = this->gen_01_DL6_reader;
    this->gen_01_DL6_buffer[(Index)this->gen_01_DL6_writer] = v;
}

number gen_01_DL6_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_DL6__maxdelay : size);
    number val = this->gen_01_DL6_read(effectiveSize, 0);
    this->gen_01_DL6_write(v);
    this->gen_01_DL6_step();
    return val;
}

array<Index, 2> gen_01_DL6_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_DL6_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_DL6_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_DL6_init() {
    auto result = this->gen_01_DL6_calcSizeInSamples();
    this->gen_01_DL6__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL6_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_DL6_wrap = requestedSizeInSamples - 1;
}

void gen_01_DL6_clear() {
    this->gen_01_DL6_buffer->setZero();
}

void gen_01_DL6_reset() {
    auto result = this->gen_01_DL6_calcSizeInSamples();
    this->gen_01_DL6__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL6_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_DL6_buffer);
    this->gen_01_DL6_wrap = this->gen_01_DL6_buffer->getSize() - 1;
    this->gen_01_DL6_clear();

    if (this->gen_01_DL6_reader >= this->gen_01_DL6__maxdelay || this->gen_01_DL6_writer >= this->gen_01_DL6__maxdelay) {
        this->gen_01_DL6_reader = 0;
        this->gen_01_DL6_writer = 0;
    }
}

void gen_01_DL6_dspsetup() {
    this->gen_01_DL6_reset();
}

number gen_01_DL6_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_DL6_size() {
    return this->gen_01_DL6__maxdelay;
}

void gen_01_DL7_step() {
    this->gen_01_DL7_reader++;

    if (this->gen_01_DL7_reader >= (int)(this->gen_01_DL7_buffer->getSize()))
        this->gen_01_DL7_reader = 0;
}

number gen_01_DL7_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_DL7_buffer->getSize()) + this->gen_01_DL7_reader - ((size > this->gen_01_DL7__maxdelay ? this->gen_01_DL7__maxdelay : (size < (1 + this->gen_01_DL7_reader != this->gen_01_DL7_writer) ? 1 + this->gen_01_DL7_reader != this->gen_01_DL7_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(
                frac,
                this->gen_01_DL7_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL7_wrap))),
                this->gen_01_DL7_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL7_wrap))),
                this->gen_01_DL7_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL7_wrap))),
                this->gen_01_DL7_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL7_wrap)))
            );
        }
    }

    number r = (int)(this->gen_01_DL7_buffer->getSize()) + this->gen_01_DL7_reader - ((size > this->gen_01_DL7__maxdelay ? this->gen_01_DL7__maxdelay : (size < (this->gen_01_DL7_reader != this->gen_01_DL7_writer) ? this->gen_01_DL7_reader != this->gen_01_DL7_writer : size)));
    long index1 = (long)(rnbo_floor(r));
    return this->gen_01_DL7_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL7_wrap)));
}

void gen_01_DL7_write(number v) {
    this->gen_01_DL7_writer = this->gen_01_DL7_reader;
    this->gen_01_DL7_buffer[(Index)this->gen_01_DL7_writer] = v;
}

number gen_01_DL7_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_DL7__maxdelay : size);
    number val = this->gen_01_DL7_read(effectiveSize, 0);
    this->gen_01_DL7_write(v);
    this->gen_01_DL7_step();
    return val;
}

array<Index, 2> gen_01_DL7_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_DL7_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_DL7_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_DL7_init() {
    auto result = this->gen_01_DL7_calcSizeInSamples();
    this->gen_01_DL7__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL7_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_DL7_wrap = requestedSizeInSamples - 1;
}

void gen_01_DL7_clear() {
    this->gen_01_DL7_buffer->setZero();
}

void gen_01_DL7_reset() {
    auto result = this->gen_01_DL7_calcSizeInSamples();
    this->gen_01_DL7__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL7_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_DL7_buffer);
    this->gen_01_DL7_wrap = this->gen_01_DL7_buffer->getSize() - 1;
    this->gen_01_DL7_clear();

    if (this->gen_01_DL7_reader >= this->gen_01_DL7__maxdelay || this->gen_01_DL7_writer >= this->gen_01_DL7__maxdelay) {
        this->gen_01_DL7_reader = 0;
        this->gen_01_DL7_writer = 0;
    }
}

void gen_01_DL7_dspsetup() {
    this->gen_01_DL7_reset();
}

number gen_01_DL7_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_DL7_size() {
    return this->gen_01_DL7__maxdelay;
}

void gen_01_DL8_step() {
    this->gen_01_DL8_reader++;

    if (this->gen_01_DL8_reader >= (int)(this->gen_01_DL8_buffer->getSize()))
        this->gen_01_DL8_reader = 0;
}

number gen_01_DL8_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_DL8_buffer->getSize()) + this->gen_01_DL8_reader - ((size > this->gen_01_DL8__maxdelay ? this->gen_01_DL8__maxdelay : (size < (1 + this->gen_01_DL8_reader != this->gen_01_DL8_writer) ? 1 + this->gen_01_DL8_reader != this->gen_01_DL8_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(
                frac,
                this->gen_01_DL8_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL8_wrap))),
                this->gen_01_DL8_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL8_wrap))),
                this->gen_01_DL8_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL8_wrap))),
                this->gen_01_DL8_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL8_wrap)))
            );
        }
    }

    number r = (int)(this->gen_01_DL8_buffer->getSize()) + this->gen_01_DL8_reader - ((size > this->gen_01_DL8__maxdelay ? this->gen_01_DL8__maxdelay : (size < (this->gen_01_DL8_reader != this->gen_01_DL8_writer) ? this->gen_01_DL8_reader != this->gen_01_DL8_writer : size)));
    long index1 = (long)(rnbo_floor(r));
    return this->gen_01_DL8_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL8_wrap)));
}

void gen_01_DL8_write(number v) {
    this->gen_01_DL8_writer = this->gen_01_DL8_reader;
    this->gen_01_DL8_buffer[(Index)this->gen_01_DL8_writer] = v;
}

number gen_01_DL8_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_DL8__maxdelay : size);
    number val = this->gen_01_DL8_read(effectiveSize, 0);
    this->gen_01_DL8_write(v);
    this->gen_01_DL8_step();
    return val;
}

array<Index, 2> gen_01_DL8_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_DL8_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_DL8_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_DL8_init() {
    auto result = this->gen_01_DL8_calcSizeInSamples();
    this->gen_01_DL8__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL8_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_DL8_wrap = requestedSizeInSamples - 1;
}

void gen_01_DL8_clear() {
    this->gen_01_DL8_buffer->setZero();
}

void gen_01_DL8_reset() {
    auto result = this->gen_01_DL8_calcSizeInSamples();
    this->gen_01_DL8__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL8_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_DL8_buffer);
    this->gen_01_DL8_wrap = this->gen_01_DL8_buffer->getSize() - 1;
    this->gen_01_DL8_clear();

    if (this->gen_01_DL8_reader >= this->gen_01_DL8__maxdelay || this->gen_01_DL8_writer >= this->gen_01_DL8__maxdelay) {
        this->gen_01_DL8_reader = 0;
        this->gen_01_DL8_writer = 0;
    }
}

void gen_01_DL8_dspsetup() {
    this->gen_01_DL8_reset();
}

number gen_01_DL8_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_DL8_size() {
    return this->gen_01_DL8__maxdelay;
}

void gen_01_DL9_step() {
    this->gen_01_DL9_reader++;

    if (this->gen_01_DL9_reader >= (int)(this->gen_01_DL9_buffer->getSize()))
        this->gen_01_DL9_reader = 0;
}

number gen_01_DL9_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_DL9_buffer->getSize()) + this->gen_01_DL9_reader - ((size > this->gen_01_DL9__maxdelay ? this->gen_01_DL9__maxdelay : (size < (1 + this->gen_01_DL9_reader != this->gen_01_DL9_writer) ? 1 + this->gen_01_DL9_reader != this->gen_01_DL9_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(
                frac,
                this->gen_01_DL9_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL9_wrap))),
                this->gen_01_DL9_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL9_wrap))),
                this->gen_01_DL9_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL9_wrap))),
                this->gen_01_DL9_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL9_wrap)))
            );
        }
    }

    number r = (int)(this->gen_01_DL9_buffer->getSize()) + this->gen_01_DL9_reader - ((size > this->gen_01_DL9__maxdelay ? this->gen_01_DL9__maxdelay : (size < (this->gen_01_DL9_reader != this->gen_01_DL9_writer) ? this->gen_01_DL9_reader != this->gen_01_DL9_writer : size)));
    long index1 = (long)(rnbo_floor(r));
    return this->gen_01_DL9_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL9_wrap)));
}

void gen_01_DL9_write(number v) {
    this->gen_01_DL9_writer = this->gen_01_DL9_reader;
    this->gen_01_DL9_buffer[(Index)this->gen_01_DL9_writer] = v;
}

number gen_01_DL9_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_DL9__maxdelay : size);
    number val = this->gen_01_DL9_read(effectiveSize, 0);
    this->gen_01_DL9_write(v);
    this->gen_01_DL9_step();
    return val;
}

array<Index, 2> gen_01_DL9_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_DL9_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_DL9_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_DL9_init() {
    auto result = this->gen_01_DL9_calcSizeInSamples();
    this->gen_01_DL9__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL9_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_DL9_wrap = requestedSizeInSamples - 1;
}

void gen_01_DL9_clear() {
    this->gen_01_DL9_buffer->setZero();
}

void gen_01_DL9_reset() {
    auto result = this->gen_01_DL9_calcSizeInSamples();
    this->gen_01_DL9__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL9_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_DL9_buffer);
    this->gen_01_DL9_wrap = this->gen_01_DL9_buffer->getSize() - 1;
    this->gen_01_DL9_clear();

    if (this->gen_01_DL9_reader >= this->gen_01_DL9__maxdelay || this->gen_01_DL9_writer >= this->gen_01_DL9__maxdelay) {
        this->gen_01_DL9_reader = 0;
        this->gen_01_DL9_writer = 0;
    }
}

void gen_01_DL9_dspsetup() {
    this->gen_01_DL9_reset();
}

number gen_01_DL9_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_DL9_size() {
    return this->gen_01_DL9__maxdelay;
}

void gen_01_DL10_step() {
    this->gen_01_DL10_reader++;

    if (this->gen_01_DL10_reader >= (int)(this->gen_01_DL10_buffer->getSize()))
        this->gen_01_DL10_reader = 0;
}

number gen_01_DL10_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_DL10_buffer->getSize()) + this->gen_01_DL10_reader - ((size > this->gen_01_DL10__maxdelay ? this->gen_01_DL10__maxdelay : (size < (1 + this->gen_01_DL10_reader != this->gen_01_DL10_writer) ? 1 + this->gen_01_DL10_reader != this->gen_01_DL10_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_01_DL10_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL10_wrap))
            ), this->gen_01_DL10_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL10_wrap))
            ), this->gen_01_DL10_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL10_wrap))
            ), this->gen_01_DL10_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL10_wrap))
            ));
        }
    }

    number r = (int)(this->gen_01_DL10_buffer->getSize()) + this->gen_01_DL10_reader - ((size > this->gen_01_DL10__maxdelay ? this->gen_01_DL10__maxdelay : (size < (this->gen_01_DL10_reader != this->gen_01_DL10_writer) ? this->gen_01_DL10_reader != this->gen_01_DL10_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_DL10_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL10_wrap))
    );
}

void gen_01_DL10_write(number v) {
    this->gen_01_DL10_writer = this->gen_01_DL10_reader;
    this->gen_01_DL10_buffer[(Index)this->gen_01_DL10_writer] = v;
}

number gen_01_DL10_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_DL10__maxdelay : size);
    number val = this->gen_01_DL10_read(effectiveSize, 0);
    this->gen_01_DL10_write(v);
    this->gen_01_DL10_step();
    return val;
}

array<Index, 2> gen_01_DL10_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_DL10_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_DL10_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_DL10_init() {
    auto result = this->gen_01_DL10_calcSizeInSamples();
    this->gen_01_DL10__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL10_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_DL10_wrap = requestedSizeInSamples - 1;
}

void gen_01_DL10_clear() {
    this->gen_01_DL10_buffer->setZero();
}

void gen_01_DL10_reset() {
    auto result = this->gen_01_DL10_calcSizeInSamples();
    this->gen_01_DL10__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL10_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_DL10_buffer);
    this->gen_01_DL10_wrap = this->gen_01_DL10_buffer->getSize() - 1;
    this->gen_01_DL10_clear();

    if (this->gen_01_DL10_reader >= this->gen_01_DL10__maxdelay || this->gen_01_DL10_writer >= this->gen_01_DL10__maxdelay) {
        this->gen_01_DL10_reader = 0;
        this->gen_01_DL10_writer = 0;
    }
}

void gen_01_DL10_dspsetup() {
    this->gen_01_DL10_reset();
}

number gen_01_DL10_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_DL10_size() {
    return this->gen_01_DL10__maxdelay;
}

void gen_01_DL11_step() {
    this->gen_01_DL11_reader++;

    if (this->gen_01_DL11_reader >= (int)(this->gen_01_DL11_buffer->getSize()))
        this->gen_01_DL11_reader = 0;
}

number gen_01_DL11_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_DL11_buffer->getSize()) + this->gen_01_DL11_reader - ((size > this->gen_01_DL11__maxdelay ? this->gen_01_DL11__maxdelay : (size < (1 + this->gen_01_DL11_reader != this->gen_01_DL11_writer) ? 1 + this->gen_01_DL11_reader != this->gen_01_DL11_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_01_DL11_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL11_wrap))
            ), this->gen_01_DL11_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL11_wrap))
            ), this->gen_01_DL11_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL11_wrap))
            ), this->gen_01_DL11_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL11_wrap))
            ));
        }
    }

    number r = (int)(this->gen_01_DL11_buffer->getSize()) + this->gen_01_DL11_reader - ((size > this->gen_01_DL11__maxdelay ? this->gen_01_DL11__maxdelay : (size < (this->gen_01_DL11_reader != this->gen_01_DL11_writer) ? this->gen_01_DL11_reader != this->gen_01_DL11_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_DL11_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL11_wrap))
    );
}

void gen_01_DL11_write(number v) {
    this->gen_01_DL11_writer = this->gen_01_DL11_reader;
    this->gen_01_DL11_buffer[(Index)this->gen_01_DL11_writer] = v;
}

number gen_01_DL11_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_DL11__maxdelay : size);
    number val = this->gen_01_DL11_read(effectiveSize, 0);
    this->gen_01_DL11_write(v);
    this->gen_01_DL11_step();
    return val;
}

array<Index, 2> gen_01_DL11_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_DL11_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_DL11_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_DL11_init() {
    auto result = this->gen_01_DL11_calcSizeInSamples();
    this->gen_01_DL11__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL11_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_DL11_wrap = requestedSizeInSamples - 1;
}

void gen_01_DL11_clear() {
    this->gen_01_DL11_buffer->setZero();
}

void gen_01_DL11_reset() {
    auto result = this->gen_01_DL11_calcSizeInSamples();
    this->gen_01_DL11__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL11_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_DL11_buffer);
    this->gen_01_DL11_wrap = this->gen_01_DL11_buffer->getSize() - 1;
    this->gen_01_DL11_clear();

    if (this->gen_01_DL11_reader >= this->gen_01_DL11__maxdelay || this->gen_01_DL11_writer >= this->gen_01_DL11__maxdelay) {
        this->gen_01_DL11_reader = 0;
        this->gen_01_DL11_writer = 0;
    }
}

void gen_01_DL11_dspsetup() {
    this->gen_01_DL11_reset();
}

number gen_01_DL11_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_DL11_size() {
    return this->gen_01_DL11__maxdelay;
}

void gen_01_DL12_step() {
    this->gen_01_DL12_reader++;

    if (this->gen_01_DL12_reader >= (int)(this->gen_01_DL12_buffer->getSize()))
        this->gen_01_DL12_reader = 0;
}

number gen_01_DL12_read(number size, Int interp) {
    if (interp == 0) {
        number r = (int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL12_wrap))
        ));
    } else if (interp == 1) {
        number r = (int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? 1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->cubicinterp(frac, this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL12_wrap))
        ));
    } else if (interp == 6) {
        number r = (int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? 1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->fastcubicinterp(frac, this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL12_wrap))
        ));
    } else if (interp == 2) {
        number r = (int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? 1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->splineinterp(frac, this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL12_wrap))
        ));
    } else if (interp == 7) {
        number r = (int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? 1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);
        Index index5 = (Index)(index4 + 1);
        Index index6 = (Index)(index5 + 1);

        return this->spline6interp(frac, this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index5 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index6 & (BinOpInt)this->gen_01_DL12_wrap))
        ));
    } else if (interp == 3) {
        number r = (int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);

        return this->cosineinterp(frac, this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL12_wrap))
        ));
    }

    number r = (int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_DL12_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL12_wrap))
    );
}

void gen_01_DL12_write(number v) {
    this->gen_01_DL12_writer = this->gen_01_DL12_reader;
    this->gen_01_DL12_buffer[(Index)this->gen_01_DL12_writer] = v;
}

number gen_01_DL12_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_DL12__maxdelay : size);
    number val = this->gen_01_DL12_read(effectiveSize, 0);
    this->gen_01_DL12_write(v);
    this->gen_01_DL12_step();
    return val;
}

array<Index, 2> gen_01_DL12_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_DL12_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_DL12_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_DL12_init() {
    auto result = this->gen_01_DL12_calcSizeInSamples();
    this->gen_01_DL12__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL12_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_DL12_wrap = requestedSizeInSamples - 1;
}

void gen_01_DL12_clear() {
    this->gen_01_DL12_buffer->setZero();
}

void gen_01_DL12_reset() {
    auto result = this->gen_01_DL12_calcSizeInSamples();
    this->gen_01_DL12__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL12_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_DL12_buffer);
    this->gen_01_DL12_wrap = this->gen_01_DL12_buffer->getSize() - 1;
    this->gen_01_DL12_clear();

    if (this->gen_01_DL12_reader >= this->gen_01_DL12__maxdelay || this->gen_01_DL12_writer >= this->gen_01_DL12__maxdelay) {
        this->gen_01_DL12_reader = 0;
        this->gen_01_DL12_writer = 0;
    }
}

void gen_01_DL12_dspsetup() {
    this->gen_01_DL12_reset();
}

number gen_01_DL12_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_DL12_size() {
    return this->gen_01_DL12__maxdelay;
}

void gen_01_DL13_step() {
    this->gen_01_DL13_reader++;

    if (this->gen_01_DL13_reader >= (int)(this->gen_01_DL13_buffer->getSize()))
        this->gen_01_DL13_reader = 0;
}

number gen_01_DL13_read(number size, Int interp) {
    if (interp == 0) {
        number r = (int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL13_wrap))
        ));
    } else if (interp == 1) {
        number r = (int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? 1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->cubicinterp(frac, this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL13_wrap))
        ));
    } else if (interp == 6) {
        number r = (int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? 1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->fastcubicinterp(frac, this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL13_wrap))
        ));
    } else if (interp == 2) {
        number r = (int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? 1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->splineinterp(frac, this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL13_wrap))
        ));
    } else if (interp == 7) {
        number r = (int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? 1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);
        Index index5 = (Index)(index4 + 1);
        Index index6 = (Index)(index5 + 1);

        return this->spline6interp(frac, this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index5 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index6 & (BinOpInt)this->gen_01_DL13_wrap))
        ));
    } else if (interp == 3) {
        number r = (int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);

        return this->cosineinterp(frac, this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL13_wrap))
        ));
    }

    number r = (int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_DL13_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL13_wrap))
    );
}

void gen_01_DL13_write(number v) {
    this->gen_01_DL13_writer = this->gen_01_DL13_reader;
    this->gen_01_DL13_buffer[(Index)this->gen_01_DL13_writer] = v;
}

number gen_01_DL13_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_DL13__maxdelay : size);
    number val = this->gen_01_DL13_read(effectiveSize, 0);
    this->gen_01_DL13_write(v);
    this->gen_01_DL13_step();
    return val;
}

array<Index, 2> gen_01_DL13_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_DL13_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_DL13_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_DL13_init() {
    auto result = this->gen_01_DL13_calcSizeInSamples();
    this->gen_01_DL13__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL13_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_DL13_wrap = requestedSizeInSamples - 1;
}

void gen_01_DL13_clear() {
    this->gen_01_DL13_buffer->setZero();
}

void gen_01_DL13_reset() {
    auto result = this->gen_01_DL13_calcSizeInSamples();
    this->gen_01_DL13__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_DL13_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_DL13_buffer);
    this->gen_01_DL13_wrap = this->gen_01_DL13_buffer->getSize() - 1;
    this->gen_01_DL13_clear();

    if (this->gen_01_DL13_reader >= this->gen_01_DL13__maxdelay || this->gen_01_DL13_writer >= this->gen_01_DL13__maxdelay) {
        this->gen_01_DL13_reader = 0;
        this->gen_01_DL13_writer = 0;
    }
}

void gen_01_DL13_dspsetup() {
    this->gen_01_DL13_reset();
}

number gen_01_DL13_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_DL13_size() {
    return this->gen_01_DL13__maxdelay;
}

number gen_01_feedback_getvalue() {
    return this->gen_01_feedback_value;
}

void gen_01_feedback_setvalue(number val) {
    this->gen_01_feedback_value = val;
}

void gen_01_feedback_reset() {
    this->gen_01_feedback_value = 0;
}

void gen_01_feedback_init() {
    this->gen_01_feedback_value = 0;
}

number gen_01_filterOutput_getvalue() {
    return this->gen_01_filterOutput_value;
}

void gen_01_filterOutput_setvalue(number val) {
    this->gen_01_filterOutput_value = val;
}

void gen_01_filterOutput_reset() {
    this->gen_01_filterOutput_value = 0;
}

void gen_01_filterOutput_init() {
    this->gen_01_filterOutput_value = 0;
}

number gen_01_history_7_getvalue() {
    return this->gen_01_history_7_value;
}

void gen_01_history_7_setvalue(number val) {
    this->gen_01_history_7_value = val;
}

void gen_01_history_7_reset() {
    this->gen_01_history_7_value = 0;
}

void gen_01_history_7_init() {
    this->gen_01_history_7_value = 0;
}

number gen_01_history_8_getvalue() {
    return this->gen_01_history_8_value;
}

void gen_01_history_8_setvalue(number val) {
    this->gen_01_history_8_value = val;
}

void gen_01_history_8_reset() {
    this->gen_01_history_8_value = 0;
}

void gen_01_history_8_init() {
    this->gen_01_history_8_value = 0;
}

void gen_01_delay_9_step() {
    this->gen_01_delay_9_reader++;

    if (this->gen_01_delay_9_reader >= (int)(this->gen_01_delay_9_buffer->getSize()))
        this->gen_01_delay_9_reader = 0;
}

number gen_01_delay_9_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        number r = (int)(this->gen_01_delay_9_buffer->getSize()) + this->gen_01_delay_9_reader - ((size > this->gen_01_delay_9__maxdelay ? this->gen_01_delay_9__maxdelay : (size < (this->gen_01_delay_9_reader != this->gen_01_delay_9_writer) ? this->gen_01_delay_9_reader != this->gen_01_delay_9_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_delay_9_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_delay_9_wrap))
        ), this->gen_01_delay_9_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_delay_9_wrap))
        ));
    }

    number r = (int)(this->gen_01_delay_9_buffer->getSize()) + this->gen_01_delay_9_reader - ((size > this->gen_01_delay_9__maxdelay ? this->gen_01_delay_9__maxdelay : (size < (this->gen_01_delay_9_reader != this->gen_01_delay_9_writer) ? this->gen_01_delay_9_reader != this->gen_01_delay_9_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_delay_9_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_delay_9_wrap))
    );
}

void gen_01_delay_9_write(number v) {
    this->gen_01_delay_9_writer = this->gen_01_delay_9_reader;
    this->gen_01_delay_9_buffer[(Index)this->gen_01_delay_9_writer] = v;
}

number gen_01_delay_9_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_delay_9__maxdelay : size);
    number val = this->gen_01_delay_9_read(effectiveSize, 0);
    this->gen_01_delay_9_write(v);
    this->gen_01_delay_9_step();
    return val;
}

array<Index, 2> gen_01_delay_9_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_delay_9_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_delay_9_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_delay_9_init() {
    auto result = this->gen_01_delay_9_calcSizeInSamples();
    this->gen_01_delay_9__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_delay_9_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_delay_9_wrap = requestedSizeInSamples - 1;
}

void gen_01_delay_9_clear() {
    this->gen_01_delay_9_buffer->setZero();
}

void gen_01_delay_9_reset() {
    auto result = this->gen_01_delay_9_calcSizeInSamples();
    this->gen_01_delay_9__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_delay_9_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_delay_9_buffer);
    this->gen_01_delay_9_wrap = this->gen_01_delay_9_buffer->getSize() - 1;
    this->gen_01_delay_9_clear();

    if (this->gen_01_delay_9_reader >= this->gen_01_delay_9__maxdelay || this->gen_01_delay_9_writer >= this->gen_01_delay_9__maxdelay) {
        this->gen_01_delay_9_reader = 0;
        this->gen_01_delay_9_writer = 0;
    }
}

void gen_01_delay_9_dspsetup() {
    this->gen_01_delay_9_reset();
}

number gen_01_delay_9_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return 88200;
}

number gen_01_delay_9_size() {
    return this->gen_01_delay_9__maxdelay;
}

number gen_01_history_10_getvalue() {
    return this->gen_01_history_10_value;
}

void gen_01_history_10_setvalue(number val) {
    this->gen_01_history_10_value = val;
}

void gen_01_history_10_reset() {
    this->gen_01_history_10_value = 0;
}

void gen_01_history_10_init() {
    this->gen_01_history_10_value = 0;
}

void gen_01_dlL1_step() {
    this->gen_01_dlL1_reader++;

    if (this->gen_01_dlL1_reader >= (int)(this->gen_01_dlL1_buffer->getSize()))
        this->gen_01_dlL1_reader = 0;
}

number gen_01_dlL1_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_dlL1_buffer->getSize()) + this->gen_01_dlL1_reader - ((size > this->gen_01_dlL1__maxdelay ? this->gen_01_dlL1__maxdelay : (size < (1 + this->gen_01_dlL1_reader != this->gen_01_dlL1_writer) ? 1 + this->gen_01_dlL1_reader != this->gen_01_dlL1_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_01_dlL1_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL1_wrap))
            ), this->gen_01_dlL1_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL1_wrap))
            ), this->gen_01_dlL1_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL1_wrap))
            ), this->gen_01_dlL1_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL1_wrap))
            ));
        }
    }

    number r = (int)(this->gen_01_dlL1_buffer->getSize()) + this->gen_01_dlL1_reader - ((size > this->gen_01_dlL1__maxdelay ? this->gen_01_dlL1__maxdelay : (size < (this->gen_01_dlL1_reader != this->gen_01_dlL1_writer) ? this->gen_01_dlL1_reader != this->gen_01_dlL1_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_dlL1_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL1_wrap))
    );
}

void gen_01_dlL1_write(number v) {
    this->gen_01_dlL1_writer = this->gen_01_dlL1_reader;
    this->gen_01_dlL1_buffer[(Index)this->gen_01_dlL1_writer] = v;
}

number gen_01_dlL1_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_dlL1__maxdelay : size);
    number val = this->gen_01_dlL1_read(effectiveSize, 0);
    this->gen_01_dlL1_write(v);
    this->gen_01_dlL1_step();
    return val;
}

array<Index, 2> gen_01_dlL1_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_dlL1_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_dlL1_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_dlL1_init() {
    auto result = this->gen_01_dlL1_calcSizeInSamples();
    this->gen_01_dlL1__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL1_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_dlL1_wrap = requestedSizeInSamples - 1;
}

void gen_01_dlL1_clear() {
    this->gen_01_dlL1_buffer->setZero();
}

void gen_01_dlL1_reset() {
    auto result = this->gen_01_dlL1_calcSizeInSamples();
    this->gen_01_dlL1__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL1_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_dlL1_buffer);
    this->gen_01_dlL1_wrap = this->gen_01_dlL1_buffer->getSize() - 1;
    this->gen_01_dlL1_clear();

    if (this->gen_01_dlL1_reader >= this->gen_01_dlL1__maxdelay || this->gen_01_dlL1_writer >= this->gen_01_dlL1__maxdelay) {
        this->gen_01_dlL1_reader = 0;
        this->gen_01_dlL1_writer = 0;
    }
}

void gen_01_dlL1_dspsetup() {
    this->gen_01_dlL1_reset();
}

number gen_01_dlL1_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_dlL1_size() {
    return this->gen_01_dlL1__maxdelay;
}

void gen_01_dlL2_step() {
    this->gen_01_dlL2_reader++;

    if (this->gen_01_dlL2_reader >= (int)(this->gen_01_dlL2_buffer->getSize()))
        this->gen_01_dlL2_reader = 0;
}

number gen_01_dlL2_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_dlL2_buffer->getSize()) + this->gen_01_dlL2_reader - ((size > this->gen_01_dlL2__maxdelay ? this->gen_01_dlL2__maxdelay : (size < (1 + this->gen_01_dlL2_reader != this->gen_01_dlL2_writer) ? 1 + this->gen_01_dlL2_reader != this->gen_01_dlL2_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_01_dlL2_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL2_wrap))
            ), this->gen_01_dlL2_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL2_wrap))
            ), this->gen_01_dlL2_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL2_wrap))
            ), this->gen_01_dlL2_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL2_wrap))
            ));
        }
    }

    number r = (int)(this->gen_01_dlL2_buffer->getSize()) + this->gen_01_dlL2_reader - ((size > this->gen_01_dlL2__maxdelay ? this->gen_01_dlL2__maxdelay : (size < (this->gen_01_dlL2_reader != this->gen_01_dlL2_writer) ? this->gen_01_dlL2_reader != this->gen_01_dlL2_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_dlL2_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL2_wrap))
    );
}

void gen_01_dlL2_write(number v) {
    this->gen_01_dlL2_writer = this->gen_01_dlL2_reader;
    this->gen_01_dlL2_buffer[(Index)this->gen_01_dlL2_writer] = v;
}

number gen_01_dlL2_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_dlL2__maxdelay : size);
    number val = this->gen_01_dlL2_read(effectiveSize, 0);
    this->gen_01_dlL2_write(v);
    this->gen_01_dlL2_step();
    return val;
}

array<Index, 2> gen_01_dlL2_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_dlL2_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_dlL2_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_dlL2_init() {
    auto result = this->gen_01_dlL2_calcSizeInSamples();
    this->gen_01_dlL2__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL2_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_dlL2_wrap = requestedSizeInSamples - 1;
}

void gen_01_dlL2_clear() {
    this->gen_01_dlL2_buffer->setZero();
}

void gen_01_dlL2_reset() {
    auto result = this->gen_01_dlL2_calcSizeInSamples();
    this->gen_01_dlL2__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL2_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_dlL2_buffer);
    this->gen_01_dlL2_wrap = this->gen_01_dlL2_buffer->getSize() - 1;
    this->gen_01_dlL2_clear();

    if (this->gen_01_dlL2_reader >= this->gen_01_dlL2__maxdelay || this->gen_01_dlL2_writer >= this->gen_01_dlL2__maxdelay) {
        this->gen_01_dlL2_reader = 0;
        this->gen_01_dlL2_writer = 0;
    }
}

void gen_01_dlL2_dspsetup() {
    this->gen_01_dlL2_reset();
}

number gen_01_dlL2_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_dlL2_size() {
    return this->gen_01_dlL2__maxdelay;
}

void gen_01_dlL3_step() {
    this->gen_01_dlL3_reader++;

    if (this->gen_01_dlL3_reader >= (int)(this->gen_01_dlL3_buffer->getSize()))
        this->gen_01_dlL3_reader = 0;
}

number gen_01_dlL3_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_dlL3_buffer->getSize()) + this->gen_01_dlL3_reader - ((size > this->gen_01_dlL3__maxdelay ? this->gen_01_dlL3__maxdelay : (size < (1 + this->gen_01_dlL3_reader != this->gen_01_dlL3_writer) ? 1 + this->gen_01_dlL3_reader != this->gen_01_dlL3_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_01_dlL3_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL3_wrap))
            ), this->gen_01_dlL3_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL3_wrap))
            ), this->gen_01_dlL3_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL3_wrap))
            ), this->gen_01_dlL3_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL3_wrap))
            ));
        }
    }

    number r = (int)(this->gen_01_dlL3_buffer->getSize()) + this->gen_01_dlL3_reader - ((size > this->gen_01_dlL3__maxdelay ? this->gen_01_dlL3__maxdelay : (size < (this->gen_01_dlL3_reader != this->gen_01_dlL3_writer) ? this->gen_01_dlL3_reader != this->gen_01_dlL3_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_dlL3_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL3_wrap))
    );
}

void gen_01_dlL3_write(number v) {
    this->gen_01_dlL3_writer = this->gen_01_dlL3_reader;
    this->gen_01_dlL3_buffer[(Index)this->gen_01_dlL3_writer] = v;
}

number gen_01_dlL3_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_dlL3__maxdelay : size);
    number val = this->gen_01_dlL3_read(effectiveSize, 0);
    this->gen_01_dlL3_write(v);
    this->gen_01_dlL3_step();
    return val;
}

array<Index, 2> gen_01_dlL3_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_dlL3_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_dlL3_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_dlL3_init() {
    auto result = this->gen_01_dlL3_calcSizeInSamples();
    this->gen_01_dlL3__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL3_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_dlL3_wrap = requestedSizeInSamples - 1;
}

void gen_01_dlL3_clear() {
    this->gen_01_dlL3_buffer->setZero();
}

void gen_01_dlL3_reset() {
    auto result = this->gen_01_dlL3_calcSizeInSamples();
    this->gen_01_dlL3__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL3_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_dlL3_buffer);
    this->gen_01_dlL3_wrap = this->gen_01_dlL3_buffer->getSize() - 1;
    this->gen_01_dlL3_clear();

    if (this->gen_01_dlL3_reader >= this->gen_01_dlL3__maxdelay || this->gen_01_dlL3_writer >= this->gen_01_dlL3__maxdelay) {
        this->gen_01_dlL3_reader = 0;
        this->gen_01_dlL3_writer = 0;
    }
}

void gen_01_dlL3_dspsetup() {
    this->gen_01_dlL3_reset();
}

number gen_01_dlL3_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_dlL3_size() {
    return this->gen_01_dlL3__maxdelay;
}

void gen_01_dlL4_step() {
    this->gen_01_dlL4_reader++;

    if (this->gen_01_dlL4_reader >= (int)(this->gen_01_dlL4_buffer->getSize()))
        this->gen_01_dlL4_reader = 0;
}

number gen_01_dlL4_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_dlL4_buffer->getSize()) + this->gen_01_dlL4_reader - ((size > this->gen_01_dlL4__maxdelay ? this->gen_01_dlL4__maxdelay : (size < (1 + this->gen_01_dlL4_reader != this->gen_01_dlL4_writer) ? 1 + this->gen_01_dlL4_reader != this->gen_01_dlL4_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_01_dlL4_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL4_wrap))
            ), this->gen_01_dlL4_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL4_wrap))
            ), this->gen_01_dlL4_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL4_wrap))
            ), this->gen_01_dlL4_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL4_wrap))
            ));
        }
    }

    number r = (int)(this->gen_01_dlL4_buffer->getSize()) + this->gen_01_dlL4_reader - ((size > this->gen_01_dlL4__maxdelay ? this->gen_01_dlL4__maxdelay : (size < (this->gen_01_dlL4_reader != this->gen_01_dlL4_writer) ? this->gen_01_dlL4_reader != this->gen_01_dlL4_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_dlL4_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL4_wrap))
    );
}

void gen_01_dlL4_write(number v) {
    this->gen_01_dlL4_writer = this->gen_01_dlL4_reader;
    this->gen_01_dlL4_buffer[(Index)this->gen_01_dlL4_writer] = v;
}

number gen_01_dlL4_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_dlL4__maxdelay : size);
    number val = this->gen_01_dlL4_read(effectiveSize, 0);
    this->gen_01_dlL4_write(v);
    this->gen_01_dlL4_step();
    return val;
}

array<Index, 2> gen_01_dlL4_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_dlL4_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_dlL4_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_dlL4_init() {
    auto result = this->gen_01_dlL4_calcSizeInSamples();
    this->gen_01_dlL4__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL4_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_dlL4_wrap = requestedSizeInSamples - 1;
}

void gen_01_dlL4_clear() {
    this->gen_01_dlL4_buffer->setZero();
}

void gen_01_dlL4_reset() {
    auto result = this->gen_01_dlL4_calcSizeInSamples();
    this->gen_01_dlL4__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL4_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_dlL4_buffer);
    this->gen_01_dlL4_wrap = this->gen_01_dlL4_buffer->getSize() - 1;
    this->gen_01_dlL4_clear();

    if (this->gen_01_dlL4_reader >= this->gen_01_dlL4__maxdelay || this->gen_01_dlL4_writer >= this->gen_01_dlL4__maxdelay) {
        this->gen_01_dlL4_reader = 0;
        this->gen_01_dlL4_writer = 0;
    }
}

void gen_01_dlL4_dspsetup() {
    this->gen_01_dlL4_reset();
}

number gen_01_dlL4_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_dlL4_size() {
    return this->gen_01_dlL4__maxdelay;
}

void gen_01_dlL5_step() {
    this->gen_01_dlL5_reader++;

    if (this->gen_01_dlL5_reader >= (int)(this->gen_01_dlL5_buffer->getSize()))
        this->gen_01_dlL5_reader = 0;
}

number gen_01_dlL5_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_dlL5_buffer->getSize()) + this->gen_01_dlL5_reader - ((size > this->gen_01_dlL5__maxdelay ? this->gen_01_dlL5__maxdelay : (size < (1 + this->gen_01_dlL5_reader != this->gen_01_dlL5_writer) ? 1 + this->gen_01_dlL5_reader != this->gen_01_dlL5_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_01_dlL5_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL5_wrap))
            ), this->gen_01_dlL5_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL5_wrap))
            ), this->gen_01_dlL5_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL5_wrap))
            ), this->gen_01_dlL5_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL5_wrap))
            ));
        }
    }

    number r = (int)(this->gen_01_dlL5_buffer->getSize()) + this->gen_01_dlL5_reader - ((size > this->gen_01_dlL5__maxdelay ? this->gen_01_dlL5__maxdelay : (size < (this->gen_01_dlL5_reader != this->gen_01_dlL5_writer) ? this->gen_01_dlL5_reader != this->gen_01_dlL5_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_dlL5_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL5_wrap))
    );
}

void gen_01_dlL5_write(number v) {
    this->gen_01_dlL5_writer = this->gen_01_dlL5_reader;
    this->gen_01_dlL5_buffer[(Index)this->gen_01_dlL5_writer] = v;
}

number gen_01_dlL5_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_dlL5__maxdelay : size);
    number val = this->gen_01_dlL5_read(effectiveSize, 0);
    this->gen_01_dlL5_write(v);
    this->gen_01_dlL5_step();
    return val;
}

array<Index, 2> gen_01_dlL5_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_dlL5_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_dlL5_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_dlL5_init() {
    auto result = this->gen_01_dlL5_calcSizeInSamples();
    this->gen_01_dlL5__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL5_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_dlL5_wrap = requestedSizeInSamples - 1;
}

void gen_01_dlL5_clear() {
    this->gen_01_dlL5_buffer->setZero();
}

void gen_01_dlL5_reset() {
    auto result = this->gen_01_dlL5_calcSizeInSamples();
    this->gen_01_dlL5__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL5_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_dlL5_buffer);
    this->gen_01_dlL5_wrap = this->gen_01_dlL5_buffer->getSize() - 1;
    this->gen_01_dlL5_clear();

    if (this->gen_01_dlL5_reader >= this->gen_01_dlL5__maxdelay || this->gen_01_dlL5_writer >= this->gen_01_dlL5__maxdelay) {
        this->gen_01_dlL5_reader = 0;
        this->gen_01_dlL5_writer = 0;
    }
}

void gen_01_dlL5_dspsetup() {
    this->gen_01_dlL5_reset();
}

number gen_01_dlL5_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_dlL5_size() {
    return this->gen_01_dlL5__maxdelay;
}

void gen_01_dlL6_step() {
    this->gen_01_dlL6_reader++;

    if (this->gen_01_dlL6_reader >= (int)(this->gen_01_dlL6_buffer->getSize()))
        this->gen_01_dlL6_reader = 0;
}

number gen_01_dlL6_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_dlL6_buffer->getSize()) + this->gen_01_dlL6_reader - ((size > this->gen_01_dlL6__maxdelay ? this->gen_01_dlL6__maxdelay : (size < (1 + this->gen_01_dlL6_reader != this->gen_01_dlL6_writer) ? 1 + this->gen_01_dlL6_reader != this->gen_01_dlL6_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_01_dlL6_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL6_wrap))
            ), this->gen_01_dlL6_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL6_wrap))
            ), this->gen_01_dlL6_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL6_wrap))
            ), this->gen_01_dlL6_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL6_wrap))
            ));
        }
    }

    number r = (int)(this->gen_01_dlL6_buffer->getSize()) + this->gen_01_dlL6_reader - ((size > this->gen_01_dlL6__maxdelay ? this->gen_01_dlL6__maxdelay : (size < (this->gen_01_dlL6_reader != this->gen_01_dlL6_writer) ? this->gen_01_dlL6_reader != this->gen_01_dlL6_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_dlL6_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL6_wrap))
    );
}

void gen_01_dlL6_write(number v) {
    this->gen_01_dlL6_writer = this->gen_01_dlL6_reader;
    this->gen_01_dlL6_buffer[(Index)this->gen_01_dlL6_writer] = v;
}

number gen_01_dlL6_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_dlL6__maxdelay : size);
    number val = this->gen_01_dlL6_read(effectiveSize, 0);
    this->gen_01_dlL6_write(v);
    this->gen_01_dlL6_step();
    return val;
}

array<Index, 2> gen_01_dlL6_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_dlL6_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_dlL6_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_dlL6_init() {
    auto result = this->gen_01_dlL6_calcSizeInSamples();
    this->gen_01_dlL6__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL6_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_dlL6_wrap = requestedSizeInSamples - 1;
}

void gen_01_dlL6_clear() {
    this->gen_01_dlL6_buffer->setZero();
}

void gen_01_dlL6_reset() {
    auto result = this->gen_01_dlL6_calcSizeInSamples();
    this->gen_01_dlL6__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL6_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_dlL6_buffer);
    this->gen_01_dlL6_wrap = this->gen_01_dlL6_buffer->getSize() - 1;
    this->gen_01_dlL6_clear();

    if (this->gen_01_dlL6_reader >= this->gen_01_dlL6__maxdelay || this->gen_01_dlL6_writer >= this->gen_01_dlL6__maxdelay) {
        this->gen_01_dlL6_reader = 0;
        this->gen_01_dlL6_writer = 0;
    }
}

void gen_01_dlL6_dspsetup() {
    this->gen_01_dlL6_reset();
}

number gen_01_dlL6_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_dlL6_size() {
    return this->gen_01_dlL6__maxdelay;
}

void gen_01_dlL7_step() {
    this->gen_01_dlL7_reader++;

    if (this->gen_01_dlL7_reader >= (int)(this->gen_01_dlL7_buffer->getSize()))
        this->gen_01_dlL7_reader = 0;
}

number gen_01_dlL7_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_dlL7_buffer->getSize()) + this->gen_01_dlL7_reader - ((size > this->gen_01_dlL7__maxdelay ? this->gen_01_dlL7__maxdelay : (size < (1 + this->gen_01_dlL7_reader != this->gen_01_dlL7_writer) ? 1 + this->gen_01_dlL7_reader != this->gen_01_dlL7_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_01_dlL7_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL7_wrap))
            ), this->gen_01_dlL7_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL7_wrap))
            ), this->gen_01_dlL7_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL7_wrap))
            ), this->gen_01_dlL7_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL7_wrap))
            ));
        }
    }

    number r = (int)(this->gen_01_dlL7_buffer->getSize()) + this->gen_01_dlL7_reader - ((size > this->gen_01_dlL7__maxdelay ? this->gen_01_dlL7__maxdelay : (size < (this->gen_01_dlL7_reader != this->gen_01_dlL7_writer) ? this->gen_01_dlL7_reader != this->gen_01_dlL7_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_dlL7_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL7_wrap))
    );
}

void gen_01_dlL7_write(number v) {
    this->gen_01_dlL7_writer = this->gen_01_dlL7_reader;
    this->gen_01_dlL7_buffer[(Index)this->gen_01_dlL7_writer] = v;
}

number gen_01_dlL7_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_dlL7__maxdelay : size);
    number val = this->gen_01_dlL7_read(effectiveSize, 0);
    this->gen_01_dlL7_write(v);
    this->gen_01_dlL7_step();
    return val;
}

array<Index, 2> gen_01_dlL7_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_dlL7_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_dlL7_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_dlL7_init() {
    auto result = this->gen_01_dlL7_calcSizeInSamples();
    this->gen_01_dlL7__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL7_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_dlL7_wrap = requestedSizeInSamples - 1;
}

void gen_01_dlL7_clear() {
    this->gen_01_dlL7_buffer->setZero();
}

void gen_01_dlL7_reset() {
    auto result = this->gen_01_dlL7_calcSizeInSamples();
    this->gen_01_dlL7__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL7_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_dlL7_buffer);
    this->gen_01_dlL7_wrap = this->gen_01_dlL7_buffer->getSize() - 1;
    this->gen_01_dlL7_clear();

    if (this->gen_01_dlL7_reader >= this->gen_01_dlL7__maxdelay || this->gen_01_dlL7_writer >= this->gen_01_dlL7__maxdelay) {
        this->gen_01_dlL7_reader = 0;
        this->gen_01_dlL7_writer = 0;
    }
}

void gen_01_dlL7_dspsetup() {
    this->gen_01_dlL7_reset();
}

number gen_01_dlL7_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_dlL7_size() {
    return this->gen_01_dlL7__maxdelay;
}

void gen_01_dlL8_step() {
    this->gen_01_dlL8_reader++;

    if (this->gen_01_dlL8_reader >= (int)(this->gen_01_dlL8_buffer->getSize()))
        this->gen_01_dlL8_reader = 0;
}

number gen_01_dlL8_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_dlL8_buffer->getSize()) + this->gen_01_dlL8_reader - ((size > this->gen_01_dlL8__maxdelay ? this->gen_01_dlL8__maxdelay : (size < (1 + this->gen_01_dlL8_reader != this->gen_01_dlL8_writer) ? 1 + this->gen_01_dlL8_reader != this->gen_01_dlL8_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_01_dlL8_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL8_wrap))
            ), this->gen_01_dlL8_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL8_wrap))
            ), this->gen_01_dlL8_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL8_wrap))
            ), this->gen_01_dlL8_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL8_wrap))
            ));
        }
    }

    number r = (int)(this->gen_01_dlL8_buffer->getSize()) + this->gen_01_dlL8_reader - ((size > this->gen_01_dlL8__maxdelay ? this->gen_01_dlL8__maxdelay : (size < (this->gen_01_dlL8_reader != this->gen_01_dlL8_writer) ? this->gen_01_dlL8_reader != this->gen_01_dlL8_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_dlL8_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL8_wrap))
    );
}

void gen_01_dlL8_write(number v) {
    this->gen_01_dlL8_writer = this->gen_01_dlL8_reader;
    this->gen_01_dlL8_buffer[(Index)this->gen_01_dlL8_writer] = v;
}

number gen_01_dlL8_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_dlL8__maxdelay : size);
    number val = this->gen_01_dlL8_read(effectiveSize, 0);
    this->gen_01_dlL8_write(v);
    this->gen_01_dlL8_step();
    return val;
}

array<Index, 2> gen_01_dlL8_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_dlL8_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_dlL8_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_dlL8_init() {
    auto result = this->gen_01_dlL8_calcSizeInSamples();
    this->gen_01_dlL8__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL8_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_dlL8_wrap = requestedSizeInSamples - 1;
}

void gen_01_dlL8_clear() {
    this->gen_01_dlL8_buffer->setZero();
}

void gen_01_dlL8_reset() {
    auto result = this->gen_01_dlL8_calcSizeInSamples();
    this->gen_01_dlL8__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL8_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_dlL8_buffer);
    this->gen_01_dlL8_wrap = this->gen_01_dlL8_buffer->getSize() - 1;
    this->gen_01_dlL8_clear();

    if (this->gen_01_dlL8_reader >= this->gen_01_dlL8__maxdelay || this->gen_01_dlL8_writer >= this->gen_01_dlL8__maxdelay) {
        this->gen_01_dlL8_reader = 0;
        this->gen_01_dlL8_writer = 0;
    }
}

void gen_01_dlL8_dspsetup() {
    this->gen_01_dlL8_reset();
}

number gen_01_dlL8_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_dlL8_size() {
    return this->gen_01_dlL8__maxdelay;
}

void gen_01_dlL9_step() {
    this->gen_01_dlL9_reader++;

    if (this->gen_01_dlL9_reader >= (int)(this->gen_01_dlL9_buffer->getSize()))
        this->gen_01_dlL9_reader = 0;
}

number gen_01_dlL9_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_dlL9_buffer->getSize()) + this->gen_01_dlL9_reader - ((size > this->gen_01_dlL9__maxdelay ? this->gen_01_dlL9__maxdelay : (size < (1 + this->gen_01_dlL9_reader != this->gen_01_dlL9_writer) ? 1 + this->gen_01_dlL9_reader != this->gen_01_dlL9_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_01_dlL9_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL9_wrap))
            ), this->gen_01_dlL9_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL9_wrap))
            ), this->gen_01_dlL9_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL9_wrap))
            ), this->gen_01_dlL9_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL9_wrap))
            ));
        }
    }

    number r = (int)(this->gen_01_dlL9_buffer->getSize()) + this->gen_01_dlL9_reader - ((size > this->gen_01_dlL9__maxdelay ? this->gen_01_dlL9__maxdelay : (size < (this->gen_01_dlL9_reader != this->gen_01_dlL9_writer) ? this->gen_01_dlL9_reader != this->gen_01_dlL9_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_dlL9_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL9_wrap))
    );
}

void gen_01_dlL9_write(number v) {
    this->gen_01_dlL9_writer = this->gen_01_dlL9_reader;
    this->gen_01_dlL9_buffer[(Index)this->gen_01_dlL9_writer] = v;
}

number gen_01_dlL9_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_dlL9__maxdelay : size);
    number val = this->gen_01_dlL9_read(effectiveSize, 0);
    this->gen_01_dlL9_write(v);
    this->gen_01_dlL9_step();
    return val;
}

array<Index, 2> gen_01_dlL9_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_dlL9_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_dlL9_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_dlL9_init() {
    auto result = this->gen_01_dlL9_calcSizeInSamples();
    this->gen_01_dlL9__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL9_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_dlL9_wrap = requestedSizeInSamples - 1;
}

void gen_01_dlL9_clear() {
    this->gen_01_dlL9_buffer->setZero();
}

void gen_01_dlL9_reset() {
    auto result = this->gen_01_dlL9_calcSizeInSamples();
    this->gen_01_dlL9__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL9_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_dlL9_buffer);
    this->gen_01_dlL9_wrap = this->gen_01_dlL9_buffer->getSize() - 1;
    this->gen_01_dlL9_clear();

    if (this->gen_01_dlL9_reader >= this->gen_01_dlL9__maxdelay || this->gen_01_dlL9_writer >= this->gen_01_dlL9__maxdelay) {
        this->gen_01_dlL9_reader = 0;
        this->gen_01_dlL9_writer = 0;
    }
}

void gen_01_dlL9_dspsetup() {
    this->gen_01_dlL9_reset();
}

number gen_01_dlL9_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_dlL9_size() {
    return this->gen_01_dlL9__maxdelay;
}

void gen_01_dlL10_step() {
    this->gen_01_dlL10_reader++;

    if (this->gen_01_dlL10_reader >= (int)(this->gen_01_dlL10_buffer->getSize()))
        this->gen_01_dlL10_reader = 0;
}

number gen_01_dlL10_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_dlL10_buffer->getSize()) + this->gen_01_dlL10_reader - ((size > this->gen_01_dlL10__maxdelay ? this->gen_01_dlL10__maxdelay : (size < (1 + this->gen_01_dlL10_reader != this->gen_01_dlL10_writer) ? 1 + this->gen_01_dlL10_reader != this->gen_01_dlL10_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_01_dlL10_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL10_wrap))
            ), this->gen_01_dlL10_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL10_wrap))
            ), this->gen_01_dlL10_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL10_wrap))
            ), this->gen_01_dlL10_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL10_wrap))
            ));
        }
    }

    number r = (int)(this->gen_01_dlL10_buffer->getSize()) + this->gen_01_dlL10_reader - ((size > this->gen_01_dlL10__maxdelay ? this->gen_01_dlL10__maxdelay : (size < (this->gen_01_dlL10_reader != this->gen_01_dlL10_writer) ? this->gen_01_dlL10_reader != this->gen_01_dlL10_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_dlL10_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL10_wrap))
    );
}

void gen_01_dlL10_write(number v) {
    this->gen_01_dlL10_writer = this->gen_01_dlL10_reader;
    this->gen_01_dlL10_buffer[(Index)this->gen_01_dlL10_writer] = v;
}

number gen_01_dlL10_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_dlL10__maxdelay : size);
    number val = this->gen_01_dlL10_read(effectiveSize, 0);
    this->gen_01_dlL10_write(v);
    this->gen_01_dlL10_step();
    return val;
}

array<Index, 2> gen_01_dlL10_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_dlL10_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_dlL10_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_dlL10_init() {
    auto result = this->gen_01_dlL10_calcSizeInSamples();
    this->gen_01_dlL10__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL10_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_dlL10_wrap = requestedSizeInSamples - 1;
}

void gen_01_dlL10_clear() {
    this->gen_01_dlL10_buffer->setZero();
}

void gen_01_dlL10_reset() {
    auto result = this->gen_01_dlL10_calcSizeInSamples();
    this->gen_01_dlL10__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL10_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_dlL10_buffer);
    this->gen_01_dlL10_wrap = this->gen_01_dlL10_buffer->getSize() - 1;
    this->gen_01_dlL10_clear();

    if (this->gen_01_dlL10_reader >= this->gen_01_dlL10__maxdelay || this->gen_01_dlL10_writer >= this->gen_01_dlL10__maxdelay) {
        this->gen_01_dlL10_reader = 0;
        this->gen_01_dlL10_writer = 0;
    }
}

void gen_01_dlL10_dspsetup() {
    this->gen_01_dlL10_reset();
}

number gen_01_dlL10_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_dlL10_size() {
    return this->gen_01_dlL10__maxdelay;
}

void gen_01_dlL11_step() {
    this->gen_01_dlL11_reader++;

    if (this->gen_01_dlL11_reader >= (int)(this->gen_01_dlL11_buffer->getSize()))
        this->gen_01_dlL11_reader = 0;
}

number gen_01_dlL11_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_01_dlL11_buffer->getSize()) + this->gen_01_dlL11_reader - ((size > this->gen_01_dlL11__maxdelay ? this->gen_01_dlL11__maxdelay : (size < (1 + this->gen_01_dlL11_reader != this->gen_01_dlL11_writer) ? 1 + this->gen_01_dlL11_reader != this->gen_01_dlL11_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_01_dlL11_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL11_wrap))
            ), this->gen_01_dlL11_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL11_wrap))
            ), this->gen_01_dlL11_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL11_wrap))
            ), this->gen_01_dlL11_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL11_wrap))
            ));
        }
    }

    number r = (int)(this->gen_01_dlL11_buffer->getSize()) + this->gen_01_dlL11_reader - ((size > this->gen_01_dlL11__maxdelay ? this->gen_01_dlL11__maxdelay : (size < (this->gen_01_dlL11_reader != this->gen_01_dlL11_writer) ? this->gen_01_dlL11_reader != this->gen_01_dlL11_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_dlL11_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL11_wrap))
    );
}

void gen_01_dlL11_write(number v) {
    this->gen_01_dlL11_writer = this->gen_01_dlL11_reader;
    this->gen_01_dlL11_buffer[(Index)this->gen_01_dlL11_writer] = v;
}

number gen_01_dlL11_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_dlL11__maxdelay : size);
    number val = this->gen_01_dlL11_read(effectiveSize, 0);
    this->gen_01_dlL11_write(v);
    this->gen_01_dlL11_step();
    return val;
}

array<Index, 2> gen_01_dlL11_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_dlL11_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_dlL11_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_dlL11_init() {
    auto result = this->gen_01_dlL11_calcSizeInSamples();
    this->gen_01_dlL11__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL11_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_dlL11_wrap = requestedSizeInSamples - 1;
}

void gen_01_dlL11_clear() {
    this->gen_01_dlL11_buffer->setZero();
}

void gen_01_dlL11_reset() {
    auto result = this->gen_01_dlL11_calcSizeInSamples();
    this->gen_01_dlL11__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL11_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_dlL11_buffer);
    this->gen_01_dlL11_wrap = this->gen_01_dlL11_buffer->getSize() - 1;
    this->gen_01_dlL11_clear();

    if (this->gen_01_dlL11_reader >= this->gen_01_dlL11__maxdelay || this->gen_01_dlL11_writer >= this->gen_01_dlL11__maxdelay) {
        this->gen_01_dlL11_reader = 0;
        this->gen_01_dlL11_writer = 0;
    }
}

void gen_01_dlL11_dspsetup() {
    this->gen_01_dlL11_reset();
}

number gen_01_dlL11_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_dlL11_size() {
    return this->gen_01_dlL11__maxdelay;
}

void gen_01_dlL12_step() {
    this->gen_01_dlL12_reader++;

    if (this->gen_01_dlL12_reader >= (int)(this->gen_01_dlL12_buffer->getSize()))
        this->gen_01_dlL12_reader = 0;
}

number gen_01_dlL12_read(number size, Int interp) {
    if (interp == 0) {
        number r = (int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL12_wrap))
        ));
    } else if (interp == 1) {
        number r = (int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? 1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->cubicinterp(frac, this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL12_wrap))
        ));
    } else if (interp == 6) {
        number r = (int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? 1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->fastcubicinterp(frac, this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL12_wrap))
        ));
    } else if (interp == 2) {
        number r = (int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? 1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->splineinterp(frac, this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL12_wrap))
        ));
    } else if (interp == 7) {
        number r = (int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? 1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);
        Index index5 = (Index)(index4 + 1);
        Index index6 = (Index)(index5 + 1);

        return this->spline6interp(frac, this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index5 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index6 & (BinOpInt)this->gen_01_dlL12_wrap))
        ));
    } else if (interp == 3) {
        number r = (int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);

        return this->cosineinterp(frac, this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL12_wrap))
        ));
    }

    number r = (int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_dlL12_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL12_wrap))
    );
}

void gen_01_dlL12_write(number v) {
    this->gen_01_dlL12_writer = this->gen_01_dlL12_reader;
    this->gen_01_dlL12_buffer[(Index)this->gen_01_dlL12_writer] = v;
}

number gen_01_dlL12_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_dlL12__maxdelay : size);
    number val = this->gen_01_dlL12_read(effectiveSize, 0);
    this->gen_01_dlL12_write(v);
    this->gen_01_dlL12_step();
    return val;
}

array<Index, 2> gen_01_dlL12_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_dlL12_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_dlL12_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_dlL12_init() {
    auto result = this->gen_01_dlL12_calcSizeInSamples();
    this->gen_01_dlL12__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL12_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_dlL12_wrap = requestedSizeInSamples - 1;
}

void gen_01_dlL12_clear() {
    this->gen_01_dlL12_buffer->setZero();
}

void gen_01_dlL12_reset() {
    auto result = this->gen_01_dlL12_calcSizeInSamples();
    this->gen_01_dlL12__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL12_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_dlL12_buffer);
    this->gen_01_dlL12_wrap = this->gen_01_dlL12_buffer->getSize() - 1;
    this->gen_01_dlL12_clear();

    if (this->gen_01_dlL12_reader >= this->gen_01_dlL12__maxdelay || this->gen_01_dlL12_writer >= this->gen_01_dlL12__maxdelay) {
        this->gen_01_dlL12_reader = 0;
        this->gen_01_dlL12_writer = 0;
    }
}

void gen_01_dlL12_dspsetup() {
    this->gen_01_dlL12_reset();
}

number gen_01_dlL12_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_dlL12_size() {
    return this->gen_01_dlL12__maxdelay;
}

void gen_01_dlL13_step() {
    this->gen_01_dlL13_reader++;

    if (this->gen_01_dlL13_reader >= (int)(this->gen_01_dlL13_buffer->getSize()))
        this->gen_01_dlL13_reader = 0;
}

number gen_01_dlL13_read(number size, Int interp) {
    if (interp == 0) {
        number r = (int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL13_wrap))
        ));
    } else if (interp == 1) {
        number r = (int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? 1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->cubicinterp(frac, this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL13_wrap))
        ));
    } else if (interp == 6) {
        number r = (int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? 1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->fastcubicinterp(frac, this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL13_wrap))
        ));
    } else if (interp == 2) {
        number r = (int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? 1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->splineinterp(frac, this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL13_wrap))
        ));
    } else if (interp == 7) {
        number r = (int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? 1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);
        Index index5 = (Index)(index4 + 1);
        Index index6 = (Index)(index5 + 1);

        return this->spline6interp(frac, this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index5 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index6 & (BinOpInt)this->gen_01_dlL13_wrap))
        ));
    } else if (interp == 3) {
        number r = (int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);

        return this->cosineinterp(frac, this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL13_wrap))
        ));
    }

    number r = (int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_01_dlL13_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL13_wrap))
    );
}

void gen_01_dlL13_write(number v) {
    this->gen_01_dlL13_writer = this->gen_01_dlL13_reader;
    this->gen_01_dlL13_buffer[(Index)this->gen_01_dlL13_writer] = v;
}

number gen_01_dlL13_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_01_dlL13__maxdelay : size);
    number val = this->gen_01_dlL13_read(effectiveSize, 0);
    this->gen_01_dlL13_write(v);
    this->gen_01_dlL13_step();
    return val;
}

array<Index, 2> gen_01_dlL13_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_dlL13_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_01_dlL13_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_dlL13_init() {
    auto result = this->gen_01_dlL13_calcSizeInSamples();
    this->gen_01_dlL13__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL13_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_dlL13_wrap = requestedSizeInSamples - 1;
}

void gen_01_dlL13_clear() {
    this->gen_01_dlL13_buffer->setZero();
}

void gen_01_dlL13_reset() {
    auto result = this->gen_01_dlL13_calcSizeInSamples();
    this->gen_01_dlL13__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_dlL13_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_dlL13_buffer);
    this->gen_01_dlL13_wrap = this->gen_01_dlL13_buffer->getSize() - 1;
    this->gen_01_dlL13_clear();

    if (this->gen_01_dlL13_reader >= this->gen_01_dlL13__maxdelay || this->gen_01_dlL13_writer >= this->gen_01_dlL13__maxdelay) {
        this->gen_01_dlL13_reader = 0;
        this->gen_01_dlL13_writer = 0;
    }
}

void gen_01_dlL13_dspsetup() {
    this->gen_01_dlL13_reset();
}

number gen_01_dlL13_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate() * 0.5;
}

number gen_01_dlL13_size() {
    return this->gen_01_dlL13__maxdelay;
}

number gen_01_feedbackL_getvalue() {
    return this->gen_01_feedbackL_value;
}

void gen_01_feedbackL_setvalue(number val) {
    this->gen_01_feedbackL_value = val;
}

void gen_01_feedbackL_reset() {
    this->gen_01_feedbackL_value = 0;
}

void gen_01_feedbackL_init() {
    this->gen_01_feedbackL_value = 0;
}

number gen_01_filterOutputL_getvalue() {
    return this->gen_01_filterOutputL_value;
}

void gen_01_filterOutputL_setvalue(number val) {
    this->gen_01_filterOutputL_value = val;
}

void gen_01_filterOutputL_reset() {
    this->gen_01_filterOutputL_value = 0;
}

void gen_01_filterOutputL_init() {
    this->gen_01_filterOutputL_value = 0;
}

number gen_01_history_11_getvalue() {
    return this->gen_01_history_11_value;
}

void gen_01_history_11_setvalue(number val) {
    this->gen_01_history_11_value = val;
}

void gen_01_history_11_reset() {
    this->gen_01_history_11_value = 0;
}

void gen_01_history_11_init() {
    this->gen_01_history_11_value = 0;
}

number gen_01_history_12_getvalue() {
    return this->gen_01_history_12_value;
}

void gen_01_history_12_setvalue(number val) {
    this->gen_01_history_12_value = val;
}

void gen_01_history_12_reset() {
    this->gen_01_history_12_value = 0;
}

void gen_01_history_12_init() {
    this->gen_01_history_12_value = 0;
}

number gen_01_phasor_4_next(number freq, number reset) {
    RNBO_UNUSED(reset);
    number pincr = freq * this->gen_01_phasor_4_conv;

    if (this->gen_01_phasor_4_currentPhase < 0.)
        this->gen_01_phasor_4_currentPhase = 1. + this->gen_01_phasor_4_currentPhase;

    if (this->gen_01_phasor_4_currentPhase > 1.)
        this->gen_01_phasor_4_currentPhase = this->gen_01_phasor_4_currentPhase - 1.;

    number tmp = this->gen_01_phasor_4_currentPhase;
    this->gen_01_phasor_4_currentPhase += pincr;
    return tmp;
}

void gen_01_phasor_4_reset() {
    this->gen_01_phasor_4_currentPhase = 0;
}

void gen_01_phasor_4_dspsetup() {
    this->gen_01_phasor_4_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

number gen_01_cycle_6_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_6_ph_conv;

    if (this->gen_01_cycle_6_ph_currentPhase < 0.)
        this->gen_01_cycle_6_ph_currentPhase = 1. + this->gen_01_cycle_6_ph_currentPhase;

    if (this->gen_01_cycle_6_ph_currentPhase > 1.)
        this->gen_01_cycle_6_ph_currentPhase = this->gen_01_cycle_6_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_6_ph_currentPhase;
    this->gen_01_cycle_6_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_6_ph_reset() {
    this->gen_01_cycle_6_ph_currentPhase = 0;
}

void gen_01_cycle_6_ph_dspsetup() {
    this->gen_01_cycle_6_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_6_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_6_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_6_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_6_dspsetup() {
    this->gen_01_cycle_6_phasei = 0;
    this->gen_01_cycle_6_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_01_cycle_6_wrap = (long)(this->gen_01_cycle_6_buffer->getSize()) - 1;
}

void gen_01_cycle_6_reset() {
    this->gen_01_cycle_6_phasei = 0;
}

void gen_01_cycle_6_bufferUpdated() {
    this->gen_01_cycle_6_wrap = (long)(this->gen_01_cycle_6_buffer->getSize()) - 1;
}

number gen_01_cycle_11_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_11_ph_conv;

    if (this->gen_01_cycle_11_ph_currentPhase < 0.)
        this->gen_01_cycle_11_ph_currentPhase = 1. + this->gen_01_cycle_11_ph_currentPhase;

    if (this->gen_01_cycle_11_ph_currentPhase > 1.)
        this->gen_01_cycle_11_ph_currentPhase = this->gen_01_cycle_11_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_11_ph_currentPhase;
    this->gen_01_cycle_11_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_11_ph_reset() {
    this->gen_01_cycle_11_ph_currentPhase = 0;
}

void gen_01_cycle_11_ph_dspsetup() {
    this->gen_01_cycle_11_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_11_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_11_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_11_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_11_dspsetup() {
    this->gen_01_cycle_11_phasei = 0;
    this->gen_01_cycle_11_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_01_cycle_11_wrap = (long)(this->gen_01_cycle_11_buffer->getSize()) - 1;
}

void gen_01_cycle_11_reset() {
    this->gen_01_cycle_11_phasei = 0;
}

void gen_01_cycle_11_bufferUpdated() {
    this->gen_01_cycle_11_wrap = (long)(this->gen_01_cycle_11_buffer->getSize()) - 1;
}

number gen_01_cycle_16_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_16_ph_conv;

    if (this->gen_01_cycle_16_ph_currentPhase < 0.)
        this->gen_01_cycle_16_ph_currentPhase = 1. + this->gen_01_cycle_16_ph_currentPhase;

    if (this->gen_01_cycle_16_ph_currentPhase > 1.)
        this->gen_01_cycle_16_ph_currentPhase = this->gen_01_cycle_16_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_16_ph_currentPhase;
    this->gen_01_cycle_16_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_16_ph_reset() {
    this->gen_01_cycle_16_ph_currentPhase = 0;
}

void gen_01_cycle_16_ph_dspsetup() {
    this->gen_01_cycle_16_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_16_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_16_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_16_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_16_dspsetup() {
    this->gen_01_cycle_16_phasei = 0;
    this->gen_01_cycle_16_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_01_cycle_16_wrap = (long)(this->gen_01_cycle_16_buffer->getSize()) - 1;
}

void gen_01_cycle_16_reset() {
    this->gen_01_cycle_16_phasei = 0;
}

void gen_01_cycle_16_bufferUpdated() {
    this->gen_01_cycle_16_wrap = (long)(this->gen_01_cycle_16_buffer->getSize()) - 1;
}

number gen_01_cycle_21_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_21_ph_conv;

    if (this->gen_01_cycle_21_ph_currentPhase < 0.)
        this->gen_01_cycle_21_ph_currentPhase = 1. + this->gen_01_cycle_21_ph_currentPhase;

    if (this->gen_01_cycle_21_ph_currentPhase > 1.)
        this->gen_01_cycle_21_ph_currentPhase = this->gen_01_cycle_21_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_21_ph_currentPhase;
    this->gen_01_cycle_21_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_21_ph_reset() {
    this->gen_01_cycle_21_ph_currentPhase = 0;
}

void gen_01_cycle_21_ph_dspsetup() {
    this->gen_01_cycle_21_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_21_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_21_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_21_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_21_dspsetup() {
    this->gen_01_cycle_21_phasei = 0;
    this->gen_01_cycle_21_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_01_cycle_21_wrap = (long)(this->gen_01_cycle_21_buffer->getSize()) - 1;
}

void gen_01_cycle_21_reset() {
    this->gen_01_cycle_21_phasei = 0;
}

void gen_01_cycle_21_bufferUpdated() {
    this->gen_01_cycle_21_wrap = (long)(this->gen_01_cycle_21_buffer->getSize()) - 1;
}

number gen_01_cycle_26_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_26_ph_conv;

    if (this->gen_01_cycle_26_ph_currentPhase < 0.)
        this->gen_01_cycle_26_ph_currentPhase = 1. + this->gen_01_cycle_26_ph_currentPhase;

    if (this->gen_01_cycle_26_ph_currentPhase > 1.)
        this->gen_01_cycle_26_ph_currentPhase = this->gen_01_cycle_26_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_26_ph_currentPhase;
    this->gen_01_cycle_26_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_26_ph_reset() {
    this->gen_01_cycle_26_ph_currentPhase = 0;
}

void gen_01_cycle_26_ph_dspsetup() {
    this->gen_01_cycle_26_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_26_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_26_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_26_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_26_dspsetup() {
    this->gen_01_cycle_26_phasei = 0;
    this->gen_01_cycle_26_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_01_cycle_26_wrap = (long)(this->gen_01_cycle_26_buffer->getSize()) - 1;
}

void gen_01_cycle_26_reset() {
    this->gen_01_cycle_26_phasei = 0;
}

void gen_01_cycle_26_bufferUpdated() {
    this->gen_01_cycle_26_wrap = (long)(this->gen_01_cycle_26_buffer->getSize()) - 1;
}

number gen_01_cycle_31_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_31_ph_conv;

    if (this->gen_01_cycle_31_ph_currentPhase < 0.)
        this->gen_01_cycle_31_ph_currentPhase = 1. + this->gen_01_cycle_31_ph_currentPhase;

    if (this->gen_01_cycle_31_ph_currentPhase > 1.)
        this->gen_01_cycle_31_ph_currentPhase = this->gen_01_cycle_31_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_31_ph_currentPhase;
    this->gen_01_cycle_31_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_31_ph_reset() {
    this->gen_01_cycle_31_ph_currentPhase = 0;
}

void gen_01_cycle_31_ph_dspsetup() {
    this->gen_01_cycle_31_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_31_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_31_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_31_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_31_dspsetup() {
    this->gen_01_cycle_31_phasei = 0;
    this->gen_01_cycle_31_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_01_cycle_31_wrap = (long)(this->gen_01_cycle_31_buffer->getSize()) - 1;
}

void gen_01_cycle_31_reset() {
    this->gen_01_cycle_31_phasei = 0;
}

void gen_01_cycle_31_bufferUpdated() {
    this->gen_01_cycle_31_wrap = (long)(this->gen_01_cycle_31_buffer->getSize()) - 1;
}

number gen_01_cycle_36_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_36_ph_conv;

    if (this->gen_01_cycle_36_ph_currentPhase < 0.)
        this->gen_01_cycle_36_ph_currentPhase = 1. + this->gen_01_cycle_36_ph_currentPhase;

    if (this->gen_01_cycle_36_ph_currentPhase > 1.)
        this->gen_01_cycle_36_ph_currentPhase = this->gen_01_cycle_36_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_36_ph_currentPhase;
    this->gen_01_cycle_36_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_36_ph_reset() {
    this->gen_01_cycle_36_ph_currentPhase = 0;
}

void gen_01_cycle_36_ph_dspsetup() {
    this->gen_01_cycle_36_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_36_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_36_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_36_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_36_dspsetup() {
    this->gen_01_cycle_36_phasei = 0;
    this->gen_01_cycle_36_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_01_cycle_36_wrap = (long)(this->gen_01_cycle_36_buffer->getSize()) - 1;
}

void gen_01_cycle_36_reset() {
    this->gen_01_cycle_36_phasei = 0;
}

void gen_01_cycle_36_bufferUpdated() {
    this->gen_01_cycle_36_wrap = (long)(this->gen_01_cycle_36_buffer->getSize()) - 1;
}

number gen_01_cycle_41_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_41_ph_conv;

    if (this->gen_01_cycle_41_ph_currentPhase < 0.)
        this->gen_01_cycle_41_ph_currentPhase = 1. + this->gen_01_cycle_41_ph_currentPhase;

    if (this->gen_01_cycle_41_ph_currentPhase > 1.)
        this->gen_01_cycle_41_ph_currentPhase = this->gen_01_cycle_41_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_41_ph_currentPhase;
    this->gen_01_cycle_41_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_41_ph_reset() {
    this->gen_01_cycle_41_ph_currentPhase = 0;
}

void gen_01_cycle_41_ph_dspsetup() {
    this->gen_01_cycle_41_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_41_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_41_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_41_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_41_dspsetup() {
    this->gen_01_cycle_41_phasei = 0;
    this->gen_01_cycle_41_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_01_cycle_41_wrap = (long)(this->gen_01_cycle_41_buffer->getSize()) - 1;
}

void gen_01_cycle_41_reset() {
    this->gen_01_cycle_41_phasei = 0;
}

void gen_01_cycle_41_bufferUpdated() {
    this->gen_01_cycle_41_wrap = (long)(this->gen_01_cycle_41_buffer->getSize()) - 1;
}

number gen_01_cycle_46_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_46_ph_conv;

    if (this->gen_01_cycle_46_ph_currentPhase < 0.)
        this->gen_01_cycle_46_ph_currentPhase = 1. + this->gen_01_cycle_46_ph_currentPhase;

    if (this->gen_01_cycle_46_ph_currentPhase > 1.)
        this->gen_01_cycle_46_ph_currentPhase = this->gen_01_cycle_46_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_46_ph_currentPhase;
    this->gen_01_cycle_46_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_46_ph_reset() {
    this->gen_01_cycle_46_ph_currentPhase = 0;
}

void gen_01_cycle_46_ph_dspsetup() {
    this->gen_01_cycle_46_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_46_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);
    RNBO_UNUSED(frequency);

    {
        uint32_t uint_phase;

        {
            uint_phase = this->gen_01_cycle_46_phasei;
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_46_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_46_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);

        {
            uint32_t pincr = (uint32_t)(uint32_trunc(0.4 * this->gen_01_cycle_46_f2i));
            this->gen_01_cycle_46_phasei = uint32_add(this->gen_01_cycle_46_phasei, pincr);
        }

        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_46_dspsetup() {
    this->gen_01_cycle_46_phasei = 0;
    this->gen_01_cycle_46_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_01_cycle_46_wrap = (long)(this->gen_01_cycle_46_buffer->getSize()) - 1;
}

void gen_01_cycle_46_reset() {
    this->gen_01_cycle_46_phasei = 0;
}

void gen_01_cycle_46_bufferUpdated() {
    this->gen_01_cycle_46_wrap = (long)(this->gen_01_cycle_46_buffer->getSize()) - 1;
}

number gen_01_cycle_54_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_54_ph_conv;

    if (this->gen_01_cycle_54_ph_currentPhase < 0.)
        this->gen_01_cycle_54_ph_currentPhase = 1. + this->gen_01_cycle_54_ph_currentPhase;

    if (this->gen_01_cycle_54_ph_currentPhase > 1.)
        this->gen_01_cycle_54_ph_currentPhase = this->gen_01_cycle_54_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_54_ph_currentPhase;
    this->gen_01_cycle_54_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_54_ph_reset() {
    this->gen_01_cycle_54_ph_currentPhase = 0;
}

void gen_01_cycle_54_ph_dspsetup() {
    this->gen_01_cycle_54_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_54_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);
    RNBO_UNUSED(frequency);

    {
        uint32_t uint_phase;

        {
            uint_phase = this->gen_01_cycle_54_phasei;
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_54_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_54_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);

        {
            uint32_t pincr = (uint32_t)(uint32_trunc(0.2 * this->gen_01_cycle_54_f2i));
            this->gen_01_cycle_54_phasei = uint32_add(this->gen_01_cycle_54_phasei, pincr);
        }

        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_54_dspsetup() {
    this->gen_01_cycle_54_phasei = 0;
    this->gen_01_cycle_54_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_01_cycle_54_wrap = (long)(this->gen_01_cycle_54_buffer->getSize()) - 1;
}

void gen_01_cycle_54_reset() {
    this->gen_01_cycle_54_phasei = 0;
}

void gen_01_cycle_54_bufferUpdated() {
    this->gen_01_cycle_54_wrap = (long)(this->gen_01_cycle_54_buffer->getSize()) - 1;
}

number gen_01_slide_69_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_01_slide_69_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(2)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(2)));
    this->gen_01_slide_69_prev = this->gen_01_slide_69_prev + ((x > this->gen_01_slide_69_prev ? iup : idown)) * temp;
    return this->gen_01_slide_69_prev;
}

void gen_01_slide_69_reset() {
    this->gen_01_slide_69_prev = 0;
}

void gen_01_noise_78_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->gen_01_noise_78_state
    );
}

void gen_01_noise_78_init() {
    this->gen_01_noise_78_reset();
}

void gen_01_noise_78_seed(number v) {
    xoshiro_reset(v, this->gen_01_noise_78_state);
}

number gen_01_noise_78_next() {
    return xoshiro_next(this->gen_01_noise_78_state);
}

void gen_01_noise_84_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->gen_01_noise_84_state
    );
}

void gen_01_noise_84_init() {
    this->gen_01_noise_84_reset();
}

void gen_01_noise_84_seed(number v) {
    xoshiro_reset(v, this->gen_01_noise_84_state);
}

number gen_01_noise_84_next() {
    return xoshiro_next(this->gen_01_noise_84_state);
}

void gen_01_noise_90_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->gen_01_noise_90_state
    );
}

void gen_01_noise_90_init() {
    this->gen_01_noise_90_reset();
}

void gen_01_noise_90_seed(number v) {
    xoshiro_reset(v, this->gen_01_noise_90_state);
}

number gen_01_noise_90_next() {
    return xoshiro_next(this->gen_01_noise_90_state);
}

void gen_01_noise_96_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->gen_01_noise_96_state
    );
}

void gen_01_noise_96_init() {
    this->gen_01_noise_96_reset();
}

void gen_01_noise_96_seed(number v) {
    xoshiro_reset(v, this->gen_01_noise_96_state);
}

number gen_01_noise_96_next() {
    return xoshiro_next(this->gen_01_noise_96_state);
}

number gen_01_phasor_105_next(number freq, number reset) {
    RNBO_UNUSED(reset);
    number pincr = freq * this->gen_01_phasor_105_conv;

    if (this->gen_01_phasor_105_currentPhase < 0.)
        this->gen_01_phasor_105_currentPhase = 1. + this->gen_01_phasor_105_currentPhase;

    if (this->gen_01_phasor_105_currentPhase > 1.)
        this->gen_01_phasor_105_currentPhase = this->gen_01_phasor_105_currentPhase - 1.;

    number tmp = this->gen_01_phasor_105_currentPhase;
    this->gen_01_phasor_105_currentPhase += pincr;
    return tmp;
}

void gen_01_phasor_105_reset() {
    this->gen_01_phasor_105_currentPhase = 0;
}

void gen_01_phasor_105_dspsetup() {
    this->gen_01_phasor_105_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

number gen_01_delta_109_next(number x) {
    number temp = (number)(x - this->gen_01_delta_109_prev);
    this->gen_01_delta_109_prev = x;
    return temp;
}

void gen_01_delta_109_dspsetup() {
    this->gen_01_delta_109_reset();
}

void gen_01_delta_109_reset() {
    this->gen_01_delta_109_prev = 0;
}

number gen_01_sah_111_next(number x, number trig, number thresh) {
    RNBO_UNUSED(thresh);

    if (this->gen_01_sah_111_prev <= 0 && trig > 0)
        this->gen_01_sah_111_value = x;

    this->gen_01_sah_111_prev = trig;
    return this->gen_01_sah_111_value;
}

void gen_01_sah_111_reset() {
    this->gen_01_sah_111_prev = 0.;
    this->gen_01_sah_111_value = 0.;
}

number gen_01_delta_120_next(number x) {
    number temp = (number)(x - this->gen_01_delta_120_prev);
    this->gen_01_delta_120_prev = x;
    return temp;
}

void gen_01_delta_120_dspsetup() {
    this->gen_01_delta_120_reset();
}

void gen_01_delta_120_reset() {
    this->gen_01_delta_120_prev = 0;
}

number gen_01_sah_122_next(number x, number trig, number thresh) {
    RNBO_UNUSED(thresh);

    if (this->gen_01_sah_122_prev <= 0 && trig > 0)
        this->gen_01_sah_122_value = x;

    this->gen_01_sah_122_prev = trig;
    return this->gen_01_sah_122_value;
}

void gen_01_sah_122_reset() {
    this->gen_01_sah_122_prev = 0.;
    this->gen_01_sah_122_value = 0.;
}

number gen_01_delta_131_next(number x) {
    number temp = (number)(x - this->gen_01_delta_131_prev);
    this->gen_01_delta_131_prev = x;
    return temp;
}

void gen_01_delta_131_dspsetup() {
    this->gen_01_delta_131_reset();
}

void gen_01_delta_131_reset() {
    this->gen_01_delta_131_prev = 0;
}

number gen_01_sah_134_next(number x, number trig, number thresh) {
    RNBO_UNUSED(thresh);

    if (this->gen_01_sah_134_prev <= 0 && trig > 0)
        this->gen_01_sah_134_value = x;

    this->gen_01_sah_134_prev = trig;
    return this->gen_01_sah_134_value;
}

void gen_01_sah_134_reset() {
    this->gen_01_sah_134_prev = 0.;
    this->gen_01_sah_134_value = 0.;
}

number gen_01_delta_143_next(number x) {
    number temp = (number)(x - this->gen_01_delta_143_prev);
    this->gen_01_delta_143_prev = x;
    return temp;
}

void gen_01_delta_143_dspsetup() {
    this->gen_01_delta_143_reset();
}

void gen_01_delta_143_reset() {
    this->gen_01_delta_143_prev = 0;
}

number gen_01_sah_145_next(number x, number trig, number thresh) {
    RNBO_UNUSED(thresh);

    if (this->gen_01_sah_145_prev <= 0 && trig > 0)
        this->gen_01_sah_145_value = x;

    this->gen_01_sah_145_prev = trig;
    return this->gen_01_sah_145_value;
}

void gen_01_sah_145_reset() {
    this->gen_01_sah_145_prev = 0.;
    this->gen_01_sah_145_value = 0.;
}

number gen_01_dcblock_223_next(number x, number gain) {
    RNBO_UNUSED(gain);
    number y = x - this->gen_01_dcblock_223_xm1 + this->gen_01_dcblock_223_ym1 * 0.9997;
    this->gen_01_dcblock_223_xm1 = x;
    this->gen_01_dcblock_223_ym1 = y;
    return y;
}

void gen_01_dcblock_223_reset() {
    this->gen_01_dcblock_223_xm1 = 0;
    this->gen_01_dcblock_223_ym1 = 0;
}

void gen_01_dcblock_223_dspsetup() {
    this->gen_01_dcblock_223_reset();
}

number gen_01_slide_229_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_01_slide_229_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(2)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(2)));
    this->gen_01_slide_229_prev = this->gen_01_slide_229_prev + ((x > this->gen_01_slide_229_prev ? iup : idown)) * temp;
    return this->gen_01_slide_229_prev;
}

void gen_01_slide_229_reset() {
    this->gen_01_slide_229_prev = 0;
}

void gen_01_noise_238_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->gen_01_noise_238_state
    );
}

void gen_01_noise_238_init() {
    this->gen_01_noise_238_reset();
}

void gen_01_noise_238_seed(number v) {
    xoshiro_reset(v, this->gen_01_noise_238_state);
}

number gen_01_noise_238_next() {
    return xoshiro_next(this->gen_01_noise_238_state);
}

void gen_01_noise_244_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->gen_01_noise_244_state
    );
}

void gen_01_noise_244_init() {
    this->gen_01_noise_244_reset();
}

void gen_01_noise_244_seed(number v) {
    xoshiro_reset(v, this->gen_01_noise_244_state);
}

number gen_01_noise_244_next() {
    return xoshiro_next(this->gen_01_noise_244_state);
}

void gen_01_noise_250_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->gen_01_noise_250_state
    );
}

void gen_01_noise_250_init() {
    this->gen_01_noise_250_reset();
}

void gen_01_noise_250_seed(number v) {
    xoshiro_reset(v, this->gen_01_noise_250_state);
}

number gen_01_noise_250_next() {
    return xoshiro_next(this->gen_01_noise_250_state);
}

void gen_01_noise_256_reset() {
    xoshiro_reset(
        systemticks() + this->voice() + this->random(0, 10000),
        this->gen_01_noise_256_state
    );
}

void gen_01_noise_256_init() {
    this->gen_01_noise_256_reset();
}

void gen_01_noise_256_seed(number v) {
    xoshiro_reset(v, this->gen_01_noise_256_state);
}

number gen_01_noise_256_next() {
    return xoshiro_next(this->gen_01_noise_256_state);
}

number gen_01_phasor_265_next(number freq, number reset) {
    RNBO_UNUSED(reset);
    number pincr = freq * this->gen_01_phasor_265_conv;

    if (this->gen_01_phasor_265_currentPhase < 0.)
        this->gen_01_phasor_265_currentPhase = 1. + this->gen_01_phasor_265_currentPhase;

    if (this->gen_01_phasor_265_currentPhase > 1.)
        this->gen_01_phasor_265_currentPhase = this->gen_01_phasor_265_currentPhase - 1.;

    number tmp = this->gen_01_phasor_265_currentPhase;
    this->gen_01_phasor_265_currentPhase += pincr;
    return tmp;
}

void gen_01_phasor_265_reset() {
    this->gen_01_phasor_265_currentPhase = 0;
}

void gen_01_phasor_265_dspsetup() {
    this->gen_01_phasor_265_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

number gen_01_delta_269_next(number x) {
    number temp = (number)(x - this->gen_01_delta_269_prev);
    this->gen_01_delta_269_prev = x;
    return temp;
}

void gen_01_delta_269_dspsetup() {
    this->gen_01_delta_269_reset();
}

void gen_01_delta_269_reset() {
    this->gen_01_delta_269_prev = 0;
}

number gen_01_sah_271_next(number x, number trig, number thresh) {
    RNBO_UNUSED(thresh);

    if (this->gen_01_sah_271_prev <= 0 && trig > 0)
        this->gen_01_sah_271_value = x;

    this->gen_01_sah_271_prev = trig;
    return this->gen_01_sah_271_value;
}

void gen_01_sah_271_reset() {
    this->gen_01_sah_271_prev = 0.;
    this->gen_01_sah_271_value = 0.;
}

number gen_01_delta_280_next(number x) {
    number temp = (number)(x - this->gen_01_delta_280_prev);
    this->gen_01_delta_280_prev = x;
    return temp;
}

void gen_01_delta_280_dspsetup() {
    this->gen_01_delta_280_reset();
}

void gen_01_delta_280_reset() {
    this->gen_01_delta_280_prev = 0;
}

number gen_01_sah_282_next(number x, number trig, number thresh) {
    RNBO_UNUSED(thresh);

    if (this->gen_01_sah_282_prev <= 0 && trig > 0)
        this->gen_01_sah_282_value = x;

    this->gen_01_sah_282_prev = trig;
    return this->gen_01_sah_282_value;
}

void gen_01_sah_282_reset() {
    this->gen_01_sah_282_prev = 0.;
    this->gen_01_sah_282_value = 0.;
}

number gen_01_delta_291_next(number x) {
    number temp = (number)(x - this->gen_01_delta_291_prev);
    this->gen_01_delta_291_prev = x;
    return temp;
}

void gen_01_delta_291_dspsetup() {
    this->gen_01_delta_291_reset();
}

void gen_01_delta_291_reset() {
    this->gen_01_delta_291_prev = 0;
}

number gen_01_sah_293_next(number x, number trig, number thresh) {
    RNBO_UNUSED(thresh);

    if (this->gen_01_sah_293_prev <= 0 && trig > 0)
        this->gen_01_sah_293_value = x;

    this->gen_01_sah_293_prev = trig;
    return this->gen_01_sah_293_value;
}

void gen_01_sah_293_reset() {
    this->gen_01_sah_293_prev = 0.;
    this->gen_01_sah_293_value = 0.;
}

number gen_01_delta_302_next(number x) {
    number temp = (number)(x - this->gen_01_delta_302_prev);
    this->gen_01_delta_302_prev = x;
    return temp;
}

void gen_01_delta_302_dspsetup() {
    this->gen_01_delta_302_reset();
}

void gen_01_delta_302_reset() {
    this->gen_01_delta_302_prev = 0;
}

number gen_01_sah_304_next(number x, number trig, number thresh) {
    RNBO_UNUSED(thresh);

    if (this->gen_01_sah_304_prev <= 0 && trig > 0)
        this->gen_01_sah_304_value = x;

    this->gen_01_sah_304_prev = trig;
    return this->gen_01_sah_304_value;
}

void gen_01_sah_304_reset() {
    this->gen_01_sah_304_prev = 0.;
    this->gen_01_sah_304_value = 0.;
}

number gen_01_dcblock_372_next(number x, number gain) {
    RNBO_UNUSED(gain);
    number y = x - this->gen_01_dcblock_372_xm1 + this->gen_01_dcblock_372_ym1 * 0.9997;
    this->gen_01_dcblock_372_xm1 = x;
    this->gen_01_dcblock_372_ym1 = y;
    return y;
}

void gen_01_dcblock_372_reset() {
    this->gen_01_dcblock_372_xm1 = 0;
    this->gen_01_dcblock_372_ym1 = 0;
}

void gen_01_dcblock_372_dspsetup() {
    this->gen_01_dcblock_372_reset();
}

void gen_01_dspsetup(bool force) {
    if ((bool)(this->gen_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gen_01_setupDone = true;
    this->gen_01_delay_1_dspsetup();
    this->gen_01_delay_2_dspsetup();
    this->gen_01_delay_5_dspsetup();
    this->gen_01_DL1_dspsetup();
    this->gen_01_DL2_dspsetup();
    this->gen_01_DL3_dspsetup();
    this->gen_01_DL4_dspsetup();
    this->gen_01_DL5_dspsetup();
    this->gen_01_DL6_dspsetup();
    this->gen_01_DL7_dspsetup();
    this->gen_01_DL8_dspsetup();
    this->gen_01_DL9_dspsetup();
    this->gen_01_DL10_dspsetup();
    this->gen_01_DL11_dspsetup();
    this->gen_01_DL12_dspsetup();
    this->gen_01_DL13_dspsetup();
    this->gen_01_delay_9_dspsetup();
    this->gen_01_dlL1_dspsetup();
    this->gen_01_dlL2_dspsetup();
    this->gen_01_dlL3_dspsetup();
    this->gen_01_dlL4_dspsetup();
    this->gen_01_dlL5_dspsetup();
    this->gen_01_dlL6_dspsetup();
    this->gen_01_dlL7_dspsetup();
    this->gen_01_dlL8_dspsetup();
    this->gen_01_dlL9_dspsetup();
    this->gen_01_dlL10_dspsetup();
    this->gen_01_dlL11_dspsetup();
    this->gen_01_dlL12_dspsetup();
    this->gen_01_dlL13_dspsetup();
    this->gen_01_phasor_4_dspsetup();
    this->gen_01_cycle_6_ph_dspsetup();
    this->gen_01_cycle_6_dspsetup();
    this->gen_01_cycle_11_ph_dspsetup();
    this->gen_01_cycle_11_dspsetup();
    this->gen_01_cycle_16_ph_dspsetup();
    this->gen_01_cycle_16_dspsetup();
    this->gen_01_cycle_21_ph_dspsetup();
    this->gen_01_cycle_21_dspsetup();
    this->gen_01_cycle_26_ph_dspsetup();
    this->gen_01_cycle_26_dspsetup();
    this->gen_01_cycle_31_ph_dspsetup();
    this->gen_01_cycle_31_dspsetup();
    this->gen_01_cycle_36_ph_dspsetup();
    this->gen_01_cycle_36_dspsetup();
    this->gen_01_cycle_41_ph_dspsetup();
    this->gen_01_cycle_41_dspsetup();
    this->gen_01_cycle_46_ph_dspsetup();
    this->gen_01_cycle_46_dspsetup();
    this->gen_01_cycle_54_ph_dspsetup();
    this->gen_01_cycle_54_dspsetup();
    this->gen_01_phasor_105_dspsetup();
    this->gen_01_delta_109_dspsetup();
    this->gen_01_delta_120_dspsetup();
    this->gen_01_delta_131_dspsetup();
    this->gen_01_delta_143_dspsetup();
    this->gen_01_dcblock_223_dspsetup();
    this->gen_01_phasor_265_dspsetup();
    this->gen_01_delta_269_dspsetup();
    this->gen_01_delta_280_dspsetup();
    this->gen_01_delta_291_dspsetup();
    this->gen_01_delta_302_dspsetup();
    this->gen_01_dcblock_372_dspsetup();
}

void gen_02_delay_1_step() {
    this->gen_02_delay_1_reader++;

    if (this->gen_02_delay_1_reader >= (int)(this->gen_02_delay_1_buffer->getSize()))
        this->gen_02_delay_1_reader = 0;
}

number gen_02_delay_1_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_1_buffer->getSize()) + this->gen_02_delay_1_reader - ((size > this->gen_02_delay_1__maxdelay ? this->gen_02_delay_1__maxdelay : (size < (1 + this->gen_02_delay_1_reader != this->gen_02_delay_1_writer) ? 1 + this->gen_02_delay_1_reader != this->gen_02_delay_1_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_1_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_1_wrap))
            ), this->gen_02_delay_1_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_1_wrap))
            ), this->gen_02_delay_1_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_1_wrap))
            ), this->gen_02_delay_1_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_1_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_1_buffer->getSize()) + this->gen_02_delay_1_reader - ((size > this->gen_02_delay_1__maxdelay ? this->gen_02_delay_1__maxdelay : (size < (this->gen_02_delay_1_reader != this->gen_02_delay_1_writer) ? this->gen_02_delay_1_reader != this->gen_02_delay_1_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_1_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_1_wrap))
    );
}

void gen_02_delay_1_write(number v) {
    this->gen_02_delay_1_writer = this->gen_02_delay_1_reader;
    this->gen_02_delay_1_buffer[(Index)this->gen_02_delay_1_writer] = v;
}

number gen_02_delay_1_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_1__maxdelay : size);
    number val = this->gen_02_delay_1_read(effectiveSize, 0);
    this->gen_02_delay_1_write(v);
    this->gen_02_delay_1_step();
    return val;
}

array<Index, 2> gen_02_delay_1_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_1_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_1_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_1_init() {
    auto result = this->gen_02_delay_1_calcSizeInSamples();
    this->gen_02_delay_1__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_1_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_1_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_1_clear() {
    this->gen_02_delay_1_buffer->setZero();
}

void gen_02_delay_1_reset() {
    auto result = this->gen_02_delay_1_calcSizeInSamples();
    this->gen_02_delay_1__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_1_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_1_buffer);
    this->gen_02_delay_1_wrap = this->gen_02_delay_1_buffer->getSize() - 1;
    this->gen_02_delay_1_clear();

    if (this->gen_02_delay_1_reader >= this->gen_02_delay_1__maxdelay || this->gen_02_delay_1_writer >= this->gen_02_delay_1__maxdelay) {
        this->gen_02_delay_1_reader = 0;
        this->gen_02_delay_1_writer = 0;
    }
}

void gen_02_delay_1_dspsetup() {
    this->gen_02_delay_1_reset();
}

number gen_02_delay_1_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_1_size() {
    return this->gen_02_delay_1__maxdelay;
}

void gen_02_delay_2_step() {
    this->gen_02_delay_2_reader++;

    if (this->gen_02_delay_2_reader >= (int)(this->gen_02_delay_2_buffer->getSize()))
        this->gen_02_delay_2_reader = 0;
}

number gen_02_delay_2_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        number r = (int)(this->gen_02_delay_2_buffer->getSize()) + this->gen_02_delay_2_reader - ((size > this->gen_02_delay_2__maxdelay ? this->gen_02_delay_2__maxdelay : (size < (this->gen_02_delay_2_reader != this->gen_02_delay_2_writer) ? this->gen_02_delay_2_reader != this->gen_02_delay_2_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->gen_02_delay_2_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_2_wrap))
        ), this->gen_02_delay_2_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_2_wrap))
        ));
    }

    number r = (int)(this->gen_02_delay_2_buffer->getSize()) + this->gen_02_delay_2_reader - ((size > this->gen_02_delay_2__maxdelay ? this->gen_02_delay_2__maxdelay : (size < (this->gen_02_delay_2_reader != this->gen_02_delay_2_writer) ? this->gen_02_delay_2_reader != this->gen_02_delay_2_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_2_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_2_wrap))
    );
}

void gen_02_delay_2_write(number v) {
    this->gen_02_delay_2_writer = this->gen_02_delay_2_reader;
    this->gen_02_delay_2_buffer[(Index)this->gen_02_delay_2_writer] = v;
}

number gen_02_delay_2_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_2__maxdelay : size);
    number val = this->gen_02_delay_2_read(effectiveSize, 0);
    this->gen_02_delay_2_write(v);
    this->gen_02_delay_2_step();
    return val;
}

array<Index, 2> gen_02_delay_2_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_2_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_2_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_2_init() {
    auto result = this->gen_02_delay_2_calcSizeInSamples();
    this->gen_02_delay_2__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_2_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_2_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_2_clear() {
    this->gen_02_delay_2_buffer->setZero();
}

void gen_02_delay_2_reset() {
    auto result = this->gen_02_delay_2_calcSizeInSamples();
    this->gen_02_delay_2__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_2_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_2_buffer);
    this->gen_02_delay_2_wrap = this->gen_02_delay_2_buffer->getSize() - 1;
    this->gen_02_delay_2_clear();

    if (this->gen_02_delay_2_reader >= this->gen_02_delay_2__maxdelay || this->gen_02_delay_2_writer >= this->gen_02_delay_2__maxdelay) {
        this->gen_02_delay_2_reader = 0;
        this->gen_02_delay_2_writer = 0;
    }
}

void gen_02_delay_2_dspsetup() {
    this->gen_02_delay_2_reset();
}

number gen_02_delay_2_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return 1000;
}

number gen_02_delay_2_size() {
    return this->gen_02_delay_2__maxdelay;
}

void gen_02_delay_3_step() {
    this->gen_02_delay_3_reader++;

    if (this->gen_02_delay_3_reader >= (int)(this->gen_02_delay_3_buffer->getSize()))
        this->gen_02_delay_3_reader = 0;
}

number gen_02_delay_3_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        number r = (int)(this->gen_02_delay_3_buffer->getSize()) + this->gen_02_delay_3_reader - ((size > this->gen_02_delay_3__maxdelay ? this->gen_02_delay_3__maxdelay : (size < (this->gen_02_delay_3_reader != this->gen_02_delay_3_writer) ? this->gen_02_delay_3_reader != this->gen_02_delay_3_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->gen_02_delay_3_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_3_wrap))
        ), this->gen_02_delay_3_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_3_wrap))
        ));
    }

    number r = (int)(this->gen_02_delay_3_buffer->getSize()) + this->gen_02_delay_3_reader - ((size > this->gen_02_delay_3__maxdelay ? this->gen_02_delay_3__maxdelay : (size < (this->gen_02_delay_3_reader != this->gen_02_delay_3_writer) ? this->gen_02_delay_3_reader != this->gen_02_delay_3_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_3_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_3_wrap))
    );
}

void gen_02_delay_3_write(number v) {
    this->gen_02_delay_3_writer = this->gen_02_delay_3_reader;
    this->gen_02_delay_3_buffer[(Index)this->gen_02_delay_3_writer] = v;
}

number gen_02_delay_3_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_3__maxdelay : size);
    number val = this->gen_02_delay_3_read(effectiveSize, 0);
    this->gen_02_delay_3_write(v);
    this->gen_02_delay_3_step();
    return val;
}

array<Index, 2> gen_02_delay_3_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_3_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_3_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_3_init() {
    auto result = this->gen_02_delay_3_calcSizeInSamples();
    this->gen_02_delay_3__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_3_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_3_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_3_clear() {
    this->gen_02_delay_3_buffer->setZero();
}

void gen_02_delay_3_reset() {
    auto result = this->gen_02_delay_3_calcSizeInSamples();
    this->gen_02_delay_3__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_3_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_3_buffer);
    this->gen_02_delay_3_wrap = this->gen_02_delay_3_buffer->getSize() - 1;
    this->gen_02_delay_3_clear();

    if (this->gen_02_delay_3_reader >= this->gen_02_delay_3__maxdelay || this->gen_02_delay_3_writer >= this->gen_02_delay_3__maxdelay) {
        this->gen_02_delay_3_reader = 0;
        this->gen_02_delay_3_writer = 0;
    }
}

void gen_02_delay_3_dspsetup() {
    this->gen_02_delay_3_reset();
}

number gen_02_delay_3_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return 1000;
}

number gen_02_delay_3_size() {
    return this->gen_02_delay_3__maxdelay;
}

void gen_02_delay_4_step() {
    this->gen_02_delay_4_reader++;

    if (this->gen_02_delay_4_reader >= (int)(this->gen_02_delay_4_buffer->getSize()))
        this->gen_02_delay_4_reader = 0;
}

number gen_02_delay_4_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_4_buffer->getSize()) + this->gen_02_delay_4_reader - ((size > this->gen_02_delay_4__maxdelay ? this->gen_02_delay_4__maxdelay : (size < (1 + this->gen_02_delay_4_reader != this->gen_02_delay_4_writer) ? 1 + this->gen_02_delay_4_reader != this->gen_02_delay_4_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_4_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_4_wrap))
            ), this->gen_02_delay_4_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_4_wrap))
            ), this->gen_02_delay_4_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_4_wrap))
            ), this->gen_02_delay_4_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_4_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_4_buffer->getSize()) + this->gen_02_delay_4_reader - ((size > this->gen_02_delay_4__maxdelay ? this->gen_02_delay_4__maxdelay : (size < (this->gen_02_delay_4_reader != this->gen_02_delay_4_writer) ? this->gen_02_delay_4_reader != this->gen_02_delay_4_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_4_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_4_wrap))
    );
}

void gen_02_delay_4_write(number v) {
    this->gen_02_delay_4_writer = this->gen_02_delay_4_reader;
    this->gen_02_delay_4_buffer[(Index)this->gen_02_delay_4_writer] = v;
}

number gen_02_delay_4_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_4__maxdelay : size);
    number val = this->gen_02_delay_4_read(effectiveSize, 0);
    this->gen_02_delay_4_write(v);
    this->gen_02_delay_4_step();
    return val;
}

array<Index, 2> gen_02_delay_4_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_4_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_4_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_4_init() {
    auto result = this->gen_02_delay_4_calcSizeInSamples();
    this->gen_02_delay_4__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_4_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_4_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_4_clear() {
    this->gen_02_delay_4_buffer->setZero();
}

void gen_02_delay_4_reset() {
    auto result = this->gen_02_delay_4_calcSizeInSamples();
    this->gen_02_delay_4__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_4_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_4_buffer);
    this->gen_02_delay_4_wrap = this->gen_02_delay_4_buffer->getSize() - 1;
    this->gen_02_delay_4_clear();

    if (this->gen_02_delay_4_reader >= this->gen_02_delay_4__maxdelay || this->gen_02_delay_4_writer >= this->gen_02_delay_4__maxdelay) {
        this->gen_02_delay_4_reader = 0;
        this->gen_02_delay_4_writer = 0;
    }
}

void gen_02_delay_4_dspsetup() {
    this->gen_02_delay_4_reset();
}

number gen_02_delay_4_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_4_size() {
    return this->gen_02_delay_4__maxdelay;
}

void gen_02_delay_5_step() {
    this->gen_02_delay_5_reader++;

    if (this->gen_02_delay_5_reader >= (int)(this->gen_02_delay_5_buffer->getSize()))
        this->gen_02_delay_5_reader = 0;
}

number gen_02_delay_5_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_5_buffer->getSize()) + this->gen_02_delay_5_reader - ((size > this->gen_02_delay_5__maxdelay ? this->gen_02_delay_5__maxdelay : (size < (1 + this->gen_02_delay_5_reader != this->gen_02_delay_5_writer) ? 1 + this->gen_02_delay_5_reader != this->gen_02_delay_5_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_5_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_5_wrap))
            ), this->gen_02_delay_5_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_5_wrap))
            ), this->gen_02_delay_5_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_5_wrap))
            ), this->gen_02_delay_5_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_5_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_5_buffer->getSize()) + this->gen_02_delay_5_reader - ((size > this->gen_02_delay_5__maxdelay ? this->gen_02_delay_5__maxdelay : (size < (this->gen_02_delay_5_reader != this->gen_02_delay_5_writer) ? this->gen_02_delay_5_reader != this->gen_02_delay_5_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_5_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_5_wrap))
    );
}

void gen_02_delay_5_write(number v) {
    this->gen_02_delay_5_writer = this->gen_02_delay_5_reader;
    this->gen_02_delay_5_buffer[(Index)this->gen_02_delay_5_writer] = v;
}

number gen_02_delay_5_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_5__maxdelay : size);
    number val = this->gen_02_delay_5_read(effectiveSize, 0);
    this->gen_02_delay_5_write(v);
    this->gen_02_delay_5_step();
    return val;
}

array<Index, 2> gen_02_delay_5_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_5_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_5_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_5_init() {
    auto result = this->gen_02_delay_5_calcSizeInSamples();
    this->gen_02_delay_5__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_5_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_5_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_5_clear() {
    this->gen_02_delay_5_buffer->setZero();
}

void gen_02_delay_5_reset() {
    auto result = this->gen_02_delay_5_calcSizeInSamples();
    this->gen_02_delay_5__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_5_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_5_buffer);
    this->gen_02_delay_5_wrap = this->gen_02_delay_5_buffer->getSize() - 1;
    this->gen_02_delay_5_clear();

    if (this->gen_02_delay_5_reader >= this->gen_02_delay_5__maxdelay || this->gen_02_delay_5_writer >= this->gen_02_delay_5__maxdelay) {
        this->gen_02_delay_5_reader = 0;
        this->gen_02_delay_5_writer = 0;
    }
}

void gen_02_delay_5_dspsetup() {
    this->gen_02_delay_5_reset();
}

number gen_02_delay_5_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_5_size() {
    return this->gen_02_delay_5__maxdelay;
}

void gen_02_delay_6_step() {
    this->gen_02_delay_6_reader++;

    if (this->gen_02_delay_6_reader >= (int)(this->gen_02_delay_6_buffer->getSize()))
        this->gen_02_delay_6_reader = 0;
}

number gen_02_delay_6_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_6_buffer->getSize()) + this->gen_02_delay_6_reader - ((size > this->gen_02_delay_6__maxdelay ? this->gen_02_delay_6__maxdelay : (size < (1 + this->gen_02_delay_6_reader != this->gen_02_delay_6_writer) ? 1 + this->gen_02_delay_6_reader != this->gen_02_delay_6_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_6_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_6_wrap))
            ), this->gen_02_delay_6_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_6_wrap))
            ), this->gen_02_delay_6_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_6_wrap))
            ), this->gen_02_delay_6_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_6_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_6_buffer->getSize()) + this->gen_02_delay_6_reader - ((size > this->gen_02_delay_6__maxdelay ? this->gen_02_delay_6__maxdelay : (size < (this->gen_02_delay_6_reader != this->gen_02_delay_6_writer) ? this->gen_02_delay_6_reader != this->gen_02_delay_6_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_6_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_6_wrap))
    );
}

void gen_02_delay_6_write(number v) {
    this->gen_02_delay_6_writer = this->gen_02_delay_6_reader;
    this->gen_02_delay_6_buffer[(Index)this->gen_02_delay_6_writer] = v;
}

number gen_02_delay_6_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_6__maxdelay : size);
    number val = this->gen_02_delay_6_read(effectiveSize, 0);
    this->gen_02_delay_6_write(v);
    this->gen_02_delay_6_step();
    return val;
}

array<Index, 2> gen_02_delay_6_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_6_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_6_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_6_init() {
    auto result = this->gen_02_delay_6_calcSizeInSamples();
    this->gen_02_delay_6__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_6_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_6_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_6_clear() {
    this->gen_02_delay_6_buffer->setZero();
}

void gen_02_delay_6_reset() {
    auto result = this->gen_02_delay_6_calcSizeInSamples();
    this->gen_02_delay_6__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_6_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_6_buffer);
    this->gen_02_delay_6_wrap = this->gen_02_delay_6_buffer->getSize() - 1;
    this->gen_02_delay_6_clear();

    if (this->gen_02_delay_6_reader >= this->gen_02_delay_6__maxdelay || this->gen_02_delay_6_writer >= this->gen_02_delay_6__maxdelay) {
        this->gen_02_delay_6_reader = 0;
        this->gen_02_delay_6_writer = 0;
    }
}

void gen_02_delay_6_dspsetup() {
    this->gen_02_delay_6_reset();
}

number gen_02_delay_6_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_6_size() {
    return this->gen_02_delay_6__maxdelay;
}

void gen_02_delay_7_step() {
    this->gen_02_delay_7_reader++;

    if (this->gen_02_delay_7_reader >= (int)(this->gen_02_delay_7_buffer->getSize()))
        this->gen_02_delay_7_reader = 0;
}

number gen_02_delay_7_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_7_buffer->getSize()) + this->gen_02_delay_7_reader - ((size > this->gen_02_delay_7__maxdelay ? this->gen_02_delay_7__maxdelay : (size < (1 + this->gen_02_delay_7_reader != this->gen_02_delay_7_writer) ? 1 + this->gen_02_delay_7_reader != this->gen_02_delay_7_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_7_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_7_wrap))
            ), this->gen_02_delay_7_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_7_wrap))
            ), this->gen_02_delay_7_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_7_wrap))
            ), this->gen_02_delay_7_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_7_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_7_buffer->getSize()) + this->gen_02_delay_7_reader - ((size > this->gen_02_delay_7__maxdelay ? this->gen_02_delay_7__maxdelay : (size < (this->gen_02_delay_7_reader != this->gen_02_delay_7_writer) ? this->gen_02_delay_7_reader != this->gen_02_delay_7_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_7_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_7_wrap))
    );
}

void gen_02_delay_7_write(number v) {
    this->gen_02_delay_7_writer = this->gen_02_delay_7_reader;
    this->gen_02_delay_7_buffer[(Index)this->gen_02_delay_7_writer] = v;
}

number gen_02_delay_7_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_7__maxdelay : size);
    number val = this->gen_02_delay_7_read(effectiveSize, 0);
    this->gen_02_delay_7_write(v);
    this->gen_02_delay_7_step();
    return val;
}

array<Index, 2> gen_02_delay_7_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_7_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_7_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_7_init() {
    auto result = this->gen_02_delay_7_calcSizeInSamples();
    this->gen_02_delay_7__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_7_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_7_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_7_clear() {
    this->gen_02_delay_7_buffer->setZero();
}

void gen_02_delay_7_reset() {
    auto result = this->gen_02_delay_7_calcSizeInSamples();
    this->gen_02_delay_7__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_7_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_7_buffer);
    this->gen_02_delay_7_wrap = this->gen_02_delay_7_buffer->getSize() - 1;
    this->gen_02_delay_7_clear();

    if (this->gen_02_delay_7_reader >= this->gen_02_delay_7__maxdelay || this->gen_02_delay_7_writer >= this->gen_02_delay_7__maxdelay) {
        this->gen_02_delay_7_reader = 0;
        this->gen_02_delay_7_writer = 0;
    }
}

void gen_02_delay_7_dspsetup() {
    this->gen_02_delay_7_reset();
}

number gen_02_delay_7_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_7_size() {
    return this->gen_02_delay_7__maxdelay;
}

void gen_02_delay_8_step() {
    this->gen_02_delay_8_reader++;

    if (this->gen_02_delay_8_reader >= (int)(this->gen_02_delay_8_buffer->getSize()))
        this->gen_02_delay_8_reader = 0;
}

number gen_02_delay_8_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_8_buffer->getSize()) + this->gen_02_delay_8_reader - ((size > this->gen_02_delay_8__maxdelay ? this->gen_02_delay_8__maxdelay : (size < (1 + this->gen_02_delay_8_reader != this->gen_02_delay_8_writer) ? 1 + this->gen_02_delay_8_reader != this->gen_02_delay_8_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_8_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_8_wrap))
            ), this->gen_02_delay_8_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_8_wrap))
            ), this->gen_02_delay_8_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_8_wrap))
            ), this->gen_02_delay_8_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_8_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_8_buffer->getSize()) + this->gen_02_delay_8_reader - ((size > this->gen_02_delay_8__maxdelay ? this->gen_02_delay_8__maxdelay : (size < (this->gen_02_delay_8_reader != this->gen_02_delay_8_writer) ? this->gen_02_delay_8_reader != this->gen_02_delay_8_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_8_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_8_wrap))
    );
}

void gen_02_delay_8_write(number v) {
    this->gen_02_delay_8_writer = this->gen_02_delay_8_reader;
    this->gen_02_delay_8_buffer[(Index)this->gen_02_delay_8_writer] = v;
}

number gen_02_delay_8_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_8__maxdelay : size);
    number val = this->gen_02_delay_8_read(effectiveSize, 0);
    this->gen_02_delay_8_write(v);
    this->gen_02_delay_8_step();
    return val;
}

array<Index, 2> gen_02_delay_8_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_8_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_8_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_8_init() {
    auto result = this->gen_02_delay_8_calcSizeInSamples();
    this->gen_02_delay_8__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_8_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_8_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_8_clear() {
    this->gen_02_delay_8_buffer->setZero();
}

void gen_02_delay_8_reset() {
    auto result = this->gen_02_delay_8_calcSizeInSamples();
    this->gen_02_delay_8__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_8_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_8_buffer);
    this->gen_02_delay_8_wrap = this->gen_02_delay_8_buffer->getSize() - 1;
    this->gen_02_delay_8_clear();

    if (this->gen_02_delay_8_reader >= this->gen_02_delay_8__maxdelay || this->gen_02_delay_8_writer >= this->gen_02_delay_8__maxdelay) {
        this->gen_02_delay_8_reader = 0;
        this->gen_02_delay_8_writer = 0;
    }
}

void gen_02_delay_8_dspsetup() {
    this->gen_02_delay_8_reset();
}

number gen_02_delay_8_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_8_size() {
    return this->gen_02_delay_8__maxdelay;
}

void gen_02_delay_9_step() {
    this->gen_02_delay_9_reader++;

    if (this->gen_02_delay_9_reader >= (int)(this->gen_02_delay_9_buffer->getSize()))
        this->gen_02_delay_9_reader = 0;
}

number gen_02_delay_9_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_9_buffer->getSize()) + this->gen_02_delay_9_reader - ((size > this->gen_02_delay_9__maxdelay ? this->gen_02_delay_9__maxdelay : (size < (1 + this->gen_02_delay_9_reader != this->gen_02_delay_9_writer) ? 1 + this->gen_02_delay_9_reader != this->gen_02_delay_9_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_9_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_9_wrap))
            ), this->gen_02_delay_9_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_9_wrap))
            ), this->gen_02_delay_9_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_9_wrap))
            ), this->gen_02_delay_9_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_9_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_9_buffer->getSize()) + this->gen_02_delay_9_reader - ((size > this->gen_02_delay_9__maxdelay ? this->gen_02_delay_9__maxdelay : (size < (this->gen_02_delay_9_reader != this->gen_02_delay_9_writer) ? this->gen_02_delay_9_reader != this->gen_02_delay_9_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_9_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_9_wrap))
    );
}

void gen_02_delay_9_write(number v) {
    this->gen_02_delay_9_writer = this->gen_02_delay_9_reader;
    this->gen_02_delay_9_buffer[(Index)this->gen_02_delay_9_writer] = v;
}

number gen_02_delay_9_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_9__maxdelay : size);
    number val = this->gen_02_delay_9_read(effectiveSize, 0);
    this->gen_02_delay_9_write(v);
    this->gen_02_delay_9_step();
    return val;
}

array<Index, 2> gen_02_delay_9_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_9_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_9_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_9_init() {
    auto result = this->gen_02_delay_9_calcSizeInSamples();
    this->gen_02_delay_9__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_9_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_9_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_9_clear() {
    this->gen_02_delay_9_buffer->setZero();
}

void gen_02_delay_9_reset() {
    auto result = this->gen_02_delay_9_calcSizeInSamples();
    this->gen_02_delay_9__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_9_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_9_buffer);
    this->gen_02_delay_9_wrap = this->gen_02_delay_9_buffer->getSize() - 1;
    this->gen_02_delay_9_clear();

    if (this->gen_02_delay_9_reader >= this->gen_02_delay_9__maxdelay || this->gen_02_delay_9_writer >= this->gen_02_delay_9__maxdelay) {
        this->gen_02_delay_9_reader = 0;
        this->gen_02_delay_9_writer = 0;
    }
}

void gen_02_delay_9_dspsetup() {
    this->gen_02_delay_9_reset();
}

number gen_02_delay_9_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_9_size() {
    return this->gen_02_delay_9__maxdelay;
}

void gen_02_delay_10_step() {
    this->gen_02_delay_10_reader++;

    if (this->gen_02_delay_10_reader >= (int)(this->gen_02_delay_10_buffer->getSize()))
        this->gen_02_delay_10_reader = 0;
}

number gen_02_delay_10_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_10_buffer->getSize()) + this->gen_02_delay_10_reader - ((size > this->gen_02_delay_10__maxdelay ? this->gen_02_delay_10__maxdelay : (size < (1 + this->gen_02_delay_10_reader != this->gen_02_delay_10_writer) ? 1 + this->gen_02_delay_10_reader != this->gen_02_delay_10_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_10_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_10_wrap))
            ), this->gen_02_delay_10_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_10_wrap))
            ), this->gen_02_delay_10_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_10_wrap))
            ), this->gen_02_delay_10_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_10_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_10_buffer->getSize()) + this->gen_02_delay_10_reader - ((size > this->gen_02_delay_10__maxdelay ? this->gen_02_delay_10__maxdelay : (size < (this->gen_02_delay_10_reader != this->gen_02_delay_10_writer) ? this->gen_02_delay_10_reader != this->gen_02_delay_10_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_10_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_10_wrap))
    );
}

void gen_02_delay_10_write(number v) {
    this->gen_02_delay_10_writer = this->gen_02_delay_10_reader;
    this->gen_02_delay_10_buffer[(Index)this->gen_02_delay_10_writer] = v;
}

number gen_02_delay_10_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_10__maxdelay : size);
    number val = this->gen_02_delay_10_read(effectiveSize, 0);
    this->gen_02_delay_10_write(v);
    this->gen_02_delay_10_step();
    return val;
}

array<Index, 2> gen_02_delay_10_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_10_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_10_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_10_init() {
    auto result = this->gen_02_delay_10_calcSizeInSamples();
    this->gen_02_delay_10__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_10_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_10_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_10_clear() {
    this->gen_02_delay_10_buffer->setZero();
}

void gen_02_delay_10_reset() {
    auto result = this->gen_02_delay_10_calcSizeInSamples();
    this->gen_02_delay_10__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_10_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_10_buffer);
    this->gen_02_delay_10_wrap = this->gen_02_delay_10_buffer->getSize() - 1;
    this->gen_02_delay_10_clear();

    if (this->gen_02_delay_10_reader >= this->gen_02_delay_10__maxdelay || this->gen_02_delay_10_writer >= this->gen_02_delay_10__maxdelay) {
        this->gen_02_delay_10_reader = 0;
        this->gen_02_delay_10_writer = 0;
    }
}

void gen_02_delay_10_dspsetup() {
    this->gen_02_delay_10_reset();
}

number gen_02_delay_10_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_10_size() {
    return this->gen_02_delay_10__maxdelay;
}

void gen_02_delay_11_step() {
    this->gen_02_delay_11_reader++;

    if (this->gen_02_delay_11_reader >= (int)(this->gen_02_delay_11_buffer->getSize()))
        this->gen_02_delay_11_reader = 0;
}

number gen_02_delay_11_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_11_buffer->getSize()) + this->gen_02_delay_11_reader - ((size > this->gen_02_delay_11__maxdelay ? this->gen_02_delay_11__maxdelay : (size < (1 + this->gen_02_delay_11_reader != this->gen_02_delay_11_writer) ? 1 + this->gen_02_delay_11_reader != this->gen_02_delay_11_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_11_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_11_wrap))
            ), this->gen_02_delay_11_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_11_wrap))
            ), this->gen_02_delay_11_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_11_wrap))
            ), this->gen_02_delay_11_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_11_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_11_buffer->getSize()) + this->gen_02_delay_11_reader - ((size > this->gen_02_delay_11__maxdelay ? this->gen_02_delay_11__maxdelay : (size < (this->gen_02_delay_11_reader != this->gen_02_delay_11_writer) ? this->gen_02_delay_11_reader != this->gen_02_delay_11_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_11_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_11_wrap))
    );
}

void gen_02_delay_11_write(number v) {
    this->gen_02_delay_11_writer = this->gen_02_delay_11_reader;
    this->gen_02_delay_11_buffer[(Index)this->gen_02_delay_11_writer] = v;
}

number gen_02_delay_11_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_11__maxdelay : size);
    number val = this->gen_02_delay_11_read(effectiveSize, 0);
    this->gen_02_delay_11_write(v);
    this->gen_02_delay_11_step();
    return val;
}

array<Index, 2> gen_02_delay_11_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_11_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_11_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_11_init() {
    auto result = this->gen_02_delay_11_calcSizeInSamples();
    this->gen_02_delay_11__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_11_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_11_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_11_clear() {
    this->gen_02_delay_11_buffer->setZero();
}

void gen_02_delay_11_reset() {
    auto result = this->gen_02_delay_11_calcSizeInSamples();
    this->gen_02_delay_11__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_11_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_11_buffer);
    this->gen_02_delay_11_wrap = this->gen_02_delay_11_buffer->getSize() - 1;
    this->gen_02_delay_11_clear();

    if (this->gen_02_delay_11_reader >= this->gen_02_delay_11__maxdelay || this->gen_02_delay_11_writer >= this->gen_02_delay_11__maxdelay) {
        this->gen_02_delay_11_reader = 0;
        this->gen_02_delay_11_writer = 0;
    }
}

void gen_02_delay_11_dspsetup() {
    this->gen_02_delay_11_reset();
}

number gen_02_delay_11_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_11_size() {
    return this->gen_02_delay_11__maxdelay;
}

void gen_02_delay_12_step() {
    this->gen_02_delay_12_reader++;

    if (this->gen_02_delay_12_reader >= (int)(this->gen_02_delay_12_buffer->getSize()))
        this->gen_02_delay_12_reader = 0;
}

number gen_02_delay_12_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_12_buffer->getSize()) + this->gen_02_delay_12_reader - ((size > this->gen_02_delay_12__maxdelay ? this->gen_02_delay_12__maxdelay : (size < (1 + this->gen_02_delay_12_reader != this->gen_02_delay_12_writer) ? 1 + this->gen_02_delay_12_reader != this->gen_02_delay_12_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_12_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_12_wrap))
            ), this->gen_02_delay_12_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_12_wrap))
            ), this->gen_02_delay_12_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_12_wrap))
            ), this->gen_02_delay_12_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_12_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_12_buffer->getSize()) + this->gen_02_delay_12_reader - ((size > this->gen_02_delay_12__maxdelay ? this->gen_02_delay_12__maxdelay : (size < (this->gen_02_delay_12_reader != this->gen_02_delay_12_writer) ? this->gen_02_delay_12_reader != this->gen_02_delay_12_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_12_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_12_wrap))
    );
}

void gen_02_delay_12_write(number v) {
    this->gen_02_delay_12_writer = this->gen_02_delay_12_reader;
    this->gen_02_delay_12_buffer[(Index)this->gen_02_delay_12_writer] = v;
}

number gen_02_delay_12_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_12__maxdelay : size);
    number val = this->gen_02_delay_12_read(effectiveSize, 0);
    this->gen_02_delay_12_write(v);
    this->gen_02_delay_12_step();
    return val;
}

array<Index, 2> gen_02_delay_12_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_12_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_12_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_12_init() {
    auto result = this->gen_02_delay_12_calcSizeInSamples();
    this->gen_02_delay_12__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_12_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_12_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_12_clear() {
    this->gen_02_delay_12_buffer->setZero();
}

void gen_02_delay_12_reset() {
    auto result = this->gen_02_delay_12_calcSizeInSamples();
    this->gen_02_delay_12__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_12_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_12_buffer);
    this->gen_02_delay_12_wrap = this->gen_02_delay_12_buffer->getSize() - 1;
    this->gen_02_delay_12_clear();

    if (this->gen_02_delay_12_reader >= this->gen_02_delay_12__maxdelay || this->gen_02_delay_12_writer >= this->gen_02_delay_12__maxdelay) {
        this->gen_02_delay_12_reader = 0;
        this->gen_02_delay_12_writer = 0;
    }
}

void gen_02_delay_12_dspsetup() {
    this->gen_02_delay_12_reset();
}

number gen_02_delay_12_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_12_size() {
    return this->gen_02_delay_12__maxdelay;
}

void gen_02_delay_13_step() {
    this->gen_02_delay_13_reader++;

    if (this->gen_02_delay_13_reader >= (int)(this->gen_02_delay_13_buffer->getSize()))
        this->gen_02_delay_13_reader = 0;
}

number gen_02_delay_13_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_13_buffer->getSize()) + this->gen_02_delay_13_reader - ((size > this->gen_02_delay_13__maxdelay ? this->gen_02_delay_13__maxdelay : (size < (1 + this->gen_02_delay_13_reader != this->gen_02_delay_13_writer) ? 1 + this->gen_02_delay_13_reader != this->gen_02_delay_13_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_13_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_13_wrap))
            ), this->gen_02_delay_13_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_13_wrap))
            ), this->gen_02_delay_13_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_13_wrap))
            ), this->gen_02_delay_13_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_13_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_13_buffer->getSize()) + this->gen_02_delay_13_reader - ((size > this->gen_02_delay_13__maxdelay ? this->gen_02_delay_13__maxdelay : (size < (this->gen_02_delay_13_reader != this->gen_02_delay_13_writer) ? this->gen_02_delay_13_reader != this->gen_02_delay_13_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_13_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_13_wrap))
    );
}

void gen_02_delay_13_write(number v) {
    this->gen_02_delay_13_writer = this->gen_02_delay_13_reader;
    this->gen_02_delay_13_buffer[(Index)this->gen_02_delay_13_writer] = v;
}

number gen_02_delay_13_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_13__maxdelay : size);
    number val = this->gen_02_delay_13_read(effectiveSize, 0);
    this->gen_02_delay_13_write(v);
    this->gen_02_delay_13_step();
    return val;
}

array<Index, 2> gen_02_delay_13_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_13_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_13_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_13_init() {
    auto result = this->gen_02_delay_13_calcSizeInSamples();
    this->gen_02_delay_13__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_13_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_13_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_13_clear() {
    this->gen_02_delay_13_buffer->setZero();
}

void gen_02_delay_13_reset() {
    auto result = this->gen_02_delay_13_calcSizeInSamples();
    this->gen_02_delay_13__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_13_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_13_buffer);
    this->gen_02_delay_13_wrap = this->gen_02_delay_13_buffer->getSize() - 1;
    this->gen_02_delay_13_clear();

    if (this->gen_02_delay_13_reader >= this->gen_02_delay_13__maxdelay || this->gen_02_delay_13_writer >= this->gen_02_delay_13__maxdelay) {
        this->gen_02_delay_13_reader = 0;
        this->gen_02_delay_13_writer = 0;
    }
}

void gen_02_delay_13_dspsetup() {
    this->gen_02_delay_13_reset();
}

number gen_02_delay_13_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_13_size() {
    return this->gen_02_delay_13__maxdelay;
}

void gen_02_delay_14_step() {
    this->gen_02_delay_14_reader++;

    if (this->gen_02_delay_14_reader >= (int)(this->gen_02_delay_14_buffer->getSize()))
        this->gen_02_delay_14_reader = 0;
}

number gen_02_delay_14_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_14_buffer->getSize()) + this->gen_02_delay_14_reader - ((size > this->gen_02_delay_14__maxdelay ? this->gen_02_delay_14__maxdelay : (size < (1 + this->gen_02_delay_14_reader != this->gen_02_delay_14_writer) ? 1 + this->gen_02_delay_14_reader != this->gen_02_delay_14_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_14_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_14_wrap))
            ), this->gen_02_delay_14_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_14_wrap))
            ), this->gen_02_delay_14_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_14_wrap))
            ), this->gen_02_delay_14_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_14_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_14_buffer->getSize()) + this->gen_02_delay_14_reader - ((size > this->gen_02_delay_14__maxdelay ? this->gen_02_delay_14__maxdelay : (size < (this->gen_02_delay_14_reader != this->gen_02_delay_14_writer) ? this->gen_02_delay_14_reader != this->gen_02_delay_14_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_14_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_14_wrap))
    );
}

void gen_02_delay_14_write(number v) {
    this->gen_02_delay_14_writer = this->gen_02_delay_14_reader;
    this->gen_02_delay_14_buffer[(Index)this->gen_02_delay_14_writer] = v;
}

number gen_02_delay_14_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_14__maxdelay : size);
    number val = this->gen_02_delay_14_read(effectiveSize, 0);
    this->gen_02_delay_14_write(v);
    this->gen_02_delay_14_step();
    return val;
}

array<Index, 2> gen_02_delay_14_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_14_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_14_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_14_init() {
    auto result = this->gen_02_delay_14_calcSizeInSamples();
    this->gen_02_delay_14__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_14_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_14_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_14_clear() {
    this->gen_02_delay_14_buffer->setZero();
}

void gen_02_delay_14_reset() {
    auto result = this->gen_02_delay_14_calcSizeInSamples();
    this->gen_02_delay_14__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_14_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_14_buffer);
    this->gen_02_delay_14_wrap = this->gen_02_delay_14_buffer->getSize() - 1;
    this->gen_02_delay_14_clear();

    if (this->gen_02_delay_14_reader >= this->gen_02_delay_14__maxdelay || this->gen_02_delay_14_writer >= this->gen_02_delay_14__maxdelay) {
        this->gen_02_delay_14_reader = 0;
        this->gen_02_delay_14_writer = 0;
    }
}

void gen_02_delay_14_dspsetup() {
    this->gen_02_delay_14_reset();
}

number gen_02_delay_14_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_14_size() {
    return this->gen_02_delay_14__maxdelay;
}

void gen_02_delay_15_step() {
    this->gen_02_delay_15_reader++;

    if (this->gen_02_delay_15_reader >= (int)(this->gen_02_delay_15_buffer->getSize()))
        this->gen_02_delay_15_reader = 0;
}

number gen_02_delay_15_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_15_buffer->getSize()) + this->gen_02_delay_15_reader - ((size > this->gen_02_delay_15__maxdelay ? this->gen_02_delay_15__maxdelay : (size < (1 + this->gen_02_delay_15_reader != this->gen_02_delay_15_writer) ? 1 + this->gen_02_delay_15_reader != this->gen_02_delay_15_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_15_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_15_wrap))
            ), this->gen_02_delay_15_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_15_wrap))
            ), this->gen_02_delay_15_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_15_wrap))
            ), this->gen_02_delay_15_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_15_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_15_buffer->getSize()) + this->gen_02_delay_15_reader - ((size > this->gen_02_delay_15__maxdelay ? this->gen_02_delay_15__maxdelay : (size < (this->gen_02_delay_15_reader != this->gen_02_delay_15_writer) ? this->gen_02_delay_15_reader != this->gen_02_delay_15_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_15_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_15_wrap))
    );
}

void gen_02_delay_15_write(number v) {
    this->gen_02_delay_15_writer = this->gen_02_delay_15_reader;
    this->gen_02_delay_15_buffer[(Index)this->gen_02_delay_15_writer] = v;
}

number gen_02_delay_15_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_15__maxdelay : size);
    number val = this->gen_02_delay_15_read(effectiveSize, 0);
    this->gen_02_delay_15_write(v);
    this->gen_02_delay_15_step();
    return val;
}

array<Index, 2> gen_02_delay_15_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_15_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_15_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_15_init() {
    auto result = this->gen_02_delay_15_calcSizeInSamples();
    this->gen_02_delay_15__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_15_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_15_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_15_clear() {
    this->gen_02_delay_15_buffer->setZero();
}

void gen_02_delay_15_reset() {
    auto result = this->gen_02_delay_15_calcSizeInSamples();
    this->gen_02_delay_15__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_15_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_15_buffer);
    this->gen_02_delay_15_wrap = this->gen_02_delay_15_buffer->getSize() - 1;
    this->gen_02_delay_15_clear();

    if (this->gen_02_delay_15_reader >= this->gen_02_delay_15__maxdelay || this->gen_02_delay_15_writer >= this->gen_02_delay_15__maxdelay) {
        this->gen_02_delay_15_reader = 0;
        this->gen_02_delay_15_writer = 0;
    }
}

void gen_02_delay_15_dspsetup() {
    this->gen_02_delay_15_reset();
}

number gen_02_delay_15_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_15_size() {
    return this->gen_02_delay_15__maxdelay;
}

number gen_02_history_16_getvalue() {
    return this->gen_02_history_16_value;
}

void gen_02_history_16_setvalue(number val) {
    this->gen_02_history_16_value = val;
}

void gen_02_history_16_reset() {
    this->gen_02_history_16_value = 0;
}

void gen_02_history_16_init() {
    this->gen_02_history_16_value = 0;
}

void gen_02_delay_17_step() {
    this->gen_02_delay_17_reader++;

    if (this->gen_02_delay_17_reader >= (int)(this->gen_02_delay_17_buffer->getSize()))
        this->gen_02_delay_17_reader = 0;
}

number gen_02_delay_17_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_17_buffer->getSize()) + this->gen_02_delay_17_reader - ((size > this->gen_02_delay_17__maxdelay ? this->gen_02_delay_17__maxdelay : (size < (1 + this->gen_02_delay_17_reader != this->gen_02_delay_17_writer) ? 1 + this->gen_02_delay_17_reader != this->gen_02_delay_17_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_17_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_17_wrap))
            ), this->gen_02_delay_17_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_17_wrap))
            ), this->gen_02_delay_17_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_17_wrap))
            ), this->gen_02_delay_17_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_17_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_17_buffer->getSize()) + this->gen_02_delay_17_reader - ((size > this->gen_02_delay_17__maxdelay ? this->gen_02_delay_17__maxdelay : (size < (this->gen_02_delay_17_reader != this->gen_02_delay_17_writer) ? this->gen_02_delay_17_reader != this->gen_02_delay_17_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_17_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_17_wrap))
    );
}

void gen_02_delay_17_write(number v) {
    this->gen_02_delay_17_writer = this->gen_02_delay_17_reader;
    this->gen_02_delay_17_buffer[(Index)this->gen_02_delay_17_writer] = v;
}

number gen_02_delay_17_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_17__maxdelay : size);
    number val = this->gen_02_delay_17_read(effectiveSize, 0);
    this->gen_02_delay_17_write(v);
    this->gen_02_delay_17_step();
    return val;
}

array<Index, 2> gen_02_delay_17_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_17_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_17_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_17_init() {
    auto result = this->gen_02_delay_17_calcSizeInSamples();
    this->gen_02_delay_17__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_17_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_17_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_17_clear() {
    this->gen_02_delay_17_buffer->setZero();
}

void gen_02_delay_17_reset() {
    auto result = this->gen_02_delay_17_calcSizeInSamples();
    this->gen_02_delay_17__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_17_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_17_buffer);
    this->gen_02_delay_17_wrap = this->gen_02_delay_17_buffer->getSize() - 1;
    this->gen_02_delay_17_clear();

    if (this->gen_02_delay_17_reader >= this->gen_02_delay_17__maxdelay || this->gen_02_delay_17_writer >= this->gen_02_delay_17__maxdelay) {
        this->gen_02_delay_17_reader = 0;
        this->gen_02_delay_17_writer = 0;
    }
}

void gen_02_delay_17_dspsetup() {
    this->gen_02_delay_17_reset();
}

number gen_02_delay_17_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_17_size() {
    return this->gen_02_delay_17__maxdelay;
}

void gen_02_delay_18_step() {
    this->gen_02_delay_18_reader++;

    if (this->gen_02_delay_18_reader >= (int)(this->gen_02_delay_18_buffer->getSize()))
        this->gen_02_delay_18_reader = 0;
}

number gen_02_delay_18_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_18_buffer->getSize()) + this->gen_02_delay_18_reader - ((size > this->gen_02_delay_18__maxdelay ? this->gen_02_delay_18__maxdelay : (size < (1 + this->gen_02_delay_18_reader != this->gen_02_delay_18_writer) ? 1 + this->gen_02_delay_18_reader != this->gen_02_delay_18_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_18_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_18_wrap))
            ), this->gen_02_delay_18_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_18_wrap))
            ), this->gen_02_delay_18_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_18_wrap))
            ), this->gen_02_delay_18_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_18_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_18_buffer->getSize()) + this->gen_02_delay_18_reader - ((size > this->gen_02_delay_18__maxdelay ? this->gen_02_delay_18__maxdelay : (size < (this->gen_02_delay_18_reader != this->gen_02_delay_18_writer) ? this->gen_02_delay_18_reader != this->gen_02_delay_18_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_18_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_18_wrap))
    );
}

void gen_02_delay_18_write(number v) {
    this->gen_02_delay_18_writer = this->gen_02_delay_18_reader;
    this->gen_02_delay_18_buffer[(Index)this->gen_02_delay_18_writer] = v;
}

number gen_02_delay_18_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_18__maxdelay : size);
    number val = this->gen_02_delay_18_read(effectiveSize, 0);
    this->gen_02_delay_18_write(v);
    this->gen_02_delay_18_step();
    return val;
}

array<Index, 2> gen_02_delay_18_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_18_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_18_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_18_init() {
    auto result = this->gen_02_delay_18_calcSizeInSamples();
    this->gen_02_delay_18__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_18_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_18_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_18_clear() {
    this->gen_02_delay_18_buffer->setZero();
}

void gen_02_delay_18_reset() {
    auto result = this->gen_02_delay_18_calcSizeInSamples();
    this->gen_02_delay_18__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_18_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_18_buffer);
    this->gen_02_delay_18_wrap = this->gen_02_delay_18_buffer->getSize() - 1;
    this->gen_02_delay_18_clear();

    if (this->gen_02_delay_18_reader >= this->gen_02_delay_18__maxdelay || this->gen_02_delay_18_writer >= this->gen_02_delay_18__maxdelay) {
        this->gen_02_delay_18_reader = 0;
        this->gen_02_delay_18_writer = 0;
    }
}

void gen_02_delay_18_dspsetup() {
    this->gen_02_delay_18_reset();
}

number gen_02_delay_18_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_18_size() {
    return this->gen_02_delay_18__maxdelay;
}

void gen_02_delay_19_step() {
    this->gen_02_delay_19_reader++;

    if (this->gen_02_delay_19_reader >= (int)(this->gen_02_delay_19_buffer->getSize()))
        this->gen_02_delay_19_reader = 0;
}

number gen_02_delay_19_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_19_buffer->getSize()) + this->gen_02_delay_19_reader - ((size > this->gen_02_delay_19__maxdelay ? this->gen_02_delay_19__maxdelay : (size < (1 + this->gen_02_delay_19_reader != this->gen_02_delay_19_writer) ? 1 + this->gen_02_delay_19_reader != this->gen_02_delay_19_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_19_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_19_wrap))
            ), this->gen_02_delay_19_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_19_wrap))
            ), this->gen_02_delay_19_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_19_wrap))
            ), this->gen_02_delay_19_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_19_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_19_buffer->getSize()) + this->gen_02_delay_19_reader - ((size > this->gen_02_delay_19__maxdelay ? this->gen_02_delay_19__maxdelay : (size < (this->gen_02_delay_19_reader != this->gen_02_delay_19_writer) ? this->gen_02_delay_19_reader != this->gen_02_delay_19_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_19_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_19_wrap))
    );
}

void gen_02_delay_19_write(number v) {
    this->gen_02_delay_19_writer = this->gen_02_delay_19_reader;
    this->gen_02_delay_19_buffer[(Index)this->gen_02_delay_19_writer] = v;
}

number gen_02_delay_19_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_19__maxdelay : size);
    number val = this->gen_02_delay_19_read(effectiveSize, 0);
    this->gen_02_delay_19_write(v);
    this->gen_02_delay_19_step();
    return val;
}

array<Index, 2> gen_02_delay_19_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_19_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_19_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_19_init() {
    auto result = this->gen_02_delay_19_calcSizeInSamples();
    this->gen_02_delay_19__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_19_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_19_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_19_clear() {
    this->gen_02_delay_19_buffer->setZero();
}

void gen_02_delay_19_reset() {
    auto result = this->gen_02_delay_19_calcSizeInSamples();
    this->gen_02_delay_19__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_19_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_19_buffer);
    this->gen_02_delay_19_wrap = this->gen_02_delay_19_buffer->getSize() - 1;
    this->gen_02_delay_19_clear();

    if (this->gen_02_delay_19_reader >= this->gen_02_delay_19__maxdelay || this->gen_02_delay_19_writer >= this->gen_02_delay_19__maxdelay) {
        this->gen_02_delay_19_reader = 0;
        this->gen_02_delay_19_writer = 0;
    }
}

void gen_02_delay_19_dspsetup() {
    this->gen_02_delay_19_reset();
}

number gen_02_delay_19_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_19_size() {
    return this->gen_02_delay_19__maxdelay;
}

void gen_02_delay_20_step() {
    this->gen_02_delay_20_reader++;

    if (this->gen_02_delay_20_reader >= (int)(this->gen_02_delay_20_buffer->getSize()))
        this->gen_02_delay_20_reader = 0;
}

number gen_02_delay_20_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (int)(this->gen_02_delay_20_buffer->getSize()) + this->gen_02_delay_20_reader - ((size > this->gen_02_delay_20__maxdelay ? this->gen_02_delay_20__maxdelay : (size < (1 + this->gen_02_delay_20_reader != this->gen_02_delay_20_writer) ? 1 + this->gen_02_delay_20_reader != this->gen_02_delay_20_writer : size)));
            long index1 = (long)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_20_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_20_wrap))
            ), this->gen_02_delay_20_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_20_wrap))
            ), this->gen_02_delay_20_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_20_wrap))
            ), this->gen_02_delay_20_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_20_wrap))
            ));
        }
    }

    number r = (int)(this->gen_02_delay_20_buffer->getSize()) + this->gen_02_delay_20_reader - ((size > this->gen_02_delay_20__maxdelay ? this->gen_02_delay_20__maxdelay : (size < (this->gen_02_delay_20_reader != this->gen_02_delay_20_writer) ? this->gen_02_delay_20_reader != this->gen_02_delay_20_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->gen_02_delay_20_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_20_wrap))
    );
}

void gen_02_delay_20_write(number v) {
    this->gen_02_delay_20_writer = this->gen_02_delay_20_reader;
    this->gen_02_delay_20_buffer[(Index)this->gen_02_delay_20_writer] = v;
}

number gen_02_delay_20_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_20__maxdelay : size);
    number val = this->gen_02_delay_20_read(effectiveSize, 0);
    this->gen_02_delay_20_write(v);
    this->gen_02_delay_20_step();
    return val;
}

array<Index, 2> gen_02_delay_20_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_20_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->gen_02_delay_20_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_20_init() {
    auto result = this->gen_02_delay_20_calcSizeInSamples();
    this->gen_02_delay_20__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_20_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_20_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_20_clear() {
    this->gen_02_delay_20_buffer->setZero();
}

void gen_02_delay_20_reset() {
    auto result = this->gen_02_delay_20_calcSizeInSamples();
    this->gen_02_delay_20__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_20_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_20_buffer);
    this->gen_02_delay_20_wrap = this->gen_02_delay_20_buffer->getSize() - 1;
    this->gen_02_delay_20_clear();

    if (this->gen_02_delay_20_reader >= this->gen_02_delay_20__maxdelay || this->gen_02_delay_20_writer >= this->gen_02_delay_20__maxdelay) {
        this->gen_02_delay_20_reader = 0;
        this->gen_02_delay_20_writer = 0;
    }
}

void gen_02_delay_20_dspsetup() {
    this->gen_02_delay_20_reset();
}

number gen_02_delay_20_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->samplerate();
}

number gen_02_delay_20_size() {
    return this->gen_02_delay_20__maxdelay;
}

number gen_02_history_21_getvalue() {
    return this->gen_02_history_21_value;
}

void gen_02_history_21_setvalue(number val) {
    this->gen_02_history_21_value = val;
}

void gen_02_history_21_reset() {
    this->gen_02_history_21_value = 0;
}

void gen_02_history_21_init() {
    this->gen_02_history_21_value = 0;
}

number gen_02_history_22_getvalue() {
    return this->gen_02_history_22_value;
}

void gen_02_history_22_setvalue(number val) {
    this->gen_02_history_22_value = val;
}

void gen_02_history_22_reset() {
    this->gen_02_history_22_value = 0;
}

void gen_02_history_22_init() {
    this->gen_02_history_22_value = 0;
}

number gen_02_history_23_getvalue() {
    return this->gen_02_history_23_value;
}

void gen_02_history_23_setvalue(number val) {
    this->gen_02_history_23_value = val;
}

void gen_02_history_23_reset() {
    this->gen_02_history_23_value = 0;
}

void gen_02_history_23_init() {
    this->gen_02_history_23_value = 0;
}

number gen_02_history_24_getvalue() {
    return this->gen_02_history_24_value;
}

void gen_02_history_24_setvalue(number val) {
    this->gen_02_history_24_value = val;
}

void gen_02_history_24_reset() {
    this->gen_02_history_24_value = 0;
}

void gen_02_history_24_init() {
    this->gen_02_history_24_value = 0;
}

number gen_02_history_25_getvalue() {
    return this->gen_02_history_25_value;
}

void gen_02_history_25_setvalue(number val) {
    this->gen_02_history_25_value = val;
}

void gen_02_history_25_reset() {
    this->gen_02_history_25_value = 0;
}

void gen_02_history_25_init() {
    this->gen_02_history_25_value = 0;
}

number gen_02_phasor_41_next(number freq, number reset) {
    RNBO_UNUSED(reset);
    number pincr = freq * this->gen_02_phasor_41_conv;

    if (this->gen_02_phasor_41_currentPhase < 0.)
        this->gen_02_phasor_41_currentPhase = 1. + this->gen_02_phasor_41_currentPhase;

    if (this->gen_02_phasor_41_currentPhase > 1.)
        this->gen_02_phasor_41_currentPhase = this->gen_02_phasor_41_currentPhase - 1.;

    number tmp = this->gen_02_phasor_41_currentPhase;
    this->gen_02_phasor_41_currentPhase += pincr;
    return tmp;
}

void gen_02_phasor_41_reset() {
    this->gen_02_phasor_41_currentPhase = 0;
}

void gen_02_phasor_41_dspsetup() {
    this->gen_02_phasor_41_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

number gen_02_cycle_43_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_43_ph_conv;

    if (this->gen_02_cycle_43_ph_currentPhase < 0.)
        this->gen_02_cycle_43_ph_currentPhase = 1. + this->gen_02_cycle_43_ph_currentPhase;

    if (this->gen_02_cycle_43_ph_currentPhase > 1.)
        this->gen_02_cycle_43_ph_currentPhase = this->gen_02_cycle_43_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_43_ph_currentPhase;
    this->gen_02_cycle_43_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_43_ph_reset() {
    this->gen_02_cycle_43_ph_currentPhase = 0;
}

void gen_02_cycle_43_ph_dspsetup() {
    this->gen_02_cycle_43_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_43_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_43_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_43_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_43_dspsetup() {
    this->gen_02_cycle_43_phasei = 0;
    this->gen_02_cycle_43_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_02_cycle_43_wrap = (long)(this->gen_02_cycle_43_buffer->getSize()) - 1;
}

void gen_02_cycle_43_reset() {
    this->gen_02_cycle_43_phasei = 0;
}

void gen_02_cycle_43_bufferUpdated() {
    this->gen_02_cycle_43_wrap = (long)(this->gen_02_cycle_43_buffer->getSize()) - 1;
}

number gen_02_cycle_50_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_50_ph_conv;

    if (this->gen_02_cycle_50_ph_currentPhase < 0.)
        this->gen_02_cycle_50_ph_currentPhase = 1. + this->gen_02_cycle_50_ph_currentPhase;

    if (this->gen_02_cycle_50_ph_currentPhase > 1.)
        this->gen_02_cycle_50_ph_currentPhase = this->gen_02_cycle_50_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_50_ph_currentPhase;
    this->gen_02_cycle_50_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_50_ph_reset() {
    this->gen_02_cycle_50_ph_currentPhase = 0;
}

void gen_02_cycle_50_ph_dspsetup() {
    this->gen_02_cycle_50_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_50_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_50_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_50_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_50_dspsetup() {
    this->gen_02_cycle_50_phasei = 0;
    this->gen_02_cycle_50_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_02_cycle_50_wrap = (long)(this->gen_02_cycle_50_buffer->getSize()) - 1;
}

void gen_02_cycle_50_reset() {
    this->gen_02_cycle_50_phasei = 0;
}

void gen_02_cycle_50_bufferUpdated() {
    this->gen_02_cycle_50_wrap = (long)(this->gen_02_cycle_50_buffer->getSize()) - 1;
}

number gen_02_dcblock_58_next(number x, number gain) {
    RNBO_UNUSED(gain);
    number y = x - this->gen_02_dcblock_58_xm1 + this->gen_02_dcblock_58_ym1 * 0.9997;
    this->gen_02_dcblock_58_xm1 = x;
    this->gen_02_dcblock_58_ym1 = y;
    return y;
}

void gen_02_dcblock_58_reset() {
    this->gen_02_dcblock_58_xm1 = 0;
    this->gen_02_dcblock_58_ym1 = 0;
}

void gen_02_dcblock_58_dspsetup() {
    this->gen_02_dcblock_58_reset();
}

number gen_02_cycle_63_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_63_ph_conv;

    if (this->gen_02_cycle_63_ph_currentPhase < 0.)
        this->gen_02_cycle_63_ph_currentPhase = 1. + this->gen_02_cycle_63_ph_currentPhase;

    if (this->gen_02_cycle_63_ph_currentPhase > 1.)
        this->gen_02_cycle_63_ph_currentPhase = this->gen_02_cycle_63_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_63_ph_currentPhase;
    this->gen_02_cycle_63_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_63_ph_reset() {
    this->gen_02_cycle_63_ph_currentPhase = 0;
}

void gen_02_cycle_63_ph_dspsetup() {
    this->gen_02_cycle_63_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_63_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_63_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_63_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_63_dspsetup() {
    this->gen_02_cycle_63_phasei = 0;
    this->gen_02_cycle_63_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_02_cycle_63_wrap = (long)(this->gen_02_cycle_63_buffer->getSize()) - 1;
}

void gen_02_cycle_63_reset() {
    this->gen_02_cycle_63_phasei = 0;
}

void gen_02_cycle_63_bufferUpdated() {
    this->gen_02_cycle_63_wrap = (long)(this->gen_02_cycle_63_buffer->getSize()) - 1;
}

number gen_02_dcblock_71_next(number x, number gain) {
    RNBO_UNUSED(gain);
    number y = x - this->gen_02_dcblock_71_xm1 + this->gen_02_dcblock_71_ym1 * 0.9997;
    this->gen_02_dcblock_71_xm1 = x;
    this->gen_02_dcblock_71_ym1 = y;
    return y;
}

void gen_02_dcblock_71_reset() {
    this->gen_02_dcblock_71_xm1 = 0;
    this->gen_02_dcblock_71_ym1 = 0;
}

void gen_02_dcblock_71_dspsetup() {
    this->gen_02_dcblock_71_reset();
}

number gen_02_cycle_118_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_118_ph_conv;

    if (this->gen_02_cycle_118_ph_currentPhase < 0.)
        this->gen_02_cycle_118_ph_currentPhase = 1. + this->gen_02_cycle_118_ph_currentPhase;

    if (this->gen_02_cycle_118_ph_currentPhase > 1.)
        this->gen_02_cycle_118_ph_currentPhase = this->gen_02_cycle_118_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_118_ph_currentPhase;
    this->gen_02_cycle_118_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_118_ph_reset() {
    this->gen_02_cycle_118_ph_currentPhase = 0;
}

void gen_02_cycle_118_ph_dspsetup() {
    this->gen_02_cycle_118_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_118_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_118_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_118_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_118_dspsetup() {
    this->gen_02_cycle_118_phasei = 0;
    this->gen_02_cycle_118_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_02_cycle_118_wrap = (long)(this->gen_02_cycle_118_buffer->getSize()) - 1;
}

void gen_02_cycle_118_reset() {
    this->gen_02_cycle_118_phasei = 0;
}

void gen_02_cycle_118_bufferUpdated() {
    this->gen_02_cycle_118_wrap = (long)(this->gen_02_cycle_118_buffer->getSize()) - 1;
}

number gen_02_cycle_135_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_135_ph_conv;

    if (this->gen_02_cycle_135_ph_currentPhase < 0.)
        this->gen_02_cycle_135_ph_currentPhase = 1. + this->gen_02_cycle_135_ph_currentPhase;

    if (this->gen_02_cycle_135_ph_currentPhase > 1.)
        this->gen_02_cycle_135_ph_currentPhase = this->gen_02_cycle_135_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_135_ph_currentPhase;
    this->gen_02_cycle_135_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_135_ph_reset() {
    this->gen_02_cycle_135_ph_currentPhase = 0;
}

void gen_02_cycle_135_ph_dspsetup() {
    this->gen_02_cycle_135_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_135_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_135_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_135_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_135_dspsetup() {
    this->gen_02_cycle_135_phasei = 0;
    this->gen_02_cycle_135_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_02_cycle_135_wrap = (long)(this->gen_02_cycle_135_buffer->getSize()) - 1;
}

void gen_02_cycle_135_reset() {
    this->gen_02_cycle_135_phasei = 0;
}

void gen_02_cycle_135_bufferUpdated() {
    this->gen_02_cycle_135_wrap = (long)(this->gen_02_cycle_135_buffer->getSize()) - 1;
}

number gen_02_cycle_144_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_144_ph_conv;

    if (this->gen_02_cycle_144_ph_currentPhase < 0.)
        this->gen_02_cycle_144_ph_currentPhase = 1. + this->gen_02_cycle_144_ph_currentPhase;

    if (this->gen_02_cycle_144_ph_currentPhase > 1.)
        this->gen_02_cycle_144_ph_currentPhase = this->gen_02_cycle_144_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_144_ph_currentPhase;
    this->gen_02_cycle_144_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_144_ph_reset() {
    this->gen_02_cycle_144_ph_currentPhase = 0;
}

void gen_02_cycle_144_ph_dspsetup() {
    this->gen_02_cycle_144_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_144_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_144_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_144_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_144_dspsetup() {
    this->gen_02_cycle_144_phasei = 0;
    this->gen_02_cycle_144_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_02_cycle_144_wrap = (long)(this->gen_02_cycle_144_buffer->getSize()) - 1;
}

void gen_02_cycle_144_reset() {
    this->gen_02_cycle_144_phasei = 0;
}

void gen_02_cycle_144_bufferUpdated() {
    this->gen_02_cycle_144_wrap = (long)(this->gen_02_cycle_144_buffer->getSize()) - 1;
}

number gen_02_cycle_161_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_161_ph_conv;

    if (this->gen_02_cycle_161_ph_currentPhase < 0.)
        this->gen_02_cycle_161_ph_currentPhase = 1. + this->gen_02_cycle_161_ph_currentPhase;

    if (this->gen_02_cycle_161_ph_currentPhase > 1.)
        this->gen_02_cycle_161_ph_currentPhase = this->gen_02_cycle_161_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_161_ph_currentPhase;
    this->gen_02_cycle_161_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_161_ph_reset() {
    this->gen_02_cycle_161_ph_currentPhase = 0;
}

void gen_02_cycle_161_ph_dspsetup() {
    this->gen_02_cycle_161_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_161_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_161_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_161_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_161_dspsetup() {
    this->gen_02_cycle_161_phasei = 0;
    this->gen_02_cycle_161_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_02_cycle_161_wrap = (long)(this->gen_02_cycle_161_buffer->getSize()) - 1;
}

void gen_02_cycle_161_reset() {
    this->gen_02_cycle_161_phasei = 0;
}

void gen_02_cycle_161_bufferUpdated() {
    this->gen_02_cycle_161_wrap = (long)(this->gen_02_cycle_161_buffer->getSize()) - 1;
}

number gen_02_cycle_186_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_186_ph_conv;

    if (this->gen_02_cycle_186_ph_currentPhase < 0.)
        this->gen_02_cycle_186_ph_currentPhase = 1. + this->gen_02_cycle_186_ph_currentPhase;

    if (this->gen_02_cycle_186_ph_currentPhase > 1.)
        this->gen_02_cycle_186_ph_currentPhase = this->gen_02_cycle_186_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_186_ph_currentPhase;
    this->gen_02_cycle_186_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_186_ph_reset() {
    this->gen_02_cycle_186_ph_currentPhase = 0;
}

void gen_02_cycle_186_ph_dspsetup() {
    this->gen_02_cycle_186_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_186_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        uint32_t uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_186_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_186_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_186_dspsetup() {
    this->gen_02_cycle_186_phasei = 0;
    this->gen_02_cycle_186_f2i = (this->samplerate() == 0. ? 0. : (number)4294967296 / this->samplerate());
    this->gen_02_cycle_186_wrap = (long)(this->gen_02_cycle_186_buffer->getSize()) - 1;
}

void gen_02_cycle_186_reset() {
    this->gen_02_cycle_186_phasei = 0;
}

void gen_02_cycle_186_bufferUpdated() {
    this->gen_02_cycle_186_wrap = (long)(this->gen_02_cycle_186_buffer->getSize()) - 1;
}

number gen_02_dcblock_233_next(number x, number gain) {
    RNBO_UNUSED(gain);
    number y = x - this->gen_02_dcblock_233_xm1 + this->gen_02_dcblock_233_ym1 * 0.9997;
    this->gen_02_dcblock_233_xm1 = x;
    this->gen_02_dcblock_233_ym1 = y;
    return y;
}

void gen_02_dcblock_233_reset() {
    this->gen_02_dcblock_233_xm1 = 0;
    this->gen_02_dcblock_233_ym1 = 0;
}

void gen_02_dcblock_233_dspsetup() {
    this->gen_02_dcblock_233_reset();
}

number gen_02_dcblock_239_next(number x, number gain) {
    RNBO_UNUSED(gain);
    number y = x - this->gen_02_dcblock_239_xm1 + this->gen_02_dcblock_239_ym1 * 0.9997;
    this->gen_02_dcblock_239_xm1 = x;
    this->gen_02_dcblock_239_ym1 = y;
    return y;
}

void gen_02_dcblock_239_reset() {
    this->gen_02_dcblock_239_xm1 = 0;
    this->gen_02_dcblock_239_ym1 = 0;
}

void gen_02_dcblock_239_dspsetup() {
    this->gen_02_dcblock_239_reset();
}

number gen_02_dcblock_277_next(number x, number gain) {
    RNBO_UNUSED(gain);
    number y = x - this->gen_02_dcblock_277_xm1 + this->gen_02_dcblock_277_ym1 * 0.9997;
    this->gen_02_dcblock_277_xm1 = x;
    this->gen_02_dcblock_277_ym1 = y;
    return y;
}

void gen_02_dcblock_277_reset() {
    this->gen_02_dcblock_277_xm1 = 0;
    this->gen_02_dcblock_277_ym1 = 0;
}

void gen_02_dcblock_277_dspsetup() {
    this->gen_02_dcblock_277_reset();
}

number gen_02_dcblock_283_next(number x, number gain) {
    RNBO_UNUSED(gain);
    number y = x - this->gen_02_dcblock_283_xm1 + this->gen_02_dcblock_283_ym1 * 0.9997;
    this->gen_02_dcblock_283_xm1 = x;
    this->gen_02_dcblock_283_ym1 = y;
    return y;
}

void gen_02_dcblock_283_reset() {
    this->gen_02_dcblock_283_xm1 = 0;
    this->gen_02_dcblock_283_ym1 = 0;
}

void gen_02_dcblock_283_dspsetup() {
    this->gen_02_dcblock_283_reset();
}

void gen_02_dspsetup(bool force) {
    if ((bool)(this->gen_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gen_02_setupDone = true;
    this->gen_02_delay_1_dspsetup();
    this->gen_02_delay_2_dspsetup();
    this->gen_02_delay_3_dspsetup();
    this->gen_02_delay_4_dspsetup();
    this->gen_02_delay_5_dspsetup();
    this->gen_02_delay_6_dspsetup();
    this->gen_02_delay_7_dspsetup();
    this->gen_02_delay_8_dspsetup();
    this->gen_02_delay_9_dspsetup();
    this->gen_02_delay_10_dspsetup();
    this->gen_02_delay_11_dspsetup();
    this->gen_02_delay_12_dspsetup();
    this->gen_02_delay_13_dspsetup();
    this->gen_02_delay_14_dspsetup();
    this->gen_02_delay_15_dspsetup();
    this->gen_02_delay_17_dspsetup();
    this->gen_02_delay_18_dspsetup();
    this->gen_02_delay_19_dspsetup();
    this->gen_02_delay_20_dspsetup();
    this->gen_02_phasor_41_dspsetup();
    this->gen_02_cycle_43_ph_dspsetup();
    this->gen_02_cycle_43_dspsetup();
    this->gen_02_cycle_50_ph_dspsetup();
    this->gen_02_cycle_50_dspsetup();
    this->gen_02_dcblock_58_dspsetup();
    this->gen_02_cycle_63_ph_dspsetup();
    this->gen_02_cycle_63_dspsetup();
    this->gen_02_dcblock_71_dspsetup();
    this->gen_02_cycle_118_ph_dspsetup();
    this->gen_02_cycle_118_dspsetup();
    this->gen_02_cycle_135_ph_dspsetup();
    this->gen_02_cycle_135_dspsetup();
    this->gen_02_cycle_144_ph_dspsetup();
    this->gen_02_cycle_144_dspsetup();
    this->gen_02_cycle_161_ph_dspsetup();
    this->gen_02_cycle_161_dspsetup();
    this->gen_02_cycle_186_ph_dspsetup();
    this->gen_02_cycle_186_dspsetup();
    this->gen_02_dcblock_233_dspsetup();
    this->gen_02_dcblock_239_dspsetup();
    this->gen_02_dcblock_277_dspsetup();
    this->gen_02_dcblock_283_dspsetup();
}

void toggle_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_02_value_number;
}

void toggle_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_02_value_number_set(preset["value"]);
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
}

void numberobj_17_init() {
    this->numberobj_17_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-87"), 1, this->_currentTime);
}

void numberobj_17_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_17_value;
}

void numberobj_17_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_17_value_set(preset["value"]);
}

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
}

void numberobj_18_init() {
    this->numberobj_18_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-68"), 1, this->_currentTime);
}

void numberobj_18_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_18_value;
}

void numberobj_18_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_18_value_set(preset["value"]);
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

void numberobj_19_init() {
    this->numberobj_19_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-136"), 1, this->_currentTime);
}

void numberobj_19_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_19_value;
}

void numberobj_19_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_19_value_set(preset["value"]);
}

void numberobj_20_init() {
    this->numberobj_20_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-139"), 1, this->_currentTime);
}

void numberobj_20_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_20_value;
}

void numberobj_20_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_20_value_set(preset["value"]);
}

void param_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_10_value;
}

void param_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_10_value_set(preset["value"]);
}

void numberobj_21_init() {
    this->numberobj_21_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-24"), 1, this->_currentTime);
}

void numberobj_21_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_21_value;
}

void numberobj_21_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_21_value_set(preset["value"]);
}

void param_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_11_value;
}

void param_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_11_value_set(preset["value"]);
}

void numberobj_22_init() {
    this->numberobj_22_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-103"), 1, this->_currentTime);
}

void numberobj_22_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_22_value;
}

void numberobj_22_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_22_value_set(preset["value"]);
}

void param_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_12_value;
}

void param_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_12_value_set(preset["value"]);
}

void numberobj_23_init() {
    this->numberobj_23_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-105"), 1, this->_currentTime);
}

void numberobj_23_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_23_value;
}

void numberobj_23_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_23_value_set(preset["value"]);
}

void param_13_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_13_value;
}

void param_13_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_13_value_set(preset["value"]);
}

void numberobj_24_init() {
    this->numberobj_24_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-6"), 1, this->_currentTime);
}

void numberobj_24_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_24_value;
}

void numberobj_24_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_24_value_set(preset["value"]);
}

void param_14_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_14_value;
}

void param_14_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_14_value_set(preset["value"]);
}

void param_15_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_15_value;
}

void param_15_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_15_value_set(preset["value"]);
}

void param_16_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_16_value;
}

void param_16_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_16_value_set(preset["value"]);
}

void param_17_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_17_value;
}

void param_17_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_17_value_set(preset["value"]);
}

void param_18_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_18_value;
}

void param_18_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_18_value_set(preset["value"]);
}

void param_19_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_19_value;
}

void param_19_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_19_value_set(preset["value"]);
}

void globaltransport_advance() {}

void globaltransport_dspsetup(bool ) {}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    param_01_value = 4;
    param_02_value = 20;
    param_03_value = 0.1;
    param_04_value = 0.1;
    numberobj_15_value = 0;
    numberobj_15_value_setter(numberobj_15_value);
    param_05_value = 0.535;
    param_06_value = 60;
    scale_05_inlow = 0;
    scale_05_inhigh = 100;
    scale_05_outlow = 0.2;
    scale_05_outhigh = 1;
    scale_05_power = 0.5;
    dspexpr_05_in1 = 0;
    dspexpr_05_in2 = -1;
    dspexpr_05_in3 = 1;
    numberobj_16_value = 0;
    numberobj_16_value_setter(numberobj_16_value);
    p_01_target = 0;
    gen_01_in1 = 0;
    gen_01_in2 = 0;
    gen_01_dry_wet = 1;
    gen_01_lfo1_bw = 1;
    gen_01_lpf = 8000;
    gen_01_fbc = 0.88;
    gen_01_emphasis = 0;
    gen_01_ptch = 0;
    gen_01_decay = 0.82;
    gen_01_ptch_ratio = 4;
    gen_01_InGain = 1;
    gen_01_modulation = 1;
    gen_01_lfo1_rate = 0.2;
    gen_01_d1 = 120;
    gen_01_g1 = 0.5;
    gen_01_d2 = 76;
    gen_01_g2 = 0.25;
    gen_01_d3 = 30;
    gen_01_g3 = 0.25;
    gen_01_d4 = 8;
    gen_01_g4 = 0.3;
    gen_01_d5 = 12;
    gen_01_g5 = 0.3;
    gen_01_d6 = 4;
    gen_01_d7 = 17;
    gen_01_d8 = 31;
    gen_01_d9 = 3;
    gen_01_d10 = 87;
    gen_01_g10 = 0.5;
    gen_01_d11 = 62;
    gen_01_g11 = 0.25;
    gen_01_damp = 2400;
    gen_01_dL1 = 111;
    gen_01_gL1 = 0.5;
    gen_01_dL2 = 37;
    gen_01_gL2 = 0.25;
    gen_01_dL3 = 15;
    gen_01_gL3 = 0.25;
    gen_01_dL4 = 8;
    gen_01_gL4 = 0.3;
    gen_01_dL5 = 12;
    gen_01_gL5 = 0.3;
    gen_01_dL6 = 3.9;
    gen_01_dL7 = 31;
    gen_01_dL8 = 17;
    gen_01_dL9 = 8;
    gen_01_dL10 = 43;
    gen_01_gL10 = 0.5;
    gen_01_dL11 = 44;
    gen_01_gL11 = 0.25;
    gen_01_dampL = 2400;
    p_02_target = 0;
    p_03_target = 0;
    p_04_target = 0;
    p_05_target = 0;
    gen_02_in1 = 0;
    gen_02_in2 = 0;
    gen_02_pre_del = 0;
    gen_02_lfo1_bw = 1;
    gen_02_fb1 = 0.1;
    gen_02_lp = 1;
    gen_02_decay2 = 0.82;
    gen_02_lpf = 8000;
    gen_02_x_fb = 0.1;
    gen_02_lfo1_rate = 0.2;
    gen_02_diff_gain = 0.2;
    gen_02_apf_g = 0.635;
    gen_02_mixfdn = 1;
    gen_02_diff_num = 4;
    p_06_target = 0;
    p_07_target = 0;
    dspexpr_06_in1 = 0;
    dspexpr_06_in2 = -1;
    dspexpr_06_in3 = 1;
    toggle_02_value_number = 0;
    toggle_02_value_number_setter(toggle_02_value_number);
    param_07_value = 0;
    numberobj_17_value = 0;
    numberobj_17_value_setter(numberobj_17_value);
    param_08_value = 50;
    numberobj_18_value = 0;
    numberobj_18_value_setter(numberobj_18_value);
    param_09_value = 0;
    numberobj_19_value = 0;
    numberobj_19_value_setter(numberobj_19_value);
    expr_07_in1 = 0;
    expr_07_in2 = 100;
    expr_07_out1 = 0;
    linetilde_08_time = 10;
    linetilde_08_keepramp = 1;
    numberobj_20_value = 0;
    numberobj_20_value_setter(numberobj_20_value);
    param_10_value = 50;
    numberobj_21_value = 0;
    numberobj_21_value_setter(numberobj_21_value);
    param_11_value = 20;
    numberobj_22_value = 0;
    numberobj_22_value_setter(numberobj_22_value);
    param_12_value = 0;
    numberobj_23_value = 0;
    numberobj_23_value_setter(numberobj_23_value);
    param_13_value = 0;
    numberobj_24_value = 0;
    numberobj_24_value_setter(numberobj_24_value);
    param_14_value = 8000;
    param_15_value = 0.3;
    scale_06_inlow = 0;
    scale_06_inhigh = 100;
    scale_06_outlow = 0.1;
    scale_06_outhigh = 1;
    scale_06_power = 1;
    param_16_value = 50;
    scale_07_inlow = 0;
    scale_07_inhigh = 100;
    scale_07_outlow = 0;
    scale_07_outhigh = 1;
    scale_07_power = 1;
    param_17_value = 90;
    param_18_value = 0.3;
    scale_08_inlow = 100;
    scale_08_inhigh = 0;
    scale_08_outlow = 500;
    scale_08_outhigh = 16000;
    scale_08_power = 1;
    param_19_value = 20;
    ctlin_01_input = 0;
    ctlin_01_controller = 1;
    ctlin_01_channel = -1;
    expr_04_in1 = 0;
    expr_04_in2 = 0.007874015748;
    expr_04_out1 = 0;
    ctlin_02_input = 0;
    ctlin_02_controller = 9;
    ctlin_02_channel = -1;
    expr_05_in1 = 0;
    expr_05_in2 = 0.007874015748;
    expr_05_out1 = 0;
    ctlin_03_input = 0;
    ctlin_03_controller = 9;
    ctlin_03_channel = -1;
    expr_06_in1 = 0;
    expr_06_in2 = 0.007874015748;
    expr_06_out1 = 0;
    ctlin_04_input = 0;
    ctlin_04_controller = 6;
    ctlin_04_channel = -1;
    expr_08_in1 = 0;
    expr_08_in2 = 0.007874015748;
    expr_08_out1 = 0;
    ctlin_05_input = 0;
    ctlin_05_controller = 1;
    ctlin_05_channel = -1;
    expr_09_in1 = 0;
    expr_09_in2 = 0.007874015748;
    expr_09_out1 = 0;
    ctlin_06_input = 0;
    ctlin_06_controller = 6;
    ctlin_06_channel = -1;
    expr_10_in1 = 0;
    expr_10_in2 = 0.007874015748;
    expr_10_out1 = 0;
    ctlin_07_input = 0;
    ctlin_07_controller = 5;
    ctlin_07_channel = -1;
    expr_11_in1 = 0;
    expr_11_in2 = 0.007874015748;
    expr_11_out1 = 0;
    ctlin_08_input = 0;
    ctlin_08_controller = 7;
    ctlin_08_channel = -1;
    expr_12_in1 = 0;
    expr_12_in2 = 0.007874015748;
    expr_12_out1 = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    signals[3] = nullptr;
    signals[4] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    param_01_lastValue = 0;
    param_02_lastValue = 0;
    param_03_lastValue = 0;
    param_04_lastValue = 0;
    numberobj_15_currentFormat = 6;
    numberobj_15_lastValue = 0;
    param_05_lastValue = 0;
    param_06_lastValue = 0;
    numberobj_16_currentFormat = 6;
    numberobj_16_lastValue = 0;
    gen_01_delay_1__maxdelay = 0;
    gen_01_delay_1_sizemode = 0;
    gen_01_delay_1_wrap = 0;
    gen_01_delay_1_reader = 0;
    gen_01_delay_1_writer = 0;
    gen_01_delay_2__maxdelay = 0;
    gen_01_delay_2_sizemode = 0;
    gen_01_delay_2_wrap = 0;
    gen_01_delay_2_reader = 0;
    gen_01_delay_2_writer = 0;
    gen_01_history_3_value = 0;
    gen_01_history_4_value = 0;
    gen_01_delay_5__maxdelay = 0;
    gen_01_delay_5_sizemode = 0;
    gen_01_delay_5_wrap = 0;
    gen_01_delay_5_reader = 0;
    gen_01_delay_5_writer = 0;
    gen_01_history_6_value = 0;
    gen_01_DL1__maxdelay = 0;
    gen_01_DL1_sizemode = 0;
    gen_01_DL1_wrap = 0;
    gen_01_DL1_reader = 0;
    gen_01_DL1_writer = 0;
    gen_01_DL2__maxdelay = 0;
    gen_01_DL2_sizemode = 0;
    gen_01_DL2_wrap = 0;
    gen_01_DL2_reader = 0;
    gen_01_DL2_writer = 0;
    gen_01_DL3__maxdelay = 0;
    gen_01_DL3_sizemode = 0;
    gen_01_DL3_wrap = 0;
    gen_01_DL3_reader = 0;
    gen_01_DL3_writer = 0;
    gen_01_DL4__maxdelay = 0;
    gen_01_DL4_sizemode = 0;
    gen_01_DL4_wrap = 0;
    gen_01_DL4_reader = 0;
    gen_01_DL4_writer = 0;
    gen_01_DL5__maxdelay = 0;
    gen_01_DL5_sizemode = 0;
    gen_01_DL5_wrap = 0;
    gen_01_DL5_reader = 0;
    gen_01_DL5_writer = 0;
    gen_01_DL6__maxdelay = 0;
    gen_01_DL6_sizemode = 0;
    gen_01_DL6_wrap = 0;
    gen_01_DL6_reader = 0;
    gen_01_DL6_writer = 0;
    gen_01_DL7__maxdelay = 0;
    gen_01_DL7_sizemode = 0;
    gen_01_DL7_wrap = 0;
    gen_01_DL7_reader = 0;
    gen_01_DL7_writer = 0;
    gen_01_DL8__maxdelay = 0;
    gen_01_DL8_sizemode = 0;
    gen_01_DL8_wrap = 0;
    gen_01_DL8_reader = 0;
    gen_01_DL8_writer = 0;
    gen_01_DL9__maxdelay = 0;
    gen_01_DL9_sizemode = 0;
    gen_01_DL9_wrap = 0;
    gen_01_DL9_reader = 0;
    gen_01_DL9_writer = 0;
    gen_01_DL10__maxdelay = 0;
    gen_01_DL10_sizemode = 0;
    gen_01_DL10_wrap = 0;
    gen_01_DL10_reader = 0;
    gen_01_DL10_writer = 0;
    gen_01_DL11__maxdelay = 0;
    gen_01_DL11_sizemode = 0;
    gen_01_DL11_wrap = 0;
    gen_01_DL11_reader = 0;
    gen_01_DL11_writer = 0;
    gen_01_DL12__maxdelay = 0;
    gen_01_DL12_sizemode = 0;
    gen_01_DL12_wrap = 0;
    gen_01_DL12_reader = 0;
    gen_01_DL12_writer = 0;
    gen_01_DL13__maxdelay = 0;
    gen_01_DL13_sizemode = 0;
    gen_01_DL13_wrap = 0;
    gen_01_DL13_reader = 0;
    gen_01_DL13_writer = 0;
    gen_01_feedback_value = 0;
    gen_01_filterOutput_value = 0;
    gen_01_history_7_value = 0;
    gen_01_history_8_value = 0;
    gen_01_delay_9__maxdelay = 0;
    gen_01_delay_9_sizemode = 0;
    gen_01_delay_9_wrap = 0;
    gen_01_delay_9_reader = 0;
    gen_01_delay_9_writer = 0;
    gen_01_history_10_value = 0;
    gen_01_dlL1__maxdelay = 0;
    gen_01_dlL1_sizemode = 0;
    gen_01_dlL1_wrap = 0;
    gen_01_dlL1_reader = 0;
    gen_01_dlL1_writer = 0;
    gen_01_dlL2__maxdelay = 0;
    gen_01_dlL2_sizemode = 0;
    gen_01_dlL2_wrap = 0;
    gen_01_dlL2_reader = 0;
    gen_01_dlL2_writer = 0;
    gen_01_dlL3__maxdelay = 0;
    gen_01_dlL3_sizemode = 0;
    gen_01_dlL3_wrap = 0;
    gen_01_dlL3_reader = 0;
    gen_01_dlL3_writer = 0;
    gen_01_dlL4__maxdelay = 0;
    gen_01_dlL4_sizemode = 0;
    gen_01_dlL4_wrap = 0;
    gen_01_dlL4_reader = 0;
    gen_01_dlL4_writer = 0;
    gen_01_dlL5__maxdelay = 0;
    gen_01_dlL5_sizemode = 0;
    gen_01_dlL5_wrap = 0;
    gen_01_dlL5_reader = 0;
    gen_01_dlL5_writer = 0;
    gen_01_dlL6__maxdelay = 0;
    gen_01_dlL6_sizemode = 0;
    gen_01_dlL6_wrap = 0;
    gen_01_dlL6_reader = 0;
    gen_01_dlL6_writer = 0;
    gen_01_dlL7__maxdelay = 0;
    gen_01_dlL7_sizemode = 0;
    gen_01_dlL7_wrap = 0;
    gen_01_dlL7_reader = 0;
    gen_01_dlL7_writer = 0;
    gen_01_dlL8__maxdelay = 0;
    gen_01_dlL8_sizemode = 0;
    gen_01_dlL8_wrap = 0;
    gen_01_dlL8_reader = 0;
    gen_01_dlL8_writer = 0;
    gen_01_dlL9__maxdelay = 0;
    gen_01_dlL9_sizemode = 0;
    gen_01_dlL9_wrap = 0;
    gen_01_dlL9_reader = 0;
    gen_01_dlL9_writer = 0;
    gen_01_dlL10__maxdelay = 0;
    gen_01_dlL10_sizemode = 0;
    gen_01_dlL10_wrap = 0;
    gen_01_dlL10_reader = 0;
    gen_01_dlL10_writer = 0;
    gen_01_dlL11__maxdelay = 0;
    gen_01_dlL11_sizemode = 0;
    gen_01_dlL11_wrap = 0;
    gen_01_dlL11_reader = 0;
    gen_01_dlL11_writer = 0;
    gen_01_dlL12__maxdelay = 0;
    gen_01_dlL12_sizemode = 0;
    gen_01_dlL12_wrap = 0;
    gen_01_dlL12_reader = 0;
    gen_01_dlL12_writer = 0;
    gen_01_dlL13__maxdelay = 0;
    gen_01_dlL13_sizemode = 0;
    gen_01_dlL13_wrap = 0;
    gen_01_dlL13_reader = 0;
    gen_01_dlL13_writer = 0;
    gen_01_feedbackL_value = 0;
    gen_01_filterOutputL_value = 0;
    gen_01_history_11_value = 0;
    gen_01_history_12_value = 0;
    gen_01_phasor_4_currentPhase = 0;
    gen_01_phasor_4_conv = 0;
    gen_01_cycle_6_ph_currentPhase = 0;
    gen_01_cycle_6_ph_conv = 0;
    gen_01_cycle_6_wrap = 0;
    gen_01_cycle_11_ph_currentPhase = 0;
    gen_01_cycle_11_ph_conv = 0;
    gen_01_cycle_11_wrap = 0;
    gen_01_cycle_16_ph_currentPhase = 0;
    gen_01_cycle_16_ph_conv = 0;
    gen_01_cycle_16_wrap = 0;
    gen_01_cycle_21_ph_currentPhase = 0;
    gen_01_cycle_21_ph_conv = 0;
    gen_01_cycle_21_wrap = 0;
    gen_01_cycle_26_ph_currentPhase = 0;
    gen_01_cycle_26_ph_conv = 0;
    gen_01_cycle_26_wrap = 0;
    gen_01_cycle_31_ph_currentPhase = 0;
    gen_01_cycle_31_ph_conv = 0;
    gen_01_cycle_31_wrap = 0;
    gen_01_cycle_36_ph_currentPhase = 0;
    gen_01_cycle_36_ph_conv = 0;
    gen_01_cycle_36_wrap = 0;
    gen_01_cycle_41_ph_currentPhase = 0;
    gen_01_cycle_41_ph_conv = 0;
    gen_01_cycle_41_wrap = 0;
    gen_01_cycle_46_ph_currentPhase = 0;
    gen_01_cycle_46_ph_conv = 0;
    gen_01_cycle_46_wrap = 0;
    gen_01_cycle_54_ph_currentPhase = 0;
    gen_01_cycle_54_ph_conv = 0;
    gen_01_cycle_54_wrap = 0;
    gen_01_slide_69_prev = 0;
    gen_01_phasor_105_currentPhase = 0;
    gen_01_phasor_105_conv = 0;
    gen_01_delta_109_prev = 0;
    gen_01_sah_111_prev = 0;
    gen_01_sah_111_value = 0;
    gen_01_delta_120_prev = 0;
    gen_01_sah_122_prev = 0;
    gen_01_sah_122_value = 0;
    gen_01_delta_131_prev = 0;
    gen_01_sah_134_prev = 0;
    gen_01_sah_134_value = 0;
    gen_01_delta_143_prev = 0;
    gen_01_sah_145_prev = 0;
    gen_01_sah_145_value = 0;
    gen_01_dcblock_223_xm1 = 0;
    gen_01_dcblock_223_ym1 = 0;
    gen_01_slide_229_prev = 0;
    gen_01_phasor_265_currentPhase = 0;
    gen_01_phasor_265_conv = 0;
    gen_01_delta_269_prev = 0;
    gen_01_sah_271_prev = 0;
    gen_01_sah_271_value = 0;
    gen_01_delta_280_prev = 0;
    gen_01_sah_282_prev = 0;
    gen_01_sah_282_value = 0;
    gen_01_delta_291_prev = 0;
    gen_01_sah_293_prev = 0;
    gen_01_sah_293_value = 0;
    gen_01_delta_302_prev = 0;
    gen_01_sah_304_prev = 0;
    gen_01_sah_304_value = 0;
    gen_01_dcblock_372_xm1 = 0;
    gen_01_dcblock_372_ym1 = 0;
    gen_01_setupDone = false;
    gen_02_delay_1__maxdelay = 0;
    gen_02_delay_1_sizemode = 0;
    gen_02_delay_1_wrap = 0;
    gen_02_delay_1_reader = 0;
    gen_02_delay_1_writer = 0;
    gen_02_delay_2__maxdelay = 0;
    gen_02_delay_2_sizemode = 0;
    gen_02_delay_2_wrap = 0;
    gen_02_delay_2_reader = 0;
    gen_02_delay_2_writer = 0;
    gen_02_delay_3__maxdelay = 0;
    gen_02_delay_3_sizemode = 0;
    gen_02_delay_3_wrap = 0;
    gen_02_delay_3_reader = 0;
    gen_02_delay_3_writer = 0;
    gen_02_delay_4__maxdelay = 0;
    gen_02_delay_4_sizemode = 0;
    gen_02_delay_4_wrap = 0;
    gen_02_delay_4_reader = 0;
    gen_02_delay_4_writer = 0;
    gen_02_delay_5__maxdelay = 0;
    gen_02_delay_5_sizemode = 0;
    gen_02_delay_5_wrap = 0;
    gen_02_delay_5_reader = 0;
    gen_02_delay_5_writer = 0;
    gen_02_delay_6__maxdelay = 0;
    gen_02_delay_6_sizemode = 0;
    gen_02_delay_6_wrap = 0;
    gen_02_delay_6_reader = 0;
    gen_02_delay_6_writer = 0;
    gen_02_delay_7__maxdelay = 0;
    gen_02_delay_7_sizemode = 0;
    gen_02_delay_7_wrap = 0;
    gen_02_delay_7_reader = 0;
    gen_02_delay_7_writer = 0;
    gen_02_delay_8__maxdelay = 0;
    gen_02_delay_8_sizemode = 0;
    gen_02_delay_8_wrap = 0;
    gen_02_delay_8_reader = 0;
    gen_02_delay_8_writer = 0;
    gen_02_delay_9__maxdelay = 0;
    gen_02_delay_9_sizemode = 0;
    gen_02_delay_9_wrap = 0;
    gen_02_delay_9_reader = 0;
    gen_02_delay_9_writer = 0;
    gen_02_delay_10__maxdelay = 0;
    gen_02_delay_10_sizemode = 0;
    gen_02_delay_10_wrap = 0;
    gen_02_delay_10_reader = 0;
    gen_02_delay_10_writer = 0;
    gen_02_delay_11__maxdelay = 0;
    gen_02_delay_11_sizemode = 0;
    gen_02_delay_11_wrap = 0;
    gen_02_delay_11_reader = 0;
    gen_02_delay_11_writer = 0;
    gen_02_delay_12__maxdelay = 0;
    gen_02_delay_12_sizemode = 0;
    gen_02_delay_12_wrap = 0;
    gen_02_delay_12_reader = 0;
    gen_02_delay_12_writer = 0;
    gen_02_delay_13__maxdelay = 0;
    gen_02_delay_13_sizemode = 0;
    gen_02_delay_13_wrap = 0;
    gen_02_delay_13_reader = 0;
    gen_02_delay_13_writer = 0;
    gen_02_delay_14__maxdelay = 0;
    gen_02_delay_14_sizemode = 0;
    gen_02_delay_14_wrap = 0;
    gen_02_delay_14_reader = 0;
    gen_02_delay_14_writer = 0;
    gen_02_delay_15__maxdelay = 0;
    gen_02_delay_15_sizemode = 0;
    gen_02_delay_15_wrap = 0;
    gen_02_delay_15_reader = 0;
    gen_02_delay_15_writer = 0;
    gen_02_history_16_value = 0;
    gen_02_delay_17__maxdelay = 0;
    gen_02_delay_17_sizemode = 0;
    gen_02_delay_17_wrap = 0;
    gen_02_delay_17_reader = 0;
    gen_02_delay_17_writer = 0;
    gen_02_delay_18__maxdelay = 0;
    gen_02_delay_18_sizemode = 0;
    gen_02_delay_18_wrap = 0;
    gen_02_delay_18_reader = 0;
    gen_02_delay_18_writer = 0;
    gen_02_delay_19__maxdelay = 0;
    gen_02_delay_19_sizemode = 0;
    gen_02_delay_19_wrap = 0;
    gen_02_delay_19_reader = 0;
    gen_02_delay_19_writer = 0;
    gen_02_delay_20__maxdelay = 0;
    gen_02_delay_20_sizemode = 0;
    gen_02_delay_20_wrap = 0;
    gen_02_delay_20_reader = 0;
    gen_02_delay_20_writer = 0;
    gen_02_history_21_value = 0;
    gen_02_history_22_value = 0;
    gen_02_history_23_value = 0;
    gen_02_history_24_value = 0;
    gen_02_history_25_value = 0;
    gen_02_phasor_41_currentPhase = 0;
    gen_02_phasor_41_conv = 0;
    gen_02_cycle_43_ph_currentPhase = 0;
    gen_02_cycle_43_ph_conv = 0;
    gen_02_cycle_43_wrap = 0;
    gen_02_cycle_50_ph_currentPhase = 0;
    gen_02_cycle_50_ph_conv = 0;
    gen_02_cycle_50_wrap = 0;
    gen_02_dcblock_58_xm1 = 0;
    gen_02_dcblock_58_ym1 = 0;
    gen_02_cycle_63_ph_currentPhase = 0;
    gen_02_cycle_63_ph_conv = 0;
    gen_02_cycle_63_wrap = 0;
    gen_02_dcblock_71_xm1 = 0;
    gen_02_dcblock_71_ym1 = 0;
    gen_02_cycle_118_ph_currentPhase = 0;
    gen_02_cycle_118_ph_conv = 0;
    gen_02_cycle_118_wrap = 0;
    gen_02_cycle_135_ph_currentPhase = 0;
    gen_02_cycle_135_ph_conv = 0;
    gen_02_cycle_135_wrap = 0;
    gen_02_cycle_144_ph_currentPhase = 0;
    gen_02_cycle_144_ph_conv = 0;
    gen_02_cycle_144_wrap = 0;
    gen_02_cycle_161_ph_currentPhase = 0;
    gen_02_cycle_161_ph_conv = 0;
    gen_02_cycle_161_wrap = 0;
    gen_02_cycle_186_ph_currentPhase = 0;
    gen_02_cycle_186_ph_conv = 0;
    gen_02_cycle_186_wrap = 0;
    gen_02_dcblock_233_xm1 = 0;
    gen_02_dcblock_233_ym1 = 0;
    gen_02_dcblock_239_xm1 = 0;
    gen_02_dcblock_239_ym1 = 0;
    gen_02_dcblock_277_xm1 = 0;
    gen_02_dcblock_277_ym1 = 0;
    gen_02_dcblock_283_xm1 = 0;
    gen_02_dcblock_283_ym1 = 0;
    gen_02_setupDone = false;
    toggle_02_lastValue = 0;
    param_07_lastValue = 0;
    numberobj_17_currentFormat = 6;
    numberobj_17_lastValue = 0;
    param_08_lastValue = 0;
    numberobj_18_currentFormat = 6;
    numberobj_18_lastValue = 0;
    param_09_lastValue = 0;
    numberobj_19_currentFormat = 6;
    numberobj_19_lastValue = 0;
    linetilde_08_currentValue = 0;
    numberobj_20_currentFormat = 6;
    numberobj_20_lastValue = 0;
    param_10_lastValue = 0;
    numberobj_21_currentFormat = 6;
    numberobj_21_lastValue = 0;
    param_11_lastValue = 0;
    numberobj_22_currentFormat = 6;
    numberobj_22_lastValue = 0;
    param_12_lastValue = 0;
    numberobj_23_currentFormat = 6;
    numberobj_23_lastValue = 0;
    param_13_lastValue = 0;
    numberobj_24_currentFormat = 6;
    numberobj_24_lastValue = 0;
    param_14_lastValue = 0;
    param_15_lastValue = 0;
    param_16_lastValue = 0;
    param_17_lastValue = 0;
    param_18_lastValue = 0;
    param_19_lastValue = 0;
    ctlin_01_status = 0;
    ctlin_01_byte1 = -1;
    ctlin_01_inchan = 0;
    ctlin_02_status = 0;
    ctlin_02_byte1 = -1;
    ctlin_02_inchan = 0;
    ctlin_03_status = 0;
    ctlin_03_byte1 = -1;
    ctlin_03_inchan = 0;
    ctlin_04_status = 0;
    ctlin_04_byte1 = -1;
    ctlin_04_inchan = 0;
    ctlin_05_status = 0;
    ctlin_05_byte1 = -1;
    ctlin_05_inchan = 0;
    ctlin_06_status = 0;
    ctlin_06_byte1 = -1;
    ctlin_06_inchan = 0;
    ctlin_07_status = 0;
    ctlin_07_byte1 = -1;
    ctlin_07_inchan = 0;
    ctlin_08_status = 0;
    ctlin_08_byte1 = -1;
    ctlin_08_inchan = 0;
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number param_01_value;
    number param_02_value;
    number param_03_value;
    number param_04_value;
    number numberobj_15_value;
    number param_05_value;
    number param_06_value;
    list scale_05_input;
    number scale_05_inlow;
    number scale_05_inhigh;
    number scale_05_outlow;
    number scale_05_outhigh;
    number scale_05_power;
    list scale_05_out;
    number dspexpr_05_in1;
    number dspexpr_05_in2;
    number dspexpr_05_in3;
    number numberobj_16_value;
    number p_01_target;
    number gen_01_in1;
    number gen_01_in2;
    number gen_01_dry_wet;
    number gen_01_lfo1_bw;
    number gen_01_lpf;
    number gen_01_fbc;
    number gen_01_emphasis;
    number gen_01_ptch;
    number gen_01_decay;
    number gen_01_ptch_ratio;
    number gen_01_InGain;
    number gen_01_modulation;
    number gen_01_lfo1_rate;
    number gen_01_d1;
    number gen_01_g1;
    number gen_01_d2;
    number gen_01_g2;
    number gen_01_d3;
    number gen_01_g3;
    number gen_01_d4;
    number gen_01_g4;
    number gen_01_d5;
    number gen_01_g5;
    number gen_01_d6;
    number gen_01_d7;
    number gen_01_d8;
    number gen_01_d9;
    number gen_01_d10;
    number gen_01_g10;
    number gen_01_d11;
    number gen_01_g11;
    number gen_01_damp;
    number gen_01_dL1;
    number gen_01_gL1;
    number gen_01_dL2;
    number gen_01_gL2;
    number gen_01_dL3;
    number gen_01_gL3;
    number gen_01_dL4;
    number gen_01_gL4;
    number gen_01_dL5;
    number gen_01_gL5;
    number gen_01_dL6;
    number gen_01_dL7;
    number gen_01_dL8;
    number gen_01_dL9;
    number gen_01_dL10;
    number gen_01_gL10;
    number gen_01_dL11;
    number gen_01_gL11;
    number gen_01_dampL;
    number p_02_target;
    number p_03_target;
    number p_04_target;
    number p_05_target;
    number gen_02_in1;
    number gen_02_in2;
    number gen_02_pre_del;
    number gen_02_lfo1_bw;
    number gen_02_fb1;
    number gen_02_lp;
    number gen_02_decay2;
    number gen_02_lpf;
    number gen_02_x_fb;
    number gen_02_lfo1_rate;
    number gen_02_diff_gain;
    number gen_02_apf_g;
    number gen_02_mixfdn;
    number gen_02_diff_num;
    number p_06_target;
    number p_07_target;
    number dspexpr_06_in1;
    number dspexpr_06_in2;
    number dspexpr_06_in3;
    number toggle_02_value_number;
    number param_07_value;
    number numberobj_17_value;
    number param_08_value;
    number numberobj_18_value;
    number param_09_value;
    number numberobj_19_value;
    number expr_07_in1;
    number expr_07_in2;
    number expr_07_out1;
    list linetilde_08_segments;
    number linetilde_08_time;
    number linetilde_08_keepramp;
    number numberobj_20_value;
    number param_10_value;
    number numberobj_21_value;
    number param_11_value;
    number numberobj_22_value;
    number param_12_value;
    number numberobj_23_value;
    number param_13_value;
    number numberobj_24_value;
    number param_14_value;
    number param_15_value;
    list scale_06_input;
    number scale_06_inlow;
    number scale_06_inhigh;
    number scale_06_outlow;
    number scale_06_outhigh;
    number scale_06_power;
    list scale_06_out;
    number param_16_value;
    list scale_07_input;
    number scale_07_inlow;
    number scale_07_inhigh;
    number scale_07_outlow;
    number scale_07_outhigh;
    number scale_07_power;
    list scale_07_out;
    number param_17_value;
    number param_18_value;
    list scale_08_input;
    number scale_08_inlow;
    number scale_08_inhigh;
    number scale_08_outlow;
    number scale_08_outhigh;
    number scale_08_power;
    list scale_08_out;
    number param_19_value;
    number ctlin_01_input;
    number ctlin_01_controller;
    number ctlin_01_channel;
    number expr_04_in1;
    number expr_04_in2;
    number expr_04_out1;
    number ctlin_02_input;
    number ctlin_02_controller;
    number ctlin_02_channel;
    number expr_05_in1;
    number expr_05_in2;
    number expr_05_out1;
    number ctlin_03_input;
    number ctlin_03_controller;
    number ctlin_03_channel;
    number expr_06_in1;
    number expr_06_in2;
    number expr_06_out1;
    number ctlin_04_input;
    number ctlin_04_controller;
    number ctlin_04_channel;
    number expr_08_in1;
    number expr_08_in2;
    number expr_08_out1;
    number ctlin_05_input;
    number ctlin_05_controller;
    number ctlin_05_channel;
    number expr_09_in1;
    number expr_09_in2;
    number expr_09_out1;
    number ctlin_06_input;
    number ctlin_06_controller;
    number ctlin_06_channel;
    number expr_10_in1;
    number expr_10_in2;
    number expr_10_out1;
    number ctlin_07_input;
    number ctlin_07_controller;
    number ctlin_07_channel;
    number expr_11_in1;
    number expr_11_in2;
    number expr_11_out1;
    number ctlin_08_input;
    number ctlin_08_controller;
    number ctlin_08_channel;
    number expr_12_in1;
    number expr_12_in2;
    number expr_12_out1;
    MillisecondTime _currentTime;
    UInt64 audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[5];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number param_01_lastValue;
    number param_02_lastValue;
    number param_03_lastValue;
    number param_04_lastValue;
    Int numberobj_15_currentFormat;
    number numberobj_15_lastValue;
    number param_05_lastValue;
    number param_06_lastValue;
    Int numberobj_16_currentFormat;
    number numberobj_16_lastValue;
    Float64BufferRef gen_01_delay_1_buffer;
    Index gen_01_delay_1__maxdelay;
    Int gen_01_delay_1_sizemode;
    Index gen_01_delay_1_wrap;
    Int gen_01_delay_1_reader;
    Int gen_01_delay_1_writer;
    Float64BufferRef gen_01_delay_2_buffer;
    Index gen_01_delay_2__maxdelay;
    Int gen_01_delay_2_sizemode;
    Index gen_01_delay_2_wrap;
    Int gen_01_delay_2_reader;
    Int gen_01_delay_2_writer;
    number gen_01_history_3_value;
    number gen_01_history_4_value;
    Float64BufferRef gen_01_delay_5_buffer;
    Index gen_01_delay_5__maxdelay;
    Int gen_01_delay_5_sizemode;
    Index gen_01_delay_5_wrap;
    Int gen_01_delay_5_reader;
    Int gen_01_delay_5_writer;
    number gen_01_history_6_value;
    Float64BufferRef gen_01_DL1_buffer;
    Index gen_01_DL1__maxdelay;
    Int gen_01_DL1_sizemode;
    Index gen_01_DL1_wrap;
    Int gen_01_DL1_reader;
    Int gen_01_DL1_writer;
    Float64BufferRef gen_01_DL2_buffer;
    Index gen_01_DL2__maxdelay;
    Int gen_01_DL2_sizemode;
    Index gen_01_DL2_wrap;
    Int gen_01_DL2_reader;
    Int gen_01_DL2_writer;
    Float64BufferRef gen_01_DL3_buffer;
    Index gen_01_DL3__maxdelay;
    Int gen_01_DL3_sizemode;
    Index gen_01_DL3_wrap;
    Int gen_01_DL3_reader;
    Int gen_01_DL3_writer;
    Float64BufferRef gen_01_DL4_buffer;
    Index gen_01_DL4__maxdelay;
    Int gen_01_DL4_sizemode;
    Index gen_01_DL4_wrap;
    Int gen_01_DL4_reader;
    Int gen_01_DL4_writer;
    Float64BufferRef gen_01_DL5_buffer;
    Index gen_01_DL5__maxdelay;
    Int gen_01_DL5_sizemode;
    Index gen_01_DL5_wrap;
    Int gen_01_DL5_reader;
    Int gen_01_DL5_writer;
    Float64BufferRef gen_01_DL6_buffer;
    Index gen_01_DL6__maxdelay;
    Int gen_01_DL6_sizemode;
    Index gen_01_DL6_wrap;
    Int gen_01_DL6_reader;
    Int gen_01_DL6_writer;
    Float64BufferRef gen_01_DL7_buffer;
    Index gen_01_DL7__maxdelay;
    Int gen_01_DL7_sizemode;
    Index gen_01_DL7_wrap;
    Int gen_01_DL7_reader;
    Int gen_01_DL7_writer;
    Float64BufferRef gen_01_DL8_buffer;
    Index gen_01_DL8__maxdelay;
    Int gen_01_DL8_sizemode;
    Index gen_01_DL8_wrap;
    Int gen_01_DL8_reader;
    Int gen_01_DL8_writer;
    Float64BufferRef gen_01_DL9_buffer;
    Index gen_01_DL9__maxdelay;
    Int gen_01_DL9_sizemode;
    Index gen_01_DL9_wrap;
    Int gen_01_DL9_reader;
    Int gen_01_DL9_writer;
    Float64BufferRef gen_01_DL10_buffer;
    Index gen_01_DL10__maxdelay;
    Int gen_01_DL10_sizemode;
    Index gen_01_DL10_wrap;
    Int gen_01_DL10_reader;
    Int gen_01_DL10_writer;
    Float64BufferRef gen_01_DL11_buffer;
    Index gen_01_DL11__maxdelay;
    Int gen_01_DL11_sizemode;
    Index gen_01_DL11_wrap;
    Int gen_01_DL11_reader;
    Int gen_01_DL11_writer;
    Float64BufferRef gen_01_DL12_buffer;
    Index gen_01_DL12__maxdelay;
    Int gen_01_DL12_sizemode;
    Index gen_01_DL12_wrap;
    Int gen_01_DL12_reader;
    Int gen_01_DL12_writer;
    Float64BufferRef gen_01_DL13_buffer;
    Index gen_01_DL13__maxdelay;
    Int gen_01_DL13_sizemode;
    Index gen_01_DL13_wrap;
    Int gen_01_DL13_reader;
    Int gen_01_DL13_writer;
    number gen_01_feedback_value;
    number gen_01_filterOutput_value;
    number gen_01_history_7_value;
    number gen_01_history_8_value;
    Float64BufferRef gen_01_delay_9_buffer;
    Index gen_01_delay_9__maxdelay;
    Int gen_01_delay_9_sizemode;
    Index gen_01_delay_9_wrap;
    Int gen_01_delay_9_reader;
    Int gen_01_delay_9_writer;
    number gen_01_history_10_value;
    Float64BufferRef gen_01_dlL1_buffer;
    Index gen_01_dlL1__maxdelay;
    Int gen_01_dlL1_sizemode;
    Index gen_01_dlL1_wrap;
    Int gen_01_dlL1_reader;
    Int gen_01_dlL1_writer;
    Float64BufferRef gen_01_dlL2_buffer;
    Index gen_01_dlL2__maxdelay;
    Int gen_01_dlL2_sizemode;
    Index gen_01_dlL2_wrap;
    Int gen_01_dlL2_reader;
    Int gen_01_dlL2_writer;
    Float64BufferRef gen_01_dlL3_buffer;
    Index gen_01_dlL3__maxdelay;
    Int gen_01_dlL3_sizemode;
    Index gen_01_dlL3_wrap;
    Int gen_01_dlL3_reader;
    Int gen_01_dlL3_writer;
    Float64BufferRef gen_01_dlL4_buffer;
    Index gen_01_dlL4__maxdelay;
    Int gen_01_dlL4_sizemode;
    Index gen_01_dlL4_wrap;
    Int gen_01_dlL4_reader;
    Int gen_01_dlL4_writer;
    Float64BufferRef gen_01_dlL5_buffer;
    Index gen_01_dlL5__maxdelay;
    Int gen_01_dlL5_sizemode;
    Index gen_01_dlL5_wrap;
    Int gen_01_dlL5_reader;
    Int gen_01_dlL5_writer;
    Float64BufferRef gen_01_dlL6_buffer;
    Index gen_01_dlL6__maxdelay;
    Int gen_01_dlL6_sizemode;
    Index gen_01_dlL6_wrap;
    Int gen_01_dlL6_reader;
    Int gen_01_dlL6_writer;
    Float64BufferRef gen_01_dlL7_buffer;
    Index gen_01_dlL7__maxdelay;
    Int gen_01_dlL7_sizemode;
    Index gen_01_dlL7_wrap;
    Int gen_01_dlL7_reader;
    Int gen_01_dlL7_writer;
    Float64BufferRef gen_01_dlL8_buffer;
    Index gen_01_dlL8__maxdelay;
    Int gen_01_dlL8_sizemode;
    Index gen_01_dlL8_wrap;
    Int gen_01_dlL8_reader;
    Int gen_01_dlL8_writer;
    Float64BufferRef gen_01_dlL9_buffer;
    Index gen_01_dlL9__maxdelay;
    Int gen_01_dlL9_sizemode;
    Index gen_01_dlL9_wrap;
    Int gen_01_dlL9_reader;
    Int gen_01_dlL9_writer;
    Float64BufferRef gen_01_dlL10_buffer;
    Index gen_01_dlL10__maxdelay;
    Int gen_01_dlL10_sizemode;
    Index gen_01_dlL10_wrap;
    Int gen_01_dlL10_reader;
    Int gen_01_dlL10_writer;
    Float64BufferRef gen_01_dlL11_buffer;
    Index gen_01_dlL11__maxdelay;
    Int gen_01_dlL11_sizemode;
    Index gen_01_dlL11_wrap;
    Int gen_01_dlL11_reader;
    Int gen_01_dlL11_writer;
    Float64BufferRef gen_01_dlL12_buffer;
    Index gen_01_dlL12__maxdelay;
    Int gen_01_dlL12_sizemode;
    Index gen_01_dlL12_wrap;
    Int gen_01_dlL12_reader;
    Int gen_01_dlL12_writer;
    Float64BufferRef gen_01_dlL13_buffer;
    Index gen_01_dlL13__maxdelay;
    Int gen_01_dlL13_sizemode;
    Index gen_01_dlL13_wrap;
    Int gen_01_dlL13_reader;
    Int gen_01_dlL13_writer;
    number gen_01_feedbackL_value;
    number gen_01_filterOutputL_value;
    number gen_01_history_11_value;
    number gen_01_history_12_value;
    number gen_01_phasor_4_currentPhase;
    number gen_01_phasor_4_conv;
    number gen_01_cycle_6_ph_currentPhase;
    number gen_01_cycle_6_ph_conv;
    Float64BufferRef gen_01_cycle_6_buffer;
    long gen_01_cycle_6_wrap;
    uint32_t gen_01_cycle_6_phasei;
    SampleValue gen_01_cycle_6_f2i;
    number gen_01_cycle_11_ph_currentPhase;
    number gen_01_cycle_11_ph_conv;
    Float64BufferRef gen_01_cycle_11_buffer;
    long gen_01_cycle_11_wrap;
    uint32_t gen_01_cycle_11_phasei;
    SampleValue gen_01_cycle_11_f2i;
    number gen_01_cycle_16_ph_currentPhase;
    number gen_01_cycle_16_ph_conv;
    Float64BufferRef gen_01_cycle_16_buffer;
    long gen_01_cycle_16_wrap;
    uint32_t gen_01_cycle_16_phasei;
    SampleValue gen_01_cycle_16_f2i;
    number gen_01_cycle_21_ph_currentPhase;
    number gen_01_cycle_21_ph_conv;
    Float64BufferRef gen_01_cycle_21_buffer;
    long gen_01_cycle_21_wrap;
    uint32_t gen_01_cycle_21_phasei;
    SampleValue gen_01_cycle_21_f2i;
    number gen_01_cycle_26_ph_currentPhase;
    number gen_01_cycle_26_ph_conv;
    Float64BufferRef gen_01_cycle_26_buffer;
    long gen_01_cycle_26_wrap;
    uint32_t gen_01_cycle_26_phasei;
    SampleValue gen_01_cycle_26_f2i;
    number gen_01_cycle_31_ph_currentPhase;
    number gen_01_cycle_31_ph_conv;
    Float64BufferRef gen_01_cycle_31_buffer;
    long gen_01_cycle_31_wrap;
    uint32_t gen_01_cycle_31_phasei;
    SampleValue gen_01_cycle_31_f2i;
    number gen_01_cycle_36_ph_currentPhase;
    number gen_01_cycle_36_ph_conv;
    Float64BufferRef gen_01_cycle_36_buffer;
    long gen_01_cycle_36_wrap;
    uint32_t gen_01_cycle_36_phasei;
    SampleValue gen_01_cycle_36_f2i;
    number gen_01_cycle_41_ph_currentPhase;
    number gen_01_cycle_41_ph_conv;
    Float64BufferRef gen_01_cycle_41_buffer;
    long gen_01_cycle_41_wrap;
    uint32_t gen_01_cycle_41_phasei;
    SampleValue gen_01_cycle_41_f2i;
    number gen_01_cycle_46_ph_currentPhase;
    number gen_01_cycle_46_ph_conv;
    Float64BufferRef gen_01_cycle_46_buffer;
    long gen_01_cycle_46_wrap;
    uint32_t gen_01_cycle_46_phasei;
    SampleValue gen_01_cycle_46_f2i;
    number gen_01_cycle_54_ph_currentPhase;
    number gen_01_cycle_54_ph_conv;
    Float64BufferRef gen_01_cycle_54_buffer;
    long gen_01_cycle_54_wrap;
    uint32_t gen_01_cycle_54_phasei;
    SampleValue gen_01_cycle_54_f2i;
    number gen_01_slide_69_prev;
    UInt gen_01_noise_78_state[4] = { };
    UInt gen_01_noise_84_state[4] = { };
    UInt gen_01_noise_90_state[4] = { };
    UInt gen_01_noise_96_state[4] = { };
    number gen_01_phasor_105_currentPhase;
    number gen_01_phasor_105_conv;
    number gen_01_delta_109_prev;
    number gen_01_sah_111_prev;
    number gen_01_sah_111_value;
    number gen_01_delta_120_prev;
    number gen_01_sah_122_prev;
    number gen_01_sah_122_value;
    number gen_01_delta_131_prev;
    number gen_01_sah_134_prev;
    number gen_01_sah_134_value;
    number gen_01_delta_143_prev;
    number gen_01_sah_145_prev;
    number gen_01_sah_145_value;
    number gen_01_dcblock_223_xm1;
    number gen_01_dcblock_223_ym1;
    number gen_01_slide_229_prev;
    UInt gen_01_noise_238_state[4] = { };
    UInt gen_01_noise_244_state[4] = { };
    UInt gen_01_noise_250_state[4] = { };
    UInt gen_01_noise_256_state[4] = { };
    number gen_01_phasor_265_currentPhase;
    number gen_01_phasor_265_conv;
    number gen_01_delta_269_prev;
    number gen_01_sah_271_prev;
    number gen_01_sah_271_value;
    number gen_01_delta_280_prev;
    number gen_01_sah_282_prev;
    number gen_01_sah_282_value;
    number gen_01_delta_291_prev;
    number gen_01_sah_293_prev;
    number gen_01_sah_293_value;
    number gen_01_delta_302_prev;
    number gen_01_sah_304_prev;
    number gen_01_sah_304_value;
    number gen_01_dcblock_372_xm1;
    number gen_01_dcblock_372_ym1;
    bool gen_01_setupDone;
    Float64BufferRef gen_02_delay_1_buffer;
    Index gen_02_delay_1__maxdelay;
    Int gen_02_delay_1_sizemode;
    Index gen_02_delay_1_wrap;
    Int gen_02_delay_1_reader;
    Int gen_02_delay_1_writer;
    Float64BufferRef gen_02_delay_2_buffer;
    Index gen_02_delay_2__maxdelay;
    Int gen_02_delay_2_sizemode;
    Index gen_02_delay_2_wrap;
    Int gen_02_delay_2_reader;
    Int gen_02_delay_2_writer;
    Float64BufferRef gen_02_delay_3_buffer;
    Index gen_02_delay_3__maxdelay;
    Int gen_02_delay_3_sizemode;
    Index gen_02_delay_3_wrap;
    Int gen_02_delay_3_reader;
    Int gen_02_delay_3_writer;
    Float64BufferRef gen_02_delay_4_buffer;
    Index gen_02_delay_4__maxdelay;
    Int gen_02_delay_4_sizemode;
    Index gen_02_delay_4_wrap;
    Int gen_02_delay_4_reader;
    Int gen_02_delay_4_writer;
    Float64BufferRef gen_02_delay_5_buffer;
    Index gen_02_delay_5__maxdelay;
    Int gen_02_delay_5_sizemode;
    Index gen_02_delay_5_wrap;
    Int gen_02_delay_5_reader;
    Int gen_02_delay_5_writer;
    Float64BufferRef gen_02_delay_6_buffer;
    Index gen_02_delay_6__maxdelay;
    Int gen_02_delay_6_sizemode;
    Index gen_02_delay_6_wrap;
    Int gen_02_delay_6_reader;
    Int gen_02_delay_6_writer;
    Float64BufferRef gen_02_delay_7_buffer;
    Index gen_02_delay_7__maxdelay;
    Int gen_02_delay_7_sizemode;
    Index gen_02_delay_7_wrap;
    Int gen_02_delay_7_reader;
    Int gen_02_delay_7_writer;
    Float64BufferRef gen_02_delay_8_buffer;
    Index gen_02_delay_8__maxdelay;
    Int gen_02_delay_8_sizemode;
    Index gen_02_delay_8_wrap;
    Int gen_02_delay_8_reader;
    Int gen_02_delay_8_writer;
    Float64BufferRef gen_02_delay_9_buffer;
    Index gen_02_delay_9__maxdelay;
    Int gen_02_delay_9_sizemode;
    Index gen_02_delay_9_wrap;
    Int gen_02_delay_9_reader;
    Int gen_02_delay_9_writer;
    Float64BufferRef gen_02_delay_10_buffer;
    Index gen_02_delay_10__maxdelay;
    Int gen_02_delay_10_sizemode;
    Index gen_02_delay_10_wrap;
    Int gen_02_delay_10_reader;
    Int gen_02_delay_10_writer;
    Float64BufferRef gen_02_delay_11_buffer;
    Index gen_02_delay_11__maxdelay;
    Int gen_02_delay_11_sizemode;
    Index gen_02_delay_11_wrap;
    Int gen_02_delay_11_reader;
    Int gen_02_delay_11_writer;
    Float64BufferRef gen_02_delay_12_buffer;
    Index gen_02_delay_12__maxdelay;
    Int gen_02_delay_12_sizemode;
    Index gen_02_delay_12_wrap;
    Int gen_02_delay_12_reader;
    Int gen_02_delay_12_writer;
    Float64BufferRef gen_02_delay_13_buffer;
    Index gen_02_delay_13__maxdelay;
    Int gen_02_delay_13_sizemode;
    Index gen_02_delay_13_wrap;
    Int gen_02_delay_13_reader;
    Int gen_02_delay_13_writer;
    Float64BufferRef gen_02_delay_14_buffer;
    Index gen_02_delay_14__maxdelay;
    Int gen_02_delay_14_sizemode;
    Index gen_02_delay_14_wrap;
    Int gen_02_delay_14_reader;
    Int gen_02_delay_14_writer;
    Float64BufferRef gen_02_delay_15_buffer;
    Index gen_02_delay_15__maxdelay;
    Int gen_02_delay_15_sizemode;
    Index gen_02_delay_15_wrap;
    Int gen_02_delay_15_reader;
    Int gen_02_delay_15_writer;
    number gen_02_history_16_value;
    Float64BufferRef gen_02_delay_17_buffer;
    Index gen_02_delay_17__maxdelay;
    Int gen_02_delay_17_sizemode;
    Index gen_02_delay_17_wrap;
    Int gen_02_delay_17_reader;
    Int gen_02_delay_17_writer;
    Float64BufferRef gen_02_delay_18_buffer;
    Index gen_02_delay_18__maxdelay;
    Int gen_02_delay_18_sizemode;
    Index gen_02_delay_18_wrap;
    Int gen_02_delay_18_reader;
    Int gen_02_delay_18_writer;
    Float64BufferRef gen_02_delay_19_buffer;
    Index gen_02_delay_19__maxdelay;
    Int gen_02_delay_19_sizemode;
    Index gen_02_delay_19_wrap;
    Int gen_02_delay_19_reader;
    Int gen_02_delay_19_writer;
    Float64BufferRef gen_02_delay_20_buffer;
    Index gen_02_delay_20__maxdelay;
    Int gen_02_delay_20_sizemode;
    Index gen_02_delay_20_wrap;
    Int gen_02_delay_20_reader;
    Int gen_02_delay_20_writer;
    number gen_02_history_21_value;
    number gen_02_history_22_value;
    number gen_02_history_23_value;
    number gen_02_history_24_value;
    number gen_02_history_25_value;
    number gen_02_phasor_41_currentPhase;
    number gen_02_phasor_41_conv;
    number gen_02_cycle_43_ph_currentPhase;
    number gen_02_cycle_43_ph_conv;
    Float64BufferRef gen_02_cycle_43_buffer;
    long gen_02_cycle_43_wrap;
    uint32_t gen_02_cycle_43_phasei;
    SampleValue gen_02_cycle_43_f2i;
    number gen_02_cycle_50_ph_currentPhase;
    number gen_02_cycle_50_ph_conv;
    Float64BufferRef gen_02_cycle_50_buffer;
    long gen_02_cycle_50_wrap;
    uint32_t gen_02_cycle_50_phasei;
    SampleValue gen_02_cycle_50_f2i;
    number gen_02_dcblock_58_xm1;
    number gen_02_dcblock_58_ym1;
    number gen_02_cycle_63_ph_currentPhase;
    number gen_02_cycle_63_ph_conv;
    Float64BufferRef gen_02_cycle_63_buffer;
    long gen_02_cycle_63_wrap;
    uint32_t gen_02_cycle_63_phasei;
    SampleValue gen_02_cycle_63_f2i;
    number gen_02_dcblock_71_xm1;
    number gen_02_dcblock_71_ym1;
    number gen_02_cycle_118_ph_currentPhase;
    number gen_02_cycle_118_ph_conv;
    Float64BufferRef gen_02_cycle_118_buffer;
    long gen_02_cycle_118_wrap;
    uint32_t gen_02_cycle_118_phasei;
    SampleValue gen_02_cycle_118_f2i;
    number gen_02_cycle_135_ph_currentPhase;
    number gen_02_cycle_135_ph_conv;
    Float64BufferRef gen_02_cycle_135_buffer;
    long gen_02_cycle_135_wrap;
    uint32_t gen_02_cycle_135_phasei;
    SampleValue gen_02_cycle_135_f2i;
    number gen_02_cycle_144_ph_currentPhase;
    number gen_02_cycle_144_ph_conv;
    Float64BufferRef gen_02_cycle_144_buffer;
    long gen_02_cycle_144_wrap;
    uint32_t gen_02_cycle_144_phasei;
    SampleValue gen_02_cycle_144_f2i;
    number gen_02_cycle_161_ph_currentPhase;
    number gen_02_cycle_161_ph_conv;
    Float64BufferRef gen_02_cycle_161_buffer;
    long gen_02_cycle_161_wrap;
    uint32_t gen_02_cycle_161_phasei;
    SampleValue gen_02_cycle_161_f2i;
    number gen_02_cycle_186_ph_currentPhase;
    number gen_02_cycle_186_ph_conv;
    Float64BufferRef gen_02_cycle_186_buffer;
    long gen_02_cycle_186_wrap;
    uint32_t gen_02_cycle_186_phasei;
    SampleValue gen_02_cycle_186_f2i;
    number gen_02_dcblock_233_xm1;
    number gen_02_dcblock_233_ym1;
    number gen_02_dcblock_239_xm1;
    number gen_02_dcblock_239_ym1;
    number gen_02_dcblock_277_xm1;
    number gen_02_dcblock_277_ym1;
    number gen_02_dcblock_283_xm1;
    number gen_02_dcblock_283_ym1;
    bool gen_02_setupDone;
    number toggle_02_lastValue;
    number param_07_lastValue;
    Int numberobj_17_currentFormat;
    number numberobj_17_lastValue;
    number param_08_lastValue;
    Int numberobj_18_currentFormat;
    number numberobj_18_lastValue;
    number param_09_lastValue;
    Int numberobj_19_currentFormat;
    number numberobj_19_lastValue;
    list linetilde_08_activeRamps;
    number linetilde_08_currentValue;
    Int numberobj_20_currentFormat;
    number numberobj_20_lastValue;
    number param_10_lastValue;
    Int numberobj_21_currentFormat;
    number numberobj_21_lastValue;
    number param_11_lastValue;
    Int numberobj_22_currentFormat;
    number numberobj_22_lastValue;
    number param_12_lastValue;
    Int numberobj_23_currentFormat;
    number numberobj_23_lastValue;
    number param_13_lastValue;
    Int numberobj_24_currentFormat;
    number numberobj_24_lastValue;
    number param_14_lastValue;
    number param_15_lastValue;
    number param_16_lastValue;
    number param_17_lastValue;
    number param_18_lastValue;
    number param_19_lastValue;
    int ctlin_01_status;
    int ctlin_01_byte1;
    int ctlin_01_inchan;
    int ctlin_02_status;
    int ctlin_02_byte1;
    int ctlin_02_inchan;
    int ctlin_03_status;
    int ctlin_03_byte1;
    int ctlin_03_inchan;
    int ctlin_04_status;
    int ctlin_04_byte1;
    int ctlin_04_inchan;
    int ctlin_05_status;
    int ctlin_05_byte1;
    int ctlin_05_inchan;
    int ctlin_06_status;
    int ctlin_06_byte1;
    int ctlin_06_inchan;
    int ctlin_07_status;
    int ctlin_07_byte1;
    int ctlin_07_inchan;
    int ctlin_08_status;
    int ctlin_08_byte1;
    int ctlin_08_inchan;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    DataRef gen_01_delay_1_bufferobj;
    DataRef gen_01_delay_2_bufferobj;
    DataRef gen_01_delay_5_bufferobj;
    DataRef gen_01_DL1_bufferobj;
    DataRef gen_01_DL2_bufferobj;
    DataRef gen_01_DL3_bufferobj;
    DataRef gen_01_DL4_bufferobj;
    DataRef gen_01_DL5_bufferobj;
    DataRef gen_01_DL6_bufferobj;
    DataRef gen_01_DL7_bufferobj;
    DataRef gen_01_DL8_bufferobj;
    DataRef gen_01_DL9_bufferobj;
    DataRef gen_01_DL10_bufferobj;
    DataRef gen_01_DL11_bufferobj;
    DataRef gen_01_DL12_bufferobj;
    DataRef gen_01_DL13_bufferobj;
    DataRef gen_01_delay_9_bufferobj;
    DataRef gen_01_dlL1_bufferobj;
    DataRef gen_01_dlL2_bufferobj;
    DataRef gen_01_dlL3_bufferobj;
    DataRef gen_01_dlL4_bufferobj;
    DataRef gen_01_dlL5_bufferobj;
    DataRef gen_01_dlL6_bufferobj;
    DataRef gen_01_dlL7_bufferobj;
    DataRef gen_01_dlL8_bufferobj;
    DataRef gen_01_dlL9_bufferobj;
    DataRef gen_01_dlL10_bufferobj;
    DataRef gen_01_dlL11_bufferobj;
    DataRef gen_01_dlL12_bufferobj;
    DataRef gen_01_dlL13_bufferobj;
    DataRef RNBODefaultSinus;
    DataRef gen_02_delay_1_bufferobj;
    DataRef gen_02_delay_2_bufferobj;
    DataRef gen_02_delay_3_bufferobj;
    DataRef gen_02_delay_4_bufferobj;
    DataRef gen_02_delay_5_bufferobj;
    DataRef gen_02_delay_6_bufferobj;
    DataRef gen_02_delay_7_bufferobj;
    DataRef gen_02_delay_8_bufferobj;
    DataRef gen_02_delay_9_bufferobj;
    DataRef gen_02_delay_10_bufferobj;
    DataRef gen_02_delay_11_bufferobj;
    DataRef gen_02_delay_12_bufferobj;
    DataRef gen_02_delay_13_bufferobj;
    DataRef gen_02_delay_14_bufferobj;
    DataRef gen_02_delay_15_bufferobj;
    DataRef gen_02_delay_17_bufferobj;
    DataRef gen_02_delay_18_bufferobj;
    DataRef gen_02_delay_19_bufferobj;
    DataRef gen_02_delay_20_bufferobj;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_188* p_01;
    RNBOSubpatcher_189* p_02;
    RNBOSubpatcher_190* p_03;
    RNBOSubpatcher_191* p_04;
    RNBOSubpatcher_192* p_05;
    RNBOSubpatcher_193* p_06;
    RNBOSubpatcher_194* p_07;

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace

