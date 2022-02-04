#include "registers.h"
#include "cb_instructions.h"
#include "memory.h"

unsigned char rlc(unsigned char value) {
	char unsigned carry = (value & 0b10000000) >> 7;

	if (carry) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	value = value << 1;
	value += carry;

	if (value == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);

	return value;
}

unsigned char rrc(unsigned char value) {
	unsigned char carry = (value & 0x1);

	if (carry) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	value = value >> 1;
	value |= (carry << 7);

	if (value == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);

	return value;
}

unsigned char rl(unsigned char value) {
	unsigned char carry_flag_value = get_flag(CARRY) ? 1 : 0;

	if (value & 0b10000000) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	value = value << 1;
	value += carry_flag_value;

	if (value == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);

	return value;
}

unsigned char rr(unsigned char value) {
	unsigned char carry_flag_value = get_flag(CARRY) ? 1 : 0;

	if (value & 0x1) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	value = value >> 1;
	value |= (carry_flag_value << 7);

	if (value == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);

	return value;
}

unsigned char sla(unsigned char value) {
	if (value & 0b10000000) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	value = value << 1;

	if (value == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);

	return value;
}

unsigned char sra(unsigned char value) {
	if (value & 0x1) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	value = ((value & 0b010000000) | (value >> 1));

	if (value == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);

	return value;
}

unsigned char swap(unsigned char value) {
	value = ((value & 0xf0) >> 4) | ((value & 0x0f) << 4);

	if (value == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);
	unset_flag(CARRY);

	return value;
}

unsigned char srl(unsigned char value) {
	if (value & 0x1) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	value = value >> 1;

	if (value == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}
		
	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);

	return value;
}

void bit(unsigned char bit, unsigned char value){
	if ((value & (1 << bit)) == 0) {
		set_flag(ZERO);
	}
	else{
		unset_flag(ZERO);
	}

	unset_flag(NEGATIVE);
	set_flag(HALF_CARRY);

	return value;
}

unsigned char res(unsigned char bit, unsigned char value) {
	value = value & (~(1 << bit));
	return value;
}

unsigned char set(unsigned char bit, unsigned char value) {
	value = value | (1 << bit);
	return value;
}

/*0x0 - 0x07*/
ins_status rlc_b(struct Instruction* instruction) { registers.b = rlc(registers.b);  return INS_SUCCESS; }
ins_status rlc_c(struct Instruction* instruction) { registers.c = rlc(registers.c);  return INS_SUCCESS; }
ins_status rlc_d(struct Instruction* instruction) { registers.d = rlc(registers.d);  return INS_SUCCESS; }
ins_status rlc_e(struct Instruction* instruction) { registers.e = rlc(registers.e);  return INS_SUCCESS; }
ins_status rlc_h(struct Instruction* instruction) { registers.h = rlc(registers.h);  return INS_SUCCESS; }
ins_status rlc_l(struct Instruction* instruction) { registers.l = rlc(registers.l);  return INS_SUCCESS; }
ins_status rlc_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = rlc(byte);  writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status rlc_a(struct Instruction* instruction) { registers.a = rlc(registers.a);  return INS_SUCCESS; }

/*0x08 - 0x0f*/
ins_status rrc_b(struct Instruction* instruction) { registers.b = rrc(registers.b);  return INS_SUCCESS; }
ins_status rrc_c(struct Instruction* instruction) { registers.c = rrc(registers.c);  return INS_SUCCESS; }
ins_status rrc_d(struct Instruction* instruction) { registers.d = rrc(registers.d);  return INS_SUCCESS; }
ins_status rrc_e(struct Instruction* instruction) { registers.e = rrc(registers.e);  return INS_SUCCESS; }
ins_status rrc_h(struct Instruction* instruction) { registers.h = rrc(registers.h);  return INS_SUCCESS; }
ins_status rrc_l(struct Instruction* instruction) { registers.l = rrc(registers.l);  return INS_SUCCESS; }
ins_status rrc_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = rrc(byte);  writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status rrc_a(struct Instruction* instruction) { registers.a = rrc(registers.a);  return INS_SUCCESS; }

