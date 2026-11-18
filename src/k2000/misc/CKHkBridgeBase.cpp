// Reconstructed original translation unit: 0x3fb460-0x3ff9b8 (GAME_TOC1, main_toc1), 41 functions, 35 live.
// Primary owner: CKHkBridgeBase (not a registered class; key 0x9c2, vtable 0xb25360, size 0xfc)
// Other owners: KBase9C2 (6)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x3fb460  CKHkBridgeBase_9c2_maybe_FindHeroSlot_maybe  [dead]
//   [ ] 0x3fb4b0  CKHkBridgeBase_9c2_maybe_AddHeroToSlots_maybe  [dead]
//   [ ] 0x3fb528  CKHkBridgeBase_9c2_maybe_NotifyHeroGroupC07_maybe  [dead]
//   [ ] 0x3fb5c0  CKHkBridgeBase_9c2_maybe_NotifyHeroGroupC08_maybe  [dead]
//   [x] 0x3fb668  CKHkBridgeBase_9c2_maybe_DetachHero_maybe
//   [x] 0x3fb6f0  CKHkBridgeBase_9c2_maybe_AttachHero_maybe
//   [ ] 0x3fb948  CKHkBridgeBase_9c2_maybe_TryAttachHero_maybe  [dead]
//   [x] 0x3fba38  KBase9C2_GetInfo
//   [x] 0x3fbb18  KBase9C2_Resume  (the actor base's 0x3f6e60: inherited)
//   [x] 0x3fbb40  KBase9C2_Pause  (the actor base's 0x3f6e58: inherited)
//   [x] 0x3fbb68  KBase9C2_Stop  (the actor base's 0x3f6e50: inherited)
//   [x] 0x3fbb90  CKHkBridgeBase_9c2_maybe_Start
//   [ ] 0x3fbc48  CKHkBridgeBase_9c2_maybe_Save
//   [x] 0x3fbc70  CKHkBridgeBase_9c2_maybe_LevelReset  (RecursiveRegistration: the actor base's, inherited)
//   [x] 0x3fbc98  CKHkBridgeBase_9c2_maybe_ClearReferences  (Destroy)
//   [x] 0x3fbd98  KBase9C2_PostLoad  (the actor base's: inherited)
//   [x] 0x3fbdc0  CKHkBridgeBase_9c2_maybe_BaseDestructor  (the header's destructor)
//   [x] 0x3fbdf0  CKHkBridgeBase_9c2_maybe_ConstructBase  (the constructor)
//   [x] 0x3fbe48  CKHkBridgeBase_9c2_maybe_AttachSounds  (KGLObjectAttached)
//   [x] 0x3fbed0  CKHkBridgeBase_9c2_maybe_DeletingDestructor  (the header's destructor)
//   [x] 0x3fbf18  CKHkBridgeBase_9c2_maybe_Destructor  (the header's destructor)
//   [ ] 0x3fbf48  CKHkBridgeBase_9c2_maybe_ConstructBase_2  [dead]
//   [x] 0x3fbfa0  CKHkBridgeBase_9c2_maybe_State1
//   [x] 0x3fc2b0  CKHkBridgeBase_9c2_maybe_SnapToLowered_maybe
//   [x] 0x3fc4f8  CKHkBridgeBase_9c2_maybe_SnapToRaised_maybe
//   [x] 0x3fc760  CKHkBridgeBase_9c2_maybe_State2_Raised_maybe
//   [x] 0x3fc7d0  CKHkBridgeBase_9c2_maybe_State4
//   [x] 0x3fca10  CKHkBridgeBase_9c2_maybe_State8_maybe
//   [x] 0x3fcad8  CKHkBridgeBase_9c2_maybe_State0_Lowered_maybe
//   [x] 0x3fcba8  CKHkBridgeBase_9c2_maybe_AttachHeroesStandingOn_maybe
//   [x] 0x3fcd78  CKHkBridgeBase_9c2_maybe_Load
//   [x] 0x3fd648  CKHkBridgeBase_9c2_maybe_DetachAllHeroes_maybe
//   [x] 0x3fd760  CKHkBridgeBase_9c2_maybe_ReleaseHeroesOffBridge_maybe
//   [x] 0x3fd9c8  CKHkBridgeBase_9c2_maybe_State5_Lower_maybe
//   [x] 0x3fdbc0  CKHkBridgeBase_9c2_maybe_State7_MoveSegments_maybe
//   [x] 0x3fe018  CKHkBridgeBase_9c2_maybe_OnDeactivate
//   [x] 0x3fe138  CKHkBridgeBase_9c2_maybe_Update
//   [x] 0x3fe550  KBase9C2_OnActivate
//   [x] 0x3fe890  CKHkBridgeBase_9c2_maybe_Restart
//   [x] 0x3feba0  CKHkBridgeBase_9c2_maybe_ComputeNextState_maybe
//   [x] 0x3ff080  CKHkBridgeBase_9c2_maybe_MessageProc
//
//   [x] 0x9c0f38  CKHkBridgeBase_9c2_maybe_IsKindOf  [inline]
//   [x] 0x9c0f90  CKHkBridgeBase_9c2_maybe_GetClassGroup  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c0f98  CKHkBridgeBase_9c2_maybe_GetClassId  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c0fa0  KBase9C2_GetTriggerProp9C  [inline]  (TriggerProp9C, below)
#include "k2000/misc/CKHkBridgeBase.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/ppc_ops.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/core/IKInfo.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKPFGraphTransition.h"
#include "k2000/logic/physics/CDynamicGround.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/CBBox.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

