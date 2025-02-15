#include "gdt.h"
#include "defs.h"

struct gdt_descriptor_t descriptors[] = {
    // limit0, base0, base1, access, limit1, flags, base2
    {0x0000, 0x0000, 0x00, 0x00, 0x0, 0x0, 0x00}, // null descriptor
    {0xFFFF, 0x0000, 0x00, 0x9A, 0xF, 0xA, 0x00}, // kernel mode code segment
    {0xFFFF, 0x0000, 0x00, 0x92, 0xF, 0xC, 0x00}, // kernel mode data segment
    {0xFFFF, 0x0000, 0x00, 0xFA, 0xF, 0xA, 0x00}, // user mode code segment
    {0xFFFF, 0x0000, 0x00, 0xF2, 0xF, 0xC, 0x00}, // user mode data segment
                                                  // TODO: add tss segment
};

void print_gdt() {
  struct gdtp_t g;
  asm volatile("sgdt %0" : "=m"(g) : : "memory");
  printk("gdtp: base=0x%x limit=0x%x\n", g.base, g.limit);
  printk("limit0\tbase0\tbase1\taccess\tlimit1\tflags\tbase2\n");
  for (int i = 0; i < g.limit; i += 8) {
    struct gdt_descriptor_t *ep = (struct gdt_descriptor_t *)(g.base + i);
    printk("0x%x\t0x%x\t0x%x\t0x%x\t0x%x\t0x%x\t0x%x\n", ep->limit0, ep->base0,
           ep->base1, ep->access, ep->limit1, ep->flags, ep->base2);
  }
}

void init_gdt() {
  // disable interrupts
  asm("cli");

  printk("old GDT table:\n");
  print_gdt();

  struct gdtp_t g;
  g.base = (uint64_t)descriptors;
  g.limit = sizeof(descriptors) - 1;
  asm volatile("lgdt %0" : : "m"(g) : "memory");
  // TODO: reload segment registers, for now they are still 0x30(set by limine)
  // which does not match our GDT table

  printk("new GDT table:\n");
  print_gdt();
}
