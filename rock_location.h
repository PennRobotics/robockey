#ifndef _rock_location_h
#define _rock_location_h

#define GAIN_PAST 10
#define GAIN_PRESENT 10
#define GAIN_FUTURE 10

char locationWhereAmI(void);
//char locationWhereAmI(unsigned char* xMemAddr, unsigned char* yMemAddr, unsigned char* dirMemAddr);

//TODO put all these in correct place
char blobXSorted[4];
char sort1;
char sort2;
char sort3;
char sort4;
long s12,s12Norm;
long s13,s13Norm;
long s14,s14Norm;
long s23,s23Norm;
long s24,s24Norm;
long s34,s34Norm;
int sMax;
int thr;

int blobX[4], blobY[4];
char blobXOld[4], blobYOld[4];

unsigned int blobMemAddr[12]; 

#define min(a,b) ((a)<(b))?a:b
//#define abs(a) (a<0)?-1*a:a

#endif
