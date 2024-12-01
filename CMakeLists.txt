cmake_minimum_required(VERSION 3.31.0)

set(CMAKE_CPP_STANDARD 23)
set(CMAKE_CPP_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CONFIGURATION_TYPES
    Debug,
    Release
)

IF (WIN32)
    add_compile_definitions(
        "UNIFY_PLATFORM_WINDOWS"
    )
ELSEIF (APPLE)
    add_compile_definitions(
        "UNIFY_PLATFORM_APPLE"
    )
ELSEIF (LINUX)
    add_compile_definitions(
        "UNIFY_PLATFORM_LINUX"
    )
ENDIF()

IF (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_compile_definitions(
        "UNIFY_CONFIG_DEBUG"
    )
ELSEIF (${CMAKE_BUILD_TYPE} STREQUAL Release)
    add_compile_definitions(
        "UNIFY_CONFIG_RELEASE"
    )
ENDIF()

project(UnifyEngine VERSION 0.1.0 LANGUAGES C CXX)

#FETCH DEPENDENCIES
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.0
)

FetchContent_MakeAvailable(glfw glad spdlog)

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/_deps/glad-src/cmake)
glad_add_library(glad_gl_core_41 REPRODUCIBLE API gl:core=4.1)

add_library(
    UnifyEngine
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Unify/src/engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Unify/src/core/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Unify/src/managers/log_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Unify/src/managers/render_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Unify/src/input/mouse.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Unify/src/graphics/helpers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Unify/src/graphics/render_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Unify/src/graphics/mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Unify/src/graphics/shader.cpp
)

target_include_directories(
    UnifyEngine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/Unify/include/unify
)

target_link_libraries(
    UnifyEngine
    glad_gl_core_41
    glfw
    spdlog
)


project(UnifyEditor VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CPP_STANDARD 23)
set(CMAKE_CPP_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    UnifyEditor
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/UnifyEditor/src/main.cpp
)

target_include_directories(
    UnifyEditor
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/UnifyEditor/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/Unify/include
)

target_link_libraries(
    UnifyEditor
    UnifyEngine
)
