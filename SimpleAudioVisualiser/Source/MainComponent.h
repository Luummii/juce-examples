#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "./Visualiser/Visualiser.h"

class MainComponent : public AudioAppComponent, public Slider::Listener
{
public:
  MainComponent();
  ~MainComponent();

  void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
  void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;
  void releaseResources() override;

  void paint(Graphics &g) override;
  void resized() override;

  void sliderValueChanged(Slider *slider) override;
  void updateFrequency(const double &bufferSize);

private:
  Slider freqSlider, ampSlider;
  Label freqLabel, ampLabel;

  Array<double> waveTable;
  double wtSize;
  double currentFrequency, targetFrequency;
  double phase;
  double increment;
  double amplitude;
  double currentSampleRate;
  double bufferSize;

  Visualiser visualiser;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
