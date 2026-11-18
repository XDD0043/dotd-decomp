// CKHkS08CrumblyZoneMultiState_2.cpp - reconstructed original translation unit 0x4150b8-0x416710 (GAME_TOC1, main_toc1), 25 functions, 23 live.
// Primary class: CKHkS08CrumblyZoneMultiState  key 0x3582  category Hook  size 0xd4  vtable 0xb25bf8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4150b8  CKHkS08CrumblyZoneMultiState_Delete
//   [ ] 0x415108  CKHkS08CrumblyZoneMultiState_IsStateBitSet_maybe  [dead]
//   [x] 0x415168  CKHkS08CrumblyZoneMultiState_OnDeactivate
//   [x] 0x415190  CKHkS08CrumblyZoneMultiState_OnActivate
//   [x] 0x4151c8  CKHkS08CrumblyZoneMultiState_Stop
//   [x] 0x4151f0  CKHkS08CrumblyZoneMultiState_Restart
//   [x] 0x415218  CKHkS08CrumblyZoneMultiState_MessageProc  (inherited: the base's answer merged with 1 is the base's for 0..3)
//   [x] 0x415270  CKHkS08CrumblyZoneMultiState_GetInfo
//   [x] 0x4152c0  CKHkS08CrumblyZoneMultiState_PostLoad  (= CKHkCrumblyZoneMultiState::PostLoad, inherited)
//   [ ] 0x4152e8  CKHkS08CrumblyZoneMultiState_Save
//   [x] 0x415310  CKHkS08CrumblyZoneMultiState_RecursiveRegistration  (inherited: CKHkCrumblyZoneMultiState's)
//   [x] 0x415338  CKHkS08CrumblyZoneMultiState_DeleteArray
//   [x] 0x4153d8  CKHkS08CrumblyZoneMultiState_Create
//   [ ] 0x415498  RegisterCKHkS08CrumblyZoneMultiStateClass
//   [ ] 0x415520  _GLOBAL__D_415520
//   [ ] 0x415530  _GLOBAL__I_415530
//   [x] 0x415540  CKHkS08CrumblyZoneMultiState_Start
//   [ ] 0x415638  CKHkS08CrumblyZoneMultiState_SetStateBit_maybe  [dead]
//   [x] 0x415690  CKHkS08CrumblyZoneMultiState_vfF0
//   [x] 0x415740  CKHkS08CrumblyZoneMultiState_SpawnExplosionFx
//   [x] 0x4157b8  CKHkS08CrumblyZoneMultiState_Update
//   [x] 0x415b48  CKHkS08CrumblyZoneMultiState_GetHitDamage_maybe
//   [x] 0x415e70  CKHkS08CrumblyZoneMultiState_Destroy
//   [x] 0x415f30  CKHkS08CrumblyZoneMultiState_CreateArray
//   [x] 0x416080  CKHkS08CrumblyZoneMultiState_Load
//
//   [ ] 0x9c2b50  CKHkS08CrumblyZoneMultiState_IsKindOfClass  [inline]
//   [ ] 0x9c2bb0  CKHkS08CrumblyZoneMultiState_GetClassType  [inline]
//   [ ] 0x9c2bb8  CKHkS08CrumblyZoneMultiState_GetClassID  [inline]
//   [ ] 0x9c2bc0  CKHkS08CrumblyZoneMultiState_Destructor  [inline]
//   [ ] 0x9c2ce8  CKHkS08CrumblyZoneMultiState_DeletingDestructor  [inline]
#include "Spyro2008/hooks/CKHkS08CrumblyZoneMultiState.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/misc/Engine.h"

#include "k2000/io/IKFile.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/CKCrumblyZoneState.h"
#include "k2000/memory/Mem.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08Damage.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/ui/CKHkS08Bonus.h"
#include "crt/ppc_ops.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/CKGrpBonus.h"
#include "Renderware/rwcore/RwCamera.h"

