# Robockey #

__Details__
The Robockey robots for the code in this repository use a differential drive and several sensors to perform autonomous tasks specific to the game of hockey. Gameplay occurs on a slick surface on a rounded rectangle with dimensions approximately four feet by eight feet. M2 (MAEVARM) microcontrollers---created by Dr. Jonathan Fiene---are used to input sensor data, perform calculations, and drive each output e.g. motors.

__Snapshot of "TODO" tags as of 23 November:__

main.c:1: Set up mRF  
main.c:2: Set up mWii  
main.c:3: Localization routine  
main.c:4: Communication routine  
main.c:5: Comm with game controller  
main.c:6: Comm with other robots  
main.c:7: Comm with local debug (USB serial monitor)  
main.c:8: rock_motor.c  
main.c:9: Add interrupts  
main.c:10: Determine best way to track IR  
rock_initialize_vars.h:4://TODO Rename rock_vars.h  
rock_localization.h:4: Lookup best max() and max3() functions!  
rock_localization.h:8:  
rock_localization.h:11:  
rock_localization.h:16:  
rock_localization.h:19:  
rock_localization.h:23: Clean rock_localization.h  
rock_localization.h:29: Make poll(x)IR extern and put in vars.h  
rock_localization.h:34:int highestIRPoll; //TODO extern?  
rock_status.c:7:   Set up Team LEDs on MAX7219  
rock_status.c:32: SPI communication using the MAX7219 IC  
rock_status.h:13: Not needed: STATUS_RED_TEAM  
rock_comm.c:21: Add to rock_interrupts:  
rock_localization.c:5: Physical robot: shield phototransistors from constellation!!!  
rock_localization.c:6: Read ATMEGA datasheet about differential measurements on ADC  
rock_localization.c:7: Also, chapter 23 details the analog comparator.  
rock_localization.c:11:  Use the return value from locationWhereAmI  
rock_localization.c:18:  Discrete Lowpass on IR polling  
rock_localization.c:66: check if we need to disable pin-change interrupts  
rock_location.h:11: put all these in correct place  
rock_init_routine.c:24: initTeamLEDPins();  
rock_init_routine.c:31: initMRF();  
rock_init_routine.c:115:  Disable digital inputs  
rock_init_routine.c:123:  //sei(); Check if needed! Should be redundant, refer to fcn.  
rock_init_routine.c:125:  ISR(ANALOG_COMP_vect)  
rock_state_machine.c:103: Physical switch to allow changing strategy  
rock_state_machine.c:107:  Potential to use STATUS_LOW_TIME  
rock_state_machine.c:127: All this needs work!  
rock_state_machine.c:139:    See if assist opportunity exists (V formation or wedge)  
rock_state_machine.c:147:  if (distToPuck == 255/*TODO*/) {return FIND_PUCK;}  
rock_motor.c:1: Fix variables in motor(id, dir, duty)  
rock_motor.c:2: Create port definitions e.g. MOTOR_L_EN_PORT  
m_usb.c:693:O: this function is untested.  Does it work?  Please email  
m_usb.c:710:   ; should this try to abort the previously  
m_usb.c:719:    UEDATX = 0; should this be 1 or 0 ???  
rock_location.c:1: rock_location.h  
rock_location.c:2: Check return of char whereAmI !! 0? -1? 1? et al?  
rock_location.c:25: Currently, having memory addresses as arguments is not helpful.  
rock_location.c:56:      This needs to compare ORDERED data, not raw data!!  
rock_location.c:57:      Fix the order and compare check and create a threshold var.  
rock_location.c:64:        Check return value!  
rock_location.c:72:    arrange points in correct order (A, B, C, D)  
rock_location.c:132:     
rock_location.c:159:    Fix signs so position is shown correctly  
rock_location.c:164:    return 1; // Check return value!  
rock_location.c:168:    code  
rock_location.c:175:    return 0; // Check return value!  
rock_location.c:178: Synchronize X, Y to rink center on startup or on switch/PCI.  
rock_location.c:180: Implement prediction into the localization.    
rock_location.c:194:  set up cases for each level of location data reliability  
rock_m2_pins.h:18:  Figure out how to disable inverted outputs  
rock_m2_pins.h:19:  Ensure no multiplexed pins are active  
rock_m2_pins.h:21: Check if B7 (/RTS) or Timer0 is in use  
rock_m2_pins.h:28: Place in appropriate bin and choose real pin numbers  
