#include "../../JuceLibraryCode/JuceHeader.h"
#include "GrassComponent.h"

GrassComponent::GrassComponent()
{
}

GrassComponent::~GrassComponent()
{
}

void GrassComponent::paint(Graphics &g)
{
  g.setColour(Colours::green);
  g.drawLine(0, getHeight(), getWidth(), getHeight(), 20.f);
}

void GrassComponent::resized()
{
}
