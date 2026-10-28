// CKHkTransportableObjectSpawner.cpp - reconstructed original translation unit 0x4a8688-0x4ac108 (GAME_TOC1, main_toc1), 45 functions, 39 live.
// Primary class: CKHkTransportableObjectSpawner  key 0x3042  category Hook  size 0x78  vtable 0xb28920
// Other owners: CKHkS08TransportableBase (5), CKHkS08TransportableKey (2), CKGrpTransportableObject (1), KBase3002 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4a8688  FUN_004a8688  [dead]
//   [ ] 0x4a8700  CKHkTransportableObjectSpawner_ApplyStatePreset_maybe
//   [ ] 0x4a8730  RegisterCKHkTransportableObjectSpawnerClass
//   [ ] 0x4a87a8  _GLOBAL__I_4a87a8
//   [x] 0x4a87b8  CKHkTransportableObjectSpawner_SetDefaultState
//   [ ] 0x4a87f0  CKHkTransportableObjectSpawner_IsPlayerHeroInRange_maybe
//   [ ] 0x4a8988  CKGrpTransportableObject_SortEntries_maybe  [dead]
//   [ ] 0x4a89c8  CKHkTransportableObjectSpawner_Resume
//   [ ] 0x4a89f0  CKHkTransportableObjectSpawner_Pause
//   [ ] 0x4a8a18  CKHkTransportableObjectSpawner_Stop
//   [ ] 0x4a8a40  CKHkTransportableObjectSpawner_GetInfo
//   [ ] 0x4a8a90  CKHkTransportableObjectSpawner_MessageProc
//   [ ] 0x4a8b80  CKHkTransportableObjectSpawner_Save
//   [ ] 0x4a8ba8  CKHkTransportableObjectSpawner_RecursiveRegistration
//   [x] 0x4a8bd0  CKHkTransportableObjectSpawner_Construct  [dead]
//   [ ] 0x4a8c40  CKHkTransportableObjectSpawner_Construct_2  [dead]
//   [x] 0x4a8cb0  CKHkTransportableObjectSpawner_DeleteArray
//   [ ] 0x4a8d58  CKHkTransportableObjectSpawner_Destroy
//   [ ] 0x4a8de8  CKHkTransportableObjectSpawner_LevelResetEntryObjects_maybe  [dead]
//   [ ] 0x4a8e78  CKHkTransportableObjectSpawner_SaveSpawnEntries_maybe  [dead]
//   [ ] 0x4a8fc8  CKHkTransportableObjectSpawner_OnDeactivate
//   [ ] 0x4a9230  CKHkTransportableObjectSpawner_Restart
//   [ ] 0x4a9510  CKHkTransportableObjectSpawner_OnActivate
//   [x] 0x4a9950  CKHkTransportableObjectSpawner_Start
//   [x] 0x4a9b08  CKHkTransportableObjectSpawner_LoadSpawnEntries_maybe
//   [ ] 0x4a9d08  CKHkTransportableObjectSpawner_BaseDestructor
//   [ ] 0x4a9da8  CKHkTransportableObjectSpawner_DeletingDestructor
//   [ ] 0x4a9e58  CKHkTransportableObjectSpawner_Destructor
//   [ ] 0x4a9ef8  CKHkTransportableObjectSpawner_PostLoad
//   [ ] 0x4a9f80  CKHkTransportableObjectSpawner_TrySpawn_maybe
//   [ ] 0x4aa490  CKHkTransportableObjectSpawner_TrySpawnOntoReceiver_maybe
//   [x] 0x4aad40  CKHkTransportableObjectSpawner_CreateArray
//   [x] 0x4aae38  CKHkTransportableObjectSpawner_Create
//   [x] 0x4aaeb8  CKHkTransportableObjectSpawner_Load
//   [ ] 0x4ab368  CKHkTransportableObjectSpawner_CanSpawnNow_maybe
//   [ ] 0x4ab500  CKHkTransportableObjectSpawner_CanSpawnAtTime_maybe
//   [ ] 0x4ab6d0  CKHkTransportableObjectSpawner_Update
//   [ ] 0x4abfb0  CKHkS08TransportableBase_3002_maybe_GetOwnerSpawner_maybe
//   [ ] 0x4abfb8  CKHkS08TransportableBase_3002_maybe_SetOwnerSpawner_maybe
//   [ ] 0x4abfc0  CKHkS08TransportableBase_3002_maybe_Update
//   [ ] 0x4abfe8  CKHkS08TransportableKey_BaseResume_maybe
//   [ ] 0x4ac010  CKHkS08TransportableKey_BasePause_maybe
//   [ ] 0x4ac038  CKHkS08TransportableBase_3002_maybe_OnLevelExit
//   [x] 0x4ac060  CKHkS08TransportableBase_3002_maybe_ResetRuntime
//   [x] 0x4ac0c8  KBase3002_PostLoad
//
//   [ ] 0x9c5210  CKHkTransportableObjectSpawner_IsKindOfClass  [inline]
//   [ ] 0x9c5268  CKHkTransportableObjectSpawner_GetClassType  [inline]
//   [ ] 0x9c5270  CKHkTransportableObjectSpawner_GetClassID  [inline]
#include "k2000/hooks/CKHkTransportableObjectSpawner.h"

