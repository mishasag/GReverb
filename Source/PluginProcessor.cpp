/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_core/juce_core.h"
#include "PluginEditor.h"
#include "ParamIDs.h"


/*using namespace RNBO;

class LoggingMessageHandler : public RNBO::EventHandler {
public:
    LoggingMessageHandler(PluginProcessor& processor, std::function<RNBO::MessageTagInfo(RNBO::MessageTag)> tagResolver)
        : m_processor(processor), tagResolver(tagResolver) {}

    void eventsAvailable() override {
        DBG("Events available to drain.");
        drainEvents();
        DBG("Finished draining events.");
    }

private:
    void handleMessageEvent(const RNBO::MessageEvent& event) override {
        if (event.getType() == RNBO::MessageEvent::Bang) {
            std::cout << "Received bang with tag " << tagResolver(event.getTag()) << "\n";
        } else if (event.getType() == RNBO::MessageEvent::Number) {
            double value = event.getNumValue();
            DBG("Received value " << value << " with tag " << tagResolver(event.getTag()));
            m_processor.setRT60Value(value); // Update RT60Value in PluginProcessor
        } else if (event.getType() == RNBO::MessageEvent::List) {
            DBG("Received list value with tag " << tagResolver(event.getTag()));
            auto list = event.getListValue().get();
            for (int i = 0; i < list->length; i++) {
                DBG("List item [" << i << "]: " << list->operator[](i));
            }
        }
    }

    PluginProcessor& m_processor; // Reference to PluginProcessor for updating RT60Value
    std::function<RNBO::MessageTagInfo(RNBO::MessageTag)> tagResolver; // Function to resolve tags
};
*/

namespace ParameterAttributes
{

const auto percent = juce::AudioParameterFloatAttributes().withStringFromValueFunction (
    // Format the number to always display three digits like "0.01 %", "10.0 %", "100 %".
    [] (auto value, auto)
    {
      constexpr auto unit = " %";

      if (auto v { std::round (value * 100.0f) / 100.0f }; v < 10.0f)
          return juce::String { v, 2 } + unit;

      if (auto v { std::round (value * 10.0f) / 10.0f }; v < 100.0f)
          return juce::String { v, 1 } + unit;

      return juce::String { std::round (value) } + unit;
    });

const auto ms = juce::AudioParameterFloatAttributes().withStringFromValueFunction (
    // Format the number to always display three digits like "10.0 ms", "100 ms".
    [] (auto value, auto)
    {
      constexpr auto unit = " ms";

      if (auto v { std::round (value * 10.0f) / 10.0f }; v < 100.0f)
          return juce::String { v, 1 } + unit;

      return juce::String { std::round (value) } + unit;
    });
    
    const auto hz = juce::AudioParameterFloatAttributes().withStringFromValueFunction (
        // Format the number to always display three digits like "10.0 ms", "100 ms".
        [] (auto value, auto)
        {
          constexpr auto unit = " hz";

          if (auto v { std::round (value * 10.0f) / 10.0f }; v < 100.0f)
              return juce::String { v, 1 } + unit;

          return juce::String { std::round (value) } + unit;
        });

const auto db = juce::AudioParameterFloatAttributes().withStringFromValueFunction (
    // Format the number to always display two digits like "0.1 dB", "10 dB".
    [] (auto value, auto)
    {
      constexpr auto unit = " dB";

      if (auto v { std::round (value * 10.0f) / 10.0f }; -10.0f < v && v < 10.0f)
          return juce::String { v, 1 } + unit;

      return juce::String { std::round (value) } + unit;
    });

const auto semitone = juce::AudioParameterFloatAttributes().withStringFromValueFunction (
    [] (auto value, auto)
    {
      constexpr auto unit = " st";
      return juce::String { value, 1 } + unit;
    });

} // namespace ParameterAttributes


