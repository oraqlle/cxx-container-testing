/// Copyright 2023 Tyler Swann

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>

#include <range/v3/range/conversion.hpp>

#include <algorithm>
#include <array>
#include <chrono>
#include <concepts>
#include <deque>
#include <functional>
#include <iterator>
#include <list>
#include <numeric>
#include <optional>
#include <random>
#include <ranges>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

template <
    template <typename> class Container,
    typename DataType = double,
    // typename Duration = std::chrono::duration<double>,
    typename Duration = std::chrono::microseconds,
    std::size_t Repeats = 7,
    bool Preallocate = false>
    requires std::default_initializable<Container<DataType>>
class Tester {

public:
    enum class TestKind : short {
        PUSH_BACK,
        PUSH_FRONT,
        LINEAR_SEARCH,
        RANDOM_INSERT,
        DESTRUCTION,
        SORT,
        INCREMENTAL_SORTED_INSERT
    };

    struct NonTrivialType { };

public:
    using size_type = std::size_t;
    using clock_type = std::chrono::high_resolution_clock;
    using sizes_type = std::vector<std::size_t>;
    using int_distribution_type = std::uniform_int_distribution<unsigned long long>;
    using real_distribution_type = std::uniform_real_distribution<double>;
    using rand_engine_type = std::mt19937;
    using results_type = std::vector<Duration>;

public:
    Tester() noexcept = default;

    explicit Tester(sizes_type sizes) noexcept
        : container {}
        , sizes { sizes }
        , engine { std::random_device {}() }
        , int_distrib { std::numeric_limits<unsigned long long>::min(), std::numeric_limits<unsigned long long>::max() }
        , real_distrib { std::numeric_limits<double>::min(), std::numeric_limits<double>::max() }
        , results {}
    {
    }

    Tester(const Tester& tester) noexcept = default;
    Tester(Tester&& tester) noexcept = default;

    ~Tester() = default;

    /// Run a particular test
    auto run(TestKind test_kind) noexcept -> void
    {
        switch (test_kind) {
        case TestKind::PUSH_BACK:
            _M_run(std::mem_fn(&Tester::_M_push_back));
            break;

        case TestKind::PUSH_FRONT:
            // _M_run(std::mem_fn(this, Tester::_M_push_front));
            break;

        case TestKind::LINEAR_SEARCH:
            // _M_run(std::mem_fn(this, Tester::_M_linear_search));
            break;

        case TestKind::RANDOM_INSERT:
            // _M_run(std::mem_fn(this, Tester::_M_random_insert));
            break;

        case TestKind::DESTRUCTION:
            // _M_run(std::mem_fn(this, Tester::_M_destruction));
            break;

        case TestKind::SORT:
            // _M_run(std::mem_fn(this, Tester::_M_sort));
            break;

        case TestKind::INCREMENTAL_SORTED_INSERT:
            // _M_run(std::mem_fn(this, Tester::_M_incremental_sorted_insert));
            break;
        }

        using namespace std::literals;
        auto r = results | std::views::transform([](auto d) { return std::to_string(d.count()) + "us"s; });
        fmt::print("{}\n", fmt::join(r, ", "));
    }

    /// Run all tests and return the results
    /// in a hashmap.
    auto run_all() noexcept
        -> std::unordered_map<std::string, results_type>;

    auto clear() noexcept -> void;

    auto write_results(std::string filename) noexcept -> void;

private:
    auto _M_run(std::function<Duration(Tester*, size_type)>&& fn) noexcept -> void
    {
        auto times = std::vector<Duration>(sizes.size(), Duration {});

        for (auto i { 0 }; auto size : sizes) {
            if constexpr (Preallocate && std::is_same_v<Container<DataType>, std::vector<DataType>>)
                container.reserve(size);

            for (auto repeat { 0 }; repeat < Repeats; ++repeat) {
                auto duration = fn(this, size);
                times.at(i) += duration;
                container = Container<DataType> {};
            }

            i += 1;
        }

        std::ranges::transform(times, std::back_inserter(results), [](auto x) { return x / Repeats; });
    }

    /// Push back test for a particular
    /// container size.
    auto _M_push_back(size_type size) noexcept
        -> Duration
    {
        auto total_time = Duration {};

        for (auto i { 0 }; i < size; ++i) {
            auto num = real_distrib(engine);
            auto start = clock_type::now();
            container.push_back(num);
            auto end = clock_type::now();
            total_time += std::chrono::duration_cast<Duration>(end - start);
        }

        // return std::chrono::duration_cast<Duration>(end - start);
        return total_time;
    }

    /// Push front test for a particular
    /// container size.
    auto _M_push_front(size_type size) noexcept
        -> Duration;

    /// Linear search test for a particular
    /// container size.
    auto _M_linear_search(size_type size) noexcept
        -> Duration;

    /// Random insert (w/ linear search)
    /// test for a particular container size.
    auto _M_random_insert(size_type size) noexcept
        -> Duration;

    /// Destruction test for a particular
    /// container size.
    auto _M_destruction(size_type size) noexcept
        -> Duration;

    /// Sorting test for a particular container size.
    auto _M_sort(size_type size) noexcept
        -> Duration;

    /// Incremental sorted insert test for
    /// a particular container size.
    auto _M_incremental_sorted_insert(size_type size) noexcept
        -> Duration;

private:
    Container<DataType> container;
    sizes_type sizes;
    rand_engine_type engine;
    int_distribution_type int_distrib;
    real_distribution_type real_distrib;
    results_type results;
}; /// class Tester

int main(int argc, char** argv)
{
    auto sizes = std::views::iota(1)
        | std::views::transform([](auto x) { return x * 100'000uL; })
        | std::views::take(10)
        | ranges::to<std::vector<std::size_t>>();

    auto test_list = Tester<std::list>(sizes);
    auto test_deque = Tester<std::deque>(sizes);
    auto test_vector = Tester<std::vector>(sizes);
    auto test_vector_pre = Tester<std::vector, double, std::chrono::microseconds, 7, true>(sizes);

    test_list.run(Tester<std::list>::TestKind::PUSH_BACK);
    test_deque.run(Tester<std::deque>::TestKind::PUSH_BACK);
    test_vector.run(Tester<std::vector>::TestKind::PUSH_BACK);
    test_vector_pre.run(Tester<std::vector, double, std::chrono::microseconds, 7, true>::TestKind::PUSH_BACK);

    return 0;
}
