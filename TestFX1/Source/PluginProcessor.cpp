/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestFX1AudioProcessor::TestFX1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(gain1 = new juce::AudioParameterFloat("Gain1", "Gain1", 0.0f, 1.0f, 0.1f));
    addParameter(gain2 = new juce::AudioParameterFloat("Gain2", "Gain2", 0.0f, 1.0f, 0.7f));
}

TestFX1AudioProcessor::~TestFX1AudioProcessor()
{
}

//==============================================================================
const juce::String TestFX1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TestFX1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TestFX1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TestFX1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TestFX1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TestFX1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TestFX1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void TestFX1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TestFX1AudioProcessor::getProgramName (int index)
{
    return {};
}

void TestFX1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TestFX1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    auto delayBufferSize = sampleRate * 2;
    delayBuffer.setSize(getTotalNumOutputChannels(), (int)delayBufferSize);
}

void TestFX1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TestFX1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TestFX1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // 使わないOutputChannelをクリア
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto bufferSize = buffer.getNumSamples();
    auto delayBufferSize = delayBuffer.getNumSamples();

    // 全InputChannelに対して実行
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        fillBuffer(channel, bufferSize, delayBufferSize, channelData);
        addDelay(channel, bufferSize, delayBufferSize, buffer);
    }
    
    writePosition += bufferSize;
    writePosition %= delayBufferSize;
}

void TestFX1AudioProcessor::fillBuffer(int channel, int bufferSize, int delayBufferSize, float* channelData)
{
    if (delayBufferSize >= (writePosition + bufferSize))
    {
        // DelayBufferサイズ以内なので丸コピー
        delayBuffer.copyFromWithRamp (channel, writePosition, channelData, bufferSize, *gain1, *gain1);
    }
    else
    {
        // DelayBuffferに収まらないので分割コピー
        auto numSamplesToEnd = delayBufferSize - writePosition;
        delayBuffer.copyFromWithRamp (channel, writePosition, channelData, numSamplesToEnd, *gain1, *gain1);
        auto numSamplesAtStart = bufferSize - numSamplesToEnd;
        delayBuffer.copyFromWithRamp (channel, 0, channelData, numSamplesAtStart, *gain1, *gain1);
    }
}

void TestFX1AudioProcessor::addDelay(int channel, int bufferSize, int delayBufferSize, juce::AudioBuffer<float>& buffer)
{
    auto readPosition = writePosition - getSampleRate();
    if (readPosition < 0)
        readPosition += delayBufferSize;

    if ((readPosition + bufferSize) <= delayBufferSize)
    {
        buffer.addFromWithRamp(channel, 0, delayBuffer.getReadPointer(channel, readPosition), bufferSize, *gain2, *gain2);
    }
    else
    {
        auto numSamplesToEnd = delayBufferSize - readPosition;
        buffer.addFromWithRamp(channel, 0, delayBuffer.getReadPointer(channel, readPosition), numSamplesToEnd, *gain2, *gain2);
        auto numSamplesAtStart = bufferSize - numSamplesToEnd;
        buffer.addFromWithRamp(channel, numSamplesToEnd, delayBuffer.getReadPointer(channel, 0), numSamplesAtStart, *gain2, *gain2);
    }
}

//==============================================================================
bool TestFX1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TestFX1AudioProcessor::createEditor()
{
    return new TestFX1AudioProcessorEditor (*this);
}

//==============================================================================
void TestFX1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TestFX1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TestFX1AudioProcessor();
}
