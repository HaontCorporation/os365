#include "vgaterm.h"
char scancode[] = "   1234567890-=^^qwertyuiop[]\n^asdfghjkl;'`  zxcvbnm,./^*^   ^^^^^^^^^^^^^^789-456+1230.^^";
class window {
	public:
	size_t width;
	size_t height;
	size_t x;
	size_t y;
	const char * caption;
	const char * text;
	window(size_t width, size_t height, size_t x, size_t y, const char * caption, const char * text_);
};
window::window(size_t width_, size_t height_, size_t x_, size_t y_, const char * caption_, const char * text_)
{
	width=width_;
	height=height_;
	x=x_;
	y=y_;
	caption=caption_;
	text=text_;
}
class Widget {
	public:
	size_t width;
	size_t height;
	size_t x;
	size_t y;
};
class button : public Widget {
	public:
	const char * text;
	void onPress()
	{
		
	}
};
void printw(const char * msg, window wnd);
bool drawObj(window target);
void z_init();
void delWin(window wnd)
{
	goToPos(wnd.x,wnd.y);
	int newy = wnd.y;
	for(int i = 10; i < wnd.height; i++)
	{
		for(int j = 10; j < wnd.width; j++)
		{
			kprint(" ");
		}
		newy--;
		goToPos(wnd.x-wnd.width,newy);
	}
}
void drawmain()
{
		terminal_setcolor(COLOR_LIGHT_GREY + COLOR_BLACK);
		z_init();
		terminal_setcolor(25);
		goToPos(0,0);
		kprint(" OS365 Kernel 1.0, Z Window System 1.0.                                         ");
		goToPos(0,24);
		kprint(" Press left CTRL to display a menu.                                             ");
		window welcome(30,10,5,5,"Welcome to Z Window System!","");
		drawObj(welcome);
		printw("Welcome to Z Window System!\n AAll is working fine.",welcome);
}
bool drawObj(window target)
{
	terminal_setcolor(26);
	goToPos(target.x, target.y);
	terminal_putchar('-');
	for(size_t topcount = 0; topcount < target.width - 2; topcount++)
	{
		terminal_putchar('-');
	}
	terminal_putchar('-');
	for(size_t middlecount = 1; middlecount < target.height - 2; middlecount++)
	{
		goToPos(target.x, target.y+middlecount);
		terminal_putchar('|');
		for(size_t middlecount2 = 0; middlecount2 < target.width - 2; middlecount2++)
		{
			terminal_putchar(' ');
		}
		terminal_putchar('|');
	}
	goToPos(target.x, target.y+target.height-2);
	terminal_putchar('-');
	for(size_t bcount = 0; bcount < target.width - 2; bcount++)
	{
		terminal_putchar('-');
	}
	terminal_putchar('-');
	goToPos(target.x, target.y+2);
	terminal_putchar('|');
	for(size_t captioncount = 0; captioncount < target.width - 2; captioncount++)
	{
		terminal_putchar('-');
	}
	terminal_putchar('|');
	goToPos(target.x+1, target.y+1);
	terminal_writestring(target.caption);
	goToPos(target.x+1, target.y + 3);
	terminal_writestring(target.text);
	return true;
}
void printw(const char * text, window wnd) //Print the text in the window.
{
	size_t currentln = 0; //for new line handling
	goToPos(wnd.x+1, wnd.y + 3); //go to inner upper left corner of the window
	size_t size = strlen(text); //string length
	for(size_t i = 0; i < size; i++)
	{
		if(i == wnd.width)
		goToPos(wnd.x+1, wnd.y + 3+currentln);
		if(text[i] != '\n')//new line handling
		terminal_putchar(text[i]);
		else
		{
			goToPos(wnd.x+1, wnd.y+3+currentln+1);
			currentln++;
			
		}
	}
}
void z_init()
{
	terminal_writestring("Z Window System is loading...");
	goToPos(0,0);
	for(size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
			
		}
	}
	
}
