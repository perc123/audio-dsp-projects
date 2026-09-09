#include <fstream>
#include <iostream>
#include <vector>
#include "SineOscillator.h"

void writeWav(
        const std::string& filename,
        const std::vector<double>& samples,
        int sampleRate)
    {
        std::ofstream file(filename, std::ios::binary);

        if (!file)
        {
            std::cerr << "Could not open file.\n";
            return;
        }

        const int numChannels = 1;
        const int bitsPerSample = 16;

        const int bytesPerSample = bitsPerSample / 8;
        const int dataSize = samples.size() * numChannels * bytesPerSample;

        const int fileSize = 36 + dataSize;

        // RIFF header
        file.write("RIFF", 4);
        file.write(reinterpret_cast<const char*>(&fileSize), 4);
        file.write("WAVE", 4);

        //fmt chunk
        file.write("fmt ", 4);

        const int fmtChunkSize = 16;
        const short audioFormat = 1; // PCM
        const short channels = numChannels;
        const short blockAlign = channels * bytesPerSample;
        const int byteRate = sampleRate * blockAlign;

        file.write(reinterpret_cast<const char*>(&fmtChunkSize), 4);
        file.write(reinterpret_cast<const char*>(&audioFormat), 2);
        file.write(reinterpret_cast<const char*>(&channels), 2);
        file.write(reinterpret_cast<const char*>(&sampleRate), 4);
        file.write(reinterpret_cast<const char*>(&byteRate), 4);
        file.write(reinterpret_cast<const char*>(&blockAlign), 2);
        file.write(reinterpret_cast<const char*>(&bitsPerSample), 2);

        // data chunk
        file.write("data", 4);
        file.write(reinterpret_cast<const char*>(&dataSize), 4);

        // Convert floating-point samples to 16-bit integers
        for (double sample : samples)
        {
            if (sample > 1.0) sample = 1.0;
            if (sample < -1.0) sample = -1.0;
            short intSample = static_cast<short>(sample * 32767.0);
            file.write(reinterpret_cast<const char*>(&intSample), 2);
        }

        file.close();
    }


void writeCsv(const std::string& filename, const std::vector<double>& samples, double sampleRate)
{
    std::ofstream file(filename);

    if (!file)
    {
    std::cerr << "Could not open CSV file.\n";
    return;
    }

    file << "sample,time,amplitude\n";

    for (std::size_t n = 0; n < samples.size(); ++n)
    {
        double amplitude = samples[n];
        double time = static_cast<double>(n) / sampleRate;
        file << n << "," << time << "," << amplitude << "\n";
    }

    file.close();
}

int main() {
    const double sampleRate = 44100.0; // Samples per second
    const double startFrequency = 440.0; // Start frequency of the sine wave
    const double endFrequency = 100.0; // End frequency of the sine wave
    const double duration = 2; // Duration of the sine wave in seconds

    const int numSamples = static_cast<int>(sampleRate * duration);

    std::vector<double> samples(numSamples);

    SineOscillator oscillator;
    
    oscillator.setSampleRate(sampleRate);
    oscillator.setFrequency(startFrequency);

    // Code for generating the sine wave samples with a frequency sweep from startFrequency to endFrequency
/*     for (int n = 0; n < numSamples; ++n) {
        // double time = static_cast<double>(n) / sampleRate;
        double progress = static_cast<double>(n) / (numSamples);
        double frequency = startFrequency + (endFrequency - startFrequency) * progress;

        oscillator.setFrequency(frequency);

        samples[n] = oscillator.process();
    } */
   // Code for generating Amplitude Modulated (AM) sine wave samples
   for (int n = 0; n < numSamples; ++n) {
        double time = static_cast<double>(n) / sampleRate;
        double Amplitude;
        if (time < 0.5) {
            Amplitude = time / 0.5; // Ramp up from 0 to 1 over the first 0.5 seconds
        }
        else if (time > 1.75) {
            Amplitude = (duration - time) / 0.25; // Ramp down from 1 to 0 over the last 0.25 seconds
        }
        else {
            Amplitude = 1.0; // Constant amplitude of 1 between 0.5 and 0.75 seconds
        }
        double sample = oscillator.process();

        samples[n] = sample * Amplitude;
    }

    std::cout << "Generated "
                << samples.size()
                <<" samples\n";

    std::cout << "First 10 samples:\n";

    for (int n = 0; n < 10; ++n) {
        std::cout << samples[n] << "\n";
    }

    writeCsv("waveform.csv", samples, sampleRate);
    writeWav("sine.wav", samples, sampleRate);

    std::cout << "Wrote sine.wav\n";

    return 0;
}
