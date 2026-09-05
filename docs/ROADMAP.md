# Heartware Roadmap

## Rev A — concept proof

- [x] Heart-shaped PCB outline
- [x] XIAO ESP32-C3 controller concept
- [x] I²S MAX98357A audio path concept
- [x] Basic LED outputs
- [x] USB-C power concept
- [x] Physical power switch concept
- [ ] Verify all exact component footprints
- [ ] Run ERC/DRC and resolve issues
- [ ] Breadboard audio path

Rev A is documentation/prototyping evidence only and should not be sent for fabrication without review.

## Rev B — advanced integrated gift

- [ ] Freeze requirements and exact board dimensions
- [ ] Select ESP32-S3 package/module strategy
- [ ] Select charger/power-path IC and LiPo connector
- [ ] Select exact Class-D amplifier and speaker
- [ ] Determine flash/storage requirement from final local audio format
- [ ] Select IMU
- [ ] Select RGB LED package and count
- [ ] Design capacitive-touch electrode
- [ ] Add battery measurement and protection strategy
- [ ] Add debug/JTAG/UART/test pads
- [ ] Complete schematic
- [ ] Perform power budget and battery-runtime estimate
- [ ] Complete placement with front-side aesthetic constraints
- [ ] Route PCB and ground/power strategy
- [ ] ERC/DRC + footprint audit
- [ ] Generate Gerbers, drill, BOM, and pick-and-place outputs
- [ ] Assemble prototype
- [ ] Board bring-up
- [ ] I²S/audio validation
- [ ] LED/audio-reactive firmware
- [ ] IMU/touch wake behavior
- [ ] Low-power validation
- [ ] Final enclosure/stand or speaker backing
- [ ] Final photos, oscilloscope captures, measurements, and README case study

## Evidence philosophy

The repository is intended to show the engineering process, including failed assumptions and corrective revisions. Design reviews, calculations, measurements, and bring-up notes are as important as the final board render.
