#include <gtest/gtest.h>
#include "fun.h"

using namespace std;

string s;

TEST(test01, basic_test_set)
{
    s = "()";
    ASSERT_TRUE(tutu(s)==true);
}

TEST(test02, basic_test_set)
{
    s = "(";
    ASSERT_TRUE(tutu(s)==false);
}

TEST(test03, basic_test_set)
{
    s = ")(())";
    ASSERT_TRUE(tutu(s)==false);
}

TEST(test04, basic_test_set)
{
    s = "(())((()())())((()))";
    ASSERT_TRUE(tutu(s)==true);
}

TEST(test05, basic_test_set)
{
    s = "";
    ASSERT_TRUE(tutu(s)==true);
}

TEST(test06, basic_test_set)
{
    s = "(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))))))))))))";
    ASSERT_TRUE(tutu(s)==true);
}

TEST(test07, basic_test_set)
{    s = ")((((((((((((((((((((((((((((((((((((((()))))))))))))))))))))))))))))))))))))))";
    ASSERT_TRUE(tutu(s)==false);
}

TEST(test08, basic_test_set)
{
    s = ")(";
    ASSERT_TRUE(tutu(s)==false);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}