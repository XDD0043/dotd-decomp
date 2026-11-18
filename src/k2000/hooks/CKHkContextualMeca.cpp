// CKHkContextualMeca.cpp - reconstructed original translation unit 0x459be0-0x460790 (GAME_TOC1, main_toc1), 47 functions, 42 live.
// Primary class: CKHkContextualMeca  key 0x2a82  category Hook  size 0x120  vtable 0xb27218
// Other owners: GetHeroModelNodeByDragonIndex (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x459be0  CKHkContextualMeca_Delete
//   [ ] 0x459c30  CKHkContextualMeca_ResetInteractionState_maybe  [dead]
//   [ ] 0x459c88  FUN_00459c88  [dead]
//   [x] 0x459c90  CKHkContextualMeca_GetProgressRatio_maybe
//   [ ] 0x459d20  RegisterCKHkContextualMecaClass
//   [ ] 0x459d98  _GLOBAL__I_459d98
//   [x] 0x459da8  CKHkContextualMeca_UpdateLoopSounds
//   [x] 0x459f98  CKHkContextualMeca_TriggerAtRestFx_maybe
//   [x] 0x45a288  CKHkContextualMeca_SetSlotActivatorsEnabled_maybe
//   [x] 0x45a3a0  CKHkContextualMeca_ReleaseHeroes
//   [ ] 0x45a550  CKHkContextualMeca_UpdateCollisionActive_maybe  [dead]
//   [x] 0x45a618  CKHkContextualMeca_IsHeroPullingAway_maybe
//   [x] 0x45a760  CKHkContextualMeca_PlaceSlotActivators_maybe
//   [x] 0x45a990  CKHkContextualMeca_OnDeactivate
//   [x] 0x45a9b8  CKHkContextualMeca_Resume  (empty / no effect: inherited)
//   [x] 0x45a9e0  CKHkContextualMeca_Pause  (empty / no effect: inherited)
//   [x] 0x45aa08  CKHkContextualMeca_Stop  (empty / no effect: inherited, CKHkActorBase_d82_maybe_Stop 0x3f6e50)
//   [x] 0x45aa30  CKHkContextualMeca_PostLoad
//   [ ] 0x45ab30  CKHkContextualMeca_Save
//   [x] 0x45ab58  CKHkContextualMeca_RecursiveRegistration  (CKHkActorBase's 0x3f6ee8, then 1: inherited)
//   [x] 0x45ab80  CKHkContextualMeca_Destroy
//   [x] 0x45ac38  CKHkContextualMeca_DeleteArray
//   [x] 0x45ace0  CKHkContextualMeca_Construct  [dead]
//   [x] 0x45ad18  CKHkContextualMeca_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x45ad48  CKHkContextualMeca_MessageProc
//   [ ] 0x45afd0  CKHkContextualMeca_Construct_2  [dead]
//   [x] 0x45b008  CKHkContextualMeca_ApplyStatePreset_maybe
//   [ ] 0x45b138  GetHeroModelNodeByDragonIndex_2  [dead: no pointer to its descriptor 0xbbe218, no call]
//   [x] 0x45b178  CKHkContextualMeca_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x45b1c0  CKHkContextualMeca_Destructor  (the C++ destructor (CKHkActorBase_d82_maybe_BaseDestructor 0x3f73f0))
//   [x] 0x45b1f0  CKHkContextualMeca_GetInfo
//   [x] 0x45b330  CKHkContextualMeca_SetDefaultState
//   [x] 0x45b420  CKHkContextualMeca_SnapHeroToSlot_maybe
//   [x] 0x45b850  CKHkContextualMeca_Create
//   [x] 0x45b8a8  CKHkContextualMeca_CreateArray
//   [x] 0x45b960  CKHkContextualMeca_Start
//   [x] 0x45b9f0  CKHkContextualMeca_Load
//   [x] 0x45c940  CKHkContextualMeca_TriggerInteractionFx_maybe
//   [x] 0x45cc48  CKHkContextualMeca_SpawnStepFx_maybe
//   [x] 0x45cfe0  CKHkContextualMeca_SetVisible
//   [x] 0x45d120  CKHkContextualMeca_Restart
//   [x] 0x45d3f0  CKHkContextualMeca_MoveTo
//   [x] 0x45d9d0  CKHkContextualMeca_SetEnabled
//   [x] 0x45dbd0  CKHkContextualMeca_UpdateHeroInteraction
//   [x] 0x45f420  CKHkContextualMeca_UpdateAtRest
//   [x] 0x4601d8  CKHkContextualMeca_Update
//   [x] 0x460450  CKHkContextualMeca_OnActivate
//
//   [ ] 0x9c3f58  CKHkContextualMeca_IsKindOfClass  [inline]
//   [ ] 0x9c3fb0  CKHkContextualMeca_GetClassType  [inline]
//   [ ] 0x9c3fb8  CKHkContextualMeca_GetClassID  [inline]
//   [ ] 0x9c3fc0  CKHkContextualMeca_GetIsBeingOperated  [inline]
//   [ ] 0x9c4020  CKHkContextualMeca_GetIsAtEnd  [inline]
//   [ ] 0x9c4048  CKHkContextualMeca_GetProgress  [inline]
#include "k2000/hooks/CKHkContextualMeca.h"
#include "k2000/core/IKInfo.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/components/CKGroundCpnt.h"
#include "k2000/components/CKImpulsionCpnt.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/hooks/CKHkHeroActivator.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/cameras/CKCameraConstraint.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Math.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/system/IKTime.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/animation/CKAnimationMarkContainer.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/services/CKSrvFx.h"
#include "Renderware/rtanim/RtAnim.h"
#include <cmath>

namespace {
// Mem_AllocAligned16(count * 4) then one contiguous reference read (vt+0x28) of count references.
IKSerializable** AllocAndReadRefs(IKFile* file, uint8_t count) {
    IKSerializable** refs =
        static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(count * sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, refs, count);
    return refs;
}
}  // namespace

// 0x0045aa30 CKHkContextualMeca_PostLoad: CKHkActorBase's part (0x3f6e70 = IKLife_PostLoad 0x19f68: level
// type only, bit 2 of the bit array), the six trigger lists' PostLoad (0x236330, returns 1) and the 0x30-byte
// records at +0x10c: OperatorNewArray(count * 0x30 + 4), the count as the cookie, +0x10c behind it. The
// records are not constructed.
int32_t CKHkContextualMeca::PostLoad(int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;  // IKLife_PostLoad returns 1 for it, and so does the rest
    m_bitArray = (m_bitArray & 0xfffffffbu) | 4u;
    m_unk9C.PostLoad(0);
    m_unkA4.PostLoad(0);
    m_unkAC.PostLoad(0);
    m_unkB4.PostLoad(0);
    m_unkBC.PostLoad(0);
    m_unkC4.PostLoad(0);
    const uint32_t count = m_unk5C;
    uint32_t* block = reinterpret_cast<uint32_t*>(new uint8_t[count * sizeof(SSlot) + sizeof(SSlot*)]);
    block[0] = count;
    m_aSlots = reinterpret_cast<SSlot*>(reinterpret_cast<uint8_t*>(block) + sizeof(SSlot*));
    return 1;
}

// 0x0045b9f0 CKHkContextualMeca_Load
int32_t CKHkContextualMeca::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_unk48);
    m_apUnk4C = AllocAndReadRefs(file, m_unk48);
    IKFile_ReadRef(file, &m_unk20);
    ReadU8(file, &m_unk50);
    ReadF32LE(file, &m_unk54);
    ReadF32LE(file, &m_unk58);
    IKFile_ReadRef(file, &m_unk2C);
    ReadF32LE(file, &m_unk30);
    ReadF32LE(file, &m_unk34);
    ReadU8(file, &m_unk40);
    IKFile_ReadRef(file, &m_unk24);
    IKFile_ReadRef(file, &m_unk28);
    ReadU8(file, &m_unk5C);
    ReadU8(file, &m_unk5E);
    if (m_unk5E == 0) {
        m_apUnk70 = nullptr;
        m_apUnk60 = nullptr;
        m_apUnk68 = nullptr;
        m_apUnk88 = nullptr;
    } else {
        m_apUnk60 = AllocAndReadRefs(file, m_unk5E);
        m_apUnk68 = AllocAndReadRefs(file, m_unk5E);
        m_apUnk88 = AllocAndReadRefs(file, m_unk5E);
        if ((m_bitArray & 0x1000u) == 0) {
            m_apUnk70 = nullptr;
        } else {
            m_apUnk70 = AllocAndReadRefs(file, m_unk5E);
        }
    }
    ReadU8(file, &m_unk5F);
    if (m_unk5F == 0) {
        m_apUnk74 = nullptr;
        m_apUnk64 = nullptr;
        m_apUnk6C = nullptr;
        m_apUnk8C = nullptr;
    } else {
        m_apUnk64 = AllocAndReadRefs(file, m_unk5F);
        m_apUnk6C = AllocAndReadRefs(file, m_unk5F);
        m_apUnk8C = AllocAndReadRefs(file, m_unk5F);
        if ((m_bitArray & 0x1000u) == 0) {
            m_apUnk74 = nullptr;
        } else {
            m_apUnk74 = AllocAndReadRefs(file, m_unk5F);
        }
    }
    ReadF32LE(file, &m_unk78);
    ReadF32LE(file, &m_unk7C);
    ReadF32LE(file, &m_unk90);
    ReadF32LE(file, &m_unk94);
    ReadF32LE(file, &m_unk80);
    ReadF32LE(file, &m_unk84);
    m_unk9C.Load(file, K_LEVEL_PLATEFORMS);
    m_unkA4.Load(file, K_LEVEL_PLATEFORMS);
    m_unkAC.Load(file, K_LEVEL_PLATEFORMS);
    m_unkB4.Load(file, K_LEVEL_PLATEFORMS);
    m_unkBC.Load(file, K_LEVEL_PLATEFORMS);
    m_unkC4.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_unk44);
    ReadF32LE(file, &m_unkCC);
    ReadU32LE(file, &m_unkD0);
    IKFile_ReadRef(file, &m_unkD8);
    IKFile_ReadRef(file, &m_unkE0);
    ReadF32LE(file, &m_unkE4);
    ReadF32LE(file, &m_unkE8);
    IKFile_ReadRef(file, &m_unkF0);
    ReadF32LE(file, &m_unk98);
    ReadF32LE(file, &m_unk38);
    ReadF32LE(file, &m_unk3C);
    IKFile_ReadRef(file, &m_unkDC);
    ReadF32LE(file, &m_unkD4);
    IKFile_ReadRef(file, &m_unkF4);
    return 1;
}

