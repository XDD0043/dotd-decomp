// CKGolemAttackCommon.cpp - reconstructed original translation unit 0x4b7728-0x4ba5a0 (GAME_TOC1, main_toc1), 35 functions, 31 live.
// Primary class: CKGolemAttackCommon  key 0x994c  category Logic  size 0x98  vtable 0xb28fc0
// Other owners: IKSerializable (5)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4b7728  RegisterCKGolemAttackCommonClass
//   [ ] 0x4b77a0  _GLOBAL__I_4b77a0
//   [x] 0x4b77b0  CKGolemAttackCommon_PlayRandomSlotSound_maybe
//   [ ] 0x4b7a38  CKGolemAttackCommon_ApplyPoseFromList58_maybe  [dead]
//   [x] 0x4b7b10  KBaseC_vf88
//   [x] 0x4b7b50  KBaseC_vf84
//   [x] 0x4b7b88  KBaseC_vf8C_2
//   [x] 0x4b7bc8  KBaseC_vf80_3
//   [ ] 0x4b7c08  CKGolemAttackCommon_QueueTriggerSignals_maybe  [dead]
//   [ ] 0x4b7c38  CKGolemAttackCommon_FireTimedTriggers_maybe  [dead]
//   [x] 0x4b7d38  CKGolemAttackCommon_FireAnimMarkTriggers_maybe
//   [ ] 0x4b7fc8  CKGolemAttackCommon_Save
//   [x] 0x4b7ff0  CKGolemAttackCommon_RecursiveRegistration  (inherited: KBase984C_vf24)
//   [x] 0x4b8018  CKGolemAttackCommon_Construct_2  (the same as 0x4b87b0 CKGolemAttackCommon_Construct)
//   [x] 0x4b8088  CKGolemAttackCommon_DeleteArray
//   [x] 0x4b8128  CKGolemAttackCommon_vf5C
//   [x] 0x4b8230  KBaseC_vf9C_2
//   [x] 0x4b8250  CKGolemAttackCommon_AttachVolumesToHotSpots_maybe
//   [x] 0x4b8400  CKGolemAttackCommon_StartAttack_maybe
//   [x] 0x4b87b0  CKGolemAttackCommon_Construct
//   [x] 0x4b8820  CKGolemAttackCommon_Destroy
//   [x] 0x4b8908  CKGolemAttackCommon_StopAttack_maybe
//   [x] 0x4b8a08  KStub_Return1_4b8a08  (vt+0x40 GetInfo: 1, the inherited default)
//   [ ] 0x4b8a10  CKGolemAttackCommon_ApplyPoseFromList5C_maybe  [dead]
//   [x] 0x4b8ae8  CKGolemAttackCommon_Destructor
//   [x] 0x4b8bc0  CKGolemAttackCommon_BaseDestructor  (the same as 0x4b8ae8 CKGolemAttackCommon_Destructor)
//   [x] 0x4b8c98  CKGolemAttackCommon_DeletingDestructor  (the same as 0x4b8ae8 CKGolemAttackCommon_Destructor)
//   [x] 0x4b8d80  CKGolemAttackCommon_PostLoad
//   [x] 0x4b8e90  CKGolemAttackCommon_CreateArray
//   [x] 0x4b8f88  CKGolemAttackCommon_Create
//   [x] 0x4b9010  CKGolemAttackCommon_AdvanceStepsList58_maybe
//   [x] 0x4b93a0  CKGolemAttackCommon_UpdateAnimAndAdvanceSteps_maybe
//   [x] 0x4b9508  CKGolemAttackCommon_AdvanceStepsList5C_maybe
//   [x] 0x4b9898  CKGolemAttackCommon_Update_maybe
//   [x] 0x4b9bb8  CKGolemAttackCommon_Load
//
//   [ ] 0x9c5580  CKGolemAttackCommon_IsKindOfClass  [inline]
//   [ ] 0x9c55b8  CKGolemAttackCommon_GetClassType  [inline]
//   [ ] 0x9c55c0  CKGolemAttackCommon_GetClassID  [inline]
#include "k2000/logic/CKGolemAttackCommon.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/hooks/CKHkGolem.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKGolemPhaseManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include "k2000/logic/animation/CKAnimationMarkContainer.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Quat.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/GolemPhaseCondAnd.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"

