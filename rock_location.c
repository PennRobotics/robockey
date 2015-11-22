//TODO rock_location.h
//TODO Check return of char whereAmI !! 0? -1? 1? et al?

// When calling this function, pass pointers as inputs:
// Let's say main() has 3 variables: robotXPos, robotYPos, robotHeading. Use:
//   locationWhereAmI(&robotXPos, &robotYPos, &robotHeading); 

#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

char locationWhereAmI(unsigned char* xMemAddr, unsigned char* yMemAddr, unsigned char* dirMemAddr)
{
  assert(  xMemAddr);
  assert(  yMemAddr);
  assert(dirMemAddr); // check that addresses are not pointing to NULL

  int totalGain;
  char   xOld =   *xMemAddr;
  char   yOld =   *xMemAddr;
  char dirOld = *dirMemAddr;

  int i; char zeroIfFourBlobs = 0;

  // Use m_wii_read() to update data at blobMemAddr
  m_wii_read(blobMemAddr);

  for (i=0;i<4;i++)
  {
    // Remember the previous values of blobX and blobY
    blobXOld[i] = blobX[i];
    blobYOld[i] = blobY[i];
    
    // Copy from blobMemAddr into blobX and blobY (blob size ignored)
    blobX[i] = blobMemAddr[i*3 + 0];
    blobY[i] = blobMemAddr[i*3 + 1];

    // Check if blobs leave the mWii field-of-view
    if ((blobX[i]==1023) && (blobY[i]==1023)) {zeroIfFourBlobs++;}
    else /*Check if new data is near old data*/
    {
      //TODO This needs to compare ORDERED data, not raw data!!
      //TODO Fix the order and compare check and create a threshold var.
thr=25;      
      if (((blobXOld[i]-blobX[i]) < thr) ||
          ((blobX[i]-blobXOld[i]) > thr) ||
          ((blobYOld[i]-blobY[i]) < thr) ||
          ((blobY[i]-blobYOld[i]) > thr))
      {
        //TODO Check return value!
        return 0; /*Current data is too far from previous data*/
      }
    }
  }

  if (zeroIfFourBlobs==0)
  {
    //TODO arrange points in correct order (A, B, C, D)
#define SQUARE(x) ((long)(x)*(long)(x))    
#define X(a) blobX[a]    
#define Y(a) blobY[a]    
    s12 = SQUARE(X(1)-X(0)) + SQUARE(Y(1)-Y(0));
    s13 = SQUARE(X(2)-X(0)) + SQUARE(Y(2)-Y(0));
    s14 = SQUARE(X(3)-X(0)) + SQUARE(Y(3)-Y(0));
    s23 = SQUARE(X(2)-X(1)) + SQUARE(Y(2)-Y(1));
    s24 = SQUARE(X(3)-X(1)) + SQUARE(Y(3)-Y(1));
    s34 = SQUARE(X(3)-X(2)) + SQUARE(Y(3)-Y(2));

    // Find the maximum "s" (blob distance squared)
    sMax =  s12 > s13 ?  s12 : s13;
    sMax = sMax > s14 ? sMax : s14;
    sMax = sMax > s23 ? sMax : s23;
    sMax = sMax > s24 ? sMax : s24;
    sMax = sMax > s34 ? sMax : s34;
    
    // Find points B and D (not ordered)
    pairBDIndex1 = (s12 == sMax) ? 0 :
                   (s13 == sMax) ? 0 :
                   (s14 == sMax) ? 0 :
                   (s23 == sMax) ? 1 :
                   (s24 == sMax) ? 1 : 2;

    pairBDIndex2 = (s12 == sMax) ? 1 :
                   (s13 == sMax) ? 2 :
                   (s14 == sMax) ? 3 :
                   (s23 == sMax) ? 2 : 3;
    
    // Find points A and C (not ordered)
    pairACIndex1 = (pairBDIndex1 != 0) ? 0 :
                  (pairBDIndex2 != 1) ? 1 : 2;

    pairACIndex2 = 6 - (pairBDIndex1 + pairBDIndex2 + otherIndex1);

    //TODO The distance from B to A and B to C should be
    //  different than the distance from D to A and D to C.
    //  Use this to determine which index is B or D.
    pointBX = X(pairBDIndex1);
    pointBY = Y(pairBDIndex1);
    pointDX = X(pairBDIndex2);
    pointDY = Y(pairBDIndex2);

    //Once points are in correct order...
    //TODO algorithm to compute distance
    //  avg(B,D) is center of constellation
    //TODO algorithm to compute heading
    //  atan2d(DBy/DBx);
    //TODO algorithm to compute X, Y from distance and heading
    //  X = Dist * cosd(Heading);
    //  Y = Dist * sind(Heading);
    return 1; //TODO Check return value!
  }
  else
  {
    //TODO code
    // If this is the first time without 4 stars,
    //   just get location of average blob X and Y.
    // Make sure to reset the flag any time there are 4 stars.
    // On subsequent iterations, take diff(blobX & Y)
    // Use diff(X & Y) to adjust the last known location of each blob.
    // Also, inform the code of limited current data reliability.
    return 0; //TODO Check return value!
  }

//TODO Synchronize X, Y to rink center on startup or on switch/PCI.
  
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

