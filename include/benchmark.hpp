#ifndef BENCHMARK
#define BENCHMARK

#include <algorithm>
#include <chrono>
#include <concepts>
#include <initializer_list>
#include <ranges>
#include <string>
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
inline auto run(Sizes sizes) noexcept
    -> std::vector<Duration>
{
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
    return results;
}
} // namespace benchmark

#endif // BENCHMARK
