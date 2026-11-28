// CKCrumblyZoneState.cpp - reconstructed original translation unit 0x403720-0x405608 (GAME_TOC1, main_toc1), 38 functions, 22 live.
// Primary class: CKCrumblyZoneState  key 0xa40c  category Logic  size 0x4c  vtable 0xb25758
// Other owners: CrumblyZoneState (7), CKSrvBonus (1), CKHkCrumblyZoneMultiState (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x403720  CKCrumblyZoneState_Delete
//   [x] 0x403770  CKCrumblyZoneState_Construct  [dead]
//   [ ] 0x403798  FUN_00403798  [dead]
//   [ ] 0x4037d0  CKCrumblyZoneState_GetFlagBit0_maybe  [dead]
//   [ ] 0x4037e0  CKCrumblyZoneState_GetFlagBit4_maybe  [dead]
//   [ ] 0x4037f0  CKCrumblyZoneState_GetFlagBit6_maybe  [dead]
//   [ ] 0x403800  CrumblyZoneState_ClearContactList_maybe  [dead]
//   [ ] 0x403840  CKCrumblyZoneState_Construct_2  [dead]
//   [ ] 0x403868  RegisterCKCrumblyZoneStateClass
//   [ ] 0x4038e0  _GLOBAL__I_4038e0
//   [x] 0x4038f0  CKCrumblyZoneState_SetVolumesDamage_maybe
//   [ ] 0x403918  CKSrvBonus_SpawnBonusesArgSwap_ViaEngine_maybe  [dead]
//   [ ] 0x403948  CKCrumblyZoneState_ShrinkBoxAndSetNavBlocked_maybe  [dead]
//   [x] 0x403a00  CrumblyZoneState_ComputeCenter_maybe
//   [x] 0x403b10  CKCrumblyZoneState_DeleteArray
//   [ ] 0x403bb0  CKCrumblyZoneState_GetFlagBit2_maybe  [dead]
//   [ ] 0x403bc0  CKCrumblyZoneState_GetFlagBit3_maybe  [dead]
//   [ ] 0x403bd0  CKCrumblyZoneState_GetFlagBit1_maybe  [dead]
//   [x] 0x403be0  CKCrumblyZoneState_GetFlagBit9_maybe
//   [ ] 0x403bf0  CKCrumblyZoneState_GetFlagBit8_maybe  [dead]
//   [ ] 0x403c00  CKCrumblyZoneState_GetFlagBit7_maybe  [dead]
//   [ ] 0x403c10  CKCrumblyZoneState_GetFlagBit5_maybe  [dead]
//   [x] 0x403c20  CrumblyZoneState_CopyContactList_maybe
//   [x] 0x403d38  CKCrumblyZoneState_CreateArray
//   [x] 0x403de8  CKCrumblyZoneState_Create
//   [ ] 0x403e40  CKCrumblyZoneState_Save
//   [x] 0x403e48  CKCrumblyZoneState_RecursiveRegistration  (returns 1: the root's empty slot)
//   [x] 0x403e50  CKCrumblyZoneState_PostLoad
//   [x] 0x403ec8  CKHkCrumblyZoneMultiState_UpdateState_maybe
//   [x] 0x403ff8  CKCrumblyZoneState_Destroy
//   [x] 0x404050  CrumblyZoneState_SetEnabled_maybe
//   [x] 0x404378  CrumblyZoneState_UpdateNavBlocking_maybe
//   [x] 0x4047d0  CrumblyZoneState_ApplyDamage_maybe
//   [x] 0x404bc0  CrumblyZoneState_OnContact_maybe
//   [x] 0x404d98  CKCrumblyZoneState_Load
//   [x] 0x405400  CKCrumblyZoneState_DeletingDestructor  (C++ deleting destructor: ~CKCrumblyZoneState, then operator delete)
//   [x] 0x4054b8  CKCrumblyZoneState_Destructor
//   [ ] 0x405560  CKCrumblyZoneState_Destructor_2  [dead]
//
//   [ ] 0x9c1140  CKCrumblyZoneState_GetClassType  [inline]
//   [ ] 0x9c1148  CKCrumblyZoneState_GetClassID  [inline]
//   [ ] 0x9c1150  CKCrumblyZoneState_IsKindOfClass  [inline]
#include "k2000/logic/CKCrumblyZoneState.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/logic/CKCrumblyZoneElement.h"
#include "k2000/hooks/CKHkCrumblyZoneMultiState.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/components/CKBonusData.h"
#include "k2000/components/CKGroundCpnt.h"
#include "k2000/core/Stub.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/components/CKBoundingCpnt.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/services/KBase201.h"
#include "k2000/system/IKTime.h"

