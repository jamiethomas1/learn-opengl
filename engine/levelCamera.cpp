#include "levelCamera.h"


/**
 * @brief Run input processing & anything else that the Camera needs to be done every frame
*/
void LevelCamera::update() // ? Eventually would like to remove all movement functionality from this class & place into derived classes in either game engine or game.
{
    // Keyboard

    float cameraSpeed = 2.5 * Renderer::deltaTime;
    if (InputManager::isKeyDown(GLFW_KEY_W)) m_CameraPos += cameraSpeed * m_CameraFront;
    if (InputManager::isKeyDown(GLFW_KEY_S)) m_CameraPos -= cameraSpeed * m_CameraFront;
    if (InputManager::isKeyDown(GLFW_KEY_A)) m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;
    if (InputManager::isKeyDown(GLFW_KEY_D)) m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;

    // Mouse

    double lastX = Window::width / 2.0, lastY = Window::height / 2.0;
    double xPos, yPos;
    InputManager::getMousePos(&xPos, &yPos);

    if (m_FirstMouse) {
        lastX = xPos, lastY = yPos;
        m_FirstMouse = false;
    }

    double xOffset = xPos - lastX, yOffset = lastY - yPos;
    lastX = xPos, lastY = yPos;
    xOffset *= m_Sensitivity, yOffset *= m_Sensitivity;

    m_Yaw += xOffset;
    m_Pitch += yOffset;

    if (m_Pitch > 89.f) m_Pitch = 89.f;
    if (m_Pitch < -89.f) m_Pitch = -89.f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    direction.y = sin(glm::radians(m_Pitch));
    direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_CameraFront = glm::normalize(direction);

    glfwSetCursorPos(Window::window, Window::width / 2.0, Window::height / 2.0);

    m_ViewMatrix = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
}
