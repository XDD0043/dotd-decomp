// CKAnimatedFx.h - an animated effect (key 0xa04c, vtable 0xb300c8, size 0x60). Original unit:
// CKAnimatedFx.cpp (0x5ca148-0x5cc298). Derived straight from IKSerializable, with two virtuals of its own.
// Not in XXL2; names ours. Grouped by CKAnimatedFxCollection (0xa08c).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKAnimatedFx : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x281)
    DOTD_DECLARE_FACTORIES(CKAnimatedFx)

    CKAnimatedFx() {}  // 0x005caac0 CKAnimatedFx_Create (and 0x5ca198): stores the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005cab58 CKAnimatedFx_Load
    // vt+0x30 PostLoad 0x5cab08 (stays the default in C2.1).
    virtual void ResetState_maybe() {}  // vt+0x50 0x5ca1b8 STUB(C2.2)
    virtual void PlayAnim_maybe() {}    // vt+0x54 0x5ca908 STUB(C2.2)

    IKSerializable* m_unk04;   // +0x04 an object reference
    uint32_t m_unk08;          // +0x08 not read
    float m_unk0c;             // +0x0c
    CVector3 m_unk10;          // +0x10 three byte-swapped words read in one block (LVL010: 1.5, 1.5, 1)
    uint8_t m_unk1c;           // +0x1c
    uint8_t m_pad1d[3];
    float m_unk20;             // +0x20
    float m_unk24;             // +0x24
    float m_unk28;             // +0x28 (LVL010: 359)
    float m_unk2c;             // +0x2c
    float m_unk30;             // +0x30
    uint8_t m_unk34;           // +0x34
    uint8_t m_unk35;           // +0x35 read first
    uint8_t m_unk36;           // +0x36
    uint8_t m_unk37;           // +0x37
    uint32_t m_unk38;          // +0x38 not read
    IKSerializable* m_unk3c;   // +0x3c an object reference
    uint32_t m_unk40;          // +0x40 not read
    IKSerializable* m_unk44;   // +0x44 an object reference
    uint32_t m_unk48;          // +0x48 not read
    IKSerializable* m_unk4c;   // +0x4c an object reference
    uint32_t m_unk50[4];       // +0x50 not read
};
static_assert(CKAnimatedFx::kClassKey == 0xa04c, "key");
DOTD_ASSERT_SIZE(CKAnimatedFx, 0x60);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk37, 0x37);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk4c, 0x4c);
