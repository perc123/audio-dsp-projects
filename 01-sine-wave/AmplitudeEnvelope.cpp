#include AmplitudeEnvelope.h

void AmplitudeEnvelope::setSampleRate(double sampleRate)
{
    this->sampleRate = sampleRate;
    updateIncrements();
}

void AmplitudeEnvelope::setAttackTime(double attackTime)
{
    this->attackTime = attackTime;
    updateIncrements();
}

void AmplitudeEnvelope::setReleaseTime(double releaseTime)
{
    this->releaseTime = releaseTime;
    updateIncrements();
}

void AmplitudeEnvelope::noteOn()
{
    state = State::Attack;
}

void AmplitudeEnvelope::noteOff()
{
    state = State::Release;
}

double AmplitudeEnvelope::process()
{
    switch (state)
    {
        case State::Idle:
            level = 0.0;
            break;

        case State::Attack:
            level += attackIncrement;
            if (level >= 1.0)
            {
                level = 1.0;
                state = State::Sustain;
            }
            break;

        case State::Sustain:
            level = 1.0;
            break;

        case State::Release:
            level -= releaseIncrement;
            if (level <= 0.0)
            {
                level = 0.0;
                state = State::Idle;
            }
            break;
    }

    return level; 
}

void AmplitudeEnvelope::updateIncrements()
{
    attackIncrement = (attackTime > 0.0) ? (1.0 / (attackTime * sampleRate)) : 1.0;
    releaseIncrement = (releaseTime > 0.0) ? (1.0 / (releaseTime * sampleRate)) : 1.0;
}