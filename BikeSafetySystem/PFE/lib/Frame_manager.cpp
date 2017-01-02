//
// Created by Antoine on 02/12/2016.
//

#include "Frame_manager.h"

Frame_manager::Frame_manager(){
    messages = String_queue();
}


void Frame_manager::parse( char* frame, int size ){

    int cursor = 0;
    while ( cursor < size ){

        /* Get the header */
        char header = frame[cursor];
		cursor++;
        switch ( header ){
            case 1 :
                /* Add a message in the list */
				messages.push( "L" );
                break;
            case 2 :
                /* Add a message in the list */
				messages.push( "R" );
                break;
        }
    }
}

unsigned char* Frame_manager::builder( String command ) {

	unsigned char cmd[20];

	switch ( command.charAt(0) ) {
		case 'L' :
			cmd[0] = 0x01;
			cmd[1] = '\n';
			break;
		case 'R':
			cmd[0] = 0x02;
			cmd[1] = '\n';
			break;
	}

	return cmd;
}


String Frame_manager::pop_message(){
	return messages.pop();
}
