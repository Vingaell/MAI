#pragma once
#include<iostream>
#include<utility>

template <typename Fig>
class Figure 
{
    template <typename T>
    friend std::istream& operator>>(std::istream& is, Figure<T>& figure);
    template <typename T>
    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& figure);

public:

    Figure(){
    for (int q = 0; q < 4; q++){
        coord[q].first = 0;
        coord[q].second = 0;
        }
    }

    Figure(std::pair<Fig, Fig> coord[4]){
     for (int q = 0; q < 4; q++){
        this->coord[q].first = coord[q].first;
        this->coord[q].second = coord[q].second;
        }
    } 

    Figure(const Figure<Fig>& other){
    for (int q = 0; q < 4; q++){
        this->coord[q].first = other.coord[q].first;
        this->coord[q].second = other.coord[q].second;
        }
    }

    Figure(Figure<Fig>&& other){
    for (int q = 0; q < 4; q++){
        this->coord[q].first = other.coord[q].first;
        other.coord[q].first = 0;
        this->coord[q].second = other.coord[q].second;
        other.coord[q].second = 0;
        }
    }

    ~Figure(){
    for (int q = 0; q < 4; q++){
        coord[q].first = 0;
        coord[q].second = 0;
        }
    }

    virtual Fig get_area() = 0;
    std::pair<Fig, Fig> get_centre(){
        this->centre.first = (this->coord[0].first + this->coord[1].first + this->coord[2].first + this->coord[3].first) / 4;
        this->centre.second = (this->coord[0].second + this->coord[1].second + this->coord[2].second + this->coord[3].second) / 4;
        return this->centre;
    }


    std::pair<Fig, Fig> coord[4];
    Fig area;
    std::pair<Fig, Fig> centre;

};

template <typename T>
inline std::istream& operator>>(std::istream& is, Figure<T>& figure){

    std::cout << "Введите координаты вершин фигуры в таком порядке через пробелы: A(x) A(y) B(x) B(y) C(x) C(y) D(x) D(y), где вершины A B C D идут по кругу: " << "\n";
    
    for (int q = 0; q < 4; q++){
        is >> figure.coord[q].first >> figure.coord[q].second;
    }
    std::cout << "Ввод закончен." << "\n";
    return is;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Figure<T>& figure){

    os << "Координаты фигуры:" << "\n"; 
    os << "A: x = " << figure.coord[0].first << "; y = " << figure.coord[0].second << "\n";
    os << "B: x = " << figure.coord[1].first << "; y = " << figure.coord[1].second << "\n";
    os << "C: x = " << figure.coord[2].first << "; y = " << figure.coord[2].second << "\n";
    os << "D: x = " << figure.coord[3].first << "; y = " << figure.coord[3].second << "\n";

    return os;
}