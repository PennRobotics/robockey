// *****************
// **  IMPORTANT  **
// *****************
//       SET THE CORRECT TEAM NUMBER IN rock_init_routine.h !!!
// ALSO, SET THE (UNIQUE) ROBOT NUMBER IN rock_init_routine.h

// TODO Comm with local debug (USB serial monitor)
// TODO Determine best way to track IR
// TODO Fix localization when 1--3 stars detected

#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void pickTeamAtBeginning(void);

int main()
{

  init(); //rock_init_routine.c

  pickTeamAtBeginning();

  updateStatusFlags(); //rock_status.c

//  while(1)
//  {
//    motorDutyL = 180;
//    motorDutyR = 175;
//    motorDirL = FORWARD;
//    motorDirR = FORWARD;
//    m_red(TOGGLE);
//  }

  while(1)
  {
    stateMachine(); //rock_state_machine.c
    getCurrentState(); //rock_state_machine.c
    updateStatusFlags(); //rock_status.c
    locationWhereAmI(); //rock_location.c
    calculateAngleToGoal(); //rock_location.c
    steeringAlgorithm(); //rock_location.c
//    if (USB_DEBUGGING) doUSB(); //rock_debug.c
  }
}

void pickTeamAtBeginning(void)
{
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
  } 
  else 
  {
    currentTeam = BLUE;
    status_set(LED_BLUE);
    enemyGoalX = GOAL_RED_X;
    teamGoalX  = GOAL_BLUE_X;
  }
}
