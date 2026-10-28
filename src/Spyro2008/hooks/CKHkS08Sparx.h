// CKHkS08Sparx.h - Sparx, the hero's dragonfly companion (key 0x3282, vtable 0xb24be8, size 0xd4). Original
// unit: CKHkS08Sparx.cpp (0x3f4108-0x3f6dc0). Derived straight from IKHook (IsKindOf: 0x2 IKHook, 0x2fe IKLife,
// 0x3fe IKUpdatable, 0xc IKSerializable). No XXL2 class. Field names: the Ghidra struct (CKHkS08Sparx).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/CMatrix34.h"

class CKHkS08Sparx : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xca)
    DOTD_DECLARE_FACTORIES(CKHkS08Sparx)

    // 0x003f4c28 CreateCKHkS08Sparx (inlined constructor, the same stores as the dead 0x3f4158
    // CKHkS08Sparx_Construct): the IKLife/IKHook defaults and the ground-contact pair at +0x7c/+0x8c.
    CKHkS08Sparx() {}
    ~CKHkS08Sparx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003f6860 CKHkS08Sparx_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x003f4540 CKHkS08Sparx_PostLoad
    void Start() override;  // vt+0x50 0x003f67e8 CKHkS08Sparx_Start (C2.2)

    IKSerializable* m_pNode;                 // +0x20 CNode* (struct draft); read 5th
    IKSerializable* m_pAnimationDictionary;  // +0x24 CAnimationDictionary*
    IKSerializable* m_pParticlesNode;        // +0x28 CParticlesNodeFx*
    // +0x2c..+0x48 eight floats (LVL010: 15, 30, 90, 75, 1, 5, 1, 3); speeds/distances_maybe.
    float m_fl2c;                            // +0x2c
    float m_fl30;                            // +0x30
    float m_fl34;                            // +0x34
    float m_fl38;                            // +0x38
    float m_fl3c;                            // +0x3c (Ghidra dwDw_3c; the data is a float, 1.0)
    float m_fl40;                            // +0x40
    float m_fl44;                            // +0x44 (Ghidra field_0x44; the data is a float, 1.0)
    float m_fl48;                            // +0x48
    IKSerializable* m_pGlowNode;             // +0x4c CGlowNodeFx*
    IKSerializable* m_pPointLightFxData;     // +0x50 CKPointLightFxData*
    uint32_t m_unk54[0xa];                   // +0x54..+0x7b runtime
    CGroundContactDatasIn m_GContactIn;      // +0x7c (masks at +0x84/+0x88 = 1, 8)
    CGroundContactDatasInOut m_GContactInOut;  // +0x8c
    uint32_t m_unkB8[3];                     // +0xb8 runtime (+0xbc CKPointLightNodeFx* live)
    CMatrix34* m_pMatrixC4;                  // +0xc4 PostLoad: RwMatrixCreate_Thunk (0x3f4540)
    uint32_t m_unkC8[3];                     // +0xc8 runtime
};
DOTD_ASSERT_SIZE(CKHkS08Sparx, 0xd4);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pNode, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pAnimationDictionary, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pParticlesNode, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_fl2c, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_fl48, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pGlowNode, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pPointLightFxData, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_GContactIn, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_GContactInOut, 0x8c);
DOTD_ASSERT_OFFSET(CKHkS08Sparx, m_pMatrixC4, 0xc4);
