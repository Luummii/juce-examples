#include "../../JuceLibraryCode/JuceHeader.h"
#include "WallComponent.h"

WallComponent::WallComponent() {}
WallComponent::~WallComponent() {}

void WallComponent::paint(Graphics &g)
{
  Rectangle<float> wall(.0f, .0f, getWidth(), getHeight());
  g.fillCheckerBoard(wall, 20, 10, Colours::sandybrown, Colours::saddlebrown);
  g.drawRect(wall);
}

void WallComponent::resized() {}
