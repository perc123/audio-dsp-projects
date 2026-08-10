#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

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

int main() {
    const double sampleRate = 44100.0; // Samples per second
    const double frequency = 220.0; // Frequency of the sine wave (A4 note)
    const double duration = 1.0; // Duration of the sine wave in seconds

    const int numSamples = static_cast<int>(sampleRate * duration);

    std::vector<double> samples(numSamples);

    for (int n = 0; n < numSamples; ++n) {
        double time = static_cast<double>(n) / sampleRate;

        samples[n] = std::sin(2.0 * M_PI * frequency * time);
    }

    std::cout << "Generated "
                << samples.size()
                <<" samples\n";

    std::cout << "First 10 samples:\n";
    for (int n = 0; n < 10; ++n) {
        std::cout << samples[n] << "\n";
    }

    writeWav("sine.wav", samples, sampleRate);

    std::cout << "Wrote sine.wav\n";

    return 0;
}
