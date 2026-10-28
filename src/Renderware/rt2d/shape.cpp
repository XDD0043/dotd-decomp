// shape.cpp - RW 3.7 tool/2d/shape.c with stroke.c and tri.c, ported from the PS3 library code
// (0x71b4d0-0x71f4c0). See Rt2d.h. The fill geometry (fill.c) is in brush.cpp, where the PS3 keeps it.
//
// A shape is a reference to a shape rep (shared through the scene's resource pool), a colour cache (the
// geometry's material colours as read) and an RpAtomic: the PS3 build tessellates every rep once, at
// load, into one RpGeometry (_rt2dShapeRepCreateGeometry: fills triangulated, strokes as quad strips,
// prelit colours and UVs from the brush, one material per brush) and draws shapes as atomics; the
// immediate-mode path (Rt2dPathFill / Rt2dPathStroke) serves shapes without an atomic.
//
// Not ported (the front end never reaches them): Rt2dShapeGetNodeCount 0x71b4d0,
// _rt2dShapeDestroyRenderAtomic_maybe 0x71bad8, Rt2dShapeRender 0x71c1c8, Rt2dShapeAddNode 0x71c1d8,
// the stream writers and sizes 0x71c260 / 0x71c410 / 0x71c4f8 / 0x71cac0 / 0x71d2b0 / 0x71d5f8,
// _rt2dShapeRepCreate_maybe 0x71c7d8, _rt2dShapeCopyData_maybe 0x71c898,
// _rt2dShapeCreateRenderAtomic_maybe 0x71c920, Rt2dShapeDestroy 0x71cbc0, Rt2dShapeStreamRead 0x71d3a8,
// Rt2dShapeCreate 0x71d520, the triangulator's free-list parameter setters 0x71e3c8 / 0x71e3d8,
// Float32ToFloat16_maybe 0x71f2b8, Quat_ToRwMatrix_maybe_2 0x71f3d8 (math helpers of another unit).
#include "Renderware/rt2d/Rt2dInternal.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Renderware/rwcore/RwTexture.h"

DOTD_ASSERT_OFFSET(Rt2dObject, data.shape.rep, 0xb0);
DOTD_ASSERT_OFFSET(Rt2dObject, data.shape.colorCache, 0xb4);
DOTD_ASSERT_OFFSET(Rt2dObject, data.shape.atomic, 0xb8);

