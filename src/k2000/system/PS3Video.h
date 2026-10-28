// PS3Video.h - the PSGL side of the Bink videos (original unit 0xaee90-0xb01f0, not a registered class):
// the frame-buffer textures, the YUV shader and the screen quad. The PS3 wraps the Bink planes in a PBO as
// GL_LUMINANCE textures and compiles three Cg programs; the remake keeps the planes in host memory and
// draws through platform/gfx/video_planes.h.
#pragma once
#include <cstdint>

#include "platform/video/bink.h"

// 0x000aee90 PS3Video_SelectNextFrame_maybe: waits for the GPU to release the next set (its fence).
void PS3Video_SelectNextFrame(BINKFRAMEBUFFERS* buffers);
// 0x000aef60 DrawPSGLTexturedScreenQuad: the current set as a quad at (x, y) pixels, video size x scale.
// useVertexMultiplier: the PS3's 9th argument (DrawPS3VideoFrameQuad passes 0: rgb multiplier 1.0).
void DrawPSGLTexturedScreenQuad(float x, float y, float scaleX, float scaleY, float alpha, BINKFRAMEBUFFERS* buffers,
                                uint32_t videoWidth, uint32_t videoHeight, int32_t useVertexMultiplier,
                                bool blend);
// 0x000af708 PS3Video_DestroyFrameTextures_maybe
void PS3Video_DestroyFrameTextures(BINKFRAMEBUFFERS* buffers);
// 0x000af8f8 PS3Video_CreateFrameBuffers_maybe: plane memory and textures for every set; 0 on failure.
int32_t PS3Video_CreateFrameBuffers(BINKFRAMEBUFFERS* buffers);
// 0x000afd78 PS3Video_CreateShader_maybe: the shader state for a viewport of width x height pixels.
int32_t PS3Video_CreateShader(uint32_t width, uint32_t height);
// 0x000aea40 PS3Video_InitRenderer_maybe (PS3_CKVideo.cpp): BinkPS3 renderer init, then the shader for
// the camera context's raster size.
void PS3Video_InitRenderer();
// 0x000ae548 PS3Video_Shutdown_maybe (PS3_CKVideo.cpp)
void PS3Video_Shutdown();
