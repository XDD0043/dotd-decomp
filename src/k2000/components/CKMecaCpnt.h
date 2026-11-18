// CKMecaCpnt.h - a mechanism's activation particles (key 0xac6, vtable 0xb24f10, size 0x8; an IKMecaCpnt).
// Original unit: CKMecaCpnt.cpp. XXL2: K/KMeca/CKMecaCpnt.h (CKMecaCpnt::PlayMecaActivationFX, the reference to a
// CParticlesNodeFx).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKMecaCpntBase.h"

class CParticlesNodeFx;
struct CVector3;

class CKMecaCpnt : public IKMecaCpnt {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x2b)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c0d18
        return key == 0xac6 || key == 0xa06 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKMecaCpnt)

    // 0x003f8060 CKMecaCpnt_Create: operator new(8), the base (0x3f7a08), the vtable. +0x04 is left as the heap has it
    // (the Load always reads it); zeroed here (the port's fresh heap).
    CKMecaCpnt() : m_pFx(nullptr) {}
    // 0x003f7d30 CKMecaCpnt_Destructor (0x3f7ce8 the deleting one): the vtable, the base's destructor (0x3f7d60, vtable
    // stores only). vt+0x10 0x003f7cc0 CKMecaCpnt_Destroy: the base's (0x3f7a78, vt+0x54), inherited. vt+0x24 0x003f7c98
    // CKMecaCpnt_RecursiveRegistration: the base's (0x3f7a70, nothing), inherited. vt+0x30 PostLoad is the base's.

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003f7b90 CKMecaCpnt_Load
    // 0x003f7ea0 CKMecaCpnt_AppendPointAndRequestUpdate_maybe (XXL2 CKMecaCpnt::PlayMecaActivationFX(CVector3, bool), the
    // CParticlesNodeFx calls inlined); CKHkActivator_CheckContactsAndToggle_maybe 0x3f9a50 calls it.
    void PlayMecaActivationFX(const CVector3* position, int32_t flag);

    CParticlesNodeFx* m_pFx;  // +0x04 reference (XXL2: the activation CParticlesNodeFx)
};
DOTD_ASSERT_SIZE(CKMecaCpnt, 0x8);
DOTD_ASSERT_OFFSET(CKMecaCpnt, m_pFx, 0x04);
