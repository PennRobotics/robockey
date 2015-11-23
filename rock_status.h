#ifndef _rock_status_h
#define _rock_status_h

void testTeamLEDPins();
void testStatusLEDPins();
void updateStatusFlags();
void sendSPI(uint16_t data);

#define STATUS_PUCK_IN_SIGHT        (0x0001)
#define STATUS_HAVE_PUCK            (0x0002)
#define STATUS_LOCALIZED            (0x0004)
#define STATUS_DEFENSE              (0x0008)
#define STATUS_TIME_ALMOST_UP       (0x0010)
#define STATUS_MOTOR_ON             (0x0020)
#define STATUS_WAIT_FOR_TEAMMATE    (0x0040)
#define STATUS_ASSISTING            (0x0080)
#define STATUS_NO_RECENT_COMM       (0x0100)
#define STATUS_NO_GAMEPLAY          (0x0200)
#define LED_RED                     (0x0400)
#define LED_BLUE                    (0x0800)

#define LOW(x)    ((x)     & 0xFF)
#define HIGH(x)  (((x)>>8) & 0xFF)

#define status_set(flag)             statusFlags |=  (flag)
#define status_clear(flag)           statusFlags &= ~(flag)
#define status_toggle(flag)          statusFlags ^=  (flag)
#define status_clear_all()           statusFlags  =  0
//TODO #define status_blink(flag)           statusFlags |=  (flag); statusBlinkFlags |=  (flag)
//TODO #define STATUS_BLINK_PERIOD_MS

#define status_check(flag)    (bool)(statusFlags  &  (flag))

#define led_red(val)    if(val==OFF){status_clear(LED_RED); }else if(val==ON){status_set(LED_RED); }else if(val==TOGGLE){status_toggle(LED_RED);}
#define led_blue(val)   if(val==OFF){status_clear(LED_BLUE);}else if(val==ON){status_set(LED_BLUE);}else if(val==TOGGLE){status_toggle(LED_BLUE);}

#endif
