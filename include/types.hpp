#ifndef CXX_CONTAINER_TESTING_TYPES
#define CXX_CONTAINER_TESTING_TYPES

#include <array>
#include <string_view>
#include <string>
#include <utility>
#include <type_traits>

namespace types {

using namespace std::literals; 

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

template<typename T>
constexpr auto name() noexcept
    -> std::string_view {
    if constexpr (std::is_same_v<T, SmallType>)
        return "SmallType"sv;
    else if (std::is_same_v<T, MediumType>)
        return "MediumType"sv;
    else if (std::is_same_v<T, LargeType>)
        return "LargeType"sv;
    else if (std::is_same_v<T, HugeType>)
        return "HugeType"sv;
    else if (std::is_same_v<T, MonsterType>)
        return "MonsterType"sv;
    else 
        return "Sized-"s + std::to_string(sizeof(T));
}

} // namespace types

#endif // CXX_CONTAINER_TESTING_TYPES
