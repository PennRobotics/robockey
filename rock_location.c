//TODO rock_location.h


void whereAmI(char* xMemAddr, char* yMemAddr)
{
  assert(xMemAddr);
  assert(yMemAddr); // check that addresses are not pointing to NULL
  //TODO doMWiiStuff
  //TODO algorithmToComputeLocation
  totalGain = GAIN_PAST + GAIN_PRESENT + GAIN_FUTURE;
  *xMemAddr = (GAIN_PAST * xOld + GAIN_PRESENT * xCalculated + GAIN_FUTURE * xPredicted) / totalGain;
  *yMemAddr = (GAIN_PAST * yOld + GAIN_PRESENT * yCalculated + GAIN_FUTURE * yPredicted) / totalGain;
  //TODO set up cases for each level of location data reliability
  default:
    totalGain = GAIN_PAST + GAIN_FUTURE;
    *xMemAddr = (GAIN_PAST * xOld + GAIN_FUTURE * xPredicted) / totalGain;
    *yMemAddr = (GAIN_PAST * yOld + GAIN_FUTURE * yPredicted) / totalGain;
}

