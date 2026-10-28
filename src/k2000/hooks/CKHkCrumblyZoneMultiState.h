// CKHkCrumblyZoneMultiState.h - a crumbly zone with several states (key 0x34c2, vtable 0xb259d0, size 0x8c).
// Original unit: CKHkCrumblyZoneMultiState.cpp (0x411100-0x413fe8). No XXL2 class (XXL2 only has the
// single-state CKHkCrumblyZone). Registered, but no object of this exact class occurs in the files: only
// its Spyro2008 leaf CKHkS08CrumblyZoneMultiState does.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKHkCrumblyZoneMultiState : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd3)

    // 0x00411df8 CKHkCrumblyZoneMultiState_Create (inlined constructor): the two reference vectors empty
    // with a capacity of 1.
    CKHkCrumblyZoneMultiState() {
        m_vUnk2C.m_pBlock = nullptr;
        m_vUnk2C.m_ui32NbElt = 1;
        m_vUnk2C.m_ui32NbUsedElt = 0;
        m_vUnk38.m_ui32NbElt = 1;
        m_vUnk38.m_ui32NbUsedElt = 0;
        m_vUnk38.m_pBlock = nullptr;
    }
    ~CKHkCrumblyZoneMultiState() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00412f98 CKHkCrumblyZoneMultiState_Load
    void Start() override;  // vt+0x50 0x004122b8 CKHkCrumblyZoneMultiState_Start

    uint32_t m_unk20;                          // +0x20
    uint32_t m_unk24;                          // +0x24
    uint32_t m_unk28;                          // +0x28 not set by Create or Load
    TVector<IKSerializable*, 1> m_vUnk2C;      // +0x2c references (the states_maybe)
    TVector<IKSerializable*, 1> m_vUnk38;      // +0x38 references
    IKSerializable* m_pUnk44;                  // +0x44
    IKSerializable* m_pUnk48;                  // +0x48
    IKSerializable* m_pUnk4C;                  // +0x4c
    float m_afUnk50[3];                        // +0x50 a vector (Read 12 + three lwbrx)
    float m_afUnk5C[3];                        // +0x5c a vector
    IKSerializable* m_pUnk68;                  // +0x68
    IKSerializable* m_pUnk6C;                  // +0x6c
    IKSerializable* m_pUnk70;                  // +0x70
    IKSerializable* m_pUnk74;                  // +0x74
    uint16_t m_unk78;                          // +0x78 lhbrx (a pathfinding node index_maybe, as XXL2
                                               // CKHkCrumblyZone::m_i16PathFindingNodeIndex)
    uint8_t m_pad7A[2];
    CTriggerStarter m_tsUnk7C;                 // +0x7c
    CTriggerStarter m_tsUnk84;                 // +0x84
};
DOTD_ASSERT_SIZE(CKHkCrumblyZoneMultiState, 0x8c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_vUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_vUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_pUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_pUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_pUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_afUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_afUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_pUnk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_pUnk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_pUnk70, 0x70);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_pUnk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_tsUnk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneMultiState, m_tsUnk84, 0x84);
