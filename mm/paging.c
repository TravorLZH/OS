#include <kernel/memory.h>
#include <kernel/utils.h>
#include <asm/shutdown.h>
#include <drivers/screen.h>
#include <cpu/isr.h>

size_t page_directory[1024] __attribute__((aligned(4096)));
size_t first_page_table[1024] __attribute__((aligned(4096)));

static void page_fault(registers_t regs){
	size_t faulting_address;
	int present,rw,us,reserved,id;
	present=regs.err_code & 1;	// Page not present
	rw=regs.err_code & 0x2;			// Write protection?
	us=regs.err_code & 0x4;			// User-mode?
	reserved=regs.err_code & 0x8;	// Overwritten CPU-reserved bits of page entry?
	id=regs.err_code & 0x10;		// Caused by an instruction fetch?
	__asm__("movl %%cr2,%0":"=r" (faulting_address));
	__kprintf("Page Fault: ");
	if(!present){__kprintf("not-present ");}
	if(rw){__kprintf("read-only ");}
	if(us){__kprintf("user-mode ");}
	if(reserved){__kprintf("reserved" );}
	__kprintf("\nat 0x%x\n",faulting_address);
	__kprintf("EIP: 0x%x\n",regs.eip);
	__kprintf("Error code: 0x%x\n",regs.err_code);
	while(1);	// Hang so we don't repeat the same error again
}

void init_paging(void){
	// TODO: Initialize the page directory
	size_t i;
	for(i=0;i<1024;i++){
		/* Set the following flags to the pages:
		 * Superwisor: Only kernel-mode can access them
		 * Write Enabled: It can be both read from and written to
		 * Not present: The page table is not present
		*/
		page_directory[i]=0x00000002;
	}
	// TODO: Initialize the first page table which maps 4 MB of the physical memory
	for(i=0;i<1024;i++){
		first_page_table[i]=(i*0x1000)|3;	// Attributes: supervisor, rw, present
	}
	first_page_table[3]=3*0x1000;	// Create a not-present page
	page_directory[0]=((size_t)first_page_table) | 3;
	register_interrupt_handler(0xE,&page_fault);
	load_page_directory(page_directory);
	enable_paging();
}