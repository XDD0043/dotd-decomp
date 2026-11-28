// CKHkSequenceMgr.cpp - reconstructed original translation unit 0x460790-0x46b0c8 (GAME_TOC1, main_toc1), 88 functions, 55 live.
// Primary class: CKHkSequenceMgr  key 0x18c2  category Hook  size 0x140  vtable 0xb27310
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x460790  CKHkSequenceMgr_Delete
//   [ ] 0x4607e0  CKHkSequenceMgr_ResetRuntimeState_maybe  [dead]
//   [ ] 0x4608b0  CKHkSequenceMgr_IsWrongActionPressed_maybe  [dead]
//   [x] 0x460b28  CKHkSequenceMgr_ReleaseIconSet_maybe
//   [ ] 0x460c90  CKHkSequenceMgr_SendMsg407ToOwner_maybe  [dead]
//   [ ] 0x460d00  KStub_Return1_460d00  [dead]
//   [ ] 0x460d08  KStub_Return1_460d08  [dead]
//   [ ] 0x460d10  FUN_00460d10  [dead]
//   [ ] 0x460d40  KStub_Nop_460d40  [dead]
//   [ ] 0x460d48  KStub_Return1_460d48  [dead]
//   [ ] 0x460d50  FUN_00460d50  [dead]
//   [ ] 0x460d98  KStub_Nop_460d98  [dead]
//   [ ] 0x460da0  KStub_Return1_460da0  [dead]
//   [ ] 0x460da8  FUN_00460da8  [dead]
//   [ ] 0x460dd0  KStub_Return1_460dd0  [dead]
//   [ ] 0x460dd8  FUN_00460dd8  [dead]
//   [ ] 0x460df8  KStub_Nop_460df8  [dead]
//   [ ] 0x460e00  CKHkSequenceMgr_SetIconSetsFlag80000_maybe  [dead]
//   [ ] 0x460ee8  FUN_00460ee8  [dead]
//   [ ] 0x460f18  FUN_00460f18  [dead]
//   [ ] 0x460fc8  RegisterCKHkSequenceMgrClass
//   [ ] 0x461040  _GLOBAL__I_461040
//   [x] 0x461050  CKHkSequenceMgr_IsStepForPlayer_maybe
//   [x] 0x461178  CKHkSequenceMgr_CheckStepWindow_maybe
//   [ ] 0x461408  CKHkSequenceMgr_RefreshIconsForPlayerCount_maybe  [dead: no pointer to its descriptor 0xbbe850, no call]
//   [ ] 0x461498  CKHkSequenceMgr_SequenceEntry_Assign_maybe  [dead]
//   [x] 0x461658  CKHkSequenceMgr_UpdateCameraFromHotSpots_maybe
//   [ ] 0x461860  CKHkSequenceMgr_UpdateStepAnimation_maybe  [dead: no pointer to its descriptor 0xbbe868, no call]
//   [x] 0x461960  CKHkSequenceMgr_AdvanceAttachedHeroesAnim_maybe
//   [ ] 0x461af0  CKHkSequenceMgr_NotifyStepObjectsHookA_maybe  [dead]
//   [ ] 0x461c58  CKHkSequenceMgr_NotifyStepObjectsHookB_maybe  [dead]
//   [ ] 0x461dc0  CKHkSequenceMgr_UpdateMarkedTriggers_maybe  [dead]
//   [ ] 0x461e68  CKHkSequenceMgr_UpdateStepMarkedFx_maybe  [dead]
//   [ ] 0x461fc8  CKHkSequenceMgr_FireStepTriggersInWindow_maybe  [dead: no pointer to its descriptor 0xbbe898, no call]
//   [x] 0x462078  CKHkSequenceMgr_UpdateSoundTriggers_maybe
//   [x] 0x4621e0  CKHkSequenceMgr_DetachHeroes_maybe
//   [ ] 0x462300  CKHkSequenceMgr_FollowAttachedObject_maybe  [dead: no pointer to its descriptor 0xbbe8b0, no call]
//   [ ] 0x4623d0  CKHkSequenceMgr_ProbeGroundPoints_maybe  [dead]
//   [x] 0x4624f8  CKHkSequenceMgr_Pause  (empty / no effect: inherited)
//   [x] 0x462520  CKHkSequenceMgr_Stop
//   [x] 0x462548  CKHkSequenceMgr_PostLoad
//   [ ] 0x4625b0  CKHkSequenceMgr_Save
//   [x] 0x4625d8  CKHkSequenceMgr_RecursiveRegistration  (the actor base's (IKHook's): inherited)
//   [x] 0x462600  CKHkSequenceMgr_Construct  [dead]
//   [x] 0x462680  CKHkSequenceMgr_DeleteArray
//   [x] 0x462728  CKHkSequenceMgr_Destroy
//   [x] 0x462848  CKHkSequenceMgr_Resume
//   [ ] 0x4628b0  CKHkSequenceMgr_Construct_2  [dead]
//   [x] 0x462930  CKHkSequenceMgr_GetInfo
//   [ ] 0x462a60  CKHkSequenceMgr_ComputeStepWindowTimes_maybe  [dead]
//   [ ] 0x462ca8  CKHkSequenceMgr_SetEntryFlag2ById_maybe  [dead]
//   [ ] 0x462d30  FUN_00462d30  [dead]
//   [x] 0x462d48  CKHkSequenceMgr_AdvanceStepObjectsAnim_maybe
//   [x] 0x462f60  CKHkSequenceMgr_InitSequenceEntry_maybe
//   [x] 0x463100  CKHkSequenceMgr_Destructor
//   [x] 0x4631c8  CKHkSequenceMgr_BaseDestructor  (= ~CKHkSequenceMgr)
//   [x] 0x463290  CKHkSequenceMgr_DeletingDestructor  (= ~CKHkSequenceMgr)
//   [ ] 0x463360  CKHkSequenceMgr_AcquireOrReleaseCamera_maybe  [dead]
//   [x] 0x4634f0  CKHkSequenceMgr_CreateArray
//   [x] 0x463600  CKHkSequenceMgr_Create
//   [x] 0x463690  CKHkSequenceMgr_StopCurrentSequence_maybe
//   [x] 0x463ef8  CKHkSequenceMgr_AbortForOwner_maybe
//   [x] 0x463f90  CKHkSequenceMgr_OnDeactivate
//   [x] 0x4640f0  CKHkSequenceMgr_AdvanceStepAnim_maybe
//   [x] 0x464268  CKHkSequenceMgr_FreeBuffers_maybe  (CKHkSequenceMgr::VfC0)
//   [ ] 0x4643a0  FUN_004643a0  [dead]
//   [x] 0x4644a8  CKHkSequenceMgr_BeginEntryAnimAndCamera_maybe
//   [x] 0x464858  CKHkSequenceMgr_AttachActorToHotSpot_maybe
//   [x] 0x464b38  CKHkSequenceMgr_SetupHeroesForSequence_maybe
//   [x] 0x464f78  CKHkSequenceMgr_StartActorAnims_maybe
//   [x] 0x465348  CKHkSequenceMgr_StartSequence_maybe
//   [ ] 0x465670  CKHkSequenceMgr_PlayNextSequence_maybe  [dead: no pointer to its descriptor 0xbbea80, no call]
//   [x] 0x4657c0  CKHkSequenceMgr_StartSequenceWithListener_maybe
//   [ ] 0x465828  CKHkSequenceMgr_StartSequenceIfIdle_maybe  [dead]
//   [x] 0x465898  CKHkSequenceMgr_MessageProc
//   [x] 0x465ad0  CKHkSequenceMgr_LoadStepParamsRecord_maybe
//   [x] 0x465da0  CKHkSequenceMgr_Start
//   [x] 0x465f18  CKHkSequenceMgr_OnActivate_maybe
//   [x] 0x4661d0  CKHkSequenceMgr_Restart
//   [ ] 0x466418  CKHkSequenceMgr_LoadSize0x18Record_maybe  [dead]
//   [x] 0x4665b8  CKHkSequenceMgr_LoadObjectRefRecord_maybe
//   [x] 0x4667a0  CKHkSequenceMgr_LoadSequenceEntry_maybe
//   [x] 0x466e38  CKHkSequenceMgr_Load
//   [x] 0x467bc8  CKHkSequenceMgr_OnWrongInput_maybe
//   [x] 0x468530  CKHkSequenceMgr_UpdateButtonIcons_maybe
//   [x] 0x468f10  CKHkSequenceMgr_OnCorrectInput_maybe
//   [x] 0x469960  CKHkSequenceMgr_UpdateStep_maybe
//   [x] 0x46a6c8  CKHkSequenceMgr_Update
//
//   [ ] 0x9c40d8  CKHkSequenceMgr_IsKindOfClass  [inline]
//   [ ] 0x9c4130  CKHkSequenceMgr_GetClassType  [inline]
//   [ ] 0x9c4138  CKHkSequenceMgr_GetClassID  [inline]
//   [ ] 0x9c4140  CKHkSequenceMgr_GetResult  [inline]
//   [ ] 0x9c4150  CKHkSequenceMgr_GetTriggerProp15E_maybe  [inline]
#include "k2000/hooks/CKHkSequenceMgr.h"
#include "k2000/core/IKInfo.h"

#include <cstring>

#include "Renderware/rtanim/RtAnim.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwTypes.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKMarkedFX.h"
#include "k2000/logic/CKMarkedTrigger.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include "k2000/logic/fx/CKInputIconFxData.h"
#include "k2000/logic/fx/CKInputIconNodeFx.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Quat.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "crt/xatanf.h"

