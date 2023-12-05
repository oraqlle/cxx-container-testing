cmake_minimum_required(VERSION 3.15)

include(cmake/prelude.cmake)

project(
    lispy
    VERSION 0.2.0
    DESCRIPTION "Simple Tests of C++ standard containers"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Dependencies ----

# find_package(Threads)
find_package(fmt CONFIG REQUIRED)
find_package(argparse CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)

find_path(RAPIDCSV_INCLUDE_DIRS "rapidcsv.h")

# ---- Declare executable ----

add_executable(cxx-container-testing src/main.cpp)
add_executable(cxx-container-testing::exe ALIAS cxx-container-testing)

target_compile_features(cxx-container-testing PRIVATE cxx_std_20)

target_include_directories(
    cxx-container-testing ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_link_libraries(cxx-container-testing PRIVATE fmt::fmt)
target_link_libraries(cxx-container-testing PRIVATE range-v3::meta range-v3::concepts range-v3::range-v3)
target_link_libraries(cxx-container-testing PRIVATE argparse::argparse)

target_include_directories(cxx-container-testing PRIVATE ${RAPIDCSV_INCLUDE_DIRS})

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
    include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT cxx-container-testing_DEVELOPER_MODE)
    return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
    message(
        AUTHOR_WARNING
        "Developer mode is intended for developers of the Lispy interpreter"
    )
endif()

include(cmake/dev-mode.cmake)
