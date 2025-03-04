#include<iostream>
#include<cmath>
#include"Rectangle.h"

Rectangle::Rectangle(): Figure()
{
    a = 0;
    b = 0;
}

Rectangle::Rectangle(double coord[8], double& a, double& b): Figure(coord)
{
    this->a = a;
    this->b = b;
}

Rectangle::Rectangle(const Rectangle& other): Figure(other)
{
    this->a = other.a;
    this->b = other.b;
}

Rectangle::Rectangle(Rectangle&& other): Figure(std::move(other))
{
    this->a = other.a;
    other.a = 0;
    this->b = other.b;
    other.b = 0;
}

Rectangle::~Rectangle()
{
    a = 0;
    b = 0;
}

Rectangle::operator double()
{   
    area = a * b;
    return area;
} 

double Rectangle:: get_area()
{
    area = a * b;
    return area;
}

double Rectangle::get_centre_x()
{
    centre_x = (coord[0]+coord[2]+coord[4]+coord[6]) / 4;
    return centre_x;
}

double Rectangle::get_centre_y()
{
    centre_y = (coord[1]+coord[3]+coord[5]+coord[7]) / 4;
    return centre_y;
}

Rectangle& Rectangle::operator=(const Rectangle& other)
{
    if (this != &other){
        // delete[] coord (указатель на динамический массив с координатами)
        // this->size = other.size; (размер массива)
        // coord = new double[size];
        for (int q = 0; q < 8; q++){
            this->coord[q] = other.coord[q];
        }
        this->a = other.a;
        this->b = other.b;
    }
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other)
{
    if (this != &other){
        // delete[] coord (указатель на динамический массив с координатами)
        // this->size = other.size; (размер массива)
        // coord = new double[size];
        for (int q = 0; q < 8; q++){
            this->coord[q] = other.coord[q];
            other.coord[q] = 0;
        }
        this->a = other.a;
        other.a = 0;
        this->b = other.b;
        other.b = 0;
    }
    return *this;
}

bool Rectangle::operator==(const Rectangle& other) const
{
    if (this->a != other.a || this->b != other.b){
        return false;
    }
    return true;
}