/*0x10 - 0x17*/
ins_status rl_b(struct Instruction* instruction) { registers.b = rl(registers.b);  return INS_SUCCESS; }
ins_status rl_c(struct Instruction* instruction) { registers.c = rl(registers.c);  return INS_SUCCESS; }
ins_status rl_d(struct Instruction* instruction) { registers.d = rl(registers.d);  return INS_SUCCESS; }
ins_status rl_e(struct Instruction* instruction) { registers.e = rl(registers.e);  return INS_SUCCESS; }
ins_status rl_h(struct Instruction* instruction) { registers.h = rl(registers.h);  return INS_SUCCESS; }
ins_status rl_l(struct Instruction* instruction) { registers.l = rl(registers.l);  return INS_SUCCESS; }
ins_status rl_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = rl(byte);  writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status rl_a(struct Instruction* instruction) { registers.a = rl(registers.a);  return INS_SUCCESS; }

/*0x18 - 0x1f*/
ins_status rr_b(struct Instruction* instruction) { registers.b = rr(registers.b);  return INS_SUCCESS; }
ins_status rr_c(struct Instruction* instruction) { registers.c = rr(registers.c);  return INS_SUCCESS; }
ins_status rr_d(struct Instruction* instruction) { registers.d = rr(registers.d);  return INS_SUCCESS; }
ins_status rr_e(struct Instruction* instruction) { registers.e = rr(registers.e);  return INS_SUCCESS; }
ins_status rr_h(struct Instruction* instruction) { registers.h = rr(registers.h);  return INS_SUCCESS; }
ins_status rr_l(struct Instruction* instruction) { registers.l = rr(registers.l);  return INS_SUCCESS; }
ins_status rr_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = rr(byte);  writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status rr_a(struct Instruction* instruction) { registers.a = rr(registers.a);  return INS_SUCCESS; }

/*0x20 - 0x27*/
ins_status sla_b(struct Instruction* instruction) { registers.b = sla(registers.b);  return INS_SUCCESS; }
ins_status sla_c(struct Instruction* instruction) { registers.c = sla(registers.c);  return INS_SUCCESS; }
ins_status sla_d(struct Instruction* instruction) { registers.d = sla(registers.d);  return INS_SUCCESS; }
ins_status sla_e(struct Instruction* instruction) { registers.e = sla(registers.e);  return INS_SUCCESS; }
ins_status sla_h(struct Instruction* instruction) { registers.h = sla(registers.h);  return INS_SUCCESS; }
ins_status sla_l(struct Instruction* instruction) { registers.l = sla(registers.l);  return INS_SUCCESS; }
ins_status sla_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = sla(byte);  writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status sla_a(struct Instruction* instruction) { registers.a = sla(registers.a);  return INS_SUCCESS; }

/*0x28 - 0x2f*/
ins_status sra_b(struct Instruction* instruction) { registers.b = sra(registers.b);  return INS_SUCCESS; }
ins_status sra_c(struct Instruction* instruction) { registers.c = sra(registers.c);  return INS_SUCCESS; }
ins_status sra_d(struct Instruction* instruction) { registers.d = sra(registers.d);  return INS_SUCCESS; }
ins_status sra_e(struct Instruction* instruction) { registers.e = sra(registers.e);  return INS_SUCCESS; }
ins_status sra_h(struct Instruction* instruction) { registers.h = sra(registers.h);  return INS_SUCCESS; }
ins_status sra_l(struct Instruction* instruction) { registers.l = rrc(registers.l);  return INS_SUCCESS; }
ins_status sra_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = sra(byte);  writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status sra_a(struct Instruction* instruction) { registers.a = sra(registers.a);  return INS_SUCCESS; }

