#include "entity.h"

Entity::Entity()
    : m_VB(m_Vertices, sizeof(m_Vertices))
    , m_IB(m_Indices, m_Indices.size())
{
}
