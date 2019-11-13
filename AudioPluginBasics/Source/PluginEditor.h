#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class AudioPluginBasicsAudioProcessorEditor : public AudioProcessorEditor, public Slider::Listener
{
public:
  AudioPluginBasicsAudioProcessorEditor(AudioPluginBasicsAudioProcessor &);
  ~AudioPluginBasicsAudioProcessorEditor();

  void paint(Graphics &) override;
  void resized() override;
  void sliderValueChanged(Slider *slider) override;

private:
  AudioPluginBasicsAudioProcessor &processor;
  Slider gainSlider;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginBasicsAudioProcessorEditor)
};
