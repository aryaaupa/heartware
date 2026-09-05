# heartware ♥

An open-source, heart-shaped musical PCB keepsake designed as both a polished birthday gift and an embedded-systems portfolio project.

Heartware is being developed as a custom PCB with real-time audio playback, programmable lighting, sensing, battery power, and low-power firmware. The physical gift is intended to play a user-supplied local copy of **“The Man Who Can't Be Moved” by The Script**; the copyrighted recording is intentionally **not** distributed in this repository.

## Project goals

- Heart-shaped custom PCB with the electronics integrated into the board
- ESP32-S3-class embedded controller
- I²S digital audio path and Class-D speaker amplifier
- Local audio playback from flash storage
- Addressable RGB LED perimeter with audio-reactive animation
- Capacitive-touch interaction
- IMU-based pick-up / motion wake behavior
- Li-ion/LiPo battery, charging, battery monitoring, and USB-C power
- Hardware power switch and low-power states
- Debug/test points for board bring-up
- KiCad design sources, BOM, manufacturing outputs, firmware, and validation documentation

## Repository structure

```text
hardware/        KiCad board and schematic sources
firmware/        Embedded firmware and audio pipeline
manufacturing/   BOM / fabrication documentation
docs/            Architecture, bring-up, and validation notes
assets/private/  LOCAL-ONLY audio assets; ignored by Git
```

## Audio asset policy

The public repository contains no copyrighted song recording. A locally obtained audio file can be placed at:

```text
assets/private/song.wav
```

That directory is excluded by `.gitignore`. The firmware/build pipeline will be developed to preprocess and embed or stream the local asset without committing it.

## Status

**Rev A** is the initial KiCad prototype and uses a simpler XIAO ESP32-C3 + I²S amplifier architecture. **Rev B** is the planned advanced redesign described above and will replace the prototype architecture before fabrication.

> Do not fabricate Rev A yet. Footprints, power design, battery circuitry, audio chain, and Rev B architecture still require design review and DRC/ERC validation.

## Engineering evidence planned

The project will document requirements, architecture tradeoffs, schematic capture, PCB layout, power budgeting, audio pipeline, firmware state machine, LED/audio synchronization, battery measurements, bring-up logs, oscilloscope captures, current consumption, and final hardware validation.
