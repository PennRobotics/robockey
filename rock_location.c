//TODO rock_location.h
//TODO Check return of char whereAmI !! 0? -1? 1? et al?

// When calling this function, pass pointers as inputs:
// Let's say main() has 3 variables: robotXPos, robotYPos, robotHeading. Use:
//   whereAmI(&robotXPos, &robotYPos, &robotHeading); 

#ifndef _rock_headers_h
#include "rock_headers.h"
#endif

char whereAmI(unsigned char* xMemAddr, unsigned char* yMemAddr, unsigned char* dirMemAddr)
{
  assert(  xMemAddr);
  assert(  yMemAddr);
  assert(dirMemAddr); // check that addresses are not pointing to NULL

  int totalGain;
  char   xOld =   *xMemAddr;
  char   yOld =   *xMemAddr;
  char dirOld = *dirMemAddr;

  int i; char zeroIfFourBlobs = 0;

  //TODO Check this loop goes 0, 1, 2, 3:
  for (i=0;i<4;i++)
  {
    blobXOld[i] = blobX[i];
    blobYOld[i] = blobY[i];
    //TODO Create a new buffer with 12 elements at blobMemAddr
    blobX[i] = m_wii_read((unsigned int*)(blobMemAddr + i*3 + 0));
    blobY[i] = m_wii_read((unsigned int*)(blobMemAddr + i*3 + 1));

    // Check if blobs leave the mWii field-of-view
    if ((blobX[i]==1023) && (blobY[i]==1023)) {zeroIfFourBlobs++;}
    else /*Check if new data is near old data*/
    {
      //TODO This needs to compare ORDERED data, not raw data!!
      //TODO Fix the order and compare check and create a threshold var.
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
    s12 = (blobX[1]-blobX[0]) * (blobX[1]-blobX[0])+
          (blobY[1]-blobY[0]) * (blobY[1]-blobY[0]);
    s13 = (blobX[2]-blobX[0]) * (blobX[2]-blobX[0])+
          (blobY[2]-blobY[0]) * (blobY[2]-blobY[0]);
    s14 = (blobX[3]-blobX[0]) * (blobX[3]-blobX[0])+
          (blobY[3]-blobY[0]) * (blobY[3]-blobY[0]);
    s23 = (blobX[2]-blobX[1]) * (blobX[2]-blobX[1])+
          (blobY[2]-blobY[1]) * (blobY[2]-blobY[1]);
    s24 = (blobX[3]-blobX[1]) * (blobX[3]-blobX[1])+
          (blobY[3]-blobY[1]) * (blobY[3]-blobY[1]);
    s34 = (blobX[3]-blobX[2]) * (blobX[3]-blobX[2])+
          (blobY[3]-blobY[2]) * (blobY[3]-blobY[2]);
    sMax = max(max3(s12,s13,s14), max3(s23,s24,s34));
    s12Norm = (long)(1000*s12)/sMax;
    s13Norm = (long)(1000*s13)/sMax;
    s14Norm = (long)(1000*s14)/sMax;
    s23Norm = (long)(1000*s23)/sMax;
    s24Norm = (long)(1000*s24)/sMax;
    s34Norm = (long)(1000*s34)/sMax;

    point1 = s12Norm + s13Norm + s14Norm; // 1613 target
    point2 = s12Norm + s23Norm + s24Norm; // 1505
    point3 = s13Norm + s23Norm + s34Norm; // 1345
    point4 = s14Norm + s24Norm + s34Norm; // 2260 

    //TODO Double check algorithm is correct!
    if (min(min(abs(point1-1613),abs(point2-1613)),
            min(abs(point3-1613),abs(point4-1613))) ==
         abs(point1-1613)) {blobXSorted[0]=blobX[0];}
    else if (min(min(abs(point1-1505),abs(point2-1505)),
            min(abs(point3-1505),abs(point4-1505))) ==
         abs(point1-1505)) {blobXSorted[0]=blobX[1];}
    else if (min(min(abs(point1-1345),abs(point2-1345)),
            min(abs(point3-1345),abs(point4-1345))) ==
         abs(point1-1345)) {blobXSorted[0]=blobX[2];}
    else if (min(min(abs(point1-2260),abs(point2-2260)),
            min(abs(point3-2260),abs(point4-2260))) ==
         abs(point1-2260)) {blobXSorted[0]=blobX[3];}

    if (min(min(abs(point1-1613),abs(point2-1613)),
            min(abs(point3-1613),abs(point4-1613))) ==
         abs(point2-1613)) {blobXSorted[1]=blobX[0];}
    else if (min(min(abs(point1-1505),abs(point2-1505)),
            min(abs(point3-1505),abs(point4-1505))) ==
         abs(point2-1505)) {blobXSorted[1]=blobX[1];}
    else if (min(min(abs(point1-1345),abs(point2-1345)),
            min(abs(point3-1345),abs(point4-1345))) ==
         abs(point2-1345)) {blobXSorted[1]=blobX[2];}
    else if (min(min(abs(point1-2260),abs(point2-2260)),
            min(abs(point3-2260),abs(point4-2260))) ==
         abs(point2-2260)) {blobXSorted[1]=blobX[3];}

    if (min(min(abs(point1-1613),abs(point2-1613)),
            min(abs(point3-1613),abs(point4-1613))) ==
         abs(point3-1613)) {blobXSorted[2]=blobX[0];}
    else if (min(min(abs(point1-1505),abs(point2-1505)),
            min(abs(point3-1505),abs(point4-1505))) ==
         abs(point3-1505)) {blobXSorted[2]=blobX[1];}
    else if (min(min(abs(point1-1345),abs(point2-1345)),
            min(abs(point3-1345),abs(point4-1345))) ==
         abs(point3-1345)) {blobXSorted[2]=blobX[2];}
    else if (min(min(abs(point1-2260),abs(point2-2260)),
            min(abs(point3-2260),abs(point4-2260))) ==
         abs(point3-2260)) {blobXSorted[2]=blobX[3];}

    if (min(min(abs(point1-1613),abs(point2-1613)),
            min(abs(point3-1613),abs(point4-1613))) ==
         abs(point4-1613)) {blobXSorted[3]=blobX[0];}
    else if (min(min(abs(point1-1505),abs(point2-1505)),
            min(abs(point3-1505),abs(point4-1505))) ==
         abs(point4-1505)) {blobXSorted[3]=blobX[1];}
    else if (min(min(abs(point1-1345),abs(point2-1345)),
            min(abs(point3-1345),abs(point4-1345))) ==
         abs(point4-1345)) {blobXSorted[3]=blobX[2];}
    else if (min(min(abs(point1-2260),abs(point2-2260)),
            min(abs(point3-2260),abs(point4-2260))) ==
         abs(point4-2260)) {blobXSorted[3]=blobX[3];}

    //TODO Use bit manipulation to accomplish abs(x)
    //TODO (Somewhere else there is abs code!)
//    lineABTest = sDistNorm -  205;
//    lineACTest = sDistNorm -  601;
//    lineADTest = sDistNorm -  807;
//    lineBCTest = sDistNorm -  300;
//    lineBDTest = sDistNorm - 1000;
//    lineCDTest = sDistNorm -  453;

//    for (j=0; j<6; j++)
//    {
//      if (/*check if s12 is AB*/) {} 
//      if (/*check if s12 is AC*/) {} 
//      if (/*      ...         */) {} 
//      if (/*check if s34 is CD*/) {} 
//      // Solve via decision tree!
//      // i.e. Swap sets of points if s-values do not match up.
//    }

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

