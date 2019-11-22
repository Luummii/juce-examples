#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class MainComponent : public Component, private Timer
{
public:
  MainComponent();
  ~MainComponent();

  void paint(Graphics &) override;
  void resized() override;
  void timerCallback() override;

private:
  SidePanel sidebar;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
