# 🌿 Singing Game (ESP32) (C code)

A small and mindful game where you face a simple challenge: match the frequency of a tone using your voice, a whistle, or another sound source. The board listens. If your voice is true, you win. If not, try again.

This project is implemented on the ESP32 platform using low-level DAC and ADC register manipulation, and it serves both as a game and a study of signal generation, sampling, and interpretation.

---

## 🎮 How It Works

1. The ESP32 generates a pure tone using its internal cosine waveform generator.
2. You listen carefully.
3. You reproduce the tone — singing, whistling, humming.
4. The ESP32 samples your sound using an amplified microphone.
5. It detects your frequency and compares it to the one it emitted.
6. A gentle LED informs you whether harmony was achieved.

---

## 🔧 Requirements

- NodeMCU-32S (ESP32 dev board)
- 2 LEDs
- 2 Pushbuttons
- 1 Amplified microphone module
- USB cable
- Breadboard and jumper wires
- Earphones or speaker (connected to DAC output pin)

## 🎥 Demo

[![Watch the singing game here](https://img.youtube.com/vi/Q-3gZDLPwIs/hqdefault.jpg)](https://youtu.be/Q-3gZDLPwIs)
