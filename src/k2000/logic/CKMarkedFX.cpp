// CKMarkedFX.cpp - reconstructed original translation unit 0x5ceb68-0x5d1748 (GAME_TOC2, main_toc2), 38 functions, 30 live.
// Primary class: CKMarkedFX  key 0xab4c  category Logic  size ?  vtable 0xb301e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5ceb68  CKMarkedFX_Delete
//   [ ] 0x5cebb8  CKMarkedFX_Construct  [dead]
//   [x] 0x5cebf0  KStub_Nop_5cebf0
//   [x] 0x5cebf8  KStub_Nop_5cebf8
//   [ ] 0x5cec00  CKMarkedFX_StopChannelNodesMatching_maybe  [dead]
//   [x] 0x5ced80  CKMarkedFX_StopAllChannelNodes_maybe
//   [x] 0x5ceec0  CKMarkedFX_StopFlaggedChannelNodes_maybe
//   [ ] 0x5cf020  KStub_Nop_5cf020  [dead]
//   [ ] 0x5cf028  KStub_Nop_5cf028  [dead]
//   [ ] 0x5cf030  KStub_Nop_5cf030  [dead]
//   [ ] 0x5cf038  KStub_Nop_5cf038  [dead]
//   [ ] 0x5cf040  CKMarkedFX_Construct_2  [dead]
//   [x] 0x5cf078  CKMarkedFX_DeleteArray
//   [ ] 0x5cf118  RegisterCKMarkedFXClass
//   [ ] 0x5cf1a0  _GLOBAL__D_5cf1a0
//   [ ] 0x5cf1b0  _GLOBAL__I_5cf1b0
//   [x] 0x5cf1c0  CKMarkedFX_ResetChannels_maybe
//   [ ] 0x5cf258  CKMarkedFX_Save
//   [x] 0x5cf260  CKMarkedFX_RecursiveRegistration  (1: the inherited default)
//   [x] 0x5cf268  CKMarkedFX_PostLoad
//   [x] 0x5cf300  CKMarkedFX_Destroy
//   [x] 0x5cf4e8  CKMarkedFX_CreateArray
//   [x] 0x5cf5a8  CKMarkedFX_Create
//   [x] 0x5cf608  CKMarkedFX_UpdateChannel_maybe
//   [x] 0x5cfb70  CKMarkedFX_StopAllChannelNodes_2_maybe
//   [x] 0x5cfcb0  CKMarkedFX_StopAllChannelNodesAndReset_maybe
//   [ ] 0x5cfdf8  CKMarkedFX_StartChannelNodesMatching_maybe  [dead]
//   [x] 0x5d0178  CKMarkedFX_FireChannel_maybe
//   [x] 0x5d0558  CKMarkedFX_FireChannelIfMarkCrossed_maybe
//   [x] 0x5d0640  CKMarkedFX_UpdateFromAnimMarks
//   [x] 0x5d0a20  CKMarkedFX_LoadFxMarkRecord_maybe
//   [x] 0x5d0bb8  CKMarkedFX_LoadFxEntry_maybe
//   [x] 0x5d0da8  CKMarkedFX_LoadChannelEntry_maybe
//   [x] 0x5d0f28  CKMarkedFX_LoadChannelTable_maybe
//   [x] 0x5d1118  CKMarkedFX_Load
//   [x] 0x5d1568  CKMarkedFX_DeletingDestructor  (the same as 0x5d1618 CKMarkedFX_Destructor)
//   [x] 0x5d1618  CKMarkedFX_Destructor
//   [x] 0x5d16b0  CKMarkedFX_Destructor_2  (the same as 0x5d1618 CKMarkedFX_Destructor)
//
//   [x] 0x9cd6b8  CKMarkedFX_GetClassType  [inline]
//   [x] 0x9cd6c0  CKMarkedFX_GetClassID  [inline]
//   [ ] 0x9cd6c8  CKMarkedFX_IsKindOfClass  [inline]
#include "k2000/logic/CKMarkedFX.h"

#include <cstring>

#include "k2000/fx/IKFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/animation/CKAnimationMarkContainer.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/services/CKSrvFx.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"

