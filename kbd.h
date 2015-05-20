#ifndef __KBD_H
#define __KBD_H
#include "io.h"
#include "graphics.h"
void waitForKey(int key)
{
	char c;
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
		}
		skip:
		int noop=0;
	}
	while(c!=key);
	return;
}
char* gets(word x,word y)
{
	char c;
	char* ret;
	int i = 0;
	bool caps = false;
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			if(c == 0x0E)
			{
				if(x != 0)
				{
					if(y != 0)
					{
						x = x - 8;
						vgaPutchar(' ',x,y,MAGENTA,LIGHT_GREY);
					}
				}
				else
				{
					y = y - 8;
					x = 639;
				}
				goto skip2;
			}
			if(c == 0x3A)
			{
				if(caps == false)
				caps = true;
				else
				caps = false;
				goto skip2;
			}
			if(c>0)
			{
			if(caps == false)
			{
			ret[i] = scancode[c+1];
			vgaPutchar(scancode[c+1],x,y,MAGENTA,LIGHT_GREY);
			}
			else
			{
			ret[i] = scancode[c+1+90];
			vgaPutchar(scancode[c+1+90],x,y,MAGENTA,LIGHT_GREY);
			}
			i++; x = x + 8;
			}
		}
		skip2:
		caps = caps;
	}
	while(c!=28);
	return ret;
}
#endif
