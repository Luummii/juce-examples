#include "Visualiser.h"

Visualiser::Visualiser() : AudioVisualiserComponent(2)
{
  setBufferSize(128);
  setSamplesPerBlock(16);
  setColours(Colours::black, Colours::indianred);
}

Visualiser::~Visualiser()
{

}
