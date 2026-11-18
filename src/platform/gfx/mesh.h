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
// New contents for a mesh made by CreateMesh, when its layout is the one given (the same stride and attributes, an index
// buffer exactly when it had one): the vertex buffer and the index buffer are filled again and true is returned, the
// vertex array object and the buffer objects stay. False (and nothing changed) for another layout or an unknown mesh:
// the caller destroys it and creates a new one. (perf: a geometry that is instanced again every frame, the trails and
// the other generic geometries the game locks, kept three GL objects' creation and deletion per mesh and frame.)
bool UpdateMesh(uint32_t mesh, const void* vertices, size_t vertexBytes, uint32_t stride, const uint32_t* indices,
                size_t indexCount, const MeshAttribute* attributes, int attributeCount);
// A mesh for one draw of streamed vertices (the immediate-mode draws: the PTank quads, Im3D through a program): the
// same as CreateMesh, but the vertex array object and its buffers are made once per attribute layout and refilled
// (glBufferData, GL_STREAM_DRAW) by every call, instead of being created and deleted around each draw (the index buffer
// only when its first indexCount indices differ from the given ones: a draw reads no more). The mesh stays
// valid until the next StreamMesh call with the same layout; the caller does not destroy it. The index buffer stays
// attached when a call has no indices (draw it non-indexed then). 0 on failure or without a device.
uint32_t StreamMesh(const void* vertices, size_t vertexBytes, uint32_t stride, const uint32_t* indices, size_t indexCount,
                    const MeshAttribute* attributes, int attributeCount);
// Deletes the stream meshes' GL objects (the device's Shutdown, before the context goes).
void ReleaseStreamMeshes();

// Binds the mesh and draws it. `mode` is the GL primitive (4 triangles, 5 triangle strip). Indexed: indices
// [0, indexCount) with the value range [minIndex, maxIndex] (glDrawRangeElements); else `count` vertices from `first`.
// `defaults` holds, for each shader input slot 0..15 the mesh has no attribute for, the constant value (4 floats) the
// shader sees; null: leave as is. The table must not change while its address is in use (the callers pass constants):
// DrawMesh remembers which slots already hold the values of the table it was last given.
void DrawMesh(uint32_t mesh, uint32_t mode, bool indexed, uint32_t minIndex, uint32_t maxIndex, uint32_t count,
              uint32_t first, const float (*defaults)[4]);

// Binds the internal render target (a draw outside DrawPrimitive).
void BindTarget();

// ---- shader programs --------------------------------------------------------------------------------
// Makes `program` current. UseProgram(0) (the original's unbind after a draw) does nothing: every draw path of the
// backend binds its own program first, so the program stays bound until another one is used (GlUseProgram).
void UseProgram(uint32_t program);
// The alpha test of the uber-shader programs' draws: the program's uniforms dotd_alphaFunc (RenderWare's function, 8 =
// always) and dotd_alphaRef (0..1). The locations are looked up once per program and a value the program already holds
// is not uploaded again (nothing else writes these two uniforms).
void SetAlphaTest(uint32_t program, int func, float ref);
// The uber-shader programs are about to be deleted (cg::DestroyPrograms): what the backend keeps per GL program is
// dropped and no program stays current.
void ForgetPrograms();
// Uniform location by name; -1 when absent.
int UniformLocation(uint32_t program, const char* name);
// Uploads `count` elements of a uniform of the given GLSL type ("mat4", "mat3x4", "vec4", "vec3", "vec2", "float", "bool",
// "int");
// `data` holds the register layout the PS3 constants have (float4 per register; a matrix as rows, uploaded verbatim:
// cg_to_glsl.h "Matrices"). `count` is the array size (1 for a plain uniform).
void SetUniform(int location, const char* glslType, int count, const float* data);
void SetUniformInt(int location, int value);
// SetUniform with the type parsed once (perf: the per-draw uploads): UniformTypeOf(glslType) then SetUniformTyped does
// what SetUniform(glslType) does. UniformFloats is the number of floats of `data` such an upload reads.
enum class UniformType : uint8_t { kMat4, kMat3x4, kVec4, kVec3, kVec2, kFloat, kBoolOrInt, kUnknown };
UniformType UniformTypeOf(const char* glslType);
int UniformFloats(UniformType type, int count);
void SetUniformTyped(int location, UniformType type, int count, const float* data);

// ---- textures ---------------------------------------------------------------------------------------
// Binds `texture` (0: the white texture) on a texture unit with the sampler state of `state` (filter, mips,
// addressing; the other DrawState fields are ignored).
void BindTextureUnit(int unit, uint32_t texture, const DrawState& state);
// The active texture unit (glActiveTexture's; BindTextureUnit leaves its unit active) and its setter: what the PS3 driver's
// RwPSGL_GetActiveTextureUnit_maybe / RwPSGL_SetActiveTextureUnit_maybe read and set. A texture created or updated later
// is bound on the active unit, so a caller that must not leave its unit active saves and restores it (BindTextureOnUnit).
int ActiveTextureUnit();
void SetActiveTextureUnit(int unit);

// ---- GL state shadow (platform/gfx internal; perf) ------------------------------------------------------
// The backend's texture unit / binding / sampler parameter calls go through these (device.cpp keeps what it last set,
// so a call that would set what GL already has is skipped): glActiveTexture(GL_TEXTURE0 + unit),
// glBindTexture(GL_TEXTURE_2D, texture) on the active unit, glTexParameteri(GL_TEXTURE_2D, pname, value) on the texture
// bound there, glDeleteTextures. No GL code outside them may change these states.
// GlActiveTexture is lazy: glActiveTexture itself is called only before a call that depends on the unit (inside
// GlBindTexture2D / GlTexParameter2D when they reach GL). Code that calls a texture image or parameter function of GL
// directly (glTexImage2D, glTexSubImage2D, glCompressedTexImage2D, glTexParameterf, ...) calls GlFlushActiveTexture
// after its GlBindTexture2D.
void GlActiveTexture(int unit);
void GlFlushActiveTexture();
void GlBindTexture2D(uint32_t texture);
void GlTexParameter2D(uint32_t pname, int value);
void GlDeleteTexture(uint32_t texture);
// The same for the blend / depth / cull states: glEnable / glDisable(cap) (GL_BLEND, GL_DEPTH_TEST, GL_CULL_FACE; another
// cap is not shadowed), glBlendFunc, glDepthFunc, glDepthMask, glFrontFace, glCullFace.
void GlCap(uint32_t cap, bool on);
void GlBlendFunc(uint32_t src, uint32_t dst);
void GlDepthFunc(uint32_t func);
void GlDepthMask(bool write);
void GlFrontFace(uint32_t mode);
void GlCullFace(uint32_t mode);
// The program and vertex array object bindings (glUseProgram, glBindVertexArray, glDeleteVertexArrays): shadowed like
// the states above, and never set back to 0 between draws. No GL code outside them may call those three functions;
// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER) is only called with the buffer's own vertex array object bound through
// GlBindVertexArray.
void GlUseProgram(uint32_t program);
void GlBindVertexArray(uint32_t vao);
void GlDeleteVertexArray(uint32_t vao);
// DrawMesh keeps the constant values it gave the shader input slots without an array (glVertexAttrib4f: context state)
// and sets only the ones that differ. A draw from a vertex array object with arrays enabled on some slots may leave
// those slots' constants undefined (older GL wording): such a draw outside DrawMesh calls this with its slot mask.
void ForgetVertexAttribDefaults(uint32_t slotMask);

}  // namespace dotd::gfx
