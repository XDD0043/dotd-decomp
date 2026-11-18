// KBase1944.cpp - reconstructed original translation unit 0x443bb8-0x445dc8 (GAME_TOC1, main_toc1), 36 functions, 32 live.
// Primary owner: KBase1944 (not a registered class)
// Other owners: KBase42C2 (9), CKGrpS08SpawnableMushroom (6), SpawnableMushroom (4), CKHkPxObject (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x443bb8  KBase1944_CompareSpawnSlotsByFloat8_maybe
//   [x] 0x443be8  CKGrpS08SpawnableMushroom_vfB8  (returns 0xb: undeclared slot (IKBaseGroup models none; nothing ported calls it))
//   [x] 0x443bf0  CKGrpS08SpawnableMushroom_ReleaseMushroom_maybe
//   [x] 0x443c60  KBase1944_PostLoad
//   [x] 0x443d58  KBase1944_ResetRuntime_maybe
//   [x] 0x443dd8  CKGrpS08SpawnableMushroom_ForEachCurrentSectorBeacon_maybe
//   [ ] 0x443f78  CKGrpS08SpawnableMushroom_ConstructBase_2_maybe  [dead]
//   [x] 0x444040  CKGrpS08SpawnableMushroom_ConstructBase_maybe
//   [x] 0x444108  KBase1944_ResolveTriggerProperty  (returns 1: IKSerializable's GetInfo inherited)
//   [x] 0x444110  CKGrpS08SpawnableMushroom_HandleMessage_Base_maybe
//   [x] 0x444478  KBase1944_LevelReset  (IKGroup's only: IKBaseGroup::RecursiveRegistration inherited)
//   [ ] 0x4444a0  KBase1944_Save
//   [x] 0x4444c8  KBase1944_Load
//   [x] 0x4446b8  KBase1944_ClearReferences
//   [x] 0x444740  KBase1944_DeactivateAllSpawned_maybe
//   [x] 0x444920  KBase1944_ReinitRuntime
//   [x] 0x444a00  KBase1944_DeactivateAllSpawned_maybe
//   [x] 0x444a08  KBase1944_Update
//   [x] 0x445980  KStub_Nop_445980  (empty)
//   [x] 0x445988  KBase42C2_OnLevelExit_maybe
//   [x] 0x445990  KStub_Nop_445990  (empty: its call in CKHkS08SpawnableMushroom_Update is left out)
//   [x] 0x445998  SpawnableMushroom_SetSlotKey_maybe
//   [x] 0x4459c0  SpawnableMushroom_ClearSlotKey_maybe
//   [ ] 0x4459e0  SpawnableMushroom_HasSlotKey_maybe  [dead]
//   [x] 0x445a38  SpawnableMushroom_GetSlotKey_maybe
//   [x] 0x445a68  KBase42C2_PostLoad
//   [x] 0x445a90  KBase42C2_Load  (inline in the header)
//   [ ] 0x445bc8  KBase42C2_Save
//   [x] 0x445bf0  KBase42C2_LevelReset  (IKHook's: inherited)
//   [x] 0x445c18  KBase42C2_vf98
//   [x] 0x445c48  KBase42C2_vf94
//   [x] 0x445c70  KBase42C2_ResetRuntime_maybe
//   [x] 0x445ca0  KBase42C2_HandleMessage
//   [x] 0x445ca8  CKHkPxObject_Delete  (DOTD_DECLARE_FACTORIES(CKHkPxObject), k2000/hooks/CKHkPxObject.h)
//   [ ] 0x445cf8  FUN_00445cf8  [dead]
//   [ ] 0x445d80  FUN_00445d80  [dead]
//
//   [x] 0x9c3540  KBase1944_GetClassGroup  [inline]
//   [x] 0x9c3548  KBase1944_GetClassId  [inline]
//   [ ] 0x9c3558  KBase1944_vf70  [inline]
//   [ ] 0x9c3560  KBase1944_vf78  [inline]
//   [ ] 0x9c3568  KBase1944_vfF0  [inline]
//   [ ] 0x9c3570  KBase1944_vfF4  [inline]
//   [ ] 0x9c3578  KBase1944_vfFC  [inline]
//   [ ] 0x9c3580  KBase1944_vf100  [inline]
//   [ ] 0x9c3588  KBase1944_vf104  [inline]
//   [ ] 0x9c3590  KBase1944_vf108  [inline]
//   [ ] 0x9c3598  KBase1944_vf10C  [inline]
//   [ ] 0x9c37c8  KBase1944_IsKindOf  [inline]
//   [ ] 0x9c3868  KBase1944_DeletingDestructor  [inline]
//   [ ] 0x9c3940  KBase1944_Destructor  [inline]
//   [ ] 0x9c39e8  KBase42C2_IsKindOf  [inline]
//   [ ] 0x9c3a40  KBase42C2_GetClassGroup  [inline]
//   [ ] 0x9c3a48  KBase42C2_GetClassId  [inline]
//   [ ] 0x9c3a50  KBase42C2_vf70  [inline]
//   [ ] 0x9c3a58  KBase42C2_vf78  [inline]
//   [ ] 0x9c3a60  KBase42C2_vfF0  [inline]
//   [ ] 0x9c3a68  KBase42C2_Destructor  [inline]
//   [ ] 0x9c3a98  KBase42C2_DeletingDestructor  [inline]
#include "Spyro2008/groups/KBase1944.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/CKGrpMeca.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "crt/ppc_ops.h"
#include "crt/Ps3Qsort.h"
#include <vector>
#include <cstring>
#include <array>
#include "Spyro2008/groups/KBase42C2.h"

