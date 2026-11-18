// CKHkTrackerManager.cpp - reconstructed original translation unit 0x451658-0x455dc0 (GAME_TOC1, main_toc1), 68 functions, 38 live.
// Primary class: CKHkTrackerManager  key 0xf42  category Hook  size 0x108  vtable 0xb26f78
// Other owners: CKSandal (7)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x451658  CKHkTrackerManager_UnassignAllHeroes_maybe  [dead]
//   [ ] 0x4516b0  CKHkTrackerManager_ReleaseTrack_maybe  [dead]
//   [ ] 0x451718  CKHkTrackerManager_CopyEntryByte9ToByte8_maybe  [dead]
//   [ ] 0x451768  CKHkTrackerManager_GetEntryType_maybe  [dead]
//   [x] 0x451790  CKHkTrackerManager_FreeBuffers_maybe  (CKHkTrackerManager::VfC0)
//   [ ] 0x4519d0  RegisterCKHkTrackerManagerClass
//   [ ] 0x451a48  _GLOBAL__I_451a48
//   [x] 0x451a58  CKHkTrackerManager_GetInfo
//   [x] 0x451aa8  CKHkTrackerManager_OnDeactivate  (inherited, CKHkActorBase's OnDeactivate)
//   [x] 0x451ad0  CKHkTrackerManager_Resume  (empty / no effect: inherited)
//   [x] 0x451af8  CKHkTrackerManager_Pause  (empty / no effect: inherited)
//   [x] 0x451b20  CKHkTrackerManager_SetDefaultState
//   [x] 0x451b68  CKHkTrackerManager_Restart
//   [x] 0x451b90  CKHkTrackerManager_Stop  (inherited, CKHkActorBase's Stop: empty)
//   [x] 0x451bb8  CKHkTrackerManager_Start
//   [x] 0x451be0  CKHkTrackerManager_PostLoad  (= the inherited slot)
//   [ ] 0x451c08  CKHkTrackerManager_Save
//   [x] 0x451c30  CKHkTrackerManager_RecursiveRegistration  (the actor base's (IKHook's): inherited)
//   [x] 0x451c58  CKHkTrackerManager_Destroy  (inherited, empty)
//   [x] 0x451c80  CKHkTrackerManager_Construct  [dead]
//   [ ] 0x451df0  CKHkTrackerManager_Construct_2  [dead]
//   [x] 0x451f60  CKHkTrackerManager_DeleteArray
//   [x] 0x452008  CKHkTrackerManager_BaseDestructor  (= ~CKHkTrackerManager)
//   [ ] 0x452280  CKHkTrackerManager_SetEntryFlagBit0_maybe  [dead]
//   [ ] 0x4522b8  CKHkTrackerManager_SetEntryFieldC_maybe  [dead]
//   [ ] 0x4522e0  CKHkTrackerManager_SetEntryFloat8_maybe  [dead]
//   [ ] 0x452308  CKHkTrackerManager_SetEntryField4_maybe  [dead]
//   [ ] 0x452330  CKHkTrackerManager_SetEntryType_maybe  [dead]
//   [ ] 0x452358  CKHkTrackerManager_IsEntryType5_maybe  [dead]
//   [ ] 0x4523a0  FUN_004523a0  [dead]
//   [ ] 0x452428  CKHkTrackerManager_GetEntryFieldC_maybe  [dead]
//   [ ] 0x452450  CKHkTrackerManager_GetEntryFloat8_maybe  [dead]
//   [ ] 0x452478  CKHkTrackerManager_GetEntryField4_maybe  [dead]
//   [ ] 0x4524a0  CKHkTrackerManager_SetEntryFlagBit4_maybe  [dead]
//   [ ] 0x452508  CKHkTrackerManager_SetEntryFlagBit3_maybe  [dead]
//   [ ] 0x452570  CKHkTrackerManager_SetEntryFlagBit2_maybe  [dead]
//   [ ] 0x4525b0  CKHkTrackerManager_SetEntryFlagBit1_maybe  [dead]
//   [ ] 0x4525f0  CKHkTrackerManager_GetEntryFlagBit0_maybe  [dead]
//   [ ] 0x452620  CKHkTrackerManager_GetEntryFlagBit4_maybe  [dead]
//   [ ] 0x452650  CKHkTrackerManager_GetEntryFlagBit3_maybe  [dead]
//   [ ] 0x452680  CKHkTrackerManager_GetEntryFlagBit2_maybe  [dead]
//   [ ] 0x4526b0  CKHkTrackerManager_GetEntryFlagBit1_maybe  [dead]
//   [x] 0x4526e0  CKHkTrackerManager_vfC8  (CKHkTrackerManager::ApplyStatePreset)
//   [x] 0x452720  CKHkTrackerManager_FilterCandidatesByCameraFrustum_maybe
//   [x] 0x452c40  CKHkTrackerManager_FilterCandidatesByDistance_maybe
//   [ ] 0x453068  FUN_00453068  [dead]
//   [ ] 0x4530d0  FUN_004530d0  [dead]
//   [ ] 0x453128  FUN_00453128  [dead]
//   [ ] 0x4531d0  FUN_004531d0  [dead]
//   [x] 0x453278  CKHkTrackerManager_OnActivate
//   [x] 0x453378  CKHkTrackerManager_MessageProc
//   [x] 0x4536e0  CKHkTrackerManager_DeletingDestructor  (= ~CKHkTrackerManager)
//   [x] 0x453968  CKHkTrackerManager_Destructor
//   [x] 0x453be0  CKHkTrackerManager_CreateArray
//   [x] 0x453dd8  CKHkTrackerManager_Create
//   [x] 0x453f68  CKHkTrackerManager_ApplyTrackFilterByType_maybe
//   [x] 0x454178  CKHkTrackerManager_PickTrackForHero_maybe
//   [x] 0x4544b8  CKHkTrackerManager_AssignHeroToTrack_maybe
//   [x] 0x454888  CKHkTrackerManager_Update
//   [x] 0x4552f0  CKHkTrackerManager_Load
//   [x] 0x455b58  CKSandal_Delete  (DOTD_DECLARE_FACTORIES in CKSandal.h; port-rest R06)
//   [x] 0x455ba8  CKSandal_UpdateCollision  (CKSandal::UpdateCollision, empty: CKSandal.h; R06)
//   [x] 0x455bb0  CKSandal_vf58  (CKSandal::IsDead, CKSandal.cpp; R06)
//   [x] 0x455be8  CKSandal_vf60  (CKSandal::KillProjectile, CKSandal.cpp; R06)
//   [x] 0x455c80  CKSandal_vf6C  (CKSandal::Vf6C, CKSandal.h; R06)
//   [x] 0x455cd0  CKSandal_vf7C  (CKSandal::Vf7C, returns 0: CKSandal.h; R06)
//   [x] 0x455cd8  CKSandal_vf80  (CKSandal::Vf80, returns 0: CKSandal.h; R06)
//   [ ] 0x455ce0  FUN_00455ce0  [dead]
//
//   [ ] 0x9c3dd8  CKHkTrackerManager_IsKindOfClass  [inline]
//   [ ] 0x9c3e30  CKHkTrackerManager_GetClassType  [inline]
//   [ ] 0x9c3e38  CKHkTrackerManager_GetClassID  [inline]
#include "k2000/hooks/CKHkTrackerManager.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/ai/CKDetectorBase.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "crt/ppc_ops.h"

