#pragma once

#include "Dial.h"
#include "Box.h"
#include "GainIndicator.h"
#include "RT60Label.h"
#include "LowCutIcon.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class EditorContent final : public juce::Component


{
public:
    EditorContent (juce::AudioProcessorValueTreeState& apvts, juce::UndoManager& um, PluginProcessor& p);
    void resized() override;
    bool keyPressed (const juce::KeyPress& k) override;
    static constexpr int defaultWidth { 640 };
    static constexpr int defaultHeight { 280 };
    
private:
    PluginProcessor& processor;
    
    GainIndicator inputIndicator;  // Input signal indicator
    GainIndicator outputIndicator; // Output signal indicator
    float fontSize = 14.0f;
    RT60Label rt60Label;
    LowCutButton lowCutButton;
   
    //PluginProcessor& audioProcessor;
    Dial low_cutDial;
    //Dial post_levelDial;
    //Dial preq_levelDial;
    Dial r_FeedbackDial;
    Dial r_InGainDial;
    Dial lfo1_rateDial;
    Dial r_DampDial;
    Dial apf_gDial;
    Dial mixDial;
    Dial pre_delDial;
    Dial SizeDial;
    //Dial himid_levDial;
    Dial himidfqDial;
    Dial high_cutDial;
    Dial lfo1_bwDial;
    
    Box  himid_levBox;
    Box preq_levelBox;
    Box post_levelBox;
    Box bass_multBox;
    Box himid_qfBox;
    Dial xoverDial;
    //Dial rt60_paramDial;
    juce::Label versionLabel;
    juce::HyperlinkButton hyperlinkButton { "donate to support development", juce::URL("https://www.paypal.com/paypalme/mishik80") };
    //juce::Colour backgroundColour = juce::Colours::black;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditorContent)
};
