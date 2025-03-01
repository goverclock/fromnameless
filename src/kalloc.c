#include "defs.h"
#include "limine.h"

void init_pmem(struct limine_memmap_response *resp) {
  uint64_t entry_count = resp->entry_count;

  printk("memmap resp->entry_count=%d\n", entry_count);

  for (uint64_t i = 0; i < entry_count; i++) {
    printk("entry[%d]:\t", i);
    struct limine_memmap_entry *e = resp->entries[i];
    printk("\tbase=%x\t", e->base);
    printk("\tlength=%d\t", e->length);
    printk("\ttype=%d\n", e->type);
  }
};

// struct limine_memmap_response {
//   uint64_t revision;
//   uint64_t entry_count;
//   LIMINE_PTR(struct limine_memmap_entry **) entries;
// };
//
// struct limine_memmap_entry {
//   uint64_t base;
//   uint64_t length;
//   uint64_t type;
// };
