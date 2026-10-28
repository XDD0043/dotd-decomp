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
    DOTD_DECLARE_FACTORIES(CKCameraBeacon)

    CKCameraBeacon() {}  // 0x00151ce8 CKCameraBeacon_Create: the KBase4C2 defaults only
    ~CKCameraBeacon() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00151d40 CKCameraBeacon_Load
    // vt+0xc4 0x00152040 CKCameraBeacon_vfC4 (called by CKSrvCamera_UpdateCameraBeacon_maybe): whether the beacon is in the
    // view the service describes (CKSrvCamera::SBeaconFrustum). STUB(C2.8): the camera beacon hooks (vfC0 0x151740 puts
    // them on the service's list +0x930, vfC4 tests them) are not ported; LVL010 has none, so the list stays empty.
    uint8_t IsInView(const void* frustum);

    uint8_t m_unk20;            // +0x20 runtime: flag bits set at PostLoad from +0x21 (0x152858)
    uint8_t m_unk21;            // +0x21
    uint8_t m_unk22;            // +0x22
    uint8_t m_unk23;            // +0x23 read after +0x34
    IKSerializable* m_unk24;    // +0x24
    CVector3 m_unk28;           // +0x28 a position_maybe (one 12-byte read, each word swapped)
    float m_unk34;              // +0x34
    float m_unk38;              // +0x38 read last
    float m_unk3C;              // +0x3c
    uint32_t m_unk40;           // +0x40 runtime (not set by Create or Load)
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
