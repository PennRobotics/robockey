#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

//TODO Physical robot: shield phototransistors from constellation!!!
//TODO=LOW Read ATMEGA datasheet about differential measurements on ADC
//TODO=LOW Also, chapter 23 details the analog comparator.

void updateLocalization(void)
{
  //TODO Use the return value from locationWhereAmI
  //  to detect when the constellation is out-of-sight & update status.
  locationWhereAmI(); //rock_location.c
}
  