static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    layout.add (std::make_unique<juce::AudioParameterBool> (juce::ParameterID { ParamIDs::lowcut, 1 }, ParamIDs::lowcut, true));
    
    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::low_cut, 1 },
                                                 "low cut",
                                                 juce::NormalisableRange<float> (10.0f, 800.0f, 0.01f, 0.5f),
                                                 20.0f,
                                                 ParameterAttributes::hz));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::post_level, 1 },
                                                 "out",
                                                 juce::NormalisableRange<float> (-100.0f, 100.0f, 0.01f, 1.0f),
                                                 0.0f,
                                                 ParameterAttributes::percent));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::preq_level, 1 },
                                                 "in",
                                                 juce::NormalisableRange<float> (-100.0f, 100.0f, 0.01f, 1.0f),
                                                 0.0f,
                                                 ParameterAttributes::percent));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::r_Feedback, 1 },
                                                 "decay",
                                                 juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 0.5f),
                                                 50.0f,
                                                 ParameterAttributes::percent));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::r_InGain, 1 },
                                                 ParamIDs::r_InGain,
                                                 juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                                 70.0f,
                                                 ParameterAttributes::percent));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::lfo1_rate, 1 },
                                                 "mod rate",
                                                 juce::NormalisableRange<float> (0.0f, 3.0f, 0.01f, 0.5f),
                                                 0.2f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                 
                                                 nullptr));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::r_Damp, 1 },
                                                 "damping",
                                                 juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                                 10.0f,
                                                 ParameterAttributes::percent));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::apf_g, 1 },
                                                 "early shape",
                                                 juce::NormalisableRange<float> (0.0f, 10.0f, 0.01f, 1.0f),
                                                 5.0f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                 
                                                 nullptr));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::mix, 1 },
                                                 "mix",
                                                 juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                                 50.0f,
                                                 ParameterAttributes::percent));


    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::pre_del, 1 },
                                                 "pre delay",
                                                 juce::NormalisableRange<float> (0.0f, 500.0f, 0.01f, 1.0f),
                                                 20.0f,
                                                 ParameterAttributes::ms));


    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::Size, 1 },
                                                 "size",
                                                 juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                                 50.0f,
                                                 ParameterAttributes::percent));


    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::himidfq, 1 },
                                                 "brightness",
                                                 juce::NormalisableRange<float> (1000.0f, 8000.0f, 0.01f, 0.5f),
                                                 2000.0f,
                                                 ParameterAttributes::hz));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::high_cut, 1 },
                                                 "high cut",
                                                 juce::NormalisableRange<float> (1000.0f, 16000.0f, 0.01f, 0.5f),
                                                 8000.0f,
                                                 ParameterAttributes::hz));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::lfo1_bw, 1 },
                                                 "mod amount",
                                                 juce::NormalisableRange<float> (0.0f, 2.0f, 0.01f, 0.8f),
                                                 0.3f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                 
                                                 nullptr));
    
    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::xover, 1 },
                                                 "bass freq",
                                                 juce::NormalisableRange<float> (100.0f, 2000.0f, 0.01f, 0.5f),
                                                 300.0f,
                                                 ParameterAttributes::hz));
    
    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::bass_mult, 1 },
                                                 "bass mult",
                                                 juce::NormalisableRange<float> (0.25f, 2.0f, 0.01f, 1.0f),
                                                 1.0f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                 
                                                 nullptr));
    
    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::rt60_param, 1 },
                                                 ParamIDs::rt60_param,
                                                 juce::NormalisableRange<float> (0.0f, 6907.0f, 0.01f, 1.0f),
                                                 0.0f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                 
                                                 nullptr));
    
    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::himid_qf, 1 },
                                                 "qf",
                                                 juce::NormalisableRange<float> (0.25f, 5.0f, 0.01f, 1.0f),
                                                 0.25f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                 
                                                 nullptr));
    
    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::himid_lev, 1 },
                                                             "gain",
                                                 juce::NormalisableRange<float> (-18.0f, 18.0f, 0.01f, 1.0f),
                                                 10.0f,
                                                             ParameterAttributes::db));
 
    
    return layout;
}


PluginProcessor::PluginProcessor()
    : AudioProcessor (BusesProperties()
                          .withInput ("Input", juce::AudioChannelSet::stereo(), true)
                          .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
    , apvts (*this, &undoManager, "Parameters", createParameterLayout())
    
{
    
    
    
    //double currentRT60Value = rnboObject.getParameterValue(rnboObject.getParameterIndexForID("rt60_param"));
    //this->rt60Value = currentRT60Value;

    //DBG("RT60 Param Value (from processBlock): " << this->rt60Value);
    
    
    
    for (RNBO::ParameterIndex i = 0; i < rnboObject.getNumParameters(); ++i)
    {
        RNBO::ParameterInfo info;
        rnboObject.getParameterInfo (i, &info);

        if (info.visible)
        {
            auto paramID = juce::String (rnboObject.getParameterId (i));

            // Each apvts parameter id and range must be the same as the rnbo param object's.
            // If you hit this assertion then you need to fix the incorrect id in ParamIDs.h.
            jassert (apvts.getParameter (paramID) != nullptr);

            // If you hit these assertions then you need to fix the incorrect apvts
            // parameter range in createParameterLayout().
            jassert (info.min == apvts.getParameterRange (paramID).start);
            jassert (info.max == apvts.getParameterRange (paramID).end);

            apvtsParamIdToRnboParamIndex[paramID] = i;

            apvts.addParameterListener (paramID, this);
            rnboObject.setParameterValue (i, apvts.getRawParameterValue (paramID)->load());
        }
    }
}

PluginProcessor::~PluginProcessor() {}

const juce::String PluginProcessor::getName() const { return JucePlugin_Name; }

bool PluginProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool PluginProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool PluginProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double PluginProcessor::getTailLengthSeconds() const { return 0.0; }

int PluginProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
        // so this should be at least 1, even if you're not really implementing programs.
}

