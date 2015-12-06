//TODO Fix variables in motor(id, dir, duty)
//TODO Create port definitions e.g. MOTOR_L_EN_PORT

#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

unsigned char motorDutyL=0, motorDutyR=0;

void motor(unsigned char motor_id, char motor_dir, unsigned char motor_duty)
{
  if (motor_id==LEFTMOTOR)
  {
    // motor driver enable signal LOW-PASS
    if (motor_dir != OFF) 
    {
      MOTOR_TIMER_OCR_L = (7*MOTOR_TIMER_OCR_L + 1*motor_duty)/8;
    } else {
      MOTOR_TIMER_OCR_L = (MOTOR_TIMER_OCR_L)*2/3 + 1;
    }

    // motor driver direction signal
    if (motor_dir == FORWARD)
    {
      //TODO set(MOTOR_L_DIR_PORT);
    } else {
      //TODO clear(MOTOR_L_DIR_PORT);
    }

  }
  else if (motor_id==RIGHTMOTOR)
  {
    // motor driver enable signal LOW-PASS
    if (motor_dir != OFF) 
    {
      MOTOR_TIMER_OCR_R = (7*MOTOR_TIMER_OCR_R + 1*motor_duty)/8;
    } else {
      MOTOR_TIMER_OCR_R = (MOTOR_TIMER_OCR_R)*2/3 + 1;
    }

    // motor driver direction signal
    if (motor_dir == FORWARD)
    {
      //TODO set(MOTOR_L_DIR_PORT);
    } else {
      //TODO clear(MOTOR_L_DIR_PORT);
    }

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
    motor(LEFTMOTOR,  FORWARD, QTR_SPEED ); m_wait(900); // motor(motor_id, direction, speed/255);
    motor(LEFTMOTOR,  OFF,     OFF       ); m_wait(200);
    motor(LEFTMOTOR,  REVERSE, QTR_SPEED ); m_wait(900);
    motor(LEFTMOTOR,  OFF,     OFF       );
    motor(RIGHTMOTOR, FORWARD, QTR_SPEED ); m_wait(900);
    motor(RIGHTMOTOR, OFF,     OFF       ); m_wait(200);
    motor(RIGHTMOTOR, REVERSE, QTR_SPEED ); m_wait(900);
    motor(RIGHTMOTOR, OFF,     OFF       );
    motor(LEFTMOTOR,  FORWARD, FULL_SPEED); m_wait(900);
    motor(LEFTMOTOR,  OFF,     OFF       ); m_wait(200);
    motor(LEFTMOTOR,  REVERSE, FULL_SPEED); m_wait(900);
    motor(LEFTMOTOR,  OFF,     OFF       );
    motor(RIGHTMOTOR, FORWARD, FULL_SPEED); m_wait(900);
    motor(RIGHTMOTOR, OFF,     OFF       ); m_wait(200);
    motor(RIGHTMOTOR, REVERSE, FULL_SPEED); m_wait(900);
    motor(RIGHTMOTOR, OFF,     OFF       );
  }
}
