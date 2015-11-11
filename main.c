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

#include "rock_headers.h"

// SHOOTER, RUNNER, V_LEFT, V_RIGHT, GOALIE, GOALIE_L, GOALIE_R, WEDGE
#define ROBOT WEDGE

// Adjustable Settings
#define TEST_LEDS_ON_STARTUP            true
#define TEST_MOTORS_ON_STARTUP          true
#define TEST_STATUS_LED_TIME_MS         2000
#define TEST_TEAM_LED_TIME_MS           1000
#define SHORT_WAIT_BEFORE_TESTS         true

int main()
{
  init();
  while(1)
  {
    stateMachine(state);
    getCurrentState();
    updateStatusFlags();
  }
}
