#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void tellFriendsAboutMe();
char bufferRF[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//TODO Transmission times in ms:
//   ID    PACKET
// ROBOT1     50
// ROBOT2    150
// ROBOT3    250
// ROBOT1    450
// ROBOT2    550
// ROBOT3    650
//  ...

//TODO=LOW If haven't received from a specific robot in over 1 second,
//  start sending requests for info every 25 ms. Have bad robot send
//  both packets every 30 ms until requested sends acknowledgement
void tellFriendsAboutMe()
{
    bufferRF[0] =      (ROBOT_NUMBER  +10);
    bufferRF[1] =      (robotX       )/4;
    bufferRF[2] =      (robotY       )/3;
    bufferRF[3] =       angleOfRobot  /2;
    bufferRF[4] =      (puckX        )/4;
    bufferRF[5] =      (puckY        )/3;
    bufferRF[6] = (char)havePuck;
    bufferRF[7] = (char)state; 
    bufferRF[8] =  HIGH(statusFlags); 
    bufferRF[9] =   LOW(statusFlags); 

    m_red(TOGGLE);
    m_rf_send((RF_TX_ADDRESS_1), bufferRF, RF_PACKET_LENGTH);
    m_rf_send((RF_TX_ADDRESS_2), bufferRF, RF_PACKET_LENGTH);
    m_red(TOGGLE);
}
