// IKCinematicBloc.h - the cinematic blocs (key 0x84c, abstract; XXL2:
// K/KServices/KServiceCinematic/CinematicElement/CinematicBloc/IKCinematicBloc.h). PS3 size 0x38.
// Original units: IKCinematicBloc.cpp (0x18e8d8-0x18edd8, the constructor) and CKCinematicBloc.cpp
// (0x18edd8-0x18fc20, BasicLoadCinematicElement, the Ghidra CKCinematicBloc_Load).
//
// DotD changed XXL2's m_i32SeqIndex / m_i32SeqBlocIndex into one reference (+0x20) and keeps
// m_fBlendingValue (+0x24, 0.1 or 0.2 in the files). +0x28 and the vector at +0x2c are DotD's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicElement.h"

class IKFile;

class IKCinematicBloc : public IKCinematicElement {
public:
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x84c || key == 0x808 || key == 0xc; }  // 0x9aa508
    IKCinematicBloc();  // 0x0018eae8 IKCinematicBloc_Construct
    ~IKCinematicBloc() override {}
    // vt+0x24 0x0018e8d8 IKCinematicBloc_LevelReset (Ghidra's name; it is the blocs' RecursiveRegistration base, every
    // bloc's RecursiveRegistration calls it first): registered with the saving manager (vt+0x24, no owner) unless the
    // type is 4..7.
    void RecursiveRegistration(int32_t type) override;

    // 0x0018edd8 CKCinematicBloc_Load (XXL2 IKCinematicBloc::BasicLoadCinematicElement): the element
    // part of every bloc's data; each bloc's Load calls it first.
    int32_t BasicLoadCinematicElement(IKFile* file, int32_t type);

    // The blocs' actor queries (vtable +0x80..+0x8c, after the element slots; the doors have none). The
    // defaults are the shared stubs 0x9a9230 / 0x9a9238 / 0x9a9240 (0) and 0x9a9248 (-1). CKPlayAnim-,
    // CKPathFinding- and CKFlaggedPathCinematicBloc answer for their actor (the C2.3 step 3 blocs).
    virtual uint8_t UsesActor() { return 0; }            // vt+0x80
    virtual uint8_t IsExclusiveOnActor() { return 0; }   // vt+0x84 InterruptConflictingBlocs asks it
    virtual uint8_t GetAnimCount() { return 0; }         // vt+0x88
    virtual int32_t GetAnimIndex() { return -1; }        // vt+0x8c

    // 0x0018e9e0 IKCinematicBloc_CheckSekensStop: 1 to go on, 0 when the bloc was stopped (vt+0x6c) because the
    // sekens it is tied to ended.
    uint8_t CheckSekensStop();
    // The bloc's Complete body, inlined in every bloc (e.g. 0x188d38 CKPlayVideoCinematicBloc_Complete): when it runs
    // (flag bit 0) it leaves the scene's running list, bit 0 is cleared and bit 2 (completed) set, the sekens byte
    // +0x28 cleared; with bit 4 its outputs are activated (CKSrvCinematic_ActivateNode) and the elements to interrupt
    // stopped (vt+0x6c).
    void CompleteBloc();
    // 0x0018ebb8 IKCinematicBloc_InterruptConflictingBlocs: 1 once the other running blocs on the same actor
    // were stopped (or when this bloc does not need it), 0 while a stop is already running.
    uint8_t InterruptConflictingBlocs();
    // 0x0018e940 IKCinematicBloc_IsOutputOf_maybe: whether this element is an output of `element`.
    uint8_t IsOutputOf(IKCinematicElement* element);
    // The beginning every bloc's Start inlines (e.g. 0x0018e400 CKTeleportCinematicBloc_Start before its own part): the
    // actor's scale kept in +0x2c (the lengths of its matrix rows, or 1 without an actor), the bloc completed (vt+0x64)
    // when it needs an actor that is not locked, then either started (it joins the scene's running list, flags: running,
    // bit 1 kept, the sekens byte cleared) or, when it plays once and has completed or the exclusive actor is busy,
    // completed.
    void StartCommon();

    // The bloc's actor animation (Ghidra CKCinematicBloc_*; the hook's node answers GetBlendSlot, vt+0xbc): through the blend
    // slot when the node has one, else through the node. `handle` is the dictionary word (CAnimationDictionary entry `index`
    // of the actor's CKCinematicSceneData).
    // 0x0018f450 AdvanceActorAnim: the animation time and the crossfade advanced by `dt`.
    void AdvanceActorAnim(double dt);
    // 0x0018f540 GetActorAnimTime_maybe / 0x0018f5f0 GetActorCurrentAnim_maybe: the evaluated time / animation.
    double GetActorAnimTime();
    uint32_t GetActorCurrentAnim();
    // 0x0018f6a0 IsActorAnimEndReached: the animation would reach its end with `dt` more.
    bool IsActorAnimEndReached(double dt);
    // 0x0018f7d0 PlayActorAnim: animation `index` set at `start` seconds, no blend.
    void PlayActorAnim(double start, int32_t index);
    // 0x0018f900 CrossfadeActorAnim: animation `index` blended in over `blend` seconds, from `start`; mode 1 or 2.
    void CrossfadeActorAnim(double blend, double start, int32_t index, uint32_t mode);

    IKSerializable* m_pSekensElement;  // +0x20 a CKSekensElement (marker) reference (DotD; XXL2 has the two sequence indices here)
    float m_fBlendingValue;   // +0x24 XXL2 name, same place in the load order (read as a swapped word)
    uint8_t m_bSekensReached;  // +0x28 CheckSekensStop sets it once its sekens element's sekens was current (not set by
                               // the constructor nor the Load)
    uint8_t m_pad29[3];
    float m_unk2c[3];         // +0x2c the constructor copies the global vector 0x00c50d58 (1, 1, 1)
};
DOTD_ASSERT_SIZE(IKCinematicBloc, 0x38);
DOTD_ASSERT_OFFSET(IKCinematicBloc, m_pSekensElement, 0x20);
DOTD_ASSERT_OFFSET(IKCinematicBloc, m_fBlendingValue, 0x24);
DOTD_ASSERT_OFFSET(IKCinematicBloc, m_unk2c, 0x2c);
