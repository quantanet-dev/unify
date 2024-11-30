#pragma once

#include <cstdint>

namespace unify::graphics {
class Mesh {
public:
  Mesh(float *vertexArray, uint32_t vertexCount, uint32_t dimensions);
  Mesh(float *vertexArray, uint32_t vertexCount, uint32_t dimensions,
       uint32_t *elementArray, uint32_t elementCount);
  ~Mesh();

  void Bind();
  void Unbind();

  inline uint32_t GetVertexCount() const { return uVertexCount; };
  inline uint32_t GetElementCount() const { return uElementCount; };

private:
  uint32_t uVertexCount;
  uint32_t uElementCount;
  uint32_t uVao, uEbo;
  uint32_t uPositionVbo;
};
} // namespace unify::graphics