// 0x004b87b0 CKGolemAttackCommon_Construct: KBase984C's constructor, then the stores in the original's order.
CKGolemAttackCommon::CKGolemAttackCommon() {
    m_apUnk08 = nullptr;
    m_unk08Capacity = 1;
    m_unk08Count = 0;
    m_unk14 = 0;
    m_unk6cCapacity = 1;
    m_unk6cCount = 0;
    m_apUnk6c = nullptr;
    // BUG(original): the blend time +0x78 has no store here, in Create (0x4b8f88), Load or PostLoad; only vt+0x78 sets
    // it. CKGolemPhaseAttack_StartStepNoStop 0x4baec0 starts the attack (vt+0x50) before it sets the blend (vt+0x78),
    // so an attack first started that way reads whatever its fresh heap held. In G (+60774, the first StartStepNoStop,
    // that attack's first start) the original took the crossfade branch (not above 0 would be PlayAnim) and the
    // crossfade ended within that frame: the blender has w = 1 and the new animation in slot 1 at once, i.e. a value in
    // (0, dt] (a small integer or a PS3 heap pointer read as a float is a tiny positive float). dotd's zeroed heap gave
    // PlayAnim (slot 0, w = 0). FLT_MIN behaves like any such value: the crossfade, finished by its first update.
    m_unk78 = 1.17549435e-38f;  // FLT_MIN
}

// 0x004b9bb8 CKGolemAttackCommon_Load: KBase984C's data, then, for K_LEVEL_PLATEFORMS only, a byte, a reference,
// two counted arrays of entries (each with its own reference in front), five byte+reference pairs and two
// more references.
int32_t CKGolemAttackCommon::Load(IKFile* file, int32_t type) {
    KBase984C::Load(file, type);
    if (type != 0) return 1;

    ReadU8(file, &m_unk64);
    IKFile_ReadRef(file, &m_unk60);

    uint32_t count = 0;
    ReadU32LE(file, &count);
    // BUG(original): a fresh one-entry block every Load; the old block is not freed and the count is kept.
    m_unk08Capacity = 1;
    m_apUnk08 = static_cast<Entry08**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry08*))));
    for (uint32_t i = 0; i < count; ++i) {
        Entry08* entry = new Entry08;
        IKSerializable* hotSpot = nullptr;
        IKSerializable* volume = nullptr;
        IKFile_ReadRef(file, &hotSpot);
        IKFile_ReadRef(file, &volume);
        entry->m_unk04 = static_cast<CSGHotSpot*>(hotSpot);
        entry->m_unk00 = static_cast<IKBoundingVolume*>(volume);
        ReadU8(file, &entry->m_unk0d);
        ReadU8(file, &entry->m_unk0c);
        ReadU8(file, &entry->m_unk09);
        ReadU8(file, &entry->m_unk08);
        ReadU8(file, &entry->m_unk0a);
        ReadU8(file, &entry->m_unk0b);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&entry->m_unk10), 3);
        if (m_unk08Capacity == m_unk08Count) {
            uint32_t capacity = m_unk08Count + 1;
            if (capacity == 0) capacity = 1;
            m_apUnk08 = static_cast<Entry08**>(
                Mem_ReallocAligned16(m_apUnk08, capacity * static_cast<uint32_t>(sizeof(Entry08*))));
            m_unk08Capacity = capacity;
        }
        m_apUnk08[m_unk08Count] = entry;
        m_unk08Count = m_unk08Count + 1;
    }

    IKFile_ReadRef(file, &m_unk68);
    count = 0;
    ReadU32LE(file, &count);
    // BUG(original): as above (a fresh block, the old one leaked, the count kept).
    m_unk6cCapacity = 1;
    m_apUnk6c = static_cast<Entry6C**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry6C*))));
    for (uint32_t i = 0; i < count; ++i) {
        Entry6C* entry = new Entry6C;
        ReadF32LE(file, &entry->m_unk00);
        ReadU32LE(file, &entry->m_unk0c);
        entry->m_unk04.Load(file, 0);
        if (m_unk6cCapacity == m_unk6cCount) {
            uint32_t capacity = m_unk6cCount + 1;
            if (capacity == 0) capacity = 1;
            m_apUnk6c = static_cast<Entry6C**>(
                Mem_ReallocAligned16(m_apUnk6c, capacity * static_cast<uint32_t>(sizeof(Entry6C*))));
            m_unk6cCapacity = capacity;
        }
        m_apUnk6c[m_unk6cCount] = entry;
        m_unk6cCount = m_unk6cCount + 1;
    }

    IKFile_ReadRef(file, &m_unk50);
    for (SoundSlot& slot : m_aSlots) {
        ReadU8(file, &slot.m_unk00);
        IKFile_ReadRef(file, &slot.m_unk04);
    }
    IKFile_ReadRef(file, &m_unk54);
    return 1;
}

