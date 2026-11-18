// CKCounterNodeFx.h - the counter display effect (key 0x590c, vtable 0xb2dfa0, size 0x68): a radial gauge node turned to
// the camera, filled by its CKCounterFxData's value, with two particle nodes (one on the start, one on each change) and
// a three-state machine (0 fade in, 1 shown, 2 fade out). Original unit: CKCounterNodeFx.cpp (0x575810-0x5774e8). Not
// in XXL2; names ours. No game file holds the class (C2.8 port-final F04).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKCounterFxData;
class CParticlesNodeFx;
struct RwTexture;

class CKCounterNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x164)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9caeb0
        return key == 0x590c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCounterNodeFx)

    // A state of the machine: the PS3 pointer to member (the function, the this adjustment; never virtual here). The
    // handler gets the frame clock (null outside Update), the event (0 tick, 1 enter, 2 leave) and the other state
    // (the next one when leaving, the previous one when entering); it returns the state to be in.
    using StateFn = uint8_t (*)(CKCounterNodeFx* node, IKTime* frameClock, int32_t event, uint8_t other);
    struct State {
        StateFn m_pfn;        // +0x00
        uint32_t m_adjust;    // +0x04 0
    };
    // One pulse key: the gauge's added size `m_fValue` at the pulse's fraction `m_fTime`.
    struct PulseKey {
        float m_fTime;
        float m_fValue;
    };

    // 0x00575c30 CKCounterNodeFx_Construct (also 0x575bd8, inlined in Create / CreateArray): IKNodeFx's, the vtable,
    // the state 0xff and the state count 0xff.
    CKCounterNodeFx();
    ~CKCounterNodeFx() override;  // 0x00577250 / 0x00577208: the vtables only

    // vt+0x10 0x00575d80 CKCounterNodeFx_Destroy: IKNodeFx's, the two textures released, the pulse keys freed.
    void Destroy() override;
    // vt+0x24 0x00575b10: IKNodeFx's (the node).
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00576160 CKCounterNodeFx_Load
    void Vf64() override;                               // vt+0x64 0x00576ec8 CKCounterNodeFx_Start
    void Stop() override;                               // vt+0x6c 0x005764c8 CKCounterNodeFx_Stop
    void Update(IKTime* frameClock) override;           // vt+0x78 0x005765d8 CKCounterNodeFx_Update
    IKFxData* GetFxData() override;                     // vt+0x80 0x009caef8 (+0x14)
    void SetFxData(IKFxData* data) override;            // vt+0x84 0x009caf00 (+0x14)

    // 0x00575918 CKCounterNodeFx_EnterState2_maybe: the owner kept for the release, then state 2 (fade out).
    void EnterFadeOut(IKSerializable* owner);
    // 0x00576458 CKCounterNodeFx_ResetDisplay_maybe: the pulse restarted and the pulse particles emitting.
    void ResetDisplay();
    // 0x00576d68 CKCounterNodeFx_InitStateMachine_maybe: the three states, no state; the particle nodes under the gauge.
    void InitStateMachine();
    // 0x00575ea8 CKCounterNodeFx_SetAlpha_maybe: the gauge's geometries' alpha (the float's integer low byte).
    void SetAlpha(float alpha);
    // The state switch the machine inlines (Start, EnterFadeOut, Update): the old state left, `next` entered.
    void SwitchState(uint8_t next, IKTime* frameClock);

    CKCounterFxData* m_pData;             // +0x14
    RwTexture* m_pTexture18;              // +0x18 (Load: a texture reference) the gauge's second texture
    RwTexture* m_pTexture1c;              // +0x1c (Load: a texture reference) the gauge's first texture
    CNode* m_pGauge;                      // +0x20 a reference: the gauge node (its first geometry the fan)
    CParticlesNodeFx* m_pStartParticles;  // +0x24 a reference: emitting from the start to the fade out
    CParticlesNodeFx* m_pPulseParticles;  // +0x28 a reference: emitting on each change (ResetDisplay)
    IKSerializable* m_pReleaseOwner;      // +0x2c the owner the fade out releases the node for
    float m_fPulseTime;                   // +0x30
    float m_fFadeTime;                    // +0x34
    PulseKey* m_aPulseKeys;               // +0x38 new[] of +0x3c keys (Load)
    uint32_t m_ui32NbPulseKeys;           // +0x3c
    float m_fPulseDuration;               // +0x40
    uint8_t m_flags44;                    // +0x44 bit 0 pulsing
    uint8_t m_pad45[3];
    State* m_pStates;                     // +0x48 the state table (+0x50)
    uint8_t m_ui8State;                   // +0x4c 0xff: none
    uint8_t m_ui8NbStates;                // +0x4d 3
    uint8_t m_pad4e[2];
    State m_aStates[3];                   // +0x50
};
static_assert(CKCounterNodeFx::kClassKey == 0x590c, "key");
DOTD_ASSERT_SIZE(CKCounterNodeFx, 0x68);
DOTD_ASSERT_OFFSET(CKCounterNodeFx, m_pData, 0x14);
DOTD_ASSERT_OFFSET(CKCounterNodeFx, m_pGauge, 0x20);
DOTD_ASSERT_OFFSET(CKCounterNodeFx, m_pReleaseOwner, 0x2c);
DOTD_ASSERT_OFFSET(CKCounterNodeFx, m_aPulseKeys, 0x38);
DOTD_ASSERT_OFFSET(CKCounterNodeFx, m_flags44, 0x44);
DOTD_ASSERT_OFFSET(CKCounterNodeFx, m_pStates, 0x48);
DOTD_ASSERT_OFFSET(CKCounterNodeFx, m_ui8State, 0x4c);
DOTD_ASSERT_OFFSET(CKCounterNodeFx, m_aStates, 0x50);
