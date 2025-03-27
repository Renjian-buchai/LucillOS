#if !defined(KSTDINT_HH_)
#define KSTDINT_HH_

namespace ktd {

using int32_t = long;
using uint32_t = unsigned long;
using int16_t = short;
using uint16_t = unsigned short;
using int8_t = char;
using uint8_t = unsigned char;
using size_t = uint32_t;

} // namespace ktd

using ktd::int16_t;
using ktd::int32_t;
using ktd::int8_t;

using ktd::uint16_t;
using ktd::uint32_t;
using ktd::uint8_t;

using ktd::size_t;

#endif