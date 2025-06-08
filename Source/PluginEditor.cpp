#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "ui/MyColours.h"

PluginEditor::PluginEditor (PluginProcessor& p, juce::AudioProcessorValueTreeState& apvts, juce::UndoManager& um)
    : AudioProcessorEditor (&p)
    , undoManager (um)
    //, audioProcessor (p)
    , editorContent (apvts, um, p)
{
    constexpr auto ratio = static_cast<double>(defaultWidth) / defaultHeight;

        setResizable(true, true);
        getConstrainer()->setFixedAspectRatio(ratio);
        getConstrainer()->setSizeLimits(defaultWidth / 2, defaultHeight / 2, defaultWidth * 2, defaultHeight * 2);

        // Load saved size or use defaults
        auto width = static_cast<int>(apvts.state.getOrCreateChildWithName("editor", nullptr).getProperty("width", defaultWidth));
        auto height = static_cast<int>(apvts.state.getOrCreateChildWithName("editor", nullptr).getProperty("height", defaultHeight));

        // Validate dimensions
        if (width < defaultWidth / 2 || width > defaultWidth * 2) width = defaultWidth;
        if (height < defaultHeight / 2 || height > defaultHeight * 2) height = defaultHeight;

        setSize(width, height);
        editorContent.setSize(getWidth(), getHeight());
        addAndMakeVisible(editorContent);
}


void PluginEditor::paint (juce::Graphics& g) { g.fillAll (MyColours::black);
    
    
}

void PluginEditor::resized()
{
    editorContent.setBounds(getLocalBounds());

        // Save the current size to state
        auto& state = dynamic_cast<PluginProcessor*>(getAudioProcessor())->getStateTree();
        auto editorState = state.getOrCreateChildWithName("editor", nullptr);
        editorState.setProperty("width", getWidth(), nullptr);
        editorState.setProperty("height", getHeight(), nullptr);
}

bool PluginEditor::keyPressed (const juce::KeyPress& k)
{
    if (k.isKeyCode ('Z') && k.getModifiers().isCommandDown())
    {
        if (k.getModifiers().isShiftDown())
            undoManager.redo();
        else
            undoManager.undo();

        return true;
    }

    return false;
}
