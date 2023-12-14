#include "camera.h"

#include <glm/ext/matrix_transform.hpp>
#include "inputManager.h"
#include "window.h"
#include "renderer.h"

glm::vec3 Camera::cameraPos = glm::vec3(0.f, 0.f, 3.f);
glm::vec3 Camera::cameraFront = glm::vec3(0.f, 0.f, -1.f);
glm::vec3 Camera::cameraUp = glm::vec3(0.f, 1.f, 0.f);
glm::mat4 Camera::viewMatrix = glm::mat4(1.f);

float Camera::yaw = -90.f, Camera::pitch = 0.f;
bool Camera::firstMouse = true;

void Camera::init()
{
    Camera::viewMatrix = glm::lookAt(Camera::cameraPos, Camera::cameraPos + Camera::cameraFront, Camera::cameraUp);
}

void Camera::cleanup()
{
}

void Camera::update() // ? Eventually would like to remove all movement functionality from this class & place into derived classes in either game engine or game.
{
    // Keyboard

    float cameraSpeed = 2.5 * Renderer::deltaTime;
    if (InputManager::isKeyDown(GLFW_KEY_W)) Camera::cameraPos += cameraSpeed * Camera::cameraFront;
    if (InputManager::isKeyDown(GLFW_KEY_S)) Camera::cameraPos -= cameraSpeed * Camera::cameraFront;
    if (InputManager::isKeyDown(GLFW_KEY_A)) Camera::cameraPos -= glm::normalize(glm::cross(Camera::cameraFront, Camera::cameraUp)) * cameraSpeed;
    if (InputManager::isKeyDown(GLFW_KEY_D)) Camera::cameraPos += glm::normalize(glm::cross(Camera::cameraFront, Camera::cameraUp)) * cameraSpeed;

    // Mouse

    double lastX = Window::width / 2.0, lastY = Window::height / 2.0;
    double xPos, yPos;
    InputManager::getMousePos(&xPos, &yPos);

    if (Camera::firstMouse) {
        lastX = xPos, lastY = yPos;
        Camera::firstMouse = false;
    }

    double xOffset = xPos - lastX, yOffset = lastY - yPos;
    lastX = xPos, lastY = yPos;
    xOffset *= Camera::sensitivity, yOffset *= Camera::sensitivity;

    Camera::yaw += xOffset;
    Camera::pitch += yOffset;

    if (Camera::pitch > 89.f) Camera::pitch = 89.f;
    if (Camera::pitch < -89.f) Camera::pitch = -89.f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(Camera::yaw)) * cos(glm::radians(Camera::pitch));
    direction.y = sin(glm::radians(Camera::pitch));
    direction.z = sin(glm::radians(Camera::yaw)) * cos(glm::radians(Camera::pitch));
    Camera::cameraFront = glm::normalize(direction);

    glfwSetCursorPos(Window::window, Window::width / 2.0, Window::height / 2.0);

    Camera::viewMatrix = glm::lookAt(Camera::cameraPos, Camera::cameraPos + Camera::cameraFront, Camera::cameraUp);
}

glm::mat4 Camera::lookAt(const glm::vec3 &pos, const glm::vec3 &target, const glm::vec3 &up)
{
    Camera::viewMatrix = glm::lookAt(pos, pos + target, up);
    return Camera::viewMatrix;
}
