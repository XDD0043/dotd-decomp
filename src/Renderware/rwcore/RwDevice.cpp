// RwDevice.cpp - see RwDevice.h. New code (the PS3 driver's job, done for platform/gfx).
#include "Renderware/rwcore/RwDevice.h"

#include <cmath>
#include <cstddef>
#include <cstring>
#include <unordered_map>
#include <vector>

#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwIm2D.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwTexture.h"
#include "platform/gfx/device.h"
#include "platform/gfx/raster.h"
#include "platform/gfx/mesh.h"
#include "platform/log.h"
#include "platform/sdl/freecam.h"

namespace gfx = dotd::gfx;

namespace {

RwCamera* g_camera = nullptr;
// The camera rasters' device targets (RwDevice_RasterTarget) and the Im2D shader bind callback.
std::unordered_map<const RwRaster*, uint32_t> g_rasterTargets;
RwDeviceIm2DShaderBind g_im2dShaderBind = nullptr;
// The Im3D shader bind callback (0xc4d674; the PS3 default is the nop 0x76b588: the device's program) and the PTank
// draws' replacement of it.
RwDeviceIm3DShaderBind g_im3dShaderBind = nullptr;
RwDeviceIm3DShaderBind g_im3dShaderBindOverride = nullptr;
// BeginPSGLCameraUpdate's saved z test / z write states of a camera without a z buffer (the driver's +0x14 / +0x18).
RwInt32 g_savedZTest = 0;
RwInt32 g_savedZWrite = 0;
RwCamera* g_worldCameras[2] = {nullptr, nullptr};  // the cameras the debug free-fly camera replaces
float g_cameraViewProj[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
float g_cameraView[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};  // world -> camera, column-major

gfx::Blend BlendOf(RwInt32 rw) {
    switch (rw) {  // rwBLEND*
        case 1: return gfx::Blend::kZero;
        case 2: return gfx::Blend::kOne;
        case 3: return gfx::Blend::kSrcColor;
        case 4: return gfx::Blend::kInvSrcColor;
        case 5: return gfx::Blend::kSrcAlpha;
        case 6: return gfx::Blend::kInvSrcAlpha;
        case 7: return gfx::Blend::kDestAlpha;
        case 8: return gfx::Blend::kInvDestAlpha;
        case 9: return gfx::Blend::kDestColor;
        case 10: return gfx::Blend::kInvDestColor;
        case 11: return gfx::Blend::kSrcAlphaSat;
        default: return gfx::Blend::kOne;
    }
}

gfx::Address AddressOf(RwInt32 rw) {
    switch (rw) {  // rwTEXTUREADDRESS*
        case 2: return gfx::Address::kMirror;
        case 3:
        case 4: return gfx::Address::kClamp;  // border: no border colour here
        default: return gfx::Address::kWrap;
    }
}

// The render states as the PSGL driver applies them. "Vertex alpha" off disables blending; the alpha test does not go
// with it: the PSGL alpha test function state (0x73c940) enables its GL cap (driver state +0x1a8 / +0x1ac) for any
// function but ALWAYS (8) whatever the vertex alpha, and the vertex alpha state (0x73dc48) only switches the blend cap
// (+0x1b0 / +0x1b4). (Coupled before: the pooled particle effects' PTanks, drawn with vertex alpha off and ONE / ZERO,
// showed their textures' cut-out texels as the flat purple and pink quads of the fights.)

gfx::DrawState StateOf(const RwIm3DRenderStates& s, void* raster) {
    gfx::DrawState d;
    // RwDevice_GetRasterTexture, with the raster's rwRASTERFORMATMIPMAP from the same search of the camera rasters (perf):
    // false for a camera texture drawn into (a render target), cFormat bit 7 otherwise.
    bool hasMipmaps = false;
    if (raster != nullptr) {
        const RwRaster* r = static_cast<const RwRaster*>(raster);
        // perf: only a camera texture raster can be in g_rasterTargets (RwDevice_RasterTarget adds no other), so every
        // other raster skips the search (two searches per bound texture of every mesh draw).
        const auto camera = r->cType == rwRASTERTYPECAMERATEXTURE ? g_rasterTargets.find(r) : g_rasterTargets.end();
        if (camera != g_rasterTargets.end()) {
            d.texture = gfx::IsReady() ? gfx::RenderTargetTexture(camera->second) : 0;
        } else {
            d.texture = gfx::IsReady() ? gfx::RasterTextureDevice(r->psgl.texture) : 0;
            hasMipmaps = (r->cFormat & 0x80) != 0;
        }
    }
    // rwFILTER*: 1 nearest, 2 linear, 3 mip nearest, 4 mip linear, 5 linear mip nearest, 6 linear mip linear
    RwInt32 filter = s.textureFilter;
    // 0x0073e048 RwPSGL_SetTextureFilterMode_maybe (and 0x0073df28 RwPSGL_SetRenderStateTextureFilter): a raster without
    // mip levels (rwRASTERFORMATMIPMAP clear: a camera texture, a DDS without DDSCAPS_MIPMAP) takes the mip modes 3 / 4 as
    // rwFILTERNEAREST and 5 / 6 as rwFILTERLINEAR; the GL filters are the driver's tables (gfx::DrawState::filterMode).
    if (raster != nullptr && (filter >= 3 && filter <= 6) && !hasMipmaps) filter = filter <= 4 ? 1 : 2;
    d.filterMode = static_cast<uint8_t>(filter >= 1 && filter <= 6 ? filter : 0);
    d.linear = !(filter == 1 || filter == 3 || filter == 5);
    d.mipmaps = filter >= 3 && filter <= 6;
    d.addressU = AddressOf(s.textureAddressU);
    d.addressV = AddressOf(s.textureAddressV);
    d.blend = s.vertexAlphaEnable != 0;
    d.srcBlend = BlendOf(s.srcBlend);
    d.dstBlend = BlendOf(s.destBlend);
    d.alphaTest = s.alphaTestFunction != 8;
    d.alphaFunc = static_cast<gfx::Compare>(s.alphaTestFunction >= 1 && s.alphaTestFunction <= 8 ? s.alphaTestFunction - 1 : 7);
    d.alphaRef = static_cast<float>(s.alphaTestFunctionRef) / 255.0f;
    d.depthTest = s.zTestEnable != 0;
    d.depthWrite = s.zWriteEnable != 0;
    d.cull = s.cullEnabled == 0 ? 0 : (s.cullFace == 3 ? 2 : 1);
    return d;
}

// An RW matrix (rows right, up, at, pos; points are row vectors) as a column-major GL matrix.
void ToGl(const RwMatrix& m, float out[16]) {
    out[0] = m.right.x; out[1] = m.right.y; out[2] = m.right.z; out[3] = 0.0f;
    out[4] = m.up.x;    out[5] = m.up.y;    out[6] = m.up.z;    out[7] = 0.0f;
    out[8] = m.at.x;    out[9] = m.at.y;    out[10] = m.at.z;   out[11] = 0.0f;
    out[12] = m.pos.x;  out[13] = m.pos.y;  out[14] = m.pos.z;  out[15] = 1.0f;
}

gfx::Primitive PrimitiveOf(RwPrimitiveType type) {
    switch (type) {
        case rwPRIMTYPELINELIST: return gfx::Primitive::kLines;
        case rwPRIMTYPEPOLYLINE: return gfx::Primitive::kLineStrip;
        case rwPRIMTYPETRISTRIP: return gfx::Primitive::kTriangleStrip;
        case rwPRIMTYPETRIFAN: return gfx::Primitive::kTriangleFan;
        default: return gfx::Primitive::kTriangles;
    }
}

// A vertex for the shader manager's programs: POSITION (slot 0), COLOR0 (slot 3), TEXCOORD0 (slot 8).
struct ShaderVertex {
    float x, y, z;
    uint8_t rgba[4];
    float u, v;
};

// The shader inputs POSITION (slot 0), COLOR0 (slot 3) and TEXCOORD0 (slot 8) in a ShaderVertex.
const gfx::MeshAttribute kShaderVertexAttributes[3] = {{0, 3, false, 0}, {3, 4, true, 12}, {8, 2, false, 16}};
// The same inputs read straight from an RwIm3DVertex (objVertex +0x00, color +0x18 as R, G, B, A bytes, u +0x1c, v +0x20;
// the normal is not an input): the values the program sees are those of the ShaderVertex copy (dotd perf: no copy).
const gfx::MeshAttribute kIm3DVertexAttributes[3] = {{0, 3, false, 0}, {3, 4, true, 0x18}, {8, 2, false, 0x1c}};
static_assert(sizeof(RwIm3DVertex) == 0x24 && offsetof(RwIm3DVertex, color) == 0x18 && offsetof(RwIm3DVertex, u) == 0x1c &&
                  offsetof(RwIm3DVertex, v) == 0x20,
              "RwIm3DVertex layout");

// One draw through a program a shader bind callback bound (and filled): the vertices (numVertices of `stride` bytes, the
// shader inputs at `attributes`) into the stream device mesh, the texture on unit 0 and the blend / depth / cull state, the
// alpha test as the program's two uniforms (the function, 8 = always, and the reference), glDrawRangeElements /
// glDrawArrays.
void DrawThroughProgram(uint32_t program, RwPrimitiveType primType, const void* vertices, RwInt32 numVertices,
                        uint32_t stride, const gfx::MeshAttribute* attributes, const RwImVertexIndex* indices,
                        RwInt32 numIndices, const gfx::DrawState& state, int alphaFunc) {
    // RwImVertexIndex is 32-bit: the indices go to the index buffer as they are.
    static_assert(sizeof(RwImVertexIndex) == sizeof(uint32_t), "32-bit Im3D indices");
    const size_t indexCount = indices != nullptr && numIndices > 0 ? static_cast<size_t>(numIndices) : 0;
    // dotd perf: one stream mesh refilled per draw (gfx::StreamMesh) instead of a mesh created and deleted around it.
    const uint32_t mesh = gfx::StreamMesh(vertices, static_cast<size_t>(numVertices) * stride, stride,
                                          indexCount != 0 ? indices : nullptr, indexCount, attributes, 3);
    gfx::BindTarget();
    gfx::BindTextureUnit(0, state.texture, state);
    gfx::ApplyState(state);
    gfx::SetAlphaTest(program, alphaFunc, state.alphaRef);
    uint32_t mode = 4;  // GL_TRIANGLES
    switch (primType) {
        case rwPRIMTYPELINELIST: mode = 1; break;
        case rwPRIMTYPEPOLYLINE: mode = 3; break;
        case rwPRIMTYPETRISTRIP: mode = 5; break;
        case rwPRIMTYPETRIFAN: mode = 6; break;
        default: break;
    }
    static const float kDefaults[16][4] = {{0, 0, 0, 1}, {1, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 1}, {0, 0, 0, 1},
                                           {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
                                           {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
                                           {0, 0, 0, 0}};
    if (indexCount != 0) {
        gfx::DrawMesh(mesh, mode, true, 0, static_cast<uint32_t>(numVertices - 1), static_cast<uint32_t>(indexCount), 0,
                      kDefaults);
    } else {
        gfx::DrawMesh(mesh, mode, false, 0, 0, static_cast<uint32_t>(numVertices), 0, kDefaults);
    }
    gfx::UseProgram(0);
}

}  // namespace

uint32_t RwDevice_GetRasterTexture(RwRaster* raster) {
    if (raster == nullptr || !gfx::IsReady()) return 0;
    // A camera raster set as a texture (RwTextureSetRaster with a camera texture, CKPBuffer's shared rasters, or the
    // raster render state of DrawFullscreenRasterQuad): its render target's colour. (perf: only a camera texture raster
    // can be in the table, see StateOf.)
    if (raster->cType == rwRASTERTYPECAMERATEXTURE) {
        const auto camera = g_rasterTargets.find(raster);
        if (camera != g_rasterTargets.end()) return gfx::RenderTargetTexture(camera->second);
    }
    return gfx::RasterTextureDevice(raster->psgl.texture);  // the raster's GL texture
}

uint32_t RwDevice_RasterTarget(const RwRaster* raster) {
    if (raster == nullptr) return 0;
    const RwRaster* top = raster;
    while (top->parent != nullptr && top->parent != top) top = top->parent;  // a sub-raster draws into its parent
    if (top->cType != rwRASTERTYPECAMERATEXTURE) return 0;  // the camera raster: the display (the internal target)
    auto found = g_rasterTargets.find(top);
    if (found != g_rasterTargets.end()) return found->second;
    const uint32_t target = gfx::CreateRenderTarget(top->width, top->height);
    if (target != 0) g_rasterTargets.emplace(top, target);
    return target;
}

void RwDevice_ReleaseRaster(const RwRaster* raster) {
    auto found = g_rasterTargets.find(raster);
    if (found == g_rasterTargets.end()) return;
    gfx::DestroyRenderTarget(found->second);
    g_rasterTargets.erase(found);
}

void RwDevice_BindRasterRenderTarget(const RwRaster* raster) {
    if (raster != nullptr) gfx::SetRenderTarget(RwDevice_RasterTarget(raster));
}

void RwDevice_UnbindRenderTarget() { gfx::SetRenderTarget(0); }

void RwDevice_BeginCameraUpdate(RwCamera* camera) {
    const RwRaster* raster = camera->frameBuffer;
    const bool texture = raster != nullptr && raster->cType == rwRASTERTYPECAMERATEXTURE;
    gfx::SetRenderTarget(texture ? RwDevice_RasterTarget(raster) : 0);
    gfx::SetFrontFaceClockwise(texture);
    gfx::BeginFrame();
    RwDevice_SetCamera(camera);
    if (camera->zBuffer == nullptr) {
        RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &g_savedZTest);
        if (g_savedZTest != 0) RwRenderStateSet(rwRENDERSTATEZTESTENABLE, nullptr);
        RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &g_savedZWrite);
        if (g_savedZWrite != 0) RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, nullptr);
    }
}

