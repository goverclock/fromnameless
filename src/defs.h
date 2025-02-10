#pragma once

// printk.c
struct limine_framebuffer;
void printkinit(struct limine_framebuffer *);
void printk(const char *, ...);

// string.c
int strlen(const char *);