// 0x00403770 CKCrumblyZoneState_Construct
CKCrumblyZoneState::CKCrumblyZoneState() {
    m_vEntries.m_pBlock = nullptr;
    m_vEntries.m_ui32NbElt = 1;
    m_vEntries.m_ui32NbUsedElt = 0;
    m_unk24 = 0;
}

// 0x00404d98 CKCrumblyZoneState_Load
int32_t CKCrumblyZoneState::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pZone);
    IKFile_ReadRef(file, &m_pGroundCpnt);
    IKFile_ReadRef(file, &m_pBoundingCpnt);
    ReadF32LE(file, &m_unk0c);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_vEntries.m_ui32NbElt = 1;
        m_vEntries.m_pBlock = static_cast<Entry*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry))));
    } else {
        m_vEntries.m_ui32NbElt = count;
        m_vEntries.m_pBlock = static_cast<Entry*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Entry))));
    }
    if (m_vEntries.m_ui32NbElt < count) {  // as in the original: cannot happen
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_vEntries.m_pBlock = static_cast<Entry*>(
            Mem_ReallocAligned16(m_vEntries.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Entry))));
        m_vEntries.m_ui32NbElt = capacity;
    }
    m_vEntries.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) {
        Entry& entry = m_vEntries.m_pBlock[i];
        ReadU8(file, &entry.m_unk00);
        ReadU8(file, &entry.m_unk01);
        ReadU8(file, &entry.m_unk02);
        ReadU32LE(file, &entry.m_unk04);
        ReadU32LEWords(file, entry.m_unk08, 3);
    }
    IKFile_ReadRef(file, &m_pSound);
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unk30);
    ReadU32LE(file, &m_unk38);
    IKFile_ReadRef(file, &m_pBonusData);
    ReadF32LE(file, &m_unk40);
    ReadS32LE(file, &m_unk44);
    ReadS32LE(file, &m_unk48);
    return 1;
}

// 0x00403e50 CKCrumblyZoneState_PostLoad
int32_t CKCrumblyZoneState::PostLoad(int32_t type) {
    if (type != 0) return 1;  // cmpdi r4,0
    // The member-function pointer {TOC +0x4928 = 0xbb4578 (OnContact 0x404bc0), r4 = the type, 0} in r5.
    static_cast<CKBoundingCpnt*>(m_pBoundingCpnt)->SetContactCallback(this, &CKCrumblyZoneState::OnContact, type);
    m_unk08 = 0.0f;                                            // li r0,0; stw r0,0x8(r31)
    static_cast<CKGroundCpnt*>(m_pGroundCpnt)->SetActive(0);  // 0x001910a8
    return 1;
}

// 0x00404bc0 CrumblyZoneState_OnContact_maybe
void CKCrumblyZoneState::OnContact(void* self, IKSerializable* volumeObject, IKSerializable* contact) {
    CKCrumblyZoneState* state = static_cast<CKCrumblyZoneState*>(self);
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(volumeObject);
    if (static_cast<uint32_t>(volume->m_ui8OwnerType) - 2u > 1u) return;
    if ((volume->m_ui16PropertiesFlags & 4u) == 0 && (volume->m_ui16PropertiesFlags & 8u) == 0) return;
    IKSerializable* owner = (state->m_unk38 & 0x40u) == 0 ? volume->m_pOwner : nullptr;
    const uint8_t touched = ContactHistory_Touch(-1000.0f, -1000.0f, &state->m_unk24, volume, owner);  // TocBridge 0x98f380
    CKHkCrumblyZoneMultiState* zone = static_cast<CKHkCrumblyZoneMultiState*>(state->m_pZone);
    const float damage = zone->GetHitDamage(volume, touched);  // vt+0xf4
    if (!(damage > 0.0f)) return;  // ble (TOC +0x492c)
    ICollision* collision = reinterpret_cast<ICollision*>(contact);
    CVector3 point;
    if (collision->IsResponseParamsMaskEqualTo(8) != 0) {  // vt+0x10
        const CVector3* at = collision->GetWorldContactPoint();  // vt+0x20
        point.x = at->x;
        point.y = at->y;
        point.z = at->z;
    } else {
        const RwFrame* frame = volume->m_pRwFrame;
        point.x = frame->ltm.pos.x;
        point.y = frame->ltm.pos.y;
        point.z = frame->ltm.pos.z;
    }
    state->ApplyDamage(damage, &point);  // 0x004047d0
}

