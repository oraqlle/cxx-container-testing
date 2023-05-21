/// Copyright 2023 Tyler Swann

#include <runners.hpp>
#include <tests.hpp>
#include <types.hpp>
/////////////
#include <range/v3/range/conversion.hpp>

#include <chrono>
#include <vector>

using SmallType = types::Trivial<8>;

int main(int argc, char* argv[])
{
    auto sizes = std::views::iota(1)
        | std::views::transform([](auto x) { return x * 100'000uL; })
        | std::views::take(10)
        | ranges::to<std::vector<std::size_t>>();

    runners::run<SmallType, tests::PushBack, std::chrono::microseconds>(sizes);

    return 0;
}
