// gstate.cpp - RW 3.7 tool/2d/gstate.c, ported from the PS3 library code (0x711ae8-0x7133a0): the toolkit's
// open/close, the device (camera, metric, flatness, layer depth) and the current transformation matrix
// (CTM) stack. See Rt2d.h; the globals block is Rt2dInternal.h.
//
// Not ported (the front end never reaches them): _rt2dDeviceOpen_maybe 0x712410 / _rt2dDeviceClose_maybe
// 0x7125d0 (dead copies of Rt2dOpen's and Rt2dClose's device parts), Rt2dVisible 0x712690,
// Rt2dDeviceGetClippath 0x712ab8.
#include "Renderware/rt2d/Rt2dInternal.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"

Rt2dGlobalVars rt2dGlobals;

namespace {

// The top of the CTM stack (inlined everywhere as ctm[mtos]).
inline RwMatrix* Top() { return rt2dGlobals.ctm[rt2dGlobals.mtos]; }

// An identity matrix written field by field, as the PS3 inlines it (flags |= identity | orthonormal).
void SetIdentityInline(RwMatrix* m) {
    m->right.x = 1.0f;
    m->at.z = 1.0f;
    m->up.y = 1.0f;
    m->right.y = 0.0f;
    m->up.x = 0.0f;
    m->right.z = 0.0f;
    m->up.z = 0.0f;
    m->at.y = 0.0f;
    m->at.x = 0.0f;
    m->pos.x = 0.0f;
    m->pos.z = 0.0f;
    m->pos.y = 0.0f;
    m->flags |= rwMATRIXINTERNALIDENTITY | rwMATRIXTYPEORTHONORMAL;
}

}  // namespace

// 0x007130e8 Rt2dOpen: the free lists and per-file state, the CTM stack (one identity matrix), the
// metric (identity), the device (0, 0, 1, 1), tolerance 0.5, flatness depth 7, layer depth 1, the index
// table 0..255; with a camera that has a frame buffer, the view window and port and the device's aspect.
RwBool Rt2dOpen(RwCamera* cam) {
    Rt2dGlobalVars& g = rt2dGlobals;
    g.TransformFlags = 0;
    _rt2dTriangulateOpen();
    _rt2dPathOpen();
    _rt2dBrushOpen();
    _rt2dFontOpen();
    _rt2dObjectOpen();
    g.mtos = 0;
    g.ctm[0] = RwMatrixCreate();
    SetIdentityInline(Top());
    g.tolerance = 0.5f;
    g.CTMValid = 0;
    g.flatDepth = 7;
    g.sqToleranceValid = 0;
    g.layerDepth = 1.0f;
    SetIdentityInline(&g.metricMtx);
    for (RwUInt32 i = 0; i < 0x100; ++i) g.topo[i] = static_cast<RwImVertexIndex>(i);
    for (RwInt32 i = 1; i < 32; ++i) g.ctm[i] = nullptr;
    g.deviceX = 0.0f;
    g.deviceY = 0.0f;
    g.deviceW = 1.0f;
    g.deviceH = 1.0f;
    g.overrideCTM = nullptr;
    g.triIdxCache = nullptr;
    g.triIdxCacheSize = 0;
    g.viewCamera = cam;
    if (cam != nullptr && cam->frameBuffer != nullptr) {
        RwRaster* raster = cam->frameBuffer;
        g.vp.x = static_cast<RwReal>(raster->width);   // fcfid + frsp
        g.vp.y = static_cast<RwReal>(raster->height);
        const RwReal vwx = cam->viewWindow.x + cam->viewWindow.x;
        const RwReal vwy = cam->viewWindow.y + cam->viewWindow.y;
        g.vw.x = vwx;
        g.CTMValid = 0;
        g.deviceY = 0.0f;
        g.deviceX = 0.0f;
        g.vw.y = vwy;
        if (vwx > vwy) {
            g.deviceH = 1.0f;
            g.deviceW = vwx / vwy;
        } else {
            g.deviceW = 1.0f;
            g.deviceH = vwy / vwx;
        }
    }
    return 1;  // the PS3 sets no return value: r3 still holds RwMatrixCreate's result (non-zero)
}

