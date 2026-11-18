// CKProjectileAccessor.cpp - reconstructed original translation unit 0x1f2868-0x1f32e0 (GAME_TOC1, main_toc1), 28 functions, 28 live.
// Primary class: CKProjectileAccessor  key 0x1e0c  category Logic  size 0xc  vtable 0xb1e858
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f2868  CKProjectileAccessor_Delete
//   [x] 0x1f28b8  CKProjectileAccessor_vf50
//   [x] 0x1f28c0  CKProjectileAccessor_vf54
//   [x] 0x1f28c8  CKProjectileAccessor_GetMaxCount
//   [x] 0x1f28e8  CKProjectileAccessor_GetActiveCount
//   [x] 0x1f2908  CKProjectileAccessor_Launch
//   [x] 0x1f2988  CKProjectileAccessor_Launch
//   [x] 0x1f2a10  CKProjectileAccessor_Launch8C
//   [x] 0x1f2a98  CKProjectileAccessor_Launch90
//   [x] 0x1f2b28  CKProjectileAccessor_Launch94
//   [x] 0x1f2bb0  CKProjectileAccessor_LaunchA0
//   [x] 0x1f2c50  CKProjectileAccessor_LaunchAtPointEx
//   [x] 0x1f2cd8  CKProjectileAccessor_LaunchAtPoint
//   [ ] 0x1f2d58  RegisterCKProjectileAccessorClass
//   [ ] 0x1f2dd0  _GLOBAL__I_1f2dd0
//   [x] 0x1f2de0  CKProjectileAccessor_RecursiveRegistration
//   [ ] 0x1f2e08  CKProjectileAccessor_Save
//   [x] 0x1f2e30  CKProjectileAccessor_Destroy  (header)
//   [x] 0x1f2e68  CKProjectileAccessor_DeletingDestructor  (the destructor; delete)
//   [x] 0x1f2eb0  CKProjectileAccessor_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x1f2ee0  CKProjectileAccessor_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x1f2f10  CKProjectileAccessor_Construct
//   [x] 0x1f2f50  CKProjectileAccessor_Construct_2  (the constructor's second C++ variant)
//   [x] 0x1f2f90  CKProjectileAccessor_DeleteArray
//   [x] 0x1f3038  CKProjectileAccessor_GetFreeSlots
//   [x] 0x1f3068  CKProjectileAccessor_CreateArray
//   [x] 0x1f3130  CKProjectileAccessor_Create
//   [x] 0x1f3190  CKProjectileAccessor_Load
//
//   [x] 0x9b07a0  CKProjectileAccessor_IsKindOfClass  [inline]
//   [ ] 0x9b07c8  CKProjectileAccessor_GetClassType  [inline]
//   [ ] 0x9b07d0  CKProjectileAccessor_GetClassID  [inline]
#include "k2000/logic/CKProjectileAccessor.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/IKProjectileType.h"

// 0x001f28c8 CKProjectileAccessor_GetMaxCount
int32_t CKProjectileAccessor::GetMaxCount() const {
    const IKProjectileType* type = static_cast<const IKProjectileType*>(m_pProjectileType);
    return type == nullptr ? 0 : type->m_ui8MaxProjectiles;
}

// 0x001f28e8 CKProjectileAccessor_GetActiveCount
int32_t CKProjectileAccessor::GetActiveCount() const {
    const IKProjectileType* type = static_cast<const IKProjectileType*>(m_pProjectileType);
    return type == nullptr ? 0 : type->m_ui8NbOfActiveProjectiles;
}

// 0x001f3038 CKProjectileAccessor_GetFreeSlots (the difference as a byte)
int32_t CKProjectileAccessor::GetFreeSlots() const {
    const IKProjectileType* type = static_cast<const IKProjectileType*>(m_pProjectileType);
    if (type == nullptr) return 0;
    return static_cast<uint8_t>(type->m_ui8MaxProjectiles - type->m_ui8NbOfActiveProjectiles);
}

// 0x001f2908 CKProjectileAccessor_Launch
uint8_t CKProjectileAccessor::Launch(const CVector3* pos, const CVector3* dir, float speed, IKSerializable* owner,
                                     const RwMatrix* matrix) {
    IKProjectileType* type = static_cast<IKProjectileType*>(m_pProjectileType);
    if (type == nullptr) return 0;
    return type->Launch(m_pProjectileData, pos, dir, speed, owner, matrix);  // vt+0x84
}

// 0x001f2988 CKProjectileAccessor_Launch (vt+0x88)
uint8_t CKProjectileAccessor::LaunchEx(const CVector3* pos, const CVector3* dir, float speed, IKSerializable* damage,
                                       IKSerializable* owner, const RwMatrix* matrix) {
    IKProjectileType* type = static_cast<IKProjectileType*>(m_pProjectileType);
    if (type == nullptr) return 0;
    return type->LaunchEx(m_pProjectileData, pos, dir, speed, damage, owner, matrix);  // vt+0x88
}

