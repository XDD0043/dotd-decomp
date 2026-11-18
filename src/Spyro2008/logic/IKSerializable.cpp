// IKSerializable.cpp - reconstructed original translation unit: 0x470778-0x472af8 (GAME_TOC1, main_toc1), 26 functions, 22 live.
// Primary owner: IKSerializable (not a registered class)
// Other owners: KBase7CCC (6), CKColossusAttackElementBase (3), Vec3 (2), CKColossusContextualAttackElement (2)
//
// The unit is the colossus attack elements' base KBase7CCC (k2000/misc/KBase7CCC.h; C2.8 port-rest R11). Nothing
// creates one yet: its two classes (CKColossusContextualAttackElement, CKColossusBaseAttackElement) are left for the
// colossus family round, and no game file holds them.
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x470778  KBaseC_vf6C_3  (KBase7CCC::Vf6C)
//   [ ] 0x470820  FUN_00470820  [dead]
//   [ ] 0x4708d0  FUN_004708d0  [dead]
//   [ ] 0x470980  Vec3_YawDifferenceWrapped_2_maybe  [dead]
//   [x] 0x470a10  IKSerializable_PostLoad  (KBase7CCC::PostLoad)
//   [x] 0x470b50  KBaseC_vf70_2  (KBase7CCC::Vf70)
//   [x] 0x470cc0  KBaseC_vf78_2  (KBase7CCC::Vf78)
//   [x] 0x470dd0  StaticInitAndDestruction_470dd0  (the two -1.0 words below)
//   [ ] 0x470e00  _GLOBAL__D_470e00
//   [ ] 0x470e10  _GLOBAL__I_470e10
//   [x] 0x470e20  KBaseC_vf64_2  (KBase7CCC::Vf64)
//   [x] 0x470f10  KBaseC_vf74_3  (KBase7CCC::Vf74)
//   [x] 0x471160  CKColossusAttackElementBase_maybe_Construct  (KBase7CCC(): KBase7CCC.h)
//   [ ] 0x471198  CKColossusAttackElementBase_maybe_Construct_2  [dead]
//   [x] 0x4711d0  KBaseC_vf7C  (KBase7CCC::Vf7C)
//   [x] 0x4712e8  KBase7CCC_vf28  (Save: returns 1, KBase7CCC.h)
//   [x] 0x4712f0  KBase7CCC_vf24  (RecursiveRegistration: returns 1, KBase7CCC.h)
//   [x] 0x4712f8  KBase7CCC_ClearReferences  (KBase7CCC::Destroy, vt+0x10)
//   [x] 0x4713e8  CKColossusContextualAttackElement_vf54  (KBase7CCC::Vf54)
//   [x] 0x471660  Vec3_RotateYawFlatNormalized_3_maybe  (RotateYawFlatNormalized below)
//   [x] 0x471930  KBaseC_vf68_2  (KBase7CCC::Vf68)
//   [x] 0x471df8  CKColossusContextualAttackElement_StartAttack_maybe  (KBase7CCC::Vf50)
//   [x] 0x472148  KBase7CCC_Load
//   [x] 0x472860  KBase7CCC_Destructor  (~KBase7CCC)
//   [x] 0x472938  CKColossusAttackElementBase_maybe_BaseDestructor  (~KBase7CCC)
//   [x] 0x472a10  KBase7CCC_DeletingDestructor  (~KBase7CCC, then delete)
//
//   [x] 0x9c4578  KBase7CCC_vf14  [inline]  (GetClassType: KBase7CCC.h)
//   [x] 0x9c4580  KBase7CCC_vf18  [inline]  (GetClassID: KBase7CCC.h)
//   [x] 0x9c4588  KBase7CCC_vf8  [inline]  (IsKindOfClass: KBase7CCC.h)
#include "k2000/misc/KBase7CCC.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/hooks/CKHkColossus.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/math/Math.h"
#include "k2000/math/Vec3.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"

