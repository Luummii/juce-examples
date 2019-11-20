#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

class Seporator : public Component
{
public:
  Seporator();
  ~Seporator();

  void paint(Graphics &) override;
  void resized() override;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Seporator)
};
