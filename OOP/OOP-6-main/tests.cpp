#include <sstream>
#include <vector>
#include <memory>
#include "ork.hpp"
#include "bear.hpp"
#include "squirrel.hpp"
#include "factory.hpp"
#include <gtest/gtest.h>

TEST(Constructors, Ork) 
{
    Ork s(0, 0, "Sandy");
    std::stringstream out;
    s.print(out);
    ASSERT_EQ(out.str(), "Ork Sandy {0, 0}");
}

TEST(Constructors, Bear) 
{
    Bear w(1, 99, "Sumerok");
    std::stringstream out;
    w.print(out);
    ASSERT_EQ(out.str(), "Bear Sumerok {1, 99}");
}

TEST(Constructors, Squirrel) 
{
    Squirrel d(50, 50, "Woody");
    std::stringstream out;
    d.print(out);
    ASSERT_EQ(out.str(), "Squirrel Woody {50, 50}");
}
