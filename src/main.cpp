/// Copyright 2023 Tyler Swann

#include <benchmark.hpp>
#include <csv-writer.hpp>
#include <makers.hpp>
#include <runners.hpp>
#include <tests.hpp>
#include <types.hpp>

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

using namespace std::literals;

using SmallType = types::Trivial<8>;

int main(int argc, char* argv[])
{
    ///////////

    auto sizes = std::views::iota(1)
        | std::views::transform([](auto x) { return x * 100'000uL; })
        | std::views::take(10)
        | ranges::to<std::vector<std::size_t>>();

    runners::run<SmallType, tests::PushBack, std::chrono::microseconds>(sizes);

    return 0;
}
