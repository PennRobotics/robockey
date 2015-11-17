#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

//TODO Physical robot: shield phototransistors from constellation!!!

int findPuckDistance(void)
  //TODO Discrete Lowpass on IR polling
  int pollLeftIR = getADCRaw(PIN_LEFT_IR_ANALOG);
  int pollCenterIR = getADCRaw(PIN_CENTER_IR_ANALOG);
  int pollRightIR = getADCRaw(PIN_RIGHT_IR_ANALOG);

  // Find highest ADC value
  highestIRPoll = max3(pollLeftIR, pollCenterIR, pollRightIR);

  // If no IR signal is strong enough, return -1.
  if (max3(highestIRPoll) < IR_THRESHOLD)
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
