 volatile unsigned int timer_ticks = 0;
void timer_wait(int ticks)
{
	unsigned int eticks;
	eticks = timer_ticks + ticks;
	while(timer_ticks < eticks)
	{
		asm volatile ("sti");
		asm volatile ("hlt");
		asm volatile ("cli");
		eticks--;
	}
}
