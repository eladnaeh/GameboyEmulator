#pragma once

#include "cpu.h"
#include "status.h"

#define CB_INSTRUCTIONS_AMOUNT (256)

/*
unsigned char rlc(unsigned char value);

unsigned char rrc(unsigned char value);

unsigned char rl(unsigned char value);

unsigned char rr(unsigned char value);

unsigned char sla(unsigned char value);

unsigned char sra(unsigned char value);

unsigned char swap(unsigned char value);

unsigned char srl(unsigned char value);

void bit(unsigned char bit, unsigned char value);

unsigned char res(unsigned char bit, unsigned char value);

unsigned char set(unsigned char bit, unsigned char value);
*/

enum CBInstructions{
	RLC_B = 0x00,
	RLC_C = 0x01,
	RLC_D = 0x02,
	RLC_E = 0x03,
	RLC_H = 0x04,
	RLC_L = 0x05,
	RLC_HL = 0x06,
	RLC_A = 0x07,

	RRC_B = 0x08,
	RRC_C = 0x09,
	RRC_D = 0x0a,
	RRC_E = 0x0b,
	RRC_H = 0x0c,
	RRC_L = 0x0d,
	RRC_HL = 0x0e,
	RRC_A = 0x0f,

	RL_B = 0x10,
	RL_C = 0x11,
	RL_D = 0x12,
	RL_E = 0x13,
	RL_H = 0x14,
	RL_L = 0x15,
	RL_HL = 0x16,
	RL_A = 0x17,

	RR_B = 0x18,
	RR_C = 0x19,
	RR_D = 0x1a,
	RR_E = 0x1b,
	RR_H = 0x1c,
	RR_L = 0x1d,
	RR_HL = 0x1e,
	RR_A = 0x1f,

	SLA_B = 0x20,
	SLA_C = 0x21,
	SLA_D = 0x22,
	SLA_E = 0x23,
	SLA_H = 0x24,
	SLA_L = 0x25,
	SLA_HL = 0x26,
	SLA_A = 0x27,

	SRA_B = 0x28,
	SRA_C = 0x29,
	SRA_D = 0x2a,
	SRA_E = 0x2b,
	SRA_H = 0x2c,
	SRA_L = 0x2d,
	SRA_HL = 0x2e,
	SRA_A = 0x2f,

	SWAP_B = 0x30,
	SWAP_C = 0x31,
	SWAP_D = 0x32,
	SWAP_E = 0x33,
	SWAP_H = 0x34,
	SWAP_L = 0x35,
	SWAP_HL = 0x36,
	SWAP_A = 0x37,

	SRL_B = 0x38,
	SRL_C = 0x39,
	SRL_D = 0x3a,
	SRL_E = 0x3b,
	SRL_H = 0x3c,
	SRL_L = 0x3d,
	SRL_HL = 0x3e,
	SRL_A = 0x3f,

	BIT_0_B = 0x40,
	BIT_0_C = 0x41,
	BIT_0_D = 0x42,
	BIT_0_E = 0x43,
	BIT_0_H = 0x44,
	BIT_0_L = 0x45,
	BIT_0_HL = 0x46,
	BIT_0_A = 0x47,

	BIT_1_B = 0x48,
	BIT_1_C = 0x49,
	BIT_1_D = 0x4a,
	BIT_1_E = 0x4b,
	BIT_1_H = 0x4c,
	BIT_1_L = 0x4d,
	BIT_1_HL = 0x4e,
	BIT_1_A = 0x4f,

	BIT_2_B = 0x50,
	BIT_2_C = 0x51,
	BIT_2_D = 0x52,
	BIT_2_E = 0x53,
	BIT_2_H = 0x54,
	BIT_2_L = 0x55,
	BIT_2_HL = 0x56,
	BIT_2_A = 0x57,

	BIT_3_B = 0x58,
	BIT_3_C = 0x59,
	BIT_3_D = 0x5a,
	BIT_3_E = 0x5b,
	BIT_3_H = 0x5c,
	BIT_3_L = 0x5d,
	BIT_3_HL = 0x5e,
	BIT_3_A = 0x5f,

	BIT_4_B = 0x60,
	BIT_4_C = 0x61,
	BIT_4_D = 0x62,
	BIT_4_E = 0x63,
	BIT_4_H = 0x64,
	BIT_4_L = 0x65,
	BIT_4_HL = 0x66,
	BIT_4_A = 0x67,

	BIT_5_B = 0x68,
	BIT_5_C = 0x69,
	BIT_5_D = 0x6a,
	BIT_5_E = 0x6b,
	BIT_5_H = 0x6c,
	BIT_5_L = 0x6d,
	BIT_5_HL = 0x6e,
	BIT_5_A = 0x6f,

	BIT_6_B = 0x70,
	BIT_6_C = 0x71,
	BIT_6_D = 0x72,
	BIT_6_E = 0x73,
	BIT_6_H = 0x74,
	BIT_6_L = 0x75,
	BIT_6_HL = 0x76,
	BIT_6_A = 0x77,

	BIT_7_B = 0x78,
	BIT_7_C = 0x79,
	BIT_7_D = 0x7a,
	BIT_7_E = 0x7b,
	BIT_7_H = 0x7c,
	BIT_7_L = 0x7d,
	BIT_7_HL = 0x7e,
	BIT_7_A = 0x7f,

	RES_0_B = 0x80,
	RES_0_C = 0x81,
	RES_0_D = 0x82,
	RES_0_E = 0x83,
	RES_0_H = 0x84,
	RES_0_L = 0x85,
	RES_0_HL = 0x86,
	RES_0_A = 0x87,

	RES_1_B = 0x88,
	RES_1_C = 0x89,
	RES_1_D = 0x8a,
	RES_1_E = 0x8b,
	RES_1_H = 0x8c,
	RES_1_L = 0x8d,
	RES_1_HL = 0x8e,
	RES_1_A = 0x8f,

