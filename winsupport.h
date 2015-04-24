/*
void winPaint(int x, int y, int width, int height, const char * caption, const char * text, int textposX, int textposY)
{
	goToPos(x, y);
	for(int i = 0; i < width; i++)
	{
		terminal_putchar('-');
	}
	terminal_putchar('-');
	int newy = y;
	for(int i2 = 0; i2 < height; i2++)
	{
		newy++;
		goToPos(x, newy);
		for(int i; i < width - 1; i++)
		{
			terminal_putchar(' ');
		}
		terminal_putchar('|');
	}
	for(int i3 = 0; i3 < width; i3++)
	{
		terminal_putchar('-');
	}
	goToPos(x + 1, y + 1);
	terminal_writestring(caption);
	goToPos(x + textposX, y + textposY);
	terminal_writestring(text);
}
*/
void messageBox(int x, int y, const char * caption, const char * text)
{
	goToPos(x, y);
	int newX=x;
	int newY=y;
	newX=newX-10;
	newY++;
	goToPos(newX, newY);
	newX=newX+10;
	terminal_writestring("----------------------------------------");
	newX=newX-10;
	newY++;
	goToPos(newX, newY);
	newX=newX+10;
	terminal_writestring("|                                      |");
	newX=newX-10;
	newY++;
	goToPos(newX, newY);
	newX=newX+10;
	terminal_writestring("|______________________________________|");
	newX=newX-10;
	newY++;
	goToPos(newX, newY);
	newX=newX+10;
	terminal_writestring("|                                      |");
	newX=newX-10;
	newY++;
	goToPos(newX, newY);
	newX=newX+10;
	terminal_writestring("|                                      |");
	newX=newX-10;
	newY++;
	goToPos(newX, newY);
	newX=newX+10;
	terminal_writestring("|                                      |");
	newX=newX-10;
	newY++;
	goToPos(newX, newY);
	newX=newX+10;
	terminal_writestring("|                                      |");
	newX=newX-10;
	newY++;
	goToPos(newX, newY);
	newX=newX+10;
	terminal_writestring("|                                      |");
	newX=newX-10;
	newY++;
	goToPos(newX, newY);
	newX=newX+10;
	terminal_writestring("|                                      |");
	newX=newX-10;
	newY++;
	goToPos(newX, newY);
	newX=newX+10;
	terminal_writestring("|                                      |");
	newX=newX-10;
	newY++;
	goToPos(newX, newY);
	newX=newX+10;
	terminal_writestring("|                                      |");
	newX=newX-10;
	newY++;
	goToPos(newX, newY);
	newX=newX+10;
	terminal_writestring("----------------------------------------");

	goToPos(x-8, y+2);
	terminal_writestring(caption);
	goToPos(x-8, y+5);
	terminal_writestring(text);
	
}
