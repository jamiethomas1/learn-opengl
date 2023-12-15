#include "sceneCamera.h"

#include <glm/ext/matrix_transform.hpp>
#include "inputManager.h"
#include "window.h"
#include "renderer.h"


SceneCamera::SceneCamera() 
    : m_CameraPos(glm::vec3(0.f, 0.f, 3.f))
    , m_CameraFront(glm::vec3(0.f, 0.f, -1.f))
    , m_CameraUp(glm::vec3(0.f, 1.f, 0.f))
    , m_ViewMatrix(glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp))
    , m_Yaw(-90.f)
    , m_Pitch(0.f)
    , m_FirstMouse(true)
{

}


SceneCamera::~SceneCamera() 
{

}


/**
 * @brief Run input processing & anything else that the Camera needs to be done every frame
*/
void SceneCamera::update() // ? Eventually would like to remove all movement functionality from this class & place into derived classes in either game engine or game.
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


/**
 * @brief Set the camera to look at something, from somewhere, from some angle
 * @param pos Position of Camera in world
 * @param target Normalised position vector of target // ? is this correct?
 * @param up What direction is up relative to the Camera?
 * @return View matrix
*/
glm::mat4 SceneCamera::lookAt(const glm::vec3 &pos, const glm::vec3 &target, const glm::vec3 &up)
{
    m_ViewMatrix = glm::lookAt(pos, pos + target, up);
    return m_ViewMatrix;
}
