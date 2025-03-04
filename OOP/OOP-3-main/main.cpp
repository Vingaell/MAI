#include<iostream>
#include"Figure.h"
#include"Rectangle.h"
#include"Trapezoid.h"
#include "Rombus.h"
#include"Array.h"

int main(){

    Array figures(3);

    double coord_rec[8] = {1.0, 4.0, 3.0, 4.0, 3.0, 1.0, 1.0, 1.0};
    double a_rec = 2.0;
    double b_rec = 3.0;
    Rectangle* rec = new Rectangle(coord_rec, a_rec, b_rec);
    figures.add(rec, 0);

    double coord_trap[8] = {2.0, 3.0, 4.0, 3.0, 5.0, 1.0, 1.0, 1.0};
    double h_trap = 2.0;
    double a_trap = 2.0;
    double b_trap = 4.0;
    Trapezoid* trap = new Trapezoid(coord_trap, h_trap, a_trap, b_trap);
    figures.add(trap, 1);

    double coord_romb[8] = {2.0, 2.0, 2.0, 4.0, 4.0, 4.0, 4.0, 4.0};
    double d1_r = 5;
    double d2_r = 6;
    Rombus* romb = new Rombus(coord_romb, d1_r, d2_r);
    figures.add(romb, 2);

    figures.all();
    std::cout << "\n" << "Общая площадь фигур в массиве: " << figures.all_area() << "\n";

    std::cout << "Введите номер фигуры, которую вы хотите удалить: " << "\n";
    int a;
    std::cin >> a;
    figures.del(a);
    std::cout << "\n";

     // ПРЯМОУГОЛЬНИК
    Rectangle rec1;
    std::cin >> rec1;
    std::cout << rec1;
    double area3 = static_cast<double>(rec1);
    std::cout << "Площадь прямоугольника: " << area3 << "\n";
    std::cout << "Координаты геометрического центра квадрата: " << rec1.get_centre_x() << "; " << rec1.get_centre_y() << "\n";

    Rectangle rec2;
    std::cin >> rec2;
    std::cout << rec2;
    if (rec1 == rec2){
        std::cout << " равны." << "\n";
    } 
    else{
        std::cout << " не равны." << "\n";
    }
    
      // ТРАПЕЦИЯ
     Trapezoid trap1;
     std::cin >> trap1;
     std::cout << trap1;
     double area55 = static_cast<double>(trap1);
     std::cout << "Площадь трапеции: " << area55 << "\n";
     std::cout << "Координаты геометрического центра квадрата: " << trap1.get_centre_x() << "; " << trap1.get_centre_y() << "\n";


     Trapezoid trap2;
     std::cin >> trap2;
     std::cout << trap2;
     double area6 = static_cast<double>(trap2);
     std::cout << "Площадь трапеции: " << area6 << "\n";

     if (trap1 == trap2){
         std::cout << "Трапеции равны." << "\n";
     } 
     else{
         std::cout << "Трапеции не равны." << "\n";
     }

     // Rombus
     Rombus romb1;
     std::cin >> romb1;
     std::cout << romb1;
     double area7 = static_cast<double>(romb1);
     std::cout << "Площадь ромба " << area7 << '\n';
     std::cout << "Координаты геометрического центра rombus: " << romb1.get_centre_x() << "; " << romb1.get_centre_y() << "\n";

     Rombus romb2;
     std::cin >> romb2;
     std::cout << romb2;
     double area8 = static_cast<double>(romb1);

     if (romb1 == romb2){
         std::cout << "ромбы равны." << "\n";
     } 
     else{
         std::cout << "ромбы не равны." << "\n";
     }

     return 0;
 }