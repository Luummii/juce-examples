#include "MainComponent.h"

MainComponent::MainComponent()
{
  setSize(800, 600);

  if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio) && !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
  {
    RuntimePermissions::request(RuntimePermissions::recordAudio, [&](bool granted) {
      if (granted)
        setAudioChannels(2, 2);
    });
  }
  else
  {
    setAudioChannels(2, 2);
  }
}

MainComponent::~MainComponent() { shutdownAudio(); }

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
  visualizer.setSampleRate(sampleRate);
  summingBuffer.setSize(1, samplesPerBlockExpected);
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
  const auto numChannels = bufferToFill.buffer->getNumChannels();
  const auto startSample = bufferToFill.startSample;
  const auto numSamples = bufferToFill.buffer->getNumSamples();

  summingBuffer.clear();
  for (auto i = 0; i < numChannels; ++i)
    summingBuffer.addFrom(0, startSample, *bufferToFill.buffer, i, startSample, numSamples);
  const auto gain = 1.f / static_cast<float>(numChannels);
  FloatVectorOperations::multiply(summingBuffer.getWritePointer(0, startSample), gain, numSamples);

  visualizer.addSamples(summingBuffer.getReadPointer(0), numSamples);

  bufferToFill.buffer->clear();
}

void MainComponent::releaseResources() {}

void MainComponent::paint(Graphics &g)
{
  g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
  visualizerComponent.setBounds(getLocalBounds());
}
