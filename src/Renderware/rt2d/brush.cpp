// brush.cpp - RW 3.7 tool/2d/brush.c, ported from the PS3 library code (0x70a430-0x70cb48; the PS3 build
// keeps the fill code, fill.c, in this range: _rt2dShapeAddFillGeometry_maybe and the immediate-mode
// fill). See Rt2d.h.
//
// A brush's colours and UVs are kept as the top corner and a delta to the top's other corner (top,
// dtop) and the same for the bottom edge (bottom, dbottom). Flag 1: the colour varies over the brush;
// flag 2: the UV varies (Rt2dBrushSetUV) or a texture is set (Rt2dBrushSetTexture, the stream).
//
// Not ported (the front end never reaches them): Rt2dBrushStreamGetSize 0x70ad30, Rt2dBrushStreamWrite
// 0x70afc8.
#include "Renderware/rt2d/Rt2dInternal.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwTexture.h"

DOTD_ASSERT_OFFSET(Rt2dBrush, colorCache, 0x60);
DOTD_ASSERT_OFFSET(Rt2dBrush, flag, 0x64);
DOTD_ASSERT_OFFSET(Rt2dBrush, material, 0x6c);
DOTD_ASSERT_OFFSET(Rt2dBrush, halfwidth, 0x70);
DOTD_ASSERT_OFFSET(Rt2dBrush, refCount, 0x74);

namespace {

// 0x00c458bc: Rt2dBrushSetFreeListCreateParams' block {entries per block 8, blocks 1}.
RwInt32 s_brushFreeListBlockSize = 8;
RwInt32 s_brushFreeListPreallocBlocks = 1;

// RwTextureDestroy 0x7548c0 as the brush calls it (a reference less; the last one destroys the texture).
void TextureRelease(RwTexture* texture) { RwTextureDestroy(texture); }

// The colour cache: fctiwz of the top colour, the low byte of each.
void SetColorCache(Rt2dBrush* brush) {
    brush->colorCache.red = static_cast<RwUInt8>(ppc::fctiwz(brush->top.col.red));
    brush->colorCache.green = static_cast<RwUInt8>(ppc::fctiwz(brush->top.col.green));
    brush->colorCache.blue = static_cast<RwUInt8>(ppc::fctiwz(brush->top.col.blue));
    brush->colorCache.alpha = static_cast<RwUInt8>(ppc::fctiwz(brush->top.col.alpha));
}

// 0x0070a940 _rt2dBrushStreamReadData_maybe: the four shade parameters, the colour cache, the flags (bit 1
// recomputed: set when a delta or top/bottom difference is non-zero), the half width; with gotTexture,
// RwStreamFindChunk(rwID_TEXTURE) and RwTextureStreamRead (a non-power-of-two raster is clamped:
// filterAddressing = (fa & 0xffff00ff) | 0x3300), the texture kept (null when the read finds none) and flag 2 set.
// No chunk: null. (No movie or widget brush of the game data carries a texture.)
Rt2dBrush* BrushStreamReadData(Rt2dBrush* brush, const _rt2dStreamBrush* record, RwStream* stream) {
    brush->top = record->top;
    brush->dtop = record->dtop;
    brush->bottom = record->bottom;
    brush->dbottom = record->dbottom;
    SetColorCache(brush);
    brush->flag = static_cast<RwInt32>(record->flag);
    const bool varies = brush->dtop.col.red != 0.0f || brush->dbottom.col.red != 0.0f ||
                        brush->top.col.red != brush->bottom.col.red || brush->dtop.col.green != 0.0f ||
                        brush->dbottom.col.green != 0.0f || brush->top.col.green != brush->bottom.col.green ||
                        brush->dtop.col.blue != 0.0f || brush->dbottom.col.blue != 0.0f ||
                        brush->top.col.blue != brush->bottom.col.blue || brush->dtop.col.alpha != 0.0f ||
                        brush->dbottom.col.alpha != 0.0f || brush->top.col.alpha != brush->bottom.col.alpha;
    if (varies) {
        brush->flag |= 1;
    } else {
        brush->flag &= ~1;
    }
    brush->halfwidth = record->halfwidth;
    if (record->gotTexture == 0) return brush;
    if (RwStreamFindChunk(stream, 6, nullptr, nullptr) == 0) return nullptr;
    RwTexture* texture = RwTextureStreamRead(stream);
    if (texture != nullptr && texture->raster != nullptr) {
        const RwUInt32 width = static_cast<RwUInt32>(texture->raster->width);
        const RwUInt32 height = static_cast<RwUInt32>(texture->raster->height);
        if (((height - 1) & height) != 0 || ((width - 1) & width) != 0) {
            texture->filterAddressing = (texture->filterAddressing & 0xffff00ffu) | 0x3300u;  // clamp, clamp
        }
    }
    brush->texture = texture;
    brush->flag |= 2;
    return brush;
}

}  // namespace

