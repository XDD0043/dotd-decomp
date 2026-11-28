// CKAnimatedFxCollection.cpp - reconstructed original translation unit 0x5cc298-0x5cdee0 (GAME_TOC2, main_toc2), 25 functions, 20 live.
// Primary class: CKAnimatedFxCollection  key 0xa08c  category Logic  size ?  vtable 0xb30128
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5cc298  CKAnimatedFxCollection_Delete
//   [ ] 0x5cc2e8  CKAnimatedFxCollection_Construct  [dead]
//   [ ] 0x5cc330  CKAnimatedFxCollection_GetEntryPtr_maybe  [dead]
//   [ ] 0x5cc378  CKAnimatedFxCollection_Construct_2  [dead]
//   [ ] 0x5cc3c0  RegisterCKAnimatedFxCollectionClass
//   [ ] 0x5cc438  _GLOBAL__I_5cc438
//   [ ] 0x5cc448  CKAnimatedFxCollection_InitActiveFlagArray_maybe  [dead]
//   [x] 0x5cc528  CKAnimatedFxCollection_Play
//   [x] 0x5cc750  CKAnimatedFxCollection_DeleteArray
//   [x] 0x5cc7f0  CKAnimatedFxCollection_SetOrientation_maybe
//   [x] 0x5cc8c8  CKAnimatedFxCollection_SetPosition
//   [x] 0x5cc990  CKAnimatedFxCollection_Stop
//   [ ] 0x5cca80  CKAnimatedFxCollection_SetBasisFromRightUp_maybe  [dead]
//   [x] 0x5ccb58  CKAnimatedFxCollection_RecursiveRegistration  (returns 1: the default slot)
//   [x] 0x5ccb60  CKAnimatedFxCollection_Destroy  (empty: the default slot)
//   [x] 0x5ccb68  CKAnimatedFxCollection_Create
//   [x] 0x5ccbd8  CKAnimatedFxCollection_CreateArray
//   [x] 0x5cccb0  CKAnimatedFxCollection_Update_maybe
//   [x] 0x5ccf58  CKAnimatedFxCollection_PostLoad
//   [x] 0x5cd0a8  CKAnimatedFxCollection_PlayWithOwnRigs_maybe
//   [x] 0x5cd2d0  CKAnimatedFxCollection_Destructor  (~CKAnimatedFxCollection, CKAnimatedFxCollection.h)
//   [x] 0x5cd388  CKAnimatedFxCollection_Destructor_2  (~CKAnimatedFxCollection (a second copy))
//   [x] 0x5cd440  CKAnimatedFxCollection_DeletingDestructor  (the destructor; delete)
//   [x] 0x5cd510  CKAnimatedFxCollection_Load
//   [ ] 0x5cda30  CKAnimatedFxCollection_Save
//
//   [x] 0x9cd648  CKAnimatedFxCollection_GetClassType  [inline]
//   [x] 0x9cd650  CKAnimatedFxCollection_GetClassID  [inline]
//   [ ] 0x9cd658  CKAnimatedFxCollection_IsKindOfClass  [inline]
#include "k2000/logic/fx/CKAnimatedFxCollection.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/scenegraph/CSGLeaf.h"

// 0x005ccb68 CKAnimatedFxCollection_Create, the inlined constructor, in its store order.
CKAnimatedFxCollection::CKAnimatedFxCollection() {
    m_unk0c.m_pBlock = nullptr;
    m_unk0c.m_ui32NbElt = 1;
    m_unk0c.m_ui32NbUsedElt = 0;
    m_vOwnRigs.m_ui32NbElt = 1;
    m_vOwnRigs.m_pBlock = nullptr;
    m_vOwnRigs.m_ui32NbUsedElt = 0;
    m_abActive.m_ui32NbElt = 1;
    m_abActive.m_ui32NbUsedElt = 0;
    m_abActive.m_pBlock = nullptr;
}

