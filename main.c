// TODO Comm with other robots
// TODO Comm with local debug (USB serial monitor)
// TODO rock_motor.c
// TODO Determine best way to track IR
// TODO Fix localization when 1--3 stars detected

#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void qualify(void); //TODO Move function after qualification!

int main()
{
  //TODO=LOW Currently, pin D5 is being used as a +5V to mWii
  set(DDRD,5);
  set(PORTD,5);

  int switchDirection = 0; //TODO

  init(); //rock_init_routine.c
  
  //TODO Which side of the rink does the robot start?
  m_wait(50);
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
    teamGoalX  = GOAL_RED_X;
  } else {
    currentTeam = BLUE;
    status_set(LED_BLUE);
    enemyGoalX = GOAL_RED_X;
    teamGoalX  = GOAL_BLUE_X;
  }
  OCR4A = 3; // 0 percent duty cycle
  OCR4D = 3; // 0 percent duty cycle
  while(1) /*TODO delete this while loop after qual*/
  {
    if (debugVar==1){status_set(STATUS_LOCALIZED);}else{status_clear(STATUS_LOCALIZED);}

    if (state==GAMEPLAY_COMM_TEST)
    {
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
    locationWhereAmI(); //rock_location.c
    if (USB_DEBUGGING) doUSB(); //rock_debug.c
  }
}

void qualify(void)
{
  debugVar = locationWhereAmI();
  calculateAngleToGoal();
  steeringAlgorithm();
}
