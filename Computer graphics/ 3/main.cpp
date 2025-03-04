#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <vector>
#include <cmath>

// Класс для управления камерой
class Camera {
public:
    float x, y, z; // Позиция камеры
    float pitch, yaw; // Углы поворота камеры

    Camera() : x(0), y(0), z(5), pitch(0), yaw(0) {}

    void apply() {
        glRotatef(-pitch, 1.0f, 0.0f, 0.0f);
        glRotatef(-yaw, 0.0f, 1.0f, 0.0f);
        glTranslatef(-x, -y, -z);
    }

    void move(float dx, float dy, float dz) {
        x += dz * sin(yaw * M_PI / 180) + dx * cos(yaw * M_PI / 180);
        z += dz * cos(yaw * M_PI / 180) - dx * sin(yaw * M_PI / 180);
        y += dy;
    }

    void rotate(float dpitch, float dyaw) {
        pitch += dpitch;
        yaw += dyaw;
    }
};

// Класс для управления объектами
class Transformable {
public:
    float x, y, z;      // Позиция
    float scale;        // Масштаб
    float pitch, yaw, roll; // Углы поворота

    Transformable() : x(0), y(0), z(0), scale(1), pitch(0), yaw(0), roll(0) {}

    void apply() {
        glTranslatef(x, y, z);
        glRotatef(pitch, 1.0f, 0.0f, 0.0f);
        glRotatef(yaw, 0.0f, 1.0f, 0.0f);
        glRotatef(roll, 0.0f, 0.0f, 1.0f);
        glScalef(scale, scale, scale);
    }

    void move(float dx, float dy, float dz) {
        // Перевод углов в радианы
        float yawRad = yaw * M_PI / 180.0f;
        float pitchRad = pitch * M_PI / 180.0f;

        // Перемещение с учётом углов поворота
        x += dz * cos(pitchRad) * sin(yawRad) + dx * cos(yawRad);
        y += dz * sin(pitchRad) + dy;
        z += dz * cos(pitchRad) * cos(yawRad) - dx * sin(yawRad);
    }

    void rotate(float dpitch, float dyaw, float droll) {
        pitch += dpitch;
        yaw += dyaw;
        roll += droll;
    }

    void rescale(float factor) {
        scale *= factor;
    }
};


// Функция для отрисовки куба
void drawCube() {
    glBegin(GL_QUADS);

    // Передняя грань
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Задняя грань
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    // Левая грань
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    // Правая грань
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    // Верхняя грань
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Нижняя грань
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    glEnd();
}

// Функция для отрисовки пирамиды
void drawPyramid() {
    glBegin(GL_TRIANGLES);

    // Передняя грань
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f); // Верхняя вершина
    glVertex3f(-0.5f, -0.5f, 0.5f); // Левая нижняя вершина
    glVertex3f(0.5f, -0.5f, 0.5f); // Правая нижняя вершина

    // Правая грань
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f); // Верхняя вершина
    glVertex3f(0.5f, -0.5f, 0.5f); // Передняя правая вершина
    glVertex3f(0.5f, -0.5f, -0.5f); // Задняя правая вершина

    // Задняя грань
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.5f, 0.0f); // Верхняя вершина
    glVertex3f(0.5f, -0.5f, -0.5f); // Правая нижняя задняя вершина
    glVertex3f(-0.5f, -0.5f, -0.5f); // Левая нижняя задняя вершина

    // Левая грань
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f); // Верхняя вершина
    glVertex3f(-0.5f, -0.5f, -0.5f); // Левая задняя нижняя вершина
    glVertex3f(-0.5f, -0.5f, 0.5f); // Левая передняя нижняя вершина

    glEnd();

    // Нижняя грань (основание)
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f); // Передняя левая
    glVertex3f(0.5f, -0.5f, 0.5f); // Передняя правая
    glVertex3f(0.5f, -0.5f, -0.5f); // Задняя правая
    glVertex3f(-0.5f, -0.5f, -0.5f); // Задняя левая
    glEnd();
}


int main() {
    sf::Window window(sf::VideoMode(800, 600), "3D", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    // Настройка OpenGL
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    Camera camera;
    Transformable cube, pyramid;
    cube.x = -1.5f;
    pyramid.x = 1.5f;

    int activeObject = 0; // 0 - камера, 1 - куб, 2 - пирамида

    bool running = true;
    while (running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Tab) {
                    activeObject = (activeObject + 1) % 3;
                }
            }
        }

        // Управление
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (activeObject == 0) camera.move(0, 0, -0.1f);
            else if (activeObject == 1) cube.move(0, 0, -0.1f);
            else if (activeObject == 2) pyramid.move(0, 0, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (activeObject == 0) camera.move(0, 0, 0.1f);
            else if (activeObject == 1) cube.move(0, 0, 0.1f);
            else if (activeObject == 2) pyramid.move(0, 0, 0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (activeObject == 0) camera.move(-0.1f, 0, 0);
            else if (activeObject == 1) cube.move(-0.1f, 0, 0);
            else if (activeObject == 2) pyramid.move(-0.1f, 0, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (activeObject == 0) camera.move(0.1f, 0, 0);
            else if (activeObject == 1) cube.move(0.1f, 0, 0);
            else if (activeObject == 2) pyramid.move(0.1f, 0, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            if (activeObject == 1) cube.rescale(1.01f);
            else if (activeObject == 2) pyramid.rescale(1.01f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            if (activeObject == 1) cube.rescale(0.99f);
            else if (activeObject == 2) pyramid.rescale(0.99f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (activeObject == 0) camera.rotate(-1, 0);
            else if (activeObject == 1) cube.rotate(-1, 0, 0);
            else if (activeObject == 2) pyramid.rotate(-1, 0, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (activeObject == 0) camera.rotate(1, 0);
            else if (activeObject == 1) cube.rotate(1, 0, 0);
            else if (activeObject == 2) pyramid.rotate(1, 0, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (activeObject == 0) camera.rotate(0, -1);
            else if (activeObject == 1) cube.rotate(0, -1, 0);
            else if (activeObject == 2) pyramid.rotate(0, -1, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (activeObject == 0) camera.rotate(0, 1);
            else if (activeObject == 1) cube.rotate(0, 1, 0);
            else if (activeObject == 2) pyramid.rotate(0, 1, 0);
        }

        // Очистка экрана
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        camera.apply();

        // Отрисовка куба
        glPushMatrix();
        cube.apply();
        drawCube();
        glPopMatrix();

        // Отрисовка пирамиды
        glPushMatrix();
        pyramid.apply();
        drawPyramid();
        glPopMatrix();

        window.display();
    }

    return 0;
}


