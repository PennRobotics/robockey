//TODO rock_location.h

// When calling this function, pass pointers as inputs:
// Let's say main() has 3 variables: robotXPos, robotYPos, robotHeading. Use:
//   whereAmI(&robotXPos, &robotYPos, &robotHeading); 

void whereAmI(unsigned char* xMemAddr, unsigned char* yMemAddr, unsigned char* dirMemAddr)
{
  assert(  xMemAddr);
  assert(  yMemAddr);
  assert(dirMemAddr); // check that addresses are not pointing to NULL
  //TODO doMWiiStuff
  //TODO algorithmToComputeLocation
    totalGain =  GAIN_PAST + GAIN_PRESENT + GAIN_FUTURE;
    *xMemAddr = (GAIN_PAST *   xOld + GAIN_PRESENT *   xCalculated + GAIN_FUTURE *   xPredicted) / totalGain;
    *yMemAddr = (GAIN_PAST *   yOld + GAIN_PRESENT *   yCalculated + GAIN_FUTURE *   yPredicted) / totalGain;
  *dirMemAddr = (GAIN_PAST * dirOld + GAIN_PRESENT * dirCalculated + GAIN_FUTURE * dirPredicted) / totalGain;

  //TODO set up cases for each level of location data reliability
  default:
      totalGain =  GAIN_PAST + GAIN_FUTURE;
      *xMemAddr = (GAIN_PAST *   xOld + GAIN_FUTURE *   xPredicted) / totalGain;
      *yMemAddr = (GAIN_PAST *   yOld + GAIN_FUTURE *   yPredicted) / totalGain;
    *dirMemAddr = (GAIN_PAST * dirOld + GAIN_FUTURE * dirPredicted) / totalGain;
}

