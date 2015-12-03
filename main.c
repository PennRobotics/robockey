// TODO Robot X and Y algorithm is ALL MESSED UP
// TODO Set up mRF
// TODO Communication routine
// TODO Comm with game controller
// TODO Comm with other robots
// TODO Comm with local debug (USB serial monitor)
// TODO rock_motor.c
// TODO Add interrupts
// TODO Determine best way to track IR

#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void qualify(void); //TODO Move function after qualification!
void calculateAngleToGoal(void); //TODO Move function after qual
void steeringAlgorithm(void); //TODO

int main()
{
/*TODO*/   set(DDRD,5);
/*TODO*/   set(PORTD,5);
  init(); //rock_init_routine.c
  
  //TODO Which side of the rink does the robot start?
  m_wait(500);
  m_green(TOGGLE);m_wait(50);
  locationWhereAmI();
  m_green(TOGGLE);
  if (robotX < 0)
  {
    currentTeam = RED;
  } else {
    currentTeam = BLUE;
  }
  OCR4A = 15; // 94 percent duty cycle
  OCR4D = 15; // 94 percent duty cycle
  while(1)
  {
//  if (m_wii_open()==0){m_red(ON);}else{m_red(OFF);}
    qualify();
    updateStatusFlags();
    if (USB_DEBUGGING) {doUSB(); m_wait(250);} //rock_debug.c
    if (debugVar==1){status_set(STATUS_LOCALIZED);}else{status_clear(STATUS_LOCALIZED);}
  }
  while(1)
  { //TODO This is the main routine code. Re-enable after qual.
//    stateMachine(); //rock_state_machine.c
//    getCurrentState(); //rock_state_machine.c
//    updateStatusFlags(); //rock_status.c
//    updateLocalization(); //rock_localization.c
  }
}

//TODO Rename this and move to rock_motor.c:
void qualify(void)
{
  debugVar = locationWhereAmI();
  calculateAngleToGoal();
  steeringAlgorithm();
}

void steeringAlgorithm(void)
{
  int degErrTurnCW, degErrTurnCCW;

  // Calculate angle error (where robot SHOULD be pointed)
  int degAngleErr = angleOfRobot -  angleToEnemyGoal;

  // Handle angles which wrap around at -179 to 180
  degAngleErr += (degAngleErr >  180) ? -360 :
                 (degAngleErr < -179) ?  360 : 0;

  // Include a small buffer when robot is almost aligned
  degErrTurnCW  =  degAngleErr - ANGLE_ERROR_TO_START_TURN;
  degErrTurnCCW = -degAngleErr - ANGLE_ERROR_TO_START_TURN;

  // Bound CW and CCW errors between 0 and MAX_ANGLE_ERROR
  degErrTurnCW  = max(0,min(MAX_ANGLE_ERROR,degErrTurnCW ));
  degErrTurnCCW = max(0,min(MAX_ANGLE_ERROR,degErrTurnCCW));

  // Each motor's PWM duty cycle will vary based on CW/CCW error
  // When the robot needs to move CW, L wheel will be faster than R
  // Calculate amount to SUBTRACT from each motor PWM
  motorDutyL =     SLOW_WHEEL_SPEED_PER_DEG * degErrTurnCW;
  motorDutyR =     SLOW_WHEEL_SPEED_PER_DEG * degErrTurnCCW;
  motorDutyL = max(FAST_WHEEL_SPEED_PER_DEG * degErrTurnCCW,motorDutyL);
  motorDutyR = max(FAST_WHEEL_SPEED_PER_DEG * degErrTurnCW, motorDutyR);

  // Ensure duty cycle is always between 0 and FULL_SPEED
  motorDutyL = max(0,FULL_SPEED - motorDutyL);
  motorDutyR = max(0,FULL_SPEED - motorDutyR);

  // Aliases are used to assign constants/variables to timer registers.
  // Low-pass filter keeps motor from changing speed quickly
  MOTOR_TIMER_OCR_R = 255-(7*MOTOR_TIMER_OCR_R + 1*motorDutyR)/8;
  MOTOR_TIMER_OCR_L = 255-(7*MOTOR_TIMER_OCR_L + 1*motorDutyL)/8;
  MOTOR_TIMER_MAX   = MAX_SPEED;
}

void calculateAngleToGoal(void)
{
//TODO Move defines to appropriate header. (Might be duplicated)
//TODO Could also use a calibration routine to accurately set goal pos.
#define GOAL_A_X    -400 
#define GOAL_A_Y       0
#define GOAL_B_X     400
#define GOAL_B_Y       0
//TODO Make sure goal selection is correct during actual gameplay!
  if (currentTeam==RED)
  {
    // Calculate angle between robot and each goal
    // Low-pass filter, take average of old and new value
    angleToEnemyGoal = (angleToEnemyGoal + atan2d(GOAL_A_Y-robotY,GOAL_A_X-robotX)+1)/2;
    angleToTeamGoal  = (angleToTeamGoal  + atan2d(GOAL_B_Y-robotY,GOAL_B_X-robotX)+1)/2;
  } else if (currentTeam==BLUE) {
    angleToEnemyGoal = (angleToEnemyGoal + atan2d(GOAL_B_Y-robotY,GOAL_B_X-robotX)+1)/2;
    angleToTeamGoal  = (angleToTeamGoal  + atan2d(GOAL_A_Y-robotY,GOAL_A_X-robotX)+1)/2;
  } else {
    m_red(ON);
  }
}
