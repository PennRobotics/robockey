#ifndef _rock_localization_h
#define _rock_localization_h

//TODO Lookup best max() and max3() functions!
#define max3(a, b, c) max(a, max(b, c))
#define max(a, b) (a>b)?a:b

//TODO
#define IR_SCHMITT_LEVEL 0

//TODO
#define TURN_LEFT        -1
#define TURN_RIGHT        1
#define TURN_NOT_NEEDED   0

//TODO
#define PUCK_DISTANCE_GAIN  10

//TODO
#define IR_THRESHOLD 6

#endif
//TODO Clean rock_localization.h

int findPuckDistance(void);

//TODO Make poll(x)IR extern and put in vars.h
extern int pollLeftIR;
extern int pollCenterIR;
extern int pollRightIR;

int highestIRPoll; //TODO extern?

char puckIsLeft;
char puckIsRight;

char turnServo;

void getADC(pin);
