// video_planes.h - drawing Bink frames: R8 plane textures and the YUV(A) -> RGB(A) quad (the PS3 build's
// PSGL path: PS3Video_CreateFrameTexture 0xaf518 wraps each plane as a GL_LUMINANCE texture,
// DrawPSGLTexturedScreenQuad 0xaef60 draws a unit quad with the Cg programs compiled by
// PS3Video_CreateShader 0xafd78). Platform code (GL 3.3 core). Family gfx proposed these in device.h; they
// live here until the merge puts them together.
#pragma once
#include <cstdint>

namespace dotd::gfx {

// A width x height single-channel 8-bit texture, linear filtering, clamp to edge (as the PS3's). 0 when the
// device is not ready.
uint32_t CreateTextureR8(int width, int height);
// Replaces the texture's pixels (rows of `pitch` bytes, top row first).
void UpdateTextureR8(uint32_t texture, int width, int height, const void* pixels, int pitch);

// Draws the video quad into the bound target: the PS3's unit quad (0,0) (1,0) (0,-1) (1,-1) with UVs
// (0,0) (1,0) (0,1) (1,1), Pos.xy = Pos.xy * adjust.zw + adjust.xy (NDC), and the BT.601 conversion of the
// PS3's Cg programs with their exact constants; the colour is multiplied by mult (rgba). a != 0 selects the
// Aplane program (alpha = the A plane), a == 0 the opaque one (alpha = 1), as the PS3 chooses by the frame
// set's A texture. alpha: blending SRC_ALPHA / ONE_MINUS_SRC_ALPHA (the PS3: vertex alpha on and blend
// table entry 1 when the video's alpha level is not 0xff); otherwise blending off. Depth and culling off.
void DrawVideoPlanes(uint32_t y, uint32_t cr, uint32_t cb, uint32_t a, const float adjust[4], const float mult[4],
                     bool alpha);

}  // namespace dotd::gfx