// ---- C2.8: the attack at run time ----

CKHkGolem* CKGolemAttackCommon::Golem() const { return static_cast<CKHkGolem*>(m_unk04); }

namespace {
CAnimatedNode* GolemNode(const CKGolemAttackCommon* attack) {
    return static_cast<CAnimatedNode*>(attack->Golem()->m_pKGLObject);  // the golem's +0x1c
}
}  // namespace

// 0x004b8d80 CKGolemAttackCommon_PostLoad: each volume's properties rebuilt from the entry's bytes (+0x0a: 0x10, +0x0b:
// 0x100, +0x09: 0x20, +0x08: 0x200), owner type 1, the golem as owner, infos bit 7 set, the attack's damage (+0x68).
int32_t CKGolemAttackCommon::PostLoad(int32_t /*type*/) {
    for (uint32_t i = 0; i < m_unk08Count; ++i) {
        Entry08* entry = m_apUnk08[i];
        IKBoundingVolume* volume = entry->m_unk00;
        volume->m_ui16PropertiesFlags = 0;
        volume->m_ui8OwnerType = 0;
        if (entry->m_unk0a != 0) volume->m_ui16PropertiesFlags = static_cast<uint16_t>(volume->m_ui16PropertiesFlags | 0x10u);
        if (entry->m_unk0b != 0) volume->m_ui16PropertiesFlags = static_cast<uint16_t>(volume->m_ui16PropertiesFlags | 0x100u);
        if (entry->m_unk09 != 0) volume->m_ui16PropertiesFlags = static_cast<uint16_t>(volume->m_ui16PropertiesFlags | 0x20u);
        if (entry->m_unk08 != 0) volume->m_ui16PropertiesFlags = static_cast<uint16_t>(volume->m_ui16PropertiesFlags | 0x200u);
        volume->m_ui8OwnerType = 1;
        volume->m_pOwner = m_unk04;
        volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0x7fu) | 0x80u);
        volume->m_unk1c = m_unk68;
    }
    return 1;
}

// 0x004b8128 CKGolemAttackCommon_vf5C: each volume out of its parent (vt+0x78) and under sector 0's root (vt+0x70).
void CKGolemAttackCommon::Vf5C() {
    for (uint32_t i = 0; i < m_unk08Count; ++i) {
        IKBoundingVolume* volume = m_apUnk08[i]->m_unk00;
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);
        CKSector* base = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[0]);
        base->m_pSectorRoot->AddChild(m_apUnk08[i]->m_unk00);
    }
}

// 0x004b8250 CKGolemAttackCommon_AttachVolumesToHotSpots_maybe: each volume switched off (+0x10 bit 2), out of its
// parent (vt+0x78), under its hot spot (CSGHotSpot_AttachVolume), moved by the entry's offset (the frame's modelling
// position, the identity flag cleared, RwFrame_MarkDirty) and given the attack's damage; no first condition list.
void CKGolemAttackCommon::AttachVolumesToHotSpots() {
    for (uint32_t i = 0; i < m_unk08Count; ++i) {
        Entry08* entry = m_apUnk08[i];
        entry->m_unk00->m_sgProperties = (entry->m_unk00->m_sgProperties & 0xfffffffbu) | 4u;
        IKBoundingVolume* volume = m_apUnk08[i]->m_unk00;
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);
        m_apUnk08[i]->m_unk04->AttachVolume(m_apUnk08[i]->m_unk00);  // 0x000ce2b8
        entry = m_apUnk08[i];
        RwFrame* frame = entry->m_unk00->m_pRwFrame;
        const float dy = entry->m_unk14;
        const float dz = entry->m_unk18;
        frame->modelling.pos.x = frame->modelling.pos.x + entry->m_unk10;
        frame->modelling.pos.y = frame->modelling.pos.y + dy;
        frame->modelling.pos.z = frame->modelling.pos.z + dz;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
        m_apUnk08[i]->m_unk00->m_unk1c = m_unk68;
    }
    m_unk58 = nullptr;
}

