
#include "Box.h"
#include "MyColours.h"

Box::Box(juce::RangedAudioParameter& param, juce::UndoManager* um)
: audioParam (param)
, paramAttachment (
      audioParam,
      [&] (float v) { updateValue (v); },
      um)
, textBox (std::make_unique<TextBox>())

{
    setWantsKeyboardFocus(true);
    setRepaintsOnMouseActivity(true);
    setColour(foregroundArcColourId, MyColours::blue);
    setColour(backgroundArcColourId, MyColours::babyYellow);
    setColour(needleColourId, MyColours::midGrey);
    setColour(borderColourId, MyColours::grey);

    
    
    
    setLabelColour (MyColours::grey);
    parameterNameLabel.setText (audioParam.getName (10), juce::NotificationType::dontSendNotification);
    parameterNameLabel.setJustificationType (juce::Justification::centred);
    parameterNameLabel.setInterceptsMouseClicks (false, false);
    
    
    
    /* Configure the parameter name label
    parameterNameLabel.setText(audioParam.getName(4), juce::dontSendNotification);
    parameterNameLabel.setFont(juce::Font(10.0f, juce::Font::bold));
    parameterNameLabel.setColour(juce::Label::textColourId, MyColours::grey);
    parameterNameLabel.setJustificationType(juce::Justification::centred);
    */
    setTextBoxColour(MyColours::grey);
    textBox->onTextChange = [&]
    {
        const auto newNormValue = audioParam.getValueForText(textBox->getText());
        const auto newDenormValue = audioParam.convertFrom0to1(newNormValue);
        paramAttachment.setValueAsCompleteGesture(newDenormValue);
        textBox->setText(audioParam.getCurrentValueAsText(), juce::NotificationType::dontSendNotification);
    };


    addAndMakeVisible (parameterNameLabel);
    addAndMakeVisible (textBox.get());

    paramAttachment.sendInitialUpdate();
}

Box::~Box() = default;
void Box::resized()
{
    auto bounds = getLocalBounds().toFloat();

    borderPath.clear();
    createBorder(bounds);

    // Reserve space for parameterNameLabel at the top
    auto labelHeight = bounds.getHeight() * 0.5f; // 20% of total height for the label
    parameterNameLabel.setBounds(bounds.removeFromTop(labelHeight).toNearestInt());

    // Center the textBox within the remaining bounds
    auto textBoxWidth = bounds.getWidth(); // 80% of width for textBox
    auto textBoxHeight = bounds.getHeight() * 0.99f; // 60% of remaining height for textBox
    auto centerBounds = bounds.withSizeKeepingCentre(textBoxWidth, textBoxHeight);

    textBox->setBounds(centerBounds.toNearestInt());

    // Adjust font sizes
    parameterNameLabel.setFont(juce::Font(static_cast<float>(labelHeight * 0.9f)));
    textBox->setFont(juce::Font(static_cast<float>(textBoxHeight) * 0.99f));

    mainArea = bounds.expanded (1.0f).withY (bounds.getY() + 1);
    //mainArea = bounds;
}

void Box::paint(juce::Graphics& g)
{
    //drawLine(g);
    
    
   //
    
    if (hasKeyboardFocus (true))
    g.strokePath (borderPath, juce::PathStrokeType { borderThickness });
}
void Box::mouseDown (const juce::MouseEvent& e)
{
    paramAttachment.beginGesture();

    e.source.enableUnboundedMouseMovement (true);

    mousePosWhenLastDragged = e.position;
}

void Box::mouseDrag (const juce::MouseEvent& e)
{
    auto diffY = (mousePosWhenLastDragged.y - e.position.y) * sensitivity;

    if (e.mods.isShiftDown())
        diffY *= 0.1f;

    value = juce::jlimit (0.0f, 1.0f, value + diffY);
    const auto newDenormValue = audioParam.convertFrom0to1 (value);
    paramAttachment.setValueAsPartOfGesture (newDenormValue);
    textBox->setText (audioParam.getCurrentValueAsText(), juce::NotificationType::dontSendNotification);

    mousePosWhenLastDragged = e.position;
}

void Box::mouseUp (const juce::MouseEvent& e)
{
    paramAttachment.endGesture();

    e.source.enableUnboundedMouseMovement (false);

    juce::Desktop::getInstance().getMainMouseSource().setScreenPosition (e.source.getLastMouseDownPosition());
}

void Box::mouseDoubleClick (const juce::MouseEvent& e)
{
    juce::ignoreUnused (e);

    const auto defaultValue = audioParam.getDefaultValue();
    value = defaultValue;

    const auto newDenormValue = audioParam.convertFrom0to1 (defaultValue);
    paramAttachment.setValueAsCompleteGesture (newDenormValue);

    textBox->setText (audioParam.getCurrentValueAsText(), juce::NotificationType::dontSendNotification);
}

bool Box::keyPressed (const juce::KeyPress& k)
{
    if (('0' <= k.getKeyCode() && k.getKeyCode() <= '9') || k.getKeyCode() == '-' || k.getKeyCode() == '.')
    {
        textBox->setValueShownWithEditor (juce::String::charToString (k.getTextCharacter()));
        textBox->showEditor();

        return true;
    }

    if (k.getKeyCode() == juce::KeyPress::upKey)
    {
        const auto newValue = getValue() + (k.getModifiers().isShiftDown() ? fineInterval : interval);
        paramAttachment.setValueAsCompleteGesture (newValue);

        return true;
    }

    if (k.getKeyCode() == juce::KeyPress::downKey)
    {
        const auto newValue = getValue() - (k.getModifiers().isShiftDown() ? fineInterval : interval);
        paramAttachment.setValueAsCompleteGesture (newValue);

        return true;
    }

    return false;
}

void Box::focusGained (FocusChangeType cause)
{
    juce::ignoreUnused (cause);
    repaint();
}

void Box::focusLost (FocusChangeType cause)
{
    juce::ignoreUnused (cause);
    repaint();
}

float Box::getValue() const { return audioParam.convertFrom0to1 (value); }

void Box::setTextBoxColour (juce::Colour newColour)
{
    textBox->setColour (juce::Label::textColourId, newColour);
    textBox->setColour (juce::Label::textWhenEditingColourId, newColour);
}

void Box::setLabelColour (juce::Colour newColour) { parameterNameLabel.setColour (juce::Label::textColourId, newColour); }

void Box::setLabelText (const juce::String& newLabelText)
{
    parameterNameLabel.setText (newLabelText, juce::NotificationType::dontSendNotification);
}

void Box::updateValue (float newValue)
{
    value = audioParam.convertTo0to1 (newValue);
    textBox->setText (audioParam.getCurrentValueAsText(), juce::NotificationType::dontSendNotification);
    repaint();
}

void Box::createBorder (const juce::Rectangle<float>& bounds)
{
    const auto area = bounds.reduced (borderThickness * 0.5f);
    auto radian = 0.0f;

    for (const auto& corner : { area.getTopLeft(), area.getTopRight(), area.getBottomRight(), area.getBottomLeft() })
    {
        constexpr auto length = 5.0f;
        juce::Path p;
        p.startNewSubPath (corner.x, corner.y + length);
        p.lineTo (corner);
        p.lineTo (corner.x + length, corner.y);
        p.applyTransform (juce::AffineTransform::rotation (radian, corner.x, corner.y));
        borderPath.addPath (p);

        radian += juce::MathConstants<float>::halfPi;
    };
}