namespace {

// The TVector push every loop of these Loads inlines: grow to used + 1 when full (Grow 1).
template <class T>
T* PushBack(TVector<T, 1>& v) {
    const uint32_t used = v.m_ui32NbUsedElt;
    if (v.m_ui32NbElt == used) {
        uint32_t capacity = used + 1;
        if (capacity == 0) capacity = 1;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        v.m_ui32NbElt = capacity;
    }
    v.m_ui32NbUsedElt = used + 1;
    return &v.m_pBlock[used];
}

// The TOC floats at +0x56fc (0x00c1b0d4) and +0x572c: 1.0f and 0.0f.
const float kOne = 1.0f;
const float kZero = 0.0f;

using SequenceEntry = CKHkSequenceMgr::SequenceEntry;
using ObjectRefRecord = CKHkSequenceMgr::ObjectRefRecord;

CDefaultGameManager* GameManager() { return g_pEngine->m_gameManager; }
CKGrpS08Hero* HeroGroup() { return static_cast<CKGrpS08Hero*>(GameManager()->m_unk04[1]); }  // +0x08
// 0x002ca080 GetHeroByDragonIndex
CKHkS08Hero* HeroAt(CKGrpS08Hero* group, uint32_t index) {
    return static_cast<CKHkS08Hero*>(group->m_apHeros[index & 0xffu]);
}
// 0x002ca288 GetControlledHeroCount: the hero group's +0x50.
uint8_t ControlledHeroCount() { return static_cast<IKGrpHero*>(GameManager()->m_unk04[1])->m_ui8ControlledHeroCount; }
// The heroes the per-hero loops visit: 2 at most (CKGrpS08Hero_GetHeroCount 0x2ca038, asked twice below 3).
int32_t SequenceHeroCount(CKGrpS08Hero* group) {
    const uint8_t count = group->GetHeroCount();
    return count > 2 ? 2 : static_cast<int32_t>(group->GetHeroCount());
}
CAnimatedNode* NodeOf(const CKHkSequenceMgr* mgr) { return static_cast<CAnimatedNode*>(mgr->m_pKGLObject); }
CAnimatedNode* HeroNode(CKHkS08Hero* hero) { return static_cast<CAnimatedNode*>(hero->m_pKGLObject); }
// The original's CAnimationDictionary_PostLoad 0x7a288 turned the words into animations: a record's "animation" is the
// first word's (null for -1); dotd keeps the words and resolves them here.
uint32_t FirstWord(const IKSerializable* dictionary) {
    return static_cast<uint32_t>(static_cast<const CAnimationDictionary*>(dictionary)->m_apAnimations[0]);
}
bool RecordHasAnim(const ObjectRefRecord& record) {
    return record.m_pRef != nullptr && CAnimationManager_GetAnimation(FirstWord(record.m_pRef)) != nullptr;
}
CKAnmKeyFrameController* SlotController(AnimBlendSlot* slot) {
    return static_cast<CKAnmKeyFrameController*>(
        static_cast<CKBlenderController*>(slot->m_pController)->m_apControllers[slot->m_unk10]);
}
// The listener (+0x138) asked through message 0x407 (vt+0x1c).
void AskListener(CKHkSequenceMgr* mgr, uint32_t request, void* data) {
    CKHkSequenceMgr::SListenerMsg msg;
    msg.m_pSender = mgr;
    msg.m_ui32Request = request;
    msg.m_pData = data;
    mgr->m_unk138->MessageProc(0x407, &msg);
}
// The camera owners of the camera service (+0xe14, count +0xe24): `owner` added once / removed (the last one moved in).
void AddCameraOwner(CKSrvCamera* service, IKSerializable* owner) {
    for (uint32_t i = 0; i < service->m_unke24; ++i) {
        if (service->m_apCinematicOwner[i] == owner) return;
    }
    service->m_apCinematicOwner[service->m_unke24] = owner;
    service->m_unke24 = service->m_unke24 + 1;
}
void RemoveCameraOwner(CKSrvCamera* service, IKSerializable* owner) {
    const uint32_t count = service->m_unke24;
    if (count == 0) return;
    uint32_t i = 0;
    while (service->m_apCinematicOwner[i] != owner) {
        if (++i == count) return;
    }
    const uint32_t last = count - 1;
    service->m_unke24 = last;
    if (last != i) service->m_apCinematicOwner[i] = service->m_apCinematicOwner[last];
}
// The hero leaves the manager: no attached moves (+0x530 / +0x534 to 0 when the attached movement is on), unlocked
// (StopCurrentSequence only), detached, vulnerable, the input unblocked (the game manager's vt+0x1e8).
void ReleaseHero(CKHkS08Hero* hero, bool unlock) {
    hero->SetUnk530IfAttachedMovement(kZero);  // 0x003626a0
    hero->SetUnk534IfAttachedMovement(kZero);  // 0x00362688
    if (unlock) hero->SetLockedToObject(0, nullptr, nullptr);  // 0x003622a8
    hero->DetachFromObject();                  // 0x00364608
    if (unlock) hero->SetInvulnerable(0);      // 0x00361b20
    GameManager()->SetInputBlocked(0);         // vt+0x1e8
}
// The hero is held by the manager: attached (mode 3), the object controls its animation and movement, locked,
// invulnerable, the input blocked.
void HoldHero(CKHkS08Hero* hero, CKHkSequenceMgr* mgr) {
    hero->AttachToObject(mgr, 3);               // 0x00362360
    hero->SetObjectControlsAnim(1);             // 0x00362010
    hero->SetAttachedMovementEnabled(1);        // 0x00362050
    hero->SetLockedToObject(1, nullptr, nullptr);  // 0x003622a8
    hero->SetInvulnerable(1);                   // 0x00361b20
    GameManager()->SetInputBlocked(1);          // vt+0x1e8
}
// The answer flash (OnCorrectInput / OnWrongInput): the effect data's flag 0x10 cleared and its screen byte (+0x38) set,
// the player's old flash stopped (vt+0x58), a new one acquired (the CKSrvFx lookup inlined), placed at the icon data's
// offset (+0x34). `placeFirst`: the position before the orientation byte (+0x2c, cleared when the manager holds it).
void StartAnswerFlash(CKHkSequenceMgr* mgr, IKFx*& slot, IKSerializable* effectData, IKSerializable* iconData,
                      bool placeFirst) {
    if (slot != nullptr) {
        slot->StopAndRelease(mgr);  // vt+0x58
        slot = nullptr;
    }
    slot = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(effectData), mgr);
    if (slot == nullptr) return;
    CKParticlesEffectNodeFx* flash = static_cast<CKParticlesEffectNodeFx*>(slot);
    const CVector3 position = static_cast<CKInputIconFxData*>(iconData)->m_unk34;
    if (!placeFirst && (flash->m_baFxData & 2u) != 0 && flash->m_pOwner == mgr) flash->m_bRefreshOrientation = 0;
    SetOwnedParticleEffectPosition(flash, &position, mgr);  // 0x001cdce0
    if (placeFirst) {
        CKParticlesEffectNodeFx* now = static_cast<CKParticlesEffectNodeFx*>(slot);
        if ((now->m_baFxData & 2u) != 0 && now->m_pOwner == mgr) now->m_bRefreshOrientation = 0;
    }
}
void PrepareFlashData(CKHkSequenceMgr* mgr, IKSerializable* effectData) {
    CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(effectData);
    data->m_ui8Flags = static_cast<uint8_t>(data->m_ui8Flags & 0xefu);
    data->m_bScreenSpace = mgr->m_ui8IconOnScreen;
}
void PlaySound(IKSerializable* dictionary, uint32_t index) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(dictionary);
    if (CKSoundDictionaryID_GetSound(sounds, index) == nullptr) return;  // 0x00112bc0
    CKSound_Play(kZero, CKSoundDictionaryID_GetSound(sounds, index));     // 0x00111230
}

}  // namespace

// 0x004665b8 CKHkSequenceMgr_LoadObjectRefRecord_maybe
int32_t CKHkSequenceMgr::ObjectRefRecord::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pRef);
        ReadF32LE(file, &m_fBlend);
        ReadU8(file, &m_ui8Loop);
        ReadS32LE(file, &m_i32Target);
        ReadS32LE(file, &m_i32HotSpot);
        ReadU8(file, &m_unk0);
    }
    return 1;
}

// 0x00465ad0 CKHkSequenceMgr_LoadStepParamsRecord_maybe (the record at +0x6c runs on into the input window +0x88)
void CKHkSequenceMgr::SequenceEntry::LoadStepParams(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_stepParams.m_unk0);
        ReadU32LE(file, &m_stepParams.m_unk4);
        ReadU32LE(file, &m_stepParams.m_unk8);
        ReadU32LE(file, &m_stepParams.m_unkC);
        ReadU32LE(file, &m_stepParams.m_unk10);
        ReadU32LE(file, &m_stepParams.m_unk18);
        ReadU8(file, &m_stepParams.m_unk14);
        ReadU8(file, &m_inputWindow.m_ui8Mode);
        ReadF32LE(file, &m_inputWindow.m_fStart);
        ReadF32LE(file, &m_inputWindow.m_fLength);
    }
}

// 0x00462f60 CKHkSequenceMgr_InitSequenceEntry_maybe (stores in the original's order)
void CKHkSequenceMgr::SequenceEntry::Init(CKHkSequenceMgr* owner) {
    m_unk0 = 1.0f;
    m_unk4 = 1.0f;
    m_recB.m_unk0 = 1;
    m_recA.m_unk0 = 1;
    m_recC.m_unk0 = 1;
    m_recA.m_i32HotSpot = -1;
    m_recA.m_pRef = nullptr;
    m_recA.m_fBlend = 0.0f;
    m_recA.m_ui8Loop = 0;
    m_recA.m_i32Target = 0;
    m_recC.m_i32HotSpot = -1;
    m_recC.m_pRef = nullptr;
    m_recC.m_fBlend = 0.0f;
    m_recC.m_ui8Loop = 0;
    m_recC.m_i32Target = 0;
    m_recB.m_i32HotSpot = -1;
    m_recB.m_pRef = nullptr;
    m_recB.m_fBlend = 0.0f;
    m_recB.m_ui8Loop = 0;
    m_recB.m_i32Target = 0;
    m_pvRecords = static_cast<TVector<ObjectRefRecord, 1>*>(
        Mem_CallocAligned16(1, static_cast<uint32_t>(sizeof(TVector<ObjectRefRecord, 1>))));
    m_pvItems = static_cast<TVector<EntryItem, 1>*>(
        Mem_CallocAligned16(1, static_cast<uint32_t>(sizeof(TVector<EntryItem, 1>))));
    m_pvRecords->m_ui32NbElt = 1;
    m_pvRecords->m_pBlock = static_cast<ObjectRefRecord*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(ObjectRefRecord))));
    m_pvItems->m_ui32NbElt = 1;
    m_pvItems->m_pBlock = static_cast<EntryItem*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(EntryItem))));
    m_unk64 = 0xffffffffu;
    m_unk68 = 0xffffffffu;
    m_stepParams.m_unk18 = 0xffffffffu;
    m_stepParams.m_unk10 = 1;
    m_stepParams.m_unk0 = 0;
    m_stepParams.m_unk4 = 0;
    m_stepParams.m_unk8 = 0;
    m_stepParams.m_unkC = 0;
    m_stepParams.m_unk14 = 0;
    m_inputWindow.m_fLength = 1.0f;
    m_inputWindow.m_ui8Mode = 0;
    m_inputWindow.m_fStart = 0.0f;
    m_triggerWindow.m_fLength = 1.0f;
    m_triggerWindow.m_fStart = 0.0f;
    m_triggerWindow.m_ui8Mode = 0;
    m_pOwner = owner;
    m_unkB0 = 0;
    m_unkB1 = 2;
    m_unkA8 = 0;
}

// 0x004667a0 CKHkSequenceMgr_LoadSequenceEntry_maybe
int32_t CKHkSequenceMgr::SequenceEntry::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_unk0);
        ReadF32LE(file, &m_unk4);
        m_recA.Load(file, K_LEVEL_PLATEFORMS);
        m_recC.Load(file, K_LEVEL_PLATEFORMS);
        m_recB.Load(file, K_LEVEL_PLATEFORMS);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        if (m_pvRecords->m_pBlock == nullptr) {
            m_pvRecords->m_ui32NbElt = 1;
            m_pvRecords->m_pBlock =
                static_cast<ObjectRefRecord*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(ObjectRefRecord))));
        }
        for (uint32_t i = 0; i < count; ++i) {
            ObjectRefRecord* record = PushBack(*m_pvRecords);
            record->m_unk0 = 1;
            record->m_pRef = nullptr;
            record->m_fBlend = 0.0f;
            record->m_ui8Loop = 0;
            record->m_i32Target = 0;
            record->m_i32HotSpot = -1;
            record->Load(file, K_LEVEL_PLATEFORMS);
        }
        ReadU32LE(file, &count);
        if (m_pvItems->m_pBlock == nullptr) {
            m_pvItems->m_ui32NbElt = 1;
            m_pvItems->m_pBlock = static_cast<EntryItem*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(EntryItem))));
        }
        for (uint32_t i = 0; i < count; ++i) {
            EntryItem* item = PushBack(*m_pvItems);
            item->m_window.m_ui8Mode = 0;
            item->m_window.m_fStart = 0.0f;
            std::memcpy(&item->m_window.m_fLength, &kOne, 4);
            item->m_unk14 = 0;
            IKFile_ReadRef(file, &item->m_pRef);
            ReadU8(file, &item->m_window.m_ui8Mode);
            ReadF32LE(file, &item->m_window.m_fStart);
            ReadF32LE(file, &item->m_window.m_fLength);
            ReadU32LE(file, &item->m_unk14);
        }
        ReadU32LE(file, &m_unk64);
        ReadU32LE(file, &m_unk68);
        LoadStepParams(file, K_LEVEL_PLATEFORMS);  // 0x00465ad0
        ReadU8(file, &m_triggerWindow.m_ui8Mode);
        ReadF32LE(file, &m_triggerWindow.m_fStart);
        ReadF32LE(file, &m_triggerWindow.m_fLength);
        ReadS32LE(file, &m_unkA8);
        ReadU8(file, &m_unkB1);
    }
    return 1;
}

// CheckStepWindow's actor table: 0 record A (the node), 1 / 2 records B / C (the heroes), 3 and up the records.
CKHkSequenceMgr::ObjectRefRecord* CKHkSequenceMgr::SequenceEntry::ActorRecord(int32_t index) {
    if (index == 0) return &m_recA;
    if (index == 1) return &m_recB;
    if (index == 2) return &m_recC;
    return &m_pvRecords->m_pBlock[index - 3];
}

