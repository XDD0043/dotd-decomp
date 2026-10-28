// path.cpp - RW 3.7 tool/2d/path.c, ported from the PS3 library code (0x7146d0-0x718a28). See Rt2d.h.
//
// A path is a chain of subpaths (Rt2dPath::next; the head's curr is the subpath being built). Locked
// (numSegment -1) a subpath's segments are an RwSList of rt2dPathNode, unlocked a plain array of
// numSegment nodes. Each node keeps its point, the unit normal of the segment arriving at it (the
// first node takes its successor's; inner nodes the miter of both, n / (n . avg)) and the length along
// the subpath. Curves are kept as three control nodes (type 2) and flattened when filled or stroked.
//
// Not ported (the front end never reaches them): _rt2dInverseTransformPointByCTM_maybe 0x7146e0,
// _rt2dPathIsPointIn_maybe 0x714788, Rt2dPathMorph 0x714928, Rt2dPathStreamGetSize 0x714c08,
// Rt2dPathInset_maybe 0x714ca8, Rt2dPathRCurveto 0x715f80, Rt2dPathRLineto 0x716048,
// Rt2dPathStreamWrite 0x7160d0, _rt2dSubPathCopy_maybe 0x716b28, Rt2dPathFlatten 0x716c70,
// Rt2dPathGetBBox 0x7176a0, Rt2dPathCopy 0x717a28, Rt2dPathOval 0x717d18, Rt2dPathRoundRect 0x717f00,
// Rt2dPathCreateMorphResultPath_maybe 0x718830.
#include "Renderware/rt2d/Rt2dInternal.h"
#include "Renderware/rwcore/RwMatrix.h"

namespace {

// 0x00c458dc: Rt2dPathSetFreeListCreateParams' block {entries per block 0x20, blocks 1}.
RwInt32 s_pathFreeListBlockSize = 0x20;
RwInt32 s_pathFreeListPreallocBlocks = 1;

inline RwSList* SegmentList(Rt2dPath* path) { return static_cast<RwSList*>(path->segments); }

// 0x00757960 _rwSListEmpty (rwcore; not in RwSList.h yet): no entry filled, the storage kept.
inline void _rwSListEmpty(RwSList* sList) { sList->numElementsFilled = 0; }

// The inlined Rt2dPathCreate: a path from the free list, empty, flat, its own current subpath, locked.
Rt2dPath* NewPath() {
    Rt2dPath* path = static_cast<Rt2dPath*>(RwFreeListAlloc(rt2dGlobals.pathFreeList, 0x301a1));
    if (path != nullptr) {
        path->next = nullptr;
        path->flat = 1;
        path->inset = 0.0f;
        path->segments = nullptr;
        path->numSegment = 0;
        path->closed = 0;
        path->curr = path;
        Rt2dPathLock(path);
    }
    return path;
}

// The inlined destruction of one subpath: its segments (an RwSList when locked) and the path itself.
void FreeSubPath(Rt2dPath* path) {
    if (path->segments != nullptr) {
        if (path->numSegment == -1) {
            _rwSListDestroy(SegmentList(path));
        } else {
            RwFree(path->segments);
        }
    }
    path->segments = nullptr;
    RwFreeListFree(rt2dGlobals.pathFreeList, path);
}

// A subpath's nodes and their count, locked or not (the inlined pattern of the readers).
rt2dPathNode* Nodes(Rt2dPath* path, RwInt32* count) {
    if (path->numSegment == -1) {
        *count = _rwSListGetNumEntries(SegmentList(path));
        return static_cast<rt2dPathNode*>(_rwSListGetArray(SegmentList(path)));
    }
    *count = path->numSegment;
    return static_cast<rt2dPathNode*>(path->segments);
}

// The node-append sequence inlined in Rt2dPathLineto, Rt2dPathClose, _rt2dFlattenBezier and
// _rt2dSubPathFlatten: a node of type at (x, y) appended to owner's (locked) segment list, its length
// and unit normal (prev.x - x, y - prev.y swapped into (ny, nx), through RW_Sqrt / RW_InvSqrt), then the
// previous node's normal: its successor's when it is the first node, else the miter
// (n0 + n1) / ((n0 + n1) . n0).
rt2dPathNode* AppendNode(Rt2dPath* owner, RwInt32 type, RwReal x, RwReal y) {
    const RwInt32 count = _rwSListGetNumEntries(SegmentList(owner));
    rt2dPathNode* node = static_cast<rt2dPathNode*>(_rwSListGetNewEntry(SegmentList(owner), 0x30190));
    node->pos.x = x;
    node->pos.y = y;
    node->type = static_cast<rt2dLinetype>(type);
    rt2dPathNode* prev = node - 1;
    const RwReal dx = prev->pos.x - x;
    const RwReal dy = y - prev->pos.y;
    const RwReal length2 = ppc::fmadds(dy, dy, dx * dx);
    const RwReal length = rwSqrt(length2);
    const RwReal inverse = rwInvSqrt(length2);
    const RwReal dist = length + prev->dist;
    const RwReal ny = dx * inverse;
    const RwReal nx = dy * inverse;
    node->dist = dist;
    node->normal.y = ny;
    node->normal.x = nx;
    if (count > 1) {
        const RwReal sy = prev->normal.y + ny;
        const RwReal sx = prev->normal.x + nx;
        const RwReal t = prev->normal.y * sy;
        const RwReal r = 1.0f / ppc::fmadds(prev->normal.x, sx, t);
        prev->normal.y = sy * r;
        prev->normal.x = sx * r;
    } else {
        prev->normal.x = nx;
        prev->normal.y = node->normal.y;
    }
    return node;
}

}  // namespace

