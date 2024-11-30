#pragma once

#include "core/window.h"
#include "managers/log_manager.h"

namespace unify {

class Engine {
public:
  static Engine &Instance();
  ~Engine() {};

  void Run();
  inline void Quit() { uIsRunning = false; };

private:
  bool uIsRunning;
  bool uIsInitialized;
  core::Window uWindow;

  bool Initialize();
  void Shutdown();
  void GetInfo();

  // managers
  managers::LogManager uLogManager;

  // singleton
  Engine();
  static Engine *uInstance;
};

} // namespace unify