namespace {
// The inlined push_back of the record lists: grows by one element when full.
template <class T>
void PushBackGrow1(TVector<T*, 1>* list, T* element) {
    const uint32_t used = list->m_ui32NbUsedElt;
    if (list->m_ui32NbElt == used) {
        uint32_t capacity = used + 1;
        uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(T*));
        if (capacity == 0) {
            capacity = 1;
            bytes = static_cast<uint32_t>(sizeof(T*));
        }
        list->m_pBlock = static_cast<T**>(Mem_ReallocAligned16(list->m_pBlock, bytes));
        list->m_ui32NbElt = capacity;
    }
    list->m_pBlock[list->m_ui32NbUsedElt] = element;
    ++list->m_ui32NbUsedElt;
}

// The list reset every Load helper does before its loop: capacity 1 and a new one-element block (the old
// block is not freed and the length is not reset).
template <class T>
void ResetToOne(TVector<T*, 1>* list) {
    list->m_ui32NbElt = 1;
    list->m_pBlock = static_cast<T**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T*))));
}
}  // namespace

// 0x005cf5a8 CKMarkedFX_Create, the inlined constructor, in its store order.
CKMarkedFX::CKMarkedFX() {
    m_fxEntries.m_pBlock = nullptr;
    m_fxEntries.m_ui32NbElt = 1;
    m_fxEntries.m_ui32NbUsedElt = 0;
    m_channels.m_ui32NbElt = 1;
    m_channels.m_ui32NbUsedElt = 0;
    m_channels.m_pBlock = nullptr;
}

// 0x005d0a20 CKMarkedFX_LoadFxMarkRecord_maybe
void CKMarkedFX::MarkRecord::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_unk00);
    IKFile_ReadRef(file, &m_unk08);
    IKFile_ReadRef(file, &m_unk0c);
    ReadU32LE(file, &m_unk04);
}

// 0x005d0bb8 CKMarkedFX_LoadFxEntry_maybe
void CKMarkedFX::FxEntry::Load(IKFile* file, int32_t type, CKMarkedFX* owner) {
    (void)owner;  // passed on to the mark records, which ignore it
    if (type != K_LEVEL_PLATEFORMS) return;
    IKFile_ReadRef(file, &m_unk00);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    ResetToOne(&m_marks);
    for (uint32_t i = 0; i < count; ++i) {
        MarkRecord* record = static_cast<MarkRecord*>(::operator new(sizeof(MarkRecord)));
        record->Load(file, K_LEVEL_PLATEFORMS);
        PushBackGrow1(&m_marks, record);
    }
}

// 0x005d0da8 CKMarkedFX_LoadChannelEntry_maybe
void CKMarkedFX::ChannelEntry::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    ReadU32LE(file, &m_unk04);
    IKFile_ReadRef(file, &m_unk0c);
    ReadU32LE(file, &m_unk08);
    ReadU8(file, &m_unk10);
}

// 0x005d0f28 CKMarkedFX_LoadChannelTable_maybe
void CKMarkedFX::ChannelTable::Load(IKFile* file, int32_t type, CKMarkedFX* owner) {
    (void)owner;  // passed on to the channel entries, which ignore it
    if (type != K_LEVEL_PLATEFORMS) return;
    IKFile_ReadRef(file, &m_unk00);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    ResetToOne(&m_entries);
    for (uint32_t i = 0; i < count; ++i) {
        ChannelEntry* entry = static_cast<ChannelEntry*>(::operator new(sizeof(ChannelEntry)));
        entry->Load(file, K_LEVEL_PLATEFORMS);
        PushBackGrow1(&m_entries, entry);
    }
}

