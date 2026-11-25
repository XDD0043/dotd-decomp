// cg_program.cpp - see cg_program.h.
#include "platform/gfx/cg_program.h"

#include <cctype>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>

#include "platform/gfx/device.h"
#include "platform/gfx/gl.h"
#include "platform/gfx/mesh.h"
#include "platform/gfx/perf.h"
#include "platform/hostfs.h"
#include "platform/log.h"

namespace dotd::gfx::cg {
namespace {

// ---- the pixel shaders at half precision (DOTD_FP16=1) ---------------------------------------------------------
// The PS3 game compiles its pixel shaders with -fastprecision -fastmath (ShaderGen_BuildCompilerArgs_maybe 0xfe518
// builds the arguments, ShaderGen_CompileCgSource_maybe 0xfe818 hands them to the built-in Cg compiler for
// sce_fp_rsx): float arithmetic at the RSX's faster 16-bit precision. GLSL ES says the same with mediump, which phone
// GPUs run at twice the rate (a desktop GPU ignores it). The translated pixel GLSL gets a default "precision mediump
// float" and stays highp where 16 bits would show:
//   - the varyings and every struct field (the interpolated texture coordinates and positions as they come in);
//   - every vec2: the uber-shader's 2-vectors are texture coordinates (its helpers take them as float2 parameters
//     and locals: GetNormalTextureVector(float2 texCoord), f2Basetex, ...);
//   - every uniform but a few colours and directions (kHalfUniforms), and those too when the vertex stage declares
//     them (GLSL ES: a uniform of both stages has one precision).
// Integers and samplers keep the header's highp. Off unless DOTD_FP16=1 (README "Half precision").
const std::set<std::string> kHalfUniforms = {
    "u_f4PixelDirLight", "u_f4PixelDirLightColor", "u_f4PixelAmbientColor", "u_f4PixelPointLightColor",
    "u_f4SpecularColor", "u_f4PixelMaterialColor", "u_f4PixelMatFx", "u_f4SpecialLight", "u_f3MinMaxShadow",
    "u_af4Gauss5x5", "dotd_alphaRef",
};

bool HalfPrecision() {
    static const int on = [] {
        const char* env = std::getenv("DOTD_FP16");
        return env != nullptr && std::strcmp(env, "1") == 0 ? 1 : 0;
    }();
    return on == 1;
}

bool IsFloatType(const std::string& t) { return t == "float" || t.rfind("vec", 0) == 0 || t.rfind("mat", 0) == 0; }

// "  TYPE name..." after `prefix` (e.g. "uniform "): the type and the name (empty when the line is not one).
void SplitDeclaration(const std::string& line, size_t at, std::string* type, std::string* name) {
    type->clear();
    name->clear();
    const size_t t0 = line.find_first_not_of(' ', at);
    if (t0 == std::string::npos) return;
    const size_t t1 = line.find(' ', t0);
    if (t1 == std::string::npos) return;
    *type = line.substr(t0, t1 - t0);
    const size_t n0 = line.find_first_not_of(' ', t1);
    size_t n1 = n0;
    while (n1 < line.size() && (std::isalnum(static_cast<unsigned char>(line[n1])) != 0 || line[n1] == '_')) ++n1;
    if (n0 != std::string::npos) *name = line.substr(n0, n1 - n0);
}

// Every "vec2 <identifier>" (a declaration, a parameter, a return type; not a constructor "vec2(") as highp.
std::string HighpVec2(const std::string& line) {
    std::string out;
    size_t i = 0;
    while (i < line.size()) {
        const size_t at = line.find("vec2", i);
        if (at == std::string::npos) break;
        const bool startsWord = at == 0 || !(std::isalnum(static_cast<unsigned char>(line[at - 1])) != 0 || line[at - 1] == '_');
        size_t next = at + 4;
        const bool endsWord = next >= line.size() || !(std::isalnum(static_cast<unsigned char>(line[next])) != 0 || line[next] == '_');
        while (next < line.size() && line[next] == ' ') ++next;
        const bool declares = next < line.size() && (std::isalpha(static_cast<unsigned char>(line[next])) != 0 || line[next] == '_');
        const bool qualified = at >= 6 && line.compare(at - 6, 6, "highp ") == 0;
        out += line.substr(i, at - i);
        if (startsWord && endsWord && declares && !qualified) out += "highp ";
        out += "vec2";
        i = at + 4;
    }
    return out + line.substr(i);
}

// The pixel GLSL with the half precision above; `vertexUniforms` are the vertex stage's.
std::string PixelAtHalfPrecision(const std::string& glsl, const std::vector<UniformInfo>& vertexUniforms) {
    std::set<std::string> shared;
    for (const UniformInfo& u : vertexUniforms) shared.insert(u.name);
    std::istringstream in(glsl);
    std::string line, out, type, name;
    bool inStruct = false;
    while (std::getline(in, line)) {
        if (line.rfind("#version", 0) == 0) {
            out += line + "\nprecision mediump float;\n";
            continue;
        }
        if (line.rfind("struct ", 0) == 0) {
            inStruct = true;
        } else if (inStruct && line.rfind("};", 0) == 0) {
            inStruct = false;
        } else if (inStruct) {
            SplitDeclaration(line, 0, &type, &name);
            if (IsFloatType(type)) line.insert(line.find(type), "highp ");
        } else if (line.rfind("uniform ", 0) == 0) {
            SplitDeclaration(line, 8, &type, &name);
            const bool half = kHalfUniforms.count(name) != 0 && shared.count(name) == 0;
            if (IsFloatType(type) && !half) line.insert(8, "highp ");
        } else if (line.rfind("in ", 0) == 0) {
            SplitDeclaration(line, 3, &type, &name);
            if (IsFloatType(type)) line.insert(3, "highp ");
        }
        out += HighpVec2(line) + "\n";
    }
    return out;
}

// After both stages of a variant are translated.
void ApplyPrecision(Program* program) {
    if (HalfPrecision()) program->pixel.glsl = PixelAtHalfPrecision(program->pixel.glsl, program->vertex.uniforms);
}

Sources g_sources;
bool g_sourcesLoaded = false;

struct ShaderObject {
    uint32_t gl = 0;
    uint32_t id = 0;
    std::string error;
    bool unchecked = false;  // background builds: compiled, its status not asked yet
};
std::map<std::string, ShaderObject> g_vertexShaders;  // GLSL text -> compiled shader
std::map<std::string, ShaderObject> g_pixelShaders;
std::map<std::string, std::unique_ptr<Program>> g_programs;           // define list -> program
std::map<std::pair<uint32_t, uint32_t>, uint32_t> g_linked;           // (vertex id, pixel id) -> GL program
Statistics g_stats;
uint32_t g_generation = 0;  // DestroyPrograms calls (ProgramsGeneration)

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

// ---- the variant list (cg_program.h) ----------------------------------------------------------------------------------
constexpr const char* kVariantListHeader = "dotd-shader-variants 1";
constexpr size_t kVariantListMaxLine = 8192;
constexpr size_t kVariantListMaxEntries = 20000;
bool g_listChecked = false;   // the environment variable was looked at
bool g_listOn = false;
std::string g_listPath;
int g_listGroup = -1;
std::map<int, std::vector<std::string>> g_listByGroup;      // group -> define keys, in file order
std::set<std::pair<int, std::string>> g_listEntries;         // what the file holds

std::string DefaultVariantListPath() {
    namespace fs = std::filesystem;
    if (const char* local = std::getenv("LOCALAPPDATA")) {
        if (*local != 0) return (fs::path(local) / "dotd" / "cache" / "shader-variants.txt").string();
    }
    if (const char* home = std::getenv("HOME")) {
        if (*home != 0) return (fs::path(home) / ".cache" / "dotd" / "shader-variants.txt").string();
    }
    return std::string();
}

// "name=value;name=value;" (DefineKey) back into the define list; false for anything else.
bool ParseDefineKey(const std::string& key, std::vector<Define>* defines) {
    defines->clear();
    size_t at = 0;
    while (at < key.size()) {
        const size_t end = key.find(';', at);
        if (end == std::string::npos) return false;
        const size_t equals = key.find('=', at);
        if (equals == std::string::npos || equals > end || equals == at) return false;
        Define define;
        define.name = key.substr(at, equals - at);
        define.value = key.substr(equals + 1, end - equals - 1);
        defines->push_back(std::move(define));
        at = end + 1;
    }
    return !defines->empty();
}

void LoadVariantList() {
    g_listByGroup.clear();
    g_listEntries.clear();
    std::ifstream file(g_listPath);
    std::string line;
    if (!file || !std::getline(file, line)) return;  // no file yet
    if (!line.empty() && line.back() == '\r') line.pop_back();
    if (line != kVariantListHeader) {
        DOTD_LOG("cg: %s is not a variant list of this version: started again", g_listPath.c_str());
        file.close();
        std::error_code ignored;
        std::filesystem::remove(g_listPath, ignored);
        return;
    }
    std::vector<Define> defines;
    while (std::getline(file, line) && g_listEntries.size() < kVariantListMaxEntries) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty() || line.size() > kVariantListMaxLine) continue;
        const size_t tab = line.find('\t');
        if (tab == std::string::npos || tab == 0) continue;
        char* end = nullptr;
        const long group = std::strtol(line.c_str(), &end, 10);
        if (end != line.c_str() + tab || group < 0 || group > 100000) continue;
        std::string key = line.substr(tab + 1);
        if (!ParseDefineKey(key, &defines)) continue;
        if (g_listEntries.emplace(static_cast<int>(group), key).second) g_listByGroup[static_cast<int>(group)].push_back(std::move(key));
    }
}