namespace {

// 0x00470dd0 StaticInitAndDestruction_470dd0: two -1.0 words of the unit's data (0x00ceb10c / 0x00ceb110), set at
// start-up and not read by this unit.
float g_unitMinusOneA = -1.0f;  // 0x00ceb10c
float g_unitMinusOneB = -1.0f;  // 0x00ceb110

constexpr float kZero = 0.0f;              // TOC +0x5918
constexpr float kOne = 1.0f;               // TOC +0x5944
constexpr float kTwoPi = 6.28318548f;      // TOC +0x592c (0x40c90fdb)
constexpr float kMinRadius = 0.001f;       // TOC +0x5914 (0x3a83126f)
constexpr float kContactTime = -1000.0f;   // TOC +0x593c
constexpr float kAtLength = 80.0f;         // TOC +0x597c

// 0x00471660 Vec3_RotateYawFlatNormalized_3_maybe (a member of the unit; `this` is not used): 0x00584e40
// Vec3_RotateYawFlatNormalized's code without its zero-angle return: `v` turned by `angle` radians about y, its y
// cleared, normalised; the zero vector (0x00c50d64) is left alone.
void RotateYawFlatNormalized(float angle, CVector3* v) {
    const float x = v->x;
    if (x == 0.0f && v->y == 0.0f && v->z == 0.0f) return;
    int32_t angleBits;
    std::memcpy(&angleBits, &angle, 4);
    float c;
    float s;
    if (angleBits >= 0) {
        c = crt::InlineCosf(angle);
        s = crt::InlineSinf(angle);
    } else {
        c = crt::LibCosf(-angle);
        s = -crt::LibSinf(-angle);
    }
    const float z = v->z;
    const float sz = s * z;
    const float cz = c * z;
    v->y = kZero;
    const float newX = ppc::fmsubs(c, x, sz);
    const float newZ = ppc::fmadds(s, x, cz);
    v->x = newX;
    v->z = newZ;
    const float length = std::sqrt(ppc::fmadds(newZ, newZ, ppc::fmadds(newX, newX, kZero)));  // Math_Sqrtf 0x10690
    if (length == kZero) return;
    const float inv = kOne / length;
    v->z = inv * v->z;
    v->x = inv * v->x;
    v->y = inv * v->y;
}

// The wrap of vf68 (the loops at 0x471a58 / 0x471ac0 / 0x471c70): up by 2 pi while below 0, then down while not below
// 2 pi (a NaN stays).
float WrapAngle(float angle) {
    if (angle < kZero) {
        do {
            angle = angle + kTwoPi;
        } while (angle < kZero);
    }
    while (angle >= kTwoPi) angle = angle - kTwoPi;
    return angle;
}

// The end of both halves of vf68: the colossus' rest `at` axis (+0x3c) turned by `yaw` (flat, normalised, normalised
// again), 80 long, as its frame's modelling `at`; the frame's type bits cleared and the frame marked dirty.
void SetOwnerAt(CKHkColossus* owner, float yaw) {
    CVector3 at = owner->m_vUnk3C;
    RotateYawFlatNormalized(yaw, &at);  // 0x00471660
    const float length = std::sqrt(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y)));  // Math_Sqrtf 0x10690
    if (length != kZero) {
        const float inv = kOne / length;
        at.z = at.z * inv;
        at.x = at.x * inv;
        at.y = at.y * inv;
    }
    at.z = at.z * kAtLength;
    at.x = at.x * kAtLength;
    at.y = at.y * kAtLength;
    RwFrame* frame = static_cast<CSGMovable*>(owner->m_pKGLObject)->m_pRwFrame;
    frame->modelling.at.x = at.x;
    frame->modelling.at.y = at.y;
    frame->modelling.at.z = at.z;
    frame->modelling.flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// The two record lists of the Load (0x472190.. / 0x472400..): a fresh one-slot block (capacity 1), the count (swapped),
