#ifndef __USER_H
#define __USER_H
#include "kbd.h"
#include "vgaterm.h"
#include "timer.h"
#include "zbase.h"
#include "scrio.h"
#include "panic.h"
#include "readDate.h"
#include "stdlib/printf.h"
void startZ(bool startwin);
void reboot()
{
	asm("int $50");
}
void nop()
{}
void fsinit();
void textEdit()
{
	drawmain();
	int curposX = 0;
	int curposY = 0;
	int charNum = 0;
	int tfNum = 0;
	bool caps = false;
	char c;
	window editor(71,23,3,2,"365 Editor","");
	drawObj(editor);
	printw("Press F5 to exit. Files cannot be saved today.",editor);
	printf("Hello, %s!","World");
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
/*			if(c == 0x3D)
			{
				int i = 0;
				char * fn;
				do
				{
					if(inb(0x60)!=c)
					{	
						c = inb(0x60);
						if(c>0)
						{
							if(caps == false)
							{
							terminal_putchar(scancode[c+1]);
							fn[i] = scancode[c+1];
							}
							else
							{
							terminal_putchar(scancode[c+1+90]);
							fn[i] = scancode[c+1+90];
							}
						}
					}
					nop();
					i++;
				} while(c!=28);
				textFiles[tfNum].filename = fn;
				tfNum++;
				kprint("YEEES");
			}*/
			if(c == 0x0E)
			{
				if(curposX != 0)
				{
					if(curposY != 0)
					{
						curposX--;
						goToPos(terminal_column-1,terminal_row);
						terminal_putchar(' ');
						goToPos(terminal_column-1,terminal_row);
						charNum--;
					}
				}
				else
				{
					curposY--;
					curposX = 68;
					goToPos(editor.x+1+curposX,editor.y+3+curposY);
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
			if(c == 28)
			{
				curposY++;
				curposX = 0;
				goToPos(editor.x+1+curposX,editor.x+2+curposY);
				goto skip2;
			}
			if(c>0)
			{
				if(caps == false)
				terminal_putchar(scancode[c+1]);
				else
				terminal_putchar(scancode[c+1+90]);
				curposX++;
			}
		}
		skip2:
		nop();
		charNum++;
	} while(c!=0x3F);
	startZ(true);
}
void calc()
{
	drawmain();
	window calc(30,20,5,3,"365 Calculator","");
/*	printw("\
 -------\n\
/        \\\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
|        |\n\
\\        /\n\
 -------- \n\
",calc);
*/
	drawObj(calc);
	printw("/--------------------------\\\n |                          |\n\\--------------------------/", calc);
	goToPos(calc.x+2,calc.y+4);
	int n1[4];
	int n2[4];
	int i;
	char c;
	char action;
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			if(c>0)
			{
				switch(scancode[c+1])
				{
				case '1':
				terminal_putchar('1'); break;
				case '2':
				terminal_putchar('2'); break;
				case '3':
				terminal_putchar('3'); break;
				case '4':
				terminal_putchar('4'); break;
				case '5':
				terminal_putchar('5'); break;
				case '6':
				terminal_putchar('6'); break;
				case '7':
				terminal_putchar('7'); break;
				case '8':
				terminal_putchar('8'); break;
				case '9':
				terminal_putchar('9'); break;
				case '0':
				terminal_putchar('0'); break;

				}
			}
		}
		skip2:
		nop();
		i++;
	} while(c!=1);
} 
void toDoList()
{
	drawmain();
	window todolist(30,16,5,5,"365 To-Do List","");
	drawObj(todolist);
	printw("Welcome.\n1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10.",todolist);
	char * list[10];
	int num = 1;
	kprint("OK1");
	goToPos(todolist.x+1,todolist.y+4);
	char c = 0;
	int i = 0;
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			if(c == 28)
			{
				goto end;
			}
			if(c>0)
			{
				list[num][i] = scancode[c+1];
				terminal_putchar(scancode[c+1]);
			}
		}
		skip2:
		nop();
		i++;
		num++;
		end:
		goToPos(todolist.x+1,todolist.y+4+num);
	} while(true);
}
void info()
{
	drawmain();
	window info(31,9,40,5,"OS365 Info","");
	drawObj(info);
	printw("OS365 ver. 1.0.1, kernel 1.0,\nZ Window System 1.0.\nRelease date: 12/04/15",info);
	waitForKey(0x2D);
	terminal_setcolor(COLOR_LIGHT_GREY + COLOR_BLACK);
	startZ(true);
}
void shutdown()
{
	outw(0xB004, 0x0 | 0x2000);
}
void authors()
{
	drawmain();
	window authors(40,19,40,5,"OS365 Authors","");
	drawObj(authors);
 	printw("Programming  Nikita Ivanov\n       Original OS name  Igor Ivanov\nZ Window System  Nikita Ivanov\nSecond Developer  Roman Zhikharevich\nHelped  Mitrofan Iskra",authors);
	terminal_putchar(3);
	waitForKey(0x2D);
	terminal_setcolor(COLOR_LIGHT_GREY + COLOR_BLACK);
	startZ(true);
}
void console()
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
	startZ(true);
}
void panicGen()
{
	drawmain();
	window question(40,10,40,5,"Question","");
	drawObj(question);
	printw("Are you sure you want to panic?\n        If you do it, system will halt\nand you will need to restart\nyour computer. Press Y to continue.",question);
	waitForKey(0x15);
	panic("Manually generated.");
}
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
	goToPos(goMenu.x+1,goMenu.y+7);
	kprint("Reboot");
	goToPos(goMenu.x+1,goMenu.y+8);
	kprint("Text Editor");
	goToPos(goMenu.x+1,goMenu.y+9);
	kprint("Shutdown");
	goToPos(1,8);
	terminal_setcolor(52);
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
					goToPos(goMenu.x+1,goMenu.y+7);
					kprint("Reboot");
					goToPos(goMenu.x+1,goMenu.y+8);
					kprint("Text Editor");
					goToPos(goMenu.x+1,goMenu.y+9);
					kprint("Shutdown");
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
						case 5:
						kprint("Reboot"); break;
						case 6:
						kprint("Text Editor"); break;
						case 7:
						kprint("Shutdown"); break;
					}
				}
			}
			if(c == 0x50)
			{
				if(selection<7)
				{
					selection++;
					terminal_setcolor(26);
					printw("OS Info\nAuthors\n",goMenu);
					kprint("Drop to command prompt");
					goToPos(goMenu.x+1,goMenu.y+6);
					kprint("Panic");
					goToPos(goMenu.x+1,goMenu.y+7);
					kprint("Reboot");
					goToPos(goMenu.x+1,goMenu.y+8);
					kprint("Text Editor");
					goToPos(goMenu.x+1,goMenu.y+9);
					kprint("Shutdown");
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
						case 5:
						kprint("Reboot"); break;
						case 6:
						kprint("Text editor"); break;
						case 7:
						kprint("Shutdown"); break;
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
		info(); break;
		}
		case 2:
		{
		authors(); break;
		}
		case 3:
		{
		console(); break;
		}
		case 4:
		{
		panicGen(); break;
		}
		case 5:
		{
		reboot(); break;
		}
		case 6:
		{
		textEdit(); break;
		}
		case 7:
		{
		shutdown(); break;
		}
	}
}
void startZ(bool startwin)
{
	char c;
	terminal_setcolor(COLOR_LIGHT_GREY + COLOR_BLACK);
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
	terminal_setcolor(0x85);
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
#endif