	RES_2_B = 0x90,
	RES_2_C = 0x91,
	RES_2_D = 0x92,
	RES_2_E = 0x93,
	RES_2_H = 0x94,
	RES_2_L = 0x95,
	RES_2_HL = 0x96,
	RES_2_A = 0x97,

	RES_3_B = 0x98,
	RES_3_C = 0x99,
	RES_3_D = 0x9a,
	RES_3_E = 0x9b,
	RES_3_H = 0x9c,
	RES_3_L = 0x9d,
	RES_3_HL = 0x9e,
	RES_3_A = 0x9f,

	RES_4_B = 0xa0,
	RES_4_C = 0xa1,
	RES_4_D = 0xa2,
	RES_4_E = 0xa3,
	RES_4_H = 0xa4,
	RES_4_L = 0xa5,
	RES_4_HL = 0xa6,
	RES_4_A = 0xa7,

	RES_5_B = 0xa8,
	RES_5_C = 0xa9,
	RES_5_D = 0xaa,
	RES_5_E = 0xab,
	RES_5_H = 0xac,
	RES_5_L = 0xad,
	RES_5_HL = 0xae,
	RES_5_A = 0xaf,

	RES_6_B = 0xb0,
	RES_6_C = 0xb1,
	RES_6_D = 0xb2,
	RES_6_E = 0xb3,
	RES_6_H = 0xb4,
	RES_6_L = 0xb5,
	RES_6_HL = 0xb6,
	RES_6_A = 0xb7,

	RES_7_B = 0xb8,
	RES_7_C = 0xb9,
	RES_7_D = 0xba,
	RES_7_E = 0xbb,
	RES_7_H = 0xbc,
	RES_7_L = 0xbd,
	RES_7_HL = 0xbe,
	RES_7_A = 0xbf,

	SET_0_B = 0xc0,
	SET_0_C = 0xc1,
	SET_0_D = 0xc2,
	SET_0_E = 0xc3,
	SET_0_H = 0xc4,
	SET_0_L = 0xc5,
	SET_0_HL = 0xc6,
	SET_0_A = 0xc7,

	SET_1_B = 0xc8,
	SET_1_C = 0xc9,
	SET_1_D = 0xca,
	SET_1_E = 0xcb,
	SET_1_H = 0xcc,
	SET_1_L = 0xcd,
	SET_1_HL = 0xce,
	SET_1_A = 0xcf,

	SET_2_B = 0xd0,
	SET_2_C = 0xd1,
	SET_2_D = 0xd2,
	SET_2_E = 0xd3,
	SET_2_H = 0xd4,
	SET_2_L = 0xd5,
	SET_2_HL = 0xd6,
	SET_2_A = 0xd7,

	SET_3_B = 0xd8,
	SET_3_C = 0xd9,
	SET_3_D = 0xda,
	SET_3_E = 0xdb,
	SET_3_H = 0xdc,
	SET_3_L = 0xdd,
	SET_3_HL = 0xde,
	SET_3_A = 0xdf,

	SET_4_B = 0xe0,
	SET_4_C = 0xe1,
	SET_4_D = 0xe2,
	SET_4_E = 0xe3,
	SET_4_H = 0xe4,
	SET_4_L = 0xe5,
	SET_4_HL = 0xe6,
	SET_4_A = 0xe7,

	SET_5_B = 0xe8,
	SET_5_C = 0xe9,
	SET_5_D = 0xea,
	SET_5_E = 0xeb,
	SET_5_H = 0xec,
	SET_5_L = 0xed,
	SET_5_HL = 0xee,
	SET_5_A = 0xef,

	SET_6_B = 0xf0,
	SET_6_C = 0xf1,
	SET_6_D = 0xf2,
	SET_6_E = 0xf3,
	SET_6_H = 0xf4,
	SET_6_L = 0xf5,
	SET_6_HL = 0xf6,
	SET_6_A = 0xf7,

	SET_7_B = 0xf8,
	SET_7_C = 0xf9,
	SET_7_D = 0xfa,
	SET_7_E = 0xfb,
	SET_7_H = 0xfc,
	SET_7_L = 0xfd,
	SET_7_HL = 0xfe,
	SET_7_A = 0xff,
};

/*0x00 - 0x07*/
ins_status rlc_b(struct Instruction* instruction);
ins_status rlc_c(struct Instruction* instruction);
ins_status rlc_d(struct Instruction* instruction);
ins_status rlc_e(struct Instruction* instruction);
ins_status rlc_h(struct Instruction* instruction);
ins_status rlc_l(struct Instruction* instruction);
ins_status rlc_hl(struct Instruction* instruction);
ins_status rlc_a(struct Instruction* instruction);

/*0x08 - 0x0f*/
ins_status rrc_b(struct Instruction* instruction);
ins_status rrc_c(struct Instruction* instruction);
ins_status rrc_d(struct Instruction* instruction);
ins_status rrc_e(struct Instruction* instruction);
ins_status rrc_h(struct Instruction* instruction);
ins_status rrc_l(struct Instruction* instruction);
ins_status rrc_hl(struct Instruction* instruction);
ins_status rrc_a(struct Instruction* instruction);

/*0x10 - 0x17*/
ins_status rl_b(struct Instruction* instruction);
ins_status rl_c(struct Instruction* instruction);
ins_status rl_d(struct Instruction* instruction);
ins_status rl_e(struct Instruction* instruction);
ins_status rl_h(struct Instruction* instruction);
ins_status rl_l(struct Instruction* instruction);
ins_status rl_hl(struct Instruction* instruction);
ins_status rl_a(struct Instruction* instruction);