namespace {

// 0x00c458e4: the triangulator's free-list blocks ({0x20, 1} vertices, then polygons).
RwInt32 s_triVertBlockSize = 0x20;
RwInt32 s_triVertPreallocBlocks = 1;
RwInt32 s_triPolyBlockSize = 0x20;
RwInt32 s_triPolyPreallocBlocks = 1;

_rt2dTriVert* NewTriVert() {
    _rt2dTriVert* vert = static_cast<_rt2dTriVert*>(RwFreeListAlloc(rt2dGlobals.triVertFreeList, 0x30190));
    if (vert != nullptr) {
        vert->next = nullptr;
        vert->idx = -1;
    }
    return vert;
}

// The release of a polygon's vertex ring and the polygon (inlined three times): the ring from poly->vert,
// then (unless shared, set to null by the caller) the points, then the polygon.
void FreePoly(_rt2dTriPoly* poly) {
    _rt2dTriVert* first = poly->vert;
    poly->next = nullptr;
    if (first != nullptr) {
        _rt2dTriVert* vert = first;
        do {
            vert->idx = -1;
            _rt2dTriVert* next = vert->next;
            vert->next = nullptr;
            RwFreeListFree(rt2dGlobals.triVertFreeList, vert);
            vert = next;
        } while (vert != first);
    }
    if (poly->pos != nullptr) RwFree(poly->pos);
    poly->vCount = 0;
    poly->vert = nullptr;
    poly->pos = nullptr;
    RwFreeListFree(rt2dGlobals.triPolyFreeList, poly);
}

// One edge test of the triangulator: the unit perpendicular of (to - from) as (to.y - from.y,
// from.x - to.x), RwV2dNormalize'd, against (base - point) with fmadds.
RwReal EdgeSide(const RwV2d& from, const RwV2d& to, const RwV2d& base, const RwV2d& point) {
    RwV2d d = {to.y - from.y, from.x - to.x};
    RwV2dNormalize(&d, &d);
    const RwReal t = (base.y - point.y) * d.y;
    return ppc::fmadds(base.x - point.x, d.x, t);
}

// 0x0071e4e0 _rt2dTriangulateSplitPolygon_maybe: cuts poly along the diagonal a-b. The vertices from a
// up to b (excluded) are moved into one ring with a new copy of b appended (poly keeps it), those from b
// up to a into another with a copy of a (the new polygon, which shares poly's points and index output).
_rt2dTriPoly* TriangulateSplitPolygon(_rt2dTriPoly* poly, _rt2dTriVert* a, _rt2dTriVert* b) {
    _rt2dTriPoly* split = static_cast<_rt2dTriPoly*>(RwFreeListAlloc(rt2dGlobals.triPolyFreeList, 0x30190));
    if (split == nullptr) return nullptr;
    split->vert = nullptr;
    split->vCount = 0;
    split->next = nullptr;
    split->pos = nullptr;
    for (_rt2dTriVert* v = poly->vert; v != a; v = v->next) {
    }
    // The ring a .. b.
    _rt2dTriVert* lastA = nullptr;
    RwInt32 countA = 1;
    if (a != b) {
        RwInt32 moved = 0;
        _rt2dTriVert* cur = a;
        _rt2dTriVert* prev = nullptr;
        for (;;) {
            _rt2dTriVert* next = cur->next;
            if (prev == nullptr) {
                cur->next = cur;
            } else {
                cur->next = prev->next;
                prev->next = cur;
            }
            ++moved;
            prev = cur;
            if (b == next) break;
            cur = next;
        }
        lastA = prev;
        countA = moved + 1;
    }
    _rt2dTriVert* copyB = NewTriVert();
    copyB->idx = b->idx;
    if (lastA == nullptr) {
        copyB->next = copyB;
    } else {
        copyB->next = lastA->next;
        lastA->next = copyB;
    }
    // The ring b .. a.
    _rt2dTriVert* lastB = nullptr;
    RwInt32 countB = 1;
    if (a != b) {
        RwInt32 moved = 0;
        _rt2dTriVert* cur = b;
        _rt2dTriVert* prev = nullptr;
        for (;;) {
            _rt2dTriVert* next = cur->next;
            if (prev == nullptr) {
                cur->next = cur;
            } else {
                cur->next = prev->next;
                prev->next = cur;
            }
            ++moved;
            prev = cur;
            if (a == next) break;
            cur = next;
        }
        lastB = prev;
        countB = moved + 1;
    }
    _rt2dTriVert* copyA = NewTriVert();
    copyA->idx = a->idx;
    if (lastB == nullptr) {
        copyA->next = copyA;
    } else {
        copyA->next = lastB->next;
        lastB->next = copyA;
    }
    _rt2dTriIndex* triIndex = poly->triIndex;
    RwV2d* pos = poly->pos;
    poly->vert = copyB;
    poly->vCount = countA;
    split->vert = copyA;
    split->vCount = countB;
    split->pos = pos;
    split->triIndex = triIndex;
    return split;
}

// 0x0071e7e0 Rt2d_TriangulatePolygon_maybe (_rt2dTriangulatePolygon): a triangle is emitted (its three
// indices); a larger polygon finds its first convex corner (prev, cur, next) from poly->vert, then the
// vertex inside that triangle farthest from the prev-next edge: with one, the polygon is split along
// cur-vertex, otherwise the ear prev-cur-next is cut off (split prev-next); both halves recurse. A
// polygon without a convex corner emits nothing.
_rt2dTriPoly* TriangulatePolygon(_rt2dTriPoly* poly) {
    if (poly->vCount == 3) {
        _rt2dTriIndex* out = poly->triIndex;
        out->idx[out->currIdx++] = poly->vert->idx;
        out->idx[out->currIdx++] = poly->vert->next->idx;
        out->idx[out->currIdx++] = poly->vert->next->next->idx;
        return poly;
    }
    const RwV2d* pos = poly->pos;
    _rt2dTriVert* prev = poly->vert;
    _rt2dTriVert* cur = prev->next;
    _rt2dTriVert* next = cur->next;
    for (;;) {
        if (EdgeSide(pos[prev->idx], pos[cur->idx], pos[prev->idx], pos[next->idx]) > 0.0f) break;
        const bool wrapped = poly->vert == cur;
        prev = cur;
        cur = next;
        next = next->next;
        if (wrapped) return poly;
    }
    poly->vert = prev;
    _rt2dTriPoly* split;
    _rt2dTriVert* candidate = next->next;
    if (candidate == prev) {
        split = TriangulateSplitPolygon(poly, poly->vert, poly->vert->next->next);
    } else {
        RwReal best = 0.0f;
        _rt2dTriVert* bestVert = nullptr;
        for (; candidate != prev; candidate = candidate->next) {
            const RwV2d& p = pos[candidate->idx];
            const RwV2d& pp = pos[prev->idx];
            const RwV2d& pc = pos[cur->idx];
            const RwV2d& pn = pos[next->idx];
            RwInt32 s1;
            const RwReal f1 = EdgeSide(pp, pc, pp, p);
            if (f1 > 0.0f) {
                s1 = 1;
            } else if (f1 < 0.0f) {
                s1 = 2;
            } else {
                s1 = 4;
            }
            RwInt32 s2 = 1;
            const RwReal f2 = EdgeSide(pc, pn, pc, p);
            if (f2 <= 0.0f) s2 = f2 < 0.0f ? 2 : 4;
            RwInt32 s3 = 1;
            const RwReal f3 = EdgeSide(pn, pp, pn, p);
            if (f3 <= 0.0f) s3 = f3 < 0.0f ? 2 : 4;
            if ((s2 & s3 & s1) != 1) continue;
            const RwReal distance = EdgeSide(pn, pp, pn, p);
            if (!(best >= distance)) {
                bestVert = candidate;
                best = distance;
            }
        }
        if (bestVert != nullptr) {
            split = TriangulateSplitPolygon(poly, cur, bestVert);
        } else {
            split = TriangulateSplitPolygon(poly, poly->vert, poly->vert->next->next);
        }
    }
    TriangulatePolygon(split);
    TriangulatePolygon(poly);
    split->pos = nullptr;  // shared with poly
    FreePoly(split);
    return poly;
}

// The shape's material for brush (fill and stroke share the logic, 0x70b748 / 0x71d790): the brush's
// cached material with a reference taken, or a new one (the brush's texture; white when the colour
// varies, else the colour cache) kept in the brush.
RpMaterial* BrushMaterial(Rt2dBrush* brush) {
    RpMaterial* material = static_cast<RpMaterial*>(static_cast<void*>(brush->material));
    if (material != nullptr) {
        ++material->refCount;
        return material;
    }
    material = RpMaterialCreate();
    if (brush->texture != nullptr) RpMaterialSetTexture(material, brush->texture);
    if ((brush->flag & 1) != 0) {
        material->color = RwRGBA{0xff, 0xff, 0xff, 0xff};
    } else {
        material->color = brush->colorCache;
    }
    brush->material = reinterpret_cast<RpMaterial*>(material);
    return material;
}

// A subpath's node count and nodes, locked or not.
rt2dPathNode* SubPathNodes(Rt2dPath* path, RwInt32* count) {
    if (path->numSegment == -1) {
        *count = _rwSListGetNumEntries(static_cast<RwSList*>(path->segments));
        return static_cast<rt2dPathNode*>(_rwSListGetArray(static_cast<RwSList*>(path->segments)));
    }
    *count = path->numSegment;
    return static_cast<rt2dPathNode*>(path->segments);
}

}  // namespace

