#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "stb_image.h"
#include "utils.h"

int main() {

    glm::vec3 dirLightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);  // Направление направленного света
glm::vec3 pointLightPosition = glm::vec3(1.2f, 1.0f, 2.0f);     // Позиция точечного света

    sf::Window window(sf::VideoMode(videoScale.x, videoScale.y), "Lab 4", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorGrabbed(true);
    window.setMouseCursorVisible(false);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Ошибка инициализации GLEW" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    GLuint texture = loadTexture("171.JPG");
    GLuint normalMap = loadTexture("171_norm.JPG");

    if (texture == 0 || normalMap == 0) {
        std::cerr << "Ошибка загрузки текстур." << std::endl;
        return -1;
    }

    GLuint shaderProgram = createShaderProgram("vertex_shader.glsl", "fragment_shader.glsl");
    if (shaderProgram == 0) {
        std::cerr << "Ошибка создания шейдерной программы." << std::endl;
        return -1;
    }

    GLuint cubeVAO, cubeVBO;
    setupCube(cubeVAO, cubeVBO);

    glm::vec3 cameraPos(0.0f, 0.0f, 5.0f);
    glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
    float yaw = -90.0f;
    float pitch = 0.0f;

    float lastX = 400.0f, lastY = 300.0f;
    bool firstMouse = true;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // Массив с позициями для нескольких кубов
    std::vector<glm::vec3> cubePositions = {
        glm::vec3(-2.0f, 0.0f, -5.0f), // Первый куб
        glm::vec3(2.0f, 0.0f, -5.0f),  // Второй куб
        glm::vec3(0.0f, 2.0f, -5.0f)   // Третий куб
    };

    // Флаг для переключения между нормальной картой и стандартным затенением
    bool useNormalMapping = true;

    sf::Clock clock;

    while (window.isOpen()) {
        
        float currentFrame = clock.getElapsedTime().asSeconds();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N) {
                useNormalMapping = !useNormalMapping; // Переключение флага
            }

            // Обработка движения мыши
            if (event.type == sf::Event::MouseMoved) {
                float xpos = static_cast<float>(event.mouseMove.x);
                float ypos = static_cast<float>(event.mouseMove.y);

                if (firstMouse) {
                    lastX = xpos;
                    lastY = ypos;
                    firstMouse = false;
                }

                float xOffset = xpos - lastX;
                float yOffset = lastY - ypos; 
                lastX = xpos;
                lastY = ypos;

                float sensitivity = 0.1f;
                xOffset *= sensitivity;
                yOffset *= sensitivity;

                yaw += xOffset;
                pitch += yOffset;

                if (pitch > 89.0f)
                    pitch = 89.0f;
                if (pitch < -89.0f)
                    pitch = -89.0f;

                glm::vec3 front;
                front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
                front.y = sin(glm::radians(pitch));
                front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
                cameraFront = glm::normalize(front);
            }
        }

        // Движение камеры
        float cameraSpeed = 10.0f * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            cameraPos += cameraSpeed * cameraFront;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            cameraPos -= cameraSpeed * cameraFront;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);

    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    GLint viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
    GLint useNormalMapLoc = glGetUniformLocation(shaderProgram, "useNormalMap");

    // Получаем локации униформ для источников света
    GLint dirLightLoc = glGetUniformLocation(shaderProgram, "dirLightDirection");
    GLint pointLightLoc = glGetUniformLocation(shaderProgram, "pointLightPosition");

    // Передаем значения униформ для позиции камеры
    glUniform3fv(viewPosLoc, 1, glm::value_ptr(cameraPos));

    // Получаем и передаем значения для направленного и точечного света
    glUniform3fv(dirLightLoc, 1, glm::value_ptr(dirLightDirection));
    glUniform3fv(pointLightLoc, 1, glm::value_ptr(pointLightPosition));

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    // Передаем флаг использования нормальной карты
    glUniform1i(useNormalMapLoc, useNormalMapping ? 1 : 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalMap);
    glUniform1i(glGetUniformLocation(shaderProgram, "normalMap"), 1);

    // Рисуем все кубы
    for (const auto& cubePos : cubePositions) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePos);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    window.display();
}

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteProgram(shaderProgram);

    return 0;
}


