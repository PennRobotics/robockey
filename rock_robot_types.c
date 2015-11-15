#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

char robotIs(char robot_id)
{
  return robot_id == ROBOT;
}

char robotIsNot(char robot_id)
{
  return robot_id != ROBOT;
}
