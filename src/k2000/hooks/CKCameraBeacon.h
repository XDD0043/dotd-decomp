// CKCameraBeacon.h - a camera beacon (key 0x582, vtable 0xb1a858, size 0x54). Original unit:
// CKCameraBeacon.cpp; its base KBase4C2's functions sit in CKCameraBeacon_2.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/KBase4C2.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CTriggerStarter.h"

class CKCameraBeacon : public KBase4C2 {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x16)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a7ad0
        return key == 0x582 || key == 0x4c2 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCameraBeacon)

    CKCameraBeacon() {}  // 0x00151ce8 CKCameraBeacon_Create: the KBase4C2 defaults only
    ~CKCameraBeacon() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00151d40 CKCameraBeacon_Load
    // vt+0xc0 0x00151740 CKCameraBeacon_vfC0 (C2.8 port-rest R03): the geometry follows the parent, the beacon joins the
    // camera service's list (+0x930) and its focus bits / time (+0x40) update. See the .cpp.
    void VfC0(IKTime* clock) override;
    // vt+0xc4 0x00152040 CKCameraBeacon_vfC4 (called by CKSrvCamera_UpdateCameraBeacon_maybe): whether the beacon is in the
    // view the service describes (CKSrvCamera::SBeaconFrustum). STUB(C2.8): the view test is not ported (vfC0 0x151740,
    // which puts the beacons on the service's list +0x930, is); LVL010 has no camera beacon.
    uint8_t IsInView(const void* frustum);

    // C2.8 port-all P16. vt+0x10 0x00151470 CKCameraBeacon_Destroy: KBase4C2's (empty), the geometry's (+0x24, vt+0x10)
    // Destroy, the reference cleared.
    void Destroy() override;
    // vt+0x24 0x001513b0 CKCameraBeacon_RecursiveRegistration: KBase4C2's (IKHook's), the geometry's with type 0 for a
    // type 0, then the two trigger starters' (KStub_Return1_2361b0: nothing).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x1c 0x00152628 CKCameraBeacon_MessageProc: 0x700 enables the beacon (+0x20 bit 0); 0x701 clears bits 0-2 and,
    // when it is the camera service's held beacon (+0x915, +0x920), takes its node's entry off the service's target stack
    // (the last entry moved into its place; +0x46c bit 23 set). Both answer 0, other messages 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    int32_t PostLoad(int32_t type) override;                 // vt+0x30 0x00152858 CKCameraBeacon_PostLoad
    void SetDefaultState(int32_t flag) override;             // vt+0x38 0x00152920 CKCameraBeacon_SetDefaultState
    // vt+0x3c 0x00152800 CKCameraBeacon_SetGameState: state 0 enables (+0x20 bit 0), state 1 clears bits 0-2; 1.
    int32_t SetGameState(const SApplyGameState* state) override;
    // vt+0x40 0x001516c8 CKCameraBeacon_GetInfo: id 1 answers 0x00151688 CKCameraBeacon_IsActiveBeaconPredicate_maybe (the
    // beacon is the camera service's held one: +0x915 and +0x920) as a byte.
    int32_t GetInfo(IKInfo* info, int32_t request) override;

    uint8_t m_unk20;            // +0x20 runtime: flag bits set at PostLoad from +0x21 (0x152858)
    uint8_t m_unk21;            // +0x21
    uint8_t m_unk22;            // +0x22
    uint8_t m_unk23;            // +0x23 read after +0x34
    IKSerializable* m_unk24;    // +0x24
    CVector3 m_unk28;           // +0x28 a position_maybe (one 12-byte read, each word swapped)
    float m_unk34;              // +0x34
    float m_unk38;              // +0x38 read last
    float m_unk3C;              // +0x3c
    float m_fUnk40;             // +0x40 runtime (not set by Create or Load): the time the beacon holds the focus (vfC0)
    CTriggerStarter m_unk44;    // +0x44
    CTriggerStarter m_unk4C;    // +0x4c
};
// 0x00151368 CKCameraBeacon_QueueEnterLeaveSignals: the beacon's enter signals (+0x44) when `enter`, else its leave
// signals (+0x4c), queued (step 5).
void CKCameraBeacon_FireEnterLeaveSignals(CKCameraBeacon* beacon, int32_t enter);

DOTD_ASSERT_SIZE(CKCameraBeacon, 0x54);
DOTD_ASSERT_OFFSET(CKCameraBeacon, m_unk21, 0x21);
DOTD_ASSERT_OFFSET(CKCameraBeacon, m_unk23, 0x23);
DOTD_ASSERT_OFFSET(CKCameraBeacon, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKCameraBeacon, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKCameraBeacon, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKCameraBeacon, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKCameraBeacon, m_unk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKCameraBeacon, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKCameraBeacon, m_unk4C, 0x4c);
