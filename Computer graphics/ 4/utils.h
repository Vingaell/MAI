#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <string>

// Объявление глобальных переменных
extern sf::Vector2f videoScale;
extern int FrameRateLimit;

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;
extern float yaw, pitch, lastX, lastY, deltaTime, lastFrame;
extern bool firstMouse;

// Объявление функций
void processMouse(sf::Event event);
GLuint loadTexture(const char* filepath);
std::string loadShaderSource(const std::string& filepath);
GLuint compileShader(GLenum type, const std::string& source);
GLuint createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
void setupCube(GLuint& VAO, GLuint& VBO);

#endif