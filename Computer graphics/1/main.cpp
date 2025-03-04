
#include <SFML/Graphics.hpp> 
#include <SFML/OpenGL.hpp>   
#include <cmath>            
#include <vector>            

// Константы
const float PI = 3.14159265359f;            
const float INTERPOLATION_SPEED_DEFAULT = 0.01f; // Начальная скорость интерполяции
const int WINDOW_WIDTH = 800;              
const int WINDOW_HEIGHT = 600;             
const float ROTATION_SPEED_DEFAULT = 0.00f; // Начальная скорость вращения

// Функция для генерации координат шестиугольника
std::vector<sf::Vector2f> generatePolygon(float radius, sf::Vector2f center) {
    // Вектор для хранения вершин многоугольника
    std::vector<sf::Vector2f> vertices;
    for (int i = 0; i < 6; ++i) {
        // Угол для текущей вершины
        float angle = i * 2 * PI / 6;
        // Вычисляем координаты вершины
        vertices.emplace_back(center.x + radius * cos(angle), center.y + radius * sin(angle));
    }
    return vertices; 
}

// Интерполяция между двумя точками
sf::Vector2f interpolate(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
    // Вычисляем координаты промежуточной точки с учетом параметра t (от 0 до 1)
    return sf::Vector2f(start.x + t * (end.x - start.x), start.y + t * (end.y - start.y));
}

// Функция для вращения точек вокруг центра
std::vector<sf::Vector2f> rotatePolygon(const std::vector<sf::Vector2f>& polygon, float angle, const sf::Vector2f& center) {
    std::vector<sf::Vector2f> rotatedPolygon; // Хранит вращенные вершины
    for (const auto& point : polygon) {
        // Перемещаем вершину относительно центра
        float x = point.x - center.x;
        float y = point.y - center.y;
        // Вычисляем новые координаты после вращения
        float newX = x * cos(angle) - y * sin(angle) + center.x;
        float newY = x * sin(angle) + y * cos(angle) + center.y;
        rotatedPolygon.emplace_back(newX, newY); 
    }
    return rotatedPolygon; 
}

int main() {
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2D Transformations");
    window.setFramerateLimit(60); // Ограничиваем FPS для стабильной анимации

    // Исходные данные для шестиугольника
    float radius = 100.0f; // Радиус шестиугольника
    sf::Vector2f center(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2); // Центр шестиугольника (центр окна)
    std::vector<sf::Vector2f> polygon = generatePolygon(radius, center); // Генерируем шестиугольник

    // Данные для анимации
    sf::Vector2f moveTarget(200.0f, 0.0f); // Вектор смещения для движения
    float interpolationProgress = 0.0f;   // Текущий прогресс интерполяции
    bool movingForward = true;            // Направление движения

    bool deforming = false;               // Флаг для включения/выключения деформации
    float shapeDeformation = 0.0f;        // Степень деформации
    bool deformingForward = true;         // Направление деформации

    float rotationAngle = 0.0f;           // Угол вращения
    bool rotating = true;                 // Флаг для включения/выключения вращения
    float rotationSpeed = ROTATION_SPEED_DEFAULT; // Скорость вращения
    float interpolationSpeed = INTERPOLATION_SPEED_DEFAULT; // Скорость интерполяции

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { 
                window.close();
            }
            // Переключение деформации пробелом
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                deforming = !deforming;
            }
            // Включение/выключение вращения клавишей R
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                rotating = !rotating;
            }
            // Изменение скорости вращения клавишами влево/вправо
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    rotationSpeed -= 0.01f;
                }
                if (event.key.code == sf::Keyboard::Right) {
                    rotationSpeed += 0.01f;
                }
            }
            // Изменение скорости интерполяции клавишами вверх/вниз
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    interpolationSpeed += 0.001f;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    interpolationSpeed -= 0.001f;
                }
            }
        }

        // Логика движения
        if (movingForward) {
            interpolationProgress += interpolationSpeed;
            if (interpolationProgress >= 1.0f) {
                interpolationProgress = 1.0f; // Ограничение
                movingForward = false;       // Смена направления
            }
        } else {
            interpolationProgress -= interpolationSpeed;
            if (interpolationProgress <= 0.0f) {
                interpolationProgress = 0.0f; // Ограничение
                movingForward = true;        // Смена направления
            }
        }
        // Вычисление текущего положения центра
        sf::Vector2f interpolatedCenter = interpolate(center, center + moveTarget, interpolationProgress);

        // Логика деформации
        if (deforming) {
            if (deformingForward) {
                shapeDeformation += 0.01f;
                if (shapeDeformation >= 0.2f) { // Ограничение деформации
                    deformingForward = false;  // Смена направления
                }
            } else {
                shapeDeformation -= 0.01f;
                if (shapeDeformation <= 0.0f) { // Ограничение
                    deformingForward = true;   // Смена направления
                }
            }
        }

        // Применение деформации
        std::vector<sf::Vector2f> animatedPolygon;
        for (size_t i = 0; i < polygon.size(); ++i) {
            float angleOffset = shapeDeformation * sin(2 * PI * i / polygon.size());
            animatedPolygon.emplace_back(interpolatedCenter.x + (polygon[i].x - center.x) * (1 + angleOffset),
                                         interpolatedCenter.y + (polygon[i].y - center.y) * (1 + angleOffset));
        }

        // Вращение 
        if (rotating) {
            animatedPolygon = rotatePolygon(animatedPolygon, rotationAngle, interpolatedCenter);
            rotationAngle += rotationSpeed;
        }

        // Отрисовка
        window.clear(sf::Color::Black); 
        sf::ConvexShape shape;
        shape.setPointCount(animatedPolygon.size());
        for (size_t i = 0; i < animatedPolygon.size(); ++i) {
            shape.setPoint(i, animatedPolygon[i]);
        }
        shape.setFillColor(sf::Color::Green); 
        window.draw(shape); 
        window.display(); 
    }

    return 0; 
}