#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvBeacon.h"

// 0x00443c60 KBase1944_PostLoad. The block is allocated anew (the constructor's null block is not freed, as in the
// original); the length becomes +0x4c (Update empties it before use).
int32_t KBase1944::PostLoad(int32_t type) {
    PostLoadLife(type);  // 0x19f68
    if (type == K_LEVEL_PLATEFORMS && m_unk40 != 0 && m_unk48 != 0) {
        if (m_unk4c == 0) {
            m_vUnk50.m_ui32NbElt = 1;
            m_vUnk50.m_pBlock = static_cast<SpawnSlot*>(Mem_AllocAligned16(sizeof(SpawnSlot)));
        } else {
            m_vUnk50.m_ui32NbElt = m_unk4c;
            m_vUnk50.m_pBlock = static_cast<SpawnSlot*>(Mem_AllocAligned16(m_unk4c * static_cast<uint32_t>(sizeof(SpawnSlot))));
        }
        const uint32_t count = m_unk4c;
        if (m_vUnk50.m_ui32NbElt < count) {
            uint32_t capacity = count + 1;
            if (capacity == 0) capacity = 1;
            m_vUnk50.m_pBlock = static_cast<SpawnSlot*>(
                Mem_ReallocAligned16(m_vUnk50.m_pBlock, capacity * static_cast<uint32_t>(sizeof(SpawnSlot))));
            m_vUnk50.m_ui32NbElt = capacity;
        }
        m_vUnk50.m_ui32NbUsedElt = count;
    }
    return 1;
}

// 0x004444c8 KBase1944_Load
int32_t KBase1944::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LE(file, &m_unk2c);
        m_list.Load(file, K_LEVEL_PLATEFORMS);
        ReadU8(file, &m_unk40);
        ReadF32LE(file, &m_unk44);
        ReadU8(file, &m_unk48);
        ReadU32LE(file, &m_unk4c);
        ReadU8(file, &m_unk41);
    }
    return 1;
}

