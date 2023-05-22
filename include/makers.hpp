#ifndef CXX_CONTAINER_TESTING_MAKERS
#define CXX_CONTAINER_TESTING_MAKERS

#include <numeric>
#include <random>
#include <ranges>

namespace makers {

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

    static inline std::mt19937 gen = std::mt19937 { std::random_device {}() };
    static inline std::uniform_int_distribution<std::size_t> distrib = std::uniform_int_distribution<std::size_t> {
        std::numeric_limits<std::size_t>::min(),
        std::numeric_limits<std::size_t>::max()
    };

    [[nodiscard]] static inline auto make(std::size_t size)
    {
        auto container = Container { size };
        std::ranges::generate(container, []() { return value_type { distrib(gen) }; });

        return container;
    }

    static inline auto clean() noexcept -> void { }
}; // struct FilledRandom

} // namespace makers

#endif // CXX_CONTAINER_TESTING_MAKERS
