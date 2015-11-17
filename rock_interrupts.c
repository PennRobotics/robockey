#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

ISR(ADC_vect) /*ADC conversion complete!*/
{
  clear(  SMCR, SE ); //Disable sleep mode
  // Have other routines look up the ADC register
}
