//OS365 main kernel file.
#define __os365__
#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include "vgaterm.h" //VGA text driver
#include "panic.h" //kernel panic
#include "decls.h"
#include "io.h" //I/O ports
#include "ring3.h" //not used now
#include "paging.h"
#include "hdd.h"
#include "os365.h"
#include "scrio.h"
#include "fonts.h"
#if defined(__linux__)
#error "Compiling is not allowed without the cross-compiler"
#endif
#if defined(__cplusplus)
extern "C"
#endif
void kernel_main()
{
	setupFonts();
	kprint("OS365 Kernel 1.0 is loaded.\nInitializing PIC...",0,0);
	init_pics(0x20,0x28);
	kprint("\nAll pre-start processes are finished. Preparing to load shell...\n",0,8);
	/*
	gdt_entry_bits *code;
	gdt_entry_bits *data;
	gdt_entry_bits gdt[50];
	//I assume your ring 0 segments are in gdt[1] and gdt[2] (0 is null segment)
	code=(void*)&gdt[3]; //gdt is a static array of gdt_entry_bits or equivalent
	data=(void*)&gdt[4];
	code->limit_low=0xFFFF;
	code->base_low=0;
	code->accessed=0;
	code->read_write=1; //make it readable for code segments
	code->conforming=0; //don't worry about this.. 
	code->code=1; //this is to signal its a code segment
	code->always_1=1;
	code->DPL=3; //set it to ring 3
	code->present=1;
	code->limit_high=0xF;
	code->available=1;
	code->always_0=0;
	code->big=1; //signal it's 32 bits
	code->gran=1; //use 4k page addressing
	code->base_high=0;
	*data=*code; //copy it all over, cause most of it is the same
	data->code=0; //signal it's not code; so it's data.
 
	write_tss(&gdt[5]); //we'll implement this function later... 
	_jump_usermode();
	*/
//	createpage();
//	loadPageDirectory(page_directory);
//	enablePaging();
	setGraphicsMode();
	shellStart();
}