void RwDevice_EndCameraUpdate(RwCamera* camera) {
    if (camera->frameBuffer != nullptr && camera->frameBuffer->cType == rwRASTERTYPECAMERATEXTURE) {
        gfx::SetRenderTarget(0);  // glBindFramebufferOES(GL_FRAMEBUFFER, 0)
        gfx::SetFrontFaceClockwise(false);
    }
    if (g_savedZTest != 0) {
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, reinterpret_cast<void*>(static_cast<intptr_t>(1)));
        g_savedZTest = 0;
    }
    if (g_savedZWrite != 0) {
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, reinterpret_cast<void*>(static_cast<intptr_t>(1)));
        g_savedZWrite = 0;
    }
}

void RwDevice_SetIm2DShaderBindCallBack(RwDeviceIm2DShaderBind callback) { g_im2dShaderBind = callback; }
void RwDevice_SetIm3DShaderBindCallBack(RwDeviceIm3DShaderBind callback) { g_im3dShaderBind = callback; }
void RwDevice_SetIm3DShaderBindOverride(RwDeviceIm3DShaderBind bind) { g_im3dShaderBindOverride = bind; }

RwMatrix RwDevice_CameraPose(const RwCamera* camera) {
    RwFrame* frame = RwCameraGetFrame(const_cast<RwCamera*>(camera));
    RwMatrix ltm;
    if (frame != nullptr) {
        ltm = *RwFrameGetLTM(frame);
    } else {
        std::memset(&ltm, 0, sizeof ltm);
        ltm.right.x = ltm.up.y = ltm.at.z = 1.0f;
    }
    // The debug free-fly camera (platform/sdl/freecam.h) replaces the pose of the world cameras; the first time it starts
    // where the game camera is.
    if ((camera == g_worldCameras[0] || camera == g_worldCameras[1]) && dotd::platform::freecam::Enabled()) {
        namespace fc = dotd::platform::freecam;
        if (!fc::HasPose()) {
            const float position[3] = {ltm.pos.x, ltm.pos.y, ltm.pos.z};
            fc::SetPose(position, std::atan2(ltm.at.x, ltm.at.z) * 57.2957795f, std::asin(ltm.at.y) * 57.2957795f);
        }
        float right[3], up[3], at[3], position[3], yaw, pitch;
        fc::GetAxes(right, up, at);
        fc::GetPose(position, &yaw, &pitch);
        ltm.right = {right[0], right[1], right[2]};
        ltm.up = {up[0], up[1], up[2]};
        ltm.at = {at[0], at[1], at[2]};
        ltm.pos = {position[0], position[1], position[2]};
    }
    return ltm;
}

