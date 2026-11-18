// CKGolemPhaseQTE.h - a golem boss phase (key 0xa10c, vtable 0xb291d0, size 0x2c). Original unit:
// CKGolemPhaseQTE.cpp (0x4bddd8-0x4bed00). Derives from CKGolemPhaseBase (k2000/misc; its Load and
// constructor are called first). No XXL2 class of this name: the members keep placeholder names. Minimal for
// C2.1: constructor and Load.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKGolemPhaseBase.h"

class CKGolemPhaseQTE : public CKGolemPhaseBase {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x284)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c56a0
        return key == 0xa10c || key == 0xc || key == 0x978c;
    }
    DOTD_DECLARE_FACTORIES(CKGolemPhaseQTE)

    CKGolemPhaseQTE() {}  // 0x004be158 CKGolemPhaseQTE_Construct: the base constructor, then the vtable only
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004be4c0 CKGolemPhaseQTE_Load
    // vt+0x1c 0x004bde48 CKGolemPhaseQTE_MessageProc: message 0x407 answers 0 for a request below 7 and sets the
    // answer byte for 7; anything else 1.
    int32_t MessageProc(uint16_t message, void* data) override;

    void Update(IKTime* clock) override;  // vt+0x50 0x004be310 CKGolemPhaseQTE_Update_maybe
    void Start() override;                // vt+0x54 0x004be268 CKGolemPhaseQTE_Start
    void Stop() override;                 // vt+0x58 0x004be008 CKGolemPhaseQTE_vf58
    void ResetPhases() override {}        // vt+0x5c 0x4bde28 (empty)
    void Vf60() override {}               // vt+0x60 0x4bde30 (empty)
    void SwitchToStep(uint32_t /*step*/, float /*blend*/) override {}     // vt+0x64 0x4bde38 (empty)
    void StartStepNoStop(uint32_t /*step*/, float /*blend*/) override {}  // vt+0x68 0x4bde40 (empty)
    int32_t GetDamageSincePhaseStart() override;  // vt+0x6c 0x004bdfc8 CKGolemPhaseQTE_GetDamageSincePhaseStart_maybe
    void MarkDamageBaseline() override;           // vt+0x70 0x004bdf90 CKGolemPhaseQTE_MarkDamageBaseline_maybe
    int32_t GetDamageSinceMark2() override;       // vt+0x74 0x004bdf50 CKGolemPhaseQTE_vf74
    int32_t GetDamageSinceUpdate() override;      // vt+0x78 0x004bdf10 CKGolemPhaseQTE_GetDamageSinceUpdate_maybe
    float GetStartTime() override;                // vt+0x7c 0x004be2f8 CKGolemPhaseQTE_vf7C: the clock's time
    float GetMarkedTime() override;               // vt+0x80 0x004be2e0 CKGolemPhaseQTE_vf80: the clock's time
    void MarkTime() override {}                   // vt+0x84 0x4bde80 (empty)

    IKSerializable* m_unk08;  // +0x08 object reference (file: key 0x18c2, a CKHkSequenceMgr: the QTE sequence)
    int32_t m_unk0c;          // +0x0c not read by the Load: the golem's damage since its mark at the start
    int32_t m_unk10;          // +0x10 not read by the Load: the same
    int32_t m_unk14;          // +0x14 not read by the Load: the golem's damage since its mark (each Update)
    int32_t m_unk18;          // +0x18 (file: -1) the phase after a won QTE (the sequence's +0x131 set)
    int32_t m_unk1c;          // +0x1c (file: -1) its step
    int32_t m_unk20;          // +0x20 (file: -1) the phase after a lost QTE
    int32_t m_unk24;          // +0x24 (file: -1) its step
    float m_unk28;            // +0x28 (file: 0) the blend time
};
DOTD_ASSERT_SIZE(CKGolemPhaseQTE, 0x2c);
DOTD_ASSERT_OFFSET(CKGolemPhaseQTE, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKGolemPhaseQTE, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKGolemPhaseQTE, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKGolemPhaseQTE, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKGolemPhaseQTE, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKGolemPhaseQTE, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKGolemPhaseQTE, m_unk28, 0x28);
