static inline uint16_t r_cs() {
  uint16_t x;
  asm volatile("mov %%cs, %0" : "=r"(x));
  return x;
}

static inline uint16_t r_ds() {
  uint16_t x;
  asm volatile("mov %%ds, %0" : "=r"(x));
  return x;
}

static inline uint16_t r_es() {
  uint16_t x;
  asm volatile("mov %%es, %0" : "=r"(x));
  return x;
}

static inline uint16_t r_fs() {
  uint16_t x;
  asm volatile("mov %%fs, %0" : "=r"(x));
  return x;
}

static inline uint16_t r_gs() {
  uint16_t x;
  asm volatile("mov %%gs, %0" : "=r"(x));
  return x;
}

static inline uint16_t r_ss() {
  uint16_t x;
  asm volatile("mov %%ss, %0" : "=r"(x));
  return x;
}

// enable device interrupts
static inline void intr_on() { asm volatile("sti"); }

// disable device interrupts
static inline void intr_off() { asm volatile("cli"); }
