#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

// Constellation points:
// A   ( 11.655,   8.741)
// B   (  0.000,  14.500)
// C   (-10.563,   2.483)
// D   (  0.000, -14.500)
// These coordinates are (X, Y) Cartesian pairs,
//  where each point is where the IR "stars" are focused on the rink.
//  Refer to each point looking down from above the constellation.
//
// Red goal is on the far left i.e. (-200, 0)
// Blue goal is on the far right i.e. (200, 0)

char locationWhereAmI(void)
{
//  int totalGain;
//  char   xOld = robotX;
//  char   yOld = robotY;
//  char dirOld = angleOfRobot;

  int i; char zeroIfFourBlobs = 0;

  // Use m_wii_read() to update data at blobMemAddr
  m_wii_read(blobMemAddr);

  for (i=0;i<4;i++)
  {
    //TODO=LOW Remember the previous values of blobX and blobY
  //  blobXOld[i] = blobX[i];
  //  blobYOld[i] = blobY[i];
    
    // Copy from blobMemAddr into blobX and blobY (blob size ignored)
    blobX[i] = blobMemAddr[i*3 + 0];
    blobY[i] = blobMemAddr[i*3 + 1];

    // Check if blobs leave the mWii field-of-view
    if ((blobX[i]==1023) && (blobY[i]==1023))
    {
      zeroIfFourBlobs++;
    }
    else /*TODO Check if new data is near old data*/
    {
      //TODO This needs to compare ORDERED data, not raw data!!
      //TODO Fix the order and compare check and create a threshold var.
//TODO thr=25;      
//      if (((blobXOld[i]-blobX[i]) < thr) ||
//          ((blobX[i]-blobXOld[i]) > thr) ||
//          ((blobYOld[i]-blobY[i]) < thr) ||
//          ((blobY[i]-blobYOld[i]) > thr))
//      {
//        //TODO Check return value!
//        return 0; /*Current data is too far from previous data*/
//      }
    }
  }
    //m_usb_tx_string("\n");

  if (zeroIfFourBlobs==0)
  {
    s12 = SQUARE(X(1)-X(0)) + SQUARE(Y(1)-Y(0));
    s13 = SQUARE(X(2)-X(0)) + SQUARE(Y(2)-Y(0));
    s14 = SQUARE(X(3)-X(0)) + SQUARE(Y(3)-Y(0));
    s23 = SQUARE(X(2)-X(1)) + SQUARE(Y(2)-Y(1));
    s24 = SQUARE(X(3)-X(1)) + SQUARE(Y(3)-Y(1));
    s34 = SQUARE(X(3)-X(2)) + SQUARE(Y(3)-Y(2));

    // Find the maximum "s" (blob distance squared)
    long sMax;
    sMax =  s12 > s13 ?  s12 : s13;
    sMax = sMax > s14 ? sMax : s14;
    sMax = sMax > s23 ? sMax : s23;
    sMax = sMax > s24 ? sMax : s24;
    sMax = sMax > s34 ? sMax : s34;
    
    // Find indices of points B and D (not ordered)
    int indexBD1 = (s12 == sMax) ? 0 :
                    (s13 == sMax) ? 0 :
                    (s14 == sMax) ? 0 :
                    (s23 == sMax) ? 1 :
                    (s24 == sMax) ? 1 : 2;

    int indexBD2 = (s12 == sMax) ? 1 :
                    (s13 == sMax) ? 2 :
                    (s14 == sMax) ? 3 :
                    (s23 == sMax) ? 2 : 3;
    
    // Find indices of points A and C (not ordered)
    int indexAC1 = (indexBD1 != 0) ? 0 :
                    (indexBD2 != 1) ? 1 : 2;

    int indexAC2 = 6 - (indexBD1 + indexBD2 + indexAC1);

    // The sum of distances from B to A and B to C should be
    //  less than the sum of distances from D to A and D to C.
    
    //  Determine which index is B and which is D
    int indexB =
      (SQUARE(X(indexBD1) - X(indexAC1)) + 
       SQUARE(Y(indexBD1) - Y(indexAC1)) +
       SQUARE(X(indexBD1) - X(indexAC2)) +
       SQUARE(Y(indexBD1) - Y(indexAC2))) <
      (SQUARE(X(indexBD2) - X(indexAC1)) + 
       SQUARE(Y(indexBD2) - Y(indexAC1)) +
       SQUARE(X(indexBD2) - X(indexAC2)) +
       SQUARE(Y(indexBD2) - Y(indexAC2))) ? indexBD1 : indexBD2;

    int indexD = 6 - (indexAC1 + indexAC2 + indexB);

    // Compare coords of point B and D to previous coords
    int pointBXOld = pointBX;
    int pointBYOld = pointBY;
    int pointDXOld = pointDX;
    int pointDYOld = pointDY;

    // Assign point B (x,y) and D (x,y) using indices
    pointBX = X(indexB);
    pointBY = Y(indexB);
    pointDX = X(indexD);
    pointDY = Y(indexD);

    int pointCenterX, pointCenterY;

    //TODO Make sure code works, then move to header
#define STAR_JUMP_THRESHOLD 25

    if ((abs(pointBXOld - pointBX) > STAR_JUMP_THRESHOLD) || 
        (abs(pointBYOld - pointBY) > STAR_JUMP_THRESHOLD) || 
        (abs(pointDXOld - pointDX) > STAR_JUMP_THRESHOLD) || 
        (abs(pointDYOld - pointDY) > STAR_JUMP_THRESHOLD)   ) 
    {
    pointCenterX = (pointBX + pointBXOld + pointDX + pointDXOld) / 4;
    pointCenterY = (pointBY + pointBYOld + pointDY + pointDYOld) / 4;
    }
    // Find the constellation center exactly between points B and D
    pointCenterX = (pointBX + pointDX) / 2;
    pointCenterY = (pointBY + pointDY) / 2;

//    distX = RINK_CENTER_X - pointCenterX;
//    distY = RINK_CENTER_Y - pointCenterY;
//****************************    
//    long distX = pointCenterX - RINK_CENTER_X;
//    long distY = RINK_CENTER_Y - pointCenterY;
//
//m_usb_tx_string("DistX:");
//    m_usb_tx_int(distX);m_usb_tx_char(32);
//m_usb_tx_string("DistY:");
//    m_usb_tx_int(distY);m_usb_tx_char(32);
//
//    int distR = distXYToR(distX, distY);
//
//    // Compute heading in degrees
//    angleOfRobot = atan2d(pointDY-pointBY,pointDX-pointBX);
//
//    angleOfRobot -= (angleOfRobot < -90) ? -270 : 90;
//    
//    // Make sure angle of robot stays between -180 and 180
//    //  while subtracting 90 degrees from angleOfRobot.
//    long dY = ((long)sind_M(angleOfRobot)*(long)distY - (long)cosd_M(angleOfRobot)*(long)distX)/1000;
//    long dX = (-1*(long)cosd_M(angleOfRobot)*(long)distY - (long)sind_M(angleOfRobot)*(long)distX)/1000;
//    int theta2 = atan2d((int)dX,(int)dY);
//
////    theta2 -= (theta2 < -90) ? -270 : 90;
//
//    angleToRobot = angleOfRobot - theta2 - 90;
//
//    angleToRobot += (angleToRobot >  180) ? -360 :
//                    (angleToRobot < -179) ?  360 : 0;
//
//    angleToRobot = theta2;
//****************************    

    //TODO #define center coords
    long distX = 512 - pointCenterX;
    long distY = 384 - pointCenterY; 

    int distR = distXYToR(distX, distY);

    angleOfRobot = atan2d(pointDY - pointBY, pointDX - pointBX);

    angleOfRobot = angleOfRobot - 90;

    angleOfRobot += (angleOfRobot < -179) ? 360 : 0;

    int theta2 = -atan2d(distX, distY);
    
    theta2 = theta2 - 90;

    theta2 += (theta2 < -179) ? 360 : 0;

    angleToRobot = theta2 - angleOfRobot;

    angleToRobot = 180 - angleToRobot;

    angleToRobot += (angleToRobot < -180) ?  360 : 
                    (angleToRobot >  180) ? -360 : 0;
//****************************
m_usb_tx_string(" ROBOT ANGLE: ");m_usb_tx_int(angleOfRobot);m_usb_tx_char(32);

    m_usb_tx_string(" THETA1: ");m_usb_tx_int(angleToRobot);m_usb_tx_char(32);

    m_usb_tx_string(" THETA2: ");m_usb_tx_int(theta2);m_usb_tx_char(32);

    // Calculate absolute X and Y using distance and angle to robot
    robotX = 512+((long)cosd_M(angleToRobot)*(long)distR)/1000;
    robotY = 384+((long)sind_M(angleToRobot)*(long)distR)/1000;

    m_usb_tx_string("ROBOT COORDS: (");m_usb_tx_int(robotX);m_usb_tx_char(32);
    m_usb_tx_int(robotY);m_usb_tx_string(")");m_usb_tx_char(32);

    return 1; //TODO Check return value!
  }
  else if (zeroIfFourBlobs==4)
  {
    status_clear(STATUS_LOCALIZED);
  }
  {
    if (status_check(STATUS_LOCALIZED))
    {
      status_clear(STATUS_LOCALIZED);
      //TODO=HIGH
      // THIS CODE needs to change distX, distY, and possible angleOfRo
      // Do this using remaining blobs.
      // Also, TODO detect when changing from 3 to 2 or 2 to 1 or 1 to 2
      // (number of blobs) since this will change avgX and avgY
      pointBXLastKnown = pointBX;
      pointBYLastKnown = pointBY;
      pointDXLastKnown = pointDX;
      pointDYLastKnown = pointDY;
    }
    else
    {
      for (i=0;i<4;i++)
      {
        avgX += (blobX[i]==1023) ? blobX[i] : 0;
        avgY += (blobY[i]==1023) ? blobY[i] : 0;
      }     
      avgX = avgX / (4-zeroIfFourBlobs);
      avgY = avgY / (4-zeroIfFourBlobs);

      diffX = avgX - avgXOld;
      diffY = avgY - avgYOld;

      avgXOld = avgX;
      avgYOld = avgY;

      pointBX = pointBXLastKnown + diffX;
      pointBY = pointBYLastKnown + diffY;
      pointDX = pointDXLastKnown + diffX;
      pointDY = pointDYLastKnown + diffY;
    }
    //TODO code
    // If last cycle, the robot detected four stars (use a flag),
    //   just get location of average blob X and Y. No calculations.
    // (Make sure to reset the flag once there are 4 stars again.)
    // On subsequent iterations, take diff(blobX & Y)
    // Use diff(X & Y) to adjust the last known location of each blob.
    // Also, inform the code of limited current data reliability.
    return 0; //TODO Check return value!
  }

//TODO=LOW Synchronize X, Y to rink center on startup or on switch/PCI.
  
//TODO Implement prediction into the localization.  
//  char   xCalculated = 0; //   *xMemAddr;
//  char   yCalculated = 0; //   *yMemAddr;
//  char dirCalculated = 0; // *dirMemAddr;
//
//  char   xPredicted  = 0; //   *xMemAddr;
//  char   yPredicted  = 0; //   *yMemAddr;
//  char dirPredicted  = 0; // *dirMemAddr;

//    totalGain =  GAIN_PAST + GAIN_PRESENT + GAIN_FUTURE;
//    *xMemAddr = (GAIN_PAST *   xOld + GAIN_PRESENT *   xCalculated + GAIN_FUTURE *   xPredicted) / totalGain;
//    *yMemAddr = (GAIN_PAST *   yOld + GAIN_PRESENT *   yCalculated + GAIN_FUTURE *   yPredicted) / totalGain;
//  *dirMemAddr = (GAIN_PAST * dirOld + GAIN_PRESENT * dirCalculated + GAIN_FUTURE * dirPredicted) / totalGain;

  //TODO set up cases for each level of location data reliability
//  switch (0) {
//    default:
//      totalGain =  GAIN_PAST + GAIN_FUTURE;
//      *xMemAddr = (GAIN_PAST *   xOld + GAIN_FUTURE *   xPredicted) / totalGain;
//      *yMemAddr = (GAIN_PAST *   yOld + GAIN_FUTURE *   yPredicted) / totalGain;
//    *dirMemAddr = (GAIN_PAST * dirOld + GAIN_FUTURE * dirPredicted) / totalGain;
//  }
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
  motorDutyL = 3*(120 - degErrTurnCW)/2;
  motorDutyR = 3*(120 - degErrTurnCCW)/2;

  int slowDownNearGoal = max(0, 120 - distXYToR(robotX-enemyGoalX, robotY-enemyGoalY));

  // Ensure duty cycle is always between 0 and FULL_SPEED
  motorDutyL = max(0, motorDutyL-slowDownNearGoal);
  motorDutyR = max(0, motorDutyR-slowDownNearGoal);

  // Cap motor duty cycle at 99.2 percent when timer overflow is 250
  motorDutyL = min(255, motorDutyL);
  motorDutyR = min(255, motorDutyR);

  // Aliases are used to assign constants/variables to timer registers.
  // Low-pass filter keeps motor from changing speed quickly
  motor( LEFTMOTOR, FORWARD, motorDutyL);
  motor(RIGHTMOTOR, FORWARD, motorDutyR);
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
    angleToEnemyGoal += atan2d(GOAL_BLUE_Y-robotY,GOAL_BLUE_X-robotX)+1;
    angleToEnemyGoal  = angleToEnemyGoal >> 1;
    angleToTeamGoal  += atan2d(GOAL_RED_Y -robotY,GOAL_RED_X -robotX)+1;
    angleToTeamGoal   = angleToTeamGoal  >> 1;
  } else if (currentTeam==BLUE) {
    angleToEnemyGoal += atan2d(GOAL_RED_Y -robotY,GOAL_RED_X -robotX)+1;
    angleToEnemyGoal  = angleToEnemyGoal >> 1;
    angleToTeamGoal  += atan2d(GOAL_BLUE_Y-robotY,GOAL_BLUE_X-robotX)+1;
    angleToTeamGoal   = angleToTeamGoal  >> 1;
  } else {
    m_red(ON);
  }
}

