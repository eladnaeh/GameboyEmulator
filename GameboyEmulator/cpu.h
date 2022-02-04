#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "status.h"

#define OPCODE_SIZE (1) //Defines OPCODE size in bytes
#define INSTRUCTIONS_AMOUNT (256)

#define T_CYCLE_MULTIPLY (4)
#define T_EDGE_MULTIPLY (8)

#define RST_00_ADDRESS (0x0000)
#define RST_08_ADDRESS (0x0008)
#define RST_10_ADDRESS (0x0010)
#define RST_18_ADDRESS (0x0018)
#define RST_20_ADDRESS (0x0020)
#define RST_28_ADDRESS (0x0028)
#define RST_30_ADDRESS (0x0030)
#define RST_38_ADDRESS (0x0038)

typedef enum InstructionStatus {
	INS_ERROR = -1,
	INS_SUCCESS = 0,
	INS_BRANCHED = 1,
	INS_RETURNED = 2,
	INS_CB_INSTRUCTION = 3,
}ins_status;

struct CPU{
	bool halt;
	unsigned long long t_edges;
	unsigned long long t_cycles;
	unsigned long long m_cycles;
	unsigned char last_opcode_t_cycles;
};

struct CPU cpu;

/*
	This struct implements an instruction
*/
struct Instruction{
	char* disassembly;
	unsigned char length;
	unsigned char m_cycles;
	ins_status (*action)(struct Instruction*);
};

enum Instructions {
	NOP = 0x0,
	LD_BC_U16 = 0x1,
	LD_BC_A = 0x2,
	INC_BC = 0x3,
	INC_B = 0x4,
	DEC_B = 0x5,
	LD_B_U8 = 0x6,
	RLCA = 0x7,
	LD_U16_SP = 0x8,
	ADD_HL_BC = 0x9,
	LD_A_BC = 0xa,
	DEC_BC = 0xb,
	INC_C = 0xc,
	DEC_C = 0xd,
	LD_C_U8 = 0xe,
	RRCA = 0xf,
	STOP = 0x10,
	LD_DE_U16 = 0x11,
	LD_DE_A = 0x12,
	INC_DE = 0x13,
	INC_D = 0x14,
	DEC_D = 0x15,
	LD_D_U8 = 0x16,
	RLA = 0x17,
	JR_I8 = 0x18,
	ADD_HL_DE = 0x19,
	LD_A_DE = 0x1a,
	DEC_DE = 0x1b,
	INC_E = 0x1c,
	DEC_E = 0x1d,
	LD_E_U8 = 0x1e,
	RRA = 0x1f,
	JR_NZ_I8 = 0x20,
	LD_HL_U16 = 0x21,
	LD_HLplus_A = 0x22,
	INC_HL = 0x23,
	INC_H = 0x24,
	DEC_H = 0x25,
	LD_H_U8 = 0x26,
	DAA = 0x27,
	JR_Z_I8 = 0x28,
	ADD_HL_HL = 0x29,
	LD_A_HLplus = 0x2a,
	DEC_HL = 0x2b,
	INC_L = 0x2c,
	DEC_L = 0x2d,
	LD_L_U8 = 0x2e,
	CPL = 0x2f,
	JR_NC_I8 = 0x30,
	LD_SP_U16 = 0x31,
	LD_HLminus_A = 0x32,
	INC_SP = 0x33,
	INC__HL__ = 0x34,
	DEC__HL__ = 0x35,
	LD_HL_U8 = 0x36,
	SCF = 0x37,
	JR_C_I8 = 0x38,
	ADD_HL_SP = 0x39,
	LD_A_HLminus = 0x3a,
	DEC_SP = 0x3b,
	INC_A = 0x3c,
	DEC_A = 0x3d,
	LD_A_U8 = 0x3e,
	CCF = 0x3f,
	LD_B_B = 0x40,
	LD_B_C = 0x41,
	LD_B_D = 0x42,
	LD_B_E = 0x43,
	LD_B_H = 0x44,
	LD_B_L = 0x45,
	LD_B_HL = 0x46,
	LD_B_A = 0x47,
	LD_C_B = 0x48,
	LD_C_C = 0x49,
	LD_C_D = 0x4a,
	LD_C_E = 0x4b,
	LD_C_H = 0x4c,
	LD_C_L = 0x4d,
	LD_C_HL = 0x4e,
	LD_C_A = 0x4f,
	LD_D_B = 0x50,
	LD_D_C = 0x51,
	LD_D_D = 0x52,
	LD_D_E = 0x53,
	LD_D_H = 0x54,
	LD_D_L = 0x55,
	LD_D_HL = 0x56,
	LD_D_A = 0x57,
	LD_E_B = 0x58,
	LD_E_C = 0x59,
	LD_E_D = 0x5a,
	LD_E_E = 0x5b,
	LD_E_H = 0x5c,
	LD_E_L = 0x5d,
	LD_E_HL = 0x5e,
	LD_E_A = 0x5f,
	LD_H_B = 0x60,
	LD_H_C = 0x61,
	LD_H_D = 0x62,
	LD_H_E = 0x63,
	LD_H_H = 0x64,
	LD_H_L = 0x65,
	LD_H_HL = 0x66,
	LD_H_A = 0x67,
	LD_L_B = 0x68,
	LD_L_C = 0x69,
	LD_L_D = 0x6a,
	LD_L_E = 0x6b,
	LD_L_H = 0x6c,
	LD_L_L = 0x6d,
	LD_L_HL = 0x6e,
	LD_L_A = 0x6f,
	LD_HL_B = 0x70,
	LD_HL_C = 0x71,
	LD_HL_D = 0x72,
	LD_HL_E = 0x73,
	LD_HL_H = 0x74,
	LD_HL_L = 0x75,
	HALT = 0x76,
	LD_HL_A = 0x77,
	LD_A_B = 0x78,
	LD_A_C = 0x79,
	LD_A_D = 0x7a,
	LD_A_E = 0x7b,
	LD_A_H = 0x7c,
	LD_A_L = 0x7d,
	LD_A_HL = 0x7e,
	LD_A_A = 0x7f,
	ADD_A_B = 0x80,
	ADD_A_C = 0x81,
	ADD_A_D = 0x82,
	ADD_A_E = 0x83,
	ADD_A_H = 0x84,
	ADD_A_L = 0x85,
	ADD_A_HL = 0x86,
	ADD_A_A = 0x87,
	ADC_A_B = 0x88,
	ADC_A_C = 0x89,
	ADC_A_D = 0x8a,
	ADC_A_E = 0x8b,
	ADC_A_H = 0x8c,
	ADC_A_L = 0x8d,
	ADC_A_HL = 0x8e,
	ADC_A_A = 0x8f,
	SUB_A_B = 0x90,
	SUB_A_C = 0x91,
	SUB_A_D = 0x92,
	SUB_A_E = 0x93,
	SUB_A_H = 0x94,
	SUB_A_L = 0x95,
	SUB_A_HL = 0x96,
	SUB_A_A = 0x97,
	SBC_A_B = 0x98,
	SBC_A_C = 0x99,
	SBC_A_D = 0x9a,
	SBC_A_E = 0x9b,
	SBC_A_H = 0x9c,
	SBC_A_L = 0x9d,
	SBC_A_HL = 0x9e,
	SBC_A_A = 0x9f,
	AND_A_B = 0xa0,
	AND_A_C = 0xa1,
	AND_A_D = 0xa2,
	AND_A_E = 0xa3,
	AND_A_H = 0xa4,
	AND_A_L = 0xa5,
	AND_A_HL = 0xa6,
	AND_A_A = 0xa7,
	XOR_A_B = 0xa8,
	XOR_A_C = 0xa9,
	XOR_A_D = 0xaa,
	XOR_A_E = 0xab,
	XOR_A_H = 0xac,
	XOR_A_L = 0xad,
	XOR_A_HL = 0xae,
	XOR_A_A = 0xaf,
	OR_A_B = 0xb0,
	OR_A_C = 0xb1,
	OR_A_D = 0xb2,
	OR_A_E = 0xb3,
	OR_A_H = 0xb4,
	OR_A_L = 0xb5,
	OR_A_HL = 0xb6,
	OR_A_A = 0xb7,
	CP_A_B = 0xb8,
	CP_A_C = 0xb9,
	CP_A_D = 0xba,
	CP_A_E = 0xbb,
	CP_A_H = 0xbc,
	CP_A_L = 0xbd,
	CP_A_HL = 0xbe,
	CP_A_A = 0xbf,
	RET_NZ = 0xc0,
	POP_BC = 0xc1,
	JP_NZ_U16 = 0xc2,
	JP_U16 = 0xc3,
	CALL_NZ_U16 = 0xc4,
	PUSH_BC = 0xc5,
	ADD_A_U8 = 0xc6,
	RST_00 = 0xc7,
	RET_Z = 0xc8,
	RET = 0xc9,
	JP_Z_U16 = 0xca,
	PREFIX_CB = 0xcb,
	CALL_Z_U16 = 0xcc,
	CALL_U16 = 0xcd,
	ADC_A_U8 = 0xce,
	RST_08 = 0xcf,
	RET_NC = 0xd0,
	POP_DE = 0xd1,
	JP_NC_U16 = 0xd2,
	CALL_NC_U16 = 0xd4,
	PUSH_DE = 0xd5,
	SUB_A_U8 = 0xd6,
	RST_10 = 0xd7,
	RET_C = 0xd8,
	RETI = 0xd9,
	JP_C_U16 = 0xda,
	CALL_C_U16 = 0xdc,
	SBC_A_U8 = 0xde,
	RST_18 = 0xdf,
	POP_HL = 0xe1,
	PUSH_HL = 0xe5,
	AND_A_U8 = 0xe6,
	RST_20 = 0xe7,
	ADD_SP_I8 = 0xe8,
	JP_HL = 0xe9,
	LD_U16_A = 0xea,
	XOR_A_U8 = 0xee,
	RST_28 = 0xef,
	POP_AF = 0xf1,
	DI = 0xf3,
	PUSH_AF = 0xf5,
	OR_A_U8 = 0xf6,
	RST_30 = 0xf7,
	LD_HL_SPplusI8 = 0xf8,
	LD_SP_HL = 0xf9,
	LD_A_U16 = 0xfa,
	EI = 0xfb,
	CP_A_U8 = 0xfe,
	RST_38 = 0xff,
};

