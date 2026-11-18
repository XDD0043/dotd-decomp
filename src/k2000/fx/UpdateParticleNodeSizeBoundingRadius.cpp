// Reconstructed original translation unit: 0xe5c80-0xe5fb8 (GAME_TOC1, main_toc1), 1 functions, 1 live.
// Primary owner: UpdateParticleNodeSizeBoundingRadius (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xe5c80  UpdateParticleNodeSizeBoundingRadius
#include "k2000/fx/UpdateParticleNodeSizeBoundingRadius.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "crt/ppc_ops.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"

namespace {
// 0x00010690 Math_Sqrtf: the double square root rounded to float.
float MathSqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }

constexpr float kHalf = 0.5f;  // TOC -0x4ed0

// The size property (rpPRTSTDPROPERTYCODEEMITTERPRTSIZE, rpprtstd.h RpPrtStdEmitterPrtSize): start size, its bias, end
// size, its bias (eight floats). The radius is half the length of start + bias, or of end + bias when that is not
// shorter (fcmpu + bge: a NaN keeps the start's).
void SizeRadius(CParticlesNodeFx* node, const float* size) {
    const float startY = size[1] + size[3];
    const float startX = size[0] + size[2];
    const float start = MathSqrtf(ppc::fmadds(startX, startX, startY * startY)) * kHalf;
    node->m_fBoundingRadius = start;
    const float endY = size[5] + size[7];
    const float endX = size[4] + size[6];
    const float endSquared = ppc::fmadds(endX, endX, endY * endY);
    const float end = MathSqrtf(endSquared) * kHalf;
    node->m_fBoundingRadius = (end >= start) ? MathSqrtf(endSquared) * kHalf : node->m_fBoundingRadius;
}
}  // namespace

// 0x000e5c80 UpdateParticleNodeSizeBoundingRadius
void UpdateParticleNodeSizeBoundingRadius(CParticlesNodeFx* node) {
    const int32_t multiOffset =
        RpPrtStdPropTabGetPropOffset(node->m_pRpPrtStdEmitter->emtClass->propTab, rpPRTADVPROPERTYCODEEMITTERPRTMULTISIZE);
    if (multiOffset != -1) {
        const uint8_t* multi = reinterpret_cast<const uint8_t*>(node->m_pRpPrtStdEmitter) + multiOffset;
        const int32_t sizeOffset =
            RpPrtStdPropTabGetPropOffset(node->m_pRpPrtStdEmitter->emtClass->propTab, rpPRTSTDPROPERTYCODEEMITTERPRTSIZE);
        // BUG(original): the size property's offset is not checked here (-1 would read one byte before the emitter).
        const float* size = reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(node->m_pRpPrtStdEmitter) + sizeOffset);
        SizeRadius(node, size);
        // The multi size keys (RpPrtAdvEmtPrtMultiSize: the count at +0, the keys of 0x18 bytes {time, timeBias, midSize,
        // midSizeBias}; the PS3 reads the list pointer at +4, which points at +0x14, where dotd reads them, see
        // RpPrtAdvRuntime.cpp): the radius grows to each key's half length.
        int32_t count;
        std::memcpy(&count, multi, 4);
        const uint8_t* key = multi + 0x14;
        for (int32_t i = 0; i != count; ++i, key += 0x18) {
            const float current = node->m_fBoundingRadius;
            float k[6];
            std::memcpy(k, key, sizeof(k));
            const float y = k[3] + k[5];
            const float x = k[2] + k[4];
            const float squared = ppc::fmadds(x, x, y * y);
            const float radius = MathSqrtf(squared) * kHalf;
            node->m_fBoundingRadius = (radius < current) ? current : MathSqrtf(squared) * kHalf;  // fcmpu + blt
        }
        return;
    }
    const int32_t sizeOffset =
        RpPrtStdPropTabGetPropOffset(node->m_pRpPrtStdEmitter->emtClass->propTab, rpPRTSTDPROPERTYCODEEMITTERPRTSIZE);
    if (sizeOffset != -1) {
        SizeRadius(node, reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(node->m_pRpPrtStdEmitter) + sizeOffset));
        return;
    }
    const int32_t tankOffset =
        RpPrtStdPropTabGetPropOffset(node->m_pRpPrtStdEmitter->emtClass->propTab, rpPRTSTDPROPERTYCODEEMITTERPTANK);
    if (tankOffset == -1) {
        node->m_fBoundingRadius = 0.0f;  // stw 0
        return;
    }
    // The PTank's constant size (its plugin data +0xc0, rpPTANKDFLAGCNSSIZE): half its length.
    const RpPrtStdEmitterPTank* tank = reinterpret_cast<const RpPrtStdEmitterPTank*>(
        reinterpret_cast<const uint8_t*>(node->m_pRpPrtStdEmitter) + tankOffset);
    float constantSize[2];
    std::memcpy(constantSize, tank->pTank->ptank->renderC0, sizeof(constantSize));
    node->m_fBoundingRadius = MathSqrtf(ppc::fmadds(constantSize[0], constantSize[0], constantSize[1] * constantSize[1])) * kHalf;
}
