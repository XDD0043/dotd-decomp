// CKBonusCpnt.h - the k2000 bonus pickup's parameters (key 0x586, vtable 0xb2f6b8, size 0x54; library-TOC code).
// Original unit: CKBonusCpnt.cpp (0x5ba9f8-0x5bb7e8). XXL2 CKBonusCpnt (IKBonusCpnt, then m_pRotationMatrix ..
// m_baFlags: the names below where the PS3 code uses the field the same way). DotD's pools hold CKS08BonusCpnt (0x1306),
// so no level file has one; CKGrpBonusPool_UpdateBonuses_maybe spins its matrix when the pool's component is one.
#pragma once
#include <cstdint>

#include "k2000/components/IKBonusCpnt.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class IKTime;

class CKBonusCpnt : public IKBonusCpnt {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x16)
    DOTD_DECLARE_FACTORIES(CKBonusCpnt)

    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ccec0
        return key == 0x586 || key == 0x606 || key == 0x6 || key == 0xc;
    }
    // 0x005bace0 CKBonusCpnt_Create (OperatorNew(0x54)): IKBonusCpnt's vtable (0xb2f660), then this one; no field set.
    CKBonusCpnt() {}
    // 0x009cce80 CKBonusCpnt_Destructor / 0x009ccef8 _DeletingDestructor: the two vtables, then IKBaseClass's (the matrix
    // is Destroy's).
    ~CKBonusCpnt() override {}

    // vt+0x10 0x005baad8 CKBonusCpnt_ClearReferences (the Destroy slot): the rotation matrix destroyed (TocBridge 0x990520
    // -> RwMatrixDestroy_Thunk 0x23f968); the pointer is left.
    void Destroy() override;
    // vt+0x24 0x005bb108 CKBonusCpnt_LevelReset: outside the types 4..7 the component registered with the saving manager
    // and, for type 0, its sound dictionary's (+0x0c) registration with 0; then +0x48's with `type`.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005bb1f0 CKBonusCpnt_Load
    // 0x005bad28 CKBonusCpnt_ComputeSpinBobMatrix_maybe: the matrix +0x10 rebuilt from the clock's game time: the turn of
    // the time's fraction of turns about y, scaled when the flags ask, and the float height (a sine of the bob's phase).
    void ComputeSpinBobMatrix(IKTime* clock);

    CMatrix34* m_pRotationMatrix;    // +0x10 XXL2 m_pRotationMatrix; the type-0 Load creates it (RwMatrixCreate)
    float m_fRotationSpeed;          // +0x14 XXL2: turns per second (ComputeSpinBobMatrix)
    float m_fHalfHeight;             // +0x18 XXL2
    float m_fFloatingHeight;         // +0x1c XXL2: the bob's base height
    float m_fDeltaFloatHeight;       // +0x20 XXL2: the bob's amplitude
    float m_fVerticalBounceSpeed;    // +0x24 XXL2
    float m_fVerticalFloatSpeed;     // +0x28 XXL2: bob cycles per second
    float m_fScale;                  // +0x2c XXL2: the matrix's scale (flag bits 3..4 == 1)
    float m_fRotationAcc;            // +0x30 XXL2
    float m_fPickUpAcc;              // +0x34 XXL2
    float m_fPickUpVerticalImpulse;  // +0x38 XXL2
    float m_fAccuracy;               // +0x3c XXL2
    float m_fMaxFlyTime;             // +0x40 XXL2
    uint32_t m_baFlags;              // +0x44 XXL2 CBitArray m_baFlags (one word here)
    IKSerializable* m_pUnk48;        // +0x48 reference (type 0 only; DotD)
    float m_unk4c;                   // +0x4c (DotD)
    float m_unk50;                   // +0x50 (DotD)
};
DOTD_ASSERT_SIZE(CKBonusCpnt, 0x54);
DOTD_ASSERT_OFFSET(CKBonusCpnt, m_pRotationMatrix, 0x10);
DOTD_ASSERT_OFFSET(CKBonusCpnt, m_fVerticalFloatSpeed, 0x28);
DOTD_ASSERT_OFFSET(CKBonusCpnt, m_baFlags, 0x44);
DOTD_ASSERT_OFFSET(CKBonusCpnt, m_pUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKBonusCpnt, m_unk50, 0x50);
