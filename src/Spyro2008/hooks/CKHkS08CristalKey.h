// CKHkS08CristalKey.h - key 0x2b42, size 0x4c. Original unit: CKHkS08CristalKey.cpp. No XXL2 class. The fields
// are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class IKTime;

class CKHkS08CristalKey : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xad)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c4730
        return key == 0x2b42 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08CristalKey)

    // 0x00478e78 CKHkS08CristalKey_Construct (inlined in 0x00479370 CKHkS08CristalKey_Create): the actor base only.
    CKHkS08CristalKey() {
    }
    // 0x00479138 CKHkS08CristalKey_Destructor / 0x00478e48 BaseDestructor / 0x004790f0 DeletingDestructor: the vtable,
    // then CKHkActorBase's.
    ~CKHkS08CristalKey() override {}
    // vt+0x10 Destroy 0x478e20, vt+0x24 RecursiveRegistration 0x478df8, vt+0x30 PostLoad 0x478da8, vt+0x68 Stop 0x478d30,
    // vt+0x70 Pause 0x478c98, vt+0x78 Resume 0x478c70: CKHkActorBase's / IKHook's (inherited here).
    // vt+0x50 0x00478d58 CKHkS08CristalKey_Start: the base's (empty), +0x3a = 0, +0x39 = 1, the byte +0x2c, +0x30 and
    // +0x20 cleared.
    void Start() override {
        CKHkActorBase::Start();  // 0x3f6e48
        m_unk3A = 0;
        m_unk39[0] = 1;
        m_unk2C = 0;
        m_unk30 = 0;
        m_pUnk20 = nullptr;
    }
    // vt+0x38 0x00478cc0 CKHkS08CristalKey_SetDefaultState: the base's (empty), +0x35 = 0, +0x48 = (+0x36 clear).
    void SetDefaultState(int32_t flag) override {
        CKHkActorBase::SetDefaultState(flag);  // 0x3f72a0
        m_unk35[0] = 0;
        m_unk48 = m_unk36 != 0 ? 0u : 1u;
    }
    // vt+0xc8 0x00478990 CKHkS08CristalKey_ApplyStatePreset_maybe: state 0: +0x48 = (+0x38 clear), +0x35 = 0; else
    // +0x48 = (+0x37 clear), +0x35 = 1.
    void ApplyStatePreset(int32_t state) override {
        if (state == 0) {
            m_unk48 = m_unk38 != 0 ? 0u : 1u;
            m_unk35[0] = 0;
        } else {
            m_unk48 = m_unk37 != 0 ? 0u : 1u;
            m_unk35[0] = 1;
        }
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004793c8 CKHkS08CristalKey_Load
    // vt+0x40 0x00479168 CKHkS08CristalKey_GetInfo: the actor base's answer (1) folded with the values 0x99 (carried by a
    // hero), 0x9a (carried by an enemy) and 0x98 (carried), each a byte.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // 0x00479738 CKHkS08CristalKey_IsCarriedByHero_maybe: +0x20's carrier (vt+0x114) is a CKS08CarrierHero (class id
    // 0x247). 0x00478af8 _IsCarriedByEnemy_maybe: a CKS08CarrierEnemy (0x256). 0x00479828 _IsCarried_maybe: either.
    uint8_t IsCarriedBy(int32_t classId) const;
    uint8_t IsCarriedByHero() const { return IsCarriedBy(0x247); }
    uint8_t IsCarriedByEnemy() const { return IsCarriedBy(0x256); }
    uint8_t IsCarried() const { return IsCarriedByHero() != 0 ? 1 : IsCarriedByEnemy(); }

    // port-final F06: the run time. The key drives its emitter (+0x24) and receiver (+0x28) state machines directly
    // (their SwitchState: the old state left with the new one as `other`, the new one entered with the old one).
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x0047a390 CKHkS08CristalKey_MessageProc
    void Restart() override;                                      // vt+0x54 0x004799b0 CKHkS08CristalKey_Restart
    void Update(IKTime* clock) override;                          // vt+0x7c 0x0047a830 CKHkS08CristalKey_Update
    void VfA0() override;                                         // vt+0xa0 0x0047b0c0 CKHkS08CristalKey_OnActivate
    void VfA4() override;                                         // vt+0xa4 0x00478f88 CKHkS08CristalKey_OnDeactivate

    IKSerializable* m_pUnk20;  // +0x20 runtime: the transportable it tracks (a CKHkS08TransportableBase; Start: 0)
    IKSerializable* m_pUnk24;  // +0x24
    IKSerializable* m_pUnk28;  // +0x28
    uint8_t m_unk2C;  // +0x2c Start: 0 (stb)
    uint8_t m_pad2D[3];
    IKSerializable* m_unk30;  // +0x30 Start: 0; message 0x996: the CKGrpFightZone waiting for the key (LVL060's triggers)
    uint8_t m_unk34;  // +0x34
    uint8_t m_unk35[1];
    uint8_t m_unk36;  // +0x36
    uint8_t m_unk37;  // +0x37
    uint8_t m_unk38;  // +0x38
    uint8_t m_unk39[1];
    uint8_t m_unk3A;  // +0x3a
    uint8_t m_unk3B[1];
    CTriggerStarter m_unk3C;  // +0x3c
    uint8_t m_unk44;   // +0x44 runtime: the transportable was carried by a hero last frame (Update)
    uint8_t m_pad45[3];
    uint32_t m_unk48;  // +0x48 SetDefaultState / ApplyStatePreset: 1 when the preset's byte is clear
};
DOTD_ASSERT_SIZE(CKHkS08CristalKey, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_pUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk36, 0x36);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk37, 0x37);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk3A, 0x3a);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08CristalKey, m_unk48, 0x48);
