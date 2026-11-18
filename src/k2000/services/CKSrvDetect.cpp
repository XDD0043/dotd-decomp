// CKSrvDetect.cpp - reconstructed original translation unit 0x1a6b70-0x1a8120 (GAME_TOC1, main_toc1), 50 functions, 47 live.
// Primary class: CKSrvDetect  key 0x4c1  category Service  size 0x18  vtable 0xb1c2a0
// Other owners: GroundContact (3), CKSectorDetector (3), CCollisionMeshBase (2), ICollisionMesh (1), CDynamicWall (1), DetectorList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a6b70  ICollisionMesh_SetActive
//   [x] 0x1a6ba8  ICollisionMesh_GetMeshSlotIndex_maybe
//   [x] 0x1a6bb8  KStub_Nop_1a6bb8  (CGround::MyDestroy: empty)
//   [x] 0x1a6bc0  CDynamicWall_UpdateQuadtreeBounds_maybe  (CDynamicWall::UpdateQuadtreeBounds; CDynamicWall_RefreshTransform_maybe 0x1a3970.. calls it)
//   [ ] 0x1a6c28  FUN_001a6c28  [dead]
//   [ ] 0x1a6c40  KStub_Return1_1a6c40  [left: save-only: called only by the meshes' Save functions (CCollisionMesh_Save, CGround_Save, CWall_Save), which are out of scope]
//   [x] 0x1a6c48  ICollisionMesh_vf24  (ICollisionMesh's RecursiveRegistration: returns 1, registers nothing: the default)
//   [x] 0x1a6c50  ICollisionMesh_Destroy
//   [x] 0x1a6c90  ICollisionMesh_Load
//   [x] 0x1a7090  GroundContact_GetTriangle_maybe
//   [x] 0x1a70e0  GroundContact_GetWorldPoint
//   [x] 0x1a71d8  GroundContact_GetWorldNormal_maybe
//   [x] 0x1a72b0  CKSrvDetect_Delete
//   [ ] 0x1a7300  FUN_001a7300  [dead]
//   [x] 0x1a7310  CKSrvDetect_DestroyService
//   [ ] 0x1a7318  CKSrvDetect_Save
//   [x] 0x1a7320  CKSrvDetect_Start
//   [x] 0x1a7330  CKSrvDetect_SectorLoaded  (SectorLoaded: empty, the IKUpdatable default)
//   [x] 0x1a7338  CKSrvDetect_Restart  (Restart, CKSrvDetect.h)
//   [x] 0x1a7348  CKSrvDetect_BeginCinematic_maybe
//   [ ] 0x1a7358  FUN_001a7358  [dead]
//   [x] 0x1a7378  CKSrvDetect_Pause
//   [x] 0x1a7380  CKSrvDetect_Stop
//   [x] 0x1a7388  CKSrvDetect_Resume
//   [ ] 0x1a7390  RegisterCKSrvDetectClass
//   [ ] 0x1a7408  _GLOBAL__I_1a7408
//   [ ] 0x1a7418  CKSrvDetect_RefreshAllPositions_maybe  [dead: no pointer to its descriptor 0xb6bf50]
//   [x] 0x1a7488  CKSrvDetect_PreSectorLoaded
//   [x] 0x1a7508  CKSrvDetect_PostLoad  (= the inherited slot)
//   [x] 0x1a7530  CKSrvDetect_Destroy
//   [x] 0x1a7580  CKSrvDetect_Construct
//   [x] 0x1a75f8  CKSrvDetect_Construct_2  (the not-in-charge copy of the constructor 0x1a7580: CKSrvDetect())
//   [x] 0x1a7670  CKSrvDetect_DeleteArray
//   [x] 0x1a7718  CKSrvDetect_RecursiveRegistration
//   [x] 0x1a77e8  CKSrvDetect_SetDefaultState
//   [x] 0x1a7860  CKSrvDetect_SectorUnload
//   [x] 0x1a78e0  CKSrvDetect_Load
//   [x] 0x1a7a68  CKSrvDetect_InitializeService
//   [x] 0x1a7a80  CKSrvDetect_CreateArray
//   [x] 0x1a7b98  CKSrvDetect_Create
//   [x] 0x1a7c30  UpdateCKSrvDetect
//   [x] 0x1a7d08  CKSrvDetect_EndCinematic_maybe
//   [x] 0x1a7d90  CKSrvDetect_UpdateInitialize
//   [x] 0x1a7e58  CKSrvDetect_DeletingDestructor  (~CKSrvDetect + delete)
//   [x] 0x1a7ec0  CKSrvDetect_Destructor  (~CKSrvDetect)
//   [x] 0x1a7f20  CKSrvDetect_Destructor_2  (~CKSrvDetect)
//   [x] 0x1a7f80  CKSectorDetector_Delete  (DOTD_DECLARE_FACTORIES(CKSectorDetector))
//   [x] 0x1a7fd0  CKSectorDetector_RecursiveRegistration
//   [ ] 0x1a8088  CKSectorDetector_Save
//   [x] 0x1a8090  DetectorList_ResetEnabledToDefault_maybe
//
//   [ ] 0x991238  ICollisionMesh_vf14  [inline]
//   [ ] 0x991240  ICollisionMesh_vf18  [inline]
//   [ ] 0x991248  ICollisionMesh_GetSerializationFlags  [inline]
//   [ ] 0x991840  ICollisionMesh_vf8  [inline]
//   [ ] 0x9921a8  ICollisionMesh_DeletingDestructor  [inline]
//   [ ] 0x992240  ICollisionMesh_vf0  [inline]
//   [ ] 0x9aae68  CKSrvDetect_IsKindOfClass  [inline]
//   [ ] 0x9aaea0  CKSrvDetect_GetClassType  [inline]
//   [ ] 0x9aaea8  CKSrvDetect_GetClassID  [inline]
#include "k2000/services/CKSrvDetect.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/ai/CKDetectedMovable.h"
#include "k2000/logic/ai/CKDetectorBase.h"
#include "k2000/logic/ai/CKSectorDetector.h"
#include "k2000/system/IKTime.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/misc/Mat4.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/logic/CDynamicWall.h"
#include "k2000/misc/CKQuadtreeAgent.h"