// 0x0045b960 CKHkContextualMeca_Start: the run-time words cleared, the float +0x110 set to -1.0f (TOC1 +0x5658),
// flags bits 19 and 20 cleared and bit 22 set.
void CKHkContextualMeca::Start() {
    CKHkActorBase::Start();
    m_afUnkF8[1] = 0.0f;
    m_afUnkF8[2] = 0.0f;
    m_afUnkF8[3] = 0.0f;
    m_afUnkF8[4] = 0.0f;
    m_afUnkF8[0] = 0.0f;
    m_bitArray = (m_bitArray & 0xffa7ffffu) | 0x400000u;
    m_fUnk11C = 0.0f;
    m_fUnk110 = -1.0f;
    m_unk5D = 0;
    m_unk118 = 0;
    m_unkEC = 0.0f;
}

// 0x0045b330 CKHkContextualMeca_SetDefaultState: state 0 always, state 1 only with bit 6. Bit 17 cleared,
// bit 18 = bit 5, bit 24 = bit 13, bit 21 = bit 9 (the original's rlwimi chain, checked bit by bit).
void CKHkContextualMeca::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    const uint32_t f = m_bitArray;
    if (flag != 0 && (f & 0x40) == 0) return;
    uint32_t r = f & ~(0x20000u | 0x40000u | 0x200000u | 0x1000000u);
    r |= (((f >> 5) & 1) << 18) | (((f >> 9) & 1) << 21) | (((f >> 13) & 1) << 24);
    m_bitArray = r;
}

// 0x0045b008 CKHkContextualMeca_ApplyStatePreset_maybe: with s = 0 (state 0) or 1: bit 17 cleared, bit 18 =
// bit 7+s, bit 21 = bit 10+s, bit 24 = bit 14+s.
void CKHkContextualMeca::ApplyStatePreset(int32_t state) {
    const uint32_t s = state == 0 ? 0u : 1u;
    const uint32_t f = m_bitArray;
    uint32_t r = f & ~(0x20000u | 0x40000u | 0x200000u | 0x1000000u);
    r |= (((f >> (7 + s)) & 1) << 18) | (((f >> (10 + s)) & 1) << 21) | (((f >> (14 + s)) & 1) << 24);
    m_bitArray = r;
}

namespace {
const float kZero = 0.0f;           // TOC1 +0x5688
const float kAlphaOpaque = 255.0f;  // TOC1 +0x56e0
const float kFadeOut = -350.0f;     // TOC1 +0x56f0: alpha per second
const float kFadeIn = 350.0f;       // TOC1 +0x56f4
const float kSlotTurn = 180.0f;     // TOC1 +0x5690: degrees

CAnimatedNode* NodeOf(const CKHkContextualMeca* meca) { return static_cast<CAnimatedNode*>(meca->m_pKGLObject); }
int32_t* AnimWords(const CKHkContextualMeca* meca) {
    return static_cast<CAnimationDictionary*>(meca->m_unk20)->m_apAnimations;
}
// The original's CAnimationDictionary_PostLoad 0x7a288 replaces each word by its animation (-1 by null), so its tests
// "entry != 0" and "node's animation == entry" are on animations; dotd keeps the words and resolves them here (an
// absent entry is -1: LVL010's meca dictionaries hold -1 at entries 2 / 3, so the original falls back to 1 / 0).
bool HasAnim(int32_t word) { return CAnimationManager_GetAnimation(static_cast<uint32_t>(word)) != nullptr; }
bool CurrentAnimIs(const CKHkContextualMeca* meca, int32_t word) {
    RtAnimAnimation* animation = CAnimationManager_GetAnimation(static_cast<uint32_t>(word));
    return animation != nullptr && reinterpret_cast<void*>(NodeOf(meca)->GetCurrentAnim()) == reinterpret_cast<void*>(animation);
}
uint8_t AlphaByte(float alpha) { return static_cast<uint8_t>(ppc::fctiwz(alpha)); }

// The collision meshes after the node's hidden bit: +0x24 alone, or with a +0x28 the one of the state (2: +0x28).
void UpdateCollisionMeshes(CKHkContextualMeca* meca, bool state2) {
    const uint32_t hidden = (NodeOf(meca)->m_sgProperties >> 2) & 1u;
    CKGroundCpnt* ground = static_cast<CKGroundCpnt*>(meca->m_unk24);
    if (meca->m_unk28 == nullptr) {
        ground->SetActive(static_cast<uint8_t>(hidden ^ 1u));  // 0x001910a8
        return;
    }
    if (!state2) {
        ground->SetActive(static_cast<uint8_t>(hidden ^ 1u));
        static_cast<CKGroundCpnt*>(meca->m_unk28)->SetActive(0);
    } else {
        ground->SetActive(0);
        static_cast<CKGroundCpnt*>(meca->m_unk28)->SetActive(hidden == 0 ? 1 : 0);
    }
}
}  // namespace

namespace {
const float kOneF = 1.0f;          // TOC1 +0x565c
const float kSnapTime = 0.2f;      // TOC1 +0x56a8: the walk into a slot lasts 0.2 s
const float kCrossfade = 0.3f;     // TOC1 +0x56e4
const float kReleaseDelay = 0.5f;  // TOC1 +0x56e8
const float kMoveTimeout = 10.0f;  // TOC1 +0x56ec
const float kRandScale = -3.05180438e-05f;  // TOC1 +0x56dc (0xb8000080)
const CVector3 kUpAxis = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC1 +0x56ac)

CKHkS08Hero* SlotHero(const CKHkContextualMeca::SSlot& slot) { return static_cast<CKHkS08Hero*>(slot.m_pHero); }
CKS08GameManager* MecaGameManager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }
IKGrpHero* MecaHeroGroup() { return static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]); }
// The hero's animation words of the mechanism: the dictionary of its dragon in the +0x4c list.
int32_t* HeroAnimWords(const CKHkContextualMeca* meca, CKHkS08Hero* hero) {
    return static_cast<CAnimationDictionary*>(meca->m_apUnk4C[hero->GetDragonIndex()])->m_apAnimations;
}
float AnimDuration(int32_t word) {  // the animation's duration (+0x10)
    return CAnimationManager_GetAnimation(static_cast<uint32_t>(word))->duration;
}
// The camera constraint of the mechanism let go when it is the camera's (its +0x30 signals, twice).
void ReleaseCameraConstraint(CKHkContextualMeca* meca) {
    CKCameraConstraint* constraint = static_cast<CKCameraConstraint*>(meca->m_unkF4);
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    if (constraint == nullptr || constraint != camera->m_pActiveConstraint) return;
    QueueTriggerSignals(&constraint->m_tsUnk30);
    camera->m_pActiveConstraint = nullptr;
    QueueTriggerSignals(&constraint->m_tsUnk30);
}
void StopLoopSound(CKHkContextualMeca* meca, uint32_t index) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(meca->m_unk2C);
    if (sounds->GetSound(index) != nullptr) Sound_Stop(sounds->GetSound(index), 0);  // 0x001111b0
}
void StartLoopSound(CKHkContextualMeca* meca, uint32_t index) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(meca->m_unk2C);
    if (sounds->GetSound(index) == nullptr) return;
    if (sounds->GetSound(index)->IsPlaying() != 0) return;  // 0x00111568
    sounds->GetSound(index)->SetLoop(1);                     // 0x00110fd0
    sounds->GetSound(index)->Play(kZero);                    // 0x00111230
}
void PlayOnce(CKHkContextualMeca* meca, uint32_t index) {
    CKSound* sound = static_cast<CKSoundDictionaryID*>(meca->m_unk2C)->GetSound(index);
    if (sound == nullptr) return;
    sound->SetLoop(0);
    sound->Play(kZero);
}
// The activators of both sides: those of side 0 on with `side0`, side 1 with `side1`, each only while the rest bit
// (21) is set.
void SetSideActivators(CKHkContextualMeca* meca, uint32_t side0, uint32_t side1) {
    for (int32_t i = 0; static_cast<int32_t>(meca->m_unk5E) > i; ++i) {
        CKHkHeroActivator_CallSetEnabled(meca->m_apUnk60[i], (meca->m_bitArray & 0x200000u) != 0 ? static_cast<int32_t>(side0) : 0);
    }
    for (int32_t i = 0; static_cast<int32_t>(meca->m_unk5F) > i; ++i) {
        CKHkHeroActivator_CallSetEnabled(meca->m_apUnk64[i], (meca->m_bitArray & 0x200000u) != 0 ? static_cast<int32_t>(side1) : 0);
    }
}
// The explosion effect of `data` acquired (CKSrvFx_AcquireFx inlined), placed at the node's world position facing its
// at row, triggered with `launch` and released.
void FireExplosionAtNode(CKHkContextualMeca* meca, IKSerializable* data, const CVector3* position, const void* launch) {
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(
        static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(data), meca));
    if (fx == nullptr) return;
    const RwMatrix* ltm = FrameLtm(NodeOf(meca)->m_pRwFrame);
    const CVector3 at = {ltm->at.x, ltm->at.y, ltm->at.z};
    fx->SetPosition(&at, position, meca);  // 0x001b6438
    fx->Trigger(meca, launch);              // 0x001b82a8
    fx->ReleaseReservation(meca);           // vt+0x54
}
}  // namespace