// 0x0070a430 Rt2dBrushSetFreeListCreateParams
void Rt2dBrushSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    s_brushFreeListPreallocBlocks = numBlocksToPrealloc;
    s_brushFreeListBlockSize = blockSize;
}

// 0x0070aec0 _rt2dBrushOpen_maybe: the vertex cache (0x2400 bytes: 256 Im3D vertices) and the free list.
RwBool _rt2dBrushOpen() {
    rt2dGlobals.brushVertexCache = static_cast<RwIm3DVertex*>(RwMalloc(256 * sizeof(RwIm3DVertex), 0x40190));
    rt2dGlobals.brushFreeList = RwFreeListCreateAndPreallocateSpace(sizeof(Rt2dBrush), s_brushFreeListBlockSize, 0x10,
                                                                    s_brushFreeListPreallocBlocks, nullptr, 0x401a2);
    return 1;
}

// 0x0070af58 _rt2dBrushClose_maybe
RwBool _rt2dBrushClose() {
    RwFreeListDestroy(rt2dGlobals.brushFreeList);
    rt2dGlobals.brushFreeList = nullptr;
    RwFree(rt2dGlobals.brushVertexCache);
    rt2dGlobals.brushVertexCache = nullptr;
    return 1;
}

// 0x0070b208 Rt2dBrushSetRGBA: top = col3, dtop = col2 - col3, bottom = col0, dbottom = col1 - col0 (as
// floats 0..255); the colour cache is col3; flag 1 when any delta or top/bottom difference is non-zero.
Rt2dBrush* Rt2dBrushSetRGBA(Rt2dBrush* brush, RwRGBA* col0, RwRGBA* col1, RwRGBA* col2, RwRGBA* col3) {
    const RwReal tr = col3->red, tg = col3->green, tb = col3->blue, ta = col3->alpha;
    brush->top.col = RwRGBAReal{tr, tg, tb, ta};
    const RwReal dtr = static_cast<RwReal>(col2->red) - tr;
    const RwReal dtg = static_cast<RwReal>(col2->green) - tg;
    const RwReal dtb = static_cast<RwReal>(col2->blue) - tb;
    const RwReal dta = static_cast<RwReal>(col2->alpha) - ta;
    brush->dtop.col = RwRGBAReal{dtr, dtg, dtb, dta};
    const RwReal br = col0->red, bg = col0->green, bb = col0->blue, ba = col0->alpha;
    brush->bottom.col = RwRGBAReal{br, bg, bb, ba};
    const RwReal dbr = static_cast<RwReal>(col1->red) - br;
    const RwReal dbg = static_cast<RwReal>(col1->green) - bg;
    const RwReal dbb = static_cast<RwReal>(col1->blue) - bb;
    const RwReal dba = static_cast<RwReal>(col1->alpha) - ba;
    brush->dbottom.col = RwRGBAReal{dbr, dbg, dbb, dba};
    brush->colorCache = *col3;
    const bool varies = dtr != 0.0f || dbr != 0.0f || tr != br || dtg != 0.0f || dbg != 0.0f || tg != bg ||
                        dtb != 0.0f || dbb != 0.0f || tb != bb || dta != 0.0f || dba != 0.0f || ta != ba;
    if (varies) {
        brush->flag |= 1;
    } else {
        brush->flag &= ~1;
    }
    return brush;
}

// 0x0070a888 Rt2dBrushSetUV: top = uv3, dtop = uv2 - uv3, bottom = uv0, dbottom = uv1 - uv0; flag 2 when
// a delta is non-zero.
Rt2dBrush* Rt2dBrushSetUV(Rt2dBrush* brush, RwV2d* uv0, RwV2d* uv1, RwV2d* uv2, RwV2d* uv3) {
    brush->top.uv = *uv3;
    const RwReal dty = uv2->y - uv3->y;
    const RwReal dtx = uv2->x - uv3->x;
    brush->dtop.uv = RwV2d{dtx, dty};
    brush->bottom.uv = *uv0;
    const RwReal dby = uv1->y - uv0->y;
    const RwReal dbx = uv1->x - uv0->x;
    brush->dbottom.uv = RwV2d{dbx, dby};
    if (dtx != 0.0f || dty != 0.0f || dbx != 0.0f || dby != 0.0f) {
        brush->flag |= 2;
    } else {
        brush->flag &= ~2;
    }
    return brush;
}

