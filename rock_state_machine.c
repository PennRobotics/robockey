#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void stateMachine(char state)
{
  switch(state)
  {
  case GAMEPLAY_NOT_PLAYING:
    motor(LEFTMOTOR, OFF, 0);
    motor(RIGHTMOTOR, OFF, 0);
    status_clear_all();
    status_set(STATUS_NO_GAMEPLAY);
    break;
  case GAMEPLAY_COMM_TEST:
    // do something;
    break;
  case GAMEPLAY_PLAYING:
    // do something;
    break;
  case GAMEPLAY_TIMEOUT:
    // do something;
    break;
  case GAMEPLAY_HALFTIME:
    // do something;
    break;
  case GAMEPLAY_SCORED_GOAL:
    // do something;
    break;
  case FIND_PUCK:
    break;
  case MOVE_TO_PUCK:
    break;
  case ALIGN_PUCK:
    break;
  case CHECK_FOR_ASSIST_CHANCE:
    break;
  case CALL_FOR_ASSIST:
    break;
  case ASSIST_BY_CLEARING_PATH:
    break;
  case MOVE_TO_GOAL:
    break;
  case RIGHT_GUIDE_TO_GOAL:
    break;
  case LEFT_GUIDE_TO_GOAL:
    break;
  case CHARGE_ENEMY_GOAL:
    break;
  case SHOOT_PUCK:
    break;
  case MOVE_PATROL:
    break;
  case MOVE_TO_DEFENSE_PUCK_IN_SIGHT:
    status_set(   STATUS_PUCK_IN_SIGHT);
    status_clear( STATUS_HAVE_PUCK);
    status_set(   STATUS_DEFENSE);
    break;
  case MOVE_TO_DEFENSE_PUCK_OUT_OF_SIGHT:
    status_clear( STATUS_PUCK_IN_SIGHT);
    status_clear( STATUS_HAVE_PUCK);
    status_set(   STATUS_DEFENSE);
    break;
  case MOVE_AROUND_PERIMETER:
    break;
  case GUARD_GOAL_PUCK_IN_SIGHT:
    status_set(   STATUS_PUCK_IN_SIGHT);
    status_clear( STATUS_HAVE_PUCK);
    status_set(   STATUS_DEFENSE);
    break;
  case GUARD_GOAL_PUCK_IN_CONTACT:
    status_set(   STATUS_PUCK_IN_SIGHT);
    status_set(   STATUS_HAVE_PUCK);
    status_set(   STATUS_DEFENSE);
    break;
  case GUARD_GOAL_PUCK_OUT_OF_SIGHT:
    status_clear( STATUS_PUCK_IN_SIGHT);
    status_clear( STATUS_HAVE_PUCK);
    status_set(   STATUS_DEFENSE);
    break;
  default:
    // do something;
    m_red(ON);
    status_clear( STATUS_PUCK_IN_SIGHT);
    status_clear( STATUS_HAVE_PUCK);
    status_clear( STATUS_LOCALIZED);
    status_clear( STATUS_DEFENSE);
    status_clear( STATUS_RED_TEAM);
    status_clear( STATUS_MOTOR_ON);
    status_clear( STATUS_WAIT_FOR_TEAMMATE);
    status_clear( STATUS_ASSISTING);
    status_set(   STATUS_NO_RECENT_COMM);
    status_set(   STATUS_NO_GAMEPLAY);
    break;
  }
}

int getCurrentState()
{
  return FIND_PUCK;
  return MOVE_TO_PUCK;
  return ALIGN_PUCK;
  return CHECK_FOR_ASSIST_CHANCE;
  return MOVE_TO_GOAL;
  return RIGHT_GUIDE_TO_GOAL;
  return LEFT_GUIDE_TO_GOAL;
  return CHARGE_ENEMY_GOAL;
  return SHOOT_PUCK;
  return MOVE_PATROL;
  return MOVE_TO_DEFENSE_PUCK_IN_SIGHT;
  return MOVE_TO_DEFENSE_PUCK_OUT_OF_SIGHT;
  return MOVE_AROUND_PERIMETER;
  return GUARD_GOAL_PUCK_IN_SIGHT;
  return GUARD_GOAL_PUCK_IN_CONTACT;
  return GUARD_GOAL_PUCK_OUT_OF_SIGHT;
}
