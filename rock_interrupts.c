#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

ISR(ADC_vect) /*ADC conversion complete!*/
{
  clear(  SMCR, SE ); //Disable sleep mode
  // Result stored in the ADC register
}

// mRF INTERRUPT
// ***************
//TODO Check if INT2 will interfere with other functionality!
ISR(INT2_vect)
{
  m_red(TOGGLE);
  m_rf_read(bufferRF, RF_PACKET_LENGTH); 
  switch((unsigned char)bufferRF[0]) /*rock_comm.h*/ {
    case 0xA0: /*COMM TEST*/
      state = GAMEPLAY_COMM_TEST;
      break;

    case 0xA1: /*PLAY*/
      state = GAMEPLAY_PLAY_COMMAND;
      break;

    case 0xA2: /*GOAL A*/
      state = GAMEPLAY_SCORED_GOAL;
      //TODO Make sure team assignment is correct!
      if (currentTeam == RED)  { enemyScore++; } else { teamScore++; }
      break;

    case 0xA3: /*GOAL B*/
      state = GAMEPLAY_SCORED_GOAL;
      if (currentTeam == BLUE) { enemyScore++; } else { teamScore++; }
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

    case FRIEND_1+10:
      robot1X     =  bufferRF[1] * 4 + 2;
      robot1Y     =  bufferRF[2] * 3 + 1;
      robot1Angle =  bufferRF[3] * 2 + 1;
      puckX       = (bufferRF[4] + puckX) * 4 / 5; //LOW PASS
      puckY       = (bufferRF[5] + puckY) * 4 / 5;
      //TODO Replace havePuck with status flag for extra packet
      if ((teamHasPuck == FALSE) || (teamHasPuck == FRIEND_1))
      {
        teamHasPuck = bufferRF[6] * FRIEND_1;
      }
      //TODO Change behavior based on friendly robot state, bufferRF[7]
      //TODO Check status flags of friendly robot
      break;

    case FRIEND_2+10:
      robot2X     =  bufferRF[1] * 4 + 2;
      robot2Y     =  bufferRF[2] * 3 + 1;
      robot2Angle =  bufferRF[3] * 2 + 1;
      puckX       = (bufferRF[4] + puckX) * 4 / 5; //LOW PASS
      puckY       = (bufferRF[5] + puckY) * 4 / 5;
      //TODO Replace havePuck with status flag for extra packet
      if ((teamHasPuck == FALSE) || (teamHasPuck == FRIEND_2))
      {
        teamHasPuck = bufferRF[6] * FRIEND_2;
      }
      //TODO Change behavior based on friendly robot state, bufferRF[7]
      //TODO Check status flags of friendly robot
      break;

    default:
      break;
  }
}

// MILLISECOND COUNTER
// ********************
ISR(TIMER0_OVF_vect)
{
  timeElapsedMS += oneIfPlaying;

  // Update the motor state using MOTOR_UPDATE_PERIOD_MS
  if (timeElapsedMS / MOTOR_UPDATE_PERIOD_MS ==
      (timeElapsedMS + MOTOR_UPDATE_PERIOD_MS - 1) /
        MOTOR_UPDATE_PERIOD_MS )
  {
    updateMotors();
  }
}

//TODO Check if better to use INTx or PCINTx
// Pin Change Interrupt
ISR(PCINT0_vect)
{
  if (m_check(PIN_HAS_PUCK))
  {
    havePuck = TRUE;
    status_set  ( STATUS_HAVE_PUCK);
  }
  else
  {
    havePuck = FALSE;
    status_clear( STATUS_HAVE_PUCK);
  }
}