// 0x007146d0 Rt2dPathSetFreeListCreateParams
void Rt2dPathSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    s_pathFreeListPreallocBlocks = numBlocksToPrealloc;
    s_pathFreeListBlockSize = blockSize;
}

// 0x00717930 _rt2dPathOpen_maybe: the path free list and the scratch path (locked twice: the inlined
// Rt2dPathCreate locks it, then the open does).
RwBool _rt2dPathOpen() {
    rt2dGlobals.pathFreeList = RwFreeListCreateAndPreallocateSpace(sizeof(Rt2dPath), s_pathFreeListBlockSize, 4,
                                                                   s_pathFreeListPreallocBlocks, nullptr, 0x401a1);
    Rt2dPath* scratch = NewPath();
    rt2dGlobals.scratch = scratch;
    Rt2dPathLock(scratch);
    return 1;
}

// 0x00716d78 _rt2dPathClose_maybe: the scratch path, then the free list.
RwBool _rt2dPathClose() {
    Rt2dPath* scratch = rt2dGlobals.scratch;
    if (scratch != nullptr) {
        Rt2dPath* next = scratch->next;
        FreeSubPath(scratch);
        Rt2dPathDestroy(next);
    }
    RwFreeListDestroy(rt2dGlobals.pathFreeList);
    rt2dGlobals.pathFreeList = nullptr;
    return 1;  // the PS3 sets no value: r3 still holds RwFreeListDestroy's result
}

// 0x00715198 Rt2dPathCreate
Rt2dPath* Rt2dPathCreate() { return NewPath(); }

// 0x00715028 Rt2dPathLock_maybe: the segment array becomes an RwSList (0x18-byte entries) holding the same
// nodes, for every subpath of the chain. Null when the list cannot be created; a locked path is returned
// as it is.
Rt2dPath* Rt2dPathLock(Rt2dPath* path) {
    if (path == nullptr || path->numSegment == -1) return path;
    RwSList* list = _rwSListCreatePreallocated(sizeof(rt2dPathNode), path->numSegment, 0x301a1);
    if (list == nullptr) return nullptr;
    RwInt32 count;
    rt2dPathNode* nodes = Nodes(path, &count);
    if (count != 0) {
        void* entries = _rwSListGetNewEntries(list, count, 0x301a1);
        if (entries != nullptr) std::memcpy(entries, nodes, static_cast<size_t>(count) * sizeof(rt2dPathNode));
        RwFree(nodes);
    }
    path->segments = list;
    path->numSegment = -1;
    Rt2dPathLock(path->next);
    return path;
}

// 0x007163d0 Rt2dPathUnlock_maybe: every subpath's RwSList becomes a plain array (_rwSListToArray; null
// when empty) with its count.
Rt2dPath* Rt2dPathUnlock(Rt2dPath* path) {
    if (path == nullptr || path->numSegment != -1) return path;
    for (Rt2dPath* p = path; p != nullptr && p->numSegment == -1; p = p->next) {
        const RwInt32 count = _rwSListGetNumEntries(SegmentList(p));
        p->segments = _rwSListToArray(SegmentList(p));
        p->numSegment = count;
    }
    return path;
}