// 0x004b8400 CKGolemAttackCommon_StartAttack_maybe: the animation (+0x60's word 0) on the golem's node, cut from 0
// (CAnimatedNode_PlayAnim_maybe, no restart) when the blend time is not above 0 (fcmpu + cror: a NaN blends), else
// blended (CrossfadeToAnim, mode 1); every condition's vt+0x0c; the volumes switched on (CKSrvCollision_EnableVolume,
// +0x10 bit 2 cleared); the timed triggers re-armed; the damage and time marks; the five sound slots not playing.
void CKGolemAttackCommon::StartAttack() {
    m_unk65 = 0;
    m_unk88 = 0.0f;
    m_unk8c = 0;
    const uint32_t word = static_cast<uint32_t>(static_cast<const CAnimationDictionary*>(m_unk60)->m_apAnimations[0]);
    CAnimatedNode* node = GolemNode(this);
    if (CAnimationManager_GetAnimation(word) != nullptr) {  // the resolved entry (dotd keeps the dictionary words)
        if (m_unk78 <= 0.0f) {
            node->PlayAnim(0.0, word, 0);  // 0x000c98b8
        } else {
            node->CrossfadeToAnim(m_unk78, 0.0, word, 1);  // 0x000c8eb0
        }
        if (node->ActiveController()->m_unk5c != nullptr) node->GetCurrentAnimTime();  // 0x000c9720 / 0x000c95a8 (unused)
        m_unk65 = 0;
    }
    if (m_unk58 != nullptr) {
        for (uint32_t i = 0; i < m_unk58->m_ui32NbUsedElt; ++i) {
            for (uint32_t c = 0; c < m_unk58->m_pBlock[i]->m_conditions.m_ui32NbUsedElt; ++c) {
                GolemPhaseCond* condition = m_unk58->m_pBlock[i]->m_conditions.m_pBlock[c];
                if (condition != nullptr) condition->OnStart();
            }
        }
    }
    if (m_unk5c != nullptr) {
        for (uint32_t i = 0; i < m_unk5c->m_ui32NbUsedElt; ++i) {
            for (uint32_t c = 0; c < m_unk5c->m_pBlock[i]->m_conditions.m_ui32NbUsedElt; ++c) {
                GolemPhaseCond* condition = m_unk5c->m_pBlock[i]->m_conditions.m_pBlock[c];
                if (condition != nullptr) condition->OnStart();
            }
        }
    }
    for (uint32_t i = 0; i < m_unk08Count; ++i) {
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->EnableVolume(m_apUnk08[i]->m_unk00);  // 0x00192090
        m_apUnk08[i]->m_unk00->m_sgProperties &= 0xfffffffbu;
    }
    for (uint32_t i = 0; i < m_unk6cCount; ++i) m_apUnk6c[i]->m_unk10 = 0;
    m_unk7c = Golem()->GetTotalDamageTaken();
    m_unk80 = Golem()->GetTotalDamageTaken();
    m_unk90 = GolemClockTime();
    m_unk94 = GolemClockTime();
    m_aSlots[4].m_unk01 = 0;
    m_aSlots[0].m_unk01 = 0;
    m_aSlots[1].m_unk01 = 0;
    m_aSlots[2].m_unk01 = 0;
    m_aSlots[3].m_unk01 = 0;
}

// 0x004b8908 CKGolemAttackCommon_StopAttack_maybe: no condition lists, the time 0, the volumes switched off
// (CKSrvCollision_DisableVolume, +0x10 bit 2 set), the damage marks.
void CKGolemAttackCommon::StopAttack() {
    m_unk5c = nullptr;
    m_unk88 = 0.0f;
    m_unk58 = nullptr;
    for (uint32_t i = 0; i < m_unk08Count; ++i) {
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->DisableVolume(m_apUnk08[i]->m_unk00);  // 0x001920e8
        m_apUnk08[i]->m_unk00->m_sgProperties = (m_apUnk08[i]->m_unk00->m_sgProperties & 0xfffffffbu) | 4u;
    }
    m_unk7c = Golem()->GetTotalDamageTaken();
    m_unk80 = Golem()->GetTotalDamageTaken();
}

