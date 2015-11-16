#ifndef _rock_headers_h
#include "rock_headers.h"
#endif
//TODO move to header
void initStatusLEDPins();

void init()
{
m_red(ON);

// Run the system clock at 16 MHz
  m_clockdivide(0);

// Disable JTAG to make F4--F7 pins available  
  m_disableJTAG();

  if (SHORT_WAIT_BEFORE_TESTS)  {m_green(ON);m_wait(1000);m_green(OFF);}
//TODO  initMWii();
  initStatusLEDPins();
  if (TEST_LEDS_ON_STARTUP)  {testStatusLEDPins();}
//TODO  initTeamLEDPins();
  if (TEST_LEDS_ON_STARTUP)  {testTeamLEDPins();}
  if (TEST_MOTORS_ON_STARTUP)  {m_green(ON);testMotors();m_green(OFF);}
//TODO  initMRF();
//TODO  initADC();

m_red(OFF);
}

void initMWii()
{

}

void initStatusLEDPins()
{
  // Set up SPI
  clear(PRR0, PRSPI); // disable power reduction
  m_set(DDR_MOSI); // MOSI
  m_set(DDR_SCLK); // SCLK
  m_set(DDR_SS); // SS
  set(SPCR, SPR1); // 125 kHz SPI clock 
  set(SPCR, SPR0); // "    "
  set(SPCR, MSTR); // SPI module in Master mode
  // set(SPCR, SPIE); // enable SPI interrupts
  set(SPCR, SPE);  // enable SPI

  // Initialize MAX7219
  sendSPI(0x0C01); // Normal operation
  sendSPI(0x0B01); // Scan Limit digits 0--1
  sendSPI(0x0A03); // Low-Medium intensity
  sendSPI(0x0900); // No decode for digits 7--0
  sendSPI(0x0F01);m_wait(100); // Test mode ON for 100 ms
  sendSPI(0x0F00);m_wait(100); // Test mode OFF

  sendSPI(0x0100); // Turn off all LEDs
  sendSPI(0x0200); //   "    "    "
  sendSPI(0x0300); //   "    "    "
  sendSPI(0x0400); //   "    "    "
  sendSPI(0x0500); //   "    "    "
  sendSPI(0x0600); //   "    "    "
  sendSPI(0x0700); //   "    "    "
  sendSPI(0x0800); //   "    "    "
}

void initTeamLEDPins()
{

}

void initMRF()
{

}

void initADC()
{

}
