// mesh.cpp - see mesh.h. New platform code (the job of PSGL's buffer and attribute calls).
#include "platform/gfx/mesh.h"

#include <cstring>
#include <map>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "platform/gfx/gl.h"
#include "platform/gfx/perf.h"
#include "platform/log.h"

using namespace dotd::gfx::gl;

namespace dotd::gfx {
namespace {

struct Mesh {
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ibo = 0;
    uint32_t enabledMask = 0;  // shader input slots with an attribute array
    uint32_t stride = 0;       // the layout CreateMesh was given (UpdateMesh)
    std::vector<MeshAttribute> attributes;
    bool alive = false;        // false: no such mesh (never made, or destroyed)
};
// The meshes by id (perf: an array, a draw's lookup is an index; it was a hash map). Ids start at 1 and are never
// given out again, so a destroyed mesh's entry stays as a dead one.
std::vector<Mesh> g_meshes(1);
uint32_t g_nextMesh = 1;

Mesh* FindMesh(uint32_t id) {
    if (id == 0 || id >= g_meshes.size() || !g_meshes[id].alive) return nullptr;
    return &g_meshes[id];
}

uint32_t AddMesh(Mesh&& mesh) {
    const uint32_t id = g_nextMesh++;
    if (g_meshes.size() <= id) g_meshes.resize(static_cast<size_t>(id) + 1);
    mesh.alive = true;
    g_meshes[id] = std::move(mesh);
    return id;
}

// The constants of the shader input slots 0..15 as DrawMesh last set them (mesh.h ForgetVertexAttribDefaults).
float g_attribDefault[16][4];
uint32_t g_attribKnown = 0;  // bit s: g_attribDefault[s] is slot s's current value
// perf: the `defaults` table DrawMesh was last given and the slots that hold that table's values now: a draw whose
// array-less slots are all among them sets nothing and compares nothing. (The callers' tables are constants.)
const float (*g_defaultsTable)[4] = nullptr;
uint32_t g_defaultsApplied = 0;  // a subset of g_attribKnown

// The stream meshes (StreamMesh), one per attribute layout.
struct StreamLayout {
    uint32_t stride = 0;
    std::vector<MeshAttribute> attributes;
    uint32_t id = 0;  // in g_meshes
    std::vector<uint32_t> indices;  // what the index buffer holds
};
std::vector<StreamLayout> g_streamMeshes;

bool SameLayout(const StreamLayout& s, uint32_t stride, const MeshAttribute* attributes, int attributeCount) {
    if (s.stride != stride || s.attributes.size() != static_cast<size_t>(attributeCount)) return false;
    for (int i = 0; i < attributeCount; ++i) {
        const MeshAttribute& a = s.attributes[static_cast<size_t>(i)];
        const MeshAttribute& b = attributes[i];
        if (a.location != b.location || a.components != b.components || a.normalizedBytes != b.normalizedBytes ||
            a.offset != b.offset) {
            return false;
        }
    }
    return true;
}

}  // namespace

uint32_t CreateMesh(const void* vertices, size_t vertexBytes, uint32_t stride, const uint32_t* indices, size_t indexCount,
                    const MeshAttribute* attributes, int attributeCount) {
    if (!IsReady() || vertices == nullptr || vertexBytes == 0) return 0;
    const perf::Scope scope(perf::kWorkMesh);
    Mesh mesh;
    glGenVertexArrays(1, &mesh.vao);
    GlBindVertexArray(mesh.vao);
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertexBytes), vertices, GL_STATIC_DRAW);
    for (int i = 0; i < attributeCount; ++i) {
        const MeshAttribute& a = attributes[i];
        glEnableVertexAttribArray(a.location);
        glVertexAttribPointer(a.location, a.components, a.normalizedBytes ? GL_UNSIGNED_BYTE : GL_FLOAT,
                              a.normalizedBytes ? 1 : 0, static_cast<GLsizei>(stride),
                              reinterpret_cast<const void*>(static_cast<uintptr_t>(a.offset)));
        mesh.enabledMask |= 1u << a.location;
    }
    if (indices != nullptr && indexCount != 0) {
        glGenBuffers(1, &mesh.ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);  // part of the VAO's state
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indexCount * sizeof(uint32_t)), indices, GL_STATIC_DRAW);
    }
    mesh.stride = stride;
    mesh.attributes.assign(attributes, attributes + attributeCount);
    return AddMesh(std::move(mesh));
}

