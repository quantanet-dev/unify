#include <input/mouse.h>
#include <memory>

namespace unify::input {

std::shared_ptr<Mouse> mouse = std::make_shared<Mouse>();

// void Mouse::Update() {
//   mouse.SetIsInWindow();
//   mouse.SetPosition();
//   mouse.SetScrollOffset();
// }

void Mouse::SetPosition(double x, double y) {
  Xposition = x;
  Yposition = y;
}

void Mouse::SetScrollOffset(double x, double y) {
  Xoffset = x;
  Yoffset = y;
}

void Mouse::SetIsInWindow(bool isSet) { isInWindow = isSet; }

void cursor_enter_callback(GLFWwindow *window, int entered) {
  if (entered) {
    mouse->SetIsInWindow(true);
  } else {
    mouse->SetIsInWindow(false);
  }
}

static void cursor_position_callback(GLFWwindow *window, double xpos,
                                     double ypos) {
  mouse->SetPosition(xpos, ypos);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  mouse->SetScrollOffset(xoffset, yoffset);
}

std::shared_ptr<Mouse> Mouse::Initialize(GLFWwindow *uWindow) {
  glfwSetCursorEnterCallback(uWindow, cursor_enter_callback);
  glfwSetCursorPosCallback(uWindow, cursor_position_callback);
  glfwSetScrollCallback(uWindow, scroll_callback);
  // glfwSetMouseButtonCallback(uWindow, mouse_button_callback);
  return mouse;
}

} // namespace unify::input