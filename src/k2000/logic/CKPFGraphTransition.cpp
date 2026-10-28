// CKPFGraphTransition.cpp - reconstructed original translation unit 0x1ea0a8-0x1ea3e0 (GAME_TOC1, main_toc1), 3 functions, 2 live.
// Primary class: CKPFGraphTransition  key 0x8c  category Logic  size 0x24  vtable 0xb1e670
// Other owners: PFGraphTransitionDoor (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1ea0a8  CKPFGraphTransition_Door_Init_2  [dead]
//   [x] 0x1ea138  CKPFGraphTransition_Door_Init
//   [x] 0x1ea1c8  PFGraphTransitionDoor_Load_maybe
#include "k2000/logic/CKPFGraphTransition.h"

#include "k2000/io/IKFile.h"

// 0x001ea138 CKPFGraphTransition_Door_Init: empty boxes (m_inf = FLT_MAX, m_sup = -FLT_MAX; FLT_MAX from
// 0x00c4ace0) and the flags, in the original's store order.
CPFPortal::CPFPortal() {
    const float big = 0x1.fffffep+127f;  // FLT_MAX
    m_DepartureBox.m_inf.x = big;
    m_DepartureBox.m_inf.z = big;
    m_DepartureBox.m_inf.y = big;
    m_DepartureBox.m_sup.x = -big;
    m_DepartureBox.m_sup.z = -big;
    m_DepartureBox.m_sup.y = -big;
    m_ArrivalBox.m_inf.x = big;
    m_ArrivalBox.m_inf.z = big;
    m_ArrivalBox.m_inf.y = big;
    m_ArrivalBox.m_sup.x = -big;
    m_ArrivalBox.m_sup.z = -big;
    m_ArrivalBox.m_sup.y = -big;
    // 0, then the low byte set to 0x80 and the top two bits cleared (rlwinm pair): 0x80.
    m_baTypesAndFlags = 0;
    m_baTypesAndFlags = ((m_baTypesAndFlags & 0xffffff00u) | 0x80u) & 0x3fffffffu;
}

// 0x001ea1c8 PFGraphTransitionDoor_Load_maybe: each vector one 12-byte read, then its words swapped;
// m_inf before m_sup.
int32_t CPFPortal::Load(IKFile* file, int32_t /*type*/) {
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_DepartureBox.m_inf), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_DepartureBox.m_sup), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_ArrivalBox.m_inf), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_ArrivalBox.m_sup), 3);
    ReadU32LE(file, &m_baTypesAndFlags);
    return 1;
}
