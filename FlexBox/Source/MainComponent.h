#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class MainComponent : public Component
{
public:
  MainComponent();
  ~MainComponent();

  void paint(Graphics &) override;
  void resized() override;

private:
  Slider slider1;
  Slider slider2;
  Slider slider3;
  Slider slider4;
  Slider slider5;
  Slider slider6;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
