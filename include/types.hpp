#ifndef CXX_CONTAINER_TESTING_TYPES
#define CXX_CONTAINER_TESTING_TYPES

#include <fmt/core.h>

#include <array>
#include <string>
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

    [[nodiscard]] auto operator<=>(const Trivial& other) const noexcept = default;

    [[nodiscard]] auto value() const noexcept -> const std::size_t&
    {
        return m_value;
    }

private:
    std::size_t m_value { 0UL };
    std::array<unsigned char, N - sizeof(m_value)> m_data {};
}; // struct Trivial

template <>
struct Trivial<sizeof(std::size_t)> {

    Trivial() noexcept = default;

    explicit Trivial(std::size_t value) noexcept
        : m_value { value }
    {
    }

    [[nodiscard]] auto operator<=>(const Trivial& other) const noexcept = default;

    [[nodiscard]] auto value() const noexcept -> const std::size_t&
    {
        return m_value;
    }

private:
    std::size_t m_value { 0UL };
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

    [[nodiscard]] auto operator<=>(const NonTrivialMovable& other) const = default;

    [[nodiscard]] auto value() const noexcept -> const std::size_t&
    {
        return m_value;
    }

private:
    std::size_t m_value { 0UL };
    std::string m_data { R"(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-=[]\\;',./_+{}:\"<>?)" };
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

    [[nodiscard]] auto operator<=>(const NonTrivialMovableNoexcept& other) const noexcept = default;

    [[nodiscard]] auto value() const noexcept -> const std::size_t&
    {
        return m_value;
    }

private:
    std::size_t m_value { 0UL };
    std::string m_data { R"(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-=[]\;',./_+{}:"<>?)" };
}; // struct NonTrivialMovableNoexcept

template <std::size_t N>
struct NonTrivial { // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)

    NonTrivial() = default;

    explicit NonTrivial(std::size_t value)
        : m_value { value }
    {
    }

    ~NonTrivial() = default;

    [[nodiscard]] auto operator<=>(const NonTrivial& other) const noexcept = default;

    [[nodiscard]] auto value() const noexcept -> const std::size_t&
    {
        return m_value;
    }

private:
    std::size_t m_value { 0UL };
    std::array<unsigned char, N - sizeof(std::size_t)> m_data {};
}; // struct NonTrivial

using NonTrivialMedium = NonTrivial<32>;

template <typename T>
[[nodiscard]] constexpr auto name() noexcept
    -> std::string
{
    if constexpr (std::is_same_v<T, TrivialSmallType>) {
        return "TrivialSmallType"s;
    } else if constexpr (std::is_same_v<T, TrivialMediumType>) {
        return "TrivialMediumType"s;
    } else if constexpr (std::is_same_v<T, TrivialLargeType>) {
        return "TrivialLargeType"s;
    } else if constexpr (std::is_same_v<T, TrivialHugeType>) {
        return "TrivialHugeType"s;
    } else if constexpr (std::is_same_v<T, TrivialMonsterType>) {
        return "TrivialMonsterType"s;
    } else if constexpr (std::is_same_v<T, NonTrivialMovable>) {
        return "NonTrivialMovable"s;
    } else if constexpr (std::is_same_v<T, NonTrivialMovableNoexcept>) {
        return "NonTrivialMovableNoexcept"s;
    } else if constexpr (std::is_same_v<T, NonTrivialMedium>) {
        return "NonTrivialMedium"s;
    } else {
        return fmt::format("Sized-{}", sizeof(T));
    }
}

} // namespace types

#endif // CXX_CONTAINER_TESTING_TYPES