// 0x001a7580 CKSrvDetect_Construct (the same stores inlined in 0x1a7b98 CKSrvDetect_Create).
CKSrvDetect::CKSrvDetect() {
    m_ui32Priority = 0x7b;
    Engine_SetSrvDetect(this);
    m_unk14 = 0;
}

// 0x001a7530 CKSrvDetect_Destroy: the detected-movable array freed (the count is kept).
void CKSrvDetect::Destroy() {
    if (m_apDetectedMovable != nullptr) {
        Mem_FreeAligned16(m_apDetectedMovable);
        m_apDetectedMovable = nullptr;
    }
}

// 0x001a78e0 CKSrvDetect_Load: a count, then the detected-movable references.
int32_t CKSrvDetect::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32NbDetectedMovable);
    if (m_ui32NbDetectedMovable == 0) {
        m_apDetectedMovable = nullptr;
        return 1;
    }
    m_apDetectedMovable = static_cast<IKSerializable**>(
        Mem_AllocAligned16(m_ui32NbDetectedMovable * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apDetectedMovable, m_ui32NbDetectedMovable);
    return 1;
}

// C2.1 (family scene): the collision meshes' base Load.

// 0x001a6c90 ICollisionMesh_Load: the counts, the triangles (after the vertices in the caller's buffer),
// the vertices, the box, the flags, then the two references. No type check.
int32_t ICollisionMesh::Load(IKFile* file, int32_t /*type*/) {
    ReadU16LE(file, &m_ui16NbTriangle);
    ReadU16LE(file, &m_ui16NbVertex);
    m_aTriangle = reinterpret_cast<CCollisionTriangle*>(reinterpret_cast<uint8_t*>(m_aVertex) + m_ui16NbVertex * 0xcu);
    {
        uint16_t* half = m_aTriangle->m_aui16Index;
        const uint32_t count = m_ui16NbTriangle * 3u;
        file->Read(half, m_ui16NbTriangle * 6u);
        for (uint32_t i = 0; i < count; ++i) {
            const uint8_t* b = reinterpret_cast<const uint8_t*>(half + i);
            half[i] = static_cast<uint16_t>(b[0] | (b[1] << 8));
        }
    }
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_aVertex), m_ui16NbVertex * 3u);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_AABB), 6);
    ReadU16LE(file, &m_ui16PropertiesFlags);
    ReadU16LE(file, &m_ba16EngineFlags);
    ReadRaw(file, &m_ui8Type, 1);
    IKFile_ReadRef(file, &m_unk04);
    IKFile_ReadRef(file, &m_pSector);
    m_ui16LastRayID = 0;
    return 1;
}

