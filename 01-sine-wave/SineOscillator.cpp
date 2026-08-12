#include "SineOscillator.h"
#include <cmath>

void SineOscillator::setSampleRate(double sampleRate)
{
    this->sampleRate = sampleRate;
    updatePhaseIncrement();
}

void SineOscillator::setFrequency(double frequency)
{
    this->frequency = frequency;
    updatePhaseIncrement();
}

double SineOscillator::process()
{
    double sample =
    std::sin(2.0 * M_PI * phase);
    phase += phaseIncrement;
    if (phase >= 1.0) {
        phase -= 1.0;
    }
    return sample;
}

void SineOscillator::updatePhaseIncrement()
{
    phaseIncrement = frequency / sampleRate;
}