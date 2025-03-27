#if !defined(KSTR_HH_)
#define KSTR_HH_

#include "kstdint.hh"

namespace ktd {

enum class base_t : int8_t { dec, hex, bin, oct };

int32_t kstrcpy(char dest[], const char source[]);

int32_t strFrom32(int32_t integral, char *str, base_t base = base_t::dec);

} // namespace ktd

using ktd::base_t;

#endif
