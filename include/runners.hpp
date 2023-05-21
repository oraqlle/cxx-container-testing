#ifndef CXX_CONTAINER_TESTING_RUNNERS
#define CXX_CONTAINER_TESTING_RUNNERS

#include <benchmark.hpp>
#include <csv-writer.hpp>
#include <makers.hpp>
#include <tests.hpp>
#include <types.hpp>

#include <range/v3/range/conversion.hpp>

#include <chrono>
#include <deque>
#include <list>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace runners {

using namespace std::literals;

auto to_count = std::views::transform([](auto x) { return x.count(); });

template <
    typename T,
    template <typename> class Test,
    typename Duration>
auto run(std::string_view data_name, const std::vector<std::size_t>& sizes) -> void
{
    auto list_results = benchmark::run<std::list<T>, Test, makers::Empty, Duration>(sizes);
    auto deque_results = benchmark::run<std::deque<T>, Test, makers::Empty, Duration>(sizes);
    auto vec_results = benchmark::run<std::vector<T>, Test, makers::Empty, Duration>(sizes);
    auto pre_vec_results = benchmark::run<std::vector<T>, Test, makers::Preallocated, Duration>(sizes);

    auto fname = ""s.append(data_name) + "-"s.append(Test<void>::name) + ".csv"s;
    csv::write(fname, "elements"s, sizes);
    csv::write(fname, "std::list"s, list_results | to_count | ranges::to<std::vector<long double>>());
    csv::write(fname, "std::deque"s, deque_results | to_count | ranges::to<std::vector<long double>>());
    csv::write(fname, "std::vector"s, vec_results | to_count | ranges::to<std::vector<long double>>());
    csv::write(fname, "preallocated std::vector"s, pre_vec_results | to_count | ranges::to<std::vector<long double>>());
}

template <typename Duration>
auto push_back(const std::vector<std::size_t>& sizes) -> void
{
    run<types::SmallType, tests::PushBack, Duration>("small-type", sizes);
    run<types::MediumType, tests::PushBack, Duration>("medium-type", sizes);
    run<types::LargeType, tests::PushBack, Duration>("large-type", sizes);
    run<types::HugeType, tests::PushBack, Duration>("huge-type", sizes);
    run<types::MonsterType, tests::PushBack, Duration>("monster-type", sizes);
}

template <typename Duration>
auto all(const std::vector<std::size_t>& sizes) -> void
{
    push_back<Duration>(sizes);
    // front_back<Duration>(sizes);
}

} // namespace runners

#endif // CXX_CONTAINER_TESTING_RUNNERS
