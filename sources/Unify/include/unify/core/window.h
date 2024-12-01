#pragma once
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <memory>

#include <input/mouse.h>

struct GLFWwindow;

namespace unify::core {
class Window {
public:
  Window();
  ~Window();

  bool Create();
  void Shutdown();

  void PollEvents();

  void BeginRender();
  void EndRender();

private:
  GLFWwindow *uWindow;
  std::shared_ptr<input::Mouse> uMouse;
};
} // namespace unify::core