// RwIm3D.cpp - the immediate-mode API (rwcore im3d.c) and the PSGL render-state block, ported for what
// they record and return. See RwIm3D.h.
//
// The PS3 keeps the immediate-mode globals at RWEngineInstance + [0xcfbba4]: +0x00 the transform
// pipeline, +0x04..+0x14 the render pipelines per primitive type (trilist, trifan, tristrip, linelist,
// polyline), then the pool rwIm3DPool at +0x38: numElements (16 bits) +0x38, elements +0x3c, stride
// +0x40 (0x24), and its stash: flags +0x44, ltm +0x48, ..., pipeline +0x64, primType +0x68, indices
// +0x6c, numIndices +0x70. RwIm3DEnd clears +0x38..+0x70.
#include "Renderware/rwcore/RwIm3D.h"

#include <cstring>
#include <utility>
#include <vector>

#include "Renderware/rwcore/RwDevice.h"
#include "crt/ppc_ops.h"
#include "platform/gfx/device.h"

namespace {

struct Im3DPool {
    RwUInt16 numElements = 0;            // +0x38
    RwIm3DVertex* elements = nullptr;    // +0x3c
    RwInt32 stride = 0;                  // +0x40
    RwUInt32 flags = 0;                  // +0x44 (stash.flags)
    RwMatrix* ltm = nullptr;             // +0x48 (stash.ltm)
    RwPrimitiveType primType = rwPRIMTYPENAPRIMTYPE;  // +0x68
    RwImVertexIndex* indices = nullptr;  // +0x6c
    RwInt32 numIndices = 0;              // +0x70
};

Im3DPool g_pool;
RwIm3DRenderStates g_states;
std::vector<RwIm3DDraw> g_draws;
// dotd perf: the vertex and index arrays of the draws recorded in earlier frames, emptied, their memory kept for the
// next draws (RwIm3DBeginFrame gives them back), so a frame's draws do not allocate once the arrays have grown. They are
// handed out in the order of the last frame's draws (its draw n's arrays to the next frame's draw n), which keeps the
// large arrays with the large draws.
std::vector<std::vector<RwIm3DVertex>> g_freeVertices;
std::vector<std::vector<RwImVertexIndex>> g_freeIndices;

template <typename T>
std::vector<T> TakeFree(std::vector<std::vector<T>>& pool) {
    if (pool.empty()) return std::vector<T>();
    std::vector<T> v = std::move(pool.back());
    pool.pop_back();
    return v;
}

void RecycleDraws() {
    for (auto it = g_draws.rbegin(); it != g_draws.rend(); ++it) {  // the last draw's arrays deepest
        RwIm3DDraw& d = *it;
        d.vertices.clear();
        d.indices.clear();
        // (only arrays that hold memory: a draw recorded without its geometry has none to give back)
        if (d.vertices.capacity() != 0) g_freeVertices.push_back(std::move(d.vertices));
        if (d.indices.capacity() != 0) g_freeIndices.push_back(std::move(d.indices));
    }
    g_draws.clear();
}

// What the render pipeline (OpenGLSubmitNoLight.csl, DrawPSGLImmediateGeometry 0x76b610) draws: the
// pool's vertices through the LTM, glDrawRangeElements with numIndices 32-bit indices when the stash has
// indices, else glDrawArrays(0, numElements). It always returns TRUE.
RwBool SubmitPool() {
    RwIm3DDraw draw;
    draw.primType = g_pool.primType;
    draw.transformFlags = g_pool.flags;
    draw.hasLtm = g_pool.ltm != nullptr;
    if (g_pool.ltm != nullptr) {
        draw.ltm = *g_pool.ltm;
    } else {
        std::memset(&draw.ltm, 0, sizeof draw.ltm);
    }
    draw.indexed = g_pool.indices != nullptr;
    const RwUInt32 numIndices = draw.indexed && g_pool.numIndices > 0 ? static_cast<RwUInt32>(g_pool.numIndices) : 0;
    draw.numVertices = g_pool.numElements;
    draw.numIndices = numIndices;
    // perf: the geometry is copied into the record only when no device draws it (RwIm3D.h).
    if (!dotd::gfx::IsReady()) {
        draw.vertices = TakeFree(g_freeVertices);
        draw.indices = TakeFree(g_freeIndices);
        draw.vertices.assign(g_pool.elements, g_pool.elements + g_pool.numElements);
        if (numIndices != 0) draw.indices.assign(g_pool.indices, g_pool.indices + numIndices);
    }
    draw.states = g_states;
    // C1.4: drawn now, from the pool's arrays (the PS3 sends them to the GPU here); no-op without a device
    RwDevice_DrawIm3D(draw, g_pool.elements, g_pool.numElements, numIndices != 0 ? g_pool.indices : nullptr, numIndices);
    g_draws.push_back(std::move(draw));
    return 1;
}

// The primitive types the jump tables at 0x76114c / 0x7612fc accept (1..5); the PS3 errors on the rest
// (E_RW 0x25) and then executes a null pipeline.
bool ValidPrimType(RwPrimitiveType primType) {
    return static_cast<RwUInt32>(primType) - 1u <= 4u;
}

}  // namespace

