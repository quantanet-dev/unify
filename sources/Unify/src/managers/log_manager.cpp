#include <log.h>
#include <managers/log_manager.h>
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace unify::managers {

void LogManager::Initialize() {
  auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console->set_pattern("%^[%Y-%m-%d @ %H:%M:%S]: %v%$");

  std::vector<spdlog::sink_ptr> sinks{console};
  auto logger = std::make_shared<spdlog::logger>(UNIFY_DEFAULT_LOGGER_NAME,
                                                 sinks.begin(), sinks.end());
  logger->set_level(spdlog::level::trace);
  logger->flush_on(spdlog::level::trace);
  spdlog::register_logger(logger);
}

void LogManager::Shutdown() { spdlog::shutdown(); };
} // namespace unify::managers