// 0x00466e38 CKHkSequenceMgr_Load
int32_t CKHkSequenceMgr::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    m_unk8c = 1.0f;
    m_unk94 = 1.0e-1f;
    m_unk88 = 1.0f;
    m_unk90 = 1.0e-1f;
    m_unk98[0] = 0.5f;
    m_unk98[1] = 2.0e-1f;
    m_unk98[2] = 0.0f;
    if (m_vEntries.m_pBlock == nullptr) {
        m_vEntries.m_ui32NbElt = 1;
        m_vEntries.m_pBlock = static_cast<SequenceEntry*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(SequenceEntry))));
    }
    if (m_vItems.m_pBlock == nullptr) {
        m_vItems.m_ui32NbElt = 1;
        m_vItems.m_pBlock = static_cast<MgrItem*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(MgrItem))));
    }
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        SequenceEntry* entry = PushBack(m_vEntries);
        entry->Init(this);
        entry->Load(file, K_LEVEL_PLATEFORMS);
    }
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        MgrItem* item = PushBack(m_vItems);
        ReadU8(file, &item->m_unk4);
        IKFile_ReadRef(file, &item->m_pRef);
        ReadU32LE(file, &item->m_unk8);
    }
    IKFile_ReadRef(file, &m_unk4c);
    IKFile_ReadObjectRefArray(file, m_apUnkC0, 5);
    m_unk50.Load(file, K_LEVEL_PLATEFORMS);
    m_unk60.Load(file, K_LEVEL_PLATEFORMS);
    m_unk68.Load(file, K_LEVEL_PLATEFORMS);
    m_unk70.Load(file, K_LEVEL_PLATEFORMS);
    m_unk80.Load(file, K_LEVEL_PLATEFORMS);
    m_unk58.Load(file, K_LEVEL_PLATEFORMS);
    m_unk78.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_unkA4);
    IKFile_ReadRef(file, &m_unkB0);
    IKFile_ReadRef(file, &m_unkB4);
    ReadF32LE(file, &m_unk88);
    ReadF32LE(file, &m_unk8c);
    ReadF32LE(file, &m_unk90);
    ReadF32LE(file, &m_unk94);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk98), 3);
    IKFile_ReadRef(file, &m_unk20);
    // One group per sequence entry: two references, then one reference per +0x30 item.
    m_vGroups.m_ui32NbElt = 1;
    m_vGroups.m_pBlock = static_cast<RefGroup**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(RefGroup*))));
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        RefGroup* group = new RefGroup;
        group->m_vRefs.m_pBlock = nullptr;
        group->m_vRefs.m_ui32NbUsedElt = 0;
        group->m_vRefs.m_ui32NbElt = 1;
        group->m_vRefs.m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
        IKFile_ReadRef(file, &group->m_pRef4);
        IKFile_ReadRef(file, &group->m_pRef0);
        for (uint32_t j = 0; j < m_vItems.m_ui32NbUsedElt; ++j) {
            IKSerializable* ref = nullptr;
            IKFile_ReadRef(file, &ref);
            *PushBack(group->m_vRefs) = ref;
        }
        *PushBack(m_vGroups) = group;
    }
    RefGroup* group = new RefGroup;
    group->m_vRefs.m_pBlock = nullptr;
    group->m_vRefs.m_ui32NbElt = 1;
    group->m_vRefs.m_ui32NbUsedElt = 0;
    m_pGroup48 = group;
    IKFile_ReadRef(file, &group->m_pRef4);
    IKFile_ReadRef(file, &m_pGroup48->m_pRef0);
    group = m_pGroup48;
    group->m_vRefs.m_ui32NbElt = 1;
    group->m_vRefs.m_pBlock =
        static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    for (uint32_t j = 0; j < m_vItems.m_ui32NbUsedElt; ++j) {
        IKSerializable* ref = nullptr;
        IKFile_ReadRef(file, &ref);
        *PushBack(m_pGroup48->m_vRefs) = ref;
    }
    IKFile_ReadRef(file, &m_unkA8);
    IKFile_ReadRef(file, &m_unkAC);
    return 1;
}

// 0x004621e0 CKHkSequenceMgr_DetachHeroes_maybe: every hero attached to this manager (+0x90) is released: +0x530 /
// +0x534 to 0 (TOC1 +0x572c) when its attached movement is on, detached, vulnerable again, and the game manager's
// input unblocked (vt+0x1e8 with 0).
void CKHkSequenceMgr::DetachHeroes() {
    CKGrpS08Hero* group = HeroGroup();
    if (group == nullptr) return;
    for (int32_t i = static_cast<int32_t>(group->GetHeroCount()) - 1; i != -1; --i) {  // 0x002ca038
        CKHkS08Hero* hero = HeroAt(group, static_cast<uint32_t>(i));  // 0x002ca080
        if (hero->GetAttachedObject() != this) continue;  // 0x00361d50
        hero->SetUnk530IfAttachedMovement(0.0f);  // 0x003626a0
        hero->SetUnk534IfAttachedMovement(0.0f);  // 0x00362688
        hero->DetachFromObject();                 // 0x00364608
        hero->SetInvulnerable(0);                 // 0x00361b20
        GameManager()->SetInputBlocked(0);        // vt+0x1e8
    }
}

namespace {
// The run-time reset Start and Restart share (and OnActivate with its own extras): no sequence, no icons, no presses,
// every item's run-time words cleared (a listener's node forgotten), the low nibble of +0xd4 cleared.
void ResetRuntime(CKHkSequenceMgr* mgr) {
    mgr->DetachHeroes();  // 0x004621e0
    mgr->m_unkE8 = -1;
    mgr->m_unkE1 = 0;
    mgr->m_apIconFx[0] = nullptr;
    mgr->m_apIconFx[1] = nullptr;
    mgr->m_unkF4 = 0;
    mgr->m_unkF8 = 0;
    mgr->m_unk138 = nullptr;
    mgr->m_unk118 = 0;
    mgr->m_unkE0 = 0;
    mgr->m_unkF0 = 0.0f;
    for (uint32_t i = mgr->m_vItems.m_ui32NbUsedElt; i != 0; --i) {
        CKHkSequenceMgr::MgrItem& item = mgr->m_vItems.m_pBlock[i - 1];
        item.m_pSavedParent = nullptr;  // +0x10
        item.m_pSavedMatrix = nullptr;  // +0x14
        item.m_pSlot = nullptr;         // +0x0c
        if (item.m_unk4 != 0) item.m_pRef = nullptr;
    }
    mgr->m_unkD4 &= 0xf0;
}
}  // namespace

// 0x00465da0 CKHkSequenceMgr_Start. Unless the manager is flagged (bit 2): a sequence still running (index in
// range) is stopped and the heroes it holds are released, the run-time words are cleared (every item's three
// words, and its reference when the item's byte is set), then the pending words. BUG(original): +0xe8 is read
// before anything wrote it on the first start (LVL010's three managers have bit 2, so the block does not run; G
// calls.jsonl: no StopCurrentSequence before +16434).
void CKHkSequenceMgr::Start() {
    CKHkActorBase::Start();
    m_unk131 = 1;
    m_unk134 = 0.0f;
    if ((m_bitArray & 4) == 0) {
        if (m_unkE8 >= 0 && static_cast<uint32_t>(m_unkE8) < m_vEntries.m_ui32NbUsedElt) {
            StopCurrentSequence();  // 0x00463690
        }
        ResetRuntime(this);
    }
    m_apIconFx[1] = nullptr;
    m_apIconDataFx[0] = nullptr;
    m_apIconDataFx[1] = nullptr;
    m_apIconFx[0] = nullptr;
}

// 0x004661d0 CKHkSequenceMgr_Restart
void CKHkSequenceMgr::Restart() {
    m_unk134 = 0.0f;
    if ((m_bitArray & 4) == 0) {
        if (m_unkE8 >= 0 && static_cast<int32_t>(m_vEntries.m_ui32NbUsedElt) > m_unkE8) {
            StopCurrentSequence();  // 0x00463690
        }
        ResetRuntime(this);
    }
    const uint8_t controlled = ControlledHeroCount();  // 0x002ca288
    if (m_unkE4 != controlled) {
        m_unkE4 = controlled;
        ReleaseIconSet(0);  // 0x00460b28
        ReleaseIconSet(1);
    }
    // BUG(original)_maybe: the loops count the entries (+0x2c) and the items (+0x38), not the groups or their refs.
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        RefGroup* group = m_vGroups.m_pBlock[i];
        static_cast<CKMarkedFX*>(group->m_pRef0)->StopAllChannelNodesAndReset();  // 0x005cfcb0
        static_cast<CKMarkedFX*>(group->m_pRef4)->StopAllChannelNodesAndReset();
        for (uint32_t j = 0; j < m_vItems.m_ui32NbUsedElt; ++j) {
            static_cast<CKMarkedFX*>(m_vGroups.m_pBlock[i]->m_vRefs.m_pBlock[j])->StopAllChannelNodesAndReset();
        }
    }
}

// 0x00460b28 CKHkSequenceMgr_ReleaseIconSet_maybe
void CKHkSequenceMgr::ReleaseIconSet(int32_t which) {
    if (which != 0 && which != 1) return;
    if (m_apIconFx[which] != nullptr) {
        m_apIconFx[which]->StopAndRelease(this);  // vt+0x58
        m_apIconFx[which] = nullptr;
    }
    if (m_apIconDataFx[which] != nullptr) {
        m_apIconDataFx[which]->ReleaseReservation(this);  // vt+0x54
        m_apIconDataFx[which] = nullptr;
    }
}

// 0x00462848 CKHkSequenceMgr_Resume
void CKHkSequenceMgr::Resume() {
    if ((m_unkD4 & 1u) != 0) GameManager()->m_flags64 |= 0x10000000u;
}

namespace {
// The TVector release the original inlines (Mem_FreeAligned16 when there is a block, length and block 0).
template <class T>
void FreeSequenceVector(TVector<T, 1>& vector) {
    if (vector.m_pBlock != nullptr) Mem_FreeAligned16(vector.m_pBlock);
    vector.m_ui32NbUsedElt = 0;
    vector.m_pBlock = nullptr;
}
// The group release of Destroy: its reference block freed (+0x08), length (+0x10) and block 0, the group deleted.
void DeleteRefGroup(CKHkSequenceMgr::RefGroup* group) {
    if (group->m_vRefs.m_pBlock != nullptr) Mem_FreeAligned16(group->m_vRefs.m_pBlock);
    group->m_vRefs.m_ui32NbUsedElt = 0;
    group->m_vRefs.m_pBlock = nullptr;
    delete group;  // OperatorDelete_Bridge
}
}  // namespace

// C2.8 port-all P18.
// 0x00463100 CKHkSequenceMgr_Destructor
CKHkSequenceMgr::~CKHkSequenceMgr() {
    FreeSequenceVector(m_vGroups);
    FreeSequenceVector(m_vItems);
    FreeSequenceVector(m_vEntries);
}

// C2.8 port-all P18.
// 0x00462728 CKHkSequenceMgr_Destroy
void CKHkSequenceMgr::Destroy() {
    CKHkActorBase::Destroy();  // 0x003f6e08: vt+0xc0
    for (uint32_t i = 0; i < m_vGroups.m_ui32NbUsedElt; ++i) {
        RefGroup* group = m_vGroups.m_pBlock[i];
        if (group != nullptr) DeleteRefGroup(group);
    }
    if (m_pGroup48 != nullptr) DeleteRefGroup(m_pGroup48);
}

