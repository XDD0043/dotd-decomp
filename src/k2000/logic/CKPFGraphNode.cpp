// CKPFGraphNode.cpp - reconstructed original translation unit 0x1ea3e0-0x1f0380 (GAME_TOC1, main_toc1), 33 functions, 27 live.
// Primary class: CKPFGraphNode  key 0x40c  category Logic  size 0x38  vtable 0xb1e618
// Other owners: NavSector (2), NavGrid (1), NavSectors (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1ea3e0  CPFSector_FindIndexFromVector
//   [x] 0x1ea470  CPFSector_FindVectorFromIndex
//   [ ] 0x1ea4e0  CKPFGraphNode_IsCellInBounds_maybe  [dead]
//   [ ] 0x1ea528  CKPFGraphNode_PlotCircleCells_maybe  [dead]
//   [x] 0x1eabc8  CPFSector_IsPathWalkableWithWidth
//   [x] 0x1ebd30  CKPFGraphNode_FreeCells_maybe
//   [x] 0x1ebd60  CKPFGraphNode_ConstructBase_maybe
//   [ ] 0x1ebd98  CKPFGraphNode_ConstructBase_2_maybe  [dead]
//   [x] 0x1ebdd0  CKPFGraphNode_LoadBoundsAndCells
//   [x] 0x1ebf00  CKPFGraphNode_SaveBoundsAndCells_maybe
//   [x] 0x1ec108  CPFSector_IsPathWalkable
//   [x] 0x1ec820  CPFSector_OptimizeGridPath
//   [ ] 0x1ecfc8  CKPFGraphNode_FindFirstBlockedCellOnSegment_maybe  [dead]
//   [x] 0x1ed3c0  NavGrid_SetBoxBlocked
//   [x] 0x1ed6e0  CKPFGraphNode_FindNearestWalkableCell_maybe
//   [x] 0x1ee190  NavSector_ClampPointWithClearance_maybe
//   [ ] 0x1ee920  CKPFGraphNode_SnapToNearestWalkableCell_maybe  [dead]
//   [ ] 0x1ef0b0  CKPFGraphNode_SetCircleBlocked_maybe  [dead]
//   [x] 0x1efb10  CKPFGraphNode_Delete
//   [x] 0x1efb60  CKPFGraphNode_RecursiveRegistration
//   [x] 0x1efbc8  CKPFGraphNode_PostLoad  (1: the inherited default)
//   [ ] 0x1efbd0  RegisterCKPFGraphNodeClass
//   [ ] 0x1efc48  _GLOBAL__I_1efc48
//   [x] 0x1efc58  CKPFGraphNode_Construct
//   [x] 0x1efca8  CKPFGraphNode_Construct_2  (the same code as 0x1efc58 CKPFGraphNode_Construct)
//   [x] 0x1efcf8  CKPFGraphNode_DeleteArray
//   [x] 0x1efda0  CKPFGraphNode_FindTransitionIndexTo_maybe
//   [x] 0x1efe18  NavSectors_FindBoxIdAtPoint_maybe
//   [ ] 0x1efef8  CKPFGraphNode_Save
//   [x] 0x1eff00  CKPFGraphNode_Destroy
//   [x] 0x1effa8  CKPFGraphNode_Load
//   [x] 0x1f0248  CKPFGraphNode_Create
//   [x] 0x1f02b0  CKPFGraphNode_CreateArray
//
//   [ ] 0x9b04b0  CKPFGraphNode_GetClassType  [inline]
//   [ ] 0x9b04b8  CKPFGraphNode_GetClassID  [inline]
//   [ ] 0x9b04c0  CKPFGraphNode_IsKindOfClass  [inline]
//   [ ] 0x9b04e0  CKPFGraphNode_Destructor  [inline]
//   [ ] 0x9b0548  CKPFGraphNode_DeletingDestructor  [inline]
#include "k2000/logic/CKPFGraphNode.h"

#include <cmath>

#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKPFGraphTransition.h"
#include "k2000/math/CVector2.h"
#include "k2000/memory/Mem.h"

namespace {
// 0x00010690 Math_Sqrtf (fsqrts).
inline float MathSqrtf(float x) { return std::sqrt(x); }

// 0x00c50d64: the shared null vector (zero; the static initialisers fill it).
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};

// The centre of a cell at the box's bottom plus 0.01 (CellToWorldPos, also inlined in FindNearestWalkableCell).
void CellCentre(const CBBox& box, uint8_t x, uint8_t z, CVector3* out) {
    const float cellSize = g_pfGridScale.m_cellSize;
    const float fx = static_cast<float>(x) + 0.5f;
    const float fz = static_cast<float>(z) + 0.5f;
    out->x = ppc::fmadds(fx, cellSize, box.m_inf.x);
    out->y = box.m_inf.y + 0.01f;  // 0x3c23d70a
    out->z = ppc::fmadds(cellSize, fz, box.m_inf.z);
}

// The cell test of the segment walks: (x, z), inside the grid (the callers test it), fails when its palette value is
// blocked, or in strict mode is anything but 1.
bool CellFails(const CPFGrid& grid, int32_t x, int32_t z, uint8_t strict) {
    const uint8_t palette = PFCellPalette(&grid, static_cast<uint8_t>(x), static_cast<uint8_t>(z));
    if (strict != 0) return palette != 1;
    return PFPaletteBlocked(palette);
}

