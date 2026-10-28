// mesh.cpp - see mesh.h. New platform code (the job of PSGL's buffer and attribute calls).
#include "platform/gfx/mesh.h"

#include <map>
#include <string_view>

#include "platform/gfx/gl.h"
#include "platform/log.h"

using namespace dotd::gfx::gl;

namespace dotd::gfx {
namespace {

struct Mesh {
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ibo = 0;
    uint32_t enabledMask = 0;  // shader input slots with an attribute array
};
std::map<uint32_t, Mesh> g_meshes;
uint32_t g_nextMesh = 1;

}  // namespace

uint32_t CreateMesh(const void* vertices, size_t vertexBytes, uint32_t stride, const uint32_t* indices, size_t indexCount,
                    const MeshAttribute* attributes, int attributeCount) {
    if (!IsReady() || vertices == nullptr || vertexBytes == 0) return 0;
    Mesh mesh;
    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);
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
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    const uint32_t id = g_nextMesh++;
    g_meshes[id] = mesh;
    return id;
}

void DestroyMesh(uint32_t id) {
    auto found = g_meshes.find(id);
    if (found == g_meshes.end()) return;
    if (IsReady()) {
        glDeleteVertexArrays(1, &found->second.vao);
        glDeleteBuffers(1, &found->second.vbo);
        if (found->second.ibo != 0) glDeleteBuffers(1, &found->second.ibo);
    }
    g_meshes.erase(found);
}

void DrawMesh(uint32_t id, uint32_t mode, bool indexed, uint32_t minIndex, uint32_t maxIndex, uint32_t count,
              uint32_t first, const float (*defaults)[4]) {
    auto found = g_meshes.find(id);
    if (found == g_meshes.end() || !IsReady()) return;
    const Mesh& mesh = found->second;
    glBindVertexArray(mesh.vao);
    if (defaults != nullptr) {
        for (uint32_t slot = 0; slot < 16; ++slot) {
            if ((mesh.enabledMask & (1u << slot)) == 0) glVertexAttrib4f(slot, defaults[slot][0], defaults[slot][1], defaults[slot][2], defaults[slot][3]);
        }
    }
    if (indexed && mesh.ibo != 0) {
        glDrawRangeElements(mode, minIndex, maxIndex, static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(mode, static_cast<GLint>(first), static_cast<GLsizei>(count));
    }
    glBindVertexArray(0);
}

void UseProgram(uint32_t program) {
    if (IsReady()) glUseProgram(program);
}

int UniformLocation(uint32_t program, const char* name) {
    if (!IsReady() || program == 0) return -1;
    return glGetUniformLocation(program, name);
}

void SetUniform(int location, const char* glslType, int count, const float* data) {
    if (!IsReady() || location < 0) return;
    const std::string_view type(glslType);
    if (type == "mat4") glUniformMatrix4fv(location, count, 0, data);
    else if (type == "mat3x4") glUniformMatrix3x4fv(location, count, 0, data);  // a Cg float3x4: 3 registers each
    else if (type == "vec4") glUniform4fv(location, count, data);
    else if (type == "vec3") glUniform3fv(location, count, data);
    else if (type == "vec2") glUniform2fv(location, count, data);
    else if (type == "float") glUniform1fv(location, count, data);
    else if (type == "bool" || type == "int") glUniform1i(location, data[0] != 0.0f ? 1 : 0);
}

void SetUniformInt(int location, int value) {
    if (IsReady() && location >= 0) glUniform1i(location, value);
}

}  // namespace dotd::gfx
