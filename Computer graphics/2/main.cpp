#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <cmath>

// Функция для отрисовки куба
void drawCube() {
    glBegin(GL_QUADS);
    // Передняя грань
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Задняя грань
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    // Верхняя грань
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    // Нижняя грань
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Правая грань
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    // Левая грань
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();
}

// Функция для отрисовки пирамиды
void drawPyramid() {
    glBegin(GL_TRIANGLES);
    // Передняя грань
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    // Правая грань
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    // Задняя грань
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    // Левая грань
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();
}

// Функция для отрисовки сферы
void drawSphere(float radius, int slices, int stacks) {
    for (int i = 0; i <= stacks; ++i) {
        float phi = (float)i / stacks * M_PI;
        float nextPhi = (float)(i + 1) / stacks * M_PI;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float theta = (float)j / slices * 2.0f * M_PI;

            float x = radius * sinf(phi) * cosf(theta);
            float y = radius * cosf(phi);
            float z = radius * sinf(phi) * sinf(theta);
            glVertex3f(x, y, z);

            x = radius * sinf(nextPhi) * cosf(theta);
            y = radius * cosf(nextPhi);
            z = radius * sinf(nextPhi) * sinf(theta);
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

void setPerspectiveProjection(float fov, float aspectRatio, float nearPlane, float farPlane) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspectRatio, nearPlane, farPlane);
    glMatrixMode(GL_MODELVIEW);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "3D Scene", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    glEnable(GL_DEPTH_TEST);

    float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 5.0f;
    float pitch = 0.0f, yaw = 0.0f;
    float fov = 45.0f;
    const float rotationSpeed = 1.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Управление камерой
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) cameraZ -= 0.1f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) cameraZ += 0.1f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cameraX -= 0.1f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) cameraX += 0.1f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) fov -= 1.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) fov += 1.0f;

        // Вращение камеры
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) pitch -= rotationSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) pitch += rotationSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) yaw -= rotationSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) yaw += rotationSpeed;

        // Ограничение угла поворота по вертикали
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        glLoadIdentity();
        glRotatef(pitch, 1.0f, 0.0f, 0.0f);
        glRotatef(yaw, 0.0f, 1.0f, 0.0f);
        glTranslatef(-cameraX, -cameraY, -cameraZ);

        setPerspectiveProjection(fov, 800.0f / 600.0f, 0.1f, 100.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        glTranslatef(-1.5f, 0.0f, 0.0f);
        drawCube();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.5f, 0.0f, 0.0f);
        drawPyramid();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, 1.5f, 0.0f);
        drawSphere(0.5f, 20, 20);
        glPopMatrix();

        window.display();
    }

    return 0;
}

