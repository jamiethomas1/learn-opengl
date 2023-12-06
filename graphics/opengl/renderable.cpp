#include "renderable.h"

#include <glad/glad.h>
#include "checkGLErrors.h"


/**
 * @brief Draw call. Draws any Renderable object to the screen. Wrapper for glDrawElements
 * @param indicesCount Number of indices in the Renderable's IndexBuffer
*/
void Renderable::render(const unsigned int indicesCount) {
    GL_CALL(glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0));
}