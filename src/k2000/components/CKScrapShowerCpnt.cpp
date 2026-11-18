// CKScrapShowerCpnt.cpp - reconstructed original translation unit 0x4a66d0-0x4a7460 (GAME_TOC1, main_toc1), 22 functions, 19 live.
// Primary class: CKScrapShowerCpnt  key 0x5c6  category Component  size 0x20  vtable 0xb286c0
// Other owners: CKHkScrapShower (5)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4a66d0  CKScrapShowerCpnt_Delete
//   [ ] 0x4a6720  RegisterCKScrapShowerCpntClass
//   [ ] 0x4a6798  _GLOBAL__I_4a6798
//   [x] 0x4a67a8  CKHkScrapShower_SetPieceShadowScale_maybe  (CKScrapShowerCpnt::SetPieceShadowScale)
//   [x] 0x4a6820  CKHkScrapShower_RegisterPieceShadow_maybe  (CKScrapShowerCpnt::RegisterPieceShadow)
//   [x] 0x4a6928  CKHkScrapShower_TryCameraShake_maybe  (CKScrapShowerCpnt::TryCameraShake)
//   [x] 0x4a69f0  CKScrapShowerCpnt_PostLoad  (the IKMecaCpnt PostLoad, inherited)
//   [x] 0x4a6a18  CKScrapShowerCpnt_RecursiveRegistration  (the IKMecaCpnt RecursiveRegistration (returns 1): the default)
//   [x] 0x4a6a40  CKScrapShowerCpnt_Destroy
//   [x] 0x4a6a80  CKScrapShowerCpnt_DeletingDestructor  (the base destructor + delete: the C++ chain)
//   [x] 0x4a6ac8  CKScrapShowerCpnt_Destructor  (the base destructor: the C++ chain)
//   [x] 0x4a6af8  CKScrapShowerCpnt_DestructBody  (the base destructor: the C++ chain)
//   [ ] 0x4a6b28  CKScrapShowerCpnt_Construct  [dead]
//   [ ] 0x4a6b60  CKScrapShowerCpnt_Construct_2  [dead]
//   [x] 0x4a6b98  CKScrapShowerCpnt_DeleteArray
//   [x] 0x4a6c38  CKHkScrapShower_LaunchScrapAtPoint_maybe  (CKScrapShowerCpnt::LaunchScrapAtPoint)
//   [ ] 0x4a6c88  FUN_004a6c88  [dead]
//   [x] 0x4a6cb0  CKHkScrapShower_UnregisterPieceShadow_maybe  (CKScrapShowerCpnt::UnregisterPieceShadow)
//   [x] 0x4a6d30  CKScrapShowerCpnt_CreateArray
//   [x] 0x4a6de0  CKScrapShowerCpnt_Create
//   [ ] 0x4a6e38  CKScrapShowerCpnt_Save
//   [x] 0x4a7138  CKScrapShowerCpnt_Load
//
//   [ ] 0x9c4ec8  CKScrapShowerCpnt_IsKindOfClass  [inline]
//   [x] 0x9c4f00  CKScrapShowerCpnt_GetClassType  [inline]
//   [x] 0x9c4f08  CKScrapShowerCpnt_GetClassID  [inline]
#include "k2000/components/CKScrapShowerCpnt.h"

#include "k2000/components/CKQuakeCameraLauncher.h"
#include "k2000/components/CKShadowCpnt.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/managers/CKInput.h"
#include "k2000/managers/CKVibrationData.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvShadow.h"

// 0x004a7138 CKScrapShowerCpnt_Load
int32_t CKScrapShowerCpnt::Load(IKFile* file, int32_t type) {
    IKMecaCpnt::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk0c);
        ReadU8(file, &m_ui8NbEntries);
        m_aEntries = new Entry[m_ui8NbEntries];  // OperatorNewArray(n * 8)
        for (uint32_t i = 0; i < m_ui8NbEntries; ++i) {
            IKFile_ReadRef(file, &m_aEntries[i].m_pRef);
            m_aEntries[i].m_bEnabled = 1;
        }
        IKFile_ReadRef(file, &m_pUnk10);
        ReadF32LE(file, &m_unk18);
        ReadF32LE(file, &m_unk1c);
        IKFile_ReadRef(file, &m_pUnk14);
    }
    return 1;
}