namespace {

const float kHalf = 0.5f;          // TOC1 +0x4754 0x3f000000
const float kOne = 1.0f;           // TOC1 +0x4758 0x3f800000
const float kMoveTimeout = 5.0f;   // TOC1 +0x475c 0x40a00000
const float kZero = 0.0f;          // TOC1 +0x4760 0x00000000
const float kRaiseVolume = 0.65f;  // TOC1 +0x4788 0x3f266666
const float kRaiseSpeed = 1.6f;    // TOC1 +0x478c 0x3fcccccd
const float kEndSpeed = 1.45f;     // TOC1 +0x4798 0x3fb9999a

CKSoundDictionaryID* Sounds(const CKHkBridgeBase* b) { return static_cast<CKSoundDictionaryID*>(b->m_pSoundDictionary); }
// The game manager's +0x08 (engine +0x8c): the hero group.
IKSerializable* HeroGroup() { return g_pEngine->m_gameManager->m_unk04[1]; }
CKSrvPathFinding* PathFinding() { return static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding); }  // engine +0x6c

// A segment's modelling position set (frame +0x40..+0x48), its matrix no longer the identity (flags bit 17 cleared), the
// frame marked dirty (RwFrame_MarkDirty 0x10698). The callers' store order differs; the result does not.
void SetSegmentPosition(CSGMovable* segment, float x, float y, float z) {
    RwFrame* frame = segment->m_pRwFrame;
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.pos.z = z;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(segment->m_pRwFrame);
}

// The inlined hero release (DetachHero's body): the hero's flag 354 bit 9 set, not invulnerable, no attached movement,
// detached; the slot cleared.
void ReleaseHeroSlot(CKHkS08Hero** slot) {
    if (*slot == nullptr) return;
    (*slot)->SetFlag354Bit9(1);              // 0x00361cc0
    (*slot)->SetInvulnerable(0);             // 0x00361b20
    (*slot)->SetAttachedMovementEnabled(0);  // 0x00362050
    (*slot)->DetachFromObject();             // 0x00364608
    *slot = nullptr;
}

// The middle of the second transition's first portal's arrival box (fadds then fmuls 0.5 per axis), as a nav point
// without a node (0xffff).
void ArrivalPoint(const CKHkBridgeBase* b, CPFPoint* point) {
    const CBBox& box = b->m_apTransitions[1]->m_aPortals[0].m_ArrivalBox;
    point->m_unk0c = 0xffff;
    point->m_position.x = (box.m_sup.x + box.m_inf.x) * kHalf;
    point->m_position.y = (box.m_sup.y + box.m_inf.y) * kHalf;
    point->m_position.z = (box.m_sup.z + box.m_inf.z) * kHalf;
}

// A transition's enabled bit (+0x04 bit 2) cleared or set.
void CloseTransition(CKPFGraphTransition* t) {
    if (t != nullptr) t->m_baFlags &= ~4u;
}
void OpenTransition(CKPFGraphTransition* t) {
    if (t != nullptr) t->m_baFlags = (t->m_baFlags & ~4u) | 4u;
}

// The inlined moving-ground refresh of Update (states 1 / 7): a ground not refreshed yet (flag 0x20) is marked so and,
// while active (bit 0), takes its parent leaf's matrix (vt+0x50), the inverse and the world box.
void RefreshGround(CDynamicGround* ground) {
    if ((ground->m_ba16EngineFlags & 0x20u) != 0) return;
    ground->m_ba16EngineFlags = static_cast<uint16_t>(ground->m_ba16EngineFlags | 0x20u);
    if ((ground->m_ba16EngineFlags & 1u) == 0) return;
    CSGMovable* parent = static_cast<CSGMovable*>(ground->m_pParent);
    parent->ForceWorldMatrixUpdate();  // vt+0x50
    const CMatrix34* ltm = reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(ground->m_pParent)->m_pRwFrame->ltm);
    Mat4_Invert(ground->m_pInvertedWorldMatrix, ltm);  // 0x0023f878
    const CMatrix34* ltm2 = reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(ground->m_pParent)->m_pRwFrame->ltm);
    BBox_TransformByMatrix(reinterpret_cast<CBBox*>(ground->m_AABB), reinterpret_cast<const CBBox*>(ground->m_OBB), ltm2);  // 0x0023bce0
}

// 0x009c0fa0 KBase9C2_GetTriggerProp9C: 1 when the bridge is raised (state 2).
uint32_t TriggerProp9C(IKSerializable* self, uint32_t) {
    return static_cast<CKHkBridgeBase*>(self)->m_ui8State == 2 ? 1u : 0u;
}

}  // namespace