// 0x005d1118 CKMarkedFX_Load
int32_t CKMarkedFX::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk04);
    IKFile_ReadRef(file, &m_unk08);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    ResetToOne(&m_fxEntries);
    for (uint32_t i = 0; i < count; ++i) {
        FxEntry* entry = static_cast<FxEntry*>(::operator new(sizeof(FxEntry)));
        entry->m_marks.m_ui32NbElt = 1;
        entry->m_marks.m_pBlock = nullptr;
        entry->m_marks.m_ui32NbUsedElt = 0;
        entry->Load(file, K_LEVEL_PLATEFORMS, this);
        PushBackGrow1(&m_fxEntries, entry);
    }
    count = 0;
    ReadU32LE(file, &count);
    ResetToOne(&m_channels);
    for (uint32_t i = 0; i < count; ++i) {
        ChannelTable* table = static_cast<ChannelTable*>(::operator new(sizeof(ChannelTable)));
        table->m_entries.m_ui32NbElt = 1;
        table->m_entries.m_pBlock = nullptr;
        table->m_entries.m_ui32NbUsedElt = 0;
        table->Load(file, K_LEVEL_PLATEFORMS, this);
        PushBackGrow1(&m_channels, table);
    }
    IKFile_ReadRef(file, &m_unk0c);
    return 1;
}

// 0x005cf268 CKMarkedFX_PostLoad
int32_t CKMarkedFX::PostLoad(int32_t type) {
    if (type == 0) {
        for (uint32_t i = 0; i < m_channels.m_ui32NbUsedElt; ++i) {
            ChannelTable* table = m_channels.m_pBlock[i];
            for (uint32_t j = 0; j < table->m_entries.m_ui32NbUsedElt; ++j) table->m_entries.m_pBlock[j]->m_unk00 = nullptr;
        }
    }
    return 1;
}

// 0x005cf1c0 CKMarkedFX_ResetChannels_maybe
void CKMarkedFX::ResetChannels() {
    for (uint32_t i = 0; i < m_channels.m_ui32NbUsedElt; ++i) {
        ChannelTable* table = m_channels.m_pBlock[i];
        for (uint32_t j = 0; j < table->m_entries.m_ui32NbUsedElt; ++j) table->m_entries.m_pBlock[j]->m_unk00 = nullptr;
    }
    m_unk28 = nullptr;
}

// 0x005cfb70 CKMarkedFX_StopAllChannelNodes_2_maybe
void CKMarkedFX::StopAllChannelNodes2() {
    for (uint32_t i = 0; i < m_channels.m_ui32NbUsedElt; ++i) {
        for (uint32_t j = 0; j < m_channels.m_pBlock[i]->m_entries.m_ui32NbUsedElt; ++j) {
            ChannelEntry* entry = m_channels.m_pBlock[i]->m_entries.m_pBlock[j];
            if (entry->m_unk00 == nullptr) continue;
            entry->m_unk00->StopAndRelease(m_unk08);  // vt+0x58
            m_channels.m_pBlock[i]->m_entries.m_pBlock[j]->m_unk00 = nullptr;
        }
    }
}

// 0x005ced80 CKMarkedFX_StopAllChannelNodes_maybe (C2.8 sequence)
void CKMarkedFX::StopAllChannelNodes() {
    for (uint32_t i = 0; i < m_channels.m_ui32NbUsedElt; ++i) {
        for (uint32_t j = 0; j < m_channels.m_pBlock[i]->m_entries.m_ui32NbUsedElt; ++j) {
            ChannelEntry* entry = m_channels.m_pBlock[i]->m_entries.m_pBlock[j];
            if (entry->m_unk00 == nullptr) continue;
            entry->m_unk00->StopAndRelease(m_unk08);  // vt+0x58
            m_channels.m_pBlock[i]->m_entries.m_pBlock[j]->m_unk00 = nullptr;
        }
    }
}

// 0x005ceec0 CKMarkedFX_StopFlaggedChannelNodes_maybe (C2.8 sequence)
void CKMarkedFX::StopFlaggedChannelNodes() {
    for (uint32_t i = 0; i < m_channels.m_ui32NbUsedElt; ++i) {
        for (uint32_t j = 0; j < m_channels.m_pBlock[i]->m_entries.m_ui32NbUsedElt; ++j) {
            ChannelEntry* entry = m_channels.m_pBlock[i]->m_entries.m_pBlock[j];
            if (entry->m_unk00 == nullptr || entry->m_unk10 == 0) continue;
            entry->m_unk00->StopAndRelease(m_unk08);  // vt+0x58
            m_channels.m_pBlock[i]->m_entries.m_pBlock[j]->m_unk00 = nullptr;
        }
    }
}

