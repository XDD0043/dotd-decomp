// CKSrvCamera.cpp - reconstructed original translation unit 0x12a888-0x13a330 (GAME_TOC1, main_toc1), 95 functions, 81 live.
// Primary owner: CKSrvCamera (not a registered class)
// Other owners: FogManager (7), RegisterCKSrvCameraClass (1), IKFile (1), CKCameraBase (1), UpdateCKSrvCamera (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x12a888  CKSrvCamera_Destroy
//   [x] 0x12a8d8  CKSrvCamera_vf98
//   [x] 0x12a8e0  CKSrvCamera_vf50
//   [x] 0x12a8e8  CKSrvCamera_vf70
//   [x] 0x12a938  CKSrvCamera_vf78
//   [ ] 0x12a988  CKSrvCamera_CacheTargetPosition_maybe  [dead]
//   [ ] 0x12aab8  CKSrvCamera_CacheHeroPositions_maybe  [dead]
//   [x] 0x12ac08  CKSrvCamera_SetPlayerCanMoveCamera
//   [x] 0x12ac50  CKSrvCamera_ResetCollisionProbes_maybe
//   [ ] 0x12ad30  FUN_0012ad30  [dead]
//   [ ] 0x12ae18  FUN_0012ae18  [dead]
//   [ ] 0x12afc0  CKSrvCamera_InitSampleRing150_maybe  [dead]
//   [ ] 0x12b040  CKSrvCamera_PushSampleRing150_maybe  [dead]
//   [ ] 0x12b0a8  CKSrvCamera_vf40
//   [x] 0x12b0b0  CKSrvCamera_StartCameraParamBlend_maybe
//   [x] 0x12b420  CKSrvCamera_CanStartScriptedCamera_maybe
//   [ ] 0x12b468  RegisterCKSrvCameraClass
//   [ ] 0x12b4e0  _GLOBAL__I_12b4e0
//   [x] 0x12b4f0  CKSrvCamera_SetActiveScriptedCamera_maybe
//   [x] 0x12b558  CKSrvCamera_IsPointInActiveConstraint_maybe
//   [x] 0x12b648  CKSrvCamera_ReleaseHeroHeadingLock_maybe
//   [ ] 0x12b808  CKSrvCamera_IsCameraUsableForHero_maybe  [dead]
//   [ ] 0x12b910  FUN_0012b910  [dead]
//   [x] 0x12b9a0  CKSrvCamera_StopAllShakes_maybe
//   [x] 0x12ba78  CKSrvCamera_AccumulateShake_maybe
//   [ ] 0x12bb20  CKSrvCamera_GetTargetPositionWithCoop_maybe  [dead]
//   [ ] 0x12bbf8  CKSrvCamera_DestroyArray
//   [x] 0x12bc98  CKSrvCamera_EnableDirectionLock_maybe
//   [x] 0x12bda0  FogManager_GetFarDensity_maybe
//   [ ] 0x12bde0  FogManager_GetFogField18_maybe  [dead]
//   [x] 0x12be20  FogManager_GetFarDistance
//   [x] 0x12be60  CKSrvCamera_GetFogStart_maybe
//   [x] 0x12bea0  CKSrvCamera_GetFogEnd_maybe
//   [x] 0x12bee0  FogManager_GetMainDensity_maybe
//   [ ] 0x12bf20  FogManager_GetFogField08_maybe  [dead]
//   [x] 0x12bf60  FogManager_GetColorForFarPass_maybe
//   [x] 0x12bfc0  FogManager_GetMainColor_maybe
//   [ ] 0x12c020  CKSrvCamera_IsViewBlockedByCollision_maybe  [dead]
//   [ ] 0x12c1b0  CKSrvCamera_ResetToInitialState_maybe
//   [ ] 0x12c2f0  CKSrvCamera_LevelReset
//   [ ] 0x12c560  CKSrvCamera_ComputeFrustumOutcode_maybe
//   [ ] 0x12c7a0  FUN_0012c7a0  [dead]
//   [x] 0x12c7d0  CKSrvCamera_FindIndexByKey_maybe
//   [x] 0x12c830  CKSrvCamera_TestSphereAgainstFrustum
//   [x] 0x12c8e0  CKSrvCamera_vf94
//   [x] 0x12c930  CKSrvCamera_Construct
//   [ ] 0x12ccd8  CKSrvCamera_Save
//   [x] 0x12cce0  CKSrvCamera_vf8C
//   [x] 0x12cd40  CKSrvCamera_AddShake_maybe
//   [x] 0x12ce08  CKSrvCamera_ConstructBase_maybe
//   [x] 0x12d1b0  CKSrvCamera_CreateArray
//   [x] 0x12d250  CKSrvCamera_Create
//   [x] 0x12d290  CKSrvCamera_UpdateCameraParamBlend_maybe
//   [x] 0x12d5a0  CKSrvCamera_Destroy
//   [x] 0x12d810  CKSrvCamera_ResetState_maybe
//   [x] 0x12dca0  CKSrvCamera_ApplyCameraEffects_maybe
//   [x] 0x12e058  CKSrvCamera_UpdateCameraZones_maybe
//   [x] 0x12e300  CKSrvCamera_QueueCameraEffect_maybe
//   [ ] 0x12e458  FUN_0012e458  [dead]
//   [x] 0x12e508  CKSrvCamera_UpdateHeroGroundReference_maybe  (CKSrvCamera_2.cpp)
//   [x] 0x12eaa0  CKSrvCamera_FindZoneCameraAtPosition_maybe
//   [x] 0x12ecd0  CKSrvCamera_FindCameraSectorAtFocus_maybe
//   [x] 0x12eee8  CKSrvCamera_StartQuake_maybe
//   [ ] 0x12f0c0  CKSrvCamera_DeletingDestructor
//   [x] 0x12f268  CKSrvCamera_ResolveGroundClearance_maybe  (CKSrvCamera_2.cpp)
//   [ ] 0x12fa38  CKSrvCamera_IsPointInFrustumScaled_maybe
//   [ ] 0x12fbe8  CKSrvCamera_IsExtentInsideFrustum_maybe
//   [x] 0x12fd98  CKSrvCamera_UpdateFrustumPlanes_maybe
//   [x] 0x130200  CKSrvCamera_HandleMessage
//   [x] 0x1308f0  CKSrvCamera_StopAll_maybe
//   [x] 0x130a00  CKSrvCamera_ReinitRuntime
//   [x] 0x130ad8  CKSrvCamera_PostLoad
//   [x] 0x130c20  IKFile_ReadObjectRef
//   [x] 0x130cc8  CKSrvCamera_PushCamera_maybe
//   [x] 0x1314f8  CKSrvCamera_SwitchCameraIfDifferent_maybe
//   [ ] 0x131530  CKSrvCamera_Destructor
//   [x] 0x1316d0  CKSrvCamera_Load
//   [ ] 0x132b38  CKSrvCamera_Destructor_2
//   [ ] 0x132cd8  CKSrvCamera_GetFrustumPlaneNormal_maybe
//   [x] 0x132d88  CKSrvCamera_CaptureHeroHeadingLock_maybe
//   [x] 0x132fd8  CKSrvCamera_AdjustViewToKeepTargetInFrameMargins_maybe  (CKSrvCamera_2.cpp)
//   [x] 0x1337c0  CKSrvCamera_ComputeViewBasis_maybe
//   [x] 0x1339a8  CKCameraBase_SetPositionAndTarget_maybe
//   [x] 0x1339e8  CKSrvCamera_TurnViewTowardDesiredDirection_maybe  (CKSrvCamera_2.cpp)
//   [x] 0x133f28  CKSrvCamera_UpdateCameraTransition_maybe
//   [x] 0x1354b0  CKSrvCamera_SmoothCalculationPosition_maybe  (CKSrvCamera_2.cpp)
//   [x] 0x1357d0  CKSrvCamera_ApplyFrameMarginAdjustment_maybe  (CKSrvCamera_2.cpp)
//   [x] 0x135c80  CKSrvCamera_SmoothCalculationTarget_maybe  (CKSrvCamera_2.cpp)
//   [x] 0x135fd0  CKSrvCamera_FetchTrackPose_maybe  (CKSrvCamera_2.cpp)
//   [x] 0x136348  CKSrvCamera_OrientMatrixToTarget_maybe  (CKSrvCamera_2.cpp)
//   [x] 0x1366a0  CKSrvCamera_UpdateCameraBeacon_maybe  (CKSrvCamera_2.cpp)
//   [x] 0x137820  CKSrvCamera_ComputeDesiredBasis_maybe
//   [x] 0x137ae0  CKSrvCamera_UpdateFrame  (CKSrvCamera_2.cpp)
//   [x] 0x1395a0  UpdateCKSrvCamera
//   [x] 0x1395b8  CKSrvCamera_OnLevelStart_maybe
//
//   [ ] 0x9a7128  CKSrvCamera_IsKindOf  [inline]
//   [ ] 0x9a7160  CKSrvCamera_GetClassGroup  [inline]
//   [ ] 0x9a7168  CKSrvCamera_GetClassId  [inline]
//   [ ] 0x9a7170  KStub_Return0_9a7170  [inline]
#include "k2000/cameras/CKSrvCamera.h"

#include <cfloat>
#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "crt/xtanf.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/components/CKQuakeCameraLauncher.h"
#include "k2000/components/CKQuakeCpntUpdater.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/render/CKCameraFogDatas.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/logic/ai/CKBeaconKluster.h"
#include "k2000/logic/cameras/CKCameraConstraint.h"
#include "k2000/logic/cameras/CKCameraSector.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/math/Quat.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/misc/Mat4.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvBeacon.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {

// 0x00c50d34 / 0x00c50d40 / 0x00c50d4c / 0x00c50d64: the shared axes and the null vector (zero in the EBOOT's
// BSS; filled by static initialisers).
const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};

// 0x00010690 Math_Sqrtf (fsqrts).
inline float Sqrtf(float x) { return std::sqrt(x); }

// 0x00014fd8 IKGameManager_GetCurrentSpawnPoint_maybe (k2000/logic/CDefaultGameManager.cpp, family gm): the game
// structure's (+0x6c) current spawn point (+0x08). Local copy.
inline CKGameSpawnPoint* GetCurrentSpawnPoint() {
    return static_cast<IKGameStructure*>(g_pEngine->m_gameManager->m_gameStructure)->m_pCurrentSpawnPoint;
}

// CKGameSpawnPoint vt+0x74 0x00994f90: a camera position beacon is set (the accessor is not all 0xffff).
inline bool SpawnPointHasCameraPosition(const CKGameSpawnPoint* spawn) {
    return !(spawn->m_baCameraPosition[0] == 0xffff && spawn->m_baCameraPosition[1] == 0xffff &&
             spawn->m_baCameraPosition[2] == 0xffff && spawn->m_baCameraPosition[3] == 0xffff);
}

// CKGameSpawnPoint vt+0x70 0x0003cbd8 CKGameSpawnPoint_GetBeaconPosition_maybe: the three 16-bit values of the
// beacon the accessor names (sector, kluster, id -> set, beacon), tenths.
inline void SpawnPointGetCameraPosition(const CKGameSpawnPoint* spawn, float* position) {
    CKSrvBeacon* beacons = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon);
    CKSrvBeacon::CKBeaconSector& sector = beacons->m_aBeaconSectors[spawn->m_baCameraPosition[0]];
    const int16_t* data = nullptr;
    if (sector.m_apBeaconKlusters != nullptr) {
        CKBeaconKluster* kluster = static_cast<CKBeaconKluster*>(sector.m_apBeaconKlusters[spawn->m_baCameraPosition[1]]);
        const int8_t setIndex = kluster->m_ai8IdToBeaconSet[spawn->m_baCameraPosition[2]];
        const CKSrvBeacon::CKBeaconSet* set = &kluster->m_aBeaconSets[setIndex];
        data = reinterpret_cast<const int16_t*>(static_cast<const uint8_t*>(set->m_aBeacons) +
                                                 static_cast<uint32_t>(spawn->m_baCameraPosition[3]) * set->m_ui8VolatileSizeBytes);
    }
    // BUG(original): without klusters the values are read from the low addresses 0, 2 and 4.
    position[0] = static_cast<float>(data != nullptr ? data[0] : 0) * 0.1f;
    position[1] = static_cast<float>(data != nullptr ? data[1] : 0) * 0.1f;
    position[2] = static_cast<float>(data != nullptr ? data[2] : 0) * 0.1f;
}

// The word at 0x00c4acb8 + 0x28 that the camera stack entries copy (read through a TOC pointer; FLT_MAX
// statically).
const float kCameraStackFar = FLT_MAX;

void InitStackEntry(CKSrvCamera::StackEntry& entry) {
    entry.m_unk05 = 1;
    entry.m_unk0c = 0;
    entry.m_unk08 = -1.0f;
    entry.m_unk10[0] = 1.0f;
    entry.m_unk10[1] = 1.0f;
    entry.m_unk10[3] = 1.0f;
    entry.m_unk10[2] = 1.0f;
    entry.m_unk20 = -1.0f;
    entry.m_unk24[2] = kCameraStackFar;
    entry.m_unk24[0] = kCameraStackFar;
    entry.m_unk24[1] = kCameraStackFar;
}

}  // namespace

// 0x0012c930 CKSrvCamera_Construct (0x12ce08 is the same code). The stores in the original's order.
CKSrvCamera::CKSrvCamera() {
    m_lKCamera = nullptr;
    // IKCamera_ConstructBase (0x1444a8) on +0x4a4, then the CKCamera vtable (0xb1a2b8): the member's constructor.
    m_GContactIn.m_MasksOfGrdForTest[0] = 1;
    m_GContactIn.m_MasksOfGrdForTest[1] = 8;
    m_GContactInOut.m_eContactStatus = 3;
    m_GContactInOut.m_i32FaceIndex = -1;
    m_GContactInOut.m_ui8SectorNumber = 0;
    m_GContactInOut.m_pGround = nullptr;
    m_FinalGrdDataIn.m_MasksOfGrdForTest[0] = 1;
    m_FinalGrdDataIn.m_MasksOfGrdForTest[1] = 8;
    m_FinalGrdDataInOut.m_i32FaceIndex = -1;
    m_FinalGrdDataInOut.m_eContactStatus = 3;
    m_FinalGrdDataInOut.m_ui8SectorNumber = 0;
    m_FinalGrdDataInOut.m_pGround = nullptr;
    m_csfCollisionSmoothSpring.m_fTargetedValue = 0.0f;
    m_v3Unk7a0.x = 0.0f;
    m_unk8a0[0] = 0.0f;
    m_unk8d0[0] = 0.0f;
    m_csfCollisionSmoothSpring.m_fCurrentSpeed = 0.0f;
    m_csfCollisionSmoothSpring.m_fCurrentValue = 0.0f;
    m_v3Unk7a0.z = 0.0f;
    m_v3Unk7a0.y = 0.0f;
    m_unk8a0[2] = 0.0f;
    m_unk8a0[1] = 0.0f;
    m_unk8d0[2] = 0.0f;
    m_unk8d0[1] = 0.0f;
    m_unk8e8 = nullptr;
    m_vUnk8ec.m_ui32NbElt = 1;
    m_vUnk8ec.m_pBlock = nullptr;
    m_vUnk8ec.m_ui32NbUsedElt = 0;
    m_pUnk930 = nullptr;
    m_BeaconFrustum.m_pMatrix = RwMatrixCreate();
    m_unk96c[0] = 0.0f;
    m_unk96c[2] = 0.0f;
    m_unk96c[1] = 0.0f;
    for (float& value : m_unkbdc) value = 0.0f;  // 25 stores of 0.0 in the original
    for (StackEntry& entry : m_aStack) InitStackEntry(entry);
    m_ui32NbStacked = 0;
    m_ui32Priority = 0x5a;
    m_unke24 = 0;
    Engine_SetSrvCamera(this);
    m_pCameraNode = nullptr;
    m_pCameraContext = nullptr;
    // The original returns the nodes of the +0x8e8 list to their pool here; the list is empty.
    m_unk8e8 = nullptr;
    m_pCurrentCamera = nullptr;
    m_unkbc = 1;
    m_fFrameTimeMean = 0.0f;
    m_ui32FrameTimeIndex = 0;
    m_fFrameTimeSum = 0.0f;
    m_apUnke00 = nullptr;
}