CKHkBridgeBase::CKHkBridgeBase() {
    m_ui8NbStates = 0xff;
    m_ui8State = 0xff;
    // The fresh heap's zeroes (the original's Create leaves the rest untouched).
    m_pSoundDictionary = nullptr;
    m_ui32NbExtra = 0;
    m_ui8NbSegments = 0;
    m_ui8CurrentSegment = 0;
    m_pStateTable = nullptr;
    for (StateHandler& s : m_aStates) s = nullptr;
    for (CKHkS08Hero*& h : m_apHeroes) h = nullptr;
    m_apSegments = nullptr;
    m_apExtraA = nullptr;
    m_apGroundsA = nullptr;
    m_apExtraB = nullptr;
    m_apGroundsB = nullptr;
    for (CKPFGraphTransition*& t : m_apTransitions) t = nullptr;
    for (float& f : m_aSegmentMotion) f = 0.0f;
    m_fTopSpeed = 0.0f;
    m_fAcceleration = 0.0f;
    m_fRaisedHeight = 0.0f;
    m_fEndRaised = 0.0f;
    m_fEndLowered = 0.0f;
    m_fEndCurrent = 0.0f;
    m_fEndSpeed = 0.0f;
    m_tsRaised.m_apDatas = nullptr;
    m_tsRaised.m_ui32NbDatas = 0;
    m_tsUnk0e4.m_apDatas = nullptr;
    m_tsUnk0e4.m_ui32NbDatas = 0;
    m_tsUnk0ec.m_apDatas = nullptr;
    m_tsUnk0ec.m_ui32NbDatas = 0;
    m_ui8Raised = 0;
    m_ui8RaisedAtStart = 0;
    m_ui8Initialised = 0;
    m_ui8OneShot = 0;
    m_ui8Locked = 0;
    m_ui8NotifyHeroGroup = 0;
    m_ui8HeroGroupNotified = 0;
    m_ui8Unk0fb = 0;
}

void CKHkBridgeBase::SwitchState(uint8_t next) {
    const uint8_t old = m_ui8State;
    if (old != 0xff) (this->*m_pStateTable[old])(nullptr, 2, next);
    m_ui8State = next;
    if (next != 0xff) (this->*m_pStateTable[next])(nullptr, 1, old);
}

// 0x003fb668 CKHkBridgeBase_9c2_maybe_DetachHero_maybe
int32_t CKHkBridgeBase::DetachHero(int32_t slot) {
    ReleaseHeroSlot(&m_apHeroes[slot]);
    return 1;
}

// 0x003fb6f0 CKHkBridgeBase_9c2_maybe_AttachHero_maybe
int32_t CKHkBridgeBase::AttachHero(CKHkS08Hero* hero) {
    hero->AttachToObject(this, 2);         // 0x00362360
    hero->SetInvulnerable(1);              // 0x00361b20
    hero->SetAttachedMovementEnabled(1);   // 0x00362050
    CPFPoint point;
    ArrivalPoint(this, &point);
    PathFinding()->SnapPointToGround(&point);  // 0x001e64c8
    const CVector3 target = point.m_position;  // sp+0x70
    CVector3 dir = point.m_position;           // sp+0x7c
    const float* position = hero->GetPositionPtr();  // 0x00361968
    const float dy = dir.y - position[1];
    const float dx = dir.x - position[0];
    const float dz = dir.z - position[2];
    dir.y = dy;
    dir.x = dx;
    dir.z = dz;
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf 0x10690
    if (length != kZero) {
        const float inv = kOne / length;
        dir.z = dir.z * inv;
        dir.x = dir.x * inv;
        dir.y = dir.y * inv;
    }
    if (static_cast<IKSerializable*>(m_apGroundsA[0]) == hero->GetGroundObject()) {  // 0x00363c40
        hero->SetLockedToObject(1, nullptr, nullptr);              // 0x003622a8
        hero->TeleportToThunk(reinterpret_cast<const CVector3*>(hero->GetPositionPtr()), &dir);  // 0x00362118
        hero->SetLockedToObject(0, nullptr, nullptr);
    }
    hero->SetMoveDestination(kMoveTimeout, &target, &dir, 0, 1, 0);  // vt+0xcc (r6 not set: unused)
    return 1;
}

// 0x003fba38 KBase9C2_GetInfo
int32_t CKHkBridgeBase::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    int32_t own = 1;
    if (request == kGetInfoValueAccessor && info->m_ui32Id == 0x9c) {
        AnswerInfo(info, TriggerProp9C, 0);
        own = 0;
    }
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x003fb420 KBase9C2_SetGameState
int32_t CKHkBridgeBase::SetGameState(const SApplyGameState* state) {
    if (state->m_ui32InfoId != 1) return 0;
    m_ui8Initialised = 0;
    const int32_t value = static_cast<int32_t>(state->m_ui32GameStateId);
    const int32_t sign = value >> 31;  // srawi
    const uint32_t magnitude = static_cast<uint32_t>((sign ^ value) - sign);
    m_ui8RaisedAtStart = static_cast<uint8_t>((magnitude - 1u) >> 31);  // 1 for game state 0
    return 1;
}

// 0x003fbb90 CKHkBridgeBase_9c2_maybe_Start
void CKHkBridgeBase::Start() {
    CKHkActorBase::Start();  // 0x003f6e48 (empty)
    m_aStates[0] = &CKHkBridgeBase::State0Lowered;          // TOC +0x4768
    m_ui8HeroGroupNotified = 1;
    m_aStates[1] = &CKHkBridgeBase::State1RaiseSegment;     // TOC +0x476c
    m_aStates[2] = &CKHkBridgeBase::State2Raised;           // TOC +0x4770
    m_aStates[3] = &CKHkBridgeBase::StateNextSegmentUp;     // 0xf9: the virtual slot +0xf8
    m_aStates[6] = &CKHkBridgeBase::StateNextSegmentDown;   // 0xfd: the virtual slot +0xfc
    m_aStates[4] = &CKHkBridgeBase::State4RaiseEnd;         // TOC +0x4774
    m_aStates[5] = &CKHkBridgeBase::State5LowerEnd;         // TOC +0x4778
    m_aStates[7] = &CKHkBridgeBase::State7LowerSegment;     // TOC +0x477c
    m_aStates[8] = &CKHkBridgeBase::State8Blocked;          // TOC +0x4780
    m_apHeroes[2] = nullptr;
    m_apHeroes[0] = nullptr;
    m_apHeroes[1] = nullptr;
}

