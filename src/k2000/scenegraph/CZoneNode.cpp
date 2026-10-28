// CZoneNode.cpp - reconstructed original translation unit 0xd3dd8-0xd4b30 (GAME_TOC1, main_toc1), 16 functions, 14 live.
// Primary class: CZoneNode  key 0x88b  category SceneNode  size 0x30  vtable 0xb18580
// Other owners: CSpawnAnimatedNode (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xd3dd8  CZoneNode_Delete
//   [ ] 0xd3e28  RegisterCZoneNodeClass
//   [ ] 0xd3ea0  _GLOBAL__I_d3ea0
//   [ ] 0xd3eb0  CZoneNode_AddChild_maybe
//   [ ] 0xd3ed8  CZoneNode_IsPointOutsideAllVolumes_maybe  [dead]
//   [ ] 0xd4068  CZoneNode_PostLoad
//   [ ] 0xd4090  CZoneNode_Destroy
//   [x] 0xd40f0  CZoneNode_DeleteArray
//   [x] 0xd4198  CZoneNode_Create
//   [x] 0xd4208  CZoneNode_Load
//   [ ] 0xd4450  CZoneNode_Save
//   [ ] 0xd4578  CZoneNode_RecursiveRegistration
//   [x] 0xd4628  CZoneNode_CreateArray
//   [ ] 0xd4710  CZoneNode_Enqueue
//   [ ] 0xd49d0  FUN_000d49d0  [dead]
//   [ ] 0xd4a60  CSpawnAnimatedNode_UpdateSharedAnim_maybe
//
//   [ ] 0x9a2cc8  CZoneNode_IsKindOfClass  [inline]
//   [ ] 0x9a2d20  CZoneNode_GetClassType  [inline]
//   [ ] 0x9a2d28  CZoneNode_GetClassID  [inline]
//   [ ] 0x9a2d30  CZoneNode_Destructor  [inline]
//   [ ] 0x9a2da0  CZoneNode_DeletingDestructor  [inline]
//   [ ] 0x9a2e18  IKBoundingBox_IsKindOf  [inline]
//   [ ] 0x9a2e60  IKBoundingBox_GetClassGroup  [inline]
//   [ ] 0x9a2e68  IKBoundingBox_GetClassId  [inline]
#include "k2000/scenegraph/CZoneNode.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x000d4208 CZoneNode_Load
int32_t CZoneNode::Load(IKFile* file, int32_t type) {
    CNode::Load(file, type);  // 0xcbd28
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint8_t bit = 0;
    ReadRaw(file, &bit, 1);
    m_sgProperties = (m_sgProperties & 0xffffefffu) | (static_cast<uint32_t>(bit) << 12);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        // The block keeps room for two; the size is not touched.
        m_ui32Capacity = 2;
        m_apDetectZone = static_cast<IKSerializable**>(Mem_AllocAligned16(2 * sizeof(IKSerializable*)));
        return 1;
    }
    m_ui32Capacity = count;
    m_apDetectZone = static_cast<IKSerializable**>(Mem_AllocAligned16(count * sizeof(IKSerializable*)));
    // (The original's growth path, Mem_ReallocAligned16 when the capacity is below the count, cannot run
    // here: the capacity was just set to the count.)
    m_ui32NbDetectors = count;
    IKFile_ReadObjectRefArray(file, m_apDetectZone, count);
    return 1;
}