/*0x18 - 0x1f*/
ins_status rr_b(struct Instruction* instruction);
ins_status rr_c(struct Instruction* instruction);
ins_status rr_d(struct Instruction* instruction);
ins_status rr_e(struct Instruction* instruction);
ins_status rr_h(struct Instruction* instruction);
ins_status rr_l(struct Instruction* instruction);
ins_status rr_hl(struct Instruction* instruction);
ins_status rr_a(struct Instruction* instruction);

/*0x20 - 0x27*/
ins_status sla_b(struct Instruction* instruction);
ins_status sla_c(struct Instruction* instruction);
ins_status sla_d(struct Instruction* instruction);
ins_status sla_e(struct Instruction* instruction);
ins_status sla_h(struct Instruction* instruction);
ins_status sla_l(struct Instruction* instruction);
ins_status sla_hl(struct Instruction* instruction);
ins_status sla_a(struct Instruction* instruction);

/*0x28 - 0x2f*/
ins_status sra_b(struct Instruction* instruction);
ins_status sra_c(struct Instruction* instruction);
ins_status sra_d(struct Instruction* instruction);
ins_status sra_e(struct Instruction* instruction);
ins_status sra_h(struct Instruction* instruction);
ins_status sra_l(struct Instruction* instruction);
ins_status sra_hl(struct Instruction* instruction);
ins_status sra_a(struct Instruction* instruction);

/*0x30 - 0x37*/
ins_status swap_b(struct Instruction* instruction);
ins_status swap_c(struct Instruction* instruction);
ins_status swap_d(struct Instruction* instruction);
ins_status swap_e(struct Instruction* instruction);
ins_status swap_h(struct Instruction* instruction);
ins_status swap_l(struct Instruction* instruction);
ins_status swap_hl(struct Instruction* instruction);
ins_status swap_a(struct Instruction* instruction);

/*0x38 - 0x3f*/
ins_status srl_b(struct Instruction* instruction);
ins_status srl_c(struct Instruction* instruction);
ins_status srl_d(struct Instruction* instruction);
ins_status srl_e(struct Instruction* instruction);
ins_status srl_h(struct Instruction* instruction);
ins_status srl_l(struct Instruction* instruction);
ins_status srl_hl(struct Instruction* instruction);
ins_status srl_a(struct Instruction* instruction);

/*0x40 - 0x7f*/
ins_status bit_0_b(struct Instruction* instruction);
ins_status bit_0_c(struct Instruction* instruction);
ins_status bit_0_d(struct Instruction* instruction);
ins_status bit_0_e(struct Instruction* instruction);
ins_status bit_0_h(struct Instruction* instruction);
ins_status bit_0_l(struct Instruction* instruction);
ins_status bit_0_hl(struct Instruction* instruction);
ins_status bit_0_a(struct Instruction* instruction);

ins_status bit_1_b(struct Instruction* instruction);
ins_status bit_1_c(struct Instruction* instruction);
ins_status bit_1_d(struct Instruction* instruction);
ins_status bit_1_e(struct Instruction* instruction);
ins_status bit_1_h(struct Instruction* instruction);
ins_status bit_1_l(struct Instruction* instruction);
ins_status bit_1_hl(struct Instruction* instruction);
ins_status bit_1_a(struct Instruction* instruction);

ins_status bit_2_b(struct Instruction* instruction);
ins_status bit_2_c(struct Instruction* instruction);
ins_status bit_2_d(struct Instruction* instruction);
ins_status bit_2_e(struct Instruction* instruction);
ins_status bit_2_h(struct Instruction* instruction);
ins_status bit_2_l(struct Instruction* instruction);
ins_status bit_2_hl(struct Instruction* instruction);
ins_status bit_2_a(struct Instruction* instruction);

ins_status bit_3_b(struct Instruction* instruction);
ins_status bit_3_c(struct Instruction* instruction);
ins_status bit_3_d(struct Instruction* instruction);
ins_status bit_3_e(struct Instruction* instruction);
ins_status bit_3_h(struct Instruction* instruction);
ins_status bit_3_l(struct Instruction* instruction);
ins_status bit_3_hl(struct Instruction* instruction);
ins_status bit_3_a(struct Instruction* instruction);

ins_status bit_4_b(struct Instruction* instruction);
ins_status bit_4_c(struct Instruction* instruction);
ins_status bit_4_d(struct Instruction* instruction);
ins_status bit_4_e(struct Instruction* instruction);
ins_status bit_4_h(struct Instruction* instruction);
ins_status bit_4_l(struct Instruction* instruction);
ins_status bit_4_hl(struct Instruction* instruction);
ins_status bit_4_a(struct Instruction* instruction);

ins_status bit_5_b(struct Instruction* instruction);
ins_status bit_5_c(struct Instruction* instruction);
ins_status bit_5_d(struct Instruction* instruction);
ins_status bit_5_e(struct Instruction* instruction);
ins_status bit_5_h(struct Instruction* instruction);
ins_status bit_5_l(struct Instruction* instruction);
ins_status bit_5_hl(struct Instruction* instruction);
ins_status bit_5_a(struct Instruction* instruction);

ins_status bit_6_b(struct Instruction* instruction);
ins_status bit_6_c(struct Instruction* instruction);
ins_status bit_6_d(struct Instruction* instruction);
ins_status bit_6_e(struct Instruction* instruction);
ins_status bit_6_h(struct Instruction* instruction);
ins_status bit_6_l(struct Instruction* instruction);
ins_status bit_6_hl(struct Instruction* instruction);
ins_status bit_6_a(struct Instruction* instruction);

ins_status bit_7_b(struct Instruction* instruction);
ins_status bit_7_c(struct Instruction* instruction);
ins_status bit_7_d(struct Instruction* instruction);
ins_status bit_7_e(struct Instruction* instruction);
ins_status bit_7_h(struct Instruction* instruction);
ins_status bit_7_l(struct Instruction* instruction);
ins_status bit_7_hl(struct Instruction* instruction);
ins_status bit_7_a(struct Instruction* instruction);

