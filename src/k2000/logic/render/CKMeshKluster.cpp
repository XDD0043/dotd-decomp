// CKMeshKluster.cpp - reconstructed original translation unit 0x31308-0x326b8 (GAME_TOC1, main_toc1), 16 functions, 14 live.
// Primary class: CKMeshKluster  key 0x108c  category Logic  size 0x3c  vtable 0xb14138
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x31308  CKMeshKluster_Delete
//   [x] 0x31358  CKMeshKluster_vf54  (header: SectorUnload_maybe (vt+0x54))
//   [x] 0x31368  CKMeshKluster_RecursiveRegistration  (IKSerializable's: returns 1)
//   [x] 0x31370  CKMeshKluster_PostLoad  (IKSerializable's: returns 1)
//   [ ] 0x31378  RegisterCKMeshKlusterClass
//   [ ] 0x313f0  _GLOBAL__I_313f0
//   [ ] 0x31400  CKMeshKluster_BuildSortedFlaggedList_maybe  [dead]
//   [x] 0x314c8  CKMeshKluster_Destroy
//   [x] 0x31570  CKMeshKluster_DeleteArray
//   [x] 0x31618  CKMeshKluster_Create
//   [x] 0x31658  CKMeshKluster_CreateArray
//   [ ] 0x31700  CKMeshKluster_UpdateDynamicGrounds_2  [dead]
//   [ ] 0x318b8  CKMeshKluster_Save
//   [x] 0x31df8  CKMeshKluster_Load
//   [x] 0x32328  CKMeshKluster_UpdateDynamicGrounds
//   [x] 0x324e0  CKMeshKluster_RebuildActiveGroundList_maybe
//
//   [ ] 0x993fd0  CKMeshKluster_GetClassType  [inline]
//   [ ] 0x993fd8  CKMeshKluster_GetClassID  [inline]
//   [ ] 0x993fe0  CKMeshKluster_GetSerializationFlags  [inline]
//   [x] 0x993fe8  SortCompare_Float28Descending_maybe  [inline]
//   [ ] 0x994018  CKMeshKluster_IsKindOfClass  [inline]
//   [ ] 0x994038  CKMeshKluster_Destructor  [inline]
//   [ ] 0x994050  CKMeshKluster_DeletingDestructor  [inline]
#include "k2000/logic/render/CKMeshKluster.h"

#include "crt/Ps3Qsort.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/ICollisionMesh.h"

namespace {

IKSerializable** AllocRefs(uint16_t count) {
    if (count == 0) return nullptr;
    return static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
}

// One reference read per element (the original's loop, not the array read).
void ReadRefs(IKFile* file, IKSerializable** refs, uint16_t count) {
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadObjectRef(file, &refs[i]);
}

// 0x00993fe8 SortCompare_Float28Descending_maybe: the grounds by the bottom of their boxes (+0x28), highest first; equal
// or unordered: 0.
int CompareGroundBottoms(const void* a, const void* b) {
    const float first = static_cast<const ICollisionMesh*>(*static_cast<IKSerializable* const*>(a))->m_AABB[4];
    const float second = static_cast<const ICollisionMesh*>(*static_cast<IKSerializable* const*>(b))->m_AABB[4];
    if (first < second) return 1;
    if (first > second) return -1;
    return 0;
}

}  // namespace

// 0x00031df8 CKMeshKluster_Load
int32_t CKMeshKluster::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_BBox), 6);
    ReadU16LE(file, &m_ui16NbGround);
    ReadU16LE(file, &m_ui16NbWall);
    ReadU16LE(file, &m_ui16NbCollisionMesh);
    m_apGround = AllocRefs(m_ui16NbGround);
    m_apWall = AllocRefs(m_ui16NbWall);
    m_apCollisionMesh = AllocRefs(m_ui16NbCollisionMesh);
    ReadRefs(file, m_apGround, m_ui16NbGround);
    ReadRefs(file, m_apWall, m_ui16NbWall);
    ReadRefs(file, m_apCollisionMesh, m_ui16NbCollisionMesh);
    m_ui8UpdateIndex = 0;
    IKFile_ReadRef(file, &m_pNext);
    m_apActiveGround = nullptr;
    m_apActiveGround = AllocRefs(m_ui16NbGround);
    m_ui16NbActiveGround = 0;
    return 1;
}

// 0x00032328 CKMeshKluster_UpdateDynamicGrounds
void CKMeshKluster::UpdateDynamicGrounds(IKTime* /*frameClock*/) {
    m_ui8UpdateIndex = m_ui8UpdateIndex == 0 ? 1 : 0;  // (index - 1) >> 63 in 64 bits
    for (uint32_t i = 0; i < m_ui16NbGround; ++i) {
        static_cast<ICollisionMesh*>(m_apGround[i])->Update(m_ui8UpdateIndex);  // vt+0x5c
    }
    bool sort = true;
    if ((g_pEngine->m_level->m_ba8GroundStateFlags & 1) != 0) {
        m_ui16NbActiveGround = 0;
        sort = m_ui16NbGround != 0;
        IKSerializable** active = m_apActiveGround;
        for (uint32_t i = 0; i < m_ui16NbGround; ++i) {
            if ((static_cast<ICollisionMesh*>(m_apGround[i])->m_ba16EngineFlags & 1) != 0) {
                *active++ = m_apGround[i];
                ++m_ui16NbActiveGround;
            }
        }
    }
    // Sorted every frame (also when the list was not rebuilt). The element is a pointer (4 bytes on the PS3).
    if (sort && m_ui16NbActiveGround > 1) {
        Ps3Qsort(m_apActiveGround, m_ui16NbActiveGround, static_cast<uint32_t>(sizeof(IKSerializable*)), CompareGroundBottoms);
    }
    // The walls' Update (vt+0x5c) with the same index. No level of the game has a CWall or CDynamicWall (C2.9).
    if (m_ui16NbWall != 0) DOTD_STUB_ONCE("CKMeshKluster_UpdateDynamicGrounds: walls (no CWall in the game's files; C2.9)");
}

// 0x000324e0 CKMeshKluster_RebuildActiveGroundList_maybe
void CKMeshKluster::SectorLoaded_maybe(int32_t /*sector*/) {
    CKLevel* level = g_pEngine->m_level;
    level->m_ba8GroundStateFlags = static_cast<uint8_t>((level->m_ba8GroundStateFlags & 0xfe) | 1);
    UpdateDynamicGrounds(nullptr);
}

// 0x000314c8 CKMeshKluster_Destroy
void CKMeshKluster::Destroy() {
    if (m_apGround != nullptr) {
        Mem_FreeAligned16(m_apGround);
        m_apGround = nullptr;
    }
    if (m_apWall != nullptr) {
        Mem_FreeAligned16(m_apWall);
        m_apWall = nullptr;
    }
    if (m_apCollisionMesh != nullptr) {
        Mem_FreeAligned16(m_apCollisionMesh);
        m_apCollisionMesh = nullptr;
    }
    if (m_apActiveGround != nullptr) {
        Mem_FreeAligned16(m_apActiveGround);
        m_apActiveGround = nullptr;
    }
}