// 0x005cd510 CKAnimatedFxCollection_Load
int32_t CKAnimatedFxCollection::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_pRigs = nullptr;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        // The length is left as it was.
        m_unk0c.m_ui32NbElt = 1;
        m_unk0c.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        m_unk0c.m_ui32NbElt = count;
        m_unk0c.m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        if (m_unk0c.m_ui32NbElt < count) {  // never true: the capacity was just set to count
            uint32_t capacity = count + 1;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(IKSerializable*));
            if (capacity == 0) {
                capacity = 1;
                bytes = static_cast<uint32_t>(sizeof(IKSerializable*));
            }
            m_unk0c.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(m_unk0c.m_pBlock, bytes));
            m_unk0c.m_ui32NbElt = capacity;
        }
        m_unk0c.m_ui32NbUsedElt = count;
    }
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_unk0c.m_pBlock[i]);
    ReadU32LE(file, &m_ui32NbOwnRigs);
    ReadU8(file, &m_bLoop);
    ReadU8(file, &m_bHasOwnRigs);
    if (m_bHasOwnRigs != 0) {
        m_vOwnRigs.m_ui32NbElt = 1;
        m_vOwnRigs.m_pBlock = static_cast<Entry*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry))));
        const uint32_t n = m_ui32NbOwnRigs;
        if (m_vOwnRigs.m_ui32NbElt < n) {
            uint32_t capacity = n + 1;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(Entry));
            if (capacity == 0) {
                capacity = 1;
                bytes = static_cast<uint32_t>(sizeof(Entry));
            }
            m_vOwnRigs.m_pBlock = static_cast<Entry*>(Mem_ReallocAligned16(m_vOwnRigs.m_pBlock, bytes));
            m_vOwnRigs.m_ui32NbElt = capacity;
        }
        m_vOwnRigs.m_ui32NbUsedElt = n;
        for (uint32_t i = 0; i < m_ui32NbOwnRigs; ++i) {
            Entry& e = m_vOwnRigs.m_pBlock[i];
            IKFile_ReadRef(file, &e.m_unk00);
            IKFile_ReadRef(file, &e.m_unk04);
            IKFile_ReadRef(file, &e.m_unk08);
            IKFile_ReadRef(file, &e.m_unk0c);
        }
    }
    return 1;
}

// 0x005ccf58 CKAnimatedFxCollection_PostLoad
int32_t CKAnimatedFxCollection::PostLoad(int32_t /*type*/) {
    m_bPlaying = 0;
    m_abActive.m_ui32NbElt = 1;
    m_abActive.m_pBlock = static_cast<uint8_t*>(Mem_AllocAligned16(1));
    const uint32_t count = m_unk0c.m_ui32NbUsedElt;
    if (m_abActive.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_abActive.m_pBlock = static_cast<uint8_t*>(Mem_ReallocAligned16(m_abActive.m_pBlock, capacity));
        m_abActive.m_ui32NbElt = capacity;
    }
    m_abActive.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < m_abActive.m_ui32NbUsedElt; ++i) m_abActive.m_pBlock[i] = 0;
    m_pOwner = nullptr;
    for (uint32_t i = 0; i < m_vOwnRigs.m_ui32NbUsedElt; ++i) {
        CSGLeaf* node = static_cast<CSGLeaf*>(m_vOwnRigs.m_pBlock[i].m_unk00);
        if (node != nullptr) node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;  // the rig hidden
    }
    return 1;
}

namespace {
CKAnimatedFx* FxAt(const TVector<IKSerializable*, 1>& fx, uint32_t i) { return static_cast<CKAnimatedFx*>(fx.m_pBlock[i]); }
}  // namespace

// The rig of effect `i`: the own rig with +0x24 (null past the own rigs), else the i-th of the rigs Play got.
SAnimatedFxRig* CKAnimatedFxCollection::RigOf(uint32_t i) {
    if (m_bHasOwnRigs == 0) return &m_pRigs[i];
    if (i < m_vOwnRigs.m_ui32NbUsedElt) return reinterpret_cast<SAnimatedFxRig*>(&m_vOwnRigs.m_pBlock[i]);
    return nullptr;
}

// 0x005cc528 CKAnimatedFxCollection_Play
int32_t CKAnimatedFxCollection::Play(CSGLeaf* owner, SAnimatedFxRig* rigs, CSGHotSpot* attach) {
    if (owner == nullptr) return 0;
    m_pOwner = owner;
    m_pAttach = attach;
    if (rigs == nullptr && m_bHasOwnRigs == 0) return 0;
    m_pRigs = rigs;
    if (m_bPlaying != 0) return 0;
    int32_t any = 0;
    for (uint32_t i = 0; i < m_unk0c.m_ui32NbUsedElt; ++i) {
        if (m_abActive.m_pBlock[i] != 0) continue;
        m_abActive.m_pBlock[i] = static_cast<uint8_t>(FxAt(m_unk0c, i)->Play(m_pOwner, RigOf(i), m_pAttach));
        if (any == 0 && m_abActive.m_pBlock[i] != 0) any = 1;
    }
    m_bPlaying = static_cast<uint8_t>(any);
    return any;
}

