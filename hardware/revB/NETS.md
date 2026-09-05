# Heartware Rev B signal plan

## MCU allocation

| Function | XIAO ESP32-S3 pin | Net |
|---|---|---|
| Capacitive heart electrode | D0 | `TOUCH` |
| RGB LED chain | D1 | `LED_DATA` |
| I2S bit clock | D2 | `I2S_BCLK` |
| I2S word select | D3 | `I2S_WS` |
| I2S PCM data | D4 | `I2S_DOUT` |
| I2C data | D5 | `I2C_SDA` |
| I2C clock | D6 | `I2C_SCL` |
| IMU interrupt | D7 | `IMU_INT` |

## Power domains

`VBUS_5V` is USB-C charging input only. `BAT+` is the protected 1S LiPo. The MCP73871 creates `SYS_RAW`; the slide switch creates the downstream switched rail `LED_PWR`. TPS63031 derives `3V3` for logic. The amplifier and RGB LEDs use the switched raw rail so their peak current does not pass through the 3.3 V regulator.

## Layout rules

Keep the ESP32 antenna region free of copper, battery, speaker magnet, and ground pour. Keep the I2S traces short and referenced to ground. Route speaker outputs as a close differential pair and keep them away from the touch electrode. Give each RGB LED a local 0.1 uF decoupler in the fabrication revision. The center touch electrode should have a ground keepout beneath and around it to preserve sensitivity.

## Important Rev B gate

The PCB contains deliberate prototype footprints so the mechanical composition, subsystem placement, and routing intent are editable immediately in KiCad. **Do not order this revision until the exact vendor footprints are replaced or audited against current manufacturer land-pattern drawings and KiCad ERC/DRC passes.**
