// gl.h - the OpenGL 3.3 core entry points the backend uses, loaded through SDL at startup.
// Only functions that also exist in OpenGL ES 3.0 are listed, so the same backend can run on WebGL2.
#pragma once
#include <cstddef>
#include <cstdint>
#include <string>

#if defined(_WIN32)
#define DOTD_GLAPI __stdcall
#else
#define DOTD_GLAPI
#endif

typedef unsigned int GLenum;
typedef unsigned int GLuint;
typedef int GLint;
typedef int GLsizei;
typedef float GLfloat;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;

enum : GLenum {
    GL_NO_ERROR = 0,
    GL_FALSE_ = 0,
    GL_TRIANGLES = 0x0004,
    GL_TRIANGLE_STRIP = 0x0005,
    GL_SRC_ALPHA = 0x0302,
    GL_ONE_MINUS_SRC_ALPHA = 0x0303,
    GL_ONE_MINUS_SRC_COLOR = 0x0301,
    GL_ONE = 1,
    GL_ZERO = 0,
    GL_DEPTH_TEST = 0x0B71,
    GL_CULL_FACE = 0x0B44,
    GL_BLEND = 0x0BE2,
    GL_SCISSOR_TEST = 0x0C11,
    GL_UNPACK_ALIGNMENT = 0x0CF5,
    GL_TEXTURE_2D = 0x0DE1,
    GL_UNSIGNED_BYTE = 0x1401,
    GL_FLOAT = 0x1406,
    GL_RGBA = 0x1908,
    GL_VERSION = 0x1F02,
    GL_RENDERER = 0x1F01,
    GL_NEAREST = 0x2600,
    GL_LINEAR = 0x2601,
    GL_TEXTURE_MAG_FILTER = 0x2800,
    GL_TEXTURE_MIN_FILTER = 0x2801,
    GL_TEXTURE_WRAP_S = 0x2802,
    GL_TEXTURE_WRAP_T = 0x2803,
    GL_CLAMP_TO_EDGE = 0x812F,
    GL_RGBA8 = 0x8058,
    GL_TEXTURE0 = 0x84C0,
    GL_ACTIVE_TEXTURE = 0x84E0,
    GL_ARRAY_BUFFER = 0x8892,
    GL_STREAM_DRAW = 0x88E0,
    GL_FRAGMENT_SHADER = 0x8B30,
    GL_VERTEX_SHADER = 0x8B31,
    GL_COMPILE_STATUS = 0x8B81,
    GL_LINK_STATUS = 0x8B82,
    GL_FRAMEBUFFER_COMPLETE = 0x8CD5,
    GL_COLOR_ATTACHMENT0 = 0x8CE0,
    GL_FRAMEBUFFER = 0x8D40,
    GL_COLOR_BUFFER_BIT = 0x00004000,
    GL_DEPTH_BUFFER_BIT = 0x00000100,
    GL_STENCIL_BUFFER_BIT = 0x00000400,
    GL_LINES = 0x0001,
    GL_LINE_STRIP = 0x0003,
    GL_TRIANGLE_FAN = 0x0006,
    GL_NEVER = 0x0200,
    GL_LESS = 0x0201,
    GL_EQUAL = 0x0202,
    GL_LEQUAL = 0x0203,
    GL_GREATER = 0x0204,
    GL_NOTEQUAL = 0x0205,
    GL_GEQUAL = 0x0206,
    GL_ALWAYS = 0x0207,
    GL_SRC_COLOR = 0x0300,
    GL_DST_ALPHA = 0x0304,
    GL_ONE_MINUS_DST_ALPHA = 0x0305,
    GL_DST_COLOR = 0x0306,
    GL_ONE_MINUS_DST_COLOR = 0x0307,
    GL_SRC_ALPHA_SATURATE = 0x0308,
    GL_FRONT = 0x0404,
    GL_BACK = 0x0405,
    GL_CW = 0x0900,
    GL_CCW = 0x0901,
    GL_PACK_ALIGNMENT = 0x0D05,
    GL_UNSIGNED_SHORT = 0x1403,
    GL_EXTENSIONS = 0x1F03,
    GL_RED = 0x1903,
    GL_NEAREST_MIPMAP_NEAREST = 0x2700,
    GL_LINEAR_MIPMAP_NEAREST = 0x2701,
    GL_NEAREST_MIPMAP_LINEAR = 0x2702,
    GL_LINEAR_MIPMAP_LINEAR = 0x2703,
    GL_REPEAT = 0x2901,
    GL_MIRRORED_REPEAT = 0x8370,
    GL_TEXTURE_BASE_LEVEL = 0x813C,
    GL_TEXTURE_MAX_LEVEL = 0x813D,
    GL_TEXTURE_MAX_LOD = 0x813B,
    GL_TEXTURE_LOD_BIAS = 0x8501,
    GL_DEPTH_STENCIL_ATTACHMENT = 0x821A,
    GL_NUM_EXTENSIONS = 0x821D,
    GL_R8 = 0x8229,
    GL_COMPRESSED_RGBA_S3TC_DXT1_EXT = 0x83F1,
    GL_COMPRESSED_RGBA_S3TC_DXT3_EXT = 0x83F2,
    GL_COMPRESSED_RGBA_S3TC_DXT5_EXT = 0x83F3,
    GL_ELEMENT_ARRAY_BUFFER = 0x8893,
    GL_DYNAMIC_DRAW = 0x88E8,
    GL_DEPTH24_STENCIL8 = 0x88F0,
    GL_RENDERBUFFER = 0x8D41,
    GL_UNSIGNED_INT = 0x1405,
    GL_STATIC_DRAW = 0x88E4,
    GL_TEXTURE1 = 0x84C1,
    GL_MAX_VERTEX_ATTRIBS = 0x8869,
    GL_MAX_TEXTURE_SIZE = 0x0D33,
    GL_MAX_RENDERBUFFER_SIZE = 0x84E8,
    // Anti-aliasing (device.h SetAntialiasing): multisampled render buffers resolved by a blit.
    GL_READ_FRAMEBUFFER = 0x8CA8,
    GL_DRAW_FRAMEBUFFER = 0x8CA9,
    GL_MAX_SAMPLES = 0x8D57,
    GL_SAMPLE_ALPHA_TO_COVERAGE = 0x809E,
};

