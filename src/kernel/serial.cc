#include "kernel/serial.hh"

#include "kernel/asm.hh"

serial_t::serial_t(COM _port) : port(_port) {
  // Disable all interrupts
  outb(uint16_t(port) + 1, 0x00);
  // Enable DLAB (set baud rate divisor)
  outb(uint16_t(port) + 3, 0x80);
  // Set divisor to 3 (lo byte) 38400 baud
  outb(uint16_t(port) + 0, 0x03);
  //                  (hi byte)
  outb(uint16_t(port) + 1, 0x00);
  // 8 bits, no parity, one stop bit
  outb(uint16_t(port) + 3, 0x03);
  // Enable FIFO, clear them, with 14-byte threshold
  outb(uint16_t(port) + 2, 0xC7);
  // IRQs enabled, RTS/DSR set
  outb(uint16_t(port) + 4, 0x0B);
  // Set in loopback mode, test the serial chip
  outb(uint16_t(port) + 4, 0x1E);
  // Test serial chip (send byte 0xAE and check if serial returns same byte)
  outb(uint16_t(port) + 0, 0xAE);

  // Check if serial is faulty (i.e: not same byte as sent)
  if (inb(uint16_t(port) + 0) != 0xAE) {
    // Honestly, if serial is fucked, we may as well just halt
    hlt();
  }

  // If serial is not faulty set it in normal operation mode
  // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
  outb(uint16_t(port) + 4, 0x0F);
}

bool serial_t::empty() {
  return static_cast<bool>(inb(uint16_t(port) + 5) & 0x20);
}

uint32_t serial_t::write(const char a) {
  while (!this->empty())
    continue;

  outb(uint16_t(port), a);
  return 0;
}

uint32_t serial_t::print(const char *str) {
  size_t i = 0;
  while (str[i] != '\0') {
    this->write(str[i++]);
  }
  return 0;
}
