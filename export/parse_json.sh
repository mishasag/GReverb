#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <json_filename>"
    exit 1
fi

json_file=$1
output_layout=$2
output_paramID=$3

if [ ! -f "$json_file" ]; then
    echo "Error: JSON file not found: $json_file"
    exit 1
fi

echo "Processing JSON file: $json_file"
echo "// This file was generated by a script" > out_layuot.h
result=$(jq -r '.parameters[] |
    "layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::\(.paramId), 1 },\n" +
    "                                             ParamIDs::\(.paramId),\n" +
    "                                             juce::NormalisableRange<float> (\(.minimum | tonumber).0f, \(.maximum | tonumber).0f, 0.01f, \(.exponent | tonumber).0f),\n" +
    "                                             \(.initialValue | tonumber).0f,\n" +
    "                                             juce::String(),\n" +
    "                                             juce::AudioProcessorParameter::genericParameter,\n" +
    "                                             percentFormat,\n" +
    "                                             nullptr));\n"
' "$json_file")
echo "Generated C++ statement: $result"
echo "$result" > out_layuot.h

echo "Processing JSON file: $json_file"
result=$(jq -r '.parameters[] |
    "           inline constexpr auto \(.paramId)        { \"\(.paramId)\"};"' "$json_file")
echo "Generated C++ statement: $result"
echo "$result" > output_paramID.h

echo "Generated C++ code in output_paramID.h"

echo "Processing JSON file: $json_file"
result=$(jq -r '.parameters[] |
    "           Dial \(.paramId)Dial;"' "$json_file")
echo "Generated C++ statement: $result"
echo "$result" > out_dial.h

echo "Processing JSON file: $json_file"
result=$(jq -r '.parameters[] |
    "           \(.paramId)Dial             (*state.getParameter (ParamIDs::\(.paramId)), &um),"' "$json_file")
echo "Generated C++ statement: $result"
echo "$result" >> out_dial.h

echo "Processing JSON file: $json_file"
result=$(jq -r '.parameters[] |
    "           \(.paramId)Dial.setLabelText            (\"\(.paramId)\");"' "$json_file")
echo "Generated C++ statement: $result"
echo "$result" >> out_dial.h
echo "Processing JSON file: $json_file"
result=$(jq -r '.parameters[] |
    "           \(.paramId)Dial.setFineInterval (1.0f);"' "$json_file")
echo "Generated C++ statement: $result"
echo "$result" >> out_dial.h

echo "Processing JSON file: $json_file"
result=$(jq -r '.parameters[] |
    "           addAndMakeVisible (\(.paramId)Dial);"' "$json_file")
echo "Generated C++ statement: $result"
echo "$result" >> out_dial.h
    
echo "Processing JSON file: $json_file"
result=$(jq -r '.parameters[] |
    "           \(.paramId)Dial.setBounds               (30,  30,  80, 95);"' "$json_file")
echo "Generated C++ statement: $result"
echo "$result" >> out_dial.h
        
            
    
echo "Generated C++ code in out_dial.h"
