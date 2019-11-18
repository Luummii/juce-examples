#include "MainComponent.h"

#define LOG(data) std::cout << data << std::endl;

MainComponent::MainComponent() : openButton("Open"), playButton("Play"), stopButton("Stop"), pauseButton("Pause"), state(Stop), juce::AudioAppComponent(otherDeviceManager)
{
  otherDeviceManager.initialise(2, 2, nullptr, true);
  audioSettings.reset(new AudioDeviceSelectorComponent(otherDeviceManager, 0, 2, 0, 2, true, true, true, true));
  addAndMakeVisible(audioSettings.get());

  openButton.onClick = [this] {
    std::cout << "Choose file" << std::endl;
    openFile();
  };
  addAndMakeVisible(&openButton);

  playButton.onClick = [this] {
    std::cout << "Play" << std::endl;
    transportStateChange(Play);
  };
  playButton.setColour(TextButton::buttonColourId, Colours::green);
  addAndMakeVisible(&playButton);

  pauseButton.onClick = [this] {
    std::cout << "Pause" << std::endl;
    transportStateChange(Pause);
  };
  pauseButton.setColour(TextButton::buttonColourId, Colours::coral);
  addAndMakeVisible(&pauseButton);

  stopButton.onClick = [this] {
    std::cout << "Stop" << std::endl;
    transportStateChange(Stop);
  };
  stopButton.setColour(TextButton::buttonColourId, Colours::blueviolet);
  addAndMakeVisible(&stopButton);

  formatManager.registerBasicFormats();
  transport.addChangeListener(this);

  // formatManager.registerFormat();

  setSize(400, 700);
  setAudioChannels (2, 2);
}

MainComponent::~MainComponent()
{
  shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
  transport.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::openFile()
{
  FileChooser chooser("Choose file", File::getSpecialLocation(File::userDesktopDirectory), "*.wav; *.mp3");

  if (chooser.browseForFileToOpen())
  {
    File file = chooser.getResult();
    AudioFormatReader *reader = formatManager.createReaderFor(file);

    if (reader != nullptr)
    {
      std::unique_ptr<AudioFormatReaderSource> tempSource(new AudioFormatReaderSource(reader, true));
      transport.setSource(tempSource.get(), 0, nullptr, reader->sampleRate);
      transportStateChange(Stop);

      playSource.reset(tempSource.release());
      LOG(reader->getFormatName());
    }
  }
}

void MainComponent::playFile()
{
  transportStateChange(Play);
}

void MainComponent::transportStateChange(TransportState state)
{
  if (this->state != state)
  {
    this->state = state;

    switch (this->state)
    {
    case Stop:
      playButton.setEnabled(true);
      pauseButton.setEnabled(false);
      stopButton.setEnabled(false);
      transport.setPosition(0.0);
      transport.stop();
      break;

    case Play:
      playButton.setEnabled(false);
      pauseButton.setEnabled(true);
      stopButton.setEnabled(true);
      transport.start();
      break;

    case Pause:
      playButton.setEnabled(true);
      pauseButton.setEnabled(false);
      stopButton.setEnabled(true);
      transport.stop();
      break;
    }
  }
}

void MainComponent::changeListenerCallback(ChangeBroadcaster *source)
{
  if (source == &transport)
  {
    if (transport.isPlaying())
    {
      LOG("isPlaying")
    }
    else
    {
      LOG("isStoping")
    }
  }
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
  bufferToFill.clearActiveBufferRegion();

  transport.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
}

void MainComponent::paint(Graphics &g)
{
  g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
  openButton.setBounds(10, 10, getWidth() - 20, 30);
  playButton.setBounds(10, 50, getWidth() - 20, 30);
  pauseButton.setBounds(10, 90, getWidth() - 20, 30);
  stopButton.setBounds(10, 130, getWidth() - 20, 30);
  audioSettings->setBounds(10, 170, getWidth() - 20, 100);
}