bool UpdateMesh(uint32_t id, const void* vertices, size_t vertexBytes, uint32_t stride, const uint32_t* indices,
                size_t indexCount, const MeshAttribute* attributes, int attributeCount) {
    if (!IsReady() || vertices == nullptr || vertexBytes == 0) return false;
    const Mesh* found = FindMesh(id);
    if (found == nullptr) return false;
    const Mesh& mesh = *found;
    const bool indexed = indices != nullptr && indexCount != 0;
    if (mesh.stride != stride || mesh.attributes.size() != static_cast<size_t>(attributeCount) || indexed != (mesh.ibo != 0)) {
        return false;
    }
    for (int i = 0; i < attributeCount; ++i) {
        const MeshAttribute& a = mesh.attributes[static_cast<size_t>(i)];
        const MeshAttribute& b = attributes[i];
        if (a.location != b.location || a.components != b.components || a.normalizedBytes != b.normalizedBytes ||
            a.offset != b.offset) {
            return false;
        }
    }
    // (glBufferData with the buffer's old storage orphaned: a draw of the last frame still in the driver's queue keeps
    // the old contents)
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertexBytes), vertices, GL_DYNAMIC_DRAW);
    perf::Add(perf::kBufferUploads);
    perf::Add(perf::kBufferBytes, vertexBytes);
    if (indexed) {
        GlBindVertexArray(mesh.vao);  // the element buffer binding belongs to the vertex array object
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indexCount * sizeof(uint32_t)), indices, GL_DYNAMIC_DRAW);
        perf::Add(perf::kBufferUploads);
        perf::Add(perf::kBufferBytes, indexCount * sizeof(uint32_t));
    }
    return true;
}

void DestroyMesh(uint32_t id) {
    Mesh* found = FindMesh(id);
    if (found == nullptr) return;
    if (IsReady()) {
        GlDeleteVertexArray(found->vao);
        glDeleteBuffers(1, &found->vbo);
        if (found->ibo != 0) glDeleteBuffers(1, &found->ibo);
    }
    *found = Mesh();  // (dead; the id is not given out again)
}

uint32_t StreamMesh(const void* vertices, size_t vertexBytes, uint32_t stride, const uint32_t* indices, size_t indexCount,
                    const MeshAttribute* attributes, int attributeCount) {
    if (!IsReady() || vertices == nullptr || vertexBytes == 0) return 0;
    StreamLayout* layout = nullptr;
    for (StreamLayout& s : g_streamMeshes) {
        if (SameLayout(s, stride, attributes, attributeCount)) {
            layout = &s;
            break;
        }
    }
    if (layout == nullptr) {
        // The vertex array object with the layout (as CreateMesh sets it up) and both buffers, the index buffer attached.
        Mesh mesh;
        glGenVertexArrays(1, &mesh.vao);
        GlBindVertexArray(mesh.vao);
        glGenBuffers(1, &mesh.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        for (int i = 0; i < attributeCount; ++i) {
            const MeshAttribute& a = attributes[i];
            glEnableVertexAttribArray(a.location);
            glVertexAttribPointer(a.location, a.components, a.normalizedBytes ? GL_UNSIGNED_BYTE : GL_FLOAT,
                                  a.normalizedBytes ? 1 : 0, static_cast<GLsizei>(stride),
                                  reinterpret_cast<const void*>(static_cast<uintptr_t>(a.offset)));
            mesh.enabledMask |= 1u << a.location;
        }
        glGenBuffers(1, &mesh.ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);  // part of the VAO's state
        StreamLayout s;
        s.stride = stride;
        s.attributes.assign(attributes, attributes + attributeCount);
        s.id = AddMesh(std::move(mesh));
        g_streamMeshes.push_back(std::move(s));
        layout = &g_streamMeshes.back();
    }
    const Mesh& mesh = g_meshes[layout->id];
    GlBindVertexArray(mesh.vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertexBytes), vertices, GL_STREAM_DRAW);
    perf::Add(perf::kBufferUploads);
    perf::Add(perf::kBufferBytes, vertexBytes);
    // The index buffer is filled only when its first indexCount indices differ from these (a draw reads no further): the
    // PTank quads' indices are one pattern, of which every draw takes the start.
    if (indices != nullptr && indexCount != 0 &&
        (indexCount > layout->indices.size() ||
         std::memcmp(indices, layout->indices.data(), indexCount * sizeof(uint32_t)) != 0)) {
        // The VAO's element buffer is mesh.ibo: binding it again while the VAO is bound keeps it attached.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indexCount * sizeof(uint32_t)), indices, GL_STREAM_DRAW);
        perf::Add(perf::kBufferUploads);
        perf::Add(perf::kBufferBytes, indexCount * sizeof(uint32_t));
        layout->indices.assign(indices, indices + indexCount);
    }
    return layout->id;
}

void ReleaseStreamMeshes() {
    for (const StreamLayout& s : g_streamMeshes) DestroyMesh(s.id);
    g_streamMeshes.clear();
}

