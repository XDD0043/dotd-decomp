// NavGrid.cpp - reconstructed original translation unit 0x1f0f10-0x1f14a0 (GAME_TOC1, main_toc1), 14 functions, 11 live.
// Primary owner: NavGrid (not a registered class)
// Other owners: CKPFGraphNode (2), PathFinding (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1f0f10  NavGrid_InitCellClassTable_maybe  [dead]
//   [ ] 0x1f0f70  NavGrid_SetCellValue_maybe  [dead]
//   [x] 0x1f0fd8  KStub_Return1_1f0fd8  (CPFGrid::Save in NavGrid.h (its caller is the save path))
//   [x] 0x1f0fe0  CKPFGraphNode_GetCellFlags_maybe  (CPFGrid::GetCellFlags)
//   [x] 0x1f1028  StaticInitAndDestruction_1f1028  (empty: the unit's static initialiser has nothing to construct)
//   [ ] 0x1f1030  _GLOBAL__I_1f1030
//   [ ] 0x1f1040  _GLOBAL__D_1f1040
//   [x] 0x1f1050  NavGrid_AllocCells_maybe  (CPFGrid::AllocCells; no caller in the original either)
//   [x] 0x1f1110  NavGrid_FreeCells_maybe  (inline in NavGrid.h; C2.8 port-all P02)
//   [x] 0x1f1158  PathFinding_SetWalkabilityMode_maybe  (PathFinding_SetWalkabilityMode)
//   [x] 0x1f11c8  CKPFGraphNode_LoadCells
//   [x] 0x1f12d8  NavGrid_SetCellBlocked
//   [x] 0x1f1370  NavGrid_Construct_maybe
//   [ ] 0x1f1408  NavGrid_Construct_2_maybe  [dead]
#include "k2000/misc/NavGrid.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

#include <cstring>

uint8_t g_pfGridPaletteUninitialised = 1;
uint8_t g_pfGridPalette[16];

// 0x001f11c8 CKPFGraphNode_LoadCells
int32_t CPFGrid::Load(IKFile* file) {
    ReadU8(file, &m_width);
    ReadU8(file, &m_height);
    uint32_t cells = static_cast<uint32_t>(m_width) * m_height;
    // Two cells per byte, rounded up; the allocation size is truncated to 16 bits (rldicl), the read is not.
    m_grid = static_cast<uint8_t*>(Mem_AllocAligned16(((cells & 1) + (cells >> 1)) & 0xffffu));
    cells = static_cast<uint32_t>(m_width) * m_height;
    ReadRaw(file, m_grid, (cells & 1) + (cells >> 1));
    return 1;
}

// 0x001f1050 NavGrid_AllocCells_maybe (the half count an arithmetic shift of the signed product)
void CPFGrid::AllocCells(uint32_t width, uint32_t height) {
    const int32_t half = static_cast<int32_t>(height * width) >> 1;
    m_width = static_cast<uint8_t>(width);
    m_height = static_cast<uint8_t>(height);
    const uint32_t size = static_cast<uint32_t>(half + 1);
    if (m_grid != nullptr) {
        m_grid = static_cast<uint8_t*>(Mem_ReallocAligned16(m_grid, size));
    } else {
        m_grid = static_cast<uint8_t*>(Mem_AllocAligned16(size));
    }
    std::memset(m_grid, 0x77, size);
}

// 0x001f1370 NavGrid_Construct_maybe
CPFGrid::CPFGrid() {
    m_grid = nullptr;
    m_width = 0;
    m_height = 0;
    if (g_pfGridPaletteUninitialised != 0) {  // XXL2 CPFGrid::InitializePalette, in the original's store order
        g_pfGridPaletteUninitialised = 0;
        g_pfGridPalette[2] = 2;
        g_pfGridPalette[3] = 3;
        g_pfGridPalette[0xf] = 0xff;
        g_pfGridPalette[6] = 6;
        g_pfGridPalette[7] = 0x7f;
        g_pfGridPalette[5] = 1;
        g_pfGridPalette[0] = 1;
        g_pfGridPalette[1] = 1;
        g_pfGridPalette[4] = 1;
        for (int i = 8; i <= 0xe; ++i) g_pfGridPalette[i] = 0xff;
    }
    m_ui8DynamicMask = 0xff;
}

// 0x001f0fe0 CKPFGraphNode_GetCellFlags_maybe
uint8_t CPFGrid::GetCellFlags(const uint8_t* cell) const {
    const uint64_t index = static_cast<uint64_t>(cell[0]) + static_cast<uint64_t>(cell[1]) * m_width;
    const uint8_t packed = m_grid[(index >> 1) & 0x7fff];
    const uint8_t nibble = (index & 1) != 0 ? packed : static_cast<uint8_t>(packed >> 4);
    return static_cast<uint8_t>((nibble & 0xf) & m_ui8DynamicMask);
}

// 0x001f12d8 NavGrid_SetCellBlocked. The value 0x7f is turned into 7 as in the original (a 4-bit value never is 0x7f).
void CPFGrid::SetCellBlocked(const uint8_t* cell, int32_t blocked) {
    const uint64_t index = static_cast<uint64_t>(cell[0]) + static_cast<uint64_t>(cell[1]) * m_width;
    uint8_t* const byte = &m_grid[(index >> 1) & 0x7fff];
    const uint8_t packed = *byte;
    const bool odd = (index & 1) != 0;
    const uint32_t flags = static_cast<uint32_t>(odd ? packed & 0xf : packed >> 4) & m_ui8DynamicMask;
    uint32_t value = blocked != 0 ? (flags | 8) : (flags & 7);
    if ((value & 0xff) == 0x7f) value = 7;
    if (odd) {
        *byte = static_cast<uint8_t>((packed & 0xf0) | value);
    } else {
        *byte = static_cast<uint8_t>((packed & 0x0f) | (value << 4));
    }
}

// 0x001f1158 PathFinding_SetWalkabilityMode_maybe
void PathFinding_SetWalkabilityMode(uint32_t mode) {
    if (mode == 1) {
        g_pfGridPalette[5] = 0x7f;
        g_pfGridPalette[4] = 1;
        g_pfGridPalette[0] = 0x7f;
    } else if (mode == 2) {
        g_pfGridPalette[5] = 0x7f;
        g_pfGridPalette[0] = 1;
        g_pfGridPalette[4] = 0x7f;
    } else if (mode == 4) {
        g_pfGridPalette[5] = 1;
        g_pfGridPalette[4] = 0x7f;
        g_pfGridPalette[0] = 1;
    }
}
