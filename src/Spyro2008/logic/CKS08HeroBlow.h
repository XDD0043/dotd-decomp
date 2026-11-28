// CKS08HeroBlow.h - one hero blow (key 0x7a8c, vtable 0xb230b0, size 0x68): the attack a CKS08HeroCombo node
// performs. Original unit: CKS08HeroBlow.cpp (0x36e2d0-0x36f578). No XXL2 class of this name; members keep
// placeholder names (types from the live struct draft and the file data). Create only stores the vtable.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08HeroDamage.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKS08HeroBlow : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1ea)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x7a8c || key == 0xc; }  // vt+0x08 0x9becb0
    DOTD_DECLARE_FACTORIES(CKS08HeroBlow)

    CKS08HeroBlow() {}  // inlined in 0x0036e440 CKS08HeroBlow_Create: the vtable only
    ~CKS08HeroBlow() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0036e6b8 CKS08HeroBlow_Load
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x0036e5b0: the curve's and the camera data's
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x0036e650: type 0 resets the timer
    void Destroy() override;                            // vt+0x10 0x0036e670: the camera data's Destroy

    // The run-time slots (vt+0x54..+0xc0; outputs/ability-analysis/combat.md has the fields' uses). Non-virtual here:
    // no class derives from CKS08HeroBlow.
    // vt+0x54 0x0036e2e0 CKS08HeroBlow_GetDamageAmount: the damage's amount as an integer (truncated; times 0 when the
    // damage is continuous).
    int32_t GetDamageAmount() const {
        const CKDamage* damage = m_pDamage;
        const float amount = damage->m_bContinuous != 0 ? damage->m_fAmount * 0.0f : damage->m_fAmount;
        return static_cast<int32_t>(static_cast<int64_t>(amount));  // fctidz, the low word
    }
    uint8_t GetLinkCode() const { return m_ui8LinkCode; }         // vt+0x58 0x009beba0
    uint8_t Vf5C() const { return m_unk50; }                // vt+0x5c 0x009beba8 CKS08HeroBlow_vf5C
    uint8_t Vf60() const { return m_unk51; }                // vt+0x60 0x009bebb0 CKS08HeroBlow_vf60
    uint8_t GetHotspotIndex() const { return m_ui8HotspotIndex; }     // vt+0x64 0x009bebb8
    float GetHitRadius() const { return m_fHitRadius; }          // vt+0x68 0x009bebc0
    float Vf6C() const { return m_unk20 + m_unk10; }        // vt+0x6c 0x009bebc8 CKS08HeroBlow_vf6C
    float Vf70() const { return m_unk20; }                  // vt+0x70 0x009bebd8 CKS08HeroBlow_vf70
    float Vf74() const { return m_unk24; }                  // vt+0x74 0x009bebe0 CKS08HeroBlow_vf74
    float Vf78() const { return m_unk28; }                  // vt+0x78 0x009bebe8 CKS08HeroBlow_vf78
    float GetRecoveryDelay() const { return m_fRecoveryDelay; }      // vt+0x7c 0x009bebf0
    IKSerializable* GetCameraData() const { return m_pCameraData; }  // vt+0x80 0x009bebf8
    uint8_t Vf84() const { return m_unk40; }                // vt+0x84 0x009bec00 CKS08HeroBlow_vf84
    float Vf88() const { return m_unk44; }                  // vt+0x88 0x009bec08 CKS08HeroBlow_vf88
    int32_t GetAnimId() const { return m_i32AnimOffset + 0x91; }    // vt+0x8c 0x0036e2d0
    float GetAnimSpeed() const { return m_fAnimSpeed; }          // vt+0x90 0x009bec10
    uint8_t Vf94() const { return m_unk34; }                // vt+0x94 0x009bec18 CKS08HeroBlow_vf94
    void Vf98(uint8_t value) { m_ui8Hero = value; }           // vt+0x98 0x009bec20 CKS08HeroBlow_vf98
    uint8_t IsGrabBlow() const { return m_bIsGrabBlow; }          // vt+0x9c 0x009bec28
    uint8_t ShouldThrowOnTimeout() const { return m_bIsGrabBlow != 0 && m_bThrowOnTimeout != 0 ? 1 : 0; }  // vt+0xa0 0x009bec30 _maybe
    float GetThrowDelay() const { return m_fThrowDelay; }         // vt+0xa4 0x009bec58
    float GetReleaseDelay() const { return m_bHasReleaseDelay != 0 ? m_fReleaseDelay : -10.0f; }  // vt+0xa8 0x0036e330 (TOC +0x2f44)
    uint8_t VfAC() const { return m_unk61; }                // vt+0xac 0x009bec60 CKS08HeroBlow_vfAC
    CKS08HeroDamage* GetDamage() const { return m_pDamage; }  // vt+0xb0 0x009bec68
    void TickTimer(float dt) { m_fTimer = m_fTimer - dt; }   // vt+0xb4 0x009bec70
    uint8_t VfB8() const { return m_fTimer < 0.0f ? 1 : 0; }  // vt+0xb8 0x009bec80 CKS08HeroBlow_vfB8 (TOC +0x2f40)
    void ResetTimer() { m_fTimer = m_unk0c; }                // vt+0xbc 0x009beca0
    // vt+0xc0 0x0036e350 CKS08HeroBlow_EvalTimeScale: the curve +0x4c at `x` when there is one, else 1.
    float EvalTimeScale(float x) const;

    uint8_t m_ui8HotspotIndex;            // +0x04
    uint8_t m_pad05[3];
    float m_fHitRadius;              // +0x08 (file: 0.8, 1.0)
    float m_unk0c;              // +0x0c
    float m_unk10;              // +0x10
    uint8_t m_unk14;            // +0x14
    uint8_t m_pad15[3];
    float m_fTimer;              // +0x18 runtime
    float m_fRecoveryDelay;              // +0x1c
    float m_unk20;              // +0x20 (file: 0.02)
    float m_unk24;              // +0x24 (file: 320, 160, 200)
    float m_unk28;              // +0x28
    uint8_t m_ui8Hero;            // +0x2c runtime
    uint8_t m_ui8LinkCode;            // +0x2d
    uint8_t m_pad2e[2];
    int32_t m_i32AnimOffset;            // +0x30
    uint8_t m_unk34;            // +0x34
    uint8_t m_pad35[3];
    float m_fAnimSpeed;              // +0x38 (file: 1.0)
    IKSerializable* m_pCameraData;    // +0x3c (file: key 0x9e8c references, live: CKAnimatedCameraData)
    uint8_t m_unk40;            // +0x40
    uint8_t m_pad41[3];
    float m_unk44;              // +0x44 (file: 0.4)
    uint8_t m_bHasTimeScaleCurve;            // +0x48 whether +0x4c is in the file
    uint8_t m_pad49[3];
    IKSerializable* m_pTimeScaleCurve;    // +0x4c (live: CKCurve2DCpnt); 0 when +0x48 is 0
    uint8_t m_unk50;            // +0x50
    uint8_t m_unk51;            // +0x51
    uint8_t m_bIsGrabBlow;            // +0x52
    uint8_t m_bThrowOnTimeout;            // +0x53
    float m_fThrowDelay;              // +0x54
    uint8_t m_unk58;            // +0x58
    uint8_t m_pad59[3];
    float m_fReleaseDelay;              // +0x5c (file: 1.0)
    uint8_t m_bHasReleaseDelay;            // +0x60
    uint8_t m_unk61;            // +0x61
    uint8_t m_pad62[2];
    CKS08HeroDamage* m_pDamage; // +0x64
};
DOTD_ASSERT_SIZE(CKS08HeroBlow, 0x68);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_ui8HotspotIndex, 0x04);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_fHitRadius, 0x08);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_fRecoveryDelay, 0x1c);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_ui8LinkCode, 0x2d);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_i32AnimOffset, 0x30);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_fAnimSpeed, 0x38);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_pCameraData, 0x3c);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_bHasTimeScaleCurve, 0x48);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_pTimeScaleCurve, 0x4c);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_bThrowOnTimeout, 0x53);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_fThrowDelay, 0x54);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_fReleaseDelay, 0x5c);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_bHasReleaseDelay, 0x60);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_unk61, 0x61);
DOTD_ASSERT_OFFSET(CKS08HeroBlow, m_pDamage, 0x64);
