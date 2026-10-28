// CKWaterSplashFxData.h - the data of a water-splash effect (key 0x3c0c, vtable 0xb2dc48, size 0x2c). Its
// Load and evaluators are in CKWaterWaveNodeFx.cpp; Create (0x56efb0) sits in another unit. Its node is
// CKWaterSplashNodeFx (0x3c4c). Not in XXL2; names ours.
//
// Four key lists of (float, float) pairs, each a count then a new[] array; EvalMesh1HeightScale,
// EvalMesh2HeightScale, EvalWidthScale and EvalAlpha (0x570608..0x5707e8) _maybe evaluate them.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKWaterSplashFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xf0)
    DOTD_DECLARE_FACTORIES(CKWaterSplashFxData)

    // Two byte-swapped words. The PS3 allocates the arrays with operator new[] and a 4-byte count cookie.
    struct Key {
        float m_unk00;
        float m_unk04;
    };

    CKWaterSplashFxData() {}  // inlined in 0x0056efb0 CKWaterSplashFxData_Create: the vtables only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00570948 CKWaterSplashFxData_Load
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x3c4c; }  // vt+0x54 0x570600

    float m_unk08;      // +0x08
    uint32_t m_unk0c;   // +0x0c key count (read third)
    Key* m_unk10;       // +0x10
    uint32_t m_unk14;   // +0x14 key count (read second)
    Key* m_unk18;       // +0x18
    uint32_t m_unk1c;   // +0x1c key count (read first)
    Key* m_unk20;       // +0x20
    uint32_t m_unk24;   // +0x24 key count (read fourth)
    Key* m_unk28;       // +0x28
};
static_assert(CKWaterSplashFxData::kClassKey == 0x3c0c, "key");
DOTD_ASSERT_SIZE(CKWaterSplashFxData::Key, 0x8);
DOTD_ASSERT_SIZE(CKWaterSplashFxData, 0x2c);
DOTD_ASSERT_OFFSET(CKWaterSplashFxData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKWaterSplashFxData, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKWaterSplashFxData, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKWaterSplashFxData, m_unk28, 0x28);
