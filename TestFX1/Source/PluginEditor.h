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
class TestFX1AudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    TestFX1AudioProcessorEditor (TestFX1AudioProcessor&);
    ~TestFX1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TestFX1AudioProcessor& audioProcessor;

    juce::Slider sGain1;
    juce::Slider sGain2;
    juce::Slider sDelay;
    void sliderValueChanged(juce::Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestFX1AudioProcessorEditor)
};