// C2.8 port-all P18.
// 0x00464268 CKHkSequenceMgr_FreeBuffers_maybe
void CKHkSequenceMgr::VfC0() {
    for (uint32_t i = m_vEntries.m_ui32NbUsedElt; i != 0; --i) {
        SequenceEntry& entry = m_vEntries.m_pBlock[i - 1];
        TVector<ObjectRefRecord, 1>* records = entry.m_pvRecords;
        if (records->m_pBlock != nullptr) {
            Mem_FreeAligned16(records->m_pBlock);
            records->m_pBlock = nullptr;
        }
        records->m_pBlock = nullptr;
        records->m_ui32NbUsedElt = 0;
        TVector<EntryItem, 1>* items = entry.m_pvItems;
        if (items->m_pBlock != nullptr) {
            Mem_FreeAligned16(items->m_pBlock);
            items->m_pBlock = nullptr;
        }
        items->m_ui32NbUsedElt = 0;
        items->m_pBlock = nullptr;
        Mem_FreeAligned16(entry.m_pvRecords);
        Mem_FreeAligned16(entry.m_pvItems);
        entry.m_unkA8 = 0;
    }
    if (m_vEntries.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vEntries.m_pBlock);
        m_vEntries.m_pBlock = nullptr;
    }
    m_vEntries.m_ui32NbUsedElt = 0;
    m_vEntries.m_pBlock = nullptr;
}

// 0x00462930 CKHkSequenceMgr_GetInfo, with 0x009c4150 _GetTriggerProp15E_maybe (+0xd4 bit 0) and 0x009c4140 _GetResult
// (+0xec, an integer); TriggerPropertyRequest_SetGetter_maybe 0x38cd8 writes them. The actor base answers 1.
int32_t CKHkSequenceMgr::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    if (info->m_ui32Id == 0x15e) {
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<uint32_t>(static_cast<CKHkSequenceMgr*>(o)->m_unkD4 & 1u); }, 0);
    }
    if (info->m_ui32Id == 0x15f) {
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<CKHkSequenceMgr*>(o)->m_unkEC; }, 1);
    }
    return 1;
}

// 0x004657c0 CKHkSequenceMgr_StartSequenceWithListener_maybe (the golem QTE phase's Start)
void CKHkSequenceMgr::StartSequenceWithListener(IKSerializable* listener, IKTime* clock, int32_t index) {
    if (m_vEntries.m_ui32NbUsedElt == 0) return;  // +0x2c
    m_unk138 = listener;
    m_unkE8 = index;
    StartSequence(clock);  // 0x00465348
    m_unkD4 = static_cast<uint8_t>((m_unkD4 & 0xfeu) | 1u);
}

// 0x00463ef8 CKHkSequenceMgr_AbortForOwner_maybe (the golem QTE phase's vf58). No index test: the listener is only set
// by StartSequenceWithListener, and the paths that leave the index at -1 (messages 0x940 / 0x997, Restart) clear it.
void CKHkSequenceMgr::AbortForOwner(IKSerializable* owner) {
    if (m_unk138 != owner) return;
    StopCurrentSequence();  // 0x00463690
    DetachHeroes();         // 0x004621e0
    m_unkD4 = static_cast<uint8_t>(m_unkD4 & 0xfcu);
    m_unk138 = nullptr;
    m_unkE8 = -1;
}

// ---- C2.8 sequence: the engine ----

// 0x00465f18 CKHkSequenceMgr_OnActivate_maybe: the actor joins the active list; the node is hidden and, from the last
// entry back, the first record A with a dictionary that is not flagged +0x14 plays its first animation from 0; the
// run-time words reset (the items' ones too), the answer flashes forgotten, the icon sets released when the controlled
// hero count changed, every group's marked FX channels forgotten (ResetChannels) and no placement (+0x12c).
void CKHkSequenceMgr::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    CAnimatedNode* node = NodeOf(this);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    for (uint32_t i = m_vEntries.m_ui32NbUsedElt; i != 0; --i) {
        const CAnimationDictionary* dictionary = static_cast<const CAnimationDictionary*>(m_vEntries.m_pBlock[i - 1].m_recA.m_pRef);
        if (dictionary == nullptr || dictionary->m_unk14 != 0) continue;
        NodeOf(this)->PlayAnim(static_cast<double>(kZero), FirstWord(dictionary), 0);  // 0x000c98b8
        break;
    }
    m_unkE8 = -1;
    m_unkE1 = 0;
    m_apIconFx[0] = nullptr;
    m_apIconFx[1] = nullptr;
    m_unkF4 = 0;
    m_unkF8 = 0;
    m_unk138 = nullptr;
    m_unk118 = 0;
    m_unkE0 = 0;
    m_unkF0 = 0.0f;
    for (uint32_t i = m_vItems.m_ui32NbUsedElt; i != 0; --i) {
        MgrItem& item = m_vItems.m_pBlock[i - 1];
        item.m_pSavedParent = nullptr;
        item.m_pSavedMatrix = nullptr;
        item.m_pSlot = nullptr;
        if (item.m_unk4 != 0) item.m_pRef = nullptr;
    }
    m_unkD4 &= 0xf0;
    m_apIconDataFx[1] = nullptr;
    m_apIconDataFx[0] = nullptr;
    const uint8_t controlled = ControlledHeroCount();  // 0x002ca288
    if (m_unkE4 != controlled) {
        m_unkE4 = controlled;
        ReleaseIconSet(0);  // 0x00460b28
        ReleaseIconSet(1);
    }
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        static_cast<CKMarkedFX*>(m_vGroups.m_pBlock[i]->m_pRef0)->ResetChannels();  // 0x005cf1c0
        static_cast<CKMarkedFX*>(m_vGroups.m_pBlock[i]->m_pRef4)->ResetChannels();
        for (uint32_t j = 0; j < m_vItems.m_ui32NbUsedElt; ++j) {
            static_cast<CKMarkedFX*>(m_vGroups.m_pBlock[i]->m_vRefs.m_pBlock[j])->ResetChannels();
        }
    }
    m_pPlacement = nullptr;
}

// 0x00463f90 CKHkSequenceMgr_OnDeactivate: a running sequence stopped and its heroes released, then every group's
// marked FX channel effects stopped (StopAllChannelNodes_2).
void CKHkSequenceMgr::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    if ((m_unkD4 & 1u) != 0 && m_unkE8 != -1 && static_cast<int32_t>(m_vEntries.m_ui32NbUsedElt) > m_unkE8) {
        StopCurrentSequence();  // 0x00463690
        DetachHeroes();         // 0x004621e0
    }
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        static_cast<CKMarkedFX*>(m_vGroups.m_pBlock[i]->m_pRef0)->StopAllChannelNodes2();  // 0x005cfb70
        static_cast<CKMarkedFX*>(m_vGroups.m_pBlock[i]->m_pRef4)->StopAllChannelNodes2();
        for (uint32_t j = 0; j < m_vItems.m_ui32NbUsedElt; ++j) {
            static_cast<CKMarkedFX*>(m_vGroups.m_pBlock[i]->m_vRefs.m_pBlock[j])->StopAllChannelNodes2();
        }
    }
}

// 0x00465898 CKHkSequenceMgr_MessageProc
int32_t CKHkSequenceMgr::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0x996) {
        own = 0;
        if ((m_unkD4 & 1u) == 0) {
            m_unkE8 = 0;  // stw of the clear bit 0
            StartSequence(g_pEngine->m_timeManager->m_pTime);  // 0x00465348 (engine +0x48 -> +0x04)
            m_unkD4 = static_cast<uint8_t>((m_unkD4 & 0xfeu) | 1u);
        }
    } else if (message == 0x940) {
        if (m_unkE8 != -1) StopCurrentSequence();  // 0x00463690
        m_unkD4 = static_cast<uint8_t>(m_unkD4 & 0xfcu);
        IKSerializable* listener = m_unk138;
        m_unkE8 = -1;
        m_unk130 = 1;
        if (listener != nullptr) listener->MessageProc(0x940, data);  // vt+0x1c
        own = 0;
        m_unk138 = nullptr;
    } else if (message == 0x997) {
        StopCurrentSequence();  // 0x00463690
        own = 0;
        m_unkD4 = static_cast<uint8_t>(m_unkD4 & 0xfcu);
        m_unkE8 = -1;
        m_unk138 = nullptr;
    } else if (message == 0x998) {
        own = 1;
        m_pPlacement = *static_cast<const IKSerializable* const*>(data);
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x00465348 CKHkSequenceMgr_StartSequence_maybe
void CKHkSequenceMgr::StartSequence(IKTime* clock) {
    SequenceEntry& entry = CurrentEntry();
    m_unk13c[0] = 0;
    m_unk13c[2] = 0;
    m_unk13c[1] = 0;
    m_unk13c[3] = 0;
    m_unkF0 = clock->m_afCurrentTime[0];  // +0x04
    m_unk118 = 0;
    entry.m_inputWindow.m_ui8Fired = 0;    // +0x94
    entry.m_triggerWindow.m_ui8Fired = 0;  // +0xa4
    m_unkF4 = static_cast<int32_t>(entry.m_stepParams.m_unk10);
    m_unkF8 = static_cast<int32_t>(entry.m_stepParams.m_unk10);
    BeginEntryAnimAndCamera();  // 0x004644a8
    StartActorAnims();          // 0x00464f78
    if (HeroGroup() != nullptr) SetupHeroesForSequence();  // 0x00464b38
    for (uint32_t i = entry.m_pvItems->m_ui32NbUsedElt; i != 0; --i) {
        entry.m_pvItems->m_pBlock[i - 1].m_window.m_ui8Fired = 0;
    }
    // The ground under the node (one point, the probe's defaults with a 0.2 step): a moving one (IsKindOf 0x4cc) and the
    // node's point on it are kept for Update.
    CGroundContactDatasIn in;
    in.m_fDeltaMax = 2.0e-1f;  // TOC +0x5740
    in.m_fObjectHeight = 0.0f;
    CGroundContactDatasInOut contact;
    const RwV3d& at = NodeOf(this)->m_pRwFrame->ltm.pos;
    const float point[3] = {at.x, at.y, at.z};
    m_pGround = nullptr;
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&in, &contact, point, 1);  // 0x00196540
    if (contact.m_eContactStatus != 3 && contact.m_pGround->IsKindOfClass(0x4cc) != 0) {  // vt+0x08
        m_pGround = contact.m_pGround;
        m_v3GroundPoint = contact.m_ProjectionOnGround;
    }
    // (KStub_Nop_5cebf0 on the entry's group of marked FX: empty.)
    AdvanceStepAnim(clock);  // 0x004640f0
    m_unkE1 = 0;
    m_unkE0 = 0;
}

// 0x004644a8 CKHkSequenceMgr_BeginEntryAnimAndCamera_maybe: record A is played (the node hidden first): without a
// dictionary the camera is not owned; with one the node is shown, the camera told vt+0x9c(0), the listener asked
// (request 3), the node updated (vt+0x50) and, if it plays, its animation started (a crossfade of the record's blend, or
// cut) and, unless +0xd4 bit 1, the manager owns the camera and the service switches to the sequence's camera. Then a
// placement from message 0x998 sets the node's local matrix.
void CKHkSequenceMgr::BeginEntryAnimAndCamera() {
    SequenceEntry& entry = CurrentEntry();
    CKSrvCamera* service = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);  // +0x70
    ObjectRefRecord& record = entry.m_recA;
    record.m_ui8Playing = 1;
    CAnimatedNode* node = NodeOf(this);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    IKSerializable* dictionary = record.m_pRef;
    if (dictionary == nullptr) {
        RemoveCameraOwner(service, this);
    } else {
        static_cast<IKCamera*>(m_unk4c)->Vf9C(0);  // vt+0x9c
        NodeOf(this)->m_sgProperties &= 0xfffffffbu;
        SCameraQuery query;
        query.m_pCamera = m_unk4c;
        query.m_pNode = m_pKGLObject;
        query.m_ui8Play = 1;
        if (m_unk138 != nullptr) AskListener(this, 3, &query);
        record.m_ui8Playing = query.m_ui8Play;
        NodeOf(this)->ForceWorldMatrixUpdate();  // vt+0x50
        if (query.m_ui8Play != 0) {
            CAnimatedNode* played = static_cast<CAnimatedNode*>(query.m_pNode);
            if (record.m_fBlend > kZero) {
                played->CrossfadeToAnim(static_cast<double>(record.m_fBlend), static_cast<double>(kZero), FirstWord(dictionary), 2);  // 0x000c8eb0
            } else {
                played->PlayAnim(static_cast<double>(kZero), FirstWord(dictionary), 0);  // 0x000c98b8
            }
            if ((m_unkD4 & 2u) == 0) {
                AddCameraOwner(service, this);
                if (service->m_pCurrentCamera != query.m_pCamera) {
                    service->m_pNextCamera = static_cast<IKCamera*>(query.m_pCamera);
                    service->m_ui8TransitionMode = 0;
                    service->m_fSwitchTimer = 0.0f;
                    service->m_baTemporaryFlags = ((service->m_baTemporaryFlags & 0xffbfffffu) | 0x400000u) & 0xffffffcfu;
                }
            }
        }
    }
    if (m_pPlacement != nullptr) {
        const CKMarkerBeacon* placement = static_cast<const CKMarkerBeacon*>(m_pPlacement);
        alignas(16) CMatrix34 matrix;
        Quat_ToMatrixNormalizing(placement->m_qOrientation, &matrix);  // 0x00241d78 (+0x10)
        matrix.m_pos = placement->m_v3Position;                        // +0x04
        matrix.m_ui32Flags &= 0xfffdffffu;
        NodeOf(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
    }
}

