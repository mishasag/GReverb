#include "GainIndicator.h"

GainIndicator::GainIndicator(PluginProcessor& proc, juce::LinearSmoothedValue<float>& level, bool isInput)
    : processor(proc), smoothedLevel(level), isInputSignal(isInput) {
    //DBG("GainIndicator created: " << (isInputSignal ? "Input" : "Output"));
    startTimerHz(15); // Start the timer
}

GainIndicator::~GainIndicator() {
    //DBG("GainIndicator destroyed: " << (isInputSignal ? "Input" : "Output"));
    stopTimer(); // Ensure the timer stops
}

void GainIndicator::paint(juce::Graphics& g) {
    auto bounds = getLocalBounds().toFloat();
    float level = smoothedLevel.getCurrentValue(); // Access the smoothed value

    // Define colors for levels
    const juce::Colour noSignalColour = juce::Colours::darkgrey;
    const juce::Colour lowColour = juce::Colours::green;
    const juce::Colour midColour = juce::Colours::yellow;
    const juce::Colour clipColour = juce::Colours::red;

    // Determine color based on level
    auto getColorForLevel = [&](float signalLevel) -> juce::Colour {
        if (signalLevel < 0.001f) return noSignalColour;
        if (signalLevel < 0.1259f) return lowColour.interpolatedWith(midColour, signalLevel / 0.1259f);
        if (signalLevel < 1.0f) return midColour.interpolatedWith(clipColour, (signalLevel - 0.1259f) / (1.0f - 0.1259f));
        return clipColour;
    };

    g.setColour(getColorForLevel(level));
    g.fillEllipse(bounds.reduced(bounds.getWidth() * 0.1f)); // Draw indicator
}


void GainIndicator::timerCallback() {
    repaint(); // Trigger a repaint at regular intervals
}