// 0x004047d0 CrumblyZoneState_ApplyDamage_maybe
void CKCrumblyZoneState::ApplyDamage(float damage, const CVector3* point) {
    CKHkCrumblyZoneMultiState* zone = static_cast<CKHkCrumblyZoneMultiState*>(m_pZone);
    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x4938)
    const float health = m_unk08;
    if (health <= damage) {  // cror lt|eq
        if (!(health > 0.0f)) return;  // ble
        zone->AdvanceToNextState(1);  // 0x00411250
        m_unk08 = 0.0f;
        CVector3 at = *point;
        ComputeCenter(&at);  // inlined (0x00403a00's loop)
        static_cast<KBase201*>(g_pEngine->m_srvBonus)
            ->SpawnBonusesArgSwap(static_cast<CKBonusData*>(m_pBonusData), &at, &kAxisY, 0);  // 0x001265b0
        QueueTriggerSignals(&zone->m_tsUnk7C);  // 0x00236338 (the state as the sender)
        CKSound* sound = CKSoundDictionaryID_GetSound(static_cast<CKSoundDictionaryID*>(m_pSound), 2);  // 0x00112bc0
        if (sound != nullptr && sound->GetSample() != nullptr) CKSound_Play(0.0f, sound);  // 0x00111000, 0x00111230
        return;
    }
    if (!(damage > 0.0f)) {  // ble
        zone->Vf104();  // vt+0x104
        return;
    }
    m_unk08 = health - damage;
    zone->PlayHitFxAt(point);  // vt+0x100
    CVector3 at = *point;
    ComputeCenter(&at);
    static_cast<KBase201*>(g_pEngine->m_srvBonus)
        ->SpawnBonusesArgSwap(static_cast<CKBonusData*>(m_pBonusData), &at, &kAxisY, 1);  // 0x001265b0
    QueueTriggerSignals(&zone->m_tsUnk7C);  // 0x00236338
    if (CKSoundDictionaryID_GetSound(static_cast<CKSoundDictionaryID*>(m_pSound), 2) != nullptr) {
        CKSound_Play(0.0f, CKSoundDictionaryID_GetSound(static_cast<CKSoundDictionaryID*>(m_pSound), 2));  // 0x00111230
    }
}

// 0x00403ec8 CKHkCrumblyZoneMultiState_UpdateState_maybe
void CKCrumblyZoneState::UpdateState(IKTime* frameClock) {
    if (m_unk40 > 0.0f) {  // ble (TOC +0x492c)
        if (m_unk40 < m_unk3c) {
            static_cast<CKHkCrumblyZoneMultiState*>(m_pZone)->GoToPreviousState(1);  // 0x00411338
        } else {
            m_unk3c = m_unk3c + frameClock->m_afDeltaTime[0];
        }
    }
    static_cast<CKBoundingCpnt*>(m_pBoundingCpnt)->DispatchActiveContacts();  // 0x00190410
    ContactHistory_Update(&m_unk24, frameClock);  // TocBridge 0x98f430
    CKSound* sound = CKSoundDictionaryID_GetSound(static_cast<CKSoundDictionaryID*>(m_pSound), 1);  // 0x00112bc0
    if (sound == nullptr || sound->GetSample() == nullptr) return;  // 0x00111000
    if (sound->m_pInstances != nullptr) return;  // its instances counted: one or more playing
    CKSound_Play(0.0f, sound);  // 0x00111230
}

// 0x004038f0 CKCrumblyZoneState_SetVolumesDamage_maybe
void CKCrumblyZoneState::SetVolumesDamage(IKSerializable* damage) {
    static_cast<CKBoundingCpnt*>(m_pBoundingCpnt)->SetVolumesDamage(damage);
}