/*0x80 - 0xbf*/
ins_status res_0_b(struct Instruction* instruction);
ins_status res_0_c(struct Instruction* instruction);
ins_status res_0_d(struct Instruction* instruction);
ins_status res_0_e(struct Instruction* instruction);
ins_status res_0_h(struct Instruction* instruction);
ins_status res_0_l(struct Instruction* instruction);
ins_status res_0_hl(struct Instruction* instruction);
ins_status res_0_a(struct Instruction* instruction);

ins_status res_1_b(struct Instruction* instruction);
ins_status res_1_c(struct Instruction* instruction);
ins_status res_1_d(struct Instruction* instruction);
ins_status res_1_e(struct Instruction* instruction);
ins_status res_1_h(struct Instruction* instruction);
ins_status res_1_l(struct Instruction* instruction);
ins_status res_1_hl(struct Instruction* instruction);
ins_status res_1_a(struct Instruction* instruction);

ins_status res_2_b(struct Instruction* instruction);
ins_status res_2_c(struct Instruction* instruction);
ins_status res_2_d(struct Instruction* instruction);
ins_status res_2_e(struct Instruction* instruction);
ins_status res_2_h(struct Instruction* instruction);
ins_status res_2_l(struct Instruction* instruction);
ins_status res_2_hl(struct Instruction* instruction);
ins_status res_2_a(struct Instruction* instruction);

ins_status res_3_b(struct Instruction* instruction);
ins_status res_3_c(struct Instruction* instruction);
ins_status res_3_d(struct Instruction* instruction);
ins_status res_3_e(struct Instruction* instruction);
ins_status res_3_h(struct Instruction* instruction);
ins_status res_3_l(struct Instruction* instruction);
ins_status res_3_hl(struct Instruction* instruction);
ins_status res_3_a(struct Instruction* instruction);

ins_status res_4_b(struct Instruction* instruction);
ins_status res_4_c(struct Instruction* instruction);
ins_status res_4_d(struct Instruction* instruction);
ins_status res_4_e(struct Instruction* instruction);
ins_status res_4_h(struct Instruction* instruction);
ins_status res_4_l(struct Instruction* instruction);
ins_status res_4_hl(struct Instruction* instruction);
ins_status res_4_a(struct Instruction* instruction);

ins_status res_5_b(struct Instruction* instruction);
ins_status res_5_c(struct Instruction* instruction);
ins_status res_5_d(struct Instruction* instruction);
ins_status res_5_e(struct Instruction* instruction);
ins_status res_5_h(struct Instruction* instruction);
ins_status res_5_l(struct Instruction* instruction);
ins_status res_5_hl(struct Instruction* instruction);
ins_status res_5_a(struct Instruction* instruction);

ins_status res_6_b(struct Instruction* instruction);
ins_status res_6_c(struct Instruction* instruction);
ins_status res_6_d(struct Instruction* instruction);
ins_status res_6_e(struct Instruction* instruction);
ins_status res_6_h(struct Instruction* instruction);
ins_status res_6_l(struct Instruction* instruction);
ins_status res_6_hl(struct Instruction* instruction);
ins_status res_6_a(struct Instruction* instruction);

ins_status res_7_b(struct Instruction* instruction);
ins_status res_7_c(struct Instruction* instruction);
ins_status res_7_d(struct Instruction* instruction);
ins_status res_7_e(struct Instruction* instruction);
ins_status res_7_h(struct Instruction* instruction);
ins_status res_7_l(struct Instruction* instruction);
ins_status res_7_hl(struct Instruction* instruction);
ins_status res_7_a(struct Instruction* instruction);

/*0xc0 - 0xff*/
ins_status set_0_b(struct Instruction* instruction);
ins_status set_0_c(struct Instruction* instruction);
ins_status set_0_d(struct Instruction* instruction);
ins_status set_0_e(struct Instruction* instruction);
ins_status set_0_h(struct Instruction* instruction);
ins_status set_0_l(struct Instruction* instruction);
ins_status set_0_hl(struct Instruction* instruction);
ins_status set_0_a(struct Instruction* instruction);

ins_status set_1_b(struct Instruction* instruction);
ins_status set_1_c(struct Instruction* instruction);
ins_status set_1_d(struct Instruction* instruction);
ins_status set_1_e(struct Instruction* instruction);
ins_status set_1_h(struct Instruction* instruction);
ins_status set_1_l(struct Instruction* instruction);
ins_status set_1_hl(struct Instruction* instruction);
ins_status set_1_a(struct Instruction* instruction);

ins_status set_2_b(struct Instruction* instruction);
ins_status set_2_c(struct Instruction* instruction);
ins_status set_2_d(struct Instruction* instruction);
ins_status set_2_e(struct Instruction* instruction);
ins_status set_2_h(struct Instruction* instruction);
ins_status set_2_l(struct Instruction* instruction);
ins_status set_2_hl(struct Instruction* instruction);
ins_status set_2_a(struct Instruction* instruction);

ins_status set_3_b(struct Instruction* instruction);
ins_status set_3_c(struct Instruction* instruction);
ins_status set_3_d(struct Instruction* instruction);
ins_status set_3_e(struct Instruction* instruction);
ins_status set_3_h(struct Instruction* instruction);
ins_status set_3_l(struct Instruction* instruction);
ins_status set_3_hl(struct Instruction* instruction);
ins_status set_3_a(struct Instruction* instruction);

ins_status set_4_b(struct Instruction* instruction);
ins_status set_4_c(struct Instruction* instruction);
ins_status set_4_d(struct Instruction* instruction);
ins_status set_4_e(struct Instruction* instruction);
ins_status set_4_h(struct Instruction* instruction);
ins_status set_4_l(struct Instruction* instruction);
ins_status set_4_hl(struct Instruction* instruction);
ins_status set_4_a(struct Instruction* instruction);

