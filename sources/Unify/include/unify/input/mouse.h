#include "GLFW/glfw3.h"
#include <memory>
namespace unify::input {

class Mouse {
private:
  double Xposition = 0, Yposition = 0, Xoffset = 0, Yoffset = 0;
  bool isInWindow = false;

public:
  Mouse() = default;
  ~Mouse() = default;

  void SetPosition(double x, double y);
  void SetScrollOffset(double x, double y);
  void SetIsInWindow(bool);
  void ScrollReset();

  static std::shared_ptr<Mouse> Initialize(GLFWwindow *uWindow);
  // static void Update();
  inline float xPosition() { return Xposition; }
  inline float yPosition() { return Yposition; }
  inline float xScrollOffset() { return Xoffset; }
  inline float yScrollOffset() { return Yoffset; }
  inline bool MouseInWindow() { return isInWindow; }
};

} // namespace unify::input