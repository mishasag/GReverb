#pragma once

#include <JuceHeader.h>
#include "RNBO.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>
#include <iostream>


class LoggingMessageHandler;

class PluginProcessor final
    : public juce::AudioProcessor
    , public juce::AudioProcessorValueTreeState::Listener



{
public:
    PluginProcessor();
    ~PluginProcessor() override;
    juce::ValueTree& getStateTree() { return apvts.state; }

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    //std::unique_ptr<LoggingMessageHandler> messageHandler;
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void parameterChanged (const juce::String& parameterID, float newValue) override;
    
    double getRT60Value() const; // Getter for RT60 value
    void setRT60Value(double newValue); // Setter for RT60 value


    juce::AudioProcessorValueTreeState& getAPVTS() { return apvts; }
    juce::LinearSmoothedValue<float>& getSmoothedInputLevel() { return smoothedInputLevel; }
    juce::LinearSmoothedValue<float>& getSmoothedOutputLevel() { return smoothedOutputLevel; }
    
    float getSmoothedInputLevel() const { return smoothedInputLevel.getCurrentValue(); }
    float getSmoothedOutputLevel() const { return smoothedOutputLevel.getCurrentValue(); }

private:
        juce::AudioProcessorValueTreeState apvts;
        juce::UndoManager undoManager;
        float calculateRMSLevel(const juce::AudioBuffer<float>& buffer);
        juce::LinearSmoothedValue<float> smoothedInputLevel { 0.0f };
        juce::LinearSmoothedValue<float> smoothedOutputLevel { 0.0f };

        RNBO::CoreObject rnboObject;

        std::unordered_map<juce::String, RNBO::ParameterIndex> apvtsParamIdToRnboParamIndex;
        double rt60Value = 0.0; // Stores the RT60 value

        // Forward-declare a custom message handler class
        //std::unique_ptr<LoggingMessageHandler> messageHandler;

      

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};




