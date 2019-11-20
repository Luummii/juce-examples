#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "./Visualizer/Visualizer.h"
#include "./VisualizerComponent/VisualizerComponent.h"

class MainComponent : public AudioAppComponent
{
public:
  MainComponent();
  ~MainComponent();

  void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
  void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;
  void releaseResources() override;

  void paint(Graphics &g) override;
  void resized() override;

private:
  Visualizer visualizer{12};
  VisualizerComponent visualizerComponent{visualizer};

  AudioBuffer<float> summingBuffer;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
