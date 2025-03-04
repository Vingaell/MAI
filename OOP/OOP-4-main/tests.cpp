#include<gtest/gtest.h>
#include"Figure.h"
#include"Rombus.h"
#include"Rectangle.h"
#include"Trapezoid.h"


TEST(test_1, AllMetods)
{   
// трапеция
    std::pair<double, double> coord_trap1[4] = {{2.0, 3.0}, {4.0, 3.0}, {5.0, 1.0}, {1.0, 1.0}};
    double high_trap1 = 2.0;
    double AB_trap1 = 2.0;
    double CD_trap1 = 4.0;
    Trapezoid<double> trap1(coord_trap1, AB_trap1, CD_trap1, high_trap1);

    std::pair<double, double> coord_trap2[4] = {{3.0, -1.0}, {4.0, -1.0}, {6.0, -3.0}, {1.0, -3.0}};
    double high_trap2 = 2.0;
    double AB_trap2 = 1.0;
    double CD_trap2 = 5.0;
    Trapezoid<double> trap2(coord_trap2, AB_trap2, CD_trap2, high_trap2);

    double get_area1 = trap1.get_area();
    double expect_get_area1 = 6;
    double get_area2 = trap2.get_area();
    double expect_get_area2 = 6;

    std::pair<double, double> centre_1 = trap1.get_centre();
    std::pair<double, double> expect_centre1 = {3.0, 2.0};
    std::pair<double, double> centre_2 = trap2.get_centre();
    std::pair<double, double> expect_centre2 = {3.5, -2.0};

// проверка

    ASSERT_EQ(get_area1, expect_get_area1);
    ASSERT_EQ(get_area2, expect_get_area2);

    ASSERT_EQ(centre_1, expect_centre1);
    ASSERT_EQ(centre_2, expect_centre2);

    EXPECT_FALSE(trap1 == trap2);

}

