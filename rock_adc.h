#ifndef _rock_adc_h
#define _rock_adc_h

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

int findPuckDistance(void);

//TODO Make poll(x)IR extern and put in vars.h

int highestIRPoll; //TODO extern?

char puckIsLeft;
char puckIsRight;

char turnServo;

void getADC(char pinADC);

#endif
