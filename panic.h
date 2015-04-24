#ifndef __PANIC_H
#define __PANIC_H
#include "vgaterm.h"
#include "scrio.h"
#include "serial.h"
#include "zbase.h"
	uint8_t eax = 0;
	uint8_t ebx = 0;
	uint8_t ecx = 0;
	uint8_t esi = 0;
void panic(const char* msg)
{
	outb(COM1,0xDEADFACE); //if runned on emulator or hardware debugger is connected to COM1, it will receive it.
	terminal_setcolor(29);
	for(size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
			
		}
	}
	goToPos(0,0);
	terminal_setcolor(48);
	terminal_writestring("Kernel panic: ");
	terminal_writestring(msg);
	terminal_writestring(" ");
	asm("mov 0, %eax");
	asm("mov 0, %ebx");
	asm("mov 0, %ecx");
	asm("mov 0, %esi");
	outb(COM1,0xFACEBEEF); //variable nulling is started
	kprint("OS365 is halted. Please restart your computer.");
	goToPos(0,10);
	kprint("/--------------\\\n\
|              |\n\
|  .        .  |\n\
|              |\n\
|  |    |      |\n\
|       |      |\n\
|  .           |\n\
| /----------\\ |\n\
|              |\n\
\\--------------/\n\
");
	terminal_row = 0;
	terminal_column = 0;
	outb(COM1,0xDEADDEAD); //The last signal from OS before crashing.
	asm("cli");
	asm("hlt");
}
#endif