// 0x001a7488 CKSrvDetect_PreSectorLoaded
void CKSrvDetect::PreSectorLoaded(int32_t sector) {
    for (uint32_t i = 0; i < m_ui32NbDetectedMovable; ++i) {
        static_cast<CKDetectedMovable*>(m_apDetectedMovable[i])->ActivateSector(sector);
    }
}

// 0x001a8090 DetectorList_ResetEnabledToDefault_maybe
static void DetectorList_ResetEnabledToDefault(CKSectorDetector* list) {
    for (uint32_t i = 0; i < list->m_ui32NbDetector; ++i) {
        CKDetectorBase* detector = static_cast<CKDetectorBase*>(list->m_apDetector[i]);
        detector->SetEnabled((detector->m_baData >> 5) & 1u);  // vt+0x58
    }
}

// 0x001a7ec0 CKSrvDetect_Destructor (0x1a7f20 / 0x1a7e58 the same)
CKSrvDetect::~CKSrvDetect() { Engine_SetSrvDetect(nullptr); }

// 0x001a7718 CKSrvDetect_RecursiveRegistration (the sector count read once)
void CKSrvDetect::RecursiveRegistration(int32_t type) {
    if (type != 4) return;
    CKLevel* level = g_pEngine->m_level;
    const uint32_t count = level->m_ui32NbSectors;
    for (uint32_t i = 0; i != count; ++i) {
        CKSectorDetector* list = static_cast<CKSector*>(level->m_vpSectors.m_pBlock[i])->m_pSectorDetector;
        if (list == nullptr) continue;  // DOTD guard (the original dereferences it), as SetDefaultState
        list->RecursiveRegistration(4);  // vt+0x24 0x001a7fd0
    }
}

// 0x001a7fd0 CKSectorDetector_RecursiveRegistration (the count read again each time)
void CKSectorDetector::RecursiveRegistration(int32_t type) {
    if (type != 4) return;
    for (uint32_t i = 0; i < m_ui32NbDetector; ++i) m_apDetector[i]->RecursiveRegistration(4);  // vt+0x24
}

// 0x001a77e8 CKSrvDetect_SetDefaultState
void CKSrvDetect::SetDefaultState(int32_t /*flag*/) {
    CKLevel* level = g_pEngine->m_level;
    for (uint32_t i = 0; i < level->m_ui32NbSectors; ++i) {
        CKSectorDetector* list = static_cast<CKSector*>(level->m_vpSectors.m_pBlock[i])->m_pSectorDetector;
        if (list == nullptr) continue;  // DOTD guard (the original dereferences it)
        DetectorList_ResetEnabledToDefault(list);
    }
}

// 0x001a7d90 CKSrvDetect_UpdateInitialize
void CKSrvDetect::UpdateInitialize() {
    CKLevel* level = g_pEngine->m_level;
    for (uint32_t i = 0; i < level->m_ui32NbSectors; ++i) {
        CKSectorDetector* list = static_cast<CKSector*>(level->m_vpSectors.m_pBlock[i])->m_pSectorDetector;
        if (list == nullptr) continue;  // DOTD guard (the original dereferences it), as in SetDefaultState
        list->ClearDetectionFlags();  // 0x1a8518
    }
    for (uint32_t i = 0; i < m_ui32NbDetectedMovable; ++i) {
        static_cast<CKDetectedMovable*>(m_apDetectedMovable[i])->RefreshDetectablePositions();  // 0x1ab068
    }
}

// 0x001a7860 CKSrvDetect_SectorUnload
void CKSrvDetect::SectorUnload(int32_t sector) {
    for (uint32_t i = 0; i < m_ui32NbDetectedMovable; ++i) {
        static_cast<CKDetectedMovable*>(m_apDetectedMovable[i])->DeactivateSector(sector);
    }
}

