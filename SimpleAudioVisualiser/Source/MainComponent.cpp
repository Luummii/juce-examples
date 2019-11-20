#include "MainComponent.h"

MainComponent::MainComponent()
{
  freqSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
  freqSlider.setRange(50.0, 5000.0);
  freqSlider.setTextValueSuffix("Hz");
  freqSlider.addListener(this);
  freqSlider.setValue(500.0);
  addAndMakeVisible(freqSlider);
  freqLabel.setText("Frequency", dontSendNotification);
  freqLabel.attachToComponent(&freqSlider, true);

  ampSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
  ampSlider.setRange(0.0, 1.0);
  ampSlider.addListener(this);
  ampSlider.setValue(0.0);
  addAndMakeVisible(ampSlider);
  ampLabel.setText("Amplitude", dontSendNotification);
  ampLabel.attachToComponent(&ampSlider, true);

  addAndMakeVisible(visualiser);

  setAudioChannels(2, 2);
  setSize(800, 600);
}

MainComponent::~MainComponent() { shutdownAudio(); }

void MainComponent::sliderValueChanged(Slider *slider)
{
  if (slider == &freqSlider)
  {
    currentFrequency = freqSlider.getValue();
  }
  else if (slider == &ampSlider)
  {
    amplitude = ampSlider.getValue();
  }
}

void MainComponent::updateFrequency(const double &bufferSize)
{
  if (targetFrequency != currentFrequency)
  {
    const double frequencyIncrement = (targetFrequency - currentFrequency) / bufferSize;
    increment = (currentFrequency + frequencyIncrement) * wtSize / currentSampleRate;
    phase = fmod((phase + increment), wtSize);
  }
  else
  {
    increment = currentFrequency * wtSize / currentSampleRate;
    phase = fmod((phase + increment), wtSize);
  }
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
  currentFrequency = freqSlider.getValue();
  targetFrequency = currentFrequency;
  amplitude = ampSlider.getValue();
  phase = 0;
  wtSize = 1024;
  currentSampleRate = sampleRate;

  for (int i = 0; i < wtSize; i++)
  {
    waveTable.insert(i, sin(2.0 * double_Pi * i / wtSize));
  }

  visualiser.clear();
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
  float *const leftSpeaker = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
  float *const rightSpeaker = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

  const double bufferSize = bufferToFill.numSamples;

  for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
  {
    leftSpeaker[sample] = waveTable[(int)phase] * amplitude;
    rightSpeaker[sample] = waveTable[(int)phase] * amplitude;
    updateFrequency(bufferSize);
  }

  visualiser.pushBuffer(bufferToFill);
}

void MainComponent::releaseResources() {}

void MainComponent::paint(Graphics &g)
{
  g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
  const int labelSpace = 100;
  freqSlider.setBounds(labelSpace, 20, getWidth() - 100, 20);
  ampSlider.setBounds(labelSpace, 50, getWidth() - 100, 50);

  visualiser.setBounds(labelSpace, 110, getWidth() - 200, 200);
}