RpMaterial* _rt2dBrushGetMaterial(Rt2dBrush* brush) { return BrushMaterial(brush); }

// 0x0071e3e8 Rt2d_CreateFreeLists_maybe (_rt2dTriangulateOpen): the vertex (8-byte) and polygon
// (0x14-byte) free lists.
RwBool _rt2dTriangulateOpen() {
    rt2dGlobals.triVertFreeList = RwFreeListCreateAndPreallocateSpace(sizeof(_rt2dTriVert), s_triVertBlockSize, 4,
                                                                      s_triVertPreallocBlocks, nullptr, 0x40190);
    rt2dGlobals.triPolyFreeList = RwFreeListCreateAndPreallocateSpace(sizeof(_rt2dTriPoly), s_triPolyBlockSize, 4,
                                                                      s_triPolyPreallocBlocks, nullptr, 0x40190);
    return 1;
}

// 0x0071e490 Rt2d_DestroyFreeLists_maybe
RwBool _rt2dTriangulateClose() {
    RwFreeListDestroy(rt2dGlobals.triVertFreeList);
    RwFreeListDestroy(rt2dGlobals.triPolyFreeList);
    rt2dGlobals.triPolyFreeList = nullptr;
    rt2dGlobals.triVertFreeList = nullptr;
    return 1;
}

// 0x0071ef48 _rt2dShapeTriangulateFill_maybe: a polygon over the subpath's points except the last (a
// closed subpath repeats its first point), triangulated into idx (index triples, idx[3k..3k+2]);
// *numTri = the indices written / 3.
Rt2dPath* _rt2dShapeTriangulateFill(Rt2dPath* path, RwInt32* numTri, RwImVertexIndex* idx) {
    RwInt32 count;
    const rt2dPathNode* nodes = SubPathNodes(path, &count);
    const RwInt32 n = count - 1;
    _rt2dTriPoly* poly = static_cast<_rt2dTriPoly*>(RwFreeListAlloc(rt2dGlobals.triPolyFreeList, 0x30190));
    if (poly == nullptr) return path;
    poly->vCount = 0;
    poly->next = nullptr;
    poly->vert = nullptr;
    poly->pos = nullptr;
    poly->pos = static_cast<RwV2d*>(RwMalloc(static_cast<RwUInt32>(n) * sizeof(RwV2d), 0x30190));
    if (poly->pos != nullptr) {
        _rt2dTriVert* last = nullptr;
        for (RwInt32 i = 0; i < n; ++i) {
            _rt2dTriVert* vert = NewTriVert();
            vert->idx = i;
            poly->pos[i] = nodes[i].pos;
            if (last == nullptr) {
                vert->next = vert;
            } else {
                vert->next = last->next;
                last->next = vert;
            }
            last = vert;
        }
        poly->vert = last;
        poly->vCount = n;
    }
    rt2dGlobals.triVertIndex.idx = reinterpret_cast<RwInt32*>(idx);
    rt2dGlobals.triVertIndex.currIdx = 0;
    poly->triIndex = &rt2dGlobals.triVertIndex;
    TriangulatePolygon(poly);
    *numTri = rt2dGlobals.triVertIndex.currIdx / 3;
    FreePoly(poly);
    return path;
}

