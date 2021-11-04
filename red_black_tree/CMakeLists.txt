cmake_minimum_required(VERSION 3.14)

add_library(RedBlackTree INTERFACE)
target_include_directories(RedBlackTree INTERFACE include)

add_executable(RedBlackTreeTest test/rb_tree_test.cpp)
target_link_libraries(RedBlackTreeTest PRIVATE RedBlackTree)
add_test(RedBlackTreeTest RedBlackTreeTest)
