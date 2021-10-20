cmake_minimum_required(VERSION 3.14)

add_library(Graph INTERFACE)
target_include_directories(Graph INTERFACE include)

add_executable(GraphTest test/graph_test.cpp)
target_link_libraries(GraphTest PRIVATE Graph)
add_test(GraphTest GraphTest)