// 0x00716658 Rt2dPathDestroy: every subpath of the chain. 0 for a null path.
RwBool Rt2dPathDestroy(Rt2dPath* path) {
    const RwBool result = path != nullptr ? 1 : 0;
    while (path != nullptr) {
        Rt2dPath* next = path->next;
        FreeSubPath(path);
        path = next;
    }
    return result;
}

// 0x00716e70 _rt2dSubPathDestroyChain_maybe: the subpath's segments, then (recursively) the subpaths
// after it, which are destroyed; the subpath stays, empty, with no successor.
Rt2dPath* _rt2dSubPathDestroyChain(Rt2dPath* path) {
    if (path->numSegment == -1) {
        _rwSListDestroy(SegmentList(path));
    } else if (path->segments != nullptr) {
        RwFree(path->segments);
    }
    path->numSegment = 0;
    path->segments = nullptr;
    if (path->next != nullptr) {
        _rt2dSubPathDestroyChain(path->next);
        Rt2dPathDestroy(path->next);
        path->next = nullptr;
    }
    return path;
}

// 0x00717580 Rt2dPathEmpty (the path locked): the subpaths after the first destroyed, the first emptied.
Rt2dPath* Rt2dPathEmpty(Rt2dPath* path) {
    Rt2dPath* next = path->next;
    if (next != nullptr) {
        Rt2dPath* after = next->next;
        FreeSubPath(next);
        Rt2dPathDestroy(after);
    }
    path->next = nullptr;
    _rwSListEmpty(SegmentList(path));
    path->curr = path;
    path->closed = 0;
    path->flat = 1;
    return path;
}

// 0x00716ab0 _rt2dGetEmptyScratchPath_maybe
Rt2dPath* _rt2dGetEmptyScratchPath() {
    Rt2dPath* scratch = rt2dGlobals.scratch;
    Rt2dPathDestroy(scratch->next);
    scratch->next = nullptr;
    _rwSListEmpty(SegmentList(scratch));
    scratch->curr = scratch;
    scratch->closed = 0;
    scratch->flat = 1;
    return rt2dGlobals.scratch;
}

// 0x00717b90 Rt2dPathMoveto: starts the current subpath, or (when it has points) a new subpath after it.
Rt2dPath* Rt2dPathMoveto(Rt2dPath* path, RwReal x, RwReal y) {
    const RwInt32 count = _rwSListGetNumEntries(SegmentList(path->curr));
    if (count == 0) {
        rt2dPathNode* node = static_cast<rt2dPathNode*>(_rwSListGetNewEntry(SegmentList(path->curr), 0x30190));
        node->pos.x = x;
        node->dist = 0.0f;
        node->type = rt2dMOVE;
        node->pos.y = y;
        node->normal.x = 0.0f;
        node->normal.y = 0.0f;
        return path;
    }
    Rt2dPath* curr = path->curr;
    Rt2dPath* sub = NewPath();
    curr->next = sub;
    Rt2dPathLock(path->curr->next);
    path->curr = path->curr->next;
    Rt2dPathMoveto(path, x, y);
    return path;
}

// 0x007158b8 Rt2dPathLineto
Rt2dPath* Rt2dPathLineto(Rt2dPath* path, RwReal x, RwReal y) {
    AppendNode(path->curr, rt2dLINE, x, y);
    return path;
}

