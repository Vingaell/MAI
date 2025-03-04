#include<iostream>
#include<cmath>
#include"Figure.h"

// инициализация массива coord при создании объектва класса Figure
Figure::Figure()
{
    for (int q = 0; q < 8; q++){
        coord[q] = 0;
    }
}

// Принимает на вход массив координат и копирует его значения в массив coord 
Figure::Figure(double coord[8])
{
    for (int q = 0; q < 8; q++){
        this->coord[q] = coord[q];
    }
}

// Принимает на вход другой объект класса Figure и копирует его массив coord в массив coord текущего объектва
Figure::Figure(const Figure& other)
{
    for (int q = 0; q < 8; q++){
        this->coord[q] = other.coord[q];
    }
}

// Принимает на вход другой объект класса Figure, перемещает его массив coord в массив coord текущего объекта и после этого обнуляет массив coord у другого объекта.
Figure::Figure(Figure&& other)
{
    for (int q = 0; q < 8; q++){
        this->coord[q] = other.coord[q];
        other.coord[q] = 0;
    }
}

// Обнуляет все значения массива coord при уничтожении объекта класса Figure.
Figure::~Figure()
{
    for (int q = 0; q < 8; q++){
        coord[q] = 0;
    }
}