#include "manyCubesLevel.h"

#include "cube.h"
#include "cubeLight.h"

ManyCubesLevel::ManyCubesLevel()
{

    Cube* cubePositions[] = {
        new Cube(0.0f, 0.0f, 0.0f),
        new Cube(2.0f, 5.0f, -15.0f),
        new Cube(-1.5f, -2.2f, -2.5f),
        new Cube(-3.8f, -2.0f, -12.3f),
        new Cube(2.4f, -0.4f, -3.5f),
        new Cube(-1.7f, 3.0f, -7.5f),
        new Cube(1.3f, -2.0f, -2.5f),
        new Cube(1.5f, 2.0f, -2.5f),
        new Cube(1.5f, 0.2f, -1.5f),
        new Cube(-1.3f, 1.0f, -1.5f)
    };

    for (unsigned int i = 0; i < 10; i++)
    {
        float angle = 20.f * i;
        cubePositions[i]->rotate(angle, glm::vec3(1.f, 0.3f, 0.5f));
        m_Models.push_back(cubePositions[i]);
    }
    m_Lights.push_back(new CubeLight(1.2f, 1.f, 2.f));
}

ManyCubesLevel::~ManyCubesLevel()
{
}

void ManyCubesLevel::update() {
    for (auto& model : m_Models) model->update();
    for (auto& light : m_Lights) light->update();
    m_Camera->update();
}