// 0x0045a760 CKHkContextualMeca_PlaceSlotActivators_maybe
void CKHkContextualMeca::PlaceSlotActivators() {
    NodeOf(this)->ForceWorldMatrixUpdate();  // vt+0x50
    for (int pass = 0; pass < 2; ++pass) {
        const uint32_t count = pass == 0 ? m_unk5E : m_unk5F;
        IKSerializable** hotSpots = pass == 0 ? m_apUnk68 : m_apUnk6C;
        IKSerializable** activators = pass == 0 ? m_apUnk60 : m_apUnk64;
        for (uint32_t i = 0; i < count; ++i) {
            CMatrix34 matrix;
            static_cast<CSGHotSpot*>(hotSpots[i])->GetWorldMatrix(&matrix);  // 0x000ce970
            Mat4_RotateLocalYDeg(kSlotTurn, &matrix);                        // 0x002413d0
            const float push = m_unkCC;
            matrix.m_pos.x = ppc::fmadds(matrix.m_at.x, push, matrix.m_pos.x);
            matrix.m_pos.y = ppc::fmadds(matrix.m_at.y, push, matrix.m_pos.y);
            matrix.m_pos.z = ppc::fmadds(matrix.m_at.z, push, matrix.m_pos.z);
            // rlwinm 14,1,31 + rotlwi 18 on the flags word (+0xc): rwMATRIXINTERNALIDENTITY (0x20000) cleared.
            uint32_t flags;
            std::memcpy(&flags, reinterpret_cast<const uint8_t*>(&matrix) + 0xc, 4);
            flags &= ~0x20000u;
            std::memcpy(reinterpret_cast<uint8_t*>(&matrix) + 0xc, &flags, 4);
            static_cast<CKHkHeroActivator*>(activators[i])->SetTransform(&matrix);  // 0x00448100
        }
    }
}

// 0x00460450 CKHkContextualMeca_OnActivate
void CKHkContextualMeca::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338 the active actor list
    for (uint32_t i = 0; i < m_unk5C; ++i) {
        m_aSlots[i].m_pHero = nullptr;
        m_aSlots[i].m_ui8State = 0;
    }
    const bool state2 = ((m_bitArray >> 17) & 3u) == 2;
    // Every activator off unless bit 21 (the rest state); then each side's on when the state is the other one.
    for (uint32_t i = 0; i < m_unk5E; ++i) {
        const int32_t on = (m_bitArray & 0x200000u) == 0 ? 0 : (state2 ? 0 : 1);
        CKHkHeroActivator_CallSetEnabled(m_apUnk60[i], on);  // 0x00448038
    }
    for (uint32_t i = 0; i < m_unk5F; ++i) {
        const int32_t on = (m_bitArray & 0x200000u) == 0 ? 0 : (state2 ? 1 : 0);
        CKHkHeroActivator_CallSetEnabled(m_apUnk64[i], on);
    }
    m_afUnkF8[1] = kZero;
    m_afUnkF8[2] = kZero;
    m_afUnkF8[3] = kZero;
    m_afUnkF8[4] = kZero;
    m_afUnkF8[0] = kZero;
    m_bitArray = (m_bitArray & 0xffa7ffffu) | 0x400000u;
    m_fUnk110 = -1.0f;  // TOC1 +0x5658
    m_unk5D = 0;
    m_unk118 = 0;
    m_unkEC = kZero;
    m_fUnk11C = kZero;
    int32_t* words = AnimWords(this);
    if (!state2) {
        m_fUnk110 = m_unk80;
        NodeOf(this)->PlayAnim(kZero, static_cast<uint32_t>(words[0]), 0);  // 0x000c98b8
        m_fUnk114 = kZero;
    } else {
        m_fUnk110 = m_unk84;
        NodeOf(this)->PlayAnim(kZero, static_cast<uint32_t>(words[1]), 0);
        m_fUnk114 = kAlphaOpaque;
    }
    SceneNode_SetAlphaRecursive(m_unk44, AlphaByte(m_fUnk114), 1);  // 0x00582c60
    PlaceSlotActivators();
    UpdateCollisionMeshes(this, state2);
    SetVisible(static_cast<int32_t>(~(m_bitArray >> 24) & 1u));  // vt+0xd0 (lbz of +0x0c: the word's top byte)
}

// 0x0045d120 CKHkContextualMeca_Restart. Unlike OnActivate: no slot reset, no PlaceSlotActivators / collision-mesh update
// of its own (SetVisible updates the meshes), and the activators of both sides get the rest bit's answer.
void CKHkContextualMeca::Restart() {
    m_afUnkF8[1] = kZero;  // integer 0 stores
    m_afUnkF8[2] = kZero;
    m_afUnkF8[3] = kZero;
    m_afUnkF8[4] = kZero;
    m_afUnkF8[0] = kZero;
    m_bitArray = (m_bitArray & 0xffa7ffffu) | 0x400000u;
    m_fUnk110 = -1.0f;  // TOC1 +0x5658
    m_unk5D = 0;
    m_fUnk11C = kZero;
    m_unk118 = 0;
    m_unkEC = kZero;
    if ((m_bitArray & 4u) != 0) return;
    ReleaseHeroes(0);  // 0x0045a3a0
    const uint32_t state = (m_bitArray >> 17) & 3u;
    const bool atEnd = !(state == 1 || state == 0);
    if (atEnd) {
        m_bitArray = (m_bitArray & 0xfff9ffffu) | 0x40000u;
        m_fUnk110 = m_unk84;
    } else {
        m_bitArray &= 0xfff9ffffu;
        m_fUnk110 = m_unk80;
    }
    for (int32_t i = 0; static_cast<int32_t>(m_unk5E) > i; ++i) {
        const int32_t on = (m_bitArray & 0x200000u) != 0 ? (atEnd ? 0 : 1) : 0;
        CKHkHeroActivator_CallSetEnabled(m_apUnk60[i], on);  // 0x00448038
    }
    for (int32_t i = 0; static_cast<int32_t>(m_unk5F) > i; ++i) {
        const int32_t on = (m_bitArray & 0x200000u) != 0 ? (atEnd ? 1 : 0) : 0;
        CKHkHeroActivator_CallSetEnabled(m_apUnk64[i], on);
    }
    int32_t* words = AnimWords(this);
    if (atEnd) {
        m_fUnk110 = m_unk84;
        NodeOf(this)->PlayAnim(kZero, static_cast<uint32_t>(words[1]), 0);  // 0x000c98b8
        m_fUnk114 = kAlphaOpaque;
    } else {
        m_fUnk110 = m_unk80;
        NodeOf(this)->PlayAnim(kZero, static_cast<uint32_t>(words[0]), 0);
        m_fUnk114 = kZero;
    }
    SetVisible(static_cast<int32_t>(~(m_bitArray >> 24) & 1u));  // vt+0xd0
    SceneNode_SetAlphaRecursive(m_unk44, AlphaByte(m_fUnk114), 1);  // TocBridge 0x98f570 -> 0x00582c60
}

// 0x0045a990 CKHkContextualMeca_OnDeactivate
void CKHkContextualMeca::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
}

// 0x0045cfe0 CKHkContextualMeca_SetVisible
void CKHkContextualMeca::SetVisible(int32_t visible) {
    if (visible == 0 && (m_bitArray & 0x200000u) != 0) SetEnabled(0);  // vt+0xcc
    CAnimatedNode* node = NodeOf(this);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | ((static_cast<uint32_t>(visible ^ 1) & 0xffu) << 2);
    UpdateCollisionMeshes(this, ((m_bitArray >> 17) & 3u) == 2);
}

// 0x0045a3a0 CKHkContextualMeca_ReleaseHeroes: every hero in a slot detached (with `all`, the player-controlled ones
// stay and the freed slots' activators switch back on); the +0xbc signals when a player's hero left.
void CKHkContextualMeca::ReleaseHeroes(uint8_t all) {
    if (m_unk5C == 0) return;
    bool player = false;
    for (uint32_t i = 0; i < m_unk5C; ++i) {
        SSlot& slot = m_aSlots[i];
        if (slot.m_pHero == nullptr) continue;
        if (static_cast<CKHkS08Hero*>(slot.m_pHero)->IsPlayerControlled() != 0 && all != 0) continue;
        if (!player && static_cast<CKHkS08Hero*>(slot.m_pHero)->IsPlayerControlled() != 0) player = true;
        static_cast<CKHkS08Hero*>(slot.m_pHero)->DetachFromObject();  // 0x00364608
        slot.m_pHero = nullptr;
        if (all != 0 && slot.m_pActivator != nullptr) CKHkHeroActivator_CallSetEnabled(slot.m_pActivator, 1);
    }
    if (player) QueueTriggerSignals(&m_unkBC);
}

// 0x00459da8 CKHkContextualMeca_UpdateLoopSounds
void CKHkContextualMeca::UpdateLoopSounds() {
    CKSoundDictionaryID* dictionary = static_cast<CKSoundDictionaryID*>(m_unk2C);
    CKSound* first = dictionary->GetSound(1);  // 0x00112bc0
    CKSound* second = dictionary->GetSound(3);
    const bool firstPlays = first != nullptr && first->m_pInstances != nullptr;
    const bool secondPlays = second != nullptr && second->m_pInstances != nullptr;
    if (!firstPlays && !secondPlays) return;
    float speed;
    float volume;
    if (m_unk40 == 0 || m_afUnkF8[3] <= kZero) {
        volume = ppc::fmadds(m_afUnkF8[1], m_unk3C - m_unk38, m_unk38);
        speed = ppc::fmadds(m_unk34 - m_unk30, m_afUnkF8[1], m_unk30);
    } else {
        const float t = m_afUnkF8[2] / m_afUnkF8[3];
        volume = ppc::fmadds(t, m_unk3C - m_unk38, m_unk38);
        speed = ppc::fmadds(m_unk34 - m_unk30, t, m_unk30);
    }
    if (!(kZero < speed) || !(kZero <= volume)) return;
    if (first != nullptr) first->SetSpeed(speed);  // 0x00110e98
    if (second != nullptr) second->SetSpeed(speed);
    if (first != nullptr) first->SetBaseVolume(volume);  // 0x00110ee8
    if (second != nullptr) second->SetBaseVolume(volume);
}

