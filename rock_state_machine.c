#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

// This is used to update the display and act in the CURRENT state.
// Use getCurrentState() to determine if the CURRENT state has changed!
void stateMachine()
{
  switch(state) /*rock_initialize_vars.h*/
  {
  case ROBOT_STARTUP: /*rock_states.h*/
    motor(LEFTMOTOR, OFF, 0); /*rock_motor.h*/ 
    motor(RIGHTMOTOR, OFF, 0);
    status_clear( STATUS_PUCK_IN_SIGHT); /*rock_status.h;rock_states.h*/
    status_clear( STATUS_HAVE_PUCK);
    status_clear( STATUS_LOCALIZED);
    status_clear( STATUS_DEFENSE);
    status_clear( STATUS_TIME_ALMOST_UP);
    status_clear( STATUS_MOTOR_ON);
    status_clear( STATUS_WAIT_FOR_TEAMMATE);
    status_clear( STATUS_ASSISTING);
    status_set  ( STATUS_NO_RECENT_COMM);
    status_set  ( STATUS_NO_GAMEPLAY);
    break;

  case GAMEPLAY_NOT_PLAYING: /*rock_states.h*/
    motor(LEFTMOTOR, OFF, 0); /*rock_motor.h*/ 
    motor(RIGHTMOTOR, OFF, 0);
    status_set  ( STATUS_NO_GAMEPLAY);
    break;

  case GAMEPLAY_COMM_TEST: /*rock_states.h*/
    oneIfPlaying = 1;
    if (timeElapsedMS/100 != 0)
    {
      timeElapsedMS = 0;
      if (currentTeam==RED)
      {
        status_toggle(LED_RED);
      } else {
        status_toggle(LED_BLUE);
      }
    }
    status_set  ( STATUS_NO_GAMEPLAY);
    break;

  case GAMEPLAY_PLAY_COMMAND: /*rock_states.h*/
    oneIfPlaying = 1;
    status_clear( STATUS_NO_GAMEPLAY);
    // do something;
    break;
  case GAMEPLAY_TIMEOUT: /*rock_states.h*/
    oneIfPlaying = 0;
    // do something;
    break;

  case GAMEPLAY_HALFTIME: /*rock_states.h*/
    oneIfPlaying = 0;
    motor(LEFTMOTOR, OFF, 0); /*rock_motor.h*/ 
    motor(RIGHTMOTOR, OFF, 0);
    //status_blink( STATUS_NO_GAMEPLAY);
    if (currentTeam == RED)
    {
      currentTeam = BLUE;
      status_set(LED_RED);
      enemyGoalX = GOAL_RED_X;
      teamGoalX  = GOAL_BLUE_X;
    }
    else if (currentTeam == BLUE)
    {
      currentTeam = BLUE;
      status_set(LED_RED);
      enemyGoalX = GOAL_RED_X;
      teamGoalX  = GOAL_BLUE_X;
    }
    break;

  case GAMEPLAY_SCORED_GOAL:
    oneIfPlaying = 0;
    // do something;
    //TODO determine which team scored goal
    break;

  case FIND_PUCK:
//TODO turn
    break;

  case MOVE_TO_PUCK:
//TODO estimate puck distance
    break;

  case ALIGN_WITH_PUCK:
//TODO if puck is too close and robot is pointing toward enemy half, drive while steering puck
    break;

  case CHECK_FOR_ASSIST_CHANCE:
//TODO ready to attempt a goal; get friendly robot position and see if robot "role" allows assist
    break;

  case CALL_FOR_ASSIST:
//TODO send request, if not acknowledged, move on to next state. otherwise, wait for assist.
    break;

  case ASSIST_BY_CLEARING_PATH:
//TODO OR drive down path in front of puck (assisting runner)
    break;

  case MOVE_TO_GOAL:
    break;

  case RIGHT_GUIDE_TO_GOAL:
    break;

  case LEFT_GUIDE_TO_GOAL:
    break;

  case CHARGE_ENEMY_GOAL:
//TODO charge goal from the side (assisting shooter) 
    break;

  case SHOOT_PUCK:
//TODO fire solenoid or run to goal (stop short at 15 cm[?] if seeking 2 points)
    break;

  case MOVE_PATROL:
//TODO if puck and/or constellation has been out-of-sight for several seconds, move in large figure eights
    break;

  case MOVE_TO_DEFENSE_PUCK_IN_SIGHT:
    status_set  ( STATUS_PUCK_IN_SIGHT); /*rock_status.h*/
    status_clear( STATUS_HAVE_PUCK);
    status_set  ( STATUS_DEFENSE);
    break;

  case MOVE_TO_DEFENSE_PUCK_OUT_OF_SIGHT:
    status_clear( STATUS_PUCK_IN_SIGHT); /*rock_status.h*/
    status_clear( STATUS_HAVE_PUCK);
    status_set  ( STATUS_DEFENSE);
    break;

  case MOVE_AROUND_PERIMETER:
    break;

  case GUARD_GOAL_PUCK_IN_SIGHT:
    status_set  ( STATUS_PUCK_IN_SIGHT); /*rock_status.h*/
    status_clear( STATUS_HAVE_PUCK);
    status_set  ( STATUS_DEFENSE);
    break;

  case GUARD_GOAL_PUCK_IN_CONTACT:
    status_set  ( STATUS_PUCK_IN_SIGHT); /*rock_status.h*/
    status_set  ( STATUS_HAVE_PUCK);
    status_set  ( STATUS_DEFENSE);
    break;

  case GUARD_GOAL_PUCK_OUT_OF_SIGHT:
    status_clear( STATUS_PUCK_IN_SIGHT); /*rock_status.h*/
    status_clear( STATUS_HAVE_PUCK);
    status_set  ( STATUS_DEFENSE);
    break;

  case GET_AGGRESSIVE:
    //status_blink(STATUS_TIME_ALMOST_UP);
    break;

  case GO_BATSHIT_CRAZY:
    status_set  ( STATUS_TIME_ALMOST_UP);
    break;

  default:
    // do something;
    m_red(ON);
    status_clear( STATUS_PUCK_IN_SIGHT); /*rock_status.h;rock_states.h*/
    status_clear( STATUS_HAVE_PUCK);
    status_clear( STATUS_LOCALIZED);
    status_clear( STATUS_DEFENSE);
    status_clear( STATUS_TIME_ALMOST_UP);
    status_clear( STATUS_MOTOR_ON);
    status_clear( STATUS_WAIT_FOR_TEAMMATE);
    status_clear( STATUS_ASSISTING);
    status_set  ( STATUS_NO_RECENT_COMM);
    status_set  ( STATUS_NO_GAMEPLAY);
    break;
  }
}