// 0x00403a00 CrumblyZoneState_ComputeCenter_maybe: the volumes' node LTM positions (frame +0x80) summed and scaled by
// 1 / count (TOC +0x4914 1.0; the count converted with fcfid).
void CKCrumblyZoneState::ComputeCenter(CVector3* center) const {
    const CKBoundingCpnt* bounding = static_cast<const CKBoundingCpnt*>(m_pBoundingCpnt);
    const uint32_t count = bounding->GetVolumeCount();  // 0x00190408
    if (count == 0) return;
    *center = CVector3{0.0f, 0.0f, 0.0f};  // the zero vector 0x00c50d64 (TOC +0x491c)
    for (uint32_t i = 0; i < count; ++i) {
        const RwFrame* frame = static_cast<CSGMovable*>(bounding->GetVolumeAt(i))->m_pRwFrame;  // 0x001903a8
        center->z = center->z + frame->ltm.pos.z;
        center->x = center->x + frame->ltm.pos.x;
        center->y = center->y + frame->ltm.pos.y;
    }
    const float inverse = 1.0f / static_cast<float>(count);
    center->z = inverse * center->z;
    center->x = inverse * center->x;
    center->y = inverse * center->y;
}

// 0x00404050 CrumblyZoneState_SetEnabled_maybe
void CKCrumblyZoneState::SetEnabled(uint8_t on, uint8_t sound) {
    CKHkCrumblyZoneMultiState* zone = static_cast<CKHkCrumblyZoneMultiState*>(m_pZone);
    CKBoundingCpnt* volumes = static_cast<CKBoundingCpnt*>(m_pBoundingCpnt);
    if (on == 0) {
        for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
            static_cast<CKCrumblyZoneElement*>(zone->m_vUnk2C.m_pBlock[i])->Deactivate();  // 0x00402d68
        }
        static_cast<CKGroundCpnt*>(m_pGroundCpnt)->SetActive(0);  // 0x001910a8
        volumes->DisableCollision();                                // 0x001905e0
        volumes->ReparentToEngineRoot();                            // 0x00190960
        CKSound* stop = CKSoundDictionaryID_GetSound(static_cast<CKSoundDictionaryID*>(m_pSound), 1);  // 0x00112bc0
        if (stop != nullptr && stop->GetSample() != nullptr && stop->m_pInstances != nullptr) {  // 0x00111000
            Sound_Stop(stop, 0);  // 0x001111b0 (the original counts the instances first: there is one)
        }
        for (ContactHistoryNode* node = m_unk24; node != nullptr;) {  // back to the pool (TOC +0x48e4, free list +0x54)
            ContactHistoryNode* next = node->m_pNext;
            ContactHistory_FreeNode(node);
            node = next;
        }
        m_unk24 = nullptr;
        if (m_pBonusData != nullptr) static_cast<CKBonusData*>(m_pBonusData)->ResetRuntime();  // 0x00126d90
        return;
    }
    m_unk08 = m_unk0c;
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        const Entry& entry = m_vEntries.m_pBlock[i];
        CKCrumblyZoneElement* piece = static_cast<CKCrumblyZoneElement*>(zone->m_vUnk2C.m_pBlock[i]);
        if (entry.m_unk00 != 0) {
            piece->Activate(entry.m_unk04);  // 0x00402a80
            piece->SetFxPosition(reinterpret_cast<const float*>(entry.m_unk08));  // 0x00402690
        } else {
            piece->Deactivate();
        }
    }
    static_cast<CKGroundCpnt*>(m_pGroundCpnt)->SetActive(1);
    volumes->ReparentTo(zone->m_pKGLObject);  // 0x00190860
    volumes->EnableCollision();                // 0x00190680
    if (sound != 0) {
        CKSound* play = CKSoundDictionaryID_GetSound(static_cast<CKSoundDictionaryID*>(m_pSound), 0);
        if (play != nullptr && play->GetSample() != nullptr) CKSound_Play(0.0f, play);  // 0x00111230, TOC +0x492c
    }
    m_unk3c = 0.0f;
    if (m_pBonusData != nullptr) static_cast<CKBonusData*>(m_pBonusData)->ResetRuntime();
}

