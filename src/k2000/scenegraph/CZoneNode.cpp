// CZoneNode.cpp - reconstructed original translation unit 0xd3dd8-0xd4b30 (GAME_TOC1, main_toc1), 16 functions, 14 live.
// Primary class: CZoneNode  key 0x88b  category SceneNode  size 0x30  vtable 0xb18580
// Other owners: CSpawnAnimatedNode (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xd3dd8  CZoneNode_Delete
//   [ ] 0xd3e28  RegisterCZoneNodeClass
//   [ ] 0xd3ea0  _GLOBAL__I_d3ea0
//   [x] 0xd3eb0  CZoneNode_AddChild_maybe  (CSGBranch's AddChild, inherited)
//   [ ] 0xd3ed8  CZoneNode_IsPointOutsideAllVolumes_maybe  [dead]
//   [x] 0xd4068  CZoneNode_PostLoad  (= the inherited slot)
//   [x] 0xd4090  CZoneNode_Destroy
//   [x] 0xd40f0  CZoneNode_DeleteArray
//   [x] 0xd4198  CZoneNode_Create
//   [x] 0xd4208  CZoneNode_Load
//   [ ] 0xd4450  CZoneNode_Save
//   [x] 0xd4578  CZoneNode_RecursiveRegistration
//   [x] 0xd4628  CZoneNode_CreateArray
//   [x] 0xd4710  CZoneNode_Enqueue
//   [ ] 0xd49d0  FUN_000d49d0  [dead]
//   [x] 0xd4a60  CSpawnAnimatedNode_UpdateSharedAnim_maybe  (CSpawnAnimatedNode_UpdateSharedAnim, CZoneNode.h; its caller 0xd33d8 is F05's)
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

#include "k2000/graphical/memory/CKSpawnPool.h"
#include "k2000/misc/ISpawnNode.h"

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/graphical/CBackgroundManager.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CMultiGeometryBasic.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/math/Vec3.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGMovable.h"

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

// 0x000d4710 CZoneNode_Enqueue (from the assembly). The position is the IKCamera's (the camera context's +0x2c, through
// the graphic's renderer) frame's modelling position, read before the loop; the zone count is read again after every
// zone. A box zone (type 0) holds the position when every axis lies within [inf, sup] (x, then z, then y; a NaN fails,
// the fcmpu + cror tests); a sphere zone (type 1) through Vec3_IsWithinRadius 0x2441e8 (extent +0x10, squared radius
// +0x14). The first zone that holds it shows the node.
void CZoneNode::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                                 int32_t /*distanceCull*/) {
    CRenderer* renderer = g_pEngine->m_graphic->m_renderer;
    const CSGMovable* cameraObject = static_cast<const CSGMovable*>(renderer->m_cameraContext->m_pCamera);
    const RwV3d& position = cameraObject->m_pRwFrame->modelling.pos;
    const float point[3] = {position.x, position.y, position.z};
    uint32_t hidden = 4;
    for (uint32_t i = 0; i < m_ui32NbDetectors; ++i) {
        const CMultiGeometryBasic* zone = static_cast<const CMultiGeometryBasic*>(m_apDetectZone[i]);
        const uint32_t shape = zone->m_baData & 3;
        const float* s = zone->m_afShape;
        bool inside = false;
        if (shape == 0) {
            // The box: sup at +0x04..+0x0c, inf at +0x10..+0x18.
            inside = s[3] <= point[0] && s[0] >= point[0] && s[5] <= point[2] && s[2] >= point[2] && s[4] <= point[1] &&
                     point[1] <= s[1];
        } else if (shape == 1) {
            inside = Vec3_IsWithinRadius(s[3], s[4], s, point) != 0;
        }
        if (inside) {
            hidden = 0;
            break;
        }
    }
    m_sgProperties = (m_sgProperties & 0xfffffffbu) | hidden;
    if ((m_sgProperties & 0x1000) != 0) {
        // The sector's background root (the background manager's +0x18 entry, then its root node +0x00) takes the flag.
        // BUG(original): no range check (a node outside every sector would index -2), and a null entry or root node
        // writes address 0x10 (the entry's null test only replaces the root by 0). Here such a node changes nothing
        // (host guard: the PS3 would read past the array or write low memory).
        CBackgroundManager* backgrounds = static_cast<CBackgroundManager*>(renderer->m_backgroundManager);
        const uint32_t sector = GetSectorIndex();  // vt+0x6c
        CBackgroundData* data =
            backgrounds->m_apRootNode != nullptr && sector < backgrounds->m_ui8NbRootNode ? backgrounds->m_apRootNode[sector] : nullptr;
        CSGLeaf* root = data != nullptr ? static_cast<CSGLeaf*>(data->m_pRootNode) : nullptr;
        if (root != nullptr) root->m_sgProperties = (root->m_sgProperties & 0xfffffffbu) | hidden;
    }
    CNode::UpdateAndExtract(0.0f, stages, frameClock, camera, 0);  // 0x000cc160 (f1 TOC -0x52bc: 0.0f, r7 0)
}

// C2.8 port-all P11.

// 0x000d4090 CZoneNode_Destroy
void CZoneNode::Destroy() {
    CNode::Destroy();  // 0x000cbe10
    if (m_apDetectZone != nullptr) {
        Mem_FreeAligned16(m_apDetectZone);
        m_apDetectZone = nullptr;
    }
    m_ui32NbDetectors = 0;
    m_apDetectZone = nullptr;
}

// 0x000d4578 CZoneNode_RecursiveRegistration (the count read again each time)
void CZoneNode::RecursiveRegistration(int32_t type) {
    CNode::RecursiveRegistration(type);  // 0x000cbaa8: nothing
    if (type != 0) return;
    for (uint32_t i = 0; i < m_ui32NbDetectors; ++i) m_apDetectZone[i]->RecursiveRegistration(0);
}

// 0x000d4a60 CSpawnAnimatedNode_UpdateSharedAnim_maybe
void CSpawnAnimatedNode_UpdateSharedAnim(ISpawnNode* spawn, CAnimatedNode* node, RenderQueue** stages, IKTime* clock,
                                         int32_t* slot, float* sphere, float* worldSphere, RwCamera* camera) {
    int32_t at = *slot;
    if (at == -1) {
        at = static_cast<int32_t>(static_cast<CKSpawnPool*>(spawn->m_pSpawnPool)->AcquireAnimSlot());  // 0x000b6d00
        *slot = at;  // stw
    }
    static_cast<CKSpawnPool*>(spawn->m_pSpawnPool)
        ->UpdateAnimSlot(node, stages, clock, static_cast<uint32_t>(at), sphere, worldSphere, camera);  // 0x000b6f48
}
