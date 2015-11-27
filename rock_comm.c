#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void tellFriendsAboutMe(void);
char bufferRF[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//TODO Transmission times in ms:
//   ID    PACKET1 PACKET2, PACKET1 ...
// ROBOT1     10     50       410
// ROBOT2    110    150       510
// ROBOT3    210    250       610
void tellFriendsAboutMe(void)
{
  //TODO Make sure m_rf_open is in initialization
  bufferRF[0] =      (ROBOT_NUMBER);
  bufferRF[1] =      (1);
  bufferRF[2] =  HIGH(robotX);
  bufferRF[3] =   LOW(robotX);
  bufferRF[4] =  HIGH(robotY);
  bufferRF[5] =   LOW(robotY);
  bufferRF[6] =  HIGH(angleOfRobot);
  bufferRF[7] =   LOW(angleOfRobot);
  bufferRF[8] = (char)hasPuck;
  bufferRF[9] = (char)state; 
  m_rf_send((RF_TX_ADDRESS_1), bufferRF, RF_PACKET_LENGTH);
  m_rf_send((RF_TX_ADDRESS_2), bufferRF, RF_PACKET_LENGTH);

  bufferRF[0] =      (ROBOT_NUMBER);
  bufferRF[1] =      (2);
  bufferRF[2] =  HIGH(puckX);
  bufferRF[3] =   LOW(puckX);
  bufferRF[4] =  HIGH(puckY);
  bufferRF[5] =   LOW(puckY);
  bufferRF[6] =  HIGH(statusFlags);
  bufferRF[7] =   LOW(statusFlags);
  bufferRF[8] =  HIGH(timeElapsedMS);
  bufferRF[9] =   LOW(timeElapsedMS); 
  m_rf_send((RF_TX_ADDRESS_1), bufferRF, RF_PACKET_LENGTH);
  m_rf_send((RF_TX_ADDRESS_2), bufferRF, RF_PACKET_LENGTH);

  //TODO If RXing local ROBOT_NUMBER, blink error lights!
}
