/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MyColours.h"
#include "ParamIDs.h"

//==============================================================================

RNBOGReverbAudioProcessorEditor::RNBOGReverbAudioProcessorEditor (RNBOGReverbAudioProcessor& p,
                                                                juce::AudioProcessorValueTreeState& state,
                                                                juce::UndoManager& um)
    : AudioProcessorEditor (&p), audioProcessor (p), undoManager (um),
    
            low_cutDial             (*state.getParameter (ParamIDs::low_cut), &um),
            post_levelDial             (*state.getParameter (ParamIDs::post_level), &um),
            preq_levelDial             (*state.getParameter (ParamIDs::preq_level), &um),
            r_FeedbackDial             (*state.getParameter (ParamIDs::r_Feedback), &um),
            r_InGainDial             (*state.getParameter (ParamIDs::r_InGain), &um),
            lfo1_rateDial             (*state.getParameter (ParamIDs::lfo1_rate), &um),
            r_DampDial             (*state.getParameter (ParamIDs::r_Damp), &um),
            apf_gDial             (*state.getParameter (ParamIDs::apf_g), &um),
            mixDial             (*state.getParameter (ParamIDs::mix), &um),
            diff_numDial             (*state.getParameter (ParamIDs::diff_num), &um),
            pre_delDial             (*state.getParameter (ParamIDs::pre_del), &um),
            fb1Dial             (*state.getParameter (ParamIDs::fb1), &um),
            x_fbDial             (*state.getParameter (ParamIDs::x_fb), &um),
            SizeDial             (*state.getParameter (ParamIDs::Size), &um),
            himid_levDial             (*state.getParameter (ParamIDs::himid_lev), &um),
            himidfqDial             (*state.getParameter (ParamIDs::himidfq), &um),
            high_cutDial             (*state.getParameter (ParamIDs::high_cut), &um),
            lfo1_bwDial             (*state.getParameter (ParamIDs::lfo1_bw), &um)

    
{
    
    auto futuraMedium = juce::Typeface::createSystemTypefaceFor (BinaryData::FuturaMedium_ttf,BinaryData::FuturaMedium_ttfSize);
    juce::LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypeface (futuraMedium);
    
    setWantsKeyboardFocus (true);
    setSize (640, 280);
    
    versionLabel.setText("mishik80@icloud.com v0.2a", juce::dontSendNotification);
    versionLabel.setFont(juce::Font(14.0f, juce::Font::bold));
    versionLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    
    low_cutDial.setLabelText            ("low_cut");
    post_levelDial.setLabelText            ("post_level");
    preq_levelDial.setLabelText            ("preq_level");
    r_FeedbackDial.setLabelText            ("Decay");
    r_InGainDial.setLabelText            ("r_InGain");
    lfo1_rateDial.setLabelText            ("lfo1_rate");
    r_DampDial.setLabelText            ("r_Damp");
    apf_gDial.setLabelText            ("apf_g");
    mixDial.setLabelText            ("mix");
    diff_numDial.setLabelText            ("diff_num");
    pre_delDial.setLabelText            ("pre_del");
    fb1Dial.setLabelText            ("fb1");
    x_fbDial.setLabelText            ("x_fb");
    SizeDial.setLabelText            ("Size");
    himid_levDial.setLabelText            ("himid_lev");
    himidfqDial.setLabelText            ("himidfq");
    high_cutDial.setLabelText            ("high_cut");
    lfo1_bwDial.setLabelText            ("lfo1_bw");
    //preq_highcutDial.setLabelText  ("pre highcut");
    
    // Set interval of values changed by arrow keys or shift + arrow keys.
    low_cutDial.setFineInterval (1.0f);
    post_levelDial.setFineInterval (1.0f);
    preq_levelDial.setFineInterval (1.0f);
    r_FeedbackDial.setFineInterval (1.0f);
    r_InGainDial.setFineInterval (1.0f);
    lfo1_rateDial.setFineInterval (1.0f);
    r_DampDial.setFineInterval (1.0f);
    apf_gDial.setFineInterval (1.0f);
    mixDial.setFineInterval (1.0f);
    diff_numDial.setFineInterval (1.0f);
    pre_delDial.setFineInterval (1.0f);
    fb1Dial.setFineInterval (1.0f);
    x_fbDial.setFineInterval (1.0f);
    SizeDial.setFineInterval (1.0f);
    himid_levDial.setFineInterval (1.0f);
    himidfqDial.setFineInterval (1.0f);
    high_cutDial.setFineInterval (1.0f);
    lfo1_bwDial.setFineInterval (1.0f);
    
    
    addAndMakeVisible (low_cutDial);
    addAndMakeVisible (post_levelDial);
    addAndMakeVisible (preq_levelDial);
    addAndMakeVisible (r_FeedbackDial);
    addAndMakeVisible (r_InGainDial);
    addAndMakeVisible (lfo1_rateDial);
    addAndMakeVisible (r_DampDial);
    addAndMakeVisible (apf_gDial);
    addAndMakeVisible (mixDial);
    addAndMakeVisible (diff_numDial);
    addAndMakeVisible (pre_delDial);
    addAndMakeVisible (fb1Dial);
    addAndMakeVisible (x_fbDial);
    addAndMakeVisible (SizeDial);
    addAndMakeVisible (himid_levDial);
    addAndMakeVisible (himidfqDial);
    addAndMakeVisible (high_cutDial);
    addAndMakeVisible (lfo1_bwDial);
    
}
 
RNBOGReverbAudioProcessorEditor::~RNBOGReverbAudioProcessorEditor()
{
}
 
void RNBOGReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (MyColours::black);
}
 
void RNBOGReverbAudioProcessorEditor::resized()
{
    //top
    mixDial.setBounds               (30,  30,  80, 95);
    r_FeedbackDial.setBounds        (130, 30,  80, 95);
    pre_delDial.setBounds           (230, 30,  80, 95);
    SizeDial.setBounds              (330, 30,  80, 95);
    lfo1_rateDial.setBounds         (430, 30,  80, 95);
    lfo1_bwDial.setBounds           (530, 30,  80, 95);
    //bottom
    r_DampDial.setBounds            (30,  155, 80, 95);
    post_levelDial.setBounds        (130, 155, 80, 95);
    himid_levDial.setBounds         (230, 155, 80, 95);
    himidfqDial.setBounds           (330, 155, 80, 95);
    high_cutDial.setBounds          (430, 155, 80, 95);
    low_cutDial.setBounds           (530, 155, 80, 95);
    versionLabel.setBounds          (480, 255, 200, 25);
}
 
bool RNBOGReverbAudioProcessorEditor::keyPressed (const juce::KeyPress& key)
{
    const auto cmdZ = juce::KeyPress { 'z', juce::ModifierKeys::commandModifier, 0 };
 
    if (key == cmdZ && undoManager.canUndo())
    {
        undoManager.undo();
        return true;
    }
 
    const auto cmdShiftZ = juce::KeyPress { 'z', juce::ModifierKeys::commandModifier
                                                 | juce::ModifierKeys::shiftModifier, 0 };
 
    if (key == cmdShiftZ && undoManager.canRedo())
    {
        undoManager.redo();
        return true;
    }
 
    return false;
}

