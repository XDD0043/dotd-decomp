// RwIm2D.cpp - see RwIm2D.h.
#include "Renderware/rwcore/RwIm2D.h"

#include "Renderware/rwcore/RwDevice.h"

// The PSGL driver's near screen z (RWEngine +0x18): 0 (GL's window z of the near plane, before the
// depth range; the value is only copied into the vertices).
RwReal RwIm2DGetNearScreenZ() { return 0.0f; }

RwBool RwIm2DRenderIndexedPrimitive(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices,
                                    RwImVertexIndex* indices, RwInt32 numIndices) {
    if (vertices == nullptr || numVertices <= 0) return 0;
    RwDevice_DrawIm2D(primType, vertices, numVertices, indices, numIndices);
    return 1;
}

RwBool RwIm2DRenderPrimitive(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices) {
    if (vertices == nullptr || numVertices <= 0) return 0;
    RwDevice_DrawIm2D(primType, vertices, numVertices, nullptr, 0);
    return 1;
}
