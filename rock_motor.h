#ifndef _rock_motor_h
#define _rock_motor_h

#define FORWARD                          1
#define REVERSE                         -1
#define LEFTMOTOR                        1
#define RIGHTMOTOR                       2
#ifndef OFF
#define OFF                              0
#endif
#define QTR_SPEED                       65
#define HALF_SPEED                     130
#define FULL_SPEED                     255
#define SLOW_WHEEL_SPEED_PER_DEG         5
#define FAST_WHEEL_SPEED_PER_DEG        10  
#define ANGLE_ERROR_TO_START_TURN        2
#define MAX_ANGLE_ERROR                 25

void motor(unsigned char motor_id, char motor_dir, unsigned char motor_duty);
void testMotors();

#endif