ins_status nop(struct Instruction* instruction); //0x00
ins_status ld_bc_u16(struct Instruction* instruction); //0x01
ins_status ld_bc_a(struct Instruction* instruction); //0x02
ins_status inc_bc(struct Instruction* instruction); //0x03
ins_status inc_b(struct Instruction* instruction); //0x04
ins_status dec_b(struct Instruction* instruction); //0x05
ins_status ld_b_u8(struct Instruction* instruction); //0x06
ins_status rlca(struct Instruction* instruction); //0x07
ins_status ld_u16_sp(struct Instruction* instruction); //0x08
ins_status add_hl_bc(struct Instruction* instruction); //0x09
ins_status ld_a_bc(struct Instruction* instruction); //0x0a
ins_status dec_bc(struct Instruction* instruction); //0x0b
ins_status inc_c(struct Instruction* instruction); //0x0c
ins_status dec_c(struct Instruction* instruction); //0x0d
ins_status ld_c_u8(struct Instruction* instruction); //0x0e
ins_status rrca(struct Instruction* instruction); //0x0f
ins_status stop(struct Instruction* instruction); //0x10
ins_status ld_de_u16(struct Instruction* instruction); //0x11
ins_status ld_de_a(struct Instruction* instruction); //0x12
ins_status inc_de(struct Instruction* instruction); //0x13
ins_status inc_d(struct Instruction* instruction); //0x14
ins_status dec_d(struct Instruction* instruction); //0x15
ins_status ld_d_u8(struct Instruction* instruction); //0x16
ins_status rla(struct Instruction* instruction); //0x17
ins_status jr_i8(struct Instruction* instruction); //0x18
ins_status add_hl_de(struct Instruction* instruction); //0x19
ins_status ld_a_de(struct Instruction* instruction); //0x1a
ins_status dec_de(struct Instruction* instruction); //0x1b
ins_status inc_e(struct Instruction* instruction); //0x1c
ins_status dec_e(struct Instruction* instruction); //0x1d
ins_status ld_e_u8(struct Instruction* instruction); //0x1e
ins_status rra(struct Instruction* instruction); //0x1f
ins_status jr_nz_i8(struct Instruction* instruction); //0x20
ins_status ld_hl_u16(struct Instruction* instruction); //0x21
ins_status ld_hl_plus_a(struct Instruction* instruction); //0x22
ins_status inc_hl(struct Instruction* instruction); //0x23
ins_status inc_h(struct Instruction* instruction); //0x24
ins_status dec_h(struct Instruction* instruction); //0x25
ins_status ld_h_u8(struct Instruction* instruction); //0x26
ins_status daa(struct Instruction* instruction); //0x27
ins_status jr_z_i8(struct Instruction* instruction); //0x28
ins_status add_hl_hl(struct Instruction* instruction); //0x29
ins_status ld_a_hl_plus(struct Instruction* instruction); //0x2a
ins_status dec_hl(struct Instruction* instruction); //0x2b
ins_status inc_l(struct Instruction* instruction); //0x2c
ins_status dec_l(struct Instruction* instruction); //0x2d
ins_status ld_l_u8(struct Instruction* instruction); //0x2e
ins_status cpl(struct Instruction* instruction); //0x2f
ins_status jr_nc_i8(struct Instruction* instruction); //0x30
ins_status ld_sp_u16(struct Instruction* instruction); //0x31
ins_status ld_hl_minus_a(struct Instruction* instruction); //0x32
ins_status inc_sp(struct Instruction* instruction); //0x33
ins_status inc__hl__(struct Instruction* instruction); //0x34
ins_status dec__hl__(struct Instruction* instruction); //0x35
ins_status ld_hl_u8(struct Instruction* instruction); //0x36
ins_status scf(struct Instruction* instruction); //0x37
ins_status jr_c_i8(struct Instruction* instruction); //0x38
ins_status add_hl_sp(struct Instruction* instruction); //0x39
ins_status ld_a_hl_minus(struct Instruction* instruction); //0x3a
ins_status dec_sp(struct Instruction* instruction); //0x3b
ins_status inc_a(struct Instruction* instruction); //0x3c
ins_status dec_a(struct Instruction* instruction); //0x3d
ins_status ld_a_u8(struct Instruction* instruction); //0x3e
ins_status ccf(struct Instruction* instruction); //0x3f
ins_status ld_b_b(struct Instruction* instruction); //0x40
ins_status ld_b_c(struct Instruction* instruction); //0x41
ins_status ld_b_d(struct Instruction* instruction); //0x42
ins_status ld_b_e(struct Instruction* instruction); //0x43
ins_status ld_b_h(struct Instruction* instruction); //0x44
ins_status ld_b_l(struct Instruction* instruction); //0x45
ins_status ld_b_hl(struct Instruction* instruction); //0x46
ins_status ld_b_a(struct Instruction* instruction); //0x47
ins_status ld_c_b(struct Instruction* instruction); //0x48
ins_status ld_c_c(struct Instruction* instruction); //0x49
ins_status ld_c_d(struct Instruction* instruction); //0x4a
ins_status ld_c_e(struct Instruction* instruction); //0x4b
ins_status ld_c_h(struct Instruction* instruction); //0x4c
ins_status ld_c_l(struct Instruction* instruction); //0x4d
ins_status ld_c_hl(struct Instruction* instruction); //0x4e
ins_status ld_c_a(struct Instruction* instruction); //0x4f
ins_status ld_d_b(struct Instruction* instruction); //0x50
ins_status ld_d_c(struct Instruction* instruction); //0x51
ins_status ld_d_d(struct Instruction* instruction); //0x52
ins_status ld_d_e(struct Instruction* instruction); //0x53
ins_status ld_d_h(struct Instruction* instruction); //0x54
ins_status ld_d_l(struct Instruction* instruction); //0x55
ins_status ld_d_hl(struct Instruction* instruction); //0x56
ins_status ld_d_a(struct Instruction* instruction); //0x57
ins_status ld_e_b(struct Instruction* instruction); //0x58
ins_status ld_e_c(struct Instruction* instruction); //0x59
ins_status ld_e_d(struct Instruction* instruction); //0x5a
ins_status ld_e_e(struct Instruction* instruction); //0x5b
ins_status ld_e_h(struct Instruction* instruction); //0x5c
ins_status ld_e_l(struct Instruction* instruction); //0x5d
ins_status ld_e_hl(struct Instruction* instruction); //0x5e
ins_status ld_e_a(struct Instruction* instruction); //0x5f
ins_status ld_h_b(struct Instruction* instruction); //0x60
ins_status ld_h_c(struct Instruction* instruction); //0x61
ins_status ld_h_d(struct Instruction* instruction); //0x62
ins_status ld_h_e(struct Instruction* instruction); //0x63
ins_status ld_h_h(struct Instruction* instruction); //0x64
ins_status ld_h_l(struct Instruction* instruction); //0x65
ins_status ld_h_hl(struct Instruction* instruction); //0x66
ins_status ld_h_a(struct Instruction* instruction); //0x67
ins_status ld_l_b(struct Instruction* instruction); //0x68
ins_status ld_l_c(struct Instruction* instruction); //0x69
ins_status ld_l_d(struct Instruction* instruction); //0x6a
ins_status ld_l_e(struct Instruction* instruction); //0x6b
ins_status ld_l_h(struct Instruction* instruction); //0x6c
ins_status ld_l_l(struct Instruction* instruction); //0x6d
ins_status ld_l_hl(struct Instruction* instruction); //0x6e
ins_status ld_l_a(struct Instruction* instruction); //0x6f
ins_status ld_hl_b(struct Instruction* instruction); //0x70
ins_status ld_hl_c(struct Instruction* instruction); //0x71
ins_status ld_hl_d(struct Instruction* instruction); //0x72
ins_status ld_hl_e(struct Instruction* instruction); //0x73
ins_status ld_hl_h(struct Instruction* instruction); //0x74
ins_status ld_hl_l(struct Instruction* instruction); //0x75
ins_status halt(struct Instruction* instruction); //0x76
ins_status ld_hl_a(struct Instruction* instruction); //0x77
ins_status ld_a_b(struct Instruction* instruction); //0x78
ins_status ld_a_c(struct Instruction* instruction); //0x79
ins_status ld_a_d(struct Instruction* instruction); //0x7a
ins_status ld_a_e(struct Instruction* instruction); //0x7b
ins_status ld_a_h(struct Instruction* instruction); //0x7c
ins_status ld_a_l(struct Instruction* instruction); //0x7d
ins_status ld_a_hl(struct Instruction* instruction); //0x7e
ins_status ld_a_a(struct Instruction* instruction); //0x7f
ins_status add_a_b(struct Instruction* instruction); //0x80
ins_status add_a_c(struct Instruction* instruction); //0x81
ins_status add_a_d(struct Instruction* instruction); //0x82
ins_status add_a_e(struct Instruction* instruction); //0x83
ins_status add_a_h(struct Instruction* instruction); //0x84
ins_status add_a_l(struct Instruction* instruction); //0x85
ins_status add_a_hl(struct Instruction* instruction); //0x86
ins_status add_a_a(struct Instruction* instruction); //0x87
ins_status adc_a_b(struct Instruction* instruction); //0x88
ins_status adc_a_c(struct Instruction* instruction); //0x89
ins_status adc_a_d(struct Instruction* instruction); //0x8a
ins_status adc_a_e(struct Instruction* instruction); //0x8b
ins_status adc_a_h(struct Instruction* instruction); //0x8c
ins_status adc_a_l(struct Instruction* instruction); //0x8d
ins_status adc_a_hl(struct Instruction* instruction); //0x8e
ins_status adc_a_a(struct Instruction* instruction); //0x8f
ins_status sub_a_b(struct Instruction* instruction); //0x90
ins_status sub_a_c(struct Instruction* instruction); //0x91
ins_status sub_a_d(struct Instruction* instruction); //0x92
ins_status sub_a_e(struct Instruction* instruction); //0x93
ins_status sub_a_h(struct Instruction* instruction); //0x94
ins_status sub_a_l(struct Instruction* instruction); //0x95
ins_status sub_a_hl(struct Instruction* instruction); //0x96
ins_status sub_a_a(struct Instruction* instruction); //0x97
ins_status sbc_a_b(struct Instruction* instruction); //0x98
ins_status sbc_a_c(struct Instruction* instruction); //0x99
ins_status sbc_a_d(struct Instruction* instruction); //0x9a
ins_status sbc_a_e(struct Instruction* instruction); //0x9b
ins_status sbc_a_h(struct Instruction* instruction); //0x9c
ins_status sbc_a_l(struct Instruction* instruction); //0x9d
ins_status sbc_a_hl(struct Instruction* instruction); //0x9e
ins_status sbc_a_a(struct Instruction* instruction); //0x9f
ins_status and_a_b(struct Instruction* instruction); //0xa0
ins_status and_a_c(struct Instruction* instruction); //0xa1
ins_status and_a_d(struct Instruction* instruction); //0xa2
ins_status and_a_e(struct Instruction* instruction); //0xa3
ins_status and_a_h(struct Instruction* instruction); //0xa4
ins_status and_a_l(struct Instruction* instruction); //0xa5
ins_status and_a_hl(struct Instruction* instruction); //0xa6
ins_status and_a_a(struct Instruction* instruction); //0xa7
ins_status xor_a_b(struct Instruction* instruction); //0xa8
ins_status xor_a_c(struct Instruction* instruction); //0xa9
ins_status xor_a_d(struct Instruction* instruction); //0xaa
ins_status xor_a_e(struct Instruction* instruction); //0xab
ins_status xor_a_h(struct Instruction* instruction); //0xac
ins_status xor_a_l(struct Instruction* instruction); //0xad
ins_status xor_a_hl(struct Instruction* instruction); //0xae
ins_status xor_a_a(struct Instruction* instruction); //0xaf
ins_status or_a_b(struct Instruction* instruction); //0xb0
ins_status or_a_c(struct Instruction* instruction); //0xb1
ins_status or_a_d(struct Instruction* instruction); //0xb2
ins_status or_a_e(struct Instruction* instruction); //0xb3
ins_status or_a_h(struct Instruction* instruction); //0xb4
ins_status or_a_l(struct Instruction* instruction); //0xb5
ins_status or_a_hl(struct Instruction* instruction); //0xb6
ins_status or_a_a(struct Instruction* instruction); //0xb7
ins_status cp_a_b(struct Instruction* instruction); //0xb8
ins_status cp_a_c(struct Instruction* instruction); //0xb9
ins_status cp_a_d(struct Instruction* instruction); //0xba
ins_status cp_a_e(struct Instruction* instruction); //0xbb
ins_status cp_a_h(struct Instruction* instruction); //0xbc
ins_status cp_a_l(struct Instruction* instruction); //0xbd
ins_status cp_a_hl(struct Instruction* instruction); //0xbe
ins_status cp_a_a(struct Instruction* instruction); //0xbf
ins_status ret_nz(struct Instruction* instruction); //0xc0
ins_status pop_bc(struct Instruction* instruction); // 0xc1
ins_status jp_nz_u16(struct Instruction* instruction); //0xc2
ins_status jp_u16(struct Instruction* instruction); //0xc3
ins_status call_nz_u16(struct Instruction* instruction); //0xc4
ins_status push_bc(struct Instruction* instruction); //0xc5
ins_status add_a_u8(struct Instruction* instruction); //0xc6
ins_status rst_00(struct Instruction* instruction); //0xc7
ins_status ret_z(struct Instruction* instruction); //0xc8
ins_status ret(struct Instruction* instruction); //0xc9
ins_status jp_z_u16(struct Instruction* instruction); //0xca
ins_status prefix_cb(struct Instruction* instruction); //0xcb
ins_status call_z_u16(struct Instruction* instruction); //0xcc
ins_status call_u16(struct Instruction* instruction); //0xcd
ins_status adc_a_u8(struct Instruction* instruction); //0xce
ins_status rst_08(struct Instruction* instruction); //0xcf
ins_status ret_nc(struct Instruction* instruction); //0xd0
ins_status pop_de(struct Instruction* instruction); // 0xd1
ins_status jp_nc_u16(struct Instruction* instruction); //0xd2
ins_status call_nc_u16(struct Instruction* instruction); //0xd4
ins_status push_de(struct Instruction* instruction); //0xd5
ins_status sub_a_u8(struct Instruction* instruction); //0xd6
ins_status rst_10(struct Instruction* instruction); //0xd7
ins_status ret_c(struct Instruction* instruction); //0xd8
ins_status reti(struct Instruction* instruction); //0xd9
ins_status jp_c_u16(struct Instruction* instruction); //0xda
ins_status call_c_u16(struct Instruction* instruction); //0xdc
ins_status sbc_a_u8(struct Instruction* instruction); //0xde
ins_status rst_18(struct Instruction* instruction); //0xdf
ins_status pop_hl(struct Instruction* instruction); // 0xe1
ins_status push_hl(struct Instruction* instruction); //0xe5
ins_status and_a_u8(struct Instruction* instruction); //0xe6
ins_status rst_20(struct Instruction* instruction); //0xe7
ins_status add_sp_i8(struct Instruction* instruction); //0xe8
ins_status jp_hl(struct Instruction* instruction); //0xe9
ins_status ld_u16_a(struct Instruction* instruction); //0xea
ins_status xor_a_u8(struct Instruction* instruction); //0xee
ins_status rst_28(struct Instruction* instruction); //0xef
ins_status pop_af(struct Instruction* instruction); // 0xf1
ins_status di(struct Instruction* instruction); //0xf3
ins_status push_af(struct Instruction* instruction); //0xf5
ins_status or_a_u8(struct Instruction* instruction); //0xf6
ins_status rst_30(struct Instruction* instruction); //0xf7
ins_status ld_hl_sp_plus_i8(struct Instruction* instruction); //0xf8
ins_status ld_sp_hl(struct Instruction* instruction); //0xf9
ins_status ld_a_u16(struct Instruction* instruction); //0xfa
ins_status ei(struct Instruction* instruction); //0xfb
ins_status cp_a_u8(struct Instruction* instruction); //0xfe
ins_status rst_38(struct Instruction* instruction); //0xff

