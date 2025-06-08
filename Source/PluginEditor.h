#pragma once

#include "PluginProcessor.h"
#include "ui/EditorContent.h"
#include "ui/EditorLnf.h"
#include "ui/GainIndicator.h"
#include "ui/MyColours.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class PluginEditor final : public juce::AudioProcessorEditor
                            
{
public:
    PluginEditor (PluginProcessor& p, juce::AudioProcessorValueTreeState& apvts, juce::UndoManager& um);
    //void timerCallback() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool keyPressed (const juce::KeyPress& k) override;
    static int getDefaultWidth() { return defaultWidth; }
    static int getDefaultHeight() { return defaultHeight; }

private:
    juce::UndoManager& undoManager;
    
    //double rt60Value = 0.0;
    //juce::Colour backgroundColour = MyColours::black;
    EditorContent editorContent;
    //PluginProcessor& audioProcessor; 
    void showContextMenu(const juce::MouseEvent& event);
    static constexpr int defaultWidth { 640 };
    static constexpr int defaultHeight { 280 };
    //void mouseDown(const juce::MouseEvent& event) override;
    struct SharedLnf
    {
        SharedLnf() { juce::LookAndFeel::setDefaultLookAndFeel (&editorLnf); }
        ~SharedLnf() { juce::LookAndFeel::setDefaultLookAndFeel (nullptr); }

        EditorLnf editorLnf;
    };

    juce::SharedResourcePointer<SharedLnf> lnf;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
