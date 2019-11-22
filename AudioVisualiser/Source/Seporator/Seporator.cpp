#include "../../JuceLibraryCode/JuceHeader.h"
#include "Seporator.h"
#include "../Utilites.h"

Seporator::Seporator()
{
}

Seporator::~Seporator()
{
}

void Seporator::paint(Graphics &g)
{
  g.setColour(Colours::grey);
  g.drawLine(0, getHeight(), getWidth(), getHeight(), 1.f);
}

void Seporator::resized()
{
}
