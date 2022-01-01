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
class TestSliderAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TestSliderAudioProcessorEditor (TestSliderAudioProcessor&);
    ~TestSliderAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TestSliderAudioProcessor& audioProcessor;

    juce::Slider sLinearHorizontal;
    juce::Slider sLinearVertical;
    juce::Slider sLinearBar;
    juce::Slider sLinearBarVertical;
    juce::Slider sRotary;
    juce::Slider sRotaryHorizontalDrag;
    juce::Slider sRotaryVerticalDrag;
    juce::Slider sRotaryHorizontalVerticalDrag;
    juce::Slider sIncDecButtons;
    juce::Slider sTwoValueHorizontal;
    juce::Slider sTwoValueVertical;
    juce::Slider sThreeValueHorizontal;
    juce::Slider sThreeValueVertical;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestSliderAudioProcessorEditor)
};
