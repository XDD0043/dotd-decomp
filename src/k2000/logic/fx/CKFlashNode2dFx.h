// CKFlashNode2dFx.h - a flash on a 2D node (key 0x15cc, vtable 0xb1cd68, size 0x7c). Original unit:
// CKFlashNode2dFx.cpp. XXL2 has m_v2CurScale, m_ui32CurFlashAlpha, m_pFlashData and m_scColor after
// IKNode2dFx; DotD's layout differs (a small state machine from +0x5c) and is not mapped yet.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNode2dFx.h"

class CKFlashNode2dFx : public IKNode2dFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x57)
    DOTD_DECLARE_FACTORIES(CKFlashNode2dFx)

    CKFlashNode2dFx();  // inlined in 0x001bcb88 CKFlashNode2dFx_Create
    ~CKFlashNode2dFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001bca10 CKFlashNode2dFx_Load

    // One state of the state machine (name ours): PostLoad (0x1bc6d8) stores the function descriptors
    // CKFlashNode2dFx_State0/1/2 (0xb6f388, 0xb6f398, 0xb6f390) and 0.
    struct State {
        const void* m_handler;  // +0x00
        uint32_t m_value;       // +0x04
    };

    uint32_t m_unk14[18];  // +0x14..+0x5b not set by the constructor or Load
    State* m_pCurState;    // +0x5c PostLoad points it at m_aStates[0]; name ours (the current state _maybe)
    uint8_t m_unk60;       // +0x60 the constructor sets 0xff (PostLoad: 0xff)
    uint8_t m_unk61;       // +0x61 the constructor sets 0xff (PostLoad: 3)
    uint16_t m_unk62;      // +0x62
    State m_aStates[3];    // +0x64 name ours
};
static_assert(CKFlashNode2dFx::kClassKey == 0x15cc, "key");
DOTD_ASSERT_SIZE(CKFlashNode2dFx, 0x7c);
DOTD_ASSERT_OFFSET(CKFlashNode2dFx, m_pCurState, 0x5c);
DOTD_ASSERT_OFFSET(CKFlashNode2dFx, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKFlashNode2dFx, m_unk61, 0x61);
DOTD_ASSERT_OFFSET(CKFlashNode2dFx, m_aStates, 0x64);
