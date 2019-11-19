#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

enum class PlayState
{
  Play,
  Stop
};

class MainComponent : public AudioAppComponent, public Timer, public Button::Listener
{
public:
  MainComponent();
  ~MainComponent();

  void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
  void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;
  void releaseResources() override;

  void paint(Graphics &g) override;
  void resized() override;

  void play();
  void stop();
  void timerCallback() override;
  void buttonClicked(Button *button) override;

private:
  tracktion_engine::Engine engine{ProjectInfo::projectName};
  tracktion_engine::Edit edit{engine, tracktion_engine::createEmptyEdit(), tracktion_engine::Edit::EditRole::forEditing, nullptr, 0};

  String timeUI{""};
  PlayState playState{PlayState::Stop};
  TextButton playButton{"Stopped"};

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
