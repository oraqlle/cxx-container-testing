#ifndef CXX_CONTAINER_TESTING_TESTS
#define CXX_CONTAINER_TESTING_TESTS

#include <utils.hpp>

#include <algorithm>
#include <array>
#include <functional>
#include <list>
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
struct NoOp {
    inline static auto run(Container& container, std::size_t size) noexcept -> void
    {
    }

}; // struct NoOp

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

}; // struct PushFront<std::vector<T>>

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

    static constexpr std::array<std::size_t, 1000> values = utils::make_array<std::size_t>(std::make_integer_sequence<std::size_t, 1000uL> {});

    inline static auto run(Container& container, std::size_t size) noexcept -> void
    {
        for (auto idx { 0uL }; idx < 1000uL; ++idx) {
            auto it = std::ranges::find_if(container, [&](auto x) { return x.a == idx; });
            container.insert(it, value_type { values[idx] });
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

template <typename Container>
struct Sort {
    inline static auto run(Container& container, std::size_t size) noexcept -> void
    {
        std::ranges::sort(container, std::less<> {});
    }

}; // struct Sort

template <typename T>
struct Sort<std::list<T>> {
    inline static auto run(std::list<T>& container, std::size_t size) noexcept -> void
    {
        container.sort();
    }

}; // struct Sort<std::list<T>>

template <typename Container>
struct Destroy {
    inline static auto run(Container& container, std::size_t size) noexcept -> void
    {
        container.erase(begin(container), end(container));
    }

}; // struct Destroy

template <typename Container>
struct RandomSortedInsert {

    static std::mt19937 gen;
    static std::uniform_int_distribution<std::size_t> distrib;

    inline static auto run(Container& container, std::size_t size) noexcept -> void
    {
        for (auto idx { 0uL }; idx < size; ++idx) {
            auto v = distrib(gen);
            container.insert(std::ranges::find_if(container, [&v](auto& x) { return x.a >= v; }), { v });
        }
    }

}; // struct RandomSortedInsert

template <typename Container>
std::mt19937 RandomSortedInsert<Container>::gen = std::mt19937 { std::random_device {}() };

template <typename Container>
std::uniform_int_distribution<std::size_t> RandomSortedInsert<Container>::distrib { 0, std::numeric_limits<std::size_t>::max() - 1uL };

} // namespace test

#endif // CXX_CONTAINER_TESTING_TESTS
