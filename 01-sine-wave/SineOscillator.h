#pragma once

#include <cmath>

class SineOscillator {
public:
    void setSampleRate(double sampleRate) {
        this->sampleRate = sampleRate;
        updatePhaseIncrement();
    }

    void setFrequency(double frequency) {
        this->frequency = frequency;
        updatePhaseIncrement();
    }

    double process() {
        double sample = std::sin(2.0 * M_PI * phase);
        phase += phaseIncrement;
        if (phase >= 1.0) {
            phase -= 1.0;
        }
        return sample;
    }

    private:

        double sampleRate = 44100.0; // Default sample rate
        double frequency = 440.0; // Default frequency 

        double phase = 0.0;
        double phaseIncrement = 0.0;

        void updatePhaseIncrement() {
            phaseIncrement = frequency / sampleRate;
        }
};