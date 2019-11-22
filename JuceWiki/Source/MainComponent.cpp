#include "MainComponent.h"
#include "./Utilites.h"
#include "./Content/Sidebar.h"

MainComponent::MainComponent() : sidebar("", 250, true, nullptr, false)
{
  /* sidebar */
  sidebar.setTitleBarHeight(35);
  auto sidebarHeader = new SidebarHeader();
  sidebar.setTitleBarComponent(sidebarHeader, false);

  auto sidebarContent = new SidebarContent();
  sidebarContent->addEntry("DSP 1");
  sidebarContent->addEntry("DSP 2");
  sidebar.setContent(sidebarContent);

  sidebar.setShadowWidth(5);
  sidebar.showOrHide(false);
  addAndMakeVisible(sidebar);

  startTimer(800);
  setSize(800, 600);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint(Graphics &g)
{
  g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
  auto area = getLocalBounds();
}

void MainComponent::timerCallback()
{
  sidebar.showOrHide(true);
  stopTimer();
}