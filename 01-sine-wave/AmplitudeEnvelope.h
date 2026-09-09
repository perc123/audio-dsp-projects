#pragma once

class AmplitudeEnvelope {
public:
    void setSampleRate(double sampleRate);

    void setAttackTime(double attackTime);
    void setReleaseTime(double releaseTime);

    void noteOn();
    void noteOff();

    double process();

private:
    enum class State {
        Idle,
        Attack,
        Sustain,
        Release
    };

    State state = State::Idle;
    double sampleRate = 44100.0; // Default sample rate

    double attackTime = 0.1; // Default attack time in seconds
    double releaseTime = 0.1; // Default release time in seconds

    double level = 0.0; // Current amplitude level

    double attackIncrement = 0.0; // Increment per sample during attack
    double releaseIncrement = 0.0; // Increment per sample during release

    void updateIncrements();
};