#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "RNBO.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

class GainIndicatorOut final : public juce::Component, private juce::Timer
{
public:
    explicit GainIndicatorOut (PluginProcessor& p);
    //~GainIndicator() override;

    //void setLevel(float newLevel);       // Set the signal level
    void paint(juce::Graphics& g) override;
    void timerCallback() override;
    void updateLevels();
    float getSmoothedInputLevel() const { return smoothedInputLevel.getCurrentValue(); }
    float getSmoothedOutputLevel() const { return smoothedOutputLevel.getCurrentValue(); }

private:
    PluginProcessor& audioProcessor;
    static constexpr float silenceThreshold = 0.001f;
    //float level = 0.0f;                  // Current signal level
    //juce::Colour getColorForLevel(float level) const; // Determines color based on level
    juce::LinearSmoothedValue<float> smoothedInputLevel { 0.0f };
    juce::LinearSmoothedValue<float> smoothedOutputLevel { 0.0f };
};