// 0x0071d790 _rt2dShapeAddStrokeGeometry_maybe: the stroke of every subpath of the ring that starts at
// path->next: two vertices per node at -(halfwidth + inset) and +(halfwidth - inset) along the node's
// normal (z = the layer depth), prelit with the brush's top / bottom colour along the length (when it
// varies; else white), UVs along the length when the UV varies, two triangles per segment; the vertex
// and triangle bases advance by what was added.
Rt2dPath* _rt2dShapeAddStrokeGeometry(Rt2dPath* path, Rt2dBrush* brush, RpGeometry* geometry, RwUInt32* vertexBase,
                                      RwUInt32* triangleBase) {
    RpMaterial* material = BrushMaterial(brush);
    RwInt32 numVerts = 0;
    RwInt32 numTris = 0;
    Rt2dPath* sub = path->next;
    do {
        RwInt32 count;
        SubPathNodes(sub, &count);
        numVerts += count * 2;
        numTris = numTris + count * 2 - 2;
        sub = sub->next;
    } while (path->next != sub);
    const RwReal halfwidth = brush->halfwidth;
    const RwReal depth = rt2dGlobals.layerDepth;
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
    RwReal inset = sub->inset;
    for (;;) {
        RwInt32 count;
        rt2dPathNode* node = SubPathNodes(sub, &count);
        const RwReal invLength = 1.0f / node[count - 1].dist;
        if (count != 0) {
            const RwReal inner = halfwidth - inset;
            const RwReal outer = halfwidth + inset;
            for (RwInt32 i = 0; i < count; ++i, ++node, vertex += 2) {
                const RwReal ny = outer * node->normal.y;
                const RwReal nx = outer * node->normal.x;
                vertex[0].z = depth;
                vertex[0].y = node->pos.y - ny;
                vertex[0].x = node->pos.x - nx;
                if ((brush->flag & 1) != 0) {
                    const RwReal t = invLength * node->dist;
                    prelit->red = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dtop.col.red, brush->top.col.red)));
                    prelit->green = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dtop.col.green, brush->top.col.green)));
                    prelit->blue = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dtop.col.blue, brush->top.col.blue)));
                    prelit->alpha = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dtop.col.alpha, brush->top.col.alpha)));
                } else {
                    *prelit = RwRGBA{0xff, 0xff, 0xff, 0xff};
                }
                ++prelit;
                if ((brush->flag & 2) != 0) {
                    const RwReal t = invLength * node->dist;
                    uv->u = ppc::fmadds(t, brush->dtop.uv.x, brush->top.uv.x);
                    uv->v = ppc::fmadds(t, brush->dtop.uv.y, brush->top.uv.y);
                    ++uv;
                }
                vertex[1].z = depth;
                vertex[1].y = ppc::fmadds(inner, node->normal.y, node->pos.y);
                vertex[1].x = ppc::fmadds(inner, node->normal.x, node->pos.x);
                if ((brush->flag & 1) != 0) {
                    const RwReal t = invLength * node->dist;
                    prelit->red = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dbottom.col.red, brush->bottom.col.red)));
                    prelit->green = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dbottom.col.green, brush->bottom.col.green)));
                    prelit->blue = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dbottom.col.blue, brush->bottom.col.blue)));
                    prelit->alpha = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dbottom.col.alpha, brush->bottom.col.alpha)));
                } else {
                    *prelit = RwRGBA{0xff, 0xff, 0xff, 0xff};
                }
                ++prelit;
                if ((brush->flag & 2) != 0) {
                    const RwReal t = invLength * node->dist;
                    uv->u = ppc::fmadds(t, brush->dbottom.uv.x, brush->bottom.uv.x);
                    uv->v = ppc::fmadds(t, brush->dbottom.uv.y, brush->bottom.uv.y);
                    ++uv;
                }
            }
        }
        // BUG(original): an empty subpath makes the loop below run 2^32 - 1 times (the count is unsigned).
        const RwUInt32 segments = static_cast<RwUInt32>(count - 1);
        RwUInt32 v = base;
        for (RwUInt32 k = 0; k < segments; ++k) {
            RpGeometryTriangleSetVertexIndices(geometry, triangle, static_cast<RwUInt16>(v), static_cast<RwUInt16>(v + 1),
                                               static_cast<RwUInt16>(v + 2));
            RpGeometryTriangleSetMaterial(geometry, triangle, material);
            RpGeometryTriangleSetVertexIndices(geometry, triangle + 1, static_cast<RwUInt16>(v + 1),
                                               static_cast<RwUInt16>(v + 3), static_cast<RwUInt16>(v + 2));
            RpGeometryTriangleSetMaterial(geometry, triangle + 1, material);
            v += 2;
            triangle += 2;
        }
        sub = sub->next;
        if (path->next == sub) break;
        base += static_cast<RwUInt32>(count) * 2;
        inset = sub->inset;
    }
    RpMaterialDestroy(material);
    *vertexBase += numVerts;
    *triangleBase += numTris;
    return path;
}

