#if !defined(SERIAL_HH_)
#define SERIAL_HH_

#include "kstdint.hh"
#include "ports.hh"

struct serial_t {
  COM port;

  serial_t(COM _port = COM::COM1);

  bool empty();
  uint32_t write(const char character);
  uint32_t print(const char *str);
};

#endif