// 0x0045f420 CKHkContextualMeca_UpdateAtRest
void CKHkContextualMeca::UpdateAtRest(IKTime* frameClock, uint32_t state) {
    const float dt = frameClock->m_afDeltaTime[0];
    CAnimatedNode* node = NodeOf(this);
    int32_t* words = AnimWords(this);
    // The animation: the closing (word 2) and opening (word 3) animations hand over to the rest ones at their end.
    if (HasAnim(words[2]) && CurrentAnimIs(this, words[2])) {
        if (!node->IsAnimEndReached(dt)) {  // 0x000ca368
            node->AddAnimTime(dt);          // 0x000c9638
        } else {
            node->PlayAnim(kZero, static_cast<uint32_t>(words[1]), 0);
        }
    } else if (HasAnim(words[3]) && CurrentAnimIs(this, words[3])) {
        if (!node->IsAnimEndReached(dt)) {
            node->AddAnimTime(dt);
        } else {
            node->PlayAnim(kZero, static_cast<uint32_t>(words[0]), 0);
        }
    }
    const uint32_t side = state & 0xffu;
    // The +0x110 delay: at its end the side's signals, its rest animation, and the progress restarted.
    if (kZero <= m_fUnk110) {
        m_fUnk110 = m_fUnk110 - dt;
        if (m_fUnk110 <= kZero) {
            if (side == 0) {
                QueueTriggerSignals(&m_unk9C);  // 0x00236338
                m_bitArray = (m_bitArray & 0xfff9ffffu) | 0x20000u;
                node->PlayAnim(kZero, static_cast<uint32_t>(words[0]), 0);
            } else {
                QueueTriggerSignals(&m_unkA4);
                m_bitArray = (m_bitArray & 0xfff9ffffu) | 0x60000u;
                node->PlayAnim(kZero, static_cast<uint32_t>(words[1]), 0);
            }
            m_bitArray = (m_bitArray & 0xffe7ffffu) | 0x80000u;
            m_unk118 = 0;
            m_afUnkF8[1] = kZero;
        }
    }
    uint32_t held = 0;        // r22: the slots with a hero snapped or holding
    bool playerHeld = false;  // r14: one of the slots' heroes is player-controlled
    if (m_afUnkF8[0] <= kZero) {
        ReleaseCameraConstraint(this);
        for (uint32_t i = 0; i < m_unk5C; ++i) {
            SSlot& slot = m_aSlots[i];
            CKHkS08Hero* hero = SlotHero(slot);
            if (hero == nullptr) continue;
            if (hero->IsPlayerControlled() != 0) playerHeld = true;  // 0x00362af0
            const uint8_t slotState = slot.m_ui8State;
            if (slotState == 1) {
                // Holding: the hero stays at the hot spot; a player pulling away lets go; the action button fires the
                // at-rest effect.
                ++held;
                hero->AdvanceObjectAnimTime(dt);                   // 0x00363410
                SnapHeroToSlot(kZero, static_cast<int32_t>(i));    // 0x0045b420
                if (IsHeroPullingAway(i) != 0) {                   // 0x0045a618
                    --held;
                    QueueTriggerSignals(&m_unkBC);
                    SlotHero(slot)->DetachFromObject();            // 0x00364608
                    CKHkHeroActivator_CallSetEnabled(slot.m_pActivator, 1);
                    slot.m_pHero = nullptr;
                }
                if (hero->IsPlayerControlled() == 0) continue;
                const uint8_t player = hero->m_ui8Hero == hero->m_ui8TrackedLeader ? hero->m_ui8Leader : 0xff;  // 0x00362ac8
                CKS08GameManager* manager = MecaGameManager();
                if (manager->IsInputBlocked() != 0) continue;              // vt+0x1ec
                if (manager->IsActionPressed(3, player) == 0) continue;    // vt+0x160
                TriggerAtRestFx();                                          // 0x00459f98
            } else if (slotState == 0) {
                // Snapping: the walk into the slot.
                ++held;
                SnapHeroToSlot(dt, static_cast<int32_t>(i));
                hero->AdvanceObjectAnimTime(dt);
            } else if (slotState == 2) {
                // A companion walking to the slot: a player's hero lets go; arrived, it takes the slot (state 0).
                if (hero->IsPlayerControlled() != 0) {
                    hero->DetachFromObject();
                    slot.m_pHero = nullptr;
                    CKHkHeroActivator_CallSetEnabled(slot.m_pActivator, 1);
                    continue;
                }
                if (hero->UpdateMoveTo(frameClock, nullptr) == 0) continue;  // vt+0xd0
                slot.m_ui8State = 0;
                const float* p = hero->GetPositionPtr();  // 0x00361968
                slot.m_vPosition = {p[0], p[1], p[2]};
                slot.m_vDirection = {hero->m_unk540, hero->m_unk544, hero->m_unk548};  // 0x00361a50
                slot.m_fTime = kZero;
                hero->SetObjectControlsAnim(1);                  // 0x00362010
                hero->SetLockedToObject(1, nullptr, nullptr);    // 0x003622a8
                hero->SetFlag364Bit12IfAttached(0);              // 0x00363e58
                hero->CrossfadeAnimResource(kCrossfade, kZero, static_cast<uint32_t>(HeroAnimWords(this, hero)[side != 0 ? 3 : 2]),
                                            1);  // vt+0xc4
            }
        }
    } else {
        m_afUnkF8[0] = m_afUnkF8[0] - dt;
        if (m_afUnkF8[0] <= kZero) ReleaseHeroes(0);
    }
    if (kZero < m_afUnkF8[0] || m_unk5C != held) {
        // The activators of the side: a hero that used one (bits 8 and 10, +0x9c) takes its slot; a free slot of a
        // mechanism a player works gets a companion sent to it.
        IKSerializable** activators = side == 0 ? m_apUnk60 : m_apUnk64;
        IKSerializable** hotSpots = (m_bitArray & 0x1000u) != 0 ? (side == 0 ? m_apUnk70 : m_apUnk74)
                                                                : (side == 0 ? m_apUnk68 : m_apUnk6C);
        const uint32_t count = side == 0 ? m_unk5E : m_unk5F;
        for (uint32_t i = 0; i < count; ++i) {
            CKHkHeroActivator* activator = static_cast<CKHkHeroActivator*>(activators[i]);
            SSlot& slot = m_aSlots[i];
            const uint32_t flags = activator->m_bitArray;
            if ((flags & 0x100u) != 0 && (flags & 0x400u) != 0) {
                CKHkS08Hero* user = static_cast<CKHkS08Hero*>(activator->m_pUser);
                if (user == nullptr || user->AttachToObject(this, 2) == 0) continue;  // 0x00362360
                CKHkHeroActivator_CallSetEnabled(activator, 0);
                user->SetAttachedMovementEnabled(1);          // 0x00362050
                user->SetObjectControlsAnim(1);               // 0x00362010
                user->SetLockedToObject(1, nullptr, nullptr);  // 0x003622a8
                user->CrossfadeAnimResource(kCrossfade, kZero, static_cast<uint32_t>(HeroAnimWords(this, user)[side != 0 ? 3 : 2]),
                                            1);  // vt+0xc4
                slot.m_pHero = user;
                slot.m_ui8State = 0;
                slot.m_unk2C = 0;
                slot.m_unk2D = 0;
                slot.m_pHotSpot = hotSpots[i];
                const float* p = user->GetPositionPtr();
                slot.m_vPosition = {p[0], p[1], p[2]};
                slot.m_vDirection = {user->m_unk540, user->m_unk544, user->m_unk548};
                slot.m_fTime = kZero;
                slot.m_pActivator = activator;
                m_afUnkF8[0] = kZero;
                m_unk5D = 0;
                continue;
            }
            if (!playerHeld || slot.m_pHero != nullptr) continue;
            IKGrpHero* group = MecaHeroGroup();
            for (uint32_t j = 0; static_cast<int32_t>(group->m_ui8CompanionHeroCount) > static_cast<int32_t>(j); ++j) {
                CKHkS08Hero* companion = static_cast<CKHkS08Hero*>(group->m_apCompanionHeroes[j]);  // 0x002ca0e8
                if (companion->GetAttachedObject() == this) continue;   // 0x00361d50
                if (companion->AttachToObject(this, 2) == 0) continue;
                CMatrix34 matrix;
                static_cast<CSGHotSpot*>(hotSpots[i])->GetWorldMatrix(&matrix);  // 0x000ce970
                companion->SetAttachedMovementEnabled(1);
                slot.m_pHero = companion;
                slot.m_pHotSpot = hotSpots[i];
                slot.m_fTime = kZero;  // stw 0
                slot.m_pActivator = activator;
                slot.m_ui8State = 2;
                companion->SetFlag364Bit12IfAttached(1);
                CKHkHeroActivator_CallSetEnabled(activator, 0);
                m_afUnkF8[0] = kZero;  // stw 0
                companion->SetMoveDestination(kMoveTimeout, &matrix.m_pos, &matrix.m_at, 0, 1, 0);  // vt+0xcc
                break;
            }
        }
        if (m_afUnkF8[0] <= kZero && !playerHeld) ReleaseHeroes(1);
        if (m_unk5D != 0) UpdateHeroInteraction(frameClock, side == 0 ? 1u : 3u);  // 0x0045dbd0
        return;
    }
    // Every slot held: the mechanism moves to the side's state.
    if ((m_bitArray & 0x400000u) != 0) {
        m_afUnkF8[1] = kZero;
        m_unk118 = 0;
    }
    IKSerializable** impulsions = side == 0 ? m_apUnk88 : m_apUnk8C;
    if (side == 0) {
        m_bitArray = (m_bitArray & 0xfff9ffffu) | 0x20000u;
        node->PlayAnim(kZero, static_cast<uint32_t>(words[0]), 0);
        QueueTriggerSignals(&m_unk9C);
    } else {
        m_bitArray = (m_bitArray & 0xfff9ffffu) | 0x60000u;
        node->PlayAnim(kZero, static_cast<uint32_t>(words[1]), 0);
        QueueTriggerSignals(&m_unkA4);
    }
    if ((m_bitArray & 0x400000u) != 0) {
        for (uint32_t i = 0; i < m_unk5C; ++i) {
            CKImpulsionCpnt* impulsion = static_cast<CKImpulsionCpnt*>(impulsions[i]);
            impulsion->m_unk2c = kZero;
            impulsion->m_unk24 = kZero;
            impulsion->m_unk28 = kZero;
        }
    }
    m_bitArray &= 0xfd67ffffu;
    m_unk5D = 0;
}

