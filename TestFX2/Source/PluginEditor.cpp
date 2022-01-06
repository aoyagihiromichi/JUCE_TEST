/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestFX2AudioProcessorEditor::TestFX2AudioProcessorEditor (TestFX2AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
    
    // Add Start
    midVolume.setComponentID("MidVolume");
    midVolume.setSliderStyle (juce::Slider::LinearVertical);
    midVolume.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    midVolume.setRange (0.0f, 2.0f, 0.05f);
    midVolume.setValue (1.0f);
    midVolume.addListener(this);
    addAndMakeVisible (midVolume);

    sideVolume.setComponentID("SideVolume");
    sideVolume.setSliderStyle (juce::Slider::LinearVertical);
    sideVolume.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    sideVolume.setRange (0.0f, 2.0f, 0.05f);
    sideVolume.setValue (1.0f);
    sideVolume.addListener(this);
    addAndMakeVisible (sideVolume);
    // Add End
}

TestFX2AudioProcessorEditor::~TestFX2AudioProcessorEditor()
{
}

//==============================================================================
void TestFX2AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

//    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void TestFX2AudioProcessorEditor::resized()
{
    // Add Start
    midVolume.setBounds(10, 10, 150, 150);
    sideVolume.setBounds(170, 10, 150, 150);
    
    *(audioProcessor.midGain) = midVolume.getValue();
    *(audioProcessor.sideGain) = sideVolume.getValue();
    // Add End
}

void TestFX2AudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if (slider->getComponentID() == "MidVolume")
        *(audioProcessor.midGain) = midVolume.getValue();
    else if (slider->getComponentID() == "SideVolume")
        *(audioProcessor.sideGain) = sideVolume.getValue();
}
