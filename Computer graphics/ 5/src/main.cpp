#include <SFML/Graphics.hpp>
#include <iostream>
#include "Scene.hpp"
#include "camera/Camera.hpp"
#include "shapes/Sphere.hpp"
#include "shapes/Plane.hpp"

constexpr float Scale = 5;

int main(int argc, char* argv[]) {
    std::cout << "Program started" << std::endl;

    // Проверка на количество переданных аргументов
    float mirror = 1.0f;  // Значение по умолчанию

    if (argc > 1) {
        // Попытка преобразования аргумента в число с плавающей точкой
        try {
            mirror = std::stof(argv[1]);
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid mirror value, using default: " << mirror << std::endl;
        }
    }

    const float Radius = Scale / 3;
    Camera cam(400, 400.f / 9 * 16, {0, 0, 0.0001}, {0, -Scale / 2.0f + Radius, Scale});

    sf::Image img, tex_floor, tex_wall, tex_roof;
    img.create(400.f / 9 * 16, 400);
    tex_roof.create(2 * Scale, 2 * Scale, {200, 0, 0});
    
    // Проверка загрузки текстур
    if (!tex_floor.loadFromFile("1.png")) {
        std::cout << "Failed to load floor texture!" << std::endl;
        return -1;
    }
    if (!tex_wall.loadFromFile("2.png")) {
        std::cout << "Failed to load wall texture!" << std::endl;
        return -1;
    }

    Plane roof({0, Scale / 2.0f, Scale}, {0, 0, 1}, {1, 0, 0}, {2.0f * Scale, 2.0f * Scale}, 0, tex_roof);
    Plane floor({0, -Scale / 2, Scale}, {1, 0, 0}, {0, 0, 1}, {2.0f * Scale, 2.0f * Scale * 3}, 0.1, tex_floor);
    Plane wall1({-Scale, 0, 2.0f * Scale}, {0, 0, 1}, {0, 1, 0}, {2.0f * Scale, Scale}, 0.1, tex_wall);
    Plane wall2({-Scale, 0, 0}, {0, 0, 1}, {0, 1, 0}, {2.0f * Scale, Scale}, 0.1, tex_wall);
    Plane wall3({Scale, 0, 2.0f * Scale}, {0, 0, -1}, {0, 1, 0}, {2.0f * Scale, Scale}, 0.1, tex_wall);
    Plane wall4({Scale, 0, 0}, {0, 0, -1}, {0, 1, 0}, {2.0f * Scale, Scale}, 0.1, tex_wall);

    // передаем параметр mirror, который можно настроить через командную строку
    Sphere sphere({0, -Scale / 2.0f + Radius, Scale}, {0.9, 0.9, 0.9}, Radius, mirror, false);
    
    std::vector<Shape*> shapes_ptr;
    shapes_ptr.push_back(&floor);
    shapes_ptr.push_back(&wall1);
    shapes_ptr.push_back(&wall2);
    shapes_ptr.push_back(&wall3);
    shapes_ptr.push_back(&wall4);
    shapes_ptr.push_back(&sphere);

    Scene scene(cam, shapes_ptr);

    // Рендеринг
    scene.render(img);
    
    // Проверка сохранения изображения
    if (img.saveToFile("output.png")) {
        std::cout << "Image saved successfully!" << std::endl;
    } else {
        std::cout << "Failed to save image." << std::endl;
    }

    std::cout << "bob" << std::endl;
    return 0;
}