// 0x00464f78 CKHkSequenceMgr_StartActorAnims_maybe: every item (last first) asks the listener for its node and blend
// slot (request 2), keeps them and plays the entry's record of its index on them (crossfade or cut; a slot's blender
// weight follows its active controller), keeps the node's parent and modelling matrix and attaches it to the record's
// target. A record without a dictionary only hides the node (+0x00 set).
void CKHkSequenceMgr::StartActorAnims() {
    SequenceEntry& entry = CurrentEntry();
    for (uint32_t i = m_vItems.m_ui32NbUsedElt; i != 0; --i) {
        MgrItem& item = m_vItems.m_pBlock[i - 1];
        SItemQuery query;
        query.m_ui8Play = 1;
        query.m_ui32Word = item.m_unk8;
        query.m_pNode = item.m_pRef;
        query.m_pSlot = nullptr;
        if (m_unk138 != nullptr) AskListener(this, 2, &query);
        item.m_pRef = query.m_pNode;
        item.m_pSlot = query.m_pSlot;
        if (query.m_pNode == nullptr) query.m_ui8Play = 0;
        ObjectRefRecord& record = entry.m_pvRecords->m_pBlock[i - 1];
        record.m_ui8Playing = query.m_ui8Play;
        if (query.m_ui8Play == 0) continue;
        CAnimatedNode* node = static_cast<CAnimatedNode*>(item.m_pRef);
        if (record.m_pRef == nullptr) {
            if (record.m_unk0 != 0) node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
            continue;
        }
        const uint32_t word = FirstWord(record.m_pRef);
        if (record.m_fBlend > kZero) {
            if (item.m_pSlot != nullptr) {
                item.m_pSlot->CrossfadeToAnim(static_cast<double>(record.m_fBlend), static_cast<double>(kZero), word, 2);  // 0x00079ea0
            } else {
                node->CrossfadeToAnim(static_cast<double>(record.m_fBlend), static_cast<double>(kZero), word, 2);  // 0x000c8eb0
            }
        } else if (item.m_pSlot != nullptr) {
            AnimBlendSlot* slot = item.m_pSlot;
            slot->m_unk14 = 0;
            if (slot->m_pController != nullptr) {
                static_cast<CKBlenderController*>(slot->m_pController)->m_unk58 = slot->m_unk10 != 0 ? kOne : kZero;
            }
            SlotController(slot)->SetAnim(kZero, word, false);  // 0x0007ab20
        } else {
            node->PlayAnim(static_cast<double>(kZero), word, 0);  // 0x000c98b8
        }
        item.m_pSavedParent = node->m_pParent;  // +0x0c
        CMatrix34* saved = RwMatrixCreate_Thunk();  // 0x0023fa68
        item.m_pSavedMatrix = saved;
        std::memcpy(saved, &node->m_pRwFrame->modelling, sizeof(CMatrix34));
        AttachActorToHotSpot(node, record.m_i32Target, record.m_i32HotSpot);  // 0x00464858
    }
}

// 0x00464b38 CKHkSequenceMgr_SetupHeroesForSequence_maybe: for heroes 1 and 0 (records C and B): without a dictionary a
// record +0x00 hides the hero and holds it, else lets it go; with one the listener may substitute the hero or refuse
// (request 1), the hero is held, plays the animation (vt+0xc4 crossfade / vt+0xc0) and is attached to the target.
void CKHkSequenceMgr::SetupHeroesForSequence() {
    SequenceEntry& entry = CurrentEntry();
    CKGrpS08Hero* group = HeroGroup();
    for (int32_t i = SequenceHeroCount(group) - 1; i != -1; --i) {
        ObjectRefRecord& record = i == 0 ? entry.m_recB : entry.m_recC;
        record.m_ui8Playing = 1;
        if (record.m_pRef == nullptr) {
            CKHkS08Hero* hero = HeroAt(HeroGroup(), static_cast<uint32_t>(i));
            if (record.m_unk0 == 0) {
                if (hero->GetAttachedObject() == this) ReleaseHero(hero, false);
            } else {
                CAnimatedNode* node = HeroNode(hero);
                node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
                if (hero->GetAttachedObject() != this) HoldHero(hero, this);
            }
            continue;
        }
        SHeroQuery query;
        query.m_pHero = HeroAt(HeroGroup(), static_cast<uint32_t>(i));
        query.m_ui8Play = 1;
        if (m_unk138 != nullptr) AskListener(this, 1, &query);
        record.m_ui8Playing = query.m_ui8Play;
        if (query.m_ui8Play == 0) continue;
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(query.m_pHero);
        if (hero->GetAttachedObject() != this) HoldHero(hero, this);
        if (record.m_fBlend > kZero) {
            hero->CrossfadeAnimResource(record.m_fBlend, kZero, FirstWord(record.m_pRef), 2);  // vt+0xc4
        } else {
            hero->PlayAnimResource(kZero, FirstWord(record.m_pRef));  // vt+0xc0
        }
        AttachActorToHotSpot(HeroNode(hero), record.m_i32Target, record.m_i32HotSpot);  // 0x00464858
    }
}

// 0x00464858 CKHkSequenceMgr_AttachActorToHotSpot_maybe: the actor leaves its parent (when the target is shown) and
// hangs under the target (-1 / 0 the node, 1-2 a hero's node, 3+ an item's node) or under its hot spot `hotSpot`; a
// listener's item node may be given another parent or a hot spot (request 6). Its local matrix becomes the identity,
// except when it hangs on a hot spot's volume or the target is hidden.
void CKHkSequenceMgr::AttachActorToHotSpot(CSGLeaf* actor, int32_t target, int32_t hotSpot) {
    MgrItem* item = nullptr;
    CAnimatedNode* parent;
    if (static_cast<uint32_t>(target + 1) <= 1) {
        parent = NodeOf(this);
    } else if (target <= 2) {
        parent = nullptr;
        CKGrpS08Hero* group = HeroGroup();
        if (group != nullptr) parent = HeroNode(HeroAt(group, static_cast<uint32_t>(target - 1)));
    } else {
        item = &m_vItems.m_pBlock[target - 3];
        parent = static_cast<CAnimatedNode*>(item->m_pRef);
    }
    CSGBranch* old = actor->m_pParent;
    if (old != nullptr && (parent->m_sgProperties & 4u) == 0) old->RemoveChild(actor);  // vt+0x78
    if (hotSpot == -1) {
        if ((parent->m_sgProperties & 4u) != 0) return;
        parent->AddChild(actor);  // vt+0x70
        static_cast<CSGMovable*>(actor)->SetIdentity();  // 0x000d08f0
        return;
    }
    if ((parent->m_sgProperties & 4u) != 0) return;
    CSGBranch* under;
    if (item != nullptr && item->m_unk4 != 0 && m_unk138 != nullptr) {
        SHotSpotQuery query;
        query.m_pNode = item->m_pRef;
        query.m_i32HotSpot = hotSpot;
        query.m_pParent = nullptr;
        query.m_pHotSpot = nullptr;
        AskListener(this, 6, &query);
        if (query.m_pHotSpot != nullptr) {
            static_cast<CSGHotSpot*>(query.m_pHotSpot)->AttachVolume(actor);  // 0x000ce2b8
            return;
        }
        under = static_cast<CSGBranch*>(query.m_pParent);
        if (under == nullptr) {
            static_cast<CSGMovable*>(actor)->SetIdentity();
            return;
        }
    } else {
        // DOTD: the 50 slots start null (the original's stack is not cleared; an index past the hot spots reads it).
        CSGLeaf* hotSpots[50] = {};
        parent->GetHotSpots(hotSpots, 50);  // vt+0x64
        under = static_cast<CSGBranch*>(hotSpots[hotSpot]);
    }
    under->AddChild(actor);  // vt+0x70
    static_cast<CSGMovable*>(actor)->SetIdentity();  // 0x000d08f0
}

// 0x00463690 CKHkSequenceMgr_StopCurrentSequence_maybe
void CKHkSequenceMgr::StopCurrentSequence() {
    SequenceEntry& entry = CurrentEntry();
    entry.m_inputWindow.m_ui8Fired = 0;
    entry.m_triggerWindow.m_ui8Fired = 0;
    for (uint32_t i = entry.m_pvItems->m_ui32NbUsedElt; i != 0; --i) {
        EntryItem& sound = entry.m_pvItems->m_pBlock[i - 1];
        sound.m_window.m_ui8Fired = 0;
        CKSound* playing = CKSoundDictionaryID_GetSound(static_cast<CKSoundDictionaryID*>(sound.m_pRef), 0);  // 0x00112bc0
        if (playing != nullptr && (playing->m_SoundFlags & 2u) != 0) Sound_Stop(playing, 0);  // 0x001111b0
    }
    // The items: shown, and those that played put back under their old parent with their old matrix.
    for (uint32_t i = m_vItems.m_ui32NbUsedElt; i != 0; --i) {
        MgrItem& item = m_vItems.m_pBlock[i - 1];
        const ObjectRefRecord& record = entry.m_pvRecords->m_pBlock[i - 1];
        if (item.m_pRef != nullptr) {
            CSGLeaf* node = static_cast<CSGLeaf*>(item.m_pRef);
            node->m_sgProperties &= 0xfffffffbu;
        }
        if (record.m_pRef == nullptr || record.m_ui8Playing == 0) continue;
        if (item.m_pSavedParent == nullptr || item.m_pSavedMatrix == nullptr) continue;
        CSGLeaf* node = static_cast<CSGLeaf*>(item.m_pRef);
        if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
        item.m_pSavedParent->AddChild(node);  // vt+0x70
        static_cast<CSGMovable*>(node)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(item.m_pSavedMatrix));  // 0x000d0be8
        if (m_unk138 != nullptr && m_unk138->IsKindOfClass(0x1402) != 0 && (NodeOf(this)->m_sgProperties & 4u) == 0) {
            item.m_pSavedParent->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&NodeOf(this)->m_pRwFrame->ltm));
        }
        RwMatrixDestroy_Thunk(item.m_pSavedMatrix);  // 0x0023f968
        item.m_pSavedParent = nullptr;
        item.m_pSavedMatrix = nullptr;
    }
    // The heroes: shown and released; one that played is put at its body hot spot (hot spot 0) under the dynamic scene.
    CKGrpS08Hero* group = HeroGroup();
    if (group != nullptr) {
        for (int32_t i = SequenceHeroCount(group) - 1; i != -1; --i) {
            CKHkS08Hero* hero = HeroAt(group, static_cast<uint32_t>(i));
            CAnimatedNode* node = HeroNode(hero);
            node->m_sgProperties &= 0xfffffffbu;
            if (hero->GetAttachedObject() == this) ReleaseHero(hero, true);
            const ObjectRefRecord& record = i == 0 ? entry.m_recB : entry.m_recC;
            if (record.m_pRef == nullptr || record.m_ui8Playing == 0) continue;
            alignas(16) CMatrix34 world;
            static_cast<CSGHotSpot*>(hero->GetHotSpot(0))->GetWorldMatrix(&world);  // 0x00361b70, 0x000ce970
            if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
            static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChildKeepWorldTransform(node);  // vt+0x74
            node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&world));  // 0x000d0be8
            if (hero->GetAttachedObject() == this) ReleaseHero(hero, true);
        }
    }
    if (entry.m_recA.m_pRef != nullptr && entry.m_recA.m_ui8Playing != 0) {
        RemoveCameraOwner(static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera), this);
    }
    for (uint32_t i = m_vEntries.m_ui32NbUsedElt; i != 0; --i) {
        RefGroup* refs = m_vGroups.m_pBlock[i - 1];
        static_cast<CKMarkedFX*>(refs->m_pRef4)->StopFlaggedChannelNodes();  // 0x005ceec0
        static_cast<CKMarkedFX*>(refs->m_pRef0)->StopFlaggedChannelNodes();
        for (uint32_t j = 0; j < m_vItems.m_ui32NbUsedElt; ++j) {
            static_cast<CKMarkedFX*>(m_vGroups.m_pBlock[i - 1]->m_vRefs.m_pBlock[j])->StopFlaggedChannelNodes();
        }
    }
    ReleaseIconSet(0);  // 0x00460b28
    ReleaseIconSet(1);
    // (KStub_Nop_5cebf8 on the entry's group of marked FX: empty.)
}