// 0x004601d8 CKHkContextualMeca_Update
void CKHkContextualMeca::Update(IKTime* frameClock) {
    RwFrame* frame = NodeOf(this)->m_pRwFrame;
    const RwMatrix* ltm = FrameLtm(frame);  // the stored LTM of the original, computed on demand
    if (frame->modelling.pos.x != ltm->pos.x || frame->modelling.pos.y != ltm->pos.y ||
        frame->modelling.pos.z != ltm->pos.z) {
        PlaceSlotActivators();
    }
    const float dt = frameClock->m_afDeltaTime[0];
    const uint32_t state = (m_bitArray >> 17) & 3u;
    if (state == 1 || state == 3) {
        UpdateHeroInteraction(frameClock, state);  // 0x0045dbd0 (the mechanism being worked)
    } else if ((m_bitArray & 0x200000u) == 0) {
        if (kZero < m_afUnkF8[0]) {
            m_afUnkF8[0] = m_afUnkF8[0] - dt;
            if (m_afUnkF8[0] <= kZero) ReleaseHeroes(0);
        }
    } else {
        UpdateAtRest(frameClock, state);
    }
    UpdateLoopSounds();
    if (m_unk44 == nullptr) return;
    // The +0x44 node fades out in states 0 / 1 and in in states 2 / 3 (350 alpha per second).
    float alpha;
    if (state < 2) {
        if (m_fUnk114 <= kZero) return;
        alpha = ppc::fmadds(dt, kFadeOut, m_fUnk114);
        if (alpha <= kZero) {
            alpha = kZero;
        } else if (kAlphaOpaque <= alpha) {
            alpha = kAlphaOpaque;
        }
    } else {
        if (kAlphaOpaque <= m_fUnk114) return;
        alpha = ppc::fmadds(dt, kFadeIn, m_fUnk114);
        if (kAlphaOpaque <= alpha) {
            alpha = kAlphaOpaque;
        } else if (alpha <= kZero) {
            alpha = kZero;
        }
    }
    m_fUnk114 = alpha;
    SceneNode_SetAlphaRecursive(m_unk44, AlphaByte(alpha), 1);
}

// 0x00459c90 CKHkContextualMeca_GetProgressRatio_maybe (the fight zone component's modes 1 and 2)
float CKHkContextualMeca::GetProgressRatio() const {
    const uint32_t flags = m_bitArray;
    float ratio;
    if ((flags & 0x80000u) == 0) {
        ratio = static_cast<float>(static_cast<int32_t>(m_unk118)) + m_afUnkF8[1];
        const float total = static_cast<float>(static_cast<int32_t>(m_unkD0));
        if (ratio > total) ratio = total;
        ratio = ratio / total;
    } else {
        ratio = m_afUnkF8[1];
    }
    if (((flags >> 17) & 3u) <= 1u) return ratio;
    return 1.0f - ratio;  // TOC 0x565c
}

// 0x0045b1f0 CKHkContextualMeca_GetInfo, with 0x009c4020 _GetIsAtEnd (the flags' bits 17-18 at 2 or 3), 0x009c3fc0
// _GetIsBeingOperated (bits 17-18 at 1 or 3 and +0x100 not at or below 0) and 0x009c4048 _GetProgress (as
// GetProgressRatio). The actor base answers 1.
int32_t CKHkContextualMeca::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    switch (info->m_ui32Id) {
    case 0x9a:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            const uint32_t mode = (static_cast<CKHkContextualMeca*>(o)->m_bitArray >> 17) & 3u;
            return mode == 2 || mode == 3 ? 1u : 0u;
        }, 0);
    case 0x9b:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            const CKHkContextualMeca* meca = static_cast<CKHkContextualMeca*>(o);
            const uint32_t mode = (meca->m_bitArray >> 17) & 3u;
            if (mode != 1 && mode != 3) return 0u;
            return meca->m_afUnkF8[2] <= 0.0f ? 0u : 1u;  // ble: a NaN answers 1
        }, 0);
    case 0x9c:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return FloatBits(static_cast<CKHkContextualMeca*>(o)->GetProgressRatio());
        }, 2);
    default:
        return 1;
    }
}

// ---- C2.8 meca-hero: the heroes working the mechanism ----


// 0x00459f98 CKHkContextualMeca_TriggerAtRestFx_maybe: the explosion +0xdc at the node, sound 2 once.
void CKHkContextualMeca::TriggerAtRestFx() {
    if (m_unkDC != nullptr) {
        const RwV3d& p = FrameLtm(NodeOf(this)->m_pRwFrame)->pos;
        const CVector3 position = {p.x, p.y, p.z};
        FireExplosionAtNode(this, m_unkDC, &position, nullptr);
    }
    PlayOnce(this, 2);
}

// 0x0045c940 CKHkContextualMeca_TriggerInteractionFx_maybe: the explosion +0xd8 at the node, sound 0 once, flag bit 23.
void CKHkContextualMeca::TriggerInteractionFx() {
    if (m_unkD8 != nullptr) {
        const RwV3d& p = FrameLtm(NodeOf(this)->m_pRwFrame)->pos;
        const CVector3 position = {p.x, p.y, p.z};
        FireExplosionAtNode(this, m_unkD8, &position, nullptr);
    }
    PlayOnce(this, 0);
    m_bitArray = (m_bitArray & 0xff7fffffu) | 0x800000u;
}

// 0x0045cc48 CKHkContextualMeca_SpawnStepFx_maybe: the explosion +0xe0 at the node's position moved by up to +0xe4 on
// each axis (three rand draws, x / y / z, only when an effect was free), launched with the node's world matrix.
void CKHkContextualMeca::SpawnStepFx() {
    if (m_unkE0 == nullptr) return;
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(
        static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_unkE0), this));
    if (fx == nullptr) return;
    const RwMatrix* ltm = FrameLtm(NodeOf(this)->m_pRwFrame);
    CVector3 position = {ltm->pos.x, ltm->pos.y, ltm->pos.z};
    const float baseY = position.y;
    position.x = ppc::fmadds(ppc::fmadds(static_cast<float>(Rand_Int() & 0xffff), kRandScale, kOneF), m_unkE4, position.x);
    const float baseZ = position.z;
    position.y = ppc::fmadds(ppc::fmadds(static_cast<float>(Rand_Int() & 0xffff), kRandScale, kOneF), m_unkE4, baseY);
    position.z = ppc::fmadds(ppc::fmadds(static_cast<float>(Rand_Int() & 0xffff), kRandScale, kOneF), m_unkE4, baseZ);
    const CVector3 at = {ltm->at.x, ltm->at.y, ltm->at.z};
    fx->SetPosition(&at, &position, this);  // 0x001b6438 (the LTM's at row)
    fx->Trigger(this, ltm);                  // 0x001b82a8 (launch: the node's LTM)
    fx->ReleaseReservation(this);            // vt+0x54
}

// 0x0045b420 CKHkContextualMeca_SnapHeroToSlot_maybe: the slot's time runs `dt` / 0.2; at 1 the hero's node stands at
// the hot spot facing its at row (state 1, holding); before, between where it took the slot and the hot spot.
void CKHkContextualMeca::SnapHeroToSlot(float dt, int32_t index) {
    SSlot& slot = m_aSlots[index];
    CSGMovable* node = static_cast<CSGMovable*>(SlotHero(slot)->m_pKGLObject);
    slot.m_fTime = slot.m_fTime + dt / kSnapTime;
    CMatrix34 matrix;
    static_cast<CSGHotSpot*>(slot.m_pHotSpot)->GetWorldMatrix(&matrix);  // 0x000ce970
    if (slot.m_fTime >= kOneF) {
        RwFrame* frame = node->m_pRwFrame;
        frame->modelling.pos.z = matrix.m_pos.z;
        frame->modelling.pos.x = matrix.m_pos.x;
        frame->modelling.pos.y = matrix.m_pos.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);                          // 0x00010698
        node->SetOrientationFromAtUp(&matrix.m_at, &kUpAxis);  // 0x000d0918
        node->ForceWorldMatrixUpdate();                    // vt+0x50
        slot.m_ui8State = 1;
        return;
    }
    const float t = slot.m_fTime;
    const float u = kOneF - t;
    CVector3 position;
    position.x = ppc::fmadds(u, slot.m_vPosition.x, t * matrix.m_pos.x);
    position.y = ppc::fmadds(u, slot.m_vPosition.y, t * matrix.m_pos.y);
    position.z = ppc::fmadds(u, slot.m_vPosition.z, t * matrix.m_pos.z);
    const float s = slot.m_fTime;
    const float v = kOneF - s;
    CVector3 direction;
    direction.x = ppc::fmadds(v, slot.m_vDirection.x, s * matrix.m_at.x);
    direction.y = ppc::fmadds(v, slot.m_vDirection.y, s * matrix.m_at.y);
    direction.z = ppc::fmadds(v, slot.m_vDirection.z, s * matrix.m_at.z);
    const float length = static_cast<float>(c22spyro::MathSqrtf(
        ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, direction.y * direction.y))));  // 0x00010690
    if (length != kZero) {
        const float inverse = kOneF / length;
        direction.z = direction.z * inverse;
        direction.x = direction.x * inverse;
        direction.y = direction.y * inverse;
    } else {
        const RwV3d& at = node->m_pRwFrame->modelling.at;
        direction = {at.x, at.y, at.z};
    }
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.z = position.z;
    frame->modelling.pos.x = position.x;
    frame->modelling.pos.y = position.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
    node->SetOrientationFromAtUp(&direction, &kUpAxis);
    node->ForceWorldMatrixUpdate();  // vt+0x50
}

// 0x0045a618 CKHkContextualMeca_IsHeroPullingAway_maybe: a player's hero pushing its stick (input byte above 200) away
// from its facing (the dot product below 0).
uint8_t CKHkContextualMeca::IsHeroPullingAway(uint32_t index) {
    CKHkS08Hero* hero = SlotHero(m_aSlots[index]);
    if (hero->IsPlayerControlled() == 0) return 0;
    if (!(hero->GetPlayerInputByte394() > 200)) return 0;  // 0x00362dd0
    const float* move = hero->GetPlayerMoveVectorPtr();   // 0x00362a40
    const float mz = move[2];
    const float mx = move[0];
    const float my = move[1];
    hero = SlotHero(m_aSlots[index]);
    const float dot = ppc::fmadds(mz, hero->m_unk548, ppc::fmadds(mx, hero->m_unk540, my * hero->m_unk544));  // +0x540
    return !(dot >= kZero) ? 1 : 0;  // bge: a NaN pulls away
}

