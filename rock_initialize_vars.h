#ifndef _rock_initialize_vars_h
#define _rock_initialize_vars_h

//TODO Rename rock_vars.h
extern           int angleOfRobot;
extern           int angleToBehindPuck;
extern           int angleToEnemyGoal;
extern           int angleToTeamGoal;
extern unsigned  int distToBehindPuck;
extern unsigned  int distToEnemyGoal;
extern unsigned  int distToPuck;
extern unsigned  int distToTeamGoal;
//TODO enemyGoalX has a #define somewhere! (same w/ teamGoalX)
extern           int enemyGoalX;
extern unsigned char enemyScore;
extern unsigned char hasPuck;
extern           int puckX;
extern           int puckY;
extern           int robotX;
extern           int robotY;
extern           int robot2X;
extern           int robot2Y;
extern           int robot3X;
extern           int robot3Y;
extern unsigned char state;
extern unsigned  int statusFlags;
extern unsigned char teamHasPuck;
extern           int teamGoalX;
extern unsigned char teamScore;
extern unsigned  int timeElapsedMS;

extern           int debugVar; //TODO
extern unsigned char currentTeam; //TODO
#ifndef RED
#define RED  1
#define BLUE 2
#endif

#endif
