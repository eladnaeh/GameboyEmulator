#pragma once

#include "status.h"

/*
	This function implements the functionality of incrementation.
	It accepts just unsigned char values.
*/
unsigned char inc(unsigned char value);

/*
	This function implements the functionality of decrementation.
	It accepts just unsigned char values.
*/
unsigned char dec(unsigned char value);

/*
	This function implements the main functionality of adding a byte sized value to another.
*/
unsigned char add_byte(unsigned short value1, unsigned short value2);

/*
	This function implements the main functionality of adding a 2 byte sized value to another.
*/
unsigned short add_2bytes(unsigned short value1, unsigned short value2);

/*
	This function implements the functionality of addition with carry flag.
	It accept just unsigned char values.
*/
unsigned char adc(unsigned char value1, unsigned char value2);

/*
	This function implements the functionality of subtraction.
	It accept just unsigned char values.
*/
unsigned char sub(unsigned char value1, unsigned char value2);

/*
	This function implements the functionality of subtraction with carry flag.
	It accept just unsigned char values.
*/
unsigned char sbc(unsigned char value1, unsigned char value2);

/*
	This function implements the functionality of AND binary operation.
	It accept just unsigned char values.
*/
unsigned char AND(unsigned char value1, unsigned char value2);

/*
	This function implements the functionality of XOR binary operation.
	It accept just unsigned char values.
*/
unsigned char XOR(unsigned char value1, unsigned char value2);

/*
	This function implements the functionality of OR binary operation.
	It accept just unsigned char values.
*/
unsigned char OR(unsigned char value1, unsigned char value2);

/*
	This function implements the functionality of comparing.
	It accept just unsigned char values.
*/
status compare(unsigned char value1, unsigned char value2);
