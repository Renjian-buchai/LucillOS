#if !defined(PORTS_HH_)
#define PORTS_HH_

#include "kstdint.hh"

enum class COM : uint16_t {
  COM1 = 0x3F8,
  COM2 = 0x2F8,
  COM3 = 0x3E8,
  COM4 = 0x2E8,
  COM5 = 0x5F8,
  COM6 = 0x4F8,
  COM7 = 0x5E8,
  COM8 = 0x4E8
};

#endif