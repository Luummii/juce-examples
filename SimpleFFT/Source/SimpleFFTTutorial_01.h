/*
  ==============================================================================

   This file is part of the JUCE tutorials.
   Copyright (c) 2017 - ROLI Ltd.

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:             SimpleFFTTutorial
 version:          1.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Displays an FFT spectrogram.

 dependencies:     juce_audio_basics, juce_audio_devices, juce_audio_formats,
                   juce_audio_processors, juce_audio_utils, juce_core,
                   juce_data_structures, juce_dsp, juce_events, juce_graphics,
                   juce_gui_basics, juce_gui_extra
 exporters:        xcode_mac, vs2017, linux_make

 type:             Component
 mainClass:        SpectrogramComponent

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/

#pragma once

//==============================================================================
class SpectrogramComponent : public AudioAppComponent,
                             private Timer
{
public:
  SpectrogramComponent()
      : spectrogramImage(Image::RGB, 512, 512, true)
  {
    setOpaque(true);
    setAudioChannels(2, 0); // we want a couple of input channels but no outputs
    startTimerHz(60);
    setSize(700, 500);
  }

  ~SpectrogramComponent() override
  {
    shutdownAudio();
  }

  //==============================================================================
  void prepareToPlay(int, double) override {}
  void releaseResources() override {}

  void getNextAudioBlock(const AudioSourceChannelInfo &) override {}

  //==============================================================================
  void paint(Graphics &g) override
  {
    g.fillAll(Colours::black);

    g.setOpacity(1.0f);
    g.drawImage(spectrogramImage, getLocalBounds().toFloat());
  }

  void timerCallback() override {}

  void pushNextSampleIntoFifo(float) noexcept
  {
    // if the fifo contains enough data, set a flag to say
    // that the next line should now be rendered..
  }

  void drawNextLineOfSpectrogram() {}

private:
  Image spectrogramImage;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpectrogramComponent)
};