// 0x00444110 CKGrpS08SpawnableMushroom_HandleMessage_Base_maybe (KBase1944's vt+0x1c)
int32_t KBase1944::MessageProc(uint16_t message, void* data) {
    const uint32_t group = (message >> 8) & 0xffu;
    const uint32_t id = message & 0xffu;
    uint32_t handled = 0;
    if (group == 9) {
        if (id == 0x96) {
            m_unk5c = 1;
            handled = 1;
        } else if (id == 0x97) {
            m_unk5c = 0;
            handled = 1;
        }
    } else if (group == 0x10) {
        CKSrvBeacon::SKBeaconMsg* msg = static_cast<CKSrvBeacon::SKBeaconMsg*>(data);
        if (id == 1) {
            // The beacons of the set: three swapped 16-bit values and two bytes each.
            IKFile* file = msg->m_pFile;
            const CKSrvBeacon::CKBeaconSet* set = msg->m_pBeaconSet;
            while (msg->m_ui32NbBeacons-- != 0) {
                uint8_t* beacon = msg->m_pvBeacon;
                ++msg->m_ai16Accessor[3];
                msg->m_pvBeacon = beacon + set->m_ui8VolatileSizeBytes;
                uint16_t* values = reinterpret_cast<uint16_t*>(beacon);
                ReadU16LE(file, &values[0]);  // one 6-byte read, three halves swapped
                ReadU16LE(file, &values[1]);
                ReadU16LE(file, &values[2]);
                ReadRaw(file, beacon + 6, 2);
            }
            return 0;
        }
        if (id == 0) {
            // The save path: the same loop with Write. Each of the three half-words goes out as two bytes, low
            // first (the PS3 copies it to the stack and reverses it with lhbrx; here the value is already in
            // host order), then the two raw bytes.
            IKFile* file = msg->m_pFile;
            const CKSrvBeacon::CKBeaconSet* set = msg->m_pBeaconSet;
            while (msg->m_ui32NbBeacons-- != 0) {  // ends at 0xffffffff, as the original's
                const uint8_t* beacon = msg->m_pvBeacon;
                ++msg->m_ai16Accessor[3];
                msg->m_pvBeacon = msg->m_pvBeacon + set->m_ui8VolatileSizeBytes;
                file->Write(beacon, 2);  // vt+0x20
                file->Write(beacon + 2, 2);
                file->Write(beacon + 4, 2);
                file->Write(beacon + 6, 2);
            }
            return 0;
        }
        if (id < 4) {
            m_bitArray = (m_bitArray & ~0x20u) | 0x20u;
            handled = 1;
        }
    }
    return static_cast<int32_t>(handled ^ 1u);
}

// 0x00443d58 KBase1944_ResetRuntime_maybe (vt+0x50)
void KBase1944::Start() {
    m_unk5c = 1;
    if (VfF0() != 0) m_bitArray = (m_bitArray & 0xffffffdfu) | 0x20u;
}

// 0x00445c70 KBase42C2_ResetRuntime_maybe (vt+0x50): the scene object stays hidden/off (flag bit 2).
void KBase42C2::Start() {
    if (m_pKGLObject == nullptr) return;
    CSGLeaf* leaf = static_cast<CSGLeaf*>(m_pKGLObject);
    leaf->m_sgProperties = (leaf->m_sgProperties & 0xfffffffbu) | 4u;
}

namespace {
CKSrvBeacon* Beacons() { return static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon); }

// A beacon's position in tenths (three 16-bit values); the original reads the low addresses without one (DOTD: 0).
void BeaconPosition(const uint16_t* slot, float* out) {
    const uint8_t* data = Beacons()->GetBeaconData(slot);
    int16_t v[3] = {0, 0, 0};
    if (data != nullptr) std::memcpy(v, data, sizeof v);
    out[0] = static_cast<float>(static_cast<double>(v[0])) * 0.1f;  // TOC +0x51e4
    out[1] = static_cast<float>(static_cast<double>(v[1])) * 0.1f;
    out[2] = static_cast<float>(static_cast<double>(v[2])) * 0.1f;
}

// The slot key of a member (KBase42C2 +0x28: SpawnableMushroom_GetSlotKey_maybe 0x445a38 / _SetSlotKey_maybe 0x445998 /
// _ClearSlotKey_maybe 0x4459c0).
bool SameKey(const uint16_t* a, const uint16_t* b) { return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3]; }

// 0x00443bb8 KBase1944_CompareSpawnSlotsByFloat8_maybe
int CompareSlots(const void* a, const void* b) {
    const float fa = static_cast<const KBase1944::SpawnSlot*>(a)->m_fDistance;
    const float fb = static_cast<const KBase1944::SpawnSlot*>(b)->m_fDistance;
    if (fa < fb) return -1;
    if (fa > fb) return 1;
    return 0;
}

// 0x00244b90 PtrArray_PopBack_maybe: the last free member (the block's [0, +0x0c) part), null when none is left.
IKSerializable* PopFree(KObjectRefList& list) {
    if (list.m_ui32Count2 == 0) return nullptr;
    --list.m_ui32Count2;
    return list.m_pBlock[list.m_ui32Count2];
}

