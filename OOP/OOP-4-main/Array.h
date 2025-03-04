#pragma once
#include<iostream>
#include<utility>
#include <memory>
#include"Figure.h"

template <typename Ary>
class Array {
public:
    Array(int size){
        lot = 0;
        this->size = size;
        array = std::shared_ptr<Ary[]>(new Ary[size]);
        for (int q = 0; q < size; q++) {
            array[q] = nullptr;
        }
    }

    ~Array(){
        size = 0;
        areas = 0;
        lot = 0;
    }

    void add(Ary figure, int index){
        if (index >= 0 && index < size) {
            if (array[index] == nullptr){
                ++lot;
                array[index] = figure;
                std::cout << "Фигура с номером " << index  << " добавлена в массив." << "\n";
                std::cout << "Количество фигур в массиве: " << lot << "\n";
            }
            else{
                std::cout << "Фигура с таким номером уже существует." << "\n";
            }
        }
    }

    void del(int index){
        if (index >= 0 && index < size && index < lot){
            if (array[index] != nullptr){
                --lot;
                array[index].reset();
                array[index] = nullptr;
                std::cout << "Фигура с номером " << index << " удалена из массива." << "\n";
                std::cout << "Осталось фигур в массиве: " << lot << "\n";
            }
        }
        else{
            std::cout << "Фигуры с таким номером не существует." << "\n";
        }
    }

    void all() const{
        int all = 0;
        for (int q = 0; q < size; ++q) {
            if (array[q] != nullptr) {
                all += array[q]->get_area();
                std::cout << "Фигура номер: " << q << "\n";
                std::cout << *array[q];
                std::cout << "Площадь фигуры: " << array[q]->get_area() << "\n";
                std::pair<double, double> centre = array[q]->get_centre();
                std::cout << "Координаты гометрического центра фигуры: " << centre.first << "; " << centre.second << "\n";
                std::cout << "\n";
            }
        }
        std::cout << "Количество фигур в массиве: " << lot << "\n";
    }

        
    double all_area() const{
        double areas = 0;
        for (int q = 0; q < size; q++){
            if (array[q] != nullptr){
                areas += array[q]->get_area();
            }
        }
        return areas;
    }

private:
    int size;
    int areas;
    int lot;
    std::shared_ptr<Ary[]> array;
};