int atan2d(long y, long x)
{
  long R;
  long angle3;
//This magic is an atan2d approximation for integers
  R = (x<0) ? (1000*(long)(x+abs(y)))/(abs(y)-x) :
              (1000*(long)(x-abs(y)))/(abs(y)+x);
//  m_usb_tx_char(47);m_usb_tx_long(R);m_usb_tx_char(45);

  angle3 = (x<0) ? 11781 : 3927;
//  m_usb_tx_int(angle);m_usb_tx_char(32);
  angle3 = angle3 + ((((R*R)/660)*R)/1464 - ((R*1963)/400));
//  m_usb_tx_int(angle);m_usb_tx_char(32);
  angle3 = angle3 / 87;
//  m_usb_tx_int(angle);m_usb_tx_char(32);
  angle3 = (y<0) ? -angle3 : angle3;
//  m_usb_tx_int(angle);m_usb_tx_char(32);
  return angle3;
}

long sind_M(long angle)
{
  long sindCalc;
  sindCalc = (angle<0) ? 1000*(long)angle/45 + 
                            (10*(long)angle*(long)angle/81) :
                         1000*(long)angle/45 -
                            (10*(long)angle*(long)angle/81);
  sindCalc = (sindCalc<0) ?
    (((-9*sindCalc*sindCalc)/1000 - 9*sindCalc)/40 + sindCalc) :
    ((( 9*sindCalc*sindCalc)/1000 - 9*sindCalc)/40 + sindCalc);

  return sindCalc;
}

long cosd_M(long angle2)
{
  angle2 += (angle2 > 90) ? -270 : 90;
  return sind_M(angle2);
}

int distXYToR (long dist_X, long dist_Y)
{
long dist_R;
long dist_R_Aprx;
long dist_R_Square;

  // Start with a good estimate of distR
  dist_R_Aprx  = ((abs(dist_X) + abs(dist_Y)) * 11) / 14;
  // Find the square of distR to use with the Babylonian method
  dist_R_Square = SQUARE(dist_X) + SQUARE(dist_Y);
  // Divide by zero protection when X and Y are at rink center
  dist_R_Aprx  = (dist_R_Aprx != 0) ? dist_R_Aprx : 2;
  // Approximate distR by finding the midpoint between
  //  the estimate and the square divided by the estimate
  dist_R_Aprx  = (dist_R_Aprx + dist_R_Square / dist_R_Aprx) / 2;
  dist_R       = (dist_R_Aprx + dist_R_Square / dist_R_Aprx) / 2;
  return dist_R;
// Typical convergence: error of distR < 1 in two approximations.
}
