#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

using namespace dsp;

struct ControlPanel : public ChangeBroadcaster
{
  ControlPanel();
  ~ControlPanel();

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControlPanel)
};
