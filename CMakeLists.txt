cmake_minimum_required(VERSION 3.14)
project(nrel_spa)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.tar.gz
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Library
add_library(spa spa.cc spa.h)
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Test
add_executable(spa_test spa_test.cc)
target_link_libraries(spa_test spa GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(spa_test)