// 0x00461050 CKHkSequenceMgr_IsStepForPlayer_maybe: with one controlled hero player 0 answers; with two the entry's
// dragon (+0xb1: 2 either player) answers for the player who controls it (0x00362ac8 GetPlayerIndexIfControlled).
uint8_t CKHkSequenceMgr::IsStepForPlayer(int32_t player) {
    const uint32_t count = m_unkE4;
    if (count == 1) return player == 0 ? 1 : 0;
    if (count != 2) return 0;
    const uint8_t dragon = CurrentEntry().m_unkB1;
    if (dragon == 2) return 1;
    if (dragon > 1) return 0;
    CKHkS08Hero* hero = HeroAt(HeroGroup(), dragon);
    int8_t index = static_cast<int8_t>(hero->m_ui8Hero == hero->m_ui8TrackedLeader ? hero->m_ui8Leader : 0xff);
    if (index == 0) return player == 0 ? 1 : 0;
    hero = HeroAt(HeroGroup(), dragon);
    index = static_cast<int8_t>(hero->m_ui8Hero == hero->m_ui8TrackedLeader ? hero->m_ui8Leader : 0xff);
    if (index != 1) return 0;
    return player != 0 ? 1 : 0;
}

// 0x00461178 CKHkSequenceMgr_CheckStepWindow_maybe: the time since the step started against `window` (scaled by the
// actor animation's duration over the entry's speed; a type 3 step whose inputs are done uses the second speed): 1, and
// the window's fired byte set, inside it. The PPC compares kept: mode 0 / 1 `bne` on cror lt|eq (start <= t) then `ble`
// (no NaN), mode 2 cror gt|eq then `bgt`.
uint8_t CKHkSequenceMgr::CheckStepWindow(IKTime* clock, StepWindow* window) {
    SequenceEntry& entry = CurrentEntry();
    const int32_t actor = entry.m_unkA8;
    const uint8_t forPlayer0 = IsStepForPlayer(0);
    const uint8_t forPlayer1 = IsStepForPlayer(1);
    if (actor < 0) return 0;
    const ObjectRefRecord* record = entry.ActorRecord(actor);
    RtAnimAnimation* animation = record->m_pRef != nullptr ? CAnimationManager_GetAnimation(FirstWord(record->m_pRef)) : nullptr;
    const float start = m_unkF0;
    float speed = entry.m_unk0;
    if (entry.m_stepParams.m_unk0 == 3) {
        const bool pressing = (forPlayer0 != 0 && m_unkF4 != 0) || (forPlayer1 != 0 && m_unkF8 != 0);
        if (!pressing) speed = entry.m_unk4;
    }
    float elapsed;
    float duration;
    if (animation != nullptr) {
        elapsed = clock->m_afCurrentTime[0] - start;
        duration = animation->duration / speed;  // fdivs
    } else {
        elapsed = kZero - start;  // BUG(original): without an animation the clock is not read
        duration = kZero;
    }
    const uint8_t mode = window->m_ui8Mode;
    if (mode == 1) {
        const float from = duration - window->m_fStart;
        if (!(from < elapsed || from == elapsed)) return 0;
        if (!(duration > elapsed)) return 0;
        window->m_ui8Fired = mode;  // stb of the mode byte (1)
        return 1;
    }
    if (mode < 1) {
        if (!(window->m_fStart < elapsed || window->m_fStart == elapsed)) return 0;
        if (!(duration > elapsed)) return 0;
        window->m_ui8Fired = 1;
        return 1;
    }
    if (mode == 2) {
        if (!(elapsed > window->m_fStart || elapsed == window->m_fStart)) return 0;
        if (!(window->m_fStart + window->m_fLength > elapsed)) return 0;
        window->m_ui8Fired = 1;
        return 1;
    }
    return 0;
}

// 0x004640f0 CKHkSequenceMgr_AdvanceStepAnim_maybe: the frame time scaled by the entry's speed (the second one for a
// type 3 step whose inputs are done) advances the node's animation (record A with an animation: unless it reached its
// end and does not loop) and the camera, then the heroes' and the items'.
void CKHkSequenceMgr::AdvanceStepAnim(IKTime* clock) {
    float dt = clock->m_afDeltaTime[0];  // +0x1c
    SequenceEntry& entry = CurrentEntry();
    const uint8_t forPlayer0 = IsStepForPlayer(0);
    const uint8_t forPlayer1 = IsStepForPlayer(1);
    float speed = entry.m_unk0;
    if (entry.m_stepParams.m_unk0 == 3 && (forPlayer0 == 0 || m_unkF4 == 0) && (forPlayer1 == 0 || m_unkF8 == 0)) {
        speed = entry.m_unk4;
    }
    dt = dt * speed;
    const ObjectRefRecord& record = CurrentEntry().m_recA;
    if (RecordHasAnim(record)) {
        CAnimatedNode* node = NodeOf(this);
        if (!node->IsAnimEndReached(static_cast<double>(dt)) || record.m_ui8Loop != 0) {  // 0x000ca368
            node->AddAnimTime(static_cast<double>(dt));  // 0x000c9638
        }
        UpdateCameraFromHotSpots();  // 0x00461658
    }
    AdvanceAttachedHeroesAnim(dt);  // 0x00461960
    AdvanceStepObjectsAnim(dt);     // 0x00462d48
}

// 0x00461658 CKHkSequenceMgr_UpdateCameraFromHotSpots_maybe: with an evaluated animation, the camera takes the position
// and target of hot spots 0 / 1 (unless they coincide), the fov of a lens whose focal length is hot spot 2's height
// above the node (2 atan(0.7085 / (focal x 0.03937)) in degrees; 70 below 1) and the roll of hot spot 3's (vt+0x88).
void CKHkSequenceMgr::UpdateCameraFromHotSpots() {
    CAnimatedNode* node = NodeOf(this);
    if (node->ActiveController()->m_unk5c == nullptr) return;  // 0x000c9720 GetActiveAnim_maybe
    node->ForceWorldMatrixUpdate();  // vt+0x50
    CVector3 spot[5];
    static_cast<CSGHotSpot*>(m_apUnkC0[4])->GetWorldPosition(&spot[4]);  // 0x000ce790
    static_cast<CSGHotSpot*>(m_apUnkC0[3])->GetWorldPosition(&spot[3]);
    static_cast<CSGHotSpot*>(m_apUnkC0[2])->GetWorldPosition(&spot[2]);
    static_cast<CSGHotSpot*>(m_apUnkC0[1])->GetWorldPosition(&spot[1]);
    static_cast<CSGHotSpot*>(m_apUnkC0[0])->GetWorldPosition(&spot[0]);
    IKCamera* camera = static_cast<IKCamera*>(m_unk4c);
    const bool same = spot[1].x == spot[0].x && spot[0].y == spot[1].y && spot[0].z == spot[1].z;
    if (!same) {
        camera->m_WorldPosition = spot[0];  // +0x20
        camera->m_WorldTarget = spot[1];    // +0x2c
    }
    const float base = NodeOf(this)->m_pRwFrame->ltm.pos.y;  // frame +0x84
    float fov = crt::Atanf(7.085000276565552e-1f / ((spot[2].y - base) * 3.937000036239624e-2f)) * 1.1459156036376953e2f;
    if (!same) {
        if (fov < kOne) fov = 70.0f;  // blt: a NaN stays
    } else if (!(fov >= kOne)) {
        fov = 70.0f;                  // bge: a NaN becomes 70
    }
    camera->m_unk18 = fov;
    camera->Vf88(spot[3].y - base);  // vt+0x88
}

// 0x00461960 CKHkSequenceMgr_AdvanceAttachedHeroesAnim_maybe: the heroes held by the manager whose record has an
// animation advance it (IKHkHero_AdvanceObjectAnimTime) unless it ends within `dt` and does not loop.
void CKHkSequenceMgr::AdvanceAttachedHeroesAnim(float dt) {
    CKGrpS08Hero* group = HeroGroup();
    if (group == nullptr) return;
    for (int32_t i = SequenceHeroCount(group) - 1; i != -1; --i) {
        CKHkS08Hero* hero = HeroAt(group, static_cast<uint32_t>(i));
        const ObjectRefRecord& record = i == 0 ? CurrentEntry().m_recB : CurrentEntry().m_recC;
        if (!RecordHasAnim(record)) continue;
        if (hero->GetAttachedObject() != this) continue;
        if (hero->WillAnimEndWithin(dt) != 0 && record.m_ui8Loop == 0) continue;  // 0x00364020
        hero->AdvanceObjectAnimTime(dt);  // 0x00363410
    }
}

// 0x00462d48 CKHkSequenceMgr_AdvanceStepObjectsAnim_maybe: each item whose record has an animation advances its node's
// (or its blend slot's active controller's: Anim_GetDuration's end test inlined) unless it ends within `dt` and does not
// loop; a controller without an animation always advances.
void CKHkSequenceMgr::AdvanceStepObjectsAnim(float dt) {
    for (uint32_t i = m_vItems.m_ui32NbUsedElt; i != 0; --i) {
        const ObjectRefRecord& record = CurrentEntry().m_pvRecords->m_pBlock[i - 1];
        if (!RecordHasAnim(record)) continue;
        const MgrItem& item = m_vItems.m_pBlock[i - 1];
        if (item.m_pRef == nullptr) continue;
        if (item.m_pSlot != nullptr) {
            CKAnmKeyFrameController* controller = SlotController(item.m_pSlot);
            if (controller->m_unk58 != nullptr && controller->HasEnded(dt) && record.m_ui8Loop == 0) continue;
            controller->m_unk50 = dt + controller->m_unk50;
            continue;
        }
        CAnimatedNode* node = static_cast<CAnimatedNode*>(item.m_pRef);
        if (node->IsAnimEndReached(static_cast<double>(dt)) && record.m_ui8Loop == 0) continue;  // 0x000ca368
        node->AddAnimTime(static_cast<double>(dt));  // 0x000c9638
    }
}

// 0x00462078 CKHkSequenceMgr_UpdateSoundTriggers_maybe: each sound of the entry (last first) starts when its window
// opens and is stopped (when playing) once it was open and is no longer.
void CKHkSequenceMgr::UpdateSoundTriggers(IKTime* clock) {
    SequenceEntry& entry = CurrentEntry();
    for (uint32_t i = entry.m_pvItems->m_ui32NbUsedElt; i != 0; --i) {
        EntryItem& sound = entry.m_pvItems->m_pBlock[i - 1];
        const uint8_t fired = sound.m_window.m_ui8Fired;
        CKSoundDictionaryID* dictionary = static_cast<CKSoundDictionaryID*>(sound.m_pRef);
        if (CheckStepWindow(clock, &sound.m_window) != 0) {
            if (fired != 0) continue;
            CKSound* playing = CKSoundDictionaryID_GetSound(dictionary, 0);  // 0x00112bc0
            if (playing != nullptr) CKSound_Play(kZero, playing);           // 0x00111230
            continue;
        }
        if (fired == 0) continue;
        CKSound* playing = CKSoundDictionaryID_GetSound(dictionary, 0);
        if (playing != nullptr && (playing->m_SoundFlags & 2u) != 0) Sound_Stop(playing, 0);  // 0x001111b0
    }
}