// 0x0012d5a0 CKSrvCamera_Destroy (the level unload). IKService's part (0x1a5b8) and the internal
// camera's (0x13da10 CKCamera_Destroy -> 0x13da.. a no-op track clear) do nothing.
void CKSrvCamera::Destroy() {
    m_lKCamera = nullptr;
    m_pStartTarget = nullptr;
    if (m_ui32NbCameraSectorMode != 0 && m_aCameraSectorMode != nullptr && *m_aCameraSectorMode != nullptr) {
        // The list heads (one counted array, m_aCameraSectorMode[0] is its start): every node back to the pool,
        // from the last list to the first, then the array.
        CameraNode** heads = *m_aCameraSectorMode;
        for (uint32_t i = m_ui32NbCameraSectorMode; i != 0; --i) {
            CameraNode* node = heads[i - 1];
            while (node != nullptr) {
                CameraNode* next = node->m_pNext;
                delete node;  // FreeListPool 0x00ceaa30
                node = next;
            }
            heads[i - 1] = nullptr;
        }
        delete[] heads;
    }
    if (m_aCameraSectorMode != nullptr) {
        delete[] m_aCameraSectorMode;
        m_aCameraSectorMode = nullptr;
    }
    m_unk24[1] = 0;
    m_ui32NbCameraSectorMode = 0;
    m_unk24[0] = 0;
    // +0x930: a node list returned to the same pool; nothing in the remake fills it yet (the constructor's 0).
    m_pUnk930 = nullptr;
    // BUG(original): the array is freed but the pointer is kept (the next Load replaces it).
    if (m_apUnke00 != nullptr) delete[] m_apUnke00;
    for (uint32_t i = 0; i < m_vUnk8ec.m_ui32NbUsedElt; ++i) {
        RefGroup& group = m_vUnk8ec.m_pBlock[i];
        if (group.m_vRefs.m_pBlock != nullptr) {
            Mem_FreeAligned16(group.m_vRefs.m_pBlock);
            group.m_vRefs.m_pBlock = nullptr;
        }
        group.m_vRefs.m_ui32NbUsedElt = 0;
        group.m_vRefs.m_pBlock = nullptr;
    }
    if (m_vUnk8ec.m_pBlock != nullptr) {
        // The inlined vector clear walks the groups a second time (all already empty), then frees the block.
        for (uint32_t i = 0; i < m_vUnk8ec.m_ui32NbUsedElt; ++i) {
            RefGroup& group = m_vUnk8ec.m_pBlock[i];
            if (group.m_vRefs.m_pBlock != nullptr) Mem_FreeAligned16(group.m_vRefs.m_pBlock);
            group.m_vRefs.m_ui32NbUsedElt = 0;
            group.m_vRefs.m_pBlock = nullptr;
        }
        Mem_FreeAligned16(m_vUnk8ec.m_pBlock);
    }
    m_vUnk8ec.m_ui32NbUsedElt = 0;
    m_vUnk8ec.m_pBlock = nullptr;
}

// 0x001316d0 CKSrvCamera_Load
int32_t CKSrvCamera::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_lKCamera);
    ReadU32LE(file, &m_ui32NbCameraSectorMode);
    if (m_ui32NbCameraSectorMode == 0) {
        m_aCameraSectorMode = nullptr;
    } else {
        m_aCameraSectorMode = new CameraNode**[m_ui32NbCameraSectorMode];  // OperatorNewArray(n * 4)
        // OperatorNewArray(n * 4 + 4): the list heads (a counted array), each cleared.
        CameraNode** heads = new CameraNode*[m_ui32NbCameraSectorMode];
        for (uint32_t i = 0; i < m_ui32NbCameraSectorMode; ++i) heads[i] = nullptr;
        for (uint32_t i = 0; i < m_ui32NbCameraSectorMode; ++i) {
            m_aCameraSectorMode[i] = &heads[i];
            CameraNode** list = m_aCameraSectorMode[i];
            uint32_t count = 0;
            ReadU32LE(file, &count);
            if (count == 0) continue;
            CameraNode* node = nullptr;
            for (uint32_t n = 0; n < count; ++n) {  // pushed at the head
                node = new CameraNode();  // FreeListPool at 0x00ceaa30 in the original
                node->m_pNext = *list;
                *list = node;
            }
            for (uint32_t n = 0; n < count; ++n) {  // read from the head
                IKFile_ReadObjectRef(file, &node->m_pObject);  // 0x130c20
                node = node->m_pNext;
            }
        }
    }

    // The start camera goes on top of the (emptied) camera stack.
    IKFile_ReadRef(file, &m_pStartTarget);
    m_ui32NbStacked = 0;
    if (m_pStartTarget != nullptr) {
        // The original also has the general push (search, removal, move down); with an empty stack only
        // this branch runs.
        StackEntry& entry = m_aStack[0];
        entry.m_unk0c = 0;
        entry.m_unk04 = 0;
        entry.m_pTarget = m_pStartTarget;
        entry.m_unk05 = 1;
        entry.m_unk10[3] = 1.0f;
        entry.m_unk20 = -1.0f;
        entry.m_unk08 = -1.0f;
        entry.m_unk10[0] = 1.0f;
        entry.m_unk10[1] = 1.0f;
        entry.m_unk10[2] = 1.0f;
        entry.m_unk24[2] = kCameraStackFar;
        entry.m_unk24[0] = kCameraStackFar;
        entry.m_unk24[1] = kCameraStackFar;
        ++m_ui32NbStacked;
        m_baTemporaryFlags = (m_baTemporaryFlags & 0xff7fffffu) | 0x800000u;
    }

    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_SmoothVisc), 0x27);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_SmoothKSpring), 0x27);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_afSafeOffsetYFromBasicTarget), 10);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_afSafeLeft), 10);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_afSafeRight), 10);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_afSafeUp), 10);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_afSafeDown), 10);
    IKFile_ReadRef(file, &m_pDodgeBS);
    IKFile_ReadRef(file, &m_pDodgeBSPushCam);
    ReadU32LE(file, &m_bSubscribedToAvoidance);
    ReadF32LE(file, &m_fRadius);
    m_pKGLObject = nullptr;
    ReadU32LEWords(file, m_unkc0, 0x24);
    ReadU32LEWords(file, m_unk150, 0x1e);
    ReadU32LEWords(file, m_unk2c, 0x24);
    for (SCameraAvoidingDatas& datas : m_asAvoidingDatas) {
        for (float& value : datas.m_afValues) ReadF32LE(file, &value);
    }
    ReadU32LE(file, &m_unk8e0);
    ReadU32LE(file, &m_unk8dc);
    ReadU32LE(file, &m_unk7ac);

    uint32_t groupCount = 0;
    ReadU32LE(file, &groupCount);
    if (groupCount == 0) {
        m_vUnk8ec.m_ui32NbElt = 1;
        m_vUnk8ec.m_pBlock = static_cast<RefGroup*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(RefGroup))));
    } else {
        m_vUnk8ec.m_ui32NbElt = groupCount;
        m_vUnk8ec.m_pBlock =
            static_cast<RefGroup*>(Mem_AllocAligned16(groupCount * static_cast<uint32_t>(sizeof(RefGroup))));
        if (m_vUnk8ec.m_ui32NbElt < groupCount) {  // as in the original: cannot happen
            uint32_t capacity = groupCount + 1;
            if (capacity == 0) capacity = 1;
            m_vUnk8ec.m_pBlock = static_cast<RefGroup*>(
                Mem_ReallocAligned16(m_vUnk8ec.m_pBlock, capacity * static_cast<uint32_t>(sizeof(RefGroup))));
            m_vUnk8ec.m_ui32NbElt = capacity;
        }
        for (uint32_t i = m_vUnk8ec.m_ui32NbUsedElt; i < groupCount; ++i) {  // the new elements
            RefGroup& group = m_vUnk8ec.m_pBlock[i];
            group.m_vRefs.m_ui32NbElt = 1;
            group.m_vRefs.m_pBlock = nullptr;
            group.m_vRefs.m_ui32NbUsedElt = 0;
        }
        for (uint32_t i = groupCount; i < m_vUnk8ec.m_ui32NbUsedElt; ++i) {  // the dropped ones
            RefGroup& group = m_vUnk8ec.m_pBlock[i];
            if (group.m_vRefs.m_pBlock != nullptr) Mem_FreeAligned16(group.m_vRefs.m_pBlock);
            group.m_vRefs.m_ui32NbUsedElt = 0;
            group.m_vRefs.m_pBlock = nullptr;
        }
        m_vUnk8ec.m_ui32NbUsedElt = groupCount;
    }
    for (uint32_t i = 0; i < groupCount; ++i) {
        RefGroup& group = m_vUnk8ec.m_pBlock[i];
        IKFile_ReadRef(file, &group.m_pObject);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        if (count == 0) {
            group.m_vRefs.m_ui32NbElt = 1;
            group.m_vRefs.m_pBlock =
                static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
        } else {
            group.m_vRefs.m_ui32NbElt = count;
            group.m_vRefs.m_pBlock =
                static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        }
        if (group.m_vRefs.m_ui32NbElt < count) {  // as in the original: cannot happen
            uint32_t capacity = count + 1;
            if (capacity == 0) capacity = 1;
            group.m_vRefs.m_pBlock = static_cast<IKSerializable**>(
                Mem_ReallocAligned16(group.m_vRefs.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
            group.m_vRefs.m_ui32NbElt = capacity;
        }
        group.m_vRefs.m_ui32NbUsedElt = count;
        for (uint32_t n = 0; n < count; ++n) IKFile_ReadObjectRef(file, &group.m_vRefs.m_pBlock[n]);
    }

    ReadU32LE(file, &m_unk1c8);
    ReadU32LE(file, &m_unk49c);
    ReadU32LE(file, &m_unk4a0);
    for (uint32_t i = 0; i < 10; ++i) {
        for (uint32_t w = 0; w < 5; ++w) ReadU32LE(file, &m_unkc40[i][w]);
    }
    ReadU32LE(file, &m_ui32NbUnke00);
    m_apUnke00 = new IKSerializable*[m_ui32NbUnke00];  // OperatorNewArray(n * 4)
    for (uint32_t i = 0; i < m_ui32NbUnke00; ++i) IKFile_ReadObjectRef(file, &m_apUnke00[i]);
    ReadU32LE(file, &m_unke08);
    return 1;
}

// 0x001308f0 CKSrvCamera_StopAll_maybe (the service's Stop): the current camera stopped (vt+0x58), and with
// bit 7 of the temporary flags the running shake effects stopped and their nodes freed.
void CKSrvCamera::Stop() {
    if (m_pCurrentCamera != nullptr) m_pCurrentCamera->Stop();
    if ((m_baTemporaryFlags & 0x80) != 0) {
        for (SShakeNode* node = m_unk8e8; node != nullptr; node = node->m_pNext) {
            node->m_pEffect->Stop();  // CKQuakeCpntUpdater_Stop 0x24f738
        }
        for (SShakeNode* node = m_unk8e8; node != nullptr;) {
            SShakeNode* next = node->m_pNext;
            delete node;  // back to the FreeListPool in the original
            node = next;
        }
        m_unk8e8 = nullptr;
        m_baTemporaryFlags &= 0xffffff7fu;
    }
}

// 0x00130a00 CKSrvCamera_Restart (vt+0x54): Stop's shake part alone.
void CKSrvCamera::Restart() {
    if ((m_baTemporaryFlags & 0x80) != 0) {
        for (SShakeNode* node = m_unk8e8; node != nullptr; node = node->m_pNext) {
            node->m_pEffect->Stop();  // CKQuakeCpntUpdater_Stop 0x24f738
        }
        for (SShakeNode* node = m_unk8e8; node != nullptr;) {
            SShakeNode* next = node->m_pNext;
            delete node;
            node = next;
        }
        m_unk8e8 = nullptr;
        m_baTemporaryFlags &= 0xffffff7fu;
    }
}

// 0x00137820 CKSrvCamera_ComputeDesiredBasis_maybe (XXL2 ComputeInternalCameraAxis): z = the normalised direction from
// the internal camera's position (+0x4c4) to its target (+0x4d0); x = (z.z, 0, -z.x) normalised, y = z x x. Looking
// (almost) straight up or down x keeps its last value and y = z x x, then x = y x z.
void CKSrvCamera::ComputeDesiredBasis() {
    const CVector3& position = m_InternalCamera.m_WorldPosition;
    const CVector3& target = m_InternalCamera.m_WorldTarget;
    const float dx = target.x - position.x;
    const float dy = target.y - position.y;
    const float dz = target.z - position.z;
    float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (length == 0.0f) return;
    const float inverse = 1.0f / length;
    CVector3& z = m_v3InternalAxisZ;
    CVector3& x = m_v3InternalAxisX;
    CVector3& y = m_v3InternalAxisY;
    z.x = dx * inverse;
    z.z = dz * inverse;
    z.y = dy * inverse;
    if (std::fabs(z.y) < 0.9998477101325989f) {  // TOC 0x3f7ff605
        x.x = z.z;
        float sum = ppc::fmadds(z.z, z.z, 0.0f);
        const float negZx = -z.x;
        x.y = 0.0f;
        sum = ppc::fmadds(negZx, negZx, sum);
        x.z = negZx;
        length = Sqrtf(sum);
        if (length != 0.0f) {
            const float inverseX = 1.0f / length;
            x.z = inverseX * x.z;
            x.x = inverseX * x.x;
            x.y = inverseX * x.y;
        }
        y.x = ppc::fmsubs(z.y, x.z, z.z * x.y);
        y.y = ppc::fmsubs(z.z, x.x, z.x * x.z);
        y.z = ppc::fmsubs(z.x, x.y, z.y * x.x);
        return;
    }
    // y = z x x (the x of the last call)
    y.x = ppc::fmsubs(z.y, x.z, z.z * x.y);
    y.y = ppc::fmsubs(z.z, x.x, z.x * x.z);
    y.z = ppc::fmsubs(z.x, x.y, z.y * x.x);
    float sum = ppc::fmadds(y.x, y.x, y.y * y.y);
    sum = ppc::fmadds(y.z, y.z, sum);
    length = Sqrtf(sum);
    if (length != 0.0f) {
        const float inverseY = 1.0f / length;
        y.z = inverseY * y.z;
        y.x = inverseY * y.x;
        y.y = inverseY * y.y;
    }
    // x = y x z
    x.x = ppc::fmsubs(y.y, z.z, y.z * z.y);
    x.y = ppc::fmsubs(y.z, z.x, y.x * z.z);
    x.z = ppc::fmsubs(y.x, z.y, y.y * z.x);
}

// 0x001339a8 CKCameraBase_SetPositionAndTarget_maybe (the word copies in the original's order: x, z, y)
void CKSrvCamera::SetCalculationPose(const CVector3* position, const CVector3* target) {
    m_v3CalcPos.x = position->x;
    m_v3CalcPos.z = position->z;
    m_v3CalcPos.y = position->y;
    m_v3CalcTarget.x = target->x;
    m_v3CalcTarget.z = target->z;
    m_v3CalcTarget.y = target->y;
    ComputeViewBasis();
}

// 0x001337c0 CKSrvCamera_ComputeViewBasis_maybe (XXL2 ComputeCalculationCameraAxis): the same from the calculation
// pose (+0x550 -> +0x55c) into +0x574 / +0x580 / +0x58c; looking straight up or down x = (z.y, -z.x, -0).
void CKSrvCamera::ComputeViewBasis() {
    const float dx = m_v3CalcTarget.x - m_v3CalcPos.x;
    const float dy = m_v3CalcTarget.y - m_v3CalcPos.y;
    const float dz = m_v3CalcTarget.z - m_v3CalcPos.z;
    float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (length == 0.0f) return;
    const float inverse = 1.0f / length;
    CVector3& z = m_v3CalcAxisZ;
    CVector3& x = m_v3CalcAxisX;
    CVector3& y = m_v3CalcAxisY;
    z.x = dx * inverse;
    z.z = dz * inverse;
    z.y = dy * inverse;
    if (std::fabs(z.y) < 0.9998477101325989f) {
        x.x = z.z;
        float sum = ppc::fmadds(z.z, z.z, 0.0f);
        const float negZx = -z.x;
        x.y = 0.0f;
        sum = ppc::fmadds(negZx, negZx, sum);
        x.z = negZx;
        length = Sqrtf(sum);
    } else {
        const float negZx = -z.x;
        x.x = z.y;  // (the original stores -z.y first and overwrites it)
        x.z = -0.0f;
        x.y = negZx;
        const float square = negZx * negZx;
        length = Sqrtf(ppc::fmadds(z.y, z.y, square) + 0.0f);
    }
    if (length != 0.0f) {
        const float inverseX = 1.0f / length;
        x.z = inverseX * x.z;
        x.x = inverseX * x.x;
        x.y = inverseX * x.y;
    }
    y.x = ppc::fmsubs(z.y, x.z, z.z * x.y);
    y.y = ppc::fmsubs(z.z, x.x, z.x * x.z);
    y.z = ppc::fmsubs(z.x, x.y, z.y * x.x);
}

// 0x0012fd98 CKSrvCamera_UpdateFrustumPlanes_maybe: the six planes (near, far, left, right, top, bottom; normal and
// distance) of the real pose's frustum. The side planes are built from the real x axis (+0x5b0) and the INTERNAL
// camera's y axis (+0x538). tanf: the PS3's (crt::Tanf, step 5).
void CKSrvCamera::UpdateFrustumPlanes() {
    const float halfAngle = (m_fRealFov * 0x1.1df468p-6f) * 0x1p-1f;
    const float tangent = crt::Tanf(halfAngle);
    const float nearScale = m_fRealFar * 0x1.0624dep-10f;  // 0.001 of the far plane
    const float aspect = m_pCameraContext->m_fHeightOverWidth * 0x1.555556p+0f;
    const CVector3& pos = m_v3RealPos;
    const CVector3& z = m_v3RealAxisZ;
    const CVector3& ax = m_v3RealAxisX;
    const CVector3& up = m_v3InternalAxisY;
    float (*planes)[4] = m_afFrustumPlanes;
    const float kx = nearScale * z.x;  // f25
    const float ky = nearScale * z.y;  // f24
    const float kz = nearScale * z.z;  // f27
    const float scale = tangent / aspect;  // f0 (fdivs)
    // plane 0: the near plane, facing -z
    planes[0][1] = -z.y;
    planes[0][0] = -z.x;
    planes[0][2] = -z.z;
    const float nearTangent = tangent * 0.75f;  // f1
    const float sx = scale * nearScale;          // f7
    const float negScale = -scale;               // f0
    const float negTan = -nearTangent;           // f13
    const float ty = nearTangent * nearScale;    // f26
    const float negSx = nearScale * negScale;    // f28
    const float negTy = nearScale * negTan;      // f23
    {
        const float ax0 = kx + pos.x;
        const float ay0 = ky + pos.y;
        const float az0 = kz + pos.z;
        const float t = ay0 * planes[0][1];
        planes[0][3] = -std::fmaf(az0, planes[0][2], std::fmaf(ax0, planes[0][0], t));
    }
    // plane 1: the far plane, facing +z
    {
        const float far = m_fRealFar;
        planes[1][1] = z.y;
        const float by = ppc::fmadds(far, z.y, pos.y);
        const float bx = ppc::fmadds(far, z.x, pos.x);
        planes[1][0] = z.x;
        const float bz = ppc::fmadds(far, z.z, pos.z);
        planes[1][2] = z.z;
        const float t = by * planes[1][1];
        planes[1][3] = -std::fmaf(bz, planes[1][2], std::fmaf(bx, planes[1][0], t));
    }
    // The normal of a side plane (nx, ny, nz from the cross products below), normalised, and its distance through the
    // eye position.
    auto finishPlane = [&](float* plane, float nx, float ny, float nz) {
        float sum = ny * ny;
        sum = ppc::fmadds(nx, nx, sum);
        sum = ppc::fmadds(nz, nz, sum);
        const float length = Sqrtf(sum);
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            nz = nz * inverse;
            nx = nx * inverse;
            ny = ny * inverse;
        }
        plane[1] = ny;
        plane[0] = nx;
        plane[2] = nz;
        const float t = plane[1] * pos.y;
        plane[3] = -std::fmaf(plane[2], pos.z, std::fmaf(plane[0], pos.x, t));
    };
    {  // left: D = sx * x + near * z, normal = D x U (U = the internal y axis)
        const float dx = ppc::fmadds(sx, ax.x, kx);
        const float dz = ppc::fmadds(sx, ax.z, kz);
        const float dy = ppc::fmadds(sx, ax.y, ky);
        const float t1 = dx * up.y;
        const float t2 = dz * up.x;
        const float t3 = dy * up.z;
        const float nz = ppc::fmsubs(dy, up.x, t1);
        const float ny = ppc::fmsubs(dx, up.z, t2);
        const float nx = ppc::fmsubs(dz, up.y, t3);
        finishPlane(planes[2], nx, ny, nz);
    }
    {  // right: D = -sx * x + near * z
        const float dx = ppc::fmadds(negSx, ax.x, kx);
        const float dz = ppc::fmadds(negSx, ax.z, kz);
        const float dy = ppc::fmadds(negSx, ax.y, ky);
        const float t1 = dx * up.z;
        const float t2 = dz * up.y;
        const float t3 = dy * up.x;
        const float ny = ppc::fmsubs(dz, up.x, t1);
        const float nx = ppc::fmsubs(dy, up.z, t2);
        const float nz = ppc::fmsubs(dx, up.y, t3);
        finishPlane(planes[3], nx, ny, nz);
    }
    {  // top: D = ty * U + near * z, normal = D x X
        const float dx = ppc::fmadds(ty, up.x, kx);
        const float dz = ppc::fmadds(ty, up.z, kz);
        const float dy = ppc::fmadds(ty, up.y, ky);
        const float t1 = dx * ax.z;
        const float t2 = dz * ax.y;
        const float t3 = dy * ax.x;
        const float ny = ppc::fmsubs(dz, ax.x, t1);
        const float nx = ppc::fmsubs(dy, ax.z, t2);
        const float nz = ppc::fmsubs(dx, ax.y, t3);
        finishPlane(planes[4], nx, ny, nz);
    }
    {  // bottom: D = -ty * U + near * z
        const float dz = ppc::fmadds(negTy, up.z, kz);
        const float dx = ppc::fmadds(negTy, up.x, kx);
        const float dy = ppc::fmadds(negTy, up.y, ky);
        const float t1 = dz * ax.x;
        const float t2 = dx * ax.y;
        const float t3 = dy * ax.z;
        const float ny = ppc::fmsubs(dx, ax.z, t1);
        const float nz = ppc::fmsubs(dy, ax.x, t2);
        const float nx = ppc::fmsubs(dz, ax.y, t3);
        finishPlane(planes[5], nx, ny, nz);
    }
}

