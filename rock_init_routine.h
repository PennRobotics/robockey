#ifndef _rock_init_routine_h
#define _rock_init_routine_h

#define MAX7219_NORMAL_OPERATION   0x0C01
#define MAX7219_SCAN_DIGITS_0TO1   0x0B01
#define MAX7219_INTENSITYx         0x0A03
#define MAX7219_DECODE_NONE        0x0900
#define MAX7219_TEST_MODE_ON       0x0F01
#define MAX7219_TEST_MODE_OFF      0x0F00

#ifndef _rock_headers_h 
#include "rock_headers.h"
#endif

void init();
void initStatusLEDPins();
void initADC();
void initMWii();

#endif
