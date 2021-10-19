cmake_minimum_required(VERSION 3.14)

add_library(Stack INTERFACE)
target_include_directories(Stack INTERFACE include)

add_executable(StackTest test/stack_test.cpp)
target_link_libraries(StackTest PRIVATE Stack)
add_test(StackTest StackTest)