// then each record (operator new 0x1c, zeroed; four words, each swapped) appended, the block growing by one slot when
// full.
void LoadEntries(IKFile* file, TVector<KBase7CCC::Entry*, 1>& list) {
    list.m_ui32NbElt = 1;
    list.m_pBlock = static_cast<KBase7CCC::Entry**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(KBase7CCC::Entry*))));
    uint32_t count = 0;
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        KBase7CCC::Entry* entry = new KBase7CCC::Entry();  // 0x00a3cd80 operator new, the seven words zeroed
        ReadU32LE(file, &entry->m_ui32HotSpot);
        ReadF32LE(file, &entry->m_fStart);
        ReadF32LE(file, &entry->m_fDuration);
        ReadF32LE(file, &entry->m_fRadiusFrom);
        uint32_t used = list.m_ui32NbUsedElt;
        if (list.m_ui32NbElt == used) {
            uint32_t capacity = used + 1;
            if (capacity == 0) capacity = 1;
            list.m_pBlock = static_cast<KBase7CCC::Entry**>(
                Mem_ReallocAligned16(list.m_pBlock, capacity * static_cast<uint32_t>(sizeof(KBase7CCC::Entry*))));
            list.m_ui32NbElt = capacity;
            used = list.m_ui32NbUsedElt;
        }
        list.m_pBlock[used] = entry;
        list.m_ui32NbUsedElt = list.m_ui32NbUsedElt + 1;
    }
}

// The start of both lists in vf50 (0x471e98.. / 0x471f78..): a sphere or swept sphere with a ramp keeps its radius
// (+0x14 / +0x18) and starts from +0x10 (0.001 when that is not above 0).
void StartRamp(KBase7CCC::Entry* entry) {
    const int32_t shape = entry->m_pVolume->GetShapeType();  // vt+0x70
    if (shape != IKBoundingVolume::kSphere && shape != IKBoundingVolume::kSweptSphere) return;
    if (entry->m_fDuration == kZero) return;
    IKBoundingVolume* volume = entry->m_pVolume;
    const float from = entry->m_fRadiusFrom;
    const float radius = volume->m_fRadius;
    entry->m_fRadiusTo = radius;
    entry->m_fRadiusSaved = radius;
    volume->m_fRadius = from > kZero ? from : kMinRadius;  // ble: a NaN takes 0.001
}

// The stop of both lists in vf54: a sphere or swept sphere with a ramp gets its kept radius back (0.001 when that is
// not above 0).
void StopRamp(KBase7CCC::Entry* entry) {
    const int32_t shape = entry->m_pVolume->GetShapeType();  // vt+0x70
    if (shape != IKBoundingVolume::kSphere && shape != IKBoundingVolume::kSweptSphere) return;
    if (entry->m_fDuration == kZero) return;
    const float saved = entry->m_fRadiusSaved;
    entry->m_pVolume->m_fRadius = saved > kZero ? saved : kMinRadius;  // ble: a NaN takes 0.001
}

CKSrvCollision* SrvCollision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }  // engine +0x58

}  // namespace

// 0x00472860 KBase7CCC_Destructor
KBase7CCC::~KBase7CCC() {
    for (ContactHistoryNode* node = m_pContacts; node != nullptr;) {  // back to the pool (free list 0x00ceaa74)
        ContactHistoryNode* next = node->m_pNext;
        ContactHistory_FreeNode(node);
        node = next;
    }
    m_pContacts = nullptr;
    if (m_vTargets.m_pBlock != nullptr) Mem_FreeAligned16(m_vTargets.m_pBlock);
    m_vTargets.m_pBlock = nullptr;
    m_vTargets.m_ui32NbUsedElt = 0;
    if (m_vVolumes.m_pBlock != nullptr) Mem_FreeAligned16(m_vVolumes.m_pBlock);
    m_vVolumes.m_ui32NbUsedElt = 0;
    m_vVolumes.m_pBlock = nullptr;
}

// 0x004712f8 KBase7CCC_ClearReferences (vt+0x10): every record deleted (both lists emptied) and the hit block deleted
// (the pointer is kept: BUG(original), a second Destroy deletes it again).
void KBase7CCC::Destroy() {
    for (uint32_t i = 0; i < m_vVolumes.m_ui32NbUsedElt; ++i) delete m_vVolumes.m_pBlock[i];  // 0x00a3ce18
    m_vVolumes.m_ui32NbUsedElt = 0;
    for (uint32_t i = 0; i < m_vTargets.m_ui32NbUsedElt; ++i) delete m_vTargets.m_pBlock[i];
    m_vTargets.m_ui32NbUsedElt = 0;
    if (m_pHitInfo != nullptr) delete m_pHitInfo;
}