// 0x00713000 Rt2dClose
RwBool Rt2dClose() {
    Rt2dGlobalVars& g = rt2dGlobals;
    for (RwMatrix*& m : g.ctm) {
        if (m != nullptr) {
            RwMatrixDestroy(m);
            m = nullptr;
        }
    }
    g.mtos = 0;
    if (g.triIdxCache != nullptr) {
        RwFree(g.triIdxCache);
        g.triIdxCache = nullptr;
        g.triIdxCacheSize = 0;
    }
    _rt2dObjectClose();
    _rt2dFontClose();
    _rt2dBrushClose();
    _rt2dPathClose();
    _rt2dTriangulateClose();
    g.viewCamera = nullptr;
    return 1;  // r3 still holds Rt2d_DestroyFreeLists_maybe's 1
}

// 0x00711b78 Rt2dDeviceSetCamera: the camera, and with a frame buffer the view window and port and the
// device's aspect (as Rt2dOpen). 0 without a frame buffer.
RwBool Rt2dDeviceSetCamera(RwCamera* cam) {
    Rt2dGlobalVars& g = rt2dGlobals;
    g.viewCamera = cam;
    if (cam == nullptr || cam->frameBuffer == nullptr) return 0;
    RwRaster* raster = cam->frameBuffer;
    g.vp.x = static_cast<RwReal>(raster->width);
    const RwReal vwx = cam->viewWindow.x + cam->viewWindow.x;
    g.vp.y = static_cast<RwReal>(raster->height);
    const RwReal vwy = cam->viewWindow.y + cam->viewWindow.y;
    g.vw.x = vwx;
    g.CTMValid = 0;
    g.deviceY = 0.0f;
    g.deviceX = 0.0f;
    g.vw.y = vwy;
    if (vwx > vwy) {
        g.deviceH = 1.0f;
        g.deviceW = vwx / vwy;
    } else {
        g.deviceW = 1.0f;
        g.deviceH = vwy / vwx;
    }
    return 1;
}

// 0x00711c48 Rt2dDeviceGetCamera
RwCamera* Rt2dDeviceGetCamera() { return rt2dGlobals.viewCamera; }

// 0x00711ae8 Rt2dDeviceGetMetric
RwBool Rt2dDeviceGetMetric(RwReal* x, RwReal* y, RwReal* w, RwReal* h) {
    *x = rt2dGlobals.deviceX;
    *y = rt2dGlobals.deviceY;
    *w = rt2dGlobals.deviceW;
    *h = rt2dGlobals.deviceH;
    return 1;
}

// 0x00711b18 Rt2dDeviceSetFlat: the flatness tolerance (positive only).
RwBool Rt2dDeviceSetFlat(RwReal r) {
    if (!(r > 0.0f)) return 0;
    rt2dGlobals.sqToleranceValid = 0;
    rt2dGlobals.tolerance = r;
    return 1;
}

// 0x00711b48 Rt2dDeviceSetLayerDepth_maybe (positive only).
RwBool Rt2dDeviceSetLayerDepth(RwReal depth) {
    if (!(depth > 0.0f)) return 0;
    rt2dGlobals.CTMValid = 0;
    rt2dGlobals.layerDepth = depth;
    return 1;
}

// 0x00711c58 Rt2dDeviceSetIm3DTransformFlags_maybe
RwBool Rt2dDeviceSetIm3DTransformFlags(RwUInt32 flags) {
    rt2dGlobals.TransformFlags = flags;
    return 1;
}

