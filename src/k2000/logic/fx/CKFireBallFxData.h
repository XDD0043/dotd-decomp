// CKFireBallFxData.h - the data of a fire-ball effect (key 0x338c, size 0x20). Its methods are in CKFilterNode2dFx.cpp
// (0x1b9dc0-0x1b9f48); Create / CreateArray / Delete sit in other units. Its node is CKFireBallNodeFx (0x33cc). Not in
// XXL2; names ours. In no LVL000 / LVL010 file.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKFireBallFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xce)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x338c || key == 0x304c || key == 0x6 || key == 0xc; }
    DOTD_DECLARE_FACTORIES(CKFireBallFxData)

    CKFireBallFxData() {}

    // vt+0x2c 0x001b9e20 CKFireBallFxData_Load: IKFxData's, then (level files) six byte-swapped words.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x001b9dd0 PostLoad, vt+0x24 0x001b9df8 RecursiveRegistration: IKFxData's (return 1); vt+0x10 0x001b9dc8
    // Destroy: empty. The defaults.
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x33cc; }  // vt+0x54 0x001b9dc0

    float m_unk08;  // +0x08 the V scroll speed (CKFireBallNodeFx_Update: +0x34 of the UV matrix)
    float m_unk0c;  // +0x0c the U scroll speed (+0x30 of the UV matrix)
    float m_unk10;  // +0x10 the node scale in X and Z
    float m_unk14;  // +0x14 the node scale in Y
    float m_unk18;  // +0x18 the fade-in speed (alpha per second)
    float m_unk1c;  // +0x1c the fade-out speed (alpha per second)
};
static_assert(CKFireBallFxData::kClassKey == 0x338c, "key");
DOTD_ASSERT_SIZE(CKFireBallFxData, 0x20);
