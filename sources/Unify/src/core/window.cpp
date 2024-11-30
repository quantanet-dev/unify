#include <core/window.h>
#include <cstddef>
#include <engine.h>

#include <log.h>

namespace unify::core {

Window::Window() : uWindow(NULL) {};

Window::~Window() {
  if (uWindow) {
    Shutdown();
  }
}

bool Window::Create() {

#ifdef UNIFY_PLATFORM_APPLE
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  uWindow = glfwCreateWindow(1280, 720, "Unify Editor", NULL, NULL);
  if (!uWindow) {
    UNIFY_ERROR("Error: Could not create window");
    return false;
  }
  glfwMakeContextCurrent(uWindow);
  glfwSetWindowSizeLimits(uWindow, 200, 200, GLFW_DONT_CARE, GLFW_DONT_CARE);

  gladLoadGL(glfwGetProcAddress);

  return true;
}

void Window::Shutdown() {
  glfwDestroyWindow(uWindow);
  uWindow = NULL;
}

void Window::PollEvents() {
  if (uWindow) {
    if (!glfwWindowShouldClose(uWindow)) {
      glfwPollEvents();
    } else {
      Engine::Instance().Quit();
    }
  }
}

void Window::BeginRender() { Engine::Instance().GetRenderManager().Clear(); }

void Window::EndRender() { glfwSwapBuffers(uWindow); }

} // namespace unify::core