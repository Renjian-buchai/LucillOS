#if !defined(KSTR_HH_)
#define KSTR_HH_

namespace ktd {

enum class base_t { dec, hex, bin, oct };

int kstrcpy(char dest[], const char source[]);

int intToStr(int integral, char *str, base_t base = base_t::dec);

} // namespace ktd

using ktd::base_t;

#endif
