#include <stdio.h>

#include "status.h"
#include "registers.h"

status set_flag(flag_t flag_type){
	struct Flag flag = flags[flag_type];

	registers.f = (bool)(registers.f | flag.flag_mask);

	return SUCCESS;
}

status unset_flag(flag_t flag_type){
	struct Flag flag = flags[flag_type];

	registers.f = (bool)(registers.f & (!flag.flag_mask));

	return SUCCESS;
}

bool get_flag(flag_t flag_type) {
	unsigned char flag_on = 0x0;
	struct Flag flag = flags[flag_type];

	flag_on = (bool)(registers.f & flag.flag_mask) >> flag.bit_location;

	return flag_on;
}

status initialize_registers(){
	
	registers.a = 0x01;
	registers.b = 0x0;
	registers.c = 0x13;
	registers.d = 0x0;
	registers.e = 0xd8;
	registers.f = 0xb0;
	registers.h = 0x01;
	registers.l = 0x4d;
	registers.sp = 0xfffe;
	registers.pc = 0x100;
		
	return SUCCESS;
}

void print_registers(){
	printf("This is the value of a register: %04x\n", registers.a);
	printf("This is the value of b register: %04x\n", registers.b);
	printf("This is the value of c register: %04x\n", registers.c);
	printf("This is the value of d register: %04x\n", registers.d);
	printf("This is the value of e register: %04x\n", registers.e);
	printf("This is the value of f register: %04x\n", registers.f);
	printf("This is the value of h register: %04x\n", registers.h);
	printf("This is the value of l register: %04x\n", registers.l);

	printf("This is the value of sp register: %04x\n", registers.sp);
	printf("This is the value of pc register: %04x\n", registers.pc);

	return;
}