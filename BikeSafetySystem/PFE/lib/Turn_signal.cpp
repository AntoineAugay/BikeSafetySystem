
/*!
 * \file Turn_signal.cpp
 * \brief Turn signal manager
 * \author AUGAY Antoine
 * \version 0.1
 */

#include "Turn_signal.h"


Turn_signal::Turn_signal( int pin_left_signal
                        , int pin_right_signal
                        , GPIO_manager& gpio
                        )
{
	gpio = gpio;         
    pin_left_turn_signal  = pin_left_signal;
	pin_right_turn_signal = pin_right_signal;
	active_signal = NONE;
	signal_state = false;
}

void Turn_signal::init(){

    /* set pins as output */
    gpio.init_output_pin(pin_left_turn_signal);
    gpio.init_output_pin(pin_right_turn_signal);

    /* set default value on those pin (turn signal off) */
    gpio.set_pin(pin_left_turn_signal, 0);
    gpio.set_pin(pin_right_turn_signal, 0);
}

void Turn_signal::set_turn_signal(L_R_enum position, bool state){

    /* set left or right turn signal with state */
    if(position == LEFT){
        gpio.set_pin(pin_left_turn_signal, state);
    }
    else if(position == RIGHT) {
        gpio.set_pin(pin_right_turn_signal, state);
    }

}

void Turn_signal::toggle_turn_signal(void){

    /* Update pin */
    if(active_signal == LEFT){
        gpio.set_pin(pin_left_turn_signal, signal_state);
    }
    else if(active_signal == RIGHT) {
        gpio.set_pin(pin_right_turn_signal, signal_state);
    }
	
	/* toggle state*/
    signal_state = !signal_state;
}

void Turn_signal::reset_state_signal(){
	signal_state = false;
	gpio.set_pin(pin_left_turn_signal, false);
	gpio.set_pin(pin_right_turn_signal, false);
}
