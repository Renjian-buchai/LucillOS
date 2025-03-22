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
