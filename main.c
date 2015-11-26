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

//TODO
extern unsigned char currentTeam;

unsigned char motorDutyL, motorDutyR;

int main()
{
  init(); //rock_init_routine.c
  
  //TODO Which side of the rink does the robot start?
  m_wait(500);
  m_green(TOGGLE);m_wait(50);
  locationWhereAmI();
  m_green(TOGGLE);
#ifndef RED
#define RED  1
#define BLUE 2
#endif
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
//TODO negativeError = max(255,min(0,k*(A1-A2+schmitt)));
//TODO positiveError = max(255,min(0,k*(A2-A1+schmitt)));
//TODO Modulo at the limits!

//Try linear interpolation from +/- 28 deg to +/- 3 deg.
// For instance, at ERRORANGLE = ROBOTANGLE - GOALANGLE = 28 (robot needs to turn CW)
// ERRORANGLE=+28  LEFT=0.50  RIGHT=0.00
// ERRORANGLE=+27  LEFT=0.52  RIGHT=0.04
// ERRORANGLE=+13  LEFT=0.80  RIGHT=0.60
// ERRORANGLE=+ 3  LEFT=1.00  RIGHT=1.00
// ERRORANGLE=+ 0  LEFT=1.00  RIGHT=1.00
// ERRORANGLE=- 4  LEFT=1.00  RIGHT=0.96
// ERRORANGLE=-13  LEFT=0.60  RIGHT=0.80
// ERRORANGLE=-60  LEFT=0.00  RIGHT=0.50
  if (FALSE/*TODO*/) { /*MOTORLEFTPWM  = negativeError;*/ }
  if (FALSE/*TODO*/) { /*MOTORRIGHTPWM = positiveError;*/ }
}

void steeringAlgorithm(void)
{
  //TODO Use proper variable names!
  int degErrTurnCW, degErrTurnCCW;
  degErrTurnCW  = robotAngle -  goalAngle - ANGLE_ERROR_TO_START_TURN;
  degErrTurnCCW =  goalAngle - robotAngle - ANGLE_ERROR_TO_START_TURN;
  degErrTurnCW  = max(0,min(MAX_ANGLE_ERROR,degErrorTurnCW ));
  degErrTurnCCW = max(0,min(MAX_ANGLE_ERROR,degErrorTurnCCW));
  //TODO Double check if this algorithm changes appropriate PWM:
  //Calculate amount to SUBTRACT from each motor PWM:
  motorDutyR =     SLOW_WHEEL_SPEED_PER_DEG * degErrTurnCCW;
  motorDutyL =     SLOW_WHEEL_SPEED_PER_DEG * degErrTurnCW;
  motorDutyR = max(FAST_WHEEL_SPEED_PER_DEG * degErrTurnCW, motorDutyR);
  motorDutyL = max(FAST_WHEEL_SPEED_PER_DEG * degErrTurnCCW,motorDutyL);
  motorDutyR = max(0,FULL_SPEED - motorDutyR);
  motorDutyL = max(0,FULL_SPEED - motorDutyL);
  MOTOR_TIMER_OCR_R = motorDutyR;
  MOTOR_TIMER_OCR_L = motorDutyL;
  MOTOR_TIMER_MAX   = MAX_SPEED;
}

void calculateAngleToGoal(void)
{
#define GOAL_A_X    -400 
#define GOAL_A_Y       0
#define GOAL_B_X     400
#define GOAL_B_Y       0
  switch (currentTeam)
  {
    case RED:
      angleToEnemyGoal = atan2d(GOAL_A_Y-robotY,GOAL_A_X-robotX);
      angleToTeamGoal  = atan2d(GOAL_B_Y-robotY,GOAL_B_X-robotX);
      break;
    case BLUE:
      angleToEnemyGoal = atan2d(GOAL_B_Y-robotY,GOAL_B_X-robotX);
      angleToTeamGoal  = atan2d(GOAL_A_Y-robotY,GOAL_A_X-robotX);
      break;
    default:
      break;
  }
}
