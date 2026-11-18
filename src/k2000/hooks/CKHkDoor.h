// CKHkDoor.h - a door mechanism (key 0x1942, vtable 0xb25d10, size 0x80). Original unit: CKHkDoor.cpp
// (0x416710-0x419a18). XXL2 has CKHkDoor (K/KMeca/Door, base IKHkMeca); DotD's derives from CKHkActorBase and
// its Load differs (an extra word before the detector count, other references). XXL2 names are used where
// the PS3 Load reads the same thing in the same place: the detector count and the two detector arrays
// allocated together, the 16-bit auto-action bits read just before the count, the two trigger starters.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class IKTime;

class CKHkDoor : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x65)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c2e10
        return key == 0x1942 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkDoor)
    // vt+0x40 0x00417638 CKHkDoor_GetInfo: the trigger values 0x9c (+0xc bit 10) and 0x9d (+0x24 at 0).
    int32_t GetInfo(IKInfo* info, int32_t request) override;

    CKHkDoor() {}  // 0x004174f0 CKHkDoor_Create: the CKHkActorBase defaults only
    ~CKHkDoor() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00419150 CKHkDoor_Load
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x00416998 CKHkDoor_SetDefaultState
    void Start() override;                        // vt+0x50 0x00417358 CKHkDoor_Start
    // vt+0xc8 0x004179a8 CKHkDoor_ApplyStatePreset_maybe: bits 6/7 (state 0) or 8/9 (state 1) of the flags
    // are the preset's "initially open" and "applies" bits (XXL2's two door states).
    void ApplyStatePreset(int32_t state) override;
    // vt+0xa0 0x00418c60 CKHkDoor_OnActivate: the slide axis from the frame's modelling rows (flag bits 3-5), the open
    // or closed state, the closed position kept (+0x28), the second leaf moved under the first one's parent at its
    // matrix, the leaves placed and shown, the detector states reset.
    void VfA0() override;
    void Restart() override;  // vt+0x54 0x00419738 CKHkDoor_Restart
    // ---- C2.8 meca-hero ----
    void Update(IKTime* frameClock) override;              // vt+0x7c 0x00417b30 CKHkDoor_Update
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x00418810 CKHkDoor_MessageProc
    // vt+0xb4 0x00417548 CKHkDoor_AttachSounds: sounds 0 and 1 of +0x68 (when there) attached to the node (+0x1c).
    void KGLObjectAttached(IKSerializable* leaf) override;
    void VfA4() override;                                  // vt+0xa4 0x00417818 CKHkDoor_OnDeactivate
    void Destroy() override;                               // vt+0x10 0x004175f0 CKHkDoor_Destroy
    // 0x00416af8 CKHkDoor_UpdateStateFromLinkedObjects_maybe: the detectors' states and the automatic open / close.
    void UpdateStateFromLinkedObjects();

    // The open (bit 10) or closed state's opening (+0x24), path-finding transitions (+0x58 / +0x5c: closed, bit 2
    // of their flags, while open) and collision mesh (+0x54: off while open); flag bit 17 set, bit 13 cleared (the
    // common start of CKHkDoor_OnActivate and CKHkDoor_Restart).
    void ApplyOpenState();
    // The two leaves at the closed position plus / minus the opening along the slide axis (fmadds), their frames'
    // identity flags cleared and marked dirty.
    void PlaceLeaves();
    // Flag bits 15-16 set and 14 cleared, every detector's 3-bit state 6, bit 12 set (as ApplyStatePreset's end).
    void ResetDetectorStates();

    uint32_t m_unk20;                      // +0x20 runtime: the detectors' 3-bit states
    float m_fOpening;                      // +0x24 runtime: 0 closed, +0x44 open (GetInfo 0x9d: closed)
    CVector3 m_vClosedPosition;            // +0x28 runtime: OnActivate keeps the first leaf's modelling position
    CVector3 m_vSlideAxis;                 // +0x34 runtime: OnActivate takes a modelling row (flag bits 3-5)
    uint8_t m_ui8NbOfDectector;            // +0x40 XXL2 m_ui8NbOfDectector (sic)
    uint8_t m_pad41;
    uint16_t m_baAutoAction;               // +0x42 XXL2 CBitArray16 m_baAutoAction
    float m_unk44;                         // +0x44 _maybe XXL2's distance/speed floats (DotD reads three)
    float m_unk48;                         // +0x48
    float m_unk4C;                         // +0x4c
    IKSerializable* m_unk50;               // +0x50
    IKSerializable* m_unk54;               // +0x54
    IKSerializable* m_unk58;               // +0x58
    IKSerializable* m_unk5C;               // +0x5c
    IKSerializable** m_apFrontDetector;    // +0x60 XXL2 CKDetectorBase** m_apFrontDetector
    IKSerializable** m_apBackDetector;     // +0x64 XXL2 CKDetectorBase** m_apBackDetector
    IKSerializable* m_unk68;               // +0x68
    IKSerializable* m_unk6C;               // +0x6c
    CTriggerStarter m_tsOpenStarter;       // +0x70 XXL2 m_tsOpenStarter_maybe (the first of the two)
    CTriggerStarter m_tsCloseStarter;      // +0x78 XXL2 m_tsCloseStarter_maybe
};
DOTD_ASSERT_SIZE(CKHkDoor, 0x80);
DOTD_ASSERT_OFFSET(CKHkDoor, m_fOpening, 0x24);
DOTD_ASSERT_OFFSET(CKHkDoor, m_vClosedPosition, 0x28);
DOTD_ASSERT_OFFSET(CKHkDoor, m_vSlideAxis, 0x34);
DOTD_ASSERT_OFFSET(CKHkDoor, m_ui8NbOfDectector, 0x40);
DOTD_ASSERT_OFFSET(CKHkDoor, m_baAutoAction, 0x42);
DOTD_ASSERT_OFFSET(CKHkDoor, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkDoor, m_unk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkDoor, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkDoor, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkDoor, m_apFrontDetector, 0x60);
DOTD_ASSERT_OFFSET(CKHkDoor, m_apBackDetector, 0x64);
DOTD_ASSERT_OFFSET(CKHkDoor, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkDoor, m_unk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkDoor, m_tsOpenStarter, 0x70);
DOTD_ASSERT_OFFSET(CKHkDoor, m_tsCloseStarter, 0x78);
