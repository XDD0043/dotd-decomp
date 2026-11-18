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

class IKBoundingVolume;
class IKTime;
struct CVector3;

class CKHkCrumblyZoneMultiState : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd3)
    // 0x00411100 Delete / 0x00412368 CreateArray / 0x00411d58 DeleteArray (the registry factories; no object of this
    // exact class occurs in the files).
    DOTD_DECLARE_FACTORIES(CKHkCrumblyZoneMultiState)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c25c0
        return key == 0x34c2 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }

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
    // vt+0x10 0x00411f88 CKHkCrumblyZoneMultiState_Destroy: the actor base's, both reference vectors freed.
    void Destroy() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00412f98 CKHkCrumblyZoneMultiState_Load
    // vt+0x30 0x00411c20 CKHkCrumblyZoneMultiState_PostLoad (CKHkS08CrumblyZoneMultiState_PostLoad 0x4152c0 calls it):
    // the actor base's; for the level type +0x28 = 0 and the two trigger lists' PostLoad (return 1).
    int32_t PostLoad(int32_t type) override {
        CKHkActorBase::PostLoad(type);
        if (type == K_LEVEL_PLATEFORMS) m_unk28 = 0;
        return 1;
    }
    // vt+0x38 0x00411150 CKHkCrumblyZoneMultiState_SetDefaultState: the current state (+0x28) = the default one (+0x20).
    void SetDefaultState(int32_t /*flag*/) override { m_unk28 = m_unk20; }
    // vt+0x3c 0x00411160 CKHkCrumblyZoneMultiState_SetGameState: game state 0 picks +0x20, any other +0x24 (the info id is
    // not tested); returns 1.
    int32_t SetGameState(const SApplyGameState* state) override {
        m_unk28 = state->m_ui32GameStateId == 0 ? m_unk20 : m_unk24;
        return 1;
    }
    void Start() override;  // vt+0x50 0x004122b8 CKHkCrumblyZoneMultiState_Start
    void Restart() override;  // vt+0x54 0x004128c8 CKHkCrumblyZoneMultiState_Restart
    // vt+0xa0 0x00412a78 CKHkCrumblyZoneMultiState_OnActivate: the actor base's, every state (last first) off and its
    // path-finding boxes freed, the current state (+0x28) set again (vt+0xf0, forced, silent), every piece (last first)
    // back to its loaded matrices.
    void VfA0() override;
    // vt+0xf0 0x004120a0 CKHkCrumblyZoneMultiState_SetState_maybe: state `state` (unforced and unchanged: nothing; else
    // the trigger starter +0x84 fired). The new state takes the current state's contact list, the current one goes off,
    // the meca group's +0x32 flag set (1, or 3 over 2), the new one on (`sound`: its sound, then the crumble / break FX
    // going forward / back); the current state = `state`, the states before it get +0x08 = 0, the others
    // +0x0c.
    virtual void SetState(uint32_t state, uint8_t force, uint8_t sound);
    // vt+0xf8 0x00413740 CKHkCrumblyZoneMultiState_PlayCrumbleFx_maybe / vt+0xfc 0x00412bd8 PlayBreakFx_maybe: the crumble
    // (+0x44's explosion at the node plus +0x50, along its at axis) / break (+0x48's at the node plus +0x5c) effect, the
    // current state's marked pieces reset to their loaded matrices, the quake (+0x74) started.
    virtual void PlayCrumbleFx();
    virtual void PlayBreakFx();
    // vt+0xf4 0x00411410 CKHkCrumblyZoneMultiState_GetHitDamage_maybe: a volume's damage (+0x1c) when it is a CKDamage
    // (0x96cc): its amount, times the frame time when continuous (+0x0c); else 0. `touched`: the contact is new.
    virtual float GetHitDamage(IKBoundingVolume* volume, uint8_t touched);
    // vt+0x100 0x00413c78 CKHkCrumblyZoneMultiState_PlayHitFxAt_maybe: +0x4c's explosion at `point`, the current state's
    // pieces with entry byte +0x01 reset, the quake +0x6c started.
    virtual void PlayHitFxAt(const CVector3* point);
    // vt+0x104 0x004114b8 CKHkCrumblyZoneMultiState_vf104 (empty; a hit that does not hurt).
    virtual void Vf104() {}
    // vt+0x7c 0x00411e78 CKHkCrumblyZoneMultiState_Update: the current state's update (UpdateState), the pieces' shakes
    // (UpdateShakes) and animations (AdvancePieceAnim), and while the meca group's +0x32 is above 1 the current state's
    // path-finding boxes blocked.
    void Update(IKTime* frameClock) override;
    // 0x00411598 CKHkCrumblyZoneMultiState_UpdateShakes_maybe: while the quake +0x6c / +0x74 runs, its outputs as a matrix
    // (ShakeSample_BuildMatrix about the identity) applied to the current state's pieces whose entry byte +0x01 / +0x02 is
    // set (the last first; CrumblyZonePiece_ApplyWorldMatrix).
    void UpdateShakes(IKTime* frameClock);
    // 0x00411250 CKHkCrumblyZoneMultiState_AdvanceToNextState_maybe / 0x00411338 GoToPreviousState: the current state's
    // next (+0x48) / previous (+0x44) one when it is a valid index, else the following / preceding state (the last / first
    // keeping itself), set with `sound` (vt+0xf0, not forced).
    void AdvanceToNextState(uint8_t sound);
    void GoToPreviousState(uint8_t sound);
    // vt+0x68 0x00411ac8 CKHkCrumblyZoneMultiState_Stop: CKHkActorBase_d82_maybe_Stop 0x3f6e50 (empty): IKHook's.
    void VfA4() override;  // vt+0xa4 0x004129c8 CKHkCrumblyZoneMultiState_OnDeactivate

    // 0x00412458 CKHkCrumblyZoneMultiState_MessageProc (vt+0x1c): the aim queries 0x400 / 0x402 and the state messages
    // 0x996..0x99d (CKHkCrumblyZoneMultiState.cpp).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x40 0x00411af0 CKHkCrumblyZoneMultiState_GetInfo: the trigger values 0x15e (in the state `arg`, 0x4114c0) and
    // 0x15f (the total health, 0x411570 -> 0x413fe8, a float). The actor base (KStub_Return1 0x3f7140) answers 1.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x108 0x00414040 CKHkCrumblyZoneMultiState_CurrentStateHasPieces_maybe: the current state's (+0x38[+0x28])
    // bounding component has volumes. (A plain member: the actor base declares no slot that far.)
    uint8_t CurrentStateHasPieces() const;

    // vt+0xd0 0x00412020 CKHkCrumblyZoneMultiState_SetVisible_maybe: the current state (+0x28) switched on or off with its
    // sound (CrumblyZoneState_SetEnabled), and the meca group's +0x32 (2 becomes 3, else 1).
    void SetVisible(int32_t visible) override;

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
