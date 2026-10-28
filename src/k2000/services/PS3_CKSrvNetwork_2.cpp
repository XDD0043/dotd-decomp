// PS3_CKSrvNetwork_2.cpp - reconstructed original translation unit 0x1e0a70-0x1e1080 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary class: PS3_CKSrvNetwork  key 0x601  category Service  size 0x2c  vtable 0xb1e2e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1e0a70  PS3_CKSrvNetwork_Construct
//   [ ] 0x1e0b28  PS3_CKSrvNetwork_Construct_2
//   [x] 0x1e0be0  PS3_CKSrvNetwork_DeleteArray
//   [ ] 0x1e0c80  PS3_CKSrvNetwork_Destructor_2
//   [x] 0x1e0d28  PS3_CKSrvNetwork_CreateArray
//   [x] 0x1e0e68  PS3_CKSrvNetwork_Create
//   [ ] 0x1e0f28  PS3_CKSrvNetwork_DeletingDestructor
//   [ ] 0x1e0fd8  PS3_CKSrvNetwork_Destructor
//
//   [ ] 0x9addf8  KBase601_DeletingDestructor  [inline]
//   [ ] 0x9adeb0  KBase601_Destructor  [inline]
#include "k2000/services/PS3_CKSrvNetwork.h"

#include "k2000/misc/Engine.h"

// 0x001e0a70 PS3_CKSrvNetwork_Construct (the same stores inlined in 0x1e0e68 PS3_CKSrvNetwork_Create):
// the IKService part, the unkeyed base's two vectors, then the priority and the engine slot.
PS3_CKSrvNetwork::PS3_CKSrvNetwork() {
    m_unk0c.m_ui32NbElt = 1;
    m_unk0c.m_pBlock = nullptr;
    m_unk0c.m_ui32NbUsedElt = 0;
    m_unk18.m_ui32NbElt = 1;
    m_unk18.m_ui32NbUsedElt = 0;
    m_unk18.m_pBlock = nullptr;
    m_ui32Priority = 0x32;
    Engine_SetSrvNetwork(this);
}