// 0x0070ad70 Rt2dBrushSetTexture: flag 2 follows the texture; the brush takes a reference and releases
// the old texture.
Rt2dBrush* Rt2dBrushSetTexture(Rt2dBrush* brush, RwTexture* texture) {
    if (texture != nullptr) {
        brush->flag |= 2;
        ++texture->refCount;
    } else {
        brush->flag &= ~2;
    }
    if (brush->texture != nullptr) TextureRelease(brush->texture);
    brush->texture = texture;
    return brush;
}

// 0x0070ae10 Rt2dBrushDestroy: drops a reference; the last frees the brush. 0 while referenced.
RwBool Rt2dBrushDestroy(Rt2dBrush* brush) {
    if (--brush->refCount > 0) return 0;
    if (brush->texture != nullptr) TextureRelease(brush->texture);
    RwFreeListFree(rt2dGlobals.brushFreeList, brush);
    return 1;
}

// 0x0070b488 Rt2dBrushCreate: white (Rt2dBrushSetRGBA), UVs 0, no texture, half width 0.5, one reference.
Rt2dBrush* Rt2dBrushCreate() {
    Rt2dBrush* brush = static_cast<Rt2dBrush*>(RwFreeListAlloc(rt2dGlobals.brushFreeList, 0x301a2));
    if (brush == nullptr) return nullptr;
    std::memset(brush, 0, sizeof(Rt2dBrush));
    RwRGBA white = {0xff, 0xff, 0xff, 0xff};
    Rt2dBrushSetRGBA(brush, &white, &white, &white, &white);
    brush->flag &= ~2;
    brush->dbottom.uv.y = 0.0f;
    brush->top.uv.y = 0.0f;
    brush->top.uv.x = 0.0f;
    brush->dtop.uv.x = 0.0f;
    brush->dtop.uv.y = 0.0f;
    brush->bottom.uv.y = 0.0f;
    brush->bottom.uv.x = 0.0f;
    brush->dbottom.uv.x = 0.0f;
    if (brush->texture != nullptr) TextureRelease(brush->texture);
    brush->halfwidth = 0.5f;
    brush->texture = nullptr;
    brush->refCount = 1;
    return brush;
}

// 0x0070ac38 _rt2dBrushStreamReadTo_maybe: the 0x70-byte record (the colour cache is first refreshed
// from the brush's current top colour); version 1 reads the data, another version returns null.
Rt2dBrush* _rt2dBrushStreamReadTo(Rt2dBrush* brush, RwStream* stream) {
    _rt2dStreamBrush record;
    if (RwStreamRead(stream, &record, sizeof(record)) != sizeof(record)) return nullptr;
    SetColorCache(brush);
    if (record.version != 1) return nullptr;
    return BrushStreamReadData(brush, &record, stream);
}

// 0x0070b5b0 Rt2dBrushStreamRead (after the caller's RwStreamFindChunk(0x1a2)): a new brush and its data.
// BUG(original): on a failed read the brush is released (destroyed: it has one reference) and the
// pointer is still returned.
Rt2dBrush* Rt2dBrushStreamRead(RwStream* stream) {
    Rt2dBrush* brush = Rt2dBrushCreate();
    _rt2dStreamBrush record;
    if (RwStreamRead(stream, &record, sizeof(record)) == sizeof(record)) {
        SetColorCache(brush);
        if (record.version == 1 && BrushStreamReadData(brush, &record, stream) != nullptr) return brush;
    }
    if (--brush->refCount <= 0) {
        if (brush->texture != nullptr) TextureRelease(brush->texture);
        RwFreeListFree(rt2dGlobals.brushFreeList, brush);
    }
    return brush;
}

