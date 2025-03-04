#pragma once
#include<iostream>
#include"Figure.h"

class Rombus: public Figure 
{

    friend std::istream& operator>>(std::istream& is, Rombus& romb);
    friend std::ostream& operator<<(std::ostream& os, const Rombus& romb);

public:

    Rombus();
    Rombus(double coord[8], double& d1, double& d2);
    Rombus(const Rombus& other);
    Rombus(Rombus&& other);
    ~Rombus();

    virtual operator double() override;
    virtual double get_area() override;
    virtual double get_centre_x() override;
    virtual double get_centre_y() override;
    
    Rombus& operator=(const Rombus& other);
    Rombus& operator=(Rombus&& other);
    bool operator==(const Rombus& other) const;

protected:
    double d1;
    double d2;
};

inline std::istream& operator>>(std::istream& is, Rombus& romb){

    double coord[8];
    std::cout << "Введите координаты вершин ромба в таком порядке через пробелы: A(x) A(y) B(x) B(y) C(x) C(y) D(x) D(y), где вершины A B C D идут по кругу: " << "\n";
    
    for (int q = 0; q < 8; q++){
        is >> coord[q];
        romb.coord[q] = coord[q];
    }
    std::cout << "Введите длину 1 диагонали: " << "\n";
    is >> romb.d1;
    std::cout << "Введите длину 2 диагонали: " << "\n";
    is >> romb.d2;
    std::cout << "Ввод закончен." << "\n";

    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Rombus& romb){

    os << "Координаты ромба:" << "\n"; 
    os << "A: x = " << romb.coord[0] << "; y = " << romb.coord[1] << "\n";
    os << "B: x = " << romb.coord[2] << "; y = " << romb.coord[3] << "\n";
    os << "C: x = " << romb.coord[4] << "; y = " << romb.coord[5] << "\n";
    os << "D: x = " << romb.coord[6] << "; y = " << romb.coord[7] << "\n";
    os << "Длины диагоналей ромба: " << romb.d1 << " " << romb.d2 << "\n";

    return os;
}