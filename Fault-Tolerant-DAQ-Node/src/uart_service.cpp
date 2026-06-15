#include <Arduino.h>
#include "system_types.h"

void UART_Init(void) {
    // Initialize the Native USB CDC connection at 115200 baud
    Serial.begin(115200);
}

// Called every 1000ms by the main loop scheduler
void task_send_uart_telemetry(void) {
    // The Leonardo's "Serial" object evaluates to true if the USB cable 
    // is plugged in and a terminal program is open on the PC.
    if (Serial) {
        Serial.print("[");
        Serial.print(daq_node.system_tick);
        Serial.print("ms] ");
        
        Serial.print("TEMP_RAW: ");
        Serial.print(daq_node.temperature);
        
        Serial.print(" | VOLT_RAW: ");
        Serial.print(daq_node.voltage);
        
        Serial.print(" | SYS_MODE: ");
        switch (daq_node.current_mode) {
            case MODE_INIT:     Serial.println("INIT"); break;
            case MODE_NORMAL:   Serial.println("NORMAL"); break;
            case MODE_WARNING:  Serial.println("WARNING"); break;
            case MODE_CRITICAL: Serial.println("CRITICAL"); break;
            default:            Serial.println("UNKNOWN"); break;
        }
    }
}