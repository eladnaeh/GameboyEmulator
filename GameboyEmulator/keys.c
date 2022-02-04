#include "keys.h"
#include "memory.h"

/*0 is selected, 1 is unselected*/
void set_action_buttons() {
	reset_bit(JOYPAD_REGISTER_ADDRESS, SELECT_ACTION_BUTTONS);
	set_bit(JOYPAD_REGISTER_ADDRESS, SELECT_DIRECTION_BUTTONS);
}

/*0 is selected, 1 is unselected*/
void set_direction_buttons() {
	reset_bit(JOYPAD_REGISTER_ADDRESS, SELECT_DIRECTION_BUTTONS);
	set_bit(JOYPAD_REGISTER_ADDRESS, SELECT_ACTION_BUTTONS);
}

/*0 is selected, 1 is unselected*/
void set_key_pressed(unsigned char bit) {
	reset_bit(JOYPAD_REGISTER_ADDRESS, bit);
}

/*Handle button release*/
//check if functionality is correct
void handle_release() {
	unsigned char value = JOYPAD_REGISTER_RELEASE_VALUE;
	writeByte(JOYPAD_REGISTER_ADDRESS, &value);
}