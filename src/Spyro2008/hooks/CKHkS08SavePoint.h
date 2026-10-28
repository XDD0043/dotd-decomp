// CKHkS08SavePoint.h - a save point hook (key 0x2e02, size 0x84). Original unit: CKHkS08SavePoint.cpp.
// No XXL2 class. The fields are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08SavePoint : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb8)
    DOTD_DECLARE_FACTORIES(CKHkS08SavePoint)

    // 0x004c9e88 CKHkS08SavePoint_Construct (inlined in 0x004ca1b0 CKHkS08SavePoint_Create): the actor
    // base only.
    CKHkS08SavePoint() {}
    ~CKHkS08SavePoint() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004cc318 CKHkS08SavePoint_Load
    void Start() override;    // vt+0x50 0x004c9d90 CKHkS08SavePoint_Start (C2.2)
    void Restart() override {}  // vt+0x54 0x004c9928 CKHkS08SavePoint_Restart (empty)

    IKSerializable* m_pUnk20;   // +0x20
    CTriggerStarter m_unk24;    // +0x24
    CTriggerStarter m_unk2C;    // +0x2c
    IKSerializable* m_pUnk34;   // +0x34
    IKSerializable* m_pUnk38;   // +0x38
    IKSerializable* m_pUnk3C;   // +0x3c
    IKSerializable* m_pUnk40;   // +0x40 a CFogBoxNodeFx (Ghidra struct type)_maybe
    // +0x44..+0x4f bytes read raw (file order): three 3-byte groups (RGB colours_maybe: 1e0a1e, 783c50,
    // ffffff in LVL010), then +0x4d/+0x4e/+0x4f.
    uint8_t m_unk44[3];         // +0x44
    uint8_t m_unk47[3];         // +0x47
    uint8_t m_unk4A[3];         // +0x4a
    uint8_t m_unk4D;            // +0x4d
    uint8_t m_unk4E;            // +0x4e
    uint8_t m_unk4F;            // +0x4f
    float m_fUnk50;             // +0x50
    float m_fUnk54;             // +0x54
    float m_fUnk58;             // +0x58
    uint32_t m_unk5C;           // +0x5c
    uint32_t m_unk60;           // +0x60
    IKSerializable* m_pUnk64;   // +0x64
    uint32_t m_unk68[7];
};
DOTD_ASSERT_SIZE(CKHkS08SavePoint, 0x84);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_unk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_pUnk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_pUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_unk47, 0x47);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_unk4A, 0x4a);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_unk4D, 0x4d);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_fUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_pUnk64, 0x64);
