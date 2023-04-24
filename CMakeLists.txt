cmake_minimum_required(VERSION 3.23)
project(route_parser C)

set(CMAKE_C_STANDARD 99)

add_library(route_parser route_parser.c tests/main.cpp)

