#include <avr/io.h>
#include <avr/interrupt.h>
#include "system_types.h"

void Timer1_Init(void) {
    cli(); 
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0; 
    OCR1A = 249; 
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS11) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
    sei(); 
}

ISR(TIMER1_COMPA_vect) {
    daq_node.system_tick++;
}