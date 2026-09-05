# Heartware Rev B

Rev B turns the original musical-heart idea into a portable embedded system rather than an LED novelty board.

## Product behavior

The physical slide switch is the hard master power control. When switched on, the board performs a short warm-light boot animation and waits. Touching the central copper heart starts or stops the locally installed song. Twelve perimeter RGB LEDs animate from a precomputed audio-energy envelope so the light behavior follows the recording without spending MCU time on real-time FFT processing. Picking the heart up can wake a dim idle glow through the accelerometer, but motion never starts the song automatically.

## Hardware stack

- XIAO ESP32-S3 controller for MP3 decoding, I2S, capacitive touch, USB debug and LED control.
- MAX98357A I2S Class-D amplifier driving a 4-8 ohm miniature speaker.
- LIS3DH 3-axis accelerometer for pick-up/wake interaction.
- Twelve SK6812MINI-E RGB LEDs on the visible front perimeter.
- MCP73871 power-path charger so the LiPo can charge while the downstream product rail is physically switched off.
- TPS63031 buck-boost regulator for a stable 3.3 V logic rail across a 1-cell LiPo discharge curve.
- USB-C charge input, protected 1S LiPo, master slide switch and labeled test pads.

The board is specified as 4-layer, about 86 mm wide, with a 1.2 mm substrate. Front-facing electronics are limited to the LEDs and copper touch artwork; the controller, audio and power components live on the back.

## Why this is portfolio-grade

The repo is intended to show system architecture, PCB design, power-path reasoning, digital audio, embedded filesystem use, offline signal processing, capacitive interaction, motion sensing, low-power behavior, fabrication planning, and hardware bring-up. The audio preprocessing tool produces both a compressed local playback file and a synchronized amplitude envelope, while intentionally keeping the copyrighted recording outside Git history.

## Fabrication status

Rev B is an **engineering prototype**, not yet a released Gerber package. The placement and routing intent are implemented in KiCad, but exact fine-pitch footprints and manufacturer-specific land patterns must be audited against current datasheets before fabrication. Run KiCad ERC/DRC and complete the checklist in `docs/BRINGUP.md` before generating manufacturing outputs.
