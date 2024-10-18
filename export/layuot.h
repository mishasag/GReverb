layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::lowcut, 1 },
                                             ParamIDs::lowcut,
                                             juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f, 1.0f),
                                             0.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::low_cut, 1 },
                                             ParamIDs::low_cut,
                                             juce::NormalisableRange<float> (10.0f, 1500.0f, 0.01f, 2.25f),
                                             20.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::post_level, 1 },
                                             ParamIDs::post_level,
                                             juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                             50.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::preq_level, 1 },
                                             ParamIDs::preq_level,
                                             juce::NormalisableRange<float> (-100.0f, 100.0f, 0.01f, 1.0f),
                                             0.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::r_Feedback, 1 },
                                             ParamIDs::r_Feedback,
                                             juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                             50.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::r_InGain, 1 },
                                             ParamIDs::r_InGain,
                                             juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                             90.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::lfo1_rate, 1 },
                                             ParamIDs::lfo1_rate,
                                             juce::NormalisableRange<float> (0.0f, 5.0f, 0.01f, 0.1f),
                                             0.3f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::r_Damp, 1 },
                                             ParamIDs::r_Damp,
                                             juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                             20.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::apf_g, 1 },
                                             ParamIDs::apf_g,
                                             juce::NormalisableRange<float> (-0.99f, 0.99f, 0.01f, 0.1f),
                                             0.535f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::mix, 1 },
                                             ParamIDs::mix,
                                             juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f, 1.0f),
                                             50.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::diff_num, 1 },
                                             ParamIDs::diff_num,
                                             juce::NormalisableRange<float> (1.0f, 4.0f, 0.01f, 1.0f),
                                             4.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::pre_del, 1 },
                                             ParamIDs::pre_del,
                                             juce::NormalisableRange<float> (0.0f, 500.0f, 0.01f, 1.0f),
                                             20.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::fb1, 1 },
                                             ParamIDs::fb1,
                                             juce::NormalisableRange<float> (0.0f, 0.9f, 0.01f, 0.1f),
                                             0.1f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::x_fb, 1 },
                                             ParamIDs::x_fb,
                                             juce::NormalisableRange<float> (0.0f, 0.9f, 0.01f, 0.1f),
                                             0.1f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::Size, 1 },
                                             ParamIDs::Size,
                                             juce::NormalisableRange<float> (0.0f, 100f, 0.01f, 0.25f),
                                             60.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::himid_lev, 1 },
                                             ParamIDs::himid_lev,
                                             juce::NormalisableRange<float> (-100.0f, 100.0f, 0.01f, 1.0f),
                                             0.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::himidfq, 1 },
                                             ParamIDs::himidfq,
                                             juce::NormalisableRange<float> (-100.0f, 100.0f, 0.01f, 1.0f),
                                             0.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::high_cut, 1 },
                                             ParamIDs::high_cut,
                                             juce::NormalisableRange<float> (300.0f, 20000.0f, 0.01f, 2.25f),
                                             8000.0f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));

layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::lfo1_bw, 1 },
                                             ParamIDs::lfo1_bw,
                                             juce::NormalisableRange<float> (0.0f, 2.0f, 0.01f, 0.1f),
                                             0.3f,
                                             juce::String(),
                                             juce::AudioProcessorParameter::genericParameter,
                                             percentFormat,
                                             nullptr));
