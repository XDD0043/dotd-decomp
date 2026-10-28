// CKGrpSquad.h - a squad of enemies with its states, spawn data and triggers (key 0x604, vtable 0xb212b0,
// size 0xd0). Original unit: CKGrpSquad.cpp. XXL2: K/KSquad/CKGrpSquad.h; DotD's layout and Load differ
// (more vectors, five trigger starters), so only the first vector keeps XXL2's name (m_vStates: XXL2's Load
// reads it first, each state with its CMatrix34) and the current matrix (m_pCurrentMatrix, a copy of the
// first state's). The other names are placeholders.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKGrpSquad : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x18)
    DOTD_DECLARE_FACTORIES(CKGrpSquad)

    // XXL2 SGrpSquadState (_maybe): 0x6c bytes. CKGrpSquad_Phase_Init (0x263530) sets the vector only.
    struct SState {
        SState() {  // 0x00263530 CKGrpSquad_Phase_Init
            m_vUnk5c.m_pBlock = nullptr;
            m_vUnk5c.m_ui32NbElt = 1;
            m_vUnk5c.m_ui32NbUsedElt = 0;
        }
        CMatrix34* m_pMatrix;        // +0x00 RwMatrixCreate + CMatrix34_LoadMatrix
        uint8_t m_unk04;             // +0x04
        uint8_t m_pad05[3];
        IKSerializable* m_pUnk08;    // +0x08 reference
        uint8_t m_unk0c;             // +0x0c
        uint8_t m_pad0d[3];
        uint32_t m_unk10;            // +0x10
        uint8_t m_unk14;             // +0x14
        uint8_t m_pad15[3];
        uint32_t m_unk18;            // +0x18
        uint8_t m_unk1c;             // +0x1c
        uint8_t m_pad1d[3];
        float m_unk20[3];            // +0x20 one 0xc-byte read, three swaps
        IKSerializable* m_pUnk2c;    // +0x2c reference
        uint8_t m_unk30;             // +0x30
        uint8_t m_pad31[3];
        IKSerializable* m_pUnk34;    // +0x34 reference
        uint8_t m_unk38;             // +0x38
        uint8_t m_unk39;             // +0x39
        uint8_t m_unk3a;             // +0x3a
        uint8_t m_pad3b;
        IKSerializable* m_pUnk3c;    // +0x3c reference
        uint32_t m_unk40[5];         // +0x40..+0x50
        uint32_t m_unk54;            // +0x54 not read
        uint32_t m_unk58;            // +0x58
        TVector<uint32_t, 1> m_vUnk5c;  // +0x5c
        uint8_t m_unk68;             // +0x68
        uint8_t m_unk69;             // +0x69
        uint8_t m_unk6a;             // +0x6a
        uint8_t m_pad6b;
    };
    // 0x20 bytes: two bytes, two word vectors and a word.
    struct SMemberEntry {
        uint8_t m_unk00;                  // +0x00
        uint8_t m_unk01;                  // +0x01
        uint8_t m_pad02[2];
        TVector<uint32_t, 1> m_vUnk04;    // +0x04
        TVector<uint32_t, 1> m_vUnk10;    // +0x10
        uint32_t m_unk1c;                 // +0x1c
    };
    // 4 bytes: two bytes the Load clears.
    struct SFlags {
        uint8_t m_unk00;
        uint8_t m_unk01;
        uint8_t m_pad02[2];
    };

    // 0x0025b4c0 CKGrpSquad_Create (the constructor 0x25aa10 inlined): the vectors null, 1, 0; +0x50 = 0;
    // the priority word 0x80000013.
    CKGrpSquad() {
        m_vUnk2c.m_pBlock = nullptr;
        m_vUnk2c.m_ui32NbElt = 1;
        m_vUnk2c.m_ui32NbUsedElt = 0;
        m_vUnk38.m_pBlock = nullptr;
        m_vUnk38.m_ui32NbElt = 1;
        m_vUnk38.m_ui32NbUsedElt = 0;
        m_vUnk44.m_pBlock = nullptr;
        m_vUnk44.m_ui32NbElt = 1;
        m_vUnk44.m_ui32NbUsedElt = 0;
        m_unk50 = 0;
        m_vStates.m_pBlock = nullptr;
        m_vStates.m_ui32NbElt = 1;
        m_vStates.m_ui32NbUsedElt = 0;
        m_vUnka8.m_pBlock = nullptr;
        m_vUnka8.m_ui32NbElt = 1;
        m_vUnka8.m_ui32NbUsedElt = 0;
        m_vUnkb4.m_pBlock = nullptr;
        m_vUnkb4.m_ui32NbElt = 1;
        m_vUnkb4.m_ui32NbUsedElt = 0;
        m_vUnkc0.m_pBlock = nullptr;
        m_vUnkc0.m_ui32NbElt = 1;
        m_vUnkc0.m_ui32NbUsedElt = 0;
        m_ui32Priority = 0x80000013u;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0025e4f0 CKGrpSquad_Load
    void Start() override;  // vt+0x50 0x0025d6c8 CKGrpSquad_Start
    // 0x0025afe0 CKGrpSquad_ResetMemberSlots_maybe (not virtual): the member-position vector (+0xa8) is zeroed and
    // grown to one slot per member of the parent enemy group (its +0x54 count, low byte).
    void ResetMemberSlots();

    TVector<SFlags, 1> m_vUnk2c;                      // +0x2c
    TVector<uint8_t, 1> m_vUnk38;                     // +0x38
    TVector<TVector<SMemberEntry, 1>, 1> m_vUnk44;    // +0x44
    uint32_t m_unk50;                                 // +0x50
    uint8_t m_unk54;                                  // +0x54 not set
    uint8_t m_unk55;                                  // +0x55 the Load clears it
    uint8_t m_pad56[2];
    TVector<SState, 1> m_vStates;                     // +0x58
    CMatrix34* m_pCurrentMatrix;                      // +0x64 a copy of the first state's matrix
    CTriggerStarter m_tsUnk68;                        // +0x68
    CTriggerStarter m_tsUnk70;                        // +0x70
    CTriggerStarter m_tsUnk78;                        // +0x78
    CTriggerStarter m_tsUnk80;                        // +0x80
    CTriggerStarter m_tsUnk88;                        // +0x88
    uint32_t m_unk90;                                 // +0x90..+0x9b not set
    uint8_t m_unk94;                                  // +0x94 runtime (Start: 0)
    uint8_t m_pad95[3];
    uint32_t m_unk98;
    SState* m_pStartState;                            // +0x9c &m_vStates[index] for a file index >= 1, else 0
    uint8_t m_unka0;                                  // +0xa0
    uint8_t m_pada1[3];
    uint32_t m_unka4;                                 // +0xa4 not set
    TVector<uint32_t, 1> m_vUnka8;                    // +0xa8 runtime (constructor only)
    TVector<uint32_t, 1> m_vUnkb4;                    // +0xb4 runtime
    TVector<uint32_t, 1> m_vUnkc0;                    // +0xc0 runtime
    uint8_t m_unkcc;                                  // +0xcc runtime (Start: 0)
    uint8_t m_padcd[3];
};
DOTD_ASSERT_SIZE(CKGrpSquad::SState, 0x6c);
DOTD_ASSERT_OFFSET(CKGrpSquad::SState, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKGrpSquad::SState, m_pUnk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKGrpSquad::SState, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKGrpSquad::SState, m_vUnk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKGrpSquad::SState, m_unk68, 0x68);
DOTD_ASSERT_SIZE(CKGrpSquad::SMemberEntry, 0x20);
DOTD_ASSERT_OFFSET(CKGrpSquad::SMemberEntry, m_vUnk10, 0x10);
DOTD_ASSERT_SIZE(CKGrpSquad, 0xd0);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_vUnk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_vUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_vUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_unk55, 0x55);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_vStates, 0x58);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_pCurrentMatrix, 0x64);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_tsUnk68, 0x68);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_tsUnk88, 0x88);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_pStartState, 0x9c);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_unka0, 0xa0);
DOTD_ASSERT_OFFSET(CKGrpSquad, m_vUnkc0, 0xc0);