namespace {

// The inlined TVector<T, 1> push of one element: grow to length + 1 when full, then bump the length.
// Returns the new element.
template <class T>
T* PushBack(TVector<T, 1>& v) {
    uint32_t used = v.m_ui32NbUsedElt;
    if (v.m_ui32NbElt == used) {
        uint32_t capacity = used + 1;
        if (capacity == 0) capacity = 1;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        used = v.m_ui32NbUsedElt;
        v.m_ui32NbElt = capacity;
    }
    v.m_ui32NbUsedElt = used + 1;
    return &v.m_pBlock[used];
}

// The Load's reset of a vector: capacity 1 and a fresh one-element block (the length is left alone).
template <class T>
void Reserve1(TVector<T, 1>& v) {
    v.m_ui32NbElt = 1;
    v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
}

}  // namespace

// 0x00416080 CKHkS08CrumblyZoneMultiState_Load
int32_t CKHkS08CrumblyZoneMultiState::Load(IKFile* file, int32_t type) {
    CKHkCrumblyZoneMultiState::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk8C);
    ReadU8(file, &m_unk9C);
    ReadF32LE(file, &m_fUnkA0);
    ReadF32LE(file, &m_fUnkA4);
    IKFile_ReadRef(file, &m_pUnkAC);
    // One count for the three vectors.
    uint32_t count = 0;
    ReadU32LE(file, &count);
    Reserve1(m_vUnkB0);
    for (uint32_t i = 0; i < count; ++i) ReadU8(file, PushBack(m_vUnkB0));
    IKFile_ReadRef(file, &m_pUnkBC);
    Reserve1(m_vUnk90);
    for (uint32_t i = 0; i < count; ++i) {
        StateEntry* entry = PushBack(m_vUnk90);
        ReadU32LE(file, &entry->m_unk0);
        for (uint8_t& b : entry->m_unk4) ReadU8(file, &b);
    }
    Reserve1(m_vUnkC0);
    for (uint32_t i = 0; i < count; ++i) ReadU8(file, PushBack(m_vUnkC0));
    ReadU8(file, &m_unkCC);
    ReadU8(file, &m_unkCD);
    ReadU32LE(file, &m_unkD0);
    return 1;
}

// 0x00415540 CKHkS08CrumblyZoneMultiState_Start
void CKHkS08CrumblyZoneMultiState::Start() {
    // 0x004122b8 CKHkCrumblyZoneMultiState_Start (k2000/hooks/CKHkCrumblyZoneMultiState.cpp, family hooks; local
    // copy): the states below +0x28 start with their +0x08 at 0, the others with +0x0c.
    // CKHkActorBase_d82_maybe_ResetRuntime 0x3f6e48: empty.
    for (uint32_t i = m_vUnk38.m_ui32NbUsedElt; i != 0; --i) {
        CKCrumblyZoneState* state = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[i - 1]);
        if (m_unk28 > i - 1) {
            state->m_unk08 = 0.0f;
        } else {
            state->m_unk08 = state->m_unk0c;
        }
    }
    // Every state's volumes get the damage object of +0x8c (0x4038f0 -> 0x1903c0, last to first).
    for (uint32_t i = m_vUnk38.m_ui32NbUsedElt; i != 0; --i) {
        CKCrumblyZoneState* state = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[i - 1]);
        c22spyro::VolumeArraySetDamage(static_cast<CKBoundingCpnt*>(state->m_pBoundingCpnt), m_pUnk8C);
    }
    // A boss zone joins the game manager's boss gauge lists (only for m_unkCC / m_unkCD; no LVL010 zone has them).
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    if (m_unkCC != 0) manager->RegisterBossGaugeZone(this);        // 0x004fe330
    if (m_unkCD != 0) manager->RegisterSecondBossGaugeZone(this);  // 0x004feba0
}

// 0x00415190 CKHkS08CrumblyZoneMultiState_OnActivate
void CKHkS08CrumblyZoneMultiState::VfA0() {
    CKHkCrumblyZoneMultiState::VfA0();  // 0x00412a78
    m_unkA8 = 0;
}