#define DOTD_GL_FUNCTIONS(X)                                                                            \
    X(void, glViewport, (GLint x, GLint y, GLsizei w, GLsizei h))                                       \
    X(void, glScissor, (GLint x, GLint y, GLsizei w, GLsizei h))                                        \
    X(void, glClearColor, (GLfloat r, GLfloat g, GLfloat b, GLfloat a))                                 \
    X(void, glClear, (GLbitfield mask))                                                                 \
    X(void, glFinish, ())                                                                               \
    X(void, glFlush, ())                                                                                \
    X(void, glColorMask, (GLboolean r, GLboolean g, GLboolean b, GLboolean a))                          \
    X(void, glEnable, (GLenum cap))                                                                     \
    X(void, glDisable, (GLenum cap))                                                                    \
    X(void, glBlendFunc, (GLenum s, GLenum d))                                                          \
    X(GLenum, glGetError, (void))                                                                       \
    X(const unsigned char*, glGetString, (GLenum name))                                                 \
    X(void, glPixelStorei, (GLenum pname, GLint param))                                                 \
    X(void, glGenTextures, (GLsizei n, GLuint* t))                                                      \
    X(void, glDeleteTextures, (GLsizei n, const GLuint* t))                                             \
    X(void, glBindTexture, (GLenum target, GLuint t))                                                   \
    X(void, glActiveTexture, (GLenum unit))                                                             \
    X(void, glTexImage2D, (GLenum target, GLint level, GLint ifmt, GLsizei w, GLsizei h, GLint border,  \
                           GLenum fmt, GLenum type, const void* data))                                  \
    X(void, glTexParameteri, (GLenum target, GLenum pname, GLint param))                                \
    X(void, glTexParameterf, (GLenum target, GLenum pname, GLfloat param))                              \
    X(void, glGenFramebuffers, (GLsizei n, GLuint* f))                                                  \
    X(void, glDeleteFramebuffers, (GLsizei n, const GLuint* f))                                         \
    X(void, glBindFramebuffer, (GLenum target, GLuint f))                                               \
    X(void, glFramebufferTexture2D, (GLenum target, GLenum att, GLenum textarget, GLuint t, GLint lvl)) \
    X(GLenum, glCheckFramebufferStatus, (GLenum target))                                                \
    X(GLuint, glCreateShader, (GLenum type))                                                            \
    X(void, glShaderSource, (GLuint s, GLsizei n, const GLchar* const* src, const GLint* len))          \
    X(void, glCompileShader, (GLuint s))                                                                \
    X(void, glGetShaderiv, (GLuint s, GLenum pname, GLint* v))                                          \
    X(void, glGetShaderInfoLog, (GLuint s, GLsizei max, GLsizei* len, GLchar* log))                     \
    X(void, glDeleteShader, (GLuint s))                                                                 \
    X(GLuint, glCreateProgram, (void))                                                                  \
    X(void, glAttachShader, (GLuint p, GLuint s))                                                       \
    X(void, glBindAttribLocation, (GLuint p, GLuint index, const GLchar* name))                         \
    X(void, glLinkProgram, (GLuint p))                                                                  \
    X(void, glGetProgramiv, (GLuint p, GLenum pname, GLint* v))                                         \
    X(void, glGetProgramInfoLog, (GLuint p, GLsizei max, GLsizei* len, GLchar* log))                    \
    X(void, glDeleteProgram, (GLuint p))                                                                \
    X(void, glUseProgram, (GLuint p))                                                                   \
    X(GLint, glGetUniformLocation, (GLuint p, const GLchar* name))                                      \
    X(void, glUniform1i, (GLint loc, GLint v))                                                          \
    X(void, glUniform1f, (GLint loc, GLfloat v))                                                        \
    X(void, glUniform4f, (GLint loc, GLfloat a, GLfloat b, GLfloat c, GLfloat d))                       \
    X(void, glGenVertexArrays, (GLsizei n, GLuint* a))                                                  \
    X(void, glDeleteVertexArrays, (GLsizei n, const GLuint* a))                                         \
    X(void, glBindVertexArray, (GLuint a))                                                              \
    X(void, glGenBuffers, (GLsizei n, GLuint* b))                                                       \
    X(void, glDeleteBuffers, (GLsizei n, const GLuint* b))                                              \
    X(void, glBindBuffer, (GLenum target, GLuint b))                                                    \
    X(void, glBufferData, (GLenum target, GLsizeiptr size, const void* data, GLenum usage))             \
    X(void, glVertexAttribPointer, (GLuint i, GLint size, GLenum type, GLboolean norm, GLsizei stride,  \
                                    const void* ptr))                                                   \
    X(void, glEnableVertexAttribArray, (GLuint i))                                                      \
    X(void, glDrawArrays, (GLenum mode, GLint first, GLsizei count))                                    \
    X(void, glDrawElements, (GLenum mode, GLsizei count, GLenum type, const void* indices))             \
    X(void, glBufferSubData, (GLenum target, GLintptr offset, GLsizeiptr size, const void* data))       \
    X(void, glCompressedTexImage2D, (GLenum target, GLint level, GLenum ifmt, GLsizei w, GLsizei h, GLint border, GLsizei size, const void* data))\
    X(void, glTexSubImage2D, (GLenum target, GLint level, GLint x, GLint y, GLsizei w, GLsizei h, GLenum fmt, GLenum type, const void* data))\
    X(void, glReadPixels, (GLint x, GLint y, GLsizei w, GLsizei h, GLenum fmt, GLenum type, void* data))\
    X(void, glUniformMatrix4fv, (GLint loc, GLsizei n, GLboolean transpose, const GLfloat* v))          \
    X(void, glUniform4fv, (GLint loc, GLsizei n, const GLfloat* v))                                     \
    X(void, glUniform1fv, (GLint loc, GLsizei n, const GLfloat* v))                                     \
    X(void, glUniform2fv, (GLint loc, GLsizei n, const GLfloat* v))                                     \
    X(void, glUniform3fv, (GLint loc, GLsizei n, const GLfloat* v))                                     \
    X(void, glUniformMatrix3fv, (GLint loc, GLsizei n, GLboolean transpose, const GLfloat* v))          \
    X(void, glUniformMatrix3x4fv, (GLint loc, GLsizei n, GLboolean transpose, const GLfloat* v))        \
    X(void, glDepthMask, (GLboolean flag))                                                              \
    X(void, glDepthFunc, (GLenum func))                                                                 \
    X(void, glCullFace, (GLenum mode))                                                                  \
    X(void, glFrontFace, (GLenum mode))                                                                 \
    X(void, glGetIntegerv, (GLenum pname, GLint* v))                                                    \
    X(const unsigned char*, glGetStringi, (GLenum name, GLuint index))                                  \
    X(void, glGenRenderbuffers, (GLsizei n, GLuint* r))                                                 \
    X(void, glDeleteRenderbuffers, (GLsizei n, const GLuint* r))                                        \
    X(void, glBindRenderbuffer, (GLenum target, GLuint r))                                              \
    X(void, glRenderbufferStorage, (GLenum target, GLenum ifmt, GLsizei w, GLsizei h))                  \
    X(void, glFramebufferRenderbuffer, (GLenum target, GLenum att, GLenum rbtarget, GLuint r))\
    X(void, glRenderbufferStorageMultisample, (GLenum target, GLsizei samples, GLenum ifmt, GLsizei w, GLsizei h))\
    X(void, glBlitFramebuffer, (GLint sx0, GLint sy0, GLint sx1, GLint sy1, GLint dx0, GLint dy0, GLint dx1, GLint dy1,\
                                GLbitfield mask, GLenum filter))\
    X(void, glVertexAttrib4f, (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w))\
    X(void, glDisableVertexAttribArray, (GLuint index))\
    X(void, glDrawRangeElements, (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices))

namespace dotd::gfx::gl {
#define DOTD_GL_DECLARE(ret, name, args) typedef ret(DOTD_GLAPI* PFN_##name) args; extern PFN_##name name;
DOTD_GL_FUNCTIONS(DOTD_GL_DECLARE)
#undef DOTD_GL_DECLARE

// Loads every entry point; false (with a log line) if one is missing.
bool Load(void* (*getProc)(const char* name));

// The backend's shaders are written in GLSL 3.30 core restricted to what GLSL ES 3.00 has. This returns the
// source for the context in use: unchanged on desktop GL; on WebGL2 the version line becomes "#version 300 es"
// with the default precisions ES asks for (highp, as desktop GL computes).
std::string ShaderSourceForContext(const char* glsl330);
}  // namespace dotd::gfx::gl
