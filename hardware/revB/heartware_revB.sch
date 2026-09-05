EESchema Schematic File Version 4
LIBS:power
LIBS:device
LIBS:Connector_Generic
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
Sheet 1 1
Title "Heartware Rev B - Advanced Musical Heart"
Date "2026-09-05"
Rev "B"
Comp "Arya Upadhyay"
Comment1 "Portable musical keepsake: ESP32-S3, I2S audio, RGB, touch, IMU, LiPo power-path"
$EndDescr
Text Notes 700 650 0 130 ~ 26
HEARTWARE REV B
Text Notes 700 1000 0 80 ~ 16
SYSTEM ARCHITECTURE
USB-C 5V -> MCP73871 power-path charger -> LiPo + switched SYS rail
Switched SYS -> TPS63031 3.3V -> XIAO ESP32-S3 + LIS3DH
Switched SYS -> MAX98357A Class-D amplifier + SK6812MINI-E LED rail
XIAO -> I2S audio / I2C motion sensing / capacitive touch / RGB animation

The public repo intentionally excludes copyrighted audio. Local build tooling converts a user-supplied song to device assets.
Text Notes 700 2100 0 80 ~ 16
MCU / INTERACTION
U1  XIAO ESP32-S3 (8 MB flash class, PSRAM-capable board)
D0  capacitive-touch heart electrode
D1  RGB LED data chain
D2  I2S BCLK
D3  I2S LRCLK/WS
D4  I2S DATA OUT
D5  I2C SDA
D6  I2C SCL
D7  LIS3DH interrupt / pick-up wake
Text Notes 6000 2100 0 80 ~ 16
AUDIO
U2  MAX98357A I2S Class-D module
SPK output -> 4 to 8 ohm miniature speaker
Firmware decodes local MP3/WAV asset, writes PCM frames over I2S,
and computes a low-cost RMS/envelope metric for synchronized LEDs.
Text Notes 700 3600 0 80 ~ 16
POWER
J1 USB-C charge input, 5.1 kOhm CC pull-downs required on CC1 and CC2.
U3 MCP73871 load-sharing LiPo charger / system power-path.
SW1 disconnects downstream SYS so battery can charge while gift is OFF.
U4 TPS63031 fixed 3.3 V buck-boost for stable MCU/sensor rail across LiPo discharge.
J2 protected 1-cell LiPo, 500-1000 mAh recommended for prototype.
Text Notes 6000 3600 0 80 ~ 16
SENSING + LIGHT
U5 LIS3DH low-power 3-axis accelerometer on I2C; INT1 used for motion wake.
D1-D12 SK6812MINI-E addressable RGB LEDs mounted on front perimeter.
Front copper touch electrode doubles as PCB art; keep ground pour clearance around electrode.
Text Notes 700 5300 0 80 ~ 16
FABRICATION GATE
Rev B is an engineering prototype source package. Before ordering boards:
1. Cross-check every QFN/LGA/module land pattern against the manufacturer drawing.
2. Complete ERC/DRC in the installed KiCad version.
3. Add continuous ground plane on In1.Cu and routed/plane SYS on In2.Cu.
4. Recheck USB-C CC resistors, charger PROG resistor, thermal vias, LED decoupling,
   antenna keepout for XIAO/ESP32-S3, speaker current paths, and battery connector polarity.
5. Generate Gerbers only after the footprint audit is signed off in docs/BRINGUP.md.
$EndSCHEMATC