// 0x00715630 Rt2dPathCurveto: three curve nodes (type 2), each with its normal and length from the node
// before (the first one also adjusts its predecessor's normal); the current subpath is no longer flat.
Rt2dPath* Rt2dPathCurveto(Rt2dPath* path, RwReal x1, RwReal y1, RwReal x2, RwReal y2, RwReal x3, RwReal y3) {
    RwSList* list = SegmentList(path->curr);
    const RwInt32 count = _rwSListGetNumEntries(list);
    rt2dPathNode* n0 = static_cast<rt2dPathNode*>(_rwSListGetNewEntries(list, 3, 0x30190));
    n0->pos.x = x1;
    n0->pos.y = y1;
    n0->type = rt2dCURVE;
    rt2dPathNode* prev = n0 - 1;
    RwReal dx = prev->pos.x - x1;
    RwReal dy = y1 - prev->pos.y;
    RwReal length2 = ppc::fmadds(dy, dy, dx * dx);
    RwReal length = rwSqrt(length2);
    RwReal inverse = rwInvSqrt(length2);
    RwReal dist = length + prev->dist;
    RwReal ny = dx * inverse;
    RwReal nx = dy * inverse;
    n0->dist = dist;
    n0->normal.y = ny;
    n0->normal.x = nx;
    if (count > 1) {
        const RwReal sy = prev->normal.y + ny;
        const RwReal sx = prev->normal.x + nx;
        const RwReal t = prev->normal.y * sy;
        const RwReal r = 1.0f / ppc::fmadds(prev->normal.x, sx, t);
        prev->normal.y = sy * r;
        prev->normal.x = sx * r;
    } else {
        prev->normal.x = nx;
        prev->normal.y = n0->normal.y;
    }
    rt2dPathNode* n1 = n0 + 1;
    rt2dPathNode* n2 = n0 + 2;
    n1->pos.x = x2;
    dx = n0->pos.x - x2;
    n1->pos.y = y2;
    dy = y2 - n0->pos.y;
    n1->type = rt2dCURVE;
    length2 = ppc::fmadds(dy, dy, dx * dx);
    length = rwSqrt(length2);
    inverse = rwInvSqrt(length2);
    n2->pos.x = x3;
    const RwReal dx2 = n1->pos.x - x3;
    dx = dx * inverse;
    n2->pos.y = y3;
    const RwReal dy2 = y3 - n1->pos.y;
    dy = dy * inverse;
    length = length + n0->dist;
    n2->type = rt2dCURVE;
    n1->normal.y = dx;
    const RwReal length2b = ppc::fmadds(dy2, dy2, dx2 * dx2);
    n1->normal.x = dy;
    n1->dist = length;
    const RwReal lengthB = rwSqrt(length2b);
    const RwReal inverseB = rwInvSqrt(length2b);
    const RwReal distB = lengthB + n1->dist;
    const RwReal ny2 = dx2 * inverseB;
    const RwReal nx2 = dy2 * inverseB;
    n2->dist = distB;
    n2->normal.y = ny2;
    n2->normal.x = nx2;
    path->curr->flat = 0;
    return path;
}

// 0x00715a38 Rt2dPathClose: unless the current subpath already ends on its first point, a line back to
// it; then the first and last nodes share the miter of their normals; the subpath is closed.
Rt2dPath* Rt2dPathClose(Rt2dPath* path) {
    Rt2dPath* curr = path->curr;
    const RwInt32 count = _rwSListGetNumEntries(SegmentList(curr));
    rt2dPathNode* first = static_cast<rt2dPathNode*>(_rwSListGetArray(SegmentList(curr)));
    rt2dPathNode* last = static_cast<rt2dPathNode*>(_rwSListGetEntry(SegmentList(curr), count - 1));
    const RwReal fy = first->pos.y;
    const RwReal fx = first->pos.x;
    if (!(fy - last->pos.y == 0.0f) || !(last->pos.x - fx == 0.0f)) {
        AppendNode(path->curr, rt2dLINE, fx, fy);
        first = static_cast<rt2dPathNode*>(_rwSListGetArray(SegmentList(curr)));
        last = static_cast<rt2dPathNode*>(_rwSListGetEntry(SegmentList(curr), count));
    }
    const RwReal sy = first->normal.y + last->normal.y;
    const RwReal sx = first->normal.x + last->normal.x;
    const RwReal t = first->normal.y * sy;
    const RwReal r = 1.0f / ppc::fmadds(first->normal.x, sx, t);
    const RwReal nx = sx * r;
    const RwReal ny = sy * r;
    last->normal.x = nx;
    last->normal.y = ny;
    first->normal.x = nx;
    first->normal.y = last->normal.y;
    curr->closed = 1;
    return path;
}

// 0x00717e60 Rt2dPathRect
Rt2dPath* Rt2dPathRect(Rt2dPath* path, RwReal x, RwReal y, RwReal w, RwReal h) {
    Rt2dPathMoveto(path, x, y);
    const RwReal right = x + w;
    const RwReal top = y + h;
    Rt2dPathLineto(path, right, y);
    Rt2dPathLineto(path, right, top);
    Rt2dPathLineto(path, x, top);
    Rt2dPathClose(path);
    return path;
}