RwCamera* RwDevice_GetCurrentCamera() { return g_camera; }

void RwDevice_SetCamera(RwCamera* camera) {
    g_camera = camera;
    if (camera == nullptr) return;
    const RwMatrix ltm = RwDevice_CameraPose(camera);
    // World -> camera: the inverse of the camera frame's LTM (general affine inverse, in double).
    const double a[3][3] = {{ltm.right.x, ltm.right.y, ltm.right.z},
                            {ltm.up.x, ltm.up.y, ltm.up.z},
                            {ltm.at.x, ltm.at.y, ltm.at.z}};
    const double det = a[0][0] * (a[1][1] * a[2][2] - a[1][2] * a[2][1]) -
                       a[0][1] * (a[1][0] * a[2][2] - a[1][2] * a[2][0]) +
                       a[0][2] * (a[1][0] * a[2][1] - a[1][1] * a[2][0]);
    if (det == 0.0) return;
    // A row-vector matrix M (p' = p M + pos): camera coordinates c = (p - pos) M^-1.
    double inv[3][3];
    inv[0][0] = (a[1][1] * a[2][2] - a[1][2] * a[2][1]) / det;
    inv[0][1] = (a[0][2] * a[2][1] - a[0][1] * a[2][2]) / det;
    inv[0][2] = (a[0][1] * a[1][2] - a[0][2] * a[1][1]) / det;
    inv[1][0] = (a[1][2] * a[2][0] - a[1][0] * a[2][2]) / det;
    inv[1][1] = (a[0][0] * a[2][2] - a[0][2] * a[2][0]) / det;
    inv[1][2] = (a[0][2] * a[1][0] - a[0][0] * a[1][2]) / det;
    inv[2][0] = (a[1][0] * a[2][1] - a[1][1] * a[2][0]) / det;
    inv[2][1] = (a[0][1] * a[2][0] - a[0][0] * a[2][1]) / det;
    inv[2][2] = (a[0][0] * a[1][1] - a[0][1] * a[1][0]) / det;
    const double pos[3] = {ltm.pos.x, ltm.pos.y, ltm.pos.z};
    // view[col][row] (column-major): c_j = sum_i p_i inv[i][j] - sum_i pos_i inv[i][j]
    double view[4][4] = {};
    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < 3; ++i) view[i][j] = inv[i][j];
        view[3][j] = -(pos[0] * inv[0][j] + pos[1] * inv[1][j] + pos[2] * inv[2][j]);
    }
    view[3][3] = 1.0;
    // Camera -> clip. RW's camera x points to the left of the screen; the view window is the half size
    // at distance 1 (perspective) or the half size (parallel); the view offset shifts the window.
    const double vwx = camera->viewWindow.x, vwy = camera->viewWindow.y;
    const double ox = camera->viewOffset.x, oy = camera->viewOffset.y;
    const double n = camera->nearPlane, f = camera->farPlane;
    double proj[4][4] = {};  // proj[col][row]
    if (camera->projectionType == rwPARALLEL) {
        proj[0][0] = -1.0 / vwx;
        proj[1][1] = 1.0 / vwy;
        proj[2][2] = 2.0 / (f - n);
        proj[3][2] = -(f + n) / (f - n);
        proj[3][0] = ox / vwx;
        proj[3][1] = -oy / vwy;
        proj[3][3] = 1.0;
    } else {
        proj[0][0] = -1.0 / vwx;
        proj[1][1] = 1.0 / vwy;
        proj[2][0] = ox / vwx;
        proj[2][1] = -oy / vwy;
        proj[2][2] = (f + n) / (f - n);
        proj[3][2] = -2.0 * f * n / (f - n);
        proj[2][3] = 1.0;
    }
    // BeginPSGLCameraUpdate: a camera texture's projection is glScalef(1, -1, 1) times the frustum (the image is stored
    // top row first, as RenderWare's rasters are; the Im2D path does not flip, DrawFullscreenRasterQuad's flip argument
    // undoes it where a pass needs it).
    if (camera->frameBuffer != nullptr && camera->frameBuffer->cType == rwRASTERTYPECAMERATEXTURE) {
        for (int c = 0; c < 4; ++c) proj[c][1] = -proj[c][1];
    }
    float out[16];
    for (int c = 0; c < 4; ++c) {
        for (int r = 0; r < 4; ++r) {
            double sum = 0.0;
            for (int k = 0; k < 4; ++k) sum += proj[k][r] * view[c][k];
            out[c * 4 + r] = static_cast<float>(sum);
        }
    }
    for (int c = 0; c < 4; ++c) {
        for (int r = 0; r < 4; ++r) g_cameraView[c * 4 + r] = static_cast<float>(view[c][r]);
    }
    std::memcpy(g_cameraViewProj, out, sizeof(out));
    gfx::SetViewProjection(out);
}

