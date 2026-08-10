# 01 · Sine Wave

Generates a 1-second, 220 Hz (A3) sine wave and writes it out as a 16-bit PCM mono WAV file.

## What it does

- Synthesizes `sampleRate * duration` samples of `sin(2π · frequency · t)`
- Prints the sample count and the first 10 sample values
- Encodes the result as a standard RIFF/WAVE file (`sine.wav`) with a hand-written WAV header — no external audio libraries

## Build & run

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o sine
./sine
```

This produces `sine.wav` in the current directory, playable in any standard audio player.

## Parameters

Edit the constants at the top of `main()` to change the output:

| Constant     | Default | Meaning                  |
|--------------|---------|---------------------------|
| `sampleRate` | 44100.0 | Samples per second (Hz)  |
| `frequency`  | 220.0   | Tone frequency (Hz)       |
| `duration`   | 1.0     | Length of the tone (sec) |

## Output format

- Mono, 16-bit signed PCM
- Sample rate matches `sampleRate` above
- Floating-point samples are clamped to `[-1.0, 1.0]` and scaled to the 16-bit range before writing
