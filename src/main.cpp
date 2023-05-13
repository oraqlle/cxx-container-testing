/// Copyright 2023 Tyler Swann

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/chrono.h>
#include <fmt/std.h>

#include <range/v3/range/conversion.hpp>

#include <chrono>
#include <vector>
#include <string>

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

    auto vector_benchmark = Benchmark<std::vector, double> { };
    auto results = vector_benchmark.run<tests::PushBack, makers::Empty, std::chrono::milliseconds>(sizes);

    fmt::print("Vector: {}\n", results);

    return 0;
}