// Whether (x, z) is inside the grid (signed compares, as the original's) and fails.
bool CellInsideFails(const CPFGrid& grid, int32_t x, int32_t z, uint8_t strict) {
    if (x < 0 || z < 0 || static_cast<int32_t>(grid.m_width) <= x || static_cast<int32_t>(grid.m_height) <= z) {
        return false;
    }
    return CellFails(grid, x, z, strict);
}
}  // namespace

// 0x001ebdd0 CKPFGraphNode_LoadBoundsAndCells (CPFSector::Load; the type is not tested).
int32_t CPFSector::Load(IKFile* file, int32_t /*type*/) {
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_box.m_inf), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_box.m_sup), 3);
    m_grid.Load(file);
    return 1;
}

// 0x001ea3e0 CPFSector_FindIndexFromVector
void CPFSector::WorldToCell(const CVector3* point, uint8_t* cell) const {
    const float inv = g_pfGridScale.m_invCellSize;
    int32_t x = ppc::fctiwz((point->x - m_box.m_inf.x) * inv);
    int32_t z = ppc::fctiwz((point->z - m_box.m_inf.z) * inv);
    if ((x & 0xff) == m_grid.m_width) x = x - 1;
    if ((z & 0xff) == m_grid.m_height) z = z - 1;
    cell[0] = static_cast<uint8_t>(x);
    cell[1] = static_cast<uint8_t>(z);
}

// 0x001ea470 CPFSector_FindVectorFromIndex
void CPFSector::CellToWorldPos(const uint8_t* cell, CVector3* out) const { CellCentre(m_box, cell[0], cell[1], out); }

// 0x001ec108 CPFSector_IsPathWalkable. Along y the column is taken from the low byte of the truncated x,
// sign-extended (the original's lbz / extsb), along x the full integers.
uint8_t CPFSector::IsSegmentWalkable(const CVector2* a, const CVector2* b, uint8_t strict) {
    const CPFGrid& grid = m_grid;
    const int32_t width = grid.m_width;
    const int32_t height = grid.m_height;
    {
        const int32_t bx = ppc::fctiwz(b->m_fX);
        const int32_t ax = ppc::fctiwz(a->m_fX);
        if (ax == bx && ppc::fctiwz(a->m_fY) == ppc::fctiwz(b->m_fY)) return 1;
        if (ax >= 0) {
            const int32_t ay = ppc::fctiwz(a->m_fY);
            if (ay >= 0 && width > ax && height > ay && CellFails(grid, ax, ay, strict)) return 0;
        }
        const int32_t bx2 = ppc::fctiwz(b->m_fX);
        if (bx2 >= 0) {
            const int32_t by = ppc::fctiwz(b->m_fY);
            if (by >= 0 && width > bx2 && height > by && CellFails(grid, bx2, by, strict)) return 0;
        }
    }
    const float adx = std::fabs(b->m_fX - a->m_fX);
    const float ady = std::fabs(b->m_fY - a->m_fY);
    if (adx >= ady) {
        // Along x.
        float lo, loY, hiY, hi;
        if (a->m_fX <= b->m_fX) {
            lo = a->m_fX;
            loY = a->m_fY;
            hiY = b->m_fY;
            hi = b->m_fX;
        } else {
            lo = b->m_fX;
            loY = b->m_fY;
            hiY = a->m_fY;
            hi = a->m_fX;
        }
        const float first = static_cast<float>(ppc::fctiwz(lo) + 1) - lo;
        float x = lo + first;
        if (x >= hi) return 1;
        const float slope = (hiY - loY) / adx;
        int32_t prevRow = ppc::fctiwz(loY);
        float y = ppc::fmadds(slope, first, loY);
        for (;;) {
            const int32_t row = ppc::fctiwz(y);
            const int32_t col = ppc::fctiwz(x + 0.5f);
            if (col >= 0 && row >= 0 && width > col && height > row && CellFails(grid, col, row, strict)) return 0;
            if (row != prevRow) {
                const int32_t col2 = ppc::fctiwz(x - 0.5f);
                if (col2 >= 0 && row >= 0 && width > col2 && height > row && CellFails(grid, col2, row, strict)) {
                    return 0;
                }
                prevRow = row;
            }
            x = x + 1.0f;
            if (x >= hi) return 1;
            y = y + slope;
        }
    }
    // Along y.
    float lo, loX, hi, hiX;
    if (a->m_fY <= b->m_fY) {
        lo = a->m_fY;
        loX = a->m_fX;
        hi = b->m_fY;
        hiX = b->m_fX;
    } else {
        lo = b->m_fY;
        loX = b->m_fX;
        hi = a->m_fY;
        hiX = a->m_fX;
    }
    const float first = static_cast<float>(ppc::fctiwz(lo) + 1) - lo;
    float y = first + lo;
    if (hi <= y) return 1;
    const float slope = (hiX - loX) / ady;
    int32_t prevCol = ppc::fctiwz(loX);
    float x = ppc::fmadds(slope, first, loX);
    for (;;) {
        const int32_t colFull = ppc::fctiwz(x);
        const int32_t col = static_cast<int8_t>(colFull & 0xff);
        if (col >= 0) {
            const int32_t row = static_cast<int8_t>(ppc::fctiwz(y + 0.5f) & 0xff);
            if (row >= 0 && width > col && height > row && CellFails(grid, col, row, strict)) return 0;
        }
        if (colFull != prevCol && col >= 0) {
            const int32_t row2 = ppc::fctiwz(y - 0.5f);
            if (row2 >= 0 && width > col && height > row2 && CellFails(grid, col, row2, strict)) return 0;
        }
        y = y + 1.0f;
        if (hi <= y) return 1;
        x = x + slope;
        prevCol = colFull;
    }
}

