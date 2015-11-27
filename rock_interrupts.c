#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

ISR(ADC_vect) /*ADC conversion complete!*/
{
  clear(  SMCR, SE ); //Disable sleep mode
  // Have other routines look up the ADC register
}

//TODO Check if INT2 will interfere with other functionality!
ISR(INT2_vect)
{
  m_rf_read(bufferRF, RF_PACKET_LENGTH); 
  switch((unsigned char)bufferRF[0]) /*rock_comm.h*/ {
    case 0xA0: /*COMM TEST*/
      state = GAMEPLAY_COMM_TEST;
      break;
    case 0xA1: /*PLAY*/
      state = GAMEPLAY_PLAY_COMMAND;
      break;
    case 0xA2: /*GOAL A*/
      //TODO Ensure team selection is correct
      state = (TRUE) ? GAMEPLAY_TIMEOUT : GAMEPLAY_SCORED_GOAL;
      break;
    case 0xA3: /*GOAL B*/
      //TODO
      state = (TRUE) ? GAMEPLAY_TIMEOUT : GAMEPLAY_SCORED_GOAL;
      break;
    case 0xA4: /*PAUSE*/
      state = GAMEPLAY_TIMEOUT;
      break;
    case 0xA5: /*HALFTIME*/
      state = GAMEPLAY_HALFTIME;
      break;
    case 0xA6: /*GAME OVER*/
      state = GAMEPLAY_NOT_PLAYING;
      break;
    case 0xA7: /*ENEMY POSITIONS*/
      //TODO Viable to use enemy position?      
//      enemyA[i] = ... 
//      enemyX[i] = ...
//      enemyY[i] = ...
      break;
    default:
      break;
  }
}

ISR(TIMER0_OVF) { timeElapsedMS++; }
