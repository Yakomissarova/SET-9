cmake_minimum_required(VERSION 4.1)
project(set_9)

set(CMAKE_CXX_STANDARD 17)

add_executable(set_9_P1 Codeforces/P1.cpp)
add_executable(set_9_P2 Codeforces/P2.cpp)
add_executable(set_9_P3 Codeforces/P3.cpp)

add_executable(run_all
        src/main.cpp
        src/string_generator.cpp
        src/string_sort_tester.cpp
        src/sorts.cpp
)
