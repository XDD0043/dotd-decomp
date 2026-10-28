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
    DOTD_DECLARE_FACTORIES(CKKLBCharacterSparx)

    CKKLBCharacterSparx() {}  // 0x00450bc8 CKKLBCharacterSparx_Create: the vtable only
    ~CKKLBCharacterSparx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00450c18 CKKLBCharacterSparx_Load
    void Vf50() override;                               // vt+0x50 0x004504f8 CKKLBCharacterSparx_vf50
    void Vf54() override;                               // vt+0x54 0x00450690 CKKLBCharacterSparx_vf54

    IKSerializable* m_pSparx;       // +0x08 runtime: CKHkS08Sparx* live (not read by Load)
    IKSerializable* m_pMoveUpdater;  // +0x0c CKMoveCpntUpdater* (struct draft); read second
    IKSerializable* m_pMoveCpnt;     // +0x10 CKMoveCpnt* (struct draft); read first
};
DOTD_ASSERT_SIZE(CKKLBCharacterSparx, 0x14);
DOTD_ASSERT_OFFSET(CKKLBCharacterSparx, m_pMoveUpdater, 0x0c);
DOTD_ASSERT_OFFSET(CKKLBCharacterSparx, m_pMoveCpnt, 0x10);
