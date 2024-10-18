/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Dial.h"

//==============================================================================
/**
*/
class RNBOGReverbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    RNBOGReverbAudioProcessorEditor (RNBOGReverbAudioProcessor& p,
                                    juce::AudioProcessorValueTreeState& state,
                                    juce::UndoManager& um);
 
    ~RNBOGReverbAudioProcessorEditor() override;
 
    void paint (juce::Graphics&) override;
    void resized() override;
 
    bool keyPressed (const juce::KeyPress& key) override;
 
private:
    RNBOGReverbAudioProcessor& audioProcessor;
    juce::UndoManager& undoManager;
    juce::Label versionLabel;
    Dial low_cutDial;
    Dial post_levelDial;
    Dial preq_levelDial;
    Dial r_FeedbackDial;
    Dial r_InGainDial;
    Dial lfo1_rateDial;
    Dial r_DampDial;
    Dial apf_gDial;
    Dial mixDial;
    Dial diff_numDial;
    Dial pre_delDial;
    Dial fb1Dial;
    Dial x_fbDial;
    Dial SizeDial;
    Dial himid_levDial;
    Dial himidfqDial;
    Dial high_cutDial;
    Dial lfo1_bwDial;
    
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RNBOGReverbAudioProcessorEditor)
};
