// CKHkMovingObject.h - a hook moving an object through a list of steps (key 0x3242, vtable 0xb2fe80,
// size 0x38; library-TOC code). Original unit: k2000/ui/CKHkMovingObject.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/IKInfo.h"
#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/memory/Mem.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKHkMovingObject : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc9)
    DOTD_DECLARE_FACTORIES(CKHkMovingObject)

    // One step of the movement (0x44 bytes, OperatorNew without a constructor: the fields the Load does
    // not read keep the allocator's bytes).
    struct Step {
        IKSerializable* m_pUnk0;     // +0x00 reference (read second): the step's CKMoveCpntUpdater
        IKSerializable* m_pUnk4;     // +0x04 reference (read first): the CKMoveCpnt it plays
        uint8_t m_unk8;              // +0x08 the default state's "running"
        uint8_t m_pad9[3];
        float m_unkC;                // +0x0c the default state's progress (0..1)
        uint8_t m_unk10;             // +0x10 the checkpoint state's "running"
        uint8_t m_pad11[3];
        float m_unk14;               // +0x14 the checkpoint state's progress
        IKSerializable* m_pUnk18;    // +0x18 reference: an object whose value (0..1) places the movement instead of the time
        uint32_t m_unk1C;            // +0x1c the value's argument
        // +0x20 the value id; PostLoad replaces it with the object's accessor (GetInfo vt+0x40).
        union {
            uint32_t m_unk20;
            InfoAccessor m_pfnValue;
        };
        uint32_t m_unk24;            // +0x24 not loaded; PostLoad: the accessor's this-adjustment (0)
        CTriggerStarter m_tsUnk28;   // +0x28 started (StartMove)
        CTriggerStarter m_tsUnk30;   // +0x30 the movement's end (Update)
        IKSerializable* m_pUnk38;    // +0x38 reference: a CKSoundDictionaryID (0 the start, 1 the loop, 2 the end sound)
        uint8_t m_unk3C;             // +0x3c running (SetDefaultState copies m_unk8; Update: the updater's running byte)
        uint8_t m_pad3D[3];
        float m_unk40;               // +0x40 the progress (the updater's time over the duration; SetDefaultState: m_unkC)
    };

    // 0x005c6508 CKHkMovingObject_Create (inlined constructor, = 0x005c5938 CKHkMovingObject_Construct):
    // the IKLife/IKHook defaults, then the step vector's capacity 1, length 0, block 0.
    CKHkMovingObject() {
        m_vpSteps.m_ui32NbElt = 1;
        m_vpSteps.m_ui32NbUsedElt = 0;
        m_vpSteps.m_pBlock = nullptr;
    }
    // 0x005c6df0 CKHkMovingObject_Destructor: the step block (+0x2c) freed when there still is one (Destroy frees and
    // clears it), then the bases' vtables.
    ~CKHkMovingObject() override {
        if (m_vpSteps.m_pBlock != nullptr) Mem_FreeAligned16(m_vpSteps.m_pBlock);  // TocBridge_Mem_FreeAligned16
    }
    // vt+0x10 0x005c5ef8 CKHkMovingObject_Destroy: the matrix destroyed, the steps deleted (last first), their block freed.
    void Destroy() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c6e58 CKHkMovingObject_Load
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x005c6360 CKHkMovingObject_SetDefaultState
    // 0x005c6278 CKHkMovingObject_RestoreCheckpointState_maybe (the SetGameState override; see
    // CKHkDetectorGroup::RestoreCheckpointState): state 0 takes the first saved values (m_unk28, step +8/+0xc),
    // any other the second (m_unk29, step +0x10/+0x14). Returns 1.
    int32_t RestoreCheckpointState(uint32_t stateIdForLeft);

    // vt+0x1c 0x005c7758 CKHkMovingObject_MessageProc (the jump table TOC2 -0x5f84; the step index in the action's
    // parameter): 0x496 start a step (unless running), 0x497 stop it, 0x498 pause, 0x499 resume, 0x49a jump to its
    // end, 0x49b hide the node with its collision off, 0x49c show it with the collision on. 0 = handled.
    int32_t MessageProc(uint16_t message, void* data) override;
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x005c6c60: the steps' value accessors, the runtime reset
    // vt+0x40 0x005c6190 CKHkMovingObject_vf40 (GetInfo): 300 the step `arg` at its start, 0x12d at its end, 0x12e
    // between them, 0x12f the node shown (bytes).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    void Restart() override;  // vt+0x54 0x005c7740 CKHkMovingObject_ReinitRuntime: RestoreState unless in an unloaded sector
    void Start() override {}   // vt+0x50 0x5c59a0 (empty)
    void Stop() override {}    // vt+0x68 0x5c59a8 (empty)
    void Pause() override {}   // vt+0x70 0x5c59b0 (empty)
    void Resume() override {}  // vt+0x78 0x5c59b8 (empty)
    // vt+0x7c 0x005c6688 CKHkMovingObject_Update: the node back at its matrix, then every step moved by its updater
    // (time) or placed by its value object, its sounds (the start sound when leaving the start, the loop sound while
    // moving), its progress and running byte kept, and at the end its end starter, the end sound and the loop
    // stopped.
    void Update(IKTime* frameClock) override;
    void VfA0() override;  // vt+0xa0 0x005c7738 (SectorNowValid): RestoreState
    void VfA4() override;  // vt+0xa4 0x005c5ff0 CKHkMovingObject_OnDeactivate (SectorNowInvalid)

    // 0x005c7570 CKHkMovingObject_RestoreState_maybe: the node at its matrix, shown and its collision as +0x2a, then
    // every running step started again at its progress and the others stopped.
    void RestoreState();
    void StartMove(uint32_t step);                     // 0x005c5c38 CKHkMovingObject_StartMove_maybe
    void StopMover(uint32_t step);                     // 0x005c5b78 CKHkMovingObject_StopMover_maybe
    void SetMoveProgress(float progress, uint32_t step);  // 0x005c6588 CKHkMovingObject_SetMoveProgress_maybe

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
