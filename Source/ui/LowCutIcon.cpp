#include "LowCutIcon.h"
#include "MyColours.h"
#include <BinaryData.h>

LowCutButton::LowCutButton (juce::RangedAudioParameter& param, juce::UndoManager* um)
    : audioParam (param)
    , paramAttachment (audioParam, [&] (float v) { updateState (static_cast<bool> (v)); }, um)
{
    setWantsKeyboardFocus (true);
    setRepaintsOnMouseActivity (true);
    setColour (onColourId, MyColours::blue);
    setColour (offColourId, MyColours::midGrey);
    setColour (focusColourId, MyColours::midGrey.brighter (0.25f));
    //setFont(juce::Font(14.0f, juce::Font::bold));
    //
    //setColour(juce::Label::textColourId, juce::Colours::grey);

    const auto svg = juce::Drawable::createFromImageData (BinaryData::highpass_svg, BinaryData::highpass_svgSize);
    jassert (svg != nullptr);

    if (svg != nullptr)
        iconPath = svg->getOutlineAsPath();

    paramAttachment.sendInitialUpdate();
}

void LowCutButton::resized()
{
    auto bounds = getLocalBounds().toFloat();
    iconBounds = getLocalBounds().toFloat();
    fontSize = bounds.getHeight() * 0.8f;
    iconPath.applyTransform (iconPath.getTransformToScaleToFit (iconBounds, true));
}

void LowCutButton::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    g.setColour (findColour (state ? onColourId : hasKeyboardFocus (true) ? focusColourId : offColourId));
    g.fillPath (iconPath);
    //lable  g.drawText("reverb time:", bounds.removeFromLeft(bounds.getWidth() * 0.5f), juce::Justification::centredLeft);
    g.setColour(MyColours::midGrey);
    g.setFont(juce::Font(fontSize, juce::Font::bold)); // Scale font
    g.drawText("pre lowcut", bounds.removeFromLeft(bounds.getWidth() * 0.5f), juce::Justification::centredLeft);
}

void LowCutButton::mouseDown (const juce::MouseEvent& e)
{
    juce::ignoreUnused (e);

    paramAttachment.setValueAsCompleteGesture (! state);

    const auto centre = iconBounds.getCentre();
    iconPath.applyTransform (juce::AffineTransform::scale (0.95f, 0.95f, centre.x, centre.y));
}

void LowCutButton::mouseUp (const juce::MouseEvent& e)
{
    juce::ignoreUnused (e);
    iconPath.applyTransform (iconPath.getTransformToScaleToFit (iconBounds, true));
}

void LowCutButton::focusGained (FocusChangeType cause)
{
    juce::ignoreUnused (cause);
    repaint();
}

void LowCutButton::focusLost (FocusChangeType cause)
{
    juce::ignoreUnused (cause);
    repaint();
}

bool LowCutButton::keyPressed (const juce::KeyPress& key)
{
    if (key == juce::KeyPress::returnKey)
    {
        paramAttachment.setValueAsCompleteGesture (! state);
        return true;
    }

    return false;
}

void LowCutButton::updateState (bool newState)
{
    state = newState;
    repaint();
}