// getCurrentState() DETERMINES the current state.
// Use stateMachine() to control robot actions based on state and to display the current state!
int getCurrentState(void)
{
  if (state==ROBOT_STARTUP)
  {
    state=GAMEPLAY_NOT_PLAYING;
  }
//TODO Physical switch to allow changing strategy
//  if (m_check(STRATEGY_SWITCH)) {return strategyB();}

  // If not winning and time is running low...
  //TODO Potential to use STATUS_LOW_TIME
  if ((teamScore < enemyScore + 1) && (timeElapsedMS > 52500)) /*rock_initialize_var.h*/
    {return GO_BATSHIT_CRAZY; /*rock_states.h*/}

  if ((teamScore == enemyScore) && (teamScore == 0))
    {return stateStart();}

  else if (teamScore == enemyScore)
    {return stateTied();}

  else if (teamScore > enemyScore + 1)
    {return stateWinningPlus();}

  else if (teamScore > enemyScore)
    {return stateWinning();}

  else
    {return stateLosing();}
}

//TODO All this needs work!
int stateStart(void)
{
  if (robotIs(GOALIE))
  {
    if (distToPuck == 255) {return GUARD_GOAL_PUCK_OUT_OF_SIGHT;}
    if (hasPuck == TRUE) {return GUARD_GOAL_PUCK_IN_CONTACT;}
    return GUARD_GOAL_PUCK_IN_SIGHT;
  }
  if (timeElapsedMS>30000) {return GET_AGGRESSIVE;}
  if ((teamHasPuck==TRUE) && (hasPuck==FALSE))
  {
    //TODO See if assist opportunity exists (V formation or wedge)
    return ASSIST_BY_CLEARING_PATH;
    return CHECK_FOR_ASSIST_CHANCE;
    return CALL_FOR_ASSIST;
    return RIGHT_GUIDE_TO_GOAL;
    return LEFT_GUIDE_TO_GOAL;
    return CHARGE_ENEMY_GOAL;
  }
  if (distToPuck == 255/*TODO*/) {return FIND_PUCK;}
  if (((angleToBehindPuck - angleOfRobot) < GOAL_ALIGN_DEG)&&
      ((angleOfRobot - angleToBehindPuck) < GOAL_ALIGN_DEG)&&
      (hasPuck == FALSE))
  {
    return MOVE_TO_PUCK;
  }
  if ((((angleOfRobot - angleToEnemyGoal) > GOAL_ALIGN_DEG) ||
       ((angleToEnemyGoal - angleOfRobot) > GOAL_ALIGN_DEG)) &&
      (hasPuck == TRUE))
  {
    if (((angleOfRobot - angleToTeamGoal) < GOAL_ALIGN_DEG) &&
        ((angleToTeamGoal - angleOfRobot) < GOAL_ALIGN_DEG) &&
        (distToTeamGoal < 15))
    {
      return CALL_FOR_ASSIST;
    }
    return ALIGN_WITH_PUCK;
  }
  //TODO Test hard-coded distance values that enable MOVE_TO_GOAL state
  if ((distToPuck <= 4) &&
      ((angleOfRobot - angleToEnemyGoal) <= GOAL_ALIGN_DEG) &&
      ((angleToEnemyGoal - angleOfRobot) <= GOAL_ALIGN_DEG) &&
      (distToEnemyGoal > 15))
  {
    if (robotIs(SHOOTER)) {return SHOOT_PUCK;}
    return MOVE_TO_GOAL; 
  }
  if (puckX < 0)
  {
    return MOVE_TO_DEFENSE_PUCK_IN_SIGHT;
    return MOVE_TO_DEFENSE_PUCK_OUT_OF_SIGHT;
  }
  if (teamHasPuck==FALSE) {
    return MOVE_AROUND_PERIMETER;
  }
  return MOVE_PATROL;
}

int stateTied() {return stateStart();}
int stateWinningPlus() {return stateStart();}
int stateWinning() {return stateStart();}
int stateLosing() {return stateStart();}
