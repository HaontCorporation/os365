#ifndef __OS365_H
#define __OS365_H
#include "vgaterm.h"
#include "user.h"
#include "scrio.h"
#include "zbase.h"
#include "io.h"
#define nostartwin false
void cmd_handle(char * cmd)
{
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
	//kprint("OS365 1.0 is started.\nLoading shell...");
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
