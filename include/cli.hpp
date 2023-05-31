#ifndef CXX_CONTAINER_TESTING_CLI
#define CXX_CONTAINER_TESTING_CLI

#include <runners.hpp>
#include <types.hpp>

#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fmt/std.h>

#include <array>
#include <string>
#include <string_view>
#include <vector>

namespace cli {

using namespace std::literals;

constexpr std::array<std::string_view, 10> test_names = {
    "all                       - Run all tests"sv,
    "push-back                 - Tests containers ability to add elements to the back."sv,
    "push-front                - Tests containers ability to erase elements add elements to the front."sv,
    "linear-search             - Tests ability linearly search for elements in the container."sv,
    "random-insert             - Tests containers ability to insert elements into a random position."sv,
    "random-erase              - Tests containers ability to erase elements from a random position."sv,
    "random-remove             - Tests containers ability to remove and then erase elements from a random position."sv,
    "sort                      - Tests containers ability to sorted."sv,
    "destruction               - Tests containers ability to be destroyed."sv,
    "incremental sorted insert - Tests containers ability to have elements incrementally inserted into a sorted position."sv,
};

auto run_tests(const std::vector<std::string>& test_args) noexcept -> void
{
    for (auto& test_arg : test_args) {
        if (test_arg == "all"sv) {
            runners::all<
                types::TrivialSmallType,
                types::TrivialMediumType,
                types::TrivialLargeType,
                types::TrivialHugeType,
                types::TrivialMonsterType>();

            break;
        } else if (test_arg == "push-back") {
            runners::run_for_types<
                runners::PushBack,
                types::TrivialSmallType,
                types::TrivialMediumType,
                types::TrivialLargeType,
                types::TrivialHugeType,
                types::TrivialMonsterType>();
        } else if (test_arg == "push-front") {
            runners::run_for_types<
                runners::PushFront,
                types::TrivialSmallType,
                types::TrivialMediumType,
                types::TrivialLargeType,
                types::TrivialHugeType,
                types::TrivialMonsterType>();
        } else if (test_arg == "linear-search"sv) {
            runners::run_for_types<
                runners::LinearSearch,
                types::TrivialSmallType,
                types::TrivialMediumType,
                types::TrivialLargeType,
                types::TrivialHugeType,
                types::TrivialMonsterType>();
        } else if (test_arg == "random-insert"sv) {
            runners::run_for_types<
                runners::RandomInsert,
                types::TrivialSmallType,
                types::TrivialMediumType,
                types::TrivialLargeType,
                types::TrivialHugeType,
                types::TrivialMonsterType>();
        } else if (test_arg == "random-erase"sv) {
            runners::run_for_types<
                runners::RandomErase,
                types::TrivialSmallType,
                types::TrivialMediumType,
                types::TrivialLargeType,
                types::TrivialHugeType,
                types::TrivialMonsterType>();
        } else if (test_arg == "random-remove"sv) {
            runners::run_for_types<
                runners::RandomRemove,
                types::TrivialSmallType,
                types::TrivialMediumType,
                types::TrivialLargeType,
                types::TrivialHugeType,
                types::TrivialMonsterType>();
        } else if (test_arg == "sort"sv) {
            runners::run_for_types<
                runners::Sort,
                types::TrivialSmallType,
                types::TrivialMediumType,
                types::TrivialLargeType,
                types::TrivialHugeType,
                types::TrivialMonsterType>();
        } else if (test_arg == "destroy"sv) {
            runners::run_for_types<
                runners::Destroy,
                types::TrivialSmallType,
                types::TrivialMediumType,
                types::TrivialLargeType,
                types::TrivialHugeType,
                types::TrivialMonsterType>();
        } else {
            fmt::print("Invalid test selected.\n\nAvailable Tests:\n{}\n\n", fmt::join(test_names, "\n"sv));
        }
    }
}

auto list_tests() noexcept -> void
{
    fmt::print("C++ Container Tester\n\nAvailable Tests:\n{}\n\n", fmt::join(test_names, "\n"sv));
}

} // namespace cli

#endif // CXX_CONTAINER_TESTING_CLI