// 0x00761400 RwIm3DTransform
void* RwIm3DTransform(RwIm3DVertex* pVerts, RwUInt32 numVerts, RwMatrix* ltm, RwUInt32 flags) {
    if (numVerts > 0x10000u) return nullptr;  // _rwerror(0x32) + RwErrorSet
    // BUG(original): numElements is a 16-bit field (sth), so exactly 0x10000 vertices store 0.
    g_pool.numElements = static_cast<RwUInt16>(numVerts);
    g_pool.elements = pVerts;
    g_pool.stride = 0x24;
    g_pool.ltm = ltm;
    g_pool.flags = flags | rwIM3D_VERTEXXYZ | rwIM3D_VERTEXRGBA;
    // RW_ExecutePipeline(transform pipeline, &pool, TRUE): its only node (RxPSGLIm3DTransform 0x76b570)
    // remembers the pool for the render node and returns TRUE, so the call succeeds.
    return pVerts;
}

// 0x00760a90 RwIm3DEnd
RwBool RwIm3DEnd() {
    if (g_pool.elements == nullptr) return 0;
    g_pool = Im3DPool();
    return 1;
}

// 0x00761028 RwIm3DRenderPrimitive
RwBool RwIm3DRenderPrimitive(RwPrimitiveType primType) {
    if (g_pool.elements == nullptr) return 0;  // _rwerror(0x23) + RwErrorSet
    g_pool.primType = primType;
    g_pool.indices = nullptr;
    g_pool.numIndices = g_pool.numElements;
    if (!ValidPrimType(primType)) {
        // _rwerror(0x25) + RwErrorSet. BUG(original): RW_ExecutePipeline then runs with a null pipeline
        // (it reads address 8 and crashes).
        return 0;
    }
    return SubmitPool();
}

// 0x00761220 RwIm3DRenderIndexedPrimitive
RwBool RwIm3DRenderIndexedPrimitive(RwPrimitiveType primType, RwImVertexIndex* indices, RwInt32 numIndices) {
    if (g_pool.elements == nullptr) return 0;  // _rwerror(0x23) + RwErrorSet
    g_pool.primType = primType;
    g_pool.indices = indices;
    g_pool.numIndices = numIndices;
    if (!ValidPrimType(primType)) return 0;  // _rwerror(0x25); BUG(original): null pipeline, as above
    if (primType == rwPRIMTYPELINELIST) {
        g_pool.numIndices = (numIndices / 2) * 2;  // srawi/addze: signed, toward zero
    } else if (primType == rwPRIMTYPETRILIST) {
        g_pool.numIndices = (numIndices / 3) * 3;  // mulhw 0x55555556: signed, toward zero
    }
    return SubmitPool();
}

