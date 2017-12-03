cmake_minimum_required(VERSION 3.0)

project(calendar-aoc2017)

set (CMAKE_CXX_STANDARD 17)

set(SRC_DIR src/)

set(SOURCE main.cpp ${SRC_DIR}/day01.cpp ${SRC_DIR}/day02.cpp ${SRC_DIR}/day03.cpp)

include_directories(${SRC_DIR})

add_executable(${PROJECT_NAME} ${SOURCE})