// C2.8 port-all P11.

// 0x004a6a40 CKScrapShowerCpnt_Destroy
void CKScrapShowerCpnt::Destroy() {
    IKMecaCpnt::Destroy();  // 0x003f7a78: vt+0x54
    delete[] m_aEntries;    // OperatorDelete (the block of OperatorNewArray(n * 8), no cookie)
}

// C2.8 port-all P18.
// 0x004a67a8 CKHkScrapShower_SetPieceShadowScale_maybe
void CKScrapShowerCpnt::SetPieceShadowScale(uint8_t index, float scale) {
    static_cast<CKShadowCpnt*>(m_aEntries[index].m_pRef)->SetShadowLong(scale);   // 0x001fe7e0
    static_cast<CKShadowCpnt*>(m_aEntries[index].m_pRef)->SetShadowWidth(scale);  // 0x001fe7e8
}

// C2.8 port-all P18.
// 0x004a6820 CKHkScrapShower_RegisterPieceShadow_maybe
int32_t CKScrapShowerCpnt::RegisterPieceShadow(IKSerializable* node, CKShadowGround* ground) {
    if (ground->m_bUsed_maybe != 0) return -1;
    if (m_ui8NbEntries == 0) return -1;
    int32_t found = -1;
    for (uint32_t i = 0;;) {
        found = m_aEntries[i].m_bEnabled != 0 ? static_cast<int32_t>(i) : -1;
        i = (i + 1) & 0xffu;
        if (i == m_ui8NbEntries) {
            if (found == -1) return -1;
            break;
        }
        if (found != -1) break;
    }
    static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)->RegisterCaster(m_aEntries[found].m_pRef, node, ground, 0, nullptr, 0);  // 0x001fb6f8
    m_aEntries[found].m_bEnabled = 0;
    return found;
}

// C2.8 port-all P18.
// 0x004a6928 CKHkScrapShower_TryCameraShake_maybe
void CKScrapShowerCpnt::TryCameraShake(float distanceSq, const CVector3* position) {
    const float range = m_unk1c * m_unk1c;
    if (!(range >= distanceSq)) return;  // fcmpu + cror gt|eq: NaN skips
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
    const float percent = static_cast<float>(static_cast<double>((r * 100u) >> 16));
    if (!(percent < m_unk18)) return;  // bge: NaN skips
    static_cast<CKQuakeCameraLauncher*>(m_pUnk10)->SetSourcePosition(position);  // 0x001532c8
    static_cast<CKQuakeCameraLauncher*>(m_pUnk10)->Trigger();                    // 0x001533c0
    static_cast<CKInput*>(g_pEngine->m_input)->PlayVibration(static_cast<const CKVibrationData*>(m_pUnk14));  // 0x00107d38
}

// C2.8 port-all P18.
// 0x004a6c38 CKHkScrapShower_LaunchScrapAtPoint_maybe. The accessor also gets f2 = 1.0 (TOC +0x6250) and the caller's r6,
// which LaunchAtPoint does not read.
void CKScrapShowerCpnt::LaunchScrapAtPoint(const CVector3* pos, const CVector3* target, float speed, IKSerializable* owner) {
    CKProjectileAccessor* accessor = static_cast<CKProjectileAccessor*>(m_pUnk0c);
    if (accessor->m_pProjectileType == nullptr) return;
    accessor->LaunchAtPoint(pos, target, speed, nullptr, owner, nullptr);  // 0x001f2cd8
}

// C2.8 port-all P18.
// 0x004a6cb0 CKHkScrapShower_UnregisterPieceShadow_maybe
void CKScrapShowerCpnt::UnregisterPieceShadow(uint8_t index, IKSerializable* /*node*/, CKShadowGround* ground) {
    if (ground->m_bUsed_maybe == 0) return;
    static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)->UnregisterCaster(ground, m_aEntries[index].m_pRef);  // 0x001fd6f0
    m_aEntries[index].m_bEnabled = 1;
}