// 0x00472148 KBase7CCC_Load: level files only: the animation dictionary, the attack volumes' records, the target volumes'
// records, four flag bytes (bits 0, 2, 3, 4; the whole byte shifted in) and the turn's top speed, acceleration and
// deceleration.
int32_t KBase7CCC::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pAnimations);
    LoadEntries(file, m_vVolumes);
    LoadEntries(file, m_vTargets);
    uint8_t byte = 0;
    ReadU8(file, &byte);
    m_ui32Flags = (m_ui32Flags & 0xfffffffeu) | byte;
    ReadU8(file, &byte);
    m_ui32Flags = (m_ui32Flags & 0xfffffffbu) | (static_cast<uint32_t>(byte) << 2);
    ReadU8(file, &byte);
    m_ui32Flags = (m_ui32Flags & 0xfffffff7u) | (static_cast<uint32_t>(byte) << 3);
    ReadU8(file, &byte);
    m_ui32Flags = (m_ui32Flags & 0xffffffefu) | (static_cast<uint32_t>(byte) << 4);
    ReadF32LE(file, &m_fTurnTopSpeed);
    ReadF32LE(file, &m_fTurnAccel);
    ReadF32LE(file, &m_fTurnDecel);
    return 1;
}

// 0x00470a10 (Ghidra IKSerializable_PostLoad): every record's volume from the colossus' hot spot record of its index
// (0x0046c320 CKHkColossus_GetHotSpotRecordByIndex_maybe; none: left as it is), the target volumes' from the record's
// +0x0c, the attack volumes' from its +0x08; no hook, no hero group, a new hit block (operator new 0x38).
int32_t KBase7CCC::PostLoad(int32_t /*type*/) {
    for (uint32_t i = 0; i < m_vTargets.m_ui32NbUsedElt; ++i) {
        const CKHkColossus::HotSpotRecord* record = m_pOwner->GetHotSpotRecordByIndex(m_vTargets.m_pBlock[i]->m_ui32HotSpot);
        if (record != nullptr) m_vTargets.m_pBlock[i]->m_pVolume = static_cast<IKBoundingVolume*>(record->m_pUnkC);
    }
    for (uint32_t i = 0; i < m_vVolumes.m_ui32NbUsedElt; ++i) {
        const CKHkColossus::HotSpotRecord* record = m_pOwner->GetHotSpotRecordByIndex(m_vVolumes.m_pBlock[i]->m_ui32HotSpot);
        if (record != nullptr) m_vVolumes.m_pBlock[i]->m_pVolume = static_cast<IKBoundingVolume*>(record->m_pUnk8);
    }
    m_pHook = nullptr;
    m_pHeroGroup = nullptr;
    m_pHitInfo = new HitInfo;  // 0x00a3cd80 operator new 0x38, not initialised
    return 1;
}

