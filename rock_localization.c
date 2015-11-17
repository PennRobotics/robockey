#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

//TODO Physical robot: shield phototransistors from constellation!!!
//TODO Read ATMEGA datasheet about differential measurements on ADC
//TODO Also, chapter 23 details the analog comparator.

int findPuckDistance(void)
{
  //TODO Discrete Lowpass on IR polling
  getADC(PIN_LEFT_IR_ANALOG);
  int pollLeftIR = ADC;
  // Optionally, 8-bit char poll(x)IR = ADCH w/ set(ADMUX,ADLAR);
  getADC(PIN_CENTER_IR_ANALOG);
  int pollCenterIR = ADC; 
  getADC(PIN_RIGHT_IR_ANALOG);
  int pollRightIR = ADC;

  // Find highest ADC value
  highestIRPoll = max3(pollLeftIR, pollCenterIR, pollRightIR);

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

void getADC(pin)
{
  switch (pin)
  {
    // Set appropriate MUX pins
    case PIN_LEFT_IR_ANALOG:
      break;
    case PIN_CENTER_IR_ANALOG:
      break;
    case PIN_RIGHT_IR_ANALOG:
      break;
    default:
  }

//TODO check if we need to disable pin-change interrupts
set(ADCSRA, ADSC); // Begin ADC conversion
set(  SMCR, SE ); //Enable sleep mode

}
