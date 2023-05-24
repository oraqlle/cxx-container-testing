#ifndef CXX_CONTAINER_TESTING_BENCHMARK
#define CXX_CONTAINER_TESTING_BENCHMARK

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/std.h>

#include <algorithm>
#include <chrono>
#include <concepts>
#include <initializer_list>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace benchmark {
template <
    typename Container,
    template <typename> class Tester,
    template <typename> class Maker,
    typename Duration,
    std::size_t Repeats = 7,
    std::ranges::input_range Sizes>
inline auto run(Sizes sizes, std::string_view test_name, std::string_view container_name) noexcept
    -> std::vector<Duration>
{
    fmt::print(
        "    {} {}\n        {} {}\n",
        fmt::styled(
            "[ Started Test ]:",
            fmt::emphasis::bold | fmt::fg(fmt::color::yellow)),
        test_name,
        fmt::styled(
            "[ Container Type ]:",
            fmt::emphasis::bold | fmt::fg(fmt::color::cyan)),
        container_name);

    using clock_type = std::chrono::high_resolution_clock;

    auto results = std::vector<Duration> {};

    for (auto size : sizes) {
        auto duration = Duration {};

        for (auto i { 0uL }; i < Repeats; ++i) {
            auto container = Maker<Container>::make(size);
            auto start = clock_type::now();
            Tester<Container>::run(container, size);
            auto end = clock_type::now();
            duration += std::chrono::duration_cast<Duration>(end - start);
        }

        results.push_back(duration);
    }

    Maker<Container>::clean();
    std::ranges::transform(results, results.begin(), [](auto x) { return x / Repeats; });

    fmt::print(
        "    {} {}\n        {} {}\n",
        fmt::styled(
            "[ Finished Test ]:",
            fmt::emphasis::bold | fmt::fg(fmt::color::green_yellow)),
        test_name,
        fmt::styled(
            "[ Container Type ]:",
            fmt::emphasis::bold | fmt::fg(fmt::color::cyan)),
        container_name);

    return results;
}
} // namespace benchmark

#endif // CXX_CONTAINER_TESTING_BENCHMARK
