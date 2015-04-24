#include "zbase.h"
#include "kbd.h"
#include "sysroot/usr/include/stdio.h"
void startZ(bool nostartwin);
void gomenu()
{
	char c;
	int selection = 1;
	window goMenu(30,20,0,5,"Go! Menu","");
	terminal_setcolor(26);
	drawObj(goMenu);
	printw("OS Info\nAuthors\n",goMenu);
	kprint("Drop to command prompt");
	goToPos(goMenu.x+1,goMenu.y+6);
	kprint("Panic");
	goToPos(1,8);
	terminal_setcolor(52);
	printf("testig");
	kprint("OS Info");
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			if(c == 0x48)
			{
				if(selection!=1)
				{
					selection--;
					terminal_setcolor(26);
					printw("OS Info\nAuthors\n",goMenu);
					kprint("Drop to command prompt");
					goToPos(goMenu.x+1,goMenu.y+6);
					kprint("Panic");
					goToPos(goMenu.x+1,goMenu.y+2+selection);
					terminal_setcolor(52);
					switch(selection)
					{
						case 1:
						kprint("OS Info"); break;
						case 2:
						kprint("Authors"); break;
						case 3:
						kprint("Drop to command prompt"); break;
						case 4:
						kprint("Panic"); break;
					}
				}
			}
			if(c == 0x50)
			{
				if(selection<4)
				{
					selection++;
					terminal_setcolor(26);
					printw("OS Info\nAuthors\n",goMenu);
					kprint("Drop to command prompt");
					goToPos(goMenu.x+1,goMenu.y+6);
					kprint("Panic");
					goToPos(goMenu.x+1,goMenu.y+2+selection);
					terminal_setcolor(52);

					switch(selection)
					{
						case 1:
						kprint("OS Info"); break;
						case 2:
						kprint("Authors"); break;
						case 3:
						kprint("Drop to command prompt"); break;
						case 4:
						kprint("Panic"); break;
					}
				}
			}

		}
		skip:
		nop();
	}
	while(c!=28);
	switch(selection)
	{
		case 1:
		{
		drawmain();
		window info(31,9,40,5,"OS365 Info","");
		drawObj(info);
		printw("OS365 ver. 1.0.1, kernel 1.0,\n Z Window System 1.0.\nRelease date: 12/04/15\nPress X to exit.",info);
		waitForKey(0x2D);
		terminal_setcolor(COLOR_LIGHT_GREY + COLOR_BLACK);
		startZ(true); break;
		}
		case 2:
		{
		drawmain();
		window authors(35,8,40,5,"OS365 Authors","");
		drawObj(authors);
		printw("Programming  Nikita Ivanov\n        Original OS name  Igor Ivanov\nZ Window System  Nikita Ivanov",authors);
		waitForKey(0x2D);
		terminal_setcolor(COLOR_LIGHT_GREY + COLOR_BLACK);
		startZ(true); break;
		}
		case 3:
		{
		drawmain();
		window console(35,15,40,5,"Console","");
		drawObj(console);
		printw("> ",console);
		char cmd[50];
		char c = 0;
		int i = 0;
		do
		{
			if(inb(0x60)!=c)
			{
				c = inb(0x60);
				if(c == 28)
				{
					if(cmd == "test")
					kprint("working\n");
					kprint("\n >");
					for(int j; j < 50; j++)
					cmd[j] = 0;
					goto skip2;
				}
				if(c>0)
				{
					cmd[i] = scancode[c+1];
					terminal_putchar(scancode[c+1]);
				}
			}
			skip2:
			nop();
			i++;
		}
		while(c!=1);
		terminal_setcolor(COLOR_LIGHT_GREY + COLOR_BLACK);
		startZ(true); break;
		}
		case 4:
		drawmain();
		window question(40,10,40,5,"Question","");
		drawObj(question);
		printw("Are you sure you want to panic?\n        If you do it, system will halt\nand you will need to restart\nyour computer. Press Y to continue.",question);
		waitForKey(0x15);
		panic("Manually generated.");
	}
}
void startZ(bool startwin)
{
	char c;
	z_init();
	terminal_setcolor(10);
	if(startwin=true)
	{
		window welcome(30,10,5,5,"Welcome to Z Window System!","");
		drawObj(welcome);
		printw("Welcome to Z Window System!\n AAll is working fine.",welcome);
	}
	else
	{}
	terminal_setcolor(25);
	goToPos(0,0);
	kprint(" OS365 Kernel 1.0, Z Window System 1.0.                                        ");
	goToPos(0,24);
	kprint(" Press left CTRL to display a menu.                                             ");
	waitForKey(29);
	gomenu();
}
void zwin_start()
{
	window test(70,20,5,4,"OS365 ",""); //creating window
	window test2(20,10,50,1,"Multi-windows","");
	z_init();
	terminal_setcolor(30);
	goToPos(0,0);
	kprint("   OS365 Kernel 0.1, Z Window System 0.1.                     Pre-alpha 0.1     ");
	drawObj(test);
	terminal_setcolor(46);
	drawObj(test2);
	terminal_setcolor(30);
	
	printw("OS365 Z Window System is working.\nNewlines is also working.\nTODO:\n    1. Write keyboard driver\n2. Write mouse driver.\n3. Add graphic mode changing.\nOS365 is a small OS in pre-alpha stage, written almost fully in C++,\nusing ASM only for 2 functions and the kernel loader. The bootloader\nis GRUB. ", test);
	terminal_setcolor(46);
	printw("Second window\n      Multiwindowing is\nfully working.\nCool!", test2);
	goToPos(0,24);
	kprint(" OS365 0.1                                                                      ");
}
