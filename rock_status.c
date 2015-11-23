#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void testTeamLEDPins()
{
  //TODO Set up Team LEDs on MAX7219
  sendSPI(0x0200 + 0x04); m_wait(TEST_TEAM_LED_TIME_MS);
  sendSPI(0x0200 + 0x08); m_wait(TEST_TEAM_LED_TIME_MS);
  sendSPI(0x0200 + 0x00);
  //m_set(RED_LED); m_wait(TEST_TEAM_LED_TIME_MS);
  //m_set(BLUE_LED); m_wait(TEST_TEAM_LED_TIME_MS);
}

void testStatusLEDPins()
{
  sendSPI(0x0100 + 0x01); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x03); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x06); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x0C); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x18); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x30); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x60); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0xC0); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x80); 
  sendSPI(0x0200 + 0x01); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x00); 
  sendSPI(0x0200 + 0x03); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0200 + 0x02); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0200 + 0x00);
}

void updateStatusFlags()
{
//TODO SPI communication using the MAX7219 IC
  sendSPI(0x0100 + LOW(statusFlags));
  sendSPI(0x0200 + HIGH(statusFlags));

  // MAX7219_DIN
  // MAX7219_CLK
  // MAX7219_LOAD

  // Connect   anodes to SEG lines
  // Connect cathodes to DIG lines 0 and 1

  //  RED LED connects to same anode as LED bar array segment 3
  // BLUE LED connects to same anode as LED bar array segment 4

  // Take datasheet of LED array: DC fwd curr & fwd volt
  // RSet will depend on these values (use table from MAX7219 datasheet)
  // Typical value may be 33kOhm between Vcc and pin 18 (ISet)
}

void sendSPI(uint16_t data)
{
  m_clear(SS);
  SPDR = HIGH(data);
  while(!check(SPSR,SPIF));
  SPDR = LOW(data);
  while(!check(SPSR,SPIF));
  m_set(SS);
}
