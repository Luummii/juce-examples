#include "../../JuceLibraryCode/JuceHeader.h"
#include "ControlPanel.h"
#include "../Utilites/Utilites.h"

ControlPanel::ControlPanel()
{
  /* open */
  btnOpen.setButtonText(tr("Открыть"));
  btnOpen.onClick = [this] {
    open();
  };
  addAndMakeVisible(&btnOpen);

  /* play */
  btnPlay.setButtonText(tr("Играть"));
  btnPlay.setColour(TextButton::buttonColourId, Colours::green);
  btnPlay.onClick = [this] {
    play();
  };
  addAndMakeVisible(&btnPlay);

  /* pause */
  btnPause.setButtonText(tr("Пауза"));
  btnPause.setColour(TextButton::buttonColourId, Colours::blueviolet);
  btnPause.onClick = [this] {
    pause();
  };
  addAndMakeVisible(&btnPause);

  /* pause */
  btnStop.setButtonText(tr("Стоп"));
  btnStop.setColour(TextButton::buttonColourId, Colours::red);
  btnStop.onClick = [this] {
    stop();
  };
  addAndMakeVisible(&btnStop);
}

ControlPanel::~ControlPanel()
{
}

void ControlPanel::open()
{
  FileChooser chooser("Choose file", File::getSpecialLocation(File::userDesktopDirectory), "*.wav; *.mp3");
  if (chooser.browseForFileToOpen())
  {
    File file = chooser.getResult();
    LOG("Oplen file: " + file.getFileName());
    btnOpenListner(file);
  }
}

void ControlPanel::play()
{
  btnActionListner(TransportState::Play);
  btnStop.setEnabled(true);
  btnPause.setEnabled(true);
  btnPlay.setEnabled(false);
}

void ControlPanel::pause()
{
  btnActionListner(TransportState::Pause);
  btnStop.setEnabled(true);
  btnPause.setEnabled(false);
  btnPlay.setEnabled(true);
}

void ControlPanel::stop()
{
  btnActionListner(TransportState::Stop);
  btnStop.setEnabled(false);
  btnPause.setEnabled(false);
  btnPlay.setEnabled(true);
}

void ControlPanel::paint(Graphics &g)
{
}

void ControlPanel::resized()
{
  btnOpen.setBounds(10, 10, 80, 20);
  btnStop.setBounds(110, 10, 60, 20);
  btnPlay.setBounds(175, 10, 60, 20);
  btnPause.setBounds(240, 10, 60, 20);
}
