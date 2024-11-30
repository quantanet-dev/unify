#include <cstdlib>
#include <stdexcept>
#include <unify/engine.h>
#include <unify/log.h>

int main() {

  unify::Engine &engine = unify::Engine::Instance();

  try {
    engine.Run();
  } catch (const std::exception &e) {
    throw std::runtime_error(e.what());
  }

  return EXIT_SUCCESS;
}