// 0x00404378 CrumblyZoneState_UpdateNavBlocking_maybe: each ground's box (the last first; shrunk in x / z by the factors
// 1 - +0x2c / 1 - +0x30 about its middle) blocked (`on`) or freed in the zone's path-finding node (+0x78); without grounds
// the box of +-0.5 around the zone's node in x / z.
void CKCrumblyZoneState::UpdateNavBlocking(uint8_t on) {
    if ((m_unk38 & 1u) == 0) return;
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);  // engine +0x6c
    CKHkCrumblyZoneMultiState* zone = static_cast<CKHkCrumblyZoneMultiState*>(m_pZone);
    const uint8_t blocked = on != 0 ? 1 : 0;
    const auto box = [&](const CVector3& sup, const CVector3& inf) {
        const float sx = 1.0f - m_unk2c;  // TOC +0x4914
        const float sz = 1.0f - m_unk30;
        const float dx = sup.x - inf.x;
        const float dz = sup.z - inf.z;
        CVector3 low;
        low.x = ppc::fmadds(dx * 0.5f, sx, inf.x);  // TOC +0x4910 / +0x4918: 0.5 / -0.5
        low.y = inf.y;
        low.z = ppc::fmadds(dz * 0.5f, sz, inf.z);
        CVector3 high;
        high.x = ppc::fmadds(dx * -0.5f, sx, sup.x);
        high.y = sup.y;
        high.z = ppc::fmadds(dz * -0.5f, sz, sup.z);
        pathFinding->SetBoxBlocked(zone->m_i16PathFindingNodeIndex, &low, &high, blocked);  // 0x001e5f60
    };
    const CKGroundCpnt* grounds = static_cast<const CKGroundCpnt*>(m_pGroundCpnt);
    const uint8_t count = static_cast<uint8_t>(grounds->m_vGrounds.m_ui32NbUsedElt);  // 0x00191148 (a byte)
    if (count == 0) {
        const RwV3d& p = static_cast<CSGMovable*>(zone->m_pKGLObject)->m_pRwFrame->ltm.pos;
        box({p.x + 0.5f, p.y, p.z + 0.5f}, {p.x - 0.5f, p.y, p.z - 0.5f});
        return;
    }
    for (uint8_t i = static_cast<uint8_t>(count - 1); i != 0xff; --i) {
        const float* aabb = static_cast<const ICollisionMesh*>(grounds->m_vGrounds.m_pBlock[i])->m_AABB;  // 0x00191090
        box({aabb[0], aabb[1], aabb[2]}, {aabb[3], aabb[4], aabb[5]});
    }
}

// 0x00403c20 CrumblyZoneState_CopyContactList_maybe
void CKCrumblyZoneState::CopyContactList(const CKCrumblyZoneState* from) {
    for (ContactHistoryNode* node = m_unk24; node != nullptr;) {  // back to the pool
        ContactHistoryNode* next = node->m_pNext;
        ContactHistory_FreeNode(node);
        node = next;
    }
    m_unk24 = nullptr;
    for (const ContactHistoryNode* source = from->m_unk24; source != nullptr; source = source->m_pNext) {
        ContactHistoryNode* copy = ContactHistory_AllocNode();  // FreeListPool_Grow 0x00244908 when empty
        copy->m_pKey = source->m_pKey;
        copy->m_pOwner = source->m_pOwner;
        copy->m_fTime1 = source->m_fTime1;
        copy->m_fTime2 = source->m_fTime2;
        copy->m_pNext = nullptr;
        copy->m_bTouched = source->m_bTouched;
        copy->m_pNext = m_unk24;
        m_unk24 = copy;
    }
}

// 0x00403ff8 CKCrumblyZoneState_Destroy
void CKCrumblyZoneState::Destroy() {
    if (m_vEntries.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vEntries.m_pBlock);
        m_vEntries.m_pBlock = nullptr;
    }
    m_vEntries.m_ui32NbUsedElt = 0;
    m_vEntries.m_pBlock = nullptr;
}

// 0x004054b8 CKCrumblyZoneState_Destructor
CKCrumblyZoneState::~CKCrumblyZoneState() {
    for (ContactHistoryNode* node = m_unk24; node != nullptr;) {
        ContactHistoryNode* next = node->m_pNext;  // +0x14
        ContactHistory_FreeNode(node);
        node = next;
    }
    m_unk24 = nullptr;
    if (m_vEntries.m_pBlock != nullptr) Mem_FreeAligned16(m_vEntries.m_pBlock);
    m_vEntries.m_ui32NbUsedElt = 0;
    m_vEntries.m_pBlock = nullptr;
}