#include "Renderware/rpmatfx/RpMatFX.h"
#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"
#include "Spyro2008/misc/CKHkS08TransportableBase.h"

namespace {

// The CVector3 globals the Load passes (initialised at run time; their live values, as in
// CLightComponent.cpp and CKExplosionFxData.cpp).
const CVector3 kVectorAxisZ = {0.0f, 0.0f, 1.0f};  // 0x00c50d4c
const CVector3 kVectorAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40

}  // namespace

// 0x004a9b08 CKHkTransportableObjectSpawner_LoadSpawnEntries_maybe: a count, then one reference per
// entry, each pushed onto +0x40 (reset to capacity 1 first; the old block is not freed).
void CKHkTransportableObjectSpawner::LoadSpawnEntries(IKFile* file) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    m_vSpawnEntries.m_ui32NbElt = 1;
    m_vSpawnEntries.m_pBlock = static_cast<SpawnEntry**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(SpawnEntry*))));
    for (uint32_t i = 0; i < count; ++i) {
        SpawnEntry* entry = new SpawnEntry;
        entry->m_pUnk0 = nullptr;
        entry->m_unk4 = 0;
        entry->m_unk8 = 0;
        IKFile_ReadRef(file, &entry->m_pUnk0);
        entry->m_unk4 = 0;
        entry->m_unk8 = 0;
        const uint32_t used = m_vSpawnEntries.m_ui32NbUsedElt;
        if (m_vSpawnEntries.m_ui32NbElt == used) {
            uint32_t capacity = used + 1;
            if (capacity == 0) capacity = 1;
            m_vSpawnEntries.m_pBlock = static_cast<SpawnEntry**>(Mem_ReallocAligned16(
                m_vSpawnEntries.m_pBlock, capacity * static_cast<uint32_t>(sizeof(SpawnEntry*))));
            m_vSpawnEntries.m_ui32NbElt = capacity;
        }
        m_vSpawnEntries.m_pBlock[m_vSpawnEntries.m_ui32NbUsedElt] = entry;
        m_vSpawnEntries.m_ui32NbUsedElt += 1;
    }
}