// 0x0071b500 _rt2dShapeRepCreateGeometry_maybe: per node a ring of working subpaths (fills: the closed
// subpaths only; curves flattened into new paths, flat subpaths borrowed (their copy's flat word 0 marks
// the borrowed nodes)), counted, then one RpGeometry (format 0x4f: tristrip, positions, one UV set,
// prelit, modulate material colour) filled node by node, its bounding sphere, RpGeometryUnlock; the
// working paths are destroyed. Null for a rep without nodes' memory.
RpGeometry* _rt2dShapeRepCreateGeometry(_rt2dShapeRep* rep) {
    // RpMeshGetTriStripMethod 0x6a79c0 is called first; its results are unused.
    const RwInt32 numNodes = _rwSListGetNumEntries(rep->nodes);
    _rt2dShapeNode* node = static_cast<_rt2dShapeNode*>(_rwSListGetArray(rep->nodes));
    _rt2dPathMeshNode* meshes =
        static_cast<_rt2dPathMeshNode*>(RwMalloc(static_cast<RwUInt32>(numNodes) * sizeof(_rt2dPathMeshNode), 0x30190));
    RwInt32 totalTris = 0;
    RwInt32 totalVerts = 0;
    for (RwInt32 i = 0; i < numNodes; ++i, ++node) {
        _rt2dPathMeshNode* mesh = &meshes[i];
        mesh->path = nullptr;
        mesh->numVert = 0;
        mesh->numTri = 0;
        mesh->numIdx = 0;
        mesh->brush = node->brush;
        mesh->flag = node->flag;
        const bool fill = (node->flag & 1) != 0;
        for (Rt2dPath* sub = node->path; sub != nullptr; sub = sub->next) {
            if (fill && sub->closed == 0) continue;
            Rt2dPath* work = Rt2dPathCreate();
            RwInt32 count;
            if (sub->flat == 0) {
                _rt2dSubPathFlatten(work, sub);
                count = work->numSegment == -1 ? _rwSListGetNumEntries(static_cast<RwSList*>(work->segments))
                                               : work->numSegment;
            } else {
                _rwSListDestroy(static_cast<RwSList*>(work->segments));
                work->numSegment = sub->numSegment;
                work->segments = sub->segments;
                work->closed = sub->closed;
                work->flat = 0;  // borrowed nodes
                count = sub->numSegment == -1 ? _rwSListGetNumEntries(static_cast<RwSList*>(sub->segments)) : sub->numSegment;
            }
            work->inset = sub->inset;
            if (fill) {
                mesh->numVert += count;
                mesh->numTri += count - 3;
                mesh->numIdx += count * 3 - 9;
            } else {
                mesh->numVert += count * 2;
                mesh->numTri += count * 2 - 2;
                mesh->numIdx += count * 6 - 6;
            }
            // The ring: mesh->path is the last working path, its next the first.
            if (mesh->path == nullptr) {
                work->next = work;
            } else {
                work->next = mesh->path->next;
                mesh->path->next = work;
            }
            mesh->path = work;
        }
        totalTris += mesh->numTri;
        totalVerts += mesh->numVert;
    }
    RpGeometry* geometry = nullptr;
    if (meshes != nullptr) {
        geometry = RpGeometryCreate(totalVerts, totalTris, 0x4f);
        RwUInt32 vertexBase = 0;
        RwUInt32 triangleBase = 0;
        for (RwInt32 i = 0; i < numNodes; ++i) {
            _rt2dPathMeshNode* mesh = &meshes[i];
            if (mesh->path == nullptr) continue;
            if ((mesh->flag & 1) != 0) {
                _rt2dShapeAddFillGeometry(mesh->path->next, mesh->brush, geometry, &vertexBase, &triangleBase);
            } else {
                _rt2dShapeAddStrokeGeometry(mesh->path->next, mesh->brush, geometry, &vertexBase, &triangleBase);
            }
        }
        if (geometry != nullptr) {
            RpMorphTarget* target = geometry->morphTarget;
            RwSphere sphere;
            RpMorphTargetCalcBoundingSphere(target, &sphere);
            target->boundingSphere = sphere;
            RpGeometryUnlock(geometry);
        }
        for (RwInt32 i = 0; i < numNodes; ++i) {
            _rt2dPathMeshNode* mesh = &meshes[i];
            Rt2dPath* first = mesh->path->next;  // BUG(original): a node without working paths reads null
            Rt2dPath* p = first;
            do {
                if (p->flat == 0) p->segments = nullptr;
                p = p->next;
            } while (mesh->path->next != p);
            mesh->path->next = nullptr;
            Rt2dPathDestroy(p);
        }
        RwFree(meshes);
    }
    rep->geometry = geometry;
    return geometry;
}

// 0x0071c5c8 _rt2dShapeRepDestroy_maybe: drops a reference; the last destroys every node's path and
// brush (the brush only with a path), the node list and the geometry. 1 when destroyed.
RwBool _rt2dShapeRepDestroy(_rt2dShapeRep* rep) {
    if (--rep->refCount != 0) return 0;
    const RwInt32 count = _rwSListGetNumEntries(rep->nodes);
    _rt2dShapeNode* node = static_cast<_rt2dShapeNode*>(_rwSListGetArray(rep->nodes));
    for (RwInt32 i = 0; i < count; ++i, ++node) {
        if (node->path == nullptr) continue;
        Rt2dPathDestroy(node->path);
        Rt2dBrushDestroy(node->brush);
    }
    _rwSListDestroy(rep->nodes);
    if (rep->geometry != nullptr) {
        RpGeometryDestroy(rep->geometry);
        rep->geometry = nullptr;
    }
    RwFree(rep);
    return 1;
}

