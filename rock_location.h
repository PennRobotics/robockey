#ifndef _rock_location_h
#define _rock_location_h

#define GAIN_PAST 10
#define GAIN_PRESENT 10
#define GAIN_FUTURE 10

char whereAmI(unsigned char* xMemAddr, unsigned char* yMemAddr, unsigned char* dirMemAddr);

//TODO put all these in correct place
char blobXSorted[4];
char point1;
char point2;
char point3;
char point4;
char s12,s12Norm;
char s13,s13Norm;
char s14,s14Norm;
char s23,s23Norm;
char s24,s24Norm;
char s34,s34Norm;
char sMax;
char thr;

int blobX[4], blobY[4];
char blobXOld[4], blobYOld[4];

#define min(a,b) ((a)<(b))?a:b

#endif
