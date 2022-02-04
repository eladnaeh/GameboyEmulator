#pragma once

#include <stdbool.h>

#include "status.h"

#define CARRY_FLAG_MASK (0b00010000)
#define HALF_CARRY_FLAG_MASK (0b00100000)
#define NEGATIVE_FLAG_MASK (0b01000000)
#define ZERO_FLAG_MASK (0b10000000)

/*
	This struct defines main registers used in the Gameboy CPU
	We are using unions to enable accessing both single registers (8bit) and double registers (16bit)
	We also want to run on a windows machine, so we have to use little-endian ordering
*/
struct Registers {
	union{
		struct {
			unsigned char f;
			unsigned char a;
		};
		unsigned short af;
	};
	union {
		struct {
			unsigned char c;
			unsigned char b;
		};
		unsigned short bc;
	};
	union {
		struct {
			unsigned char e;
			unsigned char d;
		};
		unsigned short de;
	};
	union {
		struct {
			unsigned char l;
			unsigned char h;
		};
		unsigned short hl;
	};

	unsigned short pc;
	unsigned short sp;
};

typedef enum Flags {
	CARRY = 0x4,
	HALF_CARRY = 0x5,
	NEGATIVE = 0x6,
	ZERO = 0x7,
}flag_t;

struct Flag {
	unsigned char bit_location;
	unsigned char flag_mask;
};

static struct Flag flags[0x8] = {
	[CARRY] = {CARRY, CARRY_FLAG_MASK},
	[HALF_CARRY] = {HALF_CARRY, HALF_CARRY_FLAG_MASK},
	[NEGATIVE] = {NEGATIVE, NEGATIVE_FLAG_MASK},
	[ZERO] = {ZERO, ZERO_FLAG_MASK}
};

status set_flag(flag_t flag_type);

status unset_flag(flag_t flag_type);

bool get_flag(flag_t flag_type);

struct Registers registers;

status initialize_registers();

void print_registers();