#include <cfloat>

namespace {

// The TVector sizing the Load inlines: a count of 0 gives one allocated element and leaves the length
// alone; otherwise capacity = length = count (the grow branch after the allocation cannot run).
template <class T>
void LoadReserve(TVector<T, 1>& v, uint32_t count) {
    if (count == 0) {
        v.m_ui32NbElt = 1;
        v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
        return;
    }
    v.m_ui32NbElt = count;
    v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(T))));
    v.m_ui32NbUsedElt = count;
}

}  // namespace

// 0x004552f0 CKHkTrackerManager_Load. The three element loops run from the last element down.
int32_t CKHkTrackerManager::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_ui8NbRows);
    ReadU8(file, &m_ui8NbCols34);
    ReadU8(file, &m_ui8NbCols38);
    uint32_t n = static_cast<uint32_t>(m_ui8NbRows) * m_ui8NbCols34;
    m_apRefs34 = static_cast<IKSerializable**>(Mem_AllocAligned16(n * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apRefs34, n);
    n = static_cast<uint32_t>(m_ui8NbRows) * m_ui8NbCols38;
    m_apRefs38 = static_cast<IKSerializable**>(Mem_AllocAligned16(n * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apRefs38, n);
    for (Slot& slot : m_aSlots) {
        ReadU8(file, &slot.m_unkC);
        ReadF32LE(file, &slot.m_unk10);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        LoadReserve(slot.m_vRefValues, count);
        for (uint32_t i = count; i-- != 0;) {
            IKFile_ReadRef(file, &slot.m_vRefValues.m_pBlock[i].m_pRef);
            ReadU32LE(file, &slot.m_vRefValues.m_pBlock[i].m_unk4);
        }
        ReadU32LE(file, &count);
        LoadReserve(slot.m_vValuesRefs, count);
        for (uint32_t i = count; i-- != 0;) {
            ValuesRef& v = slot.m_vValuesRefs.m_pBlock[i];
            ReadU32LE(file, &v.m_unk0);
            ReadU32LE(file, &v.m_unk4);
            ReadF32LE(file, &v.m_unk8);
            IKFile_ReadRef(file, &v.m_pRef);
        }
    }
    uint32_t count = 0;
    ReadU32LE(file, &count);
    LoadReserve(m_vRefBytes, count);
    for (uint32_t i = count; i-- != 0;) {
        IKFile_ReadRef(file, &m_vRefBytes.m_pBlock[i].m_pRef);
        ReadU8(file, &m_vRefBytes.m_pBlock[i].m_unk9);
    }
    return 1;
}

// 0x00451b20 CKHkTrackerManager_SetDefaultState: bit 9 set.
void CKHkTrackerManager::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    m_bitArray = (m_bitArray & 0xfffffdffu) | 0x200u;
}

