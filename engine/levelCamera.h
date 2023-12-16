#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

class LevelCamera {
public:
    LevelCamera();
    inline ~LevelCamera() {}

    void update();

    glm::mat4 lookAt(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up);

    inline glm::vec3 getPos() { return m_CameraPos; }
    inline glm::mat4 getViewMatrix() { return m_ViewMatrix; }

protected:
    glm::vec3 m_CameraPos;
    glm::vec3 m_CameraFront;
    glm::vec3 m_CameraUp;

    float m_Yaw, m_Pitch;
    const double m_Sensitivity = 0.1f;
    bool m_FirstMouse;

    glm::mat4 m_ViewMatrix;
};