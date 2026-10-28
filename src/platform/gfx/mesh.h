// mesh.h - indexed meshes drawn with the game's uber-shader programs (new platform code, not a port).
//
// The PS3 driver (PSGL) keeps a vertex buffer and a 32-bit index buffer per mesh and sets the attribute pointers
// before every draw (glVertexPointer / glNormalPointer / glColorPointer / glTexCoordPointer, cgGLSetParameterPointer);
// the shader's inputs sit at fixed slots by semantic (cg_to_glsl.h). Here a mesh owns a vertex array object with
// that layout, so a draw is bind + glDrawRangeElements / glDrawArrays, and the shader's uniforms and textures are
// set through the small wrappers below. Everything is a no-op returning 0 / false without a device.
#pragma once
#include <cstddef>
#include <cstdint>

#include "platform/gfx/device.h"

namespace dotd::gfx {

// One vertex attribute of an interleaved vertex.
struct MeshAttribute {
    uint8_t location;    // shader input slot (POSITION 0, NORMAL 2, COLOR0 3, TEXCOORD0 8, TANGENT 14, ...)
    uint8_t components;  // 1..4
    bool normalizedBytes;  // true: unsigned bytes mapped to 0..1 (the colour); false: floats
    uint32_t offset;     // byte offset in the vertex
};

// A vertex buffer (interleaved, `stride` bytes per vertex, little-endian floats) and an optional 32-bit index buffer.
// Returns 0 on failure or without a device.
uint32_t CreateMesh(const void* vertices, size_t vertexBytes, uint32_t stride, const uint32_t* indices, size_t indexCount,
                    const MeshAttribute* attributes, int attributeCount);
void DestroyMesh(uint32_t mesh);

// Binds the mesh and draws it. `mode` is the GL primitive (4 triangles, 5 triangle strip). Indexed: indices
// [0, indexCount) with the value range [minIndex, maxIndex] (glDrawRangeElements); else `count` vertices from `first`.
// `defaults` holds, for each shader input slot 0..15 the mesh has no attribute for, the constant value (4 floats) the
// shader sees; null: leave as is.
void DrawMesh(uint32_t mesh, uint32_t mode, bool indexed, uint32_t minIndex, uint32_t maxIndex, uint32_t count,
              uint32_t first, const float (*defaults)[4]);

// Binds the internal render target (a draw outside DrawPrimitive).
void BindTarget();

// ---- shader programs --------------------------------------------------------------------------------
void UseProgram(uint32_t program);
// Uniform location by name; -1 when absent.
int UniformLocation(uint32_t program, const char* name);
// Uploads `count` elements of a uniform of the given GLSL type ("mat4", "mat3x4", "vec4", "vec3", "vec2", "float", "bool",
// "int");
// `data` holds the register layout the PS3 constants have (float4 per register; a matrix as rows, uploaded verbatim:
// cg_to_glsl.h "Matrices"). `count` is the array size (1 for a plain uniform).
void SetUniform(int location, const char* glslType, int count, const float* data);
void SetUniformInt(int location, int value);

// ---- textures ---------------------------------------------------------------------------------------
// Binds `texture` (0: the white texture) on a texture unit with the sampler state of `state` (filter, mips,
// addressing; the other DrawState fields are ignored).
void BindTextureUnit(int unit, uint32_t texture, const DrawState& state);

}  // namespace dotd::gfx
