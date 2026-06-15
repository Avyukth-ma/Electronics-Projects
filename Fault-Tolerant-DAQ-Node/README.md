# Fault-Tolerant Telemetry DAQ Node

![Platform](https://img.shields.io/badge/Platform-Arduino_Leonardo-blue)
![Architecture](https://img.shields.io/badge/Architecture-AVR_8--bit-orange)
![Framework](https://img.shields.io/badge/Framework-Bare_Metal_C%2F%2B%2B-green)
![Build](https://img.shields.io/badge/Build-PlatformIO-lightgrey)

A deterministic, bare-metal data acquisition node engineered for high-stakes, fault-tolerant environments. Built on the ATmega32U4 (16MHz), this firmware strictly bypasses blocking abstractions (like `delay()` and `analogRead()`) in favor of a time-triggered cooperative scheduler, hardware-driven state machines, and rigorous failure-recovery mechanisms.

This project was developed to bridge the gap between low-level hardware constraints (VLSI/low-power electronics) and system-level firmware architecture, serving as a foundational node for autonomous systems, motorsport telemetry, and industrial logging.

---

## ⚙️ System Architecture

The firmware abandons the traditional Arduino `setup()`/`loop()` paradigm, utilizing a strictly layered C/C++ architecture to decouple hardware physics from the application logic.

### 1. Time-Triggered Cooperative Scheduler
* **The Heartbeat:** `Timer1` is configured in CTC mode (Clear Timer on Compare Match) to generate a hardware interrupt exactly every 1 millisecond.
* **Deterministic Execution:** The main loop acts as a traffic controller with **zero blocking delays**. Tasks are allotted specific execution slots (e.g., ADC Kickoff at 10ms, Fault Checking at 100ms, Telemetry at 1000ms), ensuring precise, predictable CPU behavior.
* **Atomic Protection:** 32-bit tick reads are wrapped in `<util/atomic.h>` `ATOMIC_BLOCK` macros to prevent interrupt tearing and data corruption on the 8-bit AVR architecture.

### 2. Interrupt-Driven ADC State Machine & DSP
* **Non-Blocking:** Analog sensors are not polled. The scheduler initiates a conversion via register manipulation (`ADCSRA`), and the CPU immediately resumes other tasks. Upon hardware completion, the `ADC_vect` interrupt saves the data, switches the MUX channel, and chains the next conversion entirely in the background.
* **Moving Average Filter:** Raw signals are processed through a circular buffer within the ISR context, applying an 8-sample moving average to eliminate electrical noise before the data ever reaches the application layer.

### 3. Fault Tolerance & Watchdog Recovery
* **Hardware Watchdog:** The system utilizes the ATmega32U4's independent Watchdog Timer (WDT) configured for a 2.0-second timeout.
* **Severity Management:** * `WARNING`: Out-of-bounds metrics (e.g., Over-Temp) are logged while maintaining system operation and watchdog petting.
  * `CRITICAL`: Catastrophic hardware failures (e.g., severed voltage lines) trigger a deliberate starvation of the WDT, forcing a hard system reboot.
* **EEPROM Death Certificates:** Microseconds before a Watchdog-induced reboot, the Fault Manager executes a "last gasp" write to non-volatile EEPROM memory to permanently log the exact cause of death.

### 4. Naked Boot Diagnostics
* Utilizes `.init3` compiler directives to execute code *before* the C runtime (`crt0`) initializes or clears memory. 
* Captures the MCU Status Register (`MCUSR`) to diagnose the precise hardware reset cause (Power-On, Brown-Out, External Reset, or Watchdog Bite). The system reads the EEPROM on boot and outputs a full diagnostic recovery report over Native USB CDC.

### 5. Deep Sleep Power Optimization
* At the conclusion of every execution cycle, the `SLEEP_MODE_IDLE` register is engaged. The main CPU completely shuts down to conserve power, automatically waking upon the next 1ms `Timer1` hardware interrupt.

---

## 📂 Repository Structure

Strict separation of concerns is maintained between the Application, Service, and Hardware Abstraction (HAL) layers.

```text
├── include/
│   ├── hardware_hal.h       # Hardware function prototypes and subsystem APIs
│   └── system_types.h       # Global memory structure, Enums, and State definitions
│
├── src/
│   ├── main.cpp             # Time-Triggered Scheduler and Sleep Architecture
│   ├── timer_hal.cpp        # Register-level configuration for Timer1 CTC mode
│   ├── adc_service.cpp      # Non-blocking ADC state machine and DSP filter
│   ├── uart_service.cpp     # Native USB CDC telemetry formatting wrapper
│   ├── fault_service.cpp    # Watchdog petting logic and limit evaluation
│   └── logger_service.cpp   # EEPROM persistent logging and .init3 boot diagnostics
│
└── platformio.ini           # Build environment and compiler configurations

```

---

## 🛠️ Hardware Setup & Recreation

**Required Components:**

* 1x Arduino Leonardo (ATmega32U4)
* 2x 10kΩ Potentiometers (Simulating Temperature and System Voltage inputs)
* Jumper Wires

**Wiring Configuration:**

1. Potentiometer 1 (Temperature Simulation) Wiper -> `A0`
2. Potentiometer 2 (Voltage Simulation) Wiper -> `A1`

**Execution & Testing:**

1. Clone this repository and open it in VS Code with the **PlatformIO** extension installed.
2. Compile and upload the firmware to the Leonardo.
3. Open the Serial Monitor at `115200` baud to view the 1Hz telemetry stream.
4. **Execute Hardware Kill Test:** Disconnect the `A1` jumper from 5V and short it directly to `GND`. Observe the system intentionally lock up, trigger a hardware Watchdog reset, and read the subsequent EEPROM crash diagnostic report upon reboot.

---

## 👨‍💻 Author

**Avyukth**

* B.Tech Electronics and Communication Engineering (ECE), VIT Chennai
* Driven by builder-first engineering, low-power VLSI optimization, and fault-tolerant system design.
* *Affiliations:* Havoltz (Management), Team Blitz Racing (Electronics Division), IEEE EDS (Events).

```

```