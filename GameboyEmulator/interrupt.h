#pragma once

#include <stdbool.h>

#include "status.h"

#define VBLANK_ADDRESS (0x40)
#define LCD_STAT_ADDRESS (0x48)
#define TIMER_ADDRESS (0x50)
#define SERIAL_ADDRESS (0x58)
#define JOYPAD_ADDRESS (0x60)

#define INTERRUPT_FLAG_ADDRESS (0xff0f)
#define INTERRUPT_ENABLE_ADDRESS (0xffff)

struct Interrupt{
	unsigned char address;
};

enum INTERRUPT_BITS{
	VBLANK = 0x0,
	LCD_STAT = 0x1,
	TIMER = 0x2,
	SERIAL = 0x3,
	JOYPAD = 0x4,
};

static struct Interrupt interrupt_types[5] = {
	[VBLANK] = {VBLANK_ADDRESS},
	[LCD_STAT] = {LCD_STAT_ADDRESS},
	[TIMER] = {TIMER_ADDRESS},
	[SERIAL] = {SERIAL_ADDRESS},
	[JOYPAD] = {JOYPAD_ADDRESS}
};

struct Interrupts{
	bool interrupt_master_enable_flag;
	struct Interrupt* interrupts;
};

struct Interrupts interrupts;

void set_interrupt_flag(unsigned char bit);

void reset_interrupt_flag(unsigned char bit);

void interruptCheck();

status initialize_interrupts();