// 0x00715238 _rt2dFlattenBezier_maybe: recursive subdivision at t = 1/2 (de Casteljau) until both inner
// control points lie within the squared tolerance of the chord, or depth runs out; each flat piece adds a
// line node to its end point.
void _rt2dFlattenBezier(Rt2dPath* owner, const RwV2d* pts, RwInt32 depth) {
    --depth;
    if (depth >= 0) {
        const RwReal x0 = pts[0].x, y0 = pts[0].y;
        const RwReal x1 = pts[1].x, y1 = pts[1].y;
        const RwReal ax = x1 - x0;
        const RwReal ay = y1 - y0;
        const RwReal cx = pts[3].x - x0;
        const RwReal cy = pts[3].y - y0;
        const RwReal tolerance = rt2dGlobals.sqTolerance;
        RwReal a2 = ppc::fmadds(ax, ax, ay * ay);
        const RwReal c2 = ppc::fmadds(cx, cx, cy * cy);
        RwReal dot = ppc::fmadds(cx, ax, cy * ay);
        a2 = a2 - tolerance;
        dot = dot * dot;
        a2 = c2 * a2;
        RwBool subdivide = 1;
        if (!(a2 >= dot)) {
            const RwReal bx = pts[2].x - x0;
            const RwReal by = pts[2].y - y0;
            RwReal b2 = ppc::fmadds(bx, bx, by * by);
            RwReal dotB = ppc::fmadds(cx, bx, cy * by);
            b2 = b2 - tolerance;
            dotB = dotB * dotB;
            b2 = c2 * b2;
            if (b2 < dotB) subdivide = 0;
        }
        if (subdivide) {
            const RwReal x2 = pts[2].x, y2 = pts[2].y;
            const RwReal q1x = (x0 + x1) * 0.5f;
            const RwReal q1y = (y0 + y1) * 0.5f;
            const RwReal my = (y1 + y2) * 0.5f;
            const RwReal mx = (x1 + x2) * 0.5f;
            const RwReal q2y = (my + q1y) * 0.5f;
            const RwReal q2x = (mx + q1x) * 0.5f;
            const RwReal r2y = (pts[3].y + y2) * 0.5f;
            const RwReal r2x = (pts[3].x + x2) * 0.5f;
            const RwReal r1y = (my + r2y) * 0.5f;
            const RwReal r1x = (mx + r2x) * 0.5f;
            const RwReal midy = (q2y + r1y) * 0.5f;
            const RwReal midx = (q2x + r1x) * 0.5f;
            const RwV2d left[4] = {{x0, y0}, {q1x, q1y}, {q2x, q2y}, {midx, midy}};
            const RwV2d right[4] = {{midx, midy}, {r1x, r1y}, {r2x, r2y}, {pts[3].x, pts[3].y}};
            _rt2dFlattenBezier(owner, left, depth);
            _rt2dFlattenBezier(owner, right, depth);
            return;
        }
    }
    AppendNode(owner, rt2dLINE, pts[3].x, pts[3].y);
}

// 0x00715c78 _rt2dSubPathFlatten_maybe: src's nodes appended to dst (locked): moves copied, lines
// re-appended (normals and lengths recomputed), curves flattened (depth flatDepth) with the squared
// tolerance of the current CTM; a closed src closes dst.
Rt2dPath* _rt2dSubPathFlatten(Rt2dPath* dst, Rt2dPath* src) {
    rt2dGlobals.sqTolerance = _rt2dGetTolerance();
    RwInt32 count;
    rt2dPathNode* node = Nodes(src, &count);
    for (RwInt32 i = 0; i < count; ++i, ++node) {
        if (node->type == rt2dCURVE) {
            const RwV2d pts[4] = {node[-1].pos, node[0].pos, node[1].pos, node[2].pos};
            _rt2dFlattenBezier(dst, pts, rt2dGlobals.flatDepth);
            i += 2;
            node += 2;
        } else if (node->type == rt2dLINE) {
            AppendNode(dst, rt2dLINE, node->pos.x, node->pos.y);
        } else {
            rt2dPathNode* copy = static_cast<rt2dPathNode*>(_rwSListGetNewEntry(SegmentList(dst), 0x301a1));
            *copy = *node;
        }
    }
    if (src->closed != 0) Rt2dPathClose(dst);
    return dst;
}

// 0x00714df0 _rt2dSubPathAccumulateBBox_maybe: bbox {minx, miny, maxx, maxy} grown by every point (each
// coordinate updates either its minimum or, failing that, its maximum).
RwReal* _rt2dSubPathAccumulateBBox(Rt2dPath* path, RwReal* bbox) {
    RwInt32 count;
    rt2dPathNode* node = Nodes(path, &count);
    for (RwInt32 i = 0; i < count; ++i, ++node) {
        const RwReal x = node->pos.x;
        if (bbox[0] > x) {
            bbox[0] = x;
        } else if (!(bbox[2] >= x)) {
            bbox[2] = x;
        }
        const RwReal y = node->pos.y;
        if (bbox[1] > y) {
            bbox[1] = y;
        } else if (!(bbox[3] >= y)) {
            bbox[3] = y;
        }
    }
    return bbox;
}

