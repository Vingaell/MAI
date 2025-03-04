#include<iostream>
#include<cmath>
#include"Trapezoid.h"

Trapezoid::Trapezoid(): Figure()
{
    high = 0;
    AB = 0;
    CD = 0;
}

Trapezoid::Trapezoid(double coord[8],double& high, double& AB, double& CD): Figure(coord)
{
    this->high = high;
    this->AB = AB;
    this->CD = CD;
}

Trapezoid::Trapezoid(const Trapezoid& other): Figure(other)
{
    this->high = other.high;
    this->AB = other.AB;
    this->CD = other.CD;
}

Trapezoid::Trapezoid(Trapezoid&& other): Figure(std::move(other))
{
    this->high = other.high;
    other.high = 0;
    this->AB = other.AB;
    other.AB = 0;
    this->high = other.high;
    other.high = 0;

}

Trapezoid::~Trapezoid()
{
    AB = 0;
    CD = 0;
    high = 0;
}
/////////////////////////////////////////////////
Trapezoid::operator double()
{   
    area = (AB + CD) * high / 2;
    return area;
} 

double Trapezoid:: get_area()
{
    area = (AB + CD) * high / 2;
    return area;
}

double Trapezoid::get_centre_x()
{
    centre_x = (coord[0]+coord[2]+coord[4]+coord[6]) / 4;
    return centre_x;
}

double Trapezoid::get_centre_y()
{
    centre_y = (coord[1]+coord[3]+coord[5]+coord[7]) / 4;
    return centre_y;
}

Trapezoid& Trapezoid::operator=(const Trapezoid& other)
{
    if (this != &other){
        // delete[] coord (указатель на динамический массив с координатами)
        // this->size = other.size; (размер массива)
        // coord = new double[size]; 
        for (int q = 0; q < 8; q++){
            this->coord[q] = other.coord[q];
        }
        this->AB = other.AB;
        this->CD = other.CD;
        this->high = other.high;
    }
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other)
{
    if (this != &other){
        // delete[] coord (указатель на динамический массив с координатами)
        // this->size = other.size; (размер массива)
        // coord = new double[size]; 
        for (int q = 0; q < 8; q++){
            this->coord[q] = other.coord[q];
            other.coord[q] = 0;
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

bool Trapezoid::operator==(const Trapezoid& other) const
{
    if (this->AB != other.AB || this->CD != other.CD || this->high != other.high){
        return false;
    }
    return true;
}