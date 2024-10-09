#include "hash_code.h"
#include <limits>
#include <string>

namespace dsac::map {

int hash_code(std::string s) {
    const int U_INT_BITS{std::numeric_limits<unsigned int>::digits};
    int h{0};
    for (char c : s) {
        h = (h << 5) | (h >> (U_INT_BITS - 5));       // 5-bit cyclic shift
        h += int(c);                                  // add in next character
    }
    return (h < 0 ? -h : h);                          // return absolute value
}

} // namespace dsac::map
