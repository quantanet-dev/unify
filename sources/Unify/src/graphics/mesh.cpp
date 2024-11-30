#include <cstdint>
#include <glad/gl.h>
#include <graphics/helpers.h>
#include <graphics/mesh.h>

namespace unify::graphics {

Mesh::Mesh(float *vertexArray, uint32_t vertexCount, uint32_t dimensions)
    : uVertexCount(vertexCount), uEbo(0), uElementCount(0) {
  glGenVertexArrays(1, &uVao);
  UNIFY_CHECK_GL_ERROR;
  glBindVertexArray(uVao);
  UNIFY_CHECK_GL_ERROR

  glGenBuffers(1, &uPositionVbo);
  glBindBuffer(GL_ARRAY_BUFFER, uPositionVbo);
  UNIFY_CHECK_GL_ERROR
  glBufferData(GL_ARRAY_BUFFER, (vertexCount * dimensions) * sizeof(float),
               vertexArray, GL_STATIC_DRAW);
  UNIFY_CHECK_GL_ERROR

  glEnableVertexAttribArray(0);
  UNIFY_CHECK_GL_ERROR
  glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, 0, 0);
  UNIFY_CHECK_GL_ERROR
  glDisableVertexAttribArray(0);
  UNIFY_CHECK_GL_ERROR
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  UNIFY_CHECK_GL_ERROR

  glBindVertexArray(0);
  UNIFY_CHECK_GL_ERROR
}

Mesh::Mesh(float *vertexArray, uint32_t vertexCount, uint32_t dimensions,
           uint32_t *elementArray, uint32_t elementCount)
    : Mesh(vertexArray, vertexCount, dimensions) {

  uElementCount = elementCount;

  glBindVertexArray(uVao);
  UNIFY_CHECK_GL_ERROR

  glGenBuffers(1, &uEbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uEbo);
  UNIFY_CHECK_GL_ERROR
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               (elementCount * dimensions) * sizeof(uint32_t), elementArray,
               GL_STATIC_DRAW);
  UNIFY_CHECK_GL_ERROR

  glBindVertexArray(0);
  UNIFY_CHECK_GL_ERROR
}

Mesh::~Mesh() {
  glDeleteBuffers(1, &uPositionVbo);
  UNIFY_CHECK_GL_ERROR
  if (uEbo != 0) {
    glDeleteBuffers(1, &uEbo);
    UNIFY_CHECK_GL_ERROR
  }
  glDeleteVertexArrays(1, &uVao);
  UNIFY_CHECK_GL_ERROR
};

void Mesh::Bind() {
  glBindVertexArray(uVao);
  UNIFY_CHECK_GL_ERROR
  glEnableVertexAttribArray(0);
  UNIFY_CHECK_GL_ERROR
}

void Mesh::Unbind() {
  glDisableVertexAttribArray(0);
  UNIFY_CHECK_GL_ERROR
  glBindVertexArray(0);
  UNIFY_CHECK_GL_ERROR
}

} // namespace unify::graphics