// 0x00244dc8 PtrArray_SwapIntoActivePartition_maybe: `member` (searched from +0x0c on, up to a null) swapped to the
// end of the free part, which grows by one (the original's three xor swaps).
void GiveBack(KObjectRefList& list, IKSerializable* member) {
    uint32_t i = list.m_ui32Count2;
    for (; i < list.m_ui32Count; ++i) {
        if (list.m_pBlock[i] == nullptr || list.m_pBlock[i] == member) break;
    }
    if (i != list.m_ui32Count2) {
        IKSerializable* t = list.m_pBlock[list.m_ui32Count2];
        list.m_pBlock[list.m_ui32Count2] = list.m_pBlock[i];
        list.m_pBlock[i] = t;
    }
    ++list.m_ui32Count2;
}
}  // namespace

// 0x00443dd8 CKGrpS08SpawnableMushroom_ForEachCurrentSectorBeacon_maybe
void KBase1944::VfF8() {
    CKSrvBeacon* beacons = Beacons();
    CKSrvBeacon::CKBeaconSet* list = beacons->BeginTypeIteration(VfEC(m_unk2c), g_pEngine->m_level->m_currentSector);
    while (CKSrvBeacon::CKBeaconSet* set = CKSrvBeacon::TakeNext(&list)) {
        uint16_t slot[4] = {set->m_aui16Accessor[0], set->m_aui16Accessor[1], set->m_aui16Accessor[2], 0xffff};
        const uint8_t* beacon = static_cast<const uint8_t*>(set->m_aBeacons);
        for (uint32_t i = 0; i < set->m_ui32NbBeacons; ++i) {
            ++slot[3];
            VfFC(slot, beacon);  // vt+0xfc
            beacon += set->m_ui8VolatileSizeBytes;
        }
    }
}

