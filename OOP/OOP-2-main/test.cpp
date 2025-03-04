#include <gtest/gtest.h>
#include "octal.hpp"

TEST(test1, basic_test_set1)
{
    Octal number1, number2;

    ASSERT_TRUE(number1.to_string() == "0" && number2.to_string() == "0");

    number1 = {'6', '3'};
    number2 = {'2', '2'};
    EXPECT_FALSE(number1 == number2);
    EXPECT_FALSE(number1 < number2);
    EXPECT_TRUE(number1 > number2);
}

TEST(test2, basic_test_set2)
{
    Octal number1, number2,  number3;

    number1 = {'6'};
    number2 = {'3'};
    number3 = {'3'};
    number2 = number2 + number3;
    EXPECT_TRUE(number1 == number2);
    EXPECT_FALSE(number1 > number2);
    EXPECT_FALSE(number1 < number2);
}

TEST(test3, basic_test_set3)
{
Octal number1, number2, number3;

    number1 = {'6', '1', '5'};
    number2 = {'5', '4'};
    number3 = {'3', '0', '7'};

    ASSERT_TRUE(number1.to_string() == "615" && number2.to_string() == "54" && number3.to_string() == "307");

    number1 = number1 - number2; 
    EXPECT_TRUE(number1.to_string() == "541");

    number3 = number3 + number2; 
    EXPECT_TRUE(number3.to_string() == "363");

}

TEST(test4, basic_test_set4)
{
    Octal number1 = {'1', '0', '0', '0'};
    Octal number2 = {'1'};
    Octal number3 = number1 - number2;

    EXPECT_TRUE(number3.to_string() == "777");

}

TEST(test5, basic_test_set5)
{
    Octal number1 = {'7', '7', '7'};
    Octal number2 = {'1'};
    Octal number3 = number1 + number2;
    
    EXPECT_TRUE(number3.to_string() == "1000");

    number3 = number2 + number1;
    EXPECT_TRUE(number3.to_string() == "1000");
}

TEST(test6, basic_test_set6)
{
    Octal number1 = {'3'};
    Octal number2 = {'0'};
    Octal number3 = number1 - number2;
    Octal number4 = number1 + number2;
    Octal number5 = number2 - number2;
    Octal number6 = number2 + number2;

    EXPECT_TRUE(number3.to_string() == "3");
    EXPECT_TRUE(number4.to_string() == "3");
    EXPECT_TRUE(number5.to_string() == "0");
    EXPECT_TRUE(number6.to_string() == "0");
}

TEST(test7, basic_test_set7)
{
Octal number1, number2;

    number1 = {'7', '1', '5', '0', '7', '4', '2', '4'};
    number2 = {'5', '4', '0', '1', '3', '4', '4', '7'};

    number1 = number1 + number2; 
    EXPECT_TRUE(number1.to_string() == "145523073");


}

