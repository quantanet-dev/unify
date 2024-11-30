#pragma once
#include <spdlog/spdlog.h>

#define UNIFY_DEFAULT_LOGGER_NAME "UnifyLogger"

#if defined(UNIFY_PLATFORM_WINDOWS)
#define UNIFY_BREAK __debugbreak();
#elif defined(UNIFY_PLATFORM_APPLE)
#define UNIFY_BREAK __builtin_debugtrap();
#else
#define UNIFY_BREAK __builtin_trap();
#endif

#ifndef UNIFY_CONFIG_RELEASE
#define UNIFY_TRACE(...)                                                       \
  if (spdlog::get(UNIFY_DEFAULT_LOGGER_NAME) != NULL) {                        \
    spdlog::get(UNIFY_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);                \
  }
#define UNIFY_DEBUG(...)                                                       \
  if (spdlog::get(UNIFY_DEFAULT_LOGGER_NAME) != NULL) {                        \
    spdlog::get(UNIFY_DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__);                \
  }
#define UNIFY_INFO(...)                                                        \
  if (spdlog::get(UNIFY_DEFAULT_LOGGER_NAME) != NULL) {                        \
    spdlog::get(UNIFY_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);                 \
  }
#define UNIFY_WARN(...)                                                        \
  if (spdlog::get(UNIFY_DEFAULT_LOGGER_NAME) != NULL) {                        \
    spdlog::get(UNIFY_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);                 \
  }
#define UNIFY_ERROR(...)                                                       \
  if (spdlog::get(UNIFY_DEFAULT_LOGGER_NAME) != NULL) {                        \
    spdlog::get(UNIFY_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);                \
  }
#define UNIFY_FATAL(...)                                                       \
  if (spdlog::get(UNIFY_DEFAULT_LOGGER_NAME) != NULL) {                        \
    spdlog::get(UNIFY_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__);             \
  }
#define UNIFY_ASSERT(x, msg)                                                   \
  if ((x)) {                                                                   \
  } else {                                                                     \
    UNIFY_FATAL("ASSERT: {}\n\t{}\n\tin file: {}\n\ton line: {}", #x, msg,     \
                __FILE__, __LINE__);                                           \
    UNIFY_BREAK                                                                \
  }
#else
// disable logging in release
#define UNIFY_TRACE(...) (void)0
#define UNIFY_DEBUG(...) (void)0
#define UNIFY_INFO(...) (void)0
#define UNIFY_WARN(...) (void)0
#define UNIFY_ERROR(...) (void)0
#define UNIFY_FATAL(...) (void)0
#endif