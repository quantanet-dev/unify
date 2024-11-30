#pragma once

#include "core/window.h"

namespace unify {

    class Engine {
        public:
            static Engine& Instance();
            ~Engine(){};
            
            void Run();
            inline void Quit() {uIsRunning = false;};

        private:
            bool uIsRunning;
            core::Window uWindow;
            
            [[nodiscard]] bool Initialize();
            void Shutdown();
            void GetInfo();
            
            //singleton
            Engine(); 
            static Engine* uInstance;
    };

}