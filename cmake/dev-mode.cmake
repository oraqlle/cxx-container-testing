include(cmake/folders.cmake)

include(CTest)
if(BUILD_TESTING)
#   add_subdirectory(tests)
endif()

add_custom_target(
    run-cxx-container-testing
    COMMAND cxx-container-testing
    VERBATIM
)
add_dependencies(run-cxx-container-testing cxx-container-testing)

option(ENABLE_COVERAGE "Enable coverage support separate from CTest's" OFF)
if(ENABLE_COVERAGE)
  include(cmake/coverage.cmake)
endif()

include(cmake/lint-targets.cmake)
include(cmake/spell-targets.cmake)

add_folders(Project)