// 0x00469960 CKHkSequenceMgr_UpdateStep_maybe (from the disassembly: the decompiler drops the input section's paths).
// Types 0 / 3: the actor's animation reaching its end (`dt` x the speed) ends the step (type 3 also runs the inputs).
// Types 1 / 3: inside the input window the action (the entry's +0x78) pressed counts for the player (OnCorrectInput,
// +0xf4 / +0xf8 down to 0), any other of the actions 2..8 (or a pending dragon switch) is wrong when the listener lets it
// (request 7: OnWrongInput, -1, and with the switch the step fails); the icons follow; leaving the window without the
// input fires +0x80 and fails the step unless +0xd4 bit 2. Type 2 ends when its window has fired and closed.
uint8_t CKHkSequenceMgr::UpdateStep(IKTime* clock, uint8_t* failed) {
    *failed = 0;
    SequenceEntry& entry = CurrentEntry();
    const float frameDt = clock->m_afDeltaTime[0];  // +0x1c
    float speed;
    if (CurrentEntry().m_stepParams.m_unk0 == 3 && m_unkF4 == 0 && (m_unkE4 == 1 || (m_unkE4 == 2 && m_unkF8 == 0))) {
        speed = entry.m_unk4;
    } else {
        speed = entry.m_unk0;
    }
    const float dt = frameDt * speed;  // f31
    uint8_t ended = 0;  // r22
    uint8_t forPlayer0 = 0;
    uint8_t forPlayer1 = 0;
    uint8_t type = entry.m_stepParams.m_unk0;
    if (type == 0 || type == 3) {
        const int32_t actor = entry.m_unkA8;
        if (actor < 0) {
            ended = 0;
        } else if (actor == 0) {
            ended = NodeOf(this)->IsAnimEndReached(static_cast<double>(dt)) ? 1 : 0;  // 0x000ca368
        } else if (actor <= 2) {
            CKGrpS08Hero* group = HeroGroup();
            ended = 0;
            if (group != nullptr) {
                const uint32_t dragon = static_cast<uint32_t>(actor - 1) & 0xffu;
                if (HeroAt(group, dragon)->GetAttachedObject() == this) {
                    ended = HeroAt(group, dragon)->WillAnimEndWithin(dt);  // 0x00364020
                }
            }
        } else {
            const MgrItem& item = m_vItems.m_pBlock[actor - 3];
            if (item.m_pSlot == nullptr) {
                ended = static_cast<CAnimatedNode*>(item.m_pRef)->IsAnimEndReached(static_cast<double>(dt)) ? 1 : 0;
            } else {
                CKAnmKeyFrameController* controller = SlotController(item.m_pSlot);
                ended = controller->m_unk58 != nullptr && controller->HasEnded(dt) ? 1 : 0;  // Anim_GetDuration inlined
            }
        }
        if (entry.m_stepParams.m_unk0 != 3) return ended;
    }
    forPlayer0 = IsStepForPlayer(0);  // r28 / r19
    forPlayer1 = IsStepForPlayer(1);  // r21 / r29
    type = entry.m_stepParams.m_unk0;
    if (type == 1 || type == 3) {
        uint8_t d4 = m_unkD4;
        if (CheckStepWindow(clock, &entry.m_inputWindow) == 0 && ((d4 = m_unkD4) & 4u) == 0) {
            // Outside the input window.
            if (entry.m_inputWindow.m_ui8Fired == 0) goto tail;
            type = entry.m_stepParams.m_unk0;
            if (type == 3 || type == 1) {
                if (m_unkF4 == 0 || m_unkF8 == 0) {
                    if (type != 3) {
                        ReleaseIconSet(0);  // 0x00460b28
                        ReleaseIconSet(1);
                        if ((forPlayer0 != 0 && m_unkF4 != 0) || (forPlayer1 != 0 && m_unkF8 != 0)) {
                            d4 = m_unkD4;
                            goto closeWindow;
                        }
                        return 1;
                    }
                    if (ended != 0) {
                        ReleaseIconSet(0);
                        ReleaseIconSet(1);
                    }
                    if ((forPlayer0 != 0 && m_unkF4 != 0) || (forPlayer1 != 0 && m_unkF8 != 0)) {
                        d4 = m_unkD4;
                        goto closeWindow;
                    }
                    return ended;
                }
            }
        closeWindow:
            if ((d4 & 4u) == 0) {
                QueueTriggerSignals(&m_unk80);  // 0x00236338
                *failed = 1;
                ReleaseIconSet(0);
                ReleaseIconSet(1);
                return 1;
            }
            entry.m_inputWindow.m_ui8Fired = 0;
            goto tail;
        }
        // Inside the input window (or +0xd4 bit 2): the inputs.
        CDefaultGameManager* manager = GameManager();
        const uint8_t action = static_cast<uint8_t>(entry.m_stepParams.m_unkC);  // lbz +0x7b
        const uint8_t pressed0 = manager->IsActionPressed(action, 0);  // vt+0x160
        const uint8_t pressed1 = manager->IsActionPressed(action, 1);
        // r16: player 1's press counts (with one controlled hero this is 1 whatever was pressed).
        uint8_t counts1;
        if (pressed1 != 0 && m_unkE4 == 2) {
            counts1 = 1;
        } else {
            counts1 = m_unkE4 == 1 ? 1 : 0;
        }
        for (int32_t player = 0; player < 2; ++player) {
            if (player == 0) {
                if (forPlayer0 == 0) continue;
            } else if (forPlayer1 == 0 || m_unkE4 != 2) {
                continue;
            }
            int32_t& left = player == 0 ? m_unkF4 : m_unkF8;
            const bool correct = player == 0 ? pressed0 != 0 : counts1 != 0;
            if (correct) {
                if (left == -1) continue;
                if (left != 0) left = left - 1;
                OnCorrectInput(player);  // 0x00468f10
                continue;
            }
            if (left == 0) continue;
            // Any other action of 2..8 (in order, the step's own skipped) pressed, or a pending dragon switch, is wrong.
            CDefaultGameManager* gm = GameManager();
            const uint32_t own = CurrentEntry().m_stepParams.m_unkC;
            bool wrong = false;
            for (uint32_t other = 2; other <= 8; ++other) {
                if (other == own) continue;
                if (gm->IsActionPressed(other, static_cast<uint8_t>(player)) != 0) {
                    wrong = true;
                    break;
                }
            }
            if (!wrong && (m_unkD4 & 8u) == 0) continue;
            uint8_t counts = 1;
            if (m_unk138 != nullptr) {
                AskListener(this, 7, &counts);
                if (counts == 0) continue;
            }
            OnWrongInput(player);  // 0x00467bc8
            left = -1;
            if ((m_unkD4 & 8u) != 0) {
                m_unkD4 = static_cast<uint8_t>(m_unkD4 & 0xf7u);
                *failed = 1;
                return 1;
            }
        }
        // 0x00469fd8: the icons, and a type 3 step's sound and icon release once its inputs are done.
        if (m_unkF4 == 0 || m_unkF8 == 0) {
            if (entry.m_stepParams.m_unk0 == 3) {
                if (m_unk118 == 0) {
                    m_unk118 = 1;
                    PlaySound(m_unk20, 0);
                }
                if (CurrentEntry().m_stepParams.m_unk10 <= 1) {
                    if (forPlayer0 != 0 && m_unkF4 == 0) ReleaseIconSet(0);
                    if (forPlayer1 != 0 && m_unkF8 == 0) ReleaseIconSet(1);
                }
                if (forPlayer0 != 0 && m_unkF4 != 0) goto icons0;
                if (forPlayer1 == 0 || m_unkF8 == 0) return ended;
            }
            if (forPlayer0 != 0 && m_unkF4 != 0) goto icons0;
            if (forPlayer1 == 0 || m_unkF8 == 0) return 1;
        } else if (forPlayer0 != 0 && m_unkF4 != 0) {
            goto icons0;
        }
        // 0x0046a05c
        if (forPlayer1 == 0 || m_unkF8 == 0) goto tail;
        if (forPlayer0 != 0 && m_unkF4 != 0) {
            UpdateButtonIcons(0);  // 0x00468530
            goto icons1;
        }
        UpdateButtonIcons(1);
        goto tail;
    icons0:
        UpdateButtonIcons(0);
        if (forPlayer1 == 0) goto tail;
    icons1:
        if (m_unkF8 == 0) goto tail;
        UpdateButtonIcons(1);
    }
tail:
    if (entry.m_stepParams.m_unk0 != 2) return 0;
    if (CheckStepWindow(clock, &entry.m_inputWindow) != 0) return 0;
    return entry.m_inputWindow.m_ui8Fired != 0 ? 1 : 0;
}

// 0x00468530 CKHkSequenceMgr_UpdateButtonIcons_maybe: the icon of `player` (player 1 only with two controlled heroes):
// a shown one follows the icon hot spot (+0xd0) or the screen position (+0x98) and gets the alpha (+0x108); a new one is
// placed (the hot spot when the node was drawn this frame, else the null vector, or the screen position), sized, offered
// to the listener (request 5), its data (one player: +0xa4, two: +0xa8 / +0xac) gets the size, the input sequence of the
// step and the screen flag, and a pooled effect of it is acquired (the CKSrvFx lookup inlined).
void CKHkSequenceMgr::UpdateButtonIcons(int32_t player) {
    for (int32_t pass = 0; pass < 2; ++pass) {
        if (pass == 0 && player != 0) continue;
        if (pass == 1 && (m_unkE4 != 2 || player != 1)) return;
        IKFx*& icon = m_apIconFx[pass];
        if (icon != nullptr) {
            if (m_unk114 == 0) {
                if (m_ui8IconOnScreen != 0) {
                    m_v3IconPosition = CVector3{m_unk98[0], m_unk98[1], m_unk98[2]};
                } else {
                    static_cast<CSGHotSpot*>(m_apUnkC0[4])->GetWorldPosition(&m_v3IconPosition);  // 0x000ce790
                }
            }
            static_cast<CKInputIconNodeFx*>(icon)->SetAlpha(m_ui8IconAlpha);  // 0x001c5da8
            continue;
        }
        CVector3 position = CVector3{0.0f, 0.0f, 0.0f};  // 0x00c50d64
        if (NodeOf(this)->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter) {
            static_cast<CSGHotSpot*>(m_apUnkC0[4])->GetWorldPosition(&position);
        }
        m_unk114 = 0;
        m_ui8IconAlpha = 0xff;
        m_ui8IconOnScreen = CurrentEntry().m_stepParams.m_unk14;  // +0x80
        if (m_ui8IconOnScreen != 0) {
            m_v3IconPosition = CVector3{m_unk98[0], m_unk98[1], m_unk98[2]};
            m_afIconSize[0] = m_unk90;
            m_afIconSize[1] = m_unk94;
        } else {
            m_v3IconPosition = position;
            m_afIconSize[0] = m_unk88;
            m_afIconSize[1] = m_unk8c;
        }
        if (m_unk138 != nullptr) AskListener(this, 5, &m_v3IconPosition);
        IKSerializable* dataRef = pass == 1 ? m_unkAC : (m_unkE4 == 1 ? m_unkA4 : m_unkA8);
        CKInputIconFxData* data = static_cast<CKInputIconFxData*>(dataRef);
        data->m_unk14 = m_afIconSize[0];
        data->m_unk18 = m_afIconSize[1];
        data->m_unk0c = static_cast<int32_t>(CurrentEntry().m_stepParams.m_unk18);  // +0x84
        data->m_unk30 = m_ui8IconOnScreen;
        icon = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
        if (icon != nullptr) static_cast<CKInputIconNodeFx*>(icon)->SetAlpha(m_ui8IconAlpha);
    }
}

