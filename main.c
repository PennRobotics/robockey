// TODO Set up mRF
// TODO Set up mWii
// TODO Localization routine
// TODO Communication routine
// TODO Comm with game controller
// TODO Comm with other robots
// TODO Comm with local debug (USB serial monitor)
// TODO rock_motor.c
// TODO Add interrupts
// TODO Determine best way to track IR

#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void qualify(void); //TODO Delete after qualification!

int main()
{
  init(); //rock_init_routine.c
  
  while(1)
  {
//    stateMachine(); //rock_state_machine.c
//    getCurrentState(); //rock_state_machine.c
//    updateStatusFlags(); //rock_status.c
//    updateLocalization(); //rock_localization.c
    qualify();
//    if (USB_DEBUGGING) {doUSB();} //rock_debug.c
  }
}

void qualify(void)
{
  debugVar = locationWhereAmI();
  doUSB();
  m_wait(1);
  calculateAngleToGoal();
//TODO negativeError = max(255,min(0,k*(A1-A2+schmitt)));
//TODO positiveError = max(255,min(0,k*(A2-A1+schmitt)));
//TODO Modulo at the limits!

//Try linear interpolation from +/- 28 deg to +/- 3 deg.
// For instance, at ERRORANGLE = ROBOTANGLE - GOALANGLE = 28 (robot needs to turn CW)
// ERRORANGLE=+28  LEFT=0.50  RIGHT=0.00
// ERRORANGLE=+27  LEFT=0.52  RIGHT=0.04
// ERRORANGLE=+13  LEFT=0.80  RIGHT=0.60
// ERRORANGLE=+ 3  LEFT=1.00  RIGHT=1.00
// ERRORANGLE=+ 0  LEFT=1.00  RIGHT=1.00
// ERRORANGLE=- 4  LEFT=1.00  RIGHT=0.96
// ERRORANGLE=-13  LEFT=0.60  RIGHT=0.80
// ERRORANGLE=-60  LEFT=0.00  RIGHT=0.50
  if (FALSE/*TODO*/) { /*MOTORLEFTPWM  = negativeError;*/ }
  if (FALSE/*TODO*/) { /*MOTORRIGHTPWM = positiveError;*/ }
}
