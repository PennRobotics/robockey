#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

          int angleOfRobot = 0; // Range -179 to 180
          int angleToBehindPuck = 0;
          int angleToEnemyGoal = 0;
          int angleToTeamGoal = 180;
unsigned  int distToBehindPuck = 285;
unsigned  int distToEnemyGoal = 780;
unsigned  int distToTeamGoal = 120;
unsigned  int distToPuck = 300;
unsigned char enemyScore = 0;
          int enemyGoalX = 812;
          int enemyGoalY = 384;
unsigned char havePuck = FALSE;
          int  puckX  =    0;
          int  puckY  =    0;
          int robotX  = -307;
          int robotY  =    0;
          int robot1X = -307;
          int robot1Y =    0;
          int robot1Angle = 0;
          int robot2X = -307;
          int robot2Y =    0;
          int robot2Angle = 0;
unsigned char state = ROBOT_STARTUP;
unsigned  int statusFlags = 0;
unsigned char teamHasPuck = FALSE;
          int teamGoalX = 212;
          int teamGoalY = 384;
unsigned char teamScore = 0;
unsigned  int timeElapsedMS = 0;

// oneIfPlaying is also 1 at startup to enable comm test blinking
         char oneIfPlaying = 1;

          int debugVar = 127;
unsigned char currentTeam = 0;