// C2.8 port-all P18.
// 0x00451a58 CKHkTrackerManager_GetInfo
int32_t CKHkTrackerManager::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    if (base == 2) return 2;
    return base == 0 ? 0 : 1;  // srawi / xor / subf / subi / rlwinm 1,31,31 / xori 1: |base| - 1 < 0
}

// C2.8 port-all P18.
// 0x004526e0 CKHkTrackerManager_vfC8
void CKHkTrackerManager::ApplyStatePreset(int32_t state) {
    if (state == 0) {
        m_bitArray = (m_bitArray & 0xfffffdffu) | 0x200u;
        return;
    }
    m_bitArray = m_bitArray & 0xfffffdffu;
}

// 0x00451bb8 CKHkTrackerManager_Start: CKHkActorBase_d82_maybe_ResetRuntime only.
void CKHkTrackerManager::Start() { CKHkActorBase::Start(); }

namespace {
using Candidate = CKHkTrackerManager::Candidate;

IKGrpHero* TrackerHeroGroup() { return static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]); }  // +0x08
CKHkS08Hero* HeroOf(IKSerializable* hero) { return static_cast<CKHkS08Hero*>(hero); }

// The global free-list pool of the candidate nodes (0x00ceaa20, its head +0x24; FreeListPool_Grow 0x244908 when empty).
// The nodes only live inside PickTrackForHero, so a native free list keeps the same behaviour.
Candidate* g_pFreeCandidates = nullptr;

Candidate* AllocCandidate() {
    Candidate* c = g_pFreeCandidates;
    if (c == nullptr) return new Candidate();  // 0x00244908 FreeListPool_Grow
    g_pFreeCandidates = c->m_pNext;
    return c;
}

void FreeCandidate(Candidate* c) {
    c->m_pNext = g_pFreeCandidates;
    g_pFreeCandidates = c;
}

// The list given back to the pool, then a single node {point, index} as the new list.
void ReplaceWithSingle(Candidate** list, int32_t point, int32_t index) {
    for (Candidate* c = *list; c != nullptr;) {
        Candidate* next = c->m_pNext;
        FreeCandidate(c);
        c = next;
    }
    *list = nullptr;
    Candidate* single = AllocCandidate();
    single->m_pNext = nullptr;
    single->m_i32Index = index;
    single->m_i32Point = point;
    single->m_pNext = *list;
    *list = single;
}

// The list walk of the filters: the nodes `keep` refuses are unlinked and freed.
template <class Keep>
void RemoveCandidates(Candidate** list, Keep keep) {
    Candidate* prev = nullptr;
    Candidate* c = *list;
    while (c != nullptr) {
        if (keep(c)) {
            prev = c;
            c = c->m_pNext;
            continue;
        }
        Candidate* next = c->m_pNext;
        if (*list == c) {
            prev = nullptr;
            FreeCandidate(c);
            *list = next;
        } else {
            prev->m_pNext = next;
            FreeCandidate(c);
        }
        c = next;
    }
}
}  // namespace

void CKHkTrackerManager::ReleasePointOf(uint32_t dragon) {
    for (uint32_t n = m_vRefBytes.m_ui32NbUsedElt; n != 0; --n) {
        RefByte& point = m_vRefBytes.m_pBlock[n - 1];
        if (static_cast<uint32_t>(point.m_i32Dragon) == dragon) {
            point.m_i32Dragon = -1;
            return;
        }
    }
}

