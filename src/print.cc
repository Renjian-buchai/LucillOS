#include "kprint.hh"

/**
 * @brief Prints string to VGA
 *
 * @param str String to print
 * @param len Length of string
 * @note Len should be long, because longs are guaranteed to be >=32 bits
 * @return int Error code. Idk.
 */
int ktd::print(const char *str) {
  const short color = 0x0F00;
  const short width = 80; // For testing purposes
  // Pray that this is 16 bits
  short *vga = (short *)0xb8000;

  unsigned char lineLeft = width;
  unsigned char lineNumber = 0;

  for (long i = 0; str[i] != '\0'; ++i) {
    // Normal wrap
    if (lineLeft <= 0) {
      lineNumber += 1;
      lineLeft = width;
    }

    // Newline wrap
    if (str[i] == '\n') {
      for (long j = width - lineLeft; j < lineLeft; ++j) {
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
