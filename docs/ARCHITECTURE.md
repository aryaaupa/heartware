# Heartware Rev B Architecture

Rev B is the portfolio-grade redesign. The objective is to keep the interaction emotionally simple while making the electronics and firmware technically substantial.

## User interaction

1. Master switch turns the device on.
2. The board boots and performs a short LED self-test.
3. Motion or capacitive touch can arm/start playback.
4. A locally supplied song is streamed over I²S to a mono Class-D amplifier and speaker.
5. An audio-analysis task computes a lightweight amplitude envelope / beat proxy and drives synchronized RGB effects.
6. After playback, the device enters a low-power idle state until touched or moved again.

## Planned hardware blocks

```text
USB-C 5 V
   |
   +--> Li-ion charger / power-path --> LiPo cell
   |                                |
   |                                +--> battery monitor
   |
   +-------------------------------> regulated system rail

ESP32-S3
   |-- I2S --> digital Class-D audio amplifier --> speaker
   |-- SPI/QSPI --> external flash (optional, depending on final storage budget)
   |-- I2C --> 6-axis IMU
   |-- GPIO/RMT --> addressable RGB LEDs
   |-- touch GPIO --> capacitive-touch electrode
   |-- ADC/I2C --> battery telemetry
   +-- UART/JTAG/test pads --> bring-up/debug
```

## Why this architecture is portfolio-worthy

The project intentionally combines PCB design, embedded firmware, digital audio, power electronics, low-power states, sensing, real-time tasks, and hardware validation. The public repository will include design decisions and measurements rather than only final source files.

## Firmware decomposition

- `power_manager`: boot, idle, sleep, wake reasons, battery state
- `audio_engine`: file/asset reading, buffering, I²S DMA playback
- `audio_features`: RMS/envelope estimation for light synchronization
- `led_engine`: animation renderer and audio-reactive modes
- `imu`: pick-up / orientation / motion event handling
- `touch`: debounced capacitive interaction
- `app_state`: explicit system state machine
- `telemetry`: serial debug information and validation counters

## State machine

```text
OFF (hardware switch)
  -> BOOT
  -> SELF_TEST
  -> IDLE
  -> PLAYING
  -> POST_PLAY
  -> IDLE / LIGHT_SLEEP

Faults such as low battery or failed storage initialization route to a visible error indication rather than silent failure.
```

## Audio handling

The repository does not ship copyrighted audio. A local preprocessing step will accept a user-supplied WAV file, normalize it to the final mono PCM format, optionally trim/fade it, and produce the firmware asset or flash image. Generated song artifacts remain ignored by Git.

## Validation targets

Before fabrication release, Rev B should have:

- KiCad ERC and DRC clean or documented waivers
- verified USB-C and charger footprints against datasheets
- battery charge-current and thermal calculations
- speaker/amplifier power budget
- worst-case LED current budget
- sleep/idle/playback current measurements
- I²S waveform capture during bring-up
- battery undervoltage behavior test
- audio clipping/distortion sanity test
- IMU/touch false-trigger testing
- assembly and bring-up checklist