// 0x001eabc8 CPFSector_IsPathWalkableWithWidth. The two side edges are the segment moved by
// +-(-dy, dx) * width / cell size (the direction normalised unless zero). Along the major axis each edge is walked one
// cell line at a time from the line after its start up to the line after the end (the first edge's); a step into a
// new minor cell also tests the cell the edge entered it from (`step` = 1 / slope, or 1 for a zero slope, compared
// with the edge's offset to the first line).
uint8_t CPFSector::IsWideSegmentWalkable(float width, const CVector2* a, const CVector2* b, uint8_t strict) {
    const CPFGrid& grid = m_grid;
    const int32_t gw = grid.m_width;
    const int32_t gh = grid.m_height;
    {
        const int32_t bx = ppc::fctiwz(b->m_fX);
        const int32_t ax = ppc::fctiwz(a->m_fX);
        if (ax == bx && ppc::fctiwz(a->m_fY) == ppc::fctiwz(b->m_fY)) return 1;
    }
    float dx = b->m_fX - a->m_fX;
    float dy = b->m_fY - a->m_fY;
    const float length = MathSqrtf(ppc::fmadds(dx, dx, dy * dy));
    if (length != 0.0f) {
        const float inv = 1.0f / length;
        dy = dy * inv;
        dx = dx * inv;
    }
    const float w = width * g_pfGridScale.m_invCellSize;
    float ox = -dy * w;
    float oy = dx * w;
    // The four corners (left edge a, b; right edge a, b).
    const float p1x = ox + a->m_fX;
    const float p1y = oy + a->m_fY;
    if (CellInsideFails(grid, ppc::fctiwz(p1x), ppc::fctiwz(p1y), strict)) return 0;
    const float p2x = ox + b->m_fX;
    const float p2y = oy + b->m_fY;
    if (CellInsideFails(grid, ppc::fctiwz(p2x), ppc::fctiwz(p2y), strict)) return 0;
    ox = -ox;
    oy = -oy;
    const float p3x = a->m_fX + ox;
    const float p3y = a->m_fY + oy;
    if (CellInsideFails(grid, ppc::fctiwz(p3x), ppc::fctiwz(p3y), strict)) return 0;
    const float p4x = b->m_fX + ox;
    const float p4y = b->m_fY + oy;
    if (CellInsideFails(grid, ppc::fctiwz(p4x), ppc::fctiwz(p4y), strict)) return 0;

    const float adx = std::fabs(b->m_fX - a->m_fX);
    const float ady = std::fabs(b->m_fY - a->m_fY);
    if (adx >= ady) {
        // Along x: e1 (x, y) the first edge's start, e2 the second's, endX the first edge's end.
        float e1x, e1y, endX, endY, e2x, e2y;
        if (a->m_fX <= b->m_fX) {
            e1y = p1y;
            e1x = p1x;
            endX = p2x;
            endY = p2y;
            e2y = p3y;
            e2x = p3x;
        } else {
            e1y = p2y;
            e1x = p2x;
            endX = p1x;
            endY = p1y;
            e2y = p4y;
            e2x = p4x;
        }
        float line1 = e1x + 1.0f;
        float line2 = e2x + 1.0f;
        const float slope = (endY - e1y) / adx;
        const float first1 = static_cast<float>(ppc::fctiwz(line1)) - e1x;
        const float first2 = static_cast<float>(ppc::fctiwz(line2)) - e2x;
        const float step = slope != 0.0f ? 1.0f / slope : 1.0f;
        const float last = static_cast<float>(ppc::fctiwz(endX + 1.0f));
        if (last <= line1) return 1;
        float next1 = e1y + slope;
        float next2 = slope + e2y;
        float cur1 = e1y;
        float cur2 = e2y;
        for (;;) {
            // The first edge.
            {
                const int32_t col = ppc::fctiwz(line1);
                const int32_t row = ppc::fctiwz(next1);
                if (CellInsideFails(grid, col, row, strict)) return 0;
                if (ppc::fctiwz(cur1) != row) {
                    if (slope > 0.0f) {
                        const float t = step * (static_cast<float>(row) - cur1);
                        if (t <= first1) {
                            if (CellInsideFails(grid, col - 1, row, strict)) return 0;
                        } else if (col >= 0 && CellInsideFails(grid, col, row - 1, strict)) {
                            return 0;
                        }
                    } else {
                        const float t = step * (static_cast<float>(row + 1) - cur1);
                        if (t <= first1) {
                            if (CellInsideFails(grid, col - 1, row, strict)) return 0;
                        } else if (col >= 0 && CellInsideFails(grid, col, row + 1, strict)) {
                            return 0;
                        }
                    }
                }
            }
            // The second edge.
            {
                const int32_t col = ppc::fctiwz(line2);
                const int32_t row = ppc::fctiwz(next2);
                if (CellInsideFails(grid, col, row, strict)) return 0;
                if (ppc::fctiwz(cur2) != row) {
                    if (slope > 0.0f) {
                        const float t = step * (static_cast<float>(row) - cur2);
                        if (t <= first2) {
                            if (CellInsideFails(grid, col - 1, row, strict)) return 0;
                        } else if (col >= 0 && CellInsideFails(grid, col, row - 1, strict)) {
                            return 0;
                        }
                    } else {
                        const float t = step * (static_cast<float>(row + 1) - cur2);
                        if (t <= first2) {
                            if (CellInsideFails(grid, col - 1, row, strict)) return 0;
                        } else if (col >= 0 && CellInsideFails(grid, col, row + 1, strict)) {
                            return 0;
                        }
                    }
                }
            }
            line1 = line1 + 1.0f;
            if (last <= line1) return 1;
            cur2 = next2;
            cur1 = next1;
            line2 = line2 + 1.0f;
            next2 = next2 + slope;
            next1 = next1 + slope;
        }
    }
    // Along y.
    float e1x, e1y, endX, endY, e2x, e2y;
    if (a->m_fY <= b->m_fY) {
        e1x = p1x;
        e1y = p1y;
        endX = p2x;
        endY = p2y;
        e2y = p3y;
        e2x = p3x;
    } else {
        e1x = p2x;
        e1y = p2y;
        endX = p1x;
        endY = p1y;
        e2y = p4y;
        e2x = p4x;
    }
    const float slope = (endX - e1x) / ady;
    const float step = slope != 0.0f ? 1.0f / slope : 1.0f;
    float line1 = e1y + 1.0f;
    float line2 = e2y + 1.0f;
    const float lastLine = endY + 1.0f;
    const int32_t i1 = ppc::fctiwz(line1);
    const int32_t i2 = ppc::fctiwz(line2);
    const float last = static_cast<float>(ppc::fctiwz(lastLine));
    const float first1 = static_cast<float>(i1) - e1y;
    const float first2 = static_cast<float>(i2) - e2y;
    if (line1 >= last) return 1;
    float next1 = e1x + slope;
    float next2 = slope + e2x;
    float cur1 = e1x;
    float cur2 = e2x;
    for (;;) {
        // The first edge.
        {
            const int32_t col = ppc::fctiwz(next1);
            const int32_t row = ppc::fctiwz(line1);
            if (CellInsideFails(grid, col, row, strict)) return 0;
            if (ppc::fctiwz(cur1) != col) {
                if (slope > 0.0f) {
                    const float t = step * (static_cast<float>(col) - cur1);
                    if (t <= first1) {
                        if (col >= 0 && CellInsideFails(grid, col, row - 1, strict)) return 0;
                    } else if (CellInsideFails(grid, col - 1, row, strict)) {
                        return 0;
                    }
                } else {
                    const float t = step * (static_cast<float>(col + 1) - cur1);
                    if (t <= first1) {
                        if (col >= 0 && CellInsideFails(grid, col, row - 1, strict)) return 0;
                    } else if (CellInsideFails(grid, col + 1, row, strict)) {
                        return 0;
                    }
                }
            }
        }
        // The second edge.
        {
            const int32_t col = ppc::fctiwz(next2);
            const int32_t row = ppc::fctiwz(line2);
            if (CellInsideFails(grid, col, row, strict)) return 0;
            if (ppc::fctiwz(cur2) != col) {
                if (slope > 0.0f) {
                    const float t = step * (static_cast<float>(col) - cur2);
                    if (t <= first2) {
                        if (col >= 0 && CellInsideFails(grid, col, row - 1, strict)) return 0;
                    } else if (CellInsideFails(grid, col - 1, row, strict)) {
                        return 0;
                    }
                } else {
                    const float t = step * (static_cast<float>(col + 1) - cur2);
                    if (t <= first2) {
                        if (col >= 0 && CellInsideFails(grid, col, row - 1, strict)) return 0;
                    } else if (CellInsideFails(grid, col + 1, row, strict)) {
                        return 0;
                    }
                }
            }
        }
        line1 = line1 + 1.0f;
        if (line1 >= last) return 1;
        cur2 = next2;
        cur1 = next1;
        line2 = line2 + 1.0f;
        next2 = next2 + slope;
        next1 = next1 + slope;
    }
    (void)gw;
    (void)gh;
}

