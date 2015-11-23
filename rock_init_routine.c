#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void init(void)
{
  m_red(ON); //m_general.h

  // Run the system clock at 16 MHz
  m_clockdivide(0); //m_general.h

  // Disable JTAG to make F4--F7 pins available  
  m_disableJTAG(); //m_general.h

  if (SHORT_WAIT_BEFORE_TESTS /*rock_settings.h*/)
    {m_green(ON);m_wait(1000);m_green(OFF); /*m_general.h*/}

  initMWii();

  initStatusLEDPins(); //rock_init_routine.c
  if (TEST_LEDS_ON_STARTUP /*rock_settings.h*/)
    {testStatusLEDPins(); /*rock_status.c*/}

//TODO  initTeamLEDPins();
  if (TEST_LEDS_ON_STARTUP /*rock_settings.h*/)
    {testTeamLEDPins(); /*rock_status.c*/}

  if (TEST_MOTORS_ON_STARTUP /*rock_settings.h*/)
    {m_green(ON);testMotors(); /*rock_motor.c*/m_green(OFF);}

  initMRF();

  initADC();
  getADC(PIN_CENTER_IR_ANALOG);
  //result = ADC;

  initUSB();

  status_clear_all(); //rock_status.h

  m_red(OFF); //m_general.h
}

void initStatusLEDPins(void)
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
  sendSPI(/*rock_status.c*/ MAX7219_NORMAL_OPERATION /*rock_init_routine.h*/); // Normal operation
  sendSPI(MAX7219_SCAN_DIGITS_0TO1); // Scan Limit digits 0--1
  sendSPI(MAX7219_INTENSITYx); // Low-Medium intensity
  sendSPI(MAX7219_DECODE_NONE); // No decode for digits 7--0
  sendSPI(MAX7219_TEST_MODE_ON);m_wait(100); // Test mode ON for 100 ms
  sendSPI(MAX7219_TEST_MODE_OFF);m_wait(100); // Test mode OFF

//  int i; for (i=1;i<<8;i++)
//  { sendSPI(/*rock_status.c*/ i<8); } // Turn off all LEDs on "row" i
  sendSPI(0x0100); // Turn off LEDs on each MAX7219 "row" 
  sendSPI(0x0200); //   "    "    "
  sendSPI(0x0300); //   "    "    "
  sendSPI(0x0400); //   "    "    "
  sendSPI(0x0500); //   "    "    "
  sendSPI(0x0600); //   "    "    "
  sendSPI(0x0700); //   "    "    "
  sendSPI(0x0800); //   "    "    "
}

void initTeamLEDPins(void)
{

}

void initMWii(void)
{
  if (WAIT_FOR_MWII_TO_OPEN)
  {
    while(!m_wii_open()){}
  }
  else {
    m_wii_open();
  } 
}

void initMRF(void)
{
  m_rf_open(RF_CHANNEL, RF_RX_ADDRESS, RF_PACKET_LENGTH);
}

void initADC(void)
{
  // Disable Power Reduction ADC (for ADC input MUX)
  clear(PRR0, PRADC);

  // Higher sample rate (more power consumption)
  set(  ADCSRB, ADHSM);

  // Set voltage reference to AREF
  clear(ADMUX, REFS1);
  clear(ADMUX, REFS0);

  // Set ADC clock prescaler /32 (16 MHz sys --> 500 kHz)
  set(  ADCSRA, ADPS2);
  clear(ADCSRA, ADPS1);
  set  (ADCSRA, ADPS0);

  //TODO Disable digital inputs
  // Bits n=0--7 are in DIDR0, 8--13 in DIDR2
//  set(  DIDRx, ADCnD);
//  set(  DIDRx, ADCnD);
//  set(  DIDRx, ADCnD);

  // Enable ADC interrupts
  set(  ADCSRA, ADIE);
  //sei(); TODO Check if needed! Should be redundant, refer to fcn.
  //Will use ISR(ADC_vect)
  //TODO ISR(ANALOG_COMP_vect)

//  // Enable triggering
//  set(ADCSRA, ADATE); // free-running mode
//  // Multiple inputs: Modify MUXn bits while conversion is in-progress.
//  //   Important! Wait at least 1 ADC CLOCK CYCLE before changing!

  // Select desired analog input
  clear(ADCSRB,MUX5); // F0 --- ADC0
  clear(ADMUX,MUX2);  //  "   "   "
  clear(ADMUX,MUX1);  //  "   "   "
  clear(ADMUX,MUX0);  //  "   "   "

  set(  ADCSRA, ADEN); // Enable ADC subsystem
//  set(ADCSRA, ADSC); // Begin first conversion

  // Read ADC result when ADIF flag is set (ISR or manual clear)
  //   result in 16-bit register mask ADC... or ADCL, then ADCH

  // Using ADC sleep mode: faster conversion & results only when polled
  clear(SMCR, SM2); //Sleep mode: ADC noise reduction mode
  clear(SMCR, SM1); // "
  set(  SMCR, SM0); // "

}

void initUSB(void)
{
  m_usb_init();
}
