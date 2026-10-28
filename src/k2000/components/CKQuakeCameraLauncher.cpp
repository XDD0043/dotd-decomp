// CKQuakeCameraLauncher.cpp - reconstructed original translation unit 0x1531c8-0x153988 (GAME_TOC1, main_toc1), 21 functions, 17 live.
// Primary class: CKQuakeCameraLauncher  key 0xa86  category Component  size 0x28  vtable 0xb1a9f0
// Other owners: CameraShakeData (7), CameraShake (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1531c8  CKQuakeCameraLauncher_Delete
//   [ ] 0x153218  CKQuakeCameraLauncher_RecursiveRegistration
//   [x] 0x153278  CKQuakeCameraLauncher_vf50
//   [x] 0x153280  CKQuakeCameraLauncher_vf54
//   [ ] 0x153288  CameraShakeData_CallVf54_maybe
//   [ ] 0x1532c8  CameraShakeData_SetPosition_maybe
//   [ ] 0x1532e8  CameraShakeData_SetAttachedObject_maybe  [dead]
//   [ ] 0x1532f0  CameraShakeData_ClearAttachedObject_maybe  [dead]
//   [ ] 0x153300  CameraShakeData_GetStaticPositionPtr_maybe  [dead]
//   [ ] 0x153310  CameraShakeData_GetPositionPtr_maybe  [dead]
//   [ ] 0x153338  RegisterCKQuakeCameraLauncherClass
//   [ ] 0x1533b0  _GLOBAL__I_1533b0
//   [x] 0x1533c0  CKQuakeCameraLauncher_Trigger
//   [ ] 0x153408  CKQuakeCameraLauncher_Save
//   [ ] 0x153430  CKQuakeCameraLauncher_Destroy
//   [x] 0x153458  CKQuakeCameraLauncher_DeleteArray
//   [x] 0x153500  CKQuakeCameraLauncher_CreateArray
//   [x] 0x1535b8  CKQuakeCameraLauncher_PostLoad
//   [x] 0x153608  CKQuakeCameraLauncher_Create
//   [x] 0x153660  CKQuakeCameraLauncher_GetDistanceAttenuation
//   [x] 0x153750  CKQuakeCameraLauncher_Load
//
//   [ ] 0x9a7bd0  CKQuakeCameraLauncher_IsKindOfClass  [inline]
//   [x] 0x9a7bf8  CKQuakeCameraLauncher_GetClassType  [inline]
//   [x] 0x9a7c00  CKQuakeCameraLauncher_GetClassID  [inline]
//   [ ] 0x9a7c08  CKQuakeCameraLauncher_Destructor  [inline]
//   [ ] 0x9a7c38  CKQuakeCameraLauncher_DeletingDestructor  [inline]
#include "k2000/components/CKQuakeCameraLauncher.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"

namespace {
// One Read of count words, then every word byte-swapped in place (an lwbrx/stw loop on the PS3). The
// file is little-endian: on a little-endian host the bytes stay as they are.
void ReadWordsLE(IKFile* file, void* dst, uint32_t count) {
    ReadRaw(file, dst, count * 4);
    uint8_t* p = static_cast<uint8_t*>(dst);
    for (uint32_t i = 0; i < count; ++i, p += 4) {
        const uint32_t v = static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8) |
                           (static_cast<uint32_t>(p[2]) << 16) | (static_cast<uint32_t>(p[3]) << 24);
        std::memcpy(p, &v, 4);
    }
}
}  // namespace

// 0x00153750 CKQuakeCameraLauncher_Load
int32_t CKQuakeCameraLauncher::Load(IKFile* file, int32_t type) {
    KBase1DCC::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pQuake);
    ReadF32LE(file, &m_unk1c);
    ReadF32LE(file, &m_unk20);
    ReadU8(file, &m_unk24);
    IKFile_ReadRef(file, &m_unk0c);
    ReadWordsLE(file, &m_unk10, 3);  // one 12-byte read
    return 1;
}

// 0x001535b8 CKQuakeCameraLauncher_PostLoad
int32_t CKQuakeCameraLauncher::PostLoad(int32_t type) {
    KBase1DCC::PostLoad(type);
    m_unk08 = static_cast<int32_t>(static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->FindIndexByKey(m_pQuake));
    return 1;
}

// 0x001533c0 CKQuakeCameraLauncher_Trigger
void CKQuakeCameraLauncher::Trigger() {
    if (m_pQuake != nullptr) {
        static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->QueueCameraEffect(static_cast<uint32_t>(m_unk08), this);
    }
}

// 0x00153660 CKQuakeCameraLauncher_GetDistanceAttenuation. The squared distance as the original sums it:
// fmadds(dz, dz, fmadds(dx, dx, dy * dy)); Math_Sqrtf is fsqrts.
float CKQuakeCameraLauncher::GetDistanceAttenuation() const {
    const IKCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_pCurrentCamera;
    if (m_unk24 != 0) return 1.0f;
    const float* source = &m_unk10.x;
    if (m_unk0c != nullptr) source = &static_cast<const CSGMovable*>(m_unk0c)->m_pRwFrame->ltm.pos.x;
    const float dy = source[1] - camera->m_WorldPosition.y;
    const float dx = source[0] - camera->m_WorldPosition.x;
    const float dz = source[2] - camera->m_WorldPosition.z;
    const float distance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (distance < m_unk1c) return 1.0f;
    if (distance > m_unk20) return 0.0f;
    return (m_unk20 - distance) / (m_unk20 - m_unk1c);
}
