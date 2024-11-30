#pragma once

namespace unify::graphics {
void CheckGLError();
} // namespace unify::graphics

#ifndef UNIFY_CONFIG_RELEASE
#define UNIFY_CHECK_GL_ERROR unify::graphics::CheckGLError();
#else
#define UNIFY_CHECK_GL_ERROR (void)0;
#endif