namespace {

// RwPSGL_RenderStateSet 0x73c410 dispatches through the setter table at 0xcefcb4 (filled by
// RwPSGL_SetupDefaultRenderStates_maybe); a null entry returns 0.
RwBool SetState(RwRenderState state, intptr_t v) {
    RwIm3DRenderStates& s = g_states;
    const RwInt32 value = static_cast<RwInt32>(v);
    switch (state) {
        case rwRENDERSTATETEXTURERASTER:  // 0x73f2a0 (0 for raster formats the driver cannot bind)
            s.textureRaster = reinterpret_cast<void*>(v);
            return 1;
        case rwRENDERSTATETEXTUREADDRESS:  // 0x73c378: the U setter, then the V setter
            if (static_cast<RwUInt32>(value) - 1u > 2u) return 0;
            s.textureAddressU = value;
            s.textureAddressV = value;
            return 1;
        case rwRENDERSTATETEXTUREADDRESSU:  // 0x73eb80: wrap, mirror, clamp
            if (static_cast<RwUInt32>(value) - 1u > 2u) return 0;
            s.textureAddressU = value;
            return 1;
        case rwRENDERSTATETEXTUREADDRESSV:  // 0x73e380
            if (static_cast<RwUInt32>(value) - 1u > 2u) return 0;
            s.textureAddressV = value;
            return 1;
        case rwRENDERSTATEZTESTENABLE:  // 0x73d7d8: the word as given
            s.zTestEnable = value;
            return 1;
        case rwRENDERSTATESHADEMODE:  // 0x73dd70: flat or gouraud only
            if (value != 1 && value != 2) return 0;
            s.shadeMode = value;
            return 1;
        case rwRENDERSTATEZWRITEENABLE:  // 0x73d860
            s.zWriteEnable = value;
            return 1;
        case rwRENDERSTATETEXTUREFILTER:  // 0x73df28 (per raster on the PS3)
            s.textureFilter = value;
            return 1;
        case rwRENDERSTATESRCBLEND:  // 0x73dbb8: 1..11 (the GL table at 0xc45a70 has no -1 there)
            if (static_cast<RwUInt32>(value) - 1u > 10u) return 0;
            s.srcBlend = value;
            return 1;
        case rwRENDERSTATEDESTBLEND:  // 0x73db28: 1..10 (rwBLENDSRCALPHASAT is not a destination)
            if (static_cast<RwUInt32>(value) - 1u > 9u) return 0;
            s.destBlend = value;
            return 1;
        case rwRENDERSTATEVERTEXALPHAENABLE:  // 0x73dc48: any non-zero value is stored as 1
            s.vertexAlphaEnable = v != 0 ? 1 : 0;
            return 1;
        case rwRENDERSTATEFOGENABLE:  // 0x73d8d8: likewise
            s.fogEnable = v != 0 ? 1 : 0;
            return 1;
        case rwRENDERSTATEFOGCOLOR:  // 0x73de68
            s.fogColor = value;
            return 1;
        case rwRENDERSTATEFOGTYPE:  // 0x73c808
            s.fogType = value;
            return 1;
        case rwRENDERSTATEFOGDENSITY: {  // 0x73c880: the value is a pointer to the float (lfs f13, 0(r3))
            s.fogDensity = *reinterpret_cast<const RwReal*>(v);
            return 1;
        }
        case rwRENDERSTATECULLMODE:  // 0x73c9f8: none / back / front
            if (value == 1) {
                s.cullEnabled = 0;
                return 1;
            }
            if (value == 2 || value == 3) {
                s.cullEnabled = 1;
                s.cullFace = value;
                return 1;
            }
            return 0;
        case rwRENDERSTATESTENCILENABLE: s.stencilEnable = value; return 1;
        case rwRENDERSTATESTENCILFAIL: s.stencilFail = value; return 1;
        case rwRENDERSTATESTENCILZFAIL: s.stencilZFail = value; return 1;
        case rwRENDERSTATESTENCILPASS: s.stencilPass = value; return 1;
        case rwRENDERSTATESTENCILFUNCTION: s.stencilFunction = value; return 1;
        case rwRENDERSTATESTENCILFUNCTIONREF: s.stencilFunctionRef = value; return 1;
        case rwRENDERSTATESTENCILFUNCTIONMASK: s.stencilFunctionMask = value; return 1;
        case rwRENDERSTATESTENCILFUNCTIONWRITEMASK: s.stencilWriteMask = value; return 1;
        case rwRENDERSTATEALPHATESTFUNCTION:  // 0x73c940
            s.alphaTestFunction = value;
            return 1;
        case rwRENDERSTATESRCBLENDALPHA: s.srcBlendAlpha = value; return 1;    // 0x73da78
        case rwRENDERSTATEDESTBLENDALPHA: s.destBlendAlpha = value; return 1;  // 0x73d9c8
        case rwRENDERSTATEALPHATESTFUNCTIONREF:  // 0x73c8c8: kept as a byte (stb)
            s.alphaTestFunctionRef = static_cast<RwUInt8>(value);
            return 1;
        default:  // 0, 5 (perspective), 13 (border colour), 18, 19 and beyond 32: no setter
            return 0;
    }
}

}  // namespace

