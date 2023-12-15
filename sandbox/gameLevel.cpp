#include "gameLevel.h"

#include "cube.h"
#include "cubeLight.h"

GameLevel::GameLevel()
{

    m_Models.push_back(new Cube(0.f, 0.f, 0.f)); // ? Could do it this way or could simply declare & initialise new Cube & change Model constructor to push to Scene instead of Renderer
    m_Lights.push_back(new CubeLight(1.2f, 1.f, 2.f)); // ? Would need to change Cube & Model constructors to require a Scene parameter (and set here to *this). Current way probably more straightforward.
}

GameLevel::~GameLevel()
{
}

void GameLevel::update() {
    for (auto& model : m_Models) model->update();
    for (auto& light : m_Lights) light->update();
    m_Camera->update(); // ? Maybe update in Level or Scene update functions?
}
