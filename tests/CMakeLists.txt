cmake_minimum_required(VERSION 3.23)
project(tests)

set(CMAKE_CXX_STANDARD 17)




#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#)

add_library(route_parser STATIC ${CMAKE_CURRENT_SOURCE_DIR}/../route_parser.c)
set_target_properties(route_parser PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-build-debug/libroute_parser.a)

find_package(GTest REQUIRED)

add_executable(
        tests
        main.cpp
)

target_link_libraries(tests route_parser)
target_link_libraries(tests GTest::gtest)
enable_testing()
gtest_add_tests(TARGET tests)##!! automatically let ctest scan
# then you can run `ctest` or `make test`
# for best practice, `ctest --output-on-failure` is what you need