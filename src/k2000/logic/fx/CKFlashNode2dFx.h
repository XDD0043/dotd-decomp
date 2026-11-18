// CKFlashNode2dFx.h - a flash on a 2D node (key 0x15cc, vtable 0xb1cd68, size 0x7c). Original unit:
// CKFlashNode2dFx.cpp. XXL2 has m_v2CurScale, m_ui32CurFlashAlpha, m_pFlashData and m_scColor after
// IKNode2dFx; DotD's layout differs (a small state machine from +0x5c) and is not mapped yet.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNode2dFx.h"

class CKFlashFxData;
class IKTime;

class CKFlashNode2dFx : public IKNode2dFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x57)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ac278
        return key == 0x15cc || key == 0x158c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKFlashNode2dFx)

    CKFlashNode2dFx();  // inlined in 0x001bcb88 CKFlashNode2dFx_Create
    ~CKFlashNode2dFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001bca10 CKFlashNode2dFx_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x001bc6d8 CKFlashNode2dFx_PostLoad
    void Destroy() override {}                          // vt+0x10 0x001bc570 CKFlashNode2dFx_Destroy (empty: the node kept)
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x001bca60
    void Vf64() override;                               // vt+0x64 0x001bccc8 CKFlashNode2dFx_Start
    void Stop() override;                               // vt+0x6c 0x001bc638 CKFlashNode2dFx_Stop
    void Update(IKTime* frameClock) override;           // vt+0x78 0x001bdd68 CKFlashNode2dFx_Update
    IKFxData* GetFxData() override { return reinterpret_cast<IKFxData*>(m_pFlashData); }  // vt+0x80 0x9ac2c0 (+0x3c)
    void SetFxData(IKFxData* data) override { m_pFlashData = reinterpret_cast<CKFlashFxData*>(data); }  // vt+0x84 0x9ac2c8

    // One state of the state machine (name ours): PostLoad (0x1bc6d8) stores the function descriptors
    // CKFlashNode2dFx_State0/1/2 (0xb6f388, 0xb6f398, 0xb6f390) and 0.
    struct State {
        const void* m_handler;  // +0x00
        uint32_t m_value;       // +0x04
    };

    // States 0 / 1 / 2 (fade in, hold, fade out) and the colour fade they share (names ours).
    uint8_t RunState(uint8_t state, float dt, int32_t phase, uint8_t other);
    void FadeColour(float dt);
    // The size, rotation and position moves of the states (`mask`: the state's bit of the data's flag bytes) and the
    // billboard's colour (IKBillboard2d SetColor). Names ours.
    void MoveSizeRotationPosition(float dt, uint8_t mask);
    void SetBillboardColour(const uint8_t* colour);

    // +0x14..+0x5b: not set by the constructor or Load (Start and the states write them; names ours).
    float m_afSize[2];          // +0x14 the billboard's size (Start: the data's +0x34)
    float m_afPos[2];           // +0x1c its position (Start: the data's +0x14 spread by +0x24)
    float m_unk24[2];           // +0x24
    float m_fHoldTime;          // +0x2c state 1's time
    float m_fRotation;          // +0x30 (Start: the data's +0x4c)
    float m_afTargetPos[2];     // +0x34 the position it moves to (the data's +0x1c spread like the position)
    CKFlashFxData* m_pFlashData;  // +0x3c GetFxData / SetFxData
    uint8_t m_aTargetColour[4]; // +0x40 the fade's target (RGBA bytes)
    uint8_t m_aColour[4];       // +0x44 the colour (RGBA bytes)
    float m_fFadeRate;          // +0x48 the fade's rate (the data's +0x58 or +0x64, / 255)
    float m_afColour[4];        // +0x4c the colour as floats
    State* m_pCurState;    // +0x5c PostLoad points it at m_aStates[0]; name ours (the current state _maybe)
    uint8_t m_unk60;       // +0x60 the constructor sets 0xff (PostLoad: 0xff)
    uint8_t m_unk61;       // +0x61 the constructor sets 0xff (PostLoad: 3)
    uint16_t m_unk62;      // +0x62
    State m_aStates[3];    // +0x64 name ours
};
static_assert(CKFlashNode2dFx::kClassKey == 0x15cc, "key");
DOTD_ASSERT_SIZE(CKFlashNode2dFx, 0x7c);
DOTD_ASSERT_OFFSET(CKFlashNode2dFx, m_pCurState, 0x5c);
DOTD_ASSERT_OFFSET(CKFlashNode2dFx, m_pFlashData, 0x3c);
DOTD_ASSERT_OFFSET(CKFlashNode2dFx, m_afColour, 0x4c);
DOTD_ASSERT_OFFSET(CKFlashNode2dFx, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKFlashNode2dFx, m_unk61, 0x61);
DOTD_ASSERT_OFFSET(CKFlashNode2dFx, m_aStates, 0x64);
