// CKHkActorBase.h - the unregistered base of most Spyro2008 and k2000 hooks (key 0xd82, vtable 0xb24cb0,
// size 0x20). Original unit: CKHkActorBase.cpp (0x3f6dc0-0x3f7430). No XXL2 class of this key. It adds no
// field to IKHook: its constructor 0x3f6dc0 sets the IKLife/IKHook parts only.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/CMatrix34.h"

// The data of message 0x400 (CKHkS08Hero_GetAimPointOnHook 0x2fd7c0 sends it to a hook it aims at): in the index of a
// hot spot to aim at; out the point (seeded with the hook node's LTM position) or a hot spot (+0x10, taking precedence).
// The hero is the sender. The words are PS3 ones (+0x14 bytes there).
struct SAimPointQuery {
    uint8_t m_ui8Index;          // +0x00
    CVector3 m_point;            // +0x04
    IKSerializable* m_pHotSpot;  // +0x10
    IKSerializable* m_pHero;     // +0x14
};

class CKHkActorBase : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x36)

    // vt+0x08 0x009c0b70 CKHkActorBase_d82_maybe_IsKindOfClass: 0xd82, then IKHook's.
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xd82 || IKHook::IsKindOfClass(key); }

    CKHkActorBase() {}  // 0x003f6dc0 CKHkActorBase_d82_maybe_Construct (the IKLife/IKHook defaults)
    ~CKHkActorBase() override {}
    // vt+0x10 0x003f6e08 CKHkActorBase_d82_maybe_ClearReferences (the actors' Destroy): vt+0xc0.
    void Destroy() override { VfC0(); }
    // vt+0xc0 0x9c0bc8 KStub_Nop_9c0bc8 (empty in every LVL010 actor's vtable: crumbly zones, save points, ...).
    virtual void VfC0() {}
    // vt+0xc4 0x003f6f10 KBaseD82_vfC4: a CNode's geometries take the colour white (value 0) or red (0xff0000ff) and
    // the "colour not opaque" bit, then a branch's children the same (recursively, through vt+0xc4). No caller of the
    // actors' slot is known (a debug highlight _maybe). Name ours.
    virtual void HighlightNode(float value, IKSerializable* node);

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003f6e98 CKHkActorBase_d82_maybe_Load
    // vt+0x30 0x003f6e70 CKHkActorBase_d82_maybe_PostLoad: IKLife_PostLoad, then 1.
    int32_t PostLoad(int32_t type) override {
        PostLoadLife(type);
        return 1;
    }
    void SetDefaultState(int32_t /*flag*/) override {}  // vt+0x38 0x3f72a0 KStub_Nop_3f72a0 (empty)
    // vt+0x3c 0x003f72a8 KBaseD82_SetGameState: a game module's state (info 1) applied as the preset vt+0xc8 (1 for game
    // state 1, else 0); 0 for any other info. The slot of 44 actor classes (CKHkCrumblyZone*, the bridges, CKHkRollingBarrel
    // and CKHkCounterWithDisplay have their own).
    int32_t SetGameState(const SApplyGameState* state) override;
    // vt+0x50 0x3f6e48 CKHkActorBase_d82_maybe_ResetRuntime (empty): the hooks' Start overrides call it first.
    void Start() override {}
    // vt+0xa0 0x003f7338 CKHkActorBase_d82_maybe_OnActivate: the actor joins the active actor list of the game manager's
    // meca group (+0xc, CKGrpMeca::AddActiveActor). Most hooks' own OnActivate call it first.
    void VfA0() override;
    // vt+0xa4 0x003f7370 CKHkActorBase_d82_maybe_OnDeactivate: the actor leaves it (CKGrpMeca::RemoveActiveActor).
    void VfA4() override;
    // vt+0xc8 0x9c0bd0 (empty here): the hooks with a state preset (CKHkDoor, CKHkPressionStone,
    // CKHkContextualMeca, ...) set their flag bits from the preset `state` (0 or 1).
    virtual void ApplyStatePreset(int32_t /*state*/) {}
    // vt+0xcc 0x9c0bd8 (empty here): CKHkHeroActivator and others switch themselves on or off.
    virtual void SetEnabled(int32_t /*enabled*/) {}
    // vt+0xd0 0x009c0c18 CKHkActorBase_d82_maybe_SetVisible: the node's (+0x1c) hidden bit (+0x10 bit 2) = !visible,
    // when there is a node.
    virtual void SetVisible(int32_t visible);
    // vt+0xd4 0x9c0be0 KStub_Nop_9c0be0 (empty here): CKHkScriptedNPC, CKHkContextualMeca (MoveTo), CKHkHazardousJet
    // (SetJetActive) and CKHkGolem override it; the actor messages 0x90c..0x90f pass (1, 0), (0, 0), (1, 1), (0, 1).
    virtual void VfD4(int32_t /*on*/, int32_t /*mode*/) {}
    // vt+0xd8 0x9c0be8 KStub_Return0_9c0be8 (0 here; CKHkActivator 0x9c0f20 answers 1, CKHkRollingBarrel 0x9c34c0 0):
    // CKProjectileTypeTargetLock_IsDead 0x596828 drops a lock on an actor that answers 0 (C2.8 port-last Z4: declared
    // for it; the meaning is not known).
    virtual uint8_t VfD8() { return 0; }
    // vt+0xec 0x9c0c10 KStub_Return0_9c0c10 (null here; vt+0xd8..+0xe8 are empty stubs too): CKHkS08TransportableWeight
    // 0x4b4bf0 answers the ground it rests on; the pression stones compare it with theirs (FindPressingObject, bit 7).
    virtual IKSerializable* VfEC() { return nullptr; }
    // vt+0x1c 0x003f7148 CKHkActorBase_d82_maybe_MessageProc: the actors' scripted messages (the jump table 0x003f7184 on
    // the message's low 16 bits less 0x908): 0x908 / 0x909 vt+0xcc (1 / 0), 0x90a / 0x90b vt+0xd0 (1 / 0), 0x90c..0x90f
    // vt+0xd4; 0 when handled, else 1 (KStub_Return1). The hooks' own MessageProcs call it first and merge the answers.
    int32_t MessageProc(uint16_t message, void* data) override;
};
DOTD_ASSERT_SIZE(CKHkActorBase, 0x20);
