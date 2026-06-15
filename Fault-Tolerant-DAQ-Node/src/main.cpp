#include <Arduino.h>
#include <avr/io.h>
#include <util/atomic.h>
#include <avr/sleep.h>     // <-- NEW: Sleep Subsystem
#include "system_types.h"
#include "hardware_hal.h"

volatile TelemetryDAQ_t daq_node = {0, 0, 0, 0, MODE_INIT};

uint32_t last_10ms_task = 0;
uint32_t last_100ms_task = 0;
uint32_t last_1000ms_task = 0;

void setup() {
    DDRC |= (1 << PC7); 
    
    UART_Init();
    Logger_Check_Previous_Death(); 
    
    Timer1_Init();
    ADC_Init();
    Fault_Init(); 
    
    // Configure CPU to enter "Idle" mode when sleeping.
    // Idle turns off the main CPU but leaves Timers and ADC running.
    set_sleep_mode(SLEEP_MODE_IDLE); 
    
    daq_node.current_mode = MODE_NORMAL;
}

void loop() {
    uint32_t current_tick;

    // Safely copy the 32-bit tick without interrupt tearing
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        current_tick = daq_node.system_tick;
    }

    if (current_tick - last_10ms_task >= 10) {
        last_10ms_task = current_tick;
        task_run_adc_state_machine(); 
    }

    if (current_tick - last_100ms_task >= 100) {
        last_100ms_task = current_tick;
        task_check_faults(); 
    }

    if (current_tick - last_1000ms_task >= 1000) {
        last_1000ms_task = current_tick;
        task_send_uart_telemetry();
        
        if (daq_node.current_mode == MODE_NORMAL) {
            PORTC ^= (1 << PC7); 
        } else if (daq_node.current_mode == MODE_WARNING) {
            PORTC |= (1 << PC7); 
        } else {
            PORTC &= ~(1 << PC7); 
        }
    }

    // --- POWER OPTIMIZATION ---
    // The CPU has checked all time slots. It has nothing left to do.
    // Go to sleep to save power. The Timer1 1ms interrupt will wake it up automatically.
    sleep_mode(); 
}