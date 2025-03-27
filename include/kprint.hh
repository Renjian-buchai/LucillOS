#if !defined(LUCILLOS_PRINT_HH_)
#define LUCILLOS_PRINT_HH_

#include <kstdint.hh>

namespace ktd {

int32_t vgaInit();

int32_t vgaPrint(const char *str);

} // namespace ktd

#endif