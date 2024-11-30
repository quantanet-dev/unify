#include <iostream>
#include <ostream>
#include <unify/engine.h>

int main(){
    std::cout << "Welcome to UnifyEditor!" << std::endl;

    unify::Engine& engine = unify::Engine::Instance();

    engine.Run();
    
    std::cout << "Press ENTER to continue..." << std::endl;
    std::cin.ignore();

    return 0;
}