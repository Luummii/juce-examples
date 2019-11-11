#include "MainComponent.h"

MainComponent::MainComponent()
{
  setSize(600, 400);
  addAndMakeVisible(wall);
  addAndMakeVisible(grass);
  addAndMakeVisible(roof);
}

MainComponent::~MainComponent() {}

void MainComponent::paint(Graphics &g)
{
  g.fillAll(Colours::skyblue);
}

void MainComponent::resized() {
  // wall.setBounds(getLocalBounds());
  // wall.setBounds(100, 180, getWidth() - 200, getHeight() - 200);
  wall.setBounds(getWidth() - 500, getHeight() - 210, 400, 200);
  grass.setBounds(getLocalBounds());
  roof.setBounds(getLocalBounds());
}
