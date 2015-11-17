#ifndef _rock_localization_h
#define _rock_localization_h

#endif
//TODO Clean rock_localization.h

int findPuckDistance(void);

//TODO Make poll(x)IR extern and put in vars.h
extern int pollLeftIR;
extern int pollCenterIR;
extern int pollRightIR;

//TODO Lookup best max() and max3() functions!
#define max3(a, b, c) max(a, max(b, c))
#define max(a, b) (a>b)?a:b

int highestIRPoll; //TODO extern?

char puckIsLeft;
char puckIsRight;
#define IR_SCHMITT_LEVEL 0

char turnServo;
#define TURN_LEFT        -1
#define TURN_RIGHT        1
#define TURN_NOT_NEEDED   0

#define PUCK_DISTANCE_GAIN  10