// 0x001f2a98 CKProjectileAccessor_Launch90 (vt+0x90; CKBlackBall_Fire's charged shots at a locked target)
uint8_t CKProjectileAccessor::Launch90(const CVector3* pos, const CVector3* dir, float speed, IKSerializable* damage,
                                       IKSerializable* owner, IKSerializable* target, const RwMatrix* matrix) {
    IKProjectileType* type = static_cast<IKProjectileType*>(m_pProjectileType);
    if (type == nullptr) return 0;
    // vt+0x90 0x9b0b98 (no type overrides it): LaunchEx with the type itself as the damage, the caller's r7 (owner) as the
    // owner and its r8 (target) as the matrix; damage and matrix are dropped. As in the original (merge of P01 / P03).
    (void)damage;
    (void)matrix;
    return type->Launch90Body(m_pProjectileData, pos, dir, speed, owner, target);
}

// 0x001f2c50 CKProjectileAccessor_LaunchAtPointEx (vt+0x9c)
uint8_t CKProjectileAccessor::LaunchAtPointEx(const CVector3* pos, const CVector3* target, float speed,
                                              IKSerializable* damage, IKSerializable* owner) {
    IKProjectileType* type = static_cast<IKProjectileType*>(m_pProjectileType);
    if (type == nullptr) return 0;
    return type->LaunchAtPointEx(m_pProjectileData, pos, target, speed, damage, owner);  // vt+0x9c
}

// 0x001f3190 CKProjectileAccessor_Load: KBase1DCC's Load, then (level data only) the two references.
int32_t CKProjectileAccessor::Load(IKFile* file, int32_t type) {
    KBase1DCC::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pProjectileType);
        IKFile_ReadRef(file, &m_pProjectileData);
    }
    return 1;
}

// 0x001f2a10 CKProjectileAccessor_Launch8C
uint8_t CKProjectileAccessor::Launch8C(const CVector3* pos, const CVector3* dir, float speed, void* /*r6*/, void* r7,
                                       void* r8, void* r9) {
    IKProjectileType* type = static_cast<IKProjectileType*>(m_pProjectileType);
    if (type == nullptr) return 0;
    return type->LaunchAtTarget(m_pProjectileData, pos, dir, speed, static_cast<IKSerializable*>(r7),
                                static_cast<IKSerializable*>(r8), static_cast<const RwMatrix*>(r9));  // vt+0x8c
}

// 0x001f2b28 CKProjectileAccessor_Launch94: the type's vt+0x94 (KStub_Return0_9b0be8 but in
// CKProjectileTypeFromExplosion; C2.8 port-final F04: the call kept).
uint8_t CKProjectileAccessor::Launch94(const CVector3* pos, const CVector3* dir, float speed, void* /*r6*/, void* r7,
                                       void* r8, void* r9) {
    IKProjectileType* type = static_cast<IKProjectileType*>(m_pProjectileType);
    if (type == nullptr) return 0;
    return type->LaunchAtTargetSpot(m_pProjectileData, pos, dir, speed, static_cast<IKSerializable*>(r7),
                                    static_cast<const ProjectileTarget*>(r8), static_cast<const RwMatrix*>(r9));  // vt+0x94
}

// 0x001f2bb0 CKProjectileAccessor_LaunchA0: the two floats at r8 copied to the stack (read with a type only), then
// vt+0xa0 with r7 the owner, the copy and r9 the matrix (KStub_Return0_9b0c48 but in CKProjectileTypeSplineLock; C2.8
// port-last Z4: the call wired).
uint8_t CKProjectileAccessor::LaunchA0(const CVector3* pos, const CVector3* dir, float speed, void* /*r6*/, void* r7,
                                       const float* r8, void* r9) {
    IKProjectileType* type = static_cast<IKProjectileType*>(m_pProjectileType);
    if (type == nullptr) return 0;
    const float point[2] = {r8[0], r8[1]};
    return type->LaunchAtScreenPoint(m_pProjectileData, pos, dir, speed, static_cast<IKSerializable*>(r7), point,
                                     static_cast<const RwMatrix*>(r9));  // vt+0xa0
}

// 0x001f2cd8 CKProjectileAccessor_LaunchAtPoint
uint8_t CKProjectileAccessor::LaunchAtPoint(const CVector3* pos, const CVector3* target, float speed, void* /*r6*/,
                                            IKSerializable* owner, void* /*r8*/) {
    IKProjectileType* type = static_cast<IKProjectileType*>(m_pProjectileType);
    if (type == nullptr) return 0;
    return type->LaunchAtPoint(m_pProjectileData, pos, target, speed, owner);  // vt+0x98
}

// 0x001f2de0 CKProjectileAccessor_RecursiveRegistration (KBase1DCC's 0x1a478 inlined: that file is P04's)
void CKProjectileAccessor::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
