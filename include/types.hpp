#ifndef CXX_CONTAINER_TESTING_TYPES
#define CXX_CONTAINER_TESTING_TYPES

#include <fmt/core.h>

#include <array>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace types {

using namespace std::literals;

template <std::size_t N>
struct Trivial {

    Trivial() noexcept = default;

    explicit Trivial(std::size_t value) noexcept
        : m_value { value }
    {
    }

    [[nodiscard]] auto operator<(const Trivial& other) const noexcept -> bool { return m_value < other.m_value; }

    [[nodiscard]] auto value() const noexcept -> const std::size_t&
    {
        return m_value;
    }

private:
    std::size_t m_value;
    std::array<unsigned char, N - sizeof(m_value)> b;
}; // struct Trivial

template <>
struct Trivial<sizeof(std::size_t)> {

    Trivial() noexcept = default;

    explicit Trivial(std::size_t value) noexcept
        : m_value { value }
    {
    }

    [[nodiscard]] auto operator<(const Trivial& other) const noexcept -> bool { return m_value < other.m_value; }

    [[nodiscard]] auto value() const noexcept -> const std::size_t&
    {
        return m_value;
    }

private:
    std::size_t m_value;
}; // struct Trivial<sizeof(std::size_t)>

using TrivialSmallType = types::Trivial<8>;
using TrivialMediumType = types::Trivial<64>;
using TrivialLargeType = types::Trivial<128>;
using TrivialHugeType = types::Trivial<1024>;
using TrivialMonsterType = types::Trivial<4UL * 1024UL>;

struct NonTrivialMovable {

    NonTrivialMovable() = default;

    explicit NonTrivialMovable(std::size_t value)
        : m_value { value }
    {
    }

    ~NonTrivialMovable() = default;

    [[nodiscard]] auto operator<(const NonTrivialMovable& other) const -> bool
    {
        return m_value < other.m_value;
    }

    [[nodiscard]] auto value() const noexcept -> const std::size_t&
    {
        return m_value;
    }

private:
    std::string m_data { R"(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-=[]\\;',./_+{}:\"<>?)" };
    std::size_t m_value;
}; // struct NonTrivialMovable

struct NonTrivialMovableNoexcept {

    NonTrivialMovableNoexcept() noexcept = default;

    explicit NonTrivialMovableNoexcept(std::size_t value) noexcept
        : m_value { value }
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
        std::swap(m_data, other.m_data);
        std::swap(m_value, other.m_value);

        return *this;
    }

    [[nodiscard]] auto operator<(const NonTrivialMovableNoexcept& other) const noexcept -> bool
    {
        return m_value < other.m_value;
    }

    [[nodiscard]] auto value() const noexcept -> const std::size_t&
    {
        return m_value;
    }

private:
    std::string m_data { R"(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-=[]\;',./_+{}:"<>?)" };
    std::size_t m_value;
}; // struct NonTrivialMovableNoexcept

template <std::size_t N>
struct NonTrivial {

    NonTrivial() = default;

    explicit NonTrivial(std::size_t value)
        : m_value { value }
    {
    }

    ~NonTrivial() = default;

    [[nodiscard]] auto operator<(const NonTrivial& other) const noexcept -> bool
    {
        return m_value < other.m_value;
    }

    [[nodiscard]] auto value() const noexcept -> const std::size_t&
    {
        return m_value;
    }

private:
    std::array<unsigned char, N - sizeof(std::size_t)> m_data;
    std::size_t m_value;
}; // struct NonTrivial

using NonTrivialMedium = NonTrivial<32>;

template <typename T>
[[nodiscard]] constexpr auto name() noexcept
    -> std::string_view
{
    if constexpr (std::is_same_v<T, TrivialSmallType>) {
        return "TrivialSmallType"sv;
    } else if (std::is_same_v<T, TrivialMediumType>) {
        return "TrivialMediumType"sv;
    } else if (std::is_same_v<T, TrivialLargeType>) {
        return "TrivialLargeType"sv;
    } else if (std::is_same_v<T, TrivialHugeType>) {
        return "TrivialHugeType"sv;
    } else if (std::is_same_v<T, TrivialMonsterType>) {
        return "TrivialMonsterType"sv;
    } else if (std::is_same_v<T, NonTrivialMovable>) {
        return "NonTrivialMovable"sv;
    } else if (std::is_same_v<T, NonTrivialMovableNoexcept>) {
        return "NonTrivialMovableNoexcept"sv;
    } else if (std::is_same_v<T, NonTrivialMedium>) {
        return "NonTrivialMedium"sv;
    } else {
        return "Sized-"s + std::to_string(sizeof(T));
    }
}

} // namespace types

#endif // CXX_CONTAINER_TESTING_TYPES