// C2.8 port-all P18.
// 0x00453378 CKHkTrackerManager_MessageProc. Messages 0x996 / 0x997 then take the 0x9xx test too (their low bytes are below
// 0xaa: no effect).
int32_t CKHkTrackerManager::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    bool family9 = false;
    if (message == 0x996) {
        own = 0;
        m_bitArray = (m_bitArray & 0xfffffdffu) | 0x200u;
        family9 = true;
    } else if (message == 0x997) {
        if ((m_bitArray & 0x200u) != 0) {
            IKGrpHero* group = TrackerHeroGroup();  // engine -> game manager +0x8c -> +0x08
            for (uint32_t c = group->m_ui8CompanionHeroCount; c != 0; --c) {  // 0x002ca290 / 0x002ca0e8
                CKHkS08Hero* hero = HeroOf(group->m_apCompanionHeroes[c - 1]);
                if (hero->PassesTrackerAssignFlagChecks() != 0) continue;  // 0x00364268
                group->m_apCompanionHeroes[c - 1]->MessageProc(0xc3b, nullptr);  // vt+0x1c
                const uint32_t dragon = HeroOf(group->m_apCompanionHeroes[c - 1])->GetDragonIndex();  // 0x00361960
                m_aui8Track[dragon] = 6;
                ReleasePointOf(dragon);
            }
        }
        own = 0;
        m_bitArray = m_bitArray & 0xfffffdffu;
        family9 = true;
    } else if ((message >> 8) == 9) {
        family9 = true;
    }
    if (family9) {
        const uint32_t low = message & 0xffu;
        if (low > 0xa9 && low < m_vRefBytes.m_ui32NbUsedElt + 0xaa) {  // cmplwi / cmplw: unsigned
            own = 0;
            m_vRefBytes.m_pBlock[low - 0xaa].m_ui8Taken = *static_cast<const uint8_t*>(data);
            m_aui8Track[0] = 6;
            m_aui8Track[2] = 6;
            m_aui8Track[1] = 6;
        }
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x00453278 CKHkTrackerManager_OnActivate: the actor base's, no dragon inside or on a track (6), the track times zero,
// every track point free (-1), then each point's taken flag from its loaded byte (+0x9).
void CKHkTrackerManager::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    m_afTrackTime[0] = 0.0f;
    m_ui8InsideMask = 0;
    m_aui8Track[0] = 6;
    m_aui8Track[2] = 6;
    m_afTrackTime[2] = 0.0f;
    m_aui8Track[1] = 6;
    m_afTrackTime[1] = 0.0f;
    for (uint32_t n = m_vRefBytes.m_ui32NbUsedElt; n != 0; --n) m_vRefBytes.m_pBlock[n - 1].m_i32Dragon = -1;
    for (uint32_t n = m_vRefBytes.m_ui32NbUsedElt; n != 0; --n) {
        RefByte& point = m_vRefBytes.m_pBlock[n - 1];
        point.m_ui8Taken = point.m_unk9;
    }
}

