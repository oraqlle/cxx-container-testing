/// Copyright 2023 Tyler Swann

#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>

#include <range/v3/range/conversion.hpp>

#include <chrono>
#include <deque>
#include <list>
#include <source_location>
#include <string>
#include <vector>

#include <benchmark.hpp>
#include <csv-writer.hpp>
#include <makers.hpp>
#include <runners.hpp>
#include <tests.hpp>
#include <types.hpp>

using namespace std::literals;

using SmallType = types::Trivial<8>;

int main(int argc, char* argv[])
{
    // auto sizes = std::views::iota(1)
    //     | std::views::transform([](auto x) { return x * 100'000uL; })
    //     | std::views::take(10)
    //     | ranges::to<std::vector<std::size_t>>();

    // auto list_results = benchmark::run<std::list<SmallType>, tests::PushBack, makers::Empty, std::chrono::microseconds>(sizes);
    // auto deque_results = benchmark::run<std::deque<SmallType>, tests::PushBack, makers::Empty, std::chrono::microseconds>(sizes);
    // auto vec_results = benchmark::run<std::vector<SmallType>, tests::PushBack, makers::Empty, std::chrono::microseconds>(sizes);
    // auto pre_vec_results = benchmark::run<std::vector<SmallType>, tests::PushBack, makers::Preallocated, std::chrono::microseconds>(sizes);

    // fmt::print("List:                 {}\n", list_results);
    // fmt::print("Deque:                {}\n", deque_results);
    // fmt::print("Vector:               {}\n", vec_results);
    // fmt::print("Pre-allocated Vector: {}\n", pre_vec_results);
    ////

    csv::write("test.csv", "name-1", std::vector<double> { 1.6, 8.01, -0.06 });
    csv::write("test.csv", "name-2", std::vector<double> { 0.333, 0.01, -15.06 });

    return 0;
}
