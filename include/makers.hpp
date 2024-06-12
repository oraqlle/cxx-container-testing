#ifndef CXX_CONTAINER_TESTING_MAKERS
#define CXX_CONTAINER_TESTING_MAKERS

#include <algorithm>
#include <numeric>
#include <random>
#include <ranges>

namespace makers {

using std::ranges::begin;
using std::ranges::end;

template <typename Container>
struct Empty {
    [[nodiscard]] static inline auto make([[maybe_unused]] std::size_t size) noexcept
        -> Container
    {
        return Container {};
    }

    static inline auto clean() noexcept -> void { }
}; // struct Empty

template <typename Container>
struct Preallocated {
    [[nodiscard]] static inline auto make(std::size_t size) noexcept
        -> Container
    {
        auto container = Container {};
        container.reserve(size);
        return container;
    }

    static inline auto clean() noexcept -> void { }
}; // struct Preallocated

template <class Container>
struct Filled {
    [[nodiscard]] static inline auto make(std::size_t size) noexcept
        -> Container
    {
        return Container { size };
    }

    static inline auto clean() noexcept -> void { }
}; // struct Filled

template <class Container>
struct FilledRandom {

    using value_type = typename Container::value_type;

    [[nodiscard]] static inline auto make(std::size_t size)
    {
        auto container = Container { size };
        auto nums = std::views::iota(0UL)
            | std::views::take(size)
            | std::views::common;

        auto temp = std::vector<value_type> { begin(nums), end(nums) };

        std::ranges::shuffle(temp, std::mt19937 { std::random_device {}() });
        container.assign(begin(temp), end(temp));

        return container;
    }

    static inline auto clean() noexcept -> void { }
}; // struct FilledRandom

} // namespace makers

#endif // CXX_CONTAINER_TESTING_MAKERS
