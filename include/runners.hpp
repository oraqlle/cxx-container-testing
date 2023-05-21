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
#include <filesystem>
#include <list>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace runners {

namespace fs = std::filesystem;
using namespace std::literals;

auto to_count = std::views::transform([](auto x) { return x.count(); });

template <typename T>
struct PushBack {
    static auto run() -> void
    {
        auto sizes = std::views::iota(1)
            | std::views::transform([](auto x) { return x * 100'000uL; })
            | std::views::take(10)
            | ranges::to<std::vector<std::size_t>>();

        auto list_results = benchmark::run<std::list<T>, tests::PushBack, makers::Empty, std::chrono::microseconds>(sizes);
        auto deque_results = benchmark::run<std::deque<T>, tests::PushBack, makers::Empty, std::chrono::microseconds>(sizes);
        auto vec_results = benchmark::run<std::vector<T>, tests::PushBack, makers::Empty, std::chrono::microseconds>(sizes);
        auto pre_vec_results = benchmark::run<std::vector<T>, tests::PushBack, makers::Preallocated, std::chrono::microseconds>(sizes);

        auto fname = ""s.append(types::name<T>()) + ".csv"s;
        auto sub_dir_name = fs::path { tests::PushBack<void>::name };
        csv::write(sub_dir_name, fname, "elements"s, sizes);
        csv::write(sub_dir_name, fname, "std::list"s, list_results | to_count | ranges::to<std::vector<long double>>());
        csv::write(sub_dir_name, fname, "std::deque"s, deque_results | to_count | ranges::to<std::vector<long double>>());
        csv::write(sub_dir_name, fname, "std::vector"s, vec_results | to_count | ranges::to<std::vector<long double>>());
        csv::write(sub_dir_name, fname, "preallocated std::vector"s, pre_vec_results | to_count | ranges::to<std::vector<long double>>());
    }
}; // struct PushBack

template <template <typename> class Runner>
auto run_for_types() -> void
{
}

template <template <typename> class Runner, typename T, typename... Ts>
auto run_for_types() -> void
{
    Runner<T>::run();
    run_for_types<Runner, Ts...>();
}

template <typename... Ts>
auto all() -> void
{
    run_for_types<PushBack, Ts...>();
}

} // namespace runners

#endif // CXX_CONTAINER_TESTING_RUNNERS
