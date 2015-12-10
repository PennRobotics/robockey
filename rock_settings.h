#ifndef _rock_settings_h
#define _rock_settings_h

// SHOOTER, RUNNER, V_LEFT, V_RIGHT, GOALIE, GOALIE_L, GOALIE_R, WEDGE
#define ROBOT RUNNER

// Adjustable Settings
#define TEST_LEDS_ON_STARTUP            TRUE 
#define TEST_MOTORS_ON_STARTUP          TRUE 
#define TEST_STATUS_LED_TIME_MS         54
#define TEST_TEAM_LED_TIME_MS           203
#define SHORT_WAIT_BEFORE_TESTS         FALSE
#define WAIT_FOR_MWII_TO_OPEN           FALSE

// How much tolerance in puck-robot-goal alignment
#define GOAL_ALIGN_DEG        12

#define MOTOR_UPDATE_PERIOD_MS          10

#define USB_DEBUGGING                   TRUE

#endif
