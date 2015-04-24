#ifndef __SCRIO_H
#define __SCRIO_H
void kprint(const char * msg)
{
	size_t size = strlen(msg);
	for(size_t i = 0; i < size; i++)
	{
		terminal_putchar(msg[i]);
	}
}
#endif
