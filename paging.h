#ifndef __PAGING_H
#define __PAGING_H
#include <stdint.h>
/*
.text
.globl loadPageDirectory
loadPageDirectory:
push %ebp
mov %esp,%ebp
mov 8(%esp),%eax
mov %eax, %cr3
mov %ebp, %esp
pop %ebp
ret
.text
.globl enablePaging
enablePaging:
push %ebp
mov %esp, %ebp
mov %cr0, %eax
or $0x80000000, %eax
mov %eax, %cr0
mov %ebp, %esp
pop %ebp
ret
*/
extern void loadPageDirectory(unsigned int*)
{
	asm("\
		push %ebp;\
		mov %esp,%ebp;\
		mov 8(%esp),%eax;\
		mov %eax, %cr3;\
		mov %ebp, %esp;\
		pop %ebp;\
");
}
extern void enablePaging()
{
	asm("\
		push %ebp;\
		mov %esp, %ebp;\
		mov %cr0, %eax;\
		or $0x80000000, %eax;\
		mov %eax, %cr0;\
		mov %ebp, %esp;\
		pop %ebp;");
}
uint32_t page_directory[1024] __attribute__((aligned(4096)));
void blankpage()
{
	for(int i = 0; i < 1024; i++)
	{
		page_directory[i] = 0x00000002;
	}
}
uint32_t first_page_table[1024] __attribute__((aligned(4096)));
void createpage()
{
	unsigned int i;
	for(i = 0; i < 1024; i++);
	{
		first_page_table[i] = (i * 0x1000) | 3;
	}
	page_directory[0] = ((unsigned int)first_page_table) | 3;
	
}
#endif
