#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

enum TransportState
{
  Stop,
  Play,
  Pause
};

class ControlPanel : public Component
{
public:
  ControlPanel();
  ~ControlPanel();

  void paint(Graphics &) override;
  void resized() override;

  void open();
  void play();
  void pause();
  void stop();

  std::function<void(File file)> btnOpenListner;
  std::function<void(TransportState state)> btnActionListner;

private:
  TextButton btnOpen;
  TextButton btnPlay;
  TextButton btnPause;
  TextButton btnStop;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControlPanel)
};