// 0x001ec820 CPFSector_OptimizeGridPath. `path` holds `count` cells from the goal (index 0) back to
// the start; the turning cells are gathered from the start on (a straight run keeps its last cell, a turn whose three
// cells and corner cell are all of one open kind is cut), then the band is pulled tight from `start`.
uint16_t CPFSector::FindWideSegmentWaypoint(float width, const CVector3* start, const CVector3* end,
                                            const uint8_t* path, uint16_t count, uint8_t* out) {
    const uint32_t n = count;
    if (n <= 1) return 0;
    const float inv = g_pfGridScale.m_invCellSize;
    CVector2 from;
    CVector2 to;
    if (n == 2) {
        from.m_fX = (start->x - m_box.m_inf.x) * inv;
        from.m_fY = inv * (start->z - m_box.m_inf.z);
        CVector2 goal;
        goal.m_fX = (end->x - m_box.m_inf.x) * inv;
        goal.m_fY = inv * (end->z - m_box.m_inf.z);
        if (IsWideSegmentWalkable(width, &from, &goal, 0) != 0) return 0;
        to.m_fX = static_cast<float>(path[0]) + 0.5f;
        to.m_fY = static_cast<float>(path[1]) + 0.5f;
        if (IsWideSegmentWalkable(width, &from, &to, 0) != 0) {
            out[1] = path[1];
            out[0] = path[0];
            return 1;
        }
        to.m_fX = static_cast<float>(path[2]) + 0.5f;
        to.m_fY = static_cast<float>(path[3]) + 0.5f;
        if (IsWideSegmentWalkable(width, &from, &to, 0) != 0) {
            out[1] = path[3];
            out[0] = path[2];
            return 1;
        }
        out[0] = path[2];
        out[1] = path[3];
        out[2] = path[0];
        out[3] = path[1];
        return 2;
    }
    // The turning cells, from the start (path[count - 1]) to the goal (path[0]).
    uint8_t turns[0x4e20];
    uint32_t t = 1;
    turns[1] = path[2 * (n - 1) + 1];
    turns[0] = path[2 * (n - 1)];
    bool inLine = false;
    bool cut = false;
    // n >= 3, so the index starts at n - 2 >= 1 (the original's branch for 0 is not reachable).
    for (uint32_t i = n - 2;; --i) {
        const uint8_t* const cur = path + 2 * (i & 0xffff);
        const uint8_t* const next = path + 2 * ((i + 1) & 0xffff);
        const uint32_t prevIndex = (i - 1) & 0xffff;
        const uint8_t* const prev = path + 2 * prevIndex;
        const bool straight = (next[0] == cur[0] && cur[0] == prev[0]) || (cur[1] == next[1] && cur[1] == prev[1]);
        if (straight) {
            if (((i + 1) & 0xffff) != n - 1 && !inLine && cut) {
                turns[2 * t + 1] = next[1];
                turns[2 * t] = next[0];
                ++t;
            }
            inLine = true;
        } else if (inLine) {
            turns[2 * t + 1] = cur[1];
            turns[2 * t] = cur[0];
            ++t;
            inLine = false;
            cut = false;
        } else {
            const uint8_t paletteNext = PFCellPalette(&m_grid, next[0], next[1]);
            const uint8_t paletteCur = PFCellPalette(&m_grid, cur[0], cur[1]);
            uint8_t corner[2] = {prev[0], prev[1]};
            const uint8_t palettePrev = PFCellPalette(&m_grid, corner[0], corner[1]);
            if (next[0] != cur[0]) corner[0] = next[0];
            if (next[1] != cur[1]) corner[1] = next[1];
            bool skip = false;
            if (palettePrev == paletteCur && paletteCur == paletteNext &&
                !PFPaletteBlocked(PFCellPalette(&m_grid, corner[0], corner[1]))) {
                skip = true;
            }
            if (skip) {
                cut = true;
            } else {
                turns[2 * t + 1] = cur[1];
                turns[2 * t] = cur[0];
                ++t;
                cut = false;
            }
        }
        if (prevIndex == 0) break;
    }
    turns[2 * t + 1] = path[1];
    turns[2 * t] = path[0];
    const uint32_t total = (t + 1) & 0xffff;
    const uint32_t limit = total + 2;
    // Pull the band tight: from the anchor (0 = `start`) to each next cell (total + 1 = `end`).
    uint32_t anchor = 0;
    uint32_t outCount = 0;
    bool firstLeg = true;
    for (uint32_t k = 2; (k & 0xffff) < limit; ++k) {
        const uint32_t target = k & 0xffff;
        const uint32_t prevK = k - 1;
        if ((anchor & 0xffff) == 0) {
            from.m_fX = (start->x - m_box.m_inf.x) * inv;
            from.m_fY = inv * (start->z - m_box.m_inf.z);
        } else {
            const uint8_t* const cell = turns + 2 * ((anchor & 0xffff) - 1);
            from.m_fX = static_cast<float>(cell[0]) + 0.5f;
            from.m_fY = static_cast<float>(cell[1]) + 0.5f;
        }
        const bool toEnd = total + 1 == target;
        if (toEnd) {
            to.m_fX = (end->x - m_box.m_inf.x) * inv;
            to.m_fY = inv * (end->z - m_box.m_inf.z);
        } else {
            const uint8_t* const cell = turns + 2 * (target - 1);
            to.m_fX = static_cast<float>(cell[0]) + 0.5f;
            to.m_fY = static_cast<float>(cell[1]) + 0.5f;
        }
        const uint8_t strict = (firstLeg || toEnd) ? 1 : 0;
        if (IsWideSegmentWalkable(width, &from, &to, strict) == 0) {
            const uint8_t* const cell = turns + 2 * ((prevK - 1) & 0xffff);
            out[2 * (outCount & 0xffff) + 1] = cell[1];
            out[2 * (outCount & 0xffff)] = cell[0];
            anchor = prevK;
            ++outCount;
        }
        firstLeg = false;
    }
    return static_cast<uint16_t>(outCount);
}