// 0x004c7420 KBaseC_vf68_3 / 0x004c7478 KBaseC_vf6C_4: the golem (if any) attaches / detaches this attack.
void CKGolemAttackCommon::Vf68() {
    if (m_unk04 != nullptr) Golem()->AddObject(this);  // vt+0xf0
}
void CKGolemAttackCommon::Vf6C() {
    if (m_unk04 != nullptr) Golem()->RemoveObject(this);  // vt+0xf4
}

// 0x004b7bc8 / 0x004b7b50 / 0x004b7b10 / 0x004b7b88: the golem's total damage less a mark (+0x7c, +0x80, +0x84).
int32_t CKGolemAttackCommon::GetDamageSinceStartMark() const { return Golem()->GetTotalDamageTaken() - m_unk7c; }
void CKGolemAttackCommon::MarkDamageStart() { m_unk7c = Golem()->GetTotalDamageTaken(); }
int32_t CKGolemAttackCommon::GetDamageSinceStart() const { return Golem()->GetTotalDamageTaken() - m_unk80; }
int32_t CKGolemAttackCommon::GetDamageSinceUpdate() const { return Golem()->GetTotalDamageTaken() - m_unk84; }

// 0x004b8230 KBaseC_vf9C_2
void CKGolemAttackCommon::MarkTime() { m_unk94 = GolemClockTime(); }

// 0x004b75d8 KBaseC_vfA0_2: the golem's vt+0x120 with the clock and the volume entries (+0x08).
void CKGolemAttackCommon::ProcessContacts(IKTime* clock) { Golem()->ProcessContacts(clock, this); }

// 0x004b9898 CKGolemAttackCommon_Update_maybe: the time advanced by the frame time, the golem's damage since its mark
// kept, the contacts (vt+0xa0), every condition's vt+0x08 with the frame time, the timed triggers whose time is past
// (above 0 and below the attack's time: fcmpu / ble, a NaN waits) fired once, then the animation and the step lists
// (UpdateAnimAndAdvanceSteps), the mark triggers and the second step list.
void CKGolemAttackCommon::Update(IKTime* clock) {
    const float dt = clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
    m_unk88 = m_unk88 + dt;
    m_unk84 = Golem()->GetDamageTakenSinceMark();  // 0x004bec68
    ProcessContacts(clock);                        // vt+0xa0
    if (m_unk58 != nullptr) {
        for (uint32_t i = 0; i < m_unk58->m_ui32NbUsedElt; ++i) {
            for (uint32_t c = 0; c < m_unk58->m_pBlock[i]->m_conditions.m_ui32NbUsedElt; ++c) {
                GolemPhaseCond* condition = m_unk58->m_pBlock[i]->m_conditions.m_pBlock[c];
                if (condition != nullptr) condition->Update(clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME]);
            }
        }
    }
    if (m_unk5c != nullptr) {
        for (uint32_t i = 0; i < m_unk5c->m_ui32NbUsedElt; ++i) {
            for (uint32_t c = 0; c < m_unk5c->m_pBlock[i]->m_conditions.m_ui32NbUsedElt; ++c) {
                GolemPhaseCond* condition = m_unk5c->m_pBlock[i]->m_conditions.m_pBlock[c];
                if (condition != nullptr) condition->Update(clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME]);
            }
        }
    }
    for (uint32_t i = 0; i < m_unk6cCount; ++i) {
        Entry6C* entry = m_apUnk6c[i];
        if (entry->m_unk00 > 0.0f && m_unk88 > entry->m_unk00 && entry->m_unk10 == 0) {
            QueueTriggerSignals(&entry->m_unk04);  // 0x00236338
            m_apUnk6c[i]->m_unk10 = 1;
        }
    }
    UpdateAnimAndAdvanceSteps(clock);
    FireAnimMarkTriggers();
    AdvanceStepsList5C();
}