// 0x0071ce08 _rt2dShapeRepStreamRead: {version, node count}, then per node a flags word; with flag 4 the
// node's flag word, a path (0x1a1 chunk; created, unlocked, read) and a brush (0x1a2 chunk), else no path
// nor brush (and the node's flag is left as it was); then the geometry. A failed read returns null.
// BUG(original): the rep read so far leaks on failure; a node without flag 4 keeps an uninitialised flag.
_rt2dShapeRep* _rt2dShapeRepStreamRead(RwStream* stream) {
    RwInt32 header[2];
    if (RwStreamRead(stream, header, 8) != 8) return nullptr;
    _rt2dShapeRep* rep = static_cast<_rt2dShapeRep*>(RwMalloc(sizeof(_rt2dShapeRep), 0x30190));
    rep->refCount = 1;
    rep->nodes = _rwSListCreatePreallocated(sizeof(_rt2dShapeNode), header[1], 0x301a4);
    rep->geometry = nullptr;
    if (header[1] != 0) _rwSListGetNewEntries(rep->nodes, header[1], 0x301a4);
    _rt2dShapeNode* node = static_cast<_rt2dShapeNode*>(_rwSListGetArray(rep->nodes));
    for (RwInt32 i = 0; i < header[1]; ++i, ++node) {
        RwUInt32 flags = 0;
        if (RwStreamRead(stream, &flags, 4) != 4) return nullptr;
        if ((flags & 4) == 0) {
            node->brush = nullptr;
            node->path = nullptr;
            continue;
        }
        Rt2dStreamReadInt32(stream, &node->flag, 4);
        RwUInt32 length, version;
        if (RwStreamFindChunk(stream, 0x1a1, &length, &version) == 0) return nullptr;
        node->path = Rt2dPathCreate();
        Rt2dPathUnlock(node->path);
        _rt2dPathStreamReadTo(node->path, stream);
        if (RwStreamFindChunk(stream, 0x1a2, &length, &version) == 0) return nullptr;
        node->brush = Rt2dBrushCreate();
        _rt2dBrushStreamReadTo(node->brush, stream);
    }
    rep->geometry = _rt2dShapeRepCreateGeometry(rep);
    return rep;
}

// 0x0071ccf0 _rt2dShapeInit_maybe: the shape takes rep (a reference), or a new rep of nodeCount empty
// nodes and no geometry; flag 1 set. Returns 1.
RwBool _rt2dShapeInit(Rt2dObject* shape, RwInt32 nodeCount, _rt2dShapeRep* rep) {
    if (rep != nullptr) {
        shape->data.shape.rep = rep;
        ++rep->refCount;
        shape->flag |= 1;
        return 1;
    }
    _rt2dShapeRep* own = static_cast<_rt2dShapeRep*>(RwMalloc(sizeof(_rt2dShapeRep), 0x30190));
    own->refCount = 1;
    own->nodes = _rwSListCreatePreallocated(sizeof(_rt2dShapeNode), nodeCount, 0x301a4);
    own->geometry = nullptr;
    if (nodeCount != 0) _rwSListGetNewEntries(own->nodes, nodeCount, 0x301a4);
    shape->data.shape.rep = own;
    shape->data.shape.colorCache = nullptr;
    shape->flag |= 1;
    return 1;
}

// 0x0071c718 _rt2dShapeDestruct_maybe: the rep reference, the atomic (and its frame), the colour cache.
RwBool _rt2dShapeDestruct(Rt2dObject* shape) {
    _rt2dShapeRepDestroy(shape->data.shape.rep);
    RpAtomic* atomic = shape->data.shape.atomic;
    if (atomic != nullptr) {
        RwFrame* frame = atomic->frame;
        if (frame != nullptr) {
            RpAtomicSetFrame(atomic, nullptr);
            RwFrameDestroy(frame);
        }
        RpAtomicDestroy(shape->data.shape.atomic);
    }
    if (shape->data.shape.colorCache != nullptr) {
        RwFree(shape->data.shape.colorCache);
        shape->data.shape.colorCache = nullptr;
    }
    return 1;
}

namespace {

// The two stroke vertices of a node (Rt2dPathStroke): at -outer and +inner along the normal, the brush's
// top / bottom colour along the length (when it varies; else the colour cache), UVs when the UV varies.
void StrokeVertices(RwIm3DVertex* v, const rt2dPathNode* node, const Rt2dBrush* brush, RwReal inner, RwReal outer,
                    RwReal depth, RwReal invLength) {
    const RwReal nx = outer * node->normal.x;
    const RwReal ny = outer * node->normal.y;
    v[0].objVertex.z = depth;
    v[0].objVertex.x = node->pos.x - nx;
    v[0].objVertex.y = node->pos.y - ny;
    if ((brush->flag & 1) != 0) {
        const RwReal t = invLength * node->dist;
        v[0].color.red = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dtop.col.red, brush->top.col.red)));
        v[0].color.green = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dtop.col.green, brush->top.col.green)));
        v[0].color.blue = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dtop.col.blue, brush->top.col.blue)));
        v[0].color.alpha = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dtop.col.alpha, brush->top.col.alpha)));
    } else {
        v[0].color = brush->colorCache;
    }
    if ((brush->flag & 2) != 0) {
        const RwReal t = invLength * node->dist;
        v[0].u = ppc::fmadds(t, brush->dtop.uv.x, brush->top.uv.x);
        v[0].v = ppc::fmadds(t, brush->dtop.uv.y, brush->top.uv.y);
    }
    v[1].objVertex.z = depth;
    v[1].objVertex.x = ppc::fmadds(inner, node->normal.x, node->pos.x);
    v[1].objVertex.y = ppc::fmadds(inner, node->normal.y, node->pos.y);
    if ((brush->flag & 1) != 0) {
        const RwReal t = invLength * node->dist;
        v[1].color.red = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dbottom.col.red, brush->bottom.col.red)));
        v[1].color.green = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dbottom.col.green, brush->bottom.col.green)));
        v[1].color.blue = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dbottom.col.blue, brush->bottom.col.blue)));
        v[1].color.alpha = static_cast<RwUInt8>(ppc::fctiwz(ppc::fmadds(t, brush->dbottom.col.alpha, brush->bottom.col.alpha)));
    } else {
        v[1].color = brush->colorCache;
    }
    if ((brush->flag & 2) != 0) {
        const RwReal t = invLength * node->dist;
        v[1].u = ppc::fmadds(t, brush->dbottom.uv.x, brush->bottom.uv.x);
        v[1].v = ppc::fmadds(t, brush->dbottom.uv.y, brush->bottom.uv.y);
    }
}

