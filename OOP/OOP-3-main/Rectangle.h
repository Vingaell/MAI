#pragma once
#include<iostream>
#include"Figure.h"

class Rectangle: public Figure 
{

    friend std::istream& operator>>(std::istream& is, Rectangle& rect);
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rect);

public:

    Rectangle();
    Rectangle(double coord[8], double& a, double& b);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other);
    ~Rectangle();

    virtual operator double() override;
    virtual double get_area() override;
    virtual double get_centre_x() override;
    virtual double get_centre_y() override;
    
    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other);
    bool operator==(const Rectangle& other) const;

protected:

    double a;
    double b;

};

inline std::istream& operator>>(std::istream& is, Rectangle& rect){

    double coord[8];
    std::cout << "Введите координаты вершин прямоугольника в таком порядке через пробелы: A(x) A(y) B(x) B(y) C(x) C(y) D(x) D(y), где вершины A B C D идут по кругу: " << "\n";
    
    for (int q = 0; q < 8; q++){
        is >> coord[q];
        rect.coord[q] = coord[q];
    }
    std::cout << "Введите длины сторон через пробел, сначала меньшую, затем большую: " << "\n";
    is >> rect.a >> rect.b;
    std::cout << "Ввод закончен." << "\n";

    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Rectangle& rect){

    os << "Координаты прямоугольника:" << "\n"; 
    os << "A: x = " << rect.coord[0] << "; y = " << rect.coord[1] << "\n";
    os << "B: x = " << rect.coord[2] << "; y = " << rect.coord[3] << "\n";
    os << "C: x = " << rect.coord[4] << "; y = " << rect.coord[5] << "\n";
    os << "D: x = " << rect.coord[6] << "; y = " << rect.coord[7] << "\n";
    os << "Длины сторон прямоугольника: " << rect.a << "; " << rect.b << "\n";

    return os;
}