// DOTD_SHADER_LIST (once): a path turns the list on, "off" keeps it off whatever EnableVariantList is given.
bool g_listForcedOff = false;
void CheckVariantListEnvironment() {
    if (g_listChecked) return;
    g_listChecked = true;
    const char* env = std::getenv("DOTD_SHADER_LIST");
    if (env == nullptr || *env == 0) return;
    if (std::string(env) == "off") {
        g_listForcedOff = true;
        return;
    }
    g_listPath = env;
    g_listOn = true;
    LoadVariantList();
}

// A variant was built: listed under the current group when it is not there yet (appended to the file at once: the run
// may end without a shutdown).
void NoteVariantBuilt(const std::string& key) {
    CheckVariantListEnvironment();
    if (!g_listOn || g_listGroup < 0 || key.size() > kVariantListMaxLine || g_listEntries.size() >= kVariantListMaxEntries) return;
    if (!g_listEntries.emplace(g_listGroup, key).second) return;
    g_listByGroup[g_listGroup].push_back(key);
    std::error_code ignored;
    const std::filesystem::path path(g_listPath);
    if (path.has_parent_path()) std::filesystem::create_directories(path.parent_path(), ignored);
    const bool fresh = !std::filesystem::exists(path, ignored);
    std::ofstream file(g_listPath, std::ios::app);
    if (!file) return;
    if (fresh) file << kVariantListHeader << '\n';
    file << g_listGroup << '\t' << key << '\n';
}

