#include "MainComponent.h"
#include "./Utilites/Utilites.h"

MainComponent::MainComponent() : AudioAppComponent(deviceManager)
{
  formatManager.registerBasicFormats();
  controlPanel.btnOpenListner = [this](File file) {
    setNewFile(file);
  };
  controlPanel.btnActionListner = [this](TransportState state) {
    transportStateChange(state);
  };

  deviceManager.initialise(2, 2, nullptr, true);
  audioSettings.reset(new AudioDeviceSelectorComponent(deviceManager, 0, 2, 0, 2, true, true, true, true));

  addAndMakeVisible(audioSettings.get());
  addAndMakeVisible(&seporator);
  addAndMakeVisible(&controlPanel);

  setSize(800, 700);
  if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio) && !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
  {
    RuntimePermissions::request(RuntimePermissions::recordAudio, [&](bool granted) { if (granted)  setAudioChannels (2, 2); });
  }
  else
  {
    setAudioChannels(2, 2);
  }
}

MainComponent::~MainComponent()
{
  shutdownAudio();
}

void MainComponent::setNewFile(File file)
{
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

void MainComponent::transportStateChange(TransportState state)
{
  switch (state)
  {
  case TransportState::Stop:
    transport.stop();
    transport.setPosition(0.0);
    LOG(">> STOP");
    break;

  case TransportState::Play:
    transport.start();
    LOG(">> PLAY");
    break;

  case TransportState::Pause:
    transport.stop();
    LOG(">> PAUSE");
    break;
  }
}

void MainComponent::changeListenerCallback(ChangeBroadcaster *source)
{
  if (source == &transport)
  {
    if (transport.isPlaying())
    {
      LOG("isPlaying");
    }
    else
    {
      LOG("isStoping");
    }
  }
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
  transport.prepareToPlay(samplesPerBlockExpected, sampleRate);
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
  controlPanel.setBounds(10, 10, getWidth() - 20, 50);
  seporator.setBounds(10, 55, getWidth() - 20, 1);

  audioSettings->setBounds(10, 60, getWidth() - 10, 100);
}
