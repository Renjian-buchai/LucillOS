#if !defined(KSTDINT_HH_)
#define KSTDINT_HH_

namespace ktd {

enum class base_t { dec, hex, bin, oct };

int intToStr(int integral, char *str, base_t base = base_t::dec);

} // namespace ktd

using ktd::base_t;

#endif