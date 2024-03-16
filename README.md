Esphome on the road
## Configuration files for smart devices in a motorhome/trailer setting

<br/>

[![Badge License: MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg)](https://github.com/git/git-scm.com/blob/main/MIT-LICENSE.txt)
 &nbsp;
[![Stand With Ukraine](https://raw.githubusercontent.com/vshymanskyy/StandWithUkraine/main/badges/StandWithUkraine.svg)](https://stand-with-ukraine.pp.ua)

</div>
<br>

## Description of architecture and list of devices:
 - Smart RV design and architecture: https://beastie.vanlerberghe.name/technical-geek-out/ 
 - Device list: https://docs.google.com/spreadsheets/d/1aTh7m6LYdMRNLjVMNrLpdHNzDydQJWMs9_gpU5-6vIQ/edit?usp=sharing

## device support:
 - Shelly: 1, 1pm, 2.5, em, +1, rgbw2, uni
 - Sonoff: nsp panel 
 - Tuya: 4ch relay
 - M5stack: atom-lite
 - Dev boards: nodemcu

## Configuration considerations:
 - Relies on separate config.py file to store secrets (WiFI and MQTT connection details)

## NSpanel thermostat / Home Assistant Dashboard:
 - The NSPanel serves a dual purpose: it is the thermostat controlling both Dometic ACs in the Airstream; it is also a Home Assistant dashboard.
 - The NSPanel has a Nextion touchscreen. The graphics/interactivity was designed with the (awful) Nextion Editor software and can be found under devices/nspanel/. The HMI files are the compiled files that can be uploaded to the Nextion screen. The tft file can be imported into the Nextion software if you want to modify it.

### Thermostat
 - The NSPanel is set up as a dual zone thermostat, controlling 2 Dometic ACs.
 - We reverse engineered the digital control signals going to the Dometics and implemented them in esphome.
 - We replaced the relay board of the NSPanel with our own board that receives 12V (stabilized) power and outputs two separate digital signals (3.3V) each going to 1 of the ACs. Hardware instructions on how to set this up forthcoming.
 - The zone temperatures are collected through MQTT from two Atom Lite devices with attached temperature sensors. 

### Home Assistant Dashboard:
 - Besides the Thermostat functionality, the NSPanel has support for 4 additional screens: TPMS sensor overview, energy consumption, tank levels, and WiFi signup QR code. 
 - All external data is captured through MQTT subscribe

## TPMS
 - I integrated PressurePro's TPMS gateway into the smart automation network. The TPMS gateway connects over serial to an Atom Lite. The Atom Lite is used to set the TPMS configuration in the gateway and to receive pressure readings from the sensors on each of the 8 tires, as well as front and back airbag pressure. The Atome Lite reads/writes from/to serial and converts the data to MQTT. The data is picked up by Home Assistant and by the NSPanel display unit.

## Home Assistant integration:
 - Integrates with Home Assistant through MQTT (you need MQTT enabled on the HA side)
 - Supports MQTT auto-discovery. No configuration needed on the HA side.

## Thanks to:
 - Sloopdog for providing the reverse engineeered Dometic protocols (https://github.com/Sloopdog/Ardunio-Code-Dometic-AC)
