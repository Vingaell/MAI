#pragma once
#include<iostream>
#include"Figure.h"

template <typename Rec>
class Rectangle: public Figure<Rec>
{

    template <typename T> friend std::istream& operator>>(std::istream& is, Rectangle<T>& rect);
    template <typename T> friend std::ostream& operator<<(std::ostream& os, const Rectangle<T>& rect);

public:

    Rectangle(): Figure<Rec>(){//так надо писать и всё
        a = 0; b = 0;
    }

    Rectangle(std::pair<Rec, Rec> coord[4], Rec& a, Rec& b): Figure<Rec>(coord){
        this->a = a; this->b = b;
    }

    Rectangle(const Rectangle& other): Figure<Rec>(other){
        this->a = other.a; this->b = other.b;
    }

    Rectangle(Rectangle&& other): Figure<Rec>(std::move(other)){//как это работает?????
        this->a = other.a;
        other.a = 0;
        this->b = other.b;
        other.b = 0;
    }

    ~Rectangle(){
        a = 0; b = 0;
    }


    virtual Rec get_area() override{
        this->area = a * b;
        return (this->area);
    }


    Rectangle<Rec>& operator=(const Rectangle<Rec>& other){
        if (this != &other){
            for (int q = 0; q < 4; q++){
                this->coord[q] = other.coord[q];
            }
            this->a = other.a;
            this->b = other.b;
        }
        return *this;
    }

    Rectangle<Rec>& operator=(Rectangle<Rec>&& other){
        if (this != &other){
            for (int q = 0; q < 4; q++){
                this->coord[q] = other.coord[q];
                other.coord[q] = {0, 0};
            }
            this->a = other.a;
            other.a = 0;
            this->b = other.b;
            other.b = 0;
        }
        return *this;
    }

    bool operator==(const Rectangle<Rec>& other) const{
        if (this->a != other.a || this->b != other.b){
            return false;
        }
        return true;
    }


    Rec a;
    Rec b;

};

template <typename T>
inline std::istream& operator>>(std::istream& is, Rectangle<T>& rect){

    std::cout << "Введите координаты вершин прямоугольника в таком порядке через пробелы: A(x) A(y) B(x) B(y) C(x) C(y) D(x) D(y), где вершины A B C D идут по кругу: " << "\n";
    
    for (int q = 0; q < 4; q++){
        is >> rect.coord[q].first >> rect.coord[q].second;
    }
    std::cout << "Введите длины сторон через пробел, сначала меньшую, затем большую: " << "\n";
    is >> rect.a >> rect.b;
    std::cout << "Ввод закончен." << "\n";

    return is;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Rectangle<T>& rect){

    os << "Координаты прямоугольника:" << "\n"; 
    os << "A: x = " << rect.coord[0].first << "; y = " << rect.coord[0].second << "\n";
    os << "B: x = " << rect.coord[1].first << "; y = " << rect.coord[1].second << "\n";
    os << "C: x = " << rect.coord[2].first << "; y = " << rect.coord[2].second << "\n";
    os << "D: x = " << rect.coord[3].first << "; y = " << rect.coord[3].second << "\n";
    os << "Длины сторон прямоугольника: " << rect.a << "; " << rect.b << "\n";

    return os;
}