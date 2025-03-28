#if !defined(VGA_HH_)
#define VGA_HH_

#include "kstdint.hh"

struct vga_t {
  const uint8_t width = 80;
  const uint8_t height = 25;
  uint16_t *vga;

  vga_t(const uint8_t width = 80, const uint8_t height = 25);

  /**
   * @brief Prints string to VGA
   *
   * @param str String to print
   * @param len Length of string
   * @note Len should be long, because longs are guaranteed to be >=32 bits
   * @return int Error code. Idk.
   */
  int32_t print(const char *str);
};

#endif