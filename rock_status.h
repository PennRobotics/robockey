#ifndef _rock_status_h
#define _rock_status_h

void testTeamLEDPins();
void testStatusLEDPins();
void updateStatusFlags();
void sendSPI(uint16_t data);

#define STATUS_PUCK_IN_SIGHT        (0x001)
#define STATUS_HAVE_PUCK            (0x002)
#define STATUS_LOCALIZED            (0x004)
#define STATUS_DEFENSE              (0x008)
#define STATUS_RED_TEAM             (0x010)
#define STATUS_MOTOR_ON             (0x020)
#define STATUS_WAIT_FOR_TEAMMATE    (0x040)
#define STATUS_ASSISTING            (0x080)
#define STATUS_NO_RECENT_COMM       (0x100)
#define STATUS_NO_GAMEPLAY          (0x200)

#define LOW(x)    ((x)     & 0xFF)
#define HIGH(x)  (((x)>>8) & 0xFF)

#define status_set(flag)             statusFlags |=  (flag)
#define status_clear(flag)           statusFlags &= ~(flag)
#define status_toggle(flag)          statusFlags ^=  (flag)
#define status_clear_all()           statusFlags  =  0

#define status_check(flag)    (bool)(statusFlags  &  (flag))

#endif
