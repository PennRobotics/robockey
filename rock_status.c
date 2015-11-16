#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

//TODO Move these into custom pin manipulation header w/ m_set, etc.
#define LOW(x)    ((x)     & 0xFF)
#define HIGH(x)  (((x)>>8) & 0xFF)

//TODO Move these routines into another file
void sendSPI(uint16_t data);

void testTeamLEDPins()
{
  m_set(RED_LED); m_wait(TEST_TEAM_LED_TIME_MS);
  m_set(BLUE_LED); m_wait(TEST_TEAM_LED_TIME_MS);
}

void testStatusLEDPins()
{
  sendSPI(0x0100 + 0x01); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x02); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x04); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x08); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x10); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x20); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x40); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x80); m_wait(TEST_STATUS_LED_TIME_MS);
  sendSPI(0x0100 + 0x00); 
  sendSPI(0x0200 + 0x01); m_wait(TEST_STATUS_LED_TIME_MS);
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

  // Connect anodes to SEG lines
  // Connect cathodes to DIG lines 0 and 1

  // Take datasheet of LED array: DC fwd curr & fwd volt
  // RSet will depend on these values (use table from MAX7219 datasheet)
  // Typical value may be 33kOhm between Vcc and pin 18 (ISet)
}

void sendSPI(uint16_t data)
{
#define SPI_PORT PORTB,0
  m_clear(SPI_PORT);
  SPDR = HIGH(data);
  while(!check(SPSR,SPIF));
  SPDR = LOW(data);
  while(!check(SPSR,SPIF));
  m_set(SPI_PORT);
}