// 0x00454888 CKHkTrackerManager_Update. Enabled (+0x0c bit 9): the track times grow, every detector of both grids runs
// (vt+0x50, last first; grid +0x34 / +0x38: column-major, entry dragon + column * rows). A companion (not dragon 2) whose
// bit is in the inside mask leaves it and every companion is sent off its track (message 0xc3b, track 6, point freed),
// every controlled hero's track dropped too. Then the controlled heroes (last first) in a zone of grid +0x34 (detection
// 1: inside) set their bit (`inA`), else of grid +0x38 (`inB`), else leaving one (detection 2) clears it (`left`; the
// three flags carry over to the next hero). Then each companion (last first): attached to something: no track; with
// `left`: sent off; else its track from its own zone in grid +0x34 (0 with inA, 3 with inB), else in grid +0x38 (1 / 4),
// else none of its zones (2 / 5).
void CKHkTrackerManager::Update(IKTime* clock) {
    // 0x003f6e68 WorldObjectBase_Update_Nop: the actor base's (empty).
    if ((m_bitArray & 0x200u) == 0) return;
    const uint8_t rows = m_ui8NbRows;
    IKGrpHero* group = TrackerHeroGroup();
    m_afTrackTime[2] = m_afTrackTime[2] + clock->m_afDeltaTime[0];
    m_afTrackTime[1] = m_afTrackTime[1] + clock->m_afDeltaTime[0];
    m_afTrackTime[0] = m_afTrackTime[0] + clock->m_afDeltaTime[0];
    for (uint32_t i = static_cast<uint32_t>(m_ui8NbCols34) * rows; i != 0; --i) {
        static_cast<CKDetectorBase*>(m_apRefs34[i - 1])->Detect();  // vt+0x50
    }
    for (uint32_t i = static_cast<uint32_t>(m_ui8NbCols38) * m_ui8NbRows; i != 0; --i) {
        static_cast<CKDetectorBase*>(m_apRefs38[i - 1])->Detect();
    }
    auto detector34 = [this](uint32_t dragon, uint32_t column) {
        return static_cast<CKDetectorBase*>(m_apRefs34[dragon + column * m_ui8NbRows]);
    };
    auto detector38 = [this](uint32_t dragon, uint32_t column) {
        return static_cast<CKDetectorBase*>(m_apRefs38[dragon + column * m_ui8NbRows]);
    };
    for (uint32_t c = group->m_ui8CompanionHeroCount; c != 0; --c) {  // 0x002ca290 / 0x002ca0e8
        const uint32_t dragon = HeroOf(group->m_apCompanionHeroes[c - 1])->GetDragonIndex();  // 0x00361960
        if (dragon == 2 || ((m_ui8InsideMask >> dragon) & 1u) == 0) continue;
        m_ui8InsideMask = static_cast<uint8_t>(m_ui8InsideMask & ~(1u << dragon));
        for (uint32_t k = group->m_ui8CompanionHeroCount; k != 0; --k) {
            const uint32_t other = HeroOf(group->m_apCompanionHeroes[k - 1])->GetDragonIndex();
            group->m_apCompanionHeroes[k - 1]->MessageProc(0xc3b, nullptr);  // vt+0x1c
            m_aui8Track[other] = 6;
            ReleasePointOf(other);
        }
        for (uint32_t k = group->m_ui8ControlledHeroCount; k != 0; --k) {  // 0x002ca288 / 0x002ca0e0
            const uint32_t other = HeroOf(group->m_apControlledHeroes[k - 1])->GetDragonIndex();
            m_aui8Track[other] = 6;
            ReleasePointOf(other);
        }
    }
    bool inA = false;
    bool inB = false;
    bool left = false;
    for (uint32_t c = group->m_ui8ControlledHeroCount; c != 0; --c) {
        const uint32_t dragon = HeroOf(group->m_apControlledHeroes[c - 1])->GetDragonIndex();
        const uint8_t bit = static_cast<uint8_t>(1u << dragon);
        for (uint32_t i = m_ui8NbCols34; i != 0; --i) {
            if (static_cast<uint8_t>(detector34(dragon, i - 1)->GetDetectionType(1)) == 0) continue;  // vt+0x54
            inA = true;
            m_ui8InsideMask = static_cast<uint8_t>((m_ui8InsideMask & ~bit) | bit);
        }
        if (inA) continue;
        for (uint32_t i = m_ui8NbCols38; i != 0; --i) {
            if (static_cast<uint8_t>(detector38(dragon, i - 1)->GetDetectionType(1)) == 0) continue;
            inB = true;
            m_ui8InsideMask = static_cast<uint8_t>((m_ui8InsideMask & ~bit) | bit);
        }
        if (inB) continue;
        for (uint32_t i = m_ui8NbCols34; i != 0; --i) {
            if (static_cast<uint8_t>(detector34(dragon, i - 1)->GetDetectionType(2)) == 0) continue;
            left = true;
            m_ui8InsideMask = static_cast<uint8_t>(m_ui8InsideMask & ~bit);
        }
        if (left) continue;
        for (uint32_t i = m_ui8NbCols38; i != 0; --i) {
            if (static_cast<uint8_t>(detector38(dragon, i - 1)->GetDetectionType(2)) == 0) continue;
            left = true;
            m_ui8InsideMask = static_cast<uint8_t>(m_ui8InsideMask & ~bit);
        }
    }
    for (uint32_t c = group->m_ui8CompanionHeroCount; c != 0; --c) {
        CKHkS08Hero* hero = HeroOf(group->m_apCompanionHeroes[c - 1]);
        const uint32_t dragon = hero->GetDragonIndex();
        if (HeroOf(group->m_apCompanionHeroes[c - 1])->GetAttachedObject() != nullptr) {  // 0x00361d50
            m_aui8Track[dragon] = 6;
            ReleasePointOf(dragon);
            continue;
        }
        if (left) {
            group->m_apCompanionHeroes[c - 1]->MessageProc(0xc3b, nullptr);
            m_aui8Track[dragon] = 6;
            ReleasePointOf(dragon);
            continue;
        }
        bool own = false;
        for (uint32_t i = m_ui8NbCols34; i != 0; --i) {
            if (static_cast<uint8_t>(detector34(dragon, i - 1)->GetDetectionType(1)) != 0) own = true;
        }
        if (own) {
            if (inA) {
                AssignHeroToTrack(0, dragon);
            } else if (inB) {
                AssignHeroToTrack(3, dragon);
            }
            continue;
        }
        own = false;
        for (uint32_t i = m_ui8NbCols38; i != 0; --i) {
            if (static_cast<uint8_t>(detector38(dragon, i - 1)->GetDetectionType(1)) != 0) own = true;
        }
        if (own) {
            if (inA) {
                AssignHeroToTrack(1, dragon);
            } else if (inB) {
                AssignHeroToTrack(4, dragon);
            }
        } else if (inA) {
            AssignHeroToTrack(2, dragon);
        } else if (inB) {
            AssignHeroToTrack(5, dragon);
        }
    }
}