// 0x0012ecd0 CKSrvCamera_FindCameraSectorAtFocus_maybe
CKCameraSector* CKSrvCamera::FindCameraSectorAtFocus(bool requireCameras, CKCameraSector* exclude) {
    if (m_ui32NbStacked != 0 && m_aStack[0].m_pTarget != nullptr && m_ui32NbCameraSectorMode != 0) {
        CSGLeaf* leaf = static_cast<CSGLeaf*>(m_aStack[0].m_pTarget);
        // The stored LTM of the original (synchronised by CKGraphic_UpdateSceneWorldMatrices right before): computed
        // on demand here.
        const RwMatrix* ltm = RwFrameGetLTM(leaf->m_pRwFrame);
        for (CameraNode* node = *m_aCameraSectorMode[m_unk24[0]]; node != nullptr; node = node->m_pNext) {
            CKCameraSector* sector = static_cast<CKCameraSector*>(node->m_pObject);
            if (sector->IsEnabledForFocusedHero() && sector != exclude &&
                (!requireCameras || sector->m_vpCameraCount != 0) && sector->ContainsPoint(&ltm->pos.x)) {
                if (m_unk24[0] == m_unk24[1] || m_ui32NbStacked == 0 || m_aStack[0].m_pTarget == nullptr ||
                    sector->FindValidCamera() != nullptr) {
                    return sector;
                }
                // The previous sector mode's list must hold the sector too.
                for (CameraNode* previous = *m_aCameraSectorMode[m_unk24[1]]; previous != nullptr;
                     previous = previous->m_pNext) {
                    if (previous->m_pObject == sector) return sector;
                }
            }
        }
    }
    return nullptr;
}

// 0x0012e058 CKSrvCamera_UpdateCameraZones_maybe
void CKSrvCamera::UpdateCameraZones() {
    if (m_ui32NbStacked == 0 || m_aStack[0].m_pTarget == nullptr) return;
    CSGLeaf* leaf = static_cast<CSGLeaf*>(m_aStack[0].m_pTarget);
    const RwMatrix* ltm = RwFrameGetLTM(leaf->m_pRwFrame);  // the stored LTM of the original, computed on demand
    // The point the zones are tested with: a camera track's target, else the focus node's world position.
    const RwV3d* focus = &ltm->pos;
    if (m_pCurrentCamera != nullptr && m_pCurrentCamera->IsKindOfClass(0x387) != 0) {
        focus = reinterpret_cast<const RwV3d*>(&m_pCurrentCamera->m_WorldTarget);
    }
    const float focusPoint[3] = {focus->x, focus->y, focus->z};
    CKCameraConstraint* const previous = m_pActiveConstraint;
    if (previous != nullptr) {
        if ((previous->m_unk1c & 2u) == 0) return;
        m_pActiveConstraint = nullptr;
    }
    const uint32_t count = m_ui32NbUnke00;
    for (uint32_t i = 0; i < count; ++i) {
        CKCameraConstraint* constraint = static_cast<CKCameraConstraint*>(m_apUnke00[i]);
        m_pActiveConstraint = constraint;
        if ((constraint->m_unk1c & 2u) == 0) break;  // the list is ordered: the first inactive zone ends the search
        uint32_t flags;
        std::memcpy(&flags, &constraint->m_unk20, sizeof(flags));
        float point[3];
        if ((flags & 0x200000u) == 0) {
            point[0] = ltm->pos.x;
            point[1] = ltm->pos.y;
            point[2] = ltm->pos.z;
        } else {
            point[0] = focusPoint[0];
            point[1] = focusPoint[1];
            point[2] = focusPoint[2];
        }
        if (constraint->IsEnabledFor(m_unk24[0]) && constraint->ContainsPoint(point)) {
            if (((constraint->m_unk1c >> 5) & 3u) == 3u) {
                m_pActiveConstraint = previous;
                return;
            }
            if (previous == constraint) return;
            if (previous != nullptr) QueueTriggerSignals(&previous->m_tsUnk30);
            QueueTriggerSignals(&constraint->m_tsUnk28);
            constraint->m_unk9c = (constraint->m_unk9c & 0x00ffffffu) | 0xff000000u;  // the byte at +0x9c = 0xff
            std::memcpy(&constraint->m_unk74, &constraint->m_afUnk44[10], sizeof(uint32_t));  // +0x74 = +0x6c
            return;
        }
    }
    if (previous != nullptr) QueueTriggerSignals(&previous->m_tsUnk30);
    m_pActiveConstraint = nullptr;
}

// 0x001395b8 CKSrvCamera_OnLevelStart_maybe (XXL2 UpdateInitialize): the service's state reset, the hero's camera
// target pushed on the target stack (CKS08GameManager vt+0x144), the sector at the focus and its camera chosen and
// started, and the camera context, the camera frame and the two dodge spheres put on that pose.
void CKSrvCamera::UpdateInitialize() {
    ResetState();
    ResetCollisionProbes();
    if (((m_baTemporaryFlags & 8) == 0) || ((m_baTemporaryFlags & 0x10) != 0)) {
        m_baTemporaryFlags &= 0xfffefffeu;
        m_unk8d0[0] = 0.0f;
        m_unk8d0[2] = 0.0f;
        m_unk8d0[1] = 0.0f;
    }
    m_baTemporaryFlags &= 0xfffdffffu;
    m_csfCollisionSmoothSpring.m_fTargetedValue = 0.0f;
    m_csfCollisionSmoothSpring.m_fCurrentSpeed = 0.0f;
    m_csfCollisionSmoothSpring.m_fCurrentValue = 0.0f;
    m_v3Unk77c = kNullVector;
    m_v3Unk788 = kNullVector;
    m_v3Unk794.x = m_v3CalcTarget.x;
    m_v3Unk794.y = m_v3CalcTarget.y;
    m_v3Unk794.z = m_v3CalcTarget.z;
    m_v3Unk7a0.x = 0.0f;
    m_v3Unk7a0.z = 0.0f;
    m_v3Unk7a0.y = 0.0f;
    const float blend = -1.0f;
    CKGameSpawnPoint* spawn = GetCurrentSpawnPoint();
    if (spawn != nullptr) {
        // CKGameSpawnPoint vt+0x78 0x3ccf8 (the node the camera follows) is 0 for the one spawn point class: the
        // hero group updates its camera targets instead (CKS08GameManager vt+0x144).
        g_pEngine->m_gameManager->UpdateHeroCameraTargets();
        if (SpawnPointHasCameraPosition(spawn)) {
            float position[3];
            SpawnPointGetCameraPosition(spawn, position);
            m_baTemporaryFlags |= 0x40u;
            m_v3ScriptedStart.x = position[0];
            m_v3ScriptedStart.z = position[2];
            m_v3ScriptedStart.y = position[1];
            m_v3SavedPos.x = position[0];
            m_v3SavedPos.y = position[1];
            m_v3SavedPos.z = position[2];
        } else {
            m_baTemporaryFlags &= 0xffffffbfu;
        }
    }
    if (m_ui32NbStacked == 0 || m_aStack[0].m_pTarget == nullptr) {
        if (m_pStartTarget != nullptr) PushStackTarget(m_pStartTarget, blend);
    }
    // The focus position: the first target's, or the null vector.
    if (m_ui32NbStacked == 0 || m_aStack[0].m_pTarget == nullptr) {
        m_v3FocusPos = kNullVector;
        m_v3FocusPosCopy = m_v3FocusPos;
    } else {
        CSGLeaf* leaf = static_cast<CSGLeaf*>(m_aStack[0].m_pTarget);
        CSGBranch* parent = static_cast<CSGBranch*>(leaf->m_pParent);
        const RwV3d* position;
        if (parent == nullptr || parent->GetClassID() != 2) {
            if ((m_baTemporaryFlags & 0x80000u) == 0) leaf->ForceWorldMatrixUpdate();
            position = &RwFrameGetLTM(leaf->m_pRwFrame)->pos;
        } else {
            position = &leaf->m_pRwFrame->modelling.pos;
        }
        m_v3FocusPos.x = position->x;
        m_v3FocusPos.y = position->y;
        m_v3FocusPos.z = position->z;
        m_v3FocusPosCopy.x = m_v3FocusPos.x;
        m_v3FocusPosCopy.z = position->z;
        m_v3FocusPosCopy.y = m_v3FocusPos.y;
    }
    for (uint32_t i = 0; i < m_ui32NbStacked; ++i) {  // each target's world position kept in its entry
        CSGLeaf* leaf = static_cast<CSGLeaf*>(m_aStack[i].m_pTarget);
        if (leaf != nullptr) {
            CSGBranch* parent = static_cast<CSGBranch*>(leaf->m_pParent);
            if ((parent == nullptr || parent->GetClassID() != 2) && (m_baTemporaryFlags & 0x80000u) == 0) {
                leaf->ForceWorldMatrixUpdate();
            }
            const RwV3d& position = RwFrameGetLTM(leaf->m_pRwFrame)->pos;
            m_aStack[i].m_unk24[0] = position.x;
            m_aStack[i].m_unk24[1] = position.y;
            m_aStack[i].m_unk24[2] = position.z;
        }
    }
    m_fSectorTimer = blend;
    if (m_unke24 == 0) {
        m_pCurrentSector = FindCameraSectorAtFocus(true, nullptr);
        if (m_pCurrentSector != nullptr) {
            m_fSectorTimer = m_pCurrentSector->m_unk54;
            m_pCurrentCamera = m_pCurrentSector->FindValidCamera();
        }
    }
    UpdateCameraZones();
    if (m_pCurrentCamera != nullptr) {
        const CVector3* start = (m_baTemporaryFlags & 0x40u) != 0 ? &m_v3ScriptedStart : nullptr;
        m_pCurrentCamera->Start(start);
        m_baTemporaryFlags &= 0xffffffbfu;
        m_InternalCamera.m_WorldPosition = m_pCurrentCamera->m_WorldPosition;
        m_InternalCamera.m_WorldTarget = m_pCurrentCamera->m_WorldTarget;
        m_InternalCamera.m_unk18 = m_pCurrentCamera->m_unk18;
        m_InternalCamera.m_fFar = m_pCurrentCamera->m_fFar;
        ComputeDesiredBasis();
    }
    m_v3CalcPos = m_InternalCamera.m_WorldPosition;
    m_v3CalcTarget = m_InternalCamera.m_WorldTarget;
    m_fCalcFov = m_InternalCamera.m_unk18;
    m_fCalcFar = m_InternalCamera.m_fFar;
    ComputeViewBasis();
    m_v3Unk794 = m_v3CalcTarget;
    m_v3SavedPos = m_v3CalcPos;
    m_v3SavedTarget = m_v3CalcTarget;
    m_v3RealPos = m_v3CalcPos;
    m_v3RealTarget = m_v3CalcTarget;
    m_v3RealAxisX = m_v3CalcAxisX;
    m_v3RealAxisY = m_v3CalcAxisY;
    m_v3RealAxisZ = m_v3CalcAxisZ;
    m_fRealFov = m_fCalcFov;
    m_fRealFar = m_fCalcFar;
    m_v3HeadingDir = m_v3CalcAxisZ;
    // The camera node on the real pose.
    RwFrame* cameraFrame = m_pCameraNode->m_pRwFrame;
    cameraFrame->modelling.pos.x = m_v3RealPos.x;
    cameraFrame->modelling.pos.y = m_v3RealPos.y;
    cameraFrame->modelling.pos.z = m_v3RealPos.z;
    cameraFrame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(cameraFrame);
    m_pCameraNode->LookAtPoint(&m_v3RealTarget.x, &m_v3RealAxisY.x);
    m_pCameraContext->SetFieldOfView(m_fRealFov, 0, 0, 1);
    m_pCameraContext->SetClipPlanes(m_fRealFar, 0.01f, 1, 0);
    UpdateFrustumPlanes();
    // The two dodge spheres: the first half its radius ahead of the camera, the second at the camera.
    IKBoundingVolume* dodge = static_cast<IKBoundingVolume*>(m_pDodgeBS);
    const float ahead = dodge->m_fRadius * 0.5f;
    RwFrame* dodgeFrame = dodge->m_pRwFrame;
    dodgeFrame->modelling.pos.x = ppc::fmadds(ahead, m_v3RealAxisZ.x, m_v3RealPos.x);
    dodgeFrame->modelling.pos.y = ppc::fmadds(ahead, m_v3RealAxisZ.y, m_v3RealPos.y);
    dodgeFrame->modelling.pos.z = ppc::fmadds(ahead, m_v3RealAxisZ.z, m_v3RealPos.z);
    dodgeFrame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(dodgeFrame);
    IKBoundingVolume* push = static_cast<IKBoundingVolume*>(m_pDodgeBSPushCam);
    RwFrame* pushFrame = push->m_pRwFrame;
    pushFrame->modelling.pos.x = m_v3RealPos.x;
    pushFrame->modelling.pos.y = m_v3RealPos.y;
    pushFrame->modelling.pos.z = m_v3RealPos.z;
    pushFrame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(pushFrame);
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->AddVolume(dodge);
    collision->AddVolume(push);
    m_baTemporaryFlags = (m_baTemporaryFlags & 0xff9fffffu) | 0x200000u;
}

