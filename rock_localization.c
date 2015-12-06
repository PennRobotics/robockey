#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

//TODO Physical robot: shield phototransistors from constellation!!!
//TODO=LOW Read ATMEGA datasheet about differential measurements on ADC
//TODO=LOW Also, chapter 23 details the analog comparator.

void updateLocalization(void)
{
  //TODO Use the return value from locationWhereAmI
  //  to detect when the constellation is out-of-sight & update status.
  locationWhereAmI(); //rock_location.c
}
  
int findPuckDistance(void)
{
  //TODO=LOW Optionally, 8-bit char pollIR = ADCH w/ set(ADMUX,ADLAR);
  //TODO Discrete Lowpass on IR polling
  getADC(ADC_PIN_FRONT_LEFT_IR);
  int pollLeftIR = ADC;
  getADC(ADC_PIN_FRONT_RIGHT_IR);
  int pollRightIR = ADC;

  // Find highest ADC value
  highestIRPoll = max(pollLeftIR, pollRightIR);

  // If no IR signal is strong enough, return -1.
  if (highestIRPoll < IR_THRESHOLD)
    return -1;
    // If findPuckDistance returns -1,
    //   check if puck is behind robot
    //   If not, scan quickly left, then right! Repeat.

  // Check if left signal is significantly higher than right.
  puckIsLeft  = pollLeftIR  > (pollRightIR + IR_SCHMITT_LEVEL);
  
  // Check if right signal is significantly higher_than_left.
  puckIsRight = pollRightIR > (pollLeftIR  + IR_SCHMITT_LEVEL);

  // Move servo if right or left signal is high.
  turnServo = (puckIsLeft)  ? TURN_LEFT  :
              (puckIsRight) ? TURN_RIGHT :
                              TURN_NOT_NEEDED;

  return PUCK_DISTANCE_GAIN * highestIRPoll;
}

void getADC(char pinADC)
{
  switch (pinADC)
  {
    // MUX registers define appropriate pin for ADC input
    case 0:
      clear(ADCSRB,MUX5);
      clear( ADMUX,MUX2);
      clear( ADMUX,MUX1);
      clear( ADMUX,MUX0);
      break;
    case 1:
      clear(ADCSRB,MUX5);
      clear( ADMUX,MUX2);
      clear( ADMUX,MUX1);
      set  ( ADMUX,MUX0);
      break;
    case 4:
      clear(ADCSRB,MUX5);
      set  ( ADMUX,MUX2);
      clear( ADMUX,MUX1);
      set  ( ADMUX,MUX0);
      break;
    case 5:
      clear(ADCSRB,MUX5);
      set  ( ADMUX,MUX2);
      clear( ADMUX,MUX1);
      set  ( ADMUX,MUX0);
      break;
    default:
      break;
  }

_delay_us(30); // Short delay required after changing ADC input
set  (ADCSRA, ADSC); // Begin ADC conversion
set  (SMCR, SE ); //Enable sleep mode

}