TEST(test_2, AllMetods)
{   
// romb
    std::pair<double, double> coord_romb1[4] = {{0.0, 0.0}, {2.0, 3.0}, {4.0, 0.0}, {2.0, -3.0}};
    double a_sq1 = 4.0; 
    double b_sq1 = 6.0;
    Rombus<double> romb1(coord_romb1, a_sq1, b_sq1);

    std::pair<double, double> coord_romb2[4] = {{-3.0, -3.0}, {-1.0, 0.0}, {1.0, -3.0}, {-1.0, -6.0}};
    double a_sq2 = 4.0; 
    double b_sq2 = 6.0;
    Rombus<double> romb2(coord_romb2, a_sq2, b_sq2);

    double get_area1 = romb1.get_area();
    double expect_get_area1 = 12;
    double get_area2 = romb2.get_area();
    double expect_get_area2 = 12;

    std::pair<double, double> centre_1 = romb1.get_centre();
    std::pair<double, double> expect_centre_1 = {2, 0};
    std::pair<double, double> centre_2 = romb2.get_centre();
    std::pair<double, double> expect_centre_2 = {-1, -3};

// проверка

    ASSERT_EQ(get_area1, expect_get_area1);
    ASSERT_EQ(get_area2, expect_get_area2);

    ASSERT_EQ(centre_1, expect_centre_1);
    ASSERT_EQ(centre_2, expect_centre_2);

    EXPECT_TRUE(romb1 == romb2);

}


 TEST(test_2, COPY)
 {   
//romb
     std::pair<double, double> coord_romb1[4] = {{2.0, 4.0}, {4.0, 4.0}, {4.0, 2.0}, {2.0, 2.0}};
     double a_sq1 = 2.0; double b_sq1 = 2.0;
     Rombus<double> romb1(coord_romb1, a_sq1, b_sq1);

     std::pair<double, double> coord_romb2[4] = {{-2.0, 2.0}, {0.0, 2.0}, {0.0, 0.0}, {-2.0, 0.0}};
     double a_sq2 = 2.0;double b_sq2 = 2.0;
     Rombus<double> romb2(coord_romb2, a_sq2, b_sq2);

     romb2 = romb1;

//  прямоугольник
     std::pair<double, double> coord_rec1[4] = {{1.0, 4.0}, {3.0, 4.0}, {3.0, 1.0}, {1.0, 1.0}};
     double a_rec1 = 2.0;
     double b_rec1 = 3.0;
     Rectangle<double> rec1(coord_rec1, a_rec1, b_rec1);

     std::pair<double, double> coord_rec2[4] = {{1.0, 1.0}, {2.0, 1.0}, {2.0, -1.0}, {1.0, -1.0}};
     double a_rec2 = 1.0;
     double b_rec2 = 2.0;
     Rectangle<double> rec2(coord_rec2, a_rec2, b_rec2);

     rec2 = rec1;

//  трапеция
     std::pair<double, double> coord_trap1[4] = {{2.0, 3.0}, {4.0, 3.0}, {5.0, 1.0}, {1.0, 1.0}};
     double high_trap1 = 2.0;
     double AB_trap1 = 2.0;
     double CD_trap1 = 4.0;
     Trapezoid<double> trap1(coord_trap1, AB_trap1, CD_trap1, high_trap1);

     std::pair<double, double> coord_trap2[4] = {{3.0, -1.0}, {4.0, -1.0}, {6.0, -3.0}, {1.0, -3.0}};
     double high_trap2 = 2.0;
     double AB_trap2 = 1.0;
     double CD_trap2 = 5.0;
     Trapezoid<double> trap2(coord_trap2, AB_trap2, CD_trap2, high_trap2);

     trap2 = trap1;

//  проверка
     EXPECT_EQ(romb1, Rombus(coord_romb1, a_sq1, b_sq1));
     EXPECT_EQ(rec1, Rectangle(coord_rec1, a_rec1, b_rec1));
     EXPECT_EQ(trap1, Trapezoid(coord_trap1, AB_trap1, CD_trap1, high_trap1));

     EXPECT_EQ(romb2, Rombus(coord_romb1, a_sq1, b_sq1));
     EXPECT_EQ(rec2, Rectangle(coord_rec1, a_rec1, b_rec1));
     EXPECT_EQ(trap2, Trapezoid(coord_trap1, AB_trap1, CD_trap1, high_trap2));
 }

 TEST(test_5, Move)
 {   
//  romb
      std::pair<double, double> coord_romb1[4] = {{2.0, 4.0}, {4.0, 4.0}, {4.0, 2.0}, {2.0, 2.0}};
     double a_sq1 = 2.0; double b_sq1 = 2.0;
     Rombus<double> romb1(coord_romb1, a_sq1, b_sq1);

     std::pair<double, double> coord_romb2[4] = {{-2.0, 2.0}, {0.0, 2.0}, {0.0, 0.0}, {-2.0, 0.0}};
     double a_sq2 = 2.0; double b_sq2 = 2.0; 
     Rombus<double> romb2(coord_romb2, a_sq2, b_sq2);

     romb2 = std::move (romb1);

//  прямоугольник
     std::pair<double, double> coord_rec1[4] = {{1.0, 4.0}, {3.0, 4.0}, {3.0, 1.0}, {1.0, 1.0}};
     double a_rec1 = 2.0;
     double b_rec1 = 3.0;
     Rectangle<double> rec1(coord_rec1, a_rec1, b_rec1);

     std::pair<double, double> coord_rec2[4] = {{1.0, 1.0}, {2.0, 1.0}, {2.0, -1.0}, {1.0, -1.0}};
     double a_rec2 = 1.0;
     double b_rec2 = 2.0;
     Rectangle<double> rec2(coord_rec2, a_rec2, b_rec2);


     rec2 = std::move (rec1);

//  трапеция
     std::pair<double, double> coord_trap1[4] = {{2.0, 3.0}, {4.0, 3.0}, {5.0, 1.0}, {1.0, 1.0}};
     double high_trap1 = 2.0;
     double AB_trap1 = 2.0;
     double CD_trap1 = 4.0;
     Trapezoid<double> trap1(coord_trap1, AB_trap1, CD_trap1, high_trap1);

     std::pair<double, double> coord_trap2[4] = {{3.0, -1.0}, {4.0, -1.0}, {6.0, -3.0}, {1.0, -3.0}};
     double high_trap2 = 2.0;
     double AB_trap2 = 1.0;
     double CD_trap2 = 5.0;
     Trapezoid<double> trap2(coord_trap2, AB_trap2, CD_trap2, high_trap2);

     trap2 = std::move (trap1);


     std::pair<double, double> coord[4] = {{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}};
     double a = 0.0;

// проверка
     EXPECT_EQ(romb1, Rombus(coord, a, a));
     EXPECT_EQ(rec1, Rectangle(coord, a, a));
     EXPECT_EQ(trap1, Trapezoid(coord, a, a, a));

     EXPECT_EQ(romb2, Rombus(coord_romb1, a_sq1, b_sq1));
     EXPECT_EQ(rec2, Rectangle(coord_rec1, a_rec1, b_rec1));
     EXPECT_EQ(trap2, Trapezoid(coord_trap1, AB_trap1, CD_trap1, high_trap1));
 }


  int main(int argc, char **argv) {
      testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
  }