// 0x0012a8e8 CKSrvCamera_vf70 (Pause) and 0x0012a938 CKSrvCamera_vf78 (Resume): the current camera's vt+0x54 / +0x5c.
void CKSrvCamera::Pause() {
    if (m_pCurrentCamera != nullptr) m_pCurrentCamera->Pause();
}
void CKSrvCamera::Resume() {
    if (m_pCurrentCamera != nullptr) m_pCurrentCamera->Resume();
}

// 0x001395a0 UpdateCKSrvCamera: only while the frame clock runs (state 0), CKSrvCamera_UpdateFrame 0x137ae0 (a tail
// call) with the unscaled frame time (+0x20).
void CKSrvCamera::Update(IKTime* frameClock) {
    if (frameClock->m_eCurrentState != IKTime::RUNNING) return;
    UpdateFrame(frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME]);
}

// 0x0012cce0 CKSrvCamera_vf8C (SectorUnload): the node list at +0x930 back to its pool and four flags reset.
void CKSrvCamera::SectorUnload(int32_t /*sector*/) {
    m_bUnk916 = 0;
    m_bUnk917 = 1;
    m_pUnk920 = nullptr;
    m_bUnk915 = 0;
    for (CameraNode* node = m_pUnk930; node != nullptr;) {
        CameraNode* next = node->m_pNext;
        delete node;
        node = next;
    }
    m_pUnk930 = nullptr;
}

// 0x0012c8e0 CKSrvCamera_vf94 (InitializeService): the renderer's camera context (CKGraphic -> renderer +0x28) and
// its camera node; the sector-mode lists emptied.
int32_t CKSrvCamera::InitializeService() {
    CameraContext* context = g_pEngine->m_graphic->m_renderer->m_cameraContext;
    m_pCameraNode = static_cast<CSGMovable*>(context->m_pCamera);
    m_unk24[1] = 0;
    m_pCameraContext = context;
    m_aCameraSectorMode = nullptr;
    m_ui32NbCameraSectorMode = 0;
    m_unk24[0] = 0;
    return 1;
}

// 0x00130ad8 CKSrvCamera_PostLoad (IKService's PostLoad, KStub_Return1_1a5b0, first)
int32_t CKSrvCamera::PostLoad(int32_t /*type*/) {
    ResetState();
    ResetCollisionProbes();
    if (((m_baTemporaryFlags & 8) == 0) || ((m_baTemporaryFlags & 0x10) != 0)) {
        m_baTemporaryFlags &= 0xfffefffeu;
        m_unk8d0[0] = 0.0f;
        m_unk8d0[2] = 0.0f;
        m_unk8d0[1] = 0.0f;
    }
    m_baTemporaryFlags &= 0xfffdffffu;
    m_csfCollisionSmoothSpring.m_fTargetedValue = 0.0f;
    m_csfCollisionSmoothSpring.m_fCurrentSpeed = 0.0f;
    m_csfCollisionSmoothSpring.m_fCurrentValue = 0.0f;
    m_v3Unk77c = kNullVector;
    m_v3Unk788 = kNullVector;
    m_v3Unk794.x = m_v3CalcTarget.x;
    m_v3Unk794.z = m_v3CalcTarget.z;
    m_v3Unk794.y = m_v3CalcTarget.y;
    m_v3Unk7a0.x = 0.0f;
    m_v3Unk7a0.y = 0.0f;
    m_v3Unk7a0.z = 0.0f;
    m_unk24[1] = 0;
    m_unk24[0] = 0;
    return 1;
}

// 0x0012ac08 CKSrvCamera_SetPlayerCanMoveCamera (XXL2 CKSrvCamera::SetPlayerCanMoveCamera(bool), the same code):
// m_baTemporaryFlags bit 2 (0x4) = the player cannot move the camera. Allowing it clears the bit unless bit 14 (0x4000)
// holds it; forbidding it sets the bit.
void CKSrvCamera::SetPlayerCanMoveCamera(bool canMove) {
    if (canMove) {
        if ((m_baTemporaryFlags & 0x4000u) != 0) return;
        m_baTemporaryFlags &= ~0x4u;
        return;
    }
    m_baTemporaryFlags = (m_baTemporaryFlags & ~0x4u) | 0x4u;
}

// 0x0012ac50 CKSrvCamera_ResetCollisionProbes_maybe (XXL2 InitializeCollisionDatas). The probes ask for ground
// masks 1 and 0x80 here (the constructor has 1 and 8).
void CKSrvCamera::ResetCollisionProbes() {
    m_baTemporaryFlags &= 0xffffc1ffu;
    m_ui8ProbeFlags = static_cast<uint8_t>(m_ui8ProbeFlags & 0xf8u);
    m_baTemporaryFlags &= 0xffffbfffu;
    m_GContactIn.m_fDeltaMax = 1.0f;
    m_GContactIn.m_fObjectHeight = 1.0f;
    m_GContactIn.m_MasksOfGrdForTest[0] = 1;
    m_GContactIn.m_MasksOfGrdForTest[1] = 0x80;
    m_GContactInOut.m_pGround = nullptr;
    m_GContactInOut.m_i32FaceIndex = -1;
    m_GContactInOut.m_ui8SectorNumber = 0;
    m_GContactInOut.m_eContactStatus = 3;
    m_FinalGrdDataIn.m_fDeltaMax = 1.0f;
    m_FinalGrdDataIn.m_fObjectHeight = 1.0f;
    m_FinalGrdDataIn.m_MasksOfGrdForTest[0] = 1;
    m_FinalGrdDataIn.m_MasksOfGrdForTest[1] = 0x80;
    m_FinalGrdDataInOut.m_i32FaceIndex = -1;
    m_FinalGrdDataInOut.m_eContactStatus = 3;
    m_FinalGrdDataInOut.m_ui8SectorNumber = 0;
    m_FinalGrdDataInOut.m_pGround = nullptr;
    m_ui8ProbeFlags = 0;
    m_unk8a0[0] = 0.0f;
    m_unk8a0[2] = 0.0f;
    m_unk8a0[1] = 0.0f;
    m_fUnk89c = 0.0f;
}

// 0x0012d810 CKSrvCamera_ResetState_maybe (XXL2 InitializeStateOfSrvCamera)
void CKSrvCamera::ResetState() {
    m_fScriptedCameraTimer = -1.0f;
    m_fBlendElapsed = 0.0f;
    m_bUnk884 = 0;
    m_baTemporaryFlags = 0;
    m_pPreviousCamera = nullptr;
    m_pCurrentCamera = nullptr;
    m_pNextCamera = nullptr;
    m_pCurrentSector = nullptr;
    m_pActiveConstraint = nullptr;
    m_pScriptedCameraHandle = nullptr;
    m_fSwitchTimer = 0.0f;
    m_fBlendDuration = 0.0f;
    m_bUnk885 = 0;
    m_fUnk8e4 = 1.0f;
    m_baTemporaryFlags &= 0xffffff7fu;
    for (SShakeNode* node = m_unk8e8; node != nullptr;) {  // the running shakes back to their pool
        SShakeNode* next = node->m_pNext;
        delete node;
        node = next;
    }
    m_unk8e8 = nullptr;
    m_baTemporaryFlags &= 0xfffffeffu;
    // The view axes of every pose are the world axes, the poses the null vector looking down +z.
    m_v3CalcAxisX = kAxisX;
    m_v3CalcAxisY = kAxisY;
    m_v3CalcAxisZ = kAxisZ;
    m_v3InternalAxisX = kAxisX;
    m_v3InternalAxisY = kAxisY;
    m_v3InternalAxisZ = kAxisZ;
    m_v3RealAxisX = kAxisX;
    m_v3RealAxisY = kAxisY;
    m_v3RealAxisZ = kAxisZ;
    m_v3FrameRight = kAxisX;
    m_v3FrameUp = kAxisY;
    m_v3FrameAt = kAxisZ;
    m_v3CalcPos = kNullVector;
    m_v3CalcTarget.x = 0.0f;
    m_v3CalcTarget.y = 0.0f;
    m_v3CalcTarget.z = 1.0f;
    m_v3SavedPos = m_v3CalcPos;
    m_v3SavedTarget = m_v3CalcTarget;
    m_InternalCamera.m_WorldPosition = kNullVector;
    m_InternalCamera.m_WorldTarget.x = 0.0f;
    m_InternalCamera.m_WorldTarget.y = 0.0f;
    m_InternalCamera.m_WorldTarget.z = 1.0f;
    m_v3RealPos = kNullVector;
    m_v3RealTarget.x = 0.0f;
    m_v3RealTarget.y = 0.0f;
    m_v3RealTarget.z = 1.0f;
    m_fCalcRoll = 0.0f;
    // BUG(original): the calculation pose gets (70, 100) as (far, fov) while the other poses get (fov 70, far 100).
    m_fCalcFar = 70.0f;
    m_fCalcFov = 100.0f;
    m_InternalCamera.m_fFar = 100.0f;
    m_InternalCamera.m_unk18 = 70.0f;
    m_fRealFov = 70.0f;
    m_fRealFar = 100.0f;
    m_baTemporaryFlags &= 0xfffdffffu;
    m_csfCollisionSmoothSpring.m_fTargetedValue = 0.0f;
    m_csfCollisionSmoothSpring.m_fCurrentSpeed = 0.0f;
    m_csfCollisionSmoothSpring.m_fCurrentValue = 0.0f;
    m_baTemporaryFlags &= 0xfffeffffu;
    m_unk8d0[0] = 0.0f;
    m_unk8d0[1] = 0.0f;
    m_unk8d0[2] = 0.0f;
    m_pUnk920 = nullptr;
    m_bUnk915 = 0;
    m_bUnk916 = 0;
    m_bUnk917 = 0;
    m_bUnk914 = 1;
    for (CameraNode* node = m_pUnk930; node != nullptr;) {  // the +0x930 node list back to its pool
        CameraNode* next = node->m_pNext;
        delete node;
        node = next;
    }
    m_pUnk930 = nullptr;
    m_bHeadingLockEnabled = 1;
    m_bHeadingLocked = 0;
    m_v3HeadingDir = kAxisZ;
    // The frame-time ring: 150 copies of the unscaled frame time (0.02 when the clock has none yet and the ring
    // was never filled).
    float frameTime = g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::FIXED_GAME_TIME];
    bool fillRing = true;
    if (frameTime == 0.0f) {
        if (m_fFrameTimeMean != 0.0f) {
            fillRing = false;
        } else {
            frameTime = 0x1.47ae14p-6f;  // 0x3ca3d70a
        }
    }
    if (fillRing) {
        float sum = 0.0f;
        m_fFrameTimeSum = 0.0f;
        m_ui32FrameTimeIndex = 0;
        for (uint32_t i = 0; i < 0x96; ++i) {
            sum = frameTime + sum;
            m_afFrameTimes[i] = frameTime;
        }
        m_fFrameTimeSum = sum;
        m_fFrameTimeMean = sum / 150.0f;
    }
    m_v3VelocityPos = kNullVector;
    m_v3VelocityTarget = kNullVector;
    m_v3VelocityAxis = kNullVector;
    m_ui32NbStacked = 0;
    m_unke24 = 0;
}

uint32_t CKSrvCamera::FindStackTarget(const IKSerializable* target) const {
    uint32_t index = 0;
    while (index < m_ui32NbStacked && m_aStack[index].m_pTarget != target) ++index;
    return index;
}

void CKSrvCamera::RemoveStackEntry(uint32_t index) {
    const uint32_t count = m_ui32NbStacked - 1;
    m_ui32NbStacked = count;
    if (index != count) {
        StackEntry& to = m_aStack[index];
        const StackEntry& from = m_aStack[count];
        to.m_pTarget = from.m_pTarget;
        to.m_unk04 = from.m_unk04;
        to.m_unk05 = from.m_unk05;
        to.m_unk0c = from.m_unk0c;
        to.m_unk08 = from.m_unk08;
        to.m_unk10[0] = from.m_unk10[0];
        to.m_unk10[1] = from.m_unk10[1];
        to.m_unk10[2] = from.m_unk10[2];
        to.m_unk10[3] = from.m_unk10[3];
        to.m_unk20 = from.m_unk20;
        to.m_unk24[0] = from.m_unk24[0];
        to.m_unk24[1] = from.m_unk24[1];
        to.m_unk24[2] = from.m_unk24[2];
    }
    m_baTemporaryFlags |= 0x800000u;
}