// 0x00471df8 CKColossusContextualAttackElement_StartAttack_maybe (vt+0x50): the time 0; the colossus plays the
// dictionary's first animation from 0 (when it has one); the attack volumes join the collision service carrying the hit
// block, the target volumes join it; every ramped sphere starts its ramp; the hero group from the game manager, bit 1
// (the animation's end) cleared, the turn state reset from the loaded speeds, the colossus' +0x4c 0, the hit block's
// +0x28 = 1 and +0x2c..+0x34 = 0; the hook (when there is one) woken in the game manager's meca group and shown.
void KBase7CCC::Vf50() {
    m_fTime = kZero;
    const uint32_t animation = static_cast<uint32_t>(static_cast<const CAnimationDictionary*>(m_pAnimations)->m_apAnimations[0]);
    if (CAnimationManager_GetAnimation(animation) != nullptr) {
        // r5 (restart) is not set: the caller's register. 0 here.
        static_cast<CAnimatedNode*>(m_pOwner->m_pKGLObject)->PlayAnim(static_cast<double>(kZero), animation, 0);  // 0x000c98b8
    }
    for (uint32_t i = 0; i < m_vVolumes.m_ui32NbUsedElt; ++i) {
        SrvCollision()->AddVolume(m_vVolumes.m_pBlock[i]->m_pVolume);  // 0x00192b80
        m_vVolumes.m_pBlock[i]->m_pVolume->m_unk1c = reinterpret_cast<IKSerializable*>(m_pHitInfo);
        StartRamp(m_vVolumes.m_pBlock[i]);
    }
    for (uint32_t i = 0; i < m_vTargets.m_ui32NbUsedElt; ++i) {
        SrvCollision()->AddVolume(m_vTargets.m_pBlock[i]->m_pVolume);  // 0x00192b80
        StartRamp(m_vTargets.m_pBlock[i]);
    }
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    m_pHeroGroup = static_cast<CKGrpS08Hero*>(manager->m_unk04[1]);  // +0x08
    m_ui32Flags = m_ui32Flags & 0xfffffffdu;
    m_afApproach[4] = kZero;  // +0x14 (the speed)
    m_pOwner->m_unk4C = kZero;
    m_afApproach[6] = kZero;  // +0x1c (the speed bonus)
    m_afApproach[2] = m_fTurnTopSpeed;  // +0x0c
    m_afApproach[0] = m_fTurnAccel;     // +0x04
    m_afApproach[1] = m_fTurnDecel;     // +0x08
    m_pHitInfo->m_unk30 = 0;
    m_pHitInfo->m_unk34 = 0;
    m_pHitInfo->m_unk2C = 0;
    m_pHitInfo->m_fUnk28 = kOne;
    if (m_pHook != nullptr) {
        SetObjectActiveInContext(g_pEngine->m_coreManager, m_pHook, 1, static_cast<IKBaseGroup*>(manager->m_unk04[2]));  // 0x0001cb10
        CSGLeaf* node = static_cast<CSGLeaf*>(m_pHook->m_pKGLObject);
        node->m_sgProperties = node->m_sgProperties & 0xfffffffbu;
    }
}

// 0x004713e8 CKColossusContextualAttackElement_vf54 (vt+0x54): every volume leaves the collision service and every
// ramped sphere gets its radius back; the hook (when there is one) put to sleep in the meca group and hidden.
void KBase7CCC::Vf54() {
    for (uint32_t i = 0; i < m_vVolumes.m_ui32NbUsedElt; ++i) {
        SrvCollision()->RemoveVolume(m_vVolumes.m_pBlock[i]->m_pVolume);  // 0x00192bc0
        StopRamp(m_vVolumes.m_pBlock[i]);
    }
    for (uint32_t i = 0; i < m_vTargets.m_ui32NbUsedElt; ++i) {
        SrvCollision()->RemoveVolume(m_vTargets.m_pBlock[i]->m_pVolume);  // 0x00192bc0
        StopRamp(m_vTargets.m_pBlock[i]);
    }
    if (m_pHook != nullptr) {
        CDefaultGameManager* manager = g_pEngine->m_gameManager;
        SetObjectActiveInContext(g_pEngine->m_coreManager, m_pHook, 0, static_cast<IKBaseGroup*>(manager->m_unk04[2]));  // 0x0001cb10
        CSGLeaf* node = static_cast<CSGLeaf*>(m_pHook->m_pKGLObject);
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    }
}

// 0x004706c0 CKColossusContextualAttackElement_vf60 (vt+0x60)
void KBase7CCC::Vf60(IKTime* frameClock) {
    m_fTime = m_fTime + frameClock->m_afDeltaTime[0];
    Vf6C(frameClock);
    Vf64(frameClock);
    Vf68(frameClock);
}

// 0x00470e20 KBaseC_vf64_2 (vt+0x64): unless the animation's end was reached (bit 1) without looping (bit 0), the
// colossus' animation runs on by dt; a non-looping one that would pass its end is put on its end and bit 1 set.
void KBase7CCC::Vf64(IKTime* frameClock) {
    CAnimatedNode* node = static_cast<CAnimatedNode*>(m_pOwner->m_pKGLObject);
    if ((m_ui32Flags & 1u) == 0 && (m_ui32Flags & 2u) != 0) return;
    if (!node->IsAnimEndReached(static_cast<double>(frameClock->m_afDeltaTime[0])) || (m_ui32Flags & 1u) != 0) {  // 0x000ca368
        node->AddAnimTime(static_cast<double>(frameClock->m_afDeltaTime[0]));  // 0x000c9638
        return;
    }
    node->SetCurrentAnimTime(node->GetCurrentAnimDuration());  // 0x000c9690 / 0x000c9768
    m_ui32Flags = (m_ui32Flags & 0xfffffffdu) | 2u;
}