void DrawMesh(uint32_t id, uint32_t mode, bool indexed, uint32_t minIndex, uint32_t maxIndex, uint32_t count,
              uint32_t first, const float (*defaults)[4]) {
    const Mesh* found = FindMesh(id);
    if (found == nullptr || !IsReady()) return;
    const Mesh& mesh = *found;
    GlBindVertexArray(mesh.vao);
    perf::Add(perf::kDraws);
    if (defaults != nullptr) {
        if (defaults != g_defaultsTable) {
            g_defaultsTable = defaults;
            g_defaultsApplied = 0;
        }
        // The slots without an array that do not hold the table's value yet (usually none).
        uint32_t todo = ~mesh.enabledMask & 0xffffu & ~g_defaultsApplied;
        for (uint32_t slot = 0; todo != 0; ++slot, todo >>= 1) {
            if ((todo & 1u) == 0) continue;
            const uint32_t bit = 1u << slot;
            if ((g_attribKnown & bit) == 0 || std::memcmp(g_attribDefault[slot], defaults[slot], sizeof g_attribDefault[slot]) != 0) {
                glVertexAttrib4f(slot, defaults[slot][0], defaults[slot][1], defaults[slot][2], defaults[slot][3]);
                std::memcpy(g_attribDefault[slot], defaults[slot], sizeof g_attribDefault[slot]);
                g_attribKnown |= bit;
            }
            g_defaultsApplied |= bit;
        }
    }
    ApplyAlphaCoverage();  // (device.cpp: on for this draw only when its SetAlphaTest asked for it)
    if (indexed && mesh.ibo != 0) {
        glDrawRangeElements(mode, minIndex, maxIndex, static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(mode, static_cast<GLint>(first), static_cast<GLsizei>(count));
    }
    g_attribKnown &= ~mesh.enabledMask;  // the slots with arrays: their constants may be undefined after the draw
    g_defaultsApplied &= ~mesh.enabledMask;
}

void ForgetVertexAttribDefaults(uint32_t slotMask) {
    g_attribKnown &= ~slotMask;
    g_defaultsApplied &= ~slotMask;
}

void UseProgram(uint32_t program) {
    if (!IsReady() || program == 0) return;  // (0: the program stays bound, mesh.h)
    GlUseProgram(program);
}

int UniformLocation(uint32_t program, const char* name) {
    if (!IsReady() || program == 0) return -1;
    return glGetUniformLocation(program, name);
}

UniformType UniformTypeOf(const char* glslType) {
    const std::string_view type(glslType);
    if (type == "mat4") return UniformType::kMat4;
    if (type == "mat3x4") return UniformType::kMat3x4;
    if (type == "vec4") return UniformType::kVec4;
    if (type == "vec3") return UniformType::kVec3;
    if (type == "vec2") return UniformType::kVec2;
    if (type == "float") return UniformType::kFloat;
    if (type == "bool" || type == "int") return UniformType::kBoolOrInt;
    return UniformType::kUnknown;
}

int UniformFloats(UniformType type, int count) {
    switch (type) {
        case UniformType::kMat4: return 16 * count;
        case UniformType::kMat3x4: return 12 * count;
        case UniformType::kVec4: return 4 * count;
        case UniformType::kVec3: return 3 * count;
        case UniformType::kVec2: return 2 * count;
        case UniformType::kFloat: return count;
        case UniformType::kBoolOrInt: return 1;  // data[0] only
        default: return 0;
    }
}

void SetUniformTyped(int location, UniformType type, int count, const float* data) {
    if (!IsReady() || location < 0) return;
    perf::Add(perf::kUniforms);
    switch (type) {
        case UniformType::kMat4: glUniformMatrix4fv(location, count, 0, data); break;
        case UniformType::kMat3x4: glUniformMatrix3x4fv(location, count, 0, data); break;  // a Cg float3x4: 3 registers each
        case UniformType::kVec4: glUniform4fv(location, count, data); break;
        case UniformType::kVec3: glUniform3fv(location, count, data); break;
        case UniformType::kVec2: glUniform2fv(location, count, data); break;
        case UniformType::kFloat: glUniform1fv(location, count, data); break;
        case UniformType::kBoolOrInt: glUniform1i(location, data[0] != 0.0f ? 1 : 0); break;
        default: break;
    }
}

void SetUniform(int location, const char* glslType, int count, const float* data) {
    if (!IsReady() || location < 0) return;
    SetUniformTyped(location, UniformTypeOf(glslType), count, data);
}

void SetUniformInt(int location, int value) {
    if (!IsReady() || location < 0) return;
    perf::Add(perf::kUniforms);
    glUniform1i(location, value);
}

}  // namespace dotd::gfx