// 0x001a7c30 UpdateCKSrvDetect
void CKSrvDetect::Update(IKTime* time) {
    if (time->m_eCurrentState != 0 || m_unk14 != 0) return;
    CKLevel* level = g_pEngine->m_level;
    for (CKSector* sector = level->IterateActiveSectors(nullptr); sector != nullptr; sector = level->IterateActiveSectors(sector)) {
        sector->m_pSectorDetector->RunDetectors();  // 0x1a8460
    }
    for (uint32_t i = 0; i != m_ui32NbDetectedMovable; ++i) {
        static_cast<CKDetectedMovable*>(m_apDetectedMovable[i])->RefreshDetectablePositions();  // 0x1ab068
    }
}

// 0x001a7d08 CKSrvDetect_EndCinematic_maybe
void CKSrvDetect::EndCinematic() {
    if (--m_unk14 == 0) {
        for (uint32_t i = 0; i < m_ui32NbDetectedMovable; ++i) {
            static_cast<CKDetectedMovable*>(m_apDetectedMovable[i])->RefreshDetectablePositions();
        }
    }
}

// 0x001a6b70 ICollisionMesh_SetActive
void ICollisionMesh::SetActive(uint16_t active) {
    CKLevel* level = g_pEngine->m_level;
    level->m_ba8GroundStateFlags = static_cast<uint8_t>((level->m_ba8GroundStateFlags & 0xfe) | 1);
    m_ba16EngineFlags = static_cast<uint16_t>((m_ba16EngineFlags & 0xfffe) | active);
}

// 0x001a6ba8 ICollisionMesh_GetMeshSlotIndex_maybe
uint16_t ICollisionMesh::GetSectorNumber() const { return static_cast<const CKSector*>(m_pSector)->m_ui16NumSector; }

// 0x001a7090 GroundContact_GetTriangle_maybe
const uint16_t* GroundContact_GetTriangle(const CGroundContactDatasInOut* contact) {
    const int32_t face = contact->m_i32FaceIndex;
    if (face == -1) return nullptr;
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(contact->m_pGround);
    if (ground == nullptr || face >= static_cast<int32_t>(ground->m_ui16NbTriangle)) return nullptr;
    return ground->m_aTriangle[face].m_aui16Index;
}

// 0x001a70e0 GroundContact_GetWorldPoint
void GroundContact_GetWorldPoint(const CGroundContactDatasInOut* contact, CVector3* out) {
    ICollisionMesh* ground = static_cast<ICollisionMesh*>(contact->m_pGround);
    if (ground->GetClassID() != 0x13) {  // vt+0x18; 0x13 = CDynamicGround
        *out = contact->m_ProjectionOnGround;
        return;
    }
    Mat4_TransformPoints(ground->GetWorldMatrix(), out, &contact->m_ProjectionOnGround, 1);  // vt+0x50
}

// 0x001a71d8 GroundContact_GetWorldNormal_maybe
void GroundContact_GetWorldNormal(const CGroundContactDatasInOut* contact, CVector3* out) {
    *out = contact->m_Normal;
    ICollisionMesh* ground = static_cast<ICollisionMesh*>(contact->m_pGround);
    if (ground->GetClassID() != 0x13) return;
    Mat4_TransformVectors(ground->GetWorldMatrix(), out, out, 1);
}

// 0x001a6bc0 CDynamicWall_UpdateQuadtreeBounds_maybe
void CDynamicWall::UpdateQuadtreeBounds() {
    CKQuadtreeAgent* agent = static_cast<CKQuadtreeAgent*>(m_unk04);
    const float minX = m_AABB[3];
    const float minZ = m_AABB[5];
    const float maxX = m_AABB[0];
    const float maxZ = m_AABB[2];
    agent->m_vMin[1] = minZ;  // +0x0c
    agent->m_vMin[0] = minX;  // +0x08
    agent->m_vMax[1] = maxZ;  // +0x14
    agent->m_vMax[0] = maxX;  // +0x10
    agent->InvalidateToRoot();  // 0x00047d30
}
