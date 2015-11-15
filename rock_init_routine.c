#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void init()
{
m_red(ON);

  m_clockdivide(0);
//  m_disableJTAG();
  if (SHORT_WAIT_BEFORE_TESTS)  {m_green(ON); m_wait(1000); m_green(OFF);}
//TODO  initMWii();
//TODO  initStatusLEDPins();
  if (TEST_LEDS_ON_STARTUP)  {testStatusLEDPins();}
//TODO  initTeamLEDPins();
  if (TEST_LEDS_ON_STARTUP)  {testTeamLEDPins();}
  if (TEST_MOTORS_ON_STARTUP)  {m_green(ON); testMotors(); m_green(OFF);}
//TODO  initMRF();
//TODO  initADC();

m_red(OFF);
}

//void initMWii()  {}
//...