// 0x005cfcb0 CKMarkedFX_StopAllChannelNodesAndReset_maybe
void CKMarkedFX::StopAllChannelNodesAndReset() {
    StopAllChannelNodes2();  // the same loop, inlined
    m_unk28 = nullptr;
}

// 0x005d0178 CKMarkedFX_FireChannel_maybe: the FX entries in order, each one's mark records in order. A record of the
// channel and value with a hot spot (+0x08) takes a pooled effect of the entry's data (the inlined CKSrvFx lookup:
// AcquireFx, the owner +0x08); the effect (a CKExplosionNodeFx) is placed at the hot spot's world position and
// triggered, then its reservation released (vt+0x54).
void CKMarkedFX::FireChannel(uint32_t channel, uint32_t value) {
    for (uint32_t i = 0; i < m_fxEntries.m_ui32NbUsedElt; ++i) {
        FxEntry* entry = m_fxEntries.m_pBlock[i];
        for (uint32_t j = 0; j < entry->m_marks.m_ui32NbUsedElt; ++j) {
            const MarkRecord* record = entry->m_marks.m_pBlock[j];
            if (record->m_unk00 != channel || record->m_unk04 != value || record->m_unk08 == nullptr) continue;
            CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // engine +0x60
            IKFx* effect = fx->AcquireFx(static_cast<IKFxData*>(entry->m_unk00), m_unk08);
            if (effect == nullptr) continue;
            CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
            CVector3 position;
            static_cast<const CSGHotSpot*>(record->m_unk08)->GetWorldPosition(&position);  // 0x000ce790
            explosion->SetTranslation(&position, m_unk08);  // 0x001b66e8
            explosion->Trigger(m_unk08, 0);               // 0x001b82a8
            explosion->ReleaseReservation(m_unk08);       // vt+0x54
        }
    }
}

// 0x005cf608 CKMarkedFX_UpdateChannel_maybe: the mark's integer value (vt+0x10) at t0 and t1. A value at t1 that is
// new (none at t0) or held (the same at t0) starts the channel entries of that value with a hot spot and no effect
// yet: the table's particle data (+0x00) gets the hot spot (+0x14) and no node (+0x10), and a pooled effect of it
// (the inlined CKSrvFx lookup, the owner +0x08) becomes the entry's (null when none is free). A value that went back
// to 0 stops the entries of the value it had at t0 (vt+0x58) and forgets them. A changed non-zero value does nothing.
void CKMarkedFX::UpdateChannel(uint32_t channel, RtAnimAnimation* animation, const float* t0, const float* t1) {
    AnimMark* mark = Anim_GetMarkById(animation, channel);  // 0x00078830
    if (animation == nullptr || mark == nullptr) return;
    const uint32_t before = AnimMark_ValueAtR3(mark, *t0);  // vt+0x10
    const uint32_t now = AnimMark_ValueAtR3(mark, *t1);
    if (now == 0) {
        if (before == 0) return;
        for (uint32_t i = 0; i < m_channels.m_ui32NbUsedElt; ++i) {
            for (uint32_t j = 0; j < m_channels.m_pBlock[i]->m_entries.m_ui32NbUsedElt; ++j) {
                ChannelEntry* entry = m_channels.m_pBlock[i]->m_entries.m_pBlock[j];
                if (entry->m_unk04 != channel || entry->m_unk08 != before || entry->m_unk00 == nullptr) continue;
                entry->m_unk00->StopAndRelease(m_unk08);  // vt+0x58
                m_channels.m_pBlock[i]->m_entries.m_pBlock[j]->m_unk00 = nullptr;
            }
        }
        return;
    }
    if (before != 0 && before != now) return;
    for (uint32_t i = 0; i < m_channels.m_ui32NbUsedElt; ++i) {
        ChannelTable* table = m_channels.m_pBlock[i];
        for (uint32_t j = 0; j < table->m_entries.m_ui32NbUsedElt; ++j) {
            ChannelEntry* entry = table->m_entries.m_pBlock[j];
            if (entry->m_unk04 != channel || entry->m_unk08 != now || entry->m_unk0c == nullptr || entry->m_unk00 != nullptr) {
                continue;
            }
            CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(table->m_unk00);
            data->m_pAttachHotSpot = entry->m_unk0c;  // +0x14
            data->m_pAttachOwner = nullptr;            // +0x10
            CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
            entry->m_unk00 = fx->AcquireFx(data, m_unk08);
        }
    }
}

