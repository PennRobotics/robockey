// TODO Set up mRF
// TODO Set up mWii
// TODO Localization routine
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
  while(1)
  {
//    stateMachine(); //rock_state_machine.c
//    getCurrentState(); //rock_state_machine.c
//    updateStatusFlags(); //rock_status.c
//    updateLocalization(); //rock_localization.c
    qualify();
//    if (USB_DEBUGGING) {doUSB();} //rock_debug.c
  }
}

//TODO Rename this and move to rock_motor.c:
void qualify(void)
{
  debugVar = locationWhereAmI();
  doUSB();
  m_wait(1);
  calculateAngleToGoal();
  steeringAlgorithm();
}

void steeringAlgorithm(void)
{
  //TODO Use proper variable names!
  int degErrTurnCW, degErrTurnCCW;
  int degAngleErr = angleOfRobot -  angleToEnemyGoal;
  degAngleErr += (degAngleErr >  180) ? -360 :
                 (degAngleErr < -179) ?  360 : 0;
  //TODO Error when moving from 179 to -179 (and vice versa)
  degErrTurnCW  =  degAngleErr - ANGLE_ERROR_TO_START_TURN;
  degErrTurnCCW = -degAngleErr - ANGLE_ERROR_TO_START_TURN;
  degErrTurnCW  = max(0,min(MAX_ANGLE_ERROR,degErrTurnCW ));
  degErrTurnCCW = max(0,min(MAX_ANGLE_ERROR,degErrTurnCCW));
  //TODO Double check if this algorithm changes appropriate PWM:
  //Calculate amount to SUBTRACT from each motor PWM:
  motorDutyL =     SLOW_WHEEL_SPEED_PER_DEG * degErrTurnCW;
  motorDutyR =     SLOW_WHEEL_SPEED_PER_DEG * degErrTurnCCW;
  motorDutyL = max(FAST_WHEEL_SPEED_PER_DEG * degErrTurnCCW,motorDutyL);
  motorDutyR = max(FAST_WHEEL_SPEED_PER_DEG * degErrTurnCW, motorDutyR);
  motorDutyL = max(0,FULL_SPEED - motorDutyL);
  motorDutyR = max(0,FULL_SPEED - motorDutyR);
  MOTOR_TIMER_OCR_R = (7*MOTOR_TIMER_OCR_R + 1*motorDutyR)/8;
  MOTOR_TIMER_OCR_L = (7*MOTOR_TIMER_OCR_L + 1*motorDutyL)/8;
  MOTOR_TIMER_MAX   = MAX_SPEED;
}

void calculateAngleToGoal(void)
{
#define GOAL_A_X    -400 
#define GOAL_A_Y       0
#define GOAL_B_X     400
#define GOAL_B_Y       0
  if (currentTeam==RED)
  {
    // Low-pass filter, take average of old and new value
    angleToEnemyGoal = (angleToEnemyGoal + atan2d(GOAL_A_Y-robotY,GOAL_A_X-robotX)+1)/2;
    angleToTeamGoal  = (angleToTeamGoal  + atan2d(GOAL_B_Y-robotY,GOAL_B_X-robotX)+1)/2;
  } else {
    angleToEnemyGoal = (angleToEnemyGoal + atan2d(GOAL_B_Y-robotY,GOAL_B_X-robotX)+1)/2;
    angleToTeamGoal  = (angleToTeamGoal  + atan2d(GOAL_A_Y-robotY,GOAL_A_X-robotX)+1)/2;
  }
}
