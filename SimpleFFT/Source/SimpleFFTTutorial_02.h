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
 version:          2.0.0
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
      : forwardFFT(fftOrder),
        spectrogramImage(Image::RGB, 512, 512, true)
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

  void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override
  {
    if (bufferToFill.buffer->getNumChannels() > 0)
    {
      auto *channelData = bufferToFill.buffer->getReadPointer(0, bufferToFill.startSample);

      for (auto i = 0; i < bufferToFill.numSamples; ++i)
        pushNextSampleIntoFifo(channelData[i]);
    }
  }

  //==============================================================================
  void paint(Graphics &g) override
  {
    g.fillAll(Colours::black);

    g.setOpacity(1.0f);
    g.drawImage(spectrogramImage, getLocalBounds().toFloat());
  }

  void timerCallback() override
  {
    if (nextFFTBlockReady)
    {
      drawNextLineOfSpectrogram();
      nextFFTBlockReady = false;
      repaint();
    }
  }

  void pushNextSampleIntoFifo(float sample) noexcept
  {
    // if the fifo contains enough data, set a flag to say
    // that the next line should now be rendered..
    if (fifoIndex == fftSize)
    {
      if (!nextFFTBlockReady)
      {
        zeromem(fftData, sizeof(fftData));
        memcpy(fftData, fifo, sizeof(fifo));
        nextFFTBlockReady = true;
      }

      fifoIndex = 0;
    }

    fifo[fifoIndex++] = sample;
  }

  void drawNextLineOfSpectrogram()
  {
    auto rightHandEdge = spectrogramImage.getWidth() - 1;
    auto imageHeight = spectrogramImage.getHeight();

    // first, shuffle our image leftwards by 1 pixel..
    spectrogramImage.moveImageSection(0, 0, 1, 0, rightHandEdge, imageHeight);

    // then render our FFT data..
    forwardFFT.performFrequencyOnlyForwardTransform(fftData);

    // find the range of values produced, so we can scale our rendering to
    // show up the detail clearly
    auto maxLevel = FloatVectorOperations::findMinAndMax(fftData, fftSize / 2);

    for (auto y = 1; y < imageHeight; ++y)
    {
      auto skewedProportionY = 1.0f - std::exp(std::log(y / (float)imageHeight) * 0.2f);
      auto fftDataIndex = jlimit(0, fftSize / 2, (int)(skewedProportionY * fftSize / 2));
      auto level = jmap(fftData[fftDataIndex], 0.0f, jmax(maxLevel.getEnd(), 1e-5f), 0.0f, 1.0f);

      spectrogramImage.setPixelAt(rightHandEdge, y, Colour::fromHSV(level, 1.0f, level, 1.0f));
    }
  }

  enum
  {
    fftOrder = 10,
    fftSize = 1 << fftOrder
  };

private:
  dsp::FFT forwardFFT;
  Image spectrogramImage;

  float fifo[fftSize];
  float fftData[2 * fftSize];
  int fifoIndex = 0;
  bool nextFFTBlockReady = false;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpectrogramComponent)
};
