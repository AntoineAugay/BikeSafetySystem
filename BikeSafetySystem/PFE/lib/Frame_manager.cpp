//
// Created by Antoine on 02/12/2016.
//

#include "Frame_manager.h"

Frame_manager::Frame_manager(){
}


void Frame_manager::parse( char* frame, int size, String_queue& messages ){

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

	unsigned char* cmd;
	cmd = (unsigned char*)malloc(20 * sizeof(unsigned char));

	switch ( command.charAt(0) ) {
		case 'L' :
			cmd[0] = 0x01;
			break;
		case 'R':
			cmd[0] = 0x02;
			break;
	}

	return cmd;
}
