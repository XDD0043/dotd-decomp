// CKS08FightZoneCpnt.h - a fight zone's parameters (key 0x1146, vtable 0xb21eb0, size 0xb0; base KBaseDC6).
// Original unit: CKS08FightZoneCpnt.cpp. No XXL2 class of this name. The Load has no type test.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/KBaseDC6.h"
#include "k2000/util/TVector.h"

class CKGrpFightZone;

class CKS08FightZoneCpnt : public KBaseDC6 {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x45)
    DOTD_DECLARE_FACTORIES(CKS08FightZoneCpnt)

    // 0x00274c38 CKS08FightZoneCpnt_Create (inlined constructor): the six vectors null, 1, 0.
    CKS08FightZoneCpnt() {
        m_vUnk30 = {nullptr, 1, 0};
        m_vUnk64 = {nullptr, 1, 0};
        m_vUnk70 = {nullptr, 1, 0};
        m_vUnk7c = {nullptr, 1, 0};
        m_vUnk88 = {nullptr, 1, 0};
        m_vUnk98 = {nullptr, 1, 0};
    }

    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bc4c8
        return key == 0x1146 || key == 0xdc6 || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002758c0 CKS08FightZoneCpnt_Load
    // vt+0x64 0x9bc418 CKS08FightZoneCpnt_vf64: the owning fight zone (CKGrpFightZone_Load calls it).
    // Not declared virtual yet (the slots between +0x4c and +0x64 are not known).
    void SetFightZone(CKGrpFightZone* zone) { m_pFightZone = zone; }
    // vt+0x60 0x274dd8 CKS08FightZoneCpnt_vf60 (CKGrpFightZone_Start / _Restart call it): +0xa8 and +0x94
    // cleared, the byte +0xa4 = whether the vector at +0x30 is empty. Not declared virtual yet (see above).
    void Vf60();

    uint32_t m_unk04;                       // +0x04
    CKGrpFightZone* m_pFightZone;           // +0x08 set by CKGrpFightZone_Load (vt+0x64)
    float m_unk0c;                          // +0x0c
    uint8_t m_unk10;                        // +0x10
    uint8_t m_pad11[3];
    uint32_t m_unk14;                       // +0x14 not set
    float m_unk18;                          // +0x18
    float m_unk1c;                          // +0x1c
    uint32_t m_unk20;                       // +0x20
    uint32_t m_unk24[3];                    // +0x24 one 0xc-byte read, three swaps
    TVector<IKSerializable*, 1> m_vUnk30;   // +0x30 references
    uint32_t m_unk3c;                       // +0x3c
    float m_unk40;                          // +0x40
    uint32_t m_unk44;                       // +0x44 not set
    float m_unk48;                          // +0x48
    IKSerializable* m_pUnk4c;               // +0x4c reference
    IKSerializable* m_pUnk50;               // +0x50 reference
    IKSerializable* m_pUnk54;               // +0x54 reference
    uint32_t m_unk58;                       // +0x58
    uint32_t m_unk5c;                       // +0x5c not set
    float m_unk60;                          // +0x60
    TVector<IKSerializable*, 1> m_vUnk64;   // +0x64 references
    TVector<uint8_t, 1> m_vUnk70;           // +0x70 bytes
    TVector<uint8_t, 1> m_vUnk7c;           // +0x7c bytes
    TVector<uint8_t, 1> m_vUnk88;           // +0x88 bytes
    uint32_t m_unk94;                       // +0x94 vf60 clears it
    TVector<IKSerializable*, 1> m_vUnk98;   // +0x98 references
    uint8_t m_unka4;                        // +0xa4 vf60: the vector at +0x30 is empty (+0xa5..+0xa7: padding never written)
    uint8_t m_pada5[3];
    uint32_t m_unka8;                       // +0xa8 vf60 / vf78 0x274b10
    uint8_t m_unkac;                        // +0xac
    uint8_t m_padad[3];
};
DOTD_ASSERT_SIZE(CKS08FightZoneCpnt, 0xb0);
DOTD_ASSERT_OFFSET(CKS08FightZoneCpnt, m_pFightZone, 0x08);
DOTD_ASSERT_OFFSET(CKS08FightZoneCpnt, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKS08FightZoneCpnt, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKS08FightZoneCpnt, m_vUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKS08FightZoneCpnt, m_pUnk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKS08FightZoneCpnt, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKS08FightZoneCpnt, m_vUnk88, 0x88);
DOTD_ASSERT_OFFSET(CKS08FightZoneCpnt, m_vUnk98, 0x98);
DOTD_ASSERT_OFFSET(CKS08FightZoneCpnt, m_unkac, 0xac);
