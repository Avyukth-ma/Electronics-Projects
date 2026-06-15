#ifndef HARDWARE_HAL_H
#define HARDWARE_HAL_H

#include <stdint.h>

// Timer Subsystem
void Timer1_Init(void);

// ADC Subsystem
void ADC_Init(void);
void task_run_adc_state_machine(void);

// UART Subsystem
void UART_Init(void);
void task_send_uart_telemetry(void);

// Fault & Logging Subsystems
void Fault_Init(void);
void task_check_faults(void);
void Logger_Check_Previous_Death(void);
void Logger_Record_Death(uint8_t mode);

#endif