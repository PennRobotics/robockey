//TODO Fix variables in motor(id, dir, duty)
//TODO Create port definitions e.g. MOTOR_L_EN_PORT

#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

unsigned char motorDutyL=0, motorDutyR=0, motorDirL=OFF, motorDirR=OFF;

void updateMotors(void)
{
  // motor driver enable signal LOW-PASS
  if (motorDirL != OFF) 
  {
    MOTOR_TIMER_OCR_L = (7*(int)MOTOR_TIMER_OCR_L + 1*(int)motorDutyL)/8;
  } else {
    MOTOR_TIMER_OCR_L = ((int)MOTOR_TIMER_OCR_L)*2/3 + 1;
  }

  if (motorDirR != OFF) 
  {
    MOTOR_TIMER_OCR_R = (7*(int)MOTOR_TIMER_OCR_R + 1*(int)motorDutyR)/8;
  } else {
    MOTOR_TIMER_OCR_R = ((int)MOTOR_TIMER_OCR_R)*2/3 + 1;
  }

  // motor driver direction signal
  if (motorDirL == FORWARD)
  {
      set(PORTD,5);
      clear(PORTD,6);
//    m_set(MOTOR_L_DIR_PORT);
//    m_clear(MOTOR_L_DIR_PORT);
  } else {
      clear(PORTD,5);
      set(PORTD,6);
//    m_set(MOTOR_L_DIR_PORT);
//    m_clear(MOTOR_L_DIR_PORT);
  }

  if (motorDirR == FORWARD)
  {
      set(PORTD,3);
      clear(PORTD,4);
//    m_set(MOTOR_L_DIR_PORT);
//    m_clear(MOTOR_L_DIR_PORT);
  } else {
      clear(PORTD,3);
      set(PORTD,4);
//    m_set(MOTOR_L_DIR_PORT);
//    m_clear(MOTOR_L_DIR_PORT);
  }


  // Enable status LED if either motor is in motion
  if ((MOTOR_TIMER_OCR_L > 20) || (MOTOR_TIMER_OCR_R > 20))
  {
    status_set(STATUS_MOTOR_ON);
  } else {
    status_clear(STATUS_MOTOR_ON);
  }
}

void testMotors()
{
  if (TEST_MOTORS_ON_STARTUP)
  {
    motorDirL=FORWARD; motorDutyL = 120; m_wait(800);
    motorDirL=OFF    ; motorDutyL = OFF      ; m_wait(200);
    motorDirL=REVERSE; motorDutyL = 120; m_wait(800);
    motorDirL=OFF    ; motorDutyL = OFF      ; m_wait(200);
    motorDirR=FORWARD; motorDutyR = 120; m_wait(800);
    motorDirR=OFF    ; motorDutyR = OFF      ; m_wait(200);
    motorDirR=REVERSE; motorDutyR = 120; m_wait(800);
    motorDirR=OFF    ; motorDutyR = OFF      ; m_wait(200);
  }
}
