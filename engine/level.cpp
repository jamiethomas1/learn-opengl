#include "level.h"

glm::mat4 Level::getViewMatrix()
{
    return m_Camera->getViewMatrix();
}