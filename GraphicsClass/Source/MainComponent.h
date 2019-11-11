#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "./WallComponent/WallComponent.h"
#include "./GrassComponent/GrassComponent.h"
#include "./RoofComponent/RoofComponent.h"

class MainComponent : public Component
{
public:
  MainComponent();
  ~MainComponent();

  //==============================================================================
  void paint(Graphics &) override;
  void resized() override;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)

  class WallComponent wall;
  class GrassComponent grass;
  class RoofComponent roof;
};
