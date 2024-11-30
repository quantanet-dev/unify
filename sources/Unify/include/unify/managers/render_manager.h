#pragma once

#include <memory>
#include <queue>

#include <graphics/render_command.h>

namespace unify::managers {
class RenderManager {
public:
  RenderManager() {}
  ~RenderManager() {}

  void Initialize();
  void Shutdown();

  // Submit render commands to queue
  void Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> rc);
  // Execute render commands in the oder they were recieved;
  void Flush();

  void Clear();

  void SetClearColor(float r, float g, float b, float a);
  void SetWireframeMode(bool enabled);

private:
  std::queue<std::unique_ptr<graphics::rendercommands::RenderCommand>>
      uRenderCommands;
};

} // namespace unify::managers