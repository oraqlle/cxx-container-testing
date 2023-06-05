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
    [[nodiscard]] auto operator<(const Trivial& other) const noexcept -> bool { return a < other.a; }
}; // struct Trivial

template <>
struct Trivial<sizeof(std::size_t)> {
    std::size_t a;
    [[nodiscard]] auto operator<(const Trivial& other) const noexcept -> bool { return a < other.a; }
}; // struct Trivial<sizeof(std::size_t)>

using TrivialSmallType = types::Trivial<8>;
using TrivialMediumType = types::Trivial<64>;
using TrivialLargeType = types::Trivial<128>;
using TrivialHugeType = types::Trivial<1024>;
using TrivialMonsterType = types::Trivial<4 * 1024>;

struct NonTrivialMovable {
public:
    NonTrivialMovable() = default;

    NonTrivialMovable(std::size_t a)
        : a { a }
    {
    }

    ~NonTrivialMovable() = default;

    [[nodiscard]] auto operator<(const NonTrivialMovable& other) const -> bool
    {
        return a < other.a;
    }

public:
    std::size_t a { 0uL };

private:
    std::string data { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-=[]\\;',./_+{}:\"<>?" };
}; // struct NonTrivialMovable

struct NonTrivialMovableNoexcept {
public:
    NonTrivialMovableNoexcept() noexcept = default;

    NonTrivialMovableNoexcept(std::size_t a) noexcept
        : a { a }
    {
    }

    NonTrivialMovableNoexcept(const NonTrivialMovableNoexcept& other) noexcept = default;
    NonTrivialMovableNoexcept(NonTrivialMovableNoexcept&& other) noexcept = default;

    ~NonTrivialMovableNoexcept() noexcept = default;

    [[nodiscard]] auto operator=(const NonTrivialMovableNoexcept& other) noexcept
        -> NonTrivialMovableNoexcept& = default;

    [[nodiscard]] auto operator=(NonTrivialMovableNoexcept&& other) noexcept
        -> NonTrivialMovableNoexcept&
    {
        std::swap(data, other.data);
        std::swap(a, other.a);

        return *this;
    }

    [[nodiscard]] auto operator<(const NonTrivialMovableNoexcept& other) const noexcept -> bool
    {
        return a < other.a;
    }

public:
    std::size_t a { 0uL };

private:
    std::string data { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-=[]\\;',./_+{}:\"<>?" };
}; // struct NonTrivialMovableNoexcept

template <std::size_t N>
struct NonTrivial {
public:
    NonTrivial() = default;

    NonTrivial(std::size_t a)
        : a { a }
    {
    }

    ~NonTrivial() = default;

    [[nodiscard]] auto operator<(const NonTrivial& other) const noexcept -> bool
    {
        return a < other.a;
    }

public:
    std::size_t a { 0uL };

private:
    std::array<unsigned char, N - sizeof(std::size_t)> data;
}; // struct NonTrivial

using NonTrivialMedium = NonTrivial<32>;

template <typename T>
[[nodiscard]] constexpr auto name() noexcept
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
    else if (std::is_same_v<T, NonTrivialMovable>)
        return "NonTrivialMovable"sv;
    else if (std::is_same_v<T, NonTrivialMovableNoexcept>)
        return "NonTrivialMovableNoexcept"sv;
    else if (std::is_same_v<T, NonTrivialMedium>)
        return "NonTrivialMedium"sv;
    else
        return "Sized-"s + std::to_string(sizeof(T));
}

} // namespace types

#endif // CXX_CONTAINER_TESTING_TYPES
