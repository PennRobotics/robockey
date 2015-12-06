#ifndef _rock_m2_pins_h
#define _rock_m2_pins_h

// DIP Switches
//   1   TODO M2 VCC
//   2   UNUSED
//   3   UNUSED
//   4   UNUSED

// In-Use ports
//  B0   SPI SS
//  B1   SPI SCLK
//  B2   SPI MOSI

//  B4   Puck contact switch

//  F0   analog IR, L Front 
//  F1   analog IR, R Front 
//  F4   analog IR, L Rear 
//  F5   analog IR, R Rear 

//  B7   Servo PWM output

//  C7   OC4A (motor, L)
//  D7   OC4D (motor, R)

//TODO Figure out if complementary outputs can be disabled

// Reserved ports
//  D0   mBUS
//  D1   mBUS
//  D2   mBUS

#define ADC_PIN_FRONT_LEFT_IR        0
#define ADC_PIN_FRONT_RIGHT_IR       1
#define ADC_PIN_REAR_LEFT_IR         4
#define ADC_PIN_REAR_RIGHT_IR        5

#define m_set(x) set(x)
#define m_clear(x) clear(x)
#define m_toggle(x) toggle(x)
#define m_check(x) check(x)
#define m_output(x) set(x)
#define m_input(x) clear(x)

// Example of naming convention:
// LED_OUT, DDR_LED_OUT
// PIN_IR_FRONT, PORT_IR_FRONT, DDR_IR_FRONT
#define     SS         PORTB,0
#define DDR_SS          DDRB,0

#define DDR_SCLK        DDRB,1

#define DDR_MOSI        DDRB,2

#define  PIN_HAS_PUCK PINB,4
#define PORT_HAS_PUCK PORTB,4
#define  DDR_HAS_PUCK DDRB,4

// May be in-use due to SPI
#define UNUSED_04_PIN PINB,3
#define UNUSED_04_PORT PORTB,3
#define UNUSED_04_DDR DDRB,3

#define UNUSED_09_PIN PIND,3
#define UNUSED_09_PORT PORTD,3
#define UNUSED_09_DDR DDRD,3

#define UNUSED_10_PIN PIND,4
#define UNUSED_10_PORT PORTD,4
#define UNUSED_10_DDR DDRD,4

#define UNUSED_11_PIN PIND,5
#define UNUSED_11_PORT PORTD,5
#define UNUSED_11_DDR DDRD,5

// May be in-use due to Timer 4
#define UNUSED_12_PIN PIND,6
#define UNUSED_12_PORT PORTD,6
#define UNUSED_12_DDR DDRD,6

// Double check JTAG disabled!
#define UNUSED_14_PIN PINF,7
#define UNUSED_14_PORT PORTF,7
#define UNUSED_14_DDR DDRF,7

// Double check JTAG disabled!
#define UNUSED_15_PIN PINF,6
#define UNUSED_15_PORT PORTF,6
#define UNUSED_15_DDR DDRF,6

#define UNUSED_18_PIN PINF,1
#define UNUSED_18_PORT PORTF,1
#define UNUSED_18_DDR DDRF,1

#define UNUSED_19_PIN PINF,0
#define UNUSED_19_PORT PORTF,0
#define UNUSED_19_DDR DDRF,0

#define UNUSED_20_PIN PINE,6
#define UNUSED_20_PORT PORTE,6
#define UNUSED_20_DDR DDRE,6

// May be in-use by timer
#define UNUSED_22_PIN PINC,6
#define UNUSED_22_PORT PORTC,6
#define UNUSED_22_DDR DDRC,6

// May be in-use by timer
#define UNUSED_23_PIN PINB,6
#define UNUSED_23_PORT PORTB,6
#define UNUSED_23_DDR DDRB,6

// May be in-use by timer
#define UNUSED_24_PIN PINB,5
#define UNUSED_24_PORT PORTB,5
#define UNUSED_24_DDR DDRB,5

#endif
