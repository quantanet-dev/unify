#include "graphics/helpers.h"
#include <log.h>
#include <managers/render_manager.h>

#include <glad/gl.h>

namespace unify::managers {

void RenderManager::Initialize() {

  UNIFY_INFO("OpenGL Info:\n \t\t\t Vendor:\t{}\n \t\t\t Renderer:\t{}\n "
             "\t\t\t Version\t{}",
             (const char *)glGetString(GL_VENDOR),
             (const char *)glGetString(GL_RENDERER),
             (const char *)glGetString(GL_VERSION));

  // Init OpenGL

  glEnable(GL_DEPTH_TEST);
  UNIFY_CHECK_GL_ERROR
  glDepthFunc(GL_LEQUAL);
  UNIFY_CHECK_GL_ERROR

  glEnable(GL_BLEND);
  UNIFY_CHECK_GL_ERROR
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  UNIFY_CHECK_GL_ERROR
  SetClearColor(0.39f, 0.58f, 0.93f, 1);
}

void RenderManager::Shutdown() {
  while (uRenderCommands.size() > 0) {
    uRenderCommands.pop();
  }
}

void RenderManager::Submit(
    std::unique_ptr<graphics::rendercommands::RenderCommand> rc) {
  uRenderCommands.push(std::move(rc));
}

void RenderManager::Flush() {
  while (uRenderCommands.size() > 0) {
    auto rc = std::move(uRenderCommands.front());
    uRenderCommands.pop();

    rc->Execute();
  }
}

void RenderManager::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  UNIFY_CHECK_GL_ERROR
}

void RenderManager::SetClearColor(float r, float g, float b, float a) {
  UNIFY_ASSERT(uRenderCommands.size() == 0,
               "Unflushed render commands in queue")
  while (uRenderCommands.size() > 0) {
    uRenderCommands.pop();
  }
  glClearColor(r, g, b, a);
  UNIFY_CHECK_GL_ERROR
}

} // namespace unify::managers