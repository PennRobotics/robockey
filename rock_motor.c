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
    MOTOR_TIMER_OCR_L = (7*MOTOR_TIMER_OCR_L + 1*motorDutyL)/8;
  } else {
    MOTOR_TIMER_OCR_L = (MOTOR_TIMER_OCR_L)*2/3 + 1;
  }

  if (motorDirR != OFF) 
  {
    MOTOR_TIMER_OCR_R = (7*MOTOR_TIMER_OCR_R + 1*motorDutyR)/8;
  } else {
    MOTOR_TIMER_OCR_R = (MOTOR_TIMER_OCR_R)*2/3 + 1;
  }

  // motor driver direction signal
  if (motorDirL == FORWARD)
  {
    //TODO set(MOTOR_L_DIR_PORT);
  } else {
    //TODO clear(MOTOR_L_DIR_PORT);
  }

  if (motorDirR == FORWARD)
  {
    //TODO set(MOTOR_R_DIR_PORT);
  } else {
    //TODO clear(MOTOR_R_DIR_PORT);
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
    motorDirL=FORWARD; motorDutyL = QTR_SPEED; m_wait(900);
    motorDirL=OFF    ; motorDutyL = OFF      ; m_wait(200);
    motorDirL=REVERSE; motorDutyL = QTR_SPEED; m_wait(900);
    motorDirL=OFF    ; motorDutyL = OFF      ; m_wait(200);
    motorDirR=FORWARD; motorDutyR = QTR_SPEED; m_wait(900);
    motorDirR=OFF    ; motorDutyR = OFF      ; m_wait(200);
    motorDirR=REVERSE; motorDutyR = QTR_SPEED; m_wait(900);
    motorDirR=OFF    ; motorDutyR = OFF      ; m_wait(200);
  }
}
