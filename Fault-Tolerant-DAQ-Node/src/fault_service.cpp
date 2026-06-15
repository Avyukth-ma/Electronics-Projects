#include <avr/wdt.h>
#include <Arduino.h>
#include "system_types.h"

extern void Logger_Record_Death(uint8_t mode);

void Fault_Init(void) {
    wdt_enable(WDTO_2S);
}

void task_check_faults(void) {
    static bool death_logged = false;

    // 1. Evaluate Temperature (Warning)
    if (daq_node.temperature > 512 && daq_node.current_mode != MODE_CRITICAL) {
        daq_node.current_mode = MODE_WARNING;
    } else if (daq_node.current_mode != MODE_CRITICAL) {
        daq_node.current_mode = MODE_NORMAL;
    }

    // 2. Evaluate Voltage (Critical)
    if (daq_node.voltage < 100) {
        daq_node.current_mode = MODE_CRITICAL;
        
        // The "Last Gasp" Write - Only execute once
        if (!death_logged) {
            Logger_Record_Death(MODE_CRITICAL);
            death_logged = true;
        }
    }

    // 3. Watchdog Petting Logic
    if (daq_node.current_mode != MODE_CRITICAL) {
        wdt_reset(); 
    }
}