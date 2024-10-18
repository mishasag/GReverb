           Dial lowcutDial;
           Dial low_cutDial;
           Dial post_levelDial;
           Dial preq_levelDial;
           Dial r_FeedbackDial;
           Dial r_InGainDial;
           Dial lfo1_rateDial;
           Dial r_DampDial;
           Dial apf_gDial;
           Dial mixDial;
           Dial diff_numDial;
           Dial pre_delDial;
           Dial fb1Dial;
           Dial x_fbDial;
           Dial SizeDial;
           Dial himid_levDial;
           Dial himidfqDial;
           Dial high_cutDial;
           Dial lfo1_bwDial;
           lowcutDial             (*state.getParameter (ParamIDs::lowcut), &um),
           low_cutDial             (*state.getParameter (ParamIDs::low_cut), &um),
           post_levelDial             (*state.getParameter (ParamIDs::post_level), &um),
           preq_levelDial             (*state.getParameter (ParamIDs::preq_level), &um),
           r_FeedbackDial             (*state.getParameter (ParamIDs::r_Feedback), &um),
           r_InGainDial             (*state.getParameter (ParamIDs::r_InGain), &um),
           lfo1_rateDial             (*state.getParameter (ParamIDs::lfo1_rate), &um),
           r_DampDial             (*state.getParameter (ParamIDs::r_Damp), &um),
           apf_gDial             (*state.getParameter (ParamIDs::apf_g), &um),
           mixDial             (*state.getParameter (ParamIDs::mix), &um),
           diff_numDial             (*state.getParameter (ParamIDs::diff_num), &um),
           pre_delDial             (*state.getParameter (ParamIDs::pre_del), &um),
           fb1Dial             (*state.getParameter (ParamIDs::fb1), &um),
           x_fbDial             (*state.getParameter (ParamIDs::x_fb), &um),
           SizeDial             (*state.getParameter (ParamIDs::Size), &um),
           himid_levDial             (*state.getParameter (ParamIDs::himid_lev), &um),
           himidfqDial             (*state.getParameter (ParamIDs::himidfq), &um),
           high_cutDial             (*state.getParameter (ParamIDs::high_cut), &um),
           lfo1_bwDial             (*state.getParameter (ParamIDs::lfo1_bw), &um),
           lowcutDial.setLabelText            ("lowcut");
           low_cutDial.setLabelText            ("low_cut");
           post_levelDial.setLabelText            ("post_level");
           preq_levelDial.setLabelText            ("preq_level");
           r_FeedbackDial.setLabelText            ("r_Feedback");
           r_InGainDial.setLabelText            ("r_InGain");
           lfo1_rateDial.setLabelText            ("lfo1_rate");
           r_DampDial.setLabelText            ("r_Damp");
           apf_gDial.setLabelText            ("apf_g");
           mixDial.setLabelText            ("mix");
           diff_numDial.setLabelText            ("diff_num");
           pre_delDial.setLabelText            ("pre_del");
           fb1Dial.setLabelText            ("fb1");
           x_fbDial.setLabelText            ("x_fb");
           SizeDial.setLabelText            ("Size");
           himid_levDial.setLabelText            ("himid_lev");
           himidfqDial.setLabelText            ("himidfq");
           high_cutDial.setLabelText            ("high_cut");
           lfo1_bwDial.setLabelText            ("lfo1_bw");
           lowcutDial.setFineInterval (1.0f);
           low_cutDial.setFineInterval (1.0f);
           post_levelDial.setFineInterval (1.0f);
           preq_levelDial.setFineInterval (1.0f);
           r_FeedbackDial.setFineInterval (1.0f);
           r_InGainDial.setFineInterval (1.0f);
           lfo1_rateDial.setFineInterval (1.0f);
           r_DampDial.setFineInterval (1.0f);
           apf_gDial.setFineInterval (1.0f);
           mixDial.setFineInterval (1.0f);
           diff_numDial.setFineInterval (1.0f);
           pre_delDial.setFineInterval (1.0f);
           fb1Dial.setFineInterval (1.0f);
           x_fbDial.setFineInterval (1.0f);
           SizeDial.setFineInterval (1.0f);
           himid_levDial.setFineInterval (1.0f);
           himidfqDial.setFineInterval (1.0f);
           high_cutDial.setFineInterval (1.0f);
           lfo1_bwDial.setFineInterval (1.0f);
           addAndMakeVisible (lowcutDial);
           addAndMakeVisible (low_cutDial);
           addAndMakeVisible (post_levelDial);
           addAndMakeVisible (preq_levelDial);
           addAndMakeVisible (r_FeedbackDial);
           addAndMakeVisible (r_InGainDial);
           addAndMakeVisible (lfo1_rateDial);
           addAndMakeVisible (r_DampDial);
           addAndMakeVisible (apf_gDial);
           addAndMakeVisible (mixDial);
           addAndMakeVisible (diff_numDial);
           addAndMakeVisible (pre_delDial);
           addAndMakeVisible (fb1Dial);
           addAndMakeVisible (x_fbDial);
           addAndMakeVisible (SizeDial);
           addAndMakeVisible (himid_levDial);
           addAndMakeVisible (himidfqDial);
           addAndMakeVisible (high_cutDial);
           addAndMakeVisible (lfo1_bwDial);
           lowcutDial.setBounds               (30,  30,  80, 95);
           low_cutDial.setBounds               (30,  30,  80, 95);
           post_levelDial.setBounds               (30,  30,  80, 95);
           preq_levelDial.setBounds               (30,  30,  80, 95);
           r_FeedbackDial.setBounds               (30,  30,  80, 95);
           r_InGainDial.setBounds               (30,  30,  80, 95);
           lfo1_rateDial.setBounds               (30,  30,  80, 95);
           r_DampDial.setBounds               (30,  30,  80, 95);
           apf_gDial.setBounds               (30,  30,  80, 95);
           mixDial.setBounds               (30,  30,  80, 95);
           diff_numDial.setBounds               (30,  30,  80, 95);
           pre_delDial.setBounds               (30,  30,  80, 95);
           fb1Dial.setBounds               (30,  30,  80, 95);
           x_fbDial.setBounds               (30,  30,  80, 95);
           SizeDial.setBounds               (30,  30,  80, 95);
           himid_levDial.setBounds               (30,  30,  80, 95);
           himidfqDial.setBounds               (30,  30,  80, 95);
           high_cutDial.setBounds               (30,  30,  80, 95);
           lfo1_bwDial.setBounds               (30,  30,  80, 95);
