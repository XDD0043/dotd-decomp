// Reconstructed original translation unit: 0x4eafb0-0x4eb8c8 (GAME_TOC1, main_toc1), 69 functions, 68 live.
// Primary owner: CKS08MaleforFireBreathAbilityHost (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4eafb0  CKS08MaleforFireBreathAbilityHost_maybe_Construct_2  (the constructor twice (one body))
//   [x] 0x4eb028  CKS08MaleforFireBreathAbilityHost_maybe_GetOwnerHook
//   [x] 0x4eb038  CKS08MaleforFireBreathAbilityHost_maybe_vfC
//   [x] 0x4eb040  CKS08MaleforFireBreathAbilityHost_maybe_vf1C
//   [x] 0x4eb098  CKS08MaleforFireBreathAbilityHost_maybe_vf20
//   [x] 0x4eb0f0  CKS08MaleforFireBreathAbilityHost_maybe_vf24
//   [x] 0x4eb148  CKS08MaleforFireBreathAbilityHost_maybe_vf30
//   [x] 0x4eb150  CKS08MaleforFireBreathAbilityHost_maybe_vf38
//   [x] 0x4eb158  CKS08MaleforFireBreathAbilityHost_maybe_vf3C
//   [x] 0x4eb160  CKS08MaleforFireBreathAbilityHost_maybe_vf40
//   [x] 0x4eb168  CKS08MaleforFireBreathAbilityHost_maybe_vf44
//   [x] 0x4eb170  CKS08MaleforFireBreathAbilityHost_maybe_vf50
//   [x] 0x4eb178  CKS08MaleforFireBreathAbilityHost_maybe_vf54
//   [x] 0x4eb180  CKS08MaleforFireBreathAbilityHost_maybe_vf5C
//   [x] 0x4eb188  CKS08MaleforFireBreathAbilityHost_maybe_vf60
//   [x] 0x4eb190  CKS08MaleforFireBreathAbilityHost_maybe_vf48
//   [x] 0x4eb198  CKS08MaleforFireBreathAbilityHost_maybe_vf64
//   [x] 0x4eb1a0  CKS08MaleforFireBreathAbilityHost_maybe_vf68
//   [x] 0x4eb1a8  CKS08MaleforFireBreathAbilityHost_maybe_vf70
//   [x] 0x4eb1b0  CKS08MaleforFireBreathAbilityHost_maybe_vf74
//   [x] 0x4eb1b8  CKS08MaleforFireBreathAbilityHost_maybe_vf6C
//   [x] 0x4eb1c0  CKS08MaleforFireBreathAbilityHost_maybe_vf78
//   [x] 0x4eb1c8  CKS08MaleforFireBreathAbilityHost_maybe_PlayAbilityAnim
//   [x] 0x4eb1e8  CKS08MaleforFireBreathAbilityHost_maybe_IsAbilityAnimPhaseDone_maybe
//   [x] 0x4eb208  CKS08MaleforFireBreathAbilityHost_maybe_vf84
//   [x] 0x4eb210  CKS08MaleforFireBreathAbilityHost_maybe_vf88
//   [x] 0x4eb218  CKS08MaleforFireBreathAbilityHost_maybe_IsAbilityButtonDown_maybe
//   [x] 0x4eb230  CKS08MaleforFireBreathAbilityHost_maybe_vf90
//   [x] 0x4eb238  CKS08MaleforFireBreathAbilityHost_maybe_vf94
//   [x] 0x4eb250  CKS08MaleforFireBreathAbilityHost_maybe_vf9C
//   [x] 0x4eb258  CKS08MaleforFireBreathAbilityHost_maybe_vfA0
//   [x] 0x4eb260  CKS08MaleforFireBreathAbilityHost_maybe_vfA4
//   [x] 0x4eb268  CKS08MaleforFireBreathAbilityHost_maybe_vfA8
//   [x] 0x4eb270  CKS08MaleforFireBreathAbilityHost_maybe_vfAC
//   [x] 0x4eb278  CKS08MaleforFireBreathAbilityHost_maybe_GetCollisionGroup
//   [x] 0x4eb280  CKS08MaleforFireBreathAbilityHost_maybe_GetCollisionMask
//   [x] 0x4eb288  CKS08MaleforFireBreathAbilityHost_maybe_ConsumeAbilityMana
//   [x] 0x4eb290  CKS08MaleforFireBreathAbilityHost_maybe_GetAbilityMana
//   [x] 0x4eb2a0  CKS08MaleforFireBreathAbilityHost_maybe_vfC0
//   [x] 0x4eb2a8  CKS08MaleforFireBreathAbilityHost_maybe_vfC4
//   [x] 0x4eb2b0  CKS08MaleforFireBreathAbilityHost_maybe_GetHotspot
//   [x] 0x4eb320  CKS08MaleforFireBreathAbilityHost_maybe_vfD4
//   [x] 0x4eb328  CKS08MaleforFireBreathAbilityHost_maybe_vfD8
//   [x] 0x4eb330  CKS08MaleforFireBreathAbilityHost_maybe_vfE4
//   [x] 0x4eb338  CKS08MaleforFireBreathAbilityHost_maybe_vfE8
//   [x] 0x4eb340  CKS08MaleforFireBreathAbilityHost_maybe_vfEC
//   [x] 0x4eb348  CKS08MaleforFireBreathAbilityHost_maybe_vfF0
//   [x] 0x4eb350  CKS08MaleforFireBreathAbilityHost_maybe_GetAbilityLevelIndex
//   [x] 0x4eb358  CKS08MaleforFireBreathAbilityHost_maybe_vfF8
//   [x] 0x4eb360  CKS08MaleforFireBreathAbilityHost_maybe_vfFC
//   [x] 0x4eb368  CKS08MaleforFireBreathAbilityHost_maybe_vf100
//   [x] 0x4eb370  CKS08MaleforFireBreathAbilityHost_maybe_GetAttachmentSets
//   [ ] 0x4eb380  CKS08MaleforFireBreathAbilityHost_maybe_Destructor_2  [dead]
//   [x] 0x4eb390  StaticInitAndDestruction_4eb390  (the two file statics below)
//   [ ] 0x4eb3c0  _GLOBAL__D_4eb3c0
//   [ ] 0x4eb3d0  _GLOBAL__I_4eb3d0
//   [x] 0x4eb3e0  CKS08MaleforFireBreathAbilityHost_maybe_vfDC
//   [x] 0x4eb408  CKS08MaleforFireBreathAbilityHost_maybe_vf98
//   [x] 0x4eb430  CKS08MaleforFireBreathAbilityHost_maybe_vf4C
//   [x] 0x4eb458  CKS08MaleforFireBreathAbilityHost_maybe_vf14
//   [x] 0x4eb480  CKS08MaleforFireBreathAbilityHost_maybe_GetOwnerUp_maybe
//   [x] 0x4eb500  CKS08MaleforFireBreathAbilityHost_maybe_GetOwnerRight_maybe
//   [x] 0x4eb580  CKS08MaleforFireBreathAbilityHost_maybe_GetOwnerForward_maybe
//   [x] 0x4eb600  CKS08MaleforFireBreathAbilityHost_maybe_GetHotspotPosition
//   [x] 0x4eb710  CKS08MaleforFireBreathAbilityHost_maybe_GetOwnerPosition
//   [x] 0x4eb790  CKS08MaleforFireBreathAbilityHost_maybe_ComputeAimDirection_maybe
//   [x] 0x4eb810  CKS08MaleforFireBreathAbilityHost_maybe_Construct
//   [x] 0x4eb888  CKS08MaleforFireBreathAbilityHost_maybe_DeletingDestructor  (the implicit destructor (the base vtable, delete))
//   [x] 0x4eb8b8  CKS08MaleforFireBreathAbilityHost_maybe_Destructor  (the implicit destructor (the base vtable, delete))
#include "Spyro2008/misc/CKS08MaleforFireBreathAbilityHost.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/logic/CKS08MaleforFireBreath.h"
#include "k2000/hooks/CKHkGolem.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/scenegraph/CSGMovable.h"

