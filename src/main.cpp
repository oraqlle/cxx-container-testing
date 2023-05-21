/// Copyright 2023 Tyler Swann

#include <runners.hpp>
#include <types.hpp>
//////////////
#include <chrono>
#include <vector>

int main(int argc, char* argv[])
{
    runners::all<
        types::SmallType,
        types::MediumType,
        types::LargeType,
        types::HugeType,
        types::MonsterType>();

    return 0;
}
