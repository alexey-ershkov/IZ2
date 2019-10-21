cmake_minimum_required(VERSION 3.8)
project(IZ2)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_C_STANDARD  99)

add_subdirectory(lib/)
include_directories(lib/googletest/include)
include_directories(headers/)

find_package (Threads)

set(LibSourses linear_search.c parallel_search.c is_capital.c)

add_library(MyLibStatic STATIC ${LibSourses})
add_library(MyLibShared SHARED ${LibSourses})

add_executable(IZ2 main.c)
target_link_libraries(IZ2 pthread MyLibStatic)


enable_testing()
add_executable(Gtest gtest.cpp)
target_link_libraries(Gtest MyLibStatic)
target_link_libraries(Gtest gtest gtest_main)
target_link_libraries(Gtest pthread)
add_test(UnitTest Gtest)



