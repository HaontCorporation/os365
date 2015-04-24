struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));
struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));
struct gdt_entry gdt[3];
struct gtd_ptr gp;
extern void gtd_flush();
