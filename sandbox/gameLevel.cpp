#include "gameLevel.h"

#include "cube.h"
#include "cubeLight.h"
#include "../engine/levelCamera.h"

GameLevel::GameLevel()
{
    Cube *cube = new Cube(0.f, 0.f, 0.f);
    CubeLight *cubeLight = new CubeLight(1.2f, 1.f, 2.f);

    cube->getShader()->setVec3f("lightPos", cubeLight->getPosition());
    cube->getShader()->setVec3f("lightColor", cubeLight->getColor());
    cube->getShader()->setMatrix4x4f("model", cube->getModelMatrix());

    m_Models.push_back(cube);
    m_Lights.push_back(cubeLight);
}

GameLevel::~GameLevel()
{
}

void GameLevel::update() {
    for (auto& model : m_Models) {
        model->getShader()->setVec3f("viewPos", m_Camera->getPos());
        model->update();
    }
    for (auto& light : m_Lights) {
        light->update();
    }
    m_Camera->update(); // * So far not necessary but if more than one property of Level needs updating, move to Level::update() and call from here
}