ins_status set_5_b(struct Instruction* instruction);
ins_status set_5_c(struct Instruction* instruction);
ins_status set_5_d(struct Instruction* instruction);
ins_status set_5_e(struct Instruction* instruction);
ins_status set_5_h(struct Instruction* instruction);
ins_status set_5_l(struct Instruction* instruction);
ins_status set_5_hl(struct Instruction* instruction);
ins_status set_5_a(struct Instruction* instruction);

ins_status set_6_b(struct Instruction* instruction);
ins_status set_6_c(struct Instruction* instruction);
ins_status set_6_d(struct Instruction* instruction);
ins_status set_6_e(struct Instruction* instruction);
ins_status set_6_h(struct Instruction* instruction);
ins_status set_6_l(struct Instruction* instruction);
ins_status set_6_hl(struct Instruction* instruction);
ins_status set_6_a(struct Instruction* instruction);

ins_status set_7_b(struct Instruction* instruction);
ins_status set_7_c(struct Instruction* instruction);
ins_status set_7_d(struct Instruction* instruction);
ins_status set_7_e(struct Instruction* instruction);
ins_status set_7_h(struct Instruction* instruction);
ins_status set_7_l(struct Instruction* instruction);
ins_status set_7_hl(struct Instruction* instruction);
ins_status set_7_a(struct Instruction* instruction);


static struct Instruction cb_instructions[CB_INSTRUCTIONS_AMOUNT] = {
	/*0x00 - 0x07*/
	[RLC_B] = {"RLC B", 2, 2, &rlc_b},
	[RLC_C] = {"RLC C", 2, 2, &rlc_c},
	[RLC_D] = {"RLC D", 2, 2, &rlc_d},
	[RLC_E] = {"RLC E", 2, 2, &rlc_e},
	[RLC_H] = {"RLC H", 2, 2, &rlc_h},
	[RLC_L] = {"RLC L", 2, 2, &rlc_l},
	[RLC_HL] = {"RLC (HL)", 2, 4, &rlc_hl},
	[RLC_A] = {"RLC A", 2, 2, &rlc_a},

	/*0x08 - 0x0f*/
	[RRC_B] = {"RRC B", 2, 2, &rrc_b},
	[RRC_C] = {"RRC C", 2, 2, &rrc_c},
	[RRC_D] = {"RRC D", 2, 2, &rrc_d},
	[RRC_E] = {"RRC E", 2, 2, &rrc_e},
	[RRC_H] = {"RRC H", 2, 2, &rrc_h},
	[RRC_L] = {"RRC L", 2, 2, &rrc_l},
	[RRC_HL] = {"RRC (HL)", 2, 4, &rrc_hl},
	[RRC_A] = {"RRC A", 2, 2, &rrc_a},

	/*0x10 - 0x17*/
	[RL_B] = {"RL B", 2, 2, &rl_b},
	[RL_C] = {"RL C", 2, 2, &rl_c},
	[RL_D] = {"RL D", 2, 2, &rl_d},
	[RL_E] = {"RL E", 2, 2, &rl_e},
	[RL_H] = {"RL H", 2, 2, &rl_h},
	[RL_L] = {"RL L", 2, 2, &rl_l},
	[RL_HL] = {"RL (HL)", 2, 4, &rl_hl},
	[RL_A] = {"RL A", 2, 2, &rl_a},

	/*0x18 - 0x1f*/
	[RR_B] = {"RR B", 2, 2, &rr_b},
	[RR_C] = {"RR C", 2, 2, &rr_c},
	[RR_D] = {"RR D", 2, 2, &rr_d},
	[RR_E] = {"RR E", 2, 2, &rr_e},
	[RR_H] = {"RR H", 2, 2, &rr_h},
	[RR_L] = {"RR L", 2, 2, &rr_l},
	[RR_HL] = {"RR (HL)", 2, 4, &rr_hl},
	[RR_A] = {"RR A", 2, 2, &rr_a},

	/*0x20 - 0x27*/
	[SLA_B] = {"SLA B", 2, 2, &sla_b},
	[SLA_C] = {"SLA C", 2, 2, &sla_c},
	[SLA_D] = {"SLA D", 2, 2, &sla_d},
	[SLA_E] = {"SLA E", 2, 2, &sla_e},
	[SLA_H] = {"SLA H", 2, 2, &sla_h},
	[SLA_L] = {"SLA L", 2, 2, &sla_l},
	[SLA_HL] = {"SLA (HL)", 2, 4, &sla_hl},
	[SLA_A] = {"SLA A", 2, 2, &sla_a},

	/*0x28 - 0x2f*/
	[SRA_B] = {"SRA B", 2, 2, &sra_b},
	[SRA_C] = {"SRA C", 2, 2, &sra_c},
	[SRA_D] = {"SRA D", 2, 2, &sra_d},
	[SRA_E] = {"SRA E", 2, 2, &sra_e},
	[SRA_H] = {"SRA H", 2, 2, &sra_h},
	[SRA_L] = {"SRA L", 2, 2, &sra_l},
	[SRA_HL] = {"SRA (HL)", 2, 4, &sra_hl},
	[SRA_A] = {"SRA A", 2, 2, &sra_a},

	/*0x30 - 0x37*/
	[SWAP_B] = {"SWAP B", 2, 2, &swap_b},
	[SWAP_C] = {"SWAP C", 2, 2, &swap_c},
	[SWAP_D] = {"SWAP D", 2, 2, &swap_d},
	[SWAP_E] = {"SWAP E", 2, 2, &swap_e},
	[SWAP_H] = {"SWAP H", 2, 2, &swap_h},
	[SWAP_L] = {"SWAP L", 2, 2, &swap_l},
	[SWAP_HL] = {"SWAP (HL)", 2, 4, &swap_hl},
	[SWAP_A] = {"SWAP A", 2, 2, &swap_a},

