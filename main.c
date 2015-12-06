// TODO Comm with other robots
// TODO Comm with local debug (USB serial monitor)
// TODO rock_motor.c
// TODO Determine best way to track IR
// TODO Fix localization when 1--3 stars detected

#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void qualify(void); //TODO Move function after qualification!
void calculateAngleToGoal(void); //TODO Move function after qual
void steeringAlgorithm(void); //TODO
void randomshit(void); //TODO

int main()
{
/*TODO*/   set(DDRD,5);
/*TODO*/   set(PORTD,5);

int switchDirection = 0; //TODO

  init(); //rock_init_routine.c
  
  //TODO Get ADC value from F0
  getADC(0); int result = ADC;

  //TODO Which side of the rink does the robot start?
  m_wait(500);
  m_green(TOGGLE);m_wait(50);
  locationWhereAmI();m_wait(50);
  int rockX = robotX;
  int rockY = robotY;
  locationWhereAmI();
  robotX = (rockX + robotX)/2;
  robotY = (rockY + robotY)/2;
  m_green(TOGGLE);
  if (robotX < 512)
  {
    currentTeam = RED;
    status_set(LED_RED);
    enemyGoalX = GOAL_BLUE_X;
    teamGoalX = GOAL_RED_X;
  } else {
    currentTeam = BLUE;
    status_set(LED_BLUE);
    enemyGoalX = GOAL_RED_X;
    teamGoalX = GOAL_BLUE_X;
  }
  OCR4A = 3; // 0 percent duty cycle
  OCR4D = 3; // 0 percent duty cycle
  while(1) /*TODO delete this while loop after qual*/
  {
    updateStatusFlags();
//    if (USB_DEBUGGING) doUSB(); //rock_debug.c
    if (debugVar==1){status_set(STATUS_LOCALIZED);}else{status_clear(STATUS_LOCALIZED);}

    if (state==GAMEPLAY_COMM_TEST)
    {
      if (timeElapsedMS/100 != 0 /*TODO*/)
      {
        timeElapsedMS = 0;
        if (currentTeam==RED) { status_toggle(LED_RED); } else { status_toggle(LED_BLUE); }
      }
      status_set(STATUS_NO_GAMEPLAY);
    }
    if (state==GAMEPLAY_PLAY_COMMAND)
    {
      if (currentTeam==RED) { status_set(LED_RED);status_clear(LED_BLUE); } else { status_set(LED_BLUE);status_clear(LED_RED); }
      status_clear(STATUS_NO_GAMEPLAY);
      if (timeElapsedMS/5 != 0 /*TODO*/)
      {
        switchDirection++;
        if (switchDirection>1600)
        {
          currentTeam = RED;
        }
        if (switchDirection>3200)
        {
          switchDirection = 0;
          currentTeam = BLUE;
        }
        timeElapsedMS = 0;
        //randomshit();
         qualify();
        status_toggle(STATUS_PUCK_IN_SIGHT);
        status_toggle(STATUS_HAVE_PUCK);
        status_toggle(STATUS_DEFENSE);
        status_toggle(STATUS_TIME_ALMOST_UP);
        status_toggle(STATUS_MOTOR_ON);
        status_toggle(STATUS_WAIT_FOR_TEAMMATE);
        status_toggle(STATUS_ASSISTING);
        status_toggle(STATUS_NO_RECENT_COMM);
      }
    }
    else if ((state==GAMEPLAY_NOT_PLAYING) || (state==GAMEPLAY_TIMEOUT) || (state==GAMEPLAY_HALFTIME) || (state==GAMEPLAY_SCORED_GOAL))
    {
      status_clear(STATUS_PUCK_IN_SIGHT);
      status_clear(STATUS_HAVE_PUCK);
      status_clear(STATUS_DEFENSE);
      status_clear(STATUS_TIME_ALMOST_UP);
      status_clear(STATUS_MOTOR_ON);
      status_clear(STATUS_WAIT_FOR_TEAMMATE);
      status_clear(STATUS_ASSISTING);
      status_clear(STATUS_NO_RECENT_COMM);
      status_set(STATUS_NO_GAMEPLAY);
      OCR4A = 3;
      OCR4D = 3;
    }
  }
  while(1)
  {
    stateMachine(); //rock_state_machine.c
    getCurrentState(); //rock_state_machine.c
    updateStatusFlags(); //rock_status.c
    updateLocalization(); //rock_localization.c
  }
}


//TODO 
void randomshit(void)
{
#define  RAND_MAX  200
  OCR4A = rand()+50;
  OCR4D = rand()+50;
}

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
  int degAngleErr = angleOfRobot - angleToEnemyGoal;

  // Handle angles which wrap around at -179 to 180
  degAngleErr += (degAngleErr >  180) ? -360 :
                 (degAngleErr < -179) ?  360 : 0;

  // Include a small buffer when robot is almost aligned
  degErrTurnCCW =  degAngleErr - ANGLE_ERROR_TO_START_TURN;
  degErrTurnCW  = -degAngleErr - ANGLE_ERROR_TO_START_TURN;

  // Bound CW and CCW errors between 0 and MAX_ANGLE_ERROR
  degErrTurnCCW = max(0, min(MAX_ANGLE_ERROR, degErrTurnCCW ));
  degErrTurnCW  = max(0, min(MAX_ANGLE_ERROR, degErrTurnCW));

  // Each motor's PWM duty cycle will vary based on CW/CCW error
  // When the robot needs to move CW, L wheel will be faster than R
  motorDutyR = 3*(120 - degErrTurnCCW)/2;
  motorDutyL = 3*(120 - degErrTurnCW)/2;

  int slowDownNearGoal = max(0, 120 - distXYToR(robotX-enemyGoalX, robotY-enemyGoalY));

  // Ensure duty cycle is always between 0 and FULL_SPEED
  motorDutyL = max(0, motorDutyL-slowDownNearGoal);
  motorDutyR = max(0, motorDutyR-slowDownNearGoal);

  // Aliases are used to assign constants/variables to timer registers.
  // Low-pass filter keeps motor from changing speed quickly
  MOTOR_TIMER_OCR_R = (7*MOTOR_TIMER_OCR_R + 1*motorDutyR)/8;
  MOTOR_TIMER_OCR_L = (7*MOTOR_TIMER_OCR_L + 1*motorDutyL)/8;
  MOTOR_TIMER_MAX   = MAX_SPEED;
}

void calculateAngleToGoal(void)
{
//TODO Move defines to appropriate header. (Might be duplicated)
//TODO Could also use a calibration routine to accurately set goal pos.
//TODO Make sure goal selection is correct during actual gameplay!
  if (currentTeam==RED)
  {
    // Calculate angle between robot and each goal
    // Low-pass filter, take average of old and new value
    angleToEnemyGoal = (angleToEnemyGoal + atan2d(GOAL_BLUE_Y-robotY,GOAL_BLUE_X-robotX)+1)/2;
    angleToTeamGoal  = (angleToTeamGoal  + atan2d(GOAL_RED_Y-robotY,GOAL_RED_X-robotX)+1)/2;
  } else if (currentTeam==BLUE) {
    angleToEnemyGoal = (angleToEnemyGoal + atan2d(GOAL_RED_Y-robotY,GOAL_RED_X-robotX)+1)/2;
    angleToTeamGoal  = (angleToTeamGoal  + atan2d(GOAL_BLUE_Y-robotY,GOAL_BLUE_X-robotX)+1)/2;
  } else {
    m_red(ON);
  }
}
