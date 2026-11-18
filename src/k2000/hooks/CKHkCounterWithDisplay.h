// CKHkCounterWithDisplay.h - a counter shown on screen (key 0x1f82, vtable 0xb26ac8, size 0x34). Original unit:
// CKHkCounterWithDisplay.cpp (0x4472f0-0x447fc0). No XXL2 class. No level file holds one (work/level-class-keys.json);
// C2.8 port-rest R03 ported it from the code. Field names are placeholders.
//
// The hook shows a counter (+0x20: a CKTimeCounter for type 0, a CKIntegerCounter for type 1, +0x28) through a counter
// FX data (+0x24, a CKCounterFxData: its node +0x1c, its maximum +0x3c). Messages 0x996 / 0x997 show / hide the display
// (and run / stop a time counter); every frame the counter's value goes to the display, and an integer counter's
// change resets the display's node (+0x2c the last value shown).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"

class CKHkCounterWithDisplay : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x7e)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c3b48
        return key == 0x1f82 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkCounterWithDisplay)

    // 0x00447a88 CKHkCounterWithDisplay_Create (the dead 0x4477d8 / 0x447818 _Construct copies): the actor base, the
    // priority word -1.
    CKHkCounterWithDisplay();
    // 0x00447778 CKHkCounterWithDisplay_Destructor (= 0x4477a8 _BaseDestructor, 0x447730 _DeletingDestructor): the actor
    // base's.
    ~CKHkCounterWithDisplay() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00447ae8 CKHkCounterWithDisplay_Load
    // vt+0x30 0x00447690 CKHkCounterWithDisplay_PostLoad: the actor base's (IKLife_PostLoad), then 1: inherited.
    void SetDefaultState(int32_t /*flag*/) override {}  // vt+0x38 0x00447340 (empty)
    // vt+0x3c 0x00447348 CKHkCounterWithDisplay_SetGameState: 1 (the actor base's preset is not applied).
    int32_t SetGameState(const SApplyGameState* /*state*/) override { return 1; }
    // vt+0x40 0x00447550 CKHkCounterWithDisplay_GetInfo: the actor base's answer (2, else 0 or 1).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x1c 0x00447e70 CKHkCounterWithDisplay_MessageProc: see the .cpp.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x004476e0 RecursiveRegistration, vt+0x10 0x00447708 Destroy, vt+0x70 / +0x78 0x447618 / 0x4475f0 Pause /
    // Resume, vt+0xa0 / +0xa4 0x4475c8 / 0x4475a0 OnActivate / OnDeactivate: the actor base's, inherited.
    // vt+0x50 0x00447ca8 CKHkCounterWithDisplay_Start: the actor base's (empty), the shown value (+0x2c) and the
    // display's maximum (+0x3c) from the counter, the counter reset.
    void Start() override;
    // vt+0x54 0x00447db0 CKHkCounterWithDisplay_Restart: the shown value from the counter, the display hidden (its node
    // released), a time counter stopped.
    void Restart() override;
    // vt+0x68 0x00447640 CKHkCounterWithDisplay_Stop: the actor base's, the display's node released when there is one.
    void Stop() override;
    // vt+0x7c 0x004478f8 CKHkCounterWithDisplay_Update: the counter's value to the display; an integer counter's change
    // resets the display's node and is kept (+0x2c).
    void Update(IKTime* clock) override;
    // 0x004473d8 CKHkCounterWithDisplay_ResetCounter_maybe: the counter reset by its type (no caller in the binary: only
    // its OPD).
    void ResetCounter();

    IKSerializable* m_pUnk20;  // +0x20 reference: the counter (CKTimeCounter for type 0, CKIntegerCounter for type 1)
    IKSerializable* m_pUnk24;  // +0x24 reference: the display (a CKCounterFxData)
    int32_t m_i32Type;         // +0x28 the counter's type (swapped): 0 time, 1 integer
    float m_fUnk2C;            // +0x2c runtime: the value last shown
    uint8_t m_unk30;           // +0x30 read last (one byte; not read by this unit)
    uint8_t m_pad31[3];
};
DOTD_ASSERT_SIZE(CKHkCounterWithDisplay, 0x34);
DOTD_ASSERT_OFFSET(CKHkCounterWithDisplay, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkCounterWithDisplay, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkCounterWithDisplay, m_i32Type, 0x28);
DOTD_ASSERT_OFFSET(CKHkCounterWithDisplay, m_fUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkCounterWithDisplay, m_unk30, 0x30);
