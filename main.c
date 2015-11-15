// TODO Create Makefile
// TODO Split main into several files with headers for definitions!
// TODO Output to LED status indicators
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

int main()
{
  init();
  while(1)
  {
    stateMachine(state);
    getCurrentState();
    updateStatusFlags(&statusFlags);
  }
}

void abort(void) {cli();while(1){ }}
