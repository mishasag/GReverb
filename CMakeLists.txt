cmake_minimum_required(VERSION 3.21)
 
set(PROJECT_NAME "GReverb")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "Build architectures for macOS")
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.11" CACHE STRING "Minimum macOS version required")
#set(JUCE_MACOS_ENABLE_CODE_SIGNING OFF CACHE BOOL "" FORCE)
set(PLUGIN_VERSION "1.0.1")
add_compile_definitions(PLUGIN_VERSION="${PLUGIN_VERSION}")
 
project("${PROJECT_NAME}" VERSION 1.1 LANGUAGES C CXX)
 
set(formats "VST3" "Standalone")
 
if(APPLE)
    list(APPEND formats "AU")
endif()
 
add_subdirectory(External/JUCE)
 
juce_add_plugin("${PROJECT_NAME}"
    VERSION "1.1"
    COMPANY_NAME "Strange Audio"
    PLUGIN_MANUFACTURER_CODE "Grvb"
    PLUGIN_CODE "RC01"
    FORMATS ${formats}
    COPY_PLUGIN_AFTER_BUILD FALSE
    IS_SYNTH FALSE     
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    PRODUCT_NAME "${PROJECT_NAME}")
 
juce_generate_juce_header("${PROJECT_NAME}")
 
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/export/rnbo"
    "${CMAKE_CURRENT_SOURCE_DIR}/export/rnbo/common")
 
target_sources("${PROJECT_NAME}"
    PRIVATE
    export/rnbo_GReverb.cpp
    export/rnbo/RNBO.cpp
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
	#Source/LoggingMessageHandler.cpp
	Source/ui/Dial.cpp
	Source/ui/Box.cpp
	Source/ui/RT60Label.cpp
	Source/ui/GainIndicator.cpp
	#Source/ui/GainIndicatorOut.cpp
	Source/ui/EditorContent.cpp
	Source/ui/EditorLnf.cpp
	Source/ui/LowCutIcon.cpp)
 
target_compile_features("${PROJECT_NAME}" PUBLIC cxx_std_20)
 
target_compile_definitions("${PROJECT_NAME}"
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

juce_add_binary_data(BinaryData
	SOURCES
	Resources/FuturaMedium.ttf
    Resources/highpass.svg)

target_link_libraries("${PROJECT_NAME}"
    PRIVATE
	BinaryData
        juce::juce_audio_utils
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