// 0x004b93a0 CKGolemAttackCommon_UpdateAnimAndAdvanceSteps_maybe: a looping animation (+0x64), or one not ended yet,
// runs: not at its end, its time advances (AddAnimTime); at its end the loop count grows and the end is kept; a
// looping one asks the first step list (it continues from the start when nothing is chosen), a single one stays on its
// last frame (the time set to the duration) and the first step list is asked. An ended single animation only asks.
void CKGolemAttackCommon::UpdateAnimAndAdvanceSteps(IKTime* clock) {
    CAnimatedNode* node = GolemNode(this);
    const float dt = clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
    if (m_unk64 != 0 || m_unk65 == 0) {
        if (!node->IsAnimEndReached(dt)) {  // 0x000ca368
            node->AddAnimTime(dt);          // 0x000c9638
            return;
        }
        m_unk8c = m_unk8c + 1;
        m_unk65 = 1;
        if (m_unk64 != 0) {
            if (AdvanceStepsList58() != 0) return;
            m_unk65 = 0;
            node->AddAnimTime(dt);
            return;
        }
        node->SetCurrentAnimTime(node->GetCurrentAnimDuration());  // 0x000c9690 / 0x000c9768
    }
    AdvanceStepsList58();
}


namespace {
// The golem's node put at a step record's marker (a CKMarkerBeacon: its quaternion +0x10 as the rotation
// (Quat_ToMatrixNormalizing 0x00241d78), its position +0x04, the identity flag cleared; CSGMovable_SetLocalMatrix_maybe).
void MoveGolemToMarker(CKGolemAttackCommon* attack, const IKSerializable* marker) {
    const CKMarkerBeacon* beacon = static_cast<const CKMarkerBeacon*>(marker);
    alignas(16) CMatrix34 matrix;
    float q[4];
    std::memcpy(q, beacon->m_qOrientation, sizeof q);
    Quat_ToMatrixNormalizing(q, &matrix);
    const CVector3 p = beacon->m_v3Position;
    matrix.m_pos.z = p.z;
    matrix.m_pos.x = p.x;
    matrix.m_pos.y = p.y;
    matrix.m_ui32Flags &= 0xfffdffffu;
    static_cast<CSGMovable*>(attack->Golem()->m_pKGLObject)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));
}
}  // namespace

// 0x004b9010 CKGolemAttackCommon_AdvanceStepsList58_maybe: the first record of the first list whose non-null
// conditions all hold (each one is asked, vt+0x28, while the record is open; a closed once-record (+0x18 / +0x19)
// fails on any non-null condition; no condition at all: taken). Taken: a once-record closes and opens its follow-up
// (+0x1c; outside the list: it only closes), the golem's node goes to the record's marker (+0x14), the golem switches
// to the record's phase and step with blend 0 (TOC +0x655c), the record's conditions reset their baselines (vt+0x2c,
// no null test). 1 when a record was taken.
uint8_t CKGolemAttackCommon::AdvanceStepsList58() {
    TVector<GolemStepA*, 1>* list = m_unk58;
    if (list == nullptr) return 0;
    for (uint32_t i = 0; i < list->m_ui32NbUsedElt; ++i) {
        bool allow = true;
        for (uint32_t c = 0; c < list->m_pBlock[i]->m_conditions.m_ui32NbUsedElt; ++c) {
            GolemStepA* record = list->m_pBlock[i];
            GolemPhaseCond* condition = record->m_conditions.m_pBlock[c];
            if (condition == nullptr) continue;
            if (record->m_unk18 == 0 || record->m_unk19 == 0) {
                const uint8_t met = condition->IsMet(this);
                list = m_unk58;
                if (met != 0) continue;
            }
            allow = false;
        }
        if (!allow) continue;
        GolemStepA* record = list->m_pBlock[i];
        if (record->m_unk18 != 0) {
            const int32_t follow = record->m_unk1c;
            if (follow < 0 || static_cast<int32_t>(list->m_ui32NbUsedElt) <= follow) {
                list->m_pBlock[i]->m_unk19 = 1;
            } else {
                list->m_pBlock[follow]->m_unk19 = 0;
                m_unk58->m_pBlock[i]->m_unk19 = 1;
            }
            list = m_unk58;
        }
        TVector<GolemStepA*, 1>* current = list;
        if (i < list->m_ui32NbUsedElt && list->m_pBlock[i]->m_unk14 != nullptr) {
            MoveGolemToMarker(this, list->m_pBlock[i]->m_unk14);
            current = m_unk58;
        }
        Golem()->PhaseManager()->SwitchToPhase(current->m_pBlock[i]->m_unk00, current->m_pBlock[i]->m_unk04, 0.0f);
        GolemStepA* taken = list->m_pBlock[i];
        for (uint32_t c = 0; c < taken->m_conditions.m_ui32NbUsedElt; ++c) {
            taken->m_conditions.m_pBlock[c]->ResetBaseline(this);
            taken = list->m_pBlock[i];
        }
        return 1;
    }
    return 0;
}