namespace {
// The 37 mark names (0x00b01198, 8-byte records: the name, then 0); the ones starting "MarkI" are the integer marks.
const char* const kMarkNames[37] = {
    "MarkI_StreamRTC_FX", "MarkI_SonPatteAvantGauch", "MarkI_SonPatteAvantDroit", "MarkI_SonPatteArriereGau",
    "MarkI_SonPatteArriereDro", "MarkI_ImpulsionStart", "MarkI_Projectiles", "MarkI_BoundingOn",
    "MarkF_VitesseDeplacement", "MarkC_Focal", "MarkI_WipeLeftOn", "MarkI_WipeRightOn", "MarkI_Interruptible",
    "MarkF_TpsAcceleration", "MarkF_TpsConstant", "MarkF_TpsDeceleration", "MarkF_Vitesse0", "MarkF_Acceleration",
    "MarkF_Deceleration", "MarkI_Enm_BoundingOn", "MarkI_Enm_ArmeSol", "MarkI_Enm_ArmeHand", "MarkC_Enm_HauteurSol",
    "MarkI_Enm_PiedGauche", "MarkI_Enm_PiedDroit", "MarkI_Enm_Spawn", "MarkI_Activate", "MarkI_Sound",
    "MarkI_Trigger", "MarkI_Explosion", "MarkI_Particles", "MarkI_Golem_FX_Explosion", "MarkI_Golem_Trigger",
    "MarkI_Golem_FX_Particule", "MarkI_Golem_FX_CameraPro", "MarkI_Golem_Sound", "MarkI_Golem_FX_Trail",
};
}  // namespace

bool IsIntegerAnimMark(uint32_t id) {
    char prefix[6];
    std::memcpy(prefix, kMarkNames[id], 5);
    prefix[5] = 0;
    return std::strcmp(prefix, "MarkI") == 0;
}

// 0x005d0640 CKMarkedFX_UpdateFromAnimMarks
void CKMarkedFX::UpdateFromAnimMarks(IKTime* /*clock*/) {
    CAnimatedNode* node = static_cast<CAnimatedNode*>(m_unk04);
    RtAnimAnimation* animation = nullptr;
    CKHkS08Hero* hero = nullptr;
    const uint32_t mode = (node->m_sgProperties >> 9) & 3;
    if (mode == 1 || mode == 2) {
        animation = node->GetCurrentAnim();  // 0x000c96d8
    } else if (m_unk0c != nullptr && m_unk0c->IsKindOfClass(0x3642) != 0) {
        hero = static_cast<CKHkS08Hero*>(m_unk0c);  // an IKHkHero: DotD's is CKHkS08Hero
        animation = hero->GetCurrentAnimResource();  // 0x00361f40
    }
    if (m_unk28 != animation) {
        // A new animation: the channel effects flagged +0x10 stopped (vt+0x58) and forgotten.
        m_unk28 = animation;
        for (uint32_t i = 0; i < m_channels.m_ui32NbUsedElt; ++i) {
            for (uint32_t j = 0; j < m_channels.m_pBlock[i]->m_entries.m_ui32NbUsedElt; ++j) {
                ChannelEntry* entry = m_channels.m_pBlock[i]->m_entries.m_pBlock[j];
                if (entry->m_unk00 == nullptr || entry->m_unk10 == 0) continue;
                entry->m_unk00->StopAndRelease(m_unk08);  // vt+0x58
                m_channels.m_pBlock[i]->m_entries.m_pBlock[j]->m_unk00 = nullptr;
            }
        }
    }
    if (animation == nullptr) return;
    float from;
    float to;
    if (hero == nullptr) {
        // The time now brought into [0, duration) (TOC1 -0x5dcc 0.0; bge / ble with cror: a NaN stays), the evaluated
        // time.
        float t = node->GetAnimTimeNow();                      // 0x000c95f0
        const float duration = node->GetCurrentAnimDuration();  // 0x000c9768
        while (t < 0.0f) t = t + duration;
        const float end = duration + 0.0f;
        while (end <= t) t = t - duration;
        to = t;
        from = node->GetCurrentAnimTime();  // 0x000c95a8
    } else {
        hero->GetAnimMarkWindow(&from, &to);  // 0x00364100
    }
    if (to == from) return;
    for (uint32_t id = 0; id < 37; ++id) {
        // strcmp of the name's first five characters with "MarkI" (0x0095f1a0).
        char prefix[6];
        std::memcpy(prefix, kMarkNames[id], 5);
        prefix[5] = 0;
        if (std::strcmp(prefix, "MarkI") != 0) continue;
        AnimMark* mark = Anim_GetMarkById(animation, id);  // 0x00078830
        if (mark != nullptr) {
            const uint32_t value = AnimMark_CrossedValueR3(mark, from, to);  // vt+0x1c
            if (value != 0) FireChannel(id, value);
        }
        UpdateChannel(id, animation, &from, &to);
    }
}

