# Project Requirements

## Project Title

Industrial Condition Monitoring Board

## Objective

Design a PCB-based analog monitoring system that demonstrates key analog electronics concepts learned during the internship.

## Sensors

### LM35

Purpose:
Temperature monitoring

### LDR

Purpose:
Light level monitoring

### Potentiometer

Purpose:
Simulation of an industrial process variable such as pressure, flow, or level.

## Functional Requirements

### Temperature Channel

Input:
LM35

Processing:
LM35 → Amplifier → Low-Pass Filter → Comparator Network

Outputs:

* Green LED (Normal)
* Yellow LED (Warning)
* Red LED (High)

### Light Channel

Input:
LDR

Processing:
LDR Divider → Filter → Schmitt Trigger

Outputs:

* Green LED (Bright)
* Red LED (Dark)

### Process Variable Channel

Input:
Potentiometer

Processing:
Potentiometer → Comparator Network

Outputs:

* Green LED (Normal)
* Yellow LED (Warning)
* Red LED (High)

## Power Supply

* 12V DC Input
* Reverse Polarity Protection
* 7805 Voltage Regulator
* Power Indicator LED

## PCB Requirements

* Two-layer PCB
* Through-hole components where practical
* Sensor headers
* Power input terminal block
* Clearly separated functional blocks

## Design Tools

* KiCad
* GitHub

## Development Stages

1. Architecture Finalization
2. Block Diagram Development
3. Component Selection
4. Schematic Design
5. Design Review
6. PCB Layout
7. Component Placement
8. Routing
9. Grounding and Decoupling
10. Manufacturing File Generation
