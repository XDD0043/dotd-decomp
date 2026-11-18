#include "platform/gfx/gl.h"

#include <cstdlib>
#include <cstring>

#include "platform/log.h"

namespace dotd::gfx::gl {

#define DOTD_GL_DEFINE(ret, name, args) PFN_##name name = nullptr;
DOTD_GL_FUNCTIONS(DOTD_GL_DEFINE)
#undef DOTD_GL_DEFINE

bool Load(void* (*getProc)(const char* name)) {
    bool ok = true;
#define DOTD_GL_LOAD(ret, name, args)                                    \
    name = reinterpret_cast<PFN_##name>(getProc(#name));                 \
    if (!name) {                                                          \
        DOTD_LOG("gl: missing entry point %s", #name);                    \
        ok = false;                                                       \
    }
    DOTD_GL_FUNCTIONS(DOTD_GL_LOAD)
#undef DOTD_GL_LOAD
    return ok;
}

std::string ShaderSourceForContext(const char* glsl330) {
#ifdef __EMSCRIPTEN__
    static const char kDesktop[] = "#version 330 core\n";
    static const char kEs[] =
        "#version 300 es\n"
        "precision highp float;\n"
        "precision highp int;\n"
        "precision highp sampler2D;\n"
        "precision highp sampler3D;\n"
        "precision highp samplerCube;\n"
        "precision highp sampler2DShadow;\n";
    const size_t n = sizeof(kDesktop) - 1;
    if (std::strncmp(glsl330, kDesktop, n) == 0) {
        std::string text = std::string(kEs) + (glsl330 + n);
        // DEV (?DOTD_SHADER_SALT=word): a constant no shader uses, named after the word, so the browser's shader
        // cache has never seen any of the texts: the timings of a first visit.
        static const char* const salt = std::getenv("DOTD_SHADER_SALT");
        if (salt != nullptr && *salt != 0) text += std::string("const float dotd_salt_") + salt + " = 1.0;";
        return text;
    }
#endif
    return glsl330;
}

}  // namespace dotd::gfx::gl
