#ifndef _rock_init_routine_h
#define _rock_init_routine_h

#define MAX7219_NORMAL_OPERATION   0x0C01
#define MAX7219_SCAN_DIGITS_0TO1   0x0B01
#define MAX7219_INTENSITYx         0x0A05
#define MAX7219_DECODE_NONE        0x0900
#define MAX7219_TEST_MODE_ON       0x0F01
#define MAX7219_TEST_MODE_OFF      0x0F00

#define RF_CHANNEL       1
#define RF_PACKET_LENGTH 10

#define TEAM_NUMBER      5
#define ROBOT_NUMBER     1
#define FRIEND_1         (ROBOTNUMBER==3?1:ROBOT_NUMBER+1
#define FRIEND_2         (ROBOTNUMBER==1?3:ROBOT_NUMBER-1

#define RF_RX_ADDRESS    (TEAM_NUMBER)*4 + (ROBOT_NUMBER) - 1
#define RF_TX_ADDRESS_1  (TEAM_NUMBER)*4 + FRIEND_1 - 1
#define RF_TX_ADDRESS_2  (TEAM_NUMBER)*4 + FRIEND_2 - 1

void init(void);
void initStatusLEDPins(void);
void initTeamLEDPins(void);
void initADC(void);
void initMWii(void);
void initUSB(void);
void initMRF(void);
void initTimers(void);

#endif
