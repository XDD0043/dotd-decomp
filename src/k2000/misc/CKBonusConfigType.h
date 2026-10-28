// CKBonusConfigType.h - the base of the bonus spawn layouts (key 0x2c8c, unregistered; no XXL2
// counterpart, the Ghidra name CKBonusConfigType_2c8c_maybe is kept). Original unit:
// CKBonusConfigType.cpp (0x127470-0x1275b0). PS3 vtable 0xb19de8 (22 slots; GetClassType 0xc and
// GetClassID 0xb2 at 0x9a7078/0x9a7080 give the key). Derived straight from IKSerializable; its classes
// are CKBonusConfigTypeStar (0x2f8c, layout type 1) and CKBonusConfigTypeCone (0x2d0c, layout type 0).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKBonusConfigType : public IKSerializable {
public:
    CKBonusConfigType() {}  // 0x001274a8 CKBonusConfigType_2c8c_maybe_Construct: stores the vtable only

    int32_t IsKindOfClass(uint32_t key) override { return key == 0x2c8c || key == 0xc; }  // vt+0x08 0x9a7088
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001274b8 CKBonusConfigType_2c8c_maybe_Load
    // vt+0x50 pure (Ghidra *_GenerateSpawns_maybe; arguments unverified).
    virtual void GenerateSpawns() = 0;
    // vt+0x54 pure (Ghidra *_GetLayoutType_maybe): Cone returns 0, Star 1 (0x127480, dead, maps them
    // back to the keys 0x2d0c / 0x2f8c).
    virtual int32_t GetLayoutType() = 0;

    uint32_t m_unk04;  // +0x04 read by the base Load (Star: 1, Cone: 0 in LVL000)
};
DOTD_ASSERT_SIZE(CKBonusConfigType, 0x8);
DOTD_ASSERT_OFFSET(CKBonusConfigType, m_unk04, 0x04);
