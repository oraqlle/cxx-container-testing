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
#include <string>
#include <vector>

#include <benchmark.hpp>
#include <makers.hpp>
#include <tests.hpp>

using namespace std::literals;

int main(int argc, char** argv)
{
    auto sizes = std::views::iota(1)
        | std::views::transform([](auto x) { return x * 100'000uL; })
        | std::views::take(10)
        | ranges::to<std::vector<std::size_t>>();

    auto list_results = benchmark::run<std::list<double>, tests::PushBack, makers::Empty, std::chrono::microseconds>(sizes);
    auto deque_results = benchmark::run<std::deque<double>, tests::PushBack, makers::Empty, std::chrono::microseconds>(sizes);
    auto vec_results = benchmark::run<std::vector<double>, tests::PushBack, makers::Empty, std::chrono::microseconds>(sizes);
    auto pre_vec_results = benchmark::run<std::vector<double>, tests::PushBack, makers::Preallocated, std::chrono::microseconds>(sizes);

    fmt::print("List:                 {}\n", list_results);
    fmt::print("Deque:                {}\n", deque_results);
    fmt::print("Vector:               {}\n", vec_results);
    fmt::print("Pre-allocated Vector: {}\n", pre_vec_results);

    return 0;
}