ShaderObject& Compile(std::map<std::string, ShaderObject>& cache, const std::string& glsl, bool vertex) {
    auto found = cache.find(glsl);
    if (found != cache.end()) return found->second;
    const perf::Scope scope(perf::kWorkShaderCompile);
    ShaderObject object;
    object.id = static_cast<uint32_t>(cache.size());
    object.gl = gl::glCreateShader(vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    const std::string source = gl::ShaderSourceForContext(glsl.c_str());
    const char* text = source.c_str();
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

// ---- background builds (cg_program.h) -----------------------------------------------------------------------------------
#ifdef __EMSCRIPTEN__
constexpr GLenum kCompletionStatus = 0x91B1;  // GL_COMPLETION_STATUS_KHR
constexpr double kStartBudgetMs = 8.0;        // per frame: the translations of the variants first met in play

struct Build {
    Program* program = nullptr;  // in g_programs
    std::vector<Define> defines;
    bool started = false;        // translated, its shaders compiling, its program linking
    bool finished = false;       // ready or failed
    ShaderObject* vs = nullptr;
    ShaderObject* ps = nullptr;
    GLuint link = 0;             // the program being linked (shared by the builds of the same shader pair)
};
std::list<Build> g_builds;
std::map<std::pair<uint32_t, uint32_t>, GLuint> g_linking;           // (vertex id, pixel id) -> program being linked
std::map<std::pair<uint32_t, uint32_t>, std::string> g_failedLinks;  // pairs that did not link
double g_startedMs = 0.0;     // this frame's StartBuild time
int g_backgroundBuilds = -1;  // -1: not looked yet

bool BackgroundBuilds() {
    if (g_backgroundBuilds < 0) {
        g_backgroundBuilds = 0;
        GLint count = 0;
        gl::glGetIntegerv(GL_NUM_EXTENSIONS, &count);
        for (GLint i = 0; i < count; ++i) {
            const char* ext = reinterpret_cast<const char*>(gl::glGetStringi(GL_EXTENSIONS, static_cast<GLuint>(i)));
            if (ext != nullptr && std::strcmp(ext, "GL_KHR_parallel_shader_compile") == 0) g_backgroundBuilds = 1;
        }
        DOTD_LOG("cg: shader programs are built %s",
                 g_backgroundBuilds ? "in the background (KHR_parallel_shader_compile)" : "at their first use");
        if (HalfPrecision()) DOTD_LOG("cg: pixel shaders at half precision (DOTD_FP16=1)");
        const char* alphaTest = std::getenv("DOTD_ALPHATEST");
        if (alphaTest != nullptr && std::strcmp(alphaTest, "0") == 0) {
            DOTD_LOG("cg: no alpha test in the pixel shaders (DOTD_ALPHATEST=0: a measurement, cut-outs draw solid)");
        }
    }
    return g_backgroundBuilds == 1;
}

void FailBuild(Build& b, const std::string& why) {
    b.program->error = why;
    b.program->building = false;
    b.finished = true;
    ++g_stats.failures;
    DOTD_LOG("cg: variant failed: %s", why.c_str());
}

// A shader object compiling: nothing is asked back, so the browser compiles it beside the game.
ShaderObject& CompileNoWait(std::map<std::string, ShaderObject>& cache, const std::string& glsl, bool vertex) {
    auto found = cache.find(glsl);
    if (found != cache.end()) return found->second;
    ShaderObject object;
    object.id = static_cast<uint32_t>(cache.size());
    object.gl = gl::glCreateShader(vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    const std::string source = gl::ShaderSourceForContext(glsl.c_str());
    const char* text = source.c_str();
    gl::glShaderSource(object.gl, 1, &text, nullptr);
    gl::glCompileShader(object.gl);
    object.unchecked = true;
    if (vertex) ++g_stats.vertexShaders;
    else ++g_stats.pixelShaders;
    return cache.emplace(glsl, object).first->second;
}

void CheckShader(ShaderObject& object, bool vertex) {
    if (!object.unchecked) return;
    object.unchecked = false;
    GLint ok = 0;
    gl::glGetShaderiv(object.gl, GL_COMPILE_STATUS, &ok);
    if (ok) return;
    char log[2048];
    gl::glGetShaderInfoLog(object.gl, sizeof log, nullptr, log);
    object.error = std::string(vertex ? "vertex" : "pixel") + " shader: " + log;
    gl::glDeleteShader(object.gl);
    object.gl = 0;
}

// The variant translated and handed to the browser: its two shaders compile and its program links from here on.
void StartBuild(Build& b) {
    const auto start = std::chrono::steady_clock::now();
    const perf::Scope scope(perf::kWorkShader);
    b.started = true;
    std::string error;
    bool translated = false;
    {
        const perf::Scope translate(perf::kWorkShaderTranslate);
        translated = BuildStage(g_sources, Stage::kVertex, b.defines, &b.program->vertex, &error);
        if (!translated) error = "vertex stage: " + error;
        if (translated) {
            translated = BuildStage(g_sources, Stage::kPixel, b.defines, &b.program->pixel, &error);
            if (!translated) error = "pixel stage: " + error;
            if (translated) ApplyPrecision(b.program);
        }
    }
    if (!translated) {
        FailBuild(b, error);
    } else {
        b.vs = &CompileNoWait(g_vertexShaders, b.program->vertex.glsl, true);
        b.ps = &CompileNoWait(g_pixelShaders, b.program->pixel.glsl, false);
        b.program->vertexShaderId = b.vs->id;
        b.program->pixelShaderId = b.ps->id;
        const std::pair<uint32_t, uint32_t> pair(b.vs->id, b.ps->id);
        if (b.vs->gl == 0) {
            FailBuild(b, b.vs->error);
        } else if (b.ps->gl == 0) {
            FailBuild(b, b.ps->error);
        } else if (g_linked.count(pair) == 0 && g_failedLinks.count(pair) == 0) {
            auto linking = g_linking.find(pair);
            if (linking == g_linking.end()) {
                const GLuint p = gl::glCreateProgram();
                gl::glAttachShader(p, b.vs->gl);
                gl::glAttachShader(p, b.ps->gl);
                gl::glLinkProgram(p);
                linking = g_linking.emplace(pair, p).first;
            }
            b.link = linking->second;
        }
    }
    g_startedMs += std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count();
}

// Completes a build the browser has finished (`wait`: whether it has or not, waiting for it). True when the build
// is over, ready or failed.
bool FinishBuild(Build& b, bool wait) {
    if (b.finished) return true;
    if (!b.started) {
        if (!wait) return false;
        StartBuild(b);
        if (b.finished) return true;
    }
    const std::pair<uint32_t, uint32_t> pair(b.vs->id, b.ps->id);
    auto linked = g_linked.find(pair);
    if (linked == g_linked.end()) {
        const auto failed = g_failedLinks.find(pair);
        if (failed != g_failedLinks.end()) {
            FailBuild(b, failed->second);
            return true;
        }
        if (!wait) {
            GLint complete = 0;
            gl::glGetProgramiv(b.link, kCompletionStatus, &complete);
            if (!complete) return false;
        }
        const perf::Scope scope(perf::kWorkShader);
        const perf::Scope linkScope(perf::kWorkShaderLink);
        CheckShader(*b.vs, true);
        CheckShader(*b.ps, false);
        std::string error = b.vs->gl == 0 ? b.vs->error : b.ps->gl == 0 ? b.ps->error : std::string();
        if (error.empty()) {
            GLint ok = 0;
            gl::glGetProgramiv(b.link, GL_LINK_STATUS, &ok);
            if (!ok) {
                char log[2048];
                gl::glGetProgramInfoLog(b.link, sizeof log, nullptr, log);
                error = std::string("link: ") + log;
            }
        }
        g_linking.erase(pair);
        if (!error.empty()) {
            gl::glDeleteProgram(b.link);
            g_failedLinks[pair] = error;
            FailBuild(b, error);
            return true;
        }
        // The samplers' texture units are their register numbers.
        GlUseProgram(b.link);  // (stays current: mesh.h)
        for (const SamplerInfo& sampler : b.program->pixel.samplers) {
            const GLint loc = gl::glGetUniformLocation(b.link, sampler.name.c_str());
            if (loc >= 0) gl::glUniform1i(loc, sampler.unit);
        }
        linked = g_linked.emplace(pair, b.link).first;
        ++g_stats.linkedPrograms;
    }
    b.program->glProgram = linked->second;
    b.program->building = false;
    b.finished = true;
    return true;
}
#endif  // __EMSCRIPTEN__

}  // namespace

void PollBuilds() {
#ifdef __EMSCRIPTEN__
    g_startedMs = 0.0;
    if (g_builds.empty()) return;
    for (auto it = g_builds.begin(); it != g_builds.end();) {
        if (FinishBuild(*it, false)) it = g_builds.erase(it);
        else ++it;
    }
    for (Build& b : g_builds) {
        if (b.started) continue;
        if (g_startedMs >= kStartBudgetMs) break;
        StartBuild(b);
    }
#endif
}

void FlushBuilds() {
#ifdef __EMSCRIPTEN__
    // Everything handed to the browser first (it builds several at a time), then each one waited for.
    for (Build& b : g_builds) {
        if (!b.started && !b.finished) StartBuild(b);
    }
    for (Build& b : g_builds) FinishBuild(b, true);
    g_builds.clear();
#endif
}

std::string GameExecutablePath(const std::string& usrdir) {
    const std::string elf = usrdir + "/EBOOT.elf";
    dotd::platform::hostfs::Info info;
    if (dotd::platform::hostfs::Stat(elf, &info)) return elf;
    return usrdir + "/EBOOT.BIN";
}

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
#ifdef __EMSCRIPTEN__
    if (IsReady() && g_sourcesLoaded && BackgroundBuilds()) {
        NoteVariantBuilt(key);  // (the variant list, cg_program.h)
        ++g_stats.variants;
        Program* program = g_programs.emplace(key, std::unique_ptr<Program>(new Program())).first->second.get();
        program->building = true;
        g_builds.emplace_back();
        Build& b = g_builds.back();
        b.program = program;
        b.defines = defines;
        if (g_startedMs < kStartBudgetMs) StartBuild(b);  // (else PollBuilds starts it in a later frame)
        return program;
    }
#endif
    const perf::Scope scope(perf::kWorkShader);
    if (IsReady()) NoteVariantBuilt(key);  // (the variant list, cg_program.h)
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
    {
        const perf::Scope translate(perf::kWorkShaderTranslate);
        if (!BuildStage(g_sources, Stage::kVertex, defines, &program->vertex, &error)) return fail("vertex stage: " + error);
        if (!BuildStage(g_sources, Stage::kPixel, defines, &program->pixel, &error)) return fail("pixel stage: " + error);
        ApplyPrecision(program.get());
    }
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
        const perf::Scope linkScope(perf::kWorkShaderLink);
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
        GlUseProgram(p);  // (stays current: mesh.h)
        for (const SamplerInfo& sampler : program->pixel.samplers) {
            const GLint loc = gl::glGetUniformLocation(p, sampler.name.c_str());
            if (loc >= 0) gl::glUniform1i(loc, sampler.unit);
        }
        g_linked[{vs.id, ps.id}] = p;
        ++g_stats.linkedPrograms;
        program->glProgram = p;
    }
    return g_programs.emplace(key, std::move(program)).first->second.get();
}

