#include "graphics/mesh.h"
#include "graphics/render_command.h"
#include <engine.h>
#include <log.h>

#include <graphics/mesh.h>
#include <graphics/shader.h>
#include <memory>

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

    // Test Mesh
    float vertices[]{-0.5f, -0.5, 0.f, 0.f, 0.5f, 0.f, 0.5f, -0.5f, 0.f};

    std::shared_ptr<graphics::Mesh> mesh =
        std::make_shared<graphics::Mesh>(&vertices[0], 3, 3);

    // Test Shader
    const char *vertexShader = R"(
      #version 410 core
      layout (location = 0) in vec3 position;
      void main(){
        gl_Position = vec4(position, 1.0);
      }
    )";

    const char *fragmentShader = R"(
      #version 410 core
      out vec4 outColor;
      void main(){
        outColor = vec4(1.0);
      }
    )";

    std::shared_ptr<graphics::Shader> shader =
        std::make_shared<graphics::Shader>(vertexShader, fragmentShader);

    while (uIsRunning) {
      uWindow.PollEvents();

      uWindow.BeginRender();

      auto rc =
          std::make_unique<graphics::rendercommands::RenderMesh>(mesh, shader);

      uRenderManager.Submit(std::move(rc));
      uRenderManager.Flush();

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

        // Initialize managers
        uRenderManager.Initialize();

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
  uRenderManager.Shutdown();
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