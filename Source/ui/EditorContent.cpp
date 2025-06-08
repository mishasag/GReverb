
#include "EditorContent.h"
#include "../ParamIDs.h"

EditorContent::EditorContent (juce::AudioProcessorValueTreeState& apvts, juce::UndoManager& um, PluginProcessor& p)
    
    
    :
    processor(p),
    lowCutButton            (*apvts.getParameter (ParamIDs::lowcut), &um),
    low_cutDial             (*apvts.getParameter (ParamIDs::low_cut), &um),
    inputIndicator(processor, processor.getSmoothedInputLevel(), true),
    preq_levelBox             (*apvts.getParameter (ParamIDs::preq_level), &um),
    r_FeedbackDial             (*apvts.getParameter (ParamIDs::r_Feedback), &um),
    r_InGainDial             (*apvts.getParameter (ParamIDs::r_InGain), &um),
    lfo1_rateDial             (*apvts.getParameter (ParamIDs::lfo1_rate), &um),
    r_DampDial             (*apvts.getParameter (ParamIDs::r_Damp), &um),
    apf_gDial             (*apvts.getParameter (ParamIDs::apf_g), &um),
    mixDial             (*apvts.getParameter (ParamIDs::mix), &um),
    pre_delDial             (*apvts.getParameter (ParamIDs::pre_del), &um),
    SizeDial             (*apvts.getParameter (ParamIDs::Size), &um),
    himid_levBox             (*apvts.getParameter (ParamIDs::himid_lev), &um),
    himidfqDial             (*apvts.getParameter (ParamIDs::himidfq), &um),
    high_cutDial             (*apvts.getParameter (ParamIDs::high_cut), &um),
    lfo1_bwDial             (*apvts.getParameter (ParamIDs::lfo1_bw), &um),
    bass_multBox             (*apvts.getParameter (ParamIDs::bass_mult), &um),
    xoverDial                   (*apvts.getParameter (ParamIDs::xover), &um),
    himid_qfBox                 (*apvts.getParameter (ParamIDs::himid_qf), &um),
    post_levelBox             (*apvts.getParameter (ParamIDs::post_level), &um),
    rt60Label                   (p),
    outputIndicator(processor, processor.getSmoothedOutputLevel(), false)
{
    setWantsKeyboardFocus (true);
    setFocusContainerType (FocusContainerType::keyboardFocusContainer);
    versionLabel.setText(" v1.1", juce::dontSendNotification);
    versionLabel.setFont(juce::Font(fontSize, juce::Font::bold));
    versionLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    hyperlinkButton.setColour(juce::HyperlinkButton::textColourId, juce::Colours::lightblue);
    // Set interval of values changed by arrow keys or shift + arrow keys.
    low_cutDial.setFineInterval (1.0f);
    post_levelBox.setFineInterval (1.0f);
    preq_levelBox.setFineInterval (1.0f);
    r_FeedbackDial.setFineInterval (1.0f);
    r_InGainDial.setFineInterval (1.0f);
    lfo1_rateDial.setFineInterval (0.1f);
    r_DampDial.setFineInterval (1.0f);
    apf_gDial.setFineInterval (1.0f);
    mixDial.setFineInterval (1.0f);
    pre_delDial.setFineInterval (1.0f);
    SizeDial.setFineInterval (1.0f);
    himid_levBox.setFineInterval (1.0f);
    himidfqDial.setFineInterval (1.0f);
    high_cutDial.setFineInterval (1.0f);
    lfo1_bwDial.setFineInterval (0.1f);
    
    
    addAndMakeVisible(inputIndicator);
    addAndMakeVisible(outputIndicator);
    addAndMakeVisible   (rt60Label);
    addAndMakeVisible (low_cutDial);
    addAndMakeVisible (post_levelBox);
    addAndMakeVisible (preq_levelBox);
    addAndMakeVisible (r_FeedbackDial);
    addAndMakeVisible (r_InGainDial);
    addAndMakeVisible (lfo1_rateDial);
    addAndMakeVisible (r_DampDial);
    //addAndMakeVisible (apf_gDial);
    addAndMakeVisible (mixDial);
    addAndMakeVisible (pre_delDial);
    addAndMakeVisible (SizeDial);
    addAndMakeVisible (himid_levBox);
    addAndMakeVisible (himidfqDial);
    addAndMakeVisible (high_cutDial);
    addAndMakeVisible (lfo1_bwDial);
    addAndMakeVisible (versionLabel);
    addAndMakeVisible (hyperlinkButton);
    addAndMakeVisible (xoverDial);
    addAndMakeVisible (himid_qfBox);
    addAndMakeVisible (apf_gDial);
    addAndMakeVisible(bass_multBox);
    addAndMakeVisible(lowCutButton);
    //addAndMakeVisible(outputLevelIndicator);
  
    
}


