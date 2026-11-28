// CKImpulsionCpnt.h - impulse parameters (key 0x806, vtable 0xb20df0, size 0x30). Original unit:
// CKImpulsionCpnt.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CKImpulsionCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x20)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b9fc8
        return key == 0x806 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKImpulsionCpnt)

    CKImpulsionCpnt() {}  // 0x0024c020 CKImpulsionCpnt_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0024c108 CKImpulsionCpnt_Load

    // 0x0024bce0 CKImpulsionCpnt_Impulse: unless still running with +0x20 set, the timer +0x2c = `scale` times the
    // duration +0x14; without an acceleration (+0x0c) the speed +0x28 jumps to `scale` times the top speed +0x10.
    void Impulse(float scale);
    // 0x0024bd40 CKImpulsionCpnt_Update: while the timer runs (down by `dt`) the speed accelerates (+0x0c) up to the top
    // speed +0x10, after it decelerates (+0x18) down to +0x1c; the value +0x24 moves by the speed, kept in [+0x08, +0x04].
    void Update(float dt);

    // +0x04..+0x1c seven floats (LVL010: 1, 0, 0, 0.5, 0.02, 2, -0.5): the value's maximum and minimum, the
    // acceleration, the top speed, the duration, the deceleration, the lowest speed (_maybe, from Update / Impulse).
    float m_unk04[7];
    uint8_t m_bWaitForRunning;   // +0x20 one byte: an impulse waits for the running one
    uint8_t m_pad21[3];
    float m_fValue;  // +0x24 the value (not set by the constructor or the Load; the hero clears +0x24..+0x2c)
    float m_fSpeed;  // +0x28 the speed
    float m_fImpulseTimer;  // +0x2c the impulse timer
};
DOTD_ASSERT_SIZE(CKImpulsionCpnt, 0x30);
DOTD_ASSERT_OFFSET(CKImpulsionCpnt, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKImpulsionCpnt, m_bWaitForRunning, 0x20);
