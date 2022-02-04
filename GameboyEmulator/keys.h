#define JOYPAD_REGISTER_ADDRESS (0xff00)

#define JOYPAD_REGISTER_RELEASE_VALUE (0xff)

enum JOYPAD_REGISTER_BITS {
	RIGHT_A = 0,
	LEFT_B = 1,
	UP_SELECT = 2,
	DOWN_START = 3,
	SELECT_DIRECTION_BUTTONS = 4,
	SELECT_ACTION_BUTTONS = 5
};

void set_action_buttons();

void set_direction_buttons();

void set_key_pressed(unsigned char bit);

void handle_release();
