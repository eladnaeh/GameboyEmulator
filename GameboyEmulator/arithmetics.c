#include "arithmetics.h"
#include "registers.h"

//DIDNT ADD 0xe8 support

unsigned char inc(unsigned char value) {
	if ((value & 0x0f) == 0x0f) {
		set_flag(HALF_CARRY);
	}
	else {
		unset_flag(HALF_CARRY);
	}

	value++;
	unset_flag(NEGATIVE);

	if (0 == value) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	return value;
}

unsigned char dec(unsigned char value){
	/*Won't borrow from bit 4(4,3,2,1,0) on -1 decrement unless first 4 bits are 0*/
	if (value & 0x0f) {
		unset_flag(HALF_CARRY);
	}
	else {
		set_flag(HALF_CARRY);
	}

	value--;
	set_flag(NEGATIVE);
	
	if (0 == value) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	return value;
}

/*
	This function implements the main functionality of adding a byte sized value to another.
*/
unsigned char add_byte(unsigned short value1, unsigned short value2){
	unsigned int result = value1 + value2;
	
	unset_flag(NEGATIVE);

	if (0 == value1) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	if (((value1 & 0xf) + (value2 & 0xf)) > 0xf) {
		set_flag(HALF_CARRY);
	}
	else {
		unset_flag(HALF_CARRY);
	}

	if ((result & 0xff00)) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	return (unsigned char)(result & 0xff);
}

/*
	This function implements the main functionality of adding a 2 byte sized value to another.
*/
//Check Implementation
unsigned short add_2bytes(unsigned short value1, unsigned short value2) {
	unsigned long result = value1 + value2;
	
	unset_flag(NEGATIVE);

	if (((value1 & 0xfff) + (value2 & 0xfff)) > 0xfff) {
		set_flag(HALF_CARRY);
	}
	else {
		unset_flag(HALF_CARRY);
	}

	if (result & 0xffff0000) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	return (unsigned short)(result & 0xffff);
}

/*
	This function implements the functionality of addition with carry flag.
	It accept just unsigned char values.
*/
unsigned char adc(unsigned char value1, unsigned char value2) {
	unsigned int result = value1 + value2;
	result += get_flag(CARRY);

	unset_flag(NEGATIVE);

	if (0 == value1) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	if (((value1 & 0xf) + (value2 & 0xf)) > 0xf) {
		set_flag(HALF_CARRY);
	}
	else {
		unset_flag(HALF_CARRY);
	}

	if ((result & 0xff00)) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	return (unsigned char)(result & 0xff);
}

/*
	This function implements the functionality of subtraction.
	It accept just unsigned char values.
*/
unsigned char sub(unsigned char value1, unsigned char value2) {
	set_flag(NEGATIVE);

	if (value2 > value1) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	if ((value2 & 0xf) > (value1 & 0xf)) {
		set_flag(HALF_CARRY);
	}
	else{
		unset_flag(HALF_CARRY);
	}

	value1 -= value2;

	if (0 == value1) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	return value1;
}

/*
	This function implements the functionality of subtraction with carry flag.
	It accept just unsigned char values.
*/
unsigned char sbc(unsigned char value1, unsigned char value2){
	unsigned char isCarry = get_flag(CARRY);

	set_flag(NEGATIVE);

	if (value2 + isCarry > value1) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	if (((value2 + isCarry) & 0xf) > (value1 & 0xf)) {
		set_flag(HALF_CARRY);
	}
	else {
		unset_flag(HALF_CARRY);
	}

	value1 -= (value2 + isCarry);

	if (0 == value1) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	return value1;
}

/*
	This function implements the functionality of AND binary operation.
	It accept just unsigned char values.
*/
unsigned char AND(unsigned char value1, unsigned char value2) {
	value1 &= value2;

	if (0 == value1) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	unset_flag(NEGATIVE);
	set_flag(HALF_CARRY);
	unset_flag(CARRY);

	return value1;
}

/*
	This function implements the functionality of OR binary operation.
	It accept just unsigned char values.
*/
unsigned char OR(unsigned char value1, unsigned char value2) {
	value1 |= value2;

	if (0 == value1) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);
	unset_flag(CARRY);

	return value1;
}

/*
	This function implements the functionality of XOR binary operation.
	It accept just unsigned char values.
*/
unsigned char XOR(unsigned char value1, unsigned char value2) {
	value1 ^= value2;

	if (0 == value1) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);
	unset_flag(CARRY);

	return value1;
}

/*
	This function implements the functionality of comparing.
	It accept just unsigned char values.
*/
status compare(unsigned char value1, unsigned char value2) {
	set_flag(NEGATIVE);

	if (value1 == value2) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	if ((value2 & 0xf) > (value1 & 0xf)) {
		set_flag(HALF_CARRY);
	}
	else {
		unset_flag(HALF_CARRY);
	}

	if (value2 > value1) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	return SUCCESS;
}