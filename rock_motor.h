#ifndef _rock_motor_h
#define _rock_motor_h

#define FORWARD       1
#define REVERSE      -1
#define LEFTMOTOR     1
#define RIGHTMOTOR    2
#ifndef OFF
#define OFF           0
#endif
#define QTR_SPEED    63
#define FULL_SPEED  255

void motor(unsigned char motor_id, char motor_dir, unsigned char motor_duty);
void testMotors();

#endif