int PluginProcessor::getCurrentProgram() { return 0; }

void PluginProcessor::setCurrentProgram (int index) { juce::ignoreUnused (index); }

const juce::String PluginProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void PluginProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)

{
    
    
    rnboObject.prepareToProcess(sampleRate, static_cast<size_t>(samplesPerBlock));
    
    double initialRT60Value = rnboObject.getParameterValue(rnboObject.getParameterIndexForID("rt60_param"));
    setRT60Value(initialRT60Value);

    smoothedInputLevel.reset(sampleRate, 0.5f);   // Reset with a valid sample rate
    smoothedOutputLevel.reset(sampleRate, 0.5f);

}

float PluginProcessor::calculateRMSLevel(const juce::AudioBuffer<float>& buffer) {
    float peakLevel = 0.0f;
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        peakLevel = juce::jmax(peakLevel, buffer.getRMSLevel(channel, 0, buffer.getNumSamples()));
    }
    return peakLevel;
}

/*void PluginProcessor::setRT60Value(double newValue) {
    rt60Value = newValue;
    DBG("PluginProcessor - Updated RT60Value to: " << rt60Value);
}*/


void PluginProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannelSet()  == juce::AudioChannelSet::disabled()
     || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::disabled())
        return false;

    // Force stereo output
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // Allow mono or stereo in
    const auto& inSet = layouts.getMainInputChannelSet();
    if (inSet == juce::AudioChannelSet::mono() || inSet == juce::AudioChannelSet::stereo())
        return true;

    return false;
}


void PluginProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                   juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(midiMessages);

    const int totalNumInputChannels  = getTotalNumInputChannels();   // 1 or 2
    const int totalNumOutputChannels = getTotalNumOutputChannels();  // in this setup, always 2 (stereo)
    const int bufferSize             = buffer.getNumSamples();

    // Clear any extra channels (e.g. if 1 in, 2 out)
    for (int ch = totalNumInputChannels; ch < totalNumOutputChannels; ++ch)
        buffer.clear(ch, 0, bufferSize);

    static int rmsUpdateCounter = 0;
    ++rmsUpdateCounter;

    if (rmsUpdateCounter >= 30)
    {
        rmsUpdateCounter = 0;
        smoothedInputLevel.setTargetValue(calculateRMSLevel(buffer));
    }


    // If we have mono input but stereo output, copy mono into second channel
    if (totalNumInputChannels == 1 && totalNumOutputChannels == 2)
    {
        const float* readPtrCh0 = buffer.getReadPointer(0);
        float* writePtrCh1      = buffer.getWritePointer(1);

        for (int i = 0; i < bufferSize; ++i)
            writePtrCh1[i] = readPtrCh0[i];
    }

    // Now call RNBO with 2 channels in/out so it sees true stereo
    rnboObject.process(
        buffer.getArrayOfWritePointers(),  // pointers to input data
        2,                                 // force 2 in
        buffer.getArrayOfWritePointers(),  // pointers to output
        2,                                 // 2 out
        static_cast<RNBO::Index>(bufferSize)
    );

    // Update output RMS if we just reset the counter
    if (rmsUpdateCounter == 0)
        smoothedOutputLevel.setTargetValue(calculateRMSLevel(buffer));

//    // Optionally get RT60
double currentRT60Value = rnboObject.getParameterValue(
        rnboObject.getParameterIndexForID("rt60_param"));
        setRT60Value(currentRT60Value);

    // Smooth RMS transitions
    smoothedInputLevel.skip(bufferSize);
    smoothedOutputLevel.skip(bufferSize);
}





//void PluginProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
//    juce::ignoreUnused(midiMessages);
//    auto bufferSize = buffer.getNumSamples();
//
//    static int rmsUpdateCounter = 0;
//        if (++rmsUpdateCounter >= 30) { // Update RMS levels every 30 blocks
//            rmsUpdateCounter = 0;
//
//            // Calculate peak input level BEFORE RNBO processing
//            float peakInputLevel = 0.0f;
//            for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
//                peakInputLevel = juce::jmax(peakInputLevel, buffer.getRMSLevel(channel, 0, bufferSize));
//            }
//            smoothedInputLevel.setTargetValue(peakInputLevel);
//        }
//
//        // Smooth input level skipping for every block
//        smoothedInputLevel.skip(bufferSize);
//
//    // RNBO processing
//    rnboObject.prepareToProcess(getSampleRate(), static_cast<size_t>(bufferSize));
//    rnboObject.process(buffer.getArrayOfWritePointers(),
//                       static_cast<RNBO::Index>(buffer.getNumChannels()),
//                       buffer.getArrayOfWritePointers(),
//                       static_cast<RNBO::Index>(buffer.getNumChannels()),
//                       static_cast<RNBO::Index>(bufferSize));
//    
//    
//    if (rmsUpdateCounter == 0) { // Update peak output level when RMS is updated
//            // Calculate peak output level AFTER RNBO processing
//            float peakOutputLevel = 0.0f;
//            for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
//                peakOutputLevel = juce::jmax(peakOutputLevel, buffer.getRMSLevel(channel, 0, bufferSize));
//            }
//            smoothedOutputLevel.setTargetValue(peakOutputLevel);
//            
//            double currentRT60Value = rnboObject.getParameterValue(rnboObject.getParameterIndexForID("rt60_param"));
//            setRT60Value(currentRT60Value);
//        }
//
//        // Smooth output level skipping for every block
//        smoothedOutputLevel.skip(bufferSize);
//
//    
//
//    // Fetch and update RT60 value
//    double currentRT60Value = rnboObject.getParameterValue(rnboObject.getParameterIndexForID("rt60_param"));
//    setRT60Value(currentRT60Value);
//}


