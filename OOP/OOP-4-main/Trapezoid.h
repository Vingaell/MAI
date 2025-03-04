#pragma once
#include<iostream>
#include"Figure.h"

template <typename Trap>
class Trapezoid: public Figure<Trap>
{

    template <typename T>
    friend std::istream& operator>>(std::istream& is, Trapezoid<T>& trap);
    template <typename T>
    friend std::ostream& operator<<(std::ostream& os, const Trapezoid<T>& trap);

public:

    Trapezoid(): Figure<Trap>(){
        AB = 0;
        CD = 0;
        high = 0;
    }

    Trapezoid(std::pair<Trap, Trap> coord[4], Trap& AB, Trap& CD, Trap& high): Figure<Trap>(coord){
        this->AB = AB;
        this->CD = CD;
        this->high = high;
    }

    Trapezoid(const Trapezoid& other): Figure<Trap>(other){
        this->AB = other.AB;
        this->CD = other.CD;
        this->high = other.high;
    }

    Trapezoid(Trapezoid&& other): Figure<Trap>(std::move(other)){
        this->AB = other.AB;
        other.AB = 0;
        this->CD = other.CD;
        other.CD = 0;
        this->high = other.high;
        other.high = 0;
    }

    ~Trapezoid(){
        AB = 0;
        CD = 0;
        high = 0;
    }


    virtual Trap get_area() override{
        this->area = ((AB + CD) * high) / 2;
        return (this->area);
    }


    Trapezoid<Trap>& operator=(const Trapezoid<Trap>& other){
        if (this != &other){
            for (int q = 0; q < 4; q++){
                this->coord[q] = other.coord[q];
            }
            this->AB = other.AB;
            this->CD = other.CD;
            this->high = other.high;
        }
        return *this;
    }

    Trapezoid<Trap>& operator=(Trapezoid<Trap>&& other){
        if (this != &other){
            for (int q = 0; q < 4; q++){
                this->coord[q] = other.coord[q];
                other.coord[q] = {0, 0};
            }
            this->AB = other.AB;
            other.AB = 0;
            this->CD = other.CD;
            other.CD = 0;
            this->high = other.high;
            other.high = 0;
        }
        return *this;
    }

    bool operator==(const Trapezoid<Trap>& other) const{
        if (this->AB != other.AB || this->CD != other.CD || this->high != other.high){
            return false;
        }
        return true;
    }


    Trap AB;
    Trap CD;
    Trap high;

};

template <typename T>
inline std::istream& operator>>(std::istream& is, Trapezoid<T>& trap){

    std::cout << "Введите координаты вершин трапеции в таком порядке через пробелы: A(x) A(y) B(x) B(y) C(x) C(y) D(x) D(y), где вершины A B C D идут по кругу: " << "\n";
    
    for (int q = 0; q < 4; q++){
        is >> trap.coord[q].first >> trap.coord[q].second;
    }
    std::cout << "Введите высоту трапеции: " << "\n";
    is >> trap.high;
    std::cout << "Введите длины оснований трапеции через пробел, сначала меньшую, затем большую: " << "\n";
    is >> trap.AB >> trap.CD;
    std::cout << "Ввод закончен." << "\n";

    return is;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Trapezoid<T>& trap){

    os << "Координаты трапеции:" << "\n"; 
    os << "A: x = " << trap.coord[0].first << "; y = " << trap.coord[0].second << "\n";
    os << "B: x = " << trap.coord[1].first << "; y = " << trap.coord[1].second << "\n";
    os << "C: x = " << trap.coord[2].first << "; y = " << trap.coord[2].second << "\n";
    os << "D: x = " << trap.coord[3].first << "; y = " << trap.coord[3].second << "\n";
    os << "Высота трапеции: " << trap.high << "\n";
    os << "Длины оснований трапеции: " << trap.AB << "; " << trap.CD << "\n";

    return os;
}