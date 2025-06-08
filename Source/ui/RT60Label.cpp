#include "RT60Label.h"
#include "../ParamIDs.h"
#include "MyColours.h"
#include "../PluginProcessor.h"

RT60Label::RT60Label(PluginProcessor& p)
    : audioProcessor(p) {
        
            setFont(juce::Font(14.0f, juce::Font::bold));
            setColour(juce::Label::textColourId, juce::Colours::grey);

//            auto& apvts = audioProcessor.getAPVTS();
//            apvts.addParameterListener(ParamIDs::r_Feedback, this);
//            apvts.addParameterListener(ParamIDs::Size, this);

            // Fetch initial parameter values
            double rt60Value = audioProcessor.getRT60Value();
            rt60Text = (rt60Value > 500.0)
                           ? "Infinity"
                           : juce::String(rt60Value, 2) + " sec";

            repaint(); // Ensure initial painting
        startTimerHz(5);
}

//RT60Label::~RT60Label() {
//    auto& apvts = audioProcessor.getAPVTS();
//
//    // Remove listeners to avoid dangling references
//    apvts.removeParameterListener(ParamIDs::r_Feedback, this);
//    apvts.removeParameterListener(ParamIDs::Size, this);
//}



//void RT60Label::parameterChanged(const juce::String& parameterID, float newValue) {
//    if (parameterID == ParamIDs::r_Feedback || parameterID == ParamIDs::Size) {
//        double rt60Value = audioProcessor.getRT60Value();
//        juce::String newText = (rt60Value > 500.0)
//                                   ? "Infinity"
//                                   : juce::String(rt60Value, 2) + " sec";
//
//        if (rt60Text != newText) {
//            rt60Text = newText;
//            repaint();
//        }
//    }
//}
void RT60Label::paint(juce::Graphics& g) {
    auto bounds = getLocalBounds().toFloat();

    // Use dynamically scaled font size
    g.setColour(MyColours::midGrey);
    g.setFont(juce::Font(fontSize, juce::Font::plain)); // Scale font
    g.drawText("reverb time:", bounds.removeFromLeft(bounds.getWidth() * 0.5f), juce::Justification::centredLeft);

    g.setColour(rt60Text == "Infinity" ? MyColours::blue : MyColours::grey);
    g.setFont(juce::Font(fontSize, juce::Font::bold));
    g.drawText(rt60Text, bounds, juce::Justification::centredLeft);
}



void RT60Label::resized() {
    auto bounds = getLocalBounds().toFloat();
    fontSize = bounds.getHeight() * 0.8f; // Scale font size based on height

        // Debug for resizing behavior
      //  DBG("RT60Label resized to: " << bounds.toString());
}

void RT60Label::timerCallback()
{
    // Fetch the RT60 value from the processor
    double rt60Value = audioProcessor.getRT60Value();

    // Format new text
    juce::String newText = (rt60Value > 500.0)
                               ? "Infinity"
                               : juce::String(rt60Value, 2) + " sec";

    // Update only if text changes
    if (rt60Text != newText) {
        rt60Text = newText;
        repaint();
    }
}