// 0x00415690 CKHkS08CrumblyZoneMultiState_vfF0
void CKHkS08CrumblyZoneMultiState::SetState(uint32_t state, uint8_t force, uint8_t sound) {
    CKHkCrumblyZoneMultiState::SetState(state, force, sound);  // 0x004120a0
    const float health = GetTotalHealth();  // 0x00413fe8 (asked whatever `sound`)
    if (health != 0.0f || sound == 0) return;  // TOC +0x4b88: 0.0f
    // The gem reward (+0xd0 gems) at the node's LTM position, around the shared y axis (0x00c50d40).
    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)
        ->SpawnGemReward(m_unkD0, reinterpret_cast<const CVector3*>(&frame->ltm.pos), &kAxisY);  // 0x004f8618
}

// 0x00415270 CKHkS08CrumblyZoneMultiState_GetInfo: CKHkCrumblyZoneMultiState's answer (2 kept, else 0 or 1).
int32_t CKHkS08CrumblyZoneMultiState::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkCrumblyZoneMultiState::GetInfo(info, request);
    if (base == 2) return 2;
    return base != 0 ? 1 : 0;
}

// 0x00415b48 CKHkS08CrumblyZoneMultiState_GetHitDamage_maybe (vt+0xf4)
float CKHkS08CrumblyZoneMultiState::GetHitDamage(IKBoundingVolume* volume, uint8_t touched) {
    CKS08Damage* damage = static_cast<CKS08Damage*>(volume->m_unk1c);
    if (damage == nullptr) return 0.0f;
    const StateEntry& entry = m_vUnk90.m_pBlock[m_unk28];
    bool hit = false;
    if (damage->IsKindOfClass(0x998c) != 0) {  // vt+0x08 CKS08HeroDamage
        if (touched == 0) return 0.0f;
        if (entry.m_unk4[4] != 0 && (damage->m_unk20 == 5 || volume->m_ui8OwnerType == 2)) {  // +0x08
            hit = true;
        } else {
            if (entry.m_unk4[0] == 0) return 0.0f;  // +0x04
            hit = true;
        }
    } else if (damage->IsKindOfClass(0x99cc) != 0) {  // CKS08ElementDamage
        if (damage->m_unk0c == 0 && touched == 0) return 0.0f;
        CKS08ElementDamage* element = static_cast<CKS08ElementDamage*>(damage);
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(volume->m_pOwner);  // +0x24
        if (element->m_unk38 == 5) {
            if (entry.m_unk4[2] != 0 && hero->GetEarthBoulderFlag2CC() != 0) hit = true;                // +0x06, 0x0032a840
            else if (entry.m_unk4[1] != 0 && hero->ShouldJoinPartnerFlightThunk() != 0) hit = true;  // +0x05, 0x0032a520
            else if (entry.m_unk4[3] != 0) hit = true;                                                // +0x07
        }
        if (!hit) {
            if ((ppc::slw(1u, damage->m_unk20) & entry.m_unk0) == 0) return 0.0f;
            hit = true;
        }
    } else if (damage->IsKindOfClass(0x970c) != 0) {  // CKS08SpyroDamage_maybe
        if (damage->m_unk0c != 0) return g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[0] * damage->m_unk04;
        if (touched == 0) return 0.0f;
        return damage->m_unk04;
    } else {
        return 0.0f;
    }
    (void)hit;
    if (damage->m_unk0c != 0) return g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[0] * damage->m_unk04;  // +0x48 -> +0x04 -> +0x1c
    return damage->m_unk04;
}

// 0x00415740 CKHkS08CrumblyZoneMultiState_SpawnExplosionFx (vt+0x104): with a game manager, its explosion 0 for the zone
// at the node's LTM position (CKS08GameManager_SpawnExplosionFx 0x004fbd70). Reached only by a hit that does not hurt
// (ApplyDamage with damage <= 0); no G frame runs it.
void CKHkS08CrumblyZoneMultiState::Vf104() {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    if (manager == nullptr) return;
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    const CVector3 position{frame->ltm.pos.x, frame->ltm.pos.y, frame->ltm.pos.z};
    manager->SpawnExplosionFx(this, 0, &position);  // 0x004fbd70
}