namespace {
// The owner's node frame (+0x1c, its +0x04), its stored LTM.
const RwMatrix* OwnerLtm(IKSerializable* owner) {
    return FrameLtm(static_cast<CSGMovable*>(static_cast<IKHook*>(owner)->m_pKGLObject)->m_pRwFrame);
}

// 0x004eb390 StaticInitAndDestruction_4eb390 (_GLOBAL__I_4eb3d0): two file statics (0x00ceb230, 0x00ceb234) set to
// -1.0f. Nothing in the game reads them.
[[maybe_unused]] float s_unkceb230 = -1.0f;
[[maybe_unused]] float s_unkceb234 = -1.0f;
}  // namespace

// 0x004eb810 CKS08MaleforFireBreathAbilityHost_maybe_Construct
CKS08MaleforFireBreathAbilityHost::CKS08MaleforFireBreathAbilityHost(IKSerializable* attack) {
    if (attack->IsKindOfClass(0xac4c) != 0) m_pAttack = static_cast<CKS08MaleforFireBreath*>(attack);  // vt+0x08
}

// 0x004eb028 CKS08MaleforFireBreathAbilityHost_maybe_GetOwnerHook: the attack's golem.
IKSerializable* CKS08MaleforFireBreathAbilityHost::GetOwner() { return m_pAttack->m_unk04; }

// 0x004eb710 CKS08MaleforFireBreathAbilityHost_maybe_GetOwnerPosition (through vt+0x08)
CVector3 CKS08MaleforFireBreathAbilityHost::GetOwnerPosition() {
    const RwV3d& pos = OwnerLtm(GetOwner())->pos;
    return CVector3{pos.x, pos.y, pos.z};
}