RwCamera* RwDevice_GetCamera() { return g_camera; }
void RwDevice_RegisterWorldCameras(RwCamera* main, RwCamera* far) {
    g_worldCameras[0] = main;
    g_worldCameras[1] = far;
}
void RwDevice_GetViewMatrix(float out[16]) { std::memcpy(out, g_cameraView, sizeof(g_cameraView)); }
void RwDevice_GetViewProjection(float out[16]) { std::memcpy(out, g_cameraViewProj, sizeof(g_cameraViewProj)); }
void RwDevice_OverrideView(const float view[16], const float viewProj[16]) {
    std::memcpy(g_cameraView, view, sizeof(g_cameraView));
    std::memcpy(g_cameraViewProj, viewProj, sizeof(g_cameraViewProj));
    gfx::SetViewProjection(viewProj);
}
dotd::gfx::DrawState RwDevice_CurrentMeshState(int* alphaFunc, float* alphaRef) {
    const RwIm3DRenderStates& s = RwIm3DCurrentStates();
    gfx::DrawState d = StateOf(s, nullptr);
    *alphaFunc = s.alphaTestFunction;
    *alphaRef = static_cast<float>(s.alphaTestFunctionRef) / 255.0f;
    return d;
}
dotd::gfx::DrawState RwDevice_TextureState(const RwTexture* texture) {
    gfx::DrawState d;
    if (texture == nullptr) return d;
    RwIm3DRenderStates s;
    const RwUInt32 fa = texture->filterAddressing;
    s.textureFilter = static_cast<RwInt32>(fa & 0xff);
    s.textureAddressU = static_cast<RwInt32>((fa >> 8) & 0xf);
    s.textureAddressV = static_cast<RwInt32>((fa >> 12) & 0xf);
    d = StateOf(s, texture->raster);
    return d;
}

void RwDevice_DrawIm3D(const RwIm3DDraw& draw, const RwIm3DVertex* vertices, size_t numVertices, const RwImVertexIndex* indices,
                       size_t numIndices) {
    if (!gfx::IsReady() || numVertices == 0) return;
    // rwIM3D_VERTEXUV clear: the PSGL immediate pipeline sends no texture coordinates (texturing off).
    void* raster = (draw.transformFlags & rwIM3D_VERTEXUV) != 0 ? draw.states.textureRaster : nullptr;
    const gfx::DrawState state = StateOf(draw.states, raster);
    // DrawPSGLImmediateGeometry 0x76b610: the shader bind callback first (the PTank draws: the programs their hook bound).
    // With a program the object-space vertices go to it (glVertexPointer / glColorPointer / glTexCoordPointer at the
    // shader's input slots; the LTM is in its world-view-projection uniform); the texture coordinates only with
    // rwIM3D_VERTEXUV (the key then has no texture coordinate set and the program does not read them).
    const RwDeviceIm3DShaderBind bind = g_im3dShaderBindOverride != nullptr ? g_im3dShaderBindOverride : g_im3dShaderBind;
    const uint32_t program = bind != nullptr ? bind(draw) : 0;
    // dotd perf: the device vertices are made after the bind (making them has no GL effect), and only for the device's
    // own program (gfx::Vertex, in a buffer kept across draws); a bound program reads the RwIm3DVertex array as it is.
    const size_t count = numVertices;
    if (program != 0) {
        if (draw.indexed && numIndices == 0) {
            gfx::UseProgram(0);
            return;
        }
        DrawThroughProgram(program, draw.primType, vertices, static_cast<RwInt32>(count), sizeof(RwIm3DVertex),
                           kIm3DVertexAttributes, draw.indexed ? indices : nullptr, static_cast<RwInt32>(numIndices), state,
                           state.alphaTest ? draw.states.alphaTestFunction : 8);
        return;
    }
    static thread_local std::vector<gfx::Vertex> deviceVertices;
    deviceVertices.resize(count);
    for (size_t i = 0; i < count; ++i) {
        const RwIm3DVertex& v = vertices[i];
        gfx::Vertex& o = deviceVertices[i];
        o.x = v.objVertex.x;
        o.y = v.objVertex.y;
        o.z = v.objVertex.z;
        o.rgba[0] = v.color.red;
        o.rgba[1] = v.color.green;
        o.rgba[2] = v.color.blue;
        o.rgba[3] = v.color.alpha;
        o.u = v.u;
        o.v = v.v;
    }
    float model[16];
    if (draw.hasLtm) ToGl(draw.ltm, model);
    static thread_local std::vector<uint16_t> deviceIndices;
    deviceIndices.clear();
    if (draw.indexed) {
        deviceIndices.reserve(numIndices);
        for (size_t i = 0; i < numIndices; ++i) deviceIndices.push_back(static_cast<uint16_t>(indices[i]));
        if (deviceIndices.empty()) return;
    }
    gfx::DrawPrimitive(PrimitiveOf(draw.primType), deviceVertices.data(), static_cast<int>(deviceVertices.size()),
                       draw.indexed ? deviceIndices.data() : nullptr, static_cast<int>(deviceIndices.size()),
                       draw.hasLtm ? model : nullptr, nullptr, state);
}

void RwDevice_DrawAtomic(const RpAtomicDraw& draw) {
    const RpGeometry* geometry = draw.geometry;
    if (!gfx::IsReady() || geometry == nullptr || geometry->morphTarget == nullptr || geometry->numVertices <= 0) return;
    const RwV3d* positions = geometry->morphTarget[0].verts;
    if (positions == nullptr) return;
    const RwTexCoords* uvs = geometry->numTexCoordSets > 0 ? geometry->texCoords[0] : nullptr;
    const bool prelit = (geometry->flags & rpGEOMETRYPRELIT) != 0 && geometry->preLitLum != nullptr;
    const bool modulate = (geometry->flags & rpGEOMETRYMODULATEMATERIALCOLOR) != 0;
    std::vector<gfx::Vertex> vertices(static_cast<size_t>(geometry->numVertices));
    bool vertexAlpha = false;
    for (RwInt32 i = 0; i < geometry->numVertices; ++i) {
        gfx::Vertex& o = vertices[static_cast<size_t>(i)];
        o.x = positions[i].x;
        o.y = positions[i].y;
        o.z = positions[i].z;
        const RwRGBA c = prelit ? geometry->preLitLum[i] : RwRGBA{255, 255, 255, 255};
        o.rgba[0] = c.red;
        o.rgba[1] = c.green;
        o.rgba[2] = c.blue;
        o.rgba[3] = c.alpha;
        vertexAlpha = vertexAlpha || c.alpha != 255;
        o.u = uvs != nullptr ? uvs[i].u : 0.0f;
        o.v = uvs != nullptr ? uvs[i].v : 0.0f;
    }
    float model[16];
    ToGl(draw.ltm, model);
    // One draw per material (RpMesh per material in RW's instancing), in material order.
    const RpMaterialList& list = geometry->matList;
    for (RwInt32 m = 0; m < list.numMaterials; ++m) {
        std::vector<uint16_t> indices;
        for (RwInt32 t = 0; t < geometry->numTriangles; ++t) {
            const RpTriangle& tri = geometry->triangles[t];
            if (tri.matIndex != m) continue;
            indices.push_back(tri.vertIndex[0]);
            indices.push_back(tri.vertIndex[1]);
            indices.push_back(tri.vertIndex[2]);
        }
        if (indices.empty()) continue;
        const RpMaterial* material = list.materials[m];
        const RwRGBA mc = static_cast<size_t>(m) < draw.materialColors.size() ? draw.materialColors[static_cast<size_t>(m)]
                                                                             : material->color;
        float scale[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        if (modulate) {
            scale[0] = mc.red / 255.0f;
            scale[1] = mc.green / 255.0f;
            scale[2] = mc.blue / 255.0f;
            scale[3] = mc.alpha / 255.0f;
        }
        void* raster = material->texture != nullptr ? material->texture->raster : nullptr;
        gfx::DrawState state = StateOf(draw.states, raster);
        if (material->texture != nullptr) {
            const RwUInt32 fa = material->texture->filterAddressing;
            RwIm3DRenderStates s = draw.states;
            s.textureFilter = static_cast<RwInt32>(fa & 0xff);
            s.textureAddressU = static_cast<RwInt32>((fa >> 8) & 0xf);
            s.textureAddressV = static_cast<RwInt32>((fa >> 12) & 0xf);
            state = StateOf(s, raster);
        }
        // The atomic pipeline turns vertex alpha on for translucent prelight or material colours.
        if (vertexAlpha || (modulate && mc.alpha != 255)) {
            state.blend = true;
            state.alphaTest = draw.states.alphaTestFunction != 8;
        }
        gfx::DrawPrimitive(gfx::Primitive::kTriangles, vertices.data(), static_cast<int>(vertices.size()), indices.data(),
                           static_cast<int>(indices.size()), model, scale, state);
    }
}

void RwDevice_DrawIm2D(RwPrimitiveType primType, const RwIm2DVertex* vertices, RwInt32 numVertices,
                       const RwImVertexIndex* indices, RwInt32 numIndices) {
    if (!gfx::IsReady() || numVertices <= 0) return;
    // Pixels of the camera raster (the device target when there is no camera) to NDC, y down.
    float w = static_cast<float>(gfx::InternalWidth()), h = static_cast<float>(gfx::InternalHeight());
    if (g_camera != nullptr && g_camera->frameBuffer != nullptr) {
        w = static_cast<float>(g_camera->frameBuffer->width);
        h = static_cast<float>(g_camera->frameBuffer->height);
    }
    const float ortho[16] = {2.0f / w, 0, 0, 0, 0, -2.0f / h, 0, 0, 0, 0, 1, 0, -1.0f, 1.0f, 0, 1};
    std::vector<gfx::Vertex> out(static_cast<size_t>(numVertices));
    for (RwInt32 i = 0; i < numVertices; ++i) {
        const RwIm2DVertex& v = vertices[i];
        gfx::Vertex& o = out[static_cast<size_t>(i)];
        o.x = v.x;
        o.y = v.y;
        o.z = 0.0f;
        o.rgba[0] = v.emissiveColor.red;
        o.rgba[1] = v.emissiveColor.green;
        o.rgba[2] = v.emissiveColor.blue;
        o.rgba[3] = v.emissiveColor.alpha;
        o.u = v.q != 0.0f ? v.s / v.q : v.s;
        o.v = v.q != 0.0f ? v.t / v.q : v.t;
    }
    const RwIm3DRenderStates& states = RwIm3DCurrentStates();
    gfx::DrawState state = StateOf(states, states.textureRaster);
    state.depthTest = false;  // screen-space quads; the PSGL Im2D path draws at the near plane
    // The shader manager's program (the post-effect passes): PSGLIm2D_ConvertScreenToClipSpace 0x7359d8 turns the
    // pixels into clip space (x * 2 / w - 1, -(y * 2 / h - 1)); the uber-shader's VSC_WORLDVIEWPROJ is the identity for
    // the Im2D pass state. Attributes at the shader's input slots: POSITION 0, COLOR0 3, TEXCOORD0 8.
    const uint32_t program = g_im2dShaderBind != nullptr ? g_im2dShaderBind() : 0;
    if (program != 0) {
        std::vector<ShaderVertex> clip(static_cast<size_t>(numVertices));
        for (RwInt32 i = 0; i < numVertices; ++i) {
            const gfx::Vertex& o = out[static_cast<size_t>(i)];
            ShaderVertex& c = clip[static_cast<size_t>(i)];
            c.x = o.x * (2.0f / w) - 1.0f;
            c.y = -(o.y * (2.0f / h) - 1.0f);
            c.z = vertices[i].z;
            std::memcpy(c.rgba, o.rgba, 4);
            c.u = o.u;
            c.v = o.v;
        }
        DrawThroughProgram(program, primType, clip.data(), static_cast<RwInt32>(clip.size()), sizeof(ShaderVertex),
                           kShaderVertexAttributes, indices, numIndices, state, state.alphaTest ? states.alphaTestFunction : 8);
        return;
    }
    std::vector<uint16_t> idx;
    if (indices != nullptr) {
        for (RwInt32 i = 0; i < numIndices; ++i) idx.push_back(static_cast<uint16_t>(indices[i]));
    }
    gfx::SetViewProjection(ortho);
    gfx::DrawPrimitive(PrimitiveOf(primType), out.data(), numVertices, indices != nullptr ? idx.data() : nullptr,
                       static_cast<int>(idx.size()), nullptr, nullptr, state);
    gfx::SetViewProjection(g_cameraViewProj);
}
