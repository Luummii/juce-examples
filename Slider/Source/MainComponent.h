#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MainComponent : public Component, Slider::Listener
{
public:
  MainComponent();
  ~MainComponent();

  void paint(Graphics &) override;
  void resized() override;
  void sliderValueChanged(Slider *slider) override;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)

  Slider slider;
  Label labelSlider;

  LookAndFeel_V4 otherLookAndFeel;
};
