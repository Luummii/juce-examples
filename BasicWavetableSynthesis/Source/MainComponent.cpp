#include "MainComponent.h"

MainComponent::MainComponent()
{
  setSize(800, 300);

  if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio) && !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
  {
    RuntimePermissions::request(RuntimePermissions::recordAudio,
                                [&](bool granted) { if (granted)  setAudioChannels (2, 2); });
  }
  else
  {
    setAudioChannels(2, 2);
  }

  frequencySlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
  frequencySlider.setRange(50, 500);
  frequencySlider.setValue(200);
  frequencySlider.addListener(this);

  amplitudeSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
  amplitudeSlider.setRange(0.0, 1.0);
  amplitudeSlider.addListener(this);

  addAndMakeVisible(frequencySlider);
  addAndMakeVisible(amplitudeSlider);
}

MainComponent::~MainComponent()
{
  shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
  std::cout << "start play" << std::endl;
  frequency = frequencySlider.getValue();
  phase = 0.0;
  wtSize = 1024.0;
  amplitude = amplitudeSlider.getValue();
  currentSampleRate = sampleRate;

  // one cycle of a sine wave
  for (int i = 0; i < wtSize; i++)
  {
    waveTable.insert(i, sin(2.0 * double_Pi * i / wtSize));
  }
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
  float *const leftSpeaker = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
  float *const rightSpeaker = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

  for (int sample = 0; sample < bufferToFill.numSamples; sample++)
  {
    leftSpeaker[sample] = waveTable[(int)phase] * amplitude;
    rightSpeaker[sample] = waveTable[(int)phase] * amplitude;
    update();
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

void MainComponent::sliderValueChanged(Slider *slider)
{
  if (slider == &frequencySlider)
  {
    frequency = frequencySlider.getValue();
    std::cout << "frequency = " << frequency << std::endl;
  }

  if (slider == &amplitudeSlider)
  {
    amplitude = amplitudeSlider.getValue();
    std::cout << "amplitude = " << amplitude << std::endl;
  }
}

void MainComponent::update()
{
  increment = frequency * wtSize / currentSampleRate;
  phase = fmod((phase + increment), wtSize);
}

void MainComponent::resized()
{
  frequencySlider.setBounds(100, 20, getWidth() - 100, 20);
  amplitudeSlider.setBounds(100, 100, getWidth() - 100, 20);
}
