#pragma once
#include "defs.h"

// TOOD: change all struct X into typedef
struct gdtp_t {
  uint16_t limit;
  uint64_t base;
} __attribute__((packed));

struct gdt_descriptor_t {
  // check out SDM 3.4.5 for explaination of each field
  uint16_t limit0;
  uint16_t base0;
  uint8_t base1;
  uint8_t access;
  uint8_t limit1 : 4;
  uint8_t flags : 4;
  uint8_t base2;
} __attribute__((packed));
