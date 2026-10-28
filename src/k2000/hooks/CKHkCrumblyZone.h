// CKHkCrumblyZone.h - a ground that breaks under the hero (key 0x1982, vtable 0xb257b0, size 0x1bc). Original
// unit: CKHkCrumblyZone.cpp (0x405608-0x410190). XXL2: KMeca/CrumblyZone/CKHkCrumblyZone.h (384 bytes, base
// IKHkMeca); DotD's class is larger. Registered, but no object of this exact class occurs in the files: only
// its Spyro2008 leaf CKHkS08CrumblyZone does.
//
// Names: the first seven members (+0x20..+0x38) follow XXL2's member layout, which has the same shape
// (two pointers, a ground list, a pointer, a ground list, two pointers); the rest stay m_unkXX.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKHkCrumblyZone : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x66)

    // A node of the ground lists (XXL2 CKHkCrumblyZone::GroundList), 8 bytes, taken from the FreeListPool
    // at TOC+0x49a8 in the original (FreeListPool_Grow when empty). New nodes go to the front.
    struct GroundNode {
        IKSerializable* m_pGround;  // +0x0
        GroundNode* m_pNext;        // +0x4
    };
    // One element of the +0xa4 vector (0x14 bytes on the PS3).
    struct Entry14 {
        IKSerializable* m_pUnk0;  // +0x0
        float m_afUnk4[3];        // +0x4
        uint8_t m_unk10;          // +0x10
        uint8_t m_pad11[3];
    };
    // One element of the +0x88 vector (8 bytes on the PS3).
    struct Entry8 {
        uint32_t m_unk0;          // +0x0 lwbrx
        IKSerializable* m_pUnk4;  // +0x4
    };

    // 0x004061c8 CKHkCrumblyZone_Create (inlined constructor), in its store order.
    CKHkCrumblyZone() {
        m_lAddedSafeGround = nullptr;
        m_lAddedBrokenGround = nullptr;
        m_vUnk7C.m_ui32NbElt = 1;
        m_vUnk7C.m_pBlock = nullptr;
        m_vUnk7C.m_ui32NbUsedElt = 0;
        m_vUnk88.m_ui32NbElt = 1;
        m_vUnk88.m_pBlock = nullptr;
        m_vUnk88.m_ui32NbUsedElt = 0;
        m_unkA0 = 0;
        m_vUnkA4.m_ui32NbElt = 1;
        m_vUnkA4.m_pBlock = nullptr;
        m_vUnkA4.m_ui32NbUsedElt = 0;
        m_vUnk1A0.m_ui32NbElt = 10;
        m_vUnk1A0.m_ui32NbUsedElt = 0;
        m_vUnk1A0.m_pBlock = nullptr;
    }
    ~CKHkCrumblyZone() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0040ca50 CKHkCrumblyZone_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00406080 CKHkCrumblyZone_PostLoad
    // 0x00405b40 CKHkCrumblyZone_SetGroundSets_maybe: the safe grounds (+0x24 and the list +0x28) switched to `safe`, the
    // broken ones (+0x2c, +0x30) to the opposite (ICollisionMesh_SetActive).
    void SetGroundSets(uint8_t safe);
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x00406290 CKHkCrumblyZone_SetDefaultState
    void Start() override;                        // vt+0x50 0x00406de0 CKHkCrumblyZone_Start
    // vt+0xa0 0x0040bf00 CKHkCrumblyZone_OnActivate (IKLife::SectorLoaded calls it when the zone's sector is valid,
    // C2.4 exit): the stage node of the zone's state shown (the intact one, or the broken one when the zone is broken).
    void VfA0() override;
    // 0x00406f90 CKHkCrumblyZone_ShowStageNode: `node` shown, the zone's other stage nodes hidden (scene node flag 4).
    void ShowStageNode(IKSerializable* node);

    IKSerializable* m_pSoundDico;              // +0x20 XXL2 m_pSoundDico (layout)
    IKSerializable* m_pGround;                 // +0x24 XXL2 m_pGround (layout)
    GroundNode* m_lAddedSafeGround;            // +0x28 XXL2 m_lAddedSafeGround (layout)
    IKSerializable* m_pBrokenGround;           // +0x2c XXL2 m_pBrokenGround (layout)
    GroundNode* m_lAddedBrokenGround;          // +0x30 XXL2 m_lAddedBrokenGround (layout)
    IKSerializable* m_pSafeLeaf;               // +0x34 XXL2 m_pSafeLeaf (layout)
    IKSerializable* m_pBrokenLeaf;             // +0x38 XXL2 m_pBrokenLeaf (layout)
    uint32_t m_unk3C[6];                       // +0x3c..+0x53 not set by Create or Load
    float m_fUnk54;                            // +0x54 read (lwbrx) into a local, stored last of its group
    uint32_t m_unk58;                          // +0x58
    uint32_t m_unk5C;                          // +0x5c
    uint32_t m_unk60[2];                       // +0x60..+0x67
    uint8_t m_unk68;                           // +0x68 OnActivate: how many heroes stand on the zone's ground
    uint8_t m_pad69[3];
    IKSerializable* m_pUnk6C;                  // +0x6c
    IKSerializable* m_pUnk70;                  // +0x70
    CMatrix34* m_pUnk74[2];                    // +0x74 PostLoad: two RwMatrixCreate_Thunk matrices
    TVector<IKSerializable*, 1> m_vUnk7C;      // +0x7c
    TVector<Entry8, 1> m_vUnk88;               // +0x88
    uint32_t m_unk94;                          // +0x94
    uint32_t m_unk98;                          // +0x98
    IKSerializable* m_pUnk9C;                  // +0x9c
    uint32_t m_unkA0;                          // +0xa0 constructor 0
    TVector<Entry14, 1> m_vUnkA4;              // +0xa4
    IKSerializable* m_pUnkB0;                  // +0xb0
    uint32_t m_unkB4;                          // +0xb4
    IKSerializable* m_pUnkB8;                  // +0xb8
    uint32_t m_unkBC;                          // +0xbc
    uint32_t m_unkC0;                          // +0xc0
    IKSerializable* m_pUnkC4;                  // +0xc4
    uint32_t m_unkC8;                          // +0xc8
    float m_afUnkCC[3];                        // +0xcc a vector (Read 12 + three lwbrx)
    float m_afUnkD8[3];                        // +0xd8
    float m_afUnkE4[3];                        // +0xe4
    float m_afUnkF0[3];                        // +0xf0
    IKSerializable* m_pUnkFC;                  // +0xfc
    IKSerializable* m_pUnk100;                 // +0x100
    IKSerializable* m_pUnk104;                 // +0x104
    uint32_t m_unk108;                         // +0x108
    IKSerializable* m_pUnk10C;                 // +0x10c
    uint8_t m_unk110;                          // +0x110
    uint8_t m_pad111[3];
    uint32_t m_unk114;                         // +0x114
    uint8_t m_unk118;                          // +0x118
    uint8_t m_pad119[3];
    uint32_t m_unk11C;                         // +0x11c
    uint8_t m_unk120[0xa];                     // +0x120..+0x129
    uint16_t m_unk12A;                         // +0x12a lhbrx
    uint32_t m_unk12C;                         // +0x12c
    uint32_t m_unk130;                         // +0x130
    CTriggerStarter m_tsUnk134;                // +0x134
    CTriggerStarter m_tsUnk13C;                // +0x13c
    uint32_t m_unk144[2];                      // +0x144
    uint32_t m_unk14C;                         // +0x14c zeroed by Load for every type, then read
    uint32_t m_unk150;                         // +0x150 zeroed by Load for every type, then read
    uint32_t m_unk154;                         // +0x154
    uint32_t m_flags158;                       // +0x158 flags: Load copies bit 11 into bit 12
    uint32_t m_unk15C;                         // +0x15c
    uint32_t m_unk160;                         // +0x160
    uint32_t m_unk164;                         // +0x164
    uint8_t m_unk168;                          // +0x168
    uint8_t m_unk169;                          // +0x169
    uint8_t m_unk16A;                          // +0x16a
    uint8_t m_unk16B;                          // +0x16b
    uint8_t m_unk16C;                          // +0x16c
    uint8_t m_pad16D[3];
    uint32_t m_unk170;                         // +0x170
    uint8_t m_unk174;                          // +0x174
    uint8_t m_unk175;                          // +0x175
    uint8_t m_pad176[2];
    uint32_t m_unk178;                         // +0x178
    IKSerializable* m_pUnk17C;                 // +0x17c
    uint8_t m_unk180;                          // +0x180 OnActivate: 0 before the animation starts
    uint8_t m_unk181;                          // +0x181 OnActivate: 0 before the animation starts
    uint8_t m_pad182[2];
    uint32_t m_unk184;                         // +0x184
    uint16_t m_unk188;                         // +0x188 Load copies +0x18a into it (before reading +0x18a)
    uint16_t m_unk18A;                         // +0x18a lhbrx
    uint16_t m_unk18C;                         // +0x18c lhbrx
    uint16_t m_unk18E;                         // +0x18e lhbrx
    uint32_t m_unk190;                         // +0x190
    uint32_t m_unk194;                         // +0x194
    uint32_t m_unk198;                         // +0x198
    uint32_t m_unk19C;                         // +0x19c
    TVector<IKSerializable*, 10> m_vUnk1A0;    // +0x1a0 references (one array read)
    IKSerializable** m_apUnk1AC;               // +0x1ac OperatorNewArray, m_ui8NbUnk1AC references
    uint8_t m_ui8NbUnk1AC;                     // +0x1b0
    uint8_t m_ui8NbUnk1B4;                     // +0x1b1
    uint8_t m_pad1B2[2];
    IKSerializable** m_apUnk1B4;               // +0x1b4 Mem_AllocAligned16, m_ui8NbUnk1B4 references (0: null)
    uint8_t m_unk1B8;                          // +0x1b8 SetDefaultState: m_ui8NbUnk1B4 + 1 (a byte store)
    uint8_t m_pad1B9[3];
};
DOTD_ASSERT_SIZE(CKHkCrumblyZone, 0x1bc);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pSoundDico, 0x20);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_lAddedSafeGround, 0x28);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_lAddedBrokenGround, 0x30);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pBrokenLeaf, 0x38);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_fUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pUnk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_vUnk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_vUnk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pUnk9C, 0x9c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_vUnkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pUnkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pUnkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_afUnkCC, 0xcc);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_afUnkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pUnkFC, 0xfc);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk110, 0x110);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk118, 0x118);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk12A, 0x12a);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_tsUnk134, 0x134);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_tsUnk13C, 0x13c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk14C, 0x14c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_flags158, 0x158);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk168, 0x168);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pUnk17C, 0x17c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk180, 0x180);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk184, 0x184);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_vUnk1A0, 0x1a0);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_apUnk1AC, 0x1ac);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_ui8NbUnk1AC, 0x1b0);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_apUnk1B4, 0x1b4);