// 0x0070b748 _rt2dShapeAddFillGeometry_maybe: the fill of every subpath of the ring that starts at
// path->next: per node a vertex moved by -inset along its normal (z = the layer depth), the brush's
// colour (bilinear over the subpath's bounding box, when it varies; else white) and UV (with a texture);
// the subpath triangulated (count - 3 triangles, indices from the triangulator's cache, which grows to
// the largest subpath). The vertex and triangle bases advance by what was added. Null when the index
// cache cannot be allocated (the material reference is then kept).
Rt2dPath* _rt2dShapeAddFillGeometry(Rt2dPath* path, Rt2dBrush* brush, RpGeometry* geometry, RwUInt32* vertexBase,
                                    RwUInt32* triangleBase) {
    Rt2dGlobalVars& g = rt2dGlobals;
    RpMaterial* material = _rt2dBrushGetMaterial(brush);
    RwUInt32 maxTris = 0;
    RwInt32 numVerts = 0;
    RwInt32 numTris = 0;
    Rt2dPath* sub = path->next;
    do {
        const RwInt32 count = sub->numSegment == -1 ? _rwSListGetNumEntries(static_cast<RwSList*>(sub->segments))
                                                    : sub->numSegment;
        if (static_cast<RwUInt32>(count) > maxTris) maxTris = static_cast<RwUInt32>(count - 3);
        numVerts += count;
        numTris = numTris + count - 3;
        sub = sub->next;
    } while (path->next != sub);
    RwUInt32* cache = nullptr;
    if (maxTris != 0) {
        if (maxTris * 3 > g.triIdxCacheSize) {
            if (g.triIdxCache != nullptr) RwFree(g.triIdxCache);
            g.triIdxCacheSize = 0;
            g.triIdxCache = static_cast<RwUInt32*>(RwMalloc(maxTris * 12, 0x30190));
            if (g.triIdxCache == nullptr) return nullptr;
            g.triIdxCacheSize = maxTris * 3;
        }
        cache = g.triIdxCache;
        std::memset(cache, 0, (maxTris * 12) & ~3u);
    }
    const RwReal depth = g.layerDepth;
    if (numTris == 0 || numVerts == 0) {
        RpMaterialDestroy(material);
        *vertexBase += numVerts;
        *triangleBase += numTris;
        return path;
    }
    RwUInt32 base = *vertexBase;
    RpTriangle* triangle = geometry->triangles + *triangleBase;
    RwV3d* vertex = geometry->morphTarget->verts + base;
    RwRGBA* prelit = geometry->preLitLum + base;
    RwTexCoords* uv = geometry->texCoords[0] + base;
    sub = path->next;
    for (;;) {
        const RwReal inset = sub->inset;
        RwInt32 count;
        rt2dPathNode* node;
        if (sub->numSegment == -1) {
            node = static_cast<rt2dPathNode*>(_rwSListGetArray(static_cast<RwSList*>(sub->segments)));
            count = _rwSListGetNumEntries(static_cast<RwSList*>(sub->segments));
        } else {
            node = static_cast<rt2dPathNode*>(sub->segments);
            count = sub->numSegment;
        }
        const RwInt32 subTris = count - 3;
        RwInt32 triangulated = subTris;
        RwReal bbox[4] = {node[0].pos.x, node[0].pos.y, node[0].pos.x, node[0].pos.y};
        _rt2dSubPathAccumulateBBox(sub, bbox);
        const RwReal invW = 1.0f / (bbox[2] - bbox[0]);
        const RwReal invH = 1.0f / (bbox[3] - bbox[1]);
        for (RwInt32 i = 0; i < count; ++i, ++node, ++vertex) {
            const RwReal ny = inset * node->normal.y;
            const RwReal nx = inset * node->normal.x;
            vertex->z = depth;
            const RwReal y = node->pos.y - ny;
            const RwReal x = node->pos.x - nx;
            vertex->y = y;
            vertex->x = x;
            const RwReal s = invW * (x - bbox[0]);
            const RwReal t = invH * (y - bbox[1]);
            if ((brush->flag & 1) != 0) {
                const RwReal br = ppc::fmadds(s, brush->dbottom.col.red, brush->bottom.col.red);
                const RwReal tr = ppc::fmadds(s, brush->dtop.col.red, brush->top.col.red);
                const RwReal bg = ppc::fmadds(s, brush->dbottom.col.green, brush->bottom.col.green);
                const RwReal tg = ppc::fmadds(s, brush->dtop.col.green, brush->top.col.green);
                const RwReal bb = ppc::fmadds(s, brush->dbottom.col.blue, brush->bottom.col.blue);
                const RwReal tb = ppc::fmadds(s, brush->dtop.col.blue, brush->top.col.blue);
                const RwReal ba = ppc::fmadds(s, brush->dbottom.col.alpha, brush->bottom.col.alpha);
                const RwReal ta = ppc::fmadds(s, brush->dtop.col.alpha, brush->top.col.alpha);
                prelit->red = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, tr - br, br)));
                prelit->green = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, tg - bg, bg)));
                prelit->blue = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, tb - bb, bb)));
                prelit->alpha = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, ta - ba, ba)));
            } else {
                *prelit = RwRGBA{0xff, 0xff, 0xff, 0xff};
            }
            ++prelit;
            if (brush->texture != nullptr) {
                const RwReal bu = ppc::fmadds(s, brush->dbottom.uv.x, brush->bottom.uv.x);
                const RwReal bv = ppc::fmadds(s, brush->dbottom.uv.y, brush->bottom.uv.y);
                const RwReal tv = ppc::fmadds(s, brush->dtop.uv.y, brush->top.uv.y);
                const RwReal tu = ppc::fmadds(s, brush->dtop.uv.x, brush->top.uv.x);
                uv->v = ppc::fmadds(t, tv - bv, bv);
                uv->u = ppc::fmadds(t, tu - bu, bu);
                ++uv;
            }
        }
        _rt2dShapeTriangulateFill(sub, &triangulated, cache);
        // The triangles: count - 3 index triples from the cache (whatever the triangulator wrote).
        // BUG(original): a subpath under 3 points makes this loop run (nearly) forever.
        const RwUInt32* idx = cache;
        for (RwInt32 k = 0; k != subTris; ++k, idx += 3, ++triangle) {
            RpGeometryTriangleSetVertexIndices(geometry, triangle, static_cast<RwUInt16>(idx[0] + base),
                                               static_cast<RwUInt16>(idx[1] + base), static_cast<RwUInt16>(idx[2] + base));
            RpGeometryTriangleSetMaterial(geometry, triangle, material);
        }
        sub = sub->next;
        if (path->next == sub) break;
        base += static_cast<RwUInt32>(count);
    }
    RpMaterialDestroy(material);
    *vertexBase += numVerts;
    *triangleBase += numTris;
    return path;
}

