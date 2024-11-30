#include <engine.h>
#include <iostream>

#include <GLFW/glfw3.h>

namespace unify {

    //public

    Engine& Engine::Instance(){
        if (!uInstance){
            uInstance = new Engine();
        }
        return *uInstance;
    };

    void Engine::Run(){


        if (Initialize()){

            while (uIsRunning){
                uWindow.PollEvents();
            }

            Shutdown();
        }

    };

    //private

    bool Engine::Initialize(){
        bool isInitialized = false;

        if (!glfwInit()){
            std::cout << "Error initializing GLFW" << std::endl;
            isInitialized = false;
        } else {
           const char* version = glfwGetVersionString();
           std::cout << "Initialized GLFW version: " << version << std::endl;

           if (uWindow.Create()){
            isInitialized = true;
            uIsRunning = true;
           }
        }

        if (isInitialized == false){
            std::cout << "Failed to initialize Unify Engine. Shutting down..." << std::endl;
        }

        return isInitialized;
    };

    void Engine::Shutdown(){

        uIsRunning = false;

        uWindow.Shutdown();
        glfwTerminate();
    }

    void Engine::GetInfo(){
        #ifdef UNIFY_CONFIG_DEBUG
            std::cout << "Configuration: DEBUG" << std::endl;
        #elif UNIFY_CONFIG_RELEASE
            std::cout << "Configuration: RELEASE" << std::endl;
        #endif
        
        #ifdef UNIFY_PLATFORM_WINDOWS
            std::cout << "Platform: Windows" << std::endl;
        #elif UNIFY_PLATFORM_APPLE
            std::cout << "Platform: MacOS" << std::endl;
        #elif UNIFY_PLATFORM_LINUX
            std::cout << "Platform: Linux" << std::endl;
        #endif
    }

    //singleton
    Engine* Engine::uInstance = NULL;

    Engine::Engine() : uIsRunning(false) {
        GetInfo();
    };

}