// 0x004b9508 CKGolemAttackCommon_AdvanceStepsList5C_maybe: the same over the second list (once +0x1c, closed +0x1d,
// follow-up +0x20, marker +0x18), the switch with the record's blend time (+0x08).
uint8_t CKGolemAttackCommon::AdvanceStepsList5C() {
    TVector<GolemStepB*, 1>* list = m_unk5c;
    if (list == nullptr) return 0;
    for (uint32_t i = 0; i < list->m_ui32NbUsedElt; ++i) {
        bool allow = true;
        for (uint32_t c = 0; c < list->m_pBlock[i]->m_conditions.m_ui32NbUsedElt; ++c) {
            GolemStepB* record = list->m_pBlock[i];
            GolemPhaseCond* condition = record->m_conditions.m_pBlock[c];
            if (condition == nullptr) continue;
            if (record->m_unk1c == 0 || record->m_unk1d == 0) {
                const uint8_t met = condition->IsMet(this);
                list = m_unk5c;
                if (met != 0) continue;
            }
            allow = false;
        }
        if (!allow) continue;
        GolemStepB* record = list->m_pBlock[i];
        if (record->m_unk1c != 0) {
            const int32_t follow = record->m_unk20;
            if (follow < 0 || static_cast<int32_t>(list->m_ui32NbUsedElt) <= follow) {
                list->m_pBlock[i]->m_unk1d = 1;
            } else {
                list->m_pBlock[follow]->m_unk1d = 0;
                m_unk5c->m_pBlock[i]->m_unk1d = 1;
            }
            list = m_unk5c;
        }
        TVector<GolemStepB*, 1>* current = list;
        if (i < list->m_ui32NbUsedElt && list->m_pBlock[i]->m_unk18 != nullptr) {
            MoveGolemToMarker(this, list->m_pBlock[i]->m_unk18);
            current = m_unk5c;
        }
        const GolemStepB* chosen = current->m_pBlock[i];
        Golem()->PhaseManager()->SwitchToPhase(chosen->m_unk00, chosen->m_unk04, chosen->m_unk08);
        GolemStepB* taken = list->m_pBlock[i];
        for (uint32_t c = 0; c < taken->m_conditions.m_ui32NbUsedElt; ++c) {
            taken->m_conditions.m_pBlock[c]->ResetBaseline(this);
            taken = list->m_pBlock[i];
        }
        return 1;
    }
    return 0;
}

// 0x004b7d38 CKGolemAttackCommon_FireAnimMarkTriggers_maybe: with an evaluated animation, the time now brought into
// [0, duration) (bge / blt; cror: a NaN stays) against the evaluated time: when they differ, the value crossed on mark
// channel 0x20 (vt+0x1c) fires the triggers of that mark (time not above 0 (cror: a NaN fails), mark index below 10
// and equal to value - 1, not fired yet) once; the value crossed on channel 0x23 plays slot value - 1's sound.
void CKGolemAttackCommon::FireAnimMarkTriggers() {
    CAnimatedNode* node = GolemNode(this);
    // 0x000c9720 CAnimatedNode_GetActiveAnim_maybe: the evaluated animation (DOTD: the pointer, not its word).
    RtAnimAnimation* animation = node->ActiveController()->m_unk5c;
    if (animation == nullptr) return;
    float to = node->GetAnimTimeNow();                     // 0x000c95f0
    const float duration = node->GetCurrentAnimDuration();  // 0x000c9768
    while (to < 0.0f) to = to + duration;
    const float end = duration + 0.0f;
    while (end <= to) to = to - duration;
    const float from = node->GetCurrentAnimTime();  // 0x000c95a8
    if (from == to) return;
    AnimMark* mark = Anim_GetMarkById(animation, 0x20);  // 0x00078830
    if (mark != nullptr) {
        const uint32_t value = AnimMark_CrossedValueR3(mark, from, to);  // vt+0x1c
        if (value != 0) {
            for (uint32_t i = 0; i < m_unk6cCount; ++i) {
                Entry6C* entry = m_apUnk6c[i];
                if (!(entry->m_unk00 <= 0.0f)) continue;
                if (entry->m_unk0c > 9 || value - 1 != entry->m_unk0c) continue;
                if (entry->m_unk10 != 0) continue;
                QueueTriggerSignals(&entry->m_unk04);  // 0x00236338
                m_apUnk6c[i]->m_unk10 = 1;
            }
        }
    }
    mark = Anim_GetMarkById(animation, 0x23);
    if (mark == nullptr) return;
    const uint32_t value = AnimMark_CrossedValueR3(mark, from, to);
    if (value == 0) return;
    PlayRandomSlotSound(value - 1);
}

