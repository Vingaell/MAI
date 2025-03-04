#include<iostream>
#include<cmath>
#include"Array.h"

Array::Array(int size)
{   
    lot = 0;
    this->size = size;
    fig = new Figure*[size];
    for (int q = 0; q < size; q++) {
        fig[q] = nullptr;
    }
}

Array::~Array() 
{
    for (int q = 0; q < size; ++q) {
            if (fig[q] != nullptr) {
                delete fig[q];
            }
        }
        delete[] fig;
}

void Array::add(Figure* figure, int index) 
{
    if (index >= 0 && index < size) {
        if (fig[index] == nullptr){
            ++lot;
            fig[index] = figure;
            std::cout << "Фигура с номером " << index  << " добавлена в массив." << "\n";
            std::cout << "Количество фигур в массиве: " << lot << "\n";
        }
        else{
            std::cout << "Фигура с таким номером уже существует." << "\n";
        }
    }
}

void Array::del(int index) 
{   
    if (index >= 0 && index < size && index < lot) {
        if (fig[index] != nullptr){
            --lot;
            delete fig[index];
            fig[index] = nullptr;
            std::cout << "Фигура с номером " << index << " удалена из массива." << "\n";
            std::cout << "Количество фигур в массиве: " << lot << "\n";
        }
    }
    else{
            std::cout << "Фигуры с таким номером не существует." << "\n";
    }
    
}

void Array::all() const 
{
    int all;
    for (int q = 0; q < size; ++q) {
        if (fig[q] != nullptr) {
            all += fig[q]->get_area();
            std::cout << "Фигура номер: " << q << "\n";
            std::cout << *fig[q];
            std::cout << "Площадь фигуры: " << fig[q]->get_area() << "\n";
            std::cout << "Координаты гометрического центра фигуры: " << fig[q]->get_centre_x() << "; " << fig[q]->get_centre_y() << "\n"; 
            std::cout << "\n";
        }
    }
    std::cout << "Количество фигур в массиве: " << lot << "\n";
}

double Array::all_area() const
{
        double areas = 0;
        for (int q = 0; q < size; q++) {
            areas += fig[q]->get_area();
        }
        return areas;
}