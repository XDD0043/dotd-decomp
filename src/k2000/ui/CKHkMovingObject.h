// CKHkMovingObject.h - a hook moving an object through a list of steps (key 0x3242, vtable 0xb2fe80,
// size 0x38; library-TOC code). Original unit: k2000/ui/CKHkMovingObject.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKHkMovingObject : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc9)
    DOTD_DECLARE_FACTORIES(CKHkMovingObject)

    // One step of the movement (0x44 bytes, OperatorNew without a constructor: the fields the Load does
    // not read keep the allocator's bytes).
    struct Step {
        IKSerializable* m_pUnk0;     // +0x00 reference (read second)
        IKSerializable* m_pUnk4;     // +0x04 reference (read first)
        uint8_t m_unk8;              // +0x08
        uint8_t m_pad9[3];
        uint32_t m_unkC;             // +0x0c
        uint8_t m_unk10;             // +0x10
        uint8_t m_pad11[3];
        uint32_t m_unk14;            // +0x14
        IKSerializable* m_pUnk18;    // +0x18 reference
        uint32_t m_unk1C;            // +0x1c
        uint32_t m_unk20;            // +0x20
        uint32_t m_unk24;            // +0x24 not loaded (the Load reads a word here into a local and drops it)
        CTriggerStarter m_tsUnk28;   // +0x28
        CTriggerStarter m_tsUnk30;   // +0x30
        IKSerializable* m_pUnk38;    // +0x38 reference
        uint8_t m_unk3C;             // +0x3c not loaded; SetDefaultState copies m_unk8 (a byte) into it
        uint8_t m_pad3D[3];
        uint32_t m_unk40;            // +0x40 not loaded; SetDefaultState copies m_unkC into it
    };

    // 0x005c6508 CKHkMovingObject_Create (inlined constructor, = 0x005c5938 CKHkMovingObject_Construct):
    // the IKLife/IKHook defaults, then the step vector's capacity 1, length 0, block 0.
    CKHkMovingObject() {
        m_vpSteps.m_ui32NbElt = 1;
        m_vpSteps.m_ui32NbUsedElt = 0;
        m_vpSteps.m_pBlock = nullptr;
    }
    ~CKHkMovingObject() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c6e58 CKHkMovingObject_Load
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x005c6360 CKHkMovingObject_SetDefaultState
    // 0x005c6278 CKHkMovingObject_RestoreCheckpointState_maybe (the SetGameState override; see
    // CKHkDetectorGroup::RestoreCheckpointState): state 0 takes the first saved values (m_unk28, step +8/+0xc),
    // any other the second (m_unk29, step +0x10/+0x14). Returns 1.
    int32_t RestoreCheckpointState(uint32_t stateIdForLeft);

    CMatrix34* m_pMatrix;                // +0x20 RwMatrixCreate, then CMatrix34_LoadMatrix (Load)
    IKSerializable* m_pUnk24;            // +0x24 reference
    uint8_t m_unk28;                     // +0x28
    uint8_t m_unk29;                     // +0x29
    uint8_t m_unk2A;                     // +0x2a runtime: m_unk28 or m_unk29 (the default / checkpoint state)
    uint8_t m_pad2B;
    TVector<Step*, 1> m_vpSteps;         // +0x2c sized by the file's count (Load)
};
DOTD_ASSERT_SIZE(CKHkMovingObject, 0x38);
DOTD_ASSERT_OFFSET(CKHkMovingObject, m_pMatrix, 0x20);
DOTD_ASSERT_OFFSET(CKHkMovingObject, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkMovingObject, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkMovingObject, m_unk29, 0x29);
DOTD_ASSERT_OFFSET(CKHkMovingObject, m_vpSteps, 0x2c);
DOTD_ASSERT_SIZE(CKHkMovingObject::Step, 0x44);
DOTD_ASSERT_OFFSET(CKHkMovingObject::Step, m_unkC, 0xc);
DOTD_ASSERT_OFFSET(CKHkMovingObject::Step, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKHkMovingObject::Step, m_pUnk18, 0x18);
DOTD_ASSERT_OFFSET(CKHkMovingObject::Step, m_tsUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkMovingObject::Step, m_pUnk38, 0x38);
