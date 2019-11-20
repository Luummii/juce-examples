#include "../../JuceLibraryCode/JuceHeader.h"
#include "VisualizerComponent.h"

VisualizerComponent::VisualizerComponent(Visualizer &visualizer) : Component("FFTDisplay"), visualizer(visualizer)
{
  fftInputBuffer.setSize(1, visualizer.getNumBins(), false, true);
  maxInputBuffer.setSize(1, visualizer.getNumBins(), false, true);

  redrawTimer.setCallback([this]() { update(); });
  redrawTimer.startTimerHz(60);

  maxResetTimer.setCallback([this]() { resetMax(); });

  addAndMakeVisible(fftGraph);
  addAndMakeVisible(maxGraph);
}

VisualizerComponent::~VisualizerComponent()
{
}

void VisualizerComponent::resetMax()
{
  visualizer.resetMax();
  maxResetTimer.stopTimer();
}

void VisualizerComponent::paint(Graphics &g)
{
  g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
  g.setColour(Colours::grey);
  g.drawRect(getLocalBounds(), 1);

  g.setColour(Colours::white);
  g.setFont(14.0f);
  g.drawText("VisualizerComponent", getLocalBounds(), Justification::centred, true);
}

void VisualizerComponent::resized()
{
  maxGraph.setBounds(getLocalBounds());
  fftGraph.setBounds(getLocalBounds());
}
