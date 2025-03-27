#include "kstr.hh"

int32_t ktd::kstrcpy(char dest[], const char source[]) {
  if (dest == nullptr || source == nullptr) {
    return -1;
  }

  int i = 0;
  while ((dest[i] = source[i]) != '\0') {
    i++;
  }

  return 0;
}

int32_t ktd::strFrom32(int32_t integral, char *str, ktd::base_t base) {
  (void)base;
  char digits[11] = "0000000000";
  for (uint8_t i = 9; i > 0; --i) {
    char digit = integral % 10;
    // Converts int to char
    digits[i] = digit + 48;
    integral /= 10;
  }

  for (uint8_t i = 0; i < 10; ++i) {
    if (digits[i] != '0') {
      if (int err = ktd::kstrcpy(str, digits + i)) {
        return err;
      }
      return 0;
    }
  }

  if (int err = ktd::kstrcpy(str, "0")) {
    return err;
  }
  return 0;
}