// 0x003fbc98 CKHkBridgeBase_9c2_maybe_ClearReferences (Destroy)
void CKHkBridgeBase::Destroy() {
    CKHkActorBase::Destroy();  // 0x003f6e08 (vt+0xc0)
    if (m_apSegments != nullptr) {
        Mem_FreeAligned16(m_apSegments);
        m_apSegments = nullptr;
    }
    if (m_apGroundsB != nullptr) {
        Mem_FreeAligned16(m_apGroundsB);
        m_apGroundsB = nullptr;
    }
    if (m_apGroundsA != nullptr) {
        Mem_FreeAligned16(m_apGroundsA);
        m_apGroundsA = nullptr;
    }
    if (m_ui32NbExtra == 0) {
        m_apExtraA = nullptr;
        m_apExtraB = nullptr;
        return;
    }
    if (m_apExtraB != nullptr) {
        Mem_FreeAligned16(m_apExtraB);
        m_apExtraB = nullptr;
    }
    if (m_apExtraA != nullptr) {
        Mem_FreeAligned16(m_apExtraA);
        m_apExtraA = nullptr;
    }
}

// 0x003fbe48 CKHkBridgeBase_9c2_maybe_AttachSounds
void CKHkBridgeBase::KGLObjectAttached(IKSerializable* /*leaf*/) {
    Sounds(this)->GetSound(0)->SetAttachObject(m_pKGLObject);  // 0x00112bc0, 0x00111350
    Sounds(this)->GetSound(1)->SetAttachObject(m_pKGLObject);
    Sounds(this)->GetSound(2)->SetAttachObject(m_pKGLObject);
}

// 0x003fbfa0 CKHkBridgeBase_9c2_maybe_State1: the current segment rises (FloatApproachAccel to the raised height);
// once up its second ground goes on and state 3 (the derived bridge's next segment) follows.
uint8_t CKHkBridgeBase::State1RaiseSegment(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        m_aSegmentMotion[4] = 0.0f;  // stw 0
        m_aSegmentMotion[2] = 0.0f;
        m_aSegmentMotion[1] = m_fTopSpeed;
        m_aSegmentMotion[0] = m_fRaisedHeight;
        m_aSegmentMotion[3] = m_fAcceleration;
        if (m_ui8CurrentSegment >= m_ui8NbSegments) return 1;
        if (Sounds(this)->GetSound(1) != nullptr) Sounds(this)->GetSound(1)->SetBaseVolume(kRaiseVolume);  // 0x00110ee8
        if (Sounds(this)->GetSound(1) != nullptr) Sounds(this)->GetSound(1)->SetSpeed(kRaiseSpeed);       // 0x00110e98
        if (Sounds(this)->GetSound(1) == nullptr) return 1;
        CKSound_Play(kZero, Sounds(this)->GetSound(1));  // 0x00111230 (0 through the stack)
        return 1;
    }
    if (phase == 2) {
        if (m_ui8OneShot != 0) m_ui8Locked = 1;
        return 1;
    }
    if (phase != 0) return 1;
    CDynamicGround* groundA = m_apGroundsA[m_ui8CurrentSegment];
    if ((groundA->m_ba16EngineFlags & 1u) == 0) groundA->SetActive(1);  // 0x001a6b70
    FloatApproachAccel_Step(clock->m_afDeltaTime[0], m_aSegmentMotion);  // 0x00243800
    const uint8_t segment = m_ui8CurrentSegment;
    if (static_cast<int32_t>(segment) < static_cast<int32_t>(m_ui8NbSegments) - 1) {  // cmpw / bge
        SetSegmentPosition(m_apSegments[segment], 0.0f, 0.0f, m_aSegmentMotion[4]);
    } else {
        SetSegmentPosition(m_apSegments[segment], 0.0f, m_fEndCurrent, m_aSegmentMotion[4]);
    }
    if (m_aSegmentMotion[4] >= m_fRaisedHeight) {  // cror gt|eq, bne (NaN: not up)
        m_apGroundsB[m_ui8CurrentSegment]->SetActive(1);
        return 3;
    }
    return 1;
}

// 0x003fc2b0 CKHkBridgeBase_9c2_maybe_SnapToLowered_maybe
void CKHkBridgeBase::SnapToLowered() {
    m_fEndCurrent = m_fEndLowered;
    m_ui8Unk0fb = 0;
    m_ui8Raised = 0;
    uint32_t count = 0;
    if (m_ui8NbSegments != 0) {
        for (uint32_t i = 0;; ++i) {
            SetSegmentPosition(m_apSegments[i], 0.0f, 0.0f, 0.0f);
            if ((m_bitArray & 4u) == 0) {
                m_apGroundsA[i]->SetActive(0);
                m_apGroundsB[i]->SetActive(0);
            }
            count = m_ui8NbSegments;
            if (count <= i + 1) break;  // cmplw / ble
        }
    }
    // BUG(original): with no segment the end segment is the word before the array.
    SetSegmentPosition(m_apSegments[static_cast<int32_t>(count) - 1], 0.0f, m_fEndCurrent, 0.0f);
    OnSnappedLowered();  // vt+0xf0
    CloseTransition(m_apTransitions[0]);
    CloseTransition(m_apTransitions[1]);
    CloseTransition(m_apTransitions[2]);
    CloseTransition(m_apTransitions[3]);
}