// 0x00711da0 UI2D_GetCompositeMatrix_maybe: the CTM in camera space. With the PS3's override matrix set,
// a copy of it. Otherwise (re)builds CTM2d = top * metric, scaled by the layer depth (1 for a parallel
// camera), by (-s, s, 1) with s the smaller view-window side, and moved by (vw.x/2, -vw.y/2) x depth;
// iCTM2d its inverse; then CTM = CTM2d * the camera frame's LTM.
RwMatrix* _rt2dCTMGetComposite() {
    Rt2dGlobalVars& g = rt2dGlobals;
    if (g.overrideCTM != nullptr) {
        g.CTM = *g.overrideCTM;
        return &g.CTM;
    }
    if (g.CTMValid == 0) {
        RwReal depth;
        RwReal zScale;
        if (g.viewCamera->projectionType == rwPARALLEL) {
            depth = 1.0f;
            zScale = 1.0f;
        } else {
            depth = g.layerDepth;
            zScale = 1.0f;
        }
        alignas(16) RwMatrix tmp;
        RwMatrixMultiply(&tmp, Top(), &g.metricMtx);
        const RwReal vwx = g.vw.x;
        const RwReal vwy = g.vw.y;
        RwV3d v = {depth, depth, zScale};
        RwMatrixScale(&tmp, &v, rwCOMBINEPOSTCONCAT);
        RwReal s = vwx;
        if (vwy <= vwx) s = vwy;  // fcmpu; ble -> vw.y
        v = RwV3d{-s, s, zScale};
        RwMatrixScale(&tmp, &v, rwCOMBINEPOSTCONCAT);
        const RwReal tx = vwx * 0.5f;
        const RwReal ty = vwy * -0.5f;
        v = RwV3d{depth * tx, depth * ty, 0.0f};
        RwMatrixTranslate(&tmp, &v, rwCOMBINEPOSTCONCAT);
        g.CTM2d = tmp;
        RwMatrixInvert(&g.iCTM2d, &tmp);
        g.CTMValid = 1;
    }
    RwMatrixMultiply(&g.CTM, &g.CTM2d, RwFrameGetLTM(RwCameraGetFrame(g.viewCamera)));
    return &g.CTM;
}

// 0x00712018 UI2D_IsCompositeMatrixMirrored_maybe: up.y * right.x - right.y * up.x < 0 (fmsubs).
RwBool _rt2dCTMIsMirrored() {
    RwMatrix* m = _rt2dCTMGetComposite();
    const RwReal f0 = m->right.y * m->up.x;
    return ppc::fmsubs(m->up.y, m->right.x, f0) < 0.0f ? 1 : 0;
}

// 0x00712068 UI2D_GetCompositeMatrixGlobal_maybe: the inverse CTM2d, after bringing the composite up to date.
RwMatrix* _rt2dCTMGetInverse() {
    _rt2dCTMGetComposite();
    return &rt2dGlobals.iCTM2d;
}

// 0x00712c08 _rt2dGetFlatnessTolerance_maybe: the squared tolerance in object space (cached): the device
// tolerance (vw.x / vp.x x depth x tolerance) along x through the inverse composite.
RwReal _rt2dGetTolerance() {
    Rt2dGlobalVars& g = rt2dGlobals;
    if (g.sqToleranceValid == 0) {
        _rt2dCTMGetComposite();
        RwReal f0 = g.vw.x / g.vp.x;
        f0 = f0 * g.layerDepth;
        f0 = f0 * g.tolerance;
        RwV3d v = {f0, 0.0f, 0.0f};
        RwV3dTransformVector(&v, &v, &g.iCTM2d);
        const RwReal yy = v.y * v.y;
        g.sqToleranceValid = 1;
        g.sqTolerance = ppc::fmadds(v.z, v.z, ppc::fmadds(v.x, v.x, yy));
    }
    return g.sqTolerance;
}