void FlushStroke(RwInt32 count, RwMatrix* ltm, const Rt2dBrush* brush) {
    Rt2dGlobalVars& g = rt2dGlobals;
    const RwUInt32 flags = (brush->texture != nullptr ? 1u : 0u) | g.TransformFlags;
    if (RwIm3DTransform(g.brushVertexCache, static_cast<RwUInt32>(count), ltm, flags) != nullptr) {
        RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRISTRIP, g.topo, count);
        RwIm3DEnd();
    }
}

}  // namespace

// 0x0071de20 DrawUIStrokePathGeometry (Rt2dPathStroke; 0x71e3c0 is a branch to it): every subpath of the
// chain (recursively), flattened into the scratch path when not flat, as a triangle strip of two vertices
// per node (-(halfwidth + inset), +(halfwidth - inset) along the normal) through the vertex cache; above
// 254 vertices the strip is drawn and restarts with the last node again.
Rt2dPath* Rt2dPathStroke(Rt2dPath* path, Rt2dBrush* brush) {
    if (path == nullptr) return path;
    Rt2dGlobalVars& g = rt2dGlobals;
    RwMatrix* ltm = _rt2dCTMGetComposite();
    const RwReal halfwidth = brush->halfwidth;
    const RwReal inset = path->inset;
    const RwReal depth = g.layerDepth;
    Rt2dPath* sub = path;
    if (path->flat == 0) {
        sub = _rt2dGetEmptyScratchPath();
        _rt2dSubPathFlatten(sub, path);
    }
    RwInt32 count;
    rt2dPathNode* nodes = SubPathNodes(sub, &count);
    if (brush->texture != nullptr) {
        const RwUInt32 fa = brush->texture->filterAddressing;
        const RwUInt32 addressU = (fa >> 8) & 0xf;
        const RwUInt32 addressV = (fa >> 12) & 0xf;
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, brush->texture->raster);
        RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, reinterpret_cast<void*>(static_cast<uintptr_t>(fa & 0xff)));
        RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,
                         reinterpret_cast<void*>(static_cast<uintptr_t>((addressU == addressV ? addressV : 0) & 0xf)));
    } else {
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
    }
    const RwReal invLength = 1.0f / nodes[count - 1].dist;
    if (count > 0) {
        const RwReal inner = halfwidth - inset;
        const RwReal outer = halfwidth + inset;
        RwIm3DVertex* v = g.brushVertexCache;
        RwInt32 inBatch = 0;
        const rt2dPathNode* node = nodes;
        RwInt32 i = 0;
        for (;;) {
            if (inBatch > 0xfd) {
                FlushStroke(inBatch, ltm, brush);
                --i;
                --node;
                v = g.brushVertexCache;
                inBatch = 2;
            } else {
                inBatch += 2;
            }
            StrokeVertices(v, node, brush, inner, outer, depth, invLength);
            if (count <= ++i) break;
            v += 2;
            ++node;
        }
        if (inBatch > 0) FlushStroke(inBatch, ltm, brush);
    }
    Rt2dPathStroke(path->next, brush);
    return path;
}