// 0x003fc4f8 CKHkBridgeBase_9c2_maybe_SnapToRaised_maybe
void CKHkBridgeBase::SnapToRaised() {
    m_fEndCurrent = m_fEndRaised;
    m_ui8Raised = 1;
    m_ui8Unk0fb = 0;
    uint32_t count = 0;
    if (m_ui8NbSegments != 0) {
        for (uint32_t i = 0;; ++i) {
            SetSegmentPosition(m_apSegments[i], 0.0f, 0.0f, m_fRaisedHeight);
            if ((m_bitArray & 4u) == 0) {
                m_apGroundsA[i]->SetActive(1);
                m_apGroundsB[i]->SetActive(1);
            }
            count = m_ui8NbSegments;
            if (count <= i + 1) break;
        }
    }
    // BUG(original): with no segment the end segment is the word before the array.
    SetSegmentPosition(m_apSegments[static_cast<int32_t>(count) - 1], 0.0f, m_fEndCurrent, m_fRaisedHeight);
    OnSnappedRaised();  // vt+0xf4
    OpenTransition(m_apTransitions[0]);
    OpenTransition(m_apTransitions[1]);
    OpenTransition(m_apTransitions[2]);
    OpenTransition(m_apTransitions[3]);
}

// 0x003fc760 CKHkBridgeBase_9c2_maybe_State2_Raised_maybe
uint8_t CKHkBridgeBase::State2Raised(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        SnapToRaised();
        return 2;
    }
    if (phase != 2) return 2;
    m_ui8CurrentSegment = static_cast<uint8_t>(m_ui8NbSegments - 1);
    return 2;
}

// 0x003fc7d0 CKHkBridgeBase_9c2_maybe_State4: the end segment rises to +0xcc; once up the raised signals, sound 2, and
// state 2.
uint8_t CKHkBridgeBase::State4RaiseEnd(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        m_ui8CurrentSegment = static_cast<uint8_t>(m_ui8NbSegments - 1);
        return 4;
    }
    if (phase == 2) {
        m_ui8Raised = 1;
        IKSerializable* group = HeroGroup();
        if (group == nullptr || m_ui8NotifyHeroGroup == 0 || m_ui8HeroGroupNotified == 0) return 4;
        group->MessageProc(0xc08, nullptr);  // vt+0x1c
        m_ui8HeroGroupNotified = 0;
        return 4;
    }
    if (phase != 0) return 4;
    const float current = m_fEndCurrent;
    const float raised = m_fEndRaised;
    if (!(raised > current)) {  // ble (NaN: up)
        QueueTriggerSignals(&m_tsRaised);  // 0x00236338
        if (Sounds(this)->GetSound(2) != nullptr) Sounds(this)->GetSound(2)->SetSpeed(kEndSpeed);
        if (Sounds(this)->GetSound(2) == nullptr) return 2;
        CKSound_Play(kZero, Sounds(this)->GetSound(2));
        return 2;
    }
    const float next = ppc::fmadds(m_fEndSpeed, clock->m_afDeltaTime[0], current);
    m_fEndCurrent = next;
    if (next > raised) m_fEndCurrent = raised;  // ble skips
    SetSegmentPosition(m_apSegments[static_cast<int32_t>(m_ui8NbSegments) - 1], 0.0f, m_fEndCurrent, m_fRaisedHeight);
    return 4;
}

// 0x003fca10 CKHkBridgeBase_9c2_maybe_State8_maybe
uint8_t CKHkBridgeBase::State8Blocked(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase != 1) return 8;
    IKSerializable* group = HeroGroup();
    if (group != nullptr && m_ui8NotifyHeroGroup != 0 && m_ui8HeroGroupNotified != 0) {
        group->MessageProc(0xc08, nullptr);
        m_ui8HeroGroupNotified = 0;
    }
    m_ui8Unk0fb = 0;
    return 8;
}

// 0x003fcad8 CKHkBridgeBase_9c2_maybe_State0_Lowered_maybe
uint8_t CKHkBridgeBase::State0Lowered(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        SnapToLowered();
        IKSerializable* group = HeroGroup();
        if (group != nullptr && m_ui8NotifyHeroGroup != 0 && m_ui8HeroGroupNotified != 0) {
            group->MessageProc(0xc08, nullptr);
            m_ui8HeroGroupNotified = 0;
        }
    } else if (phase == 2) {
        m_ui8CurrentSegment = 0;
    }
    return 0;
}

// 0x003fcba8 CKHkBridgeBase_9c2_maybe_AttachHeroesStandingOn_maybe
int32_t CKHkBridgeBase::AttachHeroesStandingOn() {
    IKGrpHero* group = static_cast<IKGrpHero*>(HeroGroup());
    if (group == nullptr) return 0;
    const uint32_t count = group->m_ui8CompanionHeroCount;  // 0x002ca290
    if (count == 0) return 0;
    uint8_t standing = 0;
    for (uint32_t i = 0; i != count; ++i) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apCompanionHeroes[i]);  // 0x002ca0e8
        if (IsBridgeGround(hero->GetGroundInfo()) == 0) continue;  // 0x00361b68, vt+0x100
        if (hero->CanAttachTo(this, 2) != 0 && hero != m_apHeroes[0] && hero != m_apHeroes[1] &&  // 0x00361d08 (vt+0xe0)
            hero != m_apHeroes[2]) {
            int32_t slot = 0;
            if (m_apHeroes[0] != nullptr) {
                slot = 1;
                if (m_apHeroes[1] != nullptr) {
                    if (m_apHeroes[2] != nullptr) {
                        standing = 1;
                        continue;
                    }
                    slot = 2;
                }
            }
            standing = 1;
            m_apHeroes[slot] = hero;
            AttachHero(hero);
            continue;
        }
        standing = 1;
    }
    return standing;
}

