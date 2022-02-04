#include "cb_instructions.h"
#include "arithmetics.h"
#include "interrupt.h"
#include "registers.h"
#include "memory.h"
#include "status.h"
#include "cpu.h"

void initiate_cpu(){
	cpu.t_edges = 0;
	cpu.t_cycles = 0;
	cpu.m_cycles = 0;
	cpu.halt = false;
	return;
}

void print_cycles(){
	printf("CPU cycles count: %llu\n", cpu.m_cycles);
}

void cpuStep(){
	if (!cpu.halt) {
		unsigned char byte;
		readByte(registers.pc, &byte);

		printf("Instruction: 0x%x\n", byte);
		print_registers();

		execute_instruction(&(instructions[byte]));
	}

	return;
}

void increment_cpu_cycles(unsigned long long m_cycles){
	cpu.m_cycles += m_cycles;
	cpu.t_cycles += m_cycles * (unsigned long long)T_CYCLE_MULTIPLY;
	cpu.t_edges += m_cycles * (unsigned long long)T_EDGE_MULTIPLY;
	return;
}

void execute_instruction(struct Instruction* instruction){
	ins_status status = instruction->action(instruction);
	increment_cpu_cycles(instruction->m_cycles);
	cpu.last_opcode_t_cycles = instruction->m_cycles * 4;
	if (INS_BRANCHED != status && INS_RETURNED != status && INS_CB_INSTRUCTION != status){
		registers.pc += instruction->length;
	}
	return;
}

unsigned char get_last_opcode_t_cycles() {
	return cpu.last_opcode_t_cycles;
}

unsigned long long get_t_cycles() {
	return cpu.t_cycles;
}

