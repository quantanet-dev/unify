#include "GLFW/glfw3.h"
#include <core/window.h>
#include <engine.h>
#include <cstddef>
#include <iostream>

namespace unify::core {

    Window::Window() : uWindow(NULL){};

    Window::~Window(){
        if (uWindow){
            Shutdown();
        }
    }

    bool Window::Create(){
        uWindow = glfwCreateWindow(1280, 720, "Unify Editor", NULL, NULL);
        if (!uWindow){
            std::cout << "Error: Could not create window" << std::endl;
            return false;
        }

        PollEvents();

        return true;
    }

    void Window::Shutdown(){
        glfwDestroyWindow(uWindow);
        uWindow = NULL;
    }

    void Window::PollEvents(){
        if (uWindow){
            if (!glfwWindowShouldClose(uWindow)){
                glfwPollEvents();
            } else {
                Engine::Instance().Quit();
            }
        }
    }

}