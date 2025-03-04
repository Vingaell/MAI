#pragma once
#include<iostream>
#include"Figure.h"

class Trapezoid: public Figure 
{

    friend std::istream& operator>>(std::istream& is, Trapezoid& trap);
    friend std::ostream& operator<<(std::ostream& os, const Trapezoid& trap);

public:

    Trapezoid();
    Trapezoid(double coord[8],double& high, double& AB, double& CD);
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other);
    ~Trapezoid();

    virtual operator double() override;
    virtual double get_area() override;
    virtual double get_centre_x() override;
    virtual double get_centre_y() override;

    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other);
    bool operator==(const Trapezoid& other) const;

protected:

    double high;
    double AB;
    double CD;

};

inline std::istream& operator>>(std::istream& is, Trapezoid& trap){

    double coord[8];
    std::cout << "Введите координаты вершин трапеции в таком порядке через пробелы: A(x) A(y) B(x) B(y) C(x) C(y) D(x) D(y), где вершины A B C D идут по кругу: " << "\n";
    
    for (int q = 0; q < 8; q++){
        is >> coord[q];
        trap.coord[q] = coord[q];
    }
    std::cout << "Введите высоту трапеции: " << "\n";
    is >> trap.high;
    std::cout << "Введите длины оснований трапеции через пробел, сначала меньшую, затем большую: " << "\n";
    is >> trap.AB >> trap.CD;
    std::cout << "Ввод закончен." << "\n";

    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Trapezoid& trap){

    os << "Координаты трапеции:" << "\n"; 
    os << "A: x = " << trap.coord[0] << "; y = " << trap.coord[1] << "\n";
    os << "B: x = " << trap.coord[2] << "; y = " << trap.coord[3] << "\n";
    os << "C: x = " << trap.coord[4] << "; y = " << trap.coord[5] << "\n";
    os << "D: x = " << trap.coord[6] << "; y = " << trap.coord[7] << "\n";
    os << "Высота трапеции: " << trap.high << "\n";
    os << "Длины оснований трапеции: " << trap.AB << "; " << trap.CD << "\n";

    return os;
}