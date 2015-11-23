#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void abort(void) {cli();while(1){m_red(ON);m_green(OFF);}}

void doUSB(void)
{
  if(m_usb_isconnected())
  {
    m_usb_tx_uint(robotX);
    m_usb_tx_uint(robotY);
    m_usb_tx_int( angleOfRobot);
  }
}
