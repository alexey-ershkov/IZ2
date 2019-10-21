//
// Created by Алексей on 2019-10-21.
//

#include "gtest/gtest.h"
#include <iostream>

extern "C"
{
    #include "headers/is_capital.h"
    #include "headers/linear_search.h"
    #include "headers/parallel_search.h"
};

TEST(test_linear_search, test1)
{
    char input[10] = "'Abc'habc";
    ASSERT_EQ(3,linear_str_search(input));
}

TEST(test_linear_search, test2)
{
    char input[10] = "abch'Abc'";
    ASSERT_EQ(3,linear_str_search(input));
}


TEST(test_linear_search, test3)
{
    char input[10] = "a'Bchabc'";
    ASSERT_EQ(6,linear_str_search(input));
}

TEST(test_parallel_search, test1)
{
    char input[10] = "'Abc'habc";
    ASSERT_EQ(3,parallel_str_search(input));
}

TEST(test_parallel_search, test2)
{
    char input[10] = "abch'Abc'";
    ASSERT_EQ(3,parallel_str_search(input));
}


TEST(test_parallel_search, test3)
{
    char input[10] = "a'Bchabc'";
    ASSERT_EQ(6,parallel_str_search(input));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}