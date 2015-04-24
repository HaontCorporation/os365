#ifndef __KBD_H
#define __KBD_H
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
#endif
