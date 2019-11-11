#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

class WallComponent : public Component
{
public:
  WallComponent();
  ~WallComponent();

  void paint(Graphics &) override;
  void resized() override;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WallComponent)
};
