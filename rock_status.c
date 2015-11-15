#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void testTeamLEDPins()
{
  m_set(RED_LED); m_wait(TEST_TEAM_LED_TIME_MS);
  m_set(BLUE_LED); m_wait(TEST_TEAM_LED_TIME_MS);
}

void testStatusLEDPins()
{
//TODO
//  set(_LED); m_wait(TEST_STATUS_LED_TIME_MS);
//  set(_LED); m_wait(TEST_STATUS_LED_TIME_MS);
//  set(_LED); m_wait(TEST_STATUS_LED_TIME_MS);
//  set(_LED); m_wait(TEST_STATUS_LED_TIME_MS);
//  set(_LED); m_wait(TEST_STATUS_LED_TIME_MS);
//  set(_LED); m_wait(TEST_STATUS_LED_TIME_MS);
//  set(_LED); m_wait(TEST_STATUS_LED_TIME_MS);
//  set(_LED); m_wait(TEST_STATUS_LED_TIME_MS);
//  set(_LED); m_wait(TEST_STATUS_LED_TIME_MS);
//  set(_LED); m_wait(TEST_STATUS_LED_TIME_MS);
}

void updateStatusFlags(unsigned int* flagMemAddr)
{
//TODO SPI communication using the MAX7219 IC
  if (*flagMemAddr & STATUS_PUCK_IN_SIGHT) { /* change status LEDs */ }
  if (*flagMemAddr & STATUS_HAVE_PUCK) { /* change status LEDs */ }
  if (*flagMemAddr & STATUS_LOCALIZED) { /* change status LEDs */ }
  if (*flagMemAddr & STATUS_DEFENSE) { /* change status LEDs */ }
  if (*flagMemAddr & STATUS_RED_TEAM) { /* change status LEDs */ }
  if (*flagMemAddr & STATUS_MOTOR_ON) { /* change status LEDs */ }
  if (*flagMemAddr & STATUS_WAIT_FOR_TEAMMATE) { /*change status LEDs*/ }
  if (*flagMemAddr & STATUS_ASSISTING) { /* change status LEDs */ }
  if (*flagMemAddr & STATUS_NO_RECENT_COMM) { /* change status LEDs */ }
  if (*flagMemAddr & STATUS_NO_GAMEPLAY) { /* change status LEDs */ }

  // MAX7219_DIN
  // MAX7219_CLK
  // MAX7219_LOAD

  // Connect anodes to SEG lines
  // Connect cathodes to DIG lines

  // Take datasheet of LED array: DC fwd curr & fwd volt
  // RSet will depend on these values (use table from MAX7219 datasheet)
  // Typical value may be 33kOhm between Vcc and pin 18 (ISet)
}
