#pragma once
/*ADD SUPPORT FOR UNACCESSIBLE VIDEO MEMORY ACCORDING TO LCD STATUS*/
#include <stdbool.h>

#include "status.h"

#define UNACCESSIBLE_MEMORY(addr) (((addr) >= 0xE000 && (addr) <= 0xFDFF) || ((addr) >= 0xFEA0 && (addr) <= 0xFEFF) ? true : false)

#define INITIALIZATION_BYTES_AMOUNT (31)

#define SP_CHANGE_BYTES_STACK_OPERATIONS (0x2)

static unsigned short initialization_addresses[INITIALIZATION_BYTES_AMOUNT] = { 0xff05, 0xff06, 0xff07, 0xff010, 0xff11, 0xff12, 0xff014, 0xff16, 0xff17, 0xff19,
																				0xff1a, 0xff1b, 0xff1c, 0xff1e, 0xff20, 0xff21, 0xff22, 0xff23, 0xff24, 0xff25,
																				0xff26, 0xff40, 0xff42, 0xff43, 0xff45, 0xff47, 0xff48, 0xff49, 0xff4a, 0xff4b, 0xffff };

static unsigned char initialization_values[INITIALIZATION_BYTES_AMOUNT] = { 0x0, 0x0, 0x0, 0x80, 0xbf, 0xf3, 0xbf, 0x3f, 0x0, 0xbf, 0x7f, 0xff, 0x9f, 0xbf, 0xff, 0x0, 0x0, 0xbf, 0x77,
																			0xf3, 0xf1, 0x91, 0x0, 0x0, 0x0, 0xfc, 0xff, 0xff, 0x0, 0x0, 0x0 };

/*
	This struct implements the memory layout of the Gameboy
*/
struct Memory{
	union{
		struct{
			/*
				unsigned char interrupt_enable;
				char high_ram[0x7f];
				char io[0x80];
				char unusable_memory[0x60]; //unaccessable
				char sprite_attribute_memory[0xa0];
				char echo_internal_ram[0x1E00]; //unaccessable
				char internal_ram[0x2000];
				char switchable_ram[0x2000];
				char video_ram[0x2000];
				char cart[0x8000];
			*/
			unsigned char cart[0x8000];
			unsigned char video_ram[0x2000];
			unsigned char switchable_ram[0x2000];
			unsigned char internal_ram[0x2000];
			unsigned char echo_internal_ram[0x1E00]; //unaccessable
			unsigned char sprite_attribute_memory[0xa0];
			unsigned char unusable_memory[0x60]; //unaccessable
			unsigned char io[0x80];
			unsigned char high_ram[0x7f];
			unsigned char interrupt_enable;
		};
		unsigned char memory[0xffff + 1];
	};
};

//The Gameboy Memory.
struct Memory memory;

/*
	This function initializes the Gameboy memory.
*/
status initialize_memory();

/*
	This function reads a byte from the memory at a given address.
	It returns status of reading from the memory.

	parameters:
		address - the address to read the memory from {unsigned short}
		byte - the location where the data will be saved {char*}
*/
status readByte(unsigned short address, unsigned char* byte);

/*
	This function writes a byte to the memory at a given address.
	It returns status of writing to the memory.

	parameters:
		address - the address to write the data to {unsigned short}
		byte - the byte to be written to memory {char*}
*/
status writeByte(unsigned short address, unsigned char* byte);

/*
	This function reads a short from the memory at a given address.
	It returns status of reading from the memory.

	parameters:
		address - the address to read the memory from {unsigned short}
		word - the location where the data will be saved {unsigned short*}
*/
status readShort(unsigned short address, unsigned short* word);

/*
	This function writes a short to the memory at a given address.
	It returns status of writing to the memory.

	parameters:
		address - the address to write the data to {unsigned short}
		word - the byte to be written to memory {unsigned short*}
*/
status writeShort(unsigned short address, unsigned short* word);


/*
	This function implements a push onto the stack
	
	*This is not an opcode - but an implementation for simplifing stack pushes
*/
status pushStack(unsigned short* word);

/*
	This function implements a pop off the stack
	
	*This is not an opcode - but an implementation for simplifing stack pops
*/
status pushStack(unsigned short* word);

/*
	This function implements the functionality of setting a bit
*/
status set_bit(unsigned short address, unsigned char bit);

/*
	This function implements the functionality if resetting a bit
*/
status reset_bit(unsigned short address, unsigned char bit);

/*
	This function implements the functionality of testing a bit
	Will recieve a byte and a bit number
	Will return True / False wether the bit is on
*/
bool test_bit(unsigned char byte, unsigned char bit);

//Which functionality does the memory need
/*
	needs to be able to read
	needs to be able to write
	(we need to know how to read and write 1 bytes and also 2 bytes (byte and short read and writes))

	limit access to memory that is prohibited

	debug options? (print memory?)
*/