// 0x004b77b0 CKGolemAttackCommon_PlayRandomSlotSound_maybe: slot `slot` (below 5) of sounds 3*slot..3*slot+2 of the
// dictionary +0x50. A slot that is not a playing loop: the sounds with a sample counted; with any, one draw (Rand_Int,
// low 16 bits x count >> 16) picks one, played at the slot's hot spot (else the null vector 0x00c50d64) with the slot's
// loop flag from 0 (the same index of the dictionary +0x54 too, when there is one); the slot is then playing. A
// playing loop: stopped (Sound_Stop, not immediate), the slot no longer playing.
void CKGolemAttackCommon::PlayRandomSlotSound(uint32_t slot) {
    if (slot >= 5) return;
    SoundSlot& s = m_aSlots[slot];
    CKSoundDictionaryID* dictionary = static_cast<CKSoundDictionaryID*>(m_unk50);
    const uint32_t first = slot * 3;
    if (s.m_unk01 != 0 && s.m_unk00 != 0) {
        s.m_unk01 = 0;
        for (uint32_t i = first; i < first + 3; ++i) {
            CKSound* sound = dictionary->GetSound2(i);  // 0x00112bd8
            if (sound != nullptr) sound->Stop(0);       // 0x001111b0
        }
        return;
    }
    int32_t count = 0;
    for (uint32_t i = first; i < first + 3; ++i) {
        CKSound* sound = dictionary->GetSound2(i);
        if (sound != nullptr && sound->GetSample() != nullptr) ++count;  // 0x00111000
    }
    if (count == 0) return;
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
    const uint32_t index = first + (((r * static_cast<uint32_t>(count)) >> 16) & 0xffffu);
    CKSound* sound = dictionary->GetSound2(index);
    CKSound* second = nullptr;
    if (m_unk54 != nullptr) second = static_cast<CKSoundDictionaryID*>(m_unk54)->GetSound2(index);
    CVector3 position{0.0f, 0.0f, 0.0f};  // BUG(original): uninitialised when only the second dictionary has the sound
    if (sound != nullptr) {
        if (s.m_unk04 != nullptr) static_cast<const CSGHotSpot*>(s.m_unk04)->GetWorldPosition(&position);  // 0x000ce790
        sound->SetPosition(&position);  // 0x00110fa0
        sound->SetLoop(s.m_unk00);      // 0x00110fd0
        sound->Play(0.0f);              // 0x00111230
        s.m_unk01 = 1;
    }
    if (second != nullptr) {
        second->SetPosition(&position);
        second->SetLoop(s.m_unk00);
        second->Play(0.0f);
    }
}

// 0x004b8820 CKGolemAttackCommon_Destroy: KStub_Nop_4c7580 (the base's), then the entries deleted.
void CKGolemAttackCommon::Destroy() {
    for (uint32_t i = 0; i < m_unk08Count; ++i) {
        if (m_apUnk08[i] != nullptr) delete m_apUnk08[i];
    }
    for (uint32_t i = 0; i < m_unk6cCount; ++i) {
        if (m_apUnk6c[i] != nullptr) delete m_apUnk6c[i];
    }
}

// 0x004b8ae8 CKGolemAttackCommon_Destructor: the two blocks freed (the +0x14 node list is empty: nothing live fills
// it); CKGolemAttackBase_maybe_BaseDestructor 0x4c75e0 stores the base's vtable only.
CKGolemAttackCommon::~CKGolemAttackCommon() {
    if (m_apUnk6c != nullptr) Mem_FreeAligned16(m_apUnk6c);
    m_unk6cCount = 0;
    m_apUnk6c = nullptr;
    m_unk14 = 0;
    if (m_apUnk08 != nullptr) Mem_FreeAligned16(m_apUnk08);
    m_unk08Count = 0;
    m_apUnk08 = nullptr;
}
