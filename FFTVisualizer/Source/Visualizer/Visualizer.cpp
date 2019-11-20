#include "../../JuceLibraryCode/JuceHeader.h"
#include "Visualizer.h"

Visualizer::Visualizer(int fftOrder) : Thread("fft"), fft(fftOrder), windowingFunction(static_cast<size_t>(fft.getSize()), dsp::WindowingFunction<float>::hamming)
{
  inputBuffer.setSize(1, 16384, false, true);
  processingBuffer.setSize(1, 2 * fft.getSize(), false, true);

  fftOutputBuffer.setSize(1, fft.getSize() / 2, false, true);
  fftMaxOutputBuffer.setSize(1, fft.getSize() / 2, false, true);

  startThread();
}

Visualizer::~Visualizer()
{
  stopThread(3000);
}

void Visualizer::setSampleRate(double fs) { sampleRate = fs; }

double Visualizer::getSampleRate() const { return sampleRate; }

int Visualizer::getNumBins() const
{
  return fft.getSize() / 2;
}

void Visualizer::addSamples(const float *samples, int numSamples)
{
  jassert(sampleRate > 0.);
  fifo.addToFifo(samples, numSamples);
}

void Visualizer::copyCurrentFft(float *samples, int numSamples) const
{
  jassert(numSamples == fft.getSize() / 2);
  ScopedLock lock(processingLock);
  FloatVectorOperations::copy(samples, fftOutputBuffer.getReadPointer(0), numSamples);
}

bool Visualizer::getMaxHasChanged()
{
  ScopedLock lock(processingLock);
  if (!maxHasChanged)
    return false;

  maxHasChanged = false;
  return true;
}

void Visualizer::resetMax()
{
  ScopedLock lock(processingLock);
  fftMaxOutputBuffer.clear();
  maxHasChanged = true;
}

void Visualizer::copyCurrentMax(float *samples, int numSamples) const
{
  jassert(numSamples == fft.getSize() / 2);
  ScopedLock lock(processingLock);
  FloatVectorOperations::copy(samples, fftMaxOutputBuffer.getReadPointer(0), numSamples);
}

void Visualizer::run()
{
  while (!threadShouldExit())
  {
    const auto numReady = fifo.abstractFifo.getNumReady();
    if (numReady > 0)
    {
      addToInputBuffer(numReady);
      perform();
    }

    sleep(1);
  }
}

void Visualizer::addToInputBuffer(int numSamples)
{
  const auto bufferSize = inputBuffer.getNumSamples();
  if (writePointer + numSamples < bufferSize)
  {
    fifo.readFromFifo(inputBuffer.getWritePointer(0, writePointer), numSamples);
    writePointer += numSamples;
  }
  else
  {
    const auto numToCopy1 = bufferSize - writePointer;
    fifo.readFromFifo(inputBuffer.getWritePointer(0, writePointer), numToCopy1);

    const auto numToCopy2 = numSamples - numToCopy1;
    fifo.readFromFifo(inputBuffer.getWritePointer(0), numToCopy2);

    writePointer = numToCopy2;
  }
}

void Visualizer::readFromInputBuffer(float *destination, int numSamples)
{
  const auto bufferSize = inputBuffer.getNumSamples();

  if (readPointer + numSamples < bufferSize)
  {
    FloatVectorOperations::copy(destination, inputBuffer.getReadPointer(0, readPointer), numSamples);
    readPointer += numSamples;
  }
  else
  {
    const auto numToCopy1 = bufferSize - readPointer;
    FloatVectorOperations::copy(destination, inputBuffer.getReadPointer(0, readPointer), numToCopy1);

    const auto numToCopy2 = numSamples - numToCopy1;
    FloatVectorOperations::copy(destination + numToCopy1, inputBuffer.getReadPointer(0), numToCopy2);

    readPointer = numToCopy2;
  }
}