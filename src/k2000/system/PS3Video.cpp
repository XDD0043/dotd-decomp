// PS3Video.cpp - reconstructed original translation unit 0xaee90-0xb01f0 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary owner: PS3Video (not a registered class)
// Other owners: DrawPSGLTexturedScreenQuad (1), CColorizedScreenData (1)
//
// The PSGL/Cg calls are replaced by platform/gfx/video_planes.h (R8 textures, the GLSL translation of the
// Cg programs); the plane memory is host memory instead of a mapped PBO, so there are no fences.
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xaee90  PS3Video_SelectNextFrame_maybe
//   [x] 0xaef60  DrawPSGLTexturedScreenQuad
//   [x] 0xaf518  PS3Video_CreateFrameTexture_maybe
//   [x] 0xaf708  PS3Video_DestroyFrameTextures_maybe
//   [x] 0xaf8f8  PS3Video_CreateFrameBuffers_maybe
//   [x] 0xafd78  PS3Video_CreateShader_maybe
//   [x] 0xb00a8  PS3Video_DestroyFrameBuffers_maybe
//   [x] 0xb01a0  CColorizedScreenData_Delete  (DOTD_DECLARE_FACTORIES(CColorizedScreenData))
#include "k2000/system/PS3Video.h"

#include <cstdlib>
#include <cstring>

#include "platform/gfx/device.h"
#include "platform/gfx/video_planes.h"

namespace {
// The shader record (TOC -0x5ee4 in the original): the programs, their parameters, the quad VBO and the
// viewport size the Adjust vector divides by (+0x10 / +0x14).
struct VideoShaderState {
    float viewportWidth;
    float viewportHeight;
    bool created;
};
VideoShaderState g_videoShader = {1280.0f, 720.0f, false};

// 0x000af518 PS3Video_CreateFrameTexture_maybe: one plane as a linear, clamped single-channel texture.
uint32_t CreateFrameTexture(uint32_t width, uint32_t height) {
    return dotd::gfx::CreateTextureR8(static_cast<int>(width), static_cast<int>(height));
}

// Uploads the set's planes when Bink wrote them since the last draw (the PS3 textures alias the planes).
void UploadSet(BINKFRAMEBUFFERS* buffers, uint32_t index) {
    BINKPLANETEXTURES& tex = buffers->Textures[index];
    if (tex.dirty == 0) return;
    const BINKFRAMEPLANESET& set = buffers->Frames[index];
    const int w = static_cast<int>(buffers->YABufferWidth), h = static_cast<int>(buffers->YABufferHeight);
    const int cw = static_cast<int>(buffers->cRcBBufferWidth), ch = static_cast<int>(buffers->cRcBBufferHeight);
    dotd::gfx::UpdateTextureR8(tex.y, w, h, set.YPlane.Buffer, static_cast<int>(set.YPlane.BufferPitch));
    dotd::gfx::UpdateTextureR8(tex.cR, cw, ch, set.cRPlane.Buffer, static_cast<int>(set.cRPlane.BufferPitch));
    dotd::gfx::UpdateTextureR8(tex.cB, cw, ch, set.cBPlane.Buffer, static_cast<int>(set.cBPlane.BufferPitch));
    if (set.APlane.Allocate) {
        dotd::gfx::UpdateTextureR8(tex.a, w, h, set.APlane.Buffer, static_cast<int>(set.APlane.BufferPitch));
    }
    tex.dirty = 0;
}
}  // namespace

// 0x000aee90 PS3Video_SelectNextFrame_maybe: the PS3 waits on the next set's fence (glFinishFenceNV) so
// Bink does not overwrite planes the GPU still reads. Host uploads copy the planes: nothing to wait for.
void PS3Video_SelectNextFrame(BINKFRAMEBUFFERS*) {}

// 0x000aef60 DrawPSGLTexturedScreenQuad
void DrawPSGLTexturedScreenQuad(float x, float y, float scaleX, float scaleY, float alpha, BINKFRAMEBUFFERS* buffers,
                                uint32_t videoWidth, uint32_t videoHeight, int32_t useVertexMultiplier, bool blend) {
    const float rgb = useVertexMultiplier == 0 ? 1.0f : alpha;
    const float vw = g_videoShader.viewportWidth;
    const float vh = g_videoShader.viewportHeight;
    // Adjust: the top-left corner and the size in NDC (the unit quad goes right and down).
    const float fx = static_cast<float>(static_cast<double>(x) / static_cast<double>(vw));
    const float fy = static_cast<float>(1.0 - static_cast<double>(static_cast<float>(static_cast<double>(y) /
                                                                                    static_cast<double>(vh))));
    float adjust[4];
    adjust[0] = static_cast<float>(static_cast<double>(fx + fx) - 1.0);
    adjust[1] = static_cast<float>(static_cast<double>(fy + fy) - 1.0);
    adjust[2] = static_cast<float>(static_cast<double>((scaleX + scaleX) * static_cast<float>(videoWidth)) /
                                   static_cast<double>(vw));
    adjust[3] = static_cast<float>(static_cast<double>((scaleY + scaleY) * static_cast<float>(videoHeight)) /
                                   static_cast<double>(vh));
    const float mult[4] = {rgb, rgb, rgb, alpha};
    const uint32_t index = buffers->FrameNum;
    UploadSet(buffers, index);
    const BINKPLANETEXTURES& tex = buffers->Textures[index];
    // The A program when the set has an A texture (+0x84 of the PS3 record), else the "NPA" program.
    dotd::gfx::DrawVideoPlanes(tex.y, tex.cR, tex.cB, tex.a, adjust, mult, blend);
}

