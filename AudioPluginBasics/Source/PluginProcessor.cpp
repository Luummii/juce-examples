#include "PluginProcessor.h"
#include "PluginEditor.h"

AudioPluginBasicsAudioProcessor::AudioPluginBasicsAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
      )
#endif
{
}

AudioPluginBasicsAudioProcessor::~AudioPluginBasicsAudioProcessor()
{
}

//==============================================================================
const String AudioPluginBasicsAudioProcessor::getName() const
{
  return JucePlugin_Name;
}

bool AudioPluginBasicsAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool AudioPluginBasicsAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool AudioPluginBasicsAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double AudioPluginBasicsAudioProcessor::getTailLengthSeconds() const
{
  return 0.0;
}

int AudioPluginBasicsAudioProcessor::getNumPrograms()
{
  return 1;
}

int AudioPluginBasicsAudioProcessor::getCurrentProgram()
{
  return 0;
}

void AudioPluginBasicsAudioProcessor::setCurrentProgram(int index)
{
}

const String AudioPluginBasicsAudioProcessor::getProgramName(int index)
{
  return {};
}

void AudioPluginBasicsAudioProcessor::changeProgramName(int index, const String &newName)
{
}

//==============================================================================
void AudioPluginBasicsAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
}

void AudioPluginBasicsAudioProcessor::releaseResources()
{
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AudioPluginBasicsAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
  ignoreUnused(layouts);
  return true;
#else
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
    return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}
#endif

void AudioPluginBasicsAudioProcessor::processBlock(AudioBuffer<float> &buffer, MidiBuffer &midiMessages)
{
  ScopedNoDenormals noDenormals;
  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  std::cout << rawVolume << std::endl;
  std::cout << "rawVolume" << std::endl;

  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

  for (int channel = 0; channel < totalNumInputChannels; ++channel)
  {
    auto *channelData = buffer.getWritePointer(channel);

    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
      channelData[sample] = buffer.getSample(channel, sample) * rawVolume;
    }
  }
}

//==============================================================================
bool AudioPluginBasicsAudioProcessor::hasEditor() const
{
  return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor *AudioPluginBasicsAudioProcessor::createEditor()
{
  return new AudioPluginBasicsAudioProcessorEditor(*this);
}

//==============================================================================
void AudioPluginBasicsAudioProcessor::getStateInformation(MemoryBlock &destData)
{
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
}

void AudioPluginBasicsAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
  // You should use this method to restore your parameters from this memory block,
  // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
  return new AudioPluginBasicsAudioProcessor();
}