	/*0x38 - 0x3f*/
	[SRL_B] = {"SRL B", 2, 2, &srl_b},
	[SRL_C] = {"SRL C", 2, 2, &srl_c},
	[SRL_D] = {"SRL D", 2, 2, &srl_d},
	[SRL_E] = {"SRL E", 2, 2, &srl_e},
	[SRL_H] = {"SRL H", 2, 2, &srl_h},
	[SRL_L] = {"SRL L", 2, 2, &srl_l},
	[SRL_HL] = {"SRL (HL)", 2, 4, &srl_hl},
	[SRL_A] = {"SRL A", 2, 2, &srl_a},

	/*0x40 - 0x7f*/
	[BIT_0_B] = {"BIT 0, B", 2, 2, &bit_0_b},
	[BIT_0_C] = {"BIT 0, C", 2, 2, &bit_0_c},
	[BIT_0_D] = {"BIT 0, D", 2, 2, &bit_0_d},
	[BIT_0_E] = {"BIT 0, E", 2, 2, &bit_0_e},
	[BIT_0_H] = {"BIT 0, H", 2, 2, &bit_0_h},
	[BIT_0_L] = {"BIT 0, L", 2, 2, &bit_0_l},
	[BIT_0_HL] = {"BIT 0, (HL)", 2, 3, &bit_0_hl},
	[BIT_0_A] = {"BIT 0, B", 2, 2, &bit_0_a},

	[BIT_1_B] = {"BIT 1, B", 2, 2, &bit_1_b},
	[BIT_1_C] = {"BIT 1, C", 2, 2, &bit_1_c},
	[BIT_1_D] = {"BIT 1, D", 2, 2, &bit_1_d},
	[BIT_1_E] = {"BIT 1, E", 2, 2, &bit_1_e},
	[BIT_1_H] = {"BIT 1, H", 2, 2, &bit_1_h},
	[BIT_1_L] = {"BIT 1, L", 2, 2, &bit_1_l},
	[BIT_1_HL] = {"BIT 1, (HL)", 2, 3, &bit_1_hl},
	[BIT_1_A] = {"BIT 1, B", 2, 2, &bit_1_a},

	[BIT_2_B] = {"BIT 2, B", 2, 2, &bit_2_b},
	[BIT_2_C] = {"BIT 2, C", 2, 2, &bit_2_c},
	[BIT_2_D] = {"BIT 2, D", 2, 2, &bit_2_d},
	[BIT_2_E] = {"BIT 2, E", 2, 2, &bit_2_e},
	[BIT_2_H] = {"BIT 2, H", 2, 2, &bit_2_h},
	[BIT_2_L] = {"BIT 2, L", 2, 2, &bit_2_l},
	[BIT_2_HL] = {"BIT 2, (HL)", 2, 3, &bit_2_hl},
	[BIT_2_A] = {"BIT 2, B", 2, 2, &bit_2_a},

	[BIT_3_B] = {"BIT 3, B", 2, 2, &bit_3_b},
	[BIT_3_C] = {"BIT 3, C", 2, 2, &bit_3_c},
	[BIT_3_D] = {"BIT 3, D", 2, 2, &bit_3_d},
	[BIT_3_E] = {"BIT 3, E", 2, 2, &bit_3_e},
	[BIT_3_H] = {"BIT 3, H", 2, 2, &bit_3_h},
	[BIT_3_L] = {"BIT 3, L", 2, 2, &bit_3_l},
	[BIT_3_HL] = {"BIT 3, (HL)", 2, 3, &bit_3_hl},
	[BIT_3_A] = {"BIT 3, B", 2, 2, &bit_3_a},

	[BIT_4_B] = {"BIT 4, B", 2, 2, &bit_4_b},
	[BIT_4_C] = {"BIT 4, C", 2, 2, &bit_4_c},
	[BIT_4_D] = {"BIT 4, D", 2, 2, &bit_4_d},
	[BIT_4_E] = {"BIT 4, E", 2, 2, &bit_4_e},
	[BIT_4_H] = {"BIT 4, H", 2, 2, &bit_4_h},
	[BIT_4_L] = {"BIT 4, L", 2, 2, &bit_4_l},
	[BIT_4_HL] = {"BIT 4, (HL)", 2, 3, &bit_4_hl},
	[BIT_4_A] = {"BIT 4, B", 2, 2, &bit_4_a},

	[BIT_5_B] = {"BIT 5, B", 2, 2, &bit_5_b},
	[BIT_5_C] = {"BIT 5, C", 2, 2, &bit_5_c},
	[BIT_5_D] = {"BIT 5, D", 2, 2, &bit_5_d},
	[BIT_5_E] = {"BIT 5, E", 2, 2, &bit_5_e},
	[BIT_5_H] = {"BIT 5, H", 2, 2, &bit_5_h},
	[BIT_5_L] = {"BIT 5, L", 2, 2, &bit_5_l},
	[BIT_5_HL] = {"BIT 5, (HL)", 2, 3, &bit_5_hl},
	[BIT_5_A] = {"BIT 5, B", 2, 2, &bit_5_a},

	[BIT_6_B] = {"BIT 6, B", 2, 2, &bit_6_b},
	[BIT_6_C] = {"BIT 6, C", 2, 2, &bit_6_c},
	[BIT_6_D] = {"BIT 6, D", 2, 2, &bit_6_d},
	[BIT_6_E] = {"BIT 6, E", 2, 2, &bit_6_e},
	[BIT_6_H] = {"BIT 6, H", 2, 2, &bit_6_h},
	[BIT_6_L] = {"BIT 6, L", 2, 2, &bit_6_l},
	[BIT_6_HL] = {"BIT 6, (HL)", 2, 3, &bit_6_hl},
	[BIT_6_A] = {"BIT 6, B", 2, 2, &bit_6_a},

