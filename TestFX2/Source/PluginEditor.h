/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TestFX2AudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    TestFX2AudioProcessorEditor (TestFX2AudioProcessor&);
    ~TestFX2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TestFX2AudioProcessor& audioProcessor;

    // Add Start
    juce::Slider midVolume;
    juce::Slider sideVolume;
    void sliderValueChanged(juce::Slider *slider) override;
    // Add End
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestFX2AudioProcessorEditor)
};
