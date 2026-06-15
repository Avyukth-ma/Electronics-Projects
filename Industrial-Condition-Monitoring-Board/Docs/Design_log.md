# DESIGN LOG

# Day 1 – Project Definition, Architecture Design and Schematic Development

## Objective

Design an analog electronics project that demonstrates the concepts learned during the Analog Electronics internship at Yuken India Ltd. and develop the complete system architecture.

---

## Project Selected

### Industrial Condition Monitoring Board

---

## Project Description

The project was designed as a multi-channel analog monitoring system capable of monitoring multiple industrial parameters and indicating system status using LEDs.

The design intentionally focuses on analog signal processing rather than microcontroller-based processing.

---

## Functional Requirements

The board was designed to monitor:

### Temperature

Using:

* LM35 Temperature Sensor

Status Indication:

* Green LED → Normal
* Yellow LED → Warning
* Red LED → Critical

---

### Process Variable

Using:

* External Analog Input
* Potentiometer for simulation

Status Indication:

* Green LED → Normal
* Yellow LED → Warning
* Red LED → Critical

---

### Light Intensity

Using:

* LDR

Status Indication:

* Green LED → Bright
* Red LED → Dark

---

## Major Functional Blocks Identified

### Power Supply Section

Functions:

* 12V Input
* Reverse Polarity Protection
* 5V Regulation

### Temperature Monitoring Channel

Functions:

* Sensor Interface
* Amplification
* Filtering
* Threshold Detection
* LED Indication

### Process Variable Monitoring Channel

Functions:

* Analog Input Interface
* Filtering
* Threshold Detection
* LED Indication

### Light Monitoring Channel

Functions:

* Voltage Divider
* Schmitt Trigger
* LED Indication

---

## Analog Concepts Demonstrated

* Voltage Dividers
* Operational Amplifiers
* Signal Conditioning
* RC Filters
* Comparators
* Schmitt Triggers
* Sensor Interfacing
* Threshold Detection
* LED Driver Circuits
* Regulated Power Supplies

---

## Circuit Design Decisions

### Temperature Channel

An LM35 sensor was selected.

The sensor output was amplified using an LM358 non-inverting amplifier.

Selected Gain:

Gain = 5

Implemented using:

* Rf = 40kΩ
* Rin = 10kΩ

The amplified signal was filtered using an RC low-pass filter.

Selected values:

* R = 10kΩ
* C = 1µF

Thresholds selected:

* 40°C
* 60°C

Comparator outputs:

* TEMP_GT_40_N
* TEMP_GT_60_N

---

### Process Variable Channel

The process channel was designed to represent industrial pressure, flow or level monitoring.

An amplifier was evaluated but rejected because the input already spans a wide voltage range.

An RC filter was added:

* R = 10kΩ
* C = 1µF

Reference voltages generated:

* 1.67V
* 3.33V

using a resistor ladder consisting of:

* 10kΩ
* 10kΩ
* 10kΩ

Comparator outputs:

* PRES_GT_1V67_N
* PRES_GT_3V33_N

---

### Light Channel

The light monitoring channel was implemented using:

* LDR
* Voltage Divider
* Schmitt Trigger

instead of a simple comparator.

Reason:

* Noise immunity
* Hysteresis
* Demonstration of positive feedback

Reference voltage:

* 2.5V

Feedback resistor:

* 100kΩ

---

## Comparator Selection

Selected Device:

### LM339

Reason:

* Four comparators in one package
* Open collector outputs
* Industrially proven component

---

## LED Logic Development

The comparator output behavior was analyzed and threshold logic was developed.

Green and red indications were implemented directly.

For warning indication, a dedicated logic circuit was developed.

Temperature Warning Logic:

Yellow = TEMP_GT_40_N AND NOT(TEMP_GT_60_N)

Process Warning Logic:

Yellow = PRES_GT_1V67_N AND NOT(PRES_GT_3V33_N)

Implementation:

