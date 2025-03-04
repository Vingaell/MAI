#include <gtest/gtest.h>
#include <memory>
#include "npc.hpp"
#include "squirrel.hpp"
#include "bear.hpp"
#include "ork.hpp"

TEST(test1, Squirrel_constructor)
{
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Squirrel>(x, y);
    EXPECT_EQ(SquirrelType,a->get_type());
}

TEST(test2, Bear_constructor)
{
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Bear>(x, y);
    EXPECT_EQ(BearType,a->get_type());
}

TEST(test3, Ork_constructor)
{
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Ork>(x, y);
    EXPECT_EQ(OrkType,a->get_type());
}