// 0x0045a288 CKHkContextualMeca_SetSlotActivatorsEnabled_maybe
void CKHkContextualMeca::SetSlotActivatorsEnabled(int32_t on) {
    for (int32_t i = 0; static_cast<int32_t>(m_unk5E) > i; ++i) CKHkHeroActivator_CallSetEnabled(m_apUnk60[i], on);
    for (int32_t i = 0; static_cast<int32_t>(m_unk5F) > i; ++i) CKHkHeroActivator_CallSetEnabled(m_apUnk64[i], on);
}

// 0x0045d9d0 CKHkContextualMeca_SetEnabled (vt+0xcc): bit 21; the camera constraint let go; disabled, MoveTo (vt+0xd4)
// to the state's end (states 2 / 3) with mode 1; the activators by the rest bit and the state.
void CKHkContextualMeca::SetEnabled(int32_t enabled) {
    const uint32_t on = static_cast<uint32_t>(enabled);
    if (on == ((m_bitArray >> 21) & 1u)) return;
    m_bitArray = (m_bitArray & 0xffdfffffu) | (on << 21);
    ReleaseCameraConstraint(this);
    const uint32_t state = (m_bitArray >> 17) & 3u;
    const uint32_t atEnd = state == 2 || state == 3 ? 1u : 0u;
    if (on == 0) VfD4(static_cast<int32_t>(atEnd), 1);  // vt+0xd4
    SetSideActivators(this, atEnd ^ 1u, atEnd);
}

// 0x0045ad48 CKHkContextualMeca_MessageProc: the actor messages, 0x940 (a hero leaves its slot: the +0xbc signals for a
// player, detached, the slot's activator back on unless the release delay runs, the slot freed) and 0x2666 (the prompt
// text of +0xf0: its text 0 in state 1, else 1).
int32_t CKHkContextualMeca::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0x940) {
        own = 0;
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(data);
        uint32_t index = 0;
        bool found = false;
        for (; index < m_unk5C; ++index) {
            if (m_aSlots[index].m_pHero == hero) {
                found = true;
                break;
            }
        }
        if (found) {
            if (hero->IsPlayerControlled() != 0) QueueTriggerSignals(&m_unkBC);
            SlotHero(m_aSlots[index])->DetachFromObject();  // 0x00364608
            if (m_afUnkF8[0] <= kZero && m_aSlots[index].m_pActivator != nullptr) {
                CKHkHeroActivator_CallSetEnabled(m_aSlots[index].m_pActivator, 1);
            }
            m_aSlots[index].m_pHero = nullptr;
        }
    } else if (message == 0x2666) {
        CKLocTextAccessor* accessor = static_cast<CKLocTextAccessor*>(m_unkF0);
        IKSerializable* text;
        if (accessor->m_texts.m_pBlock == nullptr) {
            text = accessor->m_pText;
        } else {
            text = accessor->m_texts.m_pBlock[((m_bitArray >> 17) & 3u) == 1 ? 0 : 1];
        }
        own = 0;
        *static_cast<IKSerializable**>(data) = text;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x0045d3f0 CKHkContextualMeca_MoveTo (vt+0xd4; the actor messages 0x90c..0x90f): the slots' activators back on, the
// heroes let go; `on` towards the end (states 2 / 3), off towards the start: `mode` 0 starts the move (from the
// opposite rest state, the +0x9c / +0xa4 signals) or turns a running move around (bit 19 / 20), `mode` 1 jumps there
// (the +0xb4 / +0xac signals, the state's rest animation, the activators, the +0x44 node's alpha). The collision meshes
// and the loop sounds 3 and 4 follow.
void CKHkContextualMeca::VfD4(int32_t on, int32_t mode) {
    const uint32_t state = (m_bitArray >> 17) & 3u;
    for (uint32_t i = 0; i < m_unk5C; ++i) {
        if (m_aSlots[i].m_pHero != nullptr && m_aSlots[i].m_pActivator != nullptr) {
            CKHkHeroActivator_CallSetEnabled(m_aSlots[i].m_pActivator, 1);
        }
    }
    ReleaseHeroes(0);
    int32_t* words = AnimWords(this);
    const uint32_t hidden = (NodeOf(this)->m_sgProperties >> 2) & 1u;
    if ((on & 0xff) != 0) {
        if ((mode & 0xff) != 0) {
            if (state != 2) {
                m_bitArray = (m_bitArray & 0xfff9ffffu) | 0x40000u;
                m_afUnkF8[1] = kZero;
                m_afUnkF8[2] = kZero;
                m_afUnkF8[3] = kZero;
                m_afUnkF8[4] = kZero;
                m_afUnkF8[0] = kZero;
                m_bitArray = (m_bitArray & 0xffa7ffffu) | 0x400000u;
                m_fUnk110 = -1.0f;  // TOC1 +0x5658
                m_unk5D = 0;
                m_unk118 = 0;
                m_unkEC = kZero;
                m_fUnk11C = kZero;
                NodeOf(this)->PlayAnim(kZero, static_cast<uint32_t>(words[1]), 0);  // 0x000c98b8
                for (int32_t i = 0; static_cast<int32_t>(m_unk5E) > i; ++i) CKHkHeroActivator_CallSetEnabled(m_apUnk60[i], 0);
                for (int32_t i = 0; static_cast<int32_t>(m_unk5F) > i; ++i) {
                    CKHkHeroActivator_CallSetEnabled(m_apUnk64[i], static_cast<int32_t>((m_bitArray >> 21) & 1u));
                }
                QueueTriggerSignals(&m_unkB4);
                m_fUnk110 = m_unk84;
                m_afUnkF8[1] = kZero;
                m_unk118 = 0;
                m_fUnk114 = kAlphaOpaque;
                SceneNode_SetAlphaRecursive(m_unk44, 0xff, 1);  // 0x0098f570
            }
        } else if (state == 0) {
            QueueTriggerSignals(&m_unk9C);
            m_bitArray = (m_bitArray & 0xffe1ffffu) | 0xa0000u;
            m_afUnkF8[1] = kZero;
            m_unk118 = state;
        } else if (state == 1) {
            m_bitArray = (m_bitArray & 0xfff7ffffu) | 0x80000u;
        }
        CKGroundCpnt* ground = static_cast<CKGroundCpnt*>(m_unk24);
        if (m_unk28 == nullptr) {
            ground->SetActive(static_cast<uint8_t>(hidden ^ 1u));  // 0x001910a8
        } else {
            ground->SetActive(0);
            static_cast<CKGroundCpnt*>(m_unk28)->SetActive(static_cast<uint8_t>(hidden ^ 1u));
        }
    } else {
        if ((mode & 0xff) != 0) {
            if (state != 0) {
                m_bitArray &= 0xfff9ffffu;
                m_afUnkF8[1] = kZero;
                m_afUnkF8[2] = kZero;
                m_afUnkF8[3] = kZero;
                m_afUnkF8[4] = kZero;
                m_afUnkF8[0] = kZero;
                m_bitArray = (m_bitArray & 0xffa7ffffu) | 0x400000u;
                m_fUnk110 = -1.0f;
                m_unk5D = 0;
                m_unk118 = 0;
                m_unkEC = kZero;
                m_fUnk11C = kZero;
                NodeOf(this)->PlayAnim(kZero, static_cast<uint32_t>(words[0]), 0);
                for (int32_t i = 0; static_cast<int32_t>(m_unk5E) > i; ++i) {
                    CKHkHeroActivator_CallSetEnabled(m_apUnk60[i], static_cast<int32_t>((m_bitArray >> 21) & 1u));
                }
                for (int32_t i = 0; static_cast<int32_t>(m_unk5F) > i; ++i) CKHkHeroActivator_CallSetEnabled(m_apUnk64[i], 0);
                QueueTriggerSignals(&m_unkAC);
                m_fUnk110 = m_unk80;
                m_afUnkF8[1] = kZero;
                m_fUnk114 = kZero;  // stw 0
                m_unk118 = 0;
                SceneNode_SetAlphaRecursive(m_unk44, 0, 1);
            }
        } else if (state == 2) {
            QueueTriggerSignals(&m_unkA4);
            m_bitArray = (m_bitArray & 0xffe1ffffu) | 0xe0000u;
            m_afUnkF8[1] = kZero;
            m_unk118 = static_cast<uint32_t>(mode & 0xff);
        } else if (state == 1) {
            m_bitArray = (m_bitArray & 0xffefffffu) | 0x100000u;
        }
        CKGroundCpnt* ground = static_cast<CKGroundCpnt*>(m_unk24);
        ground->SetActive(static_cast<uint8_t>(hidden ^ 1u));
        if (m_unk28 != nullptr) static_cast<CKGroundCpnt*>(m_unk28)->SetActive(0);
    }
    StopLoopSound(this, 3);
    StopLoopSound(this, 4);
}

// 0x0045dbd0 CKHkContextualMeca_UpdateHeroInteraction (side 1 or 3: the state being worked towards). The heroes in the
// slots snap / hold (a player pulling away lets go), the camera constraint follows the players; with bit 19 (moving on
// its own, +0x78 / +0x7c seconds) or bit 20 (going back) the progress +0xfc runs by itself; else the heroes push the
// side's impulsion components (+0x88 / +0x8c: the action button pressed by every player's hero, the step effect and the
// loop sounds 3 / 4) until the progress reaches 1 (+0xd0 steps of it, +0x90 / +0x94 per step). The node's animation
// and the heroes' animations follow the progress; at the end the side's signals, the state, the activators, the
// animation and the release.
void CKHkContextualMeca::UpdateHeroInteraction(IKTime* clock, uint32_t sideArg) {
    const uint32_t side = sideArg & 0xffu;
    const float dt = clock->m_afDeltaTime[0];
    float rate = side == 1 ? m_unk90 : m_unk94;  // f28
    int32_t present = 0;  // r19: heroes in the slots
    int32_t players = 0;  // r25: player-controlled ones
    bool hold = false;    // r0
    float progress;       // f30
    float one = kOneF;    // f29
    IKSerializable** impulsions = nullptr;  // r21
    uint32_t atEnd = 0;   // r25 at the end
    uint32_t flags = m_bitArray;
    CAnimatedNode* node = NodeOf(this);
    if ((flags & 0x80000u) != 0) {
        if (m_afUnkF8[0] > kZero) {
            m_afUnkF8[0] = m_afUnkF8[0] - dt;
            if (m_afUnkF8[0] <= kZero) {
                ReleaseHeroes(0);
                present = 0;
                players = 0;
                flags = m_bitArray;
                goto check20;
            }
        }
        present = 0;
        players = 0;
        goto check20;
    }
    for (uint32_t i = 0; i < m_unk5C; ++i) {
        SSlot& slot = m_aSlots[i];
        if (slot.m_pHero == nullptr) continue;
        ++present;
        if (slot.m_ui8State == 0) {
            SnapHeroToSlot(dt, static_cast<int32_t>(i));     // 0x0045b420
            SlotHero(slot)->AdvanceObjectAnimTime(dt);         // 0x00363410
        } else {
            const bool check = m_unkD0 == 0 ||
                               !(static_cast<float>(static_cast<int32_t>(m_unk118)) + m_afUnkF8[1] >=
                                 rate * static_cast<float>(static_cast<int32_t>(m_unkD0)));
            if (check && IsHeroPullingAway(i) != 0) {
                --present;
                QueueTriggerSignals(&m_unkBC);
                SlotHero(slot)->DetachFromObject();
                slot.m_pHero = nullptr;
                CKHkHeroActivator_CallSetEnabled(slot.m_pActivator, 1);
            } else {
                SnapHeroToSlot(kZero, static_cast<int32_t>(i));
            }
        }
        if (slot.m_pHero != nullptr && SlotHero(slot)->IsPlayerControlled() != 0) ++players;
    }
    if (players == 0) {
        ReleaseCameraConstraint(this);
    } else {
        // The players' camera constraint becomes the camera's (the previous one's +0x30 signals, its +0x28 ones).
        CKCameraConstraint* constraint = static_cast<CKCameraConstraint*>(m_unkF4);
        CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
        if (constraint != nullptr && constraint != camera->m_pActiveConstraint) {
            if (camera->m_pActiveConstraint != nullptr) QueueTriggerSignals(&camera->m_pActiveConstraint->m_tsUnk30);
            camera->m_pActiveConstraint = constraint;
            QueueTriggerSignals(&constraint->m_tsUnk28);
            constraint->m_unk74 = *reinterpret_cast<const uint32_t*>(&constraint->m_afUnk44[10]);  // +0x74 = +0x6c
            constraint->m_unk9c = (constraint->m_unk9c & 0x00ffffffu) | 0xff000000u;            // the byte +0x9c
        }
    }
    if (present > 0 && players == 0 && m_unkD4 >= kZero) {
        // Companions alone: they let go when no controlled hero is within +0xd4 of the node.
        const RwV3d& at = FrameLtm(node->m_pRwFrame)->pos;
        const float ax = at.x, ay = at.y, az = at.z;
        IKGrpHero* group = MecaHeroGroup();
        bool near = false;
        for (uint32_t j = 0; static_cast<int32_t>(group->m_ui8ControlledHeroCount) > static_cast<int32_t>(j); ++j) {
            const float* p = static_cast<CKHkS08Hero*>(group->m_apControlledHeroes[j])->GetPositionPtr();
            const float dy = p[1] - ay;
            const float dx = p[0] - ax;
            const float dz = p[2] - az;
            if (ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)) < m_unkD4 * m_unkD4) {
                near = true;
                break;
            }
        }
        if (!near) {
            ReleaseHeroes(0);
            present = 0;
        }
    }
    flags = m_bitArray;
