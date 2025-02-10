#pragma once

struct gdtr {
  uint16_t limit;
  uint64_t base;
} __attribute__((packed));

struct gdt_entry_t {
  uint16_t limit0;
  uint16_t base0;
  uint8_t base1;
  uint8_t access;
  uint8_t limit1 : 4;
  uint8_t flags : 4;
  //  uint8_t granularity;
  uint8_t base2;
} __attribute__((packed));

void init_gdt() {
  // disable interrupts
  asm("cli");

  struct gdtr g;
  asm volatile("sgdt %0" : "=m"(g) : : "memory");
  printk("gdtr: base=0x%x limit=0x%x\n", g.base, g.limit);
  printk("limit0\tbase0\tbase1\taccess\tlimit1\tflags\tbase2\n");
  for (int i = 0; i < g.limit; i += 8) {
    struct gdt_entry_t *ep = (struct gdt_entry_t *)(g.base + i);
    printk("0x%x\t0x%x\t0x%x\t0x%x\t0x%x\t0x%x\t0x%x\n", ep->limit0, ep->base0,
           ep->base1, ep->access, ep->limit1, ep->flags, ep->base2);
  }

  struct gdt_entry_t entries[] = {
      {0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00}, // null descriptor
      {0xFFFF, 0x0000, 0x00, 0x9A, 0x0A, 0x00}, // kernel mode code segment
      {0xFFFF, 0x0000, 0x00, 0x92, 0x0C, 0x00}, // kernel mode data segment
  };
}