// 0x005cd0a8 CKAnimatedFxCollection_PlayWithOwnRigs_maybe
int32_t CKAnimatedFxCollection::PlayWithOwnRigs(CSGLeaf* owner, CSGHotSpot* attach) {
    if (m_bHasOwnRigs == 0) return 0;
    if (owner == nullptr) return 0;
    m_pOwner = owner;
    m_pAttach = attach;
    m_pRigs = nullptr;
    if (m_bPlaying != 0) return 0;
    int32_t any = 0;
    for (uint32_t i = 0; i < m_unk0c.m_ui32NbUsedElt; ++i) {
        if (m_abActive.m_pBlock[i] != 0) continue;
        m_abActive.m_pBlock[i] = static_cast<uint8_t>(FxAt(m_unk0c, i)->Play(m_pOwner, RigOf(i), m_pAttach));
        if (any == 0 && m_abActive.m_pBlock[i] != 0) any = 1;
    }
    m_bPlaying = static_cast<uint8_t>(any);
    return any;
}

// 0x005cc990 CKAnimatedFxCollection_Stop
void CKAnimatedFxCollection::Stop() {
    if (m_bPlaying == 0) return;
    for (uint32_t i = 0; i < m_unk0c.m_ui32NbUsedElt; ++i) {
        if (m_abActive.m_pBlock[i] == 0) continue;
        FxAt(m_unk0c, i)->Stop();
        m_abActive.m_pBlock[i] = 0;
    }
    m_bPlaying = 0;
}

// 0x005cc7f0 CKAnimatedFxCollection_SetOrientation_maybe
void CKAnimatedFxCollection::SetOrientation(const CVector3* at, const CVector3* up) {
    if (m_bPlaying == 0) return;
    for (uint32_t i = 0; i < m_unk0c.m_ui32NbUsedElt; ++i) {
        if (m_abActive.m_pBlock[i] == 0) continue;
        FxAt(m_unk0c, i)->SetOrientation(at, up);  // 0x005ca2d8
    }
}

// 0x005cc8c8 CKAnimatedFxCollection_SetPosition
void CKAnimatedFxCollection::SetPosition(const CVector3* position) {
    if (m_bPlaying == 0) return;
    for (uint32_t i = 0; i < m_unk0c.m_ui32NbUsedElt; ++i) {
        if (m_abActive.m_pBlock[i] == 0) continue;
        FxAt(m_unk0c, i)->SetPosition(position);  // 0x005ca340
    }
}

// 0x005cccb0 CKAnimatedFxCollection_Update_maybe
uint8_t CKAnimatedFxCollection::Update(float dt) {
    if (m_bPlaying == 0) return 0;
    uint32_t count = m_unk0c.m_ui32NbUsedElt;
    if (count != 0) {
        bool any = false;
        for (uint32_t i = 0; i < m_unk0c.m_ui32NbUsedElt; ++i) {
            if (m_abActive.m_pBlock[i] == 0) continue;
            m_abActive.m_pBlock[i] = static_cast<uint8_t>(FxAt(m_unk0c, i)->Update(dt));
            if (!any && m_abActive.m_pBlock[i] != 0) any = true;
        }
        count = m_unk0c.m_ui32NbUsedElt;
        if (any) {
            m_bPlaying = 1;
            return 1;
        }
    }
    if (m_bLoop == 0) {
        m_bPlaying = 0;
        return 0;
    }
    if (count == 0) {
        m_bPlaying = 0;
        return m_bLoop;
    }
    // Looping collection (+0x04): every effect plays again on its rig.
    uint8_t first = 0;
    for (uint32_t i = 0; i < m_unk0c.m_ui32NbUsedElt; ++i) {
        m_abActive.m_pBlock[i] = static_cast<uint8_t>(FxAt(m_unk0c, i)->Play(m_pOwner, RigOf(i), m_pAttach));
        if (first == 0) first = m_abActive.m_pBlock[i];
    }
    m_bPlaying = first;
    if (first != 0) return 1;
    return m_bLoop;
}
