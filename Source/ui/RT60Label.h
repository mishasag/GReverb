#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "RNBO.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_dsp/juce_dsp.h>
class RT60Label final : public juce::Label, juce::Timer

//private juce::AudioProcessorValueTreeState::Listener
{
public:
    explicit RT60Label(PluginProcessor& p);
    //~RT60Label() override;
    ~RT60Label() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;
    void timerCallback() override;

private:
    //void parameterChanged(const juce::String& parameterID, float newValue) override;
    float fontSize = 14.0f;

    juce::String rt60Text { "0.0 sec" };
    PluginProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RT60Label)
};
