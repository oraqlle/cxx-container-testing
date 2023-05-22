#ifndef CXX_CONTAINER_TESTING_TESTS
#define CXX_CONTAINER_TESTING_TESTS

#include <algorithm>
#include <ranges>
#include <string_view>

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

} // namespace test

#endif // CXX_CONTAINER_TESTING_TESTS