// RwRenderStateSet -> RWEngine +0x20 -> RwPSGL_RenderStateSet 0x73c410
RwBool RwRenderStateSet(RwRenderState state, void* value) {
    if (static_cast<RwUInt32>(state) > 32u) return 0;
    return SetState(state, reinterpret_cast<intptr_t>(value));
}

// RwRenderStateGet -> RWEngine +0x24 -> RwPSGL_RenderStateGet 0x73c478
RwBool RwRenderStateGet(RwRenderState state, void* value) {
    const RwIm3DRenderStates& s = g_states;
    RwInt32 word;
    switch (state) {
        case rwRENDERSTATETEXTURERASTER:
            *static_cast<void**>(value) = s.textureRaster;
            return 1;
        case rwRENDERSTATETEXTUREADDRESS:  // V when U == V, else rwTEXTUREADDRESSNATEXTUREADDRESS
            word = s.textureAddressV == s.textureAddressU ? s.textureAddressV : 0;
            break;
        case rwRENDERSTATETEXTUREADDRESSU: word = s.textureAddressU; break;
        case rwRENDERSTATETEXTUREADDRESSV: word = s.textureAddressV; break;
        case rwRENDERSTATETEXTUREPERSPECTIVE: word = 1; break;
        case rwRENDERSTATEZTESTENABLE: word = s.zTestEnable; break;
        case rwRENDERSTATESHADEMODE: word = s.shadeMode; break;
        case rwRENDERSTATEZWRITEENABLE: word = s.zWriteEnable; break;
        case rwRENDERSTATETEXTUREFILTER: word = s.textureFilter; break;
        case rwRENDERSTATESRCBLEND: word = s.srcBlend; break;
        case rwRENDERSTATEDESTBLEND: word = s.destBlend; break;
        case rwRENDERSTATEVERTEXALPHAENABLE: word = s.vertexAlphaEnable; break;
        case rwRENDERSTATEFOGENABLE: word = s.fogEnable; break;
        case rwRENDERSTATEFOGCOLOR: word = s.fogColor; break;
        case rwRENDERSTATEFOGTYPE: word = s.fogType; break;
        case rwRENDERSTATEFOGDENSITY:  // fctidz of the float, the low word stored
            word = static_cast<RwInt32>(ppc::fctidz(s.fogDensity));
            break;
        case rwRENDERSTATECULLMODE: word = s.cullEnabled == 0 ? 1 : s.cullFace; break;
        case rwRENDERSTATESTENCILENABLE: word = s.stencilEnable; break;
        case rwRENDERSTATESTENCILFAIL: word = s.stencilFail; break;
        case rwRENDERSTATESTENCILZFAIL: word = s.stencilZFail; break;
        case rwRENDERSTATESTENCILPASS: word = s.stencilPass; break;
        case rwRENDERSTATESTENCILFUNCTION: word = s.stencilFunction; break;
        case rwRENDERSTATESTENCILFUNCTIONREF: word = s.stencilFunctionRef; break;
        case rwRENDERSTATESTENCILFUNCTIONMASK: word = s.stencilFunctionMask; break;
        case rwRENDERSTATESTENCILFUNCTIONWRITEMASK: word = s.stencilWriteMask; break;
        case rwRENDERSTATEALPHATESTFUNCTION: word = s.alphaTestFunction; break;
        case rwRENDERSTATESRCBLENDALPHA: word = s.srcBlendAlpha; break;
        case rwRENDERSTATEDESTBLENDALPHA: word = s.destBlendAlpha; break;
        case rwRENDERSTATEALPHATESTFUNCTIONREF: word = s.alphaTestFunctionRef; break;  // lbz
        default:  // 0, 13, 18, 19, > 32: nothing written
            return 0;
    }
    *static_cast<RwInt32*>(value) = word;
    return 1;
}

const std::vector<RwIm3DDraw>& RwIm3DFrameDraws() { return g_draws; }

void RwIm3DBeginFrame() { RecycleDraws(); }

const RwIm3DRenderStates& RwIm3DCurrentStates() { return g_states; }

void RwIm3DResetForTest() {
    g_pool = Im3DPool();
    g_states = RwIm3DRenderStates();
    RecycleDraws();
}
