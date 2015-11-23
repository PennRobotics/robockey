# Robockey #

__Snapshot of "TODO" tags as of 23 November:__

main.c:1:// TODO Set up mRF  
main.c:2:// TODO Set up mWii  
main.c:3:// TODO Localization routine  
main.c:4:// TODO Communication routine  
main.c:5:// TODO Comm with game controller  
main.c:6:// TODO Comm with other robots  
main.c:7:// TODO Comm with local debug (USB serial monitor)  
main.c:8:// TODO rock_motor.c  
main.c:9:// TODO Add interrupts  
main.c:10:// TODO Determine best way to track IR  
rock_initialize_vars.h:4://TODO Rename rock_vars.h  
rock_localization.h:4://TODO Lookup best max() and max3() functions!  
rock_localization.h:8://TODO  
rock_localization.h:11://TODO  
rock_localization.h:16://TODO  
rock_localization.h:19://TODO  
rock_localization.h:23://TODO Clean rock_localization.h  
rock_localization.h:29://TODO Make poll(x)IR extern and put in vars.h  
rock_localization.h:34:int highestIRPoll; //TODO extern?  
rock_status.c:7:  //TODO Set up Team LEDs on MAX7219  
rock_status.c:32://TODO SPI communication using the MAX7219 IC  
rock_status.h:13://TODO Not needed: STATUS_RED_TEAM  
rock_comm.c:21://TODO Add to rock_interrupts:  
rock_localization.c:5://TODO Physical robot: shield phototransistors from constellation!!!  
rock_localization.c:6://TODO Read ATMEGA datasheet about differential measurements on ADC  
rock_localization.c:7://TODO Also, chapter 23 details the analog comparator.  
rock_localization.c:11:  //TODO Use the return value from locationWhereAmI  
rock_localization.c:18:  //TODO Discrete Lowpass on IR polling  
rock_localization.c:66://TODO check if we need to disable pin-change interrupts  
rock_location.h:11://TODO put all these in correct place  
rock_init_routine.c:24://TODO  initTeamLEDPins();  
rock_init_routine.c:31://TODO  initMRF();  
rock_init_routine.c:115:  //TODO Disable digital inputs  
rock_init_routine.c:123:  //sei(); TODO Check if needed! Should be redundant, refer to fcn.  
rock_init_routine.c:125:  //TODO ISR(ANALOG_COMP_vect)  
rock_state_machine.c:103://TODO Physical switch to allow changing strategy  
rock_state_machine.c:107:  //TODO Potential to use STATUS_LOW_TIME  
rock_state_machine.c:127://TODO All this needs work!  
rock_state_machine.c:139:    //TODO See if assist opportunity exists (V formation or wedge)  
rock_state_machine.c:147:  if (distToPuck == 255/*TODO*/) {return FIND_PUCK;}  
rock_motor.c:1://TODO Fix variables in motor(id, dir, duty)  
rock_motor.c:2://TODO Create port definitions e.g. MOTOR_L_EN_PORT  
m_usb.c:693:// TODO: this function is untested.  Does it work?  Please email  
m_usb.c:710:            // TODO; should this try to abort the previously  
m_usb.c:719:    UEDATX = 0; // TODO: should this be 1 or 0 ???  
rock_location.c:1://TODO rock_location.h  
rock_location.c:2://TODO Check return of char whereAmI !! 0? -1? 1? et al?  
rock_location.c:25://TODO Currently, having memory addresses as arguments is not helpful.  
rock_location.c:56:      //TODO This needs to compare ORDERED data, not raw data!!  
rock_location.c:57:      //TODO Fix the order and compare check and create a threshold var.  
rock_location.c:64:        //TODO Check return value!  
rock_location.c:72:    //TODO arrange points in correct order (A, B, C, D)  
rock_location.c:132:    //TODO  
rock_location.c:159:    //TODO Fix signs so position is shown correctly  
rock_location.c:164:    return 1; //TODO Check return value!  
rock_location.c:168:    //TODO code  
rock_location.c:175:    return 0; //TODO Check return value!  
rock_location.c:178://TODO Synchronize X, Y to rink center on startup or on switch/PCI.  
rock_location.c:180://TODO TODO Implement prediction into the localization.    
rock_location.c:194:  //TODO set up cases for each level of location data reliability  
rock_m2_pins.h:18://TODO  Figure out how to disable inverted outputs  
rock_m2_pins.h:19://TODO  Ensure no multiplexed pins are active  
rock_m2_pins.h:21://TODO Check if B7 (/RTS) or Timer0 is in use  
rock_m2_pins.h:28://TODO Place in appropriate bin and choose real pin numbers  
