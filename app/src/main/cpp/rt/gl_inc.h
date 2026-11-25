// Cabecalhos do OpenGL ES 3.x: no Android os do NDK; no PC (teste com o Mesa) os do SDL + o que falta do ES 3.
#pragma once
#ifdef __ANDROID__
#include <GLES3/gl32.h>
#else
#define SDL_USE_BUILTIN_OPENGL_DEFINITIONS 1
#include "SDL_opengles2.h"
extern "C" {
GL_APICALL void GL_APIENTRY glTexStorage2D(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
GL_APICALL void GL_APIENTRY glGenQueries(GLsizei, GLuint *);
GL_APICALL void GL_APIENTRY glDeleteQueries(GLsizei, const GLuint *);
GL_APICALL void GL_APIENTRY glBeginQuery(GLenum, GLuint);
GL_APICALL void GL_APIENTRY glEndQuery(GLenum);
GL_APICALL void GL_APIENTRY glGetQueryObjectuiv(GLuint, GLenum, GLuint *);
GL_APICALL void *GL_APIENTRY glMapBufferRange(GLenum, GLintptr, GLsizeiptr, GLbitfield);
GL_APICALL GLboolean GL_APIENTRY glUnmapBuffer(GLenum);
#ifndef GL_ANY_SAMPLES_PASSED
#define GL_ANY_SAMPLES_PASSED 0x8C2F
#define GL_QUERY_RESULT 0x8866
#endif
#ifndef GL_COPY_READ_BUFFER
#define GL_COPY_READ_BUFFER 0x8F36
#endif
#ifndef GL_MAP_READ_BIT
#define GL_MAP_READ_BIT 0x0001
#endif
GL_APICALL const GLubyte *GL_APIENTRY glGetStringi(GLenum, GLuint);
#ifndef GL_NUM_EXTENSIONS
#define GL_NUM_EXTENSIONS 0x821D
#endif
GL_APICALL void GL_APIENTRY glTexStorage3D(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
GL_APICALL void GL_APIENTRY glTexSubImage3D(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
GL_APICALL void GL_APIENTRY glGenSamplers(GLsizei, GLuint *);
GL_APICALL void GL_APIENTRY glBindSampler(GLuint, GLuint);
GL_APICALL void GL_APIENTRY glSamplerParameteri(GLuint, GLenum, GLint);
GL_APICALL void GL_APIENTRY glSamplerParameterf(GLuint, GLenum, GLfloat);
GL_APICALL void GL_APIENTRY glSamplerParameterfv(GLuint, GLenum, const GLfloat *);
GL_APICALL void GL_APIENTRY glBlitFramebuffer(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
GL_APICALL void GL_APIENTRY glDrawBuffers(GLsizei, const GLenum *);
GL_APICALL void GL_APIENTRY glReadBuffer(GLenum);
GL_APICALL void GL_APIENTRY glGenVertexArrays(GLsizei, GLuint *);
GL_APICALL void GL_APIENTRY glBindVertexArray(GLuint);
GL_APICALL void GL_APIENTRY glVertexAttribDivisor(GLuint, GLuint);
GL_APICALL void GL_APIENTRY glDrawElementsInstanced(GLenum, GLsizei, GLenum, const void *, GLsizei);
GL_APICALL void GL_APIENTRY glProgramBinary(GLuint, GLenum, const void *, GLsizei);
GL_APICALL void GL_APIENTRY glGetProgramBinary(GLuint, GLsizei, GLsizei *, GLenum *, void *);
GL_APICALL void GL_APIENTRY glProgramParameteri(GLuint, GLenum, GLint);
}
#ifndef GL_R8
#define GL_R8 0x8229
#define GL_RG8 0x822B
#define GL_RGBA8 0x8058
#define GL_RGB8 0x8051
#define GL_RGB565 0x8D62
#define GL_R16F 0x822D
#define GL_RG16F 0x822F
#define GL_RGBA16F 0x881A
#define GL_R32F 0x822E
#define GL_RG32F 0x8230
#define GL_RGBA32F 0x8814
#define GL_RED 0x1903
#define GL_RG 0x8227
#define GL_HALF_FLOAT 0x140B
#define GL_RG8_SNORM 0x8F95
#define GL_RGBA8_SNORM 0x8F97
#define GL_RGB10_A2 0x8059
#define GL_UNSIGNED_INT_2_10_10_10_REV 0x8368
#define GL_INT_2_10_10_10_REV 0x8D9F
#define GL_DEPTH24_STENCIL8 0x88F0
#define GL_DEPTH_STENCIL 0x84F9
#define GL_UNSIGNED_INT_24_8 0x84FA
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#define GL_TEXTURE_3D 0x806F
#define GL_TEXTURE_WRAP_R 0x8072
#define GL_TEXTURE_MAX_LEVEL 0x813D
#define GL_TEXTURE_BASE_LEVEL 0x813C
#define GL_TEXTURE_MIN_LOD 0x813A
#define GL_TEXTURE_MAX_LOD 0x813B
#define GL_TEXTURE_SWIZZLE_R 0x8E42
#define GL_TEXTURE_SWIZZLE_G 0x8E43
#define GL_TEXTURE_SWIZZLE_B 0x8E44
#define GL_TEXTURE_SWIZZLE_A 0x8E45
#define GL_READ_FRAMEBUFFER 0x8CA8
#define GL_DRAW_FRAMEBUFFER 0x8CA9
#define GL_MIN 0x8007
#define GL_MAX 0x8008
#define GL_CLAMP_TO_BORDER 0x812D
#define GL_TEXTURE_BORDER_COLOR 0x1004
#define GL_COLOR_ATTACHMENT1 0x8CE1
#define GL_COLOR_ATTACHMENT2 0x8CE2
#define GL_COLOR_ATTACHMENT3 0x8CE3
#define GL_GREEN 0x1904
#define GL_BLUE 0x1905
#define GL_UNPACK_ROW_LENGTH 0x0CF2
#endif
#endif
#ifndef GL_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#endif
