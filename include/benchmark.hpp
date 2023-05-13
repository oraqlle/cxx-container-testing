#ifndef TESTER
#define TESTER

#include <algorithm>
#include <chrono>
#include <concepts>
#include <initializer_list>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

template <template <typename> class Container, typename DataType>
    requires std::default_initializable<Container<DataType>>
class Benchmark {

public:
public:
    using size_type = std::size_t;
    using clock_type = std::chrono::high_resolution_clock;
    using container_type = Container<DataType>;

public:
    Benchmark() noexcept = default;

    Benchmark(const Benchmark& tester) noexcept = default;
    Benchmark(Benchmark&& tester) noexcept = default;

    ~Benchmark() = default;

    template <
        template <typename> class Tester,
        template <typename> class Maker,
        typename Duration,
        std::size_t Repeats = 7,
        std::ranges::input_range Sizes>
    auto run(Sizes sizes) noexcept
        -> std::vector<Duration>
    {
        auto results = std::vector<Duration> {};

        for (auto size : sizes) {
            auto duration = Duration {};

            for (auto i { 0uL }; i < Repeats; ++i) {
                container = Maker<container_type>::make(size);
                auto start = clock_type::now();
                Tester<container_type>::run(container, size);
                auto end = clock_type::now();
                duration += std::chrono::duration_cast<Duration>(end - start);
            }

            results.push_back(duration);
        }

        Maker<container_type>::clean();
        std::ranges::transform(results, results.begin(), [](auto x) { return x / Repeats; });
        return results;
    }

private:
    container_type container;
}; /// class Benchmark

#endif // TESTER