// 0x00471930 KBaseC_vf68_2 (vt+0x68). Bit 3 (without bit 4): the yaw from the colossus' `at` axis to the first hero
// (Vec3_GetYawAngleFromX of both, wrapped to [0, 2 pi)) is approached from 0 with the colossus' turn speed (+0x4c), the
// step added to its yaw (+0x48, wrapped); the colossus faces its rest axis turned by that yaw and keeps the new yaw and
// speed. Bit 4: the yaw (+0x48) approaches 0 the same way (the speed +0x4c kept as it was).
void KBase7CCC::Vf68(IKTime* frameClock) {
    uint32_t flags = m_ui32Flags;
    if ((flags & 8u) != 0) {
        if ((flags & 0x10u) != 0) return;
        CKHkColossus* owner = m_pOwner;
        const RwFrame* ownFrame = static_cast<CSGMovable*>(owner->m_pKGLObject)->m_pRwFrame;
        const float yaw = owner->m_unk48;
        const float speed = owner->m_unk4C;
        const CVector3 at = {ownFrame->modelling.at.x, ownFrame->modelling.at.y, ownFrame->modelling.at.z};
        IKHook* hero = static_cast<IKHook*>(m_pHeroGroup->m_apHeros[0]);  // 0x002ca080 GetHeroByDragonIndex(group, 0)
        const RwFrame* heroFrame = static_cast<CSGMovable*>(hero->m_pKGLObject)->m_pRwFrame;
        ownFrame = static_cast<CSGMovable*>(m_pOwner->m_pKGLObject)->m_pRwFrame;
        CVector3 toHero;
        toHero.x = heroFrame->modelling.pos.x - ownFrame->modelling.pos.x;
        toHero.z = heroFrame->modelling.pos.z - ownFrame->modelling.pos.z;
        toHero.y = heroFrame->modelling.pos.y - ownFrame->modelling.pos.y;
        const float heroYaw = Vec3_GetYawAngleFromX(&toHero);  // 0x00244638
        const float atYaw = Vec3_GetYawAngleFromX(&at);
        const float target = WrapAngle(heroYaw - atYaw);
        m_afApproach[4] = speed;    // +0x14
        m_afApproach[5] = target;   // +0x18
        m_afApproach[3] = kZero;    // +0x10
        Math_ApproachAngleWithAccelDecel(frameClock->m_afDeltaTime[0], m_afApproach);  // 0x00243c88
        const float newYaw = WrapAngle(yaw + m_afApproach[3]);
        const float newSpeed = m_afApproach[4];
        SetOwnerAt(m_pOwner, newYaw);
        m_pOwner->m_unk48 = newYaw;
        m_pOwner->m_unk4C = newSpeed;
        flags = m_ui32Flags;
    }
    if ((flags & 0x10u) == 0) return;
    CKHkColossus* owner = m_pOwner;
    const float speed = owner->m_unk4C;
    m_afApproach[4] = speed;           // +0x14
    m_afApproach[3] = owner->m_unk48;  // +0x10
    m_afApproach[5] = kZero;           // +0x18
    Math_ApproachAngleWithAccelDecel(frameClock->m_afDeltaTime[0], m_afApproach);  // 0x00243c88
    const float newYaw = WrapAngle(m_afApproach[3]);
    SetOwnerAt(m_pOwner, newYaw);
    m_pOwner->m_unk48 = newYaw;
    m_pOwner->m_unk4C = speed;
}

// 0x00470778 KBaseC_vf6C_3 (vt+0x6c)
void KBase7CCC::Vf6C(IKTime* frameClock) {
    Vf78(frameClock);
    Vf74(frameClock);
    Vf70(frameClock);
}