// 0x007128b0 Rt2dDeviceGetStep: one pixel along x and y, and the device origin, in object space (through
// the inverse composite; the depth is -1/1 for a parallel camera, else -/+ the layer depth).
RwBool Rt2dDeviceGetStep(RwV2d* xstep, RwV2d* ystep, RwV2d* origin) {
    Rt2dGlobalVars& g = rt2dGlobals;
    RwReal depth;
    RwReal negDepth;
    if (g.viewCamera->projectionType == rwPARALLEL) {
        depth = 1.0f;
        negDepth = -1.0f;
    } else {
        depth = g.layerDepth;
        negDepth = -depth;
    }
    const RwReal vwx = g.vw.x;
    const RwReal vwy = g.vw.y;
    RwReal px = vwx / g.vp.x;
    const RwReal vpy = g.vp.y;
    _rt2dCTMGetComposite();
    RwMatrix* inverse = &g.iCTM2d;
    px = px * negDepth;
    const RwReal py = vwy / vpy;
    RwV3d v = {px, 0.0f, 0.0f};
    RwV3dTransformVector(&v, &v, inverse);
    xstep->y = v.y;
    xstep->x = v.x;
    v = RwV3d{0.0f, depth * py, 0.0f};
    RwV3dTransformVector(&v, &v, inverse);
    const RwReal hy = vwy * -0.5f;
    const RwReal hx = vwx * 0.5f;
    ystep->y = v.y;
    ystep->x = v.x;
    v = RwV3d{depth * hx, depth * hy, 0.0f};
    RwV3dTransformPoint(&v, &v, inverse);
    origin->x = v.x;
    origin->y = v.y;
    return 1;
}

// 0x00712cb0 Rt2dDeviceSetMetric: maps (x, y, w, h) onto the device: the metric becomes
// translate(origin) . scale(|xstep| x vp.x / w, |ystep| x vp.y / h) . translate(-x, -y), measured with an
// identity CTM pushed for the time of the call.
RwBool Rt2dDeviceSetMetric(RwReal x, RwReal y, RwReal w, RwReal h) {
    Rt2dGlobalVars& g = rt2dGlobals;
    SetIdentityInline(&g.metricMtx);
    if (g.mtos <= 0x1e) {  // the inlined Rt2dCTMPush
        ++g.mtos;
        if (Top() == nullptr) g.ctm[g.mtos] = RwMatrixCreate();
        *Top() = *g.ctm[g.mtos - 1];
    }
    SetIdentityInline(Top());
    g.CTMValid = 0;
    g.sqToleranceValid = 0;
    RwV2d xstep, ystep, origin;
    Rt2dDeviceGetStep(&xstep, &ystep, &origin);
    const RwReal sy = g.vp.y / h;
    ystep.y = ystep.y * sy;
    ystep.x = ystep.x * sy;
    const RwReal sx = g.vp.x / w;
    xstep.y = sx * xstep.y;
    xstep.x = sx * xstep.x;
    const RwReal scaleX = rwSqrt(ppc::fmadds(xstep.x, xstep.x, xstep.y * xstep.y));
    const RwReal scaleY = rwSqrt(ppc::fmadds(ystep.x, ystep.x, ystep.y * ystep.y));
    RwV3d v = {origin.x, origin.y, 0.0f};
    RwMatrixTranslate(&g.metricMtx, &v, rwCOMBINEPRECONCAT);
    v = RwV3d{scaleX, scaleY, 1.0f};
    RwMatrixScale(&g.metricMtx, &v, rwCOMBINEPRECONCAT);
    v = RwV3d{-x, -y, 0.0f};
    RwMatrixTranslate(&g.metricMtx, &v, rwCOMBINEPRECONCAT);
    g.deviceX = x;
    g.deviceY = y;
    g.deviceW = w;
    g.deviceH = h;
    if (g.mtos > 0) {  // the inlined Rt2dCTMPop
        g.sqToleranceValid = 0;
        --g.mtos;
        g.CTMValid = 0;
    }
    g.CTMValid = 0;
    return 1;
}

// 0x00711a20 Rt2dCTMSetIdentity
RwBool Rt2dCTMSetIdentity() {
    SetIdentityInline(Top());
    rt2dGlobals.sqToleranceValid = 0;
    rt2dGlobals.CTMValid = 0;
    return 1;
}

