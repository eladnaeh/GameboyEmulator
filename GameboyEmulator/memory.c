#include <stdio.h>
#include <string.h>

#include "status.h"
#include "memory.h"
#include "registers.h"

/*
	Check input for readByte, writeByte, readShort, writeShort
*/

status readByte(unsigned short address, unsigned char* byte){
	if (UNACCESSIBLE_MEMORY(address)) {
		return ACCESSED_PROHIBITED_MEMORY;
	}
	
	*byte = memory.memory[address];

	return SUCCESS;
}

status writeByte(unsigned short address, unsigned char* byte){
	if (UNACCESSIBLE_MEMORY(address)) {
		return ACCESSED_PROHIBITED_MEMORY;
	}

	memory.memory[address] = *byte;

	return SUCCESS;
}

status readShort(unsigned short address, unsigned short* word){
	if (UNACCESSIBLE_MEMORY(address)) {
		return ACCESSED_PROHIBITED_MEMORY;
	}
	
	unsigned char first_byte = 0x0;
	unsigned char second_byte = 0x0;

	readByte(address, &first_byte);
	readByte(address + 1, &second_byte);

	*word = (first_byte | (second_byte << 8));

	return SUCCESS;
}

status writeShort(unsigned short address, unsigned short* word){
	if (UNACCESSIBLE_MEMORY(address)) {
		return ACCESSED_PROHIBITED_MEMORY;
	}
	
	unsigned char first_byte = *word & 0xff;
	unsigned char second_byte = (*word >> 8) & 0xff;

	//Check return value of write byte
	writeByte(address, &first_byte);
	writeByte(address + 1, &second_byte);
	
	return SUCCESS;
}

status popStack(unsigned short* word){

	readShort(registers.sp, word);
	registers.sp = registers.sp + SP_CHANGE_BYTES_STACK_OPERATIONS;

	return SUCCESS;
}

status pushStack(unsigned short* word){

	registers.sp = registers.sp - SP_CHANGE_BYTES_STACK_OPERATIONS;
	writeShort(registers.sp, word);

	return SUCCESS;
}

status initialize_memory(){
	memset(memory.memory, 0, sizeof(memory.memory));

	for (int inx = 0; inx < INITIALIZATION_BYTES_AMOUNT; inx++){
		writeByte(memory.memory[initialization_addresses[inx]], &initialization_values[inx]);
	}

	return SUCCESS;
}

status set_bit(unsigned short address, unsigned char bit) {
	unsigned char byte;
	readByte(address, &byte);
	byte = byte | (1 << bit);
	writeByte(address, &byte);

	return SUCCESS;
}

status reset_bit(unsigned short address, unsigned char bit) {
	unsigned char byte;
	readByte(address, &byte);
	byte = byte | (~(1 << bit));
	writeByte(address, &byte);

	return SUCCESS;
}

bool test_bit(unsigned char byte, unsigned char bit) {
	return ((byte & (1 << bit)) ? true : false);
}