// 0x00468f10 CKHkSequenceMgr_OnCorrectInput_maybe: the last press needed fires +0x78; with the icon on the screen the
// correct answer's flash (+0xb0) starts at the icon (one player: the step's sound 0 too when several presses are
// needed). Player 0 waits for its last press when one is needed.
void CKHkSequenceMgr::OnCorrectInput(int32_t player) {
    const uint8_t forPlayer0 = IsStepForPlayer(0);
    const uint8_t forPlayer1 = IsStepForPlayer(1);
    if (!(m_unkF4 != 0 && forPlayer0 != 0) && !(m_unkF8 != 0 && forPlayer1 != 0)) QueueTriggerSignals(&m_unk78);
    if (player == 0 && CurrentEntry().m_stepParams.m_unk10 <= 1 && m_unkF4 != 0) return;
    if (m_unkE4 == 2) {
        if (player == 1) {
            if (CurrentEntry().m_stepParams.m_unk10 <= 1 && m_unkF8 != 0) return;
            if (m_ui8IconOnScreen == 0 || m_apIconFx[1] == nullptr) return;
            PrepareFlashData(this, m_unkB0);
            StartAnswerFlash(this, m_apIconDataFx[1], m_unkB0, m_unkAC, true);
            return;
        }
        if (player != 0) return;
        if (m_ui8IconOnScreen == 0 || m_apIconFx[0] == nullptr) return;
        PrepareFlashData(this, m_unkB0);
        StartAnswerFlash(this, m_apIconDataFx[0], m_unkB0, m_unkA8, false);
        return;
    }
    if (m_unkE4 != 1) return;
    if (player != 0 || m_ui8IconOnScreen == 0 || m_apIconFx[0] == nullptr) return;
    PrepareFlashData(this, m_unkB0);
    if (CurrentEntry().m_stepParams.m_unk10 > 1) PlaySound(m_unk20, 0);
    StartAnswerFlash(this, m_apIconDataFx[0], m_unkB0, m_unkA4, false);
}

// 0x00467bc8 CKHkSequenceMgr_OnWrongInput_maybe: +0x70 fires, the wrong input's sound (1) plays once per step, and with
// the icon on the screen the wrong answer's flash (+0xb4) starts at the icon.
void CKHkSequenceMgr::OnWrongInput(int32_t player) {
    QueueTriggerSignals(&m_unk70);  // 0x00236338
    if (m_unk118 == 0) {
        m_unk118 = 1;
        PlaySound(m_unk20, 1);
    }
    if (m_unkE4 == 1) {
        if (player != 0 || m_apIconFx[0] == nullptr || m_ui8IconOnScreen == 0) return;
        PrepareFlashData(this, m_unkB4);
        StartAnswerFlash(this, m_apIconDataFx[0], m_unkB4, m_unkA4, true);
        return;
    }
    if (m_unkE4 != 2) return;
    if (player == 0) {
        if (m_apIconFx[0] == nullptr || m_ui8IconOnScreen == 0) return;
        PrepareFlashData(this, m_unkB4);
        StartAnswerFlash(this, m_apIconDataFx[0], m_unkB4, m_unkA8, true);
        return;
    }
    if (player != 1 || m_apIconFx[1] == nullptr || m_ui8IconOnScreen == 0) return;
    PrepareFlashData(this, m_unkB4);
    StartAnswerFlash(this, m_apIconDataFx[1], m_unkB4, m_unkAC, true);
}

// 0x0046a6c8 CKHkSequenceMgr_Update (from the disassembly: the decompiler drops the end-of-step branches). The icon sets
// follow the controlled hero count; the answer flashes' particle nodes get scene flag 0x80000. Idle: the HUD stays hidden
// while +0x134 counts down. Running: the HUD hidden (+0x134 = 1), the node follows its moving ground, the trigger window
// (+0x98) fires +0x50 once, the sounds, a pending dragon switch noted (+0xd4 bit 3), then the step: ended (and the
// listener agrees, request 4), the end starters fire and the next entry (the listener may change it, request 0) starts,
// or the sequence ends; else the step's animations, the marked FX and triggers advance and the icons follow.
void CKHkSequenceMgr::Update(IKTime* clock) {
    // 0x003f6e68 WorldObjectBase_Update_Nop (empty).
    const uint8_t controlled = ControlledHeroCount();  // 0x002ca288
    if (m_unkE4 != controlled) {
        m_unkE4 = controlled;
        ReleaseIconSet(0);  // 0x00460b28
        ReleaseIconSet(1);
    }
    for (int32_t which = 0; which < 2; ++which) {
        CKParticlesEffectNodeFx* flash = static_cast<CKParticlesEffectNodeFx*>(m_apIconDataFx[which]);
        if (flash == nullptr) continue;
        for (uint32_t i = flash->m_ui32NodeCount; i != 0; --i) {
            CParticlesNodeFx* node = static_cast<CKParticlesEffectNodeFx*>(m_apIconDataFx[which])->m_ppParticleNodes[i - 1];
            if (node == nullptr) continue;
            node->m_sgProperties = (node->m_sgProperties & 0xfff7ffffu) | 0x80000u;
        }
    }
    if ((m_unkD4 & 1u) == 0) {
        if (m_unk134 > kZero) {
            GameManager()->m_flags64 = (GameManager()->m_flags64 & 0xefffffffu) | 0x10000000u;
            m_unk134 = m_unk134 - clock->m_afDeltaTime[0];
        }
        return;
    }
    GameManager()->m_flags64 = (GameManager()->m_flags64 & 0xefffffffu) | 0x10000000u;
    m_unk134 = kOne;
    // (KStub_Nop_106d8(0x11, "...", +0xe8): an empty debug print.)
    if (NodeOf(this)->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter) NodeOf(this)->ForceWorldMatrixUpdate();  // vt+0x50
    if (m_pGround != nullptr) {
        const CMatrix34* matrix = static_cast<ICollisionMesh*>(m_pGround)->GetWorldMatrix();  // vt+0x50
        CVector3 point;
        Mat4_TransformPoints(matrix, &point, &m_v3GroundPoint, 1);  // 0x0023f7e8
        RwFrame* frame = NodeOf(this)->m_pRwFrame;
        frame->modelling.pos.z = point.z;
        frame->modelling.pos.x = point.x;
        frame->modelling.pos.y = point.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(NodeOf(this)->m_pRwFrame);  // 0x00010698
    }
    m_unkEC = static_cast<uint32_t>(m_unkE8);
    StepWindow* trigger = &CurrentEntry().m_triggerWindow;
    if (trigger->m_ui8Fired == 0 && CheckStepWindow(clock, trigger) != 0) QueueTriggerSignals(&m_unk50);  // 0x00461178
    UpdateSoundTriggers(clock);  // 0x00462078
    if (HeroGroup()->IsDragonSwitchPending() != 0) m_unkD4 = static_cast<uint8_t>(m_unkD4 | 8u);  // 0x002ca188
    const int32_t index = m_unkE8;
    SequenceEntry* entries = m_vEntries.m_pBlock;
    uint8_t failed = 0;
    uint8_t ended = UpdateStep(clock, &failed);  // 0x00469960
    if (ended != 0) {
        SequenceEntry& step = entries[index];
        bool reported = true;
        if (m_unk138 != nullptr) {
            AskListener(this, 4, &ended);
            if (ended == 0 && (step.m_stepParams.m_unk0 == 1 || step.m_stepParams.m_unk0 == 3)) {
                // The listener keeps the input step running: the presses start again.
                m_unkF4 = static_cast<int32_t>(step.m_stepParams.m_unk10);
                m_unkF8 = static_cast<int32_t>(step.m_stepParams.m_unk10);
                reported = false;
            }
        }
        if (reported && m_unk118 == 0 && step.m_stepParams.m_unk0 == 1) {
            m_unkD4 = static_cast<uint8_t>(m_unkD4 & 0xf7u);
            m_unk118 = 1;
            PlaySound(m_unk20, 0);
        }
        if (ended != 0) {
            QueueTriggerSignals(&m_unk68);  // 0x00236338
            SNextQuery next;
            next.m_i32Current = m_unkE8;
            next.m_ui8Failed = failed;
            next.m_i32Next = static_cast<int32_t>(m_vEntries.m_pBlock[m_unkE8].m_unk64);
            if (failed != 0) {
                next.m_i32Next = static_cast<int32_t>(m_vEntries.m_pBlock[m_unkE8].m_unk68);
                QueueTriggerSignals(&m_unk60);
                if (m_unk118 == 0 && (step.m_stepParams.m_unk0 == 1 || step.m_stepParams.m_unk0 == 3)) {
                    m_unk118 = 1;
                    PlaySound(m_unk20, 1);
                }
            } else {
                QueueTriggerSignals(&m_unk58);
            }
            StepWindow* window = &m_vEntries.m_pBlock[m_unkE8].m_triggerWindow;
            if (window->m_ui8Fired == 0) {
                window->m_ui8Fired = 1;
                QueueTriggerSignals(&m_unk50);
            }
            if (next.m_i32Next != -2) StopCurrentSequence();  // 0x00463690
            if (m_unk138 != nullptr) AskListener(this, 0, &next);
            if (next.m_i32Next == -1) {
                const int32_t following = m_unkE8 + 1;
                m_unkE8 = following;
                if (failed != 0) m_unk131 = 0;
                if (following < static_cast<int32_t>(m_vEntries.m_ui32NbUsedElt)) {
                    StartSequence(clock);  // 0x00465348
                    return;
                }
                DetachHeroes();  // 0x004621e0
                m_unkD4 = static_cast<uint8_t>(m_unkD4 & 0xfcu);
                m_unk130 = 1;
                m_unkE8 = 0;
                return;
            }
            if (next.m_i32Next == -2) {
                m_unkD4 = static_cast<uint8_t>(m_unkD4 & 0xfcu);
                for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
                    static_cast<CKMarkedFX*>(m_vGroups.m_pBlock[i]->m_pRef4)->StopAllChannelNodes();  // 0x005ced80
                    static_cast<CKMarkedFX*>(m_vGroups.m_pBlock[i]->m_pRef0)->StopAllChannelNodes();
                    const uint32_t items = m_vItems.m_ui32NbUsedElt;
                    for (uint32_t j = items; j != 0; --j) {
                        static_cast<CKMarkedFX*>(m_vGroups.m_pBlock[i]->m_vRefs.m_pBlock[j - 1])->StopAllChannelNodes();
                    }
                }
                if (failed != 0) m_unk131 = 0;
                m_unk138 = nullptr;
                return;
            }
            m_unkE8 = next.m_i32Next;
            StartSequence(clock);  // 0x00465348
            if (failed != 0) m_unk131 = 0;
            return;
        }
    }
    AdvanceStepAnim(clock);  // 0x004640f0
    if (m_unkE8 >= 0 && static_cast<int32_t>(m_vGroups.m_ui32NbUsedElt) > m_unkE8) {
        RefGroup* refs = m_vGroups.m_pBlock[m_unkE8];
        static_cast<CKMarkedFX*>(refs->m_pRef4)->UpdateFromAnimMarks(clock);  // 0x005d0640
        static_cast<CKMarkedFX*>(m_vGroups.m_pBlock[m_unkE8]->m_pRef0)->UpdateFromAnimMarks(clock);
        const uint32_t count = m_vGroups.m_pBlock[m_unkE8]->m_vRefs.m_ui32NbUsedElt;
        for (uint32_t j = count; j != 0; --j) {
            static_cast<CKMarkedFX*>(m_vGroups.m_pBlock[m_unkE8]->m_vRefs.m_pBlock[j - 1])->UpdateFromAnimMarks(clock);
        }
    }
    const uint32_t triggers = m_pGroup48->m_vRefs.m_ui32NbUsedElt;
    for (uint32_t j = triggers; j != 0; --j) {
        static_cast<CKMarkedTrigger*>(m_pGroup48->m_vRefs.m_pBlock[j - 1])->UpdateFromAnimMarks(clock);  // 0x005d2068
    }
    if (m_apIconFx[0] == nullptr && m_apIconFx[1] == nullptr) return;
    const uint8_t forPlayer0 = IsStepForPlayer(0);
    const uint8_t forPlayer1 = IsStepForPlayer(1);
    if (forPlayer0 != 0) UpdateButtonIcons(0);  // 0x00468530
    if (forPlayer1 != 0) UpdateButtonIcons(1);
}
