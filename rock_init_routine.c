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

  initMWii(); //rock_init_routine.c

  initStatusLEDPins(); //rock_init_routine.c
  if (TEST_LEDS_ON_STARTUP /*rock_settings.h*/)
    {testStatusLEDPins(); /*rock_status.c*/}

  initTeamLEDPins();
  if (TEST_LEDS_ON_STARTUP /*rock_settings.h*/)
    {testTeamLEDPins(); /*rock_status.c*/}

  if (TEST_MOTORS_ON_STARTUP /*rock_settings.h*/)
    {m_green(ON);testMotors(); /*rock_motor.c*/m_green(OFF);}

  initMRF();

  initADC();
  getADC(PIN_CENTER_IR_ANALOG);
  //result = ADC;

  initUSB();

  initTimers();

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
  clear(SPCR, SPIE); // disable SPI interrupts (TODO needed?)
  set(SPCR, SPE);  // enable SPI

  // Initialize MAX7219 (rock_status.c, rock_init_routine.h)
  sendSPI(MAX7219_NORMAL_OPERATION); // Normal operation
  sendSPI(MAX7219_SCAN_DIGITS_0TO1); // Scan Limit digits 0--1
  sendSPI(MAX7219_INTENSITYx); // Low-Medium intensity
  sendSPI(MAX7219_DECODE_NONE); // No decode for digits 7--0
  if (TEST_LEDS_ON_STARTUP) {sendSPI(MAX7219_TEST_MODE_ON);m_wait(90);}
  sendSPI(MAX7219_TEST_MODE_OFF);m_wait(10); // Test mode OFF

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
  // Function deprecated. Team LEDs controlled by MAX7219.
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

void initTimers(void)
{
  // Timer 0 fires interrupt every 1 ms, increments timeElapsedMS
  // Timer 1 controls servo PWM, 2 MHz (40000 overflow, 3000 neutral)
  // Timer 4 controls motor PWM.

  /* **************************************************** */  
  //   TIMER 0 CONFIGURATION
  // Timer 0 clock 16MHz / 64 = 250 kHz (period 4 us)
  clear(TCCR0B,CS02);
  set(  TCCR0B,CS01);
  set(  TCCR0B,CS00);

  // Count UP to OCR0A
  clear(TCCR0B,WGM02);
  set(  TCCR0A,WGM01);
  set(  TCCR0A,WGM00);

  // Timer overflows every 250 cycles, 1000 us (1 ms)
  OCR0A = 250;

  // Output compares aren't used in this configuration
  // Enable the overflow interrupt
  set(TIMSK0,TOIE0);

  /* **************************************************** */  
  //   TIMER 1 CONFIGURATION
  // Timer 1 clock 16MHz / 8 = 2 MHz (period 500 ns)
  clear(TCCR1B,CS12);
  set(  TCCR1B,CS11);
  clear(TCCR1B,CS10);

  // Count UP to OCR3A
  set(  TCCR1B,WGM13);
  set(  TCCR1B,WGM12);
  set(  TCCR1A,WGM11);
  set(  TCCR1A,WGM10);

  // Timer overflows every 40,000 cycles, 20 ms
  OCR1A = 40000;

  // Channel C output B7
  set(  DDRB,7); //TODO Move to rock_m2_pins.h

  // Channel C PWM ON at 0, OFF at OCR1C
  set(  TCCR1A,COM1C1);
  clear(TCCR1A,COM1C0);

  OCR1C = 3000; // 1.5 ms, servo neutral position

  /* **************************************************** */  
  //   TIMER 4 CONFIGURATION
  // Timer 4 clock 16MHz / 2 = 8 MHz (period 125 ns)
  clear(TCCR4B,CS43);
  clear(TCCR4B,CS42);
  set(  TCCR4B,CS41);
  clear(TCCR4B,CS40);

  // Count UP to OCR4C
  clear(TCCR4D,WGM41);
  clear(TCCR4D,WGM40);

  // Timer overflows every 250 cycles, 31.25 us (32 kHz)
  OCR4C = 250;

  // Channels A and D output C7 (L) and D7 (R)
  set(  DDRC,7); //TODO Move to rock_m2_pins.h
  set(  DDRD,7); //TODO Move to rock_m2_pins.h

  // Channel A PWM ON at 0, OFF at OCR4C
  set(  TCCR4A,PWM4A);
  set(  TCCR4A,COM4A1);
  clear(TCCR4A,COM4A0);

  // Channel D PWM ON at 0, OFF at OCR4C
  set(  TCCR4C,PWM4D);
  set(  TCCR4C,COM4D1);
  clear(TCCR4C,COM4D0);

  OCR4A = 50; // 20 percent duty cycle
  OCR4D = 75; // 30 percent duty cycle

}
