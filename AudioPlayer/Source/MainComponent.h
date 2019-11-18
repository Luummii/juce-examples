#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

enum TransportState
{
  Stop,
  Play,
  Pause
};

class MainComponent : public AudioAppComponent, public ChangeListener
{
public:
  MainComponent();
  ~MainComponent();

  void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
  void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;
  void releaseResources() override;
  void paint(Graphics &g) override;
  void resized() override;
  void changeListenerCallback(ChangeBroadcaster *source) override;

  void openFile();
  void playFile();
  void pauseFile();
  void stopFile();
  void transportStateChange(TransportState state);

private:
  AudioDeviceManager otherDeviceManager;
  std::unique_ptr<AudioDeviceSelectorComponent> audioSettings;

  TextButton openButton;
  TextButton playButton;
  TextButton pauseButton;
  TextButton stopButton;
  AudioFormatManager formatManager;
  std::unique_ptr<AudioFormatReaderSource> playSource;

  AudioTransportSource transport;
  TransportState state;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
