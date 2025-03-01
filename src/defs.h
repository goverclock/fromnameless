#pragma once
#include <stdint.h>

// printk.c
struct limine_framebuffer;
void printkinit(struct limine_framebuffer *);
void printk(const char *, ...);

// string.c
int strlen(const char *);

// gdt.c
void init_gdt();

// kalloc.c
struct limine_memmap_response;
void init_pmem(struct limine_memmap_response *);
