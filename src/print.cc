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
