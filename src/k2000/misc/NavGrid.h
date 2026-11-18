// NavGrid.h - the path-finding cell grid of a graph node's sector (XXL2 CPFGrid: m_grid, m_width,
// m_height, m_ui8DynamicMask and the static palette m_aPalette[16]; vtable 0xb1e6c8, 0xc bytes on the PS3).
// Original unit: NavGrid.cpp (0x1f0f10-...).
#pragma once
#include <cstdint>

#include "k2000/memory/Mem.h"

#include "k2000/core/Layout.h"

class IKFile;

class CPFGrid {
public:
    CPFGrid();  // 0x001f1370 NavGrid_Construct_maybe (XXL2 CPFGrid::CPFGrid, with InitializePalette inlined)
    virtual ~CPFGrid() {}

    // 0x001f11c8 CKPFGraphNode_LoadCells (XXL2 CPFGrid::Load _maybe): the size, then the cells (4 bits each).
    int32_t Load(IKFile* file);

    // 0x001f0fe0 CKPFGraphNode_GetCellFlags_maybe: the 4-bit flags of the cell (cell[0], cell[1]) (x, z),
    // masked with m_ui8DynamicMask; the cell index is x + z * width, two cells per byte (even index: high
    // nibble).
    uint8_t GetCellFlags(const uint8_t* cell) const;
    // 0x001f12d8 NavGrid_SetCellBlocked (XXL2 CPFSector::SetDynamicObstacle's cell write): the cell's 4-bit flags
    // (masked with m_ui8DynamicMask, as GetCellFlags reads them) get bit 3 (the dynamic obstacle) set when `blocked`
    // is not 0, else only their low three bits are kept; the other nibble of the byte is kept.
    void SetCellBlocked(const uint8_t* cell, int32_t blocked);
    // 0x001f1050 NavGrid_AllocCells_maybe: the size set and a block of (width * height) / 2 + 1 bytes (reallocated when
    // there was one) filled with 0x77. No caller.
    void AllocCells(uint32_t width, uint32_t height);
    // 0x001f0fd8 KStub_Return1_1f0fd8: the grid's save (CKPFGraphNode_SaveBoundsAndCells_maybe calls it): 1.
    int32_t Save(IKFile* /*file*/) { return 1; }
    // 0x001f1110 NavGrid_FreeCells_maybe: the cell block freed and forgotten.
    void FreeCells() {
        if (m_grid != nullptr) {
            Mem_FreeAligned16(m_grid);
            m_grid = nullptr;
        }
    }
    uint8_t* m_grid;          // +0x04 XXL2 m_grid (Mem_AllocAligned16)
    uint8_t m_width;           // +0x08 XXL2 m_width
    uint8_t m_height;          // +0x09 XXL2 m_height
    uint8_t m_ui8DynamicMask;  // +0x0a XXL2 m_ui8DynamicMask; the constructor sets 0xff
    uint8_t m_pad0b;
};
DOTD_ASSERT_SIZE(CPFGrid, 0xc);
DOTD_ASSERT_OFFSET(CPFGrid, m_grid, 0x04);
DOTD_ASSERT_OFFSET(CPFGrid, m_width, 0x08);
DOTD_ASSERT_OFFSET(CPFGrid, m_ui8DynamicMask, 0x0a);

// 0x00cea90b XXL2 CPFGrid::m_aPalette (16 bytes here) and 0x00c40268 its "not yet initialised" flag
// (1 in the EBOOT data): the first CPFGrid built fills it.
extern uint8_t g_pfGridPaletteUninitialised;
extern uint8_t g_pfGridPalette[16];

// 0x001f1158 PathFinding_SetWalkabilityMode_maybe: the palette entries 0, 4 and 5 (0x00cea90b, 0x00cea90f,
// 0x00cea910) for a walkability mode: 1 = (0x7f, 1, 0x7f), 2 = (1, 0x7f, 0x7f), 4 = (1, 0x7f, 1); any other
// mode changes nothing. A palette value with its low seven bits set is a blocked cell.
void PathFinding_SetWalkabilityMode(uint32_t mode);

// The original's blocked-cell test on a palette value (inlined everywhere): the value with its low seven bits set is
// the value itself (0x7f or 0xff), or the value is 0x7f.
inline bool PFPaletteBlocked(uint8_t palette) {
    return static_cast<uint8_t>(palette | 0x7f) == palette || palette == 0x7f;
}
// The palette value of a cell of `grid` (g_pfGridPalette[GetCellFlags]).
inline uint8_t PFCellPalette(const CPFGrid* grid, uint8_t x, uint8_t z) {
    const uint8_t cell[2] = {x, z};
    return g_pfGridPalette[grid->GetCellFlags(cell)];
}