// 0x00712320 UI2D_PushMatrix (Rt2dCTMPush): a copy of the top. Fails above 31 entries. Unlike the other
// pushes it leaves the cached composite and tolerance valid.
RwBool Rt2dCTMPush() {
    Rt2dGlobalVars& g = rt2dGlobals;
    if (g.mtos > 0x1e) return 0;
    ++g.mtos;
    if (Top() == nullptr) g.ctm[g.mtos] = RwMatrixCreate();
    *Top() = *g.ctm[g.mtos - 1];
    return 1;
}

// 0x00711c68 UI2D_PopMatrix (Rt2dCTMPop): 0 at the bottom of the stack.
RwBool Rt2dCTMPop() {
    Rt2dGlobalVars& g = rt2dGlobals;
    if (g.mtos <= 0) return 0;
    g.sqToleranceValid = 0;
    --g.mtos;
    g.CTMValid = 0;
    return 1;
}

// 0x00711cc0 UI2D_ScaleMatrix (Rt2dCTMScale): pre-concatenated.
RwBool Rt2dCTMScale(RwReal x, RwReal y) {
    RwV3d v = {x, y, 1.0f};
    RwMatrixScale(Top(), &v, rwCOMBINEPRECONCAT);
    rt2dGlobals.sqToleranceValid = 0;
    rt2dGlobals.CTMValid = 0;
    return 1;
}

// 0x00711d30 UI2D_TranslateMatrix (Rt2dCTMTranslate): pre-concatenated.
RwBool Rt2dCTMTranslate(RwReal x, RwReal y) {
    RwV3d v = {x, y, 0.0f};
    RwMatrixTranslate(Top(), &v, rwCOMBINEPRECONCAT);
    rt2dGlobals.sqToleranceValid = 0;
    rt2dGlobals.CTMValid = 0;
    return 1;
}

// 0x00712a48 UI2d_RotateCurrentMatrix_maybe (Rt2dCTMRotate): about z, degrees, pre-concatenated.
RwBool Rt2dCTMRotate(RwReal theta) {
    RwV3d axis = {0.0f, 0.0f, 1.0f};
    RwMatrixRotate(Top(), &axis, theta, rwCOMBINEPRECONCAT);
    rt2dGlobals.sqToleranceValid = 0;
    rt2dGlobals.CTMValid = 0;
    return 1;
}

// 0x00712090 UI2D_PushLoadMatrix (_rt2dCTMPush with a matrix): pushes, then loads matrix as the top.
// Above 31 entries it fails (no push) and invalidates the caches.
RwBool _rt2dCTMPush(RwMatrix* matrix) {
    Rt2dGlobalVars& g = rt2dGlobals;
    if (g.mtos > 0x1e) {
        g.sqToleranceValid = 0;
        g.CTMValid = 0;
        return 0;
    }
    ++g.mtos;
    if (Top() == nullptr) g.ctm[g.mtos] = RwMatrixCreate();
    *Top() = *matrix;
    g.sqToleranceValid = 0;
    g.CTMValid = 0;
    return 1;
}

// 0x007121a0 UI2D_PushMultMatrix (_rt2dCTMPushMult): pushes matrix x the previous top (null: a copy).
RwBool _rt2dCTMPushMult(RwMatrix* matrix) {
    Rt2dGlobalVars& g = rt2dGlobals;
    if (g.mtos > 0x1e) {
        g.sqToleranceValid = 0;
        g.CTMValid = 0;
        return 0;
    }
    ++g.mtos;
    if (Top() == nullptr) g.ctm[g.mtos] = RwMatrixCreate();
    if (matrix != nullptr) {
        RwMatrixMultiply(Top(), matrix, g.ctm[g.mtos - 1]);
    } else {
        *Top() = *g.ctm[g.mtos - 1];
    }
    g.sqToleranceValid = 0;
    g.CTMValid = 0;
    return 1;
}

// 0x00711ca0 UI2D_GetTopMatrix (_rt2dCTMGet)
RwMatrix* _rt2dCTMGet() { return Top(); }