namespace {
// NavGrid_SetBoxBlocked's test (fcmpu, cror: NaN is outside): the point within the box on x, z, then y.
bool InSectorBox(const CBBox& box, const CVector3& p) {
    return box.m_inf.x <= p.x && box.m_sup.x >= p.x && box.m_inf.z <= p.z && box.m_sup.z >= p.z && box.m_inf.y <= p.y &&
           box.m_sup.y >= p.y;
}
}  // namespace

// 0x001ed3c0 NavGrid_SetBoxBlocked. The cell bounds: the corner's truncated cell, the last column / row when it is on the
// box's far side (the low byte equal to the size), as bytes; the cells from min to max on both axes, x outer.
uint32_t CPFSector::SetBoxBlocked(const CVector3* min, const CVector3* max, uint8_t blocked) {
    CVector3 a;
    if (InSectorBox(m_box, *min)) {
        a = *min;
    } else {
        AABB_ClampPoint(&m_box, min, &a);  // 0x0023c4b8
    }
    CVector3 b;
    if (InSectorBox(m_box, *max)) {
        const float k = 0.001f;  // TOC -0x1598: 0x3a83126f
        b.x = max->x - k;
        b.y = max->y - k;
        b.z = max->z - k;
    } else {
        AABB_ClampPoint(&m_box, max, &b);
    }
    const float inv = g_pfGridScale.m_invCellSize;  // 0x00c40264
    const uint32_t width = m_grid.m_width;
    const uint32_t height = m_grid.m_height;
    const int32_t ax = ppc::fctiwz((a.x - m_box.m_inf.x) * inv);
    const int32_t az = ppc::fctiwz((a.z - m_box.m_inf.z) * inv);
    const uint32_t x0 = ((ax & 0xff) == static_cast<int32_t>(width) ? ax - 1 : ax) & 0xffu;
    const uint32_t z0 = ((az & 0xff) == static_cast<int32_t>(height) ? az - 1 : az) & 0xffu;
    const uint32_t bx = static_cast<uint32_t>(ppc::fctiwz(inv * (b.x - m_box.m_inf.x))) & 0xffu;
    const uint32_t bz = static_cast<uint32_t>(ppc::fctiwz(inv * (b.z - m_box.m_inf.z))) & 0xffu;
    const uint32_t x1 = (bx == width ? width - 1 : bx) & 0xffu;
    const uint32_t z1 = (bz == height ? height - 1 : bz) & 0xffu;
    for (uint32_t x = x0; x <= x1; ++x) {
        for (uint32_t z = z0; z <= z1; ++z) {
            const uint8_t cell[2] = {static_cast<uint8_t>(x), static_cast<uint8_t>(z)};
            m_grid.SetCellBlocked(cell, blocked);  // 0x001f12d8
        }
    }
    return 1;
}

