#include <avr/io.h>
#include <avr/interrupt.h>
#include "system_types.h"

#define FILTER_SAMPLES 8 // Must be a power of 2 for fast division

volatile uint8_t adc_current_channel = 0; 
volatile uint8_t filter_index = 0;

// The DSP Memory Buffers
volatile uint16_t temp_buffer[FILTER_SAMPLES] = {0};
volatile uint16_t volt_buffer[FILTER_SAMPLES] = {0};
volatile uint16_t temp_sum = 0;
volatile uint16_t volt_sum = 0;

void ADC_Init(void) {
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    DIDR0 = (1 << ADC7D) | (1 << ADC6D);
}

void task_run_adc_state_machine(void) {
    if (adc_current_channel == 0) {
        adc_current_channel = 1; 
        ADMUX = (1 << REFS0) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
        ADCSRA |= (1 << ADSC);
    }
}

ISR(ADC_vect) {
    uint16_t result = ADC;

    if (adc_current_channel == 1) {
        // Temperature Moving Average Math
        temp_sum -= temp_buffer[filter_index];     // Subtract oldest value
        temp_buffer[filter_index] = result;        // Store new value
        temp_sum += result;                        // Add new value
        daq_node.temperature = temp_sum / FILTER_SAMPLES; // Save filtered average

        adc_current_channel = 2;
        ADMUX = (1 << REFS0) | (1 << MUX2) | (1 << MUX1); 
        ADCSRA |= (1 << ADSC);
    }
    else if (adc_current_channel == 2) {
        // Voltage Moving Average Math
        volt_sum -= volt_buffer[filter_index];
        volt_buffer[filter_index] = result;
        volt_sum += result;
        daq_node.voltage = volt_sum / FILTER_SAMPLES;

        // Advance the circular buffer index
        filter_index = (filter_index + 1) % FILTER_SAMPLES;
        adc_current_channel = 0;
    }
}