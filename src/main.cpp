/// Copyright 2023 Tyler Swann

#include <runners.hpp>
#include <types.hpp>
//////
#include <chrono>
#include <vector>

int main(int argc, char* argv[])
{
    runners::all<
        types::TrivialSmallType,
        types::TrivialMediumType,
        types::TrivialLargeType,
        types::TrivialHugeType,
        types::TrivialMonsterType>();

    return 0;
}