// 0x004544b8 CKHkTrackerManager_AssignHeroToTrack_maybe. A dragon keeps its track while the track's time (+0x10, not 0)
// has not run out, and is not reassigned to the track it has. Otherwise a point is picked: none, the dragon (when the
// track has no +0x0c flag and the hero fails 0x364268, or the track has it and the hero fails 0x363ff8) is sent off
// (0xc3b / 0xc41, track 6, point freed); a point: the hero gets message 0xc3a (point word bit 3), 0xc4a (bit 4) or 0xc49
// with the point. Then the dragon's track is `track` and its time 0.
void CKHkTrackerManager::AssignHeroToTrack(uint32_t track, uint32_t dragon) {
    const uint8_t current = m_aui8Track[dragon];
    bool pick = false;
    if (current != 6) {
        const float limit = m_aSlots[current].m_unk10;
        if (limit != 0.0f && !(m_afTrackTime[dragon] < limit)) pick = true;  // bge: NaN picks
    }
    if (!pick && current == track) return;
    IKGrpHero* group = TrackerHeroGroup();
    int32_t chosen[2];
    PickTrackForHero(chosen, track, dragon);  // 0x00454178
    if (chosen[0] == -1) {
        auto sendOff = [&](uint16_t message) {
            group->m_apHeros[dragon & 0xffu]->MessageProc(message, nullptr);  // 0x002ca080, vt+0x1c
            m_aui8Track[dragon] = 6;
            ReleasePointOf(dragon);
        };
        if (m_aSlots[track].m_unkC == 0) {
            const CKHkS08Hero* hero = HeroOf(group->m_apHeros[dragon & 0xffu]);
            if (hero->PassesTrackerAssignFlagChecks() == 0) sendOff(0xc3b);  // 0x00364268
        }
        if (m_aSlots[track].m_unkC != 0) {
            const CKHkS08Hero* hero = HeroOf(group->m_apHeros[dragon & 0xffu]);
            if (hero->IsFlag35CBit6AndFlag3B0Bit6Clear() == 0) sendOff(0xc41);  // 0x00363ff8
        }
    } else {
        IKSerializable* hero = group->m_apHeros[dragon & 0xffu];
        const uint32_t word = m_aSlots[track].m_vRefValues.m_pBlock[chosen[1]].m_unk4;
        IKSerializable* point = m_vRefBytes.m_pBlock[chosen[0]].m_pRef;
        uint16_t message = 0xc49;
        if ((word & 8u) != 0) {
            message = 0xc3a;
        } else if ((word & 0x10u) != 0) {
            message = 0xc4a;
        }
        hero->MessageProc(message, &point);  // vt+0x1c, the point word on the stack
    }
    m_aui8Track[dragon] = static_cast<uint8_t>(track);
    m_afTrackTime[dragon] = 0.0f;
}