// 0x003fcd78 CKHkBridgeBase_9c2_maybe_Load
int32_t CKHkBridgeBase::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // 0x003f6e98
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadRaw(file, &m_ui8NbSegments, 1);
    m_apSegments = static_cast<CSGMovable**>(Mem_AllocAligned16(static_cast<uint32_t>(m_ui8NbSegments) * 0x24u));
    m_apGroundsA = static_cast<CDynamicGround**>(
        Mem_AllocAligned16(static_cast<uint32_t>(m_ui8NbSegments) * static_cast<uint32_t>(sizeof(CDynamicGround*))));
    m_apGroundsB = static_cast<CDynamicGround**>(
        Mem_AllocAligned16(static_cast<uint32_t>(m_ui8NbSegments) * static_cast<uint32_t>(sizeof(CDynamicGround*))));
    for (uint8_t i = 0; i < m_ui8NbSegments; ++i) {
        IKFile_ReadRef(file, &m_apGroundsA[i]);
        IKFile_ReadRef(file, &m_apSegments[i]);
        IKFile_ReadRef(file, &m_apGroundsB[i]);
    }
    ReadF32LE(file, &m_fRaisedHeight);
    ReadF32LE(file, &m_fEndLowered);
    ReadF32LE(file, &m_fEndRaised);
    ReadF32LE(file, &m_fTopSpeed);
    ReadF32LE(file, &m_fAcceleration);
    ReadU32LE(file, &m_ui32NbExtra);
    if (m_ui32NbExtra == 0) {
        m_apExtraB = nullptr;
        m_apExtraA = nullptr;
    } else {
        m_apExtraA = static_cast<IKSerializable**>(Mem_AllocAligned16(m_ui32NbExtra * 0x24u));
        m_apExtraB = static_cast<IKSerializable**>(
            Mem_AllocAligned16(m_ui32NbExtra * static_cast<uint32_t>(sizeof(IKSerializable*))));
        // The counter is a byte (uVar14 & 0xff) compared with the word count.
        for (uint8_t i = 0; i < m_ui32NbExtra; ++i) {
            IKFile_ReadRef(file, &m_apExtraB[i]);
            IKFile_ReadRef(file, &m_apExtraA[i]);
        }
    }
    IKFile_ReadRef(file, &m_pSoundDictionary);
    m_tsRaised.Load(file, 0);   // 0x002361c0
    m_tsUnk0ec.Load(file, 0);
    m_tsUnk0e4.Load(file, 0);
    m_pStateTable = m_aStates;
    m_ui8State = 0xff;
    m_ui8NbStates = kStateCount;
    ReadRaw(file, &m_ui8OneShot, 1);
    ReadRaw(file, &m_ui8Locked, 1);
    ReadF32LE(file, &m_fEndSpeed);
    IKFile_ReadRef(file, &m_apTransitions[0]);
    IKFile_ReadRef(file, &m_apTransitions[1]);
    IKFile_ReadRef(file, &m_apTransitions[2]);
    IKFile_ReadRef(file, &m_apTransitions[3]);
    ReadRaw(file, &m_ui8NotifyHeroGroup, 1);
    return 1;
}

// 0x003fd648 CKHkBridgeBase_9c2_maybe_DetachAllHeroes_maybe
void CKHkBridgeBase::DetachAllHeroes() {
    ReleaseHeroSlot(&m_apHeroes[0]);
    ReleaseHeroSlot(&m_apHeroes[1]);
    ReleaseHeroSlot(&m_apHeroes[2]);
}

// 0x003fd760 CKHkBridgeBase_9c2_maybe_ReleaseHeroesOffBridge_maybe
void CKHkBridgeBase::ReleaseHeroesOffBridge(IKTime* clock) {
    for (uint8_t i = 0; i != 3; ++i) {
        CKHkS08Hero** slot = &m_apHeroes[i];
        CKHkS08Hero* hero = *slot;
        if (hero == nullptr) continue;
        const uint8_t onBridge = IsBridgeGround(hero->GetGroundInfo());  // vt+0x100, 0x00361b68
        if (onBridge == 0 && static_cast<uint8_t>(hero->GetFlag354Bit0()) != 0) {  // 0x00361a90
            CPFPoint point;
            ArrivalPoint(this, &point);
            PathFinding()->SnapPointToGround(&point);  // 0x001e64c8
            const CVector3 facing{hero->m_unk540, hero->m_unk544, hero->m_unk548};  // 0x00361a50 GetForwardDirPtr (+0x540)
            hero->TeleportToThunk(&point.m_position, &facing);                      // 0x00362118
            if (*slot == nullptr) continue;
            (*slot)->SetFlag354Bit9(1);
            (*slot)->SetInvulnerable(0);
            (*slot)->SetAttachedMovementEnabled(0);
            (*slot)->DetachFromObject();
            *slot = nullptr;  // stw r29 (0)
            continue;
        }
        if (hero->UpdateMoveTo(clock, nullptr) == 0) continue;  // vt+0xd0
        ReleaseHeroSlot(slot);
    }
}