// 0x004157b8 CKHkS08CrumblyZoneMultiState_Update (vt+0x7c)
void CKHkS08CrumblyZoneMultiState::Update(IKTime* frameClock) {
    CKHkCrumblyZoneMultiState::Update(frameClock);  // 0x00411e78
    if (m_unk9C == 0 || m_vUnkB0.m_pBlock[m_unk28] == 0) return;
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    IKGrpHero* heroes = static_cast<IKGrpHero*>(manager->m_unk04[1]);
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    float best = 3.40282347e+38f;  // 0x00c4ace0
    CKHkS08Hero* feeder = nullptr;
    for (uint32_t dragon = 0; dragon < 2; ++dragon) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(heroes->m_apHeros[dragon]);  // 0x002ca080 GetHeroByDragonIndex
        const float* p = hero->GetPositionPtr();  // 0x00361968
        frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        float dy = p[1] - frame->ltm.pos.y;
        const float dx = p[0] - frame->ltm.pos.x;
        const float dz = p[2] - frame->ltm.pos.z;
        dy = dy * dy;
        const float d = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy));
        if (m_fUnkA0 * m_fUnkA0 > d) {  // bgt
            hero->m_unk1dd1 = 1;  // 0x0032a410 CKHkS08Hero_SetNearCrumblyZoneFlags_maybe
            hero->m_unk1dd0 = 1;
        }
        const bool nearer = dragon == 0 ? best > d : d < best;
        if (nearer && manager->GetDragonMana(static_cast<int32_t>(dragon)) != 0) {  // 0x004fd7c8
            best = d;
            feeder = hero;
        }
    }
    if (feeder == nullptr) return;
    if (!(m_fUnkA0 * m_fUnkA0 > best)) return;  // ble
    float timer = m_unkA8 + frameClock->m_afDeltaTime[0];
    m_unkA8 = timer;
    float period = m_fUnkA4;
    while (timer > period) {
        timer = timer - period;
        m_unkA8 = timer;
        CKGrpBonus* group = static_cast<CKGrpBonus*>(manager->m_unk04[3]);  // the game manager's +0x10
        if (group == nullptr) continue;
        feeder->GetDragonIndex();  // 0x00361960 (its answer only picks the same call)
        CVector3 at;
        static_cast<CSGHotSpot*>(feeder->GetHotSpot(5))->GetWorldPosition(&at);  // 0x00361b70, 0x000ce790
        const uint8_t dragon = feeder->GetDragonIndex();
        manager->ConsumeDragonMana(dragon, manager->GetBonusValue(2));  // 0x004fd808, 0x004f6b10
        if (CKSoundDictionaryID_GetSound(static_cast<CKSoundDictionaryID*>(m_pUnkBC), 0) != nullptr) {  // 0x00112bc0
            CKSound_Play(0.0f, CKSoundDictionaryID_GetSound(static_cast<CKSoundDictionaryID*>(m_pUnkBC), 0));  // 0x00111230
        }
        IKSerializable* bonus = group->SpawnBonusObject(2, &at, 0);  // 0x005b0df8 (TocBridge)
        if (bonus != nullptr) {
            // 0x005b7038 CKHkS08Bonus_InitSpawnedBonus_maybe: +0x35 = 0, then vt+0xe4 (it flies to the zone).
            static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40
            static_cast<CKHkS08Bonus*>(bonus)->m_unk35 = 0;
            static_cast<CKHkS08Bonus*>(bonus)->VfE4(&kAxisY, this);
        }
        timer = m_unkA8;
        period = m_fUnkA4;
    }
}

// 0x00415e70 CKHkS08CrumblyZoneMultiState_Destroy
void CKHkS08CrumblyZoneMultiState::Destroy() {
    CKHkCrumblyZoneMultiState::Destroy();
    if (m_vUnkB0.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vUnkB0.m_pBlock);
        m_vUnkB0.m_pBlock = nullptr;
    }
    m_vUnkB0.m_ui32NbUsedElt = 0;
    m_vUnkB0.m_pBlock = nullptr;
    if (m_vUnk90.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vUnk90.m_pBlock);
        m_vUnk90.m_pBlock = nullptr;
    }
    m_vUnk90.m_ui32NbUsedElt = 0;
    m_vUnk90.m_pBlock = nullptr;
    if (m_vUnkC0.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vUnkC0.m_pBlock);
        m_vUnkC0.m_pBlock = nullptr;
    }
    m_vUnkC0.m_ui32NbUsedElt = 0;
    m_vUnkC0.m_pBlock = nullptr;
}
