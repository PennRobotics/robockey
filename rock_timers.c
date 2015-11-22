#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

// Timer 0: Action every 1 ms
// Clock 16MHz/64 = 250kHz (4 us period)
//clear(TCCR0B,CS02);
//set(  TCCR0B,CS01);
//set(  TCCR0B,CS00);
// Timer mode count UP to OCR0A.
// OCR0A is 250, so timer overflows every 1000 us (1 ms).
//clear(TCCR0B,WGM02);
//set(  TCCR0A,WGM01);
//set(  TCCR0A,WGM00);
//OCR0A = 250;
// Output compares are NOT used in this configuration!
// One flag is of importance---the overflow flag.
// An interrupt must be placed in rock_interrupts.c:
//   ISR(TIMER0_OVF) { }
// Enable ISR with the following line:
//set(TIMSK0,TOIE0);