Statistics GetStatistics() { return g_stats; }

void DestroyPrograms() {
#ifdef __EMSCRIPTEN__
    if (IsReady()) {
        for (auto& entry : g_linking) gl::glDeleteProgram(entry.second);
    }
    g_builds.clear();
    g_linking.clear();
    g_failedLinks.clear();
#endif
    if (IsReady()) {
        ForgetPrograms();  // (mesh.h: the backend's per-program state and the current program)
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
    ++g_generation;
}

uint32_t ProgramsGeneration() { return g_generation; }

void EnableVariantList(const char* path) {
    CheckVariantListEnvironment();
    if (g_listForcedOff || g_listOn) return;  // the environment variable's choice stays
    g_listPath = path != nullptr && *path != 0 ? std::string(path) : DefaultVariantListPath();
    if (g_listPath.empty()) return;
    g_listOn = true;
    LoadVariantList();
}

void SetVariantGroup(int group) { g_listGroup = group; }

int PrewarmVariantGroup(int group, void (*built)(const Program* program)) {
    CheckVariantListEnvironment();
    if (!g_listOn || !IsReady() || !g_sourcesLoaded) return 0;
    const auto listed = g_listByGroup.find(group);
    if (listed == g_listByGroup.end()) return 0;
    const std::vector<std::string> keys = listed->second;  // (a copy: GetProgram may add to the list)
    const auto start = std::chrono::steady_clock::now();
    int count = 0;
    std::vector<Define> defines;
#ifdef __EMSCRIPTEN__
    std::vector<const Program*> programs;  // (background builds: started in the loop, all waited for after it)
#endif
    for (const std::string& key : keys) {
        if (g_programs.find(key) != g_programs.end()) continue;
        if (!ParseDefineKey(key, &defines)) continue;
        const Program* program = GetProgram(defines);
        ++count;
#ifdef __EMSCRIPTEN__
        programs.push_back(program);
#else
        if (built != nullptr && program != nullptr && program->glProgram != 0) built(program);
#endif
    }
#ifdef __EMSCRIPTEN__
    FlushBuilds();
    for (const Program* program : programs) {
        if (built != nullptr && program != nullptr && program->glProgram != 0) built(program);
    }
#endif
    if (count != 0) {
        const double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count();
        DOTD_LOG("cg: %d shader variant(s) of group %d built ahead in %.0f ms (%s)", count, group, ms, g_listPath.c_str());
    }
    return count;
}

}  // namespace dotd::gfx::cg
