// CSpawnPoolRenderParam.h - a distance band of a spawn pool's rendering (key 0xe4d, vtable 0xb17a40, size
// 0x14). Original unit: CSpawnPoolRenderParam.cpp. No XXL2 class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CSpawnPoolRenderParam : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x39)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xe4d || key == 0xc; }  // vt+0x08 0x9a10b8
    DOTD_DECLARE_FACTORIES(CSpawnPoolRenderParam)

    CSpawnPoolRenderParam() {}  // 0x000ba240 CSpawnPoolRenderParam_Create: only the vtable
    ~CSpawnPoolRenderParam() override {}

    // vt+0x2c 0x000ba2e0 CSpawnPoolRenderParam_Load: two distances, then an integer (type 0 only).
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x000ba518 CSpawnPoolRenderParam_PostLoad: +0x10 = 1 / (far - near).
    int32_t PostLoad(int32_t type) override;
    // vt+0x24 0x000ba278 CSpawnPoolRenderParam_RecursiveRegistration: type 0 only, itself registered.
    void RecursiveRegistration(int32_t type) override;

    int32_t m_unk04;      // +0x04 read last (1 in LVL010)
    float m_fNear;        // +0x08 _maybe
    float m_fFar;         // +0x0c _maybe
    float m_fInvRange;    // +0x10 PostLoad
};
static_assert(CSpawnPoolRenderParam::kClassKey == 0xe4d, "key");
DOTD_ASSERT_SIZE(CSpawnPoolRenderParam, 0x14);
DOTD_ASSERT_OFFSET(CSpawnPoolRenderParam, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CSpawnPoolRenderParam, m_fNear, 0x08);
DOTD_ASSERT_OFFSET(CSpawnPoolRenderParam, m_fFar, 0x0c);
DOTD_ASSERT_OFFSET(CSpawnPoolRenderParam, m_fInvRange, 0x10);