namespace {

// The clamp of Rt2d_ColorMulAddClamped: above 255 (or unordered) 255, at or below 0 0.
inline RwReal ClampColor(RwReal v) {
    if (!(v <= 255.0f)) return 255.0f;
    if (v <= 0.0f) return 0.0f;
    return v;
}

// The texture render states of a textured fill or stroke (inlined in both): the raster, the filter (the
// low byte of filterAddressing) and the addressing (U's when U and V agree, else 0); without a texture
// only the raster (null).
void SetBrushTextureStates(const Rt2dBrush* brush) {
    if (brush->texture == nullptr) {
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
        return;
    }
    const RwUInt32 fa = brush->texture->filterAddressing;
    const RwUInt32 addressU = (fa >> 8) & 0xf;
    const RwUInt32 addressV = (fa >> 12) & 0xf;
    const RwUInt32 address = addressU == addressV ? addressV : 0;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, brush->texture->raster);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, reinterpret_cast<void*>(static_cast<uintptr_t>(fa & 0xff)));
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, reinterpret_cast<void*>(static_cast<uintptr_t>(address & 0xf)));
}

// One vertex of the immediate fill: the node moved by -inset along its normal at depth, the brush colour
// (bilinear over bbox when it varies, else the colour cache) and the UV (always).
void FillVertex(RwIm3DVertex* v, const rt2dPathNode* node, const Rt2dBrush* brush, RwReal inset, RwReal depth,
                const RwReal* bbox, RwReal invW, RwReal invH) {
    const RwReal y = node->pos.y - inset * node->normal.y;
    const RwReal x = node->pos.x - inset * node->normal.x;
    v->objVertex.x = x;
    v->objVertex.y = y;
    v->objVertex.z = depth;
    const RwReal s = invW * (x - bbox[0]);
    const RwReal t = invH * (y - bbox[1]);
    if ((brush->flag & 1) != 0) {
        const RwReal br = ppc::fmadds(s, brush->dbottom.col.red, brush->bottom.col.red);
        const RwReal tr = ppc::fmadds(s, brush->dtop.col.red, brush->top.col.red);
        const RwReal bg = ppc::fmadds(s, brush->dbottom.col.green, brush->bottom.col.green);
        const RwReal tg = ppc::fmadds(s, brush->dtop.col.green, brush->top.col.green);
        const RwReal bb = ppc::fmadds(s, brush->dbottom.col.blue, brush->bottom.col.blue);
        const RwReal tb = ppc::fmadds(s, brush->dtop.col.blue, brush->top.col.blue);
        const RwReal ba = ppc::fmadds(s, brush->dbottom.col.alpha, brush->bottom.col.alpha);
        const RwReal ta = ppc::fmadds(s, brush->dtop.col.alpha, brush->top.col.alpha);
        v->color.red = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, tr - br, br)));
        v->color.green = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, tg - bg, bg)));
        v->color.blue = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, tb - bb, bb)));
        v->color.alpha = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, ta - ba, ba)));
    } else {
        v->color = brush->colorCache;
    }
    const RwReal bu = ppc::fmadds(s, brush->dbottom.uv.x, brush->bottom.uv.x);
    const RwReal bv = ppc::fmadds(s, brush->dbottom.uv.y, brush->bottom.uv.y);
    const RwReal tv = ppc::fmadds(s, brush->dtop.uv.y, brush->top.uv.y);
    const RwReal tu = ppc::fmadds(s, brush->dtop.uv.x, brush->top.uv.x);
    v->v = ppc::fmadds(t, tv - bv, bv);
    v->u = ppc::fmadds(t, tu - bu, bu);
}