check20:
    if ((flags & 0x100000u) != 0) {
        // Going back: the progress falls by dt / (+0x7c on side 1, else +0x78).
        one = kOneF;
        m_afUnkF8[2] = one;
        m_afUnkF8[3] = one;
        const float divisor = side == 1 ? m_unk7C : m_unk78;
        if (!(divisor > kZero)) {
            hold = true;
            progress = m_afUnkF8[1];
        } else {
            hold = false;
            progress = m_afUnkF8[1] - dt / divisor;
            m_afUnkF8[1] = progress;
        }
        if (progress <= kZero) goto finished;
        if (hold) goto finished;
        goto animate;
    }
    if ((flags & 0x80000u) != 0) {
        // Moving on its own: the progress rises by dt / (+0x78 on side 1, else +0x7c).
        one = kOneF;
        m_afUnkF8[2] = one;
        m_afUnkF8[3] = one;
        const float divisor = side == 1 ? m_unk78 : m_unk7C;
        if (!(divisor > kZero)) {
            hold = true;
            progress = m_afUnkF8[1];
        } else {
            hold = false;
            progress = m_afUnkF8[1] + dt / divisor;
            m_afUnkF8[1] = progress;
        }
        if (progress >= one) goto finished;
        if (hold) goto finished;
        goto animate;
    }
    // Worked by the heroes.
    impulsions = side == 1 ? m_apUnk88 : m_apUnk8C;
    if (impulsions == nullptr) return;
    if (m_unkD0 != 0 && !(static_cast<float>(static_cast<int32_t>(m_unk118)) + m_afUnkF8[1] <
                          rate * static_cast<float>(static_cast<int32_t>(m_unkD0)))) {
        // Every step pushed: the node's animation plays to its end (the +0xc4 signals once, bit 25).
        progress = m_afUnkF8[1];
        if ((m_bitArray & 0x2000000u) == 0) {
            QueueTriggerSignals(&m_unkC4);
            m_bitArray = (m_bitArray & 0xfdffffffu) | 0x2000000u;
            progress = m_afUnkF8[1];
        }
        const float step = dt / node->GetCurrentAnimDuration();  // 0x000c9768
        one = kOneF;
        m_afUnkF8[1] = progress + step;
        goto progressCheck;
    }
    if (static_cast<int32_t>(m_unk5C) > present && m_unk5D == 0) {
        // Not every slot held: a running impulsion takes the mechanism back (bit 20), else it goes to the side's rest.
        if (static_cast<CKImpulsionCpnt*>(impulsions[0])->m_unk04[6] != kZero) {  // +0x1c
            one = kOneF;
            m_bitArray = (m_bitArray & 0xffefffffu) | 0x100000u;
            goto progressCheck;
        }
        const uint32_t toEnd = side == 3 ? 1u : 0u;  // r28
        if (toEnd != 0) {
            m_bitArray = (m_bitArray & 0xfff9ffffu) | 0x40000u;
        } else {
            m_bitArray &= 0xfff9ffffu;
        }
        m_bitArray &= 0xffbfffffu;
        UpdateCollisionMeshes(this, toEnd != 0);
        m_unk5D = 1;
        if (players == 0) {
            ReleaseHeroes(0);
            SetSideActivators(this, toEnd ^ 1u, toEnd);
        }
        one = kOneF;
        goto progressCheck;
    }
    {
        m_afUnkF8[1] = kZero;
        m_afUnkF8[2] = kZero;
        m_afUnkF8[3] = kZero;
        progress = kZero;
        const uint32_t count = m_unk5C;
        int32_t moving = 0;    // r18: impulsions with a value
        int32_t full = 0;      // r17: impulsions at their top speed
        int32_t pushers = 0;   // r16: player heroes counted
        uint8_t allPressed = 1;  // r15
        if (count == 0) {
            one = kOneF;
            goto average;
        }
        for (uint32_t i = 0; i < m_unk5C; ++i) {
            SSlot& slot = m_aSlots[i];
            if (present < static_cast<int32_t>(m_unk5C)) continue;
            if (SlotHero(slot)->IsPlayerControlled() == 0) continue;
            const uint8_t player = SlotHero(slot)->m_ui8Hero == SlotHero(slot)->m_ui8TrackedLeader
                                       ? SlotHero(slot)->m_ui8Leader : 0xff;  // 0x00362ac8
            CKS08GameManager* manager = MecaGameManager();
            if (manager->IsInputBlocked() == 0 && manager->IsActionPressed(3, player) != 0) {  // vt+0x1ec, vt+0x160
                slot.m_unk2C = 1;
                slot.m_unk2D = 1;
                CKSound* sound = static_cast<CKSoundDictionaryID*>(m_unk2C)->GetSound(1);
                const float now = clock->m_afCurrentTime[0];
                if (sound != nullptr && now - m_fUnk11C >= m_unk98) {
                    sound->SetLoop(0);
                    sound->Play(kZero);
                    m_fUnk11C = now;
                }
            } else {
                slot.m_unk2D = 0;
                allPressed = static_cast<uint8_t>(slot.m_unk2C & allPressed);
            }
            ++pushers;
            const uint8_t index = SlotHero(slot)->m_ui8Hero == SlotHero(slot)->m_ui8TrackedLeader
                                      ? SlotHero(slot)->m_ui8Leader : 0xff;
            MecaGameManager()->SetHeroInteractionTarget(this, 0, index);  // 0x004ee770
        }
        one = kOneF;
        if (m_unk5C == 0) {
            progress = m_afUnkF8[1];
            goto average;
        }
        {
            bool pushed = false;  // r22
            for (uint32_t i = 0; i < m_unk5C; ++i) {
                SSlot& slot = m_aSlots[i];
                CKImpulsionCpnt* impulsion = static_cast<CKImpulsionCpnt*>(impulsions[i]);
                const bool playerSlot = pushers > 0 && present >= static_cast<int32_t>(m_unk5C) &&
                                        SlotHero(slot)->IsPlayerControlled() != 0;
                if (!playerSlot) {
                    // Bit 16: without players and every slot held, a slow push of 0.3 keeps it going.
                    if (!pushed && (m_bitArray & 0x10000u) != 0 && pushers == 0 &&
                        !(static_cast<int32_t>(m_unk5C) > present)) {
                        pushed = true;
                        if (impulsion->m_unk28 < impulsion->m_unk04[3] * kCrossfade) impulsion->Impulse(kCrossfade);  // 0x0024bce0
                    }
                } else if (allPressed == 0) {
                    if (!pushed && slot.m_unk2D != 0) {
                        pushed = true;
                        if (impulsion->m_unk28 < impulsion->m_unk04[3] * kCrossfade) impulsion->Impulse(kCrossfade);
                    }
                } else {
                    if (!pushed) {
                        impulsion->Impulse(one);
                        pushed = true;
                    }
                    slot.m_unk2C = 0;
                }
                impulsion->Update(dt);  // 0x0024bd40
                if (m_unkD0 == 1) {
                    progress = m_afUnkF8[1] + rate * impulsion->m_unk24 / impulsion->m_unk04[0];
                } else {
                    progress = m_afUnkF8[1] + impulsion->m_unk24 / impulsion->m_unk04[0];
                }
                m_afUnkF8[1] = progress;
                m_afUnkF8[2] = m_afUnkF8[2] + impulsion->m_unk28;
                m_afUnkF8[3] = m_afUnkF8[3] + impulsion->m_unk04[3];
                if (impulsion->m_unk24 > kZero) ++moving;
                if (impulsion->m_unk28 == impulsion->m_unk04[3]) ++full;
            }
        }
        if (pushers > 1) {
            const float n = static_cast<float>(pushers);
            m_afUnkF8[3] = m_afUnkF8[3] / n;
            m_afUnkF8[2] = m_afUnkF8[2] / n;
            goto clampAndSounds;
        }
        if (pushers != 0) goto clampAndSounds;
    average:
        {
            const float n = static_cast<float>(static_cast<int32_t>(m_unk5C));
            const float m = static_cast<float>(m_unk5C);
            m_afUnkF8[2] = m_afUnkF8[2] / n;
            m_afUnkF8[3] = m_afUnkF8[3] / m;
        }
    clampAndSounds:
        if (progress < kZero) m_afUnkF8[1] = kZero;
        if (moving != 0 && (full & 0xff) == moving) {
            float timer = m_unkEC;
            if (timer <= kZero) {
                m_unkEC = timer + m_unkE8;
                SpawnStepFx();  // 0x0045cc48
                timer = m_unkEC;
            }
            m_unkEC = timer - dt;
        } else {
            m_unkEC = kZero;  // stw 0
        }
        if (m_unk5D != 0 && m_afUnkF8[2] <= kZero) m_unk5D = 0;
        if (m_afUnkF8[2] == kZero) {
            StopLoopSound(this, 3);
            StopLoopSound(this, 4);
        } else {
            StartLoopSound(this, 3);
            if ((full & 0xff) == moving) {
                StartLoopSound(this, 4);
            } else {
                StopLoopSound(this, 4);
            }
        }
    }
