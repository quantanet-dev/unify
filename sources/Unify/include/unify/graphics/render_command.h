#pragma once

#include <memory>

namespace unify::graphics {
class Mesh;
class Shader;
namespace rendercommands {

class RenderCommand {
public:
  virtual void Execute() = 0;
  virtual ~RenderCommand(){};
};

class RenderMesh : public RenderCommand {
public:
  RenderMesh(std::weak_ptr<Mesh> mesh, std::weak_ptr<Shader> shader)
      : uMesh(mesh), uShader(shader) {};

  virtual void Execute();

private:
  std::weak_ptr<Mesh> uMesh;
  std::weak_ptr<Shader> uShader;
};
} // namespace rendercommands
} // namespace unify::graphics