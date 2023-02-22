cmake_minimum_required(VERSION 3.11)

# set the project name and version
project(test_fetch_content_one_tbb VERSION 0.0)

# define C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# donwload onetbb
include(FetchContent)
FetchContent_Declare(
  tbb
  GIT_REPOSITORY https://github.com/oneapi-src/oneTBB.git
  GIT_TAG v2021.7.0
  GIT_SHALLOW ON
)
option(TBB_TEST OFF)
FetchContent_MakeAvailable(tbb)

# add the executable
add_executable(one_tbb_example one_tbb_example.cpp)

target_link_libraries(one_tbb_example TBB::tbb)

enable_testing()

add_test(NAME one_tbb_example COMMAND $<TARGET_FILE:one_tbb_example>)
