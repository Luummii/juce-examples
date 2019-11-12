#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class MainComponent : public AudioAppComponent, public Slider::Listener
{
public:
  MainComponent();
  ~MainComponent();

  void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
  void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;
  void releaseResources() override;
  void sliderValueChanged(Slider *slider) override;

  void paint(Graphics &g) override;
  void resized() override;

  void update();

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)

  Slider frequencySlider, amplitudeSlider;

  Array<double> waveTable;
  double wtSize;
  double frequency;
  double phase;
  double increment;
  double amplitude;
  double currentSampleRate;
};