/*
	This function implements the functionality of the opcode 0x0.
*/
ins_status nop(struct Instruction* instruction){
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x1.
*/
ins_status ld_bc_u16(struct Instruction* instruction){
	unsigned short word;
	readShort(registers.pc + OPCODE_SIZE, &word);
	registers.bc = word;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x2.
*/
ins_status ld_bc_a(struct Instruction* instruction){
	unsigned char byte = registers.a;
	writeByte(registers.bc, &byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x3.
*/
ins_status inc_bc(struct Instruction* instruction) {
	registers.bc++;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x4.
*/
ins_status inc_b(struct Instruction* instruction) {
	registers.b = inc(registers.b);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x5.
*/
ins_status dec_b(struct Instruction* instruction) {
	registers.b = dec(registers.b);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x6.
*/
ins_status ld_b_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.b = byte;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x7.
*/
//Check if ZERO flag functionality is correct
ins_status rlca(struct Instruction* instruction) {
	unsigned char carry = (registers.a & 0b10000000) >> 7;
	if (carry) {
		set_flag(carry);
	}
	else {
		unset_flag(carry);
	}

	registers.a = registers.a << 1;

	/*
	if (registers.a == 0) {
		set_flag(ZERO);
	}
	else
	{
		unset_flag(ZERO);
	}
	*/

	unset_flag(ZERO);
	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);

	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x8.
*/
//Check if functionality is correct
ins_status ld_u16_sp(struct Instruction* instruction){
	unsigned short word;
	unsigned short stack_pointer = registers.sp;
	readShort(registers.pc + OPCODE_SIZE, &word);
	writeShort(word, &stack_pointer);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x9.
*/
ins_status add_hl_bc(struct Instruction* instruction) {
	registers.hl = add_2bytes(registers.hl, registers.bc);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xa.
*/
ins_status ld_a_bc(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.bc, &byte);
	registers.a = byte;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xb.
*/
ins_status dec_bc(struct Instruction* instruction) {
	registers.bc--;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xc.
*/
ins_status inc_c(struct Instruction* instruction) {
	registers.c = inc(registers.c);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xd.
*/
ins_status dec_c(struct Instruction* instruction) {
	registers.c = dec(registers.c);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xe.
*/
ins_status ld_c_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.c = byte;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xf.
*/
//Check if functionality is correct (Should flag change be after shift?)
ins_status rrca(struct Instruction* instruction) {
	unsigned char carry = registers.a & 0x01;
	if (carry) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	registers.a = registers.a >> 1;
	if (carry) {
		registers.a = registers.a | 0b10000000;
	}
	/*
	if (registers.a == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}
	*/

	unset_flag(ZERO);
	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);

	return INS_SUCCESS;
}

/*
	This function implements the functionality for the opcode 0x10
*/
//For now halts the cpu (Should check if correct)
ins_status stop(struct Instruction* instruction){
	cpu.halt = true;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x11.
*/
ins_status ld_de_u16(struct Instruction* instruction){
	unsigned short word;
	readShort(registers.pc + OPCODE_SIZE, &word);
	registers.de = word;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x12.
*/
ins_status ld_de_a(struct Instruction* instruction) {
	unsigned char byte = registers.a;
	writeByte(registers.de, &byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x13.
*/
ins_status inc_de(struct Instruction* instruction) {
	registers.de++;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x14.
*/
ins_status inc_d(struct Instruction* instruction) {
	registers.d = inc(registers.d);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x15.
*/
ins_status dec_d(struct Instruction* instruction) {
	registers.d = dec(registers.d);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x16.
*/
ins_status ld_d_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.d = byte;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x17.
*/
//Check if ZERO flag functionality is correct
ins_status rla(struct Instruction* instruction) {
	unsigned char carry_flag_value = get_flag(CARRY) ? 1 : 0;

	unsigned char carry = (registers.a & 0b10000000) >> 7;
	if (carry) {
		set_flag(carry);
	}
	else {
		unset_flag(carry);
	}

	registers.a = (registers.a << 1) + carry_flag_value;
		
	unset_flag(ZERO);
	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);

	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x18.
*/
ins_status jr_i8(struct Instruction* instruction){
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.pc = byte;
	return INS_BRANCHED;
}

/*
	This function implements the functionality of the opcode 0x19.
*/
ins_status add_hl_de(struct Instruction* instruction) {
	registers.hl = add_2bytes(registers.hl, registers.de);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x1a.
*/
ins_status ld_a_de(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.de, &byte);
	registers.a = byte;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x1b.
*/
ins_status dec_de(struct Instruction* instruction) {
	registers.de--;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x1c.
*/
ins_status inc_e(struct Instruction* instruction) {
	registers.e = inc(registers.e);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x1d.
*/
ins_status dec_e(struct Instruction* instruction) {
	registers.e = dec(registers.e);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x1e.
*/
ins_status ld_e_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.e = byte;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x1f.
*/
//Check if functionality is correct
ins_status rra(struct Instrution* instruction) {
	unsigned char carry_flag_value = (get_flag(CARRY) ? 1 : 0) << 7;
	unsigned char carry = registers.a & 0x01;
	if (carry) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	registers.a = registers.a >> 1;
	registers.a = registers.a + carry_flag_value;

	/*
	if (registers.a == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}
	*/

	unset_flag(ZERO);
	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);

	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x20
*/
ins_status jr_nz_i8(struct Instruction* instruction){
	if (get_flag(ZERO)) {
		increment_cpu_cycles(2);
		return INS_SUCCESS;
	}
	else {
		unsigned char byte;
		readByte(registers.pc + OPCODE_SIZE, &byte);
		registers.pc = byte;
		increment_cpu_cycles(3);
		return INS_BRANCHED;
	}
	
	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0x21.
*/
ins_status ld_hl_u16(struct Instruction* instruction) {
	unsigned short word;
	readShort(registers.pc + OPCODE_SIZE, &word);
	registers.hl = word;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x22.
*/
ins_status ld_hl_plus_a(struct Instruction* instruction) {
	unsigned char byte = registers.a;
	writeByte(registers.hl++, &byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x23.
*/
ins_status inc_hl(struct Instruction* instruction) {
	registers.hl++;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x24.
*/
ins_status inc_h(struct Instruction* instruction) {
	registers.h = inc(registers.h);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x25.
*/
ins_status dec_h(struct Instruction* instruction) {
	registers.h = dec(registers.h);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x26.
*/
ins_status ld_h_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.h = byte;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x27.
*/
//Check if this functionality is correct
ins_status daa(struct Instruction* instruction) {
	//After addition
	if (!get_flag(NEGATIVE)) {
		if (get_flag(CARRY) || registers.a > 0x99) {
			registers.a += 0x60;
			set_flag(CARRY);
		}
		if (get_flag(HALF_CARRY) || registers.a > 0x09) {
			registers.a += 0x06;
		}
	}
	//After Subtraction
	else {
		if (get_flag(CARRY)) {
			registers.a -= 0x60;
		}
		if (get_flag(HALF_CARRY)) {
			registers.a -= 0x06;
		}
	}

	if (registers.a == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	unset_flag(HALF_CARRY);

	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x28.
*/
ins_status jr_z_i8(struct Instruction* instruction){
	if (get_flag(ZERO)) {
		unsigned char byte;
		readByte(registers.pc + OPCODE_SIZE, &byte);
		registers.pc = byte;
		increment_cpu_cycles(3);
		return INS_BRANCHED;
	}
	else {
		increment_cpu_cycles(2);
		return INS_SUCCESS;
	}

	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0x29.
*/
ins_status add_hl_hl(struct Instruction* instruction) {
	registers.hl = add_2bytes(registers.hl, registers.hl);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x2a.
*/
ins_status ld_a_hl_plus(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.hl++, &byte);
	registers.a = byte;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x2b.
*/
ins_status dec_hl(struct Instruction* instruction) {
	registers.hl--;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x2c.
*/
ins_status inc_l(struct Instruction* instruction) {
	registers.l = inc(registers.l);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x2d.
*/
ins_status dec_l(struct Instruction* instruction) {
	registers.l = dec(registers.l);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x2e.
*/
ins_status ld_l_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.l = byte;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x2f.
*/
ins_status cpl(struct Instruction* instruction) {
	registers.a = ~registers.a;
	
	set_flag(NEGATIVE);
	set_flag(HALF_CARRY);

	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x30
*/
ins_status jr_nc_i8(struct Instruction* instruction) {
	if (get_flag(CARRY)) {
		increment_cpu_cycles(2);
		return INS_SUCCESS;
	}
	else {
		unsigned char byte;
		readByte(registers.pc + OPCODE_SIZE, &byte);
		registers.pc = byte;
		increment_cpu_cycles(3);
		return INS_BRANCHED;
	}

	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0x31.
*/
ins_status ld_sp_u16(struct Instruction* instruction) {
	unsigned short word;
	readShort(registers.pc + OPCODE_SIZE, &word);
	registers.sp = word;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x32.
*/
ins_status ld_hl_minus_a(struct Instruction* instruction) {
	unsigned char byte = registers.a;
	writeByte(registers.hl--, &byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x33.
*/
ins_status inc_sp(struct Instruction* instruction) {
	registers.sp++;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x34.
*/
ins_status inc__hl__(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.hl, &byte);
	byte = inc(byte);
	writeByte(registers.hl, &byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x35.
*/
ins_status dec__hl__(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.hl, &byte);
	byte = dec(byte);
	writeByte(registers.hl, &byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x36.
*/
ins_status ld_hl_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	writeByte(registers.hl, &byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x37.
*/
ins_status scf(struct Instruction* instruction) {
	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);
	set_flag(CARRY);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x38.
*/
ins_status jr_c_i8(struct Instruction* instruction){
	if (get_flag(CARRY)) {
		unsigned char byte;
		readByte(registers.pc + OPCODE_SIZE, &byte);
		registers.pc = byte;
		increment_cpu_cycles(3);
		return INS_BRANCHED;
	}
	else {
		increment_cpu_cycles(2);
		return INS_SUCCESS;
	}

	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0x39.
*/
ins_status add_hl_sp(struct Instruction* instruction) {
	registers.hl = add_2bytes(registers.hl, registers.sp);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x3a.
*/
ins_status ld_a_hl_minus(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.hl--, &byte);
	registers.a = byte;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x3b.
*/
ins_status dec_sp(struct Instruction* instruction) {
	registers.sp--;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x3c.
*/
ins_status inc_a(struct Instruction* instruction) {
	registers.a = inc(registers.a);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x3d.
*/
ins_status dec_a(struct Instruction* instruction) {
	registers.a = dec(registers.a);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x3e.
*/
ins_status ld_a_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.a = byte;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0x3f.
*/
ins_status ccf(struct Instruction* instruction) {
	if (get_flag(CARRY)) {
		unset_flag(CARRY);
	}
	else {
		set_flag(CARRY);
	}

	unset_flag(NEGATIVE);
	unset_flag(HALF_CARRY);

	return INS_SUCCESS;
}

ins_status ld_b_b(struct Instruction* instruction) { return INS_SUCCESS; } //0x40
ins_status ld_b_c(struct Instruction* instruction) { registers.b = registers.c; return INS_SUCCESS; } //0x41
ins_status ld_b_d(struct Instruction* instruction) { registers.b = registers.d; return INS_SUCCESS; } //0x42
ins_status ld_b_e(struct Instruction* instruction) { registers.b = registers.e; return INS_SUCCESS; } //0x43
ins_status ld_b_h(struct Instruction* instruction) { registers.b = registers.h; return INS_SUCCESS; } //0x44
ins_status ld_b_l(struct Instruction* instruction) { registers.b = registers.l; return INS_SUCCESS; } //0x45
ins_status ld_b_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.b = byte; return INS_SUCCESS; } //0x46
ins_status ld_b_a(struct Instruction* instruction) { registers.b = registers.a; return INS_SUCCESS; } //0x47

ins_status ld_c_b(struct Instruction* instruction) { registers.c = registers.b; return INS_SUCCESS; } //0x48
ins_status ld_c_c(struct Instruction* instruction) { return INS_SUCCESS; } //0x49
ins_status ld_c_d(struct Instruction* instruction) { registers.c = registers.d; return INS_SUCCESS; } //0x4a
ins_status ld_c_e(struct Instruction* instruction) { registers.c = registers.e; return INS_SUCCESS; } //0x4b
ins_status ld_c_h(struct Instruction* instruction) { registers.c = registers.h; return INS_SUCCESS; } //0x4c
ins_status ld_c_l(struct Instruction* instruction) { registers.c = registers.l; return INS_SUCCESS; } //0x4d
ins_status ld_c_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.c = byte; return INS_SUCCESS; } //0x4e
ins_status ld_c_a(struct Instruction* instruction) { registers.c = registers.a; return INS_SUCCESS; } //0x4f

ins_status ld_d_b(struct Instruction* instruction) { registers.d = registers.b; return INS_SUCCESS; } //0x50
ins_status ld_d_c(struct Instruction* instruction) { registers.d = registers.c; return INS_SUCCESS; } //0x51
ins_status ld_d_d(struct Instruction* instruction) { return INS_SUCCESS; } //0x52
ins_status ld_d_e(struct Instruction* instruction) { registers.d = registers.e; return INS_SUCCESS; } //0x53
ins_status ld_d_h(struct Instruction* instruction) { registers.d = registers.h; return INS_SUCCESS; } //0x54
ins_status ld_d_l(struct Instruction* instruction) { registers.d = registers.l; return INS_SUCCESS; } //0x55
ins_status ld_d_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.d = byte; return INS_SUCCESS; } //0x56
ins_status ld_d_a(struct Instruction* instruction) { registers.d = registers.a; return INS_SUCCESS; } //0x57

ins_status ld_e_b(struct Instruction* instruction) { registers.e = registers.b; return INS_SUCCESS; } //0x58
ins_status ld_e_c(struct Instruction* instruction) { registers.e = registers.c; return INS_SUCCESS; } //0x59
ins_status ld_e_d(struct Instruction* instruction) { registers.e = registers.d; return INS_SUCCESS; } //0x5a
ins_status ld_e_e(struct Instruction* instruction) { return INS_SUCCESS; } //0x5b
ins_status ld_e_h(struct Instruction* instruction) { registers.e = registers.h; return INS_SUCCESS; } //0x5c
ins_status ld_e_l(struct Instruction* instruction) { registers.e = registers.l; return INS_SUCCESS; } //0x5d
ins_status ld_e_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.e = byte; return INS_SUCCESS; } //0x5e
ins_status ld_e_a(struct Instruction* instruction) { registers.e = registers.a; return INS_SUCCESS; } //0x5f

ins_status ld_h_b(struct Instruction* instruction) { registers.h = registers.b; return INS_SUCCESS; } //0x60
ins_status ld_h_c(struct Instruction* instruction) { registers.h = registers.c; return INS_SUCCESS; } //0x61
ins_status ld_h_d(struct Instruction* instruction) { registers.h = registers.d; return INS_SUCCESS; } //0x62
ins_status ld_h_e(struct Instruction* instruction) { registers.h = registers.e; return INS_SUCCESS; } //0x63
ins_status ld_h_h(struct Instruction* instruction) { return INS_SUCCESS; } //0x64
ins_status ld_h_l(struct Instruction* instruction) { registers.h = registers.l; return INS_SUCCESS; } //0x65
ins_status ld_h_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.h = byte; return INS_SUCCESS; } //0x66
ins_status ld_h_a(struct Instruction* instruction) { registers.h = registers.a; return INS_SUCCESS; } //0x67

ins_status ld_l_b(struct Instruction* instruction) { registers.l = registers.b; return INS_SUCCESS; } //0x68
ins_status ld_l_c(struct Instruction* instruction) { registers.l = registers.c; return INS_SUCCESS; } //0x69
ins_status ld_l_d(struct Instruction* instruction) { registers.l = registers.d; return INS_SUCCESS; } //0x6a
ins_status ld_l_e(struct Instruction* instruction) { registers.l = registers.e; return INS_SUCCESS; } //0x6b
ins_status ld_l_h(struct Instruction* instruction) { registers.l = registers.h; return INS_SUCCESS; } //0x6c
ins_status ld_l_l(struct Instruction* instruction) { return INS_SUCCESS; } //0x6d
ins_status ld_l_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.l = byte; return INS_SUCCESS; } //0x6e
ins_status ld_l_a(struct Instruction* instruction) { registers.l = registers.a; return INS_SUCCESS; } //0x6f

ins_status ld_hl_b(struct Instruction* instruction) { unsigned char byte = registers.b; writeByte(registers.hl, &byte); return INS_SUCCESS; } //0x70
ins_status ld_hl_c(struct Instruction* instruction) { unsigned char byte = registers.c; writeByte(registers.hl, &byte); return INS_SUCCESS; } //0x71
ins_status ld_hl_d(struct Instruction* instruction) { unsigned char byte = registers.d; writeByte(registers.hl, &byte); return INS_SUCCESS; } //0x72
ins_status ld_hl_e(struct Instruction* instruction) { unsigned char byte = registers.e; writeByte(registers.hl, &byte); return INS_SUCCESS;; } //0x73
ins_status ld_hl_h(struct Instruction* instruction) { unsigned char byte = registers.h; writeByte(registers.hl, &byte); return INS_SUCCESS; } //0x74
ins_status ld_hl_l(struct Instruction* instruction) { unsigned char byte = registers.l; writeByte(registers.hl, &byte); return INS_SUCCESS; } //0x75

/*
	This function implements the functionality of the opcode 0x76
*/
//Check if "halt bug" is needed to implement
ins_status halt(struct Instruction* instruction) {
	cpu.halt = true;
	return INS_SUCCESS;
}

ins_status ld_hl_a(struct Instruction* instruction) { unsigned char byte = registers.a; writeByte(registers.hl, &byte); return INS_SUCCESS; } //0x77

ins_status ld_a_b(struct Instruction* instruction) { registers.a = registers.b; return INS_SUCCESS; } //0x78
ins_status ld_a_c(struct Instruction* instruction) { registers.a = registers.c; return INS_SUCCESS; } //0x79
ins_status ld_a_d(struct Instruction* instruction) { registers.a = registers.d; return INS_SUCCESS; } //0x7a
ins_status ld_a_e(struct Instruction* instruction) { registers.a = registers.e; return INS_SUCCESS; } //0x7b
ins_status ld_a_h(struct Instruction* instruction) { registers.a = registers.h; return INS_SUCCESS; } //0x7c
ins_status ld_a_l(struct Instruction* instruction) { registers.a = registers.l; return INS_SUCCESS; } //0x7d
ins_status ld_a_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.a = byte; return INS_SUCCESS; } //0x7e
ins_status ld_a_a(struct Instruction* instruction) { return INS_SUCCESS; } //0x7f


ins_status add_a_b(struct Instruction* instruction) { registers.a = add_byte(registers.a, registers.b); return INS_SUCCESS; } //0x80
ins_status add_a_c(struct Instruction* instruction) { registers.a = add_byte(registers.a, registers.c); return INS_SUCCESS; } //0x81
ins_status add_a_d(struct Instruction* instruction) { registers.a = add_byte(registers.a, registers.d); return INS_SUCCESS; } //0x82
ins_status add_a_e(struct Instruction* instruction) { registers.a = add_byte(registers.a, registers.e); return INS_SUCCESS; } //0x83
ins_status add_a_h(struct Instruction* instruction) { registers.a = add_byte(registers.a, registers.h); return INS_SUCCESS; } //0x84
ins_status add_a_l(struct Instruction* instruction) { registers.a = add_byte(registers.a, registers.l); return INS_SUCCESS; } //0x85
ins_status add_a_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.a = add_byte(registers.a, byte); return INS_SUCCESS; } //0x86
ins_status add_a_a(struct Instruction* instruction) { registers.a = add_byte(registers.a, registers.a); return INS_SUCCESS; } //0x87

ins_status adc_a_b(struct Instruction* instruction) { registers.a = adc(registers.a, registers.b); return INS_SUCCESS; } //0x88
ins_status adc_a_c(struct Instruction* instruction) { registers.a = adc(registers.a, registers.c); return INS_SUCCESS; } //0x89
ins_status adc_a_d(struct Instruction* instruction) { registers.a = adc(registers.a, registers.d); return INS_SUCCESS; } //0x8a
ins_status adc_a_e(struct Instruction* instruction) { registers.a = adc(registers.a, registers.e); return INS_SUCCESS; } //0x8b
ins_status adc_a_h(struct Instruction* instruction) { registers.a = adc(registers.a, registers.h); return INS_SUCCESS; } //0x8c
ins_status adc_a_l(struct Instruction* instruction) { registers.a = adc(registers.a, registers.l); return INS_SUCCESS; } //0x8d
ins_status adc_a_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.a = adc(registers.a, byte); return INS_SUCCESS; } //0x8e
ins_status adc_a_a(struct Instruction* instruction) { registers.a = adc(registers.a, registers.a); return INS_SUCCESS; } //0x8f

ins_status sub_a_b(struct Instruction* instruction) { registers.a = sub(registers.a, registers.b); return INS_SUCCESS; } //0x90
ins_status sub_a_c(struct Instruction* instruction) { registers.a = sub(registers.a, registers.c); return INS_SUCCESS; } //0x91
ins_status sub_a_d(struct Instruction* instruction) { registers.a = sub(registers.a, registers.d); return INS_SUCCESS; } //0x92
ins_status sub_a_e(struct Instruction* instruction) { registers.a = sub(registers.a, registers.e); return INS_SUCCESS; } //0x93
ins_status sub_a_h(struct Instruction* instruction) { registers.a = sub(registers.a, registers.h); return INS_SUCCESS; } //0x94
ins_status sub_a_l(struct Instruction* instruction) { registers.a = sub(registers.a, registers.l); return INS_SUCCESS; } //0x95
ins_status sub_a_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.a = sub(registers.a, byte); return INS_SUCCESS; } //0x96
ins_status sub_a_a(struct Instruction* instruction) { registers.a = sub(registers.a, registers.a); return INS_SUCCESS; } //0x97

ins_status sbc_a_b(struct Instruction* instruction) { registers.a = sbc(registers.a, registers.b); return INS_SUCCESS; } //0x98
ins_status sbc_a_c(struct Instruction* instruction) { registers.a = sbc(registers.a, registers.c); return INS_SUCCESS; } //0x99
ins_status sbc_a_d(struct Instruction* instruction) { registers.a = sbc(registers.a, registers.d); return INS_SUCCESS; } //0x9a
ins_status sbc_a_e(struct Instruction* instruction) { registers.a = sbc(registers.a, registers.e); return INS_SUCCESS; } //0x9b
ins_status sbc_a_h(struct Instruction* instruction) { registers.a = sbc(registers.a, registers.h); return INS_SUCCESS; } //0x9c
ins_status sbc_a_l(struct Instruction* instruction) { registers.a = sbc(registers.a, registers.l); return INS_SUCCESS; } //0x9d
ins_status sbc_a_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.a = sbc(registers.a, byte); return INS_SUCCESS; } //0x9e
ins_status sbc_a_a(struct Instruction* instruction) { registers.a = sbc(registers.a, registers.a); return INS_SUCCESS; } //0x9f

ins_status and_a_b(struct Instruction* instruction) { registers.a = AND(registers.a, registers.b); return INS_SUCCESS; } //0xa0
ins_status and_a_c(struct Instruction* instruction) { registers.a = AND(registers.a, registers.c); return INS_SUCCESS; } //0xa1
ins_status and_a_d(struct Instruction* instruction) { registers.a = AND(registers.a, registers.d); return INS_SUCCESS; } //0xa2
ins_status and_a_e(struct Instruction* instruction) { registers.a = AND(registers.a, registers.e); return INS_SUCCESS; } //0xa3
ins_status and_a_h(struct Instruction* instruction) { registers.a = AND(registers.a, registers.h); return INS_SUCCESS; } //0xa4
ins_status and_a_l(struct Instruction* instruction) { registers.a = AND(registers.a, registers.l); return INS_SUCCESS; } //0xa5
ins_status and_a_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.a = AND(registers.a, byte); return INS_SUCCESS; } //0xa6
ins_status and_a_a(struct Instruction* instruction) { registers.a = AND(registers.a, registers.a); return INS_SUCCESS; } //0xa7

ins_status xor_a_b(struct Instruction* instruction) { registers.a = XOR(registers.a, registers.b); return INS_SUCCESS; } //0xa8
ins_status xor_a_c(struct Instruction* instruction) { registers.a = XOR(registers.a, registers.c); return INS_SUCCESS; } //0xa9
ins_status xor_a_d(struct Instruction* instruction) { registers.a = XOR(registers.a, registers.d); return INS_SUCCESS; } //0xaa
ins_status xor_a_e(struct Instruction* instruction) { registers.a = XOR(registers.a, registers.e); return INS_SUCCESS; } //0xab
ins_status xor_a_h(struct Instruction* instruction) { registers.a = XOR(registers.a, registers.h); return INS_SUCCESS; } //0xac
ins_status xor_a_l(struct Instruction* instruction) { registers.a = XOR(registers.a, registers.l); return INS_SUCCESS; } //0xad
ins_status xor_a_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.a = XOR(registers.a, byte); return INS_SUCCESS; } //0xae
ins_status xor_a_a(struct Instruction* instruction) { registers.a = XOR(registers.a, registers.a); return INS_SUCCESS; } //0xaf

ins_status or_a_b(struct Instruction* instruction) { registers.a = OR(registers.a, registers.b); return INS_SUCCESS; } //0xb0
ins_status or_a_c(struct Instruction* instruction) { registers.a = OR(registers.a, registers.c); return INS_SUCCESS; } //0xb1
ins_status or_a_d(struct Instruction* instruction) { registers.a = OR(registers.a, registers.d); return INS_SUCCESS; } //0xb2
ins_status or_a_e(struct Instruction* instruction) { registers.a = OR(registers.a, registers.e); return INS_SUCCESS; } //0xb3
ins_status or_a_h(struct Instruction* instruction) { registers.a = OR(registers.a, registers.h); return INS_SUCCESS; } //0xb4
ins_status or_a_l(struct Instruction* instruction) { registers.a = OR(registers.a, registers.l); return INS_SUCCESS; } //0xb5
ins_status or_a_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); registers.a = OR(registers.a, byte); return INS_SUCCESS; } //0xb6
ins_status or_a_a(struct Instruction* instruction) { registers.a = OR(registers.a, registers.a); return INS_SUCCESS; } //0xb7

ins_status cp_a_b(struct Instruction* instruction) { compare(registers.a, registers.b); return INS_SUCCESS; } //0xb8
ins_status cp_a_c(struct Instruction* instruction) { compare(registers.a, registers.c); return INS_SUCCESS; } //0xb9
ins_status cp_a_d(struct Instruction* instruction) { compare(registers.a, registers.d); return INS_SUCCESS; } //0xba
ins_status cp_a_e(struct Instruction* instruction) { compare(registers.a, registers.e); return INS_SUCCESS; } //0xbb
ins_status cp_a_h(struct Instruction* instruction) { compare(registers.a, registers.h); return INS_SUCCESS; } //0xbc
ins_status cp_a_l(struct Instruction* instruction) { compare(registers.a, registers.l); return INS_SUCCESS; } //0xbd
ins_status cp_a_hl(struct Instruction* instruction) { unsigned char byte; readByte(registers.hl, &byte); compare(registers.a, byte); return INS_SUCCESS; } //0xbe
ins_status cp_a_a(struct Instruction* instruction) { compare(registers.a, registers.a); return INS_SUCCESS; } //0xbf

/*
	This function implements the functionality of the opcode 0xc0
*/
ins_status ret_nz(struct Instruction* instruction){
	if (get_flag(ZERO)) {
		increment_cpu_cycles(2);
		return INS_SUCCESS;
	}
	else {
		unsigned short previous_pc = 0x0;
		popStack(&previous_pc);
		registers.pc = previous_pc;
		increment_cpu_cycles(5);
		return INS_RETURNED;
	}
	
	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0xc1
*/
ins_status pop_bc(struct Instruction* instruction){
	unsigned short word;
	popStack(&word);
	registers.bc = word;
	return INS_SUCCESS;
}

/*
	This function implements the funcionality of the opcode 0xc2
*/
ins_status jp_nz_u16(struct Instruction* instruction){
	if (get_flag(ZERO)) {
		increment_cpu_cycles(3);
		return INS_SUCCESS;
	}
	else {
		unsigned short word;
		readShort(registers.pc + OPCODE_SIZE, &word);
		registers.pc = word;
		increment_cpu_cycles(4);
		return INS_BRANCHED;
	}

	return INS_ERROR;
}

/*
	This function implements the funcionality of the opcode 0xc3
*/
ins_status jp_u16(struct Instruction* instruction) {
	unsigned short word;
	readShort(registers.pc + OPCODE_SIZE, &word);
	registers.pc = word;
	return INS_BRANCHED;
}

/*
	This function implements the functionality of the opcode 0xc4
*/
ins_status call_nz_u16(struct Instruction* instruction){
	if (get_flag(ZERO)) {
		increment_cpu_cycles(3);
		return INS_SUCCESS;
	}
	else {
		unsigned short word;
		readShort(registers.pc + OPCODE_SIZE, &word);
		pushStack(registers.pc + instruction->length);
		registers.pc = word;
		increment_cpu_cycles(6);
		return INS_BRANCHED;
	}

	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0xc5
*/
ins_status push_bc(struct Instruction* instruction){
	unsigned short word = registers.bc;
	pushStack(&word);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xc6
*/
ins_status add_a_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.a = add_byte(registers.a, byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xc7
*/
ins_status rst_00(struct Instruction* instruction){
	pushStack(registers.pc + instruction->length);
	registers.pc = RST_00_ADDRESS;
	return INS_BRANCHED;
}

/*
	This function implements the functionality of the opcode 0xc8
*/
ins_status ret_z(struct Instruction* instruction) {
	if (get_flag(ZERO)) {
		unsigned short previous_pc = 0x0;
		popStack(&previous_pc);
		registers.pc = previous_pc;
		increment_cpu_cycles(5);
		return INS_RETURNED;
	}
	else {
		increment_cpu_cycles(2);
		return INS_SUCCESS;
	}

	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0xc9
*/
ins_status ret(struct Instruction* instruction) {
	unsigned short previous_pc = 0x0; //Check if initialization to value 0x0 is valid
	popStack(&previous_pc);
	registers.pc = previous_pc;
	return INS_RETURNED;
}

/*
	This function implements the funcionality of the opcode 0xca
*/
ins_status jp_z_u16(struct Instruction* instruction) {
	if (get_flag(ZERO)) {
		unsigned short word;
		readShort(registers.pc + OPCODE_SIZE, &word);
		registers.pc = word;
		increment_cpu_cycles(4);
		return INS_BRANCHED;
	}
	else {
		increment_cpu_cycles(3);
		return INS_SUCCESS;
	}

	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0xcb
*/
ins_status prefix_cb(struct Instruction* instruction){
	struct Instruction* cb_instruction = NULL;
	unsigned char cb_instruction_type;

	readByte(registers.pc + OPCODE_SIZE, &cb_instruction_type);
	cb_instruction = &(cb_instructions[cb_instruction_type]);

	registers.pc = registers.pc + instruction->length;
	execute_instruction(cb_instruction);

	return INS_CB_INSTRUCTION;
}

/*
	This function implements the functionality of the opcode 0xcc
*/
ins_status call_z_u16(struct Instruction* instruction) {
	if (get_flag(ZERO)) {
		unsigned short word;
		readShort(registers.pc + OPCODE_SIZE, &word);
		pushStack(registers.pc + instruction->length);
		registers.pc = word;
		increment_cpu_cycles(6);
		return INS_BRANCHED;
	}
	else {
		increment_cpu_cycles(3);
		return INS_SUCCESS;
	}

	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0xcd
*/
ins_status call_u16(struct Instruction* instruction) {
	unsigned short word;
	readShort(registers.pc + OPCODE_SIZE, &word);
	pushStack(registers.pc + instruction->length);
	registers.pc = word;
	return INS_BRANCHED;
}

/*
	This function implements the functionality of the opcode 0xce
*/
ins_status adc_a_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.a = adc(registers.a, byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xcf
*/
ins_status rst_08(struct Instruction* instruction) {
	pushStack(registers.pc + instruction->length);
	registers.pc = RST_08_ADDRESS;
	return INS_BRANCHED;
}

/*
	This function implements the functionality of the opcode 0xd0
*/
ins_status ret_nc(struct Instruction* instruction) {
	if (get_flag(CARRY)) {
		increment_cpu_cycles(2);
		return INS_SUCCESS;
	}
	else {
		unsigned short previous_pc = 0x0;
		popStack(&previous_pc);
		registers.pc = previous_pc;
		increment_cpu_cycles(5);
		return INS_RETURNED;
	}

	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0xd1
*/
ins_status pop_de(struct Instruction* instruction) {
	unsigned short word;
	popStack(&word);
	registers.de = word;
	return INS_SUCCESS;
}

/*
	This function implements the funcionality of the opcode 0xd2
*/
ins_status jp_nc_u16(struct Instruction* instruction) {
	if (get_flag(CARRY)) {
		increment_cpu_cycles(3);
		return INS_SUCCESS;
	}
	else {
		unsigned short word;
		readShort(registers.pc + OPCODE_SIZE, &word);
		registers.pc = word;
		increment_cpu_cycles(4);
		return INS_BRANCHED;
	}

	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0xd4
*/
ins_status call_nc_u16(struct Instruction* instruction) {
	if (get_flag(CARRY)) {
		increment_cpu_cycles(3);
		return INS_SUCCESS;
	}
	else {
		unsigned short word;
		readShort(registers.pc + OPCODE_SIZE, &word);
		pushStack(registers.pc + instruction->length);
		registers.pc = word;
		increment_cpu_cycles(6);
		return INS_BRANCHED;
	}

	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0xd5
*/
ins_status push_de(struct Instruction* instruction) {
	unsigned short word = registers.de;
	pushStack(&word);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xd6
*/
ins_status sub_a_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.a = sub(registers.a, byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xd7
*/
ins_status rst_10(struct Instruction* instruction) {
	pushStack(registers.pc + instruction->length);
	registers.pc = RST_10_ADDRESS;
	return INS_BRANCHED;
}

/*
	This function implements the functionality of the opcode 0xd8
*/
ins_status ret_c(struct Instruction* instruction) {
	if (get_flag(CARRY)) {
		unsigned short previous_pc = 0x0;
		popStack(&previous_pc);
		registers.pc = previous_pc;
		increment_cpu_cycles(5);
		return INS_RETURNED;
	}
	else {
		increment_cpu_cycles(2);
		return INS_SUCCESS;
	}

	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0xd9
*/
ins_status reti(struct Instruction* instruction){
	unsigned short previous_pc = 0x0; //Check if initialization to value 0x0 is valid
	popStack(&previous_pc);
	registers.pc = previous_pc;
	interrupts.interrupt_master_enable_flag = true;
	return INS_RETURNED;
}

/*
	This function implements the funcionality of the opcode 0xda
*/
ins_status jp_c_u16(struct Instruction* instruction) {
	if (get_flag(CARRY)) {
		unsigned short word;
		readShort(registers.pc + OPCODE_SIZE, &word);
		registers.pc = word;
		increment_cpu_cycles(4);
		return INS_BRANCHED;
	}
	else {
		increment_cpu_cycles(3);
		return INS_SUCCESS;
	}

	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0xdc
*/
ins_status call_c_u16(struct Instruction* instruction) {
	if (get_flag(CARRY)) {
		unsigned short word;
		readShort(registers.pc + OPCODE_SIZE, &word);
		pushStack(registers.pc + instruction->length);
		registers.pc = word;
		increment_cpu_cycles(6);
		return INS_BRANCHED;
	}
	else {
		increment_cpu_cycles(3);
		return INS_SUCCESS;
	}

	return INS_ERROR;
}

/*
	This function implements the functionality of the opcode 0xde
*/
ins_status sbc_a_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.a = sbc(registers.a, byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xdf
*/
ins_status rst_18(struct Instruction* instruction) {
	pushStack(registers.pc + instruction->length);
	registers.pc = RST_18_ADDRESS;
	return INS_BRANCHED;
}

/*
	This function implements the functionality of the opcode 0xe1
*/
ins_status pop_hl(struct Instruction* instruction) {
	unsigned short word;
	popStack(&word);
	registers.hl = word;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xe5
*/
ins_status push_hl(struct Instruction* instruction) {
	unsigned short word = registers.hl;
	pushStack(&word);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xe6
*/
ins_status and_a_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.a = AND(registers.a, byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xe7
*/
ins_status rst_20(struct Instruction* instruction) {
	pushStack(registers.pc + instruction->length);
	registers.pc = RST_20_ADDRESS;
	return INS_BRANCHED;
}

/*
	This function implements the functionality of the opcode 0xe8.
*/
//Check Implementation
ins_status add_sp_i8(struct Instruction* instruction) {
	unsigned char unsigned_byte;
	readByte(registers.pc + OPCODE_SIZE, &unsigned_byte);
	signed char signed_byte = (signed char)unsigned_byte;
	
	int result = registers.sp + signed_byte;

	if ((registers.sp & 0xf) + (signed_byte & 0xf) > 0xf) {
		set_flag(HALF_CARRY);
	}
	else{
		unset_flag(HALF_CARRY);
	}

	if((result & 0xffff0000)){
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	unset_flag(ZERO);
	unset_flag(NEGATIVE);

	registers.sp = (unsigned short)(result & 0xffff);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xe9
*/
ins_status jp_hl(struct Instruction* instruction){
	registers.pc = registers.hl;
	return INS_BRANCHED;
}

/*
	This function implements the functionality of the opcode 0xea.
*/
ins_status ld_u16_a(struct Instruction* instruction) {
	unsigned short word;
	readShort(registers.pc + OPCODE_SIZE, &word);
	writeByte(word, &registers.a);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xee
*/
ins_status xor_a_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.a = XOR(registers.a, byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xef
*/
ins_status rst_28(struct Instruction* instruction) {
	pushStack(registers.pc + instruction->length);
	registers.pc = RST_28_ADDRESS;
	return INS_BRANCHED;
}

/*
	This function implements the functionality of the opcode 0xf1
*/
ins_status pop_af(struct Instruction* instruction) {
	unsigned short word;
	popStack(&word);
	registers.af = word;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of opcode 0xf3
*/
ins_status di(struct Instruction* instruction){
	interrupts.interrupt_master_enable_flag = 0x0;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xf5
*/
ins_status push_af(struct Instruction* instruction) {
	unsigned short word = registers.af;
	pushStack(&word);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xf6
*/
ins_status or_a_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	registers.a = OR(registers.a, byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xf7
*/
ins_status rst_30(struct Instruction* instruction) {
	pushStack(registers.pc + instruction->length);
	registers.pc = RST_30_ADDRESS;
	return INS_BRANCHED;
}

/*
	This function implements the functionality of the opcode 0xf8.
*/
//Check Implementation
ins_status ld_hl_sp_plus_i8(struct Instruction* instruction) {
	unsigned char unsigned_byte;
	readByte(registers.pc + OPCODE_SIZE, &unsigned_byte);
	signed char signed_byte = (signed char)unsigned_byte;

	int result = registers.sp + signed_byte;

	if ((registers.sp & 0xf) + (signed_byte & 0xf) > 0xf) {
		set_flag(HALF_CARRY);
	}
	else {
		unset_flag(HALF_CARRY);
	}

	if ((result & 0xffff0000)) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	unset_flag(ZERO);
	unset_flag(NEGATIVE);

	registers.sp = (unsigned short)(result & 0xffff);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xf9.
*/
ins_status ld_sp_hl(struct Instruction* instruction) {
	unsigned short hl_register = registers.hl;
	registers.sp = hl_register;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xfa.
*/
ins_status ld_a_u16(struct Instruction* instruction) {
	unsigned char byte;
	unsigned short word;
	readShort(registers.pc + OPCODE_SIZE, &word);
	readByte(word, &byte);
	registers.a = byte;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of opcode 0xfb
*/
//The effect of ei() is delayed by one instruction. That means that ei followed immediately by di() does not allow any interrupts between them. IMPLEMENT.
ins_status ei(struct Instruction* instruction){
	interrupts.interrupt_master_enable_flag = 0x1;
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xfe
*/
ins_status cp_a_u8(struct Instruction* instruction) {
	unsigned char byte;
	readByte(registers.pc + OPCODE_SIZE, &byte);
	compare(registers.a, byte);
	return INS_SUCCESS;
}

/*
	This function implements the functionality of the opcode 0xff
*/
ins_status rst_38(struct Instruction* instruction) {
	unsigned short value = registers.pc + instruction->length;
	pushStack(&value);
	registers.pc = RST_38_ADDRESS;
	return INS_BRANCHED;
}
