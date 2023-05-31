#ifndef CXX_CONTAINER_TESTING_TESTS
#define CXX_CONTAINER_TESTING_TESTS

#include <utils.hpp>

#include <algorithm>
#include <array>
#include <numeric>
#include <random>
#include <ranges>
#include <string_view>
#include <utility>
#include <vector>

namespace tests {

using std::ranges::begin;
using std::ranges::end;

template <typename Container>
struct PushBack {

    using value_type = typename Container::value_type;

    inline static auto run(Container& container, std::size_t size) noexcept -> void
    {
        for (auto i { 0uL }; i < size; ++i)
            container.push_back(value_type {});
    }

}; // struct PushBack

template <typename Container>
struct PushFront {

    using value_type = typename Container::value_type;

    inline static auto run(Container& container, std::size_t size) noexcept -> void
    {
        for (auto i { 0uL }; i < size; ++i)
            container.push_front(value_type {});
    }

}; // struct PushFront

template <typename T>
struct PushFront<std::vector<T>> {

    using value_type = T;

    inline static auto run(std::vector<T>& container, std::size_t size) noexcept -> void
    {
        for (auto i { 0uL }; i < size; ++i)
            container.insert(begin(container), value_type {});
    }

}; // struct PushFront

template <typename Container>
struct LinearSearch {

    using value_type = typename Container::value_type;

    inline static auto run(Container& container, std::size_t size) noexcept -> void
    {
        auto counter = 0uL;

        for (auto i { 0uL }; i < size; ++i)
            if (std::ranges::find_if(container, [&](auto x) { return x.a == i; }) != end(container))
                counter += 1uL;
    }

}; // struct LinearSearch

template <typename Container>
struct RandomInsert {
    using value_type = typename Container::value_type;

    static constexpr std::array<value_type, 1000> values = utils::make_array<value_type>(std::make_integer_sequence<std::size_t, 1000uL> {});

    inline static auto run(Container& container, std::size_t size) noexcept -> void
    {
        for (auto idx { 0uL }; idx < 1000uL; ++idx) {
            auto it = std::ranges::find_if(container, [&](auto x) { return x.a == idx; });
            container.insert(it, values[idx]);
        }
    }

}; // struct LinearSearch

template <typename Container>
struct RandomErase {
    inline static auto run(Container& container, std::size_t size) noexcept -> void
    {
        for (auto idx { 0uL }; idx < 1000uL; ++idx)
            container.erase(std::ranges::find_if(container, [&](auto x) { return x.a == idx; }));
    }

}; // struct RandomErase

template <typename Container>
struct RandomRemove {
    inline static auto run(Container& container, std::size_t size) noexcept -> void
    {
        auto [begin, end] = std::ranges::remove_if(container, [&](auto x) { return x.a < 1000uL; });
        container.erase(begin, end);
    }

}; // struct RandomRemove

} // namespace test

#endif // CXX_CONTAINER_TESTING_TESTS
