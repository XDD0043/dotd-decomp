// CKGolemAttackCommon.h - a boss attack description (key 0x994c, vtable 0xb28fc0, size 0x98). Original unit:
// CKGolemAttackCommon.cpp (0x4b7728-0x4ba5a0). No XXL2 class of this name: the members keep placeholder
// names. Derives from KBase984C (Ghidra: CKGolemAttackBase_maybe); base of the Malefor attacks
// (CKS08MaleforBigBombDeathBall, CKS08MaleforColdBall, CKS08MaleforFireBreath). Minimal for C2.1:
// constructor and Load. Two inlined growable arrays (data, capacity, count) at +0x08 and +0x6c.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase984C.h"
#include "k2000/services/CTriggerStarter.h"

class CKGolemAttackCommon : public KBase984C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x265)
    DOTD_DECLARE_FACTORIES(CKGolemAttackCommon)

    // One entry of the +0x08 array (OperatorNew(0x1c)).
    struct Entry08 {
        IKSerializable* m_unk00;  // +0x00 object reference (read second)
        IKSerializable* m_unk04;  // +0x04 object reference (read first)
        uint8_t m_unk08;          // +0x08 the six bytes are read in the order +0d, +0c, +09, +08, +0a, +0b
        uint8_t m_unk09;          // +0x09
        uint8_t m_unk0a;          // +0x0a
        uint8_t m_unk0b;          // +0x0b
        uint8_t m_unk0c;          // +0x0c
        uint8_t m_unk0d;          // +0x0d (+0x0e..+0x0f padding)
        float m_unk10;            // +0x10 (file: 0.1, 0, ...)
        float m_unk14;            // +0x14 (file: -0.5, 0, ...)
        float m_unk18;            // +0x18 (file: 0.25, -0.7, ...)
    };
    // One entry of the +0x6c array (OperatorNew(0x14)).
    struct Entry6C {
        float m_unk00;                // +0x00 (file: 1.7)
        CTriggerStarter m_unk04;      // +0x04 (loaded with type 0)
        uint32_t m_unk0c;             // +0x0c
        uint32_t m_unk10;             // +0x10 not read by the Load
    };

    CKGolemAttackCommon();  // 0x004b87b0 CKGolemAttackCommon_Construct
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004b9bb8 CKGolemAttackCommon_Load

    Entry08** m_apUnk08;      // +0x08 (Mem_AllocAligned16 / Mem_ReallocAligned16)
    uint32_t m_unk08Capacity;  // +0x0c
    uint32_t m_unk08Count;     // +0x10
    uint32_t m_unk14;          // +0x14 (constructor 0)
    uint8_t m_unk18;           // +0x18
    IKSerializable* m_unk1c;   // +0x1c object reference
    uint8_t m_unk20;           // +0x20
    IKSerializable* m_unk24;   // +0x24 object reference
    uint8_t m_unk28;           // +0x28
    IKSerializable* m_unk2c;   // +0x2c object reference
    uint8_t m_unk30;           // +0x30
    IKSerializable* m_unk34;   // +0x34 object reference
    uint8_t m_unk38;           // +0x38
    IKSerializable* m_unk3c;   // +0x3c object reference
    uint8_t m_pad40[0x10];     // +0x40..+0x4f not read by the Load
    IKSerializable* m_unk50;   // +0x50 object reference
    IKSerializable* m_unk54;   // +0x54 object reference
    uint32_t m_unk58;          // +0x58 runtime (_maybe: a pose list, see ApplyPoseFromList58)
    uint32_t m_unk5c;          // +0x5c runtime (_maybe: a pose list, see ApplyPoseFromList5C)
    IKSerializable* m_unk60;   // +0x60 object reference
    uint8_t m_unk64;           // +0x64 (+0x65..+0x67 padding)
    IKSerializable* m_unk68;   // +0x68 object reference
    Entry6C** m_apUnk6c;       // +0x6c (Mem_AllocAligned16 / Mem_ReallocAligned16)
    uint32_t m_unk6cCapacity;  // +0x70
    uint32_t m_unk6cCount;     // +0x74
    uint8_t m_pad78[0x20];     // +0x78..+0x97 not read by the Load
};
DOTD_ASSERT_SIZE(CKGolemAttackCommon::Entry08, 0x1c);
DOTD_ASSERT_SIZE(CKGolemAttackCommon::Entry6C, 0x14);
DOTD_ASSERT_SIZE(CKGolemAttackCommon, 0x98);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_apUnk08, 0x08);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk08Count, 0x10);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_apUnk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk6cCount, 0x74);
