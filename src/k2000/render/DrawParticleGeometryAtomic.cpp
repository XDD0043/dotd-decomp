// DrawParticleGeometryAtomic.cpp - reconstructed original translation unit 0x89908-0x89a70 (GAME_TOC1, main_toc1).
// Primary owner: DrawParticleGeometryAtomic (not a registered class): CParticleGeometry's vt+0x5c.
//
// Checklist, address order.
//   [x] 0x89908  DrawParticleGeometryAtomic
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "k2000/geometry/CGeometry.h"

// 0x00089908 DrawParticleGeometryAtomic (CParticleGeometry_Render, vt+0x5c): the shader's particle flags
// (ParticleDraw_SetShaderParticleFlags_maybe 0x88190 on CShaderManagerPSGL +0x8c: render flags 0x2000000 /
// 0x100000 and the byte +0x28; the PTank's shader hook builds its key with them), fog (state 14) kept only with
// render flag 0x400000 and fog on, no culling (state 20 = 1) around the atomic's render callback, then
// culling back (2) and the fog restored.
void CParticleGeometry::Render(IKTime* /*frameClock*/) {
    ParticleDraw_SetShaderParticleFlags(this);
    RwInt32 fog = 0;
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &fog);
    RwInt32 fogOn = 0;
    if ((m_BitProperties & 0x400000) != 0) fogOn = fog == 1 ? 1 : 0;
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, reinterpret_cast<void*>(static_cast<intptr_t>(fogOn)));
    RwRenderStateSet(rwRENDERSTATECULLMODE, reinterpret_cast<void*>(static_cast<intptr_t>(1)));
    RpAtomic* atomic = m_pRpAtomic;
    if (atomic->renderCallBack != nullptr) atomic->renderCallBack(atomic);  // natively null for raw atomics
    RwRenderStateSet(rwRENDERSTATECULLMODE, reinterpret_cast<void*>(static_cast<intptr_t>(2)));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, reinterpret_cast<void*>(static_cast<intptr_t>(fog)));
}
