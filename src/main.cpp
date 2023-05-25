/// Copyright 2023 Tyler Swann

#include <cli.hpp>

#include <cxxopts.hpp>

#include <string>
#include <string_view>
#include <vector>

using namespace std::literals;

int main(int argc, char* argv[])
{
    auto cli_options = cxxopts::Options {
        "C++ Container Testing",
        "A simple program for benchmarking the performance off C++ standard containers."
    };

    cli_options.add_options()(
        "t,test",
        "Run a particular test",
        cxxopts::value<std::vector<std::string>>()->implicit_value("all"));

    cli_options.add_options()(
        "l,list",
        "List all available tests",
        cxxopts::value<bool>()->default_value("false"));

    auto args = cli_options.parse(argc, argv);

    cli::list_tests(args);
    cli::run_tests(args);

    return 0;
}
