// CKHkS08CrumblyZoneMultiState.h - Spyro's multi-state crumbly zone (key 0x3582, vtable 0xb25bf8, size 0xd4).
// Original unit: CKHkS08CrumblyZoneMultiState_2.cpp (0x4150b8-0x416710). No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/CKHkCrumblyZoneMultiState.h"
#include "k2000/util/TVector.h"

class CKHkS08CrumblyZoneMultiState : public CKHkCrumblyZoneMultiState {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd6)
    DOTD_DECLARE_FACTORIES(CKHkS08CrumblyZoneMultiState)

    // One element of the +0x90 vector (12 bytes on the PS3): a word and five bytes, one per state_maybe
    // (the vector has as many elements as the +0xb0 and +0xc0 byte vectors).
    struct StateEntry {
        uint32_t m_unk0;    // +0x0 lwbrx
        uint8_t m_unk4[5];  // +0x4..+0x8 one Read of 1 byte each
        uint8_t m_pad9[3];
    };

    // 0x004153d8 CKHkS08CrumblyZoneMultiState_Create (inlined constructor): the base's, then the three
    // vectors empty with a capacity of 1.
    CKHkS08CrumblyZoneMultiState() {
        m_vUnk90.m_ui32NbElt = 1;
        m_vUnk90.m_pBlock = nullptr;
        m_vUnk90.m_ui32NbUsedElt = 0;
        m_vUnkB0.m_ui32NbElt = 1;
        m_vUnkB0.m_pBlock = nullptr;
        m_vUnkB0.m_ui32NbUsedElt = 0;
        m_vUnkC0.m_ui32NbElt = 1;
        m_vUnkC0.m_ui32NbUsedElt = 0;
        m_vUnkC0.m_pBlock = nullptr;
    }
    ~CKHkS08CrumblyZoneMultiState() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00416080 CKHkS08CrumblyZoneMultiState_Load
    void Start() override;  // vt+0x50 0x00415540 CKHkS08CrumblyZoneMultiState_Start (C2.2)

    IKSerializable* m_pUnk8C;                  // +0x8c a CKS08Damage (struct draft)
    TVector<StateEntry, 1> m_vUnk90;           // +0x90
    uint8_t m_unk9C;                           // +0x9c
    uint8_t m_pad9D[3];
    float m_fUnkA0;                            // +0xa0
    float m_fUnkA4;                            // +0xa4
    uint32_t m_unkA8;                          // +0xa8 not set by Create or Load
    IKSerializable* m_pUnkAC;                  // +0xac
    TVector<uint8_t, 1> m_vUnkB0;              // +0xb0 one byte per state_maybe
    IKSerializable* m_pUnkBC;                  // +0xbc a CKSoundDictionaryID (struct draft)
    TVector<uint8_t, 1> m_vUnkC0;              // +0xc0 one byte per state_maybe
    uint8_t m_unkCC;                           // +0xcc
    uint8_t m_unkCD;                           // +0xcd
    uint8_t m_padCE[2];
    uint32_t m_unkD0;                          // +0xd0
};
DOTD_ASSERT_SIZE(CKHkS08CrumblyZoneMultiState, 0xd4);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_pUnk8C, 0x8c);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_vUnk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_unk9C, 0x9c);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_fUnkA0, 0xa0);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_fUnkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_pUnkAC, 0xac);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_vUnkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_pUnkBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_vUnkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_unkCC, 0xcc);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_unkCD, 0xcd);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_unkD0, 0xd0);
