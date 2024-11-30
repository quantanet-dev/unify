#pragma once

#include "core/window.h"
#include "managers/log_manager.h"
#include "managers/render_manager.h"

namespace unify {

class Engine {
public:
  static Engine &Instance();
  ~Engine() {};

  void Run();
  inline void Quit() { uIsRunning = false; };

  // managers
  inline managers::RenderManager &GetRenderManager() { return uRenderManager; };

private:
  bool uIsRunning;
  bool uIsInitialized;
  core::Window uWindow;

  bool Initialize();
  void Shutdown();
  void GetInfo();

  // managers
  managers::LogManager uLogManager;
  managers::RenderManager uRenderManager;

  // singleton
  Engine();
  static Engine *uInstance;
};

} // namespace unify