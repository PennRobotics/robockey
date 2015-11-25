#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void abort(void) {cli();while(1){m_red(ON);m_green(OFF);}}

void doUSB(void)
{
 // if(m_usb_isconnected())
 // {
    m_red(ON);
    //m_usb_tx_char(97);
//    m_usb_tx_int(debugVar);
//    m_usb_tx_char(32);
//    int i;for (i=0;i<12;i++)
//    {
//      m_usb_tx_uint(blobMemAddr[i]);
//      m_usb_tx_char(32);
//    }
//    m_usb_tx_uint(robotX);
//    m_usb_tx_char(32);
//    m_usb_tx_uint(robotY);
//    m_usb_tx_char(32);
//    m_usb_tx_int(angleOfRobot);
//    m_usb_tx_char(32);
    m_usb_tx_string("\n");
//    m_usb_tx_uint(robotY);
//    m_usb_tx_int( angleOfRobot);
 // }
}
