#pragma once

namespace unify::managers {
class LogManager {
public:
  LogManager() = default;
  ~LogManager() = default;

  void Initialize();
  void Shutdown();
};
} // namespace unify::managers