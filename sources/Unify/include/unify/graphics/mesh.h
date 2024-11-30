#pragma once

#include <cstdint>

namespace unify::graphics {
class Mesh {
public:
  Mesh(float *vertexArray, uint32_t vertexCount, uint32_t dimensions);
  ~Mesh();

  void Bind();
  void Unbind();

  inline uint32_t GetVertexCount() const { return uVertexCount; };

private:
  uint32_t uVertexCount;
  uint32_t uVao;
  uint32_t uPositionVbo;
};
} // namespace unify::graphics