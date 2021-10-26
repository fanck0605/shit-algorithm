cmake_minimum_required(VERSION 3.14)

add_library(Knapsack INTERFACE)
target_include_directories(Knapsack INTERFACE include)

add_executable(KnapsackTest test/knapsack_test.cpp)
target_link_libraries(KnapsackTest PRIVATE Knapsack)
add_test(KnapsackTest KnapsackTest)
