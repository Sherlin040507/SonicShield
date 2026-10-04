# SonicShield: Project Overview

## Idea
A self-cleansing solar IoT node that removes dust from solar panels using Surface Acoustic Waves (SAW), with no water and no moving parts.

## Target environment
Arid, dusty regions such as Rajasthan, where dust accumulation is high and water is scarce.

## Key technologies
- Thin-film piezoelectric transducers to generate surface acoustic waves
- Transparent ITO electrodes so light still reaches the cells
- ESP32 microcontroller for sensing, control and IoT connectivity

## Design questions to answer
1. What transducer frequency and drive voltage clear dust effectively?
2. How much energy does one cleaning cycle use compared with the energy recovered?
3. How does ITO electrode transparency affect panel output?
4. What is the best trigger: voltage drop, time schedule, or a dust sensor?

## Next steps
1. Breadboard the voltage-sensing circuit and log real panel data.
2. Simulate the driver stage in LTspice.
3. Draw the schematic and PCB in KiCad.
4. Run before/after cleaning tests and record results in the main README.

## References
- Surface acoustic wave (SAW) based dust removal on solar panels
- ESP32 technical reference manual (ADC section)
- Thin-film piezoelectric transducer datasheets (to be selected)
