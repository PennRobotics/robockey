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
  m_red(OFF);
  m_wait(20);
}
