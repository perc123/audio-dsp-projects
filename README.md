# Audio DSP Projects

A series of small, self-contained exercises exploring digital signal processing for audio, implemented in C++ from first principles (no audio frameworks — just the standard library).

Each exercise lives in its own numbered folder with its own source, `.gitignore`, and README covering what it does and how to build it.

## Exercises

| # | Project | Description |
|---|---------|-------------|
| 01 | [sine-wave](01-sine-wave/) | Synthesize a sine wave and write it to a WAV file |

More exercises will be added over time, progressing toward topics like oscillators, filters, envelopes, and basic effects.

## Building

Each project builds standalone with `clang++`:

```bash
cd 01-sine-wave
clang++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o sine
./sine
```

See each project's own README for specifics.

## Requirements

- A C++17 compiler (`clang++` or `g++`)
- No external dependencies — output is raw WAV files playable in any standard audio player