progressCheck:
    if (!(m_afUnkF8[1] >= one)) goto animate;
    for (uint32_t i = 0; i < m_unk5C; ++i) static_cast<CKImpulsionCpnt*>(impulsions[i])->m_unk24 = kZero;  // stw 0
    flags = m_bitArray;
    goto finished;

animate:
    {
        // The node's animation at the progress (steps done + the step's progress) times its duration; the activation
        // mark (0x1a) crossed fires the interaction effect.
        const float before = node->GetCurrentAnimTime();  // 0x000c95a8
        const float after = (static_cast<float>(static_cast<int32_t>(m_unk118)) + m_afUnkF8[1]) *
                            node->GetCurrentAnimDuration();
        // 0x000c9720 answers the evaluated animation (+0x5c), tested for null; dotd's GetActiveAnim answers its dictionary
        // word, where 0 is a valid word (sector 0's first animation) and none is 0xffffffff. (Testing the word against 0
        // skipped the mark: G +36273, the mechanism's interaction effect at its activation mark came 14 frames late, at
        // the end of the move.)
        RtAnimAnimation* animation = CAnimationManager_GetAnimation(node->GetActiveAnim());
        if (animation != nullptr) {
            AnimMark* mark = Anim_GetMarkById(animation, 0x1a);  // 0x00078830
            if (mark != nullptr && before < after && AnimMark_CrossedValueR3(mark, before, after) != 0) {  // vt+0x1c
                TriggerInteractionFx();
            }
        }
        node->SetCurrentAnimTime(after);  // 0x000c9690
        if ((m_bitArray & 0x80000u) != 0) return;
        m_afUnkF8[4] = m_afUnkF8[4] + dt;
        // The heroes attached to the mechanism play the side's pair of animations (+0x4c dictionaries: words 2 / 0 on
        // side 1, 3 / 1 else), the second at the progress, weighted by +0x58 (or the speed +0x100 against +0x54).
        for (uint32_t i = 0; i < m_unk5C; ++i) {
            CKHkS08Hero* hero = SlotHero(m_aSlots[i]);
            if (hero == nullptr || hero->GetAttachedObject() != this) continue;
            int32_t* words = HeroAnimWords(this, hero);
            const int32_t loop = side == 1 ? words[2] : words[3];
            const int32_t push = side == 1 ? words[0] : words[1];
            if (loop == 0 || push == 0) continue;
            const float value = m_afUnkF8[1];
            const float pushLength = AnimDuration(push);
            float weight = one;
            if (m_unk50 == 0) {
                if (!(value >= m_unk58)) weight = value / m_unk58;
            } else {
                const float speed = std::fabs(m_afUnkF8[2]);
                if (m_unk54 > speed) weight = speed / m_unk54;
            }
            if (m_afUnkF8[4] > AnimDuration(loop)) {
                do {
                    m_afUnkF8[4] = m_afUnkF8[4] - AnimDuration(loop);
                } while (AnimDuration(loop) < m_afUnkF8[4]);
            }
            if (hero->IsAnimBlendCrossfading() == 0) {  // 0x00361fa0
                hero->SetAnimPairAndWeight(m_afUnkF8[4], value * pushLength, weight, static_cast<uint32_t>(loop),
                                           static_cast<uint32_t>(push));  // vt+0xc8
            } else {
                const float time = m_afUnkF8[1];
                hero->SetObjectAnimTime(time * hero->GetCurrentAnimDuration());  // 0x00363378, 0x00362450
            }
        }
        return;
    }

finished:
    {
        flags = m_bitArray;
        int32_t steps;
        if ((flags & 0x100000u) != 0) {
            steps = static_cast<int32_t>(m_unk118);
            if (steps > 0) {
                --steps;
                m_unk118 = static_cast<uint32_t>(steps);
            }
            if (steps != 0 && static_cast<int32_t>(m_unkD0) != steps) {
                m_afUnkF8[1] = m_afUnkF8[1] - one;
                return;
            }
        } else if ((flags & 0x80000u) != 0) {
            steps = static_cast<int32_t>(m_unkD0);
            m_unk118 = static_cast<uint32_t>(steps);
            if (steps != 0 && static_cast<int32_t>(m_unkD0) != steps) {
                m_afUnkF8[1] = m_afUnkF8[1] - one;
                return;
            }
        } else {
            steps = static_cast<int32_t>(m_unk118) + 1;
            m_unk118 = static_cast<uint32_t>(steps);
            if (steps != 0 && static_cast<int32_t>(m_unkD0) != steps) {
                m_afUnkF8[1] = m_afUnkF8[1] - one;
                return;
            }
        }
        // The move is over.
        if (side == 1) {
            if ((flags & 0x100000u) != 0) goto toStart;
            QueueTriggerSignals(&m_unkB4);
            goto toEndState;
        }
        if (side == 3) {
            if ((flags & 0x100000u) != 0) goto toEndState;
            QueueTriggerSignals(&m_unkAC);
        }
    toStart:
        atEnd = 0;
        m_bitArray &= 0xfff9ffffu;
        m_fUnk110 = m_unk80;
        goto settle;
    toEndState:
        atEnd = 1;
        m_bitArray = (m_bitArray & 0xfff9ffffu) | 0x40000u;
        m_fUnk110 = m_unk84;
    settle:
        if ((m_bitArray & 0x100000u) == 0 && (m_bitArray & 0x800000u) == 0) TriggerInteractionFx();  // 0x0045c940
        UpdateCollisionMeshes(this, atEnd != 0);
        SetSideActivators(this, atEnd ^ 1u, atEnd);
        int32_t* words = AnimWords(this);
        if (atEnd != 0) {
            node->PlayAnim(kZero, static_cast<uint32_t>(HasAnim(words[2]) ? words[2] : words[1]), 0);  // 0x000c98b8
        } else {
            node->PlayAnim(kZero, static_cast<uint32_t>(HasAnim(words[3]) ? words[3] : words[0]), 0);
        }
        if ((m_bitArray & 0x100000u) != 0) ReleaseHeroes(0);
        for (uint32_t i = 0; i < m_unk5C; ++i) {
            CKHkS08Hero* hero = SlotHero(m_aSlots[i]);
            if (hero == nullptr) continue;
            hero->SetObjectControlsAnim(0);                    // 0x00362010
            SlotHero(m_aSlots[i])->SetLockedToObject(0, nullptr, nullptr);  // 0x003622a8
        }
        m_afUnkF8[0] = kReleaseDelay;
        StopLoopSound(this, 3);
        StopLoopSound(this, 4);
        if (m_afUnkF8[1] > one) m_afUnkF8[1] = one;
        m_bitArray = (m_bitArray & 0xffbfffffu) | 0x400000u;
        m_unk5D = 0;
        m_afUnkF8[2] = kZero;
        m_unk118 = 0;
        m_afUnkF8[1] = kZero;
    }
}

// 0x0045ab80 CKHkContextualMeca_Destroy (CKHkActorBase_d82_maybe_ClearReferences 0x3f6e08 first: vt+0xc0, empty here)
void CKHkContextualMeca::Destroy() {
    Mem_FreeAligned16(m_apUnk4C);  // 0x00052fb8
    Mem_FreeAligned16(m_apUnk60);
    Mem_FreeAligned16(m_apUnk64);
    Mem_FreeAligned16(m_apUnk68);
    Mem_FreeAligned16(m_apUnk6C);
    Mem_FreeAligned16(m_apUnk70);
    Mem_FreeAligned16(m_apUnk74);
    Mem_FreeAligned16(m_apUnk88);
    Mem_FreeAligned16(m_apUnk8C);
    if (m_aSlots != nullptr) delete[] (reinterpret_cast<uint8_t*>(m_aSlots) - sizeof(SSlot*));  // 0x0098d360 OperatorDeleteArray
}
