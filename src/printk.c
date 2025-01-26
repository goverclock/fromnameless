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

static void putchar(char c) { flanterm_write(ft_ctx, &c, 1); }

static void printint(int64_t xx, int base, int sign) {
  static char digits[] = "0123456789abcdef";

  uint64_t x;
  if (sign && xx < 0)
    x = -xx;
  else
    x = xx;

  int i = 0;
  char buf[16];
  do {
    buf[i++] = digits[x % base];
  } while ((x /= base) != 0);

  if (sign && xx < 0)
    buf[i++] = '-';

  while (--i >= 0)
    putchar(buf[i]);
}

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
  va_start(ap, fmt);

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
      printint(va_arg(ap, int), 10, 1);
      break;
    case 'x':
      printint(va_arg(ap, int), 16, 0);
      break;
    default:
      putchar('%');
      putchar('?');
      break;
    }
  }

  va_end(ap);
}
