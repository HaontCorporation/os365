#include "../vgaterm.h"
int putchar(int ic)
{
	char c = (char) ic;
	terminal_write(&c, sizeof(c));
	return ic;
}
void print(const char * data, int count)
{
	for(int i; i < count; i++)
	putchar(data[i]);
}
void nop_(){}
void printf(const char * data, const char * arg)
{
	int written = 0;
	size_t amount;
	bool rejected_bad_specifier = false;
	for(int i = 0; i < strlen(data);)
	{
		finish:
		if(data[i] != '%')
		{
			putchar(data[i]);
			i++;
		}
		else
		{
			if(data[i+1] == 's')
			{
				terminal_writestring(arg); i++; goto finish;
			}
			else
			i++;
			goto no;
		}
		no:
		nop_();
	}
}