// 0x00444a08 KBase1944_Update
void KBase1944::Update(IKTime* /*clock*/) {
    CKGrpMeca* meca = static_cast<CKGrpMeca*>(g_pEngine->m_gameManager->m_unk04[2]);
    if ((meca->m_bitArray & 2u) != 0 || m_list.m_pHead == nullptr) return;
    if (static_cast<int8_t>(meca->m_unk32) > 1) VfF8();  // vt+0xf8
    float range2 = 0.0f;
    if (m_unk40 != 0) {
        range2 = m_unk44 * m_unk44;
        if (m_unk48 != 0) m_vUnk50.m_ui32NbUsedElt = 0;
    }
    CKCoreManager* core = g_pEngine->m_coreManager;
    CKSrvBeacon* beacons = Beacons();
    // The spawned members (the block from +0x0c to the count, up to a null), the last one first.
    std::vector<IKSerializable*> spawned;
    const uint32_t free = m_list.m_ui32Count2;
    for (uint32_t i = free; i != m_list.m_ui32Count && m_list.m_pBlock[i] != nullptr; ++i) {
        spawned.insert(spawned.begin(), m_list.m_pBlock[i]);
    }
    uint32_t kept = static_cast<uint32_t>(spawned.size());
    std::vector<std::array<uint16_t, 4>> fresh;  // the new slots, in order
    uint32_t added = 0;
    CKSrvBeacon::CKBeaconSet* outside = nullptr;
    CKSrvBeacon::CKBeaconSet* list = beacons->GatherBeaconsOfType(VfEC(m_unk2c), 7, &outside, nullptr);  // 0x00123b40
    // A slot either keeps its spawned member or, while members remain and it is free (Vf100), is taken.
    auto consider = [&](const uint16_t* slot) {
        for (auto it = spawned.begin(); it != spawned.end(); ++it) {
            if (free + kept <= added) return;
            if (SameKey(static_cast<KBase42C2*>(*it)->m_aUnk28, slot)) {
                spawned.erase(it);
                --kept;
                return;
            }
        }
        if (added < free + kept && Vf100(slot) != 0) {  // vt+0x100
            ++added;
            fresh.push_back({slot[0], slot[1], slot[2], slot[3]});
        }
    };
    while (CKSrvBeacon::CKBeaconSet* set = CKSrvBeacon::TakeNext(&list)) {
        uint16_t slot[4] = {set->m_aui16Accessor[0], set->m_aui16Accessor[1], set->m_aui16Accessor[2], 0xffff};
        const uint8_t* beacon = static_cast<const uint8_t*>(set->m_aBeacons);
        for (uint32_t i = 0; i < set->m_ui32NbBeacons; ++i, beacon += set->m_ui8VolatileSizeBytes) {
            ++slot[3];
            if ((m_bitArray & 0x20u) != 0) VfFC(slot, beacon);
            if (m_unk5c == 0 || !(added < free + kept)) continue;
            float distance = 0.0f;  // TOC +0x51b4
            if (m_unk40 != 0) {
                IKSerializable* heroes = g_pEngine->m_gameManager->m_unk04[1];
                float h[3];
                if (m_unk41 == 0 || heroes == nullptr) {
                    const CVector3& at = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera)->m_pCurrentCamera->m_WorldPosition;
                    h[0] = at.x;
                    h[1] = at.y;
                    h[2] = at.z;
                } else {
                    const float* at = static_cast<CKHkS08Hero*>(static_cast<IKGrpHero*>(heroes)->m_apControlledHeroes[0])->GetPositionPtr();
                    h[0] = at[0];
                    h[1] = at[1];
                    h[2] = at[2];
                }
                float b[3];
                BeaconPosition(slot, b);
                const float dy = h[1] - b[1];
                const float dx = h[0] - b[0];
                const float dz = h[2] - b[2];
                distance = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
                if (range2 < distance) continue;
            }
            if (Vf104(m_unk2c) != 0) {  // vt+0x104
                float sphere[5];
                BeaconPosition(slot, sphere);
                sphere[1] = sphere[1] + Vf10C(m_unk2c);  // vt+0x10c
                const float radius = Vf108(m_unk2c);    // vt+0x108
                sphere[3] = radius;
                sphere[4] = radius * radius;
                if (static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera)->TestSphereAgainstFrustum(sphere, 5) == 0) continue;
            }
            if (m_unk40 == 0 || m_unk48 == 0) {
                consider(slot);
            } else if (m_vUnk50.m_ui32NbUsedElt < m_unk4c) {
                if (m_vUnk50.m_ui32NbElt == m_vUnk50.m_ui32NbUsedElt) {
                    uint32_t capacity = m_vUnk50.m_ui32NbElt + 1;
                    if (capacity == 0) capacity = 1;
                    m_vUnk50.m_pBlock = static_cast<SpawnSlot*>(
                        Mem_ReallocAligned16(m_vUnk50.m_pBlock, capacity * static_cast<uint32_t>(sizeof(SpawnSlot))));
                    m_vUnk50.m_ui32NbElt = capacity;
                }
                SpawnSlot& entry = m_vUnk50.m_pBlock[m_vUnk50.m_ui32NbUsedElt++];
                std::memcpy(entry.m_aui16Key, slot, sizeof entry.m_aui16Key);
                entry.m_fDistance = distance;
            }
        }
    }
    if (m_unk40 != 0 && m_unk48 != 0) {
        Ps3Qsort(m_vUnk50.m_pBlock, m_vUnk50.m_ui32NbUsedElt, sizeof(SpawnSlot), CompareSlots);  // TocBridge_qsort
        for (uint32_t i = 0; i < m_vUnk50.m_ui32NbUsedElt; ++i) consider(m_vUnk50.m_pBlock[i].m_aui16Key);
    }
    if ((m_bitArray & 0x20u) != 0) {
        while (CKSrvBeacon::CKBeaconSet* set = CKSrvBeacon::TakeNext(&outside)) {
            uint16_t slot[4] = {set->m_aui16Accessor[0], set->m_aui16Accessor[1], set->m_aui16Accessor[2], 0xffff};
            const uint8_t* beacon = static_cast<const uint8_t*>(set->m_aBeacons);
            for (uint32_t i = 0; i < set->m_ui32NbBeacons; ++i, beacon += set->m_ui8VolatileSizeBytes) {
                ++slot[3];
                VfFC(slot, beacon);
            }
        }
    }
    for (IKSerializable* member : spawned) {
        if (static_cast<KBase1944Member*>(member)->VfF0() == 0) continue;  // vt+0xf0
        SetObjectActiveInContext(core, static_cast<IKLife*>(member), 0, this);  // 0x0001cb10
        KBase42C2* m = static_cast<KBase42C2*>(member);
        m->m_aUnk28[0] = 0xffff;
        m->m_aUnk28[3] = 0xffff;
        m->m_aUnk28[1] = 0xffff;
        m->m_aUnk28[2] = 0xffff;
        GiveBack(m_list, member);  // 0x00244dc8
    }
    for (const auto& slot : fresh) {
        IKSerializable* member = PopFree(m_list);  // 0x00244b90
        if (member == nullptr) break;
        std::memcpy(static_cast<KBase42C2*>(member)->m_aUnk28, slot.data(), 4 * sizeof(uint16_t));
        SetObjectActiveInContext(core, static_cast<IKLife*>(member), 1, this);
    }
    m_bitArray &= 0xffffffdfu;
}