/*
	This array includes all the opcodes.
	
	*Opcodes with branch option will have m_cycles=0 and will increment the pc register themselves.
*/
static struct Instruction instructions[INSTRUCTIONS_AMOUNT] = {
	[NOP] = {"NOP", 1, 1, &nop}, //0x00
	[LD_BC_U16] = {"LD BC, u16", 3, 3, &ld_bc_u16}, //0x01
	[LD_BC_A] = {"LD (BC), A", 1, 2, &ld_bc_a}, //0x02
	[INC_BC] = {"INC BC", 1, 2, &inc_bc}, //0x03
	[INC_B] = {"INC B", 1, 1, &inc_b}, //0x04
	[DEC_B] = {"DEC B", 1, 1, &dec_b}, //0x05
	[LD_B_U8] = {"LD B, u8", 2, 2, &ld_b_u8}, //0x06
	[RLCA] = {"RLCA", 1, 1, &rlca}, //0x07
	[LD_U16_SP] = {"LD U16, SP", 3, 5, &ld_u16_sp}, //0x08
	[ADD_HL_BC] = {"ADD HL, BC", 1, 2, &add_hl_bc}, //0x09
	[LD_A_BC] = {"LD A, (BC)", 1, 2, &ld_a_bc}, //0x0a
	[DEC_BC] = {"DEC BC", 1, 2, &dec_bc}, //0x0b
	[INC_C] = {"INC C", 1, 1, &inc_c}, //0x0c
	[DEC_C] = {"DEC C", 1, 1, &dec_c}, //0x0d
	[LD_C_U8] = {"LD C, u8", 2, 2, &ld_c_u8}, //0x0e
	[RRCA] = {"RRCA", 1, 1, &rrca}, //0x0f
	[STOP] = {"STOP", 1, 1, &stop}, //0x10
	[LD_DE_U16] = {"LD DE, u16", 3, 3, &ld_de_u16}, //0x11
	[LD_DE_A] = {"LD (DE), A", 1, 2, &ld_de_a}, //0x12
	[INC_DE] = {"INC DE", 1, 2, &inc_de}, //0x13
	[INC_D] = {"INC D", 1, 1, &inc_d}, //0x14
	[DEC_D] = {"DEC D", 1, 1, &dec_d}, //0x15
	[LD_D_U8] = {"LD D, u8", 2, 2, &ld_d_u8}, //0x16
	[RLA] = {"RLA", 1, 1, &rla}, //0x17
	[JR_I8] = {"JR, I8", 2, 3, &jr_i8}, //0x18
	[ADD_HL_DE] = {"ADD HL, DE", 1, 2, &add_hl_de}, //0x19
	[LD_A_DE] = {"LD A, (DE)", 1, 2, &ld_a_de}, //0x1a
	[DEC_DE] = {"DEC DE", 1, 2, &dec_de}, //0x1b
	[INC_E] = {"INC E", 1, 1, &inc_e}, //0x1c
	[DEC_E] = {"DEC E", 1, 1, &dec_e}, //0x1d
	[LD_E_U8] = {"LD E, u8", 2, 2, &ld_e_u8}, //0x1e
	[RRA] = {"RRA", 1, 1, &rra}, //0x1f
	[JR_NZ_I8] = {"JR NZ, i8", 2, 0, &jr_nz_i8}, //0x20
	[LD_HL_U16] = {"LD HL, u16", 3, 3, &ld_hl_u16}, //0x21
	[LD_HLplus_A] = {"LD (HL+), A", 1, 2, &ld_hl_plus_a}, //0x22
	[INC_HL] = {"INC HL", 1, 2, &inc_hl}, //0x23
	[INC_H] = {"INC H", 1, 1, &inc_h}, //0x24
	[DEC_H] = {"DEC H", 1, 1, &dec_h}, //0x25
	[LD_H_U8] = {"LD H, u8", 2, 2, &ld_h_u8}, //0x26
	[DAA] = {"DAA", 1, 1, &daa}, //0x027
	[JR_Z_I8] = {"JR Z, I8", 2, 0, &jr_z_i8}, //0x28
	[ADD_HL_HL] = {"ADD HL, HL", 1, 2, &add_hl_hl}, //0x29
	[LD_A_HLplus] = {"LD A, (HL+)", 1, 2, &ld_a_hl_plus}, //0x2a
	[DEC_HL] = {"DEC HL", 1, 2, &dec_hl}, //0x2b
	[INC_L] = {"INC L", 1, 1, &inc_l}, //0x2c
	[DEC_L] = {"DEC L", 1, 1, &dec_l}, //0x2d
	[LD_L_U8] = {"LD L, u8", 2, 2, &ld_l_u8}, //0x2e
	[CPL] = {"CPL", 1, 1, &cpl}, //0x2f
	[JR_NC_I8] = {"JR NC, i8", 2, 0, &jr_nc_i8}, //0x30
	[LD_SP_U16] = {"LD SP, u16", 3, 3, &ld_sp_u16}, //0x31
	[LD_HLminus_A] = {"LD (HL-), A", 1, 2, &ld_hl_minus_a}, //0x32
	[INC_SP] = {"INC SP", 1, 2, &inc_sp}, //0x33
	[INC__HL__] = {"INC (HL)", 1, 3, &inc__hl__}, //0x34
	[DEC__HL__] = {"DEC (HL)", 1, 3, &dec__hl__}, //0x35
	[LD_HL_U8] = {"LD (HL), u8", 2, 3, &ld_hl_u8}, //0x36
	[SCF] = {"SCF", 1, 1, &scf}, //0x37
	[JR_C_I8] = {"JR C, I8", 2, 0, &jr_c_i8}, //0x38
	[ADD_HL_SP] = {"ADD HL, SP", 1, 2, &add_hl_sp}, //0x39
	[LD_A_HLminus] = {"LD A, (HL-)", 1, 2, &ld_a_hl_minus}, //0x3a
	[DEC_SP] = {"DEC SP", 1, 2, &dec_sp}, //0x3b
	[INC_A] = {"INC A", 1, 1, &inc_a}, //0x3c
	[DEC_A] = {"DEC A", 1, 1, &dec_a}, //0x3d
	[LD_A_U8] = {"LD A, u8", 2, 2, &ld_a_u8}, //0x3e
	[CCF] = {"CCF", 1, 1, &ccf}, //0x3f
	[LD_B_B] = {"LD B, B", 1, 1, &ld_b_b}, //0x40
	[LD_B_C] = {"LD B, C", 1, 1, &ld_b_c}, //0x41
	[LD_B_D] = {"LD B, D", 1, 1, &ld_b_d}, //0x42
	[LD_B_E] = {"LD B, D", 1, 1, &ld_b_e}, //0x43
	[LD_B_H] = {"LD B, H", 1, 1, &ld_b_h}, //0x44
	[LD_B_L] = {"LD B, L", 1, 1, &ld_b_l}, //0x45
	[LD_B_HL] = {"LD B, (HL)", 1, 2, &ld_b_hl}, //0x46
	[LD_B_A] = {"LD B, A", 1, 1, &ld_b_a}, //0x47
	[LD_C_B] = {"LD C, B", 1, 1, &ld_c_b}, //0x48
	[LD_C_C] = {"LD C, C", 1, 1, &ld_c_c}, //0x49
	[LD_C_D] = {"LD C, D", 1, 1, &ld_c_d}, //0x4a
	[LD_C_E] = {"LD C, E", 1, 1, &ld_c_e}, //0x4b
	[LD_C_H] = {"LD C, H", 1, 1, &ld_c_h}, //0x4c
	[LD_C_L] = {"LD C, L", 1, 1, &ld_c_l}, //0x4d
	[LD_C_HL] = {"LD C, (HL)", 1, 2, &ld_c_hl}, //0x4e
	[LD_C_A] = {"LD C, A", 1, 1, &ld_c_a}, //0x4f
	[LD_D_B] = {"LD D, B", 1, 1, &ld_d_b}, //0x50
	[LD_D_C] = {"LD D, C", 1, 1, &ld_d_c}, //0x51
	[LD_D_D] = {"LD D, D", 1, 1, &ld_d_d}, //0x52
	[LD_D_E] = {"LD D, D", 1, 1, &ld_d_e}, //0x53
	[LD_D_H] = {"LD D, H", 1, 1, &ld_d_h}, //0x54
	[LD_D_L] = {"LD D, L", 1, 1, &ld_d_l}, //0x55
	[LD_D_HL] = {"LD D, (HL)", 1, 2, &ld_d_hl}, //0x56
	[LD_D_A] = {"LD D, A", 1, 1, &ld_d_a}, //0x57
	[LD_E_B] = {"LD E, B", 1, 1, &ld_e_b}, //0x58
	[LD_E_C] = {"LD E, C", 1, 1, &ld_e_c}, //0x59
	[LD_E_D] = {"LD E, D", 1, 1, &ld_e_d}, //0x5a
	[LD_E_E] = {"LD E, E", 1, 1, &ld_e_e}, //0x5b
	[LD_E_H] = {"LD E, H", 1, 1, &ld_e_h}, //0x5c
	[LD_E_L] = {"LD E, L", 1, 1, &ld_e_l}, //0x5d
	[LD_E_HL] = {"LD E, (HL)", 1, 2, &ld_e_hl}, //0x5e
	[LD_E_A] = {"LD E, A", 1, 1, &ld_e_a}, //0x5f
	[LD_H_B] = {"LD H, B", 1, 1, &ld_h_b}, //0x60
	[LD_H_C] = {"LD H, C", 1, 1, &ld_h_c}, //0x61
	[LD_H_D] = {"LD H, D", 1, 1, &ld_h_d}, //0x62
	[LD_H_E] = {"LD H, D", 1, 1, &ld_h_e}, //0x63
	[LD_H_H] = {"LD H, H", 1, 1, &ld_h_h}, //0x64
	[LD_H_L] = {"LD H, L", 1, 1, &ld_h_l}, //0x65
	[LD_H_HL] = {"LD H, (HL)", 1, 2, &ld_h_hl}, //0x66
	[LD_H_A] = {"LD H, A", 1, 1, &ld_h_a}, //0x67
	[LD_L_B] = {"LD L, B", 1, 1, &ld_l_b}, //0x68
	[LD_L_C] = {"LD L, C", 1, 1, &ld_l_c}, //0x69
	[LD_L_D] = {"LD L, D", 1, 1, &ld_l_d}, //0x6a
	[LD_L_E] = {"LD L, E", 1, 1, &ld_l_e}, //0x6b
	[LD_L_H] = {"LD L, H", 1, 1, &ld_l_h}, //0x6c
	[LD_L_L] = {"LD L, L", 1, 1, &ld_l_l}, //0x6d
	[LD_L_HL] = {"LD L, (HL)", 1, 2, &ld_l_hl}, //0xe
	[LD_L_A] = {"LD L, A", 1, 1, &ld_l_a}, //0x6f
	[LD_HL_B] = {"LD (HL), B", 1, 2, &ld_hl_b}, //0x70
	[LD_HL_C] = {"LD (HL), C", 1, 2, &ld_hl_c}, //0x71
	[LD_HL_D] = {"LD (HL), D", 1, 2, &ld_hl_d}, //0x72
	[LD_HL_E] = {"LD (HL), D", 1, 2, &ld_hl_e}, //0x73
	[LD_HL_H] = {"LD (HL), H", 1, 2, &ld_hl_h}, //0x74
	[LD_HL_L] = {"LD (HL), L", 1, 2, &ld_hl_l}, //0x75
	[HALT] = {"HALT", 1, 1, &halt}, //0x76
	[LD_HL_A] = {"LD (HL), A", 1, 2, &ld_hl_a}, //0x77
	[LD_A_B] = {"LD A, B", 1, 1, &ld_a_b}, //0x78
	[LD_A_C] = {"LD A, C", 1, 1, &ld_a_c}, //0x79
	[LD_A_D] = {"LD A, D", 1, 1, &ld_a_d}, //0x7a
	[LD_A_E] = {"LD A, E", 1, 1, &ld_a_e}, //0x7b
	[LD_A_H] = {"LD A, H", 1, 1, &ld_a_h}, //0x7c
	[LD_A_L] = {"LD A, L", 1, 1, &ld_a_l}, //0x7d
	[LD_A_HL] = {"LD A, (HL)", 1, 2, &ld_a_hl}, //0x7e
	[LD_A_A] = {"LD A, A", 1, 1, &ld_a_a}, //0x7f
	[ADD_A_B] = {"ADD A, B", 1, 1, &add_a_b}, //0x80
	[ADD_A_C] = {"ADD A, C", 1, 1, &add_a_c}, //0x81
	[ADD_A_D] = {"ADD A, D", 1, 1, &add_a_d}, //0x82
	[ADD_A_E] = {"ADD A, E", 1, 1, &add_a_e}, //0x83
	[ADD_A_H] = {"ADD A, H", 1, 1, &add_a_h}, //0x84
	[ADD_A_L] = {"ADD A, L", 1, 1, &add_a_l}, //0x85
	[ADD_A_HL] = {"ADD A, (HL)", 1, 2, &add_a_hl}, //0x86
	[ADD_A_A] = {"ADD A, A", 1, 1, &add_a_a}, //0x87
	[ADC_A_B] = { "ADC A, B", 1, 1, &adc_a_b }, //0x88
	[ADC_A_C] = { "ADC A, C", 1, 1, &adc_a_c }, //0x89
	[ADC_A_D] = { "ADC A, D", 1, 1, &adc_a_d }, //0x8a
	[ADC_A_E] = { "ADC A, E", 1, 1, &adc_a_e }, //0x8b
	[ADC_A_H] = { "ADC A, H", 1, 1, &adc_a_h }, //0x8c
	[ADC_A_L] = { "ADC A, L", 1, 1, &adc_a_l }, //0x8d
	[ADC_A_HL] = { "ADC A, (HL)", 1, 2, &adc_a_hl }, //0x8e
	[ADC_A_A] = { "ADC A, A", 1, 1, &adc_a_a }, //0x8f
	[SUB_A_B] = { "SUB A, B", 1, 1, &sub_a_b }, //0x90
	[SUB_A_C] = { "SUB A, C", 1, 1, &sub_a_c }, //0x91
	[SUB_A_D] = { "SUB A, D", 1, 1, &sub_a_d }, //0x92
	[SUB_A_E] = { "SUB A, E", 1, 1, &sub_a_e }, //0x93
	[SUB_A_H] = { "SUB A, H", 1, 1, &sub_a_h }, //0x94
	[SUB_A_L] = { "SUB A, L", 1, 1, &sub_a_l }, //0x95
	[SUB_A_HL] = { "SUB A, (HL)", 1, 2, &sub_a_hl }, //0x96
	[SUB_A_A] = { "SUB A, A", 1, 1, &sub_a_a }, //0x97
	[SBC_A_B] = { "SBC A, B", 1, 1, &sbc_a_b }, //0x98
	[SBC_A_C] = { "SBC A, C", 1, 1, &sbc_a_c }, //0x99
	[SBC_A_D] = { "SBC A, D", 1, 1, &sbc_a_d }, //0x9a
	[SBC_A_E] = { "SBC A, E", 1, 1, &sbc_a_e }, //0x9b
	[SBC_A_H] = { "SBC A, H", 1, 1, &sbc_a_h }, //0x9c
	[SBC_A_L] = { "SBC A, L", 1, 1, &sbc_a_l }, //0x9d
	[SBC_A_HL] = { "SBC A, (HL)", 1, 2, &sbc_a_hl }, //0x9e
	[SBC_A_A] = { "SBC A, A", 1, 1, &sbc_a_a }, //0x9f
	[AND_A_B] = { "AND A, B", 1, 1, &and_a_b }, //0xa0
	[AND_A_C] = { "AND A, C", 1, 1, &and_a_c }, //0xa1
	[AND_A_D] = { "AND A, D", 1, 1, &and_a_d }, //0xa2
	[AND_A_E] = { "AND A, E", 1, 1, &and_a_e }, //0xa3
	[AND_A_H] = { "AND A, H", 1, 1, &and_a_h }, //0xa4
	[AND_A_L] = { "AND A, L", 1, 1, &and_a_l }, //0xa5
	[AND_A_HL] = { "AND A, (HL)", 1, 2, &and_a_hl }, //0xa6
	[AND_A_A] = { "AND A, A", 1, 1, &and_a_a }, //0xa7
	[XOR_A_B] = { "XOR A, B", 1, 1, &xor_a_b }, //0xa8
	[XOR_A_C] = { "XOR A, C", 1, 1, &xor_a_c }, //0xa9
	[XOR_A_D] = { "XOR A, D", 1, 1, &xor_a_d }, //0xaa
	[XOR_A_E] = { "XOR A, E", 1, 1, &xor_a_e }, //0xab
	[XOR_A_H] = { "XOR A, H", 1, 1, &xor_a_h }, //0xac
	[XOR_A_L] = { "XOR A, L", 1, 1, &xor_a_l }, //0xad
	[XOR_A_HL] = { "XOR A, (HL)", 1, 2, &xor_a_hl }, //0xae
	[XOR_A_A] = { "XOR A, A", 1, 1, &xor_a_a }, //0xaf
	[OR_A_B] = { "OR A, B", 1, 1, &or_a_b }, //0xb0
	[OR_A_C] = { "OR A, C", 1, 1, &or_a_c }, //0xb1
	[OR_A_D] = { "OR A, D", 1, 1, &or_a_d }, //0xb2
	[OR_A_E] = { "OR A, E", 1, 1, &or_a_e }, //0xb3
	[OR_A_H] = { "OR A, H", 1, 1, &or_a_h }, //0xb4
	[OR_A_L] = { "OR A, L", 1, 1, &or_a_l }, //0xb5
	[OR_A_HL] = { "OR A, (HL)", 1, 2, &or_a_hl }, //0xb6
	[OR_A_A] = { "OR A, A", 1, 1, &or_a_a }, //0xb7
	[CP_A_B] = { "CP A, B", 1, 1, &cp_a_b }, //0xb8
	[CP_A_C] = { "CP A, C", 1, 1, &cp_a_c }, //0xb9
	[CP_A_D] = { "CP A, D", 1, 1, &cp_a_d }, //0xba
	[CP_A_E] = { "CP A, E", 1, 1, &cp_a_e }, //0xbb
	[CP_A_H] = { "CP A, H", 1, 1, &cp_a_h }, //0xbc
	[CP_A_L] = { "CP A, L", 1, 1, &cp_a_l }, //0xbd
	[CP_A_HL] = { "CP A, (HL)", 1, 2, &cp_a_hl }, //0xbe
	[CP_A_A] = { "CP A, A", 1, 1, &cp_a_a }, //0xbf
	[RET_NZ] = {"RET NZ", 1, 0, &ret_nz}, //0xc0
	[POP_BC] = {"POP BC", 1, 3, &pop_bc}, //0xc1
	[JP_NZ_U16] = {"JP NZ, u16", 3, 0, &jp_nz_u16}, //0xc2
	[JP_U16] = {"JP, u16", 3, 4, &jp_u16}, //0xc3
	[CALL_NZ_U16] = {"CALL NZ, u16", 3, 0, &call_nz_u16}, //0xc4
	[PUSH_BC] = {"PUSH BC", 1, 4, &push_bc}, //0xc5
	[ADD_A_U8] = {"ADD A, u8", 2, 2, &add_a_u8}, //0xc6
	[RST_00] = {"RST 00", 1, 4, &rst_00}, //0xc7
	[RET_Z] = {"RET Z", 1, 0, &ret_z}, //0xc8
	[RET] = {"RET", 1, 4, &ret}, //0xc9
	[JP_Z_U16] = {"JP Z, u16", 3, 0, &jp_z_u16}, //0xca
	[PREFIX_CB] = {"PREFIX CB", 1, 1, &prefix_cb}, //0xcb
	[CALL_Z_U16] = {"CALL Z, u16", 3, 0, &call_z_u16}, //0xcc
	[CALL_U16] = {"CALL, u16", 3, 6, &call_u16}, //0xcd
	[ADC_A_U8] = {"ADC A, u8", 2, 2, &adc_a_u8}, //0xce
	[RST_08] = {"RST 08", 1, 4, &rst_08}, //0xcf
	[POP_DE] = {"POP DE", 1, 3, &pop_de}, //0xd1
	[RET_NC] = {"RET NC", 1, 0, &ret_nc}, //0xd0
	[JP_NC_U16] = {"JP NC, u16", 3, 0, &jp_nc_u16}, //0xd2
	[CALL_NC_U16] = {"CALL NC, u16", 3, 0, &call_nc_u16}, //0xd4
	[PUSH_DE] = {"PUSH DE", 1, 4, &push_de}, //0xd5
	[SUB_A_U8] = {"SUB A, u8", 2, 2, &sub_a_u8}, //0xd6
	[RST_10] = {"RST 10", 1, 4, &rst_10}, //0xd7
	[RET_C] = {"RET C", 1, 0, &ret_c}, //0xd8
	[RETI] = {"RETI", 1, 4, &reti}, //0xd9
	[JP_C_U16] = {"JP C, u16", 3, 0, &jp_c_u16}, //0xda
	[CALL_C_U16] = {"CALL C, u16", 3, 0, &call_c_u16}, //0xdc
	[SBC_A_U8] = {"SBC A, u8", 2, 2, &sbc_a_u8}, //0xde
	[RST_18] = {"RST 18", 1, 4, &rst_18}, //0xdf
	[POP_HL] = {"POP HL", 1, 3, &pop_hl}, //0xe1
	[PUSH_HL] = {"PUSH HL", 1, 4, &push_hl}, //0xe5
	[AND_A_U8] = {"AND A, u8", 2, 2, &and_a_u8}, //0xe6
	[RST_20] = {"RST 20", 1, 4, &rst_20}, //0xe7
	[ADD_SP_I8] = {"ADD SP, i8", 2, 4, &add_sp_i8}, //0xe8
	[JP_HL] = {"JP, HL", 1, 1, &jp_hl}, //0xe9
	[LD_U16_A] = {"LD (U16), A", 3, 4, &ld_u16_a}, //0xea
	[XOR_A_U8] = {"XOR A, u8", 2, 2, &xor_a_u8}, //0xee
	[RST_28] = {"RST 28", 1, 4, &rst_28}, //0xef
	[POP_AF] = {"POP AF", 1, 3, &pop_af}, //0xf1
	[DI] = {"DI", 1, 1, &di}, //0xf3
	[PUSH_AF] = {"PUSH AF", 1, 4, &push_af}, //0xf5
	[OR_A_U8] = {"OR A, u8", 2, 2, &or_a_u8}, //0xf6
	[RST_30] = {"RST 30", 1, 4, &rst_30}, //0xf7
	[LD_HL_SPplusI8] = {"LD HL, SP+i8", 2, 3, &dec_bc}, //0xf8
	[LD_SP_HL] = {"LD SP, HL", 1, 2, &ld_sp_hl}, //0xf9
	[LD_A_U16] = {"LD A, (U16)", 3, 4, &ld_a_u16}, //0xfa
	[EI] = {"EI", 1, 1, &ei}, //0xfb
	[CP_A_U8] = {"CP A, u8", 2, 2, &cp_a_u8}, //0xfe
	[RST_38] = {"RST 38", 1, 4, &rst_38}, //0xff
};

void execute_instruction(struct Instruction* instruction);

void initiate_cpu();

void cpuStep();

unsigned char get_last_opcode_t_cycles();

unsigned long long get_t_cycles();

void print_cycles();