void CKSrvCamera::RemoveStackDuplicates(const IKSerializable* target) {
    for (uint32_t index = 1; index < m_ui32NbStacked; ++index) {
        if (m_aStack[index].m_pTarget == target) RemoveStackEntry(index);
    }
}

void CKSrvCamera::AddStackEntry(IKSerializable* target, uint8_t flagA) {
    StackEntry& entry = m_aStack[m_ui32NbStacked];
    entry.m_unk05 = 1;
    entry.m_unk20 = -1.0f;
    entry.m_pTarget = target;
    entry.m_unk04 = flagA;
    entry.m_unk0c = 0;
    entry.m_unk10[3] = 1.0f;
    entry.m_unk08 = -1.0f;
    entry.m_unk10[0] = 1.0f;
    entry.m_unk10[1] = 1.0f;
    entry.m_unk10[2] = 1.0f;
    entry.m_unk24[2] = kCameraStackFar;
    entry.m_unk24[0] = kCameraStackFar;
    entry.m_unk24[1] = kCameraStackFar;
    ++m_ui32NbStacked;
}

// The inlined stack push of UpdateInitialize (twice) and of 0x130cc8 CKSrvCamera_PushCamera_maybe.
void CKSrvCamera::PushStackTarget(IKSerializable* target, float blend) {
    uint32_t count = m_ui32NbStacked;
    if (count == 0) {
        StackEntry& entry = m_aStack[0];
        entry.m_unk0c = 0;
        entry.m_unk05 = 1;
        entry.m_unk04 = 0;
        entry.m_pTarget = target;
        entry.m_unk10[3] = 1.0f;
        entry.m_unk08 = blend;
        entry.m_unk10[0] = 1.0f;
        entry.m_unk10[1] = 1.0f;
        entry.m_unk10[2] = 1.0f;
        entry.m_unk20 = blend;
        entry.m_unk24[2] = kCameraStackFar;
        entry.m_unk24[0] = kCameraStackFar;
        entry.m_unk24[1] = kCameraStackFar;
        ++m_ui32NbStacked;
        m_baTemporaryFlags = (m_baTemporaryFlags & 0xff7fffffu) | 0x800000u;
        return;
    }
    uint32_t next = 1;
    uint32_t index = 1;
    if (1 < count) {
        do {
            for (;;) {  // the entries after the first: look for `target`
                ++next;
                if (m_aStack[index].m_pTarget == target) break;
                index = next & 0xff;
                if (count <= index) goto done;
            }
            --count;
            m_ui32NbStacked = count;
            if (index != count) {  // the last entry takes its place
                StackEntry& to = m_aStack[index];
                const StackEntry& from = m_aStack[count];
                to.m_pTarget = from.m_pTarget;
                to.m_unk04 = from.m_unk04;
                to.m_unk05 = from.m_unk05;
                to.m_unk0c = from.m_unk0c;
                to.m_unk08 = from.m_unk08;
                to.m_unk10[0] = from.m_unk10[0];
                to.m_unk10[1] = from.m_unk10[1];
                to.m_unk10[2] = from.m_unk10[2];
                to.m_unk10[3] = from.m_unk10[3];
                to.m_unk20 = from.m_unk20;
                to.m_unk24[0] = from.m_unk24[0];
                to.m_unk24[1] = from.m_unk24[1];
                to.m_unk24[2] = from.m_unk24[2];
            }
            index = next & 0xff;
            m_baTemporaryFlags = (m_baTemporaryFlags & 0xff7fffffu) | 0x800000u;
            count = m_ui32NbStacked;
        } while (index < count);
    }
done:
    if (m_aStack[0].m_pTarget != target || m_aStack[0].m_unk04 != 0) {
        m_baTemporaryFlags = (m_baTemporaryFlags & 0xff7fffffu) | 0x800000u;
    }
    m_aStack[0].m_pTarget = target;
    m_aStack[0].m_unk04 = 0;
    m_aStack[0].m_unk05 = 1;
}

// 0x0012eaa0 CKSrvCamera_FindZoneCameraAtPosition_maybe
IKCamera* CKSrvCamera::FindZoneCameraAtPosition(uint8_t refuse) {
    if (m_ui32NbStacked == 0 || m_aStack[0].m_pTarget == nullptr || m_ui32NbCameraSectorMode == 0) return nullptr;
    CSGLeaf* leaf = static_cast<CSGLeaf*>(m_aStack[0].m_pTarget);
    const RwMatrix* ltm = RwFrameGetLTM(leaf->m_pRwFrame);  // the stored LTM of the original, computed on demand
    for (CameraNode* node = *m_aCameraSectorMode[m_unk24[0]]; node != nullptr; node = node->m_pNext) {
        CKCameraSector* sector = static_cast<CKCameraSector*>(node->m_pObject);
        if (!sector->IsEnabledForFocusedHero() || !sector->ContainsPoint(&ltm->pos.x)) continue;
        IKCamera* camera = sector->FindValidCamera();
        if (camera != nullptr) return camera;
        if (refuse != 0) {
            if (m_unk24[0] == m_unk24[1]) return nullptr;
            if (m_ui32NbStacked == 0 || m_aStack[0].m_pTarget == nullptr) return nullptr;
            if (sector->FindValidCamera() != nullptr) return nullptr;  // asked a second time, as the original does
            for (CameraNode* previous = *m_aCameraSectorMode[m_unk24[1]]; previous != nullptr; previous = previous->m_pNext) {
                if (previous->m_pObject == sector) return nullptr;
            }
        }
    }
    return nullptr;
}

// 0x00130cc8 CKSrvCamera_PushCamera_maybe
void CKSrvCamera::PushCamera(float blend, IKSerializable* target, int32_t transition) {
    m_bUnk884 = 1;
    // The first half is the stack push (PushStackTarget; the new entry's blend values are -1, 0x00c4ace0 neighbour).
    const IKSerializable* const top = m_ui32NbStacked != 0 ? m_aStack[0].m_pTarget : nullptr;
    if (top != target && target != nullptr) PushStackTarget(target, -1.0f);
    if (transition == 0) {
        if ((m_baTemporaryFlags & 8u) == 0) {
            // The real pose is the start of the blend: the quaternion of the real axes, the real position and target.
            float matrix[16];
            std::memcpy(&matrix[0], &m_v3RealAxisX, 12);
            std::memcpy(&matrix[4], &m_v3RealAxisY, 12);
            std::memcpy(&matrix[8], &m_v3RealAxisZ, 12);
            std::memcpy(&matrix[12], &m_v3RealPos, 12);
            Quat_FromMatrix(reinterpret_cast<float*>(&m_unk7b0[9]), matrix);  // 0x7d4
            std::memcpy(&m_unk7b0[0], &m_v3RealPos, 12);
            std::memcpy(&m_unk7b0[3], &m_v3RealTarget, 12);
            m_fBlendElapsed = 0.0f;
            m_fBlendDuration = blend;
            m_baTemporaryFlags |= 0x20u;
        }
    } else {
        if (m_pNextCamera == nullptr) {
            if (blend == 0.0f && m_unke24 == 0) {
                // The target's world position becomes the focus (the same inlined code as UpdateInitialize's).
                CSGLeaf* first = m_ui32NbStacked != 0 ? static_cast<CSGLeaf*>(m_aStack[0].m_pTarget) : nullptr;
                const RwV3d* position;
                if (m_ui32NbStacked != 0 && first != nullptr) {
                    CSGBranch* parent = static_cast<CSGBranch*>(first->m_pParent);
                    if (parent == nullptr || parent->GetClassID() != 2) {
                        if ((m_baTemporaryFlags & 0x80000u) == 0) first->ForceWorldMatrixUpdate();
                        position = &RwFrameGetLTM(first->m_pRwFrame)->pos;
                    } else {
                        position = &first->m_pRwFrame->modelling.pos;
                    }
                } else {
                    position = reinterpret_cast<const RwV3d*>(&kNullVector);
                }
                m_v3FocusPos.x = position->x;
                m_v3FocusPos.y = position->y;
                m_v3FocusPos.z = position->z;
                m_v3FocusPosCopy = m_v3FocusPos;
                for (uint32_t i = 0; i < m_ui32NbStacked; ++i) {
                    CSGLeaf* leaf = static_cast<CSGLeaf*>(m_aStack[i].m_pTarget);
                    if (leaf == nullptr) continue;
                    CSGBranch* parent = static_cast<CSGBranch*>(leaf->m_pParent);
                    if ((parent == nullptr || parent->GetClassID() != 2) && (m_baTemporaryFlags & 0x80000u) == 0) {
                        leaf->ForceWorldMatrixUpdate();
                    }
                    const RwV3d& world = RwFrameGetLTM(leaf->m_pRwFrame)->pos;
                    m_aStack[i].m_unk24[0] = world.x;
                    m_aStack[i].m_unk24[1] = world.y;
                    m_aStack[i].m_unk24[2] = world.z;
                }
                // The sector and camera at the focus: the sectors that hold it, from the first, until one has a valid camera.
                CKCameraSector* sector = nullptr;
                CKCameraSector* firstSector = nullptr;
                IKCamera* camera = nullptr;
                bool picked = false;
                for (;;) {
                    sector = FindCameraSectorAtFocus(true, sector);
                    while (sector != nullptr && sector != firstSector) {
                        if (firstSector == nullptr) firstSector = sector;
                        camera = sector->FindValidCamera();
                        if (camera != nullptr) {
                            picked = true;
                            break;
                        }
                        sector = FindCameraSectorAtFocus(true, sector);
                    }
                    if (picked || m_unk24[0] == 0) break;
                    if (m_ui32NbCameraSectorMode != 0) m_unk24[0] = 0;
                    camera = nullptr;
                }
                if (sector != nullptr) {
                    if (sector != m_pCurrentSector) {
                        if (m_pCurrentSector != nullptr) m_pCurrentSector->FlushTriggerSignals();  // 0x129358
                        sector->QueueActivateSignals();                                            // 0x129140
                    }
                    if (camera != nullptr) {
                        m_pCurrentSector = sector;
                        m_pCurrentCamera = camera;
                    }
                }
            }
            m_pNextCamera = m_pCurrentCamera;
            m_ui8TransitionMode = 0;
        } else {
            m_ui8TransitionMode = 0;
        }
        m_fSwitchTimer = blend;
        m_baTemporaryFlags = (m_baTemporaryFlags | 0x400000u) & 0xffffffcfu;
        m_baTemporaryFlags |= 0x10u;
    }
    m_baTemporaryFlags &= 0xfffefffeu;
    m_unk8d0[0] = 0.0f;
    m_unk8d0[1] = 0.0f;
    m_unk8d0[2] = 0.0f;
}

// 0x001314f8 CKSrvCamera_SwitchCameraIfDifferent_maybe
void CKSrvCamera::SwitchCameraIfDifferent(float blend, IKSerializable* target, int32_t transition) {
    const IKSerializable* const top = m_ui32NbStacked != 0 ? m_aStack[0].m_pTarget : nullptr;
    if (top == target) return;
    PushCamera(blend, target, transition);
}

// ---- C2.4 step 6: the frustum sphere test and the fog accessors --------------------------------------------------------

// 0x0012c830 CKSrvCamera_TestSphereAgainstFrustum
uint32_t CKSrvCamera::TestSphereAgainstFrustum(const float sphere[4], int32_t lastPlane) const {
    if (lastPlane == -1) return 2;
    uint32_t result = 2;
    for (int32_t i = lastPlane; i >= 0; --i) {
        const float* plane = m_afFrustumPlanes[i];
        const float distance = ppc::fmadds(sphere[2], plane[2], ppc::fmadds(sphere[0], plane[0], sphere[1] * plane[1])) + plane[3];
        if (sphere[3] < distance) return 0;
        if (!(-sphere[3] >= distance)) result = 1;
    }
    return result;
}

namespace {
// The blended fog values of a camera transition (m_baTemporaryFlags bit 3), kept in the service's float block at +0xbdc.
float BlendedFog(const CKSrvCamera* camera, uint32_t offset) {
    return *reinterpret_cast<const float*>(camera->Ps3Field(offset));
}
const CKCameraFogDatas* FogDatasOf(const CKSrvCamera* camera) {
    return static_cast<const CKCameraFogDatas*>(camera->m_pCurrentCamera->m_unk38);
}
}  // namespace

// 0x0012be60 CKSrvCamera_GetFogStart_maybe
float CKSrvCamera::GetFogStart() const {
    if (m_pCurrentCamera == nullptr) return 0.0f;
    if ((m_baTemporaryFlags & 8) != 0) return BlendedFog(this, 0xc3c);
    return FogDatasOf(this)->m_fFogStart;
}

// 0x0012bea0 CKSrvCamera_GetFogEnd_maybe
float CKSrvCamera::GetFogEnd() const {
    if (m_pCurrentCamera == nullptr) return 1000.0f;
    if ((m_baTemporaryFlags & 8) != 0) return BlendedFog(this, 0xc30);
    return FogDatasOf(this)->m_fFogEnd;
}

// 0x0012bee0 FogManager_GetMainDensity_maybe
float CKSrvCamera::GetMainFogDensity() const {
    if (m_pCurrentCamera == nullptr) return 0.01f;  // 0x3c23d70a
    if ((m_baTemporaryFlags & 8) != 0) return BlendedFog(this, 0xbf0);
    return FogDatasOf(this)->m_fMainDensity;
}

// 0x0012bda0 FogManager_GetFarDensity_maybe
float CKSrvCamera::GetFarFogDensity() const {
    if (m_pCurrentCamera == nullptr) return 100.0f;
    if ((m_baTemporaryFlags & 8) != 0) return BlendedFog(this, 0xc10);
    return FogDatasOf(this)->m_fFarDensity;
}

// 0x0012be20 FogManager_GetFarDistance
float CKSrvCamera::GetFarFogDistance() const {
    if (m_pCurrentCamera == nullptr) return 0.01f;
    if ((m_baTemporaryFlags & 8) != 0) return BlendedFog(this, 0xc04);
    return FogDatasOf(this)->m_fFarDistance;
}

// 0x0012bfc0 FogManager_GetMainColor_maybe: without a current camera the white constant (0x00c50dfc).
void CKSrvCamera::GetMainFogColor(uint8_t color[4]) const {
    if (m_pCurrentCamera == nullptr) {
        std::memset(color, 0xff, 4);
    } else if ((m_baTemporaryFlags & 8) == 0) {
        std::memcpy(color, FogDatasOf(this)->m_cMainColor, 4);
    } else {
        std::memcpy(color, Ps3Field(0xbf4), 4);
    }
}

// 0x0012bf60 FogManager_GetColorForFarPass_maybe
void CKSrvCamera::GetFarFogColor(uint8_t color[4]) const {
    if (m_pCurrentCamera == nullptr) {
        std::memset(color, 0xff, 4);
    } else if ((m_baTemporaryFlags & 8) == 0) {
        std::memcpy(color, FogDatasOf(this)->m_cFarColor, 4);
    } else {
        std::memcpy(color, Ps3Field(0xc20), 4);
    }
}

// ---- step 5, FX: the shakes, the messages, the scripted camera and the constraint queries ----

