#include "graphics/helpers.h"
#include <graphics/render_command.h>
#include <log.h>

#include <graphics/mesh.h>
#include <graphics/shader.h>

#include <glad/gl.h>
#include <memory>

namespace unify::graphics::rendercommands {
void RenderMesh::Execute() {
  std::shared_ptr<Mesh> mesh = uMesh.lock();
  std::shared_ptr<Shader> shader = uShader.lock();
  if (mesh && shader) {
    mesh->Bind();
    shader->Bind();

    if (mesh->GetElementCount() > 0) {
      glDrawElements(GL_TRIANGLES, mesh->GetElementCount(), GL_UNSIGNED_INT, 0);
    } else {
      glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->GetVertexCount());
      UNIFY_CHECK_GL_ERROR
    }

    shader->Unbind();
    mesh->Unbind();
  } else {
    UNIFY_WARN("Attempting to execute RenderMesh() with invalid data");
  }
}
} // namespace unify::graphics::rendercommands