* BC547 Driver Transistor
* BC547 Inhibit Transistor

---

## Schematic Completion

All functional blocks were integrated into a single schematic consisting of:

* Power Supply
* Temperature Monitoring
* Process Monitoring
* Light Monitoring
* LED Indication Logic

---

## Day 1 Status

✅ Project Architecture Finalized

✅ Functional Specification Completed

✅ Signal Conditioning Design Completed

✅ Comparator Logic Completed

✅ Complete Schematic Developed

---

# Day 2 – Component Selection, Footprint Assignment and PCB Layout

## Objective

Convert the schematic into a manufacturable PCB design.

---

## PCB Technology Selection

A mixed-technology PCB approach was selected.

### SMD Components

* Resistors
* Capacitors
* LEDs
* LM358
* LM339

### Through-Hole Components

* Connectors
* LM7805
* BC547
* Protection Diodes

---

## Footprint Selection

### Resistors

0805

### Capacitors

0805 and 1206

### LEDs

1206

### LM358

SOIC-8

### LM339

SOIC-14

### LM7805

TO-220

### BC547

TO-92

---

## PCB Placement Strategy

The PCB was divided into functional zones.

### Top Left

Power Supply

### Upper Centre

Temperature Monitoring

### Upper Right

Light Monitoring

### Lower Centre

Process Monitoring

### Right Edge

LED Indicators

---

## Design Considerations

* Short signal paths
* Logical signal flow
* Easy debugging
* Manufacturability
* Demonstration-friendly layout

---

## Decoupling Strategy

100nF capacitors were placed close to:

* LM358
* LM339

to minimize supply noise.

---

## Routing Preparation

Trace widths selected:

### Signal Traces

0.25 mm

### 5V Power Traces

0.50 mm

### 12V Power Traces

0.80 mm

### Regulator Power Paths

0.80 mm – 1.00 mm

---

## Day 2 Status

✅ Footprints Assigned

✅ PCB Outline Created

✅ Component Placement Completed

✅ Routing Strategy Finalized

---

# Day 3 – Routing, Grounding, Verification and Documentation

## Objective

Complete PCB routing, perform verification and prepare manufacturing outputs.

---

## Routing

All signal traces were routed according to the defined routing strategy.

Special attention was given to:

* Analog signal paths
* Comparator inputs
* Sensor signal integrity
* Power distribution

---

## Grounding Strategy

A dedicated bottom-layer ground plane was implemented.

Advantages:

* Improved return current paths
* Reduced routing complexity
* Improved noise immunity
* Simplified PCB layout

---

## PCB Verification

### Electrical Rule Check (ERC)

Result:

0 Errors

0 Warnings

---

### Design Rule Check (DRC)

Result:

0 Errors

0 Warnings

---

## Final PCB Features

### Temperature Monitoring

* LM35 Interface
* Amplifier
* Low-Pass Filter
* Comparator Network
* Three-State LED Indication

### Process Monitoring

* Analog Input Interface
* RC Filter
* Comparator Network
* Three-State LED Indication

### Light Monitoring

* LDR Interface
* Voltage Divider
* Schmitt Trigger
* Bright/Dark Indication

### Power Supply

* 12V Input
* Reverse Polarity Protection
* LM7805 Regulation
* Decoupling Network

---

## Project Outcome

The Industrial Condition Monitoring Board was successfully designed and verified.

The project demonstrates:

* Sensor interfacing
* Analog signal conditioning
* Comparator-based decision making
* Schmitt trigger implementation
* Analog logic circuits
* Mixed-technology PCB design
* Complete PCB development workflow

without the use of any microcontroller.

---

## Final Status

✅ Architecture Completed

✅ Schematic Completed

✅ PCB Layout Completed

✅ Routing Completed

✅ Ground Plane Implemented

✅ ERC Passed

✅ DRC Passed

✅ Ready for Gerber Generation

✅ Ready for Manufacturing

### Project Successfully Completed
