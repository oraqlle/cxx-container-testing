#ifndef RUNNERS
#define RUNNERS

#include <csv-writer.hpp>

#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fmt/std.h>

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

    fmt::print("l: {}\n", list_results);
    fmt::print("d: {}\n", deque_results);
    fmt::print("v: {}\n", vec_results);
    fmt::print("p: {}\n", pre_vec_results);

    auto fname = (""s).append(Test<std::vector<T>>::name) + ".csv"s;
    csv::write(fname, "times"s, sizes);
    csv::write(fname, "std::list"s, list_results | to_count | ranges::to<std::vector<long double>>());
    // csv::write(fname, "std::deque"s, deque_results);
    // csv::write(fname, "std::vector"s, vec_results);
    // csv::write(fname, "preallocated std::vector"s, pre_vec_results);
}

} // namespace runners

#endif // RUNNERS
