#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void abort(void) {cli();while(1){m_red(ON);m_green(OFF);}}

void doUSB(void)
{
    m_usb_tx_string("\n");
 // if(m_usb_isconnected())
 // {
//    m_red(ON);
    //m_usb_tx_char(97);
//    m_usb_tx_int(debugVar);
//    m_usb_tx_char(32);
//    int i;for (i=0;i<12;i++)
//    {
//      m_usb_tx_uint(blobMemAddr[i]);
//      m_usb_tx_char(32);
//    }
    if (currentTeam == RED) {
      m_usb_tx_string("RED ");
    } else if (currentTeam == BLUE) {
      m_usb_tx_string("BLUE ");
    } else {
      m_usb_tx_string("NO TEAM! ");
    }
//    m_usb_tx_char(40);
//    m_usb_tx_int(robotX); 
//    m_usb_tx_char(44);
//    m_usb_tx_int(robotY);
//    m_usb_tx_char(41);
    m_usb_tx_char(32);
    m_usb_tx_char(60);
    m_usb_tx_int(angleOfRobot); // (X,Y) <ANGLE
    m_usb_tx_char(32);
      m_usb_tx_string("DUTY: ");
    m_usb_tx_int(motorDutyL);
    m_usb_tx_char(32);
    m_usb_tx_int(motorDutyR);
      m_usb_tx_string("ANGLE_TO_ENEMY_GOAL:");
    m_usb_tx_int(angleToEnemyGoal);
    m_usb_tx_string("\n");
//    m_usb_tx_uint(robotY);
//    m_usb_tx_int( angleOfRobot);
 // }
}
