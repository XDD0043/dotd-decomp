// CKHkDetectorGroup.h - a hook holding three lists of detection boxes (key 0x2d82, vtable 0xb2f768,
// size 0x54; library-TOC code). Original unit: k2000/ai/CKHkDetectorGroup.cpp. No XXL2 class.
//
// The constructor (0x005bc430 CKHkDetectorGroup_Construct) stores an intermediate vtable 0xb2f840
// between IKHook's and the class's (an unregistered base_maybe that adds no field); the Load calls
// CKHook_Load directly, so the class derives from IKHook here.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkDetectorGroup : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb6)
    DOTD_DECLARE_FACTORIES(CKHkDetectorGroup)

    // One detection box (0x28 bytes on the PS3, Mem_AllocAligned16 blocks; no constructor).
    struct Detector {
        // +0x00 read as one 0x18-byte block, each word swapped: the maximum corner (x, y, z) then the minimum corner
        // (TestDetector: min <= p <= max), a CBBox's layout.
        float m_aBox[6];
        // +0x18 four single-byte reads (TestDetector, read as signed bytes except [1]): [0] the shape (0 the box, 1 a
        // vertical cylinder, 2 a sphere, both of half the x extent; other: never inside), [1] the hero count threshold,
        // [2] which heroes count (0 a player-controlled hero inside, 1 none inside, 3 the focused hero inside, other:
        // always), [3] how the count of heroes inside compares with [1] (0 at least, 1 exactly, 2 at most, other: never).
        uint8_t m_unk18[4];
        uint32_t m_unk1C;            // +0x1c the mask of the hero indices tested (bit i: the group's hero i)
        // +0x20 reference: the object whose position is tested when no point is given (its +4 is read as an RwFrame and
        // the frame's LTM position +0x80: a scene node, CSGMovable's layout _maybe).
        IKSerializable* m_pUnk20;
        uint8_t m_unk24;             // +0x24 not loaded; SetDefaultState sets the byte to 1 (armed: 0 never detects)
        uint8_t m_pad25[3];
    };

    // 0x005bd050 CKHkDetectorGroup_Create (inlined constructor): only the IKLife/IKHook defaults.
    CKHkDetectorGroup() {}
    // 0x005bd480 CKHkDetectorGroup_Destructor / 0x005bdf68 CKHkDetectorGroup_DeletingDestructor: the vtables only.
    ~CKHkDetectorGroup() override {}

    // vt+0x10 0x005bcc48 CKHkDetectorGroup_Destroy (Ghidra; row name ClearReferences): the three detector lists freed
    // (Mem_FreeAligned16) and cleared.
    void Destroy() override;
    // vt+0x24 0x005bd430 (Ghidra CKHkDetectorGroup_RecursiveRegistration; row name LevelReset): IKHook's.
    void RecursiveRegistration(int32_t type) override { IKHook::RecursiveRegistration(type); }
    void Stop() override {}    // vt+0x68 0x005bcc38 CKHkDetectorGroup_vf68 (empty)
    void Pause() override {}   // vt+0x70 0x005bcc40 CKHkDetectorGroup_vf70 (empty)
    void Resume() override {}  // vt+0x78 0x005bcc30 CKHkDetectorGroup_vf78 (empty)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005bd0b8 CKHkDetectorGroup_Load
    // vt+0x30 0x005bc628 CKHkDetectorGroup_PostLoad: IKLife's, both trigger starters', and for a level (type 0) the
    // run-time word +0x4c cleared. Returns 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x50 0x005bccd0 CKHkDetectorGroup_vf50 (Start): the hold timer +0x50 cleared.
    void Start() override;
    // vt+0x54 0x005bcce0 CKHkDetectorGroup_vf54 (Restart): +0x4c bit 0 (holds) and the hold timer cleared.
    void Restart() override;
    // vt+0x7c 0x005bdc60 CKHkDetectorGroup_Update: while enabled (+0x4c bit 1) and not frozen (+0x44), the lists
    // tested at the object positions (no point): it holds when no detector of list 2 does, lists 0 and 1 are not both
    // empty, every detector of list 0 does and (when list 1 has any) one of list 1 does. A hold delay (+0x48 above 0)
    // must run out on the timer +0x50 (reset while not holding) first. Holding: when bit 0 is clear, the enter
    // starter (+0x34) fires and bit 0 is set; otherwise when bit 0 is set, the leave starter (+0x3c) fires and it is
    // cleared.
    void Update(IKTime* clock) override;
    // vt+0xa0 0x005bcd00 CKHkDetectorGroup_OnActivate (SectorNowValid): +0x4c bit 0 cleared. (vt+0xa4 0x5bcd10 is empty.)
    void VfA0() override;
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x005bcb48 CKHkDetectorGroup_SetDefaultState
    // 0x005bca38 CKHkDetectorGroup_RestoreCheckpointState_maybe: the SetGameState override (vt+0x3c; its
    // argument's second word, `stateIdForLeft`, selects which saved enable flag applies). Not yet wired to the
    // virtual: IKSerializable::SetGameState takes no argument until the game manager's SApplyGameState lands.
    int32_t RestoreCheckpointState(uint32_t stateIdForLeft);
    // 0x005bcd18 CKHkDetectorGroup_LoadDetector_maybe (the Load passes type 0; unused).
    int32_t LoadDetector(IKFile* file, int32_t type, Detector* detector);
    // 0x005bd4a0 CKHkDetectorGroup_TestDetector_maybe: 1 when the armed detector holds `point`; without a point, its
    // object's position (+0x20), else the heroes of the group (mask +0x1c) counted and selected by the bytes +0x19..+0x1b.
    int32_t TestDetector(const Detector* detector, const float* point) const;
    // 0x005bda08 CKHkDetectorGroup_EvaluateConditions_maybe: with `requireEnabled`, 0 unless bit 1 of +0x4c (enabled) is
    // set; then no detector of list 2 may hold the point, lists 0 and 1 may not both be empty, every detector of list 0
    // must hold it and (when list 1 has any) one of list 1.
    int32_t EvaluateConditions(const float* point, int32_t requireEnabled) const;
    // 0x005bdc38 CKHkDetectorGroup_IsTriggered_maybe: EvaluateConditions(point, 1) as a byte. The vtable 0xb2f768 holds
    // it at vt+0xc4 (vt+0xc0 0x9ccff0 returns +0x4c bit 0, vt+0xc8 0x9cd000 stores its byte argument at +0x44); IKHook
    // declares no slot past vt+0xbc yet, so it is a plain member here. CKCameraConstraint::ContainsPoint calls it.
    uint8_t IsTriggered(const float* point) const;
    // vt+0x1c 0x005bc840 CKHkDetectorGroup_MessageProc (Ghidra HandleMessage): 0x496 enables the group (+0x4c bit 1), 0x497
    // turns bits 0 and 1 off; 0x498 / 0x499 arm / disarm the detector of index *data (the three lists one after the
    // other; +0x24). 0 for those four, 1 for the others.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x40 0x005bc7b0 CKHkDetectorGroup_vf40 (GetInfo): the trigger values 4 (0x9cd008 GetTriggerProp4: vt+0xc0, +0x4c
    // bit 0) and 5 (0x9cd050 GetTriggerProp5: +0x4c bit 1, enabled), bytes.
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;

    uint8_t m_ui8NbDetectors[3];     // +0x20 the sizes of the three lists below
    uint8_t m_pad23;
    Detector* m_apDetectors[3];      // +0x24 Mem_AllocAligned16(count * 0x28) each (Load)
    uint8_t m_unk30;                 // +0x30
    uint8_t m_unk31;                 // +0x31
    uint8_t m_pad32[2];
    CTriggerStarter m_tsUnk34;       // +0x34
    CTriggerStarter m_tsUnk3C;       // +0x3c
    uint8_t m_unk44;                 // +0x44
    uint8_t m_pad45[3];
    float m_unk48;                   // +0x48 the hold delay (Update: the lists must hold this long; 0 or less: at once)
    // +0x4c runtime (not set by Create or Load; PostLoad clears it for a level): bit 0 holds (Update), bit 1 enabled.
    uint32_t m_unk4C[1];
    float m_fHoldTime;               // +0x50 the time the lists have held (Update; Start / Restart clear it)
};
DOTD_ASSERT_SIZE(CKHkDetectorGroup, 0x54);
DOTD_ASSERT_OFFSET(CKHkDetectorGroup, m_ui8NbDetectors, 0x20);
DOTD_ASSERT_OFFSET(CKHkDetectorGroup, m_apDetectors, 0x24);
DOTD_ASSERT_OFFSET(CKHkDetectorGroup, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkDetectorGroup, m_unk31, 0x31);
DOTD_ASSERT_OFFSET(CKHkDetectorGroup, m_tsUnk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkDetectorGroup, m_tsUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkDetectorGroup, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkDetectorGroup, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkDetectorGroup, m_fHoldTime, 0x50);
DOTD_ASSERT_SIZE(CKHkDetectorGroup::Detector, 0x28);
DOTD_ASSERT_OFFSET(CKHkDetectorGroup::Detector, m_unk1C, 0x1c);
DOTD_ASSERT_OFFSET(CKHkDetectorGroup::Detector, m_pUnk20, 0x20);
