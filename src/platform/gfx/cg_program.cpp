// cg_program.cpp - see cg_program.h.
#include "platform/gfx/cg_program.h"

#include <cstdlib>
#include <fstream>
#include <map>
#include <memory>

#include "platform/gfx/device.h"
#include "platform/gfx/gl.h"
#include "platform/log.h"

namespace dotd::gfx::cg {
namespace {

Sources g_sources;
bool g_sourcesLoaded = false;

struct ShaderObject {
    uint32_t gl = 0;
    uint32_t id = 0;
    std::string error;
};
std::map<std::string, ShaderObject> g_vertexShaders;  // GLSL text -> compiled shader
std::map<std::string, ShaderObject> g_pixelShaders;
std::map<std::string, std::unique_ptr<Program>> g_programs;           // define list -> program
std::map<std::pair<uint32_t, uint32_t>, uint32_t> g_linked;           // (vertex id, pixel id) -> GL program
Statistics g_stats;

std::string DefineKey(const std::vector<Define>& defines) {
    std::string key;
    for (const Define& d : defines) {
        key += d.name;
        key += '=';
        key += d.value;
        key += ';';
    }
    return key;
}

ShaderObject& Compile(std::map<std::string, ShaderObject>& cache, const std::string& glsl, bool vertex) {
    auto found = cache.find(glsl);
    if (found != cache.end()) return found->second;
    ShaderObject object;
    object.id = static_cast<uint32_t>(cache.size());
    object.gl = gl::glCreateShader(vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    const char* text = glsl.c_str();
    gl::glShaderSource(object.gl, 1, &text, nullptr);
    gl::glCompileShader(object.gl);
    GLint ok = 0;
    gl::glGetShaderiv(object.gl, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[2048];
        gl::glGetShaderInfoLog(object.gl, sizeof log, nullptr, log);
        object.error = std::string(vertex ? "vertex" : "pixel") + " shader: " + log;
        gl::glDeleteShader(object.gl);
        object.gl = 0;
    }
    if (vertex) ++g_stats.vertexShaders;
    else ++g_stats.pixelShaders;
    return cache.emplace(glsl, object).first->second;
}

}  // namespace

bool InitSources(const char* ebootPath, std::string* error) {
    if (g_sourcesLoaded) return true;
    if (!LoadGameSources(ebootPath, &g_sources, error)) return false;
    g_sourcesLoaded = true;
    return true;
}

bool SourcesLoaded() { return g_sourcesLoaded; }
const Sources& GameSources() { return g_sources; }

const Program* GetProgram(const std::vector<Define>& defines) {
    const std::string key = DefineKey(defines);
    auto found = g_programs.find(key);
    if (found != g_programs.end()) return found->second.get();
    ++g_stats.variants;
    std::unique_ptr<Program> program(new Program());
    auto fail = [&](const std::string& why) {
        program->error = why;
        ++g_stats.failures;
        DOTD_LOG("cg: variant failed: %s", why.c_str());
        return g_programs.emplace(key, std::move(program)).first->second.get();
    };
    if (!g_sourcesLoaded) return fail("the Cg sources are not loaded");
    std::string error;
    if (!BuildStage(g_sources, Stage::kVertex, defines, &program->vertex, &error)) return fail("vertex stage: " + error);
    if (!BuildStage(g_sources, Stage::kPixel, defines, &program->pixel, &error)) return fail("pixel stage: " + error);
    if (const char* dumpDir = std::getenv("DOTD_DUMP_GLSL")) {  // DEV: the generated GLSL of every variant, for debugging
        static int dumped = 0;
        const std::string base = std::string(dumpDir) + "/variant" + std::to_string(dumped++);
        std::ofstream(base + ".vs.glsl") << program->vertex.glsl;
        std::ofstream(base + ".fs.glsl") << program->pixel.glsl;
        std::ofstream(base + ".defines.txt") << key;
    }
    if (!IsReady()) {
        // No GL context (headless): translation only; glProgram stays 0 but the interface is filled.
        return g_programs.emplace(key, std::move(program)).first->second.get();
    }
    ShaderObject& vs = Compile(g_vertexShaders, program->vertex.glsl, true);
    ShaderObject& ps = Compile(g_pixelShaders, program->pixel.glsl, false);
    program->vertexShaderId = vs.id;
    program->pixelShaderId = ps.id;
    if (vs.gl == 0) return fail(vs.error);
    if (ps.gl == 0) return fail(ps.error);
    auto link = g_linked.find({vs.id, ps.id});
    if (link != g_linked.end()) {
        program->glProgram = link->second;
    } else {
        const GLuint p = gl::glCreateProgram();
        gl::glAttachShader(p, vs.gl);
        gl::glAttachShader(p, ps.gl);
        gl::glLinkProgram(p);
        GLint ok = 0;
        gl::glGetProgramiv(p, GL_LINK_STATUS, &ok);
        if (!ok) {
            char log[2048];
            gl::glGetProgramInfoLog(p, sizeof log, nullptr, log);
            gl::glDeleteProgram(p);
            return fail(std::string("link: ") + log);
        }
        // The samplers' texture units are their register numbers.
        gl::glUseProgram(p);
        for (const SamplerInfo& sampler : program->pixel.samplers) {
            const GLint loc = gl::glGetUniformLocation(p, sampler.name.c_str());
            if (loc >= 0) gl::glUniform1i(loc, sampler.unit);
        }
        gl::glUseProgram(0);
        g_linked[{vs.id, ps.id}] = p;
        ++g_stats.linkedPrograms;
        program->glProgram = p;
    }
    return g_programs.emplace(key, std::move(program)).first->second.get();
}

Statistics GetStatistics() { return g_stats; }

void DestroyPrograms() {
    if (IsReady()) {
        for (auto& entry : g_linked) gl::glDeleteProgram(entry.second);
        for (auto& entry : g_vertexShaders) {
            if (entry.second.gl != 0) gl::glDeleteShader(entry.second.gl);
        }
        for (auto& entry : g_pixelShaders) {
            if (entry.second.gl != 0) gl::glDeleteShader(entry.second.gl);
        }
    }
    g_vertexShaders.clear();
    g_pixelShaders.clear();
    g_programs.clear();
    g_linked.clear();
    g_stats = Statistics();
}

}  // namespace dotd::gfx::cg
