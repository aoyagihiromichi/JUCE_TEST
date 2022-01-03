/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestFX1AudioProcessorEditor::TestFX1AudioProcessorEditor (TestFX1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    sGain1.setComponentID("CopyGain");
    sGain1.setSliderStyle (juce::Slider::LinearVertical);
    sGain1.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    sGain1.setRange (0.0f, 0.9f, 0.05f);
    sGain1.setValue (0.1f);
    sGain1.addListener(this);
    addAndMakeVisible (sGain1);

    sGain2.setComponentID("DelayGain");
    sGain2.setSliderStyle (juce::Slider::LinearVertical);
    sGain2.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    sGain2.setRange (0.0f, 0.9f, 0.05f);
    sGain2.setValue (0.7f);
    sGain2.addListener(this);
    addAndMakeVisible (sGain2);
    
    sDelay.setComponentID("DelayTime");
    sDelay.setSliderStyle(juce::Slider::LinearHorizontal);
    sDelay.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    sDelay.setRange (0.0f, 4.0f, 0.1f);
    sDelay.setValue (2.0f);
    sDelay.addListener(this);
    addAndMakeVisible(sDelay);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (490, 300);
}

TestFX1AudioProcessorEditor::~TestFX1AudioProcessorEditor()
{
}

//==============================================================================
void TestFX1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

//    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void TestFX1AudioProcessorEditor::resized()
{
    sGain1.setBounds(10, 10, 150, 150);
    sGain2.setBounds(170, 10, 150, 150);
    sDelay.setBounds(330, 10, 150, 150);
    *(audioProcessor.gain1) = sGain1.getValue();
    *(audioProcessor.gain2) = sGain2.getValue();
    *(audioProcessor.delaytime) = sDelay.getValue();
}

void TestFX1AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider->getComponentID() == "CopyGain")
        *(audioProcessor.gain1) = slider->getValue();
    else if (slider->getComponentID() == "DelayGain")
        *(audioProcessor.gain2) = slider->getValue();
    else if (slider->getComponentID() == "DelayTime")
        *(audioProcessor.delaytime) = slider->getValue();
}