// 0x003fd9c8 CKHkBridgeBase_9c2_maybe_State5_Lower_maybe: the end segment lowers to +0xd0, then state 6.
uint8_t CKHkBridgeBase::State5LowerEnd(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    ReleaseHeroesOffBridge(clock);
    if (phase == 1) {
        if (Sounds(this)->GetSound(2) != nullptr) Sounds(this)->GetSound(2)->SetSpeed(kEndSpeed);
        if (Sounds(this)->GetSound(2) == nullptr) return 5;
        CKSound_Play(kZero, Sounds(this)->GetSound(2));
        return 5;
    }
    if (phase == 2) {
        m_ui8Raised = 0;
        return 5;
    }
    if (phase != 0) return 5;
    const float current = m_fEndCurrent;
    const float lowered = m_fEndLowered;
    if (!(lowered < current)) return 6;  // bge (NaN: down)
    const float next = current - m_fEndSpeed * clock->m_afDeltaTime[0];  // fmuls, fsubs
    m_fEndCurrent = next;
    if (next < lowered) m_fEndCurrent = lowered;  // bge skips
    SetSegmentPosition(m_apSegments[static_cast<int32_t>(m_ui8NbSegments) - 1], 0.0f, m_fEndCurrent, m_fRaisedHeight);
    return 5;
}

// 0x003fdbc0 CKHkBridgeBase_9c2_maybe_State7_MoveSegments_maybe: the current segment lowers to 0; down, its grounds go
// off and state 6 (the next one) follows, or state 0 after the first.
uint8_t CKHkBridgeBase::State7LowerSegment(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    ReleaseHeroesOffBridge(clock);
    if (phase == 1) {
        m_aSegmentMotion[4] = m_fRaisedHeight;
        m_aSegmentMotion[2] = 0.0f;
        m_aSegmentMotion[1] = m_fTopSpeed;
        m_aSegmentMotion[0] = 0.0f;
        m_aSegmentMotion[3] = m_fAcceleration;
        if (m_ui8CurrentSegment >= m_ui8NbSegments) return 7;
        if (Sounds(this)->GetSound(1) != nullptr) Sounds(this)->GetSound(1)->SetBaseVolume(kRaiseVolume);
        if (Sounds(this)->GetSound(1) != nullptr) Sounds(this)->GetSound(1)->SetSpeed(kRaiseSpeed);
        if (Sounds(this)->GetSound(1) == nullptr) return 7;
        CKSound_Play(kZero, Sounds(this)->GetSound(1));
        return 7;
    }
    if (phase == 2) {
        DetachAllHeroes();
        return 7;
    }
    if (phase != 0) return 7;
    CDynamicGround* groundA = m_apGroundsA[m_ui8CurrentSegment];
    if ((groundA->m_ba16EngineFlags & 1u) == 0) {
        groundA->SetActive(1);
        m_apGroundsB[m_ui8CurrentSegment]->SetActive(1);
    }
    FloatApproachAccel_Step(clock->m_afDeltaTime[0], m_aSegmentMotion);  // 0x00243800
    const uint8_t segment = m_ui8CurrentSegment;
    if (static_cast<int32_t>(segment) < static_cast<int32_t>(m_ui8NbSegments) - 1) {
        SetSegmentPosition(m_apSegments[segment], 0.0f, 0.0f, m_aSegmentMotion[4]);
    } else {
        SetSegmentPosition(m_apSegments[segment], 0.0f, m_fEndCurrent, m_aSegmentMotion[4]);
    }
    if (!(m_aSegmentMotion[4] <= kZero)) return 7;  // cror lt|eq, bne (NaN: not down)
    m_apGroundsA[m_ui8CurrentSegment]->SetActive(0);
    m_apGroundsB[m_ui8CurrentSegment]->SetActive(0);
    if (m_ui8CurrentSegment == 0) return 0;
    m_ui8CurrentSegment = static_cast<uint8_t>(m_ui8CurrentSegment - 1);
    return 6;
}

// 0x003fe018 CKHkBridgeBase_9c2_maybe_OnDeactivate
void CKHkBridgeBase::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    DetachAllHeroes();
}

// 0x003fe138 CKHkBridgeBase_9c2_maybe_Update
void CKHkBridgeBase::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68 (empty)
    uint8_t state = m_ui8State;
    if (state != 0xff) {
        const uint8_t next = (this->*m_pStateTable[state])(clock, 0, state);
        const uint8_t current = m_ui8State;
        state = current;
        if (next != current) {
            if (current != 0xff) (this->*m_pStateTable[current])(clock, 2, next);
            m_ui8State = next;
            state = next;
            if (next != 0xff) {
                (this->*m_pStateTable[next])(clock, 1, current);
                state = m_ui8State;
            }
        }
        if (state == 7) {
            AttachHeroesStandingOn();
            state = m_ui8State;
        }
    }
    if (state != 1 && state != 7) return;
    for (uint32_t i = 0; i < m_ui8NbSegments; ++i) {
        RefreshGround(m_apGroundsB[i]);
        RefreshGround(m_apGroundsA[i]);
    }
}

