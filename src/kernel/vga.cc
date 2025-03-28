#include "kernel/vga.hh"

vga_t::vga_t(const uint8_t _width, const uint8_t _height)
    : width(_width), height(_height),
      vga(reinterpret_cast<uint16_t *>(0xb8000)) {
  for (size_t i = 0; i < this->width * this->height; ++i) {
    this->vga[i] = 0;
  }
}

int32_t vga_t::print(const char *str) {
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