// 0x00454178 CKHkTrackerManager_PickTrackForHero_maybe. The dragon's track and point dropped; the candidates are the
// track's points (last first, so the list runs in the track's order) the dragon may take (word bit `dragon`) that are
// free and not taken; the track's filters narrow them while any is left; the first one left is given to the dragon.
void CKHkTrackerManager::PickTrackForHero(int32_t out[2], uint32_t track, uint32_t dragon) {
    m_aui8Track[dragon] = 6;
    ReleasePointOf(dragon);
    Slot& slot = m_aSlots[track];
    Candidate* list = nullptr;
    for (uint32_t i = slot.m_vRefValues.m_ui32NbUsedElt; i != 0; --i) {
        const RefValue& value = slot.m_vRefValues.m_pBlock[i - 1];
        if (value.m_pRef == nullptr) continue;
        int32_t point = static_cast<int32_t>(m_vRefBytes.m_ui32NbUsedElt);
        do {
            --point;
        } while (point >= 0 && m_vRefBytes.m_pBlock[point].m_pRef != value.m_pRef);
        if ((ppc::slw(1u, dragon) & value.m_unk4) == 0) continue;
        // BUG(original): a reference missing from the point list reads the entry before it (index -1); not done here.
        if (point < 0) continue;
        const RefByte& entry = m_vRefBytes.m_pBlock[point];
        if (entry.m_ui8Taken != 0 || entry.m_i32Dragon != -1) continue;
        Candidate* c = AllocCandidate();
        c->m_pNext = nullptr;
        c->m_i32Point = point;
        c->m_i32Index = static_cast<int32_t>(i - 1);
        c->m_pNext = list;
        list = c;
    }
    for (uint32_t u = 0; u < slot.m_vValuesRefs.m_ui32NbUsedElt && list != nullptr; ++u) {
        ApplyTrackFilterByType(&slot.m_vValuesRefs.m_pBlock[u], &list, dragon);  // 0x00453f68
    }
    if (list == nullptr) {
        out[0] = -1;
        out[1] = -1;
        return;
    }
    m_vRefBytes.m_pBlock[list->m_i32Point].m_i32Dragon = static_cast<int32_t>(dragon);
    out[0] = list->m_i32Point;
    out[1] = list->m_i32Index;
    for (Candidate* c = list; c != nullptr;) {
        Candidate* next = c->m_pNext;
        FreeCandidate(c);
        c = next;
    }
}

// 0x00453f68 CKHkTrackerManager_ApplyTrackFilterByType_maybe (the jump table at 0x00453fb8): 0 the distance to the first
// controlled hero, 1 to the hero `dragon`, 2 to the camera's position, 3 the camera frustum / view, 5 the distance to the
// reference's node (when set); 4 and the rest nothing.
void CKHkTrackerManager::ApplyTrackFilterByType(const ValuesRef* filter, Candidate** list, uint32_t dragon) {
    switch (filter->m_unk0) {
    case 0: {
        const float* p = HeroOf(TrackerHeroGroup()->m_apControlledHeroes[0])->GetPositionPtr();  // 0x002ca0e0, 0x00361968
        const float at[3] = {p[0], p[1], p[2]};
        FilterCandidatesByDistance(filter->m_unk8, at, filter->m_unk4, list);
        break;
    }
    case 1: {
        const float* p = HeroOf(TrackerHeroGroup()->m_apHeros[dragon & 0xffu])->GetPositionPtr();  // 0x002ca080
        const float at[3] = {p[0], p[1], p[2]};
        FilterCandidatesByDistance(filter->m_unk8, at, filter->m_unk4, list);
        break;
    }
    case 2: {
        const CVector3& c = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_v3RealPos;  // +0x598
        const float at[3] = {c.x, c.y, c.z};
        FilterCandidatesByDistance(filter->m_unk8, at, filter->m_unk4, list);
        break;
    }
    case 3:
        FilterCandidatesByCameraFrustum(filter->m_unk4, list);  // 0x00452720 (f1, the value, is not read)
        break;
    case 5: {
        if (filter->m_pRef == nullptr) break;
        const RwV3d& p = FrameLtm(static_cast<CSGMovable*>(static_cast<IKHook*>(filter->m_pRef)->m_pKGLObject)->m_pRwFrame)->pos;
        const float at[3] = {p.x, p.y, p.z};
        FilterCandidatesByDistance(filter->m_unk8, at, filter->m_unk4, list);
        break;
    }
    default:
        break;
    }
}

// 0x00452c40 CKHkTrackerManager_FilterCandidatesByDistance_maybe: the flat (x / z) distance of each candidate's point
// (CKMarkerBeacon +0x04) to `position`. Mode 0 keeps the nearer ones (limit > d), 2 the farther ones (d > limit; ble:
// a NaN drops); 1 keeps only the nearest (<=, the last of equals; from FLT_MAX), 3 only the farthest (>=, from 0).
void CKHkTrackerManager::FilterCandidatesByDistance(float limit, const float* position, uint32_t mode, Candidate** list) {
    auto distance = [&](const Candidate* c) {
        const CVector3& p = static_cast<CKMarkerBeacon*>(m_vRefBytes.m_pBlock[c->m_i32Point].m_pRef)->m_v3Position;
        const float dz = p.z - position[2];
        const float dx = p.x - position[0];
        return static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dx, dx, dz * dz)));  // 0x00010690
    };
    if (mode == 0) {
        RemoveCandidates(list, [&](const Candidate* c) { return limit > distance(c); });
        return;
    }
    if (mode == 2) {
        RemoveCandidates(list, [&](const Candidate* c) { return distance(c) > limit; });
        return;
    }
    if (mode != 1 && mode != 3) return;
    float best = mode == 1 ? FLT_MAX : 0.0f;  // the float at 0x00c4ace0 / TOC +0x550c
    // BUG(original): with no candidate passing (a NaN distance) the registers kept from before are used; 0 here.
    int32_t point = 0;
    int32_t index = 0;
    for (const Candidate* c = *list; c != nullptr; c = c->m_pNext) {
        const float d = distance(c);
        if (mode == 1 ? (d <= best) : (d >= best)) {  // cror: NaN skipped
            best = d;
            index = c->m_i32Index;
            point = c->m_i32Point;
        }
    }
    ReplaceWithSingle(list, point, index);
}

