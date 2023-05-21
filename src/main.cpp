/// Copyright 2023 Tyler Swann

#include <runners.hpp>

#include <range/v3/range/conversion.hpp>

#include <chrono>
#include <vector>

int main(int argc, char* argv[])
{
    auto sizes = std::views::iota(1)
        | std::views::transform([](auto x) { return x * 100'000uL; })
        | std::views::take(10)
        | ranges::to<std::vector<std::size_t>>();

    runners::push_back<std::chrono::microseconds>(sizes);

    return 0;
}
