#ifndef __OS365_H
#define __OS365_H
#include "vgaterm.h"
#include "user.h"
#define nostartwin false
void cmd_handle(char * cmd)
{
	kprint(cmd);
	if(cmd == "zstart -nostartwin")
	{
		startZ(nostartwin);
		return;
	}
	else if(cmd == "zstart")
	{
		startZ(true);
	}
}
void shellStart()
{
	init_pics(0x20,0x28);
	kprint("\n\nOS365 Shell is started.\n");
	terminal_setcolor(COLOR_LIGHT_GREY + COLOR_BLACK);
	terminal_writestring("\n\
               OS365 0.1\n\n");
	char cmd[80];
	char c;
	char dummy;
	int i = 0;
	startZ(true);
	/*
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			if(c == 28)
			{
				cmd_handle(cmd);
				kprint("\n >");
				goto skip;
			}
			if(c>0)
			{
				cmd[i] = scancode[c+1];
				terminal_putchar(scancode[c+1]);
			}
		}
		skip:
		nop();
		i++;
	}
	while(true);
	*/
}
#endif
