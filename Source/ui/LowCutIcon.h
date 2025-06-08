//
//  LowCutIcon.h
//  GReverb
//
//  Created by Mikhail Sagov on 05.01.2025.
//

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class LowCutButton final : public juce::Component
{
public:
    enum ColourIds
    {
        onColourId,
        offColourId,
        focusColourId
    };

    explicit LowCutButton (juce::RangedAudioParameter& param, juce::UndoManager* um = nullptr);

    void paint (juce::Graphics& g) override;
    void resized() override;

    void mouseDown (const juce::MouseEvent& event) override;
    void mouseUp (const juce::MouseEvent& event) override;

    void focusGained (FocusChangeType cause) override;
    void focusLost (FocusChangeType cause) override;

    bool keyPressed (const juce::KeyPress& key) override;

private:
    void updateState (bool newState);

    bool state { false };
    float fontSize = 14.0f;

    juce::Path iconPath;
    juce::Rectangle<float> iconBounds;

    juce::RangedAudioParameter& audioParam;
    juce::ParameterAttachment paramAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowCutButton)
};