void EditorContent::resized()
{
    auto bounds = getLocalBounds();
    auto bounds_ = getLocalBounds().toFloat();
    fontSize = bounds_.getHeight() * 0.8f;

        // Calculate scaling factors
    const float scaleX = static_cast<float>(bounds.getWidth()) / defaultWidth;
        const float scaleY = static_cast<float>(bounds.getHeight()) / defaultHeight;

        // Helper lambda to scale a rectangle
        auto scaleRect = [scaleX, scaleY](juce::Rectangle<int> rect) {
            return juce::Rectangle<int>(
                static_cast<int>(rect.getX() * scaleX),
                static_cast<int>(rect.getY() * scaleY),
                static_cast<int>(rect.getWidth() * scaleX),
                static_cast<int>(rect.getHeight() * scaleY)
            );
        };

        // Define default bounds based on default size
        const auto topDialBounds = juce::Rectangle<int>{0, 30, 80, 95};
        mixDial.setBounds(scaleRect(topDialBounds.withX(30)));
        pre_delDial.setBounds(scaleRect(topDialBounds.withX(130)));
        r_FeedbackDial.setBounds(scaleRect(topDialBounds.withX(230)));
        SizeDial.setBounds(scaleRect(topDialBounds.withX(330)));
        lfo1_rateDial.setBounds(scaleRect(topDialBounds.withX(430)));
        lfo1_bwDial.setBounds(scaleRect(topDialBounds.withX(530)));

        const auto bottomDialBounds = topDialBounds.withY(155);
        apf_gDial.setBounds(scaleRect(bottomDialBounds.withX(30)));
        r_DampDial.setBounds(scaleRect(bottomDialBounds.withX(130)));
        xoverDial.setBounds(scaleRect(bottomDialBounds.withX(230)));
        himidfqDial.setBounds(scaleRect(bottomDialBounds.withX(330)));
        high_cutDial.setBounds(scaleRect(bottomDialBounds.withX(430)));
        low_cutDial.setBounds(scaleRect(bottomDialBounds.withX(530)));

        preq_levelBox.setBounds(scaleRect(juce::Rectangle<int>{30, 3, 80, 25}));
        post_levelBox.setBounds(scaleRect(juce::Rectangle<int>{130, 3, 80, 25}));
        lowCutButton.setBounds(scaleRect(juce::Rectangle<int>{430, 3, 142, 20}));
        rt60Label.setBounds(scaleRect(juce::Rectangle<int>{256, 3, 142, 20}));
        rt60Label.resized();
        himid_qfBox.setBounds(scaleRect(juce::Rectangle<int>{330, 252, 39, 25}));
        himid_levBox.setBounds(scaleRect(juce::Rectangle<int>{371, 252, 39, 25}));
        bass_multBox.setBounds(scaleRect(juce::Rectangle<int>{230, 252, 80, 25}));
        
        inputIndicator.setBounds(scaleRect(juce::Rectangle<int>{35, 11, 10, 10}));
        outputIndicator.setBounds(scaleRect(juce::Rectangle<int>{135, 11, 10, 10}));
        hyperlinkButton.setBounds(scaleRect(juce::Rectangle<int>{433, 258, 142, 17}));
        versionLabel.setBounds(scaleRect(juce::Rectangle<int>{587, 258, 45, 17}));
  
}


bool EditorContent::keyPressed (const juce::KeyPress& k)
{
    if (k.isKeyCode (juce::KeyPress::tabKey) && hasKeyboardFocus (false))
    {
        mixDial.grabKeyboardFocus();
        return true;
    }

    return false;
}
