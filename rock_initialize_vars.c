#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

unsigned  int angleOfRobot = 0; // Range 0 to 359
unsigned  int angleToBehindPuck = 0;
unsigned  int angleToEnemyGoal = 0;
unsigned  int angleToTeamGoal = 180;
unsigned  int distToBehindPuck = 285;
unsigned  int distToEnemyGoal = 780;
unsigned  int distToTeamGoal = 120;
unsigned  int distToPuck = 300;
unsigned char enemyScore = 0;
unsigned  int enemyGoalX = 0;
unsigned char hasPuck = FALSE;
unsigned  int puckX = 511;
unsigned  int puckY = 383;
unsigned  int robotX = 204;
unsigned  int robotY = 383;
unsigned  int robot2X = 204;
unsigned  int robot2Y = 383;
unsigned  int robot3X = 204;
unsigned  int robot3Y = 383;
unsigned char state = GAMEPLAY_NOT_PLAYING;
unsigned  int statusFlags = 0;
unsigned char teamHasPuck = FALSE;
unsigned  int teamGoalX = 1023;
unsigned char teamScore = 0;
unsigned  int timeElapsedMS = 0;
