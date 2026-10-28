// CSparkNodeFx.h - a spark effect node (key 0x70b, vtable 0xb18ba8, size 0x5c). Original unit:
// CSparkNodeFx.cpp. No XXL2 class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/INodeFx.h"

class CKSparkParam;

class CSparkNodeFx : public INodeFx {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x1c)
    DOTD_DECLARE_FACTORIES(CSparkNodeFx)

    CSparkNodeFx();  // 0x000e7f20 CSparkNodeFx_Construct (inlined in 0xe8388 CSparkNodeFx_Create)
    ~CSparkNodeFx() override {}

    // vt+0x2c 0x000e8070 CSparkNodeFx_Load
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x000e9410 CSparkNodeFx_PostLoad: the spark pool (count - listed, 0x68 bytes each), the
    // matrix (+0x54), the particle geometry set up. STUB(C2.2): INodeFx's only (inherited).

    int32_t m_i32NbSparks;      // +0x2c _maybe: PostLoad allocates this many minus the listed ones
    uint32_t m_unk30;           // +0x30 PostLoad sets 0
    void* m_pFreeSparks;        // +0x34 a list (PostLoad); the constructor sets 0
    uint32_t m_unk38;           // +0x38 the constructor and PostLoad set 0
    IKSerializable* m_pGeometry;  // +0x3c PostLoad: the first geometry (a CParticleGeometry); constructor 0
    uint8_t m_unk40;            // +0x40 read; PostLoad starts the sparks when non-zero
    uint8_t m_pad41[3];
    uint32_t m_unk44;           // +0x44 not read (runtime)
    uint32_t m_unk48;           // +0x48 not read (runtime)
    uint8_t m_unk4c;            // +0x4c read
    uint8_t m_pad4d[3];
    CKSparkParam* m_pSparkParam;  // +0x50 the constructor sets 0
    void* m_pMatrix;            // +0x54 PostLoad: RwMatrixCreate; the constructor sets 0
    void* m_pSparks;            // +0x58 PostLoad: the spark array; the constructor sets 0
};
static_assert(CSparkNodeFx::kClassKey == 0x70b, "key");
DOTD_ASSERT_SIZE(CSparkNodeFx, 0x5c);
DOTD_ASSERT_OFFSET(CSparkNodeFx, m_i32NbSparks, 0x2c);
DOTD_ASSERT_OFFSET(CSparkNodeFx, m_pFreeSparks, 0x34);
DOTD_ASSERT_OFFSET(CSparkNodeFx, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CSparkNodeFx, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CSparkNodeFx, m_pSparkParam, 0x50);
DOTD_ASSERT_OFFSET(CSparkNodeFx, m_pSparks, 0x58);
