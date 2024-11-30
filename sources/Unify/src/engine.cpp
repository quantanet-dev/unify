#include <engine.h>
#include <log.h>

namespace unify {

// public

Engine &Engine::Instance() {
  if (!uInstance) {
    uInstance = new Engine();
  }
  return *uInstance;
};

void Engine::Run() {
  if (Initialize()) {

    while (uIsRunning) {
      uWindow.PollEvents();

      uWindow.BeginRender();
      uWindow.EndRender();
    }

    Shutdown();
  }
};

// private

bool Engine::Initialize() {
  UNIFY_ASSERT(!uIsInitialized,
               "Attempting to call Engine:Initialize() more than once!");

  if (!uIsInitialized) {
    uLogManager.Initialize();
    GetInfo();

    if (!glfwInit()) {
      UNIFY_ERROR("ERROR: Unable to initialize GLFW");
      uIsInitialized = false;
    } else {
      const char *version = glfwGetVersionString();
      UNIFY_INFO("Initialized GLFW version: {}", version);

      if (uWindow.Create()) {
        uIsInitialized = true;
        uIsRunning = true;
      }
    }
  }

  if (!uIsInitialized) {
    UNIFY_FATAL("FATAL: Failed to initialize Unify Engine. Shutting down...");
  }

  return uIsInitialized;
};

void Engine::Shutdown() {

  uIsRunning = false;
  uIsInitialized = false;

  // managers - in reverse order
  uLogManager.Shutdown();

  uWindow.Shutdown();
  glfwTerminate();
}

void Engine::GetInfo() {
  UNIFY_INFO("Unify Engine v{}.{}", 0, 1);

#ifdef UNIFY_CONFIG_DEBUG
  UNIFY_DEBUG("Configuration: DEBUG")
#elif UNIFY_CONFIG_RELEASE
  UNIFY_DEBUG("Configuration: RELEASE")
#endif

#ifdef UNIFY_PLATFORM_WINDOWS
  UNIFY_DEBUG("Platform: Windows");
#elif UNIFY_PLATFORM_APPLE
  UNIFY_DEBUG("Platform: MacOS");
#elif UNIFY_PLATFORM_LINUX
  UNIFY_DEBUG("Platform: Linux");
  std::cout << "Platform: Linux" << std::endl;
#endif
}

// singleton
Engine *Engine::uInstance = NULL;

Engine::Engine() : uIsRunning(false), uIsInitialized(false) {};

} // namespace unify