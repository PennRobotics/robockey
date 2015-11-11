//TODO Fix variables in motor(id, dir, duty)
//TODO Create port definitions e.g. MOTOR_L_EN_PORT

#include "rock_motor.h"

void motor(unsigned char motor_id, char motor_dir, unsigned char motor_duty)
{
  if (motor_id==MOTORLEFT)
  {
//    if (motor_dir != OFF)      {set(MOTOR_L_EN_PORT); } else {clear(MOTOR_L_EN_PORT); }
//    if (motor_dir == FORWARD)  {set(MOTOR_L_DIR_PORT);} else {clear(MOTOR_L_DIR_PORT);}
//    TimerRegA = motor_duty;
//    OC4A -> C7
//    OC4B -> B6
//
  }
  else if (motor_id==MOTORRIGHT)
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