/*void PluginProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);
    auto bufferSize = buffer.getNumSamples();
    
    
    /// Calculate peak input level before RNBO processing
    float peakInputLevel = 0.0f;
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        peakInputLevel = juce::jmax(peakInputLevel, buffer.getRMSLevel(channel, 0, buffer.getNumSamples()));
    }
    
    // Set the target for the smoothed input level
    smoothedInputLevel.setTargetValue(peakInputLevel);
    smoothedInputLevel.skip(buffer.getNumSamples());  // Advance by one buffer
    //messageHandler->eventsAvailable();
    rnboObject.prepareToProcess (getSampleRate(),
                                 static_cast<size_t> (bufferSize));
 
    rnboObject.process (buffer.getArrayOfWritePointers(),
                        static_cast<RNBO::Index> (buffer.getNumChannels()),
                        buffer.getArrayOfWritePointers(),
                        static_cast<RNBO::Index> (buffer.getNumChannels()),
                        static_cast<RNBO::Index> (bufferSize));
    
    
    // Fetch and update RT60 value
        double currentRT60Value = rnboObject.getParameterValue(rnboObject.getParameterIndexForID("rt60_param"));
        setRT60Value(currentRT60Value); // Use setRT60Value to update and log the value
    
    float peakOutputLevel = 0.0f;
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            peakOutputLevel = juce::jmax(peakOutputLevel, buffer.getRMSLevel(channel, 0, buffer.getNumSamples()));
        }

        // Set the target for the smoothed output level
        smoothedOutputLevel.setTargetValue(peakOutputLevel);
        smoothedOutputLevel.skip(buffer.getNumSamples());
        

}*/
double PluginProcessor::getRT60Value() const {
    
    return rt60Value;
    //DBG("PluginProcessor::getRT60Value() - rt60Value: " << rt60Value);
}

void PluginProcessor::setRT60Value(double newValue) {
    rt60Value = newValue;
    //DBG("PluginProcessor - Updated RT60Value to: " << rt60Value);
}



bool PluginProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginProcessor::createEditor() { return new PluginEditor (*this, apvts, undoManager); }

void PluginProcessor::getStateInformation(juce::MemoryBlock& destData) {
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);

        // Use static getters to access default width and height
        auto editorState = apvts.state.getOrCreateChildWithName("editor", nullptr);
        mos.writeInt(editorState.getProperty("width", PluginEditor::getDefaultWidth()));
        mos.writeInt(editorState.getProperty("height", PluginEditor::getDefaultHeight()));
}

void PluginProcessor::setStateInformation(const void* data, int sizeInBytes) {
    if (const auto tree = juce::ValueTree::readFromData(data, static_cast<size_t>(sizeInBytes)); tree.isValid()) {
        apvts.replaceState(tree);

        // Retrieve size information
        juce::MemoryInputStream mis(data, static_cast<size_t>(sizeInBytes), false);
        mis.skipNextBytes(static_cast<int>(tree.toXmlString().getNumBytesAsUTF8())); // Skip ValueTree data
        auto width = mis.readInt();
        auto height = mis.readInt();

        auto editorState = apvts.state.getOrCreateChildWithName("editor", nullptr);
        editorState.setProperty("width", width, nullptr);
        editorState.setProperty("height", height, nullptr);
    }
}






/*void PluginProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos (destData, true);
    apvts.state.writeToStream (mos);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (const auto tree = juce::ValueTree::readFromData (data, static_cast<size_t> (sizeInBytes)); tree.isValid())
        apvts.replaceState (tree);
}*/

void PluginProcessor::parameterChanged (const juce::String& parameterID, float newValue)
{
    rnboObject.setParameterValue (apvtsParamIdToRnboParamIndex[parameterID], newValue);
}
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new PluginProcessor(); }