// The flush of the vertex cache as a triangle strip over topo (inlined twice in the fill): when the
// cache holds at least one vertex.
void FlushFillStrip(RwIm3DVertex* end, RwMatrix* ltm, const Rt2dBrush* brush, RwInt32 count) {
    Rt2dGlobalVars& g = rt2dGlobals;
    const RwUInt32 bytes = static_cast<RwUInt32>(reinterpret_cast<RwUInt8*>(end) -
                                                 reinterpret_cast<RwUInt8*>(g.brushVertexCache));
    if (bytes + 0x23 <= 0x46) return;  // the PS3 compares (bytes + 0x23) unsigned with 0x46
    const RwUInt32 numVerts = bytes / sizeof(RwIm3DVertex);
    const RwUInt32 flags = (brush->texture != nullptr ? 1u : 0u) | g.TransformFlags;
    if (RwIm3DTransform(g.brushVertexCache, numVerts, ltm, flags) != nullptr) {
        RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRISTRIP, g.topo, count);
        RwIm3DEnd();
    }
}

}  // namespace

// 0x0070a440 Rt2d_ColorMulAddClamped_maybe (_rt2dBrushTransformColor): the brush's colours become the given
// ones (top, dtop, bottom, dbottom) x mult + offs (fmadds), each clamped to [0, 255] (deltas too), and the
// colour cache the new top colour (fctiwz).
Rt2dBrush* _rt2dBrushTransformColor(Rt2dBrush* brush, const RwRGBAReal* bottom, const RwRGBAReal* dbottom,
                                    const RwRGBAReal* dtop, const RwRGBAReal* top, const RwRGBAReal* mult,
                                    const RwRGBAReal* offs) {
    brush->top.col.red = ClampColor(ppc::fmadds(top->red, mult->red, offs->red));
    brush->top.col.green = ClampColor(ppc::fmadds(top->green, mult->green, offs->green));
    brush->top.col.blue = ClampColor(ppc::fmadds(top->blue, mult->blue, offs->blue));
    brush->top.col.alpha = ClampColor(ppc::fmadds(top->alpha, mult->alpha, offs->alpha));
    brush->dtop.col.red = ClampColor(ppc::fmadds(dtop->red, mult->red, offs->red));
    brush->dtop.col.green = ClampColor(ppc::fmadds(dtop->green, mult->green, offs->green));
    brush->dtop.col.blue = ClampColor(ppc::fmadds(dtop->blue, mult->blue, offs->blue));
    brush->dtop.col.alpha = ClampColor(ppc::fmadds(dtop->alpha, mult->alpha, offs->alpha));
    brush->bottom.col.red = ClampColor(ppc::fmadds(bottom->red, mult->red, offs->red));
    brush->bottom.col.green = ClampColor(ppc::fmadds(bottom->green, mult->green, offs->green));
    brush->bottom.col.blue = ClampColor(ppc::fmadds(bottom->blue, mult->blue, offs->blue));
    brush->bottom.col.alpha = ClampColor(ppc::fmadds(bottom->alpha, mult->alpha, offs->alpha));
    brush->dbottom.col.red = ClampColor(ppc::fmadds(dbottom->red, mult->red, offs->red));
    brush->dbottom.col.green = ClampColor(ppc::fmadds(dbottom->green, mult->green, offs->green));
    brush->dbottom.col.blue = ClampColor(ppc::fmadds(dbottom->blue, mult->blue, offs->blue));
    brush->dbottom.col.alpha = ClampColor(ppc::fmadds(dbottom->alpha, mult->alpha, offs->alpha));
    SetColorCache(brush);
    return brush;
}

