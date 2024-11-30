#pragma once
#pragma clang diagnostic ignored "-Wc++17-extensions"

struct GLFWwindow;

namespace unify::core {
    class Window {
        public:
            Window();
            ~Window();

            bool Create();
            void Shutdown();

            void PollEvents();

        private:
            GLFWwindow* uWindow;

    };
}