namespace {

// The words of +0x8f8..+0x910: the fov approach state of Math_ApproachWithAccelDecel (7 floats; UpdateFrame steps it
// while +0x46c bit 8 is set, message 0x601 starts it).
float* FovApproachState(CKSrvCamera* camera) { return reinterpret_cast<float*>(camera->m_unk8f8); }

// +0x770: the dodge ejection (XXL2 m_v3DodgeEjection), summed from the camera's collisions (message 0x300).
float* DodgeEjection(CKSrvCamera* camera) { return reinterpret_cast<float*>(camera->m_unk770); }

// The first idle effect of a shake group, from the last one down (both QueueCameraEffect and StartQuake); null when all
// of them run.
CKQuakeCpntUpdater* FindIdleEffect(const CKSrvCamera::RefGroup& group) {
    for (uint32_t i = group.m_vRefs.m_ui32NbUsedElt; i != 0; --i) {
        CKQuakeCpntUpdater* effect = static_cast<CKQuakeCpntUpdater*>(group.m_vRefs.m_pBlock[i - 1]);
        if (effect->m_bRunning == 0) return effect;
    }
    return nullptr;
}

}  // namespace

// The node push of AddShake / QueueCameraEffect / StartQuake: the shakes-running bit, a node from the pool (the
// FreeListPool 0xceaa40 in the original) at the head of the list, the effect started.
static void PushShake(CKSrvCamera* camera, CKQuakeCpntUpdater* effect, CKQuakeCameraLauncher* source) {
    camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & 0xffffff7fu) | 0x80u;
    CKSrvCamera::SShakeNode* node = new CKSrvCamera::SShakeNode();
    node->m_pNext = nullptr;
    node->m_pSource = source;
    node->m_pEffect = effect;
    node->m_pNext = camera->m_unk8e8;
    camera->m_unk8e8 = node;
    effect->Start();  // CKQuakeCpntUpdater_Start 0x24f770
    // DEV: the start frame of every camera shake (the replay compares it with the recording's: LVL010's first fight intro
    // starts quake #141 at +585 and +617, from its CKExplosionFxData launchers).
    DOTD_LOG("camera: shake started (quake %p, launcher %p)", static_cast<void*>(effect->m_pQuake), static_cast<void*>(source));
}

// 0x0012c7d0 CKSrvCamera_FindIndexByKey_maybe
uint32_t CKSrvCamera::FindIndexByKey(const IKSerializable* key) const {
    if (key == nullptr) return 0;
    for (uint32_t i = m_vUnk8ec.m_ui32NbUsedElt; i != 0; --i) {
        if (m_vUnk8ec.m_pBlock[i - 1].m_pObject == key) return i - 1;
    }
    return 0;
}

// 0x0012cd40 CKSrvCamera_AddShake_maybe (no caller)
void CKSrvCamera::AddShake(CKQuakeCpntUpdater* effect, CKQuakeCameraLauncher* source) {
    PushShake(this, effect, source);
}

// 0x0012e300 CKSrvCamera_QueueCameraEffect_maybe
int32_t CKSrvCamera::QueueCameraEffect(uint32_t group, CKQuakeCameraLauncher* source) {
    CKQuakeCpntUpdater* effect = FindIdleEffect(m_vUnk8ec.m_pBlock[group]);
    if (effect == nullptr) return 0;
    PushShake(this, effect, source);
    return 1;
}

// 0x0012eee8 CKSrvCamera_StartQuake_maybe: the group of the source's quake (the first one from the front).
int32_t CKSrvCamera::StartQuake(CKQuakeCameraLauncher* source) {
    const IKSerializable* quake = source->m_pQuake;
    if (quake == nullptr) return 0;
    uint32_t index = 0;
    while (index < m_vUnk8ec.m_ui32NbUsedElt && m_vUnk8ec.m_pBlock[index].m_pObject != quake) ++index;
    if (index == m_vUnk8ec.m_ui32NbUsedElt) {
        // BUG(original): without the group the original reads the element before the array (offset -0x10). The remake
        // starts nothing (no LVL010 launcher is without its group).
        return 0;
    }
    CKQuakeCpntUpdater* effect = FindIdleEffect(m_vUnk8ec.m_pBlock[index]);
    if (effect == nullptr) return 0;
    PushShake(this, effect, source);
    return 1;
}

// 0x0012b9a0 CKSrvCamera_StopAllShakes_maybe (no caller; the same as message 0x604)
void CKSrvCamera::StopAllShakes() {
    if ((m_baTemporaryFlags & 0x80u) == 0) return;
    for (SShakeNode* node = m_unk8e8; node != nullptr; node = node->m_pNext) node->m_pEffect->Stop();
    for (SShakeNode* node = m_unk8e8; node != nullptr;) {
        SShakeNode* next = node->m_pNext;
        delete node;  // back to the FreeListPool in the original
        node = next;
    }
    m_unk8e8 = nullptr;
    m_baTemporaryFlags &= 0xffffff7fu;
}

// 0x0012ba78 CKSrvCamera_AccumulateShake_maybe (no caller): the scale is whatever f2 holds (passed through).
uint8_t CKSrvCamera::AccumulateShake(float dt, float scale, float sum[6], CKQuakeCpntUpdater* effect) {
    float out[15];
    effect->EvaluateScaled(dt, scale, out);
    for (int32_t i = 0; i < 6; ++i) sum[i] = sum[i] + out[i];
    return effect->m_bRunning;
}

