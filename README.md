# SonicShield: Self-Cleansing Solar IoT Node

> Waterless, contact-free dust removal for solar panels using Surface Acoustic Waves (SAW).

**Status:** Concept + prototype firmware (not yet tested on hardware). Developed for Smart India Hackathon 2026.

## Problem
Dust buildup on solar panels in arid regions such as Rajasthan reduces power output. Cleaning with water or brushes is costly, uses scarce water, and needs regular maintenance.

## Solution
SonicShield places thin-film piezoelectric transducers and transparent ITO electrodes on the panel surface. When panel output drops, the controller drives the transducer to generate surface acoustic waves that help shake dust off. No water and no moving parts.

## How it works
1. An ESP32 reads the panel voltage (through a voltage divider) every few seconds.
2. It keeps a rolling baseline of recent readings.
3. If output falls below a set fraction of the baseline, it triggers a cleaning pulse on a GPIO that drives the SAW driver stage.
4. Every reading and cleaning event is logged over serial as CSV (and can be sent to a dashboard).

## Block diagram
```
Solar panel --> Voltage divider --> ESP32 (ADC)
                                      |
                              Threshold logic
                                      |
                           GPIO --> SAW driver --> Piezo transducer + ITO electrodes
                                      |
                              Serial / WiFi --> Dashboard
```

## Components
| Component | Purpose |
|---|---|
| ESP32 dev board | Controller, ADC, WiFi |
| Voltage divider (resistors) | Scale panel voltage into ADC range |
| SAW driver stage | Drives the transducer (design in progress) |
| Piezo transducer + ITO electrodes | Generates surface acoustic waves |

See [hardware/BOM.md](hardware/BOM.md) for the full list.

## Repository structure
```
SonicShield/
├── firmware/sonicshield_node/   # ESP32 Arduino sketch
├── hardware/                    # BOM, schematics (to be added)
├── docs/                        # project overview and notes
├── dashboard/                   # telemetry dashboard (planned)
└── README.md
```

## Results
No measured results yet. Planned tests:
- Panel output before vs after dust deposition
- Panel output before vs after a cleaning pulse
- Power used per cleaning cycle

## Roadmap
- [x] Concept and problem definition
- [x] Prototype firmware (threshold logic + logging)
- [ ] Build voltage-sensing circuit on breadboard
- [ ] Design SAW driver stage and simulate in LTspice
- [ ] KiCad schematic and PCB
- [ ] Bench testing and data collection
- [ ] Telemetry dashboard

## Author
Nisha Sherlin | ECE student, Chennai
Email: sherlin070504@gmail.com | [LinkedIn](https://www.linkedin.com/in/nisha-sherlin-r-7528a137a)

## License
MIT
