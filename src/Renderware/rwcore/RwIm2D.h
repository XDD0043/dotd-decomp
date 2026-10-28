// RwIm2D.h - RenderWare's immediate-mode 2D API (screen-space vertices in raster pixels) as the K code
// uses it: RWEngine +0x34 (RwIm2DRenderIndexedPrimitive, DrawScreenColorQuad 0xa31e8) and the near screen
// z at RWEngine +0x18. Drawn through the device layer (rwcore/RwDevice.h) with the render states in force.
#pragma once
#include "Renderware/rwcore/RwTypes.h"

// The PS3 Im2D vertex (0x24), as DrawScreenColorQuad fills it: position in raster pixels (y down), the
// screen z, the colour, then projective texture coordinates (s, t, r, q: u = s / q, v = t / q) and the
// reciprocal camera z.
struct RwIm2DVertex {
    RwReal x;             // +0x00
    RwReal y;             // +0x04
    RwReal z;             // +0x08
    RwRGBA emissiveColor; // +0x0c
    RwReal s;             // +0x10
    RwReal t;             // +0x14
    RwReal r;             // +0x18
    RwReal q;             // +0x1c
    RwReal recipZ;        // +0x20
};
DOTD_ASSERT_SIZE(RwIm2DVertex, 0x24);

// RWEngine +0x18: the near screen z (RwIm2DGetNearScreenZ).
RwReal RwIm2DGetNearScreenZ();
// RWEngine +0x34: draws numIndices indices into vertices (screen space of the current camera's raster).
RwBool RwIm2DRenderIndexedPrimitive(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices,
                                    RwImVertexIndex* indices, RwInt32 numIndices);
// RWEngine +0x30: draws numVertices vertices (no index list; DrawFullscreenRasterQuad's triangle strip).
RwBool RwIm2DRenderPrimitive(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices);
