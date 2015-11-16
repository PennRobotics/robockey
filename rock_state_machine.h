#ifndef _rock_state_machine_h
#define _rock_state_machine_h

void stateMachine(void);
int getCurrentState(void);
int stateStart(void);
int stateTied(void);
int stateWinningPlus(void);
int stateWinning(void);
int stateLosing(void);

#endif
