#include "kstr.hh"

int ktd::kstrcpy(char dest[], const char source[]) {
  if (dest == nullptr || source == nullptr) {
    return -1;
  }

  int i = 0;
  while ((dest[i] = source[i]) != '\0') {
    i++;
  }

  return 0;
}

int ktd::intToStr(int integral, char *str, ktd::base_t base) {
  (void)base;
  char digits[11] = "0000000000";
  for (int i = 9; i > 0; --i) {
    char digit = integral % 10;
    // Converts int to char
    digits[i] = digit + 48;
    integral /= 10;
  }

  for (int i = 0; i < 10; ++i) {
    if (i != '0') {
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
