#include "kprint.hh"
#include "kstdint.hh"

int32_t ktd::vgaInit() {
  const uint8_t width = 80;
  const uint8_t height = 25;

  uint16_t *vga = (uint16_t *)0xb8000;

  for (size_t i = 0; i < width * height; ++i) {
    vga[i] = 0;
  }

  return 0;
}

/**
 * @brief Prints string to VGA
 *
 * @param str String to print
 * @param len Length of string
 * @note Len should be long, because longs are guaranteed to be >=32 bits
 * @return int Error code. Idk.
 */
int32_t ktd::vgaPrint(const char *str) {
  const uint16_t color = 0x0F00;
  const uint16_t width = 80; // For testing purposes
  // Pray that this is 16 bits
  uint16_t *vga = (uint16_t *)0xb8000;

  unsigned char lineLeft = width;
  unsigned char lineNumber = 0;

  for (size_t i = 0; str[i] != '\0'; ++i) {
    // Normal wrap
    if (lineLeft <= 0) {
      lineNumber += 1;
      lineLeft = width;
    }

    // Newline wrap
    if (str[i] == '\n') {
      for (size_t j = width - lineLeft; j < lineLeft; ++j) {
        vga[(lineNumber - 1) * width + j] = color | ' ';
      }

      lineNumber += 1;
      lineLeft = 80;
      continue;
    }

    // Character
    vga[(lineNumber + 1) * width - lineLeft] = color | str[i];
    --lineLeft;
  }

  return 0;
}

int32_t ktd::serialInit() {
  using ktd::inb;
  using ktd::outb;
  outb(COM1 + 1, 0x00); // Disable all interrupts
  outb(COM1 + 3, 0x80); // Enable DLAB (set baud rate divisor)
  outb(COM1 + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
  outb(COM1 + 1, 0x00); //                  (hi byte)
  outb(COM1 + 3, 0x03); // 8 bits, no parity, one stop bit
  outb(COM1 + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
  outb(COM1 + 4, 0x0B); // IRQs enabled, RTS/DSR set
  outb(COM1 + 4, 0x1E); // Set in loopback mode, test the serial chip
  outb(COM1 + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial
                        // returns same byte)

  // Check if serial is faulty (i.e: not same byte as sent)
  if (inb(COM1 + 0) != 0xAE) {
    return 1;
  }

  // If serial is not faulty set it in normal operation mode
  // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
  outb(COM1 + 4, 0x0F);
  return 0;
}

int is_transmit_empty() { return ktd::inb(COM1 + 5) & 0x20; }

void write_serial(char a) {
  while (is_transmit_empty() == 0)
    continue;

  ktd::outb(COM1, a);
}

void ktd::print_serial(const char *str, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    write_serial(str[i]);
  }
}
