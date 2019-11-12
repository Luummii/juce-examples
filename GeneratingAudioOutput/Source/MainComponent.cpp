#include "MainComponent.h"

MainComponent::MainComponent()
{
  setSize(800, 600);

  if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio) && !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
  {
    RuntimePermissions::request(RuntimePermissions::recordAudio,
                                [&](bool granted) { if (granted)  setAudioChannels (2, 2); });
  }
  else
  {
    setAudioChannels(12, 12);
  }
}

MainComponent::~MainComponent()
{
  shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
  std::cout << "start play" << std::endl;
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
  std::cout << "NextAudioBlock" << std::endl;

  for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
  {
    float *const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
      buffer[sample] = (random.nextFloat() * 2.f - 1.f) * .25f;
    }
  }
}

void MainComponent::releaseResources()
{
}

//==============================================================================
void MainComponent::paint(Graphics &g)
{
  g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
}
