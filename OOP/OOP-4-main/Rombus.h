#pragma once
#include <iostream>
#include "Figure.h"

template <typename Romb>
class Rombus: public Figure<Romb>{
    template<typename T> friend std::istream& operator>>(std::istream& is, Rombus<T>& romb);
    template<typename T> friend std::ostream& operator<<(std::istream& os, const Rombus<T>& romb);

public:
    Rombus(): Figure<Romb>(){
        d1 = 0; d2 = 0;
    }

    Rombus(std::pair<Romb, Romb> coord[4], Romb& d1, Romb& d2): Figure<Romb>(coord){
        this->d1 = d1; this->d2 = d2;
    }
    
    Rombus(const Rombus& other): Figure<Romb>(other){
        this->d1 = other.d1; this->d2 = other.d2;
    }

    Rombus(Rombus&& other): Figure<Romb>(std::move(other)){
        this->d1 = other.d1;
        other.d1 = 0;
        this->d2 = other.d2;
        other.d2 = 0;
    }

    ~Rombus(){
        d1 = 0; d2 = 0;
    }

    virtual Romb get_area() override{
        this->area = (d1*d2)/2; return (this->area);
    }

    Rombus<Romb>& operator=(const Rombus<Romb>& other){
        if (this != &other){
            for (int q = 0; q < 4; q++){
                this->coord[q] = other.coord[q];
            }
            this->d1 = other.d1;
            this->d2 = other.d2;
        }
        return *this;
    }
    Rombus<Romb>& operator=(Rombus<Romb>&& other){
        if (this != &other){
            for (int q = 0; q < 4; q++){
                this->coord[q] = other.coord[q];
                other.coord[q] = {0, 0};
            }
            this->d1 = other.d1;
            other.d1 = 0;
            this->d2 = other.d2;
            other.d2 = 0;
        }
        return *this;
    }
    bool operator==(const Rombus<Romb>& other) const{
        if (this->d1 != other.d1 || this->d2 != other.d2){
            return false;
        }
        return true;
    }

    Romb d1;
    Romb d2;
};


template <typename T>
inline std::istream& operator>>(std::istream& is, Rombus<T>& romb){

    std::cout << "Введите координаты вершин ромба в таком порядке через пробелы: d1(x) d1(y) d2(x) d2(y) C(x) C(y) D(x) D(y), где вершины d1 d2 C D идут по кругу: " << "\n";
    
    for (int q = 0; q < 4; q++){
        is >> romb.coord[q].first >> romb.coord[q].second;
    }
    std::cout << "Введите длины диагоналей через пробел, сначала меньшую, затем большую: " << "\n";
    is >> romb.d1 >> romb.d2;
    std::cout << "Ввод закончен." << "\n";

    return is;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Rombus<T>& romb){

    os << "Координаты ромба:" << "\n"; 
    os << "d1: x = " << romb.coord[0].first << "; y = " << romb.coord[0].second << "\n";
    os << "d2: x = " << romb.coord[1].first << "; y = " << romb.coord[1].second << "\n";
    os << "C: x = " << romb.coord[2].first << "; y = " << romb.coord[2].second << "\n";
    os << "D: x = " << romb.coord[3].first << "; y = " << romb.coord[3].second << "\n";
    os << "Длины диагоналей ромба: " << romb.d1 << "; " << romb.d2 << "\n";

    return os;
}