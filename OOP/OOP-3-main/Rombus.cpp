#include<iostream>
#include<cmath>
#include"Rombus.h"

Rombus::Rombus(): Figure()
{
    d1 = 0;
    d2 = 0;
}

Rombus::Rombus(double coord[8], double& D1, double& D2): Figure(coord)
{
    this->d1 = D1;
    this->d2 = D2;
}

Rombus::Rombus(const Rombus& other): Figure(other)
{
    this->d1 = other.d1;
    this->d2 = other.d2;
}

Rombus::Rombus(Rombus&& other): Figure(std::move(other))
{
    this->d1 = other.d1;
    other.d1 = 0;
    this->d2 = other.d2;
    other.d2 = 0;
}

Rombus::~Rombus()
{
    d1 = 0;
    d2 = 0;
}

Rombus::operator double()
{   
     area = 0.5 * d1 * d2;
    return area;
} 

double Rombus:: get_area()
{
    area = 0.5 * d1 * d2;
    return area;
}

double Rombus::get_centre_x()
{
    centre_x = (coord[0]+coord[2]+coord[4]+coord[6]) / 4;
    return centre_x;
}

double Rombus::get_centre_y()
{
    centre_y = (coord[1]+coord[3]+coord[5]+coord[7]) / 4;
    return centre_y;
}

Rombus& Rombus::operator=(const Rombus& other)
{
    if (this != &other){
        for (int q = 0; q < 8; q++){
            this->coord[q] = other.coord[q];
        }
        this->d1 = other.d1;
        this->d2 = other.d2;
    }
    return *this;
}

Rombus& Rombus::operator=(Rombus&& other)
{
    if (this != &other){
        for (int q = 0; q < 8; q++){
            this->coord[q] = other.coord[q];
            other.coord[q] = 0;
        }
        this->d1 = other.d1;
        other.d1 = 0;
        this->d2 = other.d2;
        other.d2 = 0;
    }
    return *this;
}

bool Rombus::operator==(const Rombus& other) const
{
    if (this->d1 != other.d1 | this->d2 != other.d2){
        return false;
    }
    return true;
}