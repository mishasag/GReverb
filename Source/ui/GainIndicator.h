#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>
class GainIndicator final : public juce::Component, private juce::Timer {
public:
    GainIndicator(PluginProcessor& proc, juce::LinearSmoothedValue<float>& level, bool isInput);
    ~GainIndicator() override;

    void paint(juce::Graphics& g) override;
    void timerCallback() override;

private:
    PluginProcessor& processor;
    juce::LinearSmoothedValue<float>& smoothedLevel; // Reference to the level (input/output)
    bool isInputSignal;                              // True for input, false for output
};
