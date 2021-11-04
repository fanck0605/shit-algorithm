cmake_minimum_required(VERSION 3.14)

add_library(AvlTree INTERFACE)
target_include_directories(AvlTree INTERFACE include)

add_executable(AvlTreeTest test/avl_tree_test.cpp)
target_link_libraries(AvlTreeTest PRIVATE AvlTree)
add_test(AvlTreeTest AvlTreeTest)