// 0x003fe550 KBase9C2_OnActivate: the first time, snapped to the start pose (raised with +0xf5) and its state entered;
// later, snapped to the current one (raised in state 2). The node shown.
void CKHkBridgeBase::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    if (m_ui8Initialised == 0) {
        if (m_ui8RaisedAtStart == 0) {
            SnapToLowered();
            SwitchState(0);
        } else {
            SnapToRaised();
            SwitchState(2);
        }
        m_ui8Initialised = 1;
        static_cast<CSGLeaf*>(m_pKGLObject)->m_sgProperties &= 0xfffffffbu;
        return;
    }
    if (m_ui8State == 2) {
        SnapToRaised();
    } else {
        SnapToLowered();
    }
    static_cast<CSGLeaf*>(m_pKGLObject)->m_sgProperties &= 0xfffffffbu;
}

// 0x003fe890 CKHkBridgeBase_9c2_maybe_Restart: unless the life sleeps (+0x0c bit 2), the heroes let go and the start
// pose and state taken again.
void CKHkBridgeBase::Restart() {
    if ((m_bitArray & 4u) != 0) return;
    DetachAllHeroes();
    if (m_ui8RaisedAtStart == 0) {
        SnapToLowered();
        SwitchState(0);
    } else {
        SnapToRaised();
        SwitchState(2);
    }
    m_ui8Initialised = 1;
}

// 0x003feba0 CKHkBridgeBase_9c2_maybe_ComputeNextState_maybe
uint8_t CKHkBridgeBase::ComputeNextState(uint8_t event) {
    const uint8_t current = m_ui8State;
    uint8_t next = current;
    if (event == 2 || event == 0) {
        if (current <= 8) {
            switch (current) {  // the table TOC +0x47b0
            case 0:
            case 7:
            case 8:
                DetachAllHeroes();
                next = 1;
                break;
            case 5:
                DetachAllHeroes();
                next = 4;
                break;
            case 6:
                DetachAllHeroes();
                next = 3;
                break;
            default:
                break;
            }
        }
        if (event == 2) {
            if (next != m_ui8State) return next;
            goto toggle;
        }
    }
    if (static_cast<uint8_t>(event - 1) > 1) return next;
toggle:
    CloseTransition(m_apTransitions[0]);
    CloseTransition(m_apTransitions[2]);
    CloseTransition(m_apTransitions[3]);
    if (next > 8) return next;
    switch (next) {  // the table TOC +0x47b4
    case 1: return 7;
    case 2:
    case 4:
    case 8: return 5;
    case 3: return 6;
    default: return next;
    }
}

// 0x003ff080 CKHkBridgeBase_9c2_maybe_MessageProc
int32_t CKHkBridgeBase::MessageProc(uint16_t message, void* data) {
    CKHkActorBase::MessageProc(message, data);  // 0x003f7148 (called twice, the first answer dropped)
    const int32_t base = CKHkActorBase::MessageProc(message, data);
    int32_t own = 0;
    // The hero group told 0xc07 (the bridge on its way up), when wanted and not told yet (no null check).
    auto notifyUp = [this]() -> bool {
        if (m_ui8Raised != 0 || m_ui8NotifyHeroGroup == 0 || m_ui8HeroGroupNotified != 0) return false;
        HeroGroup()->MessageProc(0xc07, nullptr);  // vt+0x1c
        m_ui8HeroGroupNotified = 1;
        return true;
    };
    if (message == 0x996) {
        if (m_ui8Locked == 0) SwitchState(ComputeNextState(0));
        notifyUp();
    } else if (message < 0x997) {
        if (message == 0x93f) {
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(data);
            if (hero == m_apHeroes[0] || hero == m_apHeroes[1] || hero == m_apHeroes[2]) {
                own = 1;
            } else {
                int32_t slot = 0;
                own = 0;
                if (m_apHeroes[0] != nullptr) {
                    slot = 1;
                    if (m_apHeroes[1] != nullptr) {
                        if (m_apHeroes[2] != nullptr) own = 1;
                        slot = 2;
                    }
                }
                if (own == 0) {
                    m_apHeroes[slot] = hero;
                    AttachHero(hero);
                }
            }
        } else if (message == 0x940) {
            int32_t slot;
            if (m_apHeroes[0] == data) {
                slot = 0;
            } else if (m_apHeroes[1] == data) {
                slot = 1;
            } else if (m_apHeroes[2] == data) {
                slot = 2;
            } else {
                slot = -1;
                own = 1;
            }
            if (slot >= 0) ReleaseHeroSlot(&m_apHeroes[slot]);
        } else {
            own = 1;
        }
    } else if (message == 0x998) {
        if (m_ui8Locked == 0) {
            const uint8_t next = ComputeNextState(2);
            const uint8_t old = m_ui8State;
            if (old != 0xff) (this->*m_pStateTable[old])(nullptr, 2, next);
            m_ui8State = next;
            bool down = true;
            if (next != 0xff) {
                (this->*m_pStateTable[next])(nullptr, 1, old);
                if (m_ui8State == 1) {
                    notifyUp();
                    down = false;
                }
            }
            if (down) {
                IKSerializable* group = HeroGroup();
                if (group != nullptr && m_ui8NotifyHeroGroup != 0 && m_ui8HeroGroupNotified != 0) {
                    group->MessageProc(0xc08, nullptr);
                    m_ui8HeroGroupNotified = 0;
                }
            }
        }
    } else if (message > 0x997) {
        if (message == 0x999) {
            if (m_ui8Locked == 0) SwitchState(ComputeNextState(0));
            notifyUp();
            m_ui8Unk0fb = 1;
        } else {
            own = 1;
        }
    } else {  // 0x997
        if (m_ui8Locked == 0) SwitchState(ComputeNextState(1));
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}
