#include <stdio.h>
#include <stdbool.h>

#include "status.h"
#include "memory.h"
#include "registers.h"
#include "interrupt.h"
#include "rom.h"
#include "cpu.h"
#include "gpu.h"

struct Test {
	unsigned char a;
	unsigned char b;
};

struct Test t = {0};

void print(unsigned char a){
	printf("%d\n", a);
}

unsigned int counter = 0;

void print_debug() {
	printf("Counter is: %d\n", counter);
	counter++;
}

status main(int argc, char* argv[]) {
	bool running = true;

	/*Initialize registers*/
	initialize_registers();

	/*Initialize memory*/
	initialize_memory();

	/*Initiate CPU*/
	initiate_cpu();
	
	/*Load ROM*/
	char* gamefile;

	if (!(argc == 2)) {
		return INCORRECT_AMOUNT_OF_CLI_ARGUMENTS_GIVEN;
	}

	gamefile = argv[1];

	loadROM(gamefile);

	/*Initiate Graphics*/
	initialize_glfw();
	GLFWwindow* window = create_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Game Window");
	initialize_glad();

	clear_background(window);

	unsigned int vertex_shader = create_vertex_shader();
	unsigned int fragment_shader = create_fragment_shader();
	initialize_buffers();
	link_shaders(vertex_shader, fragment_shader);

	/*Main loop*/
	while (running) {
		interruptCheck();
		print_debug();
		cpuStep();
		if (gpuStep(window) == -1) {
			running = false;
		}
	}

	/*
	struct Instruction instruction = {"INC B", 1, 1, &inc_b};
	registers.b = 10;
	execute_instruction(&instruction);
	printf("value is: %d\n", registers.b);
	*/

	/*
	unsigned char a = 0xff;
	printf("Value is: %d\n", a);
	a++;
	printf("Value is: %d\n", a);
	*/

	/*
	unsigned char a = 10;
	print(a++);
	print(a);
	*/

	/*
	printf("Value: %d\n", t.a);
	printf("Value: %d\n", t.b);
	t.b = 1;
	t.a = t.b;
	t.b = 2;
	printf("Value: %d\n", t.a++);
	printf("Value: %d\n", t.b);
	printf("Value: %d\n", t.a);
	printf("Value: %d\n", t.b);
	*/
	
	/*
	char* gamefile;

	if (!(argc == 2)){
		return INCORRECT_AMOUNT_OF_CLI_ARGUMENTS_GIVEN;
	}

	gamefile = argv[1];

	initialize_memory();
	loadROM(gamefile);
	*/

	/*
	unsigned char data;
	unsigned short data2;

	readByte(0x40, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x41, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x42, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x43, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x44, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x45, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x46, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x47, &data);
	printf("The data is: 0x%01x\n", data);

	
	readShort(0x41, &data2);
	printf("The data is: 0x%02x\n", data2);

	printf("------------------------------------\n");

	readByte(0x48, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x49, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x4a, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x4b, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x4c, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x4d, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x4e, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x4f, &data);
	printf("The data is: 0x%01x\n", data);

	printf("------------------------------------\n");

	readByte(0x50, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x51, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x52, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x53, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x54, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x55, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x56, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x57, &data);
	printf("The data is: 0x%01x\n", data);

	printf("------------------------------------\n");

	readByte(0x58, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x59, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x5a, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x5b, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x5c, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x5d, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x5e, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x5f, &data);
	printf("The data is: 0x%01x\n", data);

	printf("------------------------------------\n");

	readByte(0x60, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x61, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x62, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x63, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x64, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x65, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x66, &data);
	printf("The data is: 0x%01x\n", data);
	readByte(0x67, &data);
	printf("The data is: 0x%01x\n", data);

	printf("------------------------------------\n");
	*/

	/*
	initialize_registers();
	printf("Initialized Registers\n");
	initialize_memory();
	printf("Initialized Memory\n");
	initiate_cpu();
	printf("Initialized CPU\n");

	memory.memory[0x100] = 0x1;
	memory.memory[0x101] = 0xcd;
	memory.memory[0x102] = 0xab;

	print_registers();

	cpuStep();
	printf("------------------------------------\n");

	print_registers();
	printf("------------------------------------\n");

	printf("The bc register value is: %x\n", registers.bc);

	print_cycles();
	*/




	/*
	registers.af = 0x10;
	print_registers(&registers);
	*/

	/*
	unsigned short address = 0xffff;
	char data = 'a';
	char read_data;
		
	printf("The data to write is %c\n", data);

	initialize_memory();
	writeByte(address, &data);
	readByte(address, &read_data);

	printf("The data that was written to the memory is %c\n", read_data);

	printf("The interrupt enable register value is 0x%04x\n", memory.interrupt_enable);
	printf("The interrupt enable register value is 0x%04x\n", memory.memory[0xffff]);
	*/

	/*
	unsigned short address = 0xbbbb;
	unsigned short data = 0xabcd;
	unsigned short read_data;

	printf("The data to write is 0x%x\n", data);

	initialize_memory();
	writeShort(address, &data);
	readShort(address, &read_data);

	printf("The data that was written to the memory is 0x%x\n", read_data);
	*/
	
	return SUCCESS;
}