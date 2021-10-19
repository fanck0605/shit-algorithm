cmake_minimum_required(VERSION 3.14)

add_library(BinaryTree INTERFACE)
target_include_directories(BinaryTree INTERFACE include)

add_executable(BinaryTreeTest test/binary_tree_test.cpp)
target_link_libraries(BinaryTreeTest PRIVATE BinaryTree)
add_test(BinaryTreeTest BinaryTreeTest)
