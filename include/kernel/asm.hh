#if !defined(KERNEL_BOOTLOADER_HH_)
#define KERNEL_BOOTLOADER_HH_

#include "kstdint.hh"

extern "C" uint32_t _read_port(uint32_t portNumber);
extern "C" uint32_t _write_port(uint32_t portNumber, uint32_t data);

extern "C" uint32_t _load_IDT(uint32_t idtPointer);

static inline void outb(uint16_t port, uint8_t val) {
  __asm__ volatile("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
  /* There's an outb %al, $imm8 encoding, for compile-time constant port numbers
   * that fit in 8b. (N constraint). Wider immediate constants would be
   * truncated at assemble-time (e.g. "i" constraint). The  outb  %al, %dx
   * encoding is the only option for all other cases. %1 expands to %dx because
   * port  is a uint16_t.  %w1 could be used if we had the port number a wider C
   * type */
}

static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  __asm__ volatile("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
  return ret;
}

static inline void hlt() { __asm__ volatile("hlt"); }

#endif