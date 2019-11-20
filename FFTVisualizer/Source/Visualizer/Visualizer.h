#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

class Visualizer : public Component, public Thread
{
public:
  explicit Visualizer(int fftOrder);
  ~Visualizer();

  void setSampleRate(double fs);
  double getSampleRate() const;
  int getNumBins() const;
  void addSamples(const float *samples, int numSamples);
  void copyCurrentFft(float *samples, int numSamples) const;
  bool getMaxHasChanged();
  void resetMax();
  void copyCurrentMax(float *samples, int numSamples) const;

private:
  void run() override;
  void addToInputBuffer(int numSamples);
  void readFromInputBuffer(float *destination, int numSamples);

  void copyFromFftBufferToInputBuffer()
  {
    const auto fftSize = fft.getSize();
    processingBuffer.clear();
    readFromInputBuffer(processingBuffer.getWritePointer(0), fftSize);
    windowingFunction.multiplyWithWindowingTable(processingBuffer.getWritePointer(0),
                                                 static_cast<size_t>(fftSize));
  }

  void perform()
  {
    while (getWrappedDistanceBetweenPointers() > fft.getSize())
    {
      copyFromFftBufferToInputBuffer();
      fft.performFrequencyOnlyForwardTransform(processingBuffer.getWritePointer(0));
      applyBalisticsAndCopyToOutput();
    }
  }

  void applyBalisticsAndCopyToOutput()
  {
    ScopedLock sl(processingLock);
    const auto input = processingBuffer.getWritePointer(0);
    const auto output = fftOutputBuffer.getWritePointer(0);
    const auto maxOutput = fftMaxOutputBuffer.getWritePointer(0);

    const auto decayRate = Decibels::decibelsToGain(-40.f * static_cast<float>(fft.getSize()) / static_cast<float>(sampleRate));

    for (auto n = 0; n < fftOutputBuffer.getNumSamples(); ++n)
    {
      if (input[n] > output[n])
      {
        output[n] = input[n];
      }
      else
        output[n] *= decayRate;

      if (input[n] > maxOutput[n])
      {
        maxOutput[n] = input[n];
        maxHasChanged = true;
      }
    }
  }

  int getWrappedDistanceBetweenPointers() const
  {
    if (writePointer > readPointer)
      return writePointer - readPointer;

    return inputBuffer.getNumSamples() - readPointer + writePointer;
  }

  struct Fifo
  {
    void addToFifo(const float *someData, int numItems)
    {
      int start1, size1, start2, size2;
      abstractFifo.prepareToWrite(numItems, start1, size1, start2, size2);

      if (size1 > 0)
        copySomeData(myBuffer.data() + start1, someData, size1);

      if (size2 > 0)
        copySomeData(myBuffer.data() + start2, someData + size1, size2);

      abstractFifo.finishedWrite(size1 + size2);
    }

    void readFromFifo(float *someData, int numItems)
    {
      int start1, size1, start2, size2;
      abstractFifo.prepareToRead(numItems, start1, size1, start2, size2);

      if (size1 > 0)
        copySomeData(someData, myBuffer.data() + start1, size1);

      if (size2 > 0)
        copySomeData(someData + size1, myBuffer.data() + start2, size2);

      abstractFifo.finishedRead(size1 + size2);
    }

    void copySomeData(float *dest, const float *source, int numItems) const
    {
      FloatVectorOperations::copy(dest, source, numItems);
    }

    AbstractFifo abstractFifo{4096};
    std::array<float, 4096> myBuffer{};
  };

  Fifo fifo;

  double sampleRate{0.};

  AudioBuffer<float> processingBuffer;
  AudioBuffer<float> fftOutputBuffer;
  AudioBuffer<float> fftMaxOutputBuffer;
  AudioBuffer<float> inputBuffer;

  dsp::FFT fft;

  dsp::WindowingFunction<float> windowingFunction;

  bool maxHasChanged{false};

  int writePointer{0};
  int readPointer{0};

  CriticalSection processingLock;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Visualizer)
};
