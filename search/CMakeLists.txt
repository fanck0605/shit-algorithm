cmake_minimum_required(VERSION 3.14)

add_library(Search INTERFACE)
target_include_directories(Search INTERFACE include)

add_executable(SearchTest test/search_test.cpp)
target_link_libraries(SearchTest PRIVATE Search)
add_test(SearchTest SearchTest)