// 0x00470b50 KBaseC_vf70_2 (vt+0x70): the attack volumes' collisions walked, each one's two volumes asked in the order of
// whose owner is this element; nothing is done with them.
void KBase7CCC::Vf70(IKTime* /*frameClock*/) {
    for (uint32_t i = 0; i < m_vVolumes.m_ui32NbUsedElt; ++i) {
        IKBoundingVolume* volume = m_vVolumes.m_pBlock[i]->m_pVolume;
        for (ICollision* c = static_cast<ICollision*>(volume->m_CollisionResList); c != nullptr; c = c->m_pNext) {
            if (static_cast<IKBoundingVolume*>(c->GetBoundingVolume1())->m_pOwner == this) {  // vt+0x00
                c->GetBoundingVolume1();
                c->GetBoundingVolume2();  // vt+0x04
            } else {
                c->GetBoundingVolume2();
                c->GetBoundingVolume1();
            }
        }
    }
}

// 0x00470f10 KBaseC_vf74_3 (vt+0x74): every collision of the target volumes with a contact set whose other volume (told
// apart by the colossus as owner) deals damage (property bit 3) and is new in the history (+0x50, times -1000) takes
// that volume's +0x1c object's vt+0x54 off the colossus' +0x54. The history ages at the end.
void KBase7CCC::Vf74(IKTime* frameClock) {
    for (uint32_t i = 0; i < m_vTargets.m_ui32NbUsedElt; ++i) {
        IKBoundingVolume* volume = m_vTargets.m_pBlock[i]->m_pVolume;
        for (ICollision* c = static_cast<ICollision*>(volume->m_CollisionResList); c != nullptr; c = c->m_pNext) {
            IKBoundingVolume* other;
            if (static_cast<IKBoundingVolume*>(c->GetBoundingVolume1())->m_pOwner == m_pOwner) {  // vt+0x00
                c->GetBoundingVolume1();
                other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2());  // vt+0x04
            } else {
                c->GetBoundingVolume2();
                other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume1());
            }
            if (c->HasContactSet() == 0) continue;  // vt+0x08
            if ((other->m_ui16PropertiesFlags & 8u) == 0) continue;
            if (ContactHistory_Touch(kContactTime, kContactTime, &m_pContacts, other, other->m_pOwner) == 0) continue;  // 0x0098f380
            CKHkColossus* owner = m_pOwner;
            const int32_t amount = static_cast<IKColossusHitSource_maybe*>(other->m_unk1c)->Vf54();  // vt+0x54
            owner->m_unk54 = owner->m_unk54 - static_cast<uint32_t>(amount);
        }
    }
    ContactHistory_Update(&m_pContacts, frameClock);  // 0x0098f430
}

// 0x00470cc0 KBaseC_vf78_2 (vt+0x78): vt+0x7c for every target record, then every attack record.
void KBase7CCC::Vf78(IKTime* /*frameClock*/) {
    for (uint32_t i = 0; i < m_vTargets.m_ui32NbUsedElt; ++i) Vf7C(m_vTargets.m_pBlock[i]);
    for (uint32_t i = 0; i < m_vVolumes.m_ui32NbUsedElt; ++i) Vf7C(m_vVolumes.m_pBlock[i]);
}

// 0x004711d0 KBaseC_vf7C (vt+0x7c): a ramped (duration above 0) sphere past its start time, or a swept sphere before
// it, gets the radius from +0x10 toward +0x14 at (time - start) / duration (the end radius from 1 on); 0.001 when the
// result is not above 0.
void KBase7CCC::Vf7C(Entry* entry) {
    if (entry == nullptr || entry->m_pVolume == nullptr) return;
    const int32_t shape = entry->m_pVolume->GetShapeType();  // vt+0x70
    const float duration = entry->m_fDuration;
    const float time = m_fTime;
    const float start = entry->m_fStart;
    if (shape == IKBoundingVolume::kSphere) {
        if (!(duration > kZero)) return;  // ble
        if (!(time > start)) return;      // ble
    } else {
        if (shape != IKBoundingVolume::kSweptSphere) return;
        if (!(duration > kZero)) return;  // ble
        if (!(start > time)) return;      // bgt
    }
    float radius = entry->m_fRadiusTo;
    const float from = entry->m_fRadiusFrom;
    const float t = (time - start) / duration;
    if (!(t >= kOne)) radius = ppc::fmadds(radius - from, t, from);  // cror gt|eq / bne: a NaN ramps
    entry->m_pVolume->m_fRadius = radius > kZero ? radius : kMinRadius;  // ble: a NaN takes 0.001
}
