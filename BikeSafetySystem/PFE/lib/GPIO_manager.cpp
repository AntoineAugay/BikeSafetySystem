//
// Created by Antoine on 02/12/2016.
//

/*!
 * \file GPIO_manager.cpp
 * \brief GPIO manager of arduino Fio board
 * \author AUGAY Antoine
 * \version 0.1
 */

#include "GPIO_manager.h"


GPIO_manager::GPIO_manager(){

}

void GPIO_manager::init_output_pin( int pin ){
	pinMode( pin, OUTPUT );
}

void GPIO_manager::init_input_pin( int pin ){
    pinMode( pin, INPUT );
}

void GPIO_manager::set_pin( int pin, bool state ){
    if( state ){
		digitalWrite( pin , LOW );
	} else {
		digitalWrite( pin , HIGH );
	}
	
}

bool GPIO_manager::read_pin(int pin ) {
	if ( digitalRead(pin) ) {
		return true;
	}
	else {
		return false;
	}
}

