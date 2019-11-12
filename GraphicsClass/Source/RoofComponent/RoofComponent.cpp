#include "../../JuceLibraryCode/JuceHeader.h"
#include "RoofComponent.h"

RoofComponent::RoofComponent()
{
}

RoofComponent::~RoofComponent()
{
}

void RoofComponent::paint(Graphics &g)
{
  g.setColour(Colours::red);
  Path p;
  p.startNewSubPath(getWidth() - 500, getHeight() - 220);
  p.lineTo(getWidth() - 100, getHeight() - 220);
  p.lineTo(getWidth() - 300, getHeight() - 300);
  p.closeSubPath();

  g.fillPath(p);
  g.strokePath(p, PathStrokeType(15.f));
}

void RoofComponent::resized()
{
}