// 0x00444740 KBase1944_DeactivateAllSpawned_maybe: the spawned members (the list's slots from its boundary +0x3c up to the
// count or the first null) gathered (the original pushes them on a FreeListPool list, so the last gathered comes first),
// then each one put to sleep in this group's bundle, its slot key cleared and given back to the list.
void KBase1944::DeactivateAllSpawned() {
    std::vector<IKSerializable*> spawned;
    for (uint32_t i = m_list.m_ui32Count2; i != m_list.m_ui32Count && m_list.m_pBlock[i] != nullptr; ++i) {
        spawned.push_back(m_list.m_pBlock[i]);
    }
    CKCoreManager* core = g_pEngine->m_coreManager;
    for (auto it = spawned.rbegin(); it != spawned.rend(); ++it) {
        IKSerializable* member = *it;
        SetObjectActiveInContext(core, static_cast<IKLife*>(member), 0, this);  // 0x0001cb10
        KBase42C2* m = static_cast<KBase42C2*>(member);  // SpawnableMushroom_ClearSlotKey_maybe 0x4459c0
        m->m_aUnk28[0] = 0xffff;
        m->m_aUnk28[3] = 0xffff;
        m->m_aUnk28[1] = 0xffff;
        m->m_aUnk28[2] = 0xffff;
        GiveBack(m_list, member);  // 0x00244dc8
    }
}

// 0x00443bf0 CKGrpS08SpawnableMushroom_ReleaseMushroom_maybe
void KBase1944::ReleaseMember(IKSerializable* member) {
    SetObjectActiveInContext(g_pEngine->m_coreManager, static_cast<IKLife*>(member), 0, this);  // 0x0001cb10
    KBase42C2* m = static_cast<KBase42C2*>(member);  // SpawnableMushroom_ClearSlotKey_maybe 0x4459c0
    m->m_aUnk28[0] = 0xffff;
    m->m_aUnk28[3] = 0xffff;
    m->m_aUnk28[1] = 0xffff;
    m->m_aUnk28[2] = 0xffff;
    GiveBack(m_list, member);  // 0x00244dc8
}

// 0x00444920 KBase1944_ReinitRuntime (vt+0x54): +0x5c set, every spawned member put back, and with vt+0xf0 and vt+0xf4
// both answering yes the flag bit 5 (spawn again).
void KBase1944::Restart() {
    m_unk5c = 1;
    DeactivateAllSpawned();
    if (VfF0() != 0 && VfF4() != 0) m_bitArray = (m_bitArray & 0xffffffdfu) | 0x20u;
}

// 0x00445c48 KBase42C2_vf94
void KBase42C2::Vf94() {
    if (m_pKGLObject == nullptr) return;
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties &= ~4u;
}

// 0x00445c18 KBase42C2_vf98
void KBase42C2::Vf98() {
    if (m_pKGLObject == nullptr) return;
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties |= 4u;
}

// 0x004446b8 KBase1944_Destroy
void KBase1944::Destroy() {
    m_lChilds = nullptr;
    *GetMemberListHead() = nullptr;  // vt+0xb0
    if (m_vUnk50.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vUnk50.m_pBlock);
        m_vUnk50.m_pBlock = nullptr;
    }
    m_vUnk50.m_ui32NbUsedElt = 0;
    m_vUnk50.m_pBlock = nullptr;
}
