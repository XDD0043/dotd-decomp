#include "platform/gfx/gl.h"

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

}  // namespace dotd::gfx::gl
