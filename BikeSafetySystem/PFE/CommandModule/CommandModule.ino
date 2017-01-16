
#include "Adafruit_BLE_UART.h"
#include "GPIO_manager.h"
#include "Frame_manager.h"
#include "String_queue.h"

// Connect CLK/MISO/MOSI to hardware SPI
// e.g. On UNO & compatible: CLK = 13, MISO = 12, MOSI = 11
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2     // This should be an interrupt pin, on Uno thats #2 or #3
#define ADAFRUITBLE_RST 9
#define LEFT_BUTTON	5
#define RIGHT_BUTTON 6

/* Definition of sketch variables */
Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
Frame_manager frame_manager = Frame_manager();
GPIO_manager gpio = GPIO_manager();
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;
String_queue messages = String_queue();

bool left_btn_state;
bool last_left_btn_state = LOW;
unsigned long last_debounce_time_left = 0;

bool right_btn_state;
bool last_right_btn_state = LOW;
unsigned long last_debounce_time_right = 0;

unsigned long debounce_delay = 100;

bool test = false;

void setup(void)
{ 
  Serial.begin(9600);
  while(!Serial); // Leonardo/Micro should wait for serial init
  Serial.println(F("Adafruit Bluefruit Low Energy nRF8001 Print echo demo"));

  /* Initialisation of button pin */
  gpio.init_input_pin(LEFT_BUTTON);
  gpio.init_input_pin(RIGHT_BUTTON);

  BTLEserial.setDeviceName("COMMAND"); /* 7 characters max! */
  BTLEserial.begin();
}


void loop()
{
	// Tell the nRF8001 to do whatever it should be working on.
	BTLEserial.pollACI();

	// Ask what is our current status
	aci_evt_opcode_t status = BTLEserial.getState();

	// If the status changed....
	if (status != laststatus) {
		if (status == ACI_EVT_DEVICE_STARTED) {
			Serial.println(F("* Advertising started"));
		}
		if (status == ACI_EVT_CONNECTED) {
			Serial.println(F("* Connected!"));
		}
		if (status == ACI_EVT_DISCONNECTED) {
			Serial.println(F("* Disconnected or advertising timed out"));
		}
		// set the last status change to this one
		laststatus = status;
	}


	if (status == ACI_EVT_CONNECTED) {
			
		String str = messages.pop();
		
		if (str != "") {

			Serial.print(F("\n* Msg to send -> \""));
			Serial.print(str);
			Serial.println("\"");

			// We need to convert the line to bytes, no more than 20 at this time
			unsigned char* sendbuffer = frame_manager.builder(str);
			char size = sizeof(sendbuffer);

			if (size > 1) {

				Serial.print(F("\n* Sending -> \""));
				Serial.print((char *)sendbuffer);
				Serial.println("\"");

				// write the data
				BTLEserial.write((uint8_t*)sendbuffer, size-1);
			}
		}
	}

	/* Check left button */

	// read the state of the switch into a local variable:
	bool left_value = gpio.read_pin(LEFT_BUTTON);
	// If the switch changed, due to noise or pressing:
	if (left_value != last_left_btn_state) {
		// reset the debouncing timer
		last_debounce_time_left = millis();
	}
	if ((millis() - last_debounce_time_left) > debounce_delay) {
		// if the button state has changed:
		if (left_value != left_btn_state) {
			left_btn_state = left_value;

			// only toggle the LED if the new button state is HIGH
			if (left_btn_state == LOW) {
				messages.push("L");
			}
		}
	}
	// save the reading
	last_left_btn_state = left_value;


	/* Check right button */

	int right_value = gpio.read_pin(RIGHT_BUTTON);

	if (right_value != last_right_btn_state) {
		last_debounce_time_right = millis();
	}

	if ((millis() - last_debounce_time_right) > debounce_delay) {
		if (right_value != right_btn_state) {
			
			right_btn_state = right_value;

			if (right_btn_state == LOW) {
				messages.push("R");
			}
		}
	}

	last_right_btn_state = right_value;

}
