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
*flagMemAddr = 0;
}