// 0x001ed6e0 CKPFGraphNode_FindNearestWalkableCell_maybe. A candidate replaces the one found on the same ring when
// its centre is nearer the point (not when as near); `out` still the null vector means none found yet.
uint8_t CPFSector::FindNearestWalkableCell(const CVector3* point, CVector3* out) const {
    const float inv = g_pfGridScale.m_invCellSize;
    int32_t x = ppc::fctiwz((point->x - m_box.m_inf.x) * inv);
    int32_t z = ppc::fctiwz((point->z - m_box.m_inf.z) * inv);
    if ((x & 0xff) == m_grid.m_width) x = x - 1;
    if ((z & 0xff) == m_grid.m_height) z = z - 1;
    const uint8_t cellX = static_cast<uint8_t>(x);
    const uint8_t cellZ = static_cast<uint8_t>(z);
    if (!PFPaletteBlocked(PFCellPalette(&m_grid, cellX, cellZ))) {
        CellCentre(m_box, cellX, cellZ, out);
        return 1;
    }
    *out = kNullVector;
    const int32_t x0 = cellX;
    const int32_t z0 = cellZ;
    int32_t below = z0 - 1;
    int32_t right = x0 + 1;
    int32_t above = z0 + 1;
    const int32_t width = m_grid.m_width;
    const int32_t height = m_grid.m_height;
    for (int64_t ringIndex = 0; ringIndex != 100; ++ringIndex) {
        const int32_t ring = static_cast<int32_t>(ringIndex);
        bool none = true;
        auto visit = [&](int32_t cx, int32_t cz) {
            const uint8_t bx = static_cast<uint8_t>(cx);
            const uint8_t bz = static_cast<uint8_t>(cz);
            if (PFPaletteBlocked(PFCellPalette(&m_grid, bx, bz))) return;
            if (out->x == kNullVector.x && out->y == kNullVector.y && out->z == kNullVector.z) {
                CellCentre(m_box, bx, bz, out);
                none = false;
                return;
            }
            CVector3 centre;
            CellCentre(m_box, bx, bz, &centre);
            const float cdx = centre.x - point->x;
            const float cdy = centre.y - point->y;
            const float cdz = centre.z - point->z;
            const float candidate = MathSqrtf(ppc::fmadds(cdz, cdz, ppc::fmadds(cdx, cdx, cdy * cdy)));
            const float odx = out->x - point->x;
            const float ody = out->y - point->y;
            const float odz = out->z - point->z;
            const float current = MathSqrtf(ppc::fmadds(odz, odz, ppc::fmadds(odx, odx, ody * ody)));
            if (!(candidate >= current)) *out = centre;
        };
        const int32_t zLo = z0 - ring;
        const int32_t xLo = x0 - ring - 1;
        // The row below.
        if (zLo - 1 >= 0) {
            const int32_t xHi = ring + x0 + 1;
            for (int32_t cx = xLo; cx <= xHi; ++cx) {
                if (cx < 0 || width <= cx) continue;
                visit(cx, below);
            }
        }
        // The row above.
        const int32_t zHi = ring + z0 + 1;
        if (height > zHi) {
            const int32_t xHi = x0 + ring + 1;
            for (int32_t cx = xLo; cx <= xHi; ++cx) {
                if (cx < 0 || width <= cx) continue;
                visit(cx, above);
            }
        }
        // The left column.
        if (xLo >= 0) {
            for (int32_t cz = zLo; cz < zHi; ++cz) {
                if (cz < 0 || height <= cz) continue;
                visit(xLo, cz);
            }
        }
        // The right column.
        if (width > x0 + ring + 1) {
            for (int32_t cz = zLo; cz < zHi; ++cz) {
                if (cz < 0 || height <= cz) continue;
                visit(right, cz);
            }
        }
        if (!none) {
            out->y = point->y;
            return 1;
        }
        --below;
        ++right;
        ++above;
    }
    return 0;
}