// 0x00452720 CKHkTrackerManager_FilterCandidatesByCameraFrustum_maybe: mode 0 keeps the points whose unit sphere the
// camera sees (CKSrvCamera_TestSphereAgainstFrustum, planes 5..0), 1 those it does not; 2 keeps only the point most in
// front of the camera (the largest dot of its unit direction with the camera's z axis, from -FLT_MAX), 3 the least
// (from FLT_MAX).
void CKHkTrackerManager::FilterCandidatesByCameraFrustum(uint32_t mode, Candidate** list) {
    const CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);  // +0x70
    auto visible = [&](const Candidate* c) {
        const CVector3& p = static_cast<CKMarkerBeacon*>(m_vRefBytes.m_pBlock[c->m_i32Point].m_pRef)->m_v3Position;
        const float sphere[4] = {p.x, p.y, p.z, 1.0f};  // TOC +0x54fc
        return camera->TestSphereAgainstFrustum(sphere, 5) != 0;  // 0x0012c830
    };
    if (mode == 0) {
        RemoveCandidates(list, [&](const Candidate* c) { return visible(c); });
        return;
    }
    if (mode == 1) {
        RemoveCandidates(list, [&](const Candidate* c) { return !visible(c); });
        return;
    }
    if (mode != 2 && mode != 3) return;
    float best = mode == 2 ? -FLT_MAX : FLT_MAX;
    const CVector3& axis = camera->m_v3RealAxisZ;  // +0x5c8
    const CVector3& eye = camera->m_v3RealPos;     // +0x598
    // BUG(original): with no candidate passing the registers kept from before are used; 0 here.
    int32_t point = 0;
    int32_t index = 0;
    for (const Candidate* c = *list; c != nullptr; c = c->m_pNext) {
        const CVector3& p = static_cast<CKMarkerBeacon*>(m_vRefBytes.m_pBlock[c->m_i32Point].m_pRef)->m_v3Position;
        float dy = p.y - eye.y;
        float dx = p.x - eye.x;
        float dz = p.z - eye.z;
        const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy))));
        if (length != 0.0f) {
            const float s = 1.0f / length;
            dz = dz * s;
            dx = dx * s;
            dy = dy * s;
        }
        const float dot = ppc::fmadds(axis.z, dz, ppc::fmadds(axis.x, dx, axis.y * dy));
        if (mode == 2 ? (dot > best) : (dot < best)) {  // ble / bge: NaN skipped
            best = dot;
            index = c->m_i32Index;
            point = c->m_i32Point;
        }
    }
    ReplaceWithSingle(list, point, index);
}

namespace {
template <class T>
void FreeTrackVector(TVector<T, 1>& vector) {
    if (vector.m_pBlock != nullptr) {
        Mem_FreeAligned16(vector.m_pBlock);  // 0x00052fb8
        vector.m_pBlock = nullptr;
    }
    vector.m_ui32NbUsedElt = 0;
    vector.m_pBlock = nullptr;
}
}  // namespace

// 0x00451790 CKHkTrackerManager_FreeBuffers_maybe
void CKHkTrackerManager::VfC0() {
    Mem_FreeAligned16(m_apRefs34);
    Mem_FreeAligned16(m_apRefs38);
    for (uint32_t i = 6; i != 0; --i) {
        FreeTrackVector(m_aSlots[i - 1].m_vRefValues);
        FreeTrackVector(m_aSlots[i - 1].m_vValuesRefs);
    }
}

// 0x00453968 CKHkTrackerManager_Destructor
CKHkTrackerManager::~CKHkTrackerManager() {
    FreeTrackVector(m_vRefBytes);
    for (uint32_t i = 6; i != 0; --i) {
        FreeTrackVector(m_aSlots[i - 1].m_vValuesRefs);
        FreeTrackVector(m_aSlots[i - 1].m_vRefValues);
    }
}
