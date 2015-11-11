#include "rock_init_routine.h"

void init()
{
m_red(ON);

  m_clockdivide(0);
//  m_disableJTAG();
  if (SHORT_WAIT_BEFORE_TESTS)  {m_green(ON); m_wait(1000); m_green(OFF);}
//TODO  initMWii();
//TODO  initStatusLEDPins();
  if (TEST_LEDS_ON_STARTUP)  {testStatusLEDPins(TEST_STATUS_LED_TIME_MS / 10);}
//TODO  initTeamLEDPins();
  if (TEST_LEDS_ON_STARTUP)  {testTeamLEDPins(TEST_TEAM_LED_TIME_MS / 2);}
  if (TEST_MOTORS_ON_STARTUP)  {m_green(ON); testMotors(); m_green(OFF);}
//TODO  initMRF();
//TODO  initADC();

m_red(OFF);
}

//void initMWii()  {}
//...