// 0x001ee190 NavSector_ClampPointWithClearance_maybe. The point is first clamped into its open cell shrunk by 0.001;
// then, in cell units around that cell, `dx` / `dz` (-1, 0, 1) say on which side the point is nearer than the
// clearance (half a cell less the radius): a closed (or missing) side cell pushes the point back to the clearance line,
// and with both sides open a closed diagonal cell keeps it `radius` (+ 0.001) away from the shared corner.
uint8_t CPFSector::ClampPointWithClearance(float radius, const CVector3* point, CVector3* out) const {
    CVector3 centre;
    if (FindNearestWalkableCell(point, &centre) == 0) return 0;
    const float half = g_pfGridScale.m_halfCellSize;
    const float eps = 0.001f;  // 0x3a83126f
    // Into the cell (less 0.001 on each side).
    float x;
    {
        const float lo = (centre.x - half) + eps;
        const float hi = (centre.x + half) - eps;
        if (lo <= point->x) {
            const float v = point->x;
            x = v > hi ? hi : v;
        } else {
            x = lo <= hi ? lo : hi;
        }
    }
    out->x = x;
    out->y = centre.y;
    float z;
    {
        const float lo = (centre.z - half) + eps;
        const float hi = (centre.z + half) - eps;
        if (lo <= point->z) {
            const float v = point->z;
            z = v > hi ? hi : v;
        } else {
            z = lo <= hi ? lo : hi;
        }
    }
    out->z = z;
    const float inv = g_pfGridScale.m_invCellSize;
    const float clearance = half - radius;
    const float cellFx = (centre.x - m_box.m_inf.x) * inv;
    const float cellFz = (centre.z - m_box.m_inf.z) * inv;
    const float zLoTmp = centre.z - clearance;
    const float xHiTmp = clearance + centre.x;
    const float xLoTmp = centre.x - clearance;
    const float zHiTmp = clearance + centre.z;
    const float zLo = zLoTmp + eps;
    const int32_t cellXi = ppc::fctiwz(cellFx);
    const int32_t cellZi = ppc::fctiwz(cellFz);
    const float xHi = xHiTmp - eps;
    const float xLo = xLoTmp + eps;
    const float zHi = zHiTmp - eps;
    const int32_t width = m_grid.m_width;
    const int32_t height = m_grid.m_height;
    int32_t cx = cellXi & 0xff;
    if (cx == width) cx = (cellXi - 1) & 0xff;
    int32_t cz = cellZi & 0xff;
    if (cz == height) cz = (cellZi - 1) & 0xff;
    int32_t dx;
    int32_t dz;
    if (xLo > x) {
        dx = -1;
    } else {
        dx = xHi >= x ? 0 : 1;
    }
    if (z < zLo) {
        dz = -1;
    } else {
        dz = z <= zHi ? 0 : 1;
    }
    auto open = [&](int32_t px, int32_t pz) {
        return !PFPaletteBlocked(PFCellPalette(&m_grid, static_cast<uint8_t>(px), static_cast<uint8_t>(pz)));
    };
    auto clampX = [&]() {
        out->x = dx == 1 ? xHi : xLo;
        return uint8_t{1};
    };
    auto clampZ = [&]() {
        out->z = dz == 1 ? zHi : zLo;
        return uint8_t{1};
    };
    if (dx == 0) {
        if (dz == 0) return 1;
        const int32_t sz = dz + cz;
        if (cx >= 0 && sz >= 0 && width > cx && height > sz && open(cx, sz)) return 1;
        return clampZ();
    }
    if (dz == 0) {
        const int32_t sx = dx + cx;
        if (sx >= 0 && cz >= 0 && width > sx && height > cz && open(sx, cz)) return 1;
        return clampX();
    }
    // Both: the side cell along x, then along z, then the diagonal.
    const int32_t sx = dx + cx;
    bool movedX;
    if (sx >= 0 && cz >= 0 && width > sx && height > cz && open(sx, cz)) {
        movedX = false;
    } else {
        out->x = dx == 1 ? xHi : xLo;
        movedX = true;
    }
    const int32_t sz = dz + cz;
    if (cx < 0 || sz < 0 || width <= cx || height <= sz || !open(cx, sz)) return clampZ();
    if (movedX) return 1;
    if (sx >= 0 && width > sx && height > sz && open(sx, sz)) return 1;
    // The diagonal cell is closed (or outside): the cell of the clamped point.
    const float ox = out->x;
    const float oz = out->z;
    int32_t pxi = ppc::fctiwz((ox - m_box.m_inf.x) * inv);
    int32_t pzi = ppc::fctiwz((oz - m_box.m_inf.z) * inv);
    int32_t px = pxi & 0xff;
    if (px == width) px = (pxi - 1) & 0xff;
    int32_t pzRaw = pzi;
    if ((pzi & 0xff) == height) pzRaw = pzi - 1;
    const int32_t pz = pzRaw & 0xff;
    if (cx == px && cz == pz) {
        // Still in the cell: keep the radius from the corner shared with the diagonal cell.
        const float cornerX = ppc::fmadds(static_cast<float>(dx), half, centre.x);
        const float cornerZ = ppc::fmadds(half, static_cast<float>(dz), centre.z);
        const float zero = 0.0f;
        const float ddx = point->x - cornerX;
        const float ddz = point->z - cornerZ;
        const float distance = MathSqrtf(ppc::fmadds(ddz, ddz, ppc::fmadds(ddx, ddx, zero)));
        if (distance == zero || distance <= zero) return clampX();
        const float reach = radius + eps;
        if (distance >= reach) {
            *out = *point;
            return 1;
        }
        const float scale = 1.0f / distance;
        const float ux = ddx * scale;
        const float uz = ddz * scale;
        const float uy = scale * zero;
        out->z = ppc::fmadds(reach, uz, cornerZ);
        out->x = ppc::fmadds(reach, ux, cornerX);
        out->y = ppc::fmadds(reach, uy, centre.y);
        return 1;
    }
    // Moved out of the cell: undo the smaller push.
    const float pushX = dx == 1 ? ox - xHi : xLo - ox;
    const float pushZ = dz == 1 ? oz - zHi : zLo - oz;
    if (!(pushX <= pushZ)) return clampZ();
    return clampX();
}

