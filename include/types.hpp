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

template<>
struct Trivial<0> {
    constexpr static std::string_view name = "Trivial";
}; // struct Trivial<0>

} // namespace types

#endif // CXX_CONTAINER_TESTING_TYPES
