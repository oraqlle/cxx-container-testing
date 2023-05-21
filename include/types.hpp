#ifndef CXX_CONTAINER_TESTING_TYPES
#define CXX_CONTAINER_TESTING_TYPES

#include <array>

namespace types {

template <std::size_t N>
struct Trivial {
    std::size_t a;
    std::array<unsigned char, N - sizeof(a)> b;
    auto operator<(const Trivial& other) const noexcept -> bool { return a < other.a; }
}; // struct Trivial

template <>
struct Trivial<sizeof(std::size_t)> {
    std::size_t a;
    auto operator<(const Trivial& other) const noexcept -> bool { return a < other.a; }
}; // struct Trivial<sizeof(std::size_t)>

using SmallType = types::Trivial<8>;
using MediumType = types::Trivial<64>;
using LargeType = types::Trivial<128>;
using HugeType = types::Trivial<1024>;
using MonsterType = types::Trivial<4 * 1024>;

} // namespace types

#endif // CXX_CONTAINER_TESTING_TYPES