	[BIT_7_B] = {"BIT 7, B", 2, 2, &bit_7_b},
	[BIT_7_C] = {"BIT 7, C", 2, 2, &bit_7_c},
	[BIT_7_D] = {"BIT 7, D", 2, 2, &bit_7_d},
	[BIT_7_E] = {"BIT 7, E", 2, 2, &bit_7_e},
	[BIT_7_H] = {"BIT 7, H", 2, 2, &bit_7_h},
	[BIT_7_L] = {"BIT 7, L", 2, 2, &bit_7_l},
	[BIT_7_HL] = {"BIT 7, (HL)", 2, 3, &bit_7_hl},
	[BIT_7_A] = {"BIT 7, B", 2, 2, &bit_7_a},
	
	/*0x80 - 0xbf*/
	[RES_0_B] = {"RES 0, B", 2, 2, &res_0_b},
	[RES_0_C] = {"RES 0, C", 2, 2, &res_0_c},
	[RES_0_D] = {"RES 0, D", 2, 2, &res_0_d},
	[RES_0_E] = {"RES 0, E", 2, 2, &res_0_e},
	[RES_0_H] = {"RES 0, H", 2, 2, &res_0_h},
	[RES_0_L] = {"RES 0, L", 2, 2, &res_0_l},
	[RES_0_HL] = {"RES 0, (HL)", 2, 4, &res_0_hl},
	[RES_0_A] = {"RES 0, A", 2, 2, &res_0_a},
	
	[RES_1_B] = {"RES 1, B", 2, 2, &res_1_b},
	[RES_1_C] = {"RES 1, C", 2, 2, &res_1_c},
	[RES_1_D] = {"RES 1, D", 2, 2, &res_1_d},
	[RES_1_E] = {"RES 1, E", 2, 2, &res_1_e},
	[RES_1_H] = {"RES 1, H", 2, 2, &res_1_h},
	[RES_1_L] = {"RES 1, L", 2, 2, &res_1_l},
	[RES_1_HL] = {"RES 1, (HL)", 2, 4, &res_1_hl},
	[RES_1_A] = {"RES 1, A", 2, 2, &res_1_a},

	[RES_2_B] = {"RES 2, B", 2, 2, &res_2_b},
	[RES_2_C] = {"RES 2, C", 2, 2, &res_2_c},
	[RES_2_D] = {"RES 2, D", 2, 2, &res_2_d},
	[RES_2_E] = {"RES 2, E", 2, 2, &res_2_e},
	[RES_2_H] = {"RES 2, H", 2, 2, &res_2_h},
	[RES_2_L] = {"RES 2, L", 2, 2, &res_2_l},
	[RES_2_HL] = {"RES 2, (HL)", 2, 4, &res_2_hl},
	[RES_2_A] = {"RES 2, A", 2, 2, &res_2_a},
	
	[RES_3_B] = {"RES 3, B", 2, 2, &res_3_b},
	[RES_3_C] = {"RES 3, C", 2, 2, &res_3_c},
	[RES_3_D] = {"RES 3, D", 2, 2, &res_3_d},
	[RES_3_E] = {"RES 3, E", 2, 2, &res_3_e},
	[RES_3_H] = {"RES 3, H", 2, 2, &res_3_h},
	[RES_3_L] = {"RES 3, L", 2, 2, &res_3_l},
	[RES_3_HL] = {"RES 3, (HL)", 2, 4, &res_3_hl},
	[RES_3_A] = {"RES 3, A", 2, 2, &res_3_a},

	[RES_4_B] = {"RES 4, B", 2, 2, &res_4_b},
	[RES_4_C] = {"RES 4, C", 2, 2, &res_4_c},
	[RES_4_D] = {"RES 4, D", 2, 2, &res_4_d},
	[RES_4_E] = {"RES 4, E", 2, 2, &res_4_e},
	[RES_4_H] = {"RES 4, H", 2, 2, &res_4_h},
	[RES_4_L] = {"RES 4, L", 2, 2, &res_4_l},
	[RES_4_HL] = {"RES 4, (HL)", 2, 4, &res_4_hl},
	[RES_4_A] = {"RES 4, A", 2, 2, &res_4_a},
	
	[RES_5_B] = {"RES 5, B", 2, 2, &res_5_b},
	[RES_5_C] = {"RES 5, C", 2, 2, &res_5_c},
	[RES_5_D] = {"RES 5, D", 2, 2, &res_5_d},
	[RES_5_E] = {"RES 5, E", 2, 2, &res_5_e},
	[RES_5_H] = {"RES 5, H", 2, 2, &res_5_h},
	[RES_5_L] = {"RES 5, L", 2, 2, &res_5_l},
	[RES_5_HL] = {"RES 5, (HL)", 2, 4, &res_5_hl},
	[RES_5_A] = {"RES 5, A", 2, 2, &res_5_a},

	[RES_6_B] = {"RES 6, B", 2, 2, &res_6_b},
	[RES_6_C] = {"RES 6, C", 2, 2, &res_6_c},
	[RES_6_D] = {"RES 6, D", 2, 2, &res_6_d},
	[RES_6_E] = {"RES 6, E", 2, 2, &res_6_e},
	[RES_6_H] = {"RES 6, H", 2, 2, &res_6_h},
	[RES_6_L] = {"RES 6, L", 2, 2, &res_6_l},
	[RES_6_HL] = {"RES 6, (HL)", 2, 4, &res_6_hl},
	[RES_6_A] = {"RES 6, A", 2, 2, &res_6_a},
	