// 0x0012dca0 CKSrvCamera_ApplyCameraEffects_maybe (XXL2 ApplyQuakeIfNecessary). Every running shake is evaluated with its
// source's distance attenuation (1 without a source); a shake that stopped leaves the list (after its evaluation, which
// was the zero of the stopped effect). The sums: outputs 0-2 move the calculation target (+0x55c), then the position
// (+0x550), along the calculation axes (+0x574 / +0x580 / +0x58c; fmadds, x then y then z axis); outputs 3-5 are the
// angles (degrees) of three rotations of an identity matrix about those axes, which then turns the axes themselves.
void CKSrvCamera::ApplyCameraEffects(float dt) {
    if ((m_baTemporaryFlags & 0x80u) == 0) return;
    float sum[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    SShakeNode* previous = nullptr;
    SShakeNode* node = m_unk8e8;
    while (node != nullptr) {
        float scale = 1.0f;
        if (node->m_pSource != nullptr) scale = node->m_pSource->GetDistanceAttenuation();
        CKQuakeCpntUpdater* effect = node->m_pEffect;
        float out[15];
        effect->EvaluateScaled(dt, scale, out);
        SShakeNode* next = node->m_pNext;
        if (effect->m_bRunning == 0) {
            if (m_unk8e8 == node) {
                previous = nullptr;
                m_unk8e8 = next;
            } else {
                previous->m_pNext = next;
            }
            delete node;  // back to the FreeListPool in the original
        } else {
            previous = node;
        }
        node = next;
        for (int32_t i = 0; i < 6; ++i) sum[i] = sum[i] + out[i];
    }
    const CVector3* axes[3] = {&m_v3CalcAxisX, &m_v3CalcAxisY, &m_v3CalcAxisZ};
    for (int32_t a = 0; a < 3; ++a) {
        m_v3CalcTarget.x = ppc::fmadds(sum[a], axes[a]->x, m_v3CalcTarget.x);
        m_v3CalcTarget.y = ppc::fmadds(sum[a], axes[a]->y, m_v3CalcTarget.y);
        m_v3CalcTarget.z = ppc::fmadds(sum[a], axes[a]->z, m_v3CalcTarget.z);
    }
    for (int32_t a = 0; a < 3; ++a) {
        m_v3CalcPos.x = ppc::fmadds(sum[a], axes[a]->x, m_v3CalcPos.x);
        m_v3CalcPos.y = ppc::fmadds(sum[a], axes[a]->y, m_v3CalcPos.y);
        m_v3CalcPos.z = ppc::fmadds(sum[a], axes[a]->z, m_v3CalcPos.z);
    }
    CMatrix34 rotation;
    std::memset(&rotation, 0, sizeof(rotation));  // the pads are stack garbage in the original (never read)
    rotation.m_right = {1.0f, 0.0f, 0.0f};
    rotation.m_ui32Flags = 0x20003;
    rotation.m_up = {0.0f, 1.0f, 0.0f};
    rotation.m_at = {0.0f, 0.0f, 1.0f};
    rotation.m_pos = {0.0f, 0.0f, 0.0f};
    Mat4_RotateInPlace(&rotation, &m_v3CalcAxisX, sum[3]);
    Mat4_RotateInPlace(&rotation, &m_v3CalcAxisY, sum[4]);
    Mat4_RotateInPlace(&rotation, &m_v3CalcAxisZ, sum[5]);
    Mat4_TransformVectors(&rotation, &m_v3CalcAxisX, &m_v3CalcAxisX, 1);
    Mat4_TransformVectors(&rotation, &m_v3CalcAxisY, &m_v3CalcAxisY, 1);
    Mat4_TransformVectors(&rotation, &m_v3CalcAxisZ, &m_v3CalcAxisZ, 1);
    if (m_unk8e8 == nullptr) m_baTemporaryFlags &= 0xffffff7fu;
}

// 0x00130200 CKSrvCamera_HandleMessage (XXL2 CKSrvCamera::MessageProc, which has the 0x300 part).
int32_t CKSrvCamera::MessageProc(uint16_t message, void* data) {
    if (message == 0x600) {
        m_unkbc = *static_cast<const uint32_t*>(data);  // the fov record index (its low byte, signed, is read by 0x601)
        return 0;
    }
    if (message == 0x601) {
        // The fov factor: the approach at +0x8f8 (Math_ApproachWithAccelDecel's state) heads for factor x the current
        // camera's fov; with a record (+0xbf, -1: none) its three parameters (+0x2c + 12 * index: words 0, 2, 1) are the
        // approach's. A factor of 1 only touches an approach that runs (+0x46c bit 8), and sets the target to the fov.
        const float factor = *static_cast<const float*>(data);
        const int32_t index = static_cast<int8_t>(m_unkbc & 0xffu);
        float* s = FovApproachState(this);
        const float* record = index != -1 ? reinterpret_cast<const float*>(&m_unk2c[index * 3]) : nullptr;
        if (factor == 1.0f) {
            if ((m_baTemporaryFlags & 0x100u) == 0) return 0;
            if (record == nullptr) {
                s[4] = 0.0f;
                s[3] = m_pCurrentCamera->m_unk18;
                s[5] = m_pCurrentCamera->m_unk18;
            } else {
                s[4] = 0.0f;
                s[0] = record[0];
                s[1] = record[2];
                s[2] = record[1];
                s[5] = m_pCurrentCamera->m_unk18;
            }
        } else if (record == nullptr) {
            s[4] = 0.0f;
            s[6] = 0.0f;
            s[3] = factor * m_pCurrentCamera->m_unk18;
            s[5] = factor * m_pCurrentCamera->m_unk18;
        } else {
            s[0] = record[0];
            s[1] = record[2];
            s[2] = record[1];
            s[5] = factor * m_pCurrentCamera->m_unk18;
            if ((m_baTemporaryFlags & 0x100u) == 0) {
                s[4] = 0.0f;
                s[6] = 0.0f;
                s[3] = m_pCurrentCamera->m_unk18;
            }
        }
        m_baTemporaryFlags = (m_baTemporaryFlags & 0xfffffeffu) | 0x100u;
        return 0;
    }
    if (message == 0x604) {
        if ((m_baTemporaryFlags & 0x80u) == 0) return 0;
        for (SShakeNode* node = m_unk8e8; node != nullptr; node = node->m_pNext) node->m_pEffect->Stop();
        for (SShakeNode* node = m_unk8e8; node != nullptr;) {
            SShakeNode* next = node->m_pNext;
            delete node;
            node = next;
        }
        m_unk8e8 = nullptr;
        m_baTemporaryFlags &= 0xffffff7fu;
        return 0;
    }
    if (message != 0x300) return 1;
    // 0x300: the collisions of the camera's colliding life (CKSrvCollision_ProcessPairs). The ejection restarts from the
    // null vector; for every collision of the push sphere (+0x750) with a volume that has properties bit 12, a contact
    // set and response bit 2: the interpenetration along the normal (response bit 4) or along y, added when the sphere
    // is the second volume, subtracted when it is the first (fmadds of -d).
    m_baTemporaryFlags = (m_baTemporaryFlags & 0xfffffdffu) | 0x200u;
    float* ejection = DodgeEjection(this);
    ejection[0] = kNullVector.x;
    ejection[1] = kNullVector.y;
    ejection[2] = kNullVector.z;
    for (ICollision* collision = static_cast<ICollision*>(data); collision != nullptr; collision = collision->m_pNext) {
        if (collision->GetBoundingVolume1() != m_pDodgeBSPushCam &&
            collision->GetBoundingVolume2() != m_pDodgeBSPushCam) {
            continue;
        }
        IKSerializable* const first = collision->GetBoundingVolume1();
        IKSerializable* const pushSphere = m_pDodgeBSPushCam;
        if (collision->HasContactSet() == 0) continue;
        const bool sphereFirst = first == pushSphere;
        IKSerializable* other = sphereFirst ? collision->GetBoundingVolume2() : collision->GetBoundingVolume1();
        if ((static_cast<IKBoundingVolume*>(other)->m_ui16PropertiesFlags & 0x1000u) == 0) continue;
        if (collision->AreResponseParamsActive(2) == 0) continue;
        const CVector3* direction = &kAxisY;
        if (collision->AreResponseParamsActive(4) != 0) direction = collision->GetNormale12();
        float depth = collision->GetdInterpenetration();
        if (sphereFirst) depth = -depth;
        const float x = ppc::fmadds(depth, direction->x, ejection[0]);
        const float z = ppc::fmadds(depth, direction->z, ejection[2]);
        const float y = ppc::fmadds(depth, direction->y, ejection[1]);
        ejection[0] = x;
        ejection[2] = z;
        ejection[1] = y;
    }
    return 0;
}

// 0x0012ac08 CKSrvCamera_SetPlayerCanMoveCamera
void CKSrvCamera::SetFlag46CBit2WhenZero(int32_t value) {
    if (value == 0) {
        m_baTemporaryFlags = (m_baTemporaryFlags & 0xfffffffbu) | 4u;
        return;
    }
    if ((m_baTemporaryFlags & 0x4000u) != 0) return;
    m_baTemporaryFlags &= 0xfffffffbu;
}

// 0x0012b420 CKSrvCamera_CanStartScriptedCamera_maybe: the delay +0xe08 (a float word) since the last handle's time
// (fcmpu + cror: NaN is false).
bool CKSrvCamera::CanStartScriptedCamera(float time) const {
    if (m_pScriptedCameraHandle != nullptr) return false;
    return (time - m_fScriptedCameraTimer) >= IKCamera::AsFloat(m_unke08);
}

// 0x0012b4f0 CKSrvCamera_SetActiveScriptedCamera_maybe
void CKSrvCamera::SetActiveScriptedCamera(float time, IKSerializable* handle) {
    if (handle != nullptr) {
        if (m_pScriptedCameraHandle != nullptr) {
            // ScriptedCameraHandle_Release_maybe 0x166130 (k2000/components/CKCameraEventCpnt.cpp). STUB(C2.8): the
            // scripted camera handles (CKCameraEventCpnt) are scripting; nothing activates one natively yet.
            DOTD_STUB_ONCE("CKSrvCamera_SetActiveScriptedCamera_maybe: ScriptedCameraHandle_Release_maybe 0x166130 (C2.8)");
        }
        m_fScriptedCameraTimer = time;
    }
    m_pScriptedCameraHandle = handle;
}

// 0x0012b558 CKSrvCamera_IsPointInActiveConstraint_maybe
bool CKSrvCamera::IsPointInActiveConstraint(const float* point, uint32_t sectorMode) const {
    for (uint32_t i = 0; i < m_ui32NbUnke00; ++i) {
        const CKCameraConstraint* constraint = static_cast<const CKCameraConstraint*>(m_apUnke00[i]);
        uint32_t flags;
        std::memcpy(&flags, &constraint->m_unk20, sizeof(flags));
        if ((flags & 0x100000u) == 0) continue;
        if (constraint->IsEnabledFor(sectorMode) && constraint->ContainsPoint(point)) return true;
    }
    return false;
}

// ---- step 5, FX: the heading lock and the direction lock ----

namespace {

// The clamp before Math_Acosf in the lock functions: at most -1 (fcmpu + cror lt|eq), at least 1; NaN stays.
float ClampCosine(float c) {
    if (c <= -1.0f) return -1.0f;
    if (c >= 1.0f) return 1.0f;
    return c;
}

}  // namespace

// 0x00132d88 CKSrvCamera_CaptureHeroHeadingLock_maybe. With the lock enabled (+0x64d), no cinematic owner and the focused
// hero's camera target first on the stack, the lock holds (+0x64c): the hero's move vector (the game manager's vt+0x130)
// and a fifth of the angle between the calculation and the real view directions in the ground plane (each (x, 0, z)
// normalised unless its length is 0; the dot product as the original sums it) are kept, the position reference is the
// null vector. Otherwise the lock is dropped.
void CKSrvCamera::CaptureHeroHeadingLock() {
    if (m_bHeadingLockEnabled == 0) return;
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    IKSerializable* hero = manager->GetFocusedHeroCamera();  // vt+0x120
    if (m_unke24 != 0 || hero == nullptr || m_ui32NbStacked == 0 || m_aStack[0].m_pTarget != hero) {
        m_bHeadingLocked = 0;
        return;
    }
    float x1 = m_v3CalcAxisZ.x;
    float z1 = m_v3CalcAxisZ.z;
    float y1 = 0.0f;
    float length = Sqrtf(ppc::fmadds(z1, z1, ppc::fmadds(x1, x1, 0.0f)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        z1 = z1 * inverse;
        x1 = x1 * inverse;
        y1 = inverse * 0.0f;
    }
    float x2 = m_v3RealAxisZ.x;
    float z2 = m_v3RealAxisZ.z;
    float y2 = 0.0f;
    length = Sqrtf(ppc::fmadds(z2, z2, ppc::fmadds(x2, x2, 0.0f)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        z2 = z2 * inverse;
        x2 = x2 * inverse;
        y2 = inverse * 0.0f;
    }
    const float dot = ppc::fmadds(z1, z2, ppc::fmadds(x2, x1, y1 * y2));
    const float angle = crt::Acosf(ClampCosine(dot));
    m_bHeadingLocked = 1;
    const float* heading = manager->GetFocusedHeroMoveVector();  // vt+0x130
    m_v3LockHeroHeading.x = heading[0];
    m_v3LockHeroHeading.z = heading[2];
    m_v3LockHeroHeading.y = heading[1];
    m_fLockAngle = angle * 0.2f;
    m_v3LockHeroPos = kNullVector;
}

// 0x0012b648 CKSrvCamera_ReleaseHeroHeadingLock_maybe. The lock holds while the focused hero's camera target is first on
// the stack, the hero's targeting position (vt+0x128) differs from the kept one and its move vector (vt+0x130) is within
// the kept angle of the kept one (the angle not reached; NaN keeps it).
void CKSrvCamera::ReleaseHeroHeadingLock() {
    if (m_bHeadingLocked == 0) return;
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    IKSerializable* hero = manager->GetFocusedHeroCamera();  // vt+0x120
    if (hero != nullptr && m_ui32NbStacked != 0 && m_aStack[0].m_pTarget == hero) {
        const float* position = manager->GetFocusedHeroPosition();  // vt+0x128
        if (position[0] != m_v3LockHeroPos.x || m_v3LockHeroPos.y != position[1] || m_v3LockHeroPos.z != position[2]) {
            const float* move = manager->GetFocusedHeroMoveVector();  // vt+0x130
            const float dot = ppc::fmadds(move[2], m_v3LockHeroHeading.z,
                                          ppc::fmadds(move[0], m_v3LockHeroHeading.x, move[1] * m_v3LockHeroHeading.y));
            const float angle = std::fabs(crt::Acosf(ClampCosine(dot)));
            if (!(m_fLockAngle <= angle)) return;
        }
    }
    m_bHeadingLocked = 0;
}

// 0x0012bc98 CKSrvCamera_EnableDirectionLock_maybe (the hero's jumps): the ground normal (+0x8c4) is `direction`, turned
// to point up; the ground reference B (+0x8b8) the focus copy (+0x490). The first lock (bit 0 of +0x46c clear) sets bit
// 0, and when the reference A was never set (bit 16) copies B to it (+0x8ac) and sets bit 16.
void CKSrvCamera::EnableDirectionLock(const CVector3* direction) {
    const CVector3 d = *direction;
    m_v3GroundNormal.x = d.x;
    m_v3GroundNormal.y = d.y;
    m_v3GroundNormal.z = d.z;
    if (m_v3GroundNormal.y < 0.0f) {
        m_v3GroundNormal.z = -d.z;
        m_v3GroundNormal.y = -d.y;
        m_v3GroundNormal.x = -d.x;
    }
    m_v3GroundRefB.x = m_v3FocusPosCopy.x;
    m_v3GroundRefB.z = m_v3FocusPosCopy.z;
    m_v3GroundRefB.y = m_v3FocusPosCopy.y;
    if ((m_baTemporaryFlags & 1u) != 0) return;
    m_baTemporaryFlags = (m_baTemporaryFlags & 0xfffffffeu) | 1u;
    if ((m_baTemporaryFlags & 0x10000u) != 0) return;
    m_v3GroundRefA = m_v3GroundRefB;
    m_baTemporaryFlags = (m_baTemporaryFlags & 0xfffeffffu) | 0x10000u;
}

// ---- step 5, FX: the camera parameter blend and the camera transition ----

namespace {

// A float field of the service by its PS3 offset (the transition state +0x7b0..+0x864 and the parameter blend
// +0xbdc..+0xc3c are word arrays in the header).
float& FieldF(CKSrvCamera* camera, uint32_t offset) {
    return *reinterpret_cast<float*>(camera->Ps3Field(offset));
}
uint32_t& FieldW(CKSrvCamera* camera, uint32_t offset) {
    return *reinterpret_cast<uint32_t*>(camera->Ps3Field(offset));
}
uint8_t& FieldB(CKSrvCamera* camera, uint32_t offset) {
    return *camera->Ps3Field(offset);
}
// A word of the camera's fog data (+0x38, a CKCameraFogDatas) by its PS3 offset +0x04..+0x27. PORT: through the
// first member (the words after the vtable hold no pointers), so the x64 layout is read right too.
const uint8_t* FogField(const IKCamera* camera, uint32_t offset) {
    const CKCameraFogDatas* fog = static_cast<const CKCameraFogDatas*>(camera->m_unk38);
    return reinterpret_cast<const uint8_t*>(fog->m_cMainColor) + (offset - 0x04);
}
float FogF(const IKCamera* camera, uint32_t offset) {
    return *reinterpret_cast<const float*>(FogField(camera, offset));
}
uint32_t FogW(const IKCamera* camera, uint32_t offset) {
    return *reinterpret_cast<const uint32_t*>(FogField(camera, offset));
}

// The blended fog values: (fog data offset, the service's FloatApproach {target, speed, current}) in the original's order.
struct FogBlendField {
    uint32_t fogOffset;
    uint32_t serviceOffset;
};
constexpr FogBlendField kFogBlend[7] = {{0x08, 0xbdc}, {0x0c, 0xbe8}, {0x14, 0xbfc}, {0x1c, 0xc08},
                                        {0x18, 0xc14}, {0x20, 0xc28}, {0x24, 0xc34}};

// One byte of the colour blend: (1 - u) * from + u * to (fmadds of the converted bytes), truncated (fctidz).
uint8_t BlendColorByte(float u, float w, uint8_t from, uint8_t to) {
    const float a = static_cast<float>(static_cast<double>(from));
    const float b = static_cast<float>(static_cast<double>(to));
    return static_cast<uint8_t>(ppc::fctidz(static_cast<double>(ppc::fmadds(w, a, u * b))));
}

// The game's cosine of the eased transition (inlined polynomial for a clear sign bit, the library's cosf of -x else).
float GameCosf(float x) { return std::signbit(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }

// The end of a transition, the same bit sequence everywhere in UpdateCameraTransition: bit 3 off, bit 2 off unless
// bit 14 holds, bits 4-5 off.
void EndTransitionFlags(CKSrvCamera* camera) {
    camera->m_baTemporaryFlags &= ~8u;
    if ((camera->m_baTemporaryFlags & 0x4000u) == 0) camera->m_baTemporaryFlags &= ~4u;
    camera->m_baTemporaryFlags &= ~0x30u;
}

// |b - a| with the original's sum: fmadds(dz, dz, fmadds(dx, dx, dy * dy)), then fsqrts.
float DistanceYXZ(const CVector3& a, const CVector3& b) {
    const float dy = b.y - a.y;
    const float dx = b.x - a.x;
    const float dz = b.z - a.z;
    return std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
}
float LengthYXZ(const float* v) { return std::sqrt(ppc::fmadds(v[2], v[2], ppc::fmadds(v[0], v[0], v[1] * v[1]))); }

// The calculation axes (and position) as an RwMatrix, its quaternion, the slerp from the blend's start quaternion
// (+0x7d4) at `t`, and the matrix of the result (its at row is read).
void SlerpCalcAxes(CKSrvCamera* camera, float t, const CVector3* position, CMatrix34* matrix) {
    std::memset(matrix, 0, sizeof(*matrix));  // the flags word: stack garbage & 0xfffdfffc in the original (not read)
    matrix->m_right = camera->m_v3CalcAxisX;
    matrix->m_up = camera->m_v3CalcAxisY;
    matrix->m_at = camera->m_v3CalcAxisZ;
    matrix->m_pos = *position;
    float q[4];
    float out[4];
    Quat_FromMatrix(q, reinterpret_cast<const float*>(matrix));
    Quat_Slerp(t, out, &FieldF(camera, 0x7d4), q);
    Quat_ToMatrix(out, matrix);
}

}  // namespace

// 0x0012b0b0 CKSrvCamera_StartCameraParamBlend_maybe. Without a blend time or a previous camera every fog value is the
// new camera's (target and current); otherwise each approach heads for the new camera's value at the speed
// |previous - new| / blend time, and without `keepVelocities` starts from the previous camera's values (the two colours
// too). The colours' start words are copied to +0xbf8 / +0xc24.
void CKSrvCamera::StartCameraParamBlend(uint8_t keepVelocities) {
    if (m_fBlendDuration == 0.0f || m_pPreviousCamera == nullptr) {
        for (const FogBlendField& f : kFogBlend) {
            if (f.serviceOffset == 0xc14) continue;  // +0x18 is not set here
            const float value = FogF(m_pCurrentCamera, f.fogOffset);
            FieldF(this, f.serviceOffset) = value;
            FieldF(this, f.serviceOffset + 8) = value;
        }
    } else {
        for (const FogBlendField& f : kFogBlend) {
            const float previous = FogF(m_pPreviousCamera, f.fogOffset);
            const float next = FogF(m_pCurrentCamera, f.fogOffset);
            FieldF(this, f.serviceOffset) = next;
            FieldF(this, f.serviceOffset + 4) = std::fabs(previous - next) / m_fBlendDuration;
        }
        if (keepVelocities == 0) {
            FieldW(this, 0xbf4) = FogW(m_pPreviousCamera, 0x04);
            FieldW(this, 0xc20) = FogW(m_pPreviousCamera, 0x10);
            for (const FogBlendField& f : kFogBlend) {
                FieldF(this, f.serviceOffset + 8) = FogF(m_pPreviousCamera, f.fogOffset);
            }
        }
    }
    FieldW(this, 0xbf8) = FieldW(this, 0xbf4);
    FieldW(this, 0xc24) = FieldW(this, 0xc20);
}

// 0x0012d290 CKSrvCamera_UpdateCameraParamBlend_maybe: the two colours (+0xbf4 / +0xc20) blended byte by byte from
// their start words (+0xbf8 / +0xc24) to the current camera's at u = elapsed / blend time, then one FloatApproach_Step of
// each fog value.
void CKSrvCamera::UpdateCameraParamBlend(float dt) {
    const float u = m_fBlendElapsed / m_fBlendDuration;
    const float w = 1.0f - u;
    const uint32_t colorOffsets[2][3] = {{0xbf4, 0xbf8, 0x04}, {0xc20, 0xc24, 0x10}};
    for (const auto& c : colorOffsets) {
        const uint32_t fromWord = FieldW(this, c[1]);
        const uint32_t toWord = FogW(m_pCurrentCamera, c[2]);
        uint8_t from[4];
        uint8_t to[4];
        std::memcpy(from, &fromWord, 4);
        std::memcpy(to, &toWord, 4);
        uint8_t* out = &FieldB(this, c[0]);
        for (int32_t i = 0; i < 4; ++i) out[i] = BlendColorByte(u, w, from[i], to[i]);
    }
    for (const FogBlendField& f : kFogBlend) FloatApproach_Step(dt, &FieldF(this, f.serviceOffset));
}

// 0x00133f28 CKSrvCamera_UpdateCameraTransition_maybe (XXL2 ApplyTransitionIfNecessary). Three kinds of transition move
// the calculation pose (+0x550 position, +0x55c target, the axes, fov / far / roll) from the blend's start (+0x7b0 position,
// +0x7c8 fov, +0x7cc far, +0x7d0 roll, +0x7d4 quaternion):
// - a camera switch (+0x46c bit 3) owned by a cinematic (+0xe24): the scaled game time over +0x824, eased by the mode
//   +0x831 (0 linear, 1 cosine, 2 square, 3 square root);
// - a camera switch otherwise: the position follows the real position by an accel/decel approach of the distance
//   (+0x84c; the record of mode +0x831 at +0xc0), the share of the way made sets the blend;
// - a push without switch (bit 5): the orientation alone over +0x824 (the frame time).
// A switch also runs the framing (+0x885), the parameter blend and, between two cameras with vt+0x70, the ground
// clearance with its vertical spring (+0x740). A pose further than 999999 from the real one is undone.
void CKSrvCamera::UpdateCameraTransition(float dt) {
    const CVector3 savedPos = m_v3CalcPos;
    const float savedFov = m_fCalcFov;
    const float savedFar = m_fCalcFar;
    const CVector3 savedTarget = m_v3CalcTarget;
    const float savedRoll = m_fCalcRoll;
    bool blending = false;  // r21
    if ((m_baTemporaryFlags & 8u) != 0) {
        blending = true;
        if (m_fBlendDuration == 0.0f) {
            blending = false;
            m_baTemporaryFlags &= ~0x20000u;
            m_csfCollisionSmoothSpring.m_fTargetedValue = 0.0f;
            m_csfCollisionSmoothSpring.m_fCurrentSpeed = 0.0f;
            m_csfCollisionSmoothSpring.m_fCurrentValue = 0.0f;
        }
    }

    bool groundCheck;  // the path to 0x134080 (the ground clearance between two cameras)
    if ((m_baTemporaryFlags & 8u) != 0) {
        const float duration = m_fBlendDuration;
        if (duration == 0.0f) {
            EndTransitionFlags(this);
            m_bUnk884 = 0;
        } else if (m_unke24 != 0) {
            // The cinematic switch.
            float elapsed = g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[0] + m_fBlendElapsed;
            m_fBlendElapsed = elapsed;
            float total = duration;
            if (elapsed >= total) {
                m_fBlendElapsed = total;
                EndTransitionFlags(this);
                total = m_fBlendDuration;
                elapsed = m_fBlendElapsed;
                m_bUnk884 = 0;
            }
            float u = elapsed / total;
            const uint8_t mode = m_ui8PreviousTransitionMode;
            if (mode == 2) {
                u = u * u;
            } else if (mode == 3) {
                u = Sqrtf(u);
            } else if (mode == 1) {
                const float c = GameCosf((1.0f - u) * 3.1415927f);
                u = ppc::fmadds(c, 0.5f, 0.5f);
            }
            const CVector3 p = m_v3CalcPos;
            const float sx = FieldF(this, 0x7b0), sy = FieldF(this, 0x7b4), sz = FieldF(this, 0x7b8);
            m_v3CalcPos.x = ppc::fmadds(u, p.x - sx, sx);
            m_v3CalcPos.y = ppc::fmadds(u, p.y - sy, sy);
            m_v3CalcPos.z = ppc::fmadds(u, p.z - sz, sz);
            CMatrix34 matrix;
            SlerpCalcAxes(this, u, &p, &matrix);
            const float d = DistanceYXZ(m_v3CalcPos, m_v3CalcTarget);
            m_v3CalcTarget.z = ppc::fmadds(d, matrix.m_at.z, m_v3CalcPos.z);
            m_v3CalcTarget.x = ppc::fmadds(d, matrix.m_at.x, m_v3CalcPos.x);
            m_v3CalcTarget.y = ppc::fmadds(d, matrix.m_at.y, m_v3CalcPos.y);
            m_fCalcFov = ppc::fmadds(u, m_fCalcFov - FieldF(this, 0x7c8), FieldF(this, 0x7c8));
            m_fCalcFar = ppc::fmadds(u, m_fCalcFar - FieldF(this, 0x7cc), FieldF(this, 0x7cc));
            m_fCalcRoll = ppc::fmadds(u, m_fCalcRoll - FieldF(this, 0x7d0), FieldF(this, 0x7d0));
            ComputeViewBasis();
            ApplyTransitionFraming(dt);
        } else {
            // The switch outside cinematics: the position.
            float t = 1.0f;          // f29 (f24 = 1)
            float px, py, pz;        // f26 f28 f27: the new position
            if (FieldF(this, 0x7f4) == 0.0f) {
                FieldB(this, 0x849) = 0;
                FieldF(this, 0x80c) = m_v3VelocityPos.x;
                FieldF(this, 0x814) = m_v3VelocityPos.z;
                FieldF(this, 0x810) = m_v3VelocityPos.y;
                px = m_v3CalcPos.x;
                py = m_v3CalcPos.y;
                pz = m_v3CalcPos.z;
            } else if (FieldB(this, 0x849) == 0) {
                px = m_v3CalcPos.x;
                py = m_v3CalcPos.y;
                pz = m_v3CalcPos.z;
            } else {
                float dx = m_v3CalcPos.x - m_v3RealPos.x;
                float dy = m_v3CalcPos.y - m_v3RealPos.y;
                float dz = m_v3CalcPos.z - m_v3RealPos.z;
                float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
                int32_t sign = 1;  // r26
                if (length != 0.0f) {
                    const float inverse = 1.0f / length;
                    dz = dz * inverse;
                    dx = dx * inverse;
                    dy = dy * inverse;
                    if (length < 0.0f) sign = -1;
                } else {
                    length = 0.0f;
                }
                const float distance = std::fabs(length);
                const float* velocity = &m_v3VelocityPos.x;
                float* s = &FieldF(this, 0x84c);  // the accel/decel state (7 floats)
                if (static_cast<int32_t>(FieldW(this, 0x840)) == 0) {
                    const float a = LengthYXZ(velocity);
                    const float b = LengthYXZ(&m_v3VelocityTarget.x);
                    s[4] = a <= b ? LengthYXZ(&m_v3VelocityTarget.x) : LengthYXZ(velocity);  // +0x85c
                }
                const float* record = reinterpret_cast<const float*>(&m_unkc0[m_ui8PreviousTransitionMode * 3]);
                const float top = LengthYXZ(velocity) + record[1];
                float k = LengthYXZ(velocity);
                s[2] = top;
                k = k / record[1];
                k = k * k;
                k = ppc::fmadds(k, k, 1.0f);
                s[0] = k * record[0];
                s[1] = k * record[2];
                s[6] = LengthYXZ(velocity);
                s[5] = distance;
                s[3] = 0.0f;
                const float step = Math_ApproachWithAccelDecel(dt, s);
                if (s[3] == s[5]) {
                    FieldB(this, 0x849) = 0;
                    FieldW(this, 0x840) = 0;
                    px = m_v3CalcPos.x;
                    py = m_v3CalcPos.y;
                    pz = m_v3CalcPos.z;
                } else {
                    const float signed_ = step * static_cast<float>(static_cast<double>(sign));
                    pz = ppc::fmadds(dz, signed_, m_v3RealPos.z);
                    px = ppc::fmadds(dx, signed_, m_v3RealPos.x);
                    py = ppc::fmadds(dy, signed_, m_v3RealPos.y);
                    const int32_t previous = static_cast<int32_t>(FieldW(this, 0x840));
                    FieldW(this, 0x840) = sign * previous < 0 ? 0u : static_cast<uint32_t>(sign);
                }
            }
            // The share of the way from the start (+0x7b0) made.
            const CVector3 start = {FieldF(this, 0x7b0), FieldF(this, 0x7b4), FieldF(this, 0x7b8)};
            const float sy0 = m_v3CalcPos.y - start.y;
            const float sx0 = m_v3CalcPos.x - start.x;
            const float sz0 = m_v3CalcPos.z - start.z;
            const float whole2 = ppc::fmadds(sz0, sz0, ppc::fmadds(sx0, sx0, sy0 * sy0));
            if (Sqrtf(whole2) != 0.0f) {
                const float ny = py - start.y;
                const float nx = px - start.x;
                const float nz = pz - start.z;
                const float made2 = ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny));
                const float share = std::fabs(Sqrtf(made2) / Sqrtf(whole2));
                if (!(share >= 1.0f)) t = std::fabs(Sqrtf(made2) / Sqrtf(whole2));
            }
            m_fBlendElapsed = t * m_fBlendDuration;
            float tx, ty, tz;  // f11 f13 f0: the new target
            if (FieldF(this, 0x808) == 0.0f) {
                FieldB(this, 0x848) = 0;
                FieldF(this, 0x818) = m_v3VelocityAxis.x;
                FieldF(this, 0x820) = m_v3VelocityAxis.z;
                FieldF(this, 0x81c) = m_v3VelocityAxis.y;
                tx = px + (m_v3CalcTarget.x - m_v3CalcPos.x);
                ty = py + (m_v3CalcTarget.y - m_v3CalcPos.y);
                tz = pz + (m_v3CalcTarget.z - m_v3CalcPos.z);
            } else if (FieldB(this, 0x848) == 0) {
                const float d = DistanceYXZ(m_v3CalcPos, m_v3CalcTarget);
                tx = ppc::fmadds(d, m_v3CalcAxisZ.x, px);
                tz = ppc::fmadds(d, m_v3CalcAxisZ.z, pz);
                ty = ppc::fmadds(d, m_v3CalcAxisZ.y, py);
            } else {
                CMatrix34 matrix;
                const CVector3 position = m_v3CalcPos;
                SlerpCalcAxes(this, t, &position, &matrix);
                const float d = DistanceYXZ(m_v3CalcPos, m_v3CalcTarget);
                tx = ppc::fmadds(d, matrix.m_at.x, px);
                tz = ppc::fmadds(d, matrix.m_at.z, pz);
                ty = ppc::fmadds(d, matrix.m_at.y, py);
                if (t == 1.0f) FieldB(this, 0x848) = 0;
            }
            if (FieldB(this, 0x849) == 0 && FieldB(this, 0x848) == 0) {
                EndTransitionFlags(this);
                m_bUnk884 = 0;
            }
            m_v3CalcPos = {px, py, pz};
            m_v3CalcTarget = {tx, ty, tz};
            m_fCalcFov = ppc::fmadds(t, m_fCalcFov - FieldF(this, 0x7c8), FieldF(this, 0x7c8));
            m_fCalcFar = ppc::fmadds(t, m_fCalcFar - FieldF(this, 0x7cc), FieldF(this, 0x7cc));
            m_fCalcRoll = ppc::fmadds(t, m_fCalcRoll - FieldF(this, 0x7d0), FieldF(this, 0x7d0));
            ComputeViewBasis();
            ApplyTransitionFraming(dt);
        }
        groundCheck = blending ? m_unke24 == 0 : (m_baTemporaryFlags & 0x20000u) != 0;
    } else {
        if ((m_baTemporaryFlags & 0x20u) != 0) {
            // The push blend: the orientation alone.
            float duration = m_fBlendDuration;
            if (duration <= m_fBlendElapsed) {
                m_baTemporaryFlags &= ~0x20u;
                m_bUnk884 = 0;
            } else {
                const float elapsed = dt + m_fBlendElapsed;
                m_fBlendElapsed = elapsed;
                if (duration <= elapsed) {
                    m_baTemporaryFlags &= ~0x20u;
                    duration = m_fBlendDuration;
                    m_bUnk884 = 0;
                    m_fBlendElapsed = duration;
                }
                CMatrix34 matrix;
                const CVector3 position = m_v3CalcPos;
                SlerpCalcAxes(this, m_fBlendElapsed / duration, &position, &matrix);
                const float d = DistanceYXZ(m_v3CalcPos, m_v3CalcTarget);
                m_v3CalcTarget.z = ppc::fmadds(d, matrix.m_at.z, m_v3CalcPos.z);
                m_v3CalcTarget.x = ppc::fmadds(d, matrix.m_at.x, m_v3CalcPos.x);
                m_v3CalcTarget.y = ppc::fmadds(d, matrix.m_at.y, m_v3CalcPos.y);
                ComputeViewBasis();
            }
        }
        groundCheck = blending ? m_unke24 == 0 : (m_baTemporaryFlags & 0x20000u) != 0;
    }
    // (0x134068 / 0x134340: with r21 the cinematic owner is tested first; a cinematic switch goes to the bit-17 test.)
    if (blending && m_unke24 != 0) groundCheck = (m_baTemporaryFlags & 0x20000u) != 0;

    if (groundCheck && m_pPreviousCamera != nullptr && m_pPreviousCamera->Vf70() != 0 && m_pCurrentCamera->Vf70() != 0) {
        const float yBefore = m_v3CalcPos.y;
        CVector3 saved = savedPos;
        ResolveGroundClearance(dt, &m_v3CalcPos, &m_v3RealPos, &saved, &m_v3FocusPosCopy);
        bool moved = false;  // r10
        bool revert = false;
        if ((m_baTemporaryFlags & 0x4000u) == 0) {
            const float y = m_v3CalcPos.y;
            if (yBefore != y) {
                const float a = yBefore - m_v3RealPos.y;
                const float b = y - m_v3RealPos.y;
                const float c = y - yBefore;
                const bool down = a <= 0.0f && c >= 0.0f && b <= 0.1f;
                const bool up = a >= 0.0f && c <= 0.0f && b >= -0.1f;
                moved = true;
                if (down || up) {
                    if ((m_baTemporaryFlags & 0x20000u) == 0) m_baTemporaryFlags |= 0x20000u;
                } else {
                    revert = true;
                }
            }
        } else {
            revert = true;
        }
        if (revert) {
            m_fBlendElapsed = m_fBlendDuration;
            m_v3CalcPos = savedPos;
            m_v3CalcTarget = savedTarget;
            m_baTemporaryFlags &= ~0x20000u;
            m_csfCollisionSmoothSpring.m_fTargetedValue = 0.0f;
            m_csfCollisionSmoothSpring.m_fCurrentSpeed = 0.0f;
            m_csfCollisionSmoothSpring.m_fCurrentValue = 0.0f;
        }
        if ((m_baTemporaryFlags & 0x20000u) != 0 && !moved) {
            // The vertical spring (+0x740 target, +0x744 current, +0x748 speed): the height over the real position.
            CClippedSpringFloat32& spring = m_csfCollisionSmoothSpring;
            float current = std::fabs(m_v3CalcPos.y - m_v3RealPos.y);
            const float gap = spring.m_fTargetedValue - current;
            spring.m_fCurrentValue = current;
            bool step = true;
            float accel;
            const float speed = spring.m_fCurrentSpeed;
            if (gap != 0.0f) {
                accel = ppc::fmsubs(gap, 25.0f, speed * 5.0f);
            } else if (speed != 0.0f) {
                accel = speed * -5.0f;
            } else {
                step = false;
                accel = 0.0f;
            }
            if (step) {
                const float newSpeed = ppc::fmadds(accel, dt, speed);
                current = ppc::fmadds(dt, newSpeed, current);
                if (current <= 0.0f) current = 0.0f;
                else if (current >= 1000000.0f) current = 1000000.0f;
                if (!(std::fabs(newSpeed) <= 0.0f) || !(std::fabs(current - spring.m_fTargetedValue) <= 0.0f)) {
                    spring.m_fCurrentSpeed = newSpeed;
                    spring.m_fCurrentValue = current;
                } else {
                    current = spring.m_fTargetedValue;
                    spring.m_fCurrentSpeed = 0.0f;
                    spring.m_fCurrentValue = spring.m_fTargetedValue;
                }
            }
            if (m_v3RealPos.y >= m_v3CalcPos.y) {
                m_v3CalcPos.y = current + m_v3CalcPos.y;
            } else {
                m_v3CalcPos.y = m_v3CalcPos.y - current;
            }
            if ((m_baTemporaryFlags & 8u) == 0 && std::fabs(yBefore - m_v3CalcPos.y) <= 0.01f) {
                m_baTemporaryFlags &= ~0x20000u;
                spring.m_fCurrentSpeed = 0.0f;
                spring.m_fTargetedValue = 0.0f;
                spring.m_fCurrentValue = 0.0f;
            }
        }
        ComputeViewBasis();
    }

    if (DistanceYXZ(m_v3RealPos, m_v3CalcPos) > 999999.0f) {
        m_v3CalcPos = savedPos;
        m_v3CalcTarget = savedTarget;
        m_fCalcFov = savedFov;
        m_fCalcFar = savedFar;
        m_fCalcRoll = savedRoll;
        ComputeViewBasis();
        EndTransitionFlags(this);
    }
}

// The framing step of the switch transitions (0x1345b4..0x1347d4, inline in UpdateCameraTransition): with +0x885 the
// view turned to keep the focus (the focus copy, or the middle of the first two targets) raised by the profile's safe
// offset inside the frame margins, the target put back on the turned view at the focus' depth (at least 1); then the
// parameter blend.
void CKSrvCamera::ApplyTransitionFraming(float dt) {
    if (m_bUnk885 != 0) {
        CMatrix34 matrix;
        std::memset(&matrix, 0, sizeof(matrix));
        matrix.m_right = m_v3CalcAxisX;
        matrix.m_up = m_v3CalcAxisY;
        matrix.m_at = m_v3CalcAxisZ;
        matrix.m_pos = m_v3CalcPos;
        float point[3] = {m_v3FocusPosCopy.x, m_v3FocusPosCopy.y, m_v3FocusPosCopy.z};
        if ((m_ui32NbStacked & 0xffu) > 1) {
            point[0] = (point[0] + m_aStack[1].m_unk24[0]) * 0.5f;
            point[1] = (point[1] + m_aStack[1].m_unk24[1]) * 0.5f;
            point[2] = (point[2] + m_aStack[1].m_unk24[2]) * 0.5f;
        }
        if (m_pCurrentCamera != nullptr) {
            point[1] = point[1] + m_afSafeOffsetYFromBasicTarget[m_pCurrentCamera->GetEffectiveProfileIndex()];
        }
        // (The original calls IKCamera_GetEffectiveProfileIndex_maybe with the current camera even when it is null.)
        const uint8_t profile = m_pCurrentCamera != nullptr ? m_pCurrentCamera->GetEffectiveProfileIndex() : 0;
        if (AdjustViewToKeepTargetInFrameMargins(m_fCalcFov, reinterpret_cast<float*>(&matrix), point, profile) != 0) {
            const float depth0 = (point[1] - m_v3CalcPos.y) * matrix.m_at.y;
            const float depth1 = ppc::fmadds(point[0] - m_v3CalcPos.x, matrix.m_at.x, depth0);
            float depth = std::fabs(ppc::fmadds(point[2] - m_v3CalcPos.z, matrix.m_at.z, depth1));
            if (depth < 1.0f) depth = 1.0f;
            m_v3CalcTarget.x = ppc::fmadds(depth, matrix.m_at.x, m_v3CalcPos.x);
            m_v3CalcTarget.y = ppc::fmadds(depth, matrix.m_at.y, m_v3CalcPos.y);
            m_v3CalcTarget.z = ppc::fmadds(depth, matrix.m_at.z, m_v3CalcPos.z);
            ComputeViewBasis();
        }
    }
    UpdateCameraParamBlend(dt);
}
