#ifndef CXX_CONTAINER_TESTING_TYPES
#define CXX_CONTAINER_TESTING_TYPES

#include <array>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

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

using TrivialSmallType = types::Trivial<8>;
using TrivialMediumType = types::Trivial<64>;
using TrivialLargeType = types::Trivial<128>;
using TrivialHugeType = types::Trivial<1024>;
using TrivialMonsterType = types::Trivial<4 * 1024>;

template <typename T>
constexpr auto name() noexcept
    -> std::string_view
{
    if constexpr (std::is_same_v<T, TrivialSmallType>)
        return "TrivialSmallType"sv;
    else if (std::is_same_v<T, TrivialMediumType>)
        return "TrivialMediumType"sv;
    else if (std::is_same_v<T, TrivialLargeType>)
        return "TrivialLargeType"sv;
    else if (std::is_same_v<T, TrivialHugeType>)
        return "TrivialHugeType"sv;
    else if (std::is_same_v<T, TrivialMonsterType>)
        return "TrivialMonsterType"sv;
    else
        return "Sized-"s + std::to_string(sizeof(T));
}

} // namespace types

#endif // CXX_CONTAINER_TESTING_TYPES
