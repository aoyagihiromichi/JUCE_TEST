/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestFX1AudioProcessorEditor::TestFX1AudioProcessorEditor (TestFX1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), sGain1("CopyIn"), sGain2("DelayOut")
{
    sGain1.setSliderStyle (juce::Slider::LinearVertical);
    sGain1.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    sGain1.setRange (0.0f, 1.0f, 0.05f);
    sGain1.setValue (0.1f);
    sGain1.addListener(this);
    addAndMakeVisible (sGain1);

    sGain2.setSliderStyle (juce::Slider::LinearVertical);
    sGain2.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    sGain2.setRange (0.0f, 1.0f, 0.05f);
    sGain2.setValue (0.7f);
    sGain2.addListener(this);
    addAndMakeVisible (sGain2);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
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
    *(audioProcessor.gain1) = sGain1.getValue();
    *(audioProcessor.gain2) = sGain2.getValue();
}

void TestFX1AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider->getComponentID() == "CopyIn")
        *(audioProcessor.gain1) = slider->getValue();
    else if (slider->getComponentID() == "DelayOut")
        *(audioProcessor.gain2) = slider->getValue();
}
