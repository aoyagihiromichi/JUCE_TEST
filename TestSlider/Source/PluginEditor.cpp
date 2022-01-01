/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestSliderAudioProcessorEditor::TestSliderAudioProcessorEditor (TestSliderAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    sLinearHorizontal.setSliderStyle (juce::Slider::LinearHorizontal);
    sLinearHorizontal.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    sLinearHorizontal.setRange (0.0f, 1.0f, 0.1f);
    sLinearHorizontal.setValue (0.5f);
    addAndMakeVisible (sLinearHorizontal);

    sLinearVertical.setSliderStyle (juce::Slider::LinearVertical);
    sLinearVertical.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    sLinearVertical.setRange (0.0f, 1.0f, 0.05f);
    sLinearVertical.setValue (0.5f);
    addAndMakeVisible (sLinearVertical);

    sLinearBar.setSliderStyle(juce::Slider::LinearBar);
    sLinearBar.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    sLinearBar.setRange(0.0f, 1.0f, 0.025f);
    sLinearBar.setValue(0.5f);
    addAndMakeVisible(sLinearBar);

    sLinearBarVertical.setSliderStyle(juce::Slider::LinearBarVertical);
    sLinearBarVertical.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    sLinearBarVertical.setRange(0.0f, 1.0f, 0.1f);
    sLinearBarVertical.setValue(0.5f);
    addAndMakeVisible(sLinearBarVertical);

    sRotary.setSliderStyle(juce::Slider::Rotary);
    sRotary.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 50, 25);
    sRotary.setRange(0.0f, 1.0f, 0.1f);
    sRotary.setValue(0.5f);
    addAndMakeVisible(sRotary);

    sRotaryHorizontalDrag.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    sRotaryHorizontalDrag.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 50, 25);
    sRotaryHorizontalDrag.setRange(0.0f, 1.0f, 0.1f);
    sRotaryHorizontalDrag.setValue(0.5f);
    addAndMakeVisible(sRotaryHorizontalDrag);

    sRotaryVerticalDrag.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    sRotaryVerticalDrag.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 50, 25);
    sRotaryVerticalDrag.setRange(0.0f, 1.0f, 0.1f);
    sRotaryVerticalDrag.setValue(0.5f);
    addAndMakeVisible(sRotaryVerticalDrag);

    sRotaryHorizontalVerticalDrag.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sRotaryHorizontalVerticalDrag.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 50, 25);
    sRotaryHorizontalVerticalDrag.setRange(0.0f, 1.0f, 0.1f);
    sRotaryHorizontalVerticalDrag.setValue(0.5f);
    addAndMakeVisible(sRotaryHorizontalVerticalDrag);

    sIncDecButtons.setSliderStyle(juce::Slider::IncDecButtons);
    sIncDecButtons.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    sIncDecButtons.setRange(-1.0f, 1.0f, 0.1f);
    sIncDecButtons.setValue(0.0f);
    addAndMakeVisible(sIncDecButtons);

    sTwoValueHorizontal.setSliderStyle(juce::Slider::TwoValueHorizontal);
    sTwoValueHorizontal.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    sTwoValueHorizontal.setRange(-1.0f, 1.0f, 0.1f);
//    sTwoValueHorizontal.setValue(0.0f);
    addAndMakeVisible(sTwoValueHorizontal);

    sTwoValueVertical.setSliderStyle(juce::Slider::TwoValueVertical);
    sTwoValueVertical.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    sTwoValueVertical.setRange(-1.0f, 1.0f, 0.1f);
//    sTwoValueVertical.setValue(0.0f);
    addAndMakeVisible(sTwoValueVertical);

    sThreeValueHorizontal.setSliderStyle(juce::Slider::ThreeValueHorizontal);
    sThreeValueHorizontal.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    sThreeValueHorizontal.setRange(-1.0f, 1.0f, 0.1f);
//    sThreeValueHorizontal.setValue(0.0f);
    addAndMakeVisible(sThreeValueHorizontal);

    sThreeValueVertical.setSliderStyle(juce::Slider::ThreeValueVertical);
    sThreeValueVertical.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    sThreeValueVertical.setRange(-1.0f, 1.0f, 0.1f);
//    sThreeValueVertical.setValue(0.0f);
    addAndMakeVisible(sThreeValueVertical);

    setSize (600, 400);
}

TestSliderAudioProcessorEditor::~TestSliderAudioProcessorEditor()
{
}

//==============================================================================
void TestSliderAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void TestSliderAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    sLinearHorizontal.setBounds(10, 10, 100, 100);
    sLinearVertical.setBounds(120, 10, 100, 100);
    sLinearBar.setBounds(230, 10, 100, 100);
    sLinearBarVertical.setBounds(340, 10, 100, 100);
    
    sRotary.setBounds(10, 120, 100, 100);
    sRotaryHorizontalDrag.setBounds(120, 120, 100, 100);
    sRotaryVerticalDrag.setBounds(230, 120, 100, 100);
    sRotaryHorizontalVerticalDrag.setBounds(340, 120, 100, 100);

    sIncDecButtons.setBounds(10, 230, 100, 100);
    sTwoValueHorizontal.setBounds(120, 230, 100, 100);
    sTwoValueVertical.setBounds(230, 230, 100, 100);
    sThreeValueHorizontal.setBounds(340, 230, 100, 100);
    sThreeValueVertical.setBounds(450, 230, 100, 100);
}
