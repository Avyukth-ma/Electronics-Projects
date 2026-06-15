#ifndef SYSTEM_TYPES_H
#define SYSTEM_TYPES_H

#include <stdint.h>

// Define the possible operating states
typedef enum {
    MODE_INIT,       
    MODE_NORMAL,     
    MODE_WARNING,    
    MODE_CRITICAL    
} SystemMode_t;

// Define the exact memory layout of our system
typedef struct {
    volatile uint32_t system_tick;    
    uint16_t temperature;             
    uint16_t voltage;                 
    uint8_t  fault_code;              
    SystemMode_t current_mode;        
} TelemetryDAQ_t;

// Declare the global instance (defined in main)
extern volatile TelemetryDAQ_t daq_node;

#endif