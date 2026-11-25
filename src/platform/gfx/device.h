// device.h - the graphics device (OpenGL 3.3 core backend; new platform code, not a port).
//
// The game renders into a fixed internal target of the PS3's output size (1280x720 RGBA8, plus a depth
// buffer); EndFrame composites it into the window (letterboxed, with the video-out gamma) and swaps.
// On top of it sit the RenderWare device replacement (Renderware/rwcore/RwDevice.cpp: RW render states,
// rasters and cameras turned into the calls below) and the video planes (video_planes.h, family video).
//
// Everything here is a no-op returning 0/false while the device is not ready (headless tests), so the
// game code that records its draws runs unchanged without a window.
#pragma once
#include <cstddef>
#include <cstdint>

namespace dotd::gfx {

bool Init(int internalWidth, int internalHeight);
void Shutdown();
bool IsReady();  // Init succeeded (false when running without a window, e.g. in tests)
int InternalWidth();   // the internal target's size as the game knows it (1280x720 whatever the resolution scale)
int InternalHeight();
// The resolution scale (DOTD_RES_SCALE=0.25..1 from the start, or at run time): the internal target and every
// render target asked for at its size have that fraction of its pixels in each direction, and the present scales
// the picture up. Other targets keep their size.
float ResolutionScale();
void SetResolutionScale(float scale);
// The colour writes on or off (glColorMask): off for a depth-only pass (gpuprof.h, the opaque depth pre-pass).
void SetColorWrite(bool on);

void BeginFrame();  // binds the current render target (the internal one unless SetRenderTarget chose another)
void Clear(float r, float g, float b, float a);
// Clears colour and/or depth of the current render target (RwCameraClear: rwCAMERACLEARIMAGE 1, rwCAMERACLEARZ 2;
// the PS3 driver clears whatever frame buffer is bound, ClearPSGLCamera 0x738328).
void ClearTarget(bool color, bool depth, float r, float g, float b, float a);

// ---- render targets (the PS3's camera-texture rasters, rwRASTERTYPECAMERATEXTURE, as GL frame buffers) -----
// An RGBA8 colour texture with its frame buffer object; a target of the internal size shares the internal depth
// buffer (the PS3's depth raster is one, attached to whichever colour raster the camera draws into). Returns an id
// (0 on failure or without a device). Id 0 always names the internal target.
uint32_t CreateRenderTarget(int width, int height);
void DestroyRenderTarget(uint32_t target);
// The colour texture of a render target (the internal one's for 0), sampled by later passes.
uint32_t RenderTargetTexture(uint32_t target);
// Makes `target` current: draws, clears and BindTarget go there, the viewport is its size. 0: the internal target.
void SetRenderTarget(uint32_t target);
uint32_t CurrentRenderTarget();
// The winding of front faces for culling: counter-clockwise (GL's default) or clockwise (the PS3 driver turns it
// while a camera draws into a camera texture, whose projection is flipped vertically: BeginPSGLCameraUpdate 0x738a68).
void SetFrontFaceClockwise(bool clockwise);

// ---- textures --------------------------------------------------------------------------------------
enum class TextureFormat : uint8_t {
    kRGBA8,  // 4 bytes per pixel, R G B A in memory
    kBC1,    // DXT1 (with 1-bit alpha)
    kBC2,    // DXT3
    kBC3,    // DXT5
    kR8,     // one 8-bit channel (video planes)
    kASTC4x4,  // ASTC 4x4 blocks (16 bytes each): the DXT textures transcoded for a GPU without S3TC (raster.cpp)
};
// True when the DXT textures are to be transcoded to ASTC 4x4 (texture_transcode.h): the web build on a GPU without
// S3TC whose browser has ASTC, unless DOTD_ASTC=0. Set by Init; the loader thread reads it.
bool TranscodeDxtToAstc();
// DOTD_ASTC=bench (a GPU with S3TC): the transcoding is done and timed, the DXT data kept (raster.cpp).
bool AstcBenchOnly();
// One mip level: its bytes (tightly packed rows for the uncompressed formats).
struct TextureLevel {
    const void* data;
    size_t size;
};
// A 2D texture with `levelCount` mips (0 = none created). Returns 0 on failure or without a device.
// Compressed formats are uploaded as they are when the driver has S3TC, else decoded to RGBA8 on the CPU.
uint32_t CreateTexture(TextureFormat format, int width, int height, int levelCount, const TextureLevel* levels);
// RGBA8, one level (the C1.0 test path).
uint32_t CreateTextureRGBA8(int width, int height, const void* pixels, bool linearFilter);
// The LOD bias PSGL gives every texture: PSGL_Texture_BuildGcmSamplerState_maybe 0x655348 writes the RSX filter word's
// bias as (int)((GL_TEXTURE_LOD_BIAS - 0.26) * 256) (0x655414: the constants 0.26 and 256.0 at the library TOC -0x4c70 /
// -0x4c6c), and nothing in the game sets GL_TEXTURE_LOD_BIAS (0): -66 / 256 of a mip level, so the PS3 samples a quarter
// level sharper than plain GL. CreateTexture sets it on mipmapped textures (desktop GL); the web build's translated
// pixel shaders pass it to their lookups (cg_to_glsl.cpp: WebGL 2 has no such texture parameter).
constexpr float kPsglLodBias = -66.0f / 256.0f;
// GL_TEXTURE_MAX_LOD of a texture (the PS3 driver limits the smallest mip level used, C2.4 exit).
void SetTextureMaxLod(uint32_t texture, float lod);
void DestroyTexture(uint32_t texture);

// ---- video planes: platform/gfx/video_planes.h (family video: CreateTextureR8, UpdateTextureR8,
// DrawVideoPlanes with the BT.601 programs).

// ---- immediate geometry (RwIm3D and the atomics, through RwDevice) --------------------------------
// The vertex the backend draws: position, colour (R G B A bytes), texture coordinates.
struct Vertex {
    float x, y, z;
    uint8_t rgba[4];
    float u, v;
};
static_assert(sizeof(Vertex) == 24, "gfx::Vertex");

enum class Primitive : uint8_t { kLines, kLineStrip, kTriangles, kTriangleStrip, kTriangleFan };
// Blend factors (the subset RenderWare's rwBLEND* map onto).
enum class Blend : uint8_t {
    kZero,
    kOne,
    kSrcColor,
    kInvSrcColor,
    kSrcAlpha,
    kInvSrcAlpha,
    kDestAlpha,
    kInvDestAlpha,
    kDestColor,
    kInvDestColor,
    kSrcAlphaSat,
};
enum class Compare : uint8_t { kNever, kLess, kEqual, kLessEqual, kGreater, kNotEqual, kGreaterEqual, kAlways };
enum class Address : uint8_t { kWrap, kMirror, kClamp };

struct DrawState {
    uint32_t texture = 0;          // 0: no texture (vertex colour only)
    bool linear = true;            // texture filter (linear or nearest; mips: linear/nearest mip)
    bool mipmaps = false;          // the filter mode uses mips
    // The RenderWare filter mode (rwFILTER*, 1..6) when the state comes from a texture: the GL min / mag filters are
    // then the PSGL driver's (RwPSGL_SetTextureFilterMode_maybe 0x73e048 tables: min NEAREST, LINEAR,
    // NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR; mag NEAREST, LINEAR,
    // NEAREST, LINEAR, NEAREST, LINEAR). 0: `linear` / `mipmaps` decide.
    uint8_t filterMode = 0;
    Address addressU = Address::kWrap;
    Address addressV = Address::kWrap;
    bool blend = false;            // RW "vertex alpha": blending on
    Blend srcBlend = Blend::kSrcAlpha;
    Blend dstBlend = Blend::kInvSrcAlpha;
    bool alphaTest = false;
    Compare alphaFunc = Compare::kAlways;
    float alphaRef = 0.0f;         // 0..1
    bool depthTest = false;
    bool depthWrite = false;
    uint8_t cull = 0;              // 0 none, 1 back, 2 front (RW: counter-clockwise front faces)
};

// Applies the blend, depth and cull parts of a state to the GL context (for draws outside DrawPrimitive,
// e.g. the video planes after the PS3's SetRenderStates).
void ApplyState(const DrawState& state);
// The world -> clip transform for the following draws (column-major 4x4).
void SetViewProjection(const float matrix[16]);
// Draws `count` vertices (or `indexCount` indices into them) transformed by `model` (column-major 4x4,
// null = identity) and the view-projection; the colour is vertex colour x `colorScale` (null = 1) x the
// texture's colour.
void DrawPrimitive(Primitive primitive, const Vertex* vertices, int count, const uint16_t* indices, int indexCount,
                   const float* model, const float* colorScale, const DrawState& state);

// ---- C1.0 test path -----------------------------------------------------------------------------------
// Axis-aligned quad in internal-target pixels (origin top-left), texture modulated by colour
// (0xRRGGBBAA). texture 0 = colour only. Alpha blending on.
void DrawQuad(uint32_t texture, float x0, float y0, float x1, float y1, uint32_t rgba);

// ---- frames ----------------------------------------------------------------------------------------
// Composite to the window and swap (vsync). Before that, when the environment variable
// DOTD_SCREENSHOT=path:frame (or path:frame1,frame2,...; "%d" in the path is replaced by the frame) names
// this frame (frames counted from 1 per EndFrame), the internal target is saved as a PNG.
void EndFrame();
// Frames presented so far.
uint32_t FrameCount();
// Saves the internal target (1280x720, top row first) as an RGB PNG. False without a device.
bool SaveScreenshot(const char* path);
// Reads the internal target as RGBA8, top row first (width * height * 4 bytes). False without a device.
bool ReadTarget(uint8_t* rgba);

}  // namespace dotd::gfx