// 0x004eb458 CKS08MaleforFireBreathAbilityHost_maybe_vf14: the null vector (0x00c50d64).
CVector3 CKS08MaleforFireBreathAbilityHost::GetOwnerGroundPoint() { return CVector3{0.0f, 0.0f, 0.0f}; }

// 0x004eb580 CKS08MaleforFireBreathAbilityHost_maybe_GetOwnerForward_maybe
CVector3 CKS08MaleforFireBreathAbilityHost::GetHeroForward() {
    const RwV3d& at = OwnerLtm(GetOwner())->at;
    return CVector3{at.x, at.y, at.z};
}

// 0x004eb040 CKS08MaleforFireBreathAbilityHost_maybe_vf1C: vt+0x18.
CVector3 CKS08MaleforFireBreathAbilityHost::GetHeroVec135c() { return GetHeroForward(); }

// 0x004eb098 CKS08MaleforFireBreathAbilityHost_maybe_vf20: vt+0x18.
CVector3 CKS08MaleforFireBreathAbilityHost::Vf20() { return GetHeroForward(); }

// 0x004eb0f0 CKS08MaleforFireBreathAbilityHost_maybe_vf24: vt+0x18.
CVector3 CKS08MaleforFireBreathAbilityHost::GetAimDirection(int32_t /*raw*/) { return GetHeroForward(); }

// 0x004eb500 CKS08MaleforFireBreathAbilityHost_maybe_GetOwnerRight_maybe
CVector3 CKS08MaleforFireBreathAbilityHost::GetOwnerRight() {
    const RwV3d& right = OwnerLtm(GetOwner())->right;
    return CVector3{right.x, right.y, right.z};
}

// 0x004eb480 CKS08MaleforFireBreathAbilityHost_maybe_GetOwnerUp_maybe
CVector3 CKS08MaleforFireBreathAbilityHost::GetOwnerUp() {
    const RwV3d& up = OwnerLtm(GetOwner())->up;
    return CVector3{up.x, up.y, up.z};
}

// 0x004eb430 CKS08MaleforFireBreathAbilityHost_maybe_vf4C: the null vector.
CVector3 CKS08MaleforFireBreathAbilityHost::GetOwnerVelocity() { return CVector3{0.0f, 0.0f, 0.0f}; }

// 0x004eb790 CKS08MaleforFireBreathAbilityHost_maybe_ComputeAimDirection_maybe: the owner's LTM at.
CVector3 CKS08MaleforFireBreathAbilityHost::ComputeAimDirection(float /*cone*/, CKAbilityElement* /*ability*/,
                                                                IKSerializable* /*aimCone*/) {
    const RwV3d& at = OwnerLtm(GetOwner())->at;
    return CVector3{at.x, at.y, at.z};
}

// 0x004eb408 CKS08MaleforFireBreathAbilityHost_maybe_vf98: the null vector.
CVector3 CKS08MaleforFireBreathAbilityHost::GetTargetPoint(float* /*weight*/) { return CVector3{0.0f, 0.0f, 0.0f}; }

// 0x004eb2b0 CKS08MaleforFireBreathAbilityHost_maybe_GetHotspot: the owner's (vt+0x08) vt+0xf8 with 11.
IKSerializable* CKS08MaleforFireBreathAbilityHost::GetHotspot(uint32_t /*index*/) {
    return static_cast<CKHkGolem*>(GetOwner())->GetReference(0xb);  // 0x009c5790
}

// 0x004eb600 CKS08MaleforFireBreathAbilityHost_maybe_GetHotspotPosition
CVector3 CKS08MaleforFireBreathAbilityHost::GetHotspotPosition(uint32_t index) {
    CSGHotSpot* spot = static_cast<CSGHotSpot*>(GetHotspot(index));  // vt+0xcc
    if (spot != nullptr) {
        CVector3 at{};
        spot->GetWorldPosition(&at);  // 0x000ce790
        return at;
    }
    const RwV3d& pos = OwnerLtm(GetOwner())->pos;
    return CVector3{pos.x, pos.y, pos.z};
}

// 0x004eb3e0 CKS08MaleforFireBreathAbilityHost_maybe_vfDC: the null vector.
CVector3 CKS08MaleforFireBreathAbilityHost::GetTargetAimPoint(int32_t /*fromHotSpot*/, uint8_t /*clampHeight*/) {
    return CVector3{0.0f, 0.0f, 0.0f};
}

// 0x004eb370 CKS08MaleforFireBreathAbilityHost_maybe_GetAttachmentSets: the attack's +0x98.
IKSerializable* CKS08MaleforFireBreathAbilityHost::GetAttachmentSets() {
    return reinterpret_cast<IKSerializable*>(&m_pAttack->m_unk98[0]);
}
