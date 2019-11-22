#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "./Seporator/Seporator.h"
#include "./ControlPanel/ControlPanel.h"

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

  void setNewFile(File file);
  void transportStateChange(TransportState state);

private:
  ControlPanel controlPanel;
  Seporator seporator;

  AudioFormatManager formatManager;
  AudioTransportSource transport;
  std::unique_ptr<AudioFormatReaderSource> playSource;

  AudioDeviceManager deviceManager;
  std::unique_ptr<AudioDeviceSelectorComponent> audioSettings;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
