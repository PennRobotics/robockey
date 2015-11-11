// Reserved ports
//  D0   mBUS
//  D1   mBUS
//  D2   mBUS

#ifndef _rock_m2_pins_h
#define _rock_m2_pins_h

void function();

// Example of naming convention:
// PIN_IR_FRONT, PORT_IR_FRONT, DDR_IR_FRONT
#define UNUSED_01_PIN PINB,0
#define UNUSED_01_PORT PORTB,0
#define UNUSED_01_DDR DDRB,0

#define UNUSED_02_PIN PINB,1
#define UNUSED_02_PORT PORTB,1
#define UNUSED_02_DDR DDRB,1

#define UNUSED_03_PIN PINB,2
#define UNUSED_03_PORT PORTB,2
#define UNUSED_03_DDR DDRB,2

#define UNUSED_04_PIN PINB,3
#define UNUSED_04_PORT PORTB,3
#define UNUSED_04_DDR DDRB,3

#define UNUSED_05_PIN PINB,7
#define UNUSED_05_PORT PORTB,7
#define UNUSED_05_DDR DDRB,7

#define UNUSED_09_PIN PIND,3
#define UNUSED_09_PORT PORTD,3
#define UNUSED_09_DDR DDRD,3

#define UNUSED_10_PIN PIND,4
#define UNUSED_10_PORT PORTD,4
#define UNUSED_10_DDR DDRD,4

#define UNUSED_11_PIN PIND,5
#define UNUSED_11_PORT PORTD,5
#define UNUSED_11_DDR DDRD,5

#define UNUSED_12_PIN PIND,6
#define UNUSED_12_PORT PORTD,6
#define UNUSED_12_DDR DDRD,6

#define UNUSED_13_PIN PIND,7
#define UNUSED_13_PORT PORTD,7
#define UNUSED_13_DDR DDRD,7

#define UNUSED_14_PIN PINF,7
#define UNUSED_14_PORT PORTF,7
#define UNUSED_14_DDR DDRF,7

#define UNUSED_15_PIN PINF,6
#define UNUSED_15_PORT PORTF,6
#define UNUSED_15_DDR DDRF,6

#define UNUSED_16_PIN PINF,5
#define UNUSED_16_PORT PORTF,5
#define UNUSED_16_DDR DDRF,5

#define UNUSED_17_PIN PINF,4
#define UNUSED_17_PORT PORTF,4
#define UNUSED_17_DDR DDRF,4

#define UNUSED_18_PIN PINF,1
#define UNUSED_18_PORT PORTF,1
#define UNUSED_18_DDR DDRF,1

#define UNUSED_19_PIN PINF,0
#define UNUSED_19_PORT PORTF,0
#define UNUSED_19_DDR DDRF,0

#define UNUSED_20_PIN PINE,6
#define UNUSED_20_PORT PORTE,6
#define UNUSED_20_DDR DDRE,6

#define UNUSED_21_PIN PINC,7
#define UNUSED_21_PORT PORTC,7
#define UNUSED_21_DDR DDRC,7

#define UNUSED_22_PIN PINC,6
#define UNUSED_22_PORT PORTC,6
#define UNUSED_22_DDR DDRC,6

#define UNUSED_23_PIN PINB,6
#define UNUSED_23_PORT PORTB,6
#define UNUSED_23_DDR DDRB,6

#define UNUSED_24_PIN PINB,5
#define UNUSED_24_PORT PORTB,5
#define UNUSED_24_DDR DDRB,5

#define UNUSED_25_PIN PINB,4
#define UNUSED_25_PORT PORTB,4
#define UNUSED_25_DDR DDRB,4

#define status_set(flag)             statusFlags |=  (flag)
#define status_clear(flag)           statusFlags &= ~(flag)
#define status_toggle(flag)          statusFlags ^=  (flag)
#define status_clear_all()           statusFlags  =  0

#define status_check(flag)    (bool)(statusFlags  &  (flag))

#endif
