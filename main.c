// TODO Comm with other robots
// TODO Comm with local debug (USB serial monitor)
// TODO rock_motor.c
// TODO Determine best way to track IR
// TODO Fix localization when 1--3 stars detected
// TODO Change all references to rock_initialize_vars to rock_vars

#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

int main()
{
  //TODO=LOW Currently, pin D5 is being used as a +5V to mWii
  set(DDRD,5);
  set(PORTD,5);

  int switchDirection = 0; //TODO

  init(); //rock_init_routine.c
  
  //TODO=HIGH Enable team selection using hard switch
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


  while(1)
  {
    stateMachine(); //rock_state_machine.c
    getCurrentState(); //rock_state_machine.c
    updateStatusFlags(); //rock_status.c
    locationWhereAmI(); //rock_location.c
    calculateAngleToGoal();
    steeringAlgorithm();
    if (USB_DEBUGGING) doUSB(); //rock_debug.c
  }
}
