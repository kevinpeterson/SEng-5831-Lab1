#include <pololu/orangutan.h>

#include "menu.h"
#include "led.h"
#include "tasks.h"
#include "serial.h"
#include "logger.h"

#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "yellow_led.h"
#include "red_led.h"
#include "green_led.h"

void _build_command_buffer(char c);

// local global data structures
char command_buffer[32];
unsigned char command_buffer_position;

void init_menu() {
	serial_to_send( MENU, MENU_LENGTH );

	register_incoming_callback(&_build_command_buffer);
}

//------------------------------------------------------------------------------------------
// process_received_byte: Parses a menu command (series of keystrokes) that 
// has been received on USB_COMM and processes it accordingly.
// The menu command is buffered in check_for_new_bytes_received (which calls this function).
void process_received_string(const char* buffer) {
	serial_to_send("\r\n", 2);

	// Used to pass to USB_COMM for serial communication
	int length;
	char tempBuffer[32];
	
	// parse and echo back to serial comm window (and optionally the LCD)
	char color;
	char op_char;
	int value;
	int parsed = sscanf(buffer, "%c %c %d", &op_char, &color, &value);

	if(parsed < 2) {
		log_msg("INVALID COMMAND!!", ERROR);
		return;
	}

	sprintf(tempBuffer, "Got %c %c %d", op_char, color, value);
	log_msg(tempBuffer, DEBUG);
	memset(tempBuffer, 0, strlen(tempBuffer));

	length = sprintf( tempBuffer, "Op:%c C:%c V:%d\r\n", op_char, color, value );
	serial_to_send( tempBuffer, length );
	
	// convert color to upper and check if valid
	color -= 32*(color>='a' && color<='z');
	switch (color) {
		case 'R':
		case 'G':
		case 'Y': 
		case 'A': break;
		default:
			serial_to_send( "Bad Color. Try {RGYA}\r\n", 23 );
			serial_to_send( MENU, MENU_LENGTH);
			return;
	}

	// Check valid command and implement
	switch (op_char) {
		// change toggle period <color> LED
		case 'T':
		case 't':
			setPeriod( color, value );
			break; 
			
		// print counter for <color> LED 
		case 'P':
		case 'p':
			switch(color) {
				case 'R': 
					length = sprintf( tempBuffer, "R toggles: %d\r\n", get_red_toggles() );
					serial_to_send( tempBuffer, length );
					break;
				case 'G': 
					length = sprintf( tempBuffer, "G toggles: %d\r\n", get_green_toggles() );
					serial_to_send( tempBuffer, length );
					break;
				case 'Y': 
					length = sprintf( tempBuffer, "Y toggles: %d\r\n", get_yellow_toggles() );
					serial_to_send( tempBuffer, length );
					break;
				case 'A': 

					break;
				default: 
					serial_to_send("Default in p(color). How did I get here?\r\n", 42 );
			}
			break;

		// zero counter for <color> LED 
		case 'Z':
		case 'z':
			switch(color) {
				case 'R': 
					break;
				case 'G': 
					break;
				case 'Y': 
					break;
				case 'A': 
					break;
				default: 
					serial_to_send("Default in z(color). How did I get here?\r\n", 42 );
			}
			break;
		default:
			serial_to_send( "Command does not compute.\r\n", 27 );
		} // end switch(op_char) 
		
	serial_to_send( MENU, MENU_LENGTH);

} //end menu()

void _build_command_buffer(char c) {
	command_buffer[command_buffer_position] = c;
	command_buffer_position++;
	if(strstr(command_buffer, "\r") != NULL){
		process_received_string(command_buffer);
		memset(command_buffer, 0, strlen(command_buffer));
		command_buffer_position = 0;
	}
}


