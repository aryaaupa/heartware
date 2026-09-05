EESchema Schematic File Version 4
LIBS:power
LIBS:device
LIBS:Connector_Generic
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
Sheet 1 1
Title "Heartware - Musical Heart PCB"
Date "2026-09-05"
Rev "A"
Comp "Arya Upadhyay"
Comment1 "XIAO ESP32-C3 + MAX98357A + 5 LEDs + USB-C power"
$EndDescr
Text Notes 700 700 0 120 ~ 24
HEARTWARE - MUSICAL HEART PCB

Power: USB-C 5V -> SPST -> SS14 -> XIAO 5V + MAX98357 VIN
Audio: XIAO D6=LRC, D7=BCLK, D10=DIN -> MAX98357A breakout
LEDs: XIAO D1..D5 -> 220R -> warm-white LEDs -> GND
USB-C CC1/CC2 each use 5.1k pull-down to GND.

This schematic intentionally uses connector-style module symbols for the XIAO and MAX98357A breakout so the project is easy to assemble and modify.
$Comp
L Connector_Generic:Conn_01x14 U1
U 1 1 1
P 3500 3300
F 0 "U1" H 3580 3292 50  0000 L CNN
F 1 "Seeed XIAO ESP32-C3" H 3580 3201 50 0000 L CNN
	1    3500 3300
	1 0 0 -1
$EndComp
$Comp
L Connector_Generic:Conn_01x07 U2
U 1 1 2
P 6900 3300
F 0 "U2" H 6980 3342 50 0000 L CNN
F 1 "MAX98357A Breakout" H 6980 3251 50 0000 L CNN
	1    6900 3300
	1 0 0 -1
$EndComp
$Comp
L Connector_Generic:Conn_01x02 SW1
U 1 1 3
P 2100 1900
F 0 "SW1" H 2180 1892 50 0000 L CNN
F 1 "POWER" H 2180 1801 50 0000 L CNN
	1    2100 1900
	1 0 0 -1
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 4
P 1100 1900
F 0 "J1" H 1018 2217 50 0000 C CNN
F 1 "USB-C POWER (VBUS,GND,CC1,CC2)" H 1018 2126 50 0000 C CNN
	1    1100 1900
	-1 0 0 -1
$EndComp
Text Notes 3000 4700 0 80 ~ 16
XIAO pin allocation:
D1 -> LED1
D2 -> LED2
D3 -> LED3
D4 -> LED4
D5 -> LED5
D6 -> I2S LRC
D7 -> I2S BCLK
D10 -> I2S DIN
5V -> +5V_SYS
GND -> GND
Text Notes 6500 4700 0 80 ~ 16
MAX98357A breakout header order used by PCB:
1 LRC
2 BCLK
3 DIN
4 GAIN (NC)
5 SD (NC/default enabled)
6 GND
7 VIN

Speaker connects directly to the breakout SPK+ / SPK- output.
$EndSCHEMATC