	[RES_7_B] = {"RES 7, B", 2, 2, &res_7_b},
	[RES_7_C] = {"RES 7, C", 2, 2, &res_7_c},
	[RES_7_D] = {"RES 7, D", 2, 2, &res_7_d},
	[RES_7_E] = {"RES 7, E", 2, 2, &res_7_e},
	[RES_7_H] = {"RES 7, H", 2, 2, &res_7_h},
	[RES_7_L] = {"RES 7, L", 2, 2, &res_7_l},
	[RES_7_HL] = {"RES 7, (HL)", 2, 4, &res_7_hl},
	[RES_7_A] = {"RES 7, A", 2, 2, &res_7_a},

	/*0xc0 - 0xff*/
	[SET_0_B] = {"SET 0, B", 2, 2, &set_0_b},
	[SET_0_C] = {"SET 0, C", 2, 2, &set_0_c},
	[SET_0_D] = {"SET 0, D", 2, 2, &set_0_d},
	[SET_0_E] = {"SET 0, E", 2, 2, &set_0_e},
	[SET_0_H] = {"SET 0, H", 2, 2, &set_0_h},
	[SET_0_L] = {"SET 0, L", 2, 2, &set_0_l},
	[SET_0_HL] = {"SET 0, (HL)", 2, 4, &set_0_hl},
	[SET_0_A] = {"SET 0, A", 2, 2, &set_0_a},

	[SET_1_B] = {"SET 1, B", 2, 2, &set_1_b},
	[SET_1_C] = {"SET 1, C", 2, 2, &set_1_c},
	[SET_1_D] = {"SET 1, D", 2, 2, &set_1_d},
	[SET_1_E] = {"SET 1, E", 2, 2, &set_1_e},
	[SET_1_H] = {"SET 1, H", 2, 2, &set_1_h},
	[SET_1_L] = {"SET 1, L", 2, 2, &set_1_l},
	[SET_1_HL] = {"SET 1, (HL)", 2, 4, &set_1_hl},
	[SET_1_A] = {"SET 1, A", 2, 2, &set_1_a},

	[SET_2_B] = {"SET 2, B", 2, 2, &set_2_b},
	[SET_2_C] = {"SET 2, C", 2, 2, &set_2_c},
	[SET_2_D] = {"SET 2, D", 2, 2, &set_2_d},
	[SET_2_E] = {"SET 2, E", 2, 2, &set_2_e},
	[SET_2_H] = {"SET 2, H", 2, 2, &set_2_h},
	[SET_2_L] = {"SET 2, L", 2, 2, &set_2_l},
	[SET_2_HL] = {"SET 2, (HL)", 2, 4, &set_2_hl},
	[SET_2_A] = {"SET 2, A", 2, 2, &set_2_a},

	[SET_3_B] = {"SET 3, B", 2, 2, &set_3_b},
	[SET_3_C] = {"SET 3, C", 2, 2, &set_3_c},
	[SET_3_D] = {"SET 3, D", 2, 2, &set_3_d},
	[SET_3_E] = {"SET 3, E", 2, 2, &set_3_e},
	[SET_3_H] = {"SET 3, H", 2, 2, &set_3_h},
	[SET_3_L] = {"SET 3, L", 2, 2, &set_3_l},
	[SET_3_HL] = {"SET 3, (HL)", 2, 4, &set_3_hl},
	[SET_3_A] = {"SET 3, A", 2, 2, &set_3_a},

	[SET_4_B] = {"SET 4, B", 2, 2, &set_4_b},
	[SET_4_C] = {"SET 4, C", 2, 2, &set_4_c},
	[SET_4_D] = {"SET 4, D", 2, 2, &set_4_d},
	[SET_4_E] = {"SET 4, E", 2, 2, &set_4_e},
	[SET_4_H] = {"SET 4, H", 2, 2, &set_4_h},
	[SET_4_L] = {"SET 4, L", 2, 2, &set_4_l},
	[SET_4_HL] = {"SET 4, (HL)", 2, 4, &set_4_hl},
	[SET_4_A] = {"SET 4, A", 2, 2, &set_4_a},

	[SET_5_B] = {"SET 5, B", 2, 2, &set_5_b},
	[SET_5_C] = {"SET 5, C", 2, 2, &set_5_c},
	[SET_5_D] = {"SET 5, D", 2, 2, &set_5_d},
	[SET_5_E] = {"SET 5, E", 2, 2, &set_5_e},
	[SET_5_H] = {"SET 5, H", 2, 2, &set_5_h},
	[SET_5_L] = {"SET 5, L", 2, 2, &set_5_l},
	[SET_5_HL] = {"SET 5, (HL)", 2, 4, &set_5_hl},
	[SET_5_A] = {"SET 5, A", 2, 2, &set_5_a},

	[SET_6_B] = {"SET 6, B", 2, 2, &set_6_b},
	[SET_6_C] = {"SET 6, C", 2, 2, &set_6_c},
	[SET_6_D] = {"SET 6, D", 2, 2, &set_6_d},
	[SET_6_E] = {"SET 6, E", 2, 2, &set_6_e},
	[SET_6_H] = {"SET 6, H", 2, 2, &set_6_h},
	[SET_6_L] = {"SET 6, L", 2, 2, &set_6_l},
	[SET_6_HL] = {"SET 6, (HL)", 2, 4, &set_6_hl},
	[SET_6_A] = {"SET 6, A", 2, 2, &set_6_a},

	[SET_7_B] = {"SET 7, B", 2, 2, &set_7_b},
	[SET_7_C] = {"SET 7, C", 2, 2, &set_7_c},
	[SET_7_D] = {"SET 7, D", 2, 2, &set_7_d},
	[SET_7_E] = {"SET 7, E", 2, 2, &set_7_e},
	[SET_7_H] = {"SET 7, H", 2, 2, &set_7_h},
	[SET_7_L] = {"SET 7, L", 2, 2, &set_7_l},
	[SET_7_HL] = {"SET 7, (HL)", 2, 4, &set_7_hl},
	[SET_7_A] = {"SET 7, A", 2, 2, &set_7_a},
};
