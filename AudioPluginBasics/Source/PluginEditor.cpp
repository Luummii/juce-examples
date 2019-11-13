#include "PluginProcessor.h"
#include "PluginEditor.h"

AudioPluginBasicsAudioProcessorEditor::AudioPluginBasicsAudioProcessorEditor(AudioPluginBasicsAudioProcessor &p)
    : AudioProcessorEditor(&p), processor(p)
{
  gainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
  gainSlider.setRange(0.0, 1.0);
  gainSlider.addListener(this);
  addAndMakeVisible(gainSlider);
  setSize(400, 200);
}

AudioPluginBasicsAudioProcessorEditor::~AudioPluginBasicsAudioProcessorEditor()
{
}

void AudioPluginBasicsAudioProcessorEditor::paint(Graphics &g)
{
  g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void AudioPluginBasicsAudioProcessorEditor::resized()
{
  gainSlider.setBounds(getLocalBounds());
}

void AudioPluginBasicsAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
  if (slider == &gainSlider)
  {
    processor.rawVolume = gainSlider.getValue();
  }
}