/*0x30 - 0x37*/
ins_status swap_b(struct Instruction* instruction) { registers.b = swap(registers.b);  return INS_SUCCESS; }
ins_status swap_c(struct Instruction* instruction) { registers.c = swap(registers.c);  return INS_SUCCESS; }
ins_status swap_d(struct Instruction* instruction) { registers.d = swap(registers.d);  return INS_SUCCESS; }
ins_status swap_e(struct Instruction* instruction) { registers.e = swap(registers.e);  return INS_SUCCESS; }
ins_status swap_h(struct Instruction* instruction) { registers.h = swap(registers.h);  return INS_SUCCESS; }
ins_status swap_l(struct Instruction* instruction) { registers.l = swap(registers.l);  return INS_SUCCESS; }
ins_status swap_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = swap(byte);  writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status swap_a(struct Instruction* instruction) { registers.a = swap(registers.a);  return INS_SUCCESS; }

/*0x38 - 0x3f*/
ins_status srl_b(struct Instruction* instruction) { registers.b = srl(registers.b);  return INS_SUCCESS; }
ins_status srl_c(struct Instruction* instruction) { registers.c = srl(registers.c);  return INS_SUCCESS; }
ins_status srl_d(struct Instruction* instruction) { registers.d = srl(registers.d);  return INS_SUCCESS; }
ins_status srl_e(struct Instruction* instruction) { registers.e = srl(registers.e);  return INS_SUCCESS; }
ins_status srl_h(struct Instruction* instruction) { registers.h = srl(registers.h);  return INS_SUCCESS; }
ins_status srl_l(struct Instruction* instruction) { registers.l = srl(registers.l);  return INS_SUCCESS; }
ins_status srl_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = srl(byte);  writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status srl_a(struct Instruction* instruction) { registers.a = srl(registers.a);  return INS_SUCCESS; }

/*0x40 - 0x7f*/
ins_status bit_0_b(struct Instruction* instruction) { bit(0, registers.b); return INS_SUCCESS; }
ins_status bit_0_c(struct Instruction* instruction) { bit(0, registers.c); return INS_SUCCESS; }
ins_status bit_0_d(struct Instruction* instruction) { bit(0, registers.d); return INS_SUCCESS; }
ins_status bit_0_e(struct Instruction* instruction) { bit(0, registers.e); return INS_SUCCESS; }
ins_status bit_0_h(struct Instruction* instruction) { bit(0, registers.h); return INS_SUCCESS; }
ins_status bit_0_l(struct Instruction* instruction) { bit(0, registers.l); return INS_SUCCESS; }
ins_status bit_0_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); bit(0, byte); return INS_SUCCESS; }
ins_status bit_0_a(struct Instruction* instruction) { bit(0, registers.a); return INS_SUCCESS; }

ins_status bit_1_b(struct Instruction* instruction) { bit(1, registers.b); return INS_SUCCESS; }
ins_status bit_1_c(struct Instruction* instruction) { bit(1, registers.c); return INS_SUCCESS; }
ins_status bit_1_d(struct Instruction* instruction) { bit(1, registers.d); return INS_SUCCESS; }
ins_status bit_1_e(struct Instruction* instruction) { bit(1, registers.e); return INS_SUCCESS; }
ins_status bit_1_h(struct Instruction* instruction) { bit(1, registers.h); return INS_SUCCESS; }
ins_status bit_1_l(struct Instruction* instruction) { bit(1, registers.l); return INS_SUCCESS; }
ins_status bit_1_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); bit(1, byte); return INS_SUCCESS; }
ins_status bit_1_a(struct Instruction* instruction) { bit(1, registers.a); return INS_SUCCESS; }

