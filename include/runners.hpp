#ifndef CXX_CONTAINER_TESTING_RUNNERS
#define CXX_CONTAINER_TESTING_RUNNERS

#include <benchmark.hpp>
#include <csv-writer.hpp>
#include <makers.hpp>

#include <range/v3/range/conversion.hpp>

#include <chrono>
#include <deque>
#include <list>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

// Run the given test for specified type on all data structures.

namespace runners {

using namespace std::literals;

auto to_count = std::views::transform([](auto x) { return x.count(); });

template <
    typename T,
    template <typename> class Test,
    typename Duration>
auto run(const std::vector<std::size_t>& sizes) -> void
{
    auto list_results = benchmark::run<std::list<T>, Test, makers::Empty, Duration>(sizes);
    auto deque_results = benchmark::run<std::deque<T>, Test, makers::Empty, Duration>(sizes);
    auto vec_results = benchmark::run<std::vector<T>, Test, makers::Empty, Duration>(sizes);
    auto pre_vec_results = benchmark::run<std::vector<T>, Test, makers::Preallocated, Duration>(sizes);

    auto fname = ""s.append(Test<std::vector<T>>::name) + ".csv"s;
    csv::write(fname, "elements"s, sizes);
    csv::write(fname, "std::list"s, list_results | to_count | ranges::to<std::vector<long double>>());
    csv::write(fname, "std::deque"s, deque_results | to_count | ranges::to<std::vector<long double>>());
    csv::write(fname, "std::vector"s, vec_results | to_count | ranges::to<std::vector<long double>>());
    csv::write(fname, "preallocated std::vector"s, pre_vec_results | to_count | ranges::to<std::vector<long double>>());
}

} // namespace runners

#endif // CXX_CONTAINER_TESTING_RUNNERS
