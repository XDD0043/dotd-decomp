// KBase1944.cpp - reconstructed original translation unit 0x443bb8-0x445dc8 (GAME_TOC1, main_toc1), 36 functions, 32 live.
// Primary owner: KBase1944 (not a registered class)
// Other owners: KBase42C2 (9), CKGrpS08SpawnableMushroom (6), SpawnableMushroom (4), CKHkPxObject (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x443bb8  KBase1944_CompareSpawnSlotsByFloat8_maybe
//   [ ] 0x443be8  CKGrpS08SpawnableMushroom_vfB8
//   [ ] 0x443bf0  CKGrpS08SpawnableMushroom_ReleaseMushroom_maybe
//   [ ] 0x443c60  KBase1944_PostLoad
//   [x] 0x443d58  KBase1944_ResetRuntime_maybe
//   [ ] 0x443dd8  CKGrpS08SpawnableMushroom_ForEachCurrentSectorBeacon_maybe
//   [ ] 0x443f78  CKGrpS08SpawnableMushroom_ConstructBase_2_maybe  [dead]
//   [x] 0x444040  CKGrpS08SpawnableMushroom_ConstructBase_maybe
//   [ ] 0x444108  KBase1944_ResolveTriggerProperty
//   [x] 0x444110  CKGrpS08SpawnableMushroom_HandleMessage_Base_maybe
//   [ ] 0x444478  KBase1944_LevelReset
//   [ ] 0x4444a0  KBase1944_Save
//   [x] 0x4444c8  KBase1944_Load
//   [ ] 0x4446b8  KBase1944_ClearReferences
//   [ ] 0x444740  KBase1944_DeactivateAllSpawned_maybe
//   [ ] 0x444920  KBase1944_ReinitRuntime
//   [ ] 0x444a00  KBase1944_DeactivateAllSpawned_maybe
//   [ ] 0x444a08  KBase1944_Update
//   [ ] 0x445980  KStub_Nop_445980
//   [ ] 0x445988  KBase42C2_OnLevelExit_maybe
//   [ ] 0x445990  KStub_Nop_445990
//   [ ] 0x445998  SpawnableMushroom_SetSlotKey_maybe
//   [ ] 0x4459c0  SpawnableMushroom_ClearSlotKey_maybe
//   [ ] 0x4459e0  SpawnableMushroom_HasSlotKey_maybe  [dead]
//   [ ] 0x445a38  SpawnableMushroom_GetSlotKey_maybe
//   [ ] 0x445a68  KBase42C2_PostLoad
//   [ ] 0x445a90  KBase42C2_Load
//   [ ] 0x445bc8  KBase42C2_Save
//   [ ] 0x445bf0  KBase42C2_LevelReset
//   [ ] 0x445c18  KBase42C2_vf98
//   [ ] 0x445c48  KBase42C2_vf94
//   [x] 0x445c70  KBase42C2_ResetRuntime_maybe
//   [ ] 0x445ca0  KBase42C2_HandleMessage
//   [ ] 0x445ca8  CKHkPxObject_Delete
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
#include "Spyro2008/groups/KBase42C2.h"

#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvBeacon.h"

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
        if (id == 0) return 0;  // STUB(C2.2): writes the beacons (the save path)
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
