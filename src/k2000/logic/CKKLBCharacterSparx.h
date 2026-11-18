// CKKLBCharacterSparx.h - Sparx as a linked-beacon character (key 0x9f8c, vtable 0xb26db0, size 0x14).
// Original unit: CKKLBCharacterSparx.cpp (0x450480-0x450df0). Base: CKKLBCharacterBase (0x9f0c). No XXL2
// class. Field types from the struct draft (132/132 live samples).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/ai/CKKLBCharacterBase.h"

class CKKLBCharacterSparx : public CKKLBCharacterBase {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x27e)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x9f8c || key == 0xc; }  // vt+0x08 0x9c3ce8
    DOTD_DECLARE_FACTORIES(CKKLBCharacterSparx)

    CKKLBCharacterSparx() {}  // 0x00450bc8 CKKLBCharacterSparx_Create: the vtable only
    // 0x00450dd0 CKKLBCharacterSparx_Destructor / 0x00450d88 CKKLBCharacterSparx_DeletingDestructor: the vtables put
    // back (and the memory freed).
    ~CKKLBCharacterSparx() override {}

    void Destroy() override {}                              // vt+0x10 0x00450c10 CKKLBCharacterSparx_Destroy (empty)
    void RecursiveRegistration(int32_t /*type*/) override {}  // vt+0x24 0x00450c00 (returns 1, registers nothing)
    int32_t Save(IKFile* /*file*/, int32_t /*type*/) override { return 1; }     // vt+0x28 0x004504f0 CKKLBCharacterSparx_Save
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00450c18 CKKLBCharacterSparx_Load
    int32_t PostLoad(int32_t /*type*/) override { return 1; }  // vt+0x30 0x00450c08 CKKLBCharacterSparx_PostLoad
    void Vf50() override;                               // vt+0x50 0x004504f8 CKKLBCharacterSparx_vf50
    void Vf54() override;                               // vt+0x54 0x00450690 CKKLBCharacterSparx_vf54
    int32_t Vf58() override;                            // vt+0x58 0x00450528 CKKLBCharacterSparx_vf58
    CVector3 Vf5C() override;                           // vt+0x5c 0x00450950 CKKLBCharacterSparx_vf5C
    int32_t Vf60() override { return 1; }               // vt+0x60 0x00450548 CKKLBCharacterSparx_vf60
    void Vf64(const float* direction) override;         // vt+0x64 0x00450668 CKKLBCharacterSparx_vf64
    void Vf68(const CVector3* position, float speed, int32_t unused) override;  // vt+0x68 0x00450a28
    void Vf6C(const CVector3* position, const CVector3* direction, int32_t fast) override;  // vt+0x6c 0x00450988
    void Vf70(const CVector3* position, const CVector3* direction) override;  // vt+0x70 0x00450640
    uint8_t MoveTowardTarget(IKTime* clock) override;   // vt+0x74 0x00450610 CKKLBCharacterSparx_MoveTowardTarget_maybe
    uint8_t Vf78(IKTime* clock) override;               // vt+0x78 0x00450a78 CKKLBCharacterSparx_vf78
    uint8_t Vf7C(double dt) override;                   // vt+0x7c 0x004505e0 CKKLBCharacterSparx_vf7C
    void Vf80(uint32_t animation) override;             // vt+0x80 0x00450888 CKKLBCharacterSparx_vf80
    void Vf84(double dt) override;                      // vt+0x84 0x00450858 CKKLBCharacterSparx_vf84
    void Vf88(uint32_t still) override;                 // vt+0x88 0x00450550 CKKLBCharacterSparx_vf88
    void Vf8C(uint8_t still) override;                  // vt+0x8c 0x00450ab8 CKKLBCharacterSparx_vf8C
    uint8_t SetTarget() override;                       // vt+0x90 0x00450580 CKKLBCharacterSparx_SetTarget_maybe
    CPFCharacter* Vf94() override;                      // vt+0x94 0x004508c0 CKKLBCharacterSparx_vf94
    void Vf98(int32_t reset) override;                  // vt+0x98 0x004505b0 CKKLBCharacterSparx_vf98
    IKSerializable* Vf9C() override;                    // vt+0x9c 0x00450aa8 CKKLBCharacterSparx_vf9C
    // vt+0xa0 0x00450938 CKKLBCharacterSparx_vfA0: the Sparx node's world matrix (its frame's LTM); the linked beacon's input
    // icon follows it (CKHkLinkedBeacon_ShowInputIcon_maybe).
    const CMatrix34* VfA0() override;
    IKSerializable* VfA4() override;                    // vt+0xa4 0x00450908 CKKLBCharacterSparx_vfA4
    int32_t VfA8() override { return 0; }               // vt+0xa8 0x009c3ce0 CKKLBCharacterSparx_vfA8

    IKSerializable* m_pSparx;       // +0x08 runtime: CKHkS08Sparx* live (not read by Load)
    IKSerializable* m_pMoveUpdater;  // +0x0c CKMoveCpntUpdater* (struct draft); read second
    IKSerializable* m_pMoveCpnt;     // +0x10 CKMoveCpnt* (struct draft); read first
};
DOTD_ASSERT_SIZE(CKKLBCharacterSparx, 0x14);
DOTD_ASSERT_OFFSET(CKKLBCharacterSparx, m_pMoveUpdater, 0x0c);
DOTD_ASSERT_OFFSET(CKKLBCharacterSparx, m_pMoveCpnt, 0x10);
