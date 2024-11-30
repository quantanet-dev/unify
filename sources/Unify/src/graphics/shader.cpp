#include "graphics/helpers.h"
#include <glad/gl.h>
#include <graphics/shader.h>
#include <log.h>

namespace unify::graphics {
Shader::Shader(const std::string &vertex, const std::string &fragment) {
  uProgramId = glCreateProgram(); UNIFY_CHECK_GL_ERROR

  int status = GL_FALSE;
  char errorLog[512];

  uint32_t vertexShaderId = glCreateShader(GL_VERTEX_SHADER); UNIFY_CHECK_GL_ERROR
  {
    const char *glSource = vertex.c_str();
    glShaderSource(vertexShaderId, 1, &glSource, NULL); UNIFY_CHECK_GL_ERROR

    glCompileShader(vertexShaderId); UNIFY_CHECK_GL_ERROR
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &status); UNIFY_CHECK_GL_ERROR
    if (status != GL_TRUE) {
      glGetShaderInfoLog(vertexShaderId, sizeof(errorLog), NULL, errorLog); UNIFY_CHECK_GL_ERROR
      UNIFY_ERROR("Unable to compile vertex shader: {}", errorLog);
    }

    glAttachShader(uProgramId, vertexShaderId); UNIFY_CHECK_GL_ERROR
  }
  uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER); UNIFY_CHECK_GL_ERROR
  if (status == GL_TRUE) {
    const char *glSource = fragment.c_str();
    glShaderSource(fragmentShaderId, 1, &glSource, NULL); UNIFY_CHECK_GL_ERROR

    glCompileShader(fragmentShaderId); UNIFY_CHECK_GL_ERROR
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &status); UNIFY_CHECK_GL_ERROR
    if (status != GL_TRUE) {
      glGetShaderInfoLog(fragmentShaderId, sizeof(errorLog), NULL, errorLog); UNIFY_CHECK_GL_ERROR
      UNIFY_ERROR("Unable to compile fragment shader: {}", errorLog);
    }

    glAttachShader(uProgramId, fragmentShaderId); UNIFY_CHECK_GL_ERROR

    UNIFY_ASSERT(status == GL_TRUE, "Error compiling shader")
    if (status == GL_TRUE) {
      glLinkProgram(uProgramId); UNIFY_CHECK_GL_ERROR
      glValidateProgram(uProgramId); UNIFY_CHECK_GL_ERROR
      glGetProgramiv(uProgramId, GL_LINK_STATUS, &status); UNIFY_CHECK_GL_ERROR
      if (status != GL_TRUE) {
        glGetProgramInfoLog(uProgramId, sizeof(errorLog), NULL, errorLog); UNIFY_CHECK_GL_ERROR
        UNIFY_ERROR("Unable to link shader program: {}", errorLog);
        glDeleteProgram(uProgramId); UNIFY_CHECK_GL_ERROR
        uProgramId = -1;
      }
    }
  }
  glDeleteShader(vertexShaderId); UNIFY_CHECK_GL_ERROR
  glDeleteShader(fragmentShaderId); UNIFY_CHECK_GL_ERROR
};

Shader::~Shader() {
  glUseProgram(0); UNIFY_CHECK_GL_ERROR
  glDeleteProgram(uProgramId); UNIFY_CHECK_GL_ERROR
};

void Shader::Bind() { glUseProgram(uProgramId);UNIFY_CHECK_GL_ERROR } 
void Shader::Unbind() { glUseProgram(0);UNIFY_CHECK_GL_ERROR }

void Shader::SetUniformInt(const std::string &name, int val) {
  glUseProgram(uProgramId);UNIFY_CHECK_GL_ERROR
  glUniform1i(GetUniformLocation(name), val); UNIFY_CHECK_GL_ERROR
};
void Shader::SetUniformFloat(const std::string &name, float val) {
  glUseProgram(uProgramId); UNIFY_CHECK_GL_ERROR
  glUniform1f(GetUniformLocation(name), val); UNIFY_CHECK_GL_ERROR
};
void Shader::SetUniformFloat2(const std::string &name, float val, float val2) {
  glUseProgram(uProgramId); UNIFY_CHECK_GL_ERROR
  glUniform2f(GetUniformLocation(name), val, val2); UNIFY_CHECK_GL_ERROR
};
void Shader::SetUniformFloat3(const std::string &name, float val, float val2,
                              float val3) {
  glUseProgram(uProgramId); UNIFY_CHECK_GL_ERROR
  glUniform3f(GetUniformLocation(name), val, val2, val3); UNIFY_CHECK_GL_ERROR
};
void Shader::SetUniformFloat4(const std::string &name, float val, float val2,
                              float val3, float val4) {
  glUseProgram(uProgramId); UNIFY_CHECK_GL_ERROR
  glUniform4f(GetUniformLocation(name), val, val2, val3, val4); UNIFY_CHECK_GL_ERROR
};

int Shader::GetUniformLocation(const std::string &name) {
  auto it = uUniformLocations.find(name);
  if (it == uUniformLocations.end()) {
    uUniformLocations[name] = glGetUniformLocation(uProgramId, name.c_str()); UNIFY_CHECK_GL_ERROR
  }
  return uUniformLocations[name];
};
} // namespace unify::graphics