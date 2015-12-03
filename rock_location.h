#ifndef _rock_location_h
#define _rock_location_h

//TODO Time permitting, use a MOM switch to calibrate rink center
#define RINK_CENTER_X 512
#define RINK_CENTER_Y 384

#define GAIN_PAST 10
#define GAIN_PRESENT 10
#define GAIN_FUTURE 10

#define SQUARE(x) ((long)(x)*(long)(x))    
#define X(a) blobX[a]    
#define Y(a) blobY[a]    

//TODO Lookup best max() and max3() functions!
#define max(a, b) ((a)>(b)) ? (a) : (b)
#define min(a, b) ((a)<(b)) ? (a) : (b)

char locationWhereAmI(void);

//TODO put all these in correct place
//TODO check that all variables are being called
//TODO only make variables use as much memory as needed
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
long sMax;
int thr;

int theta2; //TODO
int angleToRobot; //TODO

int blobX[4], blobY[4];
int blobXOld[4], blobYOld[4];

unsigned int blobMemAddr[12]; 

int atan2d(long y, long x);
long sind_M(long angle);
long cosd_M(long angle2);

int distXYToR (long dist_X, long dist_Y);

//TODO Not needed?  #define abs(a) (a<0)?-1*a:a

int pointBX;
int pointBY;
int pointDX;
int pointDY;
int pointBXLastKnown;
int pointBYLastKnown;
int pointDXLastKnown;
int pointDYLastKnown;

int avgX, avgY, avgXOld, avgYOld;
int diffX, diffY;

#endif
