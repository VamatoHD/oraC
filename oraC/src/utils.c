#include "utils.h"
#include <stddef.h>
#include <stdint.h>

#ifdef _MSC_VER
#include <intrin.h>
#endif

size_t strict_next_pow2(size_t n) {
    if (n == 0)
        return 1;

// 1. GCC and Clang (Linux, macOS, MinGW)
#if defined(__GNUC__) || defined(__clang__)
    return (size_t)1 << (64 - __builtin_clzll((unsigned long long)n));

// 2. MSVC (Windows / Visual Studio)
#elif defined(_MSC_VER)
    unsigned long index;
    if (_BitScanReverse64(&index, (unsigned __int64)n)) {
        return (size_t)1 << (index + 1);
    }
    return 1;

// 3. Portable Fallback (The "Bit-Smear" method)
#else
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    return n + 1;
#endif
}