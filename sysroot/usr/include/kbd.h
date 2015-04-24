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
		nop();
	}
	while(c!=key);
	return;
}