// 0x005d1618 CKMarkedFX_Destructor
CKMarkedFX::~CKMarkedFX() {
    if (m_channels.m_pBlock != nullptr) Mem_FreeAligned16(m_channels.m_pBlock);
    m_channels.m_ui32NbUsedElt = 0;
    m_channels.m_pBlock = nullptr;
    if (m_fxEntries.m_pBlock != nullptr) Mem_FreeAligned16(m_fxEntries.m_pBlock);
    m_fxEntries.m_ui32NbUsedElt = 0;
    m_fxEntries.m_pBlock = nullptr;
}

// 0x005cf300 CKMarkedFX_Destroy (OperatorDelete on the records and entries; Mem_FreeAligned16 on their blocks)
void CKMarkedFX::Destroy() {
    for (uint32_t i = 0; i < m_fxEntries.m_ui32NbUsedElt; ++i) {
        FxEntry* entry = m_fxEntries.m_pBlock[i];
        for (uint32_t j = 0; j < entry->m_marks.m_ui32NbUsedElt; ++j) ::operator delete(entry->m_marks.m_pBlock[j]);
        if (entry->m_marks.m_pBlock != nullptr) Mem_FreeAligned16(entry->m_marks.m_pBlock);
        entry->m_marks.m_ui32NbUsedElt = 0;
        entry->m_marks.m_pBlock = nullptr;
        ::operator delete(entry);
    }
    for (uint32_t i = 0; i < m_channels.m_ui32NbUsedElt; ++i) {
        ChannelTable* table = m_channels.m_pBlock[i];
        for (uint32_t j = 0; j < table->m_entries.m_ui32NbUsedElt; ++j) ::operator delete(table->m_entries.m_pBlock[j]);
        if (table->m_entries.m_pBlock != nullptr) Mem_FreeAligned16(table->m_entries.m_pBlock);
        table->m_entries.m_ui32NbUsedElt = 0;
        table->m_entries.m_pBlock = nullptr;
        ::operator delete(table);
    }
}

// 0x005d0558 CKMarkedFX_FireChannelIfMarkCrossed_maybe (Anim_GetMarkById 0x00078830 through its TOC bridge)
void CKMarkedFX::FireChannelIfMarkCrossed(uint32_t channel, RtAnimAnimation* animation, const float* t0,
                                          const float* t1) {
    AnimMark* mark = Anim_GetMarkById(animation, channel);
    if (animation == nullptr || mark == nullptr) return;
    const uint32_t value = AnimMark_CrossedValueR3(mark, *t0, *t1);  // vt+0x1c
    if (value != 0) FireChannel(channel, value);
}
