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

#ifdef RNBO_LIB_PREFIX
#define STR_IMPL(A) #A
#define STR(A) STR_IMPL(A)
#define RNBO_LIB_INCLUDE(X) STR(RNBO_LIB_PREFIX/X)
#else
#define RNBO_LIB_INCLUDE(X) #X
#endif // RNBO_LIB_PREFIX
#ifdef RNBO_INJECTPLATFORM
#define RNBO_USECUSTOMPLATFORM
#include RNBO_INJECTPLATFORM
#endif // RNBO_INJECTPLATFORM

#include RNBO_LIB_INCLUDE(RNBO_Common.h)
#include RNBO_LIB_INCLUDE(RNBO_AudioSignal.h)

namespace RNBO {


#define trunc(x) ((Int)(x))
#define autoref auto&

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

template <class ENGINE = INTERNALENGINE> class rnbomatic : public PatcherInterfaceImpl {

friend class EngineCore;
friend class Engine;
friend class MinimalEngine<>;
public:

rnbomatic()
: _internalEngine(this)
{
}

~rnbomatic()
{}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->ctlin_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_02_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_03_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_04_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_05_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_06_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_07_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_08_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_09_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_10_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
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
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
    this->p_07_perform(in1, in2, this->signals[0], this->signals[1], n);
    this->dcblock_tilde_03_perform(this->signals[0], this->dcblock_tilde_03_gain, this->signals[2], n);
    this->dcblock_tilde_04_perform(this->signals[1], this->dcblock_tilde_04_gain, this->signals[0], n);
    this->p_06_perform(this->signals[2], this->signals[0], this->signals[1], this->signals[3], n);

    this->gen_02_perform(
        this->signals[1],
        this->signals[3],
        this->gen_02_lfo1_rate,
        this->gen_02_pre_del,
        this->gen_02_decay2,
        this->gen_02_lpf,
        this->gen_02_lfo1_bw,
        this->gen_02_apf_g,
        this->gen_02_diff_gain,
        this->signals[0],
        this->signals[2],
        n
    );

    this->gen_01_perform(
        this->signals[0],
        this->signals[2],
        this->gen_01_xover,
        this->gen_01_lfo1_bw,
        this->gen_01_decay,
        this->gen_01_lfo1_rate,
        this->gen_01_InGain,
        this->gen_01_fbc,
        this->gen_01_lpf,
        this->gen_01_mult,
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
        this->signals[1],
        this->signals[4],
        this->dummyBuffer,
        n
    );

    this->p_03_perform(this->signals[3], this->signals[1], this->signals[2], this->signals[0], n);
    this->p_05_perform(this->signals[2], this->signals[0], this->signals[1], this->signals[3], n);
    this->p_04_perform(this->signals[1], this->signals[3], this->signals[0], this->signals[2], n);
    this->p_02_perform(this->signals[0], this->signals[2], this->signals[3], this->signals[1], n);
    this->snapshot_01_perform(this->signals[4], n);
    this->linetilde_09_perform(this->signals[4], n);

    this->p_01_perform(
        in1,
        in2,
        this->signals[3],
        this->signals[1],
        this->signals[4],
        this->signals[2],
        this->signals[0],
        n
    );

    this->dcblock_tilde_01_perform(this->signals[2], this->dcblock_tilde_01_gain, this->signals[4], n);
    this->dspexpr_05_perform(this->signals[4], this->dspexpr_05_in2, this->dspexpr_05_in3, out1, n);
    this->dcblock_tilde_02_perform(this->signals[0], this->dcblock_tilde_02_gain, this->signals[4], n);
    this->dspexpr_06_perform(this->signals[4], this->dspexpr_06_in2, this->dspexpr_06_in3, out2, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->advanceTime((ENGINE*)nullptr);
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

    this->dcblock_tilde_03_dspsetup(forceDSPSetup);
    this->dcblock_tilde_04_dspsetup(forceDSPSetup);
    this->gen_02_dspsetup(forceDSPSetup);
    this->gen_01_dspsetup(forceDSPSetup);
    this->dcblock_tilde_01_dspsetup(forceDSPSetup);
    this->dcblock_tilde_02_dspsetup(forceDSPSetup);
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

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getNumInputChannels() const {
    return 2;
}

Index getNumOutputChannels() const {
    return 2;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->gen_01_DL1_bufferobj);
        break;
        }
    case 1:
        {
        return addressOf(this->gen_01_DL2_bufferobj);
        break;
        }
    case 2:
        {
        return addressOf(this->gen_01_DL3_bufferobj);
        break;
        }
    case 3:
        {
        return addressOf(this->gen_01_DL4_bufferobj);
        break;
        }
    case 4:
        {
        return addressOf(this->gen_01_DL5_bufferobj);
        break;
        }
    case 5:
        {
        return addressOf(this->gen_01_DL6_bufferobj);
        break;
        }
    case 6:
        {
        return addressOf(this->gen_01_DL7_bufferobj);
        break;
        }
    case 7:
        {
        return addressOf(this->gen_01_DL8_bufferobj);
        break;
        }
    case 8:
        {
        return addressOf(this->gen_01_DL9_bufferobj);
        break;
        }
    case 9:
        {
        return addressOf(this->gen_01_DL10_bufferobj);
        break;
        }
    case 10:
        {
        return addressOf(this->gen_01_DL11_bufferobj);
        break;
        }
    case 11:
        {
        return addressOf(this->gen_01_DL12_bufferobj);
        break;
        }
    case 12:
        {
        return addressOf(this->gen_01_DL13_bufferobj);
        break;
        }
    case 13:
        {
        return addressOf(this->gen_01_dlL1_bufferobj);
        break;
        }
    case 14:
        {
        return addressOf(this->gen_01_dlL2_bufferobj);
        break;
        }
    case 15:
        {
        return addressOf(this->gen_01_dlL3_bufferobj);
        break;
        }
    case 16:
        {
        return addressOf(this->gen_01_dlL4_bufferobj);
        break;
        }
    case 17:
        {
        return addressOf(this->gen_01_dlL5_bufferobj);
        break;
        }
    case 18:
        {
        return addressOf(this->gen_01_dlL6_bufferobj);
        break;
        }
    case 19:
        {
        return addressOf(this->gen_01_dlL7_bufferobj);
        break;
        }
    case 20:
        {
        return addressOf(this->gen_01_dlL8_bufferobj);
        break;
        }
    case 21:
        {
        return addressOf(this->gen_01_dlL9_bufferobj);
        break;
        }
    case 22:
        {
        return addressOf(this->gen_01_dlL10_bufferobj);
        break;
        }
    case 23:
        {
        return addressOf(this->gen_01_dlL11_bufferobj);
        break;
        }
    case 24:
        {
        return addressOf(this->gen_01_dlL12_bufferobj);
        break;
        }
    case 25:
        {
        return addressOf(this->gen_01_dlL13_bufferobj);
        break;
        }
    case 26:
        {
        return addressOf(this->RNBODefaultSinus);
        break;
        }
    case 27:
        {
        return addressOf(this->gen_02_delay_1_bufferobj);
        break;
        }
    case 28:
        {
        return addressOf(this->gen_02_delay_2_bufferobj);
        break;
        }
    case 29:
        {
        return addressOf(this->gen_02_delay_3_bufferobj);
        break;
        }
    case 30:
        {
        return addressOf(this->gen_02_delay_4_bufferobj);
        break;
        }
    case 31:
        {
        return addressOf(this->gen_02_delay_5_bufferobj);
        break;
        }
    case 32:
        {
        return addressOf(this->gen_02_delay_6_bufferobj);
        break;
        }
    case 33:
        {
        return addressOf(this->gen_02_delay_7_bufferobj);
        break;
        }
    case 34:
        {
        return addressOf(this->gen_02_delay_8_bufferobj);
        break;
        }
    case 35:
        {
        return addressOf(this->gen_02_delay_9_bufferobj);
        break;
        }
    case 36:
        {
        return addressOf(this->gen_02_delay_11_bufferobj);
        break;
        }
    case 37:
        {
        return addressOf(this->gen_02_delay_12_bufferobj);
        break;
        }
    case 38:
        {
        return addressOf(this->gen_02_delay_13_bufferobj);
        break;
        }
    case 39:
        {
        return addressOf(this->gen_02_delay_14_bufferobj);
        break;
        }
    case 40:
        {
        return addressOf(this->gen_02_delay_15_bufferobj);
        break;
        }
    case 41:
        {
        return addressOf(this->gen_02_delay_16_bufferobj);
        break;
        }
    case 42:
        {
        return addressOf(this->gen_02_delay_17_bufferobj);
        break;
        }
    case 43:
        {
        return addressOf(this->gen_02_delay_18_bufferobj);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 44;
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (index == 0) {
        this->gen_01_DL1_buffer = reInitDataView(this->gen_01_DL1_buffer, this->gen_01_DL1_bufferobj);
    }

    if (index == 1) {
        this->gen_01_DL2_buffer = reInitDataView(this->gen_01_DL2_buffer, this->gen_01_DL2_bufferobj);
    }

    if (index == 2) {
        this->gen_01_DL3_buffer = reInitDataView(this->gen_01_DL3_buffer, this->gen_01_DL3_bufferobj);
    }

    if (index == 3) {
        this->gen_01_DL4_buffer = reInitDataView(this->gen_01_DL4_buffer, this->gen_01_DL4_bufferobj);
    }

    if (index == 4) {
        this->gen_01_DL5_buffer = reInitDataView(this->gen_01_DL5_buffer, this->gen_01_DL5_bufferobj);
    }

    if (index == 5) {
        this->gen_01_DL6_buffer = reInitDataView(this->gen_01_DL6_buffer, this->gen_01_DL6_bufferobj);
    }

    if (index == 6) {
        this->gen_01_DL7_buffer = reInitDataView(this->gen_01_DL7_buffer, this->gen_01_DL7_bufferobj);
    }

    if (index == 7) {
        this->gen_01_DL8_buffer = reInitDataView(this->gen_01_DL8_buffer, this->gen_01_DL8_bufferobj);
    }

    if (index == 8) {
        this->gen_01_DL9_buffer = reInitDataView(this->gen_01_DL9_buffer, this->gen_01_DL9_bufferobj);
    }

    if (index == 9) {
        this->gen_01_DL10_buffer = reInitDataView(this->gen_01_DL10_buffer, this->gen_01_DL10_bufferobj);
    }

    if (index == 10) {
        this->gen_01_DL11_buffer = reInitDataView(this->gen_01_DL11_buffer, this->gen_01_DL11_bufferobj);
    }

    if (index == 11) {
        this->gen_01_DL12_buffer = reInitDataView(this->gen_01_DL12_buffer, this->gen_01_DL12_bufferobj);
    }

    if (index == 12) {
        this->gen_01_DL13_buffer = reInitDataView(this->gen_01_DL13_buffer, this->gen_01_DL13_bufferobj);
    }

    if (index == 13) {
        this->gen_01_dlL1_buffer = reInitDataView(this->gen_01_dlL1_buffer, this->gen_01_dlL1_bufferobj);
    }

    if (index == 14) {
        this->gen_01_dlL2_buffer = reInitDataView(this->gen_01_dlL2_buffer, this->gen_01_dlL2_bufferobj);
    }

    if (index == 15) {
        this->gen_01_dlL3_buffer = reInitDataView(this->gen_01_dlL3_buffer, this->gen_01_dlL3_bufferobj);
    }

    if (index == 16) {
        this->gen_01_dlL4_buffer = reInitDataView(this->gen_01_dlL4_buffer, this->gen_01_dlL4_bufferobj);
    }

    if (index == 17) {
        this->gen_01_dlL5_buffer = reInitDataView(this->gen_01_dlL5_buffer, this->gen_01_dlL5_bufferobj);
    }

    if (index == 18) {
        this->gen_01_dlL6_buffer = reInitDataView(this->gen_01_dlL6_buffer, this->gen_01_dlL6_bufferobj);
    }

    if (index == 19) {
        this->gen_01_dlL7_buffer = reInitDataView(this->gen_01_dlL7_buffer, this->gen_01_dlL7_bufferobj);
    }

    if (index == 20) {
        this->gen_01_dlL8_buffer = reInitDataView(this->gen_01_dlL8_buffer, this->gen_01_dlL8_bufferobj);
    }

    if (index == 21) {
        this->gen_01_dlL9_buffer = reInitDataView(this->gen_01_dlL9_buffer, this->gen_01_dlL9_bufferobj);
    }

    if (index == 22) {
        this->gen_01_dlL10_buffer = reInitDataView(this->gen_01_dlL10_buffer, this->gen_01_dlL10_bufferobj);
    }

    if (index == 23) {
        this->gen_01_dlL11_buffer = reInitDataView(this->gen_01_dlL11_buffer, this->gen_01_dlL11_bufferobj);
    }

    if (index == 24) {
        this->gen_01_dlL12_buffer = reInitDataView(this->gen_01_dlL12_buffer, this->gen_01_dlL12_bufferobj);
    }

    if (index == 25) {
        this->gen_01_dlL13_buffer = reInitDataView(this->gen_01_dlL13_buffer, this->gen_01_dlL13_bufferobj);
    }

    if (index == 26) {
        this->gen_01_cycle_8_buffer = reInitDataView(this->gen_01_cycle_8_buffer, this->RNBODefaultSinus);
        this->gen_01_cycle_13_buffer = reInitDataView(this->gen_01_cycle_13_buffer, this->RNBODefaultSinus);
        this->gen_01_cycle_18_buffer = reInitDataView(this->gen_01_cycle_18_buffer, this->RNBODefaultSinus);
        this->gen_01_cycle_23_buffer = reInitDataView(this->gen_01_cycle_23_buffer, this->RNBODefaultSinus);
        this->gen_01_cycle_28_buffer = reInitDataView(this->gen_01_cycle_28_buffer, this->RNBODefaultSinus);
        this->gen_01_cycle_33_buffer = reInitDataView(this->gen_01_cycle_33_buffer, this->RNBODefaultSinus);
        this->gen_01_cycle_38_buffer = reInitDataView(this->gen_01_cycle_38_buffer, this->RNBODefaultSinus);
        this->gen_01_cycle_43_buffer = reInitDataView(this->gen_01_cycle_43_buffer, this->RNBODefaultSinus);
        this->gen_02_cycle_17_buffer = reInitDataView(this->gen_02_cycle_17_buffer, this->RNBODefaultSinus);
        this->gen_02_cycle_26_buffer = reInitDataView(this->gen_02_cycle_26_buffer, this->RNBODefaultSinus);
        this->gen_02_cycle_36_buffer = reInitDataView(this->gen_02_cycle_36_buffer, this->RNBODefaultSinus);
        this->gen_02_cycle_45_buffer = reInitDataView(this->gen_02_cycle_45_buffer, this->RNBODefaultSinus);
        this->gen_02_cycle_54_buffer = reInitDataView(this->gen_02_cycle_54_buffer, this->RNBODefaultSinus);
        this->gen_02_cycle_63_buffer = reInitDataView(this->gen_02_cycle_63_buffer, this->RNBODefaultSinus);
        this->gen_02_cycle_74_buffer = reInitDataView(this->gen_02_cycle_74_buffer, this->RNBODefaultSinus);
        this->gen_02_cycle_87_buffer = reInitDataView(this->gen_02_cycle_87_buffer, this->RNBODefaultSinus);
    }

    if (index == 27) {
        this->gen_02_delay_1_buffer = reInitDataView(this->gen_02_delay_1_buffer, this->gen_02_delay_1_bufferobj);
    }

    if (index == 28) {
        this->gen_02_delay_2_buffer = reInitDataView(this->gen_02_delay_2_buffer, this->gen_02_delay_2_bufferobj);
    }

    if (index == 29) {
        this->gen_02_delay_3_buffer = reInitDataView(this->gen_02_delay_3_buffer, this->gen_02_delay_3_bufferobj);
    }

    if (index == 30) {
        this->gen_02_delay_4_buffer = reInitDataView(this->gen_02_delay_4_buffer, this->gen_02_delay_4_bufferobj);
    }

    if (index == 31) {
        this->gen_02_delay_5_buffer = reInitDataView(this->gen_02_delay_5_buffer, this->gen_02_delay_5_bufferobj);
    }

    if (index == 32) {
        this->gen_02_delay_6_buffer = reInitDataView(this->gen_02_delay_6_buffer, this->gen_02_delay_6_bufferobj);
    }

    if (index == 33) {
        this->gen_02_delay_7_buffer = reInitDataView(this->gen_02_delay_7_buffer, this->gen_02_delay_7_bufferobj);
    }

    if (index == 34) {
        this->gen_02_delay_8_buffer = reInitDataView(this->gen_02_delay_8_buffer, this->gen_02_delay_8_bufferobj);
    }

    if (index == 35) {
        this->gen_02_delay_9_buffer = reInitDataView(this->gen_02_delay_9_buffer, this->gen_02_delay_9_bufferobj);
    }

    if (index == 36) {
        this->gen_02_delay_11_buffer = reInitDataView(this->gen_02_delay_11_buffer, this->gen_02_delay_11_bufferobj);
    }

    if (index == 37) {
        this->gen_02_delay_12_buffer = reInitDataView(this->gen_02_delay_12_buffer, this->gen_02_delay_12_bufferobj);
    }

    if (index == 38) {
        this->gen_02_delay_13_buffer = reInitDataView(this->gen_02_delay_13_buffer, this->gen_02_delay_13_bufferobj);
    }

    if (index == 39) {
        this->gen_02_delay_14_buffer = reInitDataView(this->gen_02_delay_14_buffer, this->gen_02_delay_14_bufferobj);
    }

    if (index == 40) {
        this->gen_02_delay_15_buffer = reInitDataView(this->gen_02_delay_15_buffer, this->gen_02_delay_15_bufferobj);
    }

    if (index == 41) {
        this->gen_02_delay_16_buffer = reInitDataView(this->gen_02_delay_16_buffer, this->gen_02_delay_16_bufferobj);
    }

    if (index == 42) {
        this->gen_02_delay_17_buffer = reInitDataView(this->gen_02_delay_17_buffer, this->gen_02_delay_17_bufferobj);
    }

    if (index == 43) {
        this->gen_02_delay_18_buffer = reInitDataView(this->gen_02_delay_18_buffer, this->gen_02_delay_18_bufferobj);
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
    this->gen_01_DL1_bufferobj = initDataRef(
        this->gen_01_DL1_bufferobj,
        this->dataRefStrings->name0,
        true,
        this->dataRefStrings->file0,
        this->dataRefStrings->tag0
    );

    this->gen_01_DL2_bufferobj = initDataRef(
        this->gen_01_DL2_bufferobj,
        this->dataRefStrings->name1,
        true,
        this->dataRefStrings->file1,
        this->dataRefStrings->tag1
    );

    this->gen_01_DL3_bufferobj = initDataRef(
        this->gen_01_DL3_bufferobj,
        this->dataRefStrings->name2,
        true,
        this->dataRefStrings->file2,
        this->dataRefStrings->tag2
    );

    this->gen_01_DL4_bufferobj = initDataRef(
        this->gen_01_DL4_bufferobj,
        this->dataRefStrings->name3,
        true,
        this->dataRefStrings->file3,
        this->dataRefStrings->tag3
    );

    this->gen_01_DL5_bufferobj = initDataRef(
        this->gen_01_DL5_bufferobj,
        this->dataRefStrings->name4,
        true,
        this->dataRefStrings->file4,
        this->dataRefStrings->tag4
    );

    this->gen_01_DL6_bufferobj = initDataRef(
        this->gen_01_DL6_bufferobj,
        this->dataRefStrings->name5,
        true,
        this->dataRefStrings->file5,
        this->dataRefStrings->tag5
    );

    this->gen_01_DL7_bufferobj = initDataRef(
        this->gen_01_DL7_bufferobj,
        this->dataRefStrings->name6,
        true,
        this->dataRefStrings->file6,
        this->dataRefStrings->tag6
    );

    this->gen_01_DL8_bufferobj = initDataRef(
        this->gen_01_DL8_bufferobj,
        this->dataRefStrings->name7,
        true,
        this->dataRefStrings->file7,
        this->dataRefStrings->tag7
    );

    this->gen_01_DL9_bufferobj = initDataRef(
        this->gen_01_DL9_bufferobj,
        this->dataRefStrings->name8,
        true,
        this->dataRefStrings->file8,
        this->dataRefStrings->tag8
    );

    this->gen_01_DL10_bufferobj = initDataRef(
        this->gen_01_DL10_bufferobj,
        this->dataRefStrings->name9,
        true,
        this->dataRefStrings->file9,
        this->dataRefStrings->tag9
    );

    this->gen_01_DL11_bufferobj = initDataRef(
        this->gen_01_DL11_bufferobj,
        this->dataRefStrings->name10,
        true,
        this->dataRefStrings->file10,
        this->dataRefStrings->tag10
    );

    this->gen_01_DL12_bufferobj = initDataRef(
        this->gen_01_DL12_bufferobj,
        this->dataRefStrings->name11,
        true,
        this->dataRefStrings->file11,
        this->dataRefStrings->tag11
    );

    this->gen_01_DL13_bufferobj = initDataRef(
        this->gen_01_DL13_bufferobj,
        this->dataRefStrings->name12,
        true,
        this->dataRefStrings->file12,
        this->dataRefStrings->tag12
    );

    this->gen_01_dlL1_bufferobj = initDataRef(
        this->gen_01_dlL1_bufferobj,
        this->dataRefStrings->name13,
        true,
        this->dataRefStrings->file13,
        this->dataRefStrings->tag13
    );

    this->gen_01_dlL2_bufferobj = initDataRef(
        this->gen_01_dlL2_bufferobj,
        this->dataRefStrings->name14,
        true,
        this->dataRefStrings->file14,
        this->dataRefStrings->tag14
    );

    this->gen_01_dlL3_bufferobj = initDataRef(
        this->gen_01_dlL3_bufferobj,
        this->dataRefStrings->name15,
        true,
        this->dataRefStrings->file15,
        this->dataRefStrings->tag15
    );

    this->gen_01_dlL4_bufferobj = initDataRef(
        this->gen_01_dlL4_bufferobj,
        this->dataRefStrings->name16,
        true,
        this->dataRefStrings->file16,
        this->dataRefStrings->tag16
    );

    this->gen_01_dlL5_bufferobj = initDataRef(
        this->gen_01_dlL5_bufferobj,
        this->dataRefStrings->name17,
        true,
        this->dataRefStrings->file17,
        this->dataRefStrings->tag17
    );

    this->gen_01_dlL6_bufferobj = initDataRef(
        this->gen_01_dlL6_bufferobj,
        this->dataRefStrings->name18,
        true,
        this->dataRefStrings->file18,
        this->dataRefStrings->tag18
    );

    this->gen_01_dlL7_bufferobj = initDataRef(
        this->gen_01_dlL7_bufferobj,
        this->dataRefStrings->name19,
        true,
        this->dataRefStrings->file19,
        this->dataRefStrings->tag19
    );

    this->gen_01_dlL8_bufferobj = initDataRef(
        this->gen_01_dlL8_bufferobj,
        this->dataRefStrings->name20,
        true,
        this->dataRefStrings->file20,
        this->dataRefStrings->tag20
    );

    this->gen_01_dlL9_bufferobj = initDataRef(
        this->gen_01_dlL9_bufferobj,
        this->dataRefStrings->name21,
        true,
        this->dataRefStrings->file21,
        this->dataRefStrings->tag21
    );

    this->gen_01_dlL10_bufferobj = initDataRef(
        this->gen_01_dlL10_bufferobj,
        this->dataRefStrings->name22,
        true,
        this->dataRefStrings->file22,
        this->dataRefStrings->tag22
    );

    this->gen_01_dlL11_bufferobj = initDataRef(
        this->gen_01_dlL11_bufferobj,
        this->dataRefStrings->name23,
        true,
        this->dataRefStrings->file23,
        this->dataRefStrings->tag23
    );

    this->gen_01_dlL12_bufferobj = initDataRef(
        this->gen_01_dlL12_bufferobj,
        this->dataRefStrings->name24,
        true,
        this->dataRefStrings->file24,
        this->dataRefStrings->tag24
    );

    this->gen_01_dlL13_bufferobj = initDataRef(
        this->gen_01_dlL13_bufferobj,
        this->dataRefStrings->name25,
        true,
        this->dataRefStrings->file25,
        this->dataRefStrings->tag25
    );

    this->RNBODefaultSinus = initDataRef(
        this->RNBODefaultSinus,
        this->dataRefStrings->name26,
        true,
        this->dataRefStrings->file26,
        this->dataRefStrings->tag26
    );

    this->gen_02_delay_1_bufferobj = initDataRef(
        this->gen_02_delay_1_bufferobj,
        this->dataRefStrings->name27,
        true,
        this->dataRefStrings->file27,
        this->dataRefStrings->tag27
    );

    this->gen_02_delay_2_bufferobj = initDataRef(
        this->gen_02_delay_2_bufferobj,
        this->dataRefStrings->name28,
        true,
        this->dataRefStrings->file28,
        this->dataRefStrings->tag28
    );

    this->gen_02_delay_3_bufferobj = initDataRef(
        this->gen_02_delay_3_bufferobj,
        this->dataRefStrings->name29,
        true,
        this->dataRefStrings->file29,
        this->dataRefStrings->tag29
    );

    this->gen_02_delay_4_bufferobj = initDataRef(
        this->gen_02_delay_4_bufferobj,
        this->dataRefStrings->name30,
        true,
        this->dataRefStrings->file30,
        this->dataRefStrings->tag30
    );

    this->gen_02_delay_5_bufferobj = initDataRef(
        this->gen_02_delay_5_bufferobj,
        this->dataRefStrings->name31,
        true,
        this->dataRefStrings->file31,
        this->dataRefStrings->tag31
    );

    this->gen_02_delay_6_bufferobj = initDataRef(
        this->gen_02_delay_6_bufferobj,
        this->dataRefStrings->name32,
        true,
        this->dataRefStrings->file32,
        this->dataRefStrings->tag32
    );

    this->gen_02_delay_7_bufferobj = initDataRef(
        this->gen_02_delay_7_bufferobj,
        this->dataRefStrings->name33,
        true,
        this->dataRefStrings->file33,
        this->dataRefStrings->tag33
    );

    this->gen_02_delay_8_bufferobj = initDataRef(
        this->gen_02_delay_8_bufferobj,
        this->dataRefStrings->name34,
        true,
        this->dataRefStrings->file34,
        this->dataRefStrings->tag34
    );

    this->gen_02_delay_9_bufferobj = initDataRef(
        this->gen_02_delay_9_bufferobj,
        this->dataRefStrings->name35,
        true,
        this->dataRefStrings->file35,
        this->dataRefStrings->tag35
    );

    this->gen_02_delay_11_bufferobj = initDataRef(
        this->gen_02_delay_11_bufferobj,
        this->dataRefStrings->name36,
        true,
        this->dataRefStrings->file36,
        this->dataRefStrings->tag36
    );

    this->gen_02_delay_12_bufferobj = initDataRef(
        this->gen_02_delay_12_bufferobj,
        this->dataRefStrings->name37,
        true,
        this->dataRefStrings->file37,
        this->dataRefStrings->tag37
    );

    this->gen_02_delay_13_bufferobj = initDataRef(
        this->gen_02_delay_13_bufferobj,
        this->dataRefStrings->name38,
        true,
        this->dataRefStrings->file38,
        this->dataRefStrings->tag38
    );

    this->gen_02_delay_14_bufferobj = initDataRef(
        this->gen_02_delay_14_bufferobj,
        this->dataRefStrings->name39,
        true,
        this->dataRefStrings->file39,
        this->dataRefStrings->tag39
    );

    this->gen_02_delay_15_bufferobj = initDataRef(
        this->gen_02_delay_15_bufferobj,
        this->dataRefStrings->name40,
        true,
        this->dataRefStrings->file40,
        this->dataRefStrings->tag40
    );

    this->gen_02_delay_16_bufferobj = initDataRef(
        this->gen_02_delay_16_bufferobj,
        this->dataRefStrings->name41,
        true,
        this->dataRefStrings->file41,
        this->dataRefStrings->tag41
    );

    this->gen_02_delay_17_bufferobj = initDataRef(
        this->gen_02_delay_17_bufferobj,
        this->dataRefStrings->name42,
        true,
        this->dataRefStrings->file42,
        this->dataRefStrings->tag42
    );

    this->gen_02_delay_18_bufferobj = initDataRef(
        this->gen_02_delay_18_bufferobj,
        this->dataRefStrings->name43,
        true,
        this->dataRefStrings->file43,
        this->dataRefStrings->tag43
    );

    this->assign_defaults();
    this->setState();
    this->gen_01_DL1_bufferobj->setIndex(0);
    this->gen_01_DL1_buffer = new Float64Buffer(this->gen_01_DL1_bufferobj);
    this->gen_01_DL2_bufferobj->setIndex(1);
    this->gen_01_DL2_buffer = new Float64Buffer(this->gen_01_DL2_bufferobj);
    this->gen_01_DL3_bufferobj->setIndex(2);
    this->gen_01_DL3_buffer = new Float64Buffer(this->gen_01_DL3_bufferobj);
    this->gen_01_DL4_bufferobj->setIndex(3);
    this->gen_01_DL4_buffer = new Float64Buffer(this->gen_01_DL4_bufferobj);
    this->gen_01_DL5_bufferobj->setIndex(4);
    this->gen_01_DL5_buffer = new Float64Buffer(this->gen_01_DL5_bufferobj);
    this->gen_01_DL6_bufferobj->setIndex(5);
    this->gen_01_DL6_buffer = new Float64Buffer(this->gen_01_DL6_bufferobj);
    this->gen_01_DL7_bufferobj->setIndex(6);
    this->gen_01_DL7_buffer = new Float64Buffer(this->gen_01_DL7_bufferobj);
    this->gen_01_DL8_bufferobj->setIndex(7);
    this->gen_01_DL8_buffer = new Float64Buffer(this->gen_01_DL8_bufferobj);
    this->gen_01_DL9_bufferobj->setIndex(8);
    this->gen_01_DL9_buffer = new Float64Buffer(this->gen_01_DL9_bufferobj);
    this->gen_01_DL10_bufferobj->setIndex(9);
    this->gen_01_DL10_buffer = new Float64Buffer(this->gen_01_DL10_bufferobj);
    this->gen_01_DL11_bufferobj->setIndex(10);
    this->gen_01_DL11_buffer = new Float64Buffer(this->gen_01_DL11_bufferobj);
    this->gen_01_DL12_bufferobj->setIndex(11);
    this->gen_01_DL12_buffer = new Float64Buffer(this->gen_01_DL12_bufferobj);
    this->gen_01_DL13_bufferobj->setIndex(12);
    this->gen_01_DL13_buffer = new Float64Buffer(this->gen_01_DL13_bufferobj);
    this->gen_01_dlL1_bufferobj->setIndex(13);
    this->gen_01_dlL1_buffer = new Float64Buffer(this->gen_01_dlL1_bufferobj);
    this->gen_01_dlL2_bufferobj->setIndex(14);
    this->gen_01_dlL2_buffer = new Float64Buffer(this->gen_01_dlL2_bufferobj);
    this->gen_01_dlL3_bufferobj->setIndex(15);
    this->gen_01_dlL3_buffer = new Float64Buffer(this->gen_01_dlL3_bufferobj);
    this->gen_01_dlL4_bufferobj->setIndex(16);
    this->gen_01_dlL4_buffer = new Float64Buffer(this->gen_01_dlL4_bufferobj);
    this->gen_01_dlL5_bufferobj->setIndex(17);
    this->gen_01_dlL5_buffer = new Float64Buffer(this->gen_01_dlL5_bufferobj);
    this->gen_01_dlL6_bufferobj->setIndex(18);
    this->gen_01_dlL6_buffer = new Float64Buffer(this->gen_01_dlL6_bufferobj);
    this->gen_01_dlL7_bufferobj->setIndex(19);
    this->gen_01_dlL7_buffer = new Float64Buffer(this->gen_01_dlL7_bufferobj);
    this->gen_01_dlL8_bufferobj->setIndex(20);
    this->gen_01_dlL8_buffer = new Float64Buffer(this->gen_01_dlL8_bufferobj);
    this->gen_01_dlL9_bufferobj->setIndex(21);
    this->gen_01_dlL9_buffer = new Float64Buffer(this->gen_01_dlL9_bufferobj);
    this->gen_01_dlL10_bufferobj->setIndex(22);
    this->gen_01_dlL10_buffer = new Float64Buffer(this->gen_01_dlL10_bufferobj);
    this->gen_01_dlL11_bufferobj->setIndex(23);
    this->gen_01_dlL11_buffer = new Float64Buffer(this->gen_01_dlL11_bufferobj);
    this->gen_01_dlL12_bufferobj->setIndex(24);
    this->gen_01_dlL12_buffer = new Float64Buffer(this->gen_01_dlL12_bufferobj);
    this->gen_01_dlL13_bufferobj->setIndex(25);
    this->gen_01_dlL13_buffer = new Float64Buffer(this->gen_01_dlL13_bufferobj);
    this->RNBODefaultSinus->setIndex(26);
    this->gen_01_cycle_8_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_01_cycle_13_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_01_cycle_18_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_01_cycle_23_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_01_cycle_28_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_01_cycle_33_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_01_cycle_38_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_01_cycle_43_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_02_cycle_17_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_02_cycle_26_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_02_cycle_36_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_02_cycle_45_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_02_cycle_54_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_02_cycle_63_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_02_cycle_74_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_02_cycle_87_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_02_delay_1_bufferobj->setIndex(27);
    this->gen_02_delay_1_buffer = new Float64Buffer(this->gen_02_delay_1_bufferobj);
    this->gen_02_delay_2_bufferobj->setIndex(28);
    this->gen_02_delay_2_buffer = new Float64Buffer(this->gen_02_delay_2_bufferobj);
    this->gen_02_delay_3_bufferobj->setIndex(29);
    this->gen_02_delay_3_buffer = new Float64Buffer(this->gen_02_delay_3_bufferobj);
    this->gen_02_delay_4_bufferobj->setIndex(30);
    this->gen_02_delay_4_buffer = new Float64Buffer(this->gen_02_delay_4_bufferobj);
    this->gen_02_delay_5_bufferobj->setIndex(31);
    this->gen_02_delay_5_buffer = new Float64Buffer(this->gen_02_delay_5_bufferobj);
    this->gen_02_delay_6_bufferobj->setIndex(32);
    this->gen_02_delay_6_buffer = new Float64Buffer(this->gen_02_delay_6_bufferobj);
    this->gen_02_delay_7_bufferobj->setIndex(33);
    this->gen_02_delay_7_buffer = new Float64Buffer(this->gen_02_delay_7_bufferobj);
    this->gen_02_delay_8_bufferobj->setIndex(34);
    this->gen_02_delay_8_buffer = new Float64Buffer(this->gen_02_delay_8_bufferobj);
    this->gen_02_delay_9_bufferobj->setIndex(35);
    this->gen_02_delay_9_buffer = new Float64Buffer(this->gen_02_delay_9_bufferobj);
    this->gen_02_delay_11_bufferobj->setIndex(36);
    this->gen_02_delay_11_buffer = new Float64Buffer(this->gen_02_delay_11_bufferobj);
    this->gen_02_delay_12_bufferobj->setIndex(37);
    this->gen_02_delay_12_buffer = new Float64Buffer(this->gen_02_delay_12_bufferobj);
    this->gen_02_delay_13_bufferobj->setIndex(38);
    this->gen_02_delay_13_buffer = new Float64Buffer(this->gen_02_delay_13_bufferobj);
    this->gen_02_delay_14_bufferobj->setIndex(39);
    this->gen_02_delay_14_buffer = new Float64Buffer(this->gen_02_delay_14_bufferobj);
    this->gen_02_delay_15_bufferobj->setIndex(40);
    this->gen_02_delay_15_buffer = new Float64Buffer(this->gen_02_delay_15_bufferobj);
    this->gen_02_delay_16_bufferobj->setIndex(41);
    this->gen_02_delay_16_buffer = new Float64Buffer(this->gen_02_delay_16_bufferobj);
    this->gen_02_delay_17_bufferobj->setIndex(42);
    this->gen_02_delay_17_buffer = new Float64Buffer(this->gen_02_delay_17_bufferobj);
    this->gen_02_delay_18_bufferobj->setIndex(43);
    this->gen_02_delay_18_buffer = new Float64Buffer(this->gen_02_delay_18_bufferobj);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

void getPreset(PatcherStateInterface& preset) {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "pre_del"));
    this->param_02_getPresetValue(getSubState(preset, "apf_g"));
    this->param_03_getPresetValue(getSubState(preset, "Size"));
    this->param_04_getPresetValue(getSubState(preset, "lowcut"));
    this->param_05_getPresetValue(getSubState(preset, "preq_level"));
    this->param_06_getPresetValue(getSubState(preset, "mix"));
    this->param_07_getPresetValue(getSubState(preset, "low_cut"));
    this->param_08_getPresetValue(getSubState(preset, "himidfq"));
    this->param_09_getPresetValue(getSubState(preset, "post_level"));
    this->param_10_getPresetValue(getSubState(preset, "himid_lev"));
    this->param_11_getPresetValue(getSubState(preset, "high_cut"));
    this->param_12_getPresetValue(getSubState(preset, "lfo1_bw"));
    this->param_13_getPresetValue(getSubState(preset, "himid_qf"));
    this->param_14_getPresetValue(getSubState(preset, "r_Feedback"));
    this->param_16_getPresetValue(getSubState(preset, "lfo1_rate"));
    this->param_17_getPresetValue(getSubState(preset, "r_Damp"));
    this->param_18_getPresetValue(getSubState(preset, "rt60_param"));
    this->param_19_getPresetValue(getSubState(preset, "xover"));
    this->param_20_getPresetValue(getSubState(preset, "bass_mult"));
    this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "Full_Mix~"));
    this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "postq_Level~"));
    this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "LowCut~"));
    this->p_04->getPreset(getSubState(getSubState(preset, "__sps"), "HighCut~"));
    this->p_05->getPreset(getSubState(getSubState(preset, "__sps"), "HighMid~"));
    this->p_06->getPreset(getSubState(getSubState(preset, "__sps"), "preq_Level~"));
    this->p_07->getPreset(getSubState(getSubState(preset, "__sps"), "preq_LowCut~"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->p_01->setPreset(time, getSubState(getSubState(preset, "__sps"), "Full_Mix~"));
    this->p_02->setPreset(time, getSubState(getSubState(preset, "__sps"), "postq_Level~"));
    this->p_03->setPreset(time, getSubState(getSubState(preset, "__sps"), "LowCut~"));
    this->p_04->setPreset(time, getSubState(getSubState(preset, "__sps"), "HighCut~"));
    this->p_05->setPreset(time, getSubState(getSubState(preset, "__sps"), "HighMid~"));
    this->p_06->setPreset(time, getSubState(getSubState(preset, "__sps"), "preq_Level~"));
    this->p_07->setPreset(time, getSubState(getSubState(preset, "__sps"), "preq_LowCut~"));
    this->param_01_setPresetValue(getSubState(preset, "pre_del"));
    this->param_02_setPresetValue(getSubState(preset, "apf_g"));
    this->param_03_setPresetValue(getSubState(preset, "Size"));
    this->param_12_setPresetValue(getSubState(preset, "lfo1_bw"));
    this->param_14_setPresetValue(getSubState(preset, "r_Feedback"));
    this->param_16_setPresetValue(getSubState(preset, "lfo1_rate"));
    this->param_17_setPresetValue(getSubState(preset, "r_Damp"));
    this->param_18_setPresetValue(getSubState(preset, "rt60_param"));
    this->param_20_setPresetValue(getSubState(preset, "bass_mult"));
    this->param_04_setPresetValue(getSubState(preset, "lowcut"));
    this->param_07_setPresetValue(getSubState(preset, "low_cut"));
    this->param_08_setPresetValue(getSubState(preset, "himidfq"));
    this->param_19_setPresetValue(getSubState(preset, "xover"));
    this->param_06_setPresetValue(getSubState(preset, "mix"));
    this->param_10_setPresetValue(getSubState(preset, "himid_lev"));
    this->param_13_setPresetValue(getSubState(preset, "himid_qf"));
    this->param_11_setPresetValue(getSubState(preset, "high_cut"));
    this->param_05_setPresetValue(getSubState(preset, "preq_level"));
    this->param_09_setPresetValue(getSubState(preset, "post_level"));
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (index) {
    case 0:
        {
        this->param_04_value_set(v);
        break;
        }
    case 1:
        {
        this->param_07_value_set(v);
        break;
        }
    case 2:
        {
        this->param_05_value_set(v);
        break;
        }
    case 3:
        {
        this->param_09_value_set(v);
        break;
        }
    case 4:
        {
        this->param_14_value_set(v);
        break;
        }
    case 5:
        {
        this->param_15_value_set(v);
        break;
        }
    case 6:
        {
        this->param_16_value_set(v);
        break;
        }
    case 7:
        {
        this->param_17_value_set(v);
        break;
        }
    case 8:
        {
        this->param_02_value_set(v);
        break;
        }
    case 9:
        {
        this->param_06_value_set(v);
        break;
        }
    case 10:
        {
        this->param_01_value_set(v);
        break;
        }
    case 11:
        {
        this->param_03_value_set(v);
        break;
        }
    case 12:
        {
        this->param_08_value_set(v);
        break;
        }
    case 13:
        {
        this->param_10_value_set(v);
        break;
        }
    case 14:
        {
        this->param_11_value_set(v);
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
        this->param_18_value_set(v);
        break;
        }
    case 18:
        {
        this->param_19_value_set(v);
        break;
        }
    case 19:
        {
        this->param_20_value_set(v);
        break;
        }
    default:
        {
        index -= 20;

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
        return this->param_04_value;
        }
    case 1:
        {
        return this->param_07_value;
        }
    case 2:
        {
        return this->param_05_value;
        }
    case 3:
        {
        return this->param_09_value;
        }
    case 4:
        {
        return this->param_14_value;
        }
    case 5:
        {
        return this->param_15_value;
        }
    case 6:
        {
        return this->param_16_value;
        }
    case 7:
        {
        return this->param_17_value;
        }
    case 8:
        {
        return this->param_02_value;
        }
    case 9:
        {
        return this->param_06_value;
        }
    case 10:
        {
        return this->param_01_value;
        }
    case 11:
        {
        return this->param_03_value;
        }
    case 12:
        {
        return this->param_08_value;
        }
    case 13:
        {
        return this->param_10_value;
        }
    case 14:
        {
        return this->param_11_value;
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
        return this->param_18_value;
        }
    case 18:
        {
        return this->param_19_value;
        }
    case 19:
        {
        return this->param_20_value;
        }
    default:
        {
        index -= 20;

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
    return 20 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters();
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
        return "preq_level";
        }
    case 3:
        {
        return "post_level";
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
        return "pre_del";
        }
    case 11:
        {
        return "Size";
        }
    case 12:
        {
        return "himidfq";
        }
    case 13:
        {
        return "himid_lev";
        }
    case 14:
        {
        return "high_cut";
        }
    case 15:
        {
        return "lfo1_bw";
        }
    case 16:
        {
        return "himid_qf";
        }
    case 17:
        {
        return "rt60_param";
        }
    case 18:
        {
        return "xover";
        }
    case 19:
        {
        return "bass_mult";
        }
    default:
        {
        index -= 20;

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
        return "preq_level";
        }
    case 3:
        {
        return "post_level";
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
        return "pre_del";
        }
    case 11:
        {
        return "Size";
        }
    case 12:
        {
        return "himidfq";
        }
    case 13:
        {
        return "himid_lev";
        }
    case 14:
        {
        return "high_cut";
        }
    case 15:
        {
        return "lfo1_bw";
        }
    case 16:
        {
        return "himid_qf";
        }
    case 17:
        {
        return "rt60_param";
        }
    case 18:
        {
        return "xover";
        }
    case 19:
        {
        return "bass_mult";
        }
    default:
        {
        index -= 20;

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
            info->initialValue = 10;
            info->min = 10;
            info->max = 800;
            info->exponent = 5;
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
            info->displayName = "post_Level";
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
            info->initialValue = 70;
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
            info->initialValue = 0.2;
            info->min = 0;
            info->max = 3;
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
            info->initialValue = 4;
            info->min = 0;
            info->max = 10;
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
        case 9:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
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
            info->initialValue = 20;
            info->min = 0;
            info->max = 500;
            info->exponent = 2.25;
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
            info->initialValue = 45;
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
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 12:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1000;
            info->min = 1000;
            info->max = 8000;
            info->exponent = 2.025;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "HighMidFreq";
            info->unit = "Hz";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 13:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -18;
            info->max = 18;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "HighMid_lev";
            info->unit = "db";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 14:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1000;
            info->min = 1000;
            info->max = 16000;
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
        case 15:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.3;
            info->min = 0;
            info->max = 2;
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
        case 16:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.25;
            info->min = 0.25;
            info->max = 5;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "HighMid_qf";
            info->unit = "q";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 17:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 6907;
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
        case 18:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 100;
            info->min = 100;
            info->max = 2000;
            info->exponent = 2.025;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "XoverFreq";
            info->unit = "Hz";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 19:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.25;
            info->min = 0.25;
            info->max = 2;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "x";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        default:
            {
            index -= 20;

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
    case 15:
        {
        {
            value = (value < 0 ? 0 : (value > 2 ? 2 : value));
            ParameterValue normalizedValue = (value - 0) / (2 - 0);
            return normalizedValue;
        }
        }
    case 6:
        {
        {
            value = (value < 0 ? 0 : (value > 3 ? 3 : value));
            ParameterValue normalizedValue = (value - 0) / (3 - 0);
            return normalizedValue;
        }
        }
    case 8:
        {
        {
            value = (value < 0 ? 0 : (value > 10 ? 10 : value));
            ParameterValue normalizedValue = (value - 0) / (10 - 0);
            return normalizedValue;
        }
        }
    case 4:
    case 5:
    case 7:
    case 9:
    case 11:
        {
        {
            value = (value < 0 ? 0 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0) / (100 - 0);
            return normalizedValue;
        }
        }
    case 10:
        {
        {
            value = (value < 0 ? 0 : (value > 500 ? 500 : value));
            ParameterValue normalizedValue = (value - 0) / (500 - 0);

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
            value = (value < 0 ? 0 : (value > 6907 ? 6907 : value));
            ParameterValue normalizedValue = (value - 0) / (6907 - 0);
            return normalizedValue;
        }
        }
    case 1:
        {
        {
            value = (value < 10 ? 10 : (value > 800 ? 800 : value));
            ParameterValue normalizedValue = (value - 10) / (800 - 10);

            {
                if (normalizedValue != 0.0) {
                    normalizedValue = rnbo_exp(
                        rnbo_log((normalizedValue <= 0.0000000001 ? 0.0000000001 : normalizedValue)) * 1. / (number)5
                    );
                }
            }

            return normalizedValue;
        }
        }
    case 18:
        {
        {
            value = (value < 100 ? 100 : (value > 2000 ? 2000 : value));
            ParameterValue normalizedValue = (value - 100) / (2000 - 100);

            {
                if (normalizedValue != 0.0) {
                    normalizedValue = rnbo_exp(
                        rnbo_log((normalizedValue <= 0.0000000001 ? 0.0000000001 : normalizedValue)) * 1. / (number)2.025
                    );
                }
            }

            return normalizedValue;
        }
        }
    case 12:
        {
        {
            value = (value < 1000 ? 1000 : (value > 8000 ? 8000 : value));
            ParameterValue normalizedValue = (value - 1000) / (8000 - 1000);

            {
                if (normalizedValue != 0.0) {
                    normalizedValue = rnbo_exp(
                        rnbo_log((normalizedValue <= 0.0000000001 ? 0.0000000001 : normalizedValue)) * 1. / (number)2.025
                    );
                }
            }

            return normalizedValue;
        }
        }
    case 14:
        {
        {
            value = (value < 1000 ? 1000 : (value > 16000 ? 16000 : value));
            ParameterValue normalizedValue = (value - 1000) / (16000 - 1000);

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
    case 2:
    case 3:
        {
        {
            value = (value < -100 ? -100 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - -100) / (100 - -100);
            return normalizedValue;
        }
        }
    case 13:
        {
        {
            value = (value < -18 ? -18 : (value > 18 ? 18 : value));
            ParameterValue normalizedValue = (value - -18) / (18 - -18);
            return normalizedValue;
        }
        }
    case 19:
        {
        {
            value = (value < 0.25 ? 0.25 : (value > 2 ? 2 : value));
            ParameterValue normalizedValue = (value - 0.25) / (2 - 0.25);
            return normalizedValue;
        }
        }
    case 16:
        {
        {
            value = (value < 0.25 ? 0.25 : (value > 5 ? 5 : value));
            ParameterValue normalizedValue = (value - 0.25) / (5 - 0.25);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 20;

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
    case 15:
        {
        {
            {
                return 0 + value * (2 - 0);
            }
        }
        }
    case 6:
        {
        {
            {
                return 0 + value * (3 - 0);
            }
        }
        }
    case 8:
        {
        {
            {
                return 0 + value * (10 - 0);
            }
        }
        }
    case 4:
    case 5:
    case 7:
    case 9:
    case 11:
        {
        {
            {
                return 0 + value * (100 - 0);
            }
        }
        }
    case 10:
        {
        {
            {
                if (value == 0.0) {
                    return 0;
                } else {
                    return 0 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 2.25) * (500 - 0);
                }
            }
        }
        }
    case 17:
        {
        {
            {
                return 0 + value * (6907 - 0);
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
                    return 10 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 5) * (800 - 10);
                }
            }
        }
        }
    case 18:
        {
        {
            {
                if (value == 0.0) {
                    return 100;
                } else {
                    return 100 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 2.025) * (2000 - 100);
                }
            }
        }
        }
    case 12:
        {
        {
            {
                if (value == 0.0) {
                    return 1000;
                } else {
                    return 1000 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 2.025) * (8000 - 1000);
                }
            }
        }
        }
    case 14:
        {
        {
            {
                if (value == 0.0) {
                    return 1000;
                } else {
                    return 1000 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 2.25) * (16000 - 1000);
                }
            }
        }
        }
    case 2:
    case 3:
        {
        {
            {
                return -100 + value * (100 - -100);
            }
        }
        }
    case 13:
        {
        {
            {
                return -18 + value * (18 - -18);
            }
        }
        }
    case 19:
        {
        {
            {
                return 0.25 + value * (2 - 0.25);
            }
        }
        }
    case 16:
        {
        {
            {
                return 0.25 + value * (5 - 0.25);
            }
        }
        }
    default:
        {
        index -= 20;

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
        return this->param_04_value_constrain(value);
        }
    case 1:
        {
        return this->param_07_value_constrain(value);
        }
    case 2:
        {
        return this->param_05_value_constrain(value);
        }
    case 3:
        {
        return this->param_09_value_constrain(value);
        }
    case 4:
        {
        return this->param_14_value_constrain(value);
        }
    case 5:
        {
        return this->param_15_value_constrain(value);
        }
    case 6:
        {
        return this->param_16_value_constrain(value);
        }
    case 7:
        {
        return this->param_17_value_constrain(value);
        }
    case 8:
        {
        return this->param_02_value_constrain(value);
        }
    case 9:
        {
        return this->param_06_value_constrain(value);
        }
    case 10:
        {
        return this->param_01_value_constrain(value);
        }
    case 11:
        {
        return this->param_03_value_constrain(value);
        }
    case 12:
        {
        return this->param_08_value_constrain(value);
        }
    case 13:
        {
        return this->param_10_value_constrain(value);
        }
    case 14:
        {
        return this->param_11_value_constrain(value);
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
        return this->param_18_value_constrain(value);
        }
    case 18:
        {
        return this->param_19_value_constrain(value);
        }
    case 19:
        {
        return this->param_20_value_constrain(value);
        }
    default:
        {
        index -= 20;

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

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (tag) {
    case TAG("valin"):
        {
        if (TAG("number_obj-20") == objectId)
            this->numberobj_14_valin_set(payload);

        if (TAG("toggle_obj-37") == objectId)
            this->toggle_02_valin_set(payload);

        if (TAG("number_obj-68") == objectId)
            this->numberobj_15_valin_set(payload);

        if (TAG("number_obj-87") == objectId)
            this->numberobj_16_valin_set(payload);

        if (TAG("number_obj-136") == objectId)
            this->numberobj_17_valin_set(payload);

        if (TAG("number_obj-139") == objectId)
            this->numberobj_18_valin_set(payload);

        if (TAG("number_obj-24") == objectId)
            this->numberobj_19_valin_set(payload);

        if (TAG("number_obj-103") == objectId)
            this->numberobj_20_valin_set(payload);

        if (TAG("number_obj-105") == objectId)
            this->numberobj_21_valin_set(payload);

        if (TAG("number_obj-6") == objectId)
            this->numberobj_22_valin_set(payload);

        if (TAG("number_obj-43") == objectId)
            this->numberobj_23_valin_set(payload);

        if (TAG("number_obj-35") == objectId)
            this->numberobj_24_valin_set(payload);

        if (TAG("number_obj-42") == objectId)
            this->numberobj_25_valin_set(payload);

        if (TAG("number_obj-50") == objectId)
            this->numberobj_26_valin_set(payload);

        if (TAG("number_obj-120") == objectId)
            this->numberobj_27_valin_set(payload);

        break;
        }
    case TAG("format"):
        {
        if (TAG("number_obj-20") == objectId)
            this->numberobj_14_format_set(payload);

        if (TAG("number_obj-68") == objectId)
            this->numberobj_15_format_set(payload);

        if (TAG("number_obj-87") == objectId)
            this->numberobj_16_format_set(payload);

        if (TAG("number_obj-136") == objectId)
            this->numberobj_17_format_set(payload);

        if (TAG("number_obj-139") == objectId)
            this->numberobj_18_format_set(payload);

        if (TAG("number_obj-24") == objectId)
            this->numberobj_19_format_set(payload);

        if (TAG("number_obj-103") == objectId)
            this->numberobj_20_format_set(payload);

        if (TAG("number_obj-105") == objectId)
            this->numberobj_21_format_set(payload);

        if (TAG("number_obj-6") == objectId)
            this->numberobj_22_format_set(payload);

        if (TAG("number_obj-43") == objectId)
            this->numberobj_23_format_set(payload);

        if (TAG("number_obj-35") == objectId)
            this->numberobj_24_format_set(payload);

        if (TAG("number_obj-42") == objectId)
            this->numberobj_25_format_set(payload);

        if (TAG("number_obj-50") == objectId)
            this->numberobj_26_format_set(payload);

        if (TAG("number_obj-120") == objectId)
            this->numberobj_27_format_set(payload);

        break;
        }
    case TAG("listin"):
        {
        if (TAG("message_obj-39") == objectId)
            this->message_01_listin_number_set(payload);

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
    this->updateTime(time, (ENGINE*)nullptr);

    switch (tag) {
    case TAG("listin"):
        {
        if (TAG("message_obj-39") == objectId)
            this->message_01_listin_list_set(payload);

        break;
        }
    }

    this->p_01->processListMessage(tag, objectId, time, payload);
    this->p_02->processListMessage(tag, objectId, time, payload);
    this->p_03->processListMessage(tag, objectId, time, payload);
    this->p_04->processListMessage(tag, objectId, time, payload);
    this->p_05->processListMessage(tag, objectId, time, payload);
    this->p_06->processListMessage(tag, objectId, time, payload);
    this->p_07->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (tag) {
    case TAG("listin"):
        {
        if (TAG("message_obj-39") == objectId)
            this->message_01_listin_bang_bang();

        break;
        }
    }

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
    case TAG("number_obj-20"):
        {
        return "number_obj-20";
        }
    case TAG("setup"):
        {
        return "setup";
        }
    case TAG("toggle_obj-37"):
        {
        return "toggle_obj-37";
        }
    case TAG("number_obj-68"):
        {
        return "number_obj-68";
        }
    case TAG("number_obj-87"):
        {
        return "number_obj-87";
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
    case TAG("number_obj-43"):
        {
        return "number_obj-43";
        }
    case TAG("listout"):
        {
        return "listout";
        }
    case TAG("message_obj-39"):
        {
        return "message_obj-39";
        }
    case TAG("number_obj-35"):
        {
        return "number_obj-35";
        }
    case TAG("number_obj-42"):
        {
        return "number_obj-42";
        }
    case TAG("number_obj-50"):
        {
        return "number_obj-50";
        }
    case TAG("number_obj-120"):
        {
        return "number_obj-120";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    case TAG("format"):
        {
        return "format";
        }
    case TAG("listin"):
        {
        return "listin";
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

class RNBOSubpatcher_72 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_72()
    {}
    
    ~RNBOSubpatcher_72()
    {}
    
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
        this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
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
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getNumInputChannels() const {
        return 5;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setPreset(MillisecondTime , PatcherStateInterface& ) {}
    
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
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void updateTime(MillisecondTime time, INTERNALENGINE*) {
    	if (time == TimeNow) time = getTopLevelPatcher()->getPatcherTime();
    	getTopLevelPatcher()->processInternalEvents(time);
    	updateTime(time, (EXTERNALENGINE*)nullptr);
    }
    
    RNBOSubpatcher_72* operator->() {
        return this;
    }
    const RNBOSubpatcher_72* operator->() const {
        return this;
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
    
    MillisecondTime getPatcherTime() const {
        return this->_currentTime;
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
    
    void setProbingTarget(MessageTag ) {}
    
    void initializeObjects() {}
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time, (ENGINE*)nullptr);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
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
    
    number xfade_tilde_01_func_next(number pos, Int channel) {
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
    
    number xfade_tilde_02_func_next(number pos, Int channel) {
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
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void updateTime(MillisecondTime time, EXTERNALENGINE ) {
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
        invsr = 0.000022675736961451248;
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

class RNBOSubpatcher_73 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_73()
    {}
    
    ~RNBOSubpatcher_73()
    {}
    
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
        this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
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
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setPreset(MillisecondTime , PatcherStateInterface& ) {}
    
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
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("postq_Level~/number_obj-7") == objectId)
                this->numberobj_01_valin_set(payload);
    
            if (TAG("postq_Level~/number_obj-14") == objectId)
                this->numberobj_02_valin_set(payload);
    
            if (TAG("postq_Level~/number_obj-5") == objectId)
                this->numberobj_03_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("postq_Level~/number_obj-7") == objectId)
                this->numberobj_01_format_set(payload);
    
            if (TAG("postq_Level~/number_obj-14") == objectId)
                this->numberobj_02_format_set(payload);
    
            if (TAG("postq_Level~/number_obj-5") == objectId)
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
        case TAG("postq_Level~/number_obj-7"):
            {
            return "postq_Level~/number_obj-7";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("postq_Level~/number_obj-14"):
            {
            return "postq_Level~/number_obj-14";
            }
        case TAG("postq_Level~/number_obj-5"):
            {
            return "postq_Level~/number_obj-5";
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
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void updateTime(MillisecondTime time, INTERNALENGINE*) {
    	if (time == TimeNow) time = getTopLevelPatcher()->getPatcherTime();
    	getTopLevelPatcher()->processInternalEvents(time);
    	updateTime(time, (EXTERNALENGINE*)nullptr);
    }
    
    RNBOSubpatcher_73* operator->() {
        return this;
    }
    const RNBOSubpatcher_73* operator->() const {
        return this;
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
    
    MillisecondTime getPatcherTime() const {
        return this->_currentTime;
    }
    
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
    
    template<typename LISTTYPE> void eventinlet_01_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_02_value_set(converted);
        }
    }
    
    void linetilde_01_target_bang() {}
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    void setProbingTarget(MessageTag ) {}
    
    void initializeObjects() {
        this->numberobj_01_init();
        this->numberobj_02_init();
        this->numberobj_03_init();
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time, (ENGINE*)nullptr);
    
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
        this->updateTime(time, (ENGINE*)nullptr);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void allocateDataRefs() {}
    
    void linetilde_01_time_set(number v) {
        this->linetilde_01_time = v;
    }
    
    template<typename LISTTYPE> void linetilde_01_segments_set(const LISTTYPE& v) {
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
            listbase<number, 1> converted = {v};
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
    
        this->numberobj_01_output_set(localvalue);
    }
    
    void expr_01_out1_set(number v) {
        this->expr_01_out1 = v;
        this->numberobj_01_value_set(this->expr_01_out1);
    }
    
    void expr_01_in1_set(number in1) {
        this->expr_01_in1 = in1;
        this->expr_01_out1_set(rnbo_pow(10, this->expr_01_in1 * 0.05));//#map:postq_Level~/dbtoa_obj-3:1
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
    
        this->numberobj_03_output_set(localvalue);
    }
    
    template<typename LISTTYPE> void scale_01_out_set(const LISTTYPE& v) {
        this->scale_01_out = jsCreateListCopy(v);
    
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_03_value_set(converted);
        }
    }
    
    template<typename LISTTYPE> void scale_01_input_set(const LISTTYPE& v) {
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
            listbase<number, 1> converted = {v};
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
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void updateTime(MillisecondTime time, EXTERNALENGINE ) {
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
        linetilde_01_keepramp = true;
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
        invsr = 0.000022675736961451248;
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

class RNBOSubpatcher_74 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_74()
    {}
    
    ~RNBOSubpatcher_74()
    {}
    
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
        this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        this->linetilde_02_perform(this->signals[0], n);
    
        this->filtercoeff_tilde_01_perform(
            this->signals[0],
            this->filtercoeff_tilde_01_gain,
            this->filtercoeff_tilde_01_q,
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
    
        this->filtercoeff_tilde_01_dspsetup(forceDSPSetup);
        this->biquad_tilde_02_dspsetup(forceDSPSetup);
        this->biquad_tilde_01_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setPreset(MillisecondTime , PatcherStateInterface& ) {}
    
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
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time, (ENGINE*)nullptr);
    
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
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void updateTime(MillisecondTime time, INTERNALENGINE*) {
    	if (time == TimeNow) time = getTopLevelPatcher()->getPatcherTime();
    	getTopLevelPatcher()->processInternalEvents(time);
    	updateTime(time, (EXTERNALENGINE*)nullptr);
    }
    
    RNBOSubpatcher_74* operator->() {
        return this;
    }
    const RNBOSubpatcher_74* operator->() const {
        return this;
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
    
    MillisecondTime getPatcherTime() const {
        return this->_currentTime;
    }
    
    void numberobj_04_valin_set(number v) {
        this->numberobj_04_value_set(v);
    }
    
    void numberobj_04_format_set(number v) {
        this->numberobj_04_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_02_out1_bang_bang() {
        this->numberobj_04_value_bang();
    }
    
    template<typename LISTTYPE> void eventinlet_02_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_04_value_set(converted);
        }
    }
    
    void linetilde_02_target_bang() {}
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    void setProbingTarget(MessageTag ) {}
    
    void initializeObjects() {
        this->numberobj_04_init();
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time, (ENGINE*)nullptr);
    
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
        this->updateTime(time, (ENGINE*)nullptr);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void allocateDataRefs() {}
    
    void linetilde_02_time_set(number v) {
        this->linetilde_02_time = v;
    }
    
    template<typename LISTTYPE> void linetilde_02_segments_set(const LISTTYPE& v) {
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
            listbase<number, 1> converted = {v};
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
    
    void filtercoeff_tilde_01_perform(
        const Sample * frequency,
        number gain,
        number q,
        SampleValue * out1,
        SampleValue * out2,
        SampleValue * out3,
        SampleValue * out4,
        SampleValue * out5,
        Index n
    ) {
        RNBO_UNUSED(q);
        RNBO_UNUSED(gain);
        auto __filtercoeff_tilde_01_resamp_value = this->filtercoeff_tilde_01_resamp_value;
        auto __filtercoeff_tilde_01_resamp_counter = this->filtercoeff_tilde_01_resamp_counter;
        auto __filtercoeff_tilde_01_lb2 = this->filtercoeff_tilde_01_lb2;
        auto __filtercoeff_tilde_01_lb1 = this->filtercoeff_tilde_01_lb1;
        auto __filtercoeff_tilde_01_la2 = this->filtercoeff_tilde_01_la2;
        auto __filtercoeff_tilde_01_la1 = this->filtercoeff_tilde_01_la1;
        auto __filtercoeff_tilde_01_la0 = this->filtercoeff_tilde_01_la0;
        auto __filtercoeff_tilde_01_c_type = this->filtercoeff_tilde_01_c_type;
        auto __filtercoeff_tilde_01_type = this->filtercoeff_tilde_01_type;
        auto __filtercoeff_tilde_01_c_q = this->filtercoeff_tilde_01_c_q;
        auto __filtercoeff_tilde_01_c_gain = this->filtercoeff_tilde_01_c_gain;
        auto __filtercoeff_tilde_01_c_frequency = this->filtercoeff_tilde_01_c_frequency;
        number sr = this->sr;
        number halfsr = sr * 0.5;
        Index i;
    
        for (i = 0; i < n; i++) {
            number __frequency = frequency[(Index)i];
            number __q = 1;
    
            if (__frequency == __filtercoeff_tilde_01_c_frequency && 1 == __filtercoeff_tilde_01_c_gain && __q == __filtercoeff_tilde_01_c_q && __filtercoeff_tilde_01_type == __filtercoeff_tilde_01_c_type) {
                out1[(Index)i] = __filtercoeff_tilde_01_la0;
                out2[(Index)i] = __filtercoeff_tilde_01_la1;
                out3[(Index)i] = __filtercoeff_tilde_01_la2;
                out4[(Index)i] = __filtercoeff_tilde_01_lb1;
                out5[(Index)i] = __filtercoeff_tilde_01_lb2;
                continue;
            }
    
            if (__filtercoeff_tilde_01_resamp_counter > 0) {
                __filtercoeff_tilde_01_resamp_counter--;
                out1[(Index)i] = __filtercoeff_tilde_01_la0;
                out2[(Index)i] = __filtercoeff_tilde_01_la1;
                out3[(Index)i] = __filtercoeff_tilde_01_la2;
                out4[(Index)i] = __filtercoeff_tilde_01_lb1;
                out5[(Index)i] = __filtercoeff_tilde_01_lb2;
                continue;
            }
    
            __filtercoeff_tilde_01_resamp_counter = __filtercoeff_tilde_01_resamp_value;
            __filtercoeff_tilde_01_c_frequency = __frequency;
            __filtercoeff_tilde_01_c_gain = 1;
            __filtercoeff_tilde_01_c_q = __q;
            __filtercoeff_tilde_01_c_type = __filtercoeff_tilde_01_type;
    
            if (__q < 1e-9)
                __q = 1e-9;
    
            __frequency = (__frequency > halfsr ? halfsr : (__frequency < 1 ? 1 : __frequency));
            number omega = __frequency * ((number)6.283185307179586 / sr);
            number cs = rnbo_cos(omega);
            number sn = rnbo_sin(omega);
            number one_over_gain = (number)1 / (number)1;
            number one_over_q = (number)1 / __q;
            number alpha = sn * 0.5 * one_over_q;
            number beta;
            number A;
            number one_over_a;
            number b0;
            number b0g;
    
            switch (__filtercoeff_tilde_01_type) {
            case 5:
                {
                A = this->safesqrt(1);
                beta = this->safesqrt((A * A + 1.) * one_over_q - (A - 1.) * (A - 1.));
                b0 = (number)1 / (A + 1. + (A - 1.) * cs + beta * sn);
                break;
                }
            case 6:
                {
                A = this->safesqrt(1);
                beta = this->safesqrt((A * A + 1.) * one_over_q - (A - 1.) * (A - 1.));
                b0 = (number)1 / (A + 1. - (A - 1.) * cs + beta * sn);
                break;
                }
            case 4:
                {
                A = this->safesqrt(1);
                one_over_a = (A == 0 ? 0 : (number)1 / A);
                b0 = (number)1 / (1. + alpha * one_over_a);
                break;
                }
            case 9:
            case 10:
            case 11:
            case 13:
            case 14:
                {
                b0 = (number)1 / (1. + alpha);
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                break;
                }
            default:
                {
                b0 = (number)1 / (1. + alpha);
                break;
                }
            }
    
            switch (__filtercoeff_tilde_01_type) {
            case 0:
                {
                __filtercoeff_tilde_01_la0 = __filtercoeff_tilde_01_la2 = (1. - cs) * 0.5 * b0;
                __filtercoeff_tilde_01_la1 = (1. - cs) * b0;
                __filtercoeff_tilde_01_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_01_lb2 = (1. - alpha) * b0;
                break;
                }
            case 1:
                {
                __filtercoeff_tilde_01_la0 = __filtercoeff_tilde_01_la2 = (1. + cs) * 0.5 * b0;
                __filtercoeff_tilde_01_la1 = -(1. + cs) * b0;
                __filtercoeff_tilde_01_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_01_lb2 = (1. - alpha) * b0;
                break;
                }
            case 2:
                {
                __filtercoeff_tilde_01_la0 = alpha * b0;
                __filtercoeff_tilde_01_la1 = 0.;
                __filtercoeff_tilde_01_la2 = -alpha * b0;
                __filtercoeff_tilde_01_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_01_lb2 = (1. - alpha) * b0;
                break;
                }
            case 7:
                {
                __filtercoeff_tilde_01_la0 = alpha * __q * b0;
                __filtercoeff_tilde_01_la1 = 0.;
                __filtercoeff_tilde_01_la2 = -alpha * __q * b0;
                __filtercoeff_tilde_01_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_01_lb2 = (1. - alpha) * b0;
                break;
                }
            case 3:
                {
                __filtercoeff_tilde_01_la1 = __filtercoeff_tilde_01_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_01_lb2 = (1. - alpha) * b0;
                __filtercoeff_tilde_01_la0 = __filtercoeff_tilde_01_la2 = b0;
                break;
                }
            case 8:
                {
                __filtercoeff_tilde_01_la1 = __filtercoeff_tilde_01_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_01_lb2 = __filtercoeff_tilde_01_la0 = (1. - alpha) * b0;
                __filtercoeff_tilde_01_la2 = 1.0;
                break;
                }
            case 4:
                {
                __filtercoeff_tilde_01_la0 = (1. + alpha * A) * b0;
                __filtercoeff_tilde_01_la1 = __filtercoeff_tilde_01_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_01_la2 = (1. - alpha * A) * b0;
                __filtercoeff_tilde_01_lb2 = (1. - alpha * one_over_a) * b0;
                break;
                }
            case 5:
                {
                __filtercoeff_tilde_01_la0 = A * (A + 1. - (A - 1.) * cs + beta * sn) * b0;
                __filtercoeff_tilde_01_la1 = 2. * A * (A - 1 - (A + 1) * cs) * b0;
                __filtercoeff_tilde_01_la2 = A * (A + 1. - (A - 1.) * cs - beta * sn) * b0;
                __filtercoeff_tilde_01_lb1 = -2. * (A - 1. + (A + 1.) * cs) * b0;
                __filtercoeff_tilde_01_lb2 = (A + 1. + (A - 1.) * cs - beta * sn) * b0;
                break;
                }
            case 6:
                {
                __filtercoeff_tilde_01_la0 = A * (A + 1. + (A - 1.) * cs + beta * sn) * b0;
                __filtercoeff_tilde_01_la1 = -2. * A * (A - 1. + (A + 1.) * cs) * b0;
                __filtercoeff_tilde_01_la2 = A * (A + 1. + (A - 1.) * cs - beta * sn) * b0;
                __filtercoeff_tilde_01_lb1 = 2. * (A - 1. - (A + 1.) * cs) * b0;
                __filtercoeff_tilde_01_lb2 = (A + 1. - (A - 1.) * cs - beta * sn) * b0;
                break;
                }
            case 9:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_01_la0 = __filtercoeff_tilde_01_la2 = (1. - cs) * 0.5 * b0g;
                __filtercoeff_tilde_01_la1 = (1. - cs) * b0g;
                __filtercoeff_tilde_01_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_01_lb2 = (1. - alpha) * b0;
                break;
                }
            case 10:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_01_la0 = __filtercoeff_tilde_01_la2 = (1. + cs) * 0.5 * b0g;
                __filtercoeff_tilde_01_la1 = -(1. + cs) * b0g;
                __filtercoeff_tilde_01_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_01_lb2 = (1. - alpha) * b0;
                break;
                }
            case 11:
                {
                __filtercoeff_tilde_01_la0 = alpha * 1 * b0;
                __filtercoeff_tilde_01_la1 = 0.;
                __filtercoeff_tilde_01_la2 = -alpha * 1 * b0;
                __filtercoeff_tilde_01_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_01_lb2 = (1. - alpha) * b0;
                break;
                }
            case 13:
                {
                __filtercoeff_tilde_01_la0 = alpha * 1 * __q * b0;
                __filtercoeff_tilde_01_la1 = 0.;
                __filtercoeff_tilde_01_la2 = -alpha * 1 * __q * b0;
                __filtercoeff_tilde_01_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_01_lb2 = (1. - alpha) * b0;
                break;
                }
            case 12:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_01_la1 = __filtercoeff_tilde_01_lb1 = -2. * cs;
                __filtercoeff_tilde_01_lb2 = (1. - alpha) * b0;
                __filtercoeff_tilde_01_la1 *= b0g;
                __filtercoeff_tilde_01_lb1 *= b0;
                __filtercoeff_tilde_01_la0 = b0g;
                __filtercoeff_tilde_01_la2 = b0g;
                break;
                }
            case 14:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_01_la0 = (1. - alpha) * b0g;
                __filtercoeff_tilde_01_la1 = -2. * cs * b0g;
                __filtercoeff_tilde_01_la2 = 1;
                __filtercoeff_tilde_01_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_01_lb2 = (1. - alpha) * b0;
                break;
                }
            case 15:
                {
                __filtercoeff_tilde_01_la0 = 1;
                __filtercoeff_tilde_01_la1 = 0;
                __filtercoeff_tilde_01_la2 = 0;
                __filtercoeff_tilde_01_lb1 = 0;
                __filtercoeff_tilde_01_lb2 = 0;
                }
            default:
                {
                break;
                }
            }
    
            out1[(Index)i] = __filtercoeff_tilde_01_la0;
            out2[(Index)i] = __filtercoeff_tilde_01_la1;
            out3[(Index)i] = __filtercoeff_tilde_01_la2;
            out4[(Index)i] = __filtercoeff_tilde_01_lb1;
            out5[(Index)i] = __filtercoeff_tilde_01_lb2;
        }
    
        this->filtercoeff_tilde_01_c_frequency = __filtercoeff_tilde_01_c_frequency;
        this->filtercoeff_tilde_01_c_gain = __filtercoeff_tilde_01_c_gain;
        this->filtercoeff_tilde_01_c_q = __filtercoeff_tilde_01_c_q;
        this->filtercoeff_tilde_01_c_type = __filtercoeff_tilde_01_c_type;
        this->filtercoeff_tilde_01_la0 = __filtercoeff_tilde_01_la0;
        this->filtercoeff_tilde_01_la1 = __filtercoeff_tilde_01_la1;
        this->filtercoeff_tilde_01_la2 = __filtercoeff_tilde_01_la2;
        this->filtercoeff_tilde_01_lb1 = __filtercoeff_tilde_01_lb1;
        this->filtercoeff_tilde_01_lb2 = __filtercoeff_tilde_01_lb2;
        this->filtercoeff_tilde_01_resamp_counter = __filtercoeff_tilde_01_resamp_counter;
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
    }
    
    void numberobj_04_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_04_value;
    }
    
    void numberobj_04_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_04_value_set(preset["value"]);
    }
    
    void filtercoeff_tilde_01_dspsetup(bool force) {
        if ((bool)(this->filtercoeff_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->filtercoeff_tilde_01_resamp_value = this->vs;
        this->filtercoeff_tilde_01_setupDone = true;
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void updateTime(MillisecondTime time, EXTERNALENGINE ) {
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
        linetilde_02_keepramp = true;
        filtercoeff_tilde_01_frequency = 1000;
        filtercoeff_tilde_01_gain = 1;
        filtercoeff_tilde_01_q = 1;
        filtercoeff_tilde_01_type = 1;
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
        invsr = 0.000022675736961451248;
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
        filtercoeff_tilde_01_la0 = 0;
        filtercoeff_tilde_01_la1 = 0;
        filtercoeff_tilde_01_la2 = 0;
        filtercoeff_tilde_01_lb1 = 0;
        filtercoeff_tilde_01_lb2 = 0;
        filtercoeff_tilde_01_c_frequency = 0;
        filtercoeff_tilde_01_c_gain = 1;
        filtercoeff_tilde_01_c_q = 1;
        filtercoeff_tilde_01_c_type = 15;
        filtercoeff_tilde_01_resamp_counter = -1;
        filtercoeff_tilde_01_resamp_value = -1;
        filtercoeff_tilde_01_setupDone = false;
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
        number filtercoeff_tilde_01_frequency;
        number filtercoeff_tilde_01_gain;
        number filtercoeff_tilde_01_q;
        Int filtercoeff_tilde_01_type;
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
        number filtercoeff_tilde_01_la0;
        number filtercoeff_tilde_01_la1;
        number filtercoeff_tilde_01_la2;
        number filtercoeff_tilde_01_lb1;
        number filtercoeff_tilde_01_lb2;
        number filtercoeff_tilde_01_c_frequency;
        number filtercoeff_tilde_01_c_gain;
        number filtercoeff_tilde_01_c_q;
        Int filtercoeff_tilde_01_c_type;
        Int filtercoeff_tilde_01_resamp_counter;
        Int filtercoeff_tilde_01_resamp_value;
        bool filtercoeff_tilde_01_setupDone;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_75 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_75()
    {}
    
    ~RNBOSubpatcher_75()
    {}
    
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
        this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        this->linetilde_03_perform(this->signals[0], n);
    
        this->filtercoeff_tilde_02_perform(
            this->signals[0],
            this->filtercoeff_tilde_02_gain,
            this->filtercoeff_tilde_02_q,
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
    
        this->filtercoeff_tilde_02_dspsetup(forceDSPSetup);
        this->biquad_tilde_04_dspsetup(forceDSPSetup);
        this->biquad_tilde_03_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setPreset(MillisecondTime , PatcherStateInterface& ) {}
    
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
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time, (ENGINE*)nullptr);
    
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
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void updateTime(MillisecondTime time, INTERNALENGINE*) {
    	if (time == TimeNow) time = getTopLevelPatcher()->getPatcherTime();
    	getTopLevelPatcher()->processInternalEvents(time);
    	updateTime(time, (EXTERNALENGINE*)nullptr);
    }
    
    RNBOSubpatcher_75* operator->() {
        return this;
    }
    const RNBOSubpatcher_75* operator->() const {
        return this;
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
    
    MillisecondTime getPatcherTime() const {
        return this->_currentTime;
    }
    
    void numberobj_05_valin_set(number v) {
        this->numberobj_05_value_set(v);
    }
    
    void numberobj_05_format_set(number v) {
        this->numberobj_05_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_03_out1_bang_bang() {
        this->numberobj_05_value_bang();
    }
    
    template<typename LISTTYPE> void eventinlet_03_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_05_value_set(converted);
        }
    }
    
    void linetilde_03_target_bang() {}
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    void setProbingTarget(MessageTag ) {}
    
    void initializeObjects() {
        this->numberobj_05_init();
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time, (ENGINE*)nullptr);
    
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
        this->updateTime(time, (ENGINE*)nullptr);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void allocateDataRefs() {}
    
    void linetilde_03_time_set(number v) {
        this->linetilde_03_time = v;
    }
    
    template<typename LISTTYPE> void linetilde_03_segments_set(const LISTTYPE& v) {
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
            listbase<number, 1> converted = {v};
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
    
    void filtercoeff_tilde_02_perform(
        const Sample * frequency,
        number gain,
        number q,
        SampleValue * out1,
        SampleValue * out2,
        SampleValue * out3,
        SampleValue * out4,
        SampleValue * out5,
        Index n
    ) {
        RNBO_UNUSED(q);
        RNBO_UNUSED(gain);
        auto __filtercoeff_tilde_02_resamp_value = this->filtercoeff_tilde_02_resamp_value;
        auto __filtercoeff_tilde_02_resamp_counter = this->filtercoeff_tilde_02_resamp_counter;
        auto __filtercoeff_tilde_02_lb2 = this->filtercoeff_tilde_02_lb2;
        auto __filtercoeff_tilde_02_lb1 = this->filtercoeff_tilde_02_lb1;
        auto __filtercoeff_tilde_02_la2 = this->filtercoeff_tilde_02_la2;
        auto __filtercoeff_tilde_02_la1 = this->filtercoeff_tilde_02_la1;
        auto __filtercoeff_tilde_02_la0 = this->filtercoeff_tilde_02_la0;
        auto __filtercoeff_tilde_02_c_type = this->filtercoeff_tilde_02_c_type;
        auto __filtercoeff_tilde_02_type = this->filtercoeff_tilde_02_type;
        auto __filtercoeff_tilde_02_c_q = this->filtercoeff_tilde_02_c_q;
        auto __filtercoeff_tilde_02_c_gain = this->filtercoeff_tilde_02_c_gain;
        auto __filtercoeff_tilde_02_c_frequency = this->filtercoeff_tilde_02_c_frequency;
        number sr = this->sr;
        number halfsr = sr * 0.5;
        Index i;
    
        for (i = 0; i < n; i++) {
            number __frequency = frequency[(Index)i];
            number __q = 1;
    
            if (__frequency == __filtercoeff_tilde_02_c_frequency && 1 == __filtercoeff_tilde_02_c_gain && __q == __filtercoeff_tilde_02_c_q && __filtercoeff_tilde_02_type == __filtercoeff_tilde_02_c_type) {
                out1[(Index)i] = __filtercoeff_tilde_02_la0;
                out2[(Index)i] = __filtercoeff_tilde_02_la1;
                out3[(Index)i] = __filtercoeff_tilde_02_la2;
                out4[(Index)i] = __filtercoeff_tilde_02_lb1;
                out5[(Index)i] = __filtercoeff_tilde_02_lb2;
                continue;
            }
    
            if (__filtercoeff_tilde_02_resamp_counter > 0) {
                __filtercoeff_tilde_02_resamp_counter--;
                out1[(Index)i] = __filtercoeff_tilde_02_la0;
                out2[(Index)i] = __filtercoeff_tilde_02_la1;
                out3[(Index)i] = __filtercoeff_tilde_02_la2;
                out4[(Index)i] = __filtercoeff_tilde_02_lb1;
                out5[(Index)i] = __filtercoeff_tilde_02_lb2;
                continue;
            }
    
            __filtercoeff_tilde_02_resamp_counter = __filtercoeff_tilde_02_resamp_value;
            __filtercoeff_tilde_02_c_frequency = __frequency;
            __filtercoeff_tilde_02_c_gain = 1;
            __filtercoeff_tilde_02_c_q = __q;
            __filtercoeff_tilde_02_c_type = __filtercoeff_tilde_02_type;
    
            if (__q < 1e-9)
                __q = 1e-9;
    
            __frequency = (__frequency > halfsr ? halfsr : (__frequency < 1 ? 1 : __frequency));
            number omega = __frequency * ((number)6.283185307179586 / sr);
            number cs = rnbo_cos(omega);
            number sn = rnbo_sin(omega);
            number one_over_gain = (number)1 / (number)1;
            number one_over_q = (number)1 / __q;
            number alpha = sn * 0.5 * one_over_q;
            number beta;
            number A;
            number one_over_a;
            number b0;
            number b0g;
    
            switch (__filtercoeff_tilde_02_type) {
            case 5:
                {
                A = this->safesqrt(1);
                beta = this->safesqrt((A * A + 1.) * one_over_q - (A - 1.) * (A - 1.));
                b0 = (number)1 / (A + 1. + (A - 1.) * cs + beta * sn);
                break;
                }
            case 6:
                {
                A = this->safesqrt(1);
                beta = this->safesqrt((A * A + 1.) * one_over_q - (A - 1.) * (A - 1.));
                b0 = (number)1 / (A + 1. - (A - 1.) * cs + beta * sn);
                break;
                }
            case 4:
                {
                A = this->safesqrt(1);
                one_over_a = (A == 0 ? 0 : (number)1 / A);
                b0 = (number)1 / (1. + alpha * one_over_a);
                break;
                }
            case 9:
            case 10:
            case 11:
            case 13:
            case 14:
                {
                b0 = (number)1 / (1. + alpha);
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                break;
                }
            default:
                {
                b0 = (number)1 / (1. + alpha);
                break;
                }
            }
    
            switch (__filtercoeff_tilde_02_type) {
            case 0:
                {
                __filtercoeff_tilde_02_la0 = __filtercoeff_tilde_02_la2 = (1. - cs) * 0.5 * b0;
                __filtercoeff_tilde_02_la1 = (1. - cs) * b0;
                __filtercoeff_tilde_02_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_02_lb2 = (1. - alpha) * b0;
                break;
                }
            case 1:
                {
                __filtercoeff_tilde_02_la0 = __filtercoeff_tilde_02_la2 = (1. + cs) * 0.5 * b0;
                __filtercoeff_tilde_02_la1 = -(1. + cs) * b0;
                __filtercoeff_tilde_02_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_02_lb2 = (1. - alpha) * b0;
                break;
                }
            case 2:
                {
                __filtercoeff_tilde_02_la0 = alpha * b0;
                __filtercoeff_tilde_02_la1 = 0.;
                __filtercoeff_tilde_02_la2 = -alpha * b0;
                __filtercoeff_tilde_02_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_02_lb2 = (1. - alpha) * b0;
                break;
                }
            case 7:
                {
                __filtercoeff_tilde_02_la0 = alpha * __q * b0;
                __filtercoeff_tilde_02_la1 = 0.;
                __filtercoeff_tilde_02_la2 = -alpha * __q * b0;
                __filtercoeff_tilde_02_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_02_lb2 = (1. - alpha) * b0;
                break;
                }
            case 3:
                {
                __filtercoeff_tilde_02_la1 = __filtercoeff_tilde_02_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_02_lb2 = (1. - alpha) * b0;
                __filtercoeff_tilde_02_la0 = __filtercoeff_tilde_02_la2 = b0;
                break;
                }
            case 8:
                {
                __filtercoeff_tilde_02_la1 = __filtercoeff_tilde_02_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_02_lb2 = __filtercoeff_tilde_02_la0 = (1. - alpha) * b0;
                __filtercoeff_tilde_02_la2 = 1.0;
                break;
                }
            case 4:
                {
                __filtercoeff_tilde_02_la0 = (1. + alpha * A) * b0;
                __filtercoeff_tilde_02_la1 = __filtercoeff_tilde_02_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_02_la2 = (1. - alpha * A) * b0;
                __filtercoeff_tilde_02_lb2 = (1. - alpha * one_over_a) * b0;
                break;
                }
            case 5:
                {
                __filtercoeff_tilde_02_la0 = A * (A + 1. - (A - 1.) * cs + beta * sn) * b0;
                __filtercoeff_tilde_02_la1 = 2. * A * (A - 1 - (A + 1) * cs) * b0;
                __filtercoeff_tilde_02_la2 = A * (A + 1. - (A - 1.) * cs - beta * sn) * b0;
                __filtercoeff_tilde_02_lb1 = -2. * (A - 1. + (A + 1.) * cs) * b0;
                __filtercoeff_tilde_02_lb2 = (A + 1. + (A - 1.) * cs - beta * sn) * b0;
                break;
                }
            case 6:
                {
                __filtercoeff_tilde_02_la0 = A * (A + 1. + (A - 1.) * cs + beta * sn) * b0;
                __filtercoeff_tilde_02_la1 = -2. * A * (A - 1. + (A + 1.) * cs) * b0;
                __filtercoeff_tilde_02_la2 = A * (A + 1. + (A - 1.) * cs - beta * sn) * b0;
                __filtercoeff_tilde_02_lb1 = 2. * (A - 1. - (A + 1.) * cs) * b0;
                __filtercoeff_tilde_02_lb2 = (A + 1. - (A - 1.) * cs - beta * sn) * b0;
                break;
                }
            case 9:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_02_la0 = __filtercoeff_tilde_02_la2 = (1. - cs) * 0.5 * b0g;
                __filtercoeff_tilde_02_la1 = (1. - cs) * b0g;
                __filtercoeff_tilde_02_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_02_lb2 = (1. - alpha) * b0;
                break;
                }
            case 10:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_02_la0 = __filtercoeff_tilde_02_la2 = (1. + cs) * 0.5 * b0g;
                __filtercoeff_tilde_02_la1 = -(1. + cs) * b0g;
                __filtercoeff_tilde_02_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_02_lb2 = (1. - alpha) * b0;
                break;
                }
            case 11:
                {
                __filtercoeff_tilde_02_la0 = alpha * 1 * b0;
                __filtercoeff_tilde_02_la1 = 0.;
                __filtercoeff_tilde_02_la2 = -alpha * 1 * b0;
                __filtercoeff_tilde_02_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_02_lb2 = (1. - alpha) * b0;
                break;
                }
            case 13:
                {
                __filtercoeff_tilde_02_la0 = alpha * 1 * __q * b0;
                __filtercoeff_tilde_02_la1 = 0.;
                __filtercoeff_tilde_02_la2 = -alpha * 1 * __q * b0;
                __filtercoeff_tilde_02_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_02_lb2 = (1. - alpha) * b0;
                break;
                }
            case 12:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_02_la1 = __filtercoeff_tilde_02_lb1 = -2. * cs;
                __filtercoeff_tilde_02_lb2 = (1. - alpha) * b0;
                __filtercoeff_tilde_02_la1 *= b0g;
                __filtercoeff_tilde_02_lb1 *= b0;
                __filtercoeff_tilde_02_la0 = b0g;
                __filtercoeff_tilde_02_la2 = b0g;
                break;
                }
            case 14:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_02_la0 = (1. - alpha) * b0g;
                __filtercoeff_tilde_02_la1 = -2. * cs * b0g;
                __filtercoeff_tilde_02_la2 = 1;
                __filtercoeff_tilde_02_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_02_lb2 = (1. - alpha) * b0;
                break;
                }
            case 15:
                {
                __filtercoeff_tilde_02_la0 = 1;
                __filtercoeff_tilde_02_la1 = 0;
                __filtercoeff_tilde_02_la2 = 0;
                __filtercoeff_tilde_02_lb1 = 0;
                __filtercoeff_tilde_02_lb2 = 0;
                }
            default:
                {
                break;
                }
            }
    
            out1[(Index)i] = __filtercoeff_tilde_02_la0;
            out2[(Index)i] = __filtercoeff_tilde_02_la1;
            out3[(Index)i] = __filtercoeff_tilde_02_la2;
            out4[(Index)i] = __filtercoeff_tilde_02_lb1;
            out5[(Index)i] = __filtercoeff_tilde_02_lb2;
        }
    
        this->filtercoeff_tilde_02_c_frequency = __filtercoeff_tilde_02_c_frequency;
        this->filtercoeff_tilde_02_c_gain = __filtercoeff_tilde_02_c_gain;
        this->filtercoeff_tilde_02_c_q = __filtercoeff_tilde_02_c_q;
        this->filtercoeff_tilde_02_c_type = __filtercoeff_tilde_02_c_type;
        this->filtercoeff_tilde_02_la0 = __filtercoeff_tilde_02_la0;
        this->filtercoeff_tilde_02_la1 = __filtercoeff_tilde_02_la1;
        this->filtercoeff_tilde_02_la2 = __filtercoeff_tilde_02_la2;
        this->filtercoeff_tilde_02_lb1 = __filtercoeff_tilde_02_lb1;
        this->filtercoeff_tilde_02_lb2 = __filtercoeff_tilde_02_lb2;
        this->filtercoeff_tilde_02_resamp_counter = __filtercoeff_tilde_02_resamp_counter;
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
    }
    
    void numberobj_05_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_05_value;
    }
    
    void numberobj_05_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_05_value_set(preset["value"]);
    }
    
    void filtercoeff_tilde_02_dspsetup(bool force) {
        if ((bool)(this->filtercoeff_tilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->filtercoeff_tilde_02_resamp_value = this->vs;
        this->filtercoeff_tilde_02_setupDone = true;
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void updateTime(MillisecondTime time, EXTERNALENGINE ) {
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
        linetilde_03_keepramp = true;
        filtercoeff_tilde_02_frequency = 1000;
        filtercoeff_tilde_02_gain = 1;
        filtercoeff_tilde_02_q = 1;
        filtercoeff_tilde_02_type = 0;
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
        invsr = 0.000022675736961451248;
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
        filtercoeff_tilde_02_la0 = 0;
        filtercoeff_tilde_02_la1 = 0;
        filtercoeff_tilde_02_la2 = 0;
        filtercoeff_tilde_02_lb1 = 0;
        filtercoeff_tilde_02_lb2 = 0;
        filtercoeff_tilde_02_c_frequency = 0;
        filtercoeff_tilde_02_c_gain = 1;
        filtercoeff_tilde_02_c_q = 1;
        filtercoeff_tilde_02_c_type = 15;
        filtercoeff_tilde_02_resamp_counter = -1;
        filtercoeff_tilde_02_resamp_value = -1;
        filtercoeff_tilde_02_setupDone = false;
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
        number filtercoeff_tilde_02_frequency;
        number filtercoeff_tilde_02_gain;
        number filtercoeff_tilde_02_q;
        Int filtercoeff_tilde_02_type;
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
        number filtercoeff_tilde_02_la0;
        number filtercoeff_tilde_02_la1;
        number filtercoeff_tilde_02_la2;
        number filtercoeff_tilde_02_lb1;
        number filtercoeff_tilde_02_lb2;
        number filtercoeff_tilde_02_c_frequency;
        number filtercoeff_tilde_02_c_gain;
        number filtercoeff_tilde_02_c_q;
        Int filtercoeff_tilde_02_c_type;
        Int filtercoeff_tilde_02_resamp_counter;
        Int filtercoeff_tilde_02_resamp_value;
        bool filtercoeff_tilde_02_setupDone;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_76 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_76()
    {}
    
    ~RNBOSubpatcher_76()
    {}
    
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
        this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        this->linetilde_04_perform(this->signals[0], n);
        this->linetilde_05_perform(this->signals[1], n);
        this->linetilde_06_perform(this->signals[2], n);
    
        this->filtercoeff_tilde_03_perform(
            this->signals[0],
            this->signals[1],
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->signals[5],
            this->signals[6],
            this->signals[7],
            n
        );
    
        this->biquad_tilde_06_perform(
            in2,
            this->signals[3],
            this->signals[4],
            this->signals[5],
            this->signals[6],
            this->signals[7],
            out2,
            n
        );
    
        this->biquad_tilde_05_perform(
            in1,
            this->signals[3],
            this->signals[4],
            this->signals[5],
            this->signals[6],
            this->signals[7],
            out1,
            n
        );
    
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 8; i++) {
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
    
        this->filtercoeff_tilde_03_dspsetup(forceDSPSetup);
        this->biquad_tilde_06_dspsetup(forceDSPSetup);
        this->biquad_tilde_05_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setPreset(MillisecondTime , PatcherStateInterface& ) {}
    
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
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("HighMid~/number_obj-7") == objectId)
                this->numberobj_06_valin_set(payload);
    
            if (TAG("HighMid~/number_obj-3") == objectId)
                this->numberobj_07_valin_set(payload);
    
            if (TAG("HighMid~/number_obj-4") == objectId)
                this->numberobj_08_valin_set(payload);
    
            if (TAG("HighMid~/number_obj-18") == objectId)
                this->numberobj_09_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("HighMid~/number_obj-7") == objectId)
                this->numberobj_06_format_set(payload);
    
            if (TAG("HighMid~/number_obj-3") == objectId)
                this->numberobj_07_format_set(payload);
    
            if (TAG("HighMid~/number_obj-4") == objectId)
                this->numberobj_08_format_set(payload);
    
            if (TAG("HighMid~/number_obj-18") == objectId)
                this->numberobj_09_format_set(payload);
    
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
        case TAG("HighMid~/number_obj-7"):
            {
            return "HighMid~/number_obj-7";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("HighMid~/number_obj-3"):
            {
            return "HighMid~/number_obj-3";
            }
        case TAG("HighMid~/number_obj-4"):
            {
            return "HighMid~/number_obj-4";
            }
        case TAG("HighMid~/number_obj-18"):
            {
            return "HighMid~/number_obj-18";
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
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void updateTime(MillisecondTime time, INTERNALENGINE*) {
    	if (time == TimeNow) time = getTopLevelPatcher()->getPatcherTime();
    	getTopLevelPatcher()->processInternalEvents(time);
    	updateTime(time, (EXTERNALENGINE*)nullptr);
    }
    
    RNBOSubpatcher_76* operator->() {
        return this;
    }
    const RNBOSubpatcher_76* operator->() const {
        return this;
    }
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -1621164530, false);
        getEngine()->flushClockEvents(this, 1114681293, false);
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
    
    MillisecondTime getPatcherTime() const {
        return this->_currentTime;
    }
    
    void eventinlet_04_out1_bang_bang() {
        this->numberobj_06_value_bang();
    }
    
    template<typename LISTTYPE> void eventinlet_04_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_06_value_set(converted);
        }
    }
    
    void numberobj_06_valin_set(number v) {
        this->numberobj_06_value_set(v);
    }
    
    void numberobj_06_format_set(number v) {
        this->numberobj_06_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_05_out1_bang_bang() {
        this->numberobj_08_value_bang();
    }
    
    template<typename LISTTYPE> void eventinlet_05_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_08_value_set(converted);
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
    
    void eventinlet_06_out1_bang_bang() {
        this->linetilde_06_segments_bang();
    }
    
    template<typename LISTTYPE> void eventinlet_06_out1_list_set(const LISTTYPE& v) {
        this->linetilde_06_segments_set(v);
    }
    
    void numberobj_09_valin_set(number v) {
        this->numberobj_09_value_set(v);
    }
    
    void numberobj_09_format_set(number v) {
        this->numberobj_09_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void linetilde_04_target_bang() {}
    
    void linetilde_05_target_bang() {}
    
    void linetilde_06_target_bang() {}
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    void setProbingTarget(MessageTag ) {}
    
    void initializeObjects() {
        this->numberobj_06_init();
        this->numberobj_07_init();
        this->numberobj_08_init();
        this->numberobj_09_init();
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (index) {
        case -1621164530:
            {
            this->linetilde_04_target_bang();
            break;
            }
        case 1114681293:
            {
            this->linetilde_05_target_bang();
            break;
            }
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
        this->updateTime(time, (ENGINE*)nullptr);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void allocateDataRefs() {}
    
    void linetilde_04_time_set(number v) {
        this->linetilde_04_time = v;
    }
    
    template<typename LISTTYPE> void linetilde_04_segments_set(const LISTTYPE& v) {
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
    
    void numberobj_06_output_set(number v) {
        {
            listbase<number, 1> converted = {v};
            this->linetilde_04_segments_set(converted);
        }
    }
    
    void numberobj_06_value_set(number v) {
        this->numberobj_06_value_setter(v);
        v = this->numberobj_06_value;
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_06_output_set(localvalue);
    }
    
    void eventinlet_04_out1_number_set(number v) {
        this->numberobj_06_value_set(v);
    }
    
    void linetilde_05_time_set(number v) {
        this->linetilde_05_time = v;
    }
    
    template<typename LISTTYPE> void linetilde_05_segments_set(const LISTTYPE& v) {
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
    
    void numberobj_07_output_set(number v) {
        {
            listbase<number, 1> converted = {v};
            this->linetilde_05_segments_set(converted);
        }
    }
    
    void numberobj_07_value_set(number v) {
        this->numberobj_07_value_setter(v);
        v = this->numberobj_07_value;
        number localvalue = v;
    
        if (this->numberobj_07_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_07_output_set(localvalue);
    }
    
    void expr_02_out1_set(number v) {
        this->expr_02_out1 = v;
        this->numberobj_07_value_set(this->expr_02_out1);
    }
    
    void expr_02_in1_set(number in1) {
        this->expr_02_in1 = in1;
        this->expr_02_out1_set(rnbo_pow(10, this->expr_02_in1 * 0.05));//#map:HighMid~/dbtoa_obj-9:1
    }
    
    void numberobj_08_output_set(number v) {
        this->expr_02_in1_set(v);
    }
    
    void numberobj_08_value_set(number v) {
        this->numberobj_08_value_setter(v);
        v = this->numberobj_08_value;
        number localvalue = v;
    
        if (this->numberobj_08_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_08_output_set(localvalue);
    }
    
    void eventinlet_05_out1_number_set(number v) {
        this->numberobj_08_value_set(v);
    }
    
    void linetilde_06_time_set(number v) {
        this->linetilde_06_time = v;
    }
    
    template<typename LISTTYPE> void linetilde_06_segments_set(const LISTTYPE& v) {
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
    
    void eventinlet_06_out1_number_set(number v) {
        {
            listbase<number, 1> converted = {v};
            this->linetilde_06_segments_set(converted);
        }
    }
    
    void numberobj_06_value_bang() {
        number v = this->numberobj_06_value;
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_06_output_set(localvalue);
    }
    
    void numberobj_08_value_bang() {
        number v = this->numberobj_08_value;
        number localvalue = v;
    
        if (this->numberobj_08_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_08_output_set(localvalue);
    }
    
    void linetilde_06_segments_bang() {
        list v = this->linetilde_06_segments;
    
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
    
    template<typename LISTTYPE> void scale_02_out_set(const LISTTYPE& v) {
        this->scale_02_out = jsCreateListCopy(v);
    }
    
    template<typename LISTTYPE> void scale_02_input_set(const LISTTYPE& v) {
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
    
    void numberobj_09_output_set(number v) {
        {
            listbase<number, 1> converted = {v};
            this->scale_02_input_set(converted);
        }
    }
    
    void numberobj_09_value_set(number v) {
        this->numberobj_09_value_setter(v);
        v = this->numberobj_09_value;
        number localvalue = v;
    
        if (this->numberobj_09_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_09_output_set(localvalue);
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
                            -1621164530,
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
                            1114681293,
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
    
    void filtercoeff_tilde_03_perform(
        const Sample * frequency,
        const Sample * gain,
        const Sample * q,
        SampleValue * out1,
        SampleValue * out2,
        SampleValue * out3,
        SampleValue * out4,
        SampleValue * out5,
        Index n
    ) {
        auto __filtercoeff_tilde_03_resamp_value = this->filtercoeff_tilde_03_resamp_value;
        auto __filtercoeff_tilde_03_resamp_counter = this->filtercoeff_tilde_03_resamp_counter;
        auto __filtercoeff_tilde_03_lb2 = this->filtercoeff_tilde_03_lb2;
        auto __filtercoeff_tilde_03_lb1 = this->filtercoeff_tilde_03_lb1;
        auto __filtercoeff_tilde_03_la2 = this->filtercoeff_tilde_03_la2;
        auto __filtercoeff_tilde_03_la1 = this->filtercoeff_tilde_03_la1;
        auto __filtercoeff_tilde_03_la0 = this->filtercoeff_tilde_03_la0;
        auto __filtercoeff_tilde_03_c_type = this->filtercoeff_tilde_03_c_type;
        auto __filtercoeff_tilde_03_type = this->filtercoeff_tilde_03_type;
        auto __filtercoeff_tilde_03_c_q = this->filtercoeff_tilde_03_c_q;
        auto __filtercoeff_tilde_03_c_gain = this->filtercoeff_tilde_03_c_gain;
        auto __filtercoeff_tilde_03_c_frequency = this->filtercoeff_tilde_03_c_frequency;
        number sr = this->sr;
        number halfsr = sr * 0.5;
        Index i;
    
        for (i = 0; i < n; i++) {
            number __frequency = frequency[(Index)i];
            number __q = q[(Index)i];
    
            if (__frequency == __filtercoeff_tilde_03_c_frequency && gain[(Index)i] == __filtercoeff_tilde_03_c_gain && __q == __filtercoeff_tilde_03_c_q && __filtercoeff_tilde_03_type == __filtercoeff_tilde_03_c_type) {
                out1[(Index)i] = __filtercoeff_tilde_03_la0;
                out2[(Index)i] = __filtercoeff_tilde_03_la1;
                out3[(Index)i] = __filtercoeff_tilde_03_la2;
                out4[(Index)i] = __filtercoeff_tilde_03_lb1;
                out5[(Index)i] = __filtercoeff_tilde_03_lb2;
                continue;
            }
    
            if (__filtercoeff_tilde_03_resamp_counter > 0) {
                __filtercoeff_tilde_03_resamp_counter--;
                out1[(Index)i] = __filtercoeff_tilde_03_la0;
                out2[(Index)i] = __filtercoeff_tilde_03_la1;
                out3[(Index)i] = __filtercoeff_tilde_03_la2;
                out4[(Index)i] = __filtercoeff_tilde_03_lb1;
                out5[(Index)i] = __filtercoeff_tilde_03_lb2;
                continue;
            }
    
            __filtercoeff_tilde_03_resamp_counter = __filtercoeff_tilde_03_resamp_value;
            __filtercoeff_tilde_03_c_frequency = __frequency;
            __filtercoeff_tilde_03_c_gain = gain[(Index)i];
            __filtercoeff_tilde_03_c_q = __q;
            __filtercoeff_tilde_03_c_type = __filtercoeff_tilde_03_type;
    
            if (__q < 1e-9)
                __q = 1e-9;
    
            __frequency = (__frequency > halfsr ? halfsr : (__frequency < 1 ? 1 : __frequency));
            number omega = __frequency * ((number)6.283185307179586 / sr);
            number cs = rnbo_cos(omega);
            number sn = rnbo_sin(omega);
            number one_over_gain = (gain[(Index)i] > 0 ? (number)1 / gain[(Index)i] : 0.0);
            number one_over_q = (number)1 / __q;
            number alpha = sn * 0.5 * one_over_q;
            number beta;
            number A;
            number one_over_a;
            number b0;
            number b0g;
    
            switch (__filtercoeff_tilde_03_type) {
            case 5:
                {
                A = this->safesqrt(gain[(Index)i]);
                beta = this->safesqrt((A * A + 1.) * one_over_q - (A - 1.) * (A - 1.));
                b0 = (number)1 / (A + 1. + (A - 1.) * cs + beta * sn);
                break;
                }
            case 6:
                {
                A = this->safesqrt(gain[(Index)i]);
                beta = this->safesqrt((A * A + 1.) * one_over_q - (A - 1.) * (A - 1.));
                b0 = (number)1 / (A + 1. - (A - 1.) * cs + beta * sn);
                break;
                }
            case 4:
                {
                A = this->safesqrt(gain[(Index)i]);
                one_over_a = (A == 0 ? 0 : (number)1 / A);
                b0 = (number)1 / (1. + alpha * one_over_a);
                break;
                }
            case 9:
            case 10:
            case 11:
            case 13:
            case 14:
                {
                b0 = (number)1 / (1. + alpha);
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                break;
                }
            default:
                {
                b0 = (number)1 / (1. + alpha);
                break;
                }
            }
    
            switch (__filtercoeff_tilde_03_type) {
            case 0:
                {
                __filtercoeff_tilde_03_la0 = __filtercoeff_tilde_03_la2 = (1. - cs) * 0.5 * b0;
                __filtercoeff_tilde_03_la1 = (1. - cs) * b0;
                __filtercoeff_tilde_03_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_03_lb2 = (1. - alpha) * b0;
                break;
                }
            case 1:
                {
                __filtercoeff_tilde_03_la0 = __filtercoeff_tilde_03_la2 = (1. + cs) * 0.5 * b0;
                __filtercoeff_tilde_03_la1 = -(1. + cs) * b0;
                __filtercoeff_tilde_03_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_03_lb2 = (1. - alpha) * b0;
                break;
                }
            case 2:
                {
                __filtercoeff_tilde_03_la0 = alpha * b0;
                __filtercoeff_tilde_03_la1 = 0.;
                __filtercoeff_tilde_03_la2 = -alpha * b0;
                __filtercoeff_tilde_03_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_03_lb2 = (1. - alpha) * b0;
                break;
                }
            case 7:
                {
                __filtercoeff_tilde_03_la0 = alpha * __q * b0;
                __filtercoeff_tilde_03_la1 = 0.;
                __filtercoeff_tilde_03_la2 = -alpha * __q * b0;
                __filtercoeff_tilde_03_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_03_lb2 = (1. - alpha) * b0;
                break;
                }
            case 3:
                {
                __filtercoeff_tilde_03_la1 = __filtercoeff_tilde_03_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_03_lb2 = (1. - alpha) * b0;
                __filtercoeff_tilde_03_la0 = __filtercoeff_tilde_03_la2 = b0;
                break;
                }
            case 8:
                {
                __filtercoeff_tilde_03_la1 = __filtercoeff_tilde_03_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_03_lb2 = __filtercoeff_tilde_03_la0 = (1. - alpha) * b0;
                __filtercoeff_tilde_03_la2 = 1.0;
                break;
                }
            case 4:
                {
                __filtercoeff_tilde_03_la0 = (1. + alpha * A) * b0;
                __filtercoeff_tilde_03_la1 = __filtercoeff_tilde_03_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_03_la2 = (1. - alpha * A) * b0;
                __filtercoeff_tilde_03_lb2 = (1. - alpha * one_over_a) * b0;
                break;
                }
            case 5:
                {
                __filtercoeff_tilde_03_la0 = A * (A + 1. - (A - 1.) * cs + beta * sn) * b0;
                __filtercoeff_tilde_03_la1 = 2. * A * (A - 1 - (A + 1) * cs) * b0;
                __filtercoeff_tilde_03_la2 = A * (A + 1. - (A - 1.) * cs - beta * sn) * b0;
                __filtercoeff_tilde_03_lb1 = -2. * (A - 1. + (A + 1.) * cs) * b0;
                __filtercoeff_tilde_03_lb2 = (A + 1. + (A - 1.) * cs - beta * sn) * b0;
                break;
                }
            case 6:
                {
                __filtercoeff_tilde_03_la0 = A * (A + 1. + (A - 1.) * cs + beta * sn) * b0;
                __filtercoeff_tilde_03_la1 = -2. * A * (A - 1. + (A + 1.) * cs) * b0;
                __filtercoeff_tilde_03_la2 = A * (A + 1. + (A - 1.) * cs - beta * sn) * b0;
                __filtercoeff_tilde_03_lb1 = 2. * (A - 1. - (A + 1.) * cs) * b0;
                __filtercoeff_tilde_03_lb2 = (A + 1. - (A - 1.) * cs - beta * sn) * b0;
                break;
                }
            case 9:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_03_la0 = __filtercoeff_tilde_03_la2 = (1. - cs) * 0.5 * b0g;
                __filtercoeff_tilde_03_la1 = (1. - cs) * b0g;
                __filtercoeff_tilde_03_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_03_lb2 = (1. - alpha) * b0;
                break;
                }
            case 10:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_03_la0 = __filtercoeff_tilde_03_la2 = (1. + cs) * 0.5 * b0g;
                __filtercoeff_tilde_03_la1 = -(1. + cs) * b0g;
                __filtercoeff_tilde_03_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_03_lb2 = (1. - alpha) * b0;
                break;
                }
            case 11:
                {
                __filtercoeff_tilde_03_la0 = alpha * gain[(Index)i] * b0;
                __filtercoeff_tilde_03_la1 = 0.;
                __filtercoeff_tilde_03_la2 = -alpha * gain[(Index)i] * b0;
                __filtercoeff_tilde_03_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_03_lb2 = (1. - alpha) * b0;
                break;
                }
            case 13:
                {
                __filtercoeff_tilde_03_la0 = alpha * gain[(Index)i] * __q * b0;
                __filtercoeff_tilde_03_la1 = 0.;
                __filtercoeff_tilde_03_la2 = -alpha * gain[(Index)i] * __q * b0;
                __filtercoeff_tilde_03_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_03_lb2 = (1. - alpha) * b0;
                break;
                }
            case 12:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_03_la1 = __filtercoeff_tilde_03_lb1 = -2. * cs;
                __filtercoeff_tilde_03_lb2 = (1. - alpha) * b0;
                __filtercoeff_tilde_03_la1 *= b0g;
                __filtercoeff_tilde_03_lb1 *= b0;
                __filtercoeff_tilde_03_la0 = b0g;
                __filtercoeff_tilde_03_la2 = b0g;
                break;
                }
            case 14:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_03_la0 = (1. - alpha) * b0g;
                __filtercoeff_tilde_03_la1 = -2. * cs * b0g;
                __filtercoeff_tilde_03_la2 = gain[(Index)i];
                __filtercoeff_tilde_03_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_03_lb2 = (1. - alpha) * b0;
                break;
                }
            case 15:
                {
                __filtercoeff_tilde_03_la0 = 1;
                __filtercoeff_tilde_03_la1 = 0;
                __filtercoeff_tilde_03_la2 = 0;
                __filtercoeff_tilde_03_lb1 = 0;
                __filtercoeff_tilde_03_lb2 = 0;
                }
            default:
                {
                break;
                }
            }
    
            out1[(Index)i] = __filtercoeff_tilde_03_la0;
            out2[(Index)i] = __filtercoeff_tilde_03_la1;
            out3[(Index)i] = __filtercoeff_tilde_03_la2;
            out4[(Index)i] = __filtercoeff_tilde_03_lb1;
            out5[(Index)i] = __filtercoeff_tilde_03_lb2;
        }
    
        this->filtercoeff_tilde_03_c_frequency = __filtercoeff_tilde_03_c_frequency;
        this->filtercoeff_tilde_03_c_gain = __filtercoeff_tilde_03_c_gain;
        this->filtercoeff_tilde_03_c_q = __filtercoeff_tilde_03_c_q;
        this->filtercoeff_tilde_03_c_type = __filtercoeff_tilde_03_c_type;
        this->filtercoeff_tilde_03_la0 = __filtercoeff_tilde_03_la0;
        this->filtercoeff_tilde_03_la1 = __filtercoeff_tilde_03_la1;
        this->filtercoeff_tilde_03_la2 = __filtercoeff_tilde_03_la2;
        this->filtercoeff_tilde_03_lb1 = __filtercoeff_tilde_03_lb1;
        this->filtercoeff_tilde_03_lb2 = __filtercoeff_tilde_03_lb2;
        this->filtercoeff_tilde_03_resamp_counter = __filtercoeff_tilde_03_resamp_counter;
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
    }
    
    void numberobj_06_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_06_value;
    }
    
    void numberobj_06_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_06_value_set(preset["value"]);
    }
    
    void filtercoeff_tilde_03_dspsetup(bool force) {
        if ((bool)(this->filtercoeff_tilde_03_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->filtercoeff_tilde_03_resamp_value = this->vs;
        this->filtercoeff_tilde_03_setupDone = true;
    }
    
    void numberobj_07_init() {
        this->numberobj_07_currentFormat = 6;
    }
    
    void numberobj_07_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_07_value;
    }
    
    void numberobj_07_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_07_value_set(preset["value"]);
    }
    
    void numberobj_08_init() {
        this->numberobj_08_currentFormat = 6;
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
    }
    
    void numberobj_09_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_09_value;
    }
    
    void numberobj_09_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_09_value_set(preset["value"]);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void updateTime(MillisecondTime time, EXTERNALENGINE ) {
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
        numberobj_06_value = 0;
        numberobj_06_value_setter(numberobj_06_value);
        linetilde_04_time = 10;
        linetilde_04_keepramp = true;
        filtercoeff_tilde_03_frequency = 1000;
        filtercoeff_tilde_03_gain = 1;
        filtercoeff_tilde_03_q = 0.25;
        filtercoeff_tilde_03_type = 4;
        numberobj_07_value = 0;
        numberobj_07_value_setter(numberobj_07_value);
        numberobj_08_value = 0;
        numberobj_08_value_setter(numberobj_08_value);
        expr_02_in1 = 0;
        expr_02_out1 = 0;
        linetilde_05_time = 10;
        linetilde_05_keepramp = true;
        linetilde_06_time = 10;
        linetilde_06_keepramp = true;
        scale_02_inlow = -100;
        scale_02_inhigh = 100;
        scale_02_outlow = -18;
        scale_02_outhigh = 18;
        scale_02_power = 1;
        numberobj_09_value = 0;
        numberobj_09_value_setter(numberobj_09_value);
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
        signals[7] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.000022675736961451248;
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
        linetilde_04_currentValue = 1700;
        filtercoeff_tilde_03_la0 = 0;
        filtercoeff_tilde_03_la1 = 0;
        filtercoeff_tilde_03_la2 = 0;
        filtercoeff_tilde_03_lb1 = 0;
        filtercoeff_tilde_03_lb2 = 0;
        filtercoeff_tilde_03_c_frequency = 0;
        filtercoeff_tilde_03_c_gain = 1;
        filtercoeff_tilde_03_c_q = 1;
        filtercoeff_tilde_03_c_type = 15;
        filtercoeff_tilde_03_resamp_counter = -1;
        filtercoeff_tilde_03_resamp_value = -1;
        filtercoeff_tilde_03_setupDone = false;
        numberobj_07_currentFormat = 6;
        numberobj_07_lastValue = 0;
        numberobj_08_currentFormat = 6;
        numberobj_08_lastValue = 0;
        linetilde_05_currentValue = 1;
        linetilde_06_currentValue = 0.5;
        numberobj_09_currentFormat = 6;
        numberobj_09_lastValue = 0;
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
        number numberobj_06_value;
        list linetilde_04_segments;
        number linetilde_04_time;
        number linetilde_04_keepramp;
        number filtercoeff_tilde_03_frequency;
        number filtercoeff_tilde_03_gain;
        number filtercoeff_tilde_03_q;
        Int filtercoeff_tilde_03_type;
        number numberobj_07_value;
        number numberobj_08_value;
        number expr_02_in1;
        number expr_02_out1;
        list linetilde_05_segments;
        number linetilde_05_time;
        number linetilde_05_keepramp;
        list linetilde_06_segments;
        number linetilde_06_time;
        number linetilde_06_keepramp;
        list scale_02_input;
        number scale_02_inlow;
        number scale_02_inhigh;
        number scale_02_outlow;
        number scale_02_outhigh;
        number scale_02_power;
        list scale_02_out;
        number numberobj_09_value;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[8];
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
        list linetilde_04_activeRamps;
        number linetilde_04_currentValue;
        number filtercoeff_tilde_03_la0;
        number filtercoeff_tilde_03_la1;
        number filtercoeff_tilde_03_la2;
        number filtercoeff_tilde_03_lb1;
        number filtercoeff_tilde_03_lb2;
        number filtercoeff_tilde_03_c_frequency;
        number filtercoeff_tilde_03_c_gain;
        number filtercoeff_tilde_03_c_q;
        Int filtercoeff_tilde_03_c_type;
        Int filtercoeff_tilde_03_resamp_counter;
        Int filtercoeff_tilde_03_resamp_value;
        bool filtercoeff_tilde_03_setupDone;
        Int numberobj_07_currentFormat;
        number numberobj_07_lastValue;
        Int numberobj_08_currentFormat;
        number numberobj_08_lastValue;
        list linetilde_05_activeRamps;
        number linetilde_05_currentValue;
        list linetilde_06_activeRamps;
        number linetilde_06_currentValue;
        Int numberobj_09_currentFormat;
        number numberobj_09_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_77 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_77()
    {}
    
    ~RNBOSubpatcher_77()
    {}
    
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
        this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        this->linetilde_07_perform(this->signals[0], n);
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
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setPreset(MillisecondTime , PatcherStateInterface& ) {}
    
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
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("preq_Level~/number_obj-7") == objectId)
                this->numberobj_10_valin_set(payload);
    
            if (TAG("preq_Level~/number_obj-14") == objectId)
                this->numberobj_11_valin_set(payload);
    
            if (TAG("preq_Level~/number_obj-5") == objectId)
                this->numberobj_12_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("preq_Level~/number_obj-7") == objectId)
                this->numberobj_10_format_set(payload);
    
            if (TAG("preq_Level~/number_obj-14") == objectId)
                this->numberobj_11_format_set(payload);
    
            if (TAG("preq_Level~/number_obj-5") == objectId)
                this->numberobj_12_format_set(payload);
    
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
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void updateTime(MillisecondTime time, INTERNALENGINE*) {
    	if (time == TimeNow) time = getTopLevelPatcher()->getPatcherTime();
    	getTopLevelPatcher()->processInternalEvents(time);
    	updateTime(time, (EXTERNALENGINE*)nullptr);
    }
    
    RNBOSubpatcher_77* operator->() {
        return this;
    }
    const RNBOSubpatcher_77* operator->() const {
        return this;
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
    
    MillisecondTime getPatcherTime() const {
        return this->_currentTime;
    }
    
    void numberobj_10_valin_set(number v) {
        this->numberobj_10_value_set(v);
    }
    
    void numberobj_10_format_set(number v) {
        this->numberobj_10_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
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
    
    void eventinlet_07_out1_bang_bang() {
        this->numberobj_11_value_bang();
    }
    
    template<typename LISTTYPE> void eventinlet_07_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_11_value_set(converted);
        }
    }
    
    void linetilde_07_target_bang() {}
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    void setProbingTarget(MessageTag ) {}
    
    void initializeObjects() {
        this->numberobj_10_init();
        this->numberobj_11_init();
        this->numberobj_12_init();
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time, (ENGINE*)nullptr);
    
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
        this->updateTime(time, (ENGINE*)nullptr);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void allocateDataRefs() {}
    
    void linetilde_07_time_set(number v) {
        this->linetilde_07_time = v;
    }
    
    template<typename LISTTYPE> void linetilde_07_segments_set(const LISTTYPE& v) {
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
    
    void numberobj_10_output_set(number v) {
        {
            listbase<number, 1> converted = {v};
            this->linetilde_07_segments_set(converted);
        }
    }
    
    void numberobj_10_value_set(number v) {
        this->numberobj_10_value_setter(v);
        v = this->numberobj_10_value;
        number localvalue = v;
    
        if (this->numberobj_10_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_10_output_set(localvalue);
    }
    
    void expr_03_out1_set(number v) {
        this->expr_03_out1 = v;
        this->numberobj_10_value_set(this->expr_03_out1);
    }
    
    void expr_03_in1_set(number in1) {
        this->expr_03_in1 = in1;
        this->expr_03_out1_set(rnbo_pow(10, this->expr_03_in1 * 0.05));//#map:preq_Level~/dbtoa_obj-3:1
    }
    
    void numberobj_12_output_set(number v) {
        this->expr_03_in1_set(v);
    }
    
    void numberobj_12_value_set(number v) {
        this->numberobj_12_value_setter(v);
        v = this->numberobj_12_value;
        number localvalue = v;
    
        if (this->numberobj_12_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_12_output_set(localvalue);
    }
    
    template<typename LISTTYPE> void scale_03_out_set(const LISTTYPE& v) {
        this->scale_03_out = jsCreateListCopy(v);
    
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_12_value_set(converted);
        }
    }
    
    template<typename LISTTYPE> void scale_03_input_set(const LISTTYPE& v) {
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
    
    void numberobj_11_output_set(number v) {
        {
            listbase<number, 1> converted = {v};
            this->scale_03_input_set(converted);
        }
    }
    
    void numberobj_11_value_set(number v) {
        this->numberobj_11_value_setter(v);
        v = this->numberobj_11_value;
        number localvalue = v;
    
        if (this->numberobj_11_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_11_output_set(localvalue);
    }
    
    void eventinlet_07_out1_number_set(number v) {
        this->numberobj_11_value_set(v);
    }
    
    void numberobj_11_value_bang() {
        number v = this->numberobj_11_value;
        number localvalue = v;
    
        if (this->numberobj_11_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_11_output_set(localvalue);
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
    
    void numberobj_10_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_10_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_10_value = localvalue;
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
    
    void numberobj_10_init() {
        this->numberobj_10_currentFormat = 6;
    }
    
    void numberobj_10_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_10_value;
    }
    
    void numberobj_10_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_10_value_set(preset["value"]);
    }
    
    void numberobj_11_init() {
        this->numberobj_11_currentFormat = 6;
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
    }
    
    void numberobj_12_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_12_value;
    }
    
    void numberobj_12_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_12_value_set(preset["value"]);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void updateTime(MillisecondTime time, EXTERNALENGINE ) {
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
        numberobj_10_value = 0;
        numberobj_10_value_setter(numberobj_10_value);
        numberobj_11_value = 0;
        numberobj_11_value_setter(numberobj_11_value);
        scale_03_inlow = -100;
        scale_03_inhigh = 100;
        scale_03_outlow = -18;
        scale_03_outhigh = 18;
        scale_03_power = 1;
        numberobj_12_value = 0;
        numberobj_12_value_setter(numberobj_12_value);
        expr_03_in1 = 0;
        expr_03_out1 = 0;
        linetilde_07_time = 10;
        linetilde_07_keepramp = true;
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
        invsr = 0.000022675736961451248;
        numberobj_10_currentFormat = 6;
        numberobj_10_lastValue = 0;
        numberobj_11_currentFormat = 6;
        numberobj_11_lastValue = 0;
        numberobj_12_currentFormat = 6;
        numberobj_12_lastValue = 0;
        linetilde_07_currentValue = 1;
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
        number numberobj_10_value;
        number numberobj_11_value;
        list scale_03_input;
        number scale_03_inlow;
        number scale_03_inhigh;
        number scale_03_outlow;
        number scale_03_outhigh;
        number scale_03_power;
        list scale_03_out;
        number numberobj_12_value;
        number expr_03_in1;
        number expr_03_out1;
        list linetilde_07_segments;
        number linetilde_07_time;
        number linetilde_07_keepramp;
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
        Int numberobj_10_currentFormat;
        number numberobj_10_lastValue;
        Int numberobj_11_currentFormat;
        number numberobj_11_lastValue;
        Int numberobj_12_currentFormat;
        number numberobj_12_lastValue;
        list linetilde_07_activeRamps;
        number linetilde_07_currentValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_78 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_78()
    {}
    
    ~RNBOSubpatcher_78()
    {}
    
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
        this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        this->linetilde_08_perform(this->signals[0], n);
    
        this->filtercoeff_tilde_04_perform(
            this->signals[0],
            this->filtercoeff_tilde_04_gain,
            this->filtercoeff_tilde_04_q,
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
    
        this->filtercoeff_tilde_04_dspsetup(forceDSPSetup);
        this->biquad_tilde_08_dspsetup(forceDSPSetup);
        this->biquad_tilde_07_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getNumInputChannels() const {
        return 2;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setPreset(MillisecondTime , PatcherStateInterface& ) {}
    
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
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("preq_LowCut~/toggle_obj-42") == objectId)
                this->toggle_01_valin_set(payload);
    
            if (TAG("preq_LowCut~/number_obj-37") == objectId)
                this->numberobj_13_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("preq_LowCut~/number_obj-37") == objectId)
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
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void updateTime(MillisecondTime time, INTERNALENGINE*) {
    	if (time == TimeNow) time = getTopLevelPatcher()->getPatcherTime();
    	getTopLevelPatcher()->processInternalEvents(time);
    	updateTime(time, (EXTERNALENGINE*)nullptr);
    }
    
    RNBOSubpatcher_78* operator->() {
        return this;
    }
    const RNBOSubpatcher_78* operator->() const {
        return this;
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
    
    MillisecondTime getPatcherTime() const {
        return this->_currentTime;
    }
    
    void toggle_01_valin_set(number v) {
        this->toggle_01_value_number_set(v);
    }
    
    void numberobj_13_valin_set(number v) {
        this->numberobj_13_value_set(v);
    }
    
    void numberobj_13_format_set(number v) {
        this->numberobj_13_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_08_out1_bang_bang() {
        this->toggle_01_value_bang_bang();
    }
    
    template<typename LISTTYPE> void eventinlet_08_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->toggle_01_value_number_set(converted);
        }
    }
    
    void linetilde_08_target_bang() {}
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    void setProbingTarget(MessageTag ) {}
    
    void initializeObjects() {
        this->numberobj_13_init();
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {}
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time, (ENGINE*)nullptr);
    
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
        this->updateTime(time, (ENGINE*)nullptr);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void allocateDataRefs() {}
    
    void linetilde_08_time_set(number v) {
        this->linetilde_08_time = v;
    }
    
    template<typename LISTTYPE> void linetilde_08_segments_set(const LISTTYPE& v) {
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
    
    void numberobj_13_output_set(number v) {
        {
            listbase<number, 1> converted = {v};
            this->linetilde_08_segments_set(converted);
        }
    }
    
    void numberobj_13_value_set(number v) {
        this->numberobj_13_value_setter(v);
        v = this->numberobj_13_value;
        number localvalue = v;
    
        if (this->numberobj_13_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_13_output_set(localvalue);
    }
    
    template<typename LISTTYPE> void listlookup_01_out_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_13_value_set(converted);
        }
    }
    
    template<typename LISTTYPE> void listlookup_01_input_set(const LISTTYPE& v) {
        this->listlookup_01_input = jsCreateListCopy(v);
        list tmp = list();
    
        for (Index i = 0; i < v->length; i++) {
            Int j = (Int)(rnbo_fround(v[(Index)i] * 1 / (number)1) * 1);
    
            if (j >= 0 && (Index)(j) < this->listlookup_01_lookup->length)
                tmp->push(this->listlookup_01_lookup[(Index)j]);
        }
    
        if ((bool)(tmp->length))
            this->listlookup_01_out_set(tmp);
    }
    
    void toggle_01_output_set(number v) {
        {
            listbase<number, 1> converted = {v};
            this->listlookup_01_input_set(converted);
        }
    }
    
    void toggle_01_value_number_set(number v) {
        this->toggle_01_value_number_setter(v);
        v = this->toggle_01_value_number;
        this->toggle_01_output_set(v);
    }
    
    void eventinlet_08_out1_number_set(number v) {
        this->toggle_01_value_number_set(v);
    }
    
    void toggle_01_value_bang_bang() {
        number val = (this->toggle_01_value_number == 1 ? 0 : 1);
        this->toggle_01_value_number_set(val);
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
    
    void filtercoeff_tilde_04_perform(
        const Sample * frequency,
        number gain,
        number q,
        SampleValue * out1,
        SampleValue * out2,
        SampleValue * out3,
        SampleValue * out4,
        SampleValue * out5,
        Index n
    ) {
        RNBO_UNUSED(q);
        RNBO_UNUSED(gain);
        auto __filtercoeff_tilde_04_resamp_value = this->filtercoeff_tilde_04_resamp_value;
        auto __filtercoeff_tilde_04_resamp_counter = this->filtercoeff_tilde_04_resamp_counter;
        auto __filtercoeff_tilde_04_lb2 = this->filtercoeff_tilde_04_lb2;
        auto __filtercoeff_tilde_04_lb1 = this->filtercoeff_tilde_04_lb1;
        auto __filtercoeff_tilde_04_la2 = this->filtercoeff_tilde_04_la2;
        auto __filtercoeff_tilde_04_la1 = this->filtercoeff_tilde_04_la1;
        auto __filtercoeff_tilde_04_la0 = this->filtercoeff_tilde_04_la0;
        auto __filtercoeff_tilde_04_c_type = this->filtercoeff_tilde_04_c_type;
        auto __filtercoeff_tilde_04_type = this->filtercoeff_tilde_04_type;
        auto __filtercoeff_tilde_04_c_q = this->filtercoeff_tilde_04_c_q;
        auto __filtercoeff_tilde_04_c_gain = this->filtercoeff_tilde_04_c_gain;
        auto __filtercoeff_tilde_04_c_frequency = this->filtercoeff_tilde_04_c_frequency;
        number sr = this->sr;
        number halfsr = sr * 0.5;
        Index i;
    
        for (i = 0; i < n; i++) {
            number __frequency = frequency[(Index)i];
            number __q = 1;
    
            if (__frequency == __filtercoeff_tilde_04_c_frequency && 1 == __filtercoeff_tilde_04_c_gain && __q == __filtercoeff_tilde_04_c_q && __filtercoeff_tilde_04_type == __filtercoeff_tilde_04_c_type) {
                out1[(Index)i] = __filtercoeff_tilde_04_la0;
                out2[(Index)i] = __filtercoeff_tilde_04_la1;
                out3[(Index)i] = __filtercoeff_tilde_04_la2;
                out4[(Index)i] = __filtercoeff_tilde_04_lb1;
                out5[(Index)i] = __filtercoeff_tilde_04_lb2;
                continue;
            }
    
            if (__filtercoeff_tilde_04_resamp_counter > 0) {
                __filtercoeff_tilde_04_resamp_counter--;
                out1[(Index)i] = __filtercoeff_tilde_04_la0;
                out2[(Index)i] = __filtercoeff_tilde_04_la1;
                out3[(Index)i] = __filtercoeff_tilde_04_la2;
                out4[(Index)i] = __filtercoeff_tilde_04_lb1;
                out5[(Index)i] = __filtercoeff_tilde_04_lb2;
                continue;
            }
    
            __filtercoeff_tilde_04_resamp_counter = __filtercoeff_tilde_04_resamp_value;
            __filtercoeff_tilde_04_c_frequency = __frequency;
            __filtercoeff_tilde_04_c_gain = 1;
            __filtercoeff_tilde_04_c_q = __q;
            __filtercoeff_tilde_04_c_type = __filtercoeff_tilde_04_type;
    
            if (__q < 1e-9)
                __q = 1e-9;
    
            __frequency = (__frequency > halfsr ? halfsr : (__frequency < 1 ? 1 : __frequency));
            number omega = __frequency * ((number)6.283185307179586 / sr);
            number cs = rnbo_cos(omega);
            number sn = rnbo_sin(omega);
            number one_over_gain = (number)1 / (number)1;
            number one_over_q = (number)1 / __q;
            number alpha = sn * 0.5 * one_over_q;
            number beta;
            number A;
            number one_over_a;
            number b0;
            number b0g;
    
            switch (__filtercoeff_tilde_04_type) {
            case 5:
                {
                A = this->safesqrt(1);
                beta = this->safesqrt((A * A + 1.) * one_over_q - (A - 1.) * (A - 1.));
                b0 = (number)1 / (A + 1. + (A - 1.) * cs + beta * sn);
                break;
                }
            case 6:
                {
                A = this->safesqrt(1);
                beta = this->safesqrt((A * A + 1.) * one_over_q - (A - 1.) * (A - 1.));
                b0 = (number)1 / (A + 1. - (A - 1.) * cs + beta * sn);
                break;
                }
            case 4:
                {
                A = this->safesqrt(1);
                one_over_a = (A == 0 ? 0 : (number)1 / A);
                b0 = (number)1 / (1. + alpha * one_over_a);
                break;
                }
            case 9:
            case 10:
            case 11:
            case 13:
            case 14:
                {
                b0 = (number)1 / (1. + alpha);
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                break;
                }
            default:
                {
                b0 = (number)1 / (1. + alpha);
                break;
                }
            }
    
            switch (__filtercoeff_tilde_04_type) {
            case 0:
                {
                __filtercoeff_tilde_04_la0 = __filtercoeff_tilde_04_la2 = (1. - cs) * 0.5 * b0;
                __filtercoeff_tilde_04_la1 = (1. - cs) * b0;
                __filtercoeff_tilde_04_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_04_lb2 = (1. - alpha) * b0;
                break;
                }
            case 1:
                {
                __filtercoeff_tilde_04_la0 = __filtercoeff_tilde_04_la2 = (1. + cs) * 0.5 * b0;
                __filtercoeff_tilde_04_la1 = -(1. + cs) * b0;
                __filtercoeff_tilde_04_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_04_lb2 = (1. - alpha) * b0;
                break;
                }
            case 2:
                {
                __filtercoeff_tilde_04_la0 = alpha * b0;
                __filtercoeff_tilde_04_la1 = 0.;
                __filtercoeff_tilde_04_la2 = -alpha * b0;
                __filtercoeff_tilde_04_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_04_lb2 = (1. - alpha) * b0;
                break;
                }
            case 7:
                {
                __filtercoeff_tilde_04_la0 = alpha * __q * b0;
                __filtercoeff_tilde_04_la1 = 0.;
                __filtercoeff_tilde_04_la2 = -alpha * __q * b0;
                __filtercoeff_tilde_04_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_04_lb2 = (1. - alpha) * b0;
                break;
                }
            case 3:
                {
                __filtercoeff_tilde_04_la1 = __filtercoeff_tilde_04_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_04_lb2 = (1. - alpha) * b0;
                __filtercoeff_tilde_04_la0 = __filtercoeff_tilde_04_la2 = b0;
                break;
                }
            case 8:
                {
                __filtercoeff_tilde_04_la1 = __filtercoeff_tilde_04_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_04_lb2 = __filtercoeff_tilde_04_la0 = (1. - alpha) * b0;
                __filtercoeff_tilde_04_la2 = 1.0;
                break;
                }
            case 4:
                {
                __filtercoeff_tilde_04_la0 = (1. + alpha * A) * b0;
                __filtercoeff_tilde_04_la1 = __filtercoeff_tilde_04_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_04_la2 = (1. - alpha * A) * b0;
                __filtercoeff_tilde_04_lb2 = (1. - alpha * one_over_a) * b0;
                break;
                }
            case 5:
                {
                __filtercoeff_tilde_04_la0 = A * (A + 1. - (A - 1.) * cs + beta * sn) * b0;
                __filtercoeff_tilde_04_la1 = 2. * A * (A - 1 - (A + 1) * cs) * b0;
                __filtercoeff_tilde_04_la2 = A * (A + 1. - (A - 1.) * cs - beta * sn) * b0;
                __filtercoeff_tilde_04_lb1 = -2. * (A - 1. + (A + 1.) * cs) * b0;
                __filtercoeff_tilde_04_lb2 = (A + 1. + (A - 1.) * cs - beta * sn) * b0;
                break;
                }
            case 6:
                {
                __filtercoeff_tilde_04_la0 = A * (A + 1. + (A - 1.) * cs + beta * sn) * b0;
                __filtercoeff_tilde_04_la1 = -2. * A * (A - 1. + (A + 1.) * cs) * b0;
                __filtercoeff_tilde_04_la2 = A * (A + 1. + (A - 1.) * cs - beta * sn) * b0;
                __filtercoeff_tilde_04_lb1 = 2. * (A - 1. - (A + 1.) * cs) * b0;
                __filtercoeff_tilde_04_lb2 = (A + 1. - (A - 1.) * cs - beta * sn) * b0;
                break;
                }
            case 9:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_04_la0 = __filtercoeff_tilde_04_la2 = (1. - cs) * 0.5 * b0g;
                __filtercoeff_tilde_04_la1 = (1. - cs) * b0g;
                __filtercoeff_tilde_04_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_04_lb2 = (1. - alpha) * b0;
                break;
                }
            case 10:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_04_la0 = __filtercoeff_tilde_04_la2 = (1. + cs) * 0.5 * b0g;
                __filtercoeff_tilde_04_la1 = -(1. + cs) * b0g;
                __filtercoeff_tilde_04_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_04_lb2 = (1. - alpha) * b0;
                break;
                }
            case 11:
                {
                __filtercoeff_tilde_04_la0 = alpha * 1 * b0;
                __filtercoeff_tilde_04_la1 = 0.;
                __filtercoeff_tilde_04_la2 = -alpha * 1 * b0;
                __filtercoeff_tilde_04_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_04_lb2 = (1. - alpha) * b0;
                break;
                }
            case 13:
                {
                __filtercoeff_tilde_04_la0 = alpha * 1 * __q * b0;
                __filtercoeff_tilde_04_la1 = 0.;
                __filtercoeff_tilde_04_la2 = -alpha * 1 * __q * b0;
                __filtercoeff_tilde_04_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_04_lb2 = (1. - alpha) * b0;
                break;
                }
            case 12:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_04_la1 = __filtercoeff_tilde_04_lb1 = -2. * cs;
                __filtercoeff_tilde_04_lb2 = (1. - alpha) * b0;
                __filtercoeff_tilde_04_la1 *= b0g;
                __filtercoeff_tilde_04_lb1 *= b0;
                __filtercoeff_tilde_04_la0 = b0g;
                __filtercoeff_tilde_04_la2 = b0g;
                break;
                }
            case 14:
                {
                b0g = (number)1 / (one_over_gain + alpha * one_over_gain);
                __filtercoeff_tilde_04_la0 = (1. - alpha) * b0g;
                __filtercoeff_tilde_04_la1 = -2. * cs * b0g;
                __filtercoeff_tilde_04_la2 = 1;
                __filtercoeff_tilde_04_lb1 = -2. * cs * b0;
                __filtercoeff_tilde_04_lb2 = (1. - alpha) * b0;
                break;
                }
            case 15:
                {
                __filtercoeff_tilde_04_la0 = 1;
                __filtercoeff_tilde_04_la1 = 0;
                __filtercoeff_tilde_04_la2 = 0;
                __filtercoeff_tilde_04_lb1 = 0;
                __filtercoeff_tilde_04_lb2 = 0;
                }
            default:
                {
                break;
                }
            }
    
            out1[(Index)i] = __filtercoeff_tilde_04_la0;
            out2[(Index)i] = __filtercoeff_tilde_04_la1;
            out3[(Index)i] = __filtercoeff_tilde_04_la2;
            out4[(Index)i] = __filtercoeff_tilde_04_lb1;
            out5[(Index)i] = __filtercoeff_tilde_04_lb2;
        }
    
        this->filtercoeff_tilde_04_c_frequency = __filtercoeff_tilde_04_c_frequency;
        this->filtercoeff_tilde_04_c_gain = __filtercoeff_tilde_04_c_gain;
        this->filtercoeff_tilde_04_c_q = __filtercoeff_tilde_04_c_q;
        this->filtercoeff_tilde_04_c_type = __filtercoeff_tilde_04_c_type;
        this->filtercoeff_tilde_04_la0 = __filtercoeff_tilde_04_la0;
        this->filtercoeff_tilde_04_la1 = __filtercoeff_tilde_04_la1;
        this->filtercoeff_tilde_04_la2 = __filtercoeff_tilde_04_la2;
        this->filtercoeff_tilde_04_lb1 = __filtercoeff_tilde_04_lb1;
        this->filtercoeff_tilde_04_lb2 = __filtercoeff_tilde_04_lb2;
        this->filtercoeff_tilde_04_resamp_counter = __filtercoeff_tilde_04_resamp_counter;
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
    
    void numberobj_13_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_13_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_13_value = localvalue;
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
    
    void numberobj_13_init() {
        this->numberobj_13_currentFormat = 6;
    }
    
    void numberobj_13_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_13_value;
    }
    
    void numberobj_13_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_13_value_set(preset["value"]);
    }
    
    void filtercoeff_tilde_04_dspsetup(bool force) {
        if ((bool)(this->filtercoeff_tilde_04_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->filtercoeff_tilde_04_resamp_value = this->vs;
        this->filtercoeff_tilde_04_setupDone = true;
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void updateTime(MillisecondTime time, EXTERNALENGINE ) {
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
        numberobj_13_value = 0;
        numberobj_13_value_setter(numberobj_13_value);
        listlookup_01_lookup = { 20, 45 };
        linetilde_08_time = 10;
        linetilde_08_keepramp = true;
        filtercoeff_tilde_04_frequency = 1000;
        filtercoeff_tilde_04_gain = 1;
        filtercoeff_tilde_04_q = 1;
        filtercoeff_tilde_04_type = 1;
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
        invsr = 0.000022675736961451248;
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
        numberobj_13_currentFormat = 6;
        numberobj_13_lastValue = 0;
        linetilde_08_currentValue = 20;
        filtercoeff_tilde_04_la0 = 0;
        filtercoeff_tilde_04_la1 = 0;
        filtercoeff_tilde_04_la2 = 0;
        filtercoeff_tilde_04_lb1 = 0;
        filtercoeff_tilde_04_lb2 = 0;
        filtercoeff_tilde_04_c_frequency = 0;
        filtercoeff_tilde_04_c_gain = 1;
        filtercoeff_tilde_04_c_q = 1;
        filtercoeff_tilde_04_c_type = 15;
        filtercoeff_tilde_04_resamp_counter = -1;
        filtercoeff_tilde_04_resamp_value = -1;
        filtercoeff_tilde_04_setupDone = false;
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
        number numberobj_13_value;
        list listlookup_01_input;
        list listlookup_01_lookup;
        list linetilde_08_segments;
        number linetilde_08_time;
        number linetilde_08_keepramp;
        number filtercoeff_tilde_04_frequency;
        number filtercoeff_tilde_04_gain;
        number filtercoeff_tilde_04_q;
        Int filtercoeff_tilde_04_type;
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
        Int numberobj_13_currentFormat;
        number numberobj_13_lastValue;
        list linetilde_08_activeRamps;
        number linetilde_08_currentValue;
        number filtercoeff_tilde_04_la0;
        number filtercoeff_tilde_04_la1;
        number filtercoeff_tilde_04_la2;
        number filtercoeff_tilde_04_lb1;
        number filtercoeff_tilde_04_lb2;
        number filtercoeff_tilde_04_c_frequency;
        number filtercoeff_tilde_04_c_gain;
        number filtercoeff_tilde_04_c_q;
        Int filtercoeff_tilde_04_c_type;
        Int filtercoeff_tilde_04_resamp_counter;
        Int filtercoeff_tilde_04_resamp_value;
        bool filtercoeff_tilde_04_setupDone;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

		
void advanceTime(EXTERNALENGINE*) {}
void advanceTime(INTERNALENGINE*) {
	_internalEngine.advanceTime(sampstoms(this->vs));
}

void processInternalEvents(MillisecondTime time) {
	_internalEngine.processEventsUntil(time);
}

void updateTime(MillisecondTime time, INTERNALENGINE*) {
	if (time == TimeNow) time = getPatcherTime();
	processInternalEvents(time);
	updateTime(time, (EXTERNALENGINE*)nullptr);
}

rnbomatic* operator->() {
    return this;
}
const rnbomatic* operator->() const {
    return this;
}
rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, 1646922831, false);
    getEngine()->flushClockEvents(this, -62043057, false);
}

template<typename LISTTYPE = list> void listquicksort(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template<typename LISTTYPE = list> Int listpartition(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
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

template<typename LISTTYPE = list> void listswapelements(LISTTYPE& arr, Int a, Int b) {
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

number maximum(number x, number y) {
    return (x < y ? y : x);
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

    Int numWraps = (Int)(trunc((x - lo) / range));
    numWraps = numWraps - ((x < lo ? 1 : 0));
    number result = x - range * numWraps;

    if (result >= hi)
        return result - range;
    else
        return result;
}

SampleIndex currentsampletime() {
    return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
}

number fromnormalized(Index index, number normalizedValue) {
    return this->convertFromNormalizedParameterValue(index, normalizedValue);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(0, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->toggle_02_value_number_set(v);
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(1, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }

    this->numberobj_19_value_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(2, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->numberobj_15_value_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(3, false);

    if (this->param_09_value != this->param_09_lastValue) {
        this->getEngine()->presetTouched();
        this->param_09_lastValue = this->param_09_value;
    }

    this->numberobj_16_value_set(v);
}

void param_14_value_set(number v) {
    v = this->param_14_value_constrain(v);
    this->param_14_value = v;
    this->sendParameter(4, false);

    if (this->param_14_value != this->param_14_lastValue) {
        this->getEngine()->presetTouched();
        this->param_14_lastValue = this->param_14_value;
    }

    this->numberobj_24_value_set(v);
}

void param_15_value_set(number v) {
    v = this->param_15_value_constrain(v);
    this->param_15_value = v;
    this->sendParameter(5, false);

    if (this->param_15_value != this->param_15_lastValue) {
        this->getEngine()->presetTouched();
        this->param_15_lastValue = this->param_15_value;
    }

    {
        listbase<number, 1> converted = {v};
        this->scale_08_input_set(converted);
    }

    {
        listbase<number, 1> converted = {v};
        this->scale_06_input_set(converted);
    }
}

void param_16_value_set(number v) {
    v = this->param_16_value_constrain(v);
    this->param_16_value = v;
    this->sendParameter(6, false);

    if (this->param_16_value != this->param_16_lastValue) {
        this->getEngine()->presetTouched();
        this->param_16_lastValue = this->param_16_value;
    }

    this->gen_01_lfo1_rate_set(v);
    this->gen_02_lfo1_rate_set(v);
}

void param_17_value_set(number v) {
    v = this->param_17_value_constrain(v);
    this->param_17_value = v;
    this->sendParameter(7, false);

    if (this->param_17_value != this->param_17_lastValue) {
        this->getEngine()->presetTouched();
        this->param_17_lastValue = this->param_17_value;
    }

    {
        listbase<number, 1> converted = {v};
        this->scale_09_input_set(converted);
    }
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(8, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    {
        listbase<number, 1> converted = {v};
        this->scale_04_input_set(converted);
    }
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(9, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }

    this->numberobj_18_value_set(v);
}

void param_01_value_set(number v) {
    v = this->param_01_value_constrain(v);
    this->param_01_value = v;
    this->sendParameter(10, false);

    if (this->param_01_value != this->param_01_lastValue) {
        this->getEngine()->presetTouched();
        this->param_01_lastValue = this->param_01_value;
    }

    this->gen_02_pre_del_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(11, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->numberobj_14_value_set(v);
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(12, false);

    if (this->param_08_value != this->param_08_lastValue) {
        this->getEngine()->presetTouched();
        this->param_08_lastValue = this->param_08_value;
    }

    this->numberobj_21_value_set(v);
}

void param_10_value_set(number v) {
    v = this->param_10_value_constrain(v);
    this->param_10_value = v;
    this->sendParameter(13, false);

    if (this->param_10_value != this->param_10_lastValue) {
        this->getEngine()->presetTouched();
        this->param_10_lastValue = this->param_10_value;
    }

    this->numberobj_20_value_set(v);
}

void param_11_value_set(number v) {
    v = this->param_11_value_constrain(v);
    this->param_11_value = v;
    this->sendParameter(14, false);

    if (this->param_11_value != this->param_11_lastValue) {
        this->getEngine()->presetTouched();
        this->param_11_lastValue = this->param_11_value;
    }

    this->numberobj_22_value_set(v);
}

void param_12_value_set(number v) {
    v = this->param_12_value_constrain(v);
    this->param_12_value = v;
    this->sendParameter(15, false);

    if (this->param_12_value != this->param_12_lastValue) {
        this->getEngine()->presetTouched();
        this->param_12_lastValue = this->param_12_value;
    }

    this->gen_01_lfo1_bw_set(v);
    this->gen_02_lfo1_bw_set(v);
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

void param_18_value_set(number v) {
    v = this->param_18_value_constrain(v);
    this->param_18_value = v;
    this->sendParameter(17, false);

    if (this->param_18_value != this->param_18_lastValue) {
        this->getEngine()->presetTouched();
        this->param_18_lastValue = this->param_18_value;
    }

    this->numberobj_25_value_set(v);
}

void param_19_value_set(number v) {
    v = this->param_19_value_constrain(v);
    this->param_19_value = v;
    this->sendParameter(18, false);

    if (this->param_19_value != this->param_19_lastValue) {
        this->getEngine()->presetTouched();
        this->param_19_lastValue = this->param_19_value;
    }

    this->numberobj_26_value_set(v);
}

void param_20_value_set(number v) {
    v = this->param_20_value_constrain(v);
    this->param_20_value = v;
    this->sendParameter(19, false);

    if (this->param_20_value != this->param_20_lastValue) {
        this->getEngine()->presetTouched();
        this->param_20_lastValue = this->param_20_value;
    }

    this->numberobj_27_value_set(v);
}

MillisecondTime getPatcherTime() const {
    return this->_currentTime;
}

void numberobj_14_valin_set(number v) {
    this->numberobj_14_value_set(v);
}

void numberobj_14_format_set(number v) {
    this->numberobj_14_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void toggle_02_valin_set(number v) {
    this->toggle_02_value_number_set(v);
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

void snapshot_01_out_set(number v) {
    this->snapshot_01_out = v;
    this->param_18_value_set(v);
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

template<typename LISTTYPE> void message_01_listin_list_set(const LISTTYPE& v) {
    this->message_01_set_set(v);
}

void message_01_listin_number_set(number v) {
    this->message_01_set_set(v);
}

void message_01_listin_bang_bang() {
    this->message_01_trigger_bang();
}

void numberobj_24_valin_set(number v) {
    this->numberobj_24_value_set(v);
}

void numberobj_24_format_set(number v) {
    this->numberobj_24_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_25_valin_set(number v) {
    this->numberobj_25_value_set(v);
}

void numberobj_25_format_set(number v) {
    this->numberobj_25_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_26_valin_set(number v) {
    this->numberobj_26_value_set(v);
}

void numberobj_26_format_set(number v) {
    this->numberobj_26_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_27_valin_set(number v) {
    this->numberobj_27_value_set(v);
}

void numberobj_27_format_set(number v) {
    this->numberobj_27_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void linetilde_09_target_bang() {}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

void setProbingTarget(MessageTag ) {}

void fillRNBODefaultSinus(DataRef& ref) {
    SampleBuffer buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        buffer[i] = rnbo_cos(i * 3.14159265358979323846 * 2. / bufsize);
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 26:
        {
        this->fillRNBODefaultSinus(ref);
        break;
        }
    }
}

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void allocateDataRefs() {
    this->p_01->allocateDataRefs();
    this->p_02->allocateDataRefs();
    this->p_03->allocateDataRefs();
    this->p_04->allocateDataRefs();
    this->p_05->allocateDataRefs();
    this->p_06->allocateDataRefs();
    this->p_07->allocateDataRefs();
    this->gen_01_cycle_8_buffer->requestSize(16384, 1);
    this->gen_01_cycle_8_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_13_buffer->requestSize(16384, 1);
    this->gen_01_cycle_13_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_18_buffer->requestSize(16384, 1);
    this->gen_01_cycle_18_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_23_buffer->requestSize(16384, 1);
    this->gen_01_cycle_23_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_28_buffer->requestSize(16384, 1);
    this->gen_01_cycle_28_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_33_buffer->requestSize(16384, 1);
    this->gen_01_cycle_33_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_38_buffer->requestSize(16384, 1);
    this->gen_01_cycle_38_buffer->setSampleRate(this->sr);
    this->gen_01_cycle_43_buffer->requestSize(16384, 1);
    this->gen_01_cycle_43_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_17_buffer->requestSize(16384, 1);
    this->gen_02_cycle_17_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_26_buffer->requestSize(16384, 1);
    this->gen_02_cycle_26_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_36_buffer->requestSize(16384, 1);
    this->gen_02_cycle_36_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_45_buffer->requestSize(16384, 1);
    this->gen_02_cycle_45_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_54_buffer->requestSize(16384, 1);
    this->gen_02_cycle_54_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_63_buffer->requestSize(16384, 1);
    this->gen_02_cycle_63_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_74_buffer->requestSize(16384, 1);
    this->gen_02_cycle_74_buffer->setSampleRate(this->sr);
    this->gen_02_cycle_87_buffer->requestSize(16384, 1);
    this->gen_02_cycle_87_buffer->setSampleRate(this->sr);
    this->gen_01_DL1_buffer = this->gen_01_DL1_buffer->allocateIfNeeded();

    if (this->gen_01_DL1_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL1_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL1_bufferobj);

        this->getEngine()->sendDataRefUpdated(0);
    }

    this->gen_01_DL2_buffer = this->gen_01_DL2_buffer->allocateIfNeeded();

    if (this->gen_01_DL2_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL2_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL2_bufferobj);

        this->getEngine()->sendDataRefUpdated(1);
    }

    this->gen_01_DL3_buffer = this->gen_01_DL3_buffer->allocateIfNeeded();

    if (this->gen_01_DL3_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL3_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL3_bufferobj);

        this->getEngine()->sendDataRefUpdated(2);
    }

    this->gen_01_DL4_buffer = this->gen_01_DL4_buffer->allocateIfNeeded();

    if (this->gen_01_DL4_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL4_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL4_bufferobj);

        this->getEngine()->sendDataRefUpdated(3);
    }

    this->gen_01_DL5_buffer = this->gen_01_DL5_buffer->allocateIfNeeded();

    if (this->gen_01_DL5_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL5_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL5_bufferobj);

        this->getEngine()->sendDataRefUpdated(4);
    }

    this->gen_01_DL6_buffer = this->gen_01_DL6_buffer->allocateIfNeeded();

    if (this->gen_01_DL6_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL6_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL6_bufferobj);

        this->getEngine()->sendDataRefUpdated(5);
    }

    this->gen_01_DL7_buffer = this->gen_01_DL7_buffer->allocateIfNeeded();

    if (this->gen_01_DL7_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL7_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL7_bufferobj);

        this->getEngine()->sendDataRefUpdated(6);
    }

    this->gen_01_DL8_buffer = this->gen_01_DL8_buffer->allocateIfNeeded();

    if (this->gen_01_DL8_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL8_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL8_bufferobj);

        this->getEngine()->sendDataRefUpdated(7);
    }

    this->gen_01_DL9_buffer = this->gen_01_DL9_buffer->allocateIfNeeded();

    if (this->gen_01_DL9_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL9_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL9_bufferobj);

        this->getEngine()->sendDataRefUpdated(8);
    }

    this->gen_01_DL10_buffer = this->gen_01_DL10_buffer->allocateIfNeeded();

    if (this->gen_01_DL10_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL10_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL10_bufferobj);

        this->getEngine()->sendDataRefUpdated(9);
    }

    this->gen_01_DL11_buffer = this->gen_01_DL11_buffer->allocateIfNeeded();

    if (this->gen_01_DL11_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL11_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL11_bufferobj);

        this->getEngine()->sendDataRefUpdated(10);
    }

    this->gen_01_DL12_buffer = this->gen_01_DL12_buffer->allocateIfNeeded();

    if (this->gen_01_DL12_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL12_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL12_bufferobj);

        this->getEngine()->sendDataRefUpdated(11);
    }

    this->gen_01_DL13_buffer = this->gen_01_DL13_buffer->allocateIfNeeded();

    if (this->gen_01_DL13_bufferobj->hasRequestedSize()) {
        if (this->gen_01_DL13_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_DL13_bufferobj);

        this->getEngine()->sendDataRefUpdated(12);
    }

    this->gen_01_dlL1_buffer = this->gen_01_dlL1_buffer->allocateIfNeeded();

    if (this->gen_01_dlL1_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL1_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL1_bufferobj);

        this->getEngine()->sendDataRefUpdated(13);
    }

    this->gen_01_dlL2_buffer = this->gen_01_dlL2_buffer->allocateIfNeeded();

    if (this->gen_01_dlL2_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL2_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL2_bufferobj);

        this->getEngine()->sendDataRefUpdated(14);
    }

    this->gen_01_dlL3_buffer = this->gen_01_dlL3_buffer->allocateIfNeeded();

    if (this->gen_01_dlL3_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL3_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL3_bufferobj);

        this->getEngine()->sendDataRefUpdated(15);
    }

    this->gen_01_dlL4_buffer = this->gen_01_dlL4_buffer->allocateIfNeeded();

    if (this->gen_01_dlL4_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL4_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL4_bufferobj);

        this->getEngine()->sendDataRefUpdated(16);
    }

    this->gen_01_dlL5_buffer = this->gen_01_dlL5_buffer->allocateIfNeeded();

    if (this->gen_01_dlL5_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL5_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL5_bufferobj);

        this->getEngine()->sendDataRefUpdated(17);
    }

    this->gen_01_dlL6_buffer = this->gen_01_dlL6_buffer->allocateIfNeeded();

    if (this->gen_01_dlL6_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL6_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL6_bufferobj);

        this->getEngine()->sendDataRefUpdated(18);
    }

    this->gen_01_dlL7_buffer = this->gen_01_dlL7_buffer->allocateIfNeeded();

    if (this->gen_01_dlL7_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL7_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL7_bufferobj);

        this->getEngine()->sendDataRefUpdated(19);
    }

    this->gen_01_dlL8_buffer = this->gen_01_dlL8_buffer->allocateIfNeeded();

    if (this->gen_01_dlL8_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL8_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL8_bufferobj);

        this->getEngine()->sendDataRefUpdated(20);
    }

    this->gen_01_dlL9_buffer = this->gen_01_dlL9_buffer->allocateIfNeeded();

    if (this->gen_01_dlL9_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL9_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL9_bufferobj);

        this->getEngine()->sendDataRefUpdated(21);
    }

    this->gen_01_dlL10_buffer = this->gen_01_dlL10_buffer->allocateIfNeeded();

    if (this->gen_01_dlL10_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL10_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL10_bufferobj);

        this->getEngine()->sendDataRefUpdated(22);
    }

    this->gen_01_dlL11_buffer = this->gen_01_dlL11_buffer->allocateIfNeeded();

    if (this->gen_01_dlL11_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL11_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL11_bufferobj);

        this->getEngine()->sendDataRefUpdated(23);
    }

    this->gen_01_dlL12_buffer = this->gen_01_dlL12_buffer->allocateIfNeeded();

    if (this->gen_01_dlL12_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL12_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL12_bufferobj);

        this->getEngine()->sendDataRefUpdated(24);
    }

    this->gen_01_dlL13_buffer = this->gen_01_dlL13_buffer->allocateIfNeeded();

    if (this->gen_01_dlL13_bufferobj->hasRequestedSize()) {
        if (this->gen_01_dlL13_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_dlL13_bufferobj);

        this->getEngine()->sendDataRefUpdated(25);
    }

    this->gen_01_cycle_8_buffer = this->gen_01_cycle_8_buffer->allocateIfNeeded();
    this->gen_01_cycle_13_buffer = this->gen_01_cycle_13_buffer->allocateIfNeeded();
    this->gen_01_cycle_18_buffer = this->gen_01_cycle_18_buffer->allocateIfNeeded();
    this->gen_01_cycle_23_buffer = this->gen_01_cycle_23_buffer->allocateIfNeeded();
    this->gen_01_cycle_28_buffer = this->gen_01_cycle_28_buffer->allocateIfNeeded();
    this->gen_01_cycle_33_buffer = this->gen_01_cycle_33_buffer->allocateIfNeeded();
    this->gen_01_cycle_38_buffer = this->gen_01_cycle_38_buffer->allocateIfNeeded();
    this->gen_01_cycle_43_buffer = this->gen_01_cycle_43_buffer->allocateIfNeeded();
    this->gen_02_cycle_17_buffer = this->gen_02_cycle_17_buffer->allocateIfNeeded();
    this->gen_02_cycle_26_buffer = this->gen_02_cycle_26_buffer->allocateIfNeeded();
    this->gen_02_cycle_36_buffer = this->gen_02_cycle_36_buffer->allocateIfNeeded();
    this->gen_02_cycle_45_buffer = this->gen_02_cycle_45_buffer->allocateIfNeeded();
    this->gen_02_cycle_54_buffer = this->gen_02_cycle_54_buffer->allocateIfNeeded();
    this->gen_02_cycle_63_buffer = this->gen_02_cycle_63_buffer->allocateIfNeeded();
    this->gen_02_cycle_74_buffer = this->gen_02_cycle_74_buffer->allocateIfNeeded();
    this->gen_02_cycle_87_buffer = this->gen_02_cycle_87_buffer->allocateIfNeeded();

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(26);
    }

    this->gen_02_delay_1_buffer = this->gen_02_delay_1_buffer->allocateIfNeeded();

    if (this->gen_02_delay_1_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_1_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_1_bufferobj);

        this->getEngine()->sendDataRefUpdated(27);
    }

    this->gen_02_delay_2_buffer = this->gen_02_delay_2_buffer->allocateIfNeeded();

    if (this->gen_02_delay_2_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_2_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_2_bufferobj);

        this->getEngine()->sendDataRefUpdated(28);
    }

    this->gen_02_delay_3_buffer = this->gen_02_delay_3_buffer->allocateIfNeeded();

    if (this->gen_02_delay_3_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_3_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_3_bufferobj);

        this->getEngine()->sendDataRefUpdated(29);
    }

    this->gen_02_delay_4_buffer = this->gen_02_delay_4_buffer->allocateIfNeeded();

    if (this->gen_02_delay_4_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_4_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_4_bufferobj);

        this->getEngine()->sendDataRefUpdated(30);
    }

    this->gen_02_delay_5_buffer = this->gen_02_delay_5_buffer->allocateIfNeeded();

    if (this->gen_02_delay_5_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_5_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_5_bufferobj);

        this->getEngine()->sendDataRefUpdated(31);
    }

    this->gen_02_delay_6_buffer = this->gen_02_delay_6_buffer->allocateIfNeeded();

    if (this->gen_02_delay_6_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_6_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_6_bufferobj);

        this->getEngine()->sendDataRefUpdated(32);
    }

    this->gen_02_delay_7_buffer = this->gen_02_delay_7_buffer->allocateIfNeeded();

    if (this->gen_02_delay_7_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_7_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_7_bufferobj);

        this->getEngine()->sendDataRefUpdated(33);
    }

    this->gen_02_delay_8_buffer = this->gen_02_delay_8_buffer->allocateIfNeeded();

    if (this->gen_02_delay_8_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_8_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_8_bufferobj);

        this->getEngine()->sendDataRefUpdated(34);
    }

    this->gen_02_delay_9_buffer = this->gen_02_delay_9_buffer->allocateIfNeeded();

    if (this->gen_02_delay_9_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_9_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_9_bufferobj);

        this->getEngine()->sendDataRefUpdated(35);
    }

    this->gen_02_delay_11_buffer = this->gen_02_delay_11_buffer->allocateIfNeeded();

    if (this->gen_02_delay_11_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_11_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_11_bufferobj);

        this->getEngine()->sendDataRefUpdated(36);
    }

    this->gen_02_delay_12_buffer = this->gen_02_delay_12_buffer->allocateIfNeeded();

    if (this->gen_02_delay_12_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_12_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_12_bufferobj);

        this->getEngine()->sendDataRefUpdated(37);
    }

    this->gen_02_delay_13_buffer = this->gen_02_delay_13_buffer->allocateIfNeeded();

    if (this->gen_02_delay_13_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_13_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_13_bufferobj);

        this->getEngine()->sendDataRefUpdated(38);
    }

    this->gen_02_delay_14_buffer = this->gen_02_delay_14_buffer->allocateIfNeeded();

    if (this->gen_02_delay_14_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_14_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_14_bufferobj);

        this->getEngine()->sendDataRefUpdated(39);
    }

    this->gen_02_delay_15_buffer = this->gen_02_delay_15_buffer->allocateIfNeeded();

    if (this->gen_02_delay_15_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_15_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_15_bufferobj);

        this->getEngine()->sendDataRefUpdated(40);
    }

    this->gen_02_delay_16_buffer = this->gen_02_delay_16_buffer->allocateIfNeeded();

    if (this->gen_02_delay_16_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_16_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_16_bufferobj);

        this->getEngine()->sendDataRefUpdated(41);
    }

    this->gen_02_delay_17_buffer = this->gen_02_delay_17_buffer->allocateIfNeeded();

    if (this->gen_02_delay_17_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_17_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_17_bufferobj);

        this->getEngine()->sendDataRefUpdated(42);
    }

    this->gen_02_delay_18_buffer = this->gen_02_delay_18_buffer->allocateIfNeeded();

    if (this->gen_02_delay_18_bufferobj->hasRequestedSize()) {
        if (this->gen_02_delay_18_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_02_delay_18_bufferobj);

        this->getEngine()->sendDataRefUpdated(43);
    }
}

void initializeObjects() {
    this->numberobj_14_init();
    this->gen_01_history_1_init();
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
    this->gen_01_history_2_init();
    this->gen_01_history_3_init();
    this->gen_01_history_4_init();
    this->gen_01_history_5_init();
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
    this->gen_01_history_6_init();
    this->gen_01_history_7_init();
    this->gen_01_history_8_init();
    this->gen_01_history_9_init();
    this->gen_01_history_10_init();
    this->gen_02_delay_1_init();
    this->gen_02_delay_2_init();
    this->gen_02_delay_3_init();
    this->gen_02_delay_4_init();
    this->gen_02_delay_5_init();
    this->gen_02_delay_6_init();
    this->gen_02_delay_7_init();
    this->gen_02_delay_8_init();
    this->gen_02_delay_9_init();
    this->gen_02_history_10_init();
    this->gen_02_delay_11_init();
    this->gen_02_delay_12_init();
    this->gen_02_delay_13_init();
    this->gen_02_delay_14_init();
    this->gen_02_delay_15_init();
    this->gen_02_delay_16_init();
    this->gen_02_delay_17_init();
    this->gen_02_delay_18_init();
    this->gen_02_history_19_init();
    this->numberobj_15_init();
    this->numberobj_16_init();
    this->numberobj_17_init();
    this->numberobj_18_init();
    this->numberobj_19_init();
    this->numberobj_20_init();
    this->numberobj_21_init();
    this->numberobj_22_init();
    this->numberobj_23_init();
    this->message_01_init();
    this->numberobj_24_init();
    this->numberobj_25_init();
    this->numberobj_26_init();
    this->numberobj_27_init();
    this->p_01->initializeObjects();
    this->p_02->initializeObjects();
    this->p_03->initializeObjects();
    this->p_04->initializeObjects();
    this->p_05->initializeObjects();
    this->p_06->initializeObjects();
    this->p_07->initializeObjects();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

void getState(PatcherStateInterface& ) {}

void setState() {

    this->p_01->setEngineAndPatcher(this->getEngine(), this);
    this->p_01->initialize();
    this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));

    this->p_02->setEngineAndPatcher(this->getEngine(), this);
    this->p_02->initialize();
    this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));

    this->p_03->setEngineAndPatcher(this->getEngine(), this);
    this->p_03->initialize();
    this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));

    this->p_04->setEngineAndPatcher(this->getEngine(), this);
    this->p_04->initialize();
    this->p_04->setParameterOffset(this->getParameterOffset(this->p_04));

    this->p_05->setEngineAndPatcher(this->getEngine(), this);
    this->p_05->initialize();
    this->p_05->setParameterOffset(this->getParameterOffset(this->p_05));

    this->p_06->setEngineAndPatcher(this->getEngine(), this);
    this->p_06->initialize();
    this->p_06->setParameterOffset(this->getParameterOffset(this->p_06));

    this->p_07->setEngineAndPatcher(this->getEngine(), this);
    this->p_07->initialize();
    this->p_07->setParameterOffset(this->getParameterOffset(this->p_07));
}

ParameterIndex getParameterOffset(BaseInterface& subpatcher) const {
    if (addressOf(subpatcher) == addressOf(this->p_01))
        return 20;

    if (addressOf(subpatcher) == addressOf(this->p_02))
        return 20 + this->p_01->getNumParameters();

    if (addressOf(subpatcher) == addressOf(this->p_03))
        return 20 + this->p_01->getNumParameters() + this->p_02->getNumParameters();

    if (addressOf(subpatcher) == addressOf(this->p_04))
        return 20 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters();

    if (addressOf(subpatcher) == addressOf(this->p_05))
        return 20 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters();

    if (addressOf(subpatcher) == addressOf(this->p_06))
        return 20 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters();

    if (addressOf(subpatcher) == addressOf(this->p_07))
        return 20 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters() + this->p_05->getNumParameters() + this->p_06->getNumParameters();

    return 0;
}

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(hasValue);
    this->updateTime(time, (ENGINE*)nullptr);

    switch (index) {
    case 1646922831:
        {
        this->snapshot_01_out_set(value);
        break;
        }
    case -62043057:
        {
        this->linetilde_09_target_bang();
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
    this->updateTime(time, (ENGINE*)nullptr);
    this->processOutletAtCurrentTime(sender, index, value);
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
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
        this->scheduleParamInit(12, 5);
    }

    {
        this->scheduleParamInit(13, 6);
    }

    {
        this->scheduleParamInit(14, 7);
    }

    {
        this->scheduleParamInit(15, 0);
    }

    {
        this->scheduleParamInit(16, 6);
    }

    {
        this->scheduleParamInit(17, 0);
    }

    {
        this->scheduleParamInit(18, 5);
    }

    {
        this->scheduleParamInit(19, 0);
    }

    this->processParamInitEvents();
}

number param_04_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

void p_07_in3_number_set(number v) {
    this->p_07->updateTime(this->_currentTime, (ENGINE*)nullptr);
    this->p_07->eventinlet_08_out1_number_set(v);
}

void toggle_02_output_set(number v) {
    this->p_07_in3_number_set(v);
}

void toggle_02_value_number_set(number v) {
    this->toggle_02_value_number_setter(v);
    v = this->toggle_02_value_number;
    this->toggle_02_output_set(v);
}

number param_07_value_constrain(number v) const {
    v = (v > 800 ? 800 : (v < 10 ? 10 : v));
    return v;
}

void p_03_in3_number_set(number v) {
    this->p_03->updateTime(this->_currentTime, (ENGINE*)nullptr);
    this->p_03->eventinlet_02_out1_number_set(v);
}

void numberobj_19_output_set(number v) {
    this->p_03_in3_number_set(v);
}

void numberobj_19_value_set(number v) {
    this->numberobj_19_value_setter(v);
    v = this->numberobj_19_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 10) {
        localvalue = 10;
    }

    if ((bool)(true) && localvalue > 1500) {
        localvalue = 1500;
    }

    if (this->numberobj_19_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_19_output_set(localvalue);
}

number param_05_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < -100 ? -100 : v));
    return v;
}

void p_06_in3_number_set(number v) {
    this->p_06->updateTime(this->_currentTime, (ENGINE*)nullptr);
    this->p_06->eventinlet_07_out1_number_set(v);
}

void numberobj_15_output_set(number v) {
    this->p_06_in3_number_set(v);
}

void numberobj_15_value_set(number v) {
    this->numberobj_15_value_setter(v);
    v = this->numberobj_15_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_15_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_15_output_set(localvalue);
}

number param_09_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < -100 ? -100 : v));
    return v;
}

void p_02_in3_number_set(number v) {
    this->p_02->updateTime(this->_currentTime, (ENGINE*)nullptr);
    this->p_02->eventinlet_01_out1_number_set(v);
}

void numberobj_16_output_set(number v) {
    this->p_02_in3_number_set(v);
}

void numberobj_16_value_set(number v) {
    this->numberobj_16_value_setter(v);
    v = this->numberobj_16_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_16_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_16_output_set(localvalue);
}

number param_14_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_fbc_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_fbc_set(number v) {
    v = this->gen_01_fbc_constrain(v);
    this->gen_01_fbc = v;
}

template<typename LISTTYPE> void scale_07_out_set(const LISTTYPE& v) {
    this->scale_07_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gen_01_fbc_set(converted);
    }
}

template<typename LISTTYPE> void scale_07_input_set(const LISTTYPE& v) {
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

void numberobj_24_output_set(number v) {
    {
        listbase<number, 1> converted = {v};
        this->scale_07_input_set(converted);
    }
}

void numberobj_24_value_set(number v) {
    this->numberobj_24_value_setter(v);
    v = this->numberobj_24_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_24_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_24_output_set(localvalue);
}

number param_15_value_constrain(number v) const {
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

template<typename LISTTYPE> void scale_08_out_set(const LISTTYPE& v) {
    this->scale_08_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gen_01_InGain_set(converted);
    }
}

template<typename LISTTYPE> void scale_08_input_set(const LISTTYPE& v) {
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

number gen_02_diff_gain_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_02_diff_gain_set(number v) {
    v = this->gen_02_diff_gain_constrain(v);
    this->gen_02_diff_gain = v;
}

template<typename LISTTYPE> void scale_06_out_set(const LISTTYPE& v) {
    this->scale_06_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gen_02_diff_gain_set(converted);
    }
}

template<typename LISTTYPE> void scale_06_input_set(const LISTTYPE& v) {
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

number param_16_value_constrain(number v) const {
    v = (v > 3 ? 3 : (v < 0 ? 0 : v));
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

number param_17_value_constrain(number v) const {
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

template<typename LISTTYPE> void scale_09_out_set(const LISTTYPE& v) {
    this->scale_09_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gen_01_lpf_set(converted);
    }

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gen_02_lpf_set(converted);
    }
}

template<typename LISTTYPE> void scale_09_input_set(const LISTTYPE& v) {
    this->scale_09_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_09_inlow,
            this->scale_09_inhigh,
            this->scale_09_outlow,
            this->scale_09_outhigh,
            this->scale_09_power
        ));
    }

    this->scale_09_out_set(tmp);
}

number param_02_value_constrain(number v) const {
    v = (v > 10 ? 10 : (v < 0 ? 0 : v));
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

void slide_01_out1_set(number v) {
    this->gen_02_apf_g_set(v);
}

void slide_01_x_set(number x) {
    this->slide_01_x = x;
    auto down = this->slide_01_down;
    auto up = this->slide_01_up;
    number temp = x - this->slide_01_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
    this->slide_01_prev = this->slide_01_prev + ((x > this->slide_01_prev ? iup : idown)) * temp;

    {
        this->slide_01_out1_set(this->slide_01_prev);
        return;
    }
}

void slide_01_up_set(number v) {
    this->slide_01_up = v;
}

void slide_01_down_set(number v) {
    this->slide_01_down = v;
}

template<typename LISTTYPE> void scale_04_out_set(const LISTTYPE& v) {
    this->scale_04_out = jsCreateListCopy(v);

    {
        if (v->length > 2)
            this->slide_01_down_set(v[2]);

        if (v->length > 1)
            this->slide_01_up_set(v[1]);

        number converted = (v->length > 0 ? v[0] : 0);
        this->slide_01_x_set(converted);
    }
}

template<typename LISTTYPE> void scale_04_input_set(const LISTTYPE& v) {
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

number param_06_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void linetilde_09_time_set(number v) {
    this->linetilde_09_time = v;
}

template<typename LISTTYPE> void linetilde_09_segments_set(const LISTTYPE& v) {
    this->linetilde_09_segments = jsCreateListCopy(v);

    if ((bool)(v->length)) {
        if (v->length == 1 && this->linetilde_09_time == 0) {
            this->linetilde_09_activeRamps->length = 0;
            this->linetilde_09_currentValue = v[0];
        } else {
            auto currentTime = this->currentsampletime();
            number lastRampValue = this->linetilde_09_currentValue;
            number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;

            for (Index i = 0; i < this->linetilde_09_activeRamps->length; i += 3) {
                rampEnd = this->linetilde_09_activeRamps[(Index)(i + 2)];

                if (rampEnd > currentTime) {
                    this->linetilde_09_activeRamps[(Index)(i + 2)] = currentTime;
                    number diff = rampEnd - currentTime;
                    number valueDiff = diff * this->linetilde_09_activeRamps[(Index)(i + 1)];
                    lastRampValue = this->linetilde_09_activeRamps[(Index)i] - valueDiff;
                    this->linetilde_09_activeRamps[(Index)i] = lastRampValue;
                    this->linetilde_09_activeRamps->length = i + 3;
                    rampEnd = currentTime;
                } else {
                    lastRampValue = this->linetilde_09_activeRamps[(Index)i];
                }
            }

            if (rampEnd < currentTime) {
                this->linetilde_09_activeRamps->push(lastRampValue);
                this->linetilde_09_activeRamps->push(0);
                this->linetilde_09_activeRamps->push(currentTime);
            }

            number lastRampEnd = currentTime;

            for (Index i = 0; i < v->length; i += 2) {
                number destinationValue = v[(Index)i];
                number inc = 0;
                number rampTimeInSamples;

                if (v->length > i + 1) {
                    rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);

                    if ((bool)(this->linetilde_09_keepramp)) {
                        this->linetilde_09_time_set(v[(Index)(i + 1)]);
                    }
                } else {
                    rampTimeInSamples = this->mstosamps(this->linetilde_09_time);
                }

                if (rampTimeInSamples <= 0) {
                    rampTimeInSamples = 1;
                }

                inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                lastRampEnd += rampTimeInSamples;
                this->linetilde_09_activeRamps->push(destinationValue);
                this->linetilde_09_activeRamps->push(inc);
                this->linetilde_09_activeRamps->push(lastRampEnd);
                lastRampValue = destinationValue;
            }
        }
    }
}

void numberobj_17_output_set(number v) {
    {
        listbase<number, 1> converted = {v};
        this->linetilde_09_segments_set(converted);
    }
}

void numberobj_17_value_set(number v) {
    this->numberobj_17_value_setter(v);
    v = this->numberobj_17_value;
    number localvalue = v;

    if (this->numberobj_17_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_17_output_set(localvalue);
}

void expr_06_out1_set(number v) {
    this->expr_06_out1 = v;
    this->numberobj_17_value_set(this->expr_06_out1);
}

void expr_06_in1_set(number in1) {
    this->expr_06_in1 = in1;

    this->expr_06_out1_set(
        (this->expr_06_in2 == 0 ? 0 : (this->expr_06_in2 == 0. ? 0. : this->expr_06_in1 / this->expr_06_in2))
    );//#map:/_obj-137:1
}

void numberobj_18_output_set(number v) {
    this->expr_06_in1_set(v);
}

void numberobj_18_value_set(number v) {
    this->numberobj_18_value_setter(v);
    v = this->numberobj_18_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_18_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_18_output_set(localvalue);
}

number param_01_value_constrain(number v) const {
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
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_decay_constrain(number v) const {
    if (v < 0.2)
        v = 0.2;

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

template<typename LISTTYPE> void scale_05_out_set(const LISTTYPE& v) {
    this->scale_05_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gen_01_decay_set(converted);
    }

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->gen_02_decay2_set(converted);
    }
}

template<typename LISTTYPE> void scale_05_input_set(const LISTTYPE& v) {
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

void numberobj_14_output_set(number v) {
    {
        listbase<number, 1> converted = {v};
        this->scale_05_input_set(converted);
    }
}

void numberobj_14_value_set(number v) {
    this->numberobj_14_value_setter(v);
    v = this->numberobj_14_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_14_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_14_output_set(localvalue);
}

number param_08_value_constrain(number v) const {
    v = (v > 8000 ? 8000 : (v < 1000 ? 1000 : v));
    return v;
}

void p_05_in3_number_set(number v) {
    this->p_05->updateTime(this->_currentTime, (ENGINE*)nullptr);
    this->p_05->eventinlet_04_out1_number_set(v);
}

void numberobj_21_output_set(number v) {
    this->p_05_in3_number_set(v);
}

void numberobj_21_value_set(number v) {
    this->numberobj_21_value_setter(v);
    v = this->numberobj_21_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 1000) {
        localvalue = 1000;
    }

    if ((bool)(true) && localvalue > 8000) {
        localvalue = 8000;
    }

    if (this->numberobj_21_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_21_output_set(localvalue);
}

number param_10_value_constrain(number v) const {
    v = (v > 18 ? 18 : (v < -18 ? -18 : v));
    return v;
}

void p_05_in4_number_set(number v) {
    this->p_05->updateTime(this->_currentTime, (ENGINE*)nullptr);
    this->p_05->eventinlet_05_out1_number_set(v);
}

void numberobj_20_output_set(number v) {
    this->p_05_in4_number_set(v);
}

void numberobj_20_value_set(number v) {
    this->numberobj_20_value_setter(v);
    v = this->numberobj_20_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < -18) {
        localvalue = -18;
    }

    if ((bool)(true) && localvalue > 18) {
        localvalue = 18;
    }

    if (this->numberobj_20_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_20_output_set(localvalue);
}

number param_11_value_constrain(number v) const {
    v = (v > 16000 ? 16000 : (v < 1000 ? 1000 : v));
    return v;
}

void p_04_in3_number_set(number v) {
    this->p_04->updateTime(this->_currentTime, (ENGINE*)nullptr);
    this->p_04->eventinlet_03_out1_number_set(v);
}

void numberobj_22_output_set(number v) {
    this->p_04_in3_number_set(v);
}

void numberobj_22_value_set(number v) {
    this->numberobj_22_value_setter(v);
    v = this->numberobj_22_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 300) {
        localvalue = 300;
    }

    if ((bool)(true) && localvalue > 20000) {
        localvalue = 20000;
    }

    if (this->numberobj_22_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_22_output_set(localvalue);
}

number param_12_value_constrain(number v) const {
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

number param_13_value_constrain(number v) const {
    v = (v > 5 ? 5 : (v < 0.25 ? 0.25 : v));
    return v;
}

void p_05_in5_number_set(number v) {
    this->p_05->updateTime(this->_currentTime, (ENGINE*)nullptr);
    this->p_05->eventinlet_06_out1_number_set(v);
}

void numberobj_23_output_set(number v) {
    this->p_05_in5_number_set(v);
}

void numberobj_23_value_set(number v) {
    this->numberobj_23_value_setter(v);
    v = this->numberobj_23_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0.5) {
        localvalue = 0.5;
    }

    if ((bool)(true) && localvalue > 7) {
        localvalue = 7;
    }

    if (this->numberobj_23_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_23_output_set(localvalue);
}

number param_18_value_constrain(number v) const {
    v = (v > 6907 ? 6907 : (v < 0 ? 0 : v));
    return v;
}

void numberobj_25_output_set(number ) {}

void numberobj_25_value_set(number v) {
    this->numberobj_25_value_setter(v);
    v = this->numberobj_25_value;
    number localvalue = v;

    if (this->numberobj_25_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_25_output_set(localvalue);
}

number param_19_value_constrain(number v) const {
    v = (v > 2000 ? 2000 : (v < 100 ? 100 : v));
    return v;
}

void gen_01_xover_set(number v) {
    this->gen_01_xover = v;
}

void numberobj_26_output_set(number v) {
    this->gen_01_xover_set(v);
}

void numberobj_26_value_set(number v) {
    this->numberobj_26_value_setter(v);
    v = this->numberobj_26_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 400) {
        localvalue = 400;
    }

    if ((bool)(true) && localvalue > 8000) {
        localvalue = 8000;
    }

    if (this->numberobj_26_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_26_output_set(localvalue);
}

number param_20_value_constrain(number v) const {
    v = (v > 2 ? 2 : (v < 0.25 ? 0.25 : v));
    return v;
}

number gen_01_mult_constrain(number v) const {
    if (v < 0.25)
        v = 0.25;

    if (v > 2)
        v = 2;

    return v;
}

void gen_01_mult_set(number v) {
    v = this->gen_01_mult_constrain(v);
    this->gen_01_mult = v;
}

void numberobj_27_output_set(number v) {
    this->gen_01_mult_set(v);
}

void numberobj_27_value_set(number v) {
    this->numberobj_27_value_setter(v);
    v = this->numberobj_27_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 4) {
        localvalue = 4;
    }

    if (this->numberobj_27_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_27_output_set(localvalue);
}

template<typename LISTTYPE> void message_01_set_set(const LISTTYPE& v) {
    this->message_01_set = jsCreateListCopy(v);
}

template<typename LISTTYPE> void message_01_out_set(const LISTTYPE& ) {}

void message_01_trigger_bang() {
    if ((bool)(this->message_01_set->length) || (bool)(false)) {
        this->message_01_out_set(this->message_01_set);
    }
}

void ctlin_01_outchannel_set(number ) {}

void ctlin_01_outcontroller_set(number ) {}

void fromnormalized_01_output_set(number v) {
    this->param_04_value_set(v);
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
    this->param_05_value_set(v);
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
    this->param_06_value_set(v);
}

void fromnormalized_03_input_set(number v) {
    this->fromnormalized_03_output_set(this->fromnormalized(9, v));
}

void expr_07_out1_set(number v) {
    this->expr_07_out1 = v;
    this->fromnormalized_03_input_set(this->expr_07_out1);
}

void expr_07_in1_set(number in1) {
    this->expr_07_in1 = in1;
    this->expr_07_out1_set(this->expr_07_in1 * this->expr_07_in2);//#map:expr_07:1
}

void ctlin_03_value_set(number v) {
    this->expr_07_in1_set(v);
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
    this->param_07_value_set(v);
}

void fromnormalized_04_input_set(number v) {
    this->fromnormalized_04_output_set(this->fromnormalized(1, v));
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
    this->param_08_value_set(v);
}

void fromnormalized_05_input_set(number v) {
    this->fromnormalized_05_output_set(this->fromnormalized(12, v));
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
    this->param_09_value_set(v);
}

void fromnormalized_06_input_set(number v) {
    this->fromnormalized_06_output_set(this->fromnormalized(3, v));
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
    this->param_10_value_set(v);
}

void fromnormalized_07_input_set(number v) {
    this->fromnormalized_07_output_set(this->fromnormalized(13, v));
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
    this->param_11_value_set(v);
}

void fromnormalized_08_input_set(number v) {
    this->fromnormalized_08_output_set(this->fromnormalized(14, v));
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

void ctlin_09_outchannel_set(number ) {}

void ctlin_09_outcontroller_set(number ) {}

void fromnormalized_09_output_set(number v) {
    this->param_13_value_set(v);
}

void fromnormalized_09_input_set(number v) {
    this->fromnormalized_09_output_set(this->fromnormalized(16, v));
}

void expr_13_out1_set(number v) {
    this->expr_13_out1 = v;
    this->fromnormalized_09_input_set(this->expr_13_out1);
}

void expr_13_in1_set(number in1) {
    this->expr_13_in1 = in1;
    this->expr_13_out1_set(this->expr_13_in1 * this->expr_13_in2);//#map:expr_13:1
}

void ctlin_09_value_set(number v) {
    this->expr_13_in1_set(v);
}

void ctlin_09_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_09_channel || this->ctlin_09_channel == -1) && (data[1] == this->ctlin_09_controller || this->ctlin_09_controller == -1)) {
        this->ctlin_09_outchannel_set(channel);
        this->ctlin_09_outcontroller_set(data[1]);
        this->ctlin_09_value_set(data[2]);
        this->ctlin_09_status = 0;
    }
}

void ctlin_10_outchannel_set(number ) {}

void ctlin_10_outcontroller_set(number ) {}

void fromnormalized_10_output_set(number v) {
    this->param_19_value_set(v);
}

void fromnormalized_10_input_set(number v) {
    this->fromnormalized_10_output_set(this->fromnormalized(18, v));
}

void expr_14_out1_set(number v) {
    this->expr_14_out1 = v;
    this->fromnormalized_10_input_set(this->expr_14_out1);
}

void expr_14_in1_set(number in1) {
    this->expr_14_in1 = in1;
    this->expr_14_out1_set(this->expr_14_in1 * this->expr_14_in2);//#map:expr_14:1
}

void ctlin_10_value_set(number v) {
    this->expr_14_in1_set(v);
}

void ctlin_10_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_10_channel || this->ctlin_10_channel == -1) && (data[1] == this->ctlin_10_controller || this->ctlin_10_controller == -1)) {
        this->ctlin_10_outchannel_set(channel);
        this->ctlin_10_outcontroller_set(data[1]);
        this->ctlin_10_value_set(data[2]);
        this->ctlin_10_status = 0;
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

void dcblock_tilde_03_perform(const Sample * x, number gain, SampleValue * out1, Index n) {
    RNBO_UNUSED(gain);
    auto __dcblock_tilde_03_ym1 = this->dcblock_tilde_03_ym1;
    auto __dcblock_tilde_03_xm1 = this->dcblock_tilde_03_xm1;
    Index i;

    for (i = 0; i < n; i++) {
        number y = x[(Index)i] - __dcblock_tilde_03_xm1 + __dcblock_tilde_03_ym1 * 0.9997;
        __dcblock_tilde_03_xm1 = x[(Index)i];
        __dcblock_tilde_03_ym1 = y;
        out1[(Index)i] = y;
    }

    this->dcblock_tilde_03_xm1 = __dcblock_tilde_03_xm1;
    this->dcblock_tilde_03_ym1 = __dcblock_tilde_03_ym1;
}

void dcblock_tilde_04_perform(const Sample * x, number gain, SampleValue * out1, Index n) {
    RNBO_UNUSED(gain);
    auto __dcblock_tilde_04_ym1 = this->dcblock_tilde_04_ym1;
    auto __dcblock_tilde_04_xm1 = this->dcblock_tilde_04_xm1;
    Index i;

    for (i = 0; i < n; i++) {
        number y = x[(Index)i] - __dcblock_tilde_04_xm1 + __dcblock_tilde_04_ym1 * 0.9997;
        __dcblock_tilde_04_xm1 = x[(Index)i];
        __dcblock_tilde_04_ym1 = y;
        out1[(Index)i] = y;
    }

    this->dcblock_tilde_04_xm1 = __dcblock_tilde_04_xm1;
    this->dcblock_tilde_04_ym1 = __dcblock_tilde_04_ym1;
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
    number lfo1_rate,
    number pre_del,
    number decay2,
    number lpf,
    number lfo1_bw,
    number apf_g,
    number diff_gain,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    auto __gen_02_history_19_value = this->gen_02_history_19_value;
    auto __gen_02_history_10_value = this->gen_02_history_10_value;
    number abs_20_0 = rnbo_abs(lpf);
    number mul_21_1 = (this->sr == 0. ? 0. : abs_20_0 * -6.28318530717958647692 / this->sr);
    number exp_22_2 = rnbo_exp(mul_21_1);
    number neg_130_114 = -apf_g;
    number neg_137_121 = -apf_g;
    number neg_144_128 = -apf_g;
    number neg_151_135 = -apf_g;
    number neg_158_142 = -apf_g;
    number neg_165_149 = -apf_g;
    number neg_172_156 = -apf_g;
    number neg_179_163 = -apf_g;
    number neg_194_179 = -apf_g;
    number neg_201_186 = -apf_g;
    number neg_208_193 = -apf_g;
    number neg_215_200 = -apf_g;
    number neg_222_207 = -apf_g;
    number neg_229_214 = -apf_g;
    number neg_236_221 = -apf_g;
    number neg_243_228 = -apf_g;
    Index i;

    for (i = 0; i < n; i++) {
        number float_23_3 = float(73.69);
        number slide_24_5 = this->gen_02_slide_4_next(decay2, 2000, 2000);
        number mul_25_6 = float_23_3 * slide_24_5;
        number float_26_7 = float(70.13);
        number mul_27_8 = float_26_7 * slide_24_5;
        number float_28_9 = float(65.03);
        number mul_29_10 = float_28_9 * slide_24_5;
        number float_30_11 = float(62.1);
        number mul_31_12 = float_30_11 * slide_24_5;
        number float_32_13 = float(57.72);
        number mul_33_14 = float_32_13 * slide_24_5;
        number phasor_34_16 = this->gen_02_phasor_15_next(lfo1_rate, 0);
        number cycle_35 = 0;
        number cycleindex_36 = 0;
        array<number, 2> result_18 = this->gen_02_cycle_17_next(phasor_34_16, 0);
        cycleindex_36 = result_18[1];
        cycle_35 = result_18[0];
        auto scale_37_19 = this->scale(cycle_35, -1, 1, 0, 1, 1);
        number mul_38_20 = scale_37_19 * lfo1_bw;
        number add_39_21 = mul_25_6 + mul_38_20;
        auto mstosamps_40_22 = this->mstosamps(add_39_21);
        number float_41_23 = float(55.75);
        number mul_42_24 = float_41_23 * slide_24_5;
        number add_43_25 = phasor_34_16 + 0.5;
        number cycle_44 = 0;
        number cycleindex_45 = 0;
        array<number, 2> result_27 = this->gen_02_cycle_26_next(add_43_25, 0);
        cycleindex_45 = result_27[1];
        cycle_44 = result_27[0];
        auto scale_46_28 = this->scale(cycle_44, -1, 1, 0, 1, 1);
        number mul_47_29 = scale_46_28 * lfo1_bw;
        number add_48_30 = mul_27_8 + mul_47_29;
        auto mstosamps_49_31 = this->mstosamps(add_48_30);
        number float_50_32 = float(52.45);
        number mul_51_33 = float_50_32 * slide_24_5;
        number add_52_34 = phasor_34_16 + 0.12;
        number cycle_53 = 0;
        number cycleindex_54 = 0;
        array<number, 2> result_37 = this->gen_02_cycle_36_next(add_52_34, 0);
        cycleindex_54 = result_37[1];
        cycle_53 = result_37[0];
        auto scale_55_38 = this->scale(cycle_53, -1, 1, 0, 1, 1);
        number mul_56_39 = scale_55_38 * lfo1_bw;
        number add_57_40 = mul_29_10 + mul_56_39;
        auto mstosamps_58_41 = this->mstosamps(add_57_40);
        number float_59_42 = float(49.33);
        number mul_60_43 = float_59_42 * slide_24_5;
        number add_61_44 = phasor_34_16 + 0.46;
        number cycle_62 = 0;
        number cycleindex_63 = 0;
        array<number, 2> result_46 = this->gen_02_cycle_45_next(add_61_44, 0);
        cycleindex_63 = result_46[1];
        cycle_62 = result_46[0];
        auto scale_64_47 = this->scale(cycle_62, -1, 1, 0, 1, 1);
        number mul_65_48 = scale_64_47 * lfo1_bw;
        number add_66_49 = mul_31_12 + mul_65_48;
        auto mstosamps_67_50 = this->mstosamps(add_66_49);
        number float_68_51 = float(46.4);
        number mul_69_52 = float_68_51 * slide_24_5;
        number add_70_53 = phasor_34_16 + 0.18;
        number cycle_71 = 0;
        number cycleindex_72 = 0;
        array<number, 2> result_55 = this->gen_02_cycle_54_next(add_70_53, 0);
        cycleindex_72 = result_55[1];
        cycle_71 = result_55[0];
        auto scale_73_56 = this->scale(cycle_71, -1, 1, 0, 1, 1);
        number mul_74_57 = scale_73_56 * lfo1_bw;
        number add_75_58 = mul_33_14 + mul_74_57;
        auto mstosamps_76_59 = this->mstosamps(add_75_58);
        number float_77_60 = float(43.57);
        number mul_78_61 = float_77_60 * slide_24_5;
        number add_79_62 = phasor_34_16 + 0.4;
        number cycle_80 = 0;
        number cycleindex_81 = 0;
        array<number, 2> result_64 = this->gen_02_cycle_63_next(add_79_62, 0);
        cycleindex_81 = result_64[1];
        cycle_80 = result_64[0];
        auto scale_82_65 = this->scale(cycle_80, -1, 1, 0, 1, 1);
        number mul_83_66 = scale_82_65 * lfo1_bw;
        number add_84_67 = mul_42_24 + mul_83_66;
        auto mstosamps_85_68 = this->mstosamps(add_84_67);
        number float_86_69 = float(41.72);
        number mul_87_70 = float_86_69 * slide_24_5;
        number add_88_71 = mul_87_70 + mul_83_66;
        auto mstosamps_89_72 = this->mstosamps(add_88_71);
        number add_90_73 = phasor_34_16 + 0.25;
        number cycle_91 = 0;
        number cycleindex_92 = 0;
        array<number, 2> result_75 = this->gen_02_cycle_74_next(add_90_73, 0);
        cycleindex_92 = result_75[1];
        cycle_91 = result_75[0];
        auto scale_93_76 = this->scale(cycle_91, -1, 1, 0, 1, 1);
        number mul_94_77 = scale_93_76 * lfo1_bw;
        number add_95_78 = mul_51_33 + mul_94_77;
        auto mstosamps_96_79 = this->mstosamps(add_95_78);
        number add_97_80 = mul_78_61 + mul_94_77;
        auto mstosamps_98_81 = this->mstosamps(add_97_80);
        number float_99_82 = float(38.11);
        number mul_100_83 = float_99_82 * slide_24_5;
        number add_101_84 = mul_100_83 + mul_74_57;
        auto mstosamps_102_85 = this->mstosamps(add_101_84);
        number add_103_86 = phasor_34_16 + 0.32;
        number cycle_104 = 0;
        number cycleindex_105 = 0;
        array<number, 2> result_88 = this->gen_02_cycle_87_next(add_103_86, 0);
        cycleindex_105 = result_88[1];
        cycle_104 = result_88[0];
        auto scale_106_89 = this->scale(cycle_104, -1, 1, 0, 1, 1);
        number mul_107_90 = scale_106_89 * lfo1_bw;
        number add_108_91 = mul_60_43 + mul_107_90;
        auto mstosamps_109_92 = this->mstosamps(add_108_91);
        number add_110_93 = mul_69_52 + mul_107_90;
        auto mstosamps_111_94 = this->mstosamps(add_110_93);
        number float_112_95 = float(36.15);
        number mul_113_96 = float_112_95 * slide_24_5;
        number add_114_97 = mul_113_96 + mul_65_48;
        auto mstosamps_115_98 = this->mstosamps(add_114_97);
        number float_116_99 = float(35.45);
        number mul_117_100 = float_116_99 * slide_24_5;
        number add_118_101 = mul_117_100 + mul_56_39;
        auto mstosamps_119_102 = this->mstosamps(add_118_101);
        number add_120_103 = in1[(Index)i] + in2[(Index)i];
        number slide_121_105 = this->gen_02_slide_104_next(pre_del, 500, 500);
        auto mstosamps_122_106 = this->mstosamps(slide_121_105);
        this->gen_02_delay_1_write(add_120_103);
        number tap_123_107 = this->gen_02_delay_1_read(mstosamps_122_106, 1);
        number mul_124_108 = tap_123_107 * diff_gain;
        number float_125_109 = float(32.87);
        number mul_126_110 = float_125_109 * slide_24_5;
        number add_127_111 = mul_126_110 + mul_47_29;
        auto mstosamps_128_112 = this->mstosamps(add_127_111);
        number tap_129_113 = this->gen_02_delay_2_read(mstosamps_128_112, 1);
        number mul_131_115 = tap_129_113 * apf_g;
        number add_132_116 = mul_124_108 + mul_131_115;
        number mul_133_117 = add_132_116 * neg_130_114;
        number add_134_118 = tap_129_113 + mul_133_117;
        number gen_135_119 = add_134_118;
        number tap_136_120 = this->gen_02_delay_3_read(mstosamps_115_98, 1);
        number mul_138_122 = tap_136_120 * apf_g;
        number add_139_123 = gen_135_119 + mul_138_122;
        number mul_140_124 = add_139_123 * neg_137_121;
        number add_141_125 = tap_136_120 + mul_140_124;
        number gen_142_126 = add_141_125;
        number tap_143_127 = this->gen_02_delay_4_read(mstosamps_89_72, 1);
        number mul_145_129 = tap_143_127 * apf_g;
        number add_146_130 = gen_142_126 + mul_145_129;
        number mul_147_131 = add_146_130 * neg_144_128;
        number add_148_132 = tap_143_127 + mul_147_131;
        number gen_149_133 = add_148_132;
        number tap_150_134 = this->gen_02_delay_5_read(mstosamps_111_94, 1);
        number mul_152_136 = tap_150_134 * apf_g;
        number add_153_137 = gen_149_133 + mul_152_136;
        number mul_154_138 = add_153_137 * neg_151_135;
        number add_155_139 = tap_150_134 + mul_154_138;
        number gen_156_140 = add_155_139;
        number tap_157_141 = this->gen_02_delay_6_read(mstosamps_96_79, 1);
        number mul_159_143 = tap_157_141 * apf_g;
        number add_160_144 = gen_156_140 + mul_159_143;
        number mul_161_145 = add_160_144 * neg_158_142;
        number add_162_146 = tap_157_141 + mul_161_145;
        number gen_163_147 = add_162_146;
        number tap_164_148 = this->gen_02_delay_7_read(mstosamps_76_59, 1);
        number mul_166_150 = tap_164_148 * apf_g;
        number add_167_151 = gen_163_147 + mul_166_150;
        number mul_168_152 = add_167_151 * neg_165_149;
        number add_169_153 = tap_164_148 + mul_168_152;
        number gen_170_154 = add_169_153;
        number tap_171_155 = this->gen_02_delay_8_read(mstosamps_58_41, 1);
        number mul_173_157 = tap_171_155 * apf_g;
        number add_174_158 = gen_170_154 + mul_173_157;
        number mul_175_159 = add_174_158 * neg_172_156;
        number add_176_160 = tap_171_155 + mul_175_159;
        number gen_177_161 = add_176_160;
        number tap_178_162 = this->gen_02_delay_9_read(mstosamps_40_22, 1);
        number mul_180_164 = tap_178_162 * apf_g;
        number add_181_165 = gen_177_161 + mul_180_164;
        number mul_182_166 = add_181_165 * neg_179_163;
        number add_183_167 = tap_178_162 + mul_182_166;
        number gen_184_168 = add_183_167;
        number mix_185_169 = gen_184_168 + exp_22_2 * (__gen_02_history_10_value - gen_184_168);
        number gen_186_170 = mix_185_169;
        number history_10_next_187_171 = fixdenorm(mix_185_169);
        number dcblock_188_173 = this->gen_02_dcblock_172_next(gen_186_170, 0.9997);
        out2[(Index)i] = dcblock_188_173;
        number float_189_174 = float(30.59);
        number mul_190_175 = float_189_174 * slide_24_5;
        number add_191_176 = mul_190_175 + mul_38_20;
        auto mstosamps_192_177 = this->mstosamps(add_191_176);
        number tap_193_178 = this->gen_02_delay_11_read(mstosamps_192_177, 1);
        number mul_195_180 = tap_193_178 * apf_g;
        number add_196_181 = mul_124_108 + mul_195_180;
        number mul_197_182 = add_196_181 * neg_194_179;
        number add_198_183 = tap_193_178 + mul_197_182;
        number gen_199_184 = add_198_183;
        number tap_200_185 = this->gen_02_delay_12_read(mstosamps_119_102, 1);
        number mul_202_187 = tap_200_185 * apf_g;
        number add_203_188 = gen_199_184 + mul_202_187;
        number mul_204_189 = add_203_188 * neg_201_186;
        number add_205_190 = tap_200_185 + mul_204_189;
        number gen_206_191 = add_205_190;
        number tap_207_192 = this->gen_02_delay_13_read(mstosamps_102_85, 1);
        number mul_209_194 = tap_207_192 * apf_g;
        number add_210_195 = gen_206_191 + mul_209_194;
        number mul_211_196 = add_210_195 * neg_208_193;
        number add_212_197 = tap_207_192 + mul_211_196;
        number gen_213_198 = add_212_197;
        number tap_214_199 = this->gen_02_delay_14_read(mstosamps_98_81, 1);
        number mul_216_201 = tap_214_199 * apf_g;
        number add_217_202 = gen_213_198 + mul_216_201;
        number mul_218_203 = add_217_202 * neg_215_200;
        number add_219_204 = tap_214_199 + mul_218_203;
        number gen_220_205 = add_219_204;
        number tap_221_206 = this->gen_02_delay_15_read(mstosamps_109_92, 1);
        number mul_223_208 = tap_221_206 * apf_g;
        number add_224_209 = gen_220_205 + mul_223_208;
        number mul_225_210 = add_224_209 * neg_222_207;
        number add_226_211 = tap_221_206 + mul_225_210;
        number gen_227_212 = add_226_211;
        number tap_228_213 = this->gen_02_delay_16_read(mstosamps_85_68, 1);
        number mul_230_215 = tap_228_213 * apf_g;
        number add_231_216 = gen_227_212 + mul_230_215;
        number mul_232_217 = add_231_216 * neg_229_214;
        number add_233_218 = tap_228_213 + mul_232_217;
        number gen_234_219 = add_233_218;
        number tap_235_220 = this->gen_02_delay_17_read(mstosamps_67_50, 1);
        number mul_237_222 = tap_235_220 * apf_g;
        number add_238_223 = gen_234_219 + mul_237_222;
        number mul_239_224 = add_238_223 * neg_236_221;
        number add_240_225 = tap_235_220 + mul_239_224;
        number gen_241_226 = add_240_225;
        number tap_242_227 = this->gen_02_delay_18_read(mstosamps_49_31, 1);
        number mul_244_229 = tap_242_227 * apf_g;
        number add_245_230 = gen_241_226 + mul_244_229;
        number mul_246_231 = add_245_230 * neg_243_228;
        number add_247_232 = tap_242_227 + mul_246_231;
        number gen_248_233 = add_247_232;
        number mix_249_234 = gen_248_233 + exp_22_2 * (__gen_02_history_19_value - gen_248_233);
        number gen_250_235 = mix_249_234;
        number history_19_next_251_236 = fixdenorm(mix_249_234);
        number dcblock_252_238 = this->gen_02_dcblock_237_next(gen_250_235, 0.9997);
        out1[(Index)i] = dcblock_252_238;
        this->gen_02_delay_2_write(add_132_116);
        __gen_02_history_19_value = history_19_next_251_236;
        this->gen_02_delay_18_write(add_245_230);
        this->gen_02_delay_17_write(add_238_223);
        this->gen_02_delay_16_write(add_231_216);
        this->gen_02_delay_15_write(add_224_209);
        this->gen_02_delay_14_write(add_217_202);
        this->gen_02_delay_13_write(add_210_195);
        this->gen_02_delay_12_write(add_203_188);
        this->gen_02_delay_11_write(add_196_181);
        __gen_02_history_10_value = history_10_next_187_171;
        this->gen_02_delay_9_write(add_181_165);
        this->gen_02_delay_8_write(add_174_158);
        this->gen_02_delay_7_write(add_167_151);
        this->gen_02_delay_6_write(add_160_144);
        this->gen_02_delay_5_write(add_153_137);
        this->gen_02_delay_4_write(add_146_130);
        this->gen_02_delay_3_write(add_139_123);
        this->gen_02_delay_1_step();
        this->gen_02_delay_2_step();
        this->gen_02_delay_3_step();
        this->gen_02_delay_4_step();
        this->gen_02_delay_5_step();
        this->gen_02_delay_6_step();
        this->gen_02_delay_7_step();
        this->gen_02_delay_8_step();
        this->gen_02_delay_9_step();
        this->gen_02_delay_11_step();
        this->gen_02_delay_12_step();
        this->gen_02_delay_13_step();
        this->gen_02_delay_14_step();
        this->gen_02_delay_15_step();
        this->gen_02_delay_16_step();
        this->gen_02_delay_17_step();
        this->gen_02_delay_18_step();
    }

    this->gen_02_history_10_value = __gen_02_history_10_value;
    this->gen_02_history_19_value = __gen_02_history_19_value;
}

void gen_01_perform(
    const Sample * in1,
    const Sample * in2,
    number xover,
    number lfo1_bw,
    number decay,
    number lfo1_rate,
    number InGain,
    number fbc,
    number lpf,
    number mult,
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
    SampleValue * out3,
    SampleValue * out4,
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
    auto __gen_01_history_8_value = this->gen_01_history_8_value;
    auto __gen_01_history_7_value = this->gen_01_history_7_value;
    auto __gen_01_history_6_value = this->gen_01_history_6_value;
    auto __gen_01_history_5_value = this->gen_01_history_5_value;
    auto __gen_01_history_9_value = this->gen_01_history_9_value;
    auto __gen_01_history_4_value = this->gen_01_history_4_value;
    auto __gen_01_history_3_value = this->gen_01_history_3_value;
    auto __gen_01_history_2_value = this->gen_01_history_2_value;
    auto __gen_01_filterOutput_value = this->gen_01_filterOutput_value;
    auto __gen_01_history_1_value = this->gen_01_history_1_value;
    auto __gen_01_history_10_value = this->gen_01_history_10_value;
    number mul_55_47 = 1 * lpf;
    number abs_56_48 = rnbo_abs(mul_55_47);
    number mul_57_49 = (this->sr == 0. ? 0. : abs_56_48 * -6.28318530717958647692 / this->sr);
    number exp_58_50 = rnbo_exp(mul_57_49);
    number alpha_102 = 1 - rnbo_exp((this->sr == 0. ? 0. : -15079.644737231041 / this->sr));
    number l_feedback_109 = mult * fbc;
    number expr_68_110 = l_feedback_109;
    number clamp_70_112 = (xover > this->sr / (number)4 ? this->sr / (number)4 : (xover < 0 ? 0 : xover));
    number clamp_71_113 = (clamp_70_112 > this->sr / (number)4 ? this->sr / (number)4 : (clamp_70_112 < -this->sr / (number)4 ? -this->sr / (number)4 : clamp_70_112));
    number abs_72_114 = rnbo_abs(clamp_71_113);
    number mul_73_115 = (this->sr == 0. ? 0. : abs_72_114 * 6.28318530717958647692 / this->sr);
    number cos_74_116 = rnbo_cos(mul_73_115);
    number sin_75_117 = rnbo_sin(mul_73_115);
    number sub_76_118 = sin_75_117 - 1;
    number div_77_119 = (cos_74_116 == 0. ? 0. : sub_76_118 / cos_74_116);
    number clamp_78_120 = (div_77_119 > 1 ? 1 : (div_77_119 < -1 ? -1 : div_77_119));
    number neg_81_123 = -clamp_78_120;
    number abs_88_130 = rnbo_abs(clamp_70_112);
    number clamp_89_131 = (abs_88_130 > this->sr / (number)4 ? this->sr / (number)4 : (abs_88_130 < 0 ? 0 : abs_88_130));
    number mul_90_132 = (this->sr == 0. ? 0. : clamp_89_131 * 3.14159265358979323846 / this->sr);
    number tan_91_133 = rnbo_tan(mul_90_132);
    number add_92_134 = tan_91_133 + 1;
    number div_93_135 = (add_92_134 == 0. ? 0. : tan_91_133 / add_92_134);
    number abs_103_145 = rnbo_abs(clamp_70_112);
    number clamp_104_146 = (abs_103_145 > this->sr / (number)4 ? this->sr / (number)4 : (abs_103_145 < 0 ? 0 : abs_103_145));
    number mul_105_147 = (this->sr == 0. ? 0. : clamp_104_146 * 3.14159265358979323846 / this->sr);
    number tan_106_148 = rnbo_tan(mul_105_147);
    number add_107_149 = tan_106_148 + 1;
    number div_108_150 = (add_107_149 == 0. ? 0. : tan_106_148 / add_107_149);
    number clamp_176_218 = (xover > this->sr / (number)4 ? this->sr / (number)4 : (xover < 0 ? 0 : xover));
    number clamp_177_219 = (clamp_176_218 > this->sr / (number)4 ? this->sr / (number)4 : (clamp_176_218 < -this->sr / (number)4 ? -this->sr / (number)4 : clamp_176_218));
    number abs_178_220 = rnbo_abs(clamp_177_219);
    number mul_179_221 = (this->sr == 0. ? 0. : abs_178_220 * 6.28318530717958647692 / this->sr);
    number cos_180_222 = rnbo_cos(mul_179_221);
    number sin_181_223 = rnbo_sin(mul_179_221);
    number sub_182_224 = sin_181_223 - 1;
    number div_183_225 = (cos_180_222 == 0. ? 0. : sub_182_224 / cos_180_222);
    number clamp_184_226 = (div_183_225 > 1 ? 1 : (div_183_225 < -1 ? -1 : div_183_225));
    number neg_187_229 = -clamp_184_226;
    number abs_194_236 = rnbo_abs(clamp_176_218);
    number clamp_195_237 = (abs_194_236 > this->sr / (number)4 ? this->sr / (number)4 : (abs_194_236 < 0 ? 0 : abs_194_236));
    number mul_196_238 = (this->sr == 0. ? 0. : clamp_195_237 * 3.14159265358979323846 / this->sr);
    number tan_197_239 = rnbo_tan(mul_196_238);
    number add_198_240 = tan_197_239 + 1;
    number div_199_241 = (add_198_240 == 0. ? 0. : tan_197_239 / add_198_240);
    number abs_209_251 = rnbo_abs(clamp_176_218);
    number clamp_210_252 = (abs_209_251 > this->sr / (number)4 ? this->sr / (number)4 : (abs_209_251 < 0 ? 0 : abs_209_251));
    number mul_211_253 = (this->sr == 0. ? 0. : clamp_210_252 * 3.14159265358979323846 / this->sr);
    number tan_212_254 = rnbo_tan(mul_211_253);
    number add_213_255 = tan_212_254 + 1;
    number div_214_256 = (add_213_255 == 0. ? 0. : tan_212_254 / add_213_255);
    Index i;

    for (i = 0; i < n; i++) {
        number slide_11_1 = this->gen_01_slide_0_next(decay, 2000, 1500);
        number slide_12_3 = this->gen_01_slide_2_next(decay, 2000, 2000);
        number mul_13_4 = in1[(Index)i] * InGain;
        number mul_14_5 = in2[(Index)i] * InGain;
        number phasor_15_7 = this->gen_01_phasor_6_next(lfo1_rate, 0);
        number cycle_16 = 0;
        number cycleindex_17 = 0;
        array<number, 2> result_9 = this->gen_01_cycle_8_next(phasor_15_7, 0);
        cycleindex_17 = result_9[1];
        cycle_16 = result_9[0];
        auto scale_18_10 = this->scale(cycle_16, -1, 1, 0, 1, 1);
        number mul_19_11 = scale_18_10 * lfo1_bw;
        number add_20_12 = phasor_15_7 + 0.12;
        number cycle_21 = 0;
        number cycleindex_22 = 0;
        array<number, 2> result_14 = this->gen_01_cycle_13_next(add_20_12, 0);
        cycleindex_22 = result_14[1];
        cycle_21 = result_14[0];
        auto scale_23_15 = this->scale(cycle_21, -1, 1, 0, 1, 1);
        number mul_24_16 = scale_23_15 * lfo1_bw;
        number add_25_17 = phasor_15_7 + 0.18;
        number cycle_26 = 0;
        number cycleindex_27 = 0;
        array<number, 2> result_19 = this->gen_01_cycle_18_next(add_25_17, 0);
        cycleindex_27 = result_19[1];
        cycle_26 = result_19[0];
        auto scale_28_20 = this->scale(cycle_26, -1, 1, 0, 1, 1);
        number mul_29_21 = scale_28_20 * lfo1_bw;
        number add_30_22 = phasor_15_7 + 0.25;
        number cycle_31 = 0;
        number cycleindex_32 = 0;
        array<number, 2> result_24 = this->gen_01_cycle_23_next(add_30_22, 0);
        cycleindex_32 = result_24[1];
        cycle_31 = result_24[0];
        auto scale_33_25 = this->scale(cycle_31, -1, 1, 0, 1, 1);
        number mul_34_26 = scale_33_25 * lfo1_bw;
        number add_35_27 = phasor_15_7 + 0.32;
        number cycle_36 = 0;
        number cycleindex_37 = 0;
        array<number, 2> result_29 = this->gen_01_cycle_28_next(add_35_27, 0);
        cycleindex_37 = result_29[1];
        cycle_36 = result_29[0];
        auto scale_38_30 = this->scale(cycle_36, -1, 1, 0, 1, 1);
        number mul_39_31 = scale_38_30 * lfo1_bw;
        number add_40_32 = phasor_15_7 + 0.4;
        number cycle_41 = 0;
        number cycleindex_42 = 0;
        array<number, 2> result_34 = this->gen_01_cycle_33_next(add_40_32, 0);
        cycleindex_42 = result_34[1];
        cycle_41 = result_34[0];
        auto scale_43_35 = this->scale(cycle_41, -1, 1, 0, 1, 1);
        number mul_44_36 = scale_43_35 * lfo1_bw;
        number add_45_37 = phasor_15_7 + 0.46;
        number cycle_46 = 0;
        number cycleindex_47 = 0;
        array<number, 2> result_39 = this->gen_01_cycle_38_next(add_45_37, 0);
        cycleindex_47 = result_39[1];
        cycle_46 = result_39[0];
        auto scale_48_40 = this->scale(cycle_46, -1, 1, 0, 1, 1);
        number mul_49_41 = scale_48_40 * lfo1_bw;
        number add_50_42 = phasor_15_7 + 0.5;
        number cycle_51 = 0;
        number cycleindex_52 = 0;
        array<number, 2> result_44 = this->gen_01_cycle_43_next(add_50_42, 0);
        cycleindex_52 = result_44[1];
        cycle_51 = result_44[0];
        auto scale_53_45 = this->scale(cycle_51, -1, 1, 0, 1, 1);
        number mul_54_46 = scale_53_45 * lfo1_bw;
        number mix_59_51 = __gen_01_history_10_value + exp_58_50 * (__gen_01_history_1_value - __gen_01_history_10_value);
        number gen_60_52 = mix_59_51;
        number history_1_next_61_53 = fixdenorm(mix_59_51);
        number add_62_54 = gen_60_52 + mul_13_4;
        number lfo1_55 = mul_19_11;
        number lfo2_56 = mul_24_16;
        number lfo3_57 = mul_29_21;
        number lfo5_58 = mul_39_31;
        number size_59 = slide_11_1;
        number d1mod_60 = 120 * size_59 + lfo1_55;
        number d2mod_61 = 76 * size_59 + lfo2_56;
        number d3mod_62 = 30 * size_59 + lfo3_57;
        number d4mod_63 = 8 * size_59 + mul_34_26;
        number d5mod_64 = 12 * size_59 + lfo5_58;
        number d6mod_65 = 4 * size_59 + mul_44_36;
        number d7mod_66 = 17 * size_59 + mul_49_41;
        number d8mod_67 = 31 * size_59 + mul_54_46;
        number d9mod_68 = 3 * size_59 + lfo5_58;
        number d10mod_69 = 87 * size_59 + mul_44_36;
        number d11mod_70 = 62 * size_59 + mul_49_41;
        number dt1_rt60_71 = (120 + 76 + 30 + 8 + 12 + 4 + 17 + 31 + 3 + 87 + 62) * size_59;
        number expr_63_72 = dt1_rt60_71;
        number ds1_73 = d1mod_60 * this->sr / (number)1000;
        number ds2_74 = d2mod_61 * this->sr / (number)1000;
        number ds3_75 = d3mod_62 * this->sr / (number)1000;
        number ds4_76 = d4mod_63 * this->sr / (number)1000;
        number ds5_77 = d5mod_64 * this->sr / (number)1000;
        number ds6_78 = d6mod_65 * this->sr / (number)1000;
        number ds7_79 = d7mod_66 * this->sr / (number)1000;
        number ds8_80 = d8mod_67 * this->sr / (number)1000;
        number ds9_81 = d9mod_68 * this->sr / (number)1000;
        number ds10_82 = d10mod_69 * this->sr / (number)1000;
        number ds11_83 = d11mod_70 * this->sr / (number)1000;
        number apf1out_84 = -0.3 * add_62_54 + this->gen_01_DL4_read(ds4_76, 1);
        this->gen_01_DL4_write(add_62_54 + 0.3 * apf1out_84);
        number apf2out_85 = -0.3 * apf1out_84 + this->gen_01_DL5_read(ds5_77, 1);
        this->gen_01_DL5_write(apf1out_84 + 0.3 * apf2out_85);
        this->gen_01_DL6_write(apf2out_85);
        number dl6out_86 = this->gen_01_DL6_read(ds6_78, 1);
        number expr_64_87 = dl6out_86 * 0.34;
        this->gen_01_DL7_write(dl6out_86);
        number dl7out_88 = this->gen_01_DL7_read(ds7_79, 1);
        number napf1out_89 = this->gen_01_DL10_read(ds10_82, 1) - 0.5 * dl7out_88;
        this->gen_01_DL10_write(dl7out_88 + 0.5 * napf1out_89);
        number allPassOut2_90 = this->gen_01_DL11_read(ds11_83, 1) - 0.25 * napf1out_89;
        this->gen_01_DL11_write(napf1out_89 + 0.25 * allPassOut2_90);
        this->gen_01_DL8_write(allPassOut2_90);
        number dl8out_91 = this->gen_01_DL8_read(ds8_80, 1);
        number expr_65_92 = dl8out_91 * 0.14;
        this->gen_01_DL9_write(dl8out_91);
        number dl9out_93 = this->gen_01_DL9_read(ds9_81, 1);
        number x5_94 = dl9out_93;
        number y1_95 = -0.5 * x5_94 + this->gen_01_DL1_read(ds1_73, 1);
        this->gen_01_DL1_write(x5_94 + 0.5 * y1_95);
        number delayAddr1_96 = ds1_73 - ds2_74;
        number y2_97 = -0.25 * y1_95 + this->gen_01_DL2_read(delayAddr1_96, 1);
        this->gen_01_DL2_write(y1_95 + 0.25 * y2_97);
        number delayAddr2_98 = ds1_73 - ds3_75;
        number y3_99 = -0.25 * y2_97 + this->gen_01_DL3_read(delayAddr2_98, 1);
        this->gen_01_DL3_write(y2_97 + 0.25 * y3_99);
        number y_100 = -0.5 * x5_94 + this->gen_01_DL1_read(ds1_73, 1);
        this->gen_01_DL1_write(x5_94 + 0.5 * y_100);
        number tolp_101 = y3_99;
        number inlp_103 = tolp_101;
        number lowpass_104 = (1 - alpha_102) * __gen_01_filterOutput_value + alpha_102 * inlp_103;
        __gen_01_filterOutput_value = lowpass_104;
        number expr_66_105 = y3_99 * 0.14;
        number expr_67_106 = y3_99;
        number dt_to_sec_107 = expr_63_72 / (number)1000;
        number rt60_108 = (rnbo_log10((fbc * 0.93 <= 0.0000000001 ? 0.0000000001 : fbc * 0.93)) == 0. ? 0. : -3 * dt_to_sec_107 / rnbo_log10((fbc * 0.93 <= 0.0000000001 ? 0.0000000001 : fbc * 0.93)));
        number expr_69_111 = rt60_108;
        out3[(Index)i] = expr_69_111;
        out4[(Index)i] = expr_68_110;
        number mul_79_121 = __gen_01_history_2_value * clamp_78_120;
        number add_80_122 = expr_67_106 + mul_79_121;
        number mul_82_124 = add_80_122 * neg_81_123;
        number add_83_125 = __gen_01_history_2_value + mul_82_124;
        number gen_84_126 = add_83_125;
        number history_2_next_85_127 = fixdenorm(add_80_122);
        number gen_86_128 = gen_84_126;
        number sub_87_129 = expr_67_106 - __gen_01_history_3_value;
        number mul_94_136 = sub_87_129 * div_93_135;
        number add_95_137 = mul_94_136 + __gen_01_history_3_value;
        number gen_96_138 = add_95_137;
        number sub_97_139 = expr_67_106 - add_95_137;
        number gen_98_140 = sub_97_139;
        number add_99_141 = sub_97_139 + add_95_137;
        number gen_100_142 = add_99_141;
        number history_3_next_101_143 = fixdenorm(add_95_137 + mul_94_136);
        number sub_102_144 = gen_96_138 - __gen_01_history_4_value;
        number mul_109_151 = sub_102_144 * div_108_150;
        number add_110_152 = mul_109_151 + __gen_01_history_4_value;
        number gen_111_153 = add_110_152;
        number sub_112_154 = gen_96_138 - add_110_152;
        number gen_113_155 = sub_112_154;
        number add_114_156 = sub_112_154 + add_110_152;
        number gen_115_157 = add_114_156;
        number history_3_next_116_158 = fixdenorm(add_110_152 + mul_109_151);
        number gen_117_159 = gen_111_153;
        number sub_118_160 = gen_86_128 - gen_111_153;
        number gen_119_161 = sub_118_160;
        number mul_120_162 = gen_117_159 * expr_68_110;
        number mul_121_163 = gen_119_161 * fbc;
        number add_122_164 = mul_120_162 + mul_121_163;
        number tanh_123_165 = rnbo_tanh(add_122_164);
        number add_124_166 = expr_64_87 + expr_65_92;
        number add_125_167 = add_124_166 + expr_66_105;
        number outL_126_168 = add_125_167;
        number tanh_127_169 = rnbo_tanh(outL_126_168);
        out1[(Index)i] = tanh_127_169;
        number mix_128_170 = __gen_01_history_9_value + exp_58_50 * (__gen_01_history_5_value - __gen_01_history_9_value);
        number gen_129_171 = mix_128_170;
        number history_5_next_130_172 = fixdenorm(mix_128_170);
        number add_131_173 = mul_14_5 + gen_129_171;
        number d1mod_132_174 = 111 * slide_12_3 + mul_19_11;
        number d2mod_133_175 = 37 * slide_12_3 + mul_24_16;
        number d3mod_134_176 = 15 * slide_12_3 + mul_29_21;
        number d4mod_135_177 = 8 * slide_12_3 + mul_34_26;
        number d5mod_136_178 = 12 * slide_12_3 + mul_39_31;
        number d6mod_137_179 = 3.9 * slide_12_3 + mul_44_36;
        number d7mod_138_180 = 31 * slide_12_3 + mul_49_41;
        number d8mod_139_181 = 17 * slide_12_3 + mul_54_46;
        number d9mod_140_182 = 8 * slide_12_3 + mul_39_31;
        number d10mod_141_183 = 43 * slide_12_3 + mul_44_36;
        number d11mod_142_184 = 44 * slide_12_3 + mul_49_41;
        number ds_143_185 = d1mod_132_174 * this->sr / (number)1000;
        number ds_144_186 = d2mod_133_175 * this->sr / (number)1000;
        number ds_145_187 = d3mod_134_176 * this->sr / (number)1000;
        number ds_146_188 = d4mod_135_177 * this->sr / (number)1000;
        number ds_147_189 = d5mod_136_178 * this->sr / (number)1000;
        number ds_148_190 = d6mod_137_179 * this->sr / (number)1000;
        number ds_149_191 = d7mod_138_180 * this->sr / (number)1000;
        number ds_150_192 = d8mod_139_181 * this->sr / (number)1000;
        number ds_151_193 = d9mod_140_182 * this->sr / (number)1000;
        number ds_152_194 = d10mod_141_183 * this->sr / (number)1000;
        number ds_153_195 = d11mod_142_184 * this->sr / (number)1000;
        number apf1out_154_196 = -0.3 * add_131_173 + this->gen_01_dlL4_read(ds_146_188, 1);
        this->gen_01_dlL4_write(add_131_173 + 0.3 * apf1out_154_196);
        number apf2out_155_197 = -0.3 * apf1out_154_196 + this->gen_01_dlL5_read(ds_147_189, 1);
        this->gen_01_dlL5_write(apf1out_154_196 + 0.3 * apf2out_155_197);
        this->gen_01_dlL6_write(apf2out_155_197);
        number dl6out_156_198 = this->gen_01_dlL6_read(ds_148_190, 1);
        number expr_157_199 = dl6out_156_198 * 0.34;
        this->gen_01_dlL7_write(dl6out_156_198);
        number dl7out_158_200 = this->gen_01_dlL7_read(ds_149_191, 1);
        number napf1out_159_201 = this->gen_01_dlL10_read(ds_152_194, 1) - 0.5 * dl7out_158_200;
        this->gen_01_dlL10_write(dl7out_158_200 + 0.5 * napf1out_159_201);
        number allPassOut_160_202 = this->gen_01_dlL11_read(ds_153_195, 1) - 0.25 * napf1out_159_201;
        this->gen_01_dlL11_write(napf1out_159_201 + 0.25 * allPassOut_160_202);
        this->gen_01_dlL8_write(allPassOut_160_202);
        number dl8out_161_203 = this->gen_01_dlL8_read(ds_150_192, 1);
        number expr_162_204 = dl8out_161_203 * 0.14;
        this->gen_01_dlL9_write(dl8out_161_203);
        number dl9out_163_205 = this->gen_01_dlL9_read(ds_151_193, 1);
        number y_164_206 = -0.5 * dl9out_163_205 + this->gen_01_dlL1_read(ds_143_185, 1);
        this->gen_01_dlL1_write(dl9out_163_205 + 0.5 * y_164_206);
        number delayAddr_165_207 = ds_143_185 - ds_144_186;
        number y_166_208 = -0.25 * y_164_206 + this->gen_01_dlL2_read(delayAddr_165_207, 1);
        this->gen_01_dlL2_write(y_164_206 + 0.25 * y_166_208);
        number delayAddr_167_209 = ds_143_185 - ds_145_187;
        number y_168_210 = -0.25 * y_166_208 + this->gen_01_dlL3_read(delayAddr_167_209, 1);
        this->gen_01_dlL3_write(y_166_208 + 0.25 * y_168_210);
        number y_169_211 = -0.5 * dl9out_163_205 + this->gen_01_dlL1_read(ds_143_185, 1);
        this->gen_01_dlL1_write(dl9out_163_205 + 0.5 * y_169_211);
        number expr_170_212 = y_168_210 * 0.14;
        number expr_171_213 = y_168_210;
        number add_172_214 = expr_157_199 + expr_162_204;
        number add_173_215 = add_172_214 + expr_170_212;
        number outR_174_216 = add_173_215;
        number tanh_175_217 = rnbo_tanh(outR_174_216);
        out2[(Index)i] = tanh_175_217;
        number mul_185_227 = __gen_01_history_6_value * clamp_184_226;
        number add_186_228 = expr_171_213 + mul_185_227;
        number mul_188_230 = add_186_228 * neg_187_229;
        number add_189_231 = __gen_01_history_6_value + mul_188_230;
        number gen_190_232 = add_189_231;
        number history_2_next_191_233 = fixdenorm(add_186_228);
        number gen_192_234 = gen_190_232;
        number sub_193_235 = expr_171_213 - __gen_01_history_7_value;
        number mul_200_242 = sub_193_235 * div_199_241;
        number add_201_243 = mul_200_242 + __gen_01_history_7_value;
        number gen_202_244 = add_201_243;
        number sub_203_245 = expr_171_213 - add_201_243;
        number gen_204_246 = sub_203_245;
        number add_205_247 = sub_203_245 + add_201_243;
        number gen_206_248 = add_205_247;
        number history_3_next_207_249 = fixdenorm(add_201_243 + mul_200_242);
        number sub_208_250 = gen_202_244 - __gen_01_history_8_value;
        number mul_215_257 = sub_208_250 * div_214_256;
        number add_216_258 = mul_215_257 + __gen_01_history_8_value;
        number gen_217_259 = add_216_258;
        number sub_218_260 = gen_202_244 - add_216_258;
        number gen_219_261 = sub_218_260;
        number add_220_262 = sub_218_260 + add_216_258;
        number gen_221_263 = add_220_262;
        number history_3_next_222_264 = fixdenorm(add_216_258 + mul_215_257);
        number gen_223_265 = gen_217_259;
        number sub_224_266 = gen_192_234 - gen_217_259;
        number gen_225_267 = sub_224_266;
        number mul_226_268 = gen_223_265 * expr_68_110;
        number mul_227_269 = gen_225_267 * fbc;
        number add_228_270 = mul_226_268 + mul_227_269;
        number tanh_229_271 = rnbo_tanh(add_228_270);
        number history_9_next_230_272 = fixdenorm(tanh_123_165);
        number history_10_next_231_273 = fixdenorm(tanh_229_271);
        __gen_01_history_1_value = history_1_next_61_53;
        __gen_01_history_10_value = history_10_next_231_273;
        __gen_01_history_9_value = history_9_next_230_272;
        __gen_01_history_7_value = history_3_next_207_249;
        __gen_01_history_8_value = history_3_next_222_264;
        __gen_01_history_6_value = history_2_next_191_233;
        __gen_01_history_5_value = history_5_next_130_172;
        __gen_01_history_3_value = history_3_next_101_143;
        __gen_01_history_4_value = history_3_next_116_158;
        __gen_01_history_2_value = history_2_next_85_127;
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

    this->gen_01_history_10_value = __gen_01_history_10_value;
    this->gen_01_history_1_value = __gen_01_history_1_value;
    this->gen_01_filterOutput_value = __gen_01_filterOutput_value;
    this->gen_01_history_2_value = __gen_01_history_2_value;
    this->gen_01_history_3_value = __gen_01_history_3_value;
    this->gen_01_history_4_value = __gen_01_history_4_value;
    this->gen_01_history_9_value = __gen_01_history_9_value;
    this->gen_01_history_5_value = __gen_01_history_5_value;
    this->gen_01_history_6_value = __gen_01_history_6_value;
    this->gen_01_history_7_value = __gen_01_history_7_value;
    this->gen_01_history_8_value = __gen_01_history_8_value;
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
    // subpatcher: postq_Level~
    ConstSampleArray<2> ins = {in1, in2};

    SampleArray<2> outs = {out1, out2};
    this->p_02->process(ins, 2, outs, 2, n);
}

void snapshot_01_perform(const SampleValue * input_signal, Index n) {
    auto __snapshot_01_lastValue = this->snapshot_01_lastValue;
    auto __snapshot_01_calc = this->snapshot_01_calc;
    auto __snapshot_01_count = this->snapshot_01_count;
    auto __snapshot_01_nextTime = this->snapshot_01_nextTime;
    auto __snapshot_01_interval = this->snapshot_01_interval;
    number timeInSamples = this->msToSamps(__snapshot_01_interval, this->sr);

    if (__snapshot_01_interval > 0) {
        for (Index i = 0; i < n; i++) {
            if (__snapshot_01_nextTime <= __snapshot_01_count + (SampleIndex)(i)) {
                {
                    __snapshot_01_calc = input_signal[(Index)i];
                }

                this->getEngine()->scheduleClockEventWithValue(
                    this,
                    1646922831,
                    this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                    __snapshot_01_calc
                );;

                __snapshot_01_calc = 0;
                __snapshot_01_nextTime += timeInSamples;
            }
        }

        __snapshot_01_count += this->vs;
    }

    __snapshot_01_lastValue = input_signal[(Index)(n - 1)];
    this->snapshot_01_nextTime = __snapshot_01_nextTime;
    this->snapshot_01_count = __snapshot_01_count;
    this->snapshot_01_calc = __snapshot_01_calc;
    this->snapshot_01_lastValue = __snapshot_01_lastValue;
}

void linetilde_09_perform(SampleValue * out, Index n) {
    auto __linetilde_09_time = this->linetilde_09_time;
    auto __linetilde_09_keepramp = this->linetilde_09_keepramp;
    auto __linetilde_09_currentValue = this->linetilde_09_currentValue;
    Index i = 0;

    if ((bool)(this->linetilde_09_activeRamps->length)) {
        while ((bool)(this->linetilde_09_activeRamps->length) && i < n) {
            number destinationValue = this->linetilde_09_activeRamps[0];
            number inc = this->linetilde_09_activeRamps[1];
            number rampTimeInSamples = this->linetilde_09_activeRamps[2] - this->audioProcessSampleCount - i;
            number val = __linetilde_09_currentValue;

            while (rampTimeInSamples > 0 && i < n) {
                out[(Index)i] = val;
                val += inc;
                i++;
                rampTimeInSamples--;
            }

            if (rampTimeInSamples <= 0) {
                val = destinationValue;
                this->linetilde_09_activeRamps->splice(0, 3);

                if ((bool)(!(bool)(this->linetilde_09_activeRamps->length))) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -62043057,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;

                    if ((bool)(!(bool)(__linetilde_09_keepramp))) {
                        __linetilde_09_time = 0;
                    }
                }
            }

            __linetilde_09_currentValue = val;
        }
    }

    while (i < n) {
        out[(Index)i] = __linetilde_09_currentValue;
        i++;
    }

    this->linetilde_09_currentValue = __linetilde_09_currentValue;
    this->linetilde_09_time = __linetilde_09_time;
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

void dcblock_tilde_01_perform(const Sample * x, number gain, SampleValue * out1, Index n) {
    RNBO_UNUSED(gain);
    auto __dcblock_tilde_01_ym1 = this->dcblock_tilde_01_ym1;
    auto __dcblock_tilde_01_xm1 = this->dcblock_tilde_01_xm1;
    Index i;

    for (i = 0; i < n; i++) {
        number y = x[(Index)i] - __dcblock_tilde_01_xm1 + __dcblock_tilde_01_ym1 * 0.9997;
        __dcblock_tilde_01_xm1 = x[(Index)i];
        __dcblock_tilde_01_ym1 = y;
        out1[(Index)i] = y;
    }

    this->dcblock_tilde_01_xm1 = __dcblock_tilde_01_xm1;
    this->dcblock_tilde_01_ym1 = __dcblock_tilde_01_ym1;
}

void dspexpr_05_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < -1 ? -1 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void dcblock_tilde_02_perform(const Sample * x, number gain, SampleValue * out1, Index n) {
    RNBO_UNUSED(gain);
    auto __dcblock_tilde_02_ym1 = this->dcblock_tilde_02_ym1;
    auto __dcblock_tilde_02_xm1 = this->dcblock_tilde_02_xm1;
    Index i;

    for (i = 0; i < n; i++) {
        number y = x[(Index)i] - __dcblock_tilde_02_xm1 + __dcblock_tilde_02_ym1 * 0.9997;
        __dcblock_tilde_02_xm1 = x[(Index)i];
        __dcblock_tilde_02_ym1 = y;
        out1[(Index)i] = y;
    }

    this->dcblock_tilde_02_xm1 = __dcblock_tilde_02_xm1;
    this->dcblock_tilde_02_ym1 = __dcblock_tilde_02_ym1;
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

void numberobj_14_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_14_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_14_value = localvalue;
}

void toggle_02_value_number_setter(number v) {
    this->toggle_02_value_number = (v != 0 ? 1 : 0);
}

void numberobj_15_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_15_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_15_value = localvalue;
}

void numberobj_16_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_16_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_16_value = localvalue;
}

void numberobj_17_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_17_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_17_value = localvalue;
}

void numberobj_18_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
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

    if ((bool)(true) && localvalue < 10) {
        localvalue = 10;
    }

    if ((bool)(true) && localvalue > 1500) {
        localvalue = 1500;
    }

    if (this->numberobj_19_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_19_value = localvalue;
}

void numberobj_20_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < -18) {
        localvalue = -18;
    }

    if ((bool)(true) && localvalue > 18) {
        localvalue = 18;
    }

    if (this->numberobj_20_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_20_value = localvalue;
}

void numberobj_21_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 1000) {
        localvalue = 1000;
    }

    if ((bool)(true) && localvalue > 8000) {
        localvalue = 8000;
    }

    if (this->numberobj_21_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_21_value = localvalue;
}

void numberobj_22_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 300) {
        localvalue = 300;
    }

    if ((bool)(true) && localvalue > 20000) {
        localvalue = 20000;
    }

    if (this->numberobj_22_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_22_value = localvalue;
}

void numberobj_23_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0.5) {
        localvalue = 0.5;
    }

    if ((bool)(true) && localvalue > 7) {
        localvalue = 7;
    }

    if (this->numberobj_23_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_23_value = localvalue;
}

void numberobj_24_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_24_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_24_value = localvalue;
}

void numberobj_25_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_25_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_25_value = localvalue;
}

void numberobj_26_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 400) {
        localvalue = 400;
    }

    if ((bool)(true) && localvalue > 8000) {
        localvalue = 8000;
    }

    if (this->numberobj_26_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_26_value = localvalue;
}

void numberobj_27_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 4) {
        localvalue = 4;
    }

    if (this->numberobj_27_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_27_value = localvalue;
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

void numberobj_14_init() {
    this->numberobj_14_currentFormat = 6;
}

void numberobj_14_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_14_value;
}

void numberobj_14_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_14_value_set(preset["value"]);
}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void dcblock_tilde_01_reset() {
    this->dcblock_tilde_01_xm1 = 0;
    this->dcblock_tilde_01_ym1 = 0;
}

void dcblock_tilde_01_dspsetup(bool force) {
    if ((bool)(this->dcblock_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->dcblock_tilde_01_reset();
    this->dcblock_tilde_01_setupDone = true;
}

number gen_01_history_1_getvalue() {
    return this->gen_01_history_1_value;
}

void gen_01_history_1_setvalue(number val) {
    this->gen_01_history_1_value = val;
}

void gen_01_history_1_reset() {
    this->gen_01_history_1_value = 0;
}

void gen_01_history_1_init() {
    this->gen_01_history_1_value = 0;
}

void gen_01_DL1_step() {
    this->gen_01_DL1_reader++;

    if (this->gen_01_DL1_reader >= (Int)(this->gen_01_DL1_buffer->getSize()))
        this->gen_01_DL1_reader = 0;
}

number gen_01_DL1_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_DL1_buffer->getSize()) + this->gen_01_DL1_reader - ((size > this->gen_01_DL1__maxdelay ? this->gen_01_DL1__maxdelay : (size < (1 + this->gen_01_DL1_reader != this->gen_01_DL1_writer) ? 1 + this->gen_01_DL1_reader != this->gen_01_DL1_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_DL1_buffer->getSize()) + this->gen_01_DL1_reader - ((size > this->gen_01_DL1__maxdelay ? this->gen_01_DL1__maxdelay : (size < (this->gen_01_DL1_reader != this->gen_01_DL1_writer) ? this->gen_01_DL1_reader != this->gen_01_DL1_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));
    return this->gen_01_DL1_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL1_wrap)));
}

void gen_01_DL1_write(number v) {
    this->gen_01_DL1_writer = this->gen_01_DL1_reader;
    this->gen_01_DL1_buffer[(Index)this->gen_01_DL1_writer] = v;
}

number gen_01_DL1_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_DL1_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_DL1_size() {
    return this->gen_01_DL1__maxdelay;
}

void gen_01_DL2_step() {
    this->gen_01_DL2_reader++;

    if (this->gen_01_DL2_reader >= (Int)(this->gen_01_DL2_buffer->getSize()))
        this->gen_01_DL2_reader = 0;
}

number gen_01_DL2_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_DL2_buffer->getSize()) + this->gen_01_DL2_reader - ((size > this->gen_01_DL2__maxdelay ? this->gen_01_DL2__maxdelay : (size < (1 + this->gen_01_DL2_reader != this->gen_01_DL2_writer) ? 1 + this->gen_01_DL2_reader != this->gen_01_DL2_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_DL2_buffer->getSize()) + this->gen_01_DL2_reader - ((size > this->gen_01_DL2__maxdelay ? this->gen_01_DL2__maxdelay : (size < (this->gen_01_DL2_reader != this->gen_01_DL2_writer) ? this->gen_01_DL2_reader != this->gen_01_DL2_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));
    return this->gen_01_DL2_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL2_wrap)));
}

void gen_01_DL2_write(number v) {
    this->gen_01_DL2_writer = this->gen_01_DL2_reader;
    this->gen_01_DL2_buffer[(Index)this->gen_01_DL2_writer] = v;
}

number gen_01_DL2_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_DL2_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_DL2_size() {
    return this->gen_01_DL2__maxdelay;
}

void gen_01_DL3_step() {
    this->gen_01_DL3_reader++;

    if (this->gen_01_DL3_reader >= (Int)(this->gen_01_DL3_buffer->getSize()))
        this->gen_01_DL3_reader = 0;
}

number gen_01_DL3_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_DL3_buffer->getSize()) + this->gen_01_DL3_reader - ((size > this->gen_01_DL3__maxdelay ? this->gen_01_DL3__maxdelay : (size < (1 + this->gen_01_DL3_reader != this->gen_01_DL3_writer) ? 1 + this->gen_01_DL3_reader != this->gen_01_DL3_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_DL3_buffer->getSize()) + this->gen_01_DL3_reader - ((size > this->gen_01_DL3__maxdelay ? this->gen_01_DL3__maxdelay : (size < (this->gen_01_DL3_reader != this->gen_01_DL3_writer) ? this->gen_01_DL3_reader != this->gen_01_DL3_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));
    return this->gen_01_DL3_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL3_wrap)));
}

void gen_01_DL3_write(number v) {
    this->gen_01_DL3_writer = this->gen_01_DL3_reader;
    this->gen_01_DL3_buffer[(Index)this->gen_01_DL3_writer] = v;
}

number gen_01_DL3_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_DL3_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_DL3_size() {
    return this->gen_01_DL3__maxdelay;
}

void gen_01_DL4_step() {
    this->gen_01_DL4_reader++;

    if (this->gen_01_DL4_reader >= (Int)(this->gen_01_DL4_buffer->getSize()))
        this->gen_01_DL4_reader = 0;
}

number gen_01_DL4_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_DL4_buffer->getSize()) + this->gen_01_DL4_reader - ((size > this->gen_01_DL4__maxdelay ? this->gen_01_DL4__maxdelay : (size < (1 + this->gen_01_DL4_reader != this->gen_01_DL4_writer) ? 1 + this->gen_01_DL4_reader != this->gen_01_DL4_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_DL4_buffer->getSize()) + this->gen_01_DL4_reader - ((size > this->gen_01_DL4__maxdelay ? this->gen_01_DL4__maxdelay : (size < (this->gen_01_DL4_reader != this->gen_01_DL4_writer) ? this->gen_01_DL4_reader != this->gen_01_DL4_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));
    return this->gen_01_DL4_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL4_wrap)));
}

void gen_01_DL4_write(number v) {
    this->gen_01_DL4_writer = this->gen_01_DL4_reader;
    this->gen_01_DL4_buffer[(Index)this->gen_01_DL4_writer] = v;
}

number gen_01_DL4_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_DL4_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_DL4_size() {
    return this->gen_01_DL4__maxdelay;
}

void gen_01_DL5_step() {
    this->gen_01_DL5_reader++;

    if (this->gen_01_DL5_reader >= (Int)(this->gen_01_DL5_buffer->getSize()))
        this->gen_01_DL5_reader = 0;
}

number gen_01_DL5_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_DL5_buffer->getSize()) + this->gen_01_DL5_reader - ((size > this->gen_01_DL5__maxdelay ? this->gen_01_DL5__maxdelay : (size < (1 + this->gen_01_DL5_reader != this->gen_01_DL5_writer) ? 1 + this->gen_01_DL5_reader != this->gen_01_DL5_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_DL5_buffer->getSize()) + this->gen_01_DL5_reader - ((size > this->gen_01_DL5__maxdelay ? this->gen_01_DL5__maxdelay : (size < (this->gen_01_DL5_reader != this->gen_01_DL5_writer) ? this->gen_01_DL5_reader != this->gen_01_DL5_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));
    return this->gen_01_DL5_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL5_wrap)));
}

void gen_01_DL5_write(number v) {
    this->gen_01_DL5_writer = this->gen_01_DL5_reader;
    this->gen_01_DL5_buffer[(Index)this->gen_01_DL5_writer] = v;
}

number gen_01_DL5_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_DL5_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_DL5_size() {
    return this->gen_01_DL5__maxdelay;
}

void gen_01_DL6_step() {
    this->gen_01_DL6_reader++;

    if (this->gen_01_DL6_reader >= (Int)(this->gen_01_DL6_buffer->getSize()))
        this->gen_01_DL6_reader = 0;
}

number gen_01_DL6_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_DL6_buffer->getSize()) + this->gen_01_DL6_reader - ((size > this->gen_01_DL6__maxdelay ? this->gen_01_DL6__maxdelay : (size < (1 + this->gen_01_DL6_reader != this->gen_01_DL6_writer) ? 1 + this->gen_01_DL6_reader != this->gen_01_DL6_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_DL6_buffer->getSize()) + this->gen_01_DL6_reader - ((size > this->gen_01_DL6__maxdelay ? this->gen_01_DL6__maxdelay : (size < (this->gen_01_DL6_reader != this->gen_01_DL6_writer) ? this->gen_01_DL6_reader != this->gen_01_DL6_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));
    return this->gen_01_DL6_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL6_wrap)));
}

void gen_01_DL6_write(number v) {
    this->gen_01_DL6_writer = this->gen_01_DL6_reader;
    this->gen_01_DL6_buffer[(Index)this->gen_01_DL6_writer] = v;
}

number gen_01_DL6_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_DL6_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_DL6_size() {
    return this->gen_01_DL6__maxdelay;
}

void gen_01_DL7_step() {
    this->gen_01_DL7_reader++;

    if (this->gen_01_DL7_reader >= (Int)(this->gen_01_DL7_buffer->getSize()))
        this->gen_01_DL7_reader = 0;
}

number gen_01_DL7_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_DL7_buffer->getSize()) + this->gen_01_DL7_reader - ((size > this->gen_01_DL7__maxdelay ? this->gen_01_DL7__maxdelay : (size < (1 + this->gen_01_DL7_reader != this->gen_01_DL7_writer) ? 1 + this->gen_01_DL7_reader != this->gen_01_DL7_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_DL7_buffer->getSize()) + this->gen_01_DL7_reader - ((size > this->gen_01_DL7__maxdelay ? this->gen_01_DL7__maxdelay : (size < (this->gen_01_DL7_reader != this->gen_01_DL7_writer) ? this->gen_01_DL7_reader != this->gen_01_DL7_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));
    return this->gen_01_DL7_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL7_wrap)));
}

void gen_01_DL7_write(number v) {
    this->gen_01_DL7_writer = this->gen_01_DL7_reader;
    this->gen_01_DL7_buffer[(Index)this->gen_01_DL7_writer] = v;
}

number gen_01_DL7_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_DL7_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_DL7_size() {
    return this->gen_01_DL7__maxdelay;
}

void gen_01_DL8_step() {
    this->gen_01_DL8_reader++;

    if (this->gen_01_DL8_reader >= (Int)(this->gen_01_DL8_buffer->getSize()))
        this->gen_01_DL8_reader = 0;
}

number gen_01_DL8_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_DL8_buffer->getSize()) + this->gen_01_DL8_reader - ((size > this->gen_01_DL8__maxdelay ? this->gen_01_DL8__maxdelay : (size < (1 + this->gen_01_DL8_reader != this->gen_01_DL8_writer) ? 1 + this->gen_01_DL8_reader != this->gen_01_DL8_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_DL8_buffer->getSize()) + this->gen_01_DL8_reader - ((size > this->gen_01_DL8__maxdelay ? this->gen_01_DL8__maxdelay : (size < (this->gen_01_DL8_reader != this->gen_01_DL8_writer) ? this->gen_01_DL8_reader != this->gen_01_DL8_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));
    return this->gen_01_DL8_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL8_wrap)));
}

void gen_01_DL8_write(number v) {
    this->gen_01_DL8_writer = this->gen_01_DL8_reader;
    this->gen_01_DL8_buffer[(Index)this->gen_01_DL8_writer] = v;
}

number gen_01_DL8_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_DL8_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_DL8_size() {
    return this->gen_01_DL8__maxdelay;
}

void gen_01_DL9_step() {
    this->gen_01_DL9_reader++;

    if (this->gen_01_DL9_reader >= (Int)(this->gen_01_DL9_buffer->getSize()))
        this->gen_01_DL9_reader = 0;
}

number gen_01_DL9_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_DL9_buffer->getSize()) + this->gen_01_DL9_reader - ((size > this->gen_01_DL9__maxdelay ? this->gen_01_DL9__maxdelay : (size < (1 + this->gen_01_DL9_reader != this->gen_01_DL9_writer) ? 1 + this->gen_01_DL9_reader != this->gen_01_DL9_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_DL9_buffer->getSize()) + this->gen_01_DL9_reader - ((size > this->gen_01_DL9__maxdelay ? this->gen_01_DL9__maxdelay : (size < (this->gen_01_DL9_reader != this->gen_01_DL9_writer) ? this->gen_01_DL9_reader != this->gen_01_DL9_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));
    return this->gen_01_DL9_buffer->getSample(0, (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL9_wrap)));
}

void gen_01_DL9_write(number v) {
    this->gen_01_DL9_writer = this->gen_01_DL9_reader;
    this->gen_01_DL9_buffer[(Index)this->gen_01_DL9_writer] = v;
}

number gen_01_DL9_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_DL9_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_DL9_size() {
    return this->gen_01_DL9__maxdelay;
}

void gen_01_DL10_step() {
    this->gen_01_DL10_reader++;

    if (this->gen_01_DL10_reader >= (Int)(this->gen_01_DL10_buffer->getSize()))
        this->gen_01_DL10_reader = 0;
}

number gen_01_DL10_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_DL10_buffer->getSize()) + this->gen_01_DL10_reader - ((size > this->gen_01_DL10__maxdelay ? this->gen_01_DL10__maxdelay : (size < (1 + this->gen_01_DL10_reader != this->gen_01_DL10_writer) ? 1 + this->gen_01_DL10_reader != this->gen_01_DL10_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_DL10_buffer->getSize()) + this->gen_01_DL10_reader - ((size > this->gen_01_DL10__maxdelay ? this->gen_01_DL10__maxdelay : (size < (this->gen_01_DL10_reader != this->gen_01_DL10_writer) ? this->gen_01_DL10_reader != this->gen_01_DL10_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_DL10_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL10_wrap))
    );
}

void gen_01_DL10_write(number v) {
    this->gen_01_DL10_writer = this->gen_01_DL10_reader;
    this->gen_01_DL10_buffer[(Index)this->gen_01_DL10_writer] = v;
}

number gen_01_DL10_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_DL10_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_DL10_size() {
    return this->gen_01_DL10__maxdelay;
}

void gen_01_DL11_step() {
    this->gen_01_DL11_reader++;

    if (this->gen_01_DL11_reader >= (Int)(this->gen_01_DL11_buffer->getSize()))
        this->gen_01_DL11_reader = 0;
}

number gen_01_DL11_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_DL11_buffer->getSize()) + this->gen_01_DL11_reader - ((size > this->gen_01_DL11__maxdelay ? this->gen_01_DL11__maxdelay : (size < (1 + this->gen_01_DL11_reader != this->gen_01_DL11_writer) ? 1 + this->gen_01_DL11_reader != this->gen_01_DL11_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_DL11_buffer->getSize()) + this->gen_01_DL11_reader - ((size > this->gen_01_DL11__maxdelay ? this->gen_01_DL11__maxdelay : (size < (this->gen_01_DL11_reader != this->gen_01_DL11_writer) ? this->gen_01_DL11_reader != this->gen_01_DL11_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_DL11_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL11_wrap))
    );
}

void gen_01_DL11_write(number v) {
    this->gen_01_DL11_writer = this->gen_01_DL11_reader;
    this->gen_01_DL11_buffer[(Index)this->gen_01_DL11_writer] = v;
}

number gen_01_DL11_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_DL11_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_DL11_size() {
    return this->gen_01_DL11__maxdelay;
}

void gen_01_DL12_step() {
    this->gen_01_DL12_reader++;

    if (this->gen_01_DL12_reader >= (Int)(this->gen_01_DL12_buffer->getSize()))
        this->gen_01_DL12_reader = 0;
}

number gen_01_DL12_read(number size, Int interp) {
    if (interp == 0) {
        number r = (Int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Int index2 = (Int)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL12_wrap))
        ), this->gen_01_DL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL12_wrap))
        ));
    } else if (interp == 1) {
        number r = (Int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? 1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? 1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? 1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? 1 + this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_DL12_buffer->getSize()) + this->gen_01_DL12_reader - ((size > this->gen_01_DL12__maxdelay ? this->gen_01_DL12__maxdelay : (size < (this->gen_01_DL12_reader != this->gen_01_DL12_writer) ? this->gen_01_DL12_reader != this->gen_01_DL12_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_DL12_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL12_wrap))
    );
}

void gen_01_DL12_write(number v) {
    this->gen_01_DL12_writer = this->gen_01_DL12_reader;
    this->gen_01_DL12_buffer[(Index)this->gen_01_DL12_writer] = v;
}

number gen_01_DL12_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_DL12_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_DL12_size() {
    return this->gen_01_DL12__maxdelay;
}

void gen_01_DL13_step() {
    this->gen_01_DL13_reader++;

    if (this->gen_01_DL13_reader >= (Int)(this->gen_01_DL13_buffer->getSize()))
        this->gen_01_DL13_reader = 0;
}

number gen_01_DL13_read(number size, Int interp) {
    if (interp == 0) {
        number r = (Int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Int index2 = (Int)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL13_wrap))
        ), this->gen_01_DL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_DL13_wrap))
        ));
    } else if (interp == 1) {
        number r = (Int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? 1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? 1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? 1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? 1 + this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_DL13_buffer->getSize()) + this->gen_01_DL13_reader - ((size > this->gen_01_DL13__maxdelay ? this->gen_01_DL13__maxdelay : (size < (this->gen_01_DL13_reader != this->gen_01_DL13_writer) ? this->gen_01_DL13_reader != this->gen_01_DL13_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_DL13_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_DL13_wrap))
    );
}

void gen_01_DL13_write(number v) {
    this->gen_01_DL13_writer = this->gen_01_DL13_reader;
    this->gen_01_DL13_buffer[(Index)this->gen_01_DL13_writer] = v;
}

number gen_01_DL13_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_DL13_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
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

number gen_01_history_2_getvalue() {
    return this->gen_01_history_2_value;
}

void gen_01_history_2_setvalue(number val) {
    this->gen_01_history_2_value = val;
}

void gen_01_history_2_reset() {
    this->gen_01_history_2_value = 0;
}

void gen_01_history_2_init() {
    this->gen_01_history_2_value = 0;
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

number gen_01_history_5_getvalue() {
    return this->gen_01_history_5_value;
}

void gen_01_history_5_setvalue(number val) {
    this->gen_01_history_5_value = val;
}

void gen_01_history_5_reset() {
    this->gen_01_history_5_value = 0;
}

void gen_01_history_5_init() {
    this->gen_01_history_5_value = 0;
}

void gen_01_dlL1_step() {
    this->gen_01_dlL1_reader++;

    if (this->gen_01_dlL1_reader >= (Int)(this->gen_01_dlL1_buffer->getSize()))
        this->gen_01_dlL1_reader = 0;
}

number gen_01_dlL1_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_dlL1_buffer->getSize()) + this->gen_01_dlL1_reader - ((size > this->gen_01_dlL1__maxdelay ? this->gen_01_dlL1__maxdelay : (size < (1 + this->gen_01_dlL1_reader != this->gen_01_dlL1_writer) ? 1 + this->gen_01_dlL1_reader != this->gen_01_dlL1_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_dlL1_buffer->getSize()) + this->gen_01_dlL1_reader - ((size > this->gen_01_dlL1__maxdelay ? this->gen_01_dlL1__maxdelay : (size < (this->gen_01_dlL1_reader != this->gen_01_dlL1_writer) ? this->gen_01_dlL1_reader != this->gen_01_dlL1_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_dlL1_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL1_wrap))
    );
}

void gen_01_dlL1_write(number v) {
    this->gen_01_dlL1_writer = this->gen_01_dlL1_reader;
    this->gen_01_dlL1_buffer[(Index)this->gen_01_dlL1_writer] = v;
}

number gen_01_dlL1_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_dlL1_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_dlL1_size() {
    return this->gen_01_dlL1__maxdelay;
}

void gen_01_dlL2_step() {
    this->gen_01_dlL2_reader++;

    if (this->gen_01_dlL2_reader >= (Int)(this->gen_01_dlL2_buffer->getSize()))
        this->gen_01_dlL2_reader = 0;
}

number gen_01_dlL2_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_dlL2_buffer->getSize()) + this->gen_01_dlL2_reader - ((size > this->gen_01_dlL2__maxdelay ? this->gen_01_dlL2__maxdelay : (size < (1 + this->gen_01_dlL2_reader != this->gen_01_dlL2_writer) ? 1 + this->gen_01_dlL2_reader != this->gen_01_dlL2_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_dlL2_buffer->getSize()) + this->gen_01_dlL2_reader - ((size > this->gen_01_dlL2__maxdelay ? this->gen_01_dlL2__maxdelay : (size < (this->gen_01_dlL2_reader != this->gen_01_dlL2_writer) ? this->gen_01_dlL2_reader != this->gen_01_dlL2_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_dlL2_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL2_wrap))
    );
}

void gen_01_dlL2_write(number v) {
    this->gen_01_dlL2_writer = this->gen_01_dlL2_reader;
    this->gen_01_dlL2_buffer[(Index)this->gen_01_dlL2_writer] = v;
}

number gen_01_dlL2_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_dlL2_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_dlL2_size() {
    return this->gen_01_dlL2__maxdelay;
}

void gen_01_dlL3_step() {
    this->gen_01_dlL3_reader++;

    if (this->gen_01_dlL3_reader >= (Int)(this->gen_01_dlL3_buffer->getSize()))
        this->gen_01_dlL3_reader = 0;
}

number gen_01_dlL3_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_dlL3_buffer->getSize()) + this->gen_01_dlL3_reader - ((size > this->gen_01_dlL3__maxdelay ? this->gen_01_dlL3__maxdelay : (size < (1 + this->gen_01_dlL3_reader != this->gen_01_dlL3_writer) ? 1 + this->gen_01_dlL3_reader != this->gen_01_dlL3_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_dlL3_buffer->getSize()) + this->gen_01_dlL3_reader - ((size > this->gen_01_dlL3__maxdelay ? this->gen_01_dlL3__maxdelay : (size < (this->gen_01_dlL3_reader != this->gen_01_dlL3_writer) ? this->gen_01_dlL3_reader != this->gen_01_dlL3_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_dlL3_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL3_wrap))
    );
}

void gen_01_dlL3_write(number v) {
    this->gen_01_dlL3_writer = this->gen_01_dlL3_reader;
    this->gen_01_dlL3_buffer[(Index)this->gen_01_dlL3_writer] = v;
}

number gen_01_dlL3_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_dlL3_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_dlL3_size() {
    return this->gen_01_dlL3__maxdelay;
}

void gen_01_dlL4_step() {
    this->gen_01_dlL4_reader++;

    if (this->gen_01_dlL4_reader >= (Int)(this->gen_01_dlL4_buffer->getSize()))
        this->gen_01_dlL4_reader = 0;
}

number gen_01_dlL4_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_dlL4_buffer->getSize()) + this->gen_01_dlL4_reader - ((size > this->gen_01_dlL4__maxdelay ? this->gen_01_dlL4__maxdelay : (size < (1 + this->gen_01_dlL4_reader != this->gen_01_dlL4_writer) ? 1 + this->gen_01_dlL4_reader != this->gen_01_dlL4_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_dlL4_buffer->getSize()) + this->gen_01_dlL4_reader - ((size > this->gen_01_dlL4__maxdelay ? this->gen_01_dlL4__maxdelay : (size < (this->gen_01_dlL4_reader != this->gen_01_dlL4_writer) ? this->gen_01_dlL4_reader != this->gen_01_dlL4_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_dlL4_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL4_wrap))
    );
}

void gen_01_dlL4_write(number v) {
    this->gen_01_dlL4_writer = this->gen_01_dlL4_reader;
    this->gen_01_dlL4_buffer[(Index)this->gen_01_dlL4_writer] = v;
}

number gen_01_dlL4_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_dlL4_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_dlL4_size() {
    return this->gen_01_dlL4__maxdelay;
}

void gen_01_dlL5_step() {
    this->gen_01_dlL5_reader++;

    if (this->gen_01_dlL5_reader >= (Int)(this->gen_01_dlL5_buffer->getSize()))
        this->gen_01_dlL5_reader = 0;
}

number gen_01_dlL5_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_dlL5_buffer->getSize()) + this->gen_01_dlL5_reader - ((size > this->gen_01_dlL5__maxdelay ? this->gen_01_dlL5__maxdelay : (size < (1 + this->gen_01_dlL5_reader != this->gen_01_dlL5_writer) ? 1 + this->gen_01_dlL5_reader != this->gen_01_dlL5_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_dlL5_buffer->getSize()) + this->gen_01_dlL5_reader - ((size > this->gen_01_dlL5__maxdelay ? this->gen_01_dlL5__maxdelay : (size < (this->gen_01_dlL5_reader != this->gen_01_dlL5_writer) ? this->gen_01_dlL5_reader != this->gen_01_dlL5_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_dlL5_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL5_wrap))
    );
}

void gen_01_dlL5_write(number v) {
    this->gen_01_dlL5_writer = this->gen_01_dlL5_reader;
    this->gen_01_dlL5_buffer[(Index)this->gen_01_dlL5_writer] = v;
}

number gen_01_dlL5_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_dlL5_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_dlL5_size() {
    return this->gen_01_dlL5__maxdelay;
}

void gen_01_dlL6_step() {
    this->gen_01_dlL6_reader++;

    if (this->gen_01_dlL6_reader >= (Int)(this->gen_01_dlL6_buffer->getSize()))
        this->gen_01_dlL6_reader = 0;
}

number gen_01_dlL6_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_dlL6_buffer->getSize()) + this->gen_01_dlL6_reader - ((size > this->gen_01_dlL6__maxdelay ? this->gen_01_dlL6__maxdelay : (size < (1 + this->gen_01_dlL6_reader != this->gen_01_dlL6_writer) ? 1 + this->gen_01_dlL6_reader != this->gen_01_dlL6_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_dlL6_buffer->getSize()) + this->gen_01_dlL6_reader - ((size > this->gen_01_dlL6__maxdelay ? this->gen_01_dlL6__maxdelay : (size < (this->gen_01_dlL6_reader != this->gen_01_dlL6_writer) ? this->gen_01_dlL6_reader != this->gen_01_dlL6_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_dlL6_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL6_wrap))
    );
}

void gen_01_dlL6_write(number v) {
    this->gen_01_dlL6_writer = this->gen_01_dlL6_reader;
    this->gen_01_dlL6_buffer[(Index)this->gen_01_dlL6_writer] = v;
}

number gen_01_dlL6_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_dlL6_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_dlL6_size() {
    return this->gen_01_dlL6__maxdelay;
}

void gen_01_dlL7_step() {
    this->gen_01_dlL7_reader++;

    if (this->gen_01_dlL7_reader >= (Int)(this->gen_01_dlL7_buffer->getSize()))
        this->gen_01_dlL7_reader = 0;
}

number gen_01_dlL7_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_dlL7_buffer->getSize()) + this->gen_01_dlL7_reader - ((size > this->gen_01_dlL7__maxdelay ? this->gen_01_dlL7__maxdelay : (size < (1 + this->gen_01_dlL7_reader != this->gen_01_dlL7_writer) ? 1 + this->gen_01_dlL7_reader != this->gen_01_dlL7_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_dlL7_buffer->getSize()) + this->gen_01_dlL7_reader - ((size > this->gen_01_dlL7__maxdelay ? this->gen_01_dlL7__maxdelay : (size < (this->gen_01_dlL7_reader != this->gen_01_dlL7_writer) ? this->gen_01_dlL7_reader != this->gen_01_dlL7_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_dlL7_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL7_wrap))
    );
}

void gen_01_dlL7_write(number v) {
    this->gen_01_dlL7_writer = this->gen_01_dlL7_reader;
    this->gen_01_dlL7_buffer[(Index)this->gen_01_dlL7_writer] = v;
}

number gen_01_dlL7_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_dlL7_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_dlL7_size() {
    return this->gen_01_dlL7__maxdelay;
}

void gen_01_dlL8_step() {
    this->gen_01_dlL8_reader++;

    if (this->gen_01_dlL8_reader >= (Int)(this->gen_01_dlL8_buffer->getSize()))
        this->gen_01_dlL8_reader = 0;
}

number gen_01_dlL8_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_dlL8_buffer->getSize()) + this->gen_01_dlL8_reader - ((size > this->gen_01_dlL8__maxdelay ? this->gen_01_dlL8__maxdelay : (size < (1 + this->gen_01_dlL8_reader != this->gen_01_dlL8_writer) ? 1 + this->gen_01_dlL8_reader != this->gen_01_dlL8_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_dlL8_buffer->getSize()) + this->gen_01_dlL8_reader - ((size > this->gen_01_dlL8__maxdelay ? this->gen_01_dlL8__maxdelay : (size < (this->gen_01_dlL8_reader != this->gen_01_dlL8_writer) ? this->gen_01_dlL8_reader != this->gen_01_dlL8_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_dlL8_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL8_wrap))
    );
}

void gen_01_dlL8_write(number v) {
    this->gen_01_dlL8_writer = this->gen_01_dlL8_reader;
    this->gen_01_dlL8_buffer[(Index)this->gen_01_dlL8_writer] = v;
}

number gen_01_dlL8_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_dlL8_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_dlL8_size() {
    return this->gen_01_dlL8__maxdelay;
}

void gen_01_dlL9_step() {
    this->gen_01_dlL9_reader++;

    if (this->gen_01_dlL9_reader >= (Int)(this->gen_01_dlL9_buffer->getSize()))
        this->gen_01_dlL9_reader = 0;
}

number gen_01_dlL9_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_dlL9_buffer->getSize()) + this->gen_01_dlL9_reader - ((size > this->gen_01_dlL9__maxdelay ? this->gen_01_dlL9__maxdelay : (size < (1 + this->gen_01_dlL9_reader != this->gen_01_dlL9_writer) ? 1 + this->gen_01_dlL9_reader != this->gen_01_dlL9_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_dlL9_buffer->getSize()) + this->gen_01_dlL9_reader - ((size > this->gen_01_dlL9__maxdelay ? this->gen_01_dlL9__maxdelay : (size < (this->gen_01_dlL9_reader != this->gen_01_dlL9_writer) ? this->gen_01_dlL9_reader != this->gen_01_dlL9_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_dlL9_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL9_wrap))
    );
}

void gen_01_dlL9_write(number v) {
    this->gen_01_dlL9_writer = this->gen_01_dlL9_reader;
    this->gen_01_dlL9_buffer[(Index)this->gen_01_dlL9_writer] = v;
}

number gen_01_dlL9_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_dlL9_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_dlL9_size() {
    return this->gen_01_dlL9__maxdelay;
}

void gen_01_dlL10_step() {
    this->gen_01_dlL10_reader++;

    if (this->gen_01_dlL10_reader >= (Int)(this->gen_01_dlL10_buffer->getSize()))
        this->gen_01_dlL10_reader = 0;
}

number gen_01_dlL10_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_dlL10_buffer->getSize()) + this->gen_01_dlL10_reader - ((size > this->gen_01_dlL10__maxdelay ? this->gen_01_dlL10__maxdelay : (size < (1 + this->gen_01_dlL10_reader != this->gen_01_dlL10_writer) ? 1 + this->gen_01_dlL10_reader != this->gen_01_dlL10_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_dlL10_buffer->getSize()) + this->gen_01_dlL10_reader - ((size > this->gen_01_dlL10__maxdelay ? this->gen_01_dlL10__maxdelay : (size < (this->gen_01_dlL10_reader != this->gen_01_dlL10_writer) ? this->gen_01_dlL10_reader != this->gen_01_dlL10_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_dlL10_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL10_wrap))
    );
}

void gen_01_dlL10_write(number v) {
    this->gen_01_dlL10_writer = this->gen_01_dlL10_reader;
    this->gen_01_dlL10_buffer[(Index)this->gen_01_dlL10_writer] = v;
}

number gen_01_dlL10_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_dlL10_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_dlL10_size() {
    return this->gen_01_dlL10__maxdelay;
}

void gen_01_dlL11_step() {
    this->gen_01_dlL11_reader++;

    if (this->gen_01_dlL11_reader >= (Int)(this->gen_01_dlL11_buffer->getSize()))
        this->gen_01_dlL11_reader = 0;
}

number gen_01_dlL11_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_01_dlL11_buffer->getSize()) + this->gen_01_dlL11_reader - ((size > this->gen_01_dlL11__maxdelay ? this->gen_01_dlL11__maxdelay : (size < (1 + this->gen_01_dlL11_reader != this->gen_01_dlL11_writer) ? 1 + this->gen_01_dlL11_reader != this->gen_01_dlL11_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_dlL11_buffer->getSize()) + this->gen_01_dlL11_reader - ((size > this->gen_01_dlL11__maxdelay ? this->gen_01_dlL11__maxdelay : (size < (this->gen_01_dlL11_reader != this->gen_01_dlL11_writer) ? this->gen_01_dlL11_reader != this->gen_01_dlL11_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_dlL11_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL11_wrap))
    );
}

void gen_01_dlL11_write(number v) {
    this->gen_01_dlL11_writer = this->gen_01_dlL11_reader;
    this->gen_01_dlL11_buffer[(Index)this->gen_01_dlL11_writer] = v;
}

number gen_01_dlL11_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_dlL11_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_dlL11_size() {
    return this->gen_01_dlL11__maxdelay;
}

void gen_01_dlL12_step() {
    this->gen_01_dlL12_reader++;

    if (this->gen_01_dlL12_reader >= (Int)(this->gen_01_dlL12_buffer->getSize()))
        this->gen_01_dlL12_reader = 0;
}

number gen_01_dlL12_read(number size, Int interp) {
    if (interp == 0) {
        number r = (Int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Int index2 = (Int)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL12_wrap))
        ), this->gen_01_dlL12_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL12_wrap))
        ));
    } else if (interp == 1) {
        number r = (Int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? 1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? 1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? 1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? 1 + this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_dlL12_buffer->getSize()) + this->gen_01_dlL12_reader - ((size > this->gen_01_dlL12__maxdelay ? this->gen_01_dlL12__maxdelay : (size < (this->gen_01_dlL12_reader != this->gen_01_dlL12_writer) ? this->gen_01_dlL12_reader != this->gen_01_dlL12_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_dlL12_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL12_wrap))
    );
}

void gen_01_dlL12_write(number v) {
    this->gen_01_dlL12_writer = this->gen_01_dlL12_reader;
    this->gen_01_dlL12_buffer[(Index)this->gen_01_dlL12_writer] = v;
}

number gen_01_dlL12_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_dlL12_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_01_dlL12_size() {
    return this->gen_01_dlL12__maxdelay;
}

void gen_01_dlL13_step() {
    this->gen_01_dlL13_reader++;

    if (this->gen_01_dlL13_reader >= (Int)(this->gen_01_dlL13_buffer->getSize()))
        this->gen_01_dlL13_reader = 0;
}

number gen_01_dlL13_read(number size, Int interp) {
    if (interp == 0) {
        number r = (Int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Int index2 = (Int)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL13_wrap))
        ), this->gen_01_dlL13_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_dlL13_wrap))
        ));
    } else if (interp == 1) {
        number r = (Int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? 1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? 1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? 1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? 1 + this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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
        number r = (Int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_01_dlL13_buffer->getSize()) + this->gen_01_dlL13_reader - ((size > this->gen_01_dlL13__maxdelay ? this->gen_01_dlL13__maxdelay : (size < (this->gen_01_dlL13_reader != this->gen_01_dlL13_writer) ? this->gen_01_dlL13_reader != this->gen_01_dlL13_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_dlL13_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_dlL13_wrap))
    );
}

void gen_01_dlL13_write(number v) {
    this->gen_01_dlL13_writer = this->gen_01_dlL13_reader;
    this->gen_01_dlL13_buffer[(Index)this->gen_01_dlL13_writer] = v;
}

number gen_01_dlL13_next(number v, Int size) {
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
        sizeInSamples = this->gen_01_dlL13_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
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

number gen_01_history_9_getvalue() {
    return this->gen_01_history_9_value;
}

void gen_01_history_9_setvalue(number val) {
    this->gen_01_history_9_value = val;
}

void gen_01_history_9_reset() {
    this->gen_01_history_9_value = 0;
}

void gen_01_history_9_init() {
    this->gen_01_history_9_value = 0;
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

number gen_01_slide_0_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_01_slide_0_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(2000)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(1500)));
    this->gen_01_slide_0_prev = this->gen_01_slide_0_prev + ((x > this->gen_01_slide_0_prev ? iup : idown)) * temp;
    return this->gen_01_slide_0_prev;
}

void gen_01_slide_0_reset() {
    this->gen_01_slide_0_prev = 0;
}

number gen_01_slide_2_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_01_slide_2_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(2000)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(2000)));
    this->gen_01_slide_2_prev = this->gen_01_slide_2_prev + ((x > this->gen_01_slide_2_prev ? iup : idown)) * temp;
    return this->gen_01_slide_2_prev;
}

void gen_01_slide_2_reset() {
    this->gen_01_slide_2_prev = 0;
}

number gen_01_phasor_6_next(number freq, number reset) {
    RNBO_UNUSED(reset);
    number pincr = freq * this->gen_01_phasor_6_conv;

    if (this->gen_01_phasor_6_currentPhase < 0.)
        this->gen_01_phasor_6_currentPhase = 1. + this->gen_01_phasor_6_currentPhase;

    if (this->gen_01_phasor_6_currentPhase > 1.)
        this->gen_01_phasor_6_currentPhase = this->gen_01_phasor_6_currentPhase - 1.;

    number tmp = this->gen_01_phasor_6_currentPhase;
    this->gen_01_phasor_6_currentPhase += pincr;
    return tmp;
}

void gen_01_phasor_6_reset() {
    this->gen_01_phasor_6_currentPhase = 0;
}

void gen_01_phasor_6_dspsetup() {
    this->gen_01_phasor_6_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

number gen_01_cycle_8_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_8_ph_conv;

    if (this->gen_01_cycle_8_ph_currentPhase < 0.)
        this->gen_01_cycle_8_ph_currentPhase = 1. + this->gen_01_cycle_8_ph_currentPhase;

    if (this->gen_01_cycle_8_ph_currentPhase > 1.)
        this->gen_01_cycle_8_ph_currentPhase = this->gen_01_cycle_8_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_8_ph_currentPhase;
    this->gen_01_cycle_8_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_8_ph_reset() {
    this->gen_01_cycle_8_ph_currentPhase = 0;
}

void gen_01_cycle_8_ph_dspsetup() {
    this->gen_01_cycle_8_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_8_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_8_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_8_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_8_dspsetup() {
    this->gen_01_cycle_8_phasei = 0;
    this->gen_01_cycle_8_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_01_cycle_8_wrap = (Int)(this->gen_01_cycle_8_buffer->getSize()) - 1;
}

void gen_01_cycle_8_reset() {
    this->gen_01_cycle_8_phasei = 0;
}

void gen_01_cycle_8_bufferUpdated() {
    this->gen_01_cycle_8_wrap = (Int)(this->gen_01_cycle_8_buffer->getSize()) - 1;
}

number gen_01_cycle_13_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_13_ph_conv;

    if (this->gen_01_cycle_13_ph_currentPhase < 0.)
        this->gen_01_cycle_13_ph_currentPhase = 1. + this->gen_01_cycle_13_ph_currentPhase;

    if (this->gen_01_cycle_13_ph_currentPhase > 1.)
        this->gen_01_cycle_13_ph_currentPhase = this->gen_01_cycle_13_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_13_ph_currentPhase;
    this->gen_01_cycle_13_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_13_ph_reset() {
    this->gen_01_cycle_13_ph_currentPhase = 0;
}

void gen_01_cycle_13_ph_dspsetup() {
    this->gen_01_cycle_13_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_13_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_13_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_13_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_13_dspsetup() {
    this->gen_01_cycle_13_phasei = 0;
    this->gen_01_cycle_13_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_01_cycle_13_wrap = (Int)(this->gen_01_cycle_13_buffer->getSize()) - 1;
}

void gen_01_cycle_13_reset() {
    this->gen_01_cycle_13_phasei = 0;
}

void gen_01_cycle_13_bufferUpdated() {
    this->gen_01_cycle_13_wrap = (Int)(this->gen_01_cycle_13_buffer->getSize()) - 1;
}

number gen_01_cycle_18_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_18_ph_conv;

    if (this->gen_01_cycle_18_ph_currentPhase < 0.)
        this->gen_01_cycle_18_ph_currentPhase = 1. + this->gen_01_cycle_18_ph_currentPhase;

    if (this->gen_01_cycle_18_ph_currentPhase > 1.)
        this->gen_01_cycle_18_ph_currentPhase = this->gen_01_cycle_18_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_18_ph_currentPhase;
    this->gen_01_cycle_18_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_18_ph_reset() {
    this->gen_01_cycle_18_ph_currentPhase = 0;
}

void gen_01_cycle_18_ph_dspsetup() {
    this->gen_01_cycle_18_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_18_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_18_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_18_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_18_dspsetup() {
    this->gen_01_cycle_18_phasei = 0;
    this->gen_01_cycle_18_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_01_cycle_18_wrap = (Int)(this->gen_01_cycle_18_buffer->getSize()) - 1;
}

void gen_01_cycle_18_reset() {
    this->gen_01_cycle_18_phasei = 0;
}

void gen_01_cycle_18_bufferUpdated() {
    this->gen_01_cycle_18_wrap = (Int)(this->gen_01_cycle_18_buffer->getSize()) - 1;
}

number gen_01_cycle_23_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_23_ph_conv;

    if (this->gen_01_cycle_23_ph_currentPhase < 0.)
        this->gen_01_cycle_23_ph_currentPhase = 1. + this->gen_01_cycle_23_ph_currentPhase;

    if (this->gen_01_cycle_23_ph_currentPhase > 1.)
        this->gen_01_cycle_23_ph_currentPhase = this->gen_01_cycle_23_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_23_ph_currentPhase;
    this->gen_01_cycle_23_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_23_ph_reset() {
    this->gen_01_cycle_23_ph_currentPhase = 0;
}

void gen_01_cycle_23_ph_dspsetup() {
    this->gen_01_cycle_23_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_23_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_23_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_23_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_23_dspsetup() {
    this->gen_01_cycle_23_phasei = 0;
    this->gen_01_cycle_23_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_01_cycle_23_wrap = (Int)(this->gen_01_cycle_23_buffer->getSize()) - 1;
}

void gen_01_cycle_23_reset() {
    this->gen_01_cycle_23_phasei = 0;
}

void gen_01_cycle_23_bufferUpdated() {
    this->gen_01_cycle_23_wrap = (Int)(this->gen_01_cycle_23_buffer->getSize()) - 1;
}

number gen_01_cycle_28_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_28_ph_conv;

    if (this->gen_01_cycle_28_ph_currentPhase < 0.)
        this->gen_01_cycle_28_ph_currentPhase = 1. + this->gen_01_cycle_28_ph_currentPhase;

    if (this->gen_01_cycle_28_ph_currentPhase > 1.)
        this->gen_01_cycle_28_ph_currentPhase = this->gen_01_cycle_28_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_28_ph_currentPhase;
    this->gen_01_cycle_28_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_28_ph_reset() {
    this->gen_01_cycle_28_ph_currentPhase = 0;
}

void gen_01_cycle_28_ph_dspsetup() {
    this->gen_01_cycle_28_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_28_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_28_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_28_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_28_dspsetup() {
    this->gen_01_cycle_28_phasei = 0;
    this->gen_01_cycle_28_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_01_cycle_28_wrap = (Int)(this->gen_01_cycle_28_buffer->getSize()) - 1;
}

void gen_01_cycle_28_reset() {
    this->gen_01_cycle_28_phasei = 0;
}

void gen_01_cycle_28_bufferUpdated() {
    this->gen_01_cycle_28_wrap = (Int)(this->gen_01_cycle_28_buffer->getSize()) - 1;
}

number gen_01_cycle_33_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_33_ph_conv;

    if (this->gen_01_cycle_33_ph_currentPhase < 0.)
        this->gen_01_cycle_33_ph_currentPhase = 1. + this->gen_01_cycle_33_ph_currentPhase;

    if (this->gen_01_cycle_33_ph_currentPhase > 1.)
        this->gen_01_cycle_33_ph_currentPhase = this->gen_01_cycle_33_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_33_ph_currentPhase;
    this->gen_01_cycle_33_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_33_ph_reset() {
    this->gen_01_cycle_33_ph_currentPhase = 0;
}

void gen_01_cycle_33_ph_dspsetup() {
    this->gen_01_cycle_33_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_33_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_33_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_33_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_33_dspsetup() {
    this->gen_01_cycle_33_phasei = 0;
    this->gen_01_cycle_33_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_01_cycle_33_wrap = (Int)(this->gen_01_cycle_33_buffer->getSize()) - 1;
}

void gen_01_cycle_33_reset() {
    this->gen_01_cycle_33_phasei = 0;
}

void gen_01_cycle_33_bufferUpdated() {
    this->gen_01_cycle_33_wrap = (Int)(this->gen_01_cycle_33_buffer->getSize()) - 1;
}

number gen_01_cycle_38_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_38_ph_conv;

    if (this->gen_01_cycle_38_ph_currentPhase < 0.)
        this->gen_01_cycle_38_ph_currentPhase = 1. + this->gen_01_cycle_38_ph_currentPhase;

    if (this->gen_01_cycle_38_ph_currentPhase > 1.)
        this->gen_01_cycle_38_ph_currentPhase = this->gen_01_cycle_38_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_38_ph_currentPhase;
    this->gen_01_cycle_38_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_38_ph_reset() {
    this->gen_01_cycle_38_ph_currentPhase = 0;
}

void gen_01_cycle_38_ph_dspsetup() {
    this->gen_01_cycle_38_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_38_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_38_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_38_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_38_dspsetup() {
    this->gen_01_cycle_38_phasei = 0;
    this->gen_01_cycle_38_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_01_cycle_38_wrap = (Int)(this->gen_01_cycle_38_buffer->getSize()) - 1;
}

void gen_01_cycle_38_reset() {
    this->gen_01_cycle_38_phasei = 0;
}

void gen_01_cycle_38_bufferUpdated() {
    this->gen_01_cycle_38_wrap = (Int)(this->gen_01_cycle_38_buffer->getSize()) - 1;
}

number gen_01_cycle_43_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_01_cycle_43_ph_conv;

    if (this->gen_01_cycle_43_ph_currentPhase < 0.)
        this->gen_01_cycle_43_ph_currentPhase = 1. + this->gen_01_cycle_43_ph_currentPhase;

    if (this->gen_01_cycle_43_ph_currentPhase > 1.)
        this->gen_01_cycle_43_ph_currentPhase = this->gen_01_cycle_43_ph_currentPhase - 1.;

    number tmp = this->gen_01_cycle_43_ph_currentPhase;
    this->gen_01_cycle_43_ph_currentPhase += pincr;
    return tmp;
}

void gen_01_cycle_43_ph_reset() {
    this->gen_01_cycle_43_ph_currentPhase = 0;
}

void gen_01_cycle_43_ph_dspsetup() {
    this->gen_01_cycle_43_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_01_cycle_43_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_01_cycle_43_buffer[(Index)idx];
        number y1 = this->gen_01_cycle_43_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_01_cycle_43_dspsetup() {
    this->gen_01_cycle_43_phasei = 0;
    this->gen_01_cycle_43_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_01_cycle_43_wrap = (Int)(this->gen_01_cycle_43_buffer->getSize()) - 1;
}

void gen_01_cycle_43_reset() {
    this->gen_01_cycle_43_phasei = 0;
}

void gen_01_cycle_43_bufferUpdated() {
    this->gen_01_cycle_43_wrap = (Int)(this->gen_01_cycle_43_buffer->getSize()) - 1;
}

void gen_01_dspsetup(bool force) {
    if ((bool)(this->gen_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gen_01_setupDone = true;
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
    this->gen_01_phasor_6_dspsetup();
    this->gen_01_cycle_8_ph_dspsetup();
    this->gen_01_cycle_8_dspsetup();
    this->gen_01_cycle_13_ph_dspsetup();
    this->gen_01_cycle_13_dspsetup();
    this->gen_01_cycle_18_ph_dspsetup();
    this->gen_01_cycle_18_dspsetup();
    this->gen_01_cycle_23_ph_dspsetup();
    this->gen_01_cycle_23_dspsetup();
    this->gen_01_cycle_28_ph_dspsetup();
    this->gen_01_cycle_28_dspsetup();
    this->gen_01_cycle_33_ph_dspsetup();
    this->gen_01_cycle_33_dspsetup();
    this->gen_01_cycle_38_ph_dspsetup();
    this->gen_01_cycle_38_dspsetup();
    this->gen_01_cycle_43_ph_dspsetup();
    this->gen_01_cycle_43_dspsetup();
}

void gen_02_delay_1_step() {
    this->gen_02_delay_1_reader++;

    if (this->gen_02_delay_1_reader >= (Int)(this->gen_02_delay_1_buffer->getSize()))
        this->gen_02_delay_1_reader = 0;
}

number gen_02_delay_1_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_1_buffer->getSize()) + this->gen_02_delay_1_reader - ((size > this->gen_02_delay_1__maxdelay ? this->gen_02_delay_1__maxdelay : (size < (1 + this->gen_02_delay_1_reader != this->gen_02_delay_1_writer) ? 1 + this->gen_02_delay_1_reader != this->gen_02_delay_1_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_1_buffer->getSize()) + this->gen_02_delay_1_reader - ((size > this->gen_02_delay_1__maxdelay ? this->gen_02_delay_1__maxdelay : (size < (this->gen_02_delay_1_reader != this->gen_02_delay_1_writer) ? this->gen_02_delay_1_reader != this->gen_02_delay_1_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_1_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_1_wrap))
    );
}

void gen_02_delay_1_write(number v) {
    this->gen_02_delay_1_writer = this->gen_02_delay_1_reader;
    this->gen_02_delay_1_buffer[(Index)this->gen_02_delay_1_writer] = v;
}

number gen_02_delay_1_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_1_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_1_size() {
    return this->gen_02_delay_1__maxdelay;
}

void gen_02_delay_2_step() {
    this->gen_02_delay_2_reader++;

    if (this->gen_02_delay_2_reader >= (Int)(this->gen_02_delay_2_buffer->getSize()))
        this->gen_02_delay_2_reader = 0;
}

number gen_02_delay_2_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_2_buffer->getSize()) + this->gen_02_delay_2_reader - ((size > this->gen_02_delay_2__maxdelay ? this->gen_02_delay_2__maxdelay : (size < (1 + this->gen_02_delay_2_reader != this->gen_02_delay_2_writer) ? 1 + this->gen_02_delay_2_reader != this->gen_02_delay_2_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_2_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_2_wrap))
            ), this->gen_02_delay_2_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_2_wrap))
            ), this->gen_02_delay_2_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_2_wrap))
            ), this->gen_02_delay_2_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_2_wrap))
            ));
        }
    }

    number r = (Int)(this->gen_02_delay_2_buffer->getSize()) + this->gen_02_delay_2_reader - ((size > this->gen_02_delay_2__maxdelay ? this->gen_02_delay_2__maxdelay : (size < (this->gen_02_delay_2_reader != this->gen_02_delay_2_writer) ? this->gen_02_delay_2_reader != this->gen_02_delay_2_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_2_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_2_wrap))
    );
}

void gen_02_delay_2_write(number v) {
    this->gen_02_delay_2_writer = this->gen_02_delay_2_reader;
    this->gen_02_delay_2_buffer[(Index)this->gen_02_delay_2_writer] = v;
}

number gen_02_delay_2_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_2_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_2_size() {
    return this->gen_02_delay_2__maxdelay;
}

void gen_02_delay_3_step() {
    this->gen_02_delay_3_reader++;

    if (this->gen_02_delay_3_reader >= (Int)(this->gen_02_delay_3_buffer->getSize()))
        this->gen_02_delay_3_reader = 0;
}

number gen_02_delay_3_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_3_buffer->getSize()) + this->gen_02_delay_3_reader - ((size > this->gen_02_delay_3__maxdelay ? this->gen_02_delay_3__maxdelay : (size < (1 + this->gen_02_delay_3_reader != this->gen_02_delay_3_writer) ? 1 + this->gen_02_delay_3_reader != this->gen_02_delay_3_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_3_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_3_wrap))
            ), this->gen_02_delay_3_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_3_wrap))
            ), this->gen_02_delay_3_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_3_wrap))
            ), this->gen_02_delay_3_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_3_wrap))
            ));
        }
    }

    number r = (Int)(this->gen_02_delay_3_buffer->getSize()) + this->gen_02_delay_3_reader - ((size > this->gen_02_delay_3__maxdelay ? this->gen_02_delay_3__maxdelay : (size < (this->gen_02_delay_3_reader != this->gen_02_delay_3_writer) ? this->gen_02_delay_3_reader != this->gen_02_delay_3_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_3_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_3_wrap))
    );
}

void gen_02_delay_3_write(number v) {
    this->gen_02_delay_3_writer = this->gen_02_delay_3_reader;
    this->gen_02_delay_3_buffer[(Index)this->gen_02_delay_3_writer] = v;
}

number gen_02_delay_3_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_3_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_3_size() {
    return this->gen_02_delay_3__maxdelay;
}

void gen_02_delay_4_step() {
    this->gen_02_delay_4_reader++;

    if (this->gen_02_delay_4_reader >= (Int)(this->gen_02_delay_4_buffer->getSize()))
        this->gen_02_delay_4_reader = 0;
}

number gen_02_delay_4_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_4_buffer->getSize()) + this->gen_02_delay_4_reader - ((size > this->gen_02_delay_4__maxdelay ? this->gen_02_delay_4__maxdelay : (size < (1 + this->gen_02_delay_4_reader != this->gen_02_delay_4_writer) ? 1 + this->gen_02_delay_4_reader != this->gen_02_delay_4_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_4_buffer->getSize()) + this->gen_02_delay_4_reader - ((size > this->gen_02_delay_4__maxdelay ? this->gen_02_delay_4__maxdelay : (size < (this->gen_02_delay_4_reader != this->gen_02_delay_4_writer) ? this->gen_02_delay_4_reader != this->gen_02_delay_4_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_4_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_4_wrap))
    );
}

void gen_02_delay_4_write(number v) {
    this->gen_02_delay_4_writer = this->gen_02_delay_4_reader;
    this->gen_02_delay_4_buffer[(Index)this->gen_02_delay_4_writer] = v;
}

number gen_02_delay_4_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_4_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_4_size() {
    return this->gen_02_delay_4__maxdelay;
}

void gen_02_delay_5_step() {
    this->gen_02_delay_5_reader++;

    if (this->gen_02_delay_5_reader >= (Int)(this->gen_02_delay_5_buffer->getSize()))
        this->gen_02_delay_5_reader = 0;
}

number gen_02_delay_5_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_5_buffer->getSize()) + this->gen_02_delay_5_reader - ((size > this->gen_02_delay_5__maxdelay ? this->gen_02_delay_5__maxdelay : (size < (1 + this->gen_02_delay_5_reader != this->gen_02_delay_5_writer) ? 1 + this->gen_02_delay_5_reader != this->gen_02_delay_5_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_5_buffer->getSize()) + this->gen_02_delay_5_reader - ((size > this->gen_02_delay_5__maxdelay ? this->gen_02_delay_5__maxdelay : (size < (this->gen_02_delay_5_reader != this->gen_02_delay_5_writer) ? this->gen_02_delay_5_reader != this->gen_02_delay_5_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_5_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_5_wrap))
    );
}

void gen_02_delay_5_write(number v) {
    this->gen_02_delay_5_writer = this->gen_02_delay_5_reader;
    this->gen_02_delay_5_buffer[(Index)this->gen_02_delay_5_writer] = v;
}

number gen_02_delay_5_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_5_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_5_size() {
    return this->gen_02_delay_5__maxdelay;
}

void gen_02_delay_6_step() {
    this->gen_02_delay_6_reader++;

    if (this->gen_02_delay_6_reader >= (Int)(this->gen_02_delay_6_buffer->getSize()))
        this->gen_02_delay_6_reader = 0;
}

number gen_02_delay_6_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_6_buffer->getSize()) + this->gen_02_delay_6_reader - ((size > this->gen_02_delay_6__maxdelay ? this->gen_02_delay_6__maxdelay : (size < (1 + this->gen_02_delay_6_reader != this->gen_02_delay_6_writer) ? 1 + this->gen_02_delay_6_reader != this->gen_02_delay_6_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_6_buffer->getSize()) + this->gen_02_delay_6_reader - ((size > this->gen_02_delay_6__maxdelay ? this->gen_02_delay_6__maxdelay : (size < (this->gen_02_delay_6_reader != this->gen_02_delay_6_writer) ? this->gen_02_delay_6_reader != this->gen_02_delay_6_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_6_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_6_wrap))
    );
}

void gen_02_delay_6_write(number v) {
    this->gen_02_delay_6_writer = this->gen_02_delay_6_reader;
    this->gen_02_delay_6_buffer[(Index)this->gen_02_delay_6_writer] = v;
}

number gen_02_delay_6_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_6_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_6_size() {
    return this->gen_02_delay_6__maxdelay;
}

void gen_02_delay_7_step() {
    this->gen_02_delay_7_reader++;

    if (this->gen_02_delay_7_reader >= (Int)(this->gen_02_delay_7_buffer->getSize()))
        this->gen_02_delay_7_reader = 0;
}

number gen_02_delay_7_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_7_buffer->getSize()) + this->gen_02_delay_7_reader - ((size > this->gen_02_delay_7__maxdelay ? this->gen_02_delay_7__maxdelay : (size < (1 + this->gen_02_delay_7_reader != this->gen_02_delay_7_writer) ? 1 + this->gen_02_delay_7_reader != this->gen_02_delay_7_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_7_buffer->getSize()) + this->gen_02_delay_7_reader - ((size > this->gen_02_delay_7__maxdelay ? this->gen_02_delay_7__maxdelay : (size < (this->gen_02_delay_7_reader != this->gen_02_delay_7_writer) ? this->gen_02_delay_7_reader != this->gen_02_delay_7_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_7_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_7_wrap))
    );
}

void gen_02_delay_7_write(number v) {
    this->gen_02_delay_7_writer = this->gen_02_delay_7_reader;
    this->gen_02_delay_7_buffer[(Index)this->gen_02_delay_7_writer] = v;
}

number gen_02_delay_7_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_7_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_7_size() {
    return this->gen_02_delay_7__maxdelay;
}

void gen_02_delay_8_step() {
    this->gen_02_delay_8_reader++;

    if (this->gen_02_delay_8_reader >= (Int)(this->gen_02_delay_8_buffer->getSize()))
        this->gen_02_delay_8_reader = 0;
}

number gen_02_delay_8_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_8_buffer->getSize()) + this->gen_02_delay_8_reader - ((size > this->gen_02_delay_8__maxdelay ? this->gen_02_delay_8__maxdelay : (size < (1 + this->gen_02_delay_8_reader != this->gen_02_delay_8_writer) ? 1 + this->gen_02_delay_8_reader != this->gen_02_delay_8_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_8_buffer->getSize()) + this->gen_02_delay_8_reader - ((size > this->gen_02_delay_8__maxdelay ? this->gen_02_delay_8__maxdelay : (size < (this->gen_02_delay_8_reader != this->gen_02_delay_8_writer) ? this->gen_02_delay_8_reader != this->gen_02_delay_8_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_8_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_8_wrap))
    );
}

void gen_02_delay_8_write(number v) {
    this->gen_02_delay_8_writer = this->gen_02_delay_8_reader;
    this->gen_02_delay_8_buffer[(Index)this->gen_02_delay_8_writer] = v;
}

number gen_02_delay_8_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_8_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_8_size() {
    return this->gen_02_delay_8__maxdelay;
}

void gen_02_delay_9_step() {
    this->gen_02_delay_9_reader++;

    if (this->gen_02_delay_9_reader >= (Int)(this->gen_02_delay_9_buffer->getSize()))
        this->gen_02_delay_9_reader = 0;
}

number gen_02_delay_9_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_9_buffer->getSize()) + this->gen_02_delay_9_reader - ((size > this->gen_02_delay_9__maxdelay ? this->gen_02_delay_9__maxdelay : (size < (1 + this->gen_02_delay_9_reader != this->gen_02_delay_9_writer) ? 1 + this->gen_02_delay_9_reader != this->gen_02_delay_9_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_9_buffer->getSize()) + this->gen_02_delay_9_reader - ((size > this->gen_02_delay_9__maxdelay ? this->gen_02_delay_9__maxdelay : (size < (this->gen_02_delay_9_reader != this->gen_02_delay_9_writer) ? this->gen_02_delay_9_reader != this->gen_02_delay_9_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_9_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_9_wrap))
    );
}

void gen_02_delay_9_write(number v) {
    this->gen_02_delay_9_writer = this->gen_02_delay_9_reader;
    this->gen_02_delay_9_buffer[(Index)this->gen_02_delay_9_writer] = v;
}

number gen_02_delay_9_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_9_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_9_size() {
    return this->gen_02_delay_9__maxdelay;
}

number gen_02_history_10_getvalue() {
    return this->gen_02_history_10_value;
}

void gen_02_history_10_setvalue(number val) {
    this->gen_02_history_10_value = val;
}

void gen_02_history_10_reset() {
    this->gen_02_history_10_value = 0;
}

void gen_02_history_10_init() {
    this->gen_02_history_10_value = 0;
}

void gen_02_delay_11_step() {
    this->gen_02_delay_11_reader++;

    if (this->gen_02_delay_11_reader >= (Int)(this->gen_02_delay_11_buffer->getSize()))
        this->gen_02_delay_11_reader = 0;
}

number gen_02_delay_11_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_11_buffer->getSize()) + this->gen_02_delay_11_reader - ((size > this->gen_02_delay_11__maxdelay ? this->gen_02_delay_11__maxdelay : (size < (1 + this->gen_02_delay_11_reader != this->gen_02_delay_11_writer) ? 1 + this->gen_02_delay_11_reader != this->gen_02_delay_11_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_11_buffer->getSize()) + this->gen_02_delay_11_reader - ((size > this->gen_02_delay_11__maxdelay ? this->gen_02_delay_11__maxdelay : (size < (this->gen_02_delay_11_reader != this->gen_02_delay_11_writer) ? this->gen_02_delay_11_reader != this->gen_02_delay_11_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_11_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_11_wrap))
    );
}

void gen_02_delay_11_write(number v) {
    this->gen_02_delay_11_writer = this->gen_02_delay_11_reader;
    this->gen_02_delay_11_buffer[(Index)this->gen_02_delay_11_writer] = v;
}

number gen_02_delay_11_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_11_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_11_size() {
    return this->gen_02_delay_11__maxdelay;
}

void gen_02_delay_12_step() {
    this->gen_02_delay_12_reader++;

    if (this->gen_02_delay_12_reader >= (Int)(this->gen_02_delay_12_buffer->getSize()))
        this->gen_02_delay_12_reader = 0;
}

number gen_02_delay_12_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_12_buffer->getSize()) + this->gen_02_delay_12_reader - ((size > this->gen_02_delay_12__maxdelay ? this->gen_02_delay_12__maxdelay : (size < (1 + this->gen_02_delay_12_reader != this->gen_02_delay_12_writer) ? 1 + this->gen_02_delay_12_reader != this->gen_02_delay_12_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_12_buffer->getSize()) + this->gen_02_delay_12_reader - ((size > this->gen_02_delay_12__maxdelay ? this->gen_02_delay_12__maxdelay : (size < (this->gen_02_delay_12_reader != this->gen_02_delay_12_writer) ? this->gen_02_delay_12_reader != this->gen_02_delay_12_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_12_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_12_wrap))
    );
}

void gen_02_delay_12_write(number v) {
    this->gen_02_delay_12_writer = this->gen_02_delay_12_reader;
    this->gen_02_delay_12_buffer[(Index)this->gen_02_delay_12_writer] = v;
}

number gen_02_delay_12_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_12_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_12_size() {
    return this->gen_02_delay_12__maxdelay;
}

void gen_02_delay_13_step() {
    this->gen_02_delay_13_reader++;

    if (this->gen_02_delay_13_reader >= (Int)(this->gen_02_delay_13_buffer->getSize()))
        this->gen_02_delay_13_reader = 0;
}

number gen_02_delay_13_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_13_buffer->getSize()) + this->gen_02_delay_13_reader - ((size > this->gen_02_delay_13__maxdelay ? this->gen_02_delay_13__maxdelay : (size < (1 + this->gen_02_delay_13_reader != this->gen_02_delay_13_writer) ? 1 + this->gen_02_delay_13_reader != this->gen_02_delay_13_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_13_buffer->getSize()) + this->gen_02_delay_13_reader - ((size > this->gen_02_delay_13__maxdelay ? this->gen_02_delay_13__maxdelay : (size < (this->gen_02_delay_13_reader != this->gen_02_delay_13_writer) ? this->gen_02_delay_13_reader != this->gen_02_delay_13_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_13_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_13_wrap))
    );
}

void gen_02_delay_13_write(number v) {
    this->gen_02_delay_13_writer = this->gen_02_delay_13_reader;
    this->gen_02_delay_13_buffer[(Index)this->gen_02_delay_13_writer] = v;
}

number gen_02_delay_13_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_13_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_13_size() {
    return this->gen_02_delay_13__maxdelay;
}

void gen_02_delay_14_step() {
    this->gen_02_delay_14_reader++;

    if (this->gen_02_delay_14_reader >= (Int)(this->gen_02_delay_14_buffer->getSize()))
        this->gen_02_delay_14_reader = 0;
}

number gen_02_delay_14_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_14_buffer->getSize()) + this->gen_02_delay_14_reader - ((size > this->gen_02_delay_14__maxdelay ? this->gen_02_delay_14__maxdelay : (size < (1 + this->gen_02_delay_14_reader != this->gen_02_delay_14_writer) ? 1 + this->gen_02_delay_14_reader != this->gen_02_delay_14_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_14_buffer->getSize()) + this->gen_02_delay_14_reader - ((size > this->gen_02_delay_14__maxdelay ? this->gen_02_delay_14__maxdelay : (size < (this->gen_02_delay_14_reader != this->gen_02_delay_14_writer) ? this->gen_02_delay_14_reader != this->gen_02_delay_14_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_14_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_14_wrap))
    );
}

void gen_02_delay_14_write(number v) {
    this->gen_02_delay_14_writer = this->gen_02_delay_14_reader;
    this->gen_02_delay_14_buffer[(Index)this->gen_02_delay_14_writer] = v;
}

number gen_02_delay_14_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_14_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_14_size() {
    return this->gen_02_delay_14__maxdelay;
}

void gen_02_delay_15_step() {
    this->gen_02_delay_15_reader++;

    if (this->gen_02_delay_15_reader >= (Int)(this->gen_02_delay_15_buffer->getSize()))
        this->gen_02_delay_15_reader = 0;
}

number gen_02_delay_15_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_15_buffer->getSize()) + this->gen_02_delay_15_reader - ((size > this->gen_02_delay_15__maxdelay ? this->gen_02_delay_15__maxdelay : (size < (1 + this->gen_02_delay_15_reader != this->gen_02_delay_15_writer) ? 1 + this->gen_02_delay_15_reader != this->gen_02_delay_15_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_15_buffer->getSize()) + this->gen_02_delay_15_reader - ((size > this->gen_02_delay_15__maxdelay ? this->gen_02_delay_15__maxdelay : (size < (this->gen_02_delay_15_reader != this->gen_02_delay_15_writer) ? this->gen_02_delay_15_reader != this->gen_02_delay_15_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_15_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_15_wrap))
    );
}

void gen_02_delay_15_write(number v) {
    this->gen_02_delay_15_writer = this->gen_02_delay_15_reader;
    this->gen_02_delay_15_buffer[(Index)this->gen_02_delay_15_writer] = v;
}

number gen_02_delay_15_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_15_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_15_size() {
    return this->gen_02_delay_15__maxdelay;
}

void gen_02_delay_16_step() {
    this->gen_02_delay_16_reader++;

    if (this->gen_02_delay_16_reader >= (Int)(this->gen_02_delay_16_buffer->getSize()))
        this->gen_02_delay_16_reader = 0;
}

number gen_02_delay_16_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_16_buffer->getSize()) + this->gen_02_delay_16_reader - ((size > this->gen_02_delay_16__maxdelay ? this->gen_02_delay_16__maxdelay : (size < (1 + this->gen_02_delay_16_reader != this->gen_02_delay_16_writer) ? 1 + this->gen_02_delay_16_reader != this->gen_02_delay_16_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
            number frac = r - index1;
            Index index2 = (Index)(index1 + 1);
            Index index3 = (Index)(index2 + 1);
            Index index4 = (Index)(index3 + 1);

            return this->cubicinterp(frac, this->gen_02_delay_16_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_16_wrap))
            ), this->gen_02_delay_16_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_02_delay_16_wrap))
            ), this->gen_02_delay_16_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->gen_02_delay_16_wrap))
            ), this->gen_02_delay_16_buffer->getSample(
                0,
                (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->gen_02_delay_16_wrap))
            ));
        }
    }

    number r = (Int)(this->gen_02_delay_16_buffer->getSize()) + this->gen_02_delay_16_reader - ((size > this->gen_02_delay_16__maxdelay ? this->gen_02_delay_16__maxdelay : (size < (this->gen_02_delay_16_reader != this->gen_02_delay_16_writer) ? this->gen_02_delay_16_reader != this->gen_02_delay_16_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_16_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_16_wrap))
    );
}

void gen_02_delay_16_write(number v) {
    this->gen_02_delay_16_writer = this->gen_02_delay_16_reader;
    this->gen_02_delay_16_buffer[(Index)this->gen_02_delay_16_writer] = v;
}

number gen_02_delay_16_next(number v, Int size) {
    number effectiveSize = (size == -1 ? this->gen_02_delay_16__maxdelay : size);
    number val = this->gen_02_delay_16_read(effectiveSize, 0);
    this->gen_02_delay_16_write(v);
    this->gen_02_delay_16_step();
    return val;
}

array<Index, 2> gen_02_delay_16_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_02_delay_16_evaluateSizeExpr(this->sr, this->vs);
        this->gen_02_delay_16_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_02_delay_16_init() {
    auto result = this->gen_02_delay_16_calcSizeInSamples();
    this->gen_02_delay_16__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_16_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_02_delay_16_wrap = requestedSizeInSamples - 1;
}

void gen_02_delay_16_clear() {
    this->gen_02_delay_16_buffer->setZero();
}

void gen_02_delay_16_reset() {
    auto result = this->gen_02_delay_16_calcSizeInSamples();
    this->gen_02_delay_16__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_02_delay_16_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_02_delay_16_buffer);
    this->gen_02_delay_16_wrap = this->gen_02_delay_16_buffer->getSize() - 1;
    this->gen_02_delay_16_clear();

    if (this->gen_02_delay_16_reader >= this->gen_02_delay_16__maxdelay || this->gen_02_delay_16_writer >= this->gen_02_delay_16__maxdelay) {
        this->gen_02_delay_16_reader = 0;
        this->gen_02_delay_16_writer = 0;
    }
}

void gen_02_delay_16_dspsetup() {
    this->gen_02_delay_16_reset();
}

number gen_02_delay_16_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return this->sr;
}

number gen_02_delay_16_size() {
    return this->gen_02_delay_16__maxdelay;
}

void gen_02_delay_17_step() {
    this->gen_02_delay_17_reader++;

    if (this->gen_02_delay_17_reader >= (Int)(this->gen_02_delay_17_buffer->getSize()))
        this->gen_02_delay_17_reader = 0;
}

number gen_02_delay_17_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_17_buffer->getSize()) + this->gen_02_delay_17_reader - ((size > this->gen_02_delay_17__maxdelay ? this->gen_02_delay_17__maxdelay : (size < (1 + this->gen_02_delay_17_reader != this->gen_02_delay_17_writer) ? 1 + this->gen_02_delay_17_reader != this->gen_02_delay_17_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_17_buffer->getSize()) + this->gen_02_delay_17_reader - ((size > this->gen_02_delay_17__maxdelay ? this->gen_02_delay_17__maxdelay : (size < (this->gen_02_delay_17_reader != this->gen_02_delay_17_writer) ? this->gen_02_delay_17_reader != this->gen_02_delay_17_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_17_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_17_wrap))
    );
}

void gen_02_delay_17_write(number v) {
    this->gen_02_delay_17_writer = this->gen_02_delay_17_reader;
    this->gen_02_delay_17_buffer[(Index)this->gen_02_delay_17_writer] = v;
}

number gen_02_delay_17_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_17_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_17_size() {
    return this->gen_02_delay_17__maxdelay;
}

void gen_02_delay_18_step() {
    this->gen_02_delay_18_reader++;

    if (this->gen_02_delay_18_reader >= (Int)(this->gen_02_delay_18_buffer->getSize()))
        this->gen_02_delay_18_reader = 0;
}

number gen_02_delay_18_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        {
            number r = (Int)(this->gen_02_delay_18_buffer->getSize()) + this->gen_02_delay_18_reader - ((size > this->gen_02_delay_18__maxdelay ? this->gen_02_delay_18__maxdelay : (size < (1 + this->gen_02_delay_18_reader != this->gen_02_delay_18_writer) ? 1 + this->gen_02_delay_18_reader != this->gen_02_delay_18_writer : size)));
            Int index1 = (Int)(rnbo_floor(r));
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

    number r = (Int)(this->gen_02_delay_18_buffer->getSize()) + this->gen_02_delay_18_reader - ((size > this->gen_02_delay_18__maxdelay ? this->gen_02_delay_18__maxdelay : (size < (this->gen_02_delay_18_reader != this->gen_02_delay_18_writer) ? this->gen_02_delay_18_reader != this->gen_02_delay_18_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_02_delay_18_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_02_delay_18_wrap))
    );
}

void gen_02_delay_18_write(number v) {
    this->gen_02_delay_18_writer = this->gen_02_delay_18_reader;
    this->gen_02_delay_18_buffer[(Index)this->gen_02_delay_18_writer] = v;
}

number gen_02_delay_18_next(number v, Int size) {
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
        sizeInSamples = this->gen_02_delay_18_evaluateSizeExpr(this->sr, this->vs);
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
    return this->sr;
}

number gen_02_delay_18_size() {
    return this->gen_02_delay_18__maxdelay;
}

number gen_02_history_19_getvalue() {
    return this->gen_02_history_19_value;
}

void gen_02_history_19_setvalue(number val) {
    this->gen_02_history_19_value = val;
}

void gen_02_history_19_reset() {
    this->gen_02_history_19_value = 0;
}

void gen_02_history_19_init() {
    this->gen_02_history_19_value = 0;
}

number gen_02_slide_4_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_02_slide_4_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(2000)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(2000)));
    this->gen_02_slide_4_prev = this->gen_02_slide_4_prev + ((x > this->gen_02_slide_4_prev ? iup : idown)) * temp;
    return this->gen_02_slide_4_prev;
}

void gen_02_slide_4_reset() {
    this->gen_02_slide_4_prev = 0;
}

number gen_02_phasor_15_next(number freq, number reset) {
    RNBO_UNUSED(reset);
    number pincr = freq * this->gen_02_phasor_15_conv;

    if (this->gen_02_phasor_15_currentPhase < 0.)
        this->gen_02_phasor_15_currentPhase = 1. + this->gen_02_phasor_15_currentPhase;

    if (this->gen_02_phasor_15_currentPhase > 1.)
        this->gen_02_phasor_15_currentPhase = this->gen_02_phasor_15_currentPhase - 1.;

    number tmp = this->gen_02_phasor_15_currentPhase;
    this->gen_02_phasor_15_currentPhase += pincr;
    return tmp;
}

void gen_02_phasor_15_reset() {
    this->gen_02_phasor_15_currentPhase = 0;
}

void gen_02_phasor_15_dspsetup() {
    this->gen_02_phasor_15_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

number gen_02_cycle_17_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_17_ph_conv;

    if (this->gen_02_cycle_17_ph_currentPhase < 0.)
        this->gen_02_cycle_17_ph_currentPhase = 1. + this->gen_02_cycle_17_ph_currentPhase;

    if (this->gen_02_cycle_17_ph_currentPhase > 1.)
        this->gen_02_cycle_17_ph_currentPhase = this->gen_02_cycle_17_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_17_ph_currentPhase;
    this->gen_02_cycle_17_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_17_ph_reset() {
    this->gen_02_cycle_17_ph_currentPhase = 0;
}

void gen_02_cycle_17_ph_dspsetup() {
    this->gen_02_cycle_17_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_17_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_17_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_17_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_17_dspsetup() {
    this->gen_02_cycle_17_phasei = 0;
    this->gen_02_cycle_17_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_02_cycle_17_wrap = (Int)(this->gen_02_cycle_17_buffer->getSize()) - 1;
}

void gen_02_cycle_17_reset() {
    this->gen_02_cycle_17_phasei = 0;
}

void gen_02_cycle_17_bufferUpdated() {
    this->gen_02_cycle_17_wrap = (Int)(this->gen_02_cycle_17_buffer->getSize()) - 1;
}

number gen_02_cycle_26_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_26_ph_conv;

    if (this->gen_02_cycle_26_ph_currentPhase < 0.)
        this->gen_02_cycle_26_ph_currentPhase = 1. + this->gen_02_cycle_26_ph_currentPhase;

    if (this->gen_02_cycle_26_ph_currentPhase > 1.)
        this->gen_02_cycle_26_ph_currentPhase = this->gen_02_cycle_26_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_26_ph_currentPhase;
    this->gen_02_cycle_26_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_26_ph_reset() {
    this->gen_02_cycle_26_ph_currentPhase = 0;
}

void gen_02_cycle_26_ph_dspsetup() {
    this->gen_02_cycle_26_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_26_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_26_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_26_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_26_dspsetup() {
    this->gen_02_cycle_26_phasei = 0;
    this->gen_02_cycle_26_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_02_cycle_26_wrap = (Int)(this->gen_02_cycle_26_buffer->getSize()) - 1;
}

void gen_02_cycle_26_reset() {
    this->gen_02_cycle_26_phasei = 0;
}

void gen_02_cycle_26_bufferUpdated() {
    this->gen_02_cycle_26_wrap = (Int)(this->gen_02_cycle_26_buffer->getSize()) - 1;
}

number gen_02_cycle_36_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_36_ph_conv;

    if (this->gen_02_cycle_36_ph_currentPhase < 0.)
        this->gen_02_cycle_36_ph_currentPhase = 1. + this->gen_02_cycle_36_ph_currentPhase;

    if (this->gen_02_cycle_36_ph_currentPhase > 1.)
        this->gen_02_cycle_36_ph_currentPhase = this->gen_02_cycle_36_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_36_ph_currentPhase;
    this->gen_02_cycle_36_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_36_ph_reset() {
    this->gen_02_cycle_36_ph_currentPhase = 0;
}

void gen_02_cycle_36_ph_dspsetup() {
    this->gen_02_cycle_36_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_36_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_36_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_36_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_36_dspsetup() {
    this->gen_02_cycle_36_phasei = 0;
    this->gen_02_cycle_36_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_02_cycle_36_wrap = (Int)(this->gen_02_cycle_36_buffer->getSize()) - 1;
}

void gen_02_cycle_36_reset() {
    this->gen_02_cycle_36_phasei = 0;
}

void gen_02_cycle_36_bufferUpdated() {
    this->gen_02_cycle_36_wrap = (Int)(this->gen_02_cycle_36_buffer->getSize()) - 1;
}

number gen_02_cycle_45_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_45_ph_conv;

    if (this->gen_02_cycle_45_ph_currentPhase < 0.)
        this->gen_02_cycle_45_ph_currentPhase = 1. + this->gen_02_cycle_45_ph_currentPhase;

    if (this->gen_02_cycle_45_ph_currentPhase > 1.)
        this->gen_02_cycle_45_ph_currentPhase = this->gen_02_cycle_45_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_45_ph_currentPhase;
    this->gen_02_cycle_45_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_45_ph_reset() {
    this->gen_02_cycle_45_ph_currentPhase = 0;
}

void gen_02_cycle_45_ph_dspsetup() {
    this->gen_02_cycle_45_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_45_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_45_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_45_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_45_dspsetup() {
    this->gen_02_cycle_45_phasei = 0;
    this->gen_02_cycle_45_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_02_cycle_45_wrap = (Int)(this->gen_02_cycle_45_buffer->getSize()) - 1;
}

void gen_02_cycle_45_reset() {
    this->gen_02_cycle_45_phasei = 0;
}

void gen_02_cycle_45_bufferUpdated() {
    this->gen_02_cycle_45_wrap = (Int)(this->gen_02_cycle_45_buffer->getSize()) - 1;
}

number gen_02_cycle_54_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_54_ph_conv;

    if (this->gen_02_cycle_54_ph_currentPhase < 0.)
        this->gen_02_cycle_54_ph_currentPhase = 1. + this->gen_02_cycle_54_ph_currentPhase;

    if (this->gen_02_cycle_54_ph_currentPhase > 1.)
        this->gen_02_cycle_54_ph_currentPhase = this->gen_02_cycle_54_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_54_ph_currentPhase;
    this->gen_02_cycle_54_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_54_ph_reset() {
    this->gen_02_cycle_54_ph_currentPhase = 0;
}

void gen_02_cycle_54_ph_dspsetup() {
    this->gen_02_cycle_54_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_54_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_54_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_54_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_54_dspsetup() {
    this->gen_02_cycle_54_phasei = 0;
    this->gen_02_cycle_54_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_02_cycle_54_wrap = (Int)(this->gen_02_cycle_54_buffer->getSize()) - 1;
}

void gen_02_cycle_54_reset() {
    this->gen_02_cycle_54_phasei = 0;
}

void gen_02_cycle_54_bufferUpdated() {
    this->gen_02_cycle_54_wrap = (Int)(this->gen_02_cycle_54_buffer->getSize()) - 1;
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
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_63_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_63_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_63_dspsetup() {
    this->gen_02_cycle_63_phasei = 0;
    this->gen_02_cycle_63_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_02_cycle_63_wrap = (Int)(this->gen_02_cycle_63_buffer->getSize()) - 1;
}

void gen_02_cycle_63_reset() {
    this->gen_02_cycle_63_phasei = 0;
}

void gen_02_cycle_63_bufferUpdated() {
    this->gen_02_cycle_63_wrap = (Int)(this->gen_02_cycle_63_buffer->getSize()) - 1;
}

number gen_02_cycle_74_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_74_ph_conv;

    if (this->gen_02_cycle_74_ph_currentPhase < 0.)
        this->gen_02_cycle_74_ph_currentPhase = 1. + this->gen_02_cycle_74_ph_currentPhase;

    if (this->gen_02_cycle_74_ph_currentPhase > 1.)
        this->gen_02_cycle_74_ph_currentPhase = this->gen_02_cycle_74_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_74_ph_currentPhase;
    this->gen_02_cycle_74_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_74_ph_reset() {
    this->gen_02_cycle_74_ph_currentPhase = 0;
}

void gen_02_cycle_74_ph_dspsetup() {
    this->gen_02_cycle_74_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_74_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_74_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_74_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_74_dspsetup() {
    this->gen_02_cycle_74_phasei = 0;
    this->gen_02_cycle_74_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_02_cycle_74_wrap = (Int)(this->gen_02_cycle_74_buffer->getSize()) - 1;
}

void gen_02_cycle_74_reset() {
    this->gen_02_cycle_74_phasei = 0;
}

void gen_02_cycle_74_bufferUpdated() {
    this->gen_02_cycle_74_wrap = (Int)(this->gen_02_cycle_74_buffer->getSize()) - 1;
}

number gen_02_cycle_87_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_02_cycle_87_ph_conv;

    if (this->gen_02_cycle_87_ph_currentPhase < 0.)
        this->gen_02_cycle_87_ph_currentPhase = 1. + this->gen_02_cycle_87_ph_currentPhase;

    if (this->gen_02_cycle_87_ph_currentPhase > 1.)
        this->gen_02_cycle_87_ph_currentPhase = this->gen_02_cycle_87_ph_currentPhase - 1.;

    number tmp = this->gen_02_cycle_87_ph_currentPhase;
    this->gen_02_cycle_87_ph_currentPhase += pincr;
    return tmp;
}

void gen_02_cycle_87_ph_reset() {
    this->gen_02_cycle_87_ph_currentPhase = 0;
}

void gen_02_cycle_87_ph_dspsetup() {
    this->gen_02_cycle_87_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_02_cycle_87_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_02_cycle_87_buffer[(Index)idx];
        number y1 = this->gen_02_cycle_87_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_02_cycle_87_dspsetup() {
    this->gen_02_cycle_87_phasei = 0;
    this->gen_02_cycle_87_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_02_cycle_87_wrap = (Int)(this->gen_02_cycle_87_buffer->getSize()) - 1;
}

void gen_02_cycle_87_reset() {
    this->gen_02_cycle_87_phasei = 0;
}

void gen_02_cycle_87_bufferUpdated() {
    this->gen_02_cycle_87_wrap = (Int)(this->gen_02_cycle_87_buffer->getSize()) - 1;
}

number gen_02_slide_104_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_02_slide_104_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(500)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(500)));
    this->gen_02_slide_104_prev = this->gen_02_slide_104_prev + ((x > this->gen_02_slide_104_prev ? iup : idown)) * temp;
    return this->gen_02_slide_104_prev;
}

void gen_02_slide_104_reset() {
    this->gen_02_slide_104_prev = 0;
}

number gen_02_dcblock_172_next(number x, number gain) {
    RNBO_UNUSED(gain);
    number y = x - this->gen_02_dcblock_172_xm1 + this->gen_02_dcblock_172_ym1 * 0.9997;
    this->gen_02_dcblock_172_xm1 = x;
    this->gen_02_dcblock_172_ym1 = y;
    return y;
}

void gen_02_dcblock_172_reset() {
    this->gen_02_dcblock_172_xm1 = 0;
    this->gen_02_dcblock_172_ym1 = 0;
}

void gen_02_dcblock_172_dspsetup() {
    this->gen_02_dcblock_172_reset();
}

number gen_02_dcblock_237_next(number x, number gain) {
    RNBO_UNUSED(gain);
    number y = x - this->gen_02_dcblock_237_xm1 + this->gen_02_dcblock_237_ym1 * 0.9997;
    this->gen_02_dcblock_237_xm1 = x;
    this->gen_02_dcblock_237_ym1 = y;
    return y;
}

void gen_02_dcblock_237_reset() {
    this->gen_02_dcblock_237_xm1 = 0;
    this->gen_02_dcblock_237_ym1 = 0;
}

void gen_02_dcblock_237_dspsetup() {
    this->gen_02_dcblock_237_reset();
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
    this->gen_02_delay_11_dspsetup();
    this->gen_02_delay_12_dspsetup();
    this->gen_02_delay_13_dspsetup();
    this->gen_02_delay_14_dspsetup();
    this->gen_02_delay_15_dspsetup();
    this->gen_02_delay_16_dspsetup();
    this->gen_02_delay_17_dspsetup();
    this->gen_02_delay_18_dspsetup();
    this->gen_02_phasor_15_dspsetup();
    this->gen_02_cycle_17_ph_dspsetup();
    this->gen_02_cycle_17_dspsetup();
    this->gen_02_cycle_26_ph_dspsetup();
    this->gen_02_cycle_26_dspsetup();
    this->gen_02_cycle_36_ph_dspsetup();
    this->gen_02_cycle_36_dspsetup();
    this->gen_02_cycle_45_ph_dspsetup();
    this->gen_02_cycle_45_dspsetup();
    this->gen_02_cycle_54_ph_dspsetup();
    this->gen_02_cycle_54_dspsetup();
    this->gen_02_cycle_63_ph_dspsetup();
    this->gen_02_cycle_63_dspsetup();
    this->gen_02_cycle_74_ph_dspsetup();
    this->gen_02_cycle_74_dspsetup();
    this->gen_02_cycle_87_ph_dspsetup();
    this->gen_02_cycle_87_dspsetup();
    this->gen_02_dcblock_172_dspsetup();
    this->gen_02_dcblock_237_dspsetup();
}

void dcblock_tilde_02_reset() {
    this->dcblock_tilde_02_xm1 = 0;
    this->dcblock_tilde_02_ym1 = 0;
}

void dcblock_tilde_02_dspsetup(bool force) {
    if ((bool)(this->dcblock_tilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->dcblock_tilde_02_reset();
    this->dcblock_tilde_02_setupDone = true;
}

void dcblock_tilde_03_reset() {
    this->dcblock_tilde_03_xm1 = 0;
    this->dcblock_tilde_03_ym1 = 0;
}

void dcblock_tilde_03_dspsetup(bool force) {
    if ((bool)(this->dcblock_tilde_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->dcblock_tilde_03_reset();
    this->dcblock_tilde_03_setupDone = true;
}

void dcblock_tilde_04_reset() {
    this->dcblock_tilde_04_xm1 = 0;
    this->dcblock_tilde_04_ym1 = 0;
}

void dcblock_tilde_04_dspsetup(bool force) {
    if ((bool)(this->dcblock_tilde_04_setupDone) && (bool)(!(bool)(force)))
        return;

    this->dcblock_tilde_04_reset();
    this->dcblock_tilde_04_setupDone = true;
}

void toggle_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_02_value_number;
}

void toggle_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_02_value_number_set(preset["value"]);
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

void numberobj_16_init() {
    this->numberobj_16_currentFormat = 6;
}

void numberobj_16_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_16_value;
}

void numberobj_16_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_16_value_set(preset["value"]);
}

void numberobj_17_init() {
    this->numberobj_17_currentFormat = 6;
}

void numberobj_17_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_17_value;
}

void numberobj_17_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_17_value_set(preset["value"]);
}

void numberobj_18_init() {
    this->numberobj_18_currentFormat = 6;
}

void numberobj_18_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_18_value;
}

void numberobj_18_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_18_value_set(preset["value"]);
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
}

void numberobj_19_init() {
    this->numberobj_19_currentFormat = 6;
}

void numberobj_19_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_19_value;
}

void numberobj_19_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_19_value_set(preset["value"]);
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
}

void numberobj_20_init() {
    this->numberobj_20_currentFormat = 6;
}

void numberobj_20_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_20_value;
}

void numberobj_20_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_20_value_set(preset["value"]);
}

void numberobj_21_init() {
    this->numberobj_21_currentFormat = 6;
}

void numberobj_21_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_21_value;
}

void numberobj_21_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_21_value_set(preset["value"]);
}

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

void param_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_10_value;
}

void param_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_10_value_set(preset["value"]);
}

void numberobj_22_init() {
    this->numberobj_22_currentFormat = 6;
}

void numberobj_22_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_22_value;
}

void numberobj_22_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_22_value_set(preset["value"]);
}

void param_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_11_value;
}

void param_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_11_value_set(preset["value"]);
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

void message_01_init() {
    this->message_01_set_set(listbase<number, 0>{});
}

void param_14_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_14_value;
}

void param_14_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_14_value_set(preset["value"]);
}

void numberobj_24_init() {
    this->numberobj_24_currentFormat = 6;
}

void numberobj_24_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_24_value;
}

void numberobj_24_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_24_value_set(preset["value"]);
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

void numberobj_25_init() {
    this->numberobj_25_currentFormat = 6;
}

void numberobj_25_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_25_value;
}

void numberobj_25_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_25_value_set(preset["value"]);
}

void param_18_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_18_value;
}

void param_18_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_18_value_set(preset["value"]);
}

void numberobj_26_init() {
    this->numberobj_26_currentFormat = 6;
}

void numberobj_26_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_26_value;
}

void numberobj_26_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_26_value_set(preset["value"]);
}

void param_19_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_19_value;
}

void param_19_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_19_value_set(preset["value"]);
}

void param_20_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_20_value;
}

void param_20_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_20_value_set(preset["value"]);
}

void numberobj_27_init() {
    this->numberobj_27_currentFormat = 6;
}

void numberobj_27_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_27_value;
}

void numberobj_27_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_27_value_set(preset["value"]);
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

Index getPatcherSerial() const {
    return 0;
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
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

void updateTime(MillisecondTime time, EXTERNALENGINE ) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    param_01_value = 20;
    scale_04_inlow = 0;
    scale_04_inhigh = 10;
    scale_04_outlow = 0.5;
    scale_04_outhigh = 0.99;
    scale_04_power = 1;
    param_02_value = 4;
    slide_01_x = 0;
    slide_01_up = 0.5;
    slide_01_down = 0.99;
    slide_02_x = 0;
    slide_02_up = 10;
    slide_02_down = 100;
    scale_05_inlow = 0;
    scale_05_inhigh = 100;
    scale_05_outlow = 0.2;
    scale_05_outhigh = 2;
    scale_05_power = 1;
    numberobj_14_value = 0;
    numberobj_14_value_setter(numberobj_14_value);
    param_03_value = 45;
    dcblock_tilde_01_x = 0;
    dcblock_tilde_01_gain = 0.9997;
    dspexpr_05_in1 = 0;
    dspexpr_05_in2 = -1;
    dspexpr_05_in3 = 1;
    p_01_target = 0;
    gen_01_in1 = 0;
    gen_01_in2 = 0;
    gen_01_xover = 0;
    gen_01_lfo1_bw = 1;
    gen_01_decay = 0.82;
    gen_01_lfo1_rate = 0.2;
    gen_01_InGain = 0;
    gen_01_fbc = 0;
    gen_01_lpf = 8000;
    gen_01_mult = 0;
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
    gen_02_lfo1_rate = 0.2;
    gen_02_pre_del = 0;
    gen_02_decay2 = 0.82;
    gen_02_lpf = 8000;
    gen_02_lfo1_bw = 1;
    gen_02_apf_g = 0;
    gen_02_diff_gain = 0;
    dcblock_tilde_02_x = 0;
    dcblock_tilde_02_gain = 0.9997;
    dspexpr_06_in1 = 0;
    dspexpr_06_in2 = -1;
    dspexpr_06_in3 = 1;
    dcblock_tilde_03_x = 0;
    dcblock_tilde_03_gain = 0.9997;
    p_06_target = 0;
    p_07_target = 0;
    dcblock_tilde_04_x = 0;
    dcblock_tilde_04_gain = 0.9997;
    toggle_02_value_number = 0;
    toggle_02_value_number_setter(toggle_02_value_number);
    param_04_value = 0;
    numberobj_15_value = 0;
    numberobj_15_value_setter(numberobj_15_value);
    param_05_value = 0;
    numberobj_16_value = 0;
    numberobj_16_value_setter(numberobj_16_value);
    numberobj_17_value = 0;
    numberobj_17_value_setter(numberobj_17_value);
    expr_06_in1 = 0;
    expr_06_in2 = 100;
    expr_06_out1 = 0;
    linetilde_09_time = 10;
    linetilde_09_keepramp = true;
    numberobj_18_value = 0;
    numberobj_18_value_setter(numberobj_18_value);
    param_06_value = 0;
    snapshot_01_interval = 5;
    snapshot_01_out = 0;
    numberobj_19_value = 0;
    numberobj_19_value_setter(numberobj_19_value);
    param_07_value = 0;
    numberobj_20_value = 0;
    numberobj_20_value_setter(numberobj_20_value);
    numberobj_21_value = 0;
    numberobj_21_value_setter(numberobj_21_value);
    param_08_value = 0;
    param_09_value = 0;
    param_10_value = 0;
    numberobj_22_value = 0;
    numberobj_22_value_setter(numberobj_22_value);
    param_11_value = 0;
    param_12_value = 0.3;
    scale_06_inlow = 0;
    scale_06_inhigh = 100;
    scale_06_outlow = 0;
    scale_06_outhigh = 1;
    scale_06_power = 1;
    numberobj_23_value = 0;
    numberobj_23_value_setter(numberobj_23_value);
    param_13_value = 0;
    scale_07_inlow = 0;
    scale_07_inhigh = 100;
    scale_07_outlow = 0.1;
    scale_07_outhigh = 1;
    scale_07_power = 1;
    param_14_value = 50;
    numberobj_24_value = 0;
    numberobj_24_value_setter(numberobj_24_value);
    scale_08_inlow = 0;
    scale_08_inhigh = 100;
    scale_08_outlow = 0;
    scale_08_outhigh = 2;
    scale_08_power = 1;
    param_15_value = 70;
    param_16_value = 0.2;
    scale_09_inlow = 100;
    scale_09_inhigh = 0;
    scale_09_outlow = 500;
    scale_09_outhigh = 16000;
    scale_09_power = 1;
    param_17_value = 20;
    numberobj_25_value = 0;
    numberobj_25_value_setter(numberobj_25_value);
    param_18_value = 0;
    numberobj_26_value = 0;
    numberobj_26_value_setter(numberobj_26_value);
    param_19_value = 0;
    param_20_value = 0;
    numberobj_27_value = 0;
    numberobj_27_value_setter(numberobj_27_value);
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
    ctlin_03_controller = 6;
    ctlin_03_channel = -1;
    expr_07_in1 = 0;
    expr_07_in2 = 0.007874015748;
    expr_07_out1 = 0;
    ctlin_04_input = 0;
    ctlin_04_controller = 1;
    ctlin_04_channel = -1;
    expr_08_in1 = 0;
    expr_08_in2 = 0.007874015748;
    expr_08_out1 = 0;
    ctlin_05_input = 0;
    ctlin_05_controller = 5;
    ctlin_05_channel = -1;
    expr_09_in1 = 0;
    expr_09_in2 = 0.007874015748;
    expr_09_out1 = 0;
    ctlin_06_input = 0;
    ctlin_06_controller = 9;
    ctlin_06_channel = -1;
    expr_10_in1 = 0;
    expr_10_in2 = 0.007874015748;
    expr_10_out1 = 0;
    ctlin_07_input = 0;
    ctlin_07_controller = 6;
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
    ctlin_09_input = 0;
    ctlin_09_controller = 6;
    ctlin_09_channel = -1;
    expr_13_in1 = 0;
    expr_13_in2 = 0.007874015748;
    expr_13_out1 = 0;
    ctlin_10_input = 0;
    ctlin_10_controller = 5;
    ctlin_10_channel = -1;
    expr_14_in1 = 0;
    expr_14_in2 = 0.007874015748;
    expr_14_out1 = 0;
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
    invsr = 0.000022675736961451248;
    param_01_lastValue = 0;
    param_02_lastValue = 0;
    slide_01_prev = 0;
    slide_02_prev = 0;
    numberobj_14_currentFormat = 6;
    numberobj_14_lastValue = 0;
    param_03_lastValue = 0;
    dcblock_tilde_01_xm1 = 0;
    dcblock_tilde_01_ym1 = 0;
    dcblock_tilde_01_setupDone = false;
    gen_01_history_1_value = 0;
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
    gen_01_history_2_value = 0;
    gen_01_history_3_value = 0;
    gen_01_history_4_value = 0;
    gen_01_history_5_value = 0;
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
    gen_01_history_6_value = 0;
    gen_01_history_7_value = 0;
    gen_01_history_8_value = 0;
    gen_01_history_9_value = 0;
    gen_01_history_10_value = 0;
    gen_01_slide_0_prev = 0;
    gen_01_slide_2_prev = 0;
    gen_01_phasor_6_currentPhase = 0;
    gen_01_phasor_6_conv = 0;
    gen_01_cycle_8_ph_currentPhase = 0;
    gen_01_cycle_8_ph_conv = 0;
    gen_01_cycle_8_wrap = 0;
    gen_01_cycle_13_ph_currentPhase = 0;
    gen_01_cycle_13_ph_conv = 0;
    gen_01_cycle_13_wrap = 0;
    gen_01_cycle_18_ph_currentPhase = 0;
    gen_01_cycle_18_ph_conv = 0;
    gen_01_cycle_18_wrap = 0;
    gen_01_cycle_23_ph_currentPhase = 0;
    gen_01_cycle_23_ph_conv = 0;
    gen_01_cycle_23_wrap = 0;
    gen_01_cycle_28_ph_currentPhase = 0;
    gen_01_cycle_28_ph_conv = 0;
    gen_01_cycle_28_wrap = 0;
    gen_01_cycle_33_ph_currentPhase = 0;
    gen_01_cycle_33_ph_conv = 0;
    gen_01_cycle_33_wrap = 0;
    gen_01_cycle_38_ph_currentPhase = 0;
    gen_01_cycle_38_ph_conv = 0;
    gen_01_cycle_38_wrap = 0;
    gen_01_cycle_43_ph_currentPhase = 0;
    gen_01_cycle_43_ph_conv = 0;
    gen_01_cycle_43_wrap = 0;
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
    gen_02_history_10_value = 0;
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
    gen_02_delay_16__maxdelay = 0;
    gen_02_delay_16_sizemode = 0;
    gen_02_delay_16_wrap = 0;
    gen_02_delay_16_reader = 0;
    gen_02_delay_16_writer = 0;
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
    gen_02_history_19_value = 0;
    gen_02_slide_4_prev = 0;
    gen_02_phasor_15_currentPhase = 0;
    gen_02_phasor_15_conv = 0;
    gen_02_cycle_17_ph_currentPhase = 0;
    gen_02_cycle_17_ph_conv = 0;
    gen_02_cycle_17_wrap = 0;
    gen_02_cycle_26_ph_currentPhase = 0;
    gen_02_cycle_26_ph_conv = 0;
    gen_02_cycle_26_wrap = 0;
    gen_02_cycle_36_ph_currentPhase = 0;
    gen_02_cycle_36_ph_conv = 0;
    gen_02_cycle_36_wrap = 0;
    gen_02_cycle_45_ph_currentPhase = 0;
    gen_02_cycle_45_ph_conv = 0;
    gen_02_cycle_45_wrap = 0;
    gen_02_cycle_54_ph_currentPhase = 0;
    gen_02_cycle_54_ph_conv = 0;
    gen_02_cycle_54_wrap = 0;
    gen_02_cycle_63_ph_currentPhase = 0;
    gen_02_cycle_63_ph_conv = 0;
    gen_02_cycle_63_wrap = 0;
    gen_02_cycle_74_ph_currentPhase = 0;
    gen_02_cycle_74_ph_conv = 0;
    gen_02_cycle_74_wrap = 0;
    gen_02_cycle_87_ph_currentPhase = 0;
    gen_02_cycle_87_ph_conv = 0;
    gen_02_cycle_87_wrap = 0;
    gen_02_slide_104_prev = 0;
    gen_02_dcblock_172_xm1 = 0;
    gen_02_dcblock_172_ym1 = 0;
    gen_02_dcblock_237_xm1 = 0;
    gen_02_dcblock_237_ym1 = 0;
    gen_02_setupDone = false;
    dcblock_tilde_02_xm1 = 0;
    dcblock_tilde_02_ym1 = 0;
    dcblock_tilde_02_setupDone = false;
    dcblock_tilde_03_xm1 = 0;
    dcblock_tilde_03_ym1 = 0;
    dcblock_tilde_03_setupDone = false;
    dcblock_tilde_04_xm1 = 0;
    dcblock_tilde_04_ym1 = 0;
    dcblock_tilde_04_setupDone = false;
    toggle_02_lastValue = 0;
    param_04_lastValue = 0;
    numberobj_15_currentFormat = 6;
    numberobj_15_lastValue = 0;
    param_05_lastValue = 0;
    numberobj_16_currentFormat = 6;
    numberobj_16_lastValue = 0;
    numberobj_17_currentFormat = 6;
    numberobj_17_lastValue = 0;
    linetilde_09_currentValue = 0;
    numberobj_18_currentFormat = 6;
    numberobj_18_lastValue = 0;
    param_06_lastValue = 0;
    snapshot_01_calc = 0;
    snapshot_01_nextTime = 0;
    snapshot_01_count = 0;
    snapshot_01_lastValue = 0;
    numberobj_19_currentFormat = 6;
    numberobj_19_lastValue = 0;
    param_07_lastValue = 0;
    numberobj_20_currentFormat = 6;
    numberobj_20_lastValue = 0;
    numberobj_21_currentFormat = 6;
    numberobj_21_lastValue = 0;
    param_08_lastValue = 0;
    param_09_lastValue = 0;
    param_10_lastValue = 0;
    numberobj_22_currentFormat = 6;
    numberobj_22_lastValue = 0;
    param_11_lastValue = 0;
    param_12_lastValue = 0;
    numberobj_23_currentFormat = 6;
    numberobj_23_lastValue = 0;
    param_13_lastValue = 0;
    param_14_lastValue = 0;
    numberobj_24_currentFormat = 6;
    numberobj_24_lastValue = 0;
    param_15_lastValue = 0;
    param_16_lastValue = 0;
    param_17_lastValue = 0;
    numberobj_25_currentFormat = 6;
    numberobj_25_lastValue = 0;
    param_18_lastValue = 0;
    numberobj_26_currentFormat = 6;
    numberobj_26_lastValue = 0;
    param_19_lastValue = 0;
    param_20_lastValue = 0;
    numberobj_27_currentFormat = 6;
    numberobj_27_lastValue = 0;
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
    ctlin_09_status = 0;
    ctlin_09_byte1 = -1;
    ctlin_09_inchan = 0;
    ctlin_10_status = 0;
    ctlin_10_byte1 = -1;
    ctlin_10_inchan = 0;
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

    // data ref strings
    struct DataRefStrings {
    	static constexpr auto& name0 = "gen_01_DL1_bufferobj";
    	static constexpr auto& file0 = "";
    	static constexpr auto& tag0 = "buffer~";
    	static constexpr auto& name1 = "gen_01_DL2_bufferobj";
    	static constexpr auto& file1 = "";
    	static constexpr auto& tag1 = "buffer~";
    	static constexpr auto& name2 = "gen_01_DL3_bufferobj";
    	static constexpr auto& file2 = "";
    	static constexpr auto& tag2 = "buffer~";
    	static constexpr auto& name3 = "gen_01_DL4_bufferobj";
    	static constexpr auto& file3 = "";
    	static constexpr auto& tag3 = "buffer~";
    	static constexpr auto& name4 = "gen_01_DL5_bufferobj";
    	static constexpr auto& file4 = "";
    	static constexpr auto& tag4 = "buffer~";
    	static constexpr auto& name5 = "gen_01_DL6_bufferobj";
    	static constexpr auto& file5 = "";
    	static constexpr auto& tag5 = "buffer~";
    	static constexpr auto& name6 = "gen_01_DL7_bufferobj";
    	static constexpr auto& file6 = "";
    	static constexpr auto& tag6 = "buffer~";
    	static constexpr auto& name7 = "gen_01_DL8_bufferobj";
    	static constexpr auto& file7 = "";
    	static constexpr auto& tag7 = "buffer~";
    	static constexpr auto& name8 = "gen_01_DL9_bufferobj";
    	static constexpr auto& file8 = "";
    	static constexpr auto& tag8 = "buffer~";
    	static constexpr auto& name9 = "gen_01_DL10_bufferobj";
    	static constexpr auto& file9 = "";
    	static constexpr auto& tag9 = "buffer~";
    	static constexpr auto& name10 = "gen_01_DL11_bufferobj";
    	static constexpr auto& file10 = "";
    	static constexpr auto& tag10 = "buffer~";
    	static constexpr auto& name11 = "gen_01_DL12_bufferobj";
    	static constexpr auto& file11 = "";
    	static constexpr auto& tag11 = "buffer~";
    	static constexpr auto& name12 = "gen_01_DL13_bufferobj";
    	static constexpr auto& file12 = "";
    	static constexpr auto& tag12 = "buffer~";
    	static constexpr auto& name13 = "gen_01_dlL1_bufferobj";
    	static constexpr auto& file13 = "";
    	static constexpr auto& tag13 = "buffer~";
    	static constexpr auto& name14 = "gen_01_dlL2_bufferobj";
    	static constexpr auto& file14 = "";
    	static constexpr auto& tag14 = "buffer~";
    	static constexpr auto& name15 = "gen_01_dlL3_bufferobj";
    	static constexpr auto& file15 = "";
    	static constexpr auto& tag15 = "buffer~";
    	static constexpr auto& name16 = "gen_01_dlL4_bufferobj";
    	static constexpr auto& file16 = "";
    	static constexpr auto& tag16 = "buffer~";
    	static constexpr auto& name17 = "gen_01_dlL5_bufferobj";
    	static constexpr auto& file17 = "";
    	static constexpr auto& tag17 = "buffer~";
    	static constexpr auto& name18 = "gen_01_dlL6_bufferobj";
    	static constexpr auto& file18 = "";
    	static constexpr auto& tag18 = "buffer~";
    	static constexpr auto& name19 = "gen_01_dlL7_bufferobj";
    	static constexpr auto& file19 = "";
    	static constexpr auto& tag19 = "buffer~";
    	static constexpr auto& name20 = "gen_01_dlL8_bufferobj";
    	static constexpr auto& file20 = "";
    	static constexpr auto& tag20 = "buffer~";
    	static constexpr auto& name21 = "gen_01_dlL9_bufferobj";
    	static constexpr auto& file21 = "";
    	static constexpr auto& tag21 = "buffer~";
    	static constexpr auto& name22 = "gen_01_dlL10_bufferobj";
    	static constexpr auto& file22 = "";
    	static constexpr auto& tag22 = "buffer~";
    	static constexpr auto& name23 = "gen_01_dlL11_bufferobj";
    	static constexpr auto& file23 = "";
    	static constexpr auto& tag23 = "buffer~";
    	static constexpr auto& name24 = "gen_01_dlL12_bufferobj";
    	static constexpr auto& file24 = "";
    	static constexpr auto& tag24 = "buffer~";
    	static constexpr auto& name25 = "gen_01_dlL13_bufferobj";
    	static constexpr auto& file25 = "";
    	static constexpr auto& tag25 = "buffer~";
    	static constexpr auto& name26 = "RNBODefaultSinus";
    	static constexpr auto& file26 = "";
    	static constexpr auto& tag26 = "buffer~";
    	static constexpr auto& name27 = "gen_02_delay_1_bufferobj";
    	static constexpr auto& file27 = "";
    	static constexpr auto& tag27 = "buffer~";
    	static constexpr auto& name28 = "gen_02_delay_2_bufferobj";
    	static constexpr auto& file28 = "";
    	static constexpr auto& tag28 = "buffer~";
    	static constexpr auto& name29 = "gen_02_delay_3_bufferobj";
    	static constexpr auto& file29 = "";
    	static constexpr auto& tag29 = "buffer~";
    	static constexpr auto& name30 = "gen_02_delay_4_bufferobj";
    	static constexpr auto& file30 = "";
    	static constexpr auto& tag30 = "buffer~";
    	static constexpr auto& name31 = "gen_02_delay_5_bufferobj";
    	static constexpr auto& file31 = "";
    	static constexpr auto& tag31 = "buffer~";
    	static constexpr auto& name32 = "gen_02_delay_6_bufferobj";
    	static constexpr auto& file32 = "";
    	static constexpr auto& tag32 = "buffer~";
    	static constexpr auto& name33 = "gen_02_delay_7_bufferobj";
    	static constexpr auto& file33 = "";
    	static constexpr auto& tag33 = "buffer~";
    	static constexpr auto& name34 = "gen_02_delay_8_bufferobj";
    	static constexpr auto& file34 = "";
    	static constexpr auto& tag34 = "buffer~";
    	static constexpr auto& name35 = "gen_02_delay_9_bufferobj";
    	static constexpr auto& file35 = "";
    	static constexpr auto& tag35 = "buffer~";
    	static constexpr auto& name36 = "gen_02_delay_11_bufferobj";
    	static constexpr auto& file36 = "";
    	static constexpr auto& tag36 = "buffer~";
    	static constexpr auto& name37 = "gen_02_delay_12_bufferobj";
    	static constexpr auto& file37 = "";
    	static constexpr auto& tag37 = "buffer~";
    	static constexpr auto& name38 = "gen_02_delay_13_bufferobj";
    	static constexpr auto& file38 = "";
    	static constexpr auto& tag38 = "buffer~";
    	static constexpr auto& name39 = "gen_02_delay_14_bufferobj";
    	static constexpr auto& file39 = "";
    	static constexpr auto& tag39 = "buffer~";
    	static constexpr auto& name40 = "gen_02_delay_15_bufferobj";
    	static constexpr auto& file40 = "";
    	static constexpr auto& tag40 = "buffer~";
    	static constexpr auto& name41 = "gen_02_delay_16_bufferobj";
    	static constexpr auto& file41 = "";
    	static constexpr auto& tag41 = "buffer~";
    	static constexpr auto& name42 = "gen_02_delay_17_bufferobj";
    	static constexpr auto& file42 = "";
    	static constexpr auto& tag42 = "buffer~";
    	static constexpr auto& name43 = "gen_02_delay_18_bufferobj";
    	static constexpr auto& file43 = "";
    	static constexpr auto& tag43 = "buffer~";
    	DataRefStrings* operator->() { return this; }
    	const DataRefStrings* operator->() const { return this; }
    };

    DataRefStrings dataRefStrings;

// member variables

    number param_01_value;
    list scale_04_input;
    number scale_04_inlow;
    number scale_04_inhigh;
    number scale_04_outlow;
    number scale_04_outhigh;
    number scale_04_power;
    list scale_04_out;
    number param_02_value;
    number slide_01_x;
    number slide_01_up;
    number slide_01_down;
    number slide_02_x;
    number slide_02_up;
    number slide_02_down;
    list scale_05_input;
    number scale_05_inlow;
    number scale_05_inhigh;
    number scale_05_outlow;
    number scale_05_outhigh;
    number scale_05_power;
    list scale_05_out;
    number numberobj_14_value;
    number param_03_value;
    number dcblock_tilde_01_x;
    number dcblock_tilde_01_gain;
    number dspexpr_05_in1;
    number dspexpr_05_in2;
    number dspexpr_05_in3;
    number p_01_target;
    number gen_01_in1;
    number gen_01_in2;
    number gen_01_xover;
    number gen_01_lfo1_bw;
    number gen_01_decay;
    number gen_01_lfo1_rate;
    number gen_01_InGain;
    number gen_01_fbc;
    number gen_01_lpf;
    number gen_01_mult;
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
    number gen_02_lfo1_rate;
    number gen_02_pre_del;
    number gen_02_decay2;
    number gen_02_lpf;
    number gen_02_lfo1_bw;
    number gen_02_apf_g;
    number gen_02_diff_gain;
    number dcblock_tilde_02_x;
    number dcblock_tilde_02_gain;
    number dspexpr_06_in1;
    number dspexpr_06_in2;
    number dspexpr_06_in3;
    number dcblock_tilde_03_x;
    number dcblock_tilde_03_gain;
    number p_06_target;
    number p_07_target;
    number dcblock_tilde_04_x;
    number dcblock_tilde_04_gain;
    number toggle_02_value_number;
    number param_04_value;
    number numberobj_15_value;
    number param_05_value;
    number numberobj_16_value;
    number numberobj_17_value;
    number expr_06_in1;
    number expr_06_in2;
    number expr_06_out1;
    list linetilde_09_segments;
    number linetilde_09_time;
    number linetilde_09_keepramp;
    number numberobj_18_value;
    number param_06_value;
    number snapshot_01_interval;
    number snapshot_01_out;
    number numberobj_19_value;
    number param_07_value;
    number numberobj_20_value;
    number numberobj_21_value;
    number param_08_value;
    number param_09_value;
    number param_10_value;
    number numberobj_22_value;
    number param_11_value;
    number param_12_value;
    list scale_06_input;
    number scale_06_inlow;
    number scale_06_inhigh;
    number scale_06_outlow;
    number scale_06_outhigh;
    number scale_06_power;
    list scale_06_out;
    number numberobj_23_value;
    number param_13_value;
    list message_01_set;
    list scale_07_input;
    number scale_07_inlow;
    number scale_07_inhigh;
    number scale_07_outlow;
    number scale_07_outhigh;
    number scale_07_power;
    list scale_07_out;
    number param_14_value;
    number numberobj_24_value;
    list scale_08_input;
    number scale_08_inlow;
    number scale_08_inhigh;
    number scale_08_outlow;
    number scale_08_outhigh;
    number scale_08_power;
    list scale_08_out;
    number param_15_value;
    number param_16_value;
    list scale_09_input;
    number scale_09_inlow;
    number scale_09_inhigh;
    number scale_09_outlow;
    number scale_09_outhigh;
    number scale_09_power;
    list scale_09_out;
    number param_17_value;
    number numberobj_25_value;
    number param_18_value;
    number numberobj_26_value;
    number param_19_value;
    number param_20_value;
    number numberobj_27_value;
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
    number expr_07_in1;
    number expr_07_in2;
    number expr_07_out1;
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
    number ctlin_09_input;
    number ctlin_09_controller;
    number ctlin_09_channel;
    number expr_13_in1;
    number expr_13_in2;
    number expr_13_out1;
    number ctlin_10_input;
    number ctlin_10_controller;
    number ctlin_10_channel;
    number expr_14_in1;
    number expr_14_in2;
    number expr_14_out1;
    MillisecondTime _currentTime;
    ENGINE _internalEngine;
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
    number slide_01_prev;
    number slide_02_prev;
    Int numberobj_14_currentFormat;
    number numberobj_14_lastValue;
    number param_03_lastValue;
    number dcblock_tilde_01_xm1;
    number dcblock_tilde_01_ym1;
    bool dcblock_tilde_01_setupDone;
    number gen_01_history_1_value;
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
    number gen_01_history_2_value;
    number gen_01_history_3_value;
    number gen_01_history_4_value;
    number gen_01_history_5_value;
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
    number gen_01_history_6_value;
    number gen_01_history_7_value;
    number gen_01_history_8_value;
    number gen_01_history_9_value;
    number gen_01_history_10_value;
    number gen_01_slide_0_prev;
    number gen_01_slide_2_prev;
    number gen_01_phasor_6_currentPhase;
    number gen_01_phasor_6_conv;
    number gen_01_cycle_8_ph_currentPhase;
    number gen_01_cycle_8_ph_conv;
    SampleBufferRef gen_01_cycle_8_buffer;
    Int gen_01_cycle_8_wrap;
    UInt32 gen_01_cycle_8_phasei;
    SampleValue gen_01_cycle_8_f2i;
    number gen_01_cycle_13_ph_currentPhase;
    number gen_01_cycle_13_ph_conv;
    SampleBufferRef gen_01_cycle_13_buffer;
    Int gen_01_cycle_13_wrap;
    UInt32 gen_01_cycle_13_phasei;
    SampleValue gen_01_cycle_13_f2i;
    number gen_01_cycle_18_ph_currentPhase;
    number gen_01_cycle_18_ph_conv;
    SampleBufferRef gen_01_cycle_18_buffer;
    Int gen_01_cycle_18_wrap;
    UInt32 gen_01_cycle_18_phasei;
    SampleValue gen_01_cycle_18_f2i;
    number gen_01_cycle_23_ph_currentPhase;
    number gen_01_cycle_23_ph_conv;
    SampleBufferRef gen_01_cycle_23_buffer;
    Int gen_01_cycle_23_wrap;
    UInt32 gen_01_cycle_23_phasei;
    SampleValue gen_01_cycle_23_f2i;
    number gen_01_cycle_28_ph_currentPhase;
    number gen_01_cycle_28_ph_conv;
    SampleBufferRef gen_01_cycle_28_buffer;
    Int gen_01_cycle_28_wrap;
    UInt32 gen_01_cycle_28_phasei;
    SampleValue gen_01_cycle_28_f2i;
    number gen_01_cycle_33_ph_currentPhase;
    number gen_01_cycle_33_ph_conv;
    SampleBufferRef gen_01_cycle_33_buffer;
    Int gen_01_cycle_33_wrap;
    UInt32 gen_01_cycle_33_phasei;
    SampleValue gen_01_cycle_33_f2i;
    number gen_01_cycle_38_ph_currentPhase;
    number gen_01_cycle_38_ph_conv;
    SampleBufferRef gen_01_cycle_38_buffer;
    Int gen_01_cycle_38_wrap;
    UInt32 gen_01_cycle_38_phasei;
    SampleValue gen_01_cycle_38_f2i;
    number gen_01_cycle_43_ph_currentPhase;
    number gen_01_cycle_43_ph_conv;
    SampleBufferRef gen_01_cycle_43_buffer;
    Int gen_01_cycle_43_wrap;
    UInt32 gen_01_cycle_43_phasei;
    SampleValue gen_01_cycle_43_f2i;
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
    number gen_02_history_10_value;
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
    Float64BufferRef gen_02_delay_16_buffer;
    Index gen_02_delay_16__maxdelay;
    Int gen_02_delay_16_sizemode;
    Index gen_02_delay_16_wrap;
    Int gen_02_delay_16_reader;
    Int gen_02_delay_16_writer;
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
    number gen_02_history_19_value;
    number gen_02_slide_4_prev;
    number gen_02_phasor_15_currentPhase;
    number gen_02_phasor_15_conv;
    number gen_02_cycle_17_ph_currentPhase;
    number gen_02_cycle_17_ph_conv;
    SampleBufferRef gen_02_cycle_17_buffer;
    Int gen_02_cycle_17_wrap;
    UInt32 gen_02_cycle_17_phasei;
    SampleValue gen_02_cycle_17_f2i;
    number gen_02_cycle_26_ph_currentPhase;
    number gen_02_cycle_26_ph_conv;
    SampleBufferRef gen_02_cycle_26_buffer;
    Int gen_02_cycle_26_wrap;
    UInt32 gen_02_cycle_26_phasei;
    SampleValue gen_02_cycle_26_f2i;
    number gen_02_cycle_36_ph_currentPhase;
    number gen_02_cycle_36_ph_conv;
    SampleBufferRef gen_02_cycle_36_buffer;
    Int gen_02_cycle_36_wrap;
    UInt32 gen_02_cycle_36_phasei;
    SampleValue gen_02_cycle_36_f2i;
    number gen_02_cycle_45_ph_currentPhase;
    number gen_02_cycle_45_ph_conv;
    SampleBufferRef gen_02_cycle_45_buffer;
    Int gen_02_cycle_45_wrap;
    UInt32 gen_02_cycle_45_phasei;
    SampleValue gen_02_cycle_45_f2i;
    number gen_02_cycle_54_ph_currentPhase;
    number gen_02_cycle_54_ph_conv;
    SampleBufferRef gen_02_cycle_54_buffer;
    Int gen_02_cycle_54_wrap;
    UInt32 gen_02_cycle_54_phasei;
    SampleValue gen_02_cycle_54_f2i;
    number gen_02_cycle_63_ph_currentPhase;
    number gen_02_cycle_63_ph_conv;
    SampleBufferRef gen_02_cycle_63_buffer;
    Int gen_02_cycle_63_wrap;
    UInt32 gen_02_cycle_63_phasei;
    SampleValue gen_02_cycle_63_f2i;
    number gen_02_cycle_74_ph_currentPhase;
    number gen_02_cycle_74_ph_conv;
    SampleBufferRef gen_02_cycle_74_buffer;
    Int gen_02_cycle_74_wrap;
    UInt32 gen_02_cycle_74_phasei;
    SampleValue gen_02_cycle_74_f2i;
    number gen_02_cycle_87_ph_currentPhase;
    number gen_02_cycle_87_ph_conv;
    SampleBufferRef gen_02_cycle_87_buffer;
    Int gen_02_cycle_87_wrap;
    UInt32 gen_02_cycle_87_phasei;
    SampleValue gen_02_cycle_87_f2i;
    number gen_02_slide_104_prev;
    number gen_02_dcblock_172_xm1;
    number gen_02_dcblock_172_ym1;
    number gen_02_dcblock_237_xm1;
    number gen_02_dcblock_237_ym1;
    bool gen_02_setupDone;
    number dcblock_tilde_02_xm1;
    number dcblock_tilde_02_ym1;
    bool dcblock_tilde_02_setupDone;
    number dcblock_tilde_03_xm1;
    number dcblock_tilde_03_ym1;
    bool dcblock_tilde_03_setupDone;
    number dcblock_tilde_04_xm1;
    number dcblock_tilde_04_ym1;
    bool dcblock_tilde_04_setupDone;
    number toggle_02_lastValue;
    number param_04_lastValue;
    Int numberobj_15_currentFormat;
    number numberobj_15_lastValue;
    number param_05_lastValue;
    Int numberobj_16_currentFormat;
    number numberobj_16_lastValue;
    Int numberobj_17_currentFormat;
    number numberobj_17_lastValue;
    list linetilde_09_activeRamps;
    number linetilde_09_currentValue;
    Int numberobj_18_currentFormat;
    number numberobj_18_lastValue;
    number param_06_lastValue;
    number snapshot_01_calc;
    number snapshot_01_nextTime;
    SampleIndex snapshot_01_count;
    number snapshot_01_lastValue;
    Int numberobj_19_currentFormat;
    number numberobj_19_lastValue;
    number param_07_lastValue;
    Int numberobj_20_currentFormat;
    number numberobj_20_lastValue;
    Int numberobj_21_currentFormat;
    number numberobj_21_lastValue;
    number param_08_lastValue;
    number param_09_lastValue;
    number param_10_lastValue;
    Int numberobj_22_currentFormat;
    number numberobj_22_lastValue;
    number param_11_lastValue;
    number param_12_lastValue;
    Int numberobj_23_currentFormat;
    number numberobj_23_lastValue;
    number param_13_lastValue;
    number param_14_lastValue;
    Int numberobj_24_currentFormat;
    number numberobj_24_lastValue;
    number param_15_lastValue;
    number param_16_lastValue;
    number param_17_lastValue;
    Int numberobj_25_currentFormat;
    number numberobj_25_lastValue;
    number param_18_lastValue;
    Int numberobj_26_currentFormat;
    number numberobj_26_lastValue;
    number param_19_lastValue;
    number param_20_lastValue;
    Int numberobj_27_currentFormat;
    number numberobj_27_lastValue;
    Int ctlin_01_status;
    Int ctlin_01_byte1;
    Int ctlin_01_inchan;
    Int ctlin_02_status;
    Int ctlin_02_byte1;
    Int ctlin_02_inchan;
    Int ctlin_03_status;
    Int ctlin_03_byte1;
    Int ctlin_03_inchan;
    Int ctlin_04_status;
    Int ctlin_04_byte1;
    Int ctlin_04_inchan;
    Int ctlin_05_status;
    Int ctlin_05_byte1;
    Int ctlin_05_inchan;
    Int ctlin_06_status;
    Int ctlin_06_byte1;
    Int ctlin_06_inchan;
    Int ctlin_07_status;
    Int ctlin_07_byte1;
    Int ctlin_07_inchan;
    Int ctlin_08_status;
    Int ctlin_08_byte1;
    Int ctlin_08_inchan;
    Int ctlin_09_status;
    Int ctlin_09_byte1;
    Int ctlin_09_inchan;
    Int ctlin_10_status;
    Int ctlin_10_byte1;
    Int ctlin_10_inchan;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
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
    DataRef gen_02_delay_11_bufferobj;
    DataRef gen_02_delay_12_bufferobj;
    DataRef gen_02_delay_13_bufferobj;
    DataRef gen_02_delay_14_bufferobj;
    DataRef gen_02_delay_15_bufferobj;
    DataRef gen_02_delay_16_bufferobj;
    DataRef gen_02_delay_17_bufferobj;
    DataRef gen_02_delay_18_bufferobj;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_72 p_01;
    RNBOSubpatcher_73 p_02;
    RNBOSubpatcher_74 p_03;
    RNBOSubpatcher_75 p_04;
    RNBOSubpatcher_76 p_05;
    RNBOSubpatcher_77 p_06;
    RNBOSubpatcher_78 p_07;

};

static PatcherInterface* creaternbomatic()
{
    return new rnbomatic<EXTERNALENGINE>();
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction()
#else
extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction()
#endif
{
    return creaternbomatic;
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" void SetLogger(Logger* logger)
#else
void rnbomaticSetLogger(Logger* logger)
#endif
{
    console = logger;
}

} // end RNBO namespace