// 0x00714f08 _rt2dPathRemoveDegenerateSubPaths_maybe (locked): drops the subpaths of exactly one node.
Rt2dPath* _rt2dPathRemoveDegenerateSubPaths(Rt2dPath* path) {
    if (path == nullptr) return path;
    path->next = _rt2dPathRemoveDegenerateSubPaths(path->next);
    if (_rwSListGetNumEntries(SegmentList(path)) != 1) return path;
    Rt2dPath* next = path->next;
    FreeSubPath(path);
    return next;
}

// 0x007181f8 _rt2dSubPathStreamReadData_maybe: the path's old segments and successors released, then
// {numSegment, flags (1 closed, 2 flat, 4 another subpath follows in a 0x1a1 chunk), inset} from the
// header and the nodes (unlocked array). A following subpath that fails is destroyed; one with another
// record version is kept as it is (empty, locked). Every successor's curr is set to path.
Rt2dPath* _rt2dSubPathStreamReadData(Rt2dPath* path, const RwInt32* header, RwStream* stream) {
    if (path->numSegment == -1) {
        _rwSListDestroy(SegmentList(path));
    } else if (path->segments != nullptr) {
        RwFree(path->segments);
    }
    path->segments = nullptr;
    path->numSegment = 0;
    if (path->next != nullptr) {
        _rt2dSubPathDestroyChain(path->next);
        Rt2dPathDestroy(path->next);
        path->next = nullptr;
    }
    path->curr = path;
    path->numSegment = header[1];
    path->closed = static_cast<RwUInt32>(header[2]) & 1;
    path->flat = (static_cast<RwUInt32>(header[2]) >> 1) & 1;
    std::memcpy(&path->inset, &header[3], sizeof(RwReal));
    const RwUInt32 size = static_cast<RwUInt32>(path->numSegment) * sizeof(rt2dPathNode);
    void* nodes = RwMalloc(size, 0x301a1);
    if (nodes == nullptr) return nullptr;
    if (path->numSegment != 0) {
        if (RwStreamRead(stream, nodes, size) != size) return nullptr;  // BUG(original): nodes leaks
        // RwMemLittleEndian32: the words are already native on a little-endian host.
    }
    path->segments = nodes;
    if ((static_cast<RwUInt32>(header[2]) & 4) != 0) {
        if (RwStreamFindChunk(stream, 0x1a1, nullptr, nullptr) == 0) return nullptr;
        Rt2dPath* next = NewPath();
        RwInt32 nextHeader[4];
        if (RwStreamRead(stream, nextHeader, sizeof(nextHeader)) != sizeof(nextHeader)) {
            Rt2dPathDestroy(next);
            path->next = nullptr;
        } else {
            Rt2dPath* read = next;
            if (nextHeader[0] == 1) read = _rt2dSubPathStreamReadData(next, nextHeader, stream);
            if (read != nullptr) {
                path->next = read;
            } else {
                Rt2dPathDestroy(next);
                path->next = nullptr;
            }
        }
    }
    for (Rt2dPath* p = path->next; p != nullptr; p = p->next) p->curr = path;
    return path;
}

// 0x00718540 _rt2dPathStreamReadTo: the 0x10-byte header; version 1 reads the data, another version
// leaves the path as it is.
Rt2dPath* _rt2dPathStreamReadTo(Rt2dPath* path, RwStream* stream) {
    RwInt32 header[4];
    if (RwStreamRead(stream, header, sizeof(header)) != sizeof(header)) return nullptr;
    if (header[0] != 1) return path;
    return _rt2dSubPathStreamReadData(path, header, stream);
}

// 0x007185e0 Rt2dPathStreamRead (after the caller's RwStreamFindChunk(0x1a1)): a new path and its data;
// on failure the path is destroyed. Another record version returns the new, empty (locked) path.
Rt2dPath* Rt2dPathStreamRead(RwStream* stream) {
    Rt2dPath* path = NewPath();
    RwInt32 header[4];
    Rt2dPath* result = nullptr;
    if (RwStreamRead(stream, header, sizeof(header)) == sizeof(header)) {
        result = path;
        if (header[0] == 1) result = _rt2dSubPathStreamReadData(path, header, stream);
        if (result != nullptr) return result;
    }
    if (path != nullptr) {
        Rt2dPath* next = path->next;
        FreeSubPath(path);
        Rt2dPathDestroy(next);
    }
    return nullptr;
}
