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
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c2b50
        return key == 0x3582 || key == 0x34c2 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe ||
               key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08CrumblyZoneMultiState)

    // 0x00413fe8 CKHkS08CrumblyZoneMultiState_GetTotalHealth_maybe: the states' (+0x38) health (+0x08) summed (float adds,
    // from the last state).
    float GetTotalHealth() const;
    // 0x00414098 CKHkS08CrumblyZoneMultiState_GetTotalMaxHealth_maybe: the states' maximum health (+0x0c) summed.
    float GetTotalMaxHealth() const;
    int32_t GetInfo(IKInfo* info, int32_t request) override;  // vt+0x40 0x00415270 CKHkS08CrumblyZoneMultiState_GetInfo

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
        m_vDamageFilters.m_ui32NbElt = 1;
        m_vDamageFilters.m_pBlock = nullptr;
        m_vDamageFilters.m_ui32NbUsedElt = 0;
        m_vManaFeedStateFlags.m_ui32NbElt = 1;
        m_vManaFeedStateFlags.m_pBlock = nullptr;
        m_vManaFeedStateFlags.m_ui32NbUsedElt = 0;
        m_vUnkC0.m_ui32NbElt = 1;
        m_vUnkC0.m_ui32NbUsedElt = 0;
        m_vUnkC0.m_pBlock = nullptr;
    }
    ~CKHkS08CrumblyZoneMultiState() override {}
    // vt+0x10 0x00415e70 CKHkS08CrumblyZoneMultiState_Destroy: the base's, then the +0xb0, +0x90 and +0xc0 vectors freed.
    void Destroy() override;

    // vt+0xa0 0x00415190 CKHkS08CrumblyZoneMultiState_OnActivate: the base's, then +0xa8 cleared.
    void VfA0() override;
    // vt+0xf0 0x00415690 CKHkS08CrumblyZoneMultiState_vfF0: the base's SetState; a zone with `sound` whose total health is
    // 0 drops its gem reward (CKS08GameManager_SpawnGemReward_maybe 0x4f8618 with +0xd0 at the node).
    void SetState(uint32_t state, uint8_t force, uint8_t sound) override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00416080 CKHkS08CrumblyZoneMultiState_Load
    void Start() override;  // vt+0x50 0x00415540 CKHkS08CrumblyZoneMultiState_Start (C2.2)
    // vt+0x54 0x004151f0 CKHkS08CrumblyZoneMultiState_Restart: the base's only.
    void Restart() override { CKHkCrumblyZoneMultiState::Restart(); }
    // vt+0xf4 0x00415b48 CKHkS08CrumblyZoneMultiState_GetHitDamage_maybe: by the damage class of the volume's damage
    // (+0x1c) and the current state's entry of +0x90: a hero damage (0x998c) on a new contact when the entry allows it
    // (+0x08 with an earth hit (kind 5) or a hero volume (owner type 2), or +0x04); an element damage (0x99cc,
    // continuous or new) whose element (+0x20) is in the entry's mask (+0x00), or as ability 5 (+0x38) with the earth
    // boulder rolling (+0x06), the partner flight (+0x05) or +0x07; a Spyro damage (0x970c, continuous or new) always.
    // A hit is the damage's amount, times the frame time when continuous; anything else 0.
    float GetHitDamage(IKBoundingVolume* volume, uint8_t touched) override;
    // vt+0x104 0x00415740 CKHkS08CrumblyZoneMultiState_SpawnExplosionFx: the game manager's explosion effect for the zone.
    void Vf104() override;
    // vt+0x7c 0x004157b8 CKHkS08CrumblyZoneMultiState_Update: the base's; then a zone fed with mana (+0x9c, the current
    // state's byte of +0xb0): the heroes within +0xa0 marked near a crumbly zone (CKHkS08Hero_SetNearCrumblyZoneFlags_maybe),
    // the nearest one with mana feeds it: every +0xa4 seconds (+0xa8 the timer) his mana pays a mana bonus's value
    // (ConsumeDragonMana), sound 0 of +0xbc plays and a mana bonus spawned at his hot spot 5 flies to the zone.
    void Update(IKTime* frameClock) override;

    IKSerializable* m_pDamage;                  // +0x8c a CKS08Damage (struct draft)
    TVector<StateEntry, 1> m_vDamageFilters;           // +0x90
    uint8_t m_bManaFeedEnabled;                           // +0x9c
    uint8_t m_pad9D[3];
    float m_fManaFeedRadius;                            // +0xa0
    float m_fManaFeedInterval;                            // +0xa4
    float m_fManaFeedTimer;                             // +0xa8 not set by Create or Load: the mana feed's timer
    IKSerializable* m_pUnkAC;                  // +0xac
    TVector<uint8_t, 1> m_vManaFeedStateFlags;              // +0xb0 one byte per state_maybe
    IKSerializable* m_pSoundDico;                  // +0xbc a CKSoundDictionaryID (struct draft)
    TVector<uint8_t, 1> m_vUnkC0;              // +0xc0 one byte per state_maybe
    uint8_t m_unkCC;                           // +0xcc
    uint8_t m_unkCD;                           // +0xcd
    uint8_t m_padCE[2];
    uint32_t m_ui32GemReward;                          // +0xd0
};
DOTD_ASSERT_SIZE(CKHkS08CrumblyZoneMultiState, 0xd4);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_pDamage, 0x8c);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_vDamageFilters, 0x90);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_bManaFeedEnabled, 0x9c);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_fManaFeedRadius, 0xa0);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_fManaFeedInterval, 0xa4);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_pUnkAC, 0xac);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_vManaFeedStateFlags, 0xb0);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_pSoundDico, 0xbc);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_vUnkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_unkCC, 0xcc);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_unkCD, 0xcd);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZoneMultiState, m_ui32GemReward, 0xd0);
