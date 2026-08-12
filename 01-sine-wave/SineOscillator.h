#pragma once

#include <cmath>

class SineOscillator {
public:
    void setSampleRate(double sampleRate); 
    void setFrequency(double frequency); 
    double process(); 

private:

        double sampleRate = 44100.0; // Default sample rate
        double frequency = 440.0; // Default frequency 

        double phase = 0.0;
        double phaseIncrement = 0.0;

        void updatePhaseIncrement();
};