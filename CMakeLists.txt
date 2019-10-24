cmake_minimum_required(VERSION 3.8)
project(IZ2)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_C_STANDARD  99)

add_subdirectory(lib/)
include_directories(lib/googletest/include)
include_directories(headers/)

find_package (Threads)

set(LibSourses linear_search.c parallel_search.c is_capital.c)
set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic")

add_library(MyLibStatic STATIC ${LibSourses})
add_library(MyLibShared SHARED ${LibSourses})


add_executable(IZ2  main.c)
target_link_libraries(IZ2 ${CMAKE_THREAD_LIBS_INIT} MyLibStatic)


enable_testing()
add_executable(Gtest gtest.cpp)
target_link_libraries(Gtest MyLibStatic)
target_link_libraries(Gtest gtest gtest_main)
target_link_libraries(Gtest pthread)
add_test(UnitTest Gtest)

# ------------------------------------------------------------------------------
# Valgrind
# ------------------------------------------------------------------------------
include(CTest)
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --track-fds=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")

# ------------------------------------------------------------------------------
# Coverage
# ------------------------------------------------------------------------------

if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

