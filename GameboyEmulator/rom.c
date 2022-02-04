#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "status.h"
#include "memory.h"
#include "rom.h"

/*
	Thing to check:
		ROM Type
		Gameboy Type
		ROM Size?
*/

status _checkCartType(){
	unsigned char type;
	readByte(CART_TYPE_ADDRESS, &type);

	if (ROM_ONLY != type){
		printf("Unsupported Cart type - The Cart type is %s\n", cart_types[type]);

		return UNSUPPORTED_CART_TYPE;
;	}

	return SUCCESS;
}

status _checkGameboyType(){
	unsigned char type;
	readByte(GAMEBOY_TYPE_ADDRESS, &type);
	
	if (GAMEBOY != type){
		printf("Unsupported Gameboy Game - The Game is for %s\n", gameboy_types[type]);

		return UNSUPPORTED_GAMEBOY_TYPE;
	}

	return SUCCESS;
}


status _checkROM(){
	status rom_type_check = _checkCartType();
	if (SUCCESS != rom_type_check) {
		return rom_type_check;
	}

	status gameboy_type_check = _checkGameboyType();
	if (SUCCESS != gameboy_type_check){
		return gameboy_type_check;
	}

	return SUCCESS;
}

status loadROM(char* gamefile){
	FILE* gamefile_fp = NULL;
	size_t bytes_read = 0;
	errno_t err;

	err = fopen_s(&gamefile_fp, gamefile, "rb");
	if (err != 0){
		return OPENING_GAMEFILE_ERROR;
	}

	if (NULL == gamefile_fp){
		return OPENING_GAMEFILE_ERROR;
	}

	bytes_read = fread(memory.cart, sizeof(memory.cart), 1, gamefile_fp);
	if (sizeof(memory.cart) == bytes_read){
		return READING_CART_FAILURE;
	}
	
	fclose(gamefile_fp);

	status rom_check = _checkROM();
	if (SUCCESS != rom_check){
		return rom_check;
	}

	return SUCCESS;
}

status unloadROM() {
	memset(memory.cart, 0, sizeof(memory.cart));

	return SUCCESS;
}