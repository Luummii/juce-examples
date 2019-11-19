#include "MainComponent.h"

MainComponent::MainComponent()
{
  slider1.setSliderStyle(Slider::SliderStyle::LinearVertical);
  slider1.setColour(Slider::backgroundColourId, Colours::red);
  slider1.setRange(0.0, 1.0);
  slider1.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
  addAndMakeVisible(slider1);

  slider2.setSliderStyle(Slider::SliderStyle::LinearVertical);
  slider2.setColour(Slider::backgroundColourId, Colours::blue);
  slider2.setRange(0.0, 1.0);
  slider2.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
  addAndMakeVisible(slider2);

  slider3.setSliderStyle(Slider::SliderStyle::LinearVertical);
  slider3.setColour(Slider::backgroundColourId, Colours::greenyellow);
  slider3.setRange(0.0, 1.0);
  slider3.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
  addAndMakeVisible(slider3);

  slider4.setSliderStyle(Slider::SliderStyle::Rotary);
  slider4.setColour(Slider::backgroundColourId, Colours::ivory);
  slider4.setRange(0.0, 1.0);
  slider4.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
  addAndMakeVisible(slider4);

  slider5.setSliderStyle(Slider::SliderStyle::Rotary);
  slider5.setColour(Slider::backgroundColourId, Colours::violet);
  slider5.setRange(0.0, 1.0);
  slider5.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
  addAndMakeVisible(slider5);

  slider6.setSliderStyle(Slider::SliderStyle::Rotary);
  slider6.setColour(Slider::backgroundColourId, Colours::navajowhite);
  slider6.setRange(0.0, 1.0);
  slider6.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
  addAndMakeVisible(slider6);

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
  Rectangle<int> bounds = getLocalBounds();

  FlexBox flexbox;
  flexbox.flexDirection = FlexBox::Direction::column;
  flexbox.flexWrap = FlexBox::Wrap::wrap;
  flexbox.alignContent = FlexBox::AlignContent::stretch;

  Array<FlexItem> itemArray;
  itemArray.add(FlexItem(150, 200, slider1));
  itemArray.add(FlexItem(150, 200, slider2));
  itemArray.add(FlexItem(150, 200, slider3));

  flexbox.items = itemArray;
  flexbox.performLayout(bounds.removeFromLeft(400));

  FlexBox flexbox2;
  flexbox2.flexDirection = FlexBox::Direction::column;
  flexbox2.flexWrap = FlexBox::Wrap::wrap;
  flexbox2.alignContent = FlexBox::AlignContent::stretch;

  Array<FlexItem> itemArray2;
  itemArray2.add(FlexItem(150, 200, slider4));
  itemArray2.add(FlexItem(150, 200, slider5));
  itemArray2.add(FlexItem(150, 200, slider6));

  flexbox2.items = itemArray2;
  flexbox2.performLayout(bounds);
}