// 0x001efc58 CKPFGraphNode_Construct (also inlined in 0x001f0248 CKPFGraphNode_Create).
CKPFGraphNode::CKPFGraphNode() {
    m_ppTransition = nullptr;
    m_lpIncludedNode = nullptr;
}

// 0x001effa8 CKPFGraphNode_Load
int32_t CKPFGraphNode::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_Sector.Load(file, K_LEVEL_PLATEFORMS);
    uint32_t count = 0;
    ReadU32LE(file, &count);  // a word; its low half is the transition count
    m_ppTransition = nullptr;  // the original stores the type (0) here
    m_ui16TransitionSize = static_cast<uint16_t>(count);
    if (m_ui16TransitionSize != 0) {
        m_ppTransition = static_cast<CKPFGraphTransition**>(
            Mem_AllocAligned16(m_ui16TransitionSize * static_cast<uint32_t>(sizeof(CKPFGraphTransition*))));
        if (m_ui16TransitionSize != 0) {
            IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_ppTransition), m_ui16TransitionSize);
        }
    }
    uint32_t included = 0;
    ReadU32LE(file, &included);
    for (uint32_t i = 0; i < included; ++i) {
        IKSerializable* node = nullptr;
        IKFile_ReadRef(file, &node);
        IncludedNode* entry = new IncludedNode();  // a FreeListPool node in the original
        entry->m_pNext = nullptr;
        entry->m_pNode = node;
        entry->m_pNext = m_lpIncludedNode;
        m_lpIncludedNode = entry;
    }
    return 1;
}

// 0x001efe18 NavSectors_FindBoxIdAtPoint_maybe
uint16_t CKPFGraphNode::FindBoxIdAtPoint(const float* point) const {
    uint16_t id = m_ui16Node;
    const IncludedNode* entry = m_lpIncludedNode;
    if (entry == nullptr) return id;
    const float y = point[1];
    const CKPFGraphNode* node = static_cast<const CKPFGraphNode*>(entry->m_pNode);
    if (node->m_Sector.m_box.m_inf.y > y) return id;
    do {
        const CBBox& box = node->m_Sector.m_box;
        if (box.m_inf.x <= point[0] && box.m_sup.x >= point[0] && box.m_inf.z <= point[2] && box.m_sup.z >= point[2] &&
            box.m_inf.y <= y && box.m_sup.y >= y) {
            id = node->m_ui16Node;
        }
        entry = entry->m_pNext;
    } while (entry != nullptr &&
             (node = static_cast<const CKPFGraphNode*>(entry->m_pNode))->m_Sector.m_box.m_inf.y <= y);
    return id;
}

// 0x001efda0 CKPFGraphNode_FindTransitionIndexTo_maybe
int32_t CKPFGraphNode::FindTransitionIndexTo(const IKSerializable* node) const {
    for (uint32_t i = 0; i < m_ui16TransitionSize; ++i) {
        if (m_ppTransition[i]->m_pNode == node) return static_cast<int32_t>(i);
    }
    return -1;
}

#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x001ebf00 CKPFGraphNode_SaveBoundsAndCells_maybe (each float through stwbrx and a 4-byte write, vt+0x20)
int32_t CPFSector::Save(IKFile* file, int32_t /*type*/) {
    const float values[6] = {m_box.m_inf.x, m_box.m_inf.y, m_box.m_inf.z, m_box.m_sup.x, m_box.m_sup.y, m_box.m_sup.z};
    for (float value : values) {
        uint32_t bits;
        std::memcpy(&bits, &value, sizeof bits);
        WriteU32LE(file, bits);
    }
    return 1;  // the grid's save: KStub_Return1_1f0fd8
}

// 0x001eff00 CKPFGraphNode_Destroy
void CKPFGraphNode::Destroy() {
    IncludedNode* entry = m_lpIncludedNode;
    while (entry != nullptr) {
        IncludedNode* next = entry->m_pNext;
        delete entry;  // FreeListPool 0x00ceaa30 in the original
        entry = next;
    }
    m_lpIncludedNode = nullptr;
    if (m_ppTransition != nullptr) {
        Mem_FreeAligned16(m_ppTransition);
        m_ppTransition = nullptr;
    }
    m_Sector.FreeCells();
}

// 0x001efb60 CKPFGraphNode_RecursiveRegistration
void CKPFGraphNode::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}
