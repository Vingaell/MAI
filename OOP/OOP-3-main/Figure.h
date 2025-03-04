#pragma once
#include<iostream>

class Figure 
{

// Прототипы операторов ввода и вывода объявлены как friend, чтобы они имели доступ к закрытым членам класса
    friend std::istream& operator>>(std::istream& is, Figure& figure);
    friend std::ostream& operator<<(std::ostream& os, const Figure& figure);

public:

// Конструкторы и деструктор
    Figure();
    Figure(double coord[8]);
    Figure(const Figure& other);
    Figure(Figure&& other);
    virtual ~Figure();

// Виртуальные методы для получения площади, координат центра фигуры и оператор приведения к типу double
    virtual operator double() = 0; 
    virtual double get_area() = 0;
    virtual double get_centre_x() = 0;
    virtual double get_centre_y() = 0;

protected:

 // Массив координат, площадь и координаты центра фигуры
    double coord[8];
    double area;
    double centre_x;
    double centre_y;

};

inline std::istream& operator>>(std::istream& is, Figure& figure){

// Оператор ввода координат фигуры с клавиатуры
    double coord[8];
    std::cout << "Введите координаты вершин фигуры в таком порядке через пробелы: A(x) A(y) B(x) B(y) C(x) C(y) D(x) D(y), где вершины A B C D идут по кругу: " << "\n";
    
    for (int q = 0; q < 8; q++){
        is >> coord[q];
        figure.coord[q] = coord[q];
    }
    std::cout << "Ввод закончен." << "\n";
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Figure& figure){

// Оператор вывода координат фигуры
    os << "Координаты фигуры:" << "\n"; 
    os << "A: x = " << figure.coord[0] << "; y = " << figure.coord[1] << "\n";
    os << "B: x = " << figure.coord[2] << "; y = " << figure.coord[3] << "\n";
    os << "C: x = " << figure.coord[4] << "; y = " << figure.coord[5] << "\n";
    os << "D: x = " << figure.coord[6] << "; y = " << figure.coord[7] << "\n";

    return os;
}