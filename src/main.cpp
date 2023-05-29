/// Copyright 2023 Tyler Swann

#include <cli.hpp>

#include <argparse/argparse.hpp>

#include <cstdlib>
#include <exception>
#include <ostream>
#include <string>
#include <vector>

using namespace std::literals;

int main(int argc, char* argv[])
{
    auto program = argparse::ArgumentParser { "cxx-container-testing", "v0.1.0" };

    program.add_description("Tests a variety of different fundamental operations on C++ Containers");

    program.add_argument("-l", "--list")
        .help("Lists all available tests")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-t", "--test")
        .help("Run a particular test")
        .append();

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    if (program["--list"] == true) {
        cli::list_tests();
        std::exit(0);
    }

    auto tests = program.get<std::vector<std::string>>("--test");

    if (tests.empty())
        tests.push_back("all"s);

    cli::run_tests(tests);
    std::exit(0);

    return 0;
}