ins_status bit_2_b(struct Instruction* instruction) { bit(2, registers.b); return INS_SUCCESS; }
ins_status bit_2_c(struct Instruction* instruction) { bit(2, registers.c); return INS_SUCCESS; }
ins_status bit_2_d(struct Instruction* instruction) { bit(2, registers.d); return INS_SUCCESS; }
ins_status bit_2_e(struct Instruction* instruction) { bit(2, registers.e); return INS_SUCCESS; }
ins_status bit_2_h(struct Instruction* instruction) { bit(2, registers.h); return INS_SUCCESS; }
ins_status bit_2_l(struct Instruction* instruction) { bit(2, registers.l); return INS_SUCCESS; }
ins_status bit_2_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); bit(2, byte); return INS_SUCCESS; }
ins_status bit_2_a(struct Instruction* instruction) { bit(2, registers.a); return INS_SUCCESS; }

ins_status bit_3_b(struct Instruction* instruction) { bit(3, registers.b); return INS_SUCCESS; }
ins_status bit_3_c(struct Instruction* instruction) { bit(3, registers.c); return INS_SUCCESS; }
ins_status bit_3_d(struct Instruction* instruction) { bit(3, registers.d); return INS_SUCCESS; }
ins_status bit_3_e(struct Instruction* instruction) { bit(3, registers.e); return INS_SUCCESS; }
ins_status bit_3_h(struct Instruction* instruction) { bit(3, registers.h); return INS_SUCCESS; }
ins_status bit_3_l(struct Instruction* instruction) { bit(3, registers.l); return INS_SUCCESS; }
ins_status bit_3_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); bit(3, byte); return INS_SUCCESS; }
ins_status bit_3_a(struct Instruction* instruction) { bit(3, registers.a); return INS_SUCCESS; }

ins_status bit_4_b(struct Instruction* instruction) { bit(4, registers.b); return INS_SUCCESS; }
ins_status bit_4_c(struct Instruction* instruction) { bit(4, registers.c); return INS_SUCCESS; }
ins_status bit_4_d(struct Instruction* instruction) { bit(4, registers.d); return INS_SUCCESS; }
ins_status bit_4_e(struct Instruction* instruction) { bit(4, registers.e); return INS_SUCCESS; }
ins_status bit_4_h(struct Instruction* instruction) { bit(4, registers.h); return INS_SUCCESS; }
ins_status bit_4_l(struct Instruction* instruction) { bit(4, registers.l); return INS_SUCCESS; }
ins_status bit_4_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); bit(4, byte); return INS_SUCCESS; }
ins_status bit_4_a(struct Instruction* instruction) { bit(4, registers.a); return INS_SUCCESS; }

ins_status bit_5_b(struct Instruction* instruction) { bit(5, registers.b); return INS_SUCCESS; }
ins_status bit_5_c(struct Instruction* instruction) { bit(5, registers.c); return INS_SUCCESS; }
ins_status bit_5_d(struct Instruction* instruction) { bit(5, registers.d); return INS_SUCCESS; }
ins_status bit_5_e(struct Instruction* instruction) { bit(5, registers.e); return INS_SUCCESS; }
ins_status bit_5_h(struct Instruction* instruction) { bit(5, registers.h); return INS_SUCCESS; }
ins_status bit_5_l(struct Instruction* instruction) { bit(5, registers.l); return INS_SUCCESS; }
ins_status bit_5_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); bit(5, byte); return INS_SUCCESS; }
ins_status bit_5_a(struct Instruction* instruction) { bit(5, registers.a); return INS_SUCCESS; }

ins_status bit_6_b(struct Instruction* instruction) { bit(6, registers.b); return INS_SUCCESS; }
ins_status bit_6_c(struct Instruction* instruction) { bit(6, registers.c); return INS_SUCCESS; }
ins_status bit_6_d(struct Instruction* instruction) { bit(6, registers.d); return INS_SUCCESS; }
ins_status bit_6_e(struct Instruction* instruction) { bit(6, registers.e); return INS_SUCCESS; }
ins_status bit_6_h(struct Instruction* instruction) { bit(6, registers.h); return INS_SUCCESS; }
ins_status bit_6_l(struct Instruction* instruction) { bit(6, registers.l); return INS_SUCCESS; }
ins_status bit_6_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); bit(6, byte); return INS_SUCCESS; }
ins_status bit_6_a(struct Instruction* instruction) { bit(6, registers.a); return INS_SUCCESS; }

