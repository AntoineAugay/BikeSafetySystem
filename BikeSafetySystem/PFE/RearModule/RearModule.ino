

#include <SPI.h>
#include "Timer.h"
#include "Adafruit_BLE_UART.h"
#include "Frame_manager.h"
#include "Turn_signal.h"
#include "String_queue.h"

// Connect CLK/MISO/MOSI to hardware SPI
// e.g. On FIO : CLK = 13, MISO = 12, MOSI = 11
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2     // This should be an interrupt pin, on Uno thats #2 or #3
#define ADAFRUITBLE_RST 9
#define LEFT_TURN_SIGNAL 3
#define RIGHT_TURN_SIGNAL 4


/* Definition of sketch variables */
Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART( ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST );
Frame_manager frame_manager = Frame_manager();
GPIO_manager gpio = GPIO_manager();
Turn_signal turn_signal = Turn_signal( LEFT_TURN_SIGNAL,  RIGHT_TURN_SIGNAL, gpio );
String_queue messages = String_queue();


Timer t;
int turn_signal_event = -1;
int turn_signal_after_event = -1;
char message[20] = "";
String command;
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;


/*!
 *  \brief Reset environment at the end of blinking
 *
 *  \param nothing
 *  \return nothing
 */
void End_of_blinking(void){

    /* Stop the periodic event */
    t.stop( turn_signal_event );

    /* Set active signal to NOTHING */
    turn_signal.set_active_signal( NONE );
    turn_signal.reset_state_signal();
    /* Reset event ID */
    turn_signal_event = -1;
    turn_signal_after_event = -1;
}

/*!
 *  \brief Reset environment before the end of a sequence of blinking
 *
 *  \param nothing
 *  \return nothing
 */
void Stop_current_blinking(void){

    /* Erase after event */
    if(turn_signal_after_event != -1){
        t.stop(turn_signal_after_event);
        turn_signal_after_event = -1;
    }

    /* Erase signal event */
    if(turn_signal_event != -1){
        t.stop(turn_signal_event);
        turn_signal.set_active_signal(NONE);
        turn_signal.reset_state_signal();
        turn_signal_event = -1;
    }
}

void On_blink(void){
    turn_signal.toggle_turn_signal();
}

void setup(void)
{
    Serial.begin( 9600 );
    //while( !Serial ); // Leonardo/Micro should wait for serial init
    Serial.println( F("Adafruit Bluefruit Low Energy nRF8001 Print echo demo") );

    BTLEserial.setDeviceName( "REAR" ); /* 7 characters max! */
    BTLEserial.begin();

    turn_signal.init();

}

void loop()
{
    
    // Tell the nRF8001 to do whatever it should be working on.
    BTLEserial.pollACI();
    t.update();
    int size;
    
    // Ask what is our current status
    aci_evt_opcode_t status = BTLEserial.getState();
    // If the status changed....
    if ( status != laststatus ) {
      // print it out!
      if (status == ACI_EVT_DEVICE_STARTED) {
          Serial.println(F("* Advertising started"));
      }
      if (status == ACI_EVT_CONNECTED) {
          Serial.println(F("* Connected!"));
      }
      if (status == ACI_EVT_DISCONNECTED) {
          Serial.println( F("* Disconnected or advertising timed out") );
      }
      // OK set the last status change to this one
      laststatus = status;
    }
  
    if ( status == ACI_EVT_CONNECTED ) {
        // Lets see if there's any data for us!
        if ( BTLEserial.available() ){
            Serial.print( "* " );
            Serial.print( BTLEserial.available() );
            Serial.println( F(" bytes available from BTLE") );
        }
        // OK while we still have something to read, get a character and print it out
        size = 0;
        while ( BTLEserial.available() ) {
            char c = BTLEserial.read();
            Serial.println( c, HEX );
            message[size] = c;
            size++;
        }
        
        /* parse the frame received */
        if( size != 0 ){
            
			Serial.println( "" );
            Serial.print( "Message : " );
            
			for( int i=0 ; i < size ; i++ ){
              Serial.print( message[i], HEX );
            }
            Serial.println( "" );

            frame_manager.parse( message, size, messages);
        }
    }

    command = messages.pop();
    
    if( command != "" ){
         Serial.println( "Command : " + command );
    }

   
    if( command != "" ){

        switch( command.charAt( 0 ) ){
            case 'L': 
                Stop_current_blinking();
                turn_signal.set_active_signal( LEFT );
                turn_signal_event = t.every( 500, On_blink );
                turn_signal_after_event = t.after( 5000, End_of_blinking );
                break;
            case 'R':
                Stop_current_blinking();
                turn_signal.set_active_signal( RIGHT );
                turn_signal_event = t.every( 500, On_blink );
                turn_signal_after_event = t.after( 5000, End_of_blinking );
                break;
        }
    }
}