// 0x0070be48 DrawUIFilledPathGeometry (Rt2dPathFill, one subpath): flattened into the scratch path when
// not flat; the texture states; then a triangle strip zig-zagging from both ends of the node list (last,
// first, last-1, first+1, ...) through the 256-vertex cache, flushed (RwIm3DTransform with the composite
// CTM, rwPRIMTYPETRISTRIP over topo) when 254 vertices are reached and at the end. A flushed strip
// restarts from the next unused nodes, without repeating the last two.
Rt2dPath* Rt2dPathFill(Rt2dPath* path, Rt2dBrush* brush) {
    Rt2dGlobalVars& g = rt2dGlobals;
    RwMatrix* ltm = _rt2dCTMGetComposite();
    const RwReal inset = path->inset;
    const RwReal depth = g.layerDepth;
    Rt2dPath* sub = path;
    if (path->flat == 0) {
        sub = _rt2dGetEmptyScratchPath();
        _rt2dSubPathFlatten(sub, path);
    }
    RwInt32 count;
    rt2dPathNode* nodes;
    if (sub->numSegment == -1) {
        nodes = static_cast<rt2dPathNode*>(_rwSListGetArray(static_cast<RwSList*>(sub->segments)));
        count = _rwSListGetNumEntries(static_cast<RwSList*>(sub->segments));
    } else {
        nodes = static_cast<rt2dPathNode*>(sub->segments);
        count = sub->numSegment;
    }
    RwReal bbox[4] = {nodes[0].pos.x, nodes[0].pos.y, nodes[0].pos.x, nodes[0].pos.y};
    _rt2dSubPathAccumulateBBox(sub, bbox);
    const RwReal invW = 1.0f / (bbox[2] - bbox[0]);
    const RwReal invH = 1.0f / (bbox[3] - bbox[1]);
    SetBrushTextureStates(brush);
    RwIm3DVertex* v = g.brushVertexCache;
    RwInt32 inBatch = 0x100;
    if (count > 1) {
        const rt2dPathNode* front = nodes;
        const rt2dPathNode* back = nodes + count - 1;
        RwInt32 pairs = 1;
        bool startBatch = true;
        for (;;) {
            if (startBatch || inBatch > 0xfd) {
                // A new batch: the cache so far is drawn, then back, front and the next back are emitted.
                FlushFillStrip(v, ltm, brush, inBatch);
                v = g.brushVertexCache;
                FillVertex(v++, back, brush, inset, depth, bbox, invW, invH);
                FillVertex(v++, front, brush, inset, depth, bbox, invW, invH);
                --back;
                ++front;
                inBatch = 3;
                startBatch = false;
            } else {
                ++inBatch;
            }
            FillVertex(v++, back, brush, inset, depth, bbox, invW, invH);
            --back;
            if (front > back) break;
            FillVertex(v++, front, brush, inset, depth, bbox, invW, invH);
            ++front;
            ++inBatch;
            if (back < front) break;
            if (++pairs == count) break;
        }
    }
    FlushFillStrip(v, ltm, brush, inBatch);
    return path;
}

// 0x0070c8e0 DrawUISubsequentShapePaths / 0x0070cad0 DrawUIShapePathChain (_rt2dPathFillChain): every
// closed subpath of the chain filled.
Rt2dPath* _rt2dPathRenderChain(Rt2dPath* path, Rt2dBrush* brush) {
    if (path == nullptr) return path;
    for (Rt2dPath* sub = path; sub != nullptr; sub = sub->next) {
        if (sub->closed != 0) Rt2dPathFill(sub, brush);
    }
    return path;
}