// 0x0071bb80 DrawUIShapeSceneObject (_rt2dShapeRender): a visible shape combines its colour transform with
// the inherited one (offset x 255 here: object offsets are stored x 255). With an atomic: the colour cache
// transformed into the materials (fctiwz, clamped to 0..255), the colour flag cleared, the LTM pushed, the
// atomic's frame placed at the composite CTM and the atomic's render callback called. Without one: per
// node the brush colours transformed for the call (Rt2d_ColorMulAddClamped) and restored, closed fills
// (flag 1) or strokes drawn in immediate mode.
Rt2dObject* _rt2dShapeRender(Rt2dObject* shape, RwRGBAReal* colorMult, RwRGBAReal* colorOffs) {
    if ((shape->flag & 4) == 0) return shape;
    RwRGBAReal mult;
    RwRGBAReal offs;
    const RwReal oa = colorOffs->alpha * 255.0f;
    const RwReal orr = colorOffs->red * 255.0f;
    const RwReal og = colorOffs->green * 255.0f;
    const RwReal ob = colorOffs->blue * 255.0f;
    mult.red = shape->colorMult.red * colorMult->red;
    mult.green = shape->colorMult.green * colorMult->green;
    mult.blue = shape->colorMult.blue * colorMult->blue;
    mult.alpha = shape->colorMult.alpha * colorMult->alpha;
    offs.red = ppc::fmadds(shape->colorOffs.red, colorMult->red, orr);
    offs.green = ppc::fmadds(shape->colorOffs.green, colorMult->green, og);
    offs.blue = ppc::fmadds(shape->colorOffs.blue, colorMult->blue, ob);
    offs.alpha = ppc::fmadds(shape->colorOffs.alpha, colorMult->alpha, oa);
    RpAtomic* atomic = shape->data.shape.atomic;
    if (atomic != nullptr) {
        RpGeometry* geometry = shape->data.shape.rep->geometry;
        for (RwInt32 i = 0; i < geometry->matList.numMaterials; ++i) {
            const RwRGBA cached = shape->data.shape.colorCache[i];
            auto channel = [](RwUInt8 c, RwReal m, RwReal o) -> RwUInt8 {
                const RwInt32 v = ppc::fctiwz(ppc::fmadds(static_cast<RwReal>(c), m, o));
                if (v <= 0) return 0;
                return static_cast<RwUInt8>(v > 0xff ? 0xff : v);
            };
            RpMaterial* material = geometry->matList.materials[i];
            material->color.red = channel(cached.red, mult.red, offs.red);
            material->color.alpha = channel(cached.alpha, mult.alpha, offs.alpha);
            material->color.blue = channel(cached.blue, mult.blue, offs.blue);
            material->color.green = channel(cached.green, mult.green, offs.green);
        }
        shape->flag &= ~8;
        if ((shape->flag & 2) != 0) {
            _rt2dCTMPushMult(&shape->MTM);
            shape->LTM = *_rt2dCTMGet();
            shape->flag &= ~2;
        } else {
            _rt2dCTMPush(&shape->LTM);
        }
        RwFrame* frame = shape->data.shape.atomic->frame;
        RwFrameTransform(frame, _rt2dCTMGetComposite(), rwCOMBINEREPLACE);
        RpAtomic* drawn = shape->data.shape.atomic;
        drawn->renderCallBack(drawn);
        Rt2dCTMPop();
        return shape;
    }
    if ((shape->flag & 2) != 0) {
        _rt2dCTMPushMult(&shape->MTM);
        shape->LTM = *_rt2dCTMGet();
        shape->flag &= ~2;
    } else {
        _rt2dCTMPush(&shape->LTM);
    }
    const RwInt32 count = _rwSListGetNumEntries(shape->data.shape.rep->nodes);
    _rt2dShapeNode* node = static_cast<_rt2dShapeNode*>(_rwSListGetArray(shape->data.shape.rep->nodes));
    for (RwInt32 i = 0; i < count; ++i, ++node) {
        Rt2dBrush* brush = node->brush;
        const RwRGBAReal bottom = brush->bottom.col;
        const RwRGBAReal dbottom = brush->dbottom.col;
        const RwRGBAReal dtop = brush->dtop.col;
        const RwRGBAReal top = brush->top.col;
        _rt2dBrushTransformColor(brush, &bottom, &dbottom, &dtop, &top, &mult, &offs);
        if ((node->flag & 1) != 0) {
            _rt2dPathRenderChain(node->path, brush);
        } else {
            Rt2dPathStroke(node->path, brush);
        }
        brush->bottom.col = bottom;
        brush->dbottom.col = dbottom;
        brush->dtop.col = dtop;
        brush->top.col = top;
    }
    Rt2dCTMPop();
    return shape;
}

// 0x0071d0c0 _rt2dShapeStreamReadTo: the rep (read here without a pool, else the pool entry of a read
// index), its material colours as the colour cache, a reference to the rep, then an atomic with a new
// frame placed at the current composite CTM and the rep's geometry.
// BUG(original): a rep without geometry (no nodes' memory) is read through a null pointer.
Rt2dObject* _rt2dShapeStreamReadTo(Rt2dObject* shape, RwStream* stream, _rt2dSceneResourcePool* pool) {
    _rt2dShapeRep* rep;
    if (pool == nullptr) {
        rep = _rt2dShapeRepStreamRead(stream);
    } else {
        RwUInt32 index = 0;
        if (RwStreamRead(stream, &index, 4) != 4) return nullptr;
        rep = pool->shapeReps[index];
    }
    shape->flag &= ~1;
    RpGeometry* geometry = rep->geometry;
    const RwInt32 numMaterials = geometry->matList.numMaterials;
    RwRGBA* cache = nullptr;
    if (numMaterials != 0) {
        cache = static_cast<RwRGBA*>(RwMalloc(static_cast<RwUInt32>(numMaterials) * sizeof(RwRGBA), 0x30190));
        for (RwInt32 i = 0; i < numMaterials; ++i) cache[i] = geometry->matList.materials[i]->color;
    }
    shape->data.shape.colorCache = cache;
    shape->data.shape.rep = rep;
    ++rep->refCount;
    shape->flag |= 1;
    RwFrame* frame = RwFrameCreate();
    RwFrameTransform(frame, _rt2dCTMGetComposite(), rwCOMBINEREPLACE);
    RpAtomic* atomic = RpAtomicCreate();
    RpAtomicSetFrame(atomic, frame);
    RpAtomicSetGeometry(atomic, rep->geometry, 0);
    shape->data.shape.atomic = atomic;
    return shape;
}
