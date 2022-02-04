#include "interrupt.h"
#include "registers.h"
#include "memory.h"
#include "cpu.h"

status initialize_interrupts(){
	interrupts.interrupt_master_enable_flag = 0x1;
	interrupts.interrupts = &interrupt_types;

	return SUCCESS;
}

/*
	This function implements an interrupt handler.

	For now it will handle just ONE interrupt (according to the priority) - No multiple needed beacuse we are using "1 cpu core" and things are sync.
	Future expension can be running on multiple cpu core (means async) - so we will have to change this implementation (to support multiple interrupts).
*/
void handle_interrupt(struct Interrupt interrupt){
	interrupts.interrupt_master_enable_flag = false;
	pushStack(registers.pc);
	registers.pc = interrupt.address;
	return;
}

void set_interrupt_flag(unsigned char bit) {
	unsigned char interrupt_flag;
	readByte(INTERRUPT_FLAG_ADDRESS, &interrupt_flag);
	interrupt_flag = interrupt_flag | (1 << bit);
	writeByte(INTERRUPT_FLAG_ADDRESS, &interrupt_flag);
	return;
}

void reset_interrupt_flag(unsigned char bit){
	unsigned char interrupt_flag;
	readByte(INTERRUPT_FLAG_ADDRESS, &interrupt_flag);
	interrupt_flag = interrupt_flag & (!(1 << bit));
	writeByte(INTERRUPT_FLAG_ADDRESS, &interrupt_flag);
	return;
}

/*
	This function implements an interrupt check.

	*The mechanism isn't checked completley:
		Now just the reti instruction resets the interrupt_master_enable_flag (check if okay)
		Also the cpu continues execution but won't accept more interrupts because of the interrupt_master_enable_flag
		(check if mechanism works correctly)
*/
void interruptCheck(){
	unsigned char interrupt_flag;
	unsigned char interrupt_enable;

	readByte(INTERRUPT_FLAG_ADDRESS, &interrupt_flag);
	readByte(INTERRUPT_ENABLE_ADDRESS, &interrupt_enable);

	if (interrupt_enable & interrupt_flag){

		if (interrupts.interrupt_master_enable_flag){

			if (cpu.halt) {
				cpu.halt = false;
			}

			if (interrupt_flag & (1 << VBLANK)) {
				handle_interrupt(interrupts.interrupts[VBLANK]);
				reset_interrupt_flag(VBLANK);
				return SUCCESS;
			}

			else if (interrupt_flag & (1 << LCD_STAT)) {
				handle_interrupt(interrupts.interrupts[LCD_STAT]);
				reset_interrupt_flag(LCD_STAT);
				return SUCCESS;
			}

			else if (interrupt_flag & (1 << TIMER)) {
				handle_interrupt(interrupts.interrupts[TIMER]);
				reset_interrupt_flag(TIMER);
				return SUCCESS;
			}

			else if (interrupt_flag & (1 << SERIAL)) {
				handle_interrupt(interrupts.interrupts[SERIAL]);
				reset_interrupt_flag(SERIAL);
				return SUCCESS;
			}

			else if (interrupt_flag & (1 << JOYPAD)) {
				handle_interrupt(interrupts.interrupts[JOYPAD]);
				reset_interrupt_flag(JOYPAD);
				return SUCCESS;
			}

			return INTERRUPT_NOT_FOUND_ERROR;
		}
		
		else {
			if (cpu.halt){
				cpu.halt = false;
			}
		}

	}

	return SUCCESS;
}