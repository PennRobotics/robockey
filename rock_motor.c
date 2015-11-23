//TODO Fix variables in motor(id, dir, duty)
//TODO Create port definitions e.g. MOTOR_L_EN_PORT

#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void motor(unsigned char motor_id, char motor_dir, unsigned char motor_duty)
{
  if (motor_id==LEFTMOTOR)
  {
    // motor driver enable signal
    if (motor_dir != OFF) 
    {
      //TODO set(MOTOR_L_EN_PORT);
      status_set(STATUS_MOTOR_ON);
    } else {
      //TODO clear(MOTOR_L_EN_PORT);
      //TODO Check if both motors disabled before clearing status!
      //status_clear(STATUS_MOTOR_OFF);
    }

    // motor driver direction signal
    if (motor_dir == FORWARD)
    {
      //TODO set(MOTOR_L_DIR_PORT);
    } else {
      //TODO clear(MOTOR_L_DIR_PORT);
    }
//TODO    TimerRegA = motor_duty;
//TODO One compare reg for each motor. Check these to disable status.
//    OC4A -> C7
//    OC4B -> B6

  }
  else if (motor_id==RIGHTMOTOR)
  {
// copy from above
//    TimerRegB = motor_duty;
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
