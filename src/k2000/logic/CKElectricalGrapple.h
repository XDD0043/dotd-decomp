// CKElectricalGrapple.h - the electric grab (key 0xa00c, vtable 0xb237e8, size 0x158). Original unit:
// CKElectricalGrapple.cpp (0x395018-0x396748). Derives from CKGrabElement (its constructor and Load run first).
// No XXL2 class of this name. The grab draws a lightning bolt (the level's CKLightningBoltFxData, +0x140) from the
// user's hot spot 2 to the grabbed target's hot spot (host vt+0xe4) or aim point, with the element damage on its
// sphere; LVL010's kind-0 enemies hold one at +0x784 (their fourth attack, CKS08EnemyAbilityHost).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKGrabElement.h"

class CKLightningBoltNodeFx;
class CKSound;

class CKElectricalGrapple : public CKGrabElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x280)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bfc08
        return key == 0xa00c || key == 0xc || key == 0x9fcc || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKElectricalGrapple)

    CKElectricalGrapple() {}  // 0x003953f8 CKElectricalGrapple_Construct: CKGrabElement's constructor, then the vtable only
    ~CKElectricalGrapple() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00395c90 CKElectricalGrapple_Load
    // vt+0x30 0x003952d8 CKElectricalGrapple_PostLoad: CKGrabElement's (ResetRuntime, vt+0x6c).

    uint8_t GetAbilityId() override { return 7; }  // vt+0x50 0x00395068
    // vt+0x58 0x003952a8 CKElectricalGrapple_Start: the loop sound cleared, CKGrabElement's Start.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x64 0x00395230 CKElectricalGrapple_End: the loop sound stopped, CKGrabElement's End.
    void End(int32_t forced) override;
    // vt+0x6c 0x00395070 CKElectricalGrapple_ResetRuntime: CKGrabElement's, then the hot spot 2, no bolt, no sound.
    void ResetRuntime() override;
    // vt+0x70 0x00396120 CKElectricalGrapple_SetFxActive: on: the level's bolt from the user's hot spot 2 to the
    // grabbed hot spot (else the target's aim point), the damage set up (vt+0x8c) and put on the bolt's sphere, the
    // bolt started; the start sound and the loop sound (+0x154). Off: the bolt released, the stop sound and the loop
    // sound stopped.
    void SetFxActive(int32_t on) override;
    // vt+0x74 0x00395790 CKElectricalGrapple_UpdateGrab_maybe (the miss): a bolt toward 10 units in front of the user's
    // ground point that lives 0.2 s, not kept; the start sound.
    void UpdateGrab() override;
    // vt+0x78 0x009bfc70 CKElectricalGrapple_StartEmitterFx: CKGrabElement's.
    // vt+0x7c 0x00395630 CKElectricalGrapple_GrabTarget_maybe: CKGrabElement's.
    // vt+0x80 0x003955b0 CKElectricalGrapple_Slot80_maybe: the hold goes on while the host's GrabEnemy (vt+0xec, grab
    // 1, mode 1, no damage or target) answers.
    uint8_t Vf80(float dt) override;
    // vt+0x84 0x00395678 CKElectricalGrapple_Slot84_maybe: the bolt data's target the grabbed hot spot; without one the
    // bolt aims at the target's aim point (host vt+0xdc).
    void Vf84(float dt) override;
    uint8_t Vf94() override { return 1; }  // vt+0x94 0x009bfc68: the grab follows the target

    // 0x003950b8 CKElectricalGrapple_GetSoundForEvent_maybe: event 0 the start sound (+0x150 index 0), 4 the stop
    // sound (4), 1 the loop sound of the level (level 2: 3, level 1: 2, when present with a sample; else 1).
    CKSound* GetSoundForEvent(int32_t event);

    IKSerializable* m_apLightningBoltFxData[3];      // +0x140 references (live: CKLightningBoltFxData), one per level
    CKLightningBoltNodeFx* m_pBolt;   // +0x14c runtime: the bolt while the grab holds (SetFxActive)
    IKSerializable* m_pSoundDico;         // +0x150 reference (live: CKSoundDictionaryID)
    CKSound* m_pLoopSound;            // +0x154 runtime: the playing loop sound
};
DOTD_ASSERT_SIZE(CKElectricalGrapple, 0x158);
DOTD_ASSERT_OFFSET(CKElectricalGrapple, m_apLightningBoltFxData, 0x140);
DOTD_ASSERT_OFFSET(CKElectricalGrapple, m_pBolt, 0x14c);
DOTD_ASSERT_OFFSET(CKElectricalGrapple, m_pSoundDico, 0x150);
DOTD_ASSERT_OFFSET(CKElectricalGrapple, m_pLoopSound, 0x154);
