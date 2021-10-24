cmake_minimum_required(VERSION 3.14)

add_library(Sort INTERFACE)
target_include_directories(Sort INTERFACE include)

add_executable(SortTest test/sort_test.cpp)
target_link_libraries(SortTest PRIVATE Sort)
add_test(SortTest SortTest)
