/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParamIDs.h"
//

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
                                                 ParamIDs::low_cut,
                                                 juce::NormalisableRange<float> (10.0f, 1500.0f, 0.01f, 2.25f),
                                                 20.0f,
                                                 ParameterAttributes::hz));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::post_level, 1 },
                                                 ParamIDs::post_level,
                                                 juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                                 50.0f,
                                                 ParameterAttributes::percent));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::preq_level, 1 },
                                                 ParamIDs::preq_level,
                                                 juce::NormalisableRange<float> (-100.0f, 100.0f, 0.01f, 1.0f),
                                                 0.0f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                 
                                                 nullptr));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::r_Feedback, 1 },
                                                 ParamIDs::r_Feedback,
                                                 juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                                 50.0f,
                                                 ParameterAttributes::percent));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::r_InGain, 1 },
                                                 ParamIDs::r_InGain,
                                                 juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                                 90.0f,
                                                 ParameterAttributes::percent));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::lfo1_rate, 1 },
                                                 ParamIDs::lfo1_rate,
                                                 juce::NormalisableRange<float> (0.0f, 5.0f, 0.01f, 0.1f),
                                                 0.3f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                 
                                                 nullptr));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::r_Damp, 1 },
                                                 ParamIDs::r_Damp,
                                                 juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                                 20.0f,
                                                 ParameterAttributes::percent));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::apf_g, 1 },
                                                 ParamIDs::apf_g,
                                                 juce::NormalisableRange<float> (-0.99f, 0.99f, 0.01f, 0.01f),
                                                 0.635f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                 
                                                 nullptr));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::mix, 1 },
                                                 ParamIDs::mix,
                                                 juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                                 50.0f,
                                                 ParameterAttributes::percent));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::diff_num, 1 },
                                                 ParamIDs::diff_num,
                                                 juce::NormalisableRange<float> (1.0f, 4.0f, 0.01f, 1.0f),
                                                 4.0f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                
                                                 nullptr));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::pre_del, 1 },
                                                 ParamIDs::pre_del,
                                                 juce::NormalisableRange<float> (0.0f, 500.0f, 0.01f, 1.0f),
                                                 0.0f,
                                                 ParameterAttributes::ms));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::fb1, 1 },
                                                 ParamIDs::fb1,
                                                 juce::NormalisableRange<float> (0.0f, 0.9f, 0.01f, 0.01f),
                                                 0.1f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                 
                                                 nullptr));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::x_fb, 1 },
                                                 ParamIDs::x_fb,
                                                 juce::NormalisableRange<float> (0.0f, 0.9f, 0.01f, 0.01f),
                                                 0.1f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                
                                                 nullptr));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::Size, 1 },
                                                 ParamIDs::Size,
                                                 juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                                 60.0f,
                                                 ParameterAttributes::percent));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::himid_lev, 1 },
                                                 ParamIDs::himid_lev,
                                                 juce::NormalisableRange<float> (-100.0f, 100.0f, 0.01f, 1.0f),
                                                 0.0f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                 
                                                 nullptr));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::himidfq, 1 },
                                                 ParamIDs::himidfq,
                                                 juce::NormalisableRange<float> (-100.0f, 100.0f, 0.01f, 1.0f),
                                                 0.0f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                 
                                                 nullptr));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::high_cut, 1 },
                                                 ParamIDs::high_cut,
                                                 juce::NormalisableRange<float> (300.0f, 20000.0f, 0.01f, 2.25f),
                                                 8000.0f,
                                                 ParameterAttributes::hz));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::lfo1_bw, 1 },
                                                 ParamIDs::lfo1_bw,
                                                 juce::NormalisableRange<float> (0.0f, 2.0f, 0.01f, 0.1f),
                                                 0.3f,
                                                 juce::String(),
                                                 juce::AudioProcessorParameter::genericParameter,
                                                 
                                                 nullptr));
 
 
    return layout;
}
 
//==============================================================================
RNBOGReverbAudioProcessor::RNBOGReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
       apvts (*this, &undoManager, "Parameters", createParameterLayout())
{
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
 
RNBOGReverbAudioProcessor::~RNBOGReverbAudioProcessor()
{
}
 
//==============================================================================
const juce::String RNBOGReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}
 
bool RNBOGReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}
 
bool RNBOGReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}
 
bool RNBOGReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}
 
double RNBOGReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
 
int RNBOGReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}
 
int RNBOGReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}
 
void RNBOGReverbAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}
 
const juce::String RNBOGReverbAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}
 
void RNBOGReverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}
 
//==============================================================================
void RNBOGReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    rnboObject.prepareToProcess (sampleRate, static_cast<size_t> (samplesPerBlock));
}
 
void RNBOGReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}
 
#ifndef JucePlugin_PreferredChannelConfigurations
bool RNBOGReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
 
    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif
 
    return true;
  #endif
}
#endif
 
void RNBOGReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);
    auto bufferSize = buffer.getNumSamples();
 
   /* rnboObject.prepareToProcess (getSampleRate(),
                                 static_cast<size_t> (bufferSize)); */
 
    rnboObject.process (buffer.getArrayOfWritePointers(),
                        static_cast<RNBO::Index> (buffer.getNumChannels()),
                        buffer.getArrayOfWritePointers(),
                        static_cast<RNBO::Index> (buffer.getNumChannels()),
                        static_cast<RNBO::Index> (bufferSize));
}
 
//==============================================================================
bool RNBOGReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}
 
juce::AudioProcessorEditor* RNBOGReverbAudioProcessor::createEditor()
{
    return new RNBOGReverbAudioProcessorEditor (*this, apvts, undoManager);
    //return new juce::GenericAudioProcessorEditor (*this);
}
 
//==============================================================================
void RNBOGReverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos (destData, true);
    apvts.state.writeToStream (mos);
}
 
void RNBOGReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData (data, static_cast<size_t> (sizeInBytes));
 
    if (tree.isValid())
        apvts.replaceState (tree);
}
 
void RNBOGReverbAudioProcessor::parameterChanged (const juce::String& parameterID, float newValue)
{
    rnboObject.setParameterValue (apvtsParamIdToRnboParamIndex[parameterID], newValue);
}
 
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RNBOGReverbAudioProcessor();
}
