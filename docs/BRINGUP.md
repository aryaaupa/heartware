# Rev B bring-up and release gate

Do not connect a LiPo until power-path checks 1-7 pass.

1. Audit J1 USB-C footprint, shell tabs, CC1/CC2 5.1 kOhm pull-downs and VBUS polarity.
2. Audit MCP73871 QFN-20 land pattern, exposed pad, PROG resistor, charge current and system/battery routing against the current datasheet.
3. Audit TPS63031 WSON-10 footprint, inductor value/current rating, input/output capacitor placement and thermal pad.
4. Audit LIS3DH LGA orientation, I2C address strap and INT1 routing.
5. Confirm SK6812MINI-E orientation on all 12 positions and add one 0.1 uF local bypass capacitor per LED in the fabrication revision.
6. Confirm XIAO ESP32-S3 physical orientation, antenna keepout and access to its USB connector for firmware recovery.
7. Confirm speaker connector polarity and that MAX98357A output traces are isolated from the touch electrode and IMU.
8. Run KiCad ERC and DRC with the intended fab-house rules. No unconnected critical nets, copper-to-edge errors, antenna copper, or accidental mask slivers.
9. Power from a current-limited bench supply first. Verify 3.3 V before installing U1, U2 or the LiPo.
10. Populate MCU only; flash a GPIO/serial smoke test. Then add IMU, then one RGB LED, then the full LED chain, then amplifier and speaker.
11. Measure idle current, LED peak current, playback current and charge current. Record results in `docs/VALIDATION.md`.
12. Only after electrical bring-up succeeds should Gerbers/BOM/CPL be tagged as a fabrication release.
