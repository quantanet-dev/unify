#include <unify/engine.h>
#include <unify/log.h>

int main() {
  UNIFY_TRACE("Welcome to Unify Editor v{}.{}!", 0, 1);

  unify::Engine &engine = unify::Engine::Instance();

  engine.Run();

  return 0;
}