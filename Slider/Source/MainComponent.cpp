#include "MainComponent.h"

MainComponent::MainComponent()
{
  slider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
  slider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxLeft, false, 50, 20);
  slider.setTextValueSuffix(" Hz");
  slider.setRange(50.f, 5000.f, 10.f);
  slider.setValue(500.f);
  slider.addListener(this);
  slider.setSkewFactorFromMidPoint(100.f);
  addAndMakeVisible(slider);

  labelSlider.setText("Label slider", dontSendNotification);
  labelSlider.attachToComponent(&slider, false);
  addAndMakeVisible(labelSlider);

  getLookAndFeel().setColour(Slider::thumbColourId, Colours::blue);
  // getLookAndFeel().setColour(Slider::rotarySliderFillColourId, Colours::red); для круглых слайдеров
  getLookAndFeel().setColour(Slider::trackColourId, Colours::red);

  // otherLookAndFeel.setColour(Slider::thumbColourId, Colours::beige);
  // slider.setLookAndFeel(&otherLookAndFeel);

  setSize(600, 400);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint(Graphics &g)
{
  g.fillAll(Colours::salmon);

  Rectangle<int> section1 = getLocalBounds().removeFromRight(getLocalBounds().getWidth() * .5).removeFromTop(getLocalBounds().getHeight() * .5);
  g.setColour(Colours::blue);
  g.drawRect(section1);

  Rectangle<int> section2 = getLocalBounds().removeFromLeft(getLocalBounds().getWidth() * .5).removeFromBottom(getLocalBounds().getHeight() * .5);
  g.setColour(Colours::red);
  g.fillRect(section2);
  g.drawRect(section2);
}

void MainComponent::resized()
{
  const int border = 50;
  Rectangle<int> area = getLocalBounds();
  Rectangle<int> sliderArea = area.removeFromTop(area.getHeight() * .3).removeFromLeft(area.getWidth() * .5).reduced(border);
  slider.setBounds(sliderArea);
}

void MainComponent::sliderValueChanged(Slider *slider)
{
  if (slider == &this->slider)
  {
    Logger::outputDebugString(String(this->slider.getValue()));
  }
}