ins_status bit_7_b(struct Instruction* instruction) { bit(7, registers.b); return INS_SUCCESS; }
ins_status bit_7_c(struct Instruction* instruction) { bit(7, registers.c); return INS_SUCCESS; }
ins_status bit_7_d(struct Instruction* instruction) { bit(7, registers.d); return INS_SUCCESS; }
ins_status bit_7_e(struct Instruction* instruction) { bit(7, registers.e); return INS_SUCCESS; }
ins_status bit_7_h(struct Instruction* instruction) { bit(7, registers.h); return INS_SUCCESS; }
ins_status bit_7_l(struct Instruction* instruction) { bit(7, registers.l); return INS_SUCCESS; }
ins_status bit_7_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); bit(7, byte); return INS_SUCCESS; }
ins_status bit_7_a(struct Instruction* instruction) { bit(7, registers.a); return INS_SUCCESS; }

/*0x80 - 0xbf*/
ins_status res_0_b(struct Instruction* instruction) { registers.b = res(0, registers.b); return INS_SUCCESS; }
ins_status res_0_c(struct Instruction* instruction) { registers.b = res(0, registers.c); return INS_SUCCESS; }
ins_status res_0_d(struct Instruction* instruction) { registers.b = res(0, registers.d); return INS_SUCCESS; }
ins_status res_0_e(struct Instruction* instruction) { registers.b = res(0, registers.e); return INS_SUCCESS; }
ins_status res_0_h(struct Instruction* instruction) { registers.b = res(0, registers.h); return INS_SUCCESS; }
ins_status res_0_l(struct Instruction* instruction) { registers.b = res(0, registers.l); return INS_SUCCESS; }
ins_status res_0_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = res(0, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status res_0_a(struct Instruction* instruction) { registers.b = res(0, registers.a); return INS_SUCCESS; }

ins_status res_1_b(struct Instruction* instruction) { registers.b = res(1, registers.b); return INS_SUCCESS; }
ins_status res_1_c(struct Instruction* instruction) { registers.b = res(1, registers.c); return INS_SUCCESS; }
ins_status res_1_d(struct Instruction* instruction) { registers.b = res(1, registers.d); return INS_SUCCESS; }
ins_status res_1_e(struct Instruction* instruction) { registers.b = res(1, registers.e); return INS_SUCCESS; }
ins_status res_1_h(struct Instruction* instruction) { registers.b = res(1, registers.h); return INS_SUCCESS; }
ins_status res_1_l(struct Instruction* instruction) { registers.b = res(1, registers.l); return INS_SUCCESS; }
ins_status res_1_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = res(1, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status res_1_a(struct Instruction* instruction) { registers.b = res(1, registers.a); return INS_SUCCESS; }

ins_status res_2_b(struct Instruction* instruction) { registers.b = res(2, registers.b); return INS_SUCCESS; }
ins_status res_2_c(struct Instruction* instruction) { registers.b = res(2, registers.c); return INS_SUCCESS; }
ins_status res_2_d(struct Instruction* instruction) { registers.b = res(2, registers.d); return INS_SUCCESS; }
ins_status res_2_e(struct Instruction* instruction) { registers.b = res(2, registers.e); return INS_SUCCESS; }
ins_status res_2_h(struct Instruction* instruction) { registers.b = res(2, registers.h); return INS_SUCCESS; }
ins_status res_2_l(struct Instruction* instruction) { registers.b = res(2, registers.l); return INS_SUCCESS; }
ins_status res_2_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = res(2, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status res_2_a(struct Instruction* instruction) { registers.b = res(2, registers.a); return INS_SUCCESS; }

ins_status res_3_b(struct Instruction* instruction) { registers.b = res(3, registers.b); return INS_SUCCESS; }
ins_status res_3_c(struct Instruction* instruction) { registers.b = res(3, registers.c); return INS_SUCCESS; }
ins_status res_3_d(struct Instruction* instruction) { registers.b = res(3, registers.d); return INS_SUCCESS; }
ins_status res_3_e(struct Instruction* instruction) { registers.b = res(3, registers.e); return INS_SUCCESS; }
ins_status res_3_h(struct Instruction* instruction) { registers.b = res(3, registers.h); return INS_SUCCESS; }
ins_status res_3_l(struct Instruction* instruction) { registers.b = res(3, registers.l); return INS_SUCCESS; }
ins_status res_3_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = res(3, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status res_3_a(struct Instruction* instruction) { registers.b = res(3, registers.a); return INS_SUCCESS; }

ins_status res_4_b(struct Instruction* instruction) { registers.b = res(4, registers.b); return INS_SUCCESS; }
ins_status res_4_c(struct Instruction* instruction) { registers.b = res(4, registers.c); return INS_SUCCESS; }
ins_status res_4_d(struct Instruction* instruction) { registers.b = res(4, registers.d); return INS_SUCCESS; }
ins_status res_4_e(struct Instruction* instruction) { registers.b = res(4, registers.e); return INS_SUCCESS; }
ins_status res_4_h(struct Instruction* instruction) { registers.b = res(4, registers.h); return INS_SUCCESS; }
ins_status res_4_l(struct Instruction* instruction) { registers.b = res(4, registers.l); return INS_SUCCESS; }
ins_status res_4_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = res(4, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status res_4_a(struct Instruction* instruction) { registers.b = res(4, registers.a); return INS_SUCCESS; }

ins_status res_5_b(struct Instruction* instruction) { registers.b = res(5, registers.b); return INS_SUCCESS; }
ins_status res_5_c(struct Instruction* instruction) { registers.b = res(5, registers.c); return INS_SUCCESS; }
ins_status res_5_d(struct Instruction* instruction) { registers.b = res(5, registers.d); return INS_SUCCESS; }
ins_status res_5_e(struct Instruction* instruction) { registers.b = res(5, registers.e); return INS_SUCCESS; }
ins_status res_5_h(struct Instruction* instruction) { registers.b = res(5, registers.h); return INS_SUCCESS; }
ins_status res_5_l(struct Instruction* instruction) { registers.b = res(5, registers.l); return INS_SUCCESS; }
ins_status res_5_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = res(5, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status res_5_a(struct Instruction* instruction) { registers.b = res(5, registers.a); return INS_SUCCESS; }

ins_status res_6_b(struct Instruction* instruction) { registers.b = res(6, registers.b); return INS_SUCCESS; }
ins_status res_6_c(struct Instruction* instruction) { registers.b = res(6, registers.c); return INS_SUCCESS; }
ins_status res_6_d(struct Instruction* instruction) { registers.b = res(6, registers.d); return INS_SUCCESS; }
ins_status res_6_e(struct Instruction* instruction) { registers.b = res(6, registers.e); return INS_SUCCESS; }
ins_status res_6_h(struct Instruction* instruction) { registers.b = res(6, registers.h); return INS_SUCCESS; }
ins_status res_6_l(struct Instruction* instruction) { registers.b = res(6, registers.l); return INS_SUCCESS; }
ins_status res_6_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = res(6, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status res_6_a(struct Instruction* instruction) { registers.b = res(6, registers.a); return INS_SUCCESS; }

ins_status res_7_b(struct Instruction* instruction) { registers.b = res(7, registers.b); return INS_SUCCESS; }
ins_status res_7_c(struct Instruction* instruction) { registers.b = res(7, registers.c); return INS_SUCCESS; }
ins_status res_7_d(struct Instruction* instruction) { registers.b = res(7, registers.d); return INS_SUCCESS; }
ins_status res_7_e(struct Instruction* instruction) { registers.b = res(7, registers.e); return INS_SUCCESS; }
ins_status res_7_h(struct Instruction* instruction) { registers.b = res(7, registers.h); return INS_SUCCESS; }
ins_status res_7_l(struct Instruction* instruction) { registers.b = res(7, registers.l); return INS_SUCCESS; }
ins_status res_7_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = res(7, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status res_7_a(struct Instruction* instruction) { registers.b = res(7, registers.a); return INS_SUCCESS; }

/*0xc0 - 0xff*/
ins_status set_0_b(struct Instruction* instruction) { registers.b = set(0, registers.b); return INS_SUCCESS; }
ins_status set_0_c(struct Instruction* instruction) { registers.c = set(0, registers.c); return INS_SUCCESS; }
ins_status set_0_d(struct Instruction* instruction) { registers.d = set(0, registers.d); return INS_SUCCESS; }
ins_status set_0_e(struct Instruction* instruction) { registers.e = set(0, registers.e); return INS_SUCCESS; }
ins_status set_0_h(struct Instruction* instruction) { registers.h = set(0, registers.h); return INS_SUCCESS; }
ins_status set_0_l(struct Instruction* instruction) { registers.l = set(0, registers.l); return INS_SUCCESS; }
ins_status set_0_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = set(0, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status set_0_a(struct Instruction* instruction) { registers.a = set(0, registers.a); return INS_SUCCESS; }

ins_status set_1_b(struct Instruction* instruction) { registers.b = set(1, registers.b); return INS_SUCCESS; }
ins_status set_1_c(struct Instruction* instruction) { registers.c = set(1, registers.c); return INS_SUCCESS; }
ins_status set_1_d(struct Instruction* instruction) { registers.d = set(1, registers.d); return INS_SUCCESS; }
ins_status set_1_e(struct Instruction* instruction) { registers.e = set(1, registers.e); return INS_SUCCESS; }
ins_status set_1_h(struct Instruction* instruction) { registers.h = set(1, registers.h); return INS_SUCCESS; }
ins_status set_1_l(struct Instruction* instruction) { registers.l = set(1, registers.l); return INS_SUCCESS; }
ins_status set_1_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = set(1, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status set_1_a(struct Instruction* instruction) { registers.a = set(1, registers.a); return INS_SUCCESS; }

ins_status set_2_b(struct Instruction* instruction) { registers.b = set(2, registers.b); return INS_SUCCESS; }
ins_status set_2_c(struct Instruction* instruction) { registers.c = set(2, registers.c); return INS_SUCCESS; }
ins_status set_2_d(struct Instruction* instruction) { registers.d = set(2, registers.d); return INS_SUCCESS; }
ins_status set_2_e(struct Instruction* instruction) { registers.e = set(2, registers.e); return INS_SUCCESS; }
ins_status set_2_h(struct Instruction* instruction) { registers.h = set(2, registers.h); return INS_SUCCESS; }
ins_status set_2_l(struct Instruction* instruction) { registers.l = set(2, registers.l); return INS_SUCCESS; }
ins_status set_2_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = set(2, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status set_2_a(struct Instruction* instruction) { registers.a = set(2, registers.a); return INS_SUCCESS; }

ins_status set_3_b(struct Instruction* instruction) { registers.b = set(3, registers.b); return INS_SUCCESS; }
ins_status set_3_c(struct Instruction* instruction) { registers.c = set(3, registers.c); return INS_SUCCESS; }
ins_status set_3_d(struct Instruction* instruction) { registers.d = set(3, registers.d); return INS_SUCCESS; }
ins_status set_3_e(struct Instruction* instruction) { registers.e = set(3, registers.e); return INS_SUCCESS; }
ins_status set_3_h(struct Instruction* instruction) { registers.h = set(3, registers.h); return INS_SUCCESS; }
ins_status set_3_l(struct Instruction* instruction) { registers.l = set(3, registers.l); return INS_SUCCESS; }
ins_status set_3_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = set(3, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status set_3_a(struct Instruction* instruction) { registers.a = set(3, registers.a); return INS_SUCCESS; }

ins_status set_4_b(struct Instruction* instruction) { registers.b = set(4, registers.b); return INS_SUCCESS; }
ins_status set_4_c(struct Instruction* instruction) { registers.c = set(4, registers.c); return INS_SUCCESS; }
ins_status set_4_d(struct Instruction* instruction) { registers.d = set(4, registers.d); return INS_SUCCESS; }
ins_status set_4_e(struct Instruction* instruction) { registers.e = set(4, registers.e); return INS_SUCCESS; }
ins_status set_4_h(struct Instruction* instruction) { registers.h = set(4, registers.h); return INS_SUCCESS; }
ins_status set_4_l(struct Instruction* instruction) { registers.l = set(4, registers.l); return INS_SUCCESS; }
ins_status set_4_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = set(4, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status set_4_a(struct Instruction* instruction) { registers.a = set(4, registers.a); return INS_SUCCESS; }

ins_status set_5_b(struct Instruction* instruction) { registers.b = set(5, registers.b); return INS_SUCCESS; }
ins_status set_5_c(struct Instruction* instruction) { registers.c = set(5, registers.c); return INS_SUCCESS; }
ins_status set_5_d(struct Instruction* instruction) { registers.d = set(5, registers.d); return INS_SUCCESS; }
ins_status set_5_e(struct Instruction* instruction) { registers.e = set(5, registers.e); return INS_SUCCESS; }
ins_status set_5_h(struct Instruction* instruction) { registers.h = set(5, registers.h); return INS_SUCCESS; }
ins_status set_5_l(struct Instruction* instruction) { registers.l = set(5, registers.l); return INS_SUCCESS; }
ins_status set_5_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = set(5, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status set_5_a(struct Instruction* instruction) { registers.a = set(5, registers.a); return INS_SUCCESS; }

ins_status set_6_b(struct Instruction* instruction) { registers.b = set(6, registers.b); return INS_SUCCESS; }
ins_status set_6_c(struct Instruction* instruction) { registers.c = set(6, registers.c); return INS_SUCCESS; }
ins_status set_6_d(struct Instruction* instruction) { registers.d = set(6, registers.d); return INS_SUCCESS; }
ins_status set_6_e(struct Instruction* instruction) { registers.e = set(6, registers.e); return INS_SUCCESS; }
ins_status set_6_h(struct Instruction* instruction) { registers.h = set(6, registers.h); return INS_SUCCESS; }
ins_status set_6_l(struct Instruction* instruction) { registers.l = set(6, registers.l); return INS_SUCCESS; }
ins_status set_6_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = set(6, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status set_6_a(struct Instruction* instruction) { registers.a = set(6, registers.a); return INS_SUCCESS; }

ins_status set_7_b(struct Instruction* instruction) { registers.b = set(7, registers.b); return INS_SUCCESS; }
ins_status set_7_c(struct Instruction* instruction) { registers.c = set(7, registers.c); return INS_SUCCESS; }
ins_status set_7_d(struct Instruction* instruction) { registers.d = set(7, registers.d); return INS_SUCCESS; }
ins_status set_7_e(struct Instruction* instruction) { registers.e = set(7, registers.e); return INS_SUCCESS; }
ins_status set_7_h(struct Instruction* instruction) { registers.h = set(7, registers.h); return INS_SUCCESS; }
ins_status set_7_l(struct Instruction* instruction) { registers.l = set(7, registers.l); return INS_SUCCESS; }
ins_status set_7_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); byte = set(7, byte); writeByte(registers.hl, &byte); return INS_SUCCESS; }
ins_status set_7_a(struct Instruction* instruction) { registers.a = set(7, registers.a); return INS_SUCCESS; }
