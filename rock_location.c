//TODO rock_location.h

// When calling this function, pass pointers as inputs:
// Let's say main() has 3 variables: robotXPos, robotYPos, robotHeading. Use:
//   whereAmI(&robotXPos, &robotYPos, &robotHeading); 

#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

void whereAmI(unsigned char* xMemAddr, unsigned char* yMemAddr, unsigned char* dirMemAddr)
{
  assert(  xMemAddr);
  assert(  yMemAddr);
  assert(dirMemAddr); // check that addresses are not pointing to NULL

  int totalGain;
  char   xOld =   *xMemAddr;
  char   yOld =   *xMemAddr;
  char dirOld = *dirMemAddr;

  char i; char zeroIfFourBlobs = 0;

  //TODO Check this loop goes 0, 1, 2, 3:
  for (i=0;i<4;i++)
  {
    blobX[i] = m_wii_read(unsigned int* i);
    blobY[i] = m_wii_read(unsigned int* i);
    if ((blobX[i]==1023)&&(blobY[i]==1023)) {zeroIfFourBlobs++;}
  }

  if (zeroIfFourBlobs==0)
  {
    //code
  }
  else
  {
    //code
  }

  //TODO arrange points in correct order (A, B, C, D)
  //TODO algorithm to compute distance
  //TODO algorithm to compute heading
  //TODO algorithm to compute X, Y from distance and heading

  char   xCalculated =   *xMemAddr;
  char   yCalculated =   *yMemAddr;
  char dirCalculated = *dirMemAddr;

  char   xPredicted =   *xMemAddr;
  char   yPredicted =   *yMemAddr;
  char dirPredicted = *dirMemAddr;

    totalGain =  GAIN_PAST + GAIN_PRESENT + GAIN_FUTURE;
    *xMemAddr = (GAIN_PAST *   xOld + GAIN_PRESENT *   xCalculated + GAIN_FUTURE *   xPredicted) / totalGain;
    *yMemAddr = (GAIN_PAST *   yOld + GAIN_PRESENT *   yCalculated + GAIN_FUTURE *   yPredicted) / totalGain;
  *dirMemAddr = (GAIN_PAST * dirOld + GAIN_PRESENT * dirCalculated + GAIN_FUTURE * dirPredicted) / totalGain;

  //TODO set up cases for each level of location data reliability
  switch (0) {
    default:
      totalGain =  GAIN_PAST + GAIN_FUTURE;
      *xMemAddr = (GAIN_PAST *   xOld + GAIN_FUTURE *   xPredicted) / totalGain;
      *yMemAddr = (GAIN_PAST *   yOld + GAIN_FUTURE *   yPredicted) / totalGain;
    *dirMemAddr = (GAIN_PAST * dirOld + GAIN_FUTURE * dirPredicted) / totalGain;
  }
}

