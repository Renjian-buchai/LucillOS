#if !defined(KERNEL_BOOTLOADER_HH_)
#define KERNEL_BOOTLOADER_HH_

#include "kstdint.hh"

extern "C" uint32_t _read_port(uint32_t portNumber);
extern "C" uint32_t _write_port(uint32_t portNumber, uint32_t data);

extern "C" uint32_t _load_IDT(uint32_t idtPointer);

#endif