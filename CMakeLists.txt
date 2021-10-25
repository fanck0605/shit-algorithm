cmake_minimum_required(VERSION 3.14)

project(TryCMake VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

add_subdirectory(brackets_match)
add_subdirectory(stack)
add_subdirectory(rvalue_reference)
add_subdirectory(binary_tree)
add_subdirectory(graph)
add_subdirectory(search)
add_subdirectory(sort)
add_subdirectory(longest_common_subsequence)

add_executable(Main main.cpp)
