#include "defs.h"
#include "flanterm/backends/fb.h"
#include "flanterm/flanterm.h"
#include "limine.h"
#include <stdarg.h>

struct flanterm_context *ft_ctx;

void printkinit(struct limine_framebuffer *fbp) {
  ft_ctx = flanterm_fb_init(
      NULL, NULL, (uint32_t *)fbp->address, fbp->width, fbp->height, fbp->pitch,
      fbp->red_mask_size, fbp->red_mask_shift, fbp->green_mask_size,
      fbp->green_mask_shift, fbp->blue_mask_size, fbp->blue_mask_shift, NULL,
      NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1, 0, 0, 0);
}

void putchar(char c) { flanterm_write(ft_ctx, &c, 1); }

void panic(char *s) {
  printk("panic: ");
  printk(s);
  printk("\n");
  for (;;) {
    asm("hlt");
  }
}

void printk(const char *fmt, ...) {
  va_list ap;

  for (int i = 0; fmt[i]; i++) {
    char c = fmt[i];

    if (c != '%') {
      putchar(fmt[i]);
      continue;
    }
    c = fmt[++i];
    if (!c)
      break;
    switch (c) {
    case 'd':
      //      printint(va_arg(ap, int), 10, 1);
      putchar('D');
      break;
    default:
      putchar('%');
      putchar('?');
      break;
    }
  }

  va_end(ap);
}
