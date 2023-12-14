#pragma once

#include "glm/glm.hpp"

class Camera {
public:
    static void init();
    static void cleanup();
    static void update();

    static glm::mat4 lookAt(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up);

    static glm::vec3 cameraPos;
    static glm::vec3 cameraFront;
    static glm::vec3 cameraUp;

    static float yaw, pitch;
    static constexpr double sensitivity = 0.1f;
    static bool firstMouse;

    static glm::mat4 viewMatrix;

private:
    Camera() {}
};