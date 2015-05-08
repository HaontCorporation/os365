#ifndef __IO_H_
#define __IO_H_
#define PIC1 0x20
#define PIC2 0xA0
#define ICW1 0x11
#define ICW4 0x01
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long int qword;
char scancode[] = "   1234567890-=^^qwertyuiop[]\n^asdfghjkl;'`  zxcvbnm,./^*^   ^^^^^^^^^^^^^^789-456+1230.^^   !@#$%^&*()_+^^QWERTYUIOP{}\n^ASDFGHJKL:'^  ZXCVBNM<>?^*^   ^^^^^^^^^^^^^^&*(_$%^+!@#)>^^";
inline byte inb(word port)
{
   byte r;
   asm volatile(
   ".intel_syntax noprefix\n\t"
   "in al,dx\n\t"
   ".att_syntax"
   :"=a"(r)
   :"d"(port)
   );
   return(r);
}

inline void outb(word port,byte val)
{
   asm volatile(
   ".intel_syntax noprefix\n\t"
   "out dx,al\n\t"
   ".att_syntax"
   :
   :"d"(port),"a"(val)
   );
}
static inline void outw(uint16_t port, uint16_t val)
{
	asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}
static inline uint16_t inw(uint16_t port)
{
	uint16_t ret;
	asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
	return ret;
}
static inline void outl(uint16_t port, uint32_t val)
{
	asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}
static inline uint32_t inl(uint16_t port)
{
	uint32_t ret;
	asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
	return ret;
}
void insl(unsigned short port, unsigned int buffer, unsigned long count)
{
asm("cld; rep; insl" :: "D" (buffer), "d" (port), "c" (count));
}
int getch()
{
	char c = 0;
	do
	{
		if(inb(0x60)!=c)
		{
			c = inb(0x60);
			if(c>0)
			{
				return scancode[c+1];
			}
		}
	}
	while(c!=1);
}
void init_pics(int pic1, int pic2)
{
	outb(PIC1, ICW1);
	outb(PIC2, ICW1);
	outb(PIC1 + 1, pic1);
	outb(PIC2 + 1, pic2);
	outb(PIC1 + 1, 4);
	outb(PIC2 + 1, 2);
	outb(PIC1 + 1, ICW4);
	outb(PIC2 + 1, ICW4);
	outb(PIC1 + 1, 0xFF);
}
void update_cursor(int row, int col)
{
	unsigned short position=(row*80) + col;
	outb(0x3D4,0x0F);
	outb(0x3D5,(unsigned char) (position&0xFF));
	outb(0x3D4,0x0E);
	outb(0x3D5,(unsigned char) ((position>>8)&0xFF));
}
#endif