// 0x004aaeb8 CKHkTransportableObjectSpawner_Load
int32_t CKHkTransportableObjectSpawner::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_pMatrix = RwMatrixCreate_Thunk();
    CVector3 pos;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&pos), 3);
    // The inlined identity (RwMatrixSetIdentity), then the position; the identity flag is cleared.
    CMatrix34* m = m_pMatrix;
    m->m_ui32Flags = 0x20003u;
    m->m_right.x = 1.0f;
    m->m_right.z = 0.0f;
    m->m_right.y = 0.0f;
    m->m_pos.x = 0.0f;
    m->m_up.y = 1.0f;
    m->m_up.x = 0.0f;
    m->m_at.y = 0.0f;
    m->m_at.x = 0.0f;
    m->m_up.z = 0.0f;
    m->m_pos.z = 0.0f;
    m->m_pos.y = 0.0f;
    m->m_at.z = 1.0f;
    m->m_pos.z = pos.z;
    m->m_pos.x = pos.x;
    m->m_pos.y = pos.y;
    m->m_ui32Flags &= 0xfffdffffu;
    Mat4_SetBasisFromAtUp(m_pMatrix, &kVectorAxisZ, &kVectorAxisY);
    IKFile_ReadRef(file, &m_unk5c);
    ReadU32LE(file, &m_unk4c);
    ReadU32LE(file, &m_unk50);
    LoadSpawnEntries(file);
    IKFile_ReadRef(file, &m_unk64);
    ReadU32LE(file, &m_unk3c);
    ReadU8(file, &m_unk68);
    IKFile_ReadRef(file, &m_unk6c);
    ReadU32LE(file, &m_unk74);
    ReadU8(file, &m_unk25);
    IKFile_ReadRef(file, &m_unk20);
    ReadU8(file, &m_unk69);
    return 1;
}

// 0x004a87b8 CKHkTransportableObjectSpawner_SetDefaultState
void CKHkTransportableObjectSpawner::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    m_unk24 = 1;
}

// 0x004a9950 CKHkTransportableObjectSpawner_Start. The current entry is the group's entry m_unk3c. The +0x2c
// vector is resized to m_unk4c elements unless its length already equals the word at +0x58 (a first start
// allocates a one-element block, then grows it to m_unk4c); the spawn entries' two words and the vector's
// elements are cleared, then the counters.
void CKHkTransportableObjectSpawner::Start() {
    CKHkActorBase::Start();
    m_pCurrentEntry = static_cast<CKGrpTransportableObject*>(m_unk64)->m_vEntries.m_pBlock[m_unk3c];
    bool resize = false;
    if (m_vUnk2c.m_pBlock == nullptr) {
        m_vUnk2c.m_ui32NbElt = 1;
        m_vUnk2c.m_pBlock = static_cast<void**>(Mem_AllocAligned16(4));
        resize = true;
    } else if (m_vUnk2c.m_ui32NbUsedElt != m_unk54[1]) {
        resize = true;
    }
    if (resize) {
        const uint32_t count = m_unk4c;
        if (m_vUnk2c.m_ui32NbElt < count) {
            uint32_t capacity = count + 1;
            uint32_t bytes = capacity * 4;
            if (capacity == 0) {
                capacity = 1;
                bytes = 4;
            }
            m_vUnk2c.m_pBlock = static_cast<void**>(Mem_ReallocAligned16(m_vUnk2c.m_pBlock, bytes));
            m_vUnk2c.m_ui32NbElt = capacity;
        }
        m_vUnk2c.m_ui32NbUsedElt = count;
    }
    for (uint32_t i = 0; i < m_vSpawnEntries.m_ui32NbUsedElt; ++i) {
        m_vSpawnEntries.m_pBlock[i]->m_unk8 = 0;
        m_vSpawnEntries.m_pBlock[i]->m_unk4 = 0;
    }
    for (uint32_t i = 0; i < m_vUnk2c.m_ui32NbUsedElt; ++i) m_vUnk2c.m_pBlock[i] = nullptr;
    m_unk70 = 0;
    m_unk54[0] = 0;
    m_unk28 = 0;
    m_unk54[1] = 0;
}

// 0x004ac060 CKHkS08TransportableBase_3002_maybe_ResetRuntime (the base's Start, in the spawner's unit):
// CKHkActorBase_d82_maybe_ResetRuntime (empty), +0x25 = 1, +0x28 = 0, then vt+0x144 with 0.
void CKHkS08TransportableBase::Start() {
    CKHkActorBase::Start();
    m_unk25 = 1;
    m_unk28 = 0;
    SetFlag2C(0);
}