// 0x000af708 PS3Video_DestroyFrameTextures_maybe
void PS3Video_DestroyFrameTextures(BINKFRAMEBUFFERS* buffers) {
    for (BINKPLANETEXTURES& tex : buffers->Textures) {
        dotd::gfx::DestroyTexture(tex.y);
        dotd::gfx::DestroyTexture(tex.cR);
        dotd::gfx::DestroyTexture(tex.cB);
        dotd::gfx::DestroyTexture(tex.a);
        tex.y = tex.cR = tex.cB = tex.a = 0;
        tex.dirty = 0;
    }
    std::free(buffers->PlaneMemory);  // 0x000b00a8 PS3Video_DestroyFrameBuffers_maybe: the PBO
    buffers->PlaneMemory = nullptr;
    for (BINKFRAMEPLANESET& set : buffers->Frames) {
        set.YPlane.Buffer = set.cRPlane.Buffer = set.cBPlane.Buffer = set.APlane.Buffer = nullptr;
    }
}

// 0x000af8f8 PS3Video_CreateFrameBuffers_maybe: one block for all sets (the PS3's PBO, 128-byte aligned
// rows), each set Y | A | cR | cB, and a texture per allocated plane.
int32_t PS3Video_CreateFrameBuffers(BINKFRAMEBUFFERS* buffers) {
    const uint32_t yPitch = (buffers->YABufferWidth + 0x7fu) & ~0x7fu;
    const uint32_t cPitch = (buffers->cRcBBufferWidth + 0x7fu) & ~0x7fu;
    const uint32_t ySize = yPitch * buffers->YABufferHeight;
    const uint32_t cSize = cPitch * buffers->cRcBBufferHeight;
    const bool hasA = buffers->Frames[0].APlane.Allocate != 0;
    const uint32_t setSize = ySize + (hasA ? ySize : 0u) + 2u * cSize;
    uint8_t* memory = static_cast<uint8_t*>(std::calloc(static_cast<size_t>(setSize) * 2u, 1));
    if (memory == nullptr) return 0;
    buffers->PlaneMemory = memory;
    buffers->SetSize = setSize;
    for (int32_t i = 0; i < buffers->TotalFrames && i < 2; ++i) {
        uint8_t* base = memory + static_cast<size_t>(setSize) * static_cast<size_t>(i);
        BINKFRAMEPLANESET& set = buffers->Frames[i];
        BINKPLANETEXTURES& tex = buffers->Textures[i];
        tex = {};
        set.YPlane.Buffer = base;
        set.YPlane.BufferPitch = yPitch;
        tex.y = CreateFrameTexture(buffers->YABufferWidth, buffers->YABufferHeight);
        uint8_t* next = base + ySize;
        if (hasA) {
            set.APlane.Buffer = next;
            set.APlane.BufferPitch = yPitch;
            tex.a = CreateFrameTexture(buffers->YABufferWidth, buffers->YABufferHeight);
            next += ySize;
        }
        set.cRPlane.Buffer = next;
        set.cRPlane.BufferPitch = cPitch;
        tex.cR = CreateFrameTexture(buffers->cRcBBufferWidth, buffers->cRcBBufferHeight);
        set.cBPlane.Buffer = next + cSize;
        set.cBPlane.BufferPitch = cPitch;
        tex.cB = CreateFrameTexture(buffers->cRcBBufferWidth, buffers->cRcBBufferHeight);
        // Host: the sets start as a black picture (Y 16, Cr and Cb 128; an A plane stays 0), uploaded by the
        // first draw. The video is drawn every frame, also before Bink decoded into a set: the PS3 always has
        // the first frame by then, a decoder that waits for data (the web build) has not, and planes of zeros
        // would be shown as a green screen.
        std::memset(set.YPlane.Buffer, 16, ySize);
        std::memset(set.cRPlane.Buffer, 128, cSize);
        std::memset(set.cBPlane.Buffer, 128, cSize);
        tex.dirty = 1;
    }
    return 1;
}

// 0x000afd78 PS3Video_CreateShader_maybe: the PS3 creates the quad VBO once, keeps the viewport size and
// compiles the three Cg programs (cgCreateProgram from source). The GLSL programs are built on first draw.
int32_t PS3Video_CreateShader(uint32_t width, uint32_t height) {
    g_videoShader.viewportWidth = static_cast<float>(width);
    g_videoShader.viewportHeight = static_cast<float>(height);
    g_videoShader.created = true;
    return 1;
}
