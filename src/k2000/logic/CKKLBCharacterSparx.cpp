// CKKLBCharacterSparx.cpp - reconstructed original translation unit 0x450480-0x450df0 (GAME_TOC1, main_toc1), 39 functions, 36 live.
// Primary class: CKKLBCharacterSparx  key 0x9f8c  category Logic  size 0x14  vtable 0xb26db0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x450480  CKKLBCharacterSparx_Delete
//   [x] 0x4504d0  CKKLBCharacterSparx_Construct  [dead]
//   [ ] 0x4504e0  CKKLBCharacterSparx_Construct_2  [dead]
//   [x] 0x4504f0  CKKLBCharacterSparx_Save
//   [x] 0x4504f8  CKKLBCharacterSparx_vf50
//   [x] 0x450528  CKKLBCharacterSparx_vf58
//   [x] 0x450548  CKKLBCharacterSparx_vf60
//   [x] 0x450550  CKKLBCharacterSparx_vf88
//   [x] 0x450580  CKKLBCharacterSparx_SetTarget_maybe
//   [x] 0x4505b0  CKKLBCharacterSparx_vf98
//   [x] 0x4505e0  CKKLBCharacterSparx_vf7C
//   [x] 0x450610  CKKLBCharacterSparx_MoveTowardTarget_maybe
//   [x] 0x450640  CKKLBCharacterSparx_vf70
//   [x] 0x450668  CKKLBCharacterSparx_vf64
//   [x] 0x450690  CKKLBCharacterSparx_vf54
//   [x] 0x450708  CKKLBCharacterSparx_DeleteArray
//   [x] 0x4507b0  RegisterCKKLBCharacterSparxClass (RegisterAllClasses: ClassTable.inc)
//   [x] 0x450838  _GLOBAL__D_450838 (RegisterCKKLBCharacterSparxClass(0, 0xffff): nothing)
//   [x] 0x450848  _GLOBAL__I_450848 (RegisterCKKLBCharacterSparxClass(1, 0xffff))
//   [x] 0x450858  CKKLBCharacterSparx_vf84
//   [x] 0x450888  CKKLBCharacterSparx_vf80
//   [x] 0x4508c0  CKKLBCharacterSparx_vf94
//   [x] 0x450908  CKKLBCharacterSparx_vfA4
//   [x] 0x450938  CKKLBCharacterSparx_vfA0
//   [x] 0x450950  CKKLBCharacterSparx_vf5C
//   [x] 0x450988  CKKLBCharacterSparx_vf6C
//   [x] 0x450a28  CKKLBCharacterSparx_vf68
//   [x] 0x450a78  CKKLBCharacterSparx_vf78
//   [x] 0x450aa8  CKKLBCharacterSparx_vf9C
//   [x] 0x450ab8  CKKLBCharacterSparx_vf8C
//   [x] 0x450b30  CKKLBCharacterSparx_CreateArray
//   [x] 0x450bc8  CKKLBCharacterSparx_Create
//   [x] 0x450c00  CKKLBCharacterSparx_RecursiveRegistration
//   [x] 0x450c08  CKKLBCharacterSparx_PostLoad
//   [x] 0x450c10  CKKLBCharacterSparx_Destroy
//   [x] 0x450c18  CKKLBCharacterSparx_Load
//   [ ] 0x450d68  CKKLBCharacterSparx_Destructor_2  [dead]
//   [x] 0x450d88  CKKLBCharacterSparx_DeletingDestructor
//   [x] 0x450dd0  CKKLBCharacterSparx_Destructor
//
//   [x] 0x9c3cd0  CKKLBCharacterSparx_GetClassType  [inline]
//   [x] 0x9c3cd8  CKKLBCharacterSparx_GetClassID  [inline]
//   [x] 0x9c3ce0  CKKLBCharacterSparx_vfA8  [inline]
//   [x] 0x9c3ce8  CKKLBCharacterSparx_IsKindOfClass  [inline]
#include "k2000/logic/CKKLBCharacterSparx.h"

#include <cstdint>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Sparx.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/components/CKMoveCpntUpdater.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

namespace {

// 0x00c50d64 the null vector (zero in the EBOOT's BSS; a static initialiser fills it).
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};

CKHkS08Sparx* SparxOf(const CKKLBCharacterSparx* character) { return static_cast<CKHkS08Sparx*>(character->m_pSparx); }

// The game manager's hero group (+0x08; GetHeroGroup 0x276f70).
IKSerializable* HeroGroup() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->m_unk04[1]; }

}  // namespace

// 0x004504f8 CKKLBCharacterSparx_vf50: the hero group's Sparx (its +0xad0), or none without a group.
void CKKLBCharacterSparx::Vf50() {
    IKSerializable* group = HeroGroup();
    if (group != nullptr) {
        m_pSparx = static_cast<CKGrpS08Hero*>(group)->m_pUnkad0;
        return;
    }
    m_pSparx = nullptr;
}

// 0x00450690 CKKLBCharacterSparx_vf54: the Sparx lets go of this beacon when it is its current target (+0xb8):
// CKHkS08Sparx_ClearTargetIfCurrentAndPlayAnim_maybe 0x3f48a8 and CKHkS08Sparx_StopMoveUpdaterIfCurrent_maybe 0x3f4318
// with this character's move updater (+0x0c).
void CKKLBCharacterSparx::Vf54() {
    CKHkS08Sparx* sparx = SparxOf(this);
    if (m_pBeacon != sparx->m_pTargetB8) return;
    sparx->ClearTargetIfCurrentAndPlayAnim(m_pBeacon);
    sparx->StopMoveUpdaterIfCurrent(static_cast<CKMoveCpntUpdater*>(m_pMoveUpdater));
}

// 0x00450528 CKKLBCharacterSparx_vf58: a Sparx is bound (the srawi / xor / subf form of `!= 0`).
int32_t CKKLBCharacterSparx::Vf58() { return m_pSparx != nullptr ? 1 : 0; }

// 0x00450950 CKKLBCharacterSparx_vf5C: the LTM position (+0x80 of the frame) of the Sparx's node.
CVector3 CKKLBCharacterSparx::Vf5C() {
    const RwFrame* frame = static_cast<CSGMovable*>(SparxOf(this)->m_pKGLObject)->m_pRwFrame;
    CVector3 position;
    position.x = frame->ltm.pos.x;
    position.y = frame->ltm.pos.y;
    position.z = frame->ltm.pos.z;
    return position;
}

// 0x00450668 CKKLBCharacterSparx_vf64: the Sparx takes the direction (CKHkS08Sparx_SetDirectionVec_maybe 0x3f46b0).
void CKKLBCharacterSparx::Vf64(const float* direction) { SparxOf(this)->SetDirectionVec(direction); }

// 0x00450a28 CKKLBCharacterSparx_vf68: the goal at `position` with the null direction (a copy of 0x00c50d64) and
// `speed` (CKHkS08Sparx_SetMoveGoalPosDirFloat70_maybe 0x3f4850; `unused` goes on as its fifth word, never read).
void CKKLBCharacterSparx::Vf68(const CVector3* position, float speed, int32_t /*unused*/) {
    const CVector3 direction = kNullVector;
    SparxOf(this)->SetMoveGoal(position, &direction, speed);
}

// 0x00450988 CKKLBCharacterSparx_vf6C: the goal at `position` facing a copy of `direction`, at twice the Sparx's default
// speed (+0x2c, fadds) when `fast`, else the default (-1, TOC +0x541c).
void CKKLBCharacterSparx::Vf6C(const CVector3* position, const CVector3* direction, int32_t fast) {
    CKHkS08Sparx* sparx = SparxOf(this);
    const float speed = sparx->m_fl2c;
    const CVector3 copy = *direction;
    sparx->SetMoveGoal(position, &copy, fast != 0 ? speed + speed : -1.0f);
}

// 0x00450640 CKKLBCharacterSparx_vf70: CKHkS08Sparx_SetPositionAndDirection_maybe 0x3f4cc0.
void CKKLBCharacterSparx::Vf70(const CVector3* position, const CVector3* direction) {
    SparxOf(this)->SetPositionAndDirection(position, direction);
}

// 0x00450610 CKKLBCharacterSparx_MoveTowardTarget_maybe: CKHkS08Sparx_MoveTowardTarget_maybe 0x3f5c38 with the clock's dt.
uint8_t CKKLBCharacterSparx::MoveTowardTarget(IKTime* clock) { return SparxOf(this)->MoveTowardTarget(clock->m_afDeltaTime[0]); }

// 0x00450a78 CKKLBCharacterSparx_vf78: the same body as vt+0x74.
uint8_t CKKLBCharacterSparx::Vf78(IKTime* clock) { return SparxOf(this)->MoveTowardTarget(clock->m_afDeltaTime[0]); }

// 0x004505e0 CKKLBCharacterSparx_vf7C: the Sparx node's animation at its end after `dt` (CAnimatedNode_IsAnimEndReached_maybe
// 0xca368).
uint8_t CKKLBCharacterSparx::Vf7C(double dt) {
    return static_cast<CAnimatedNode*>(SparxOf(this)->m_pKGLObject)->IsAnimEndReached(dt) ? 1 : 0;
}

// 0x00450888 CKKLBCharacterSparx_vf80: the Sparx's node plays dictionary animation `animation` from 0 (TOC +0x5438), no
// restart (CAnimatedNode_PlayAnim_maybe 0xc98b8).
void CKKLBCharacterSparx::Vf80(uint32_t animation) {
    static_cast<CAnimatedNode*>(SparxOf(this)->m_pKGLObject)->PlayAnim(0.0, animation, 0);
}

// 0x00450858 CKKLBCharacterSparx_vf84: the Sparx's node advances its animation by `dt` (CAnimatedNode_AddAnimTime_maybe).
void CKKLBCharacterSparx::Vf84(double dt) { static_cast<CAnimatedNode*>(SparxOf(this)->m_pKGLObject)->AddAnimTime(dt); }

// 0x00450550 CKKLBCharacterSparx_vf88: the Sparx's +0x54 bit 2 (its node animates) = `still` ^ 1 (the whole word
// shifted, no mask).
void CKKLBCharacterSparx::Vf88(uint32_t still) {
    CKHkS08Sparx* sparx = SparxOf(this);
    sparx->m_ui32Flags = (sparx->m_ui32Flags & 0xfffffffbu) | ((still ^ 1u) << 2);
}

// 0x00450ab8 CKKLBCharacterSparx_vf8C: the Sparx's goal reset to its position (0x3f47f8), +0x54 bit 2 = `still` ^ 1
// (the byte's bits, masked 0x3fc), then this character's move updater starts driving it (0x3f4938).
void CKKLBCharacterSparx::Vf8C(uint8_t still) {
    CKHkS08Sparx* sparx = SparxOf(this);
    sparx->ResetMoveTargetToCurrentPosition();
    sparx = SparxOf(this);
    sparx->m_ui32Flags = (sparx->m_ui32Flags & 0xfffffffbu) | ((static_cast<uint32_t>(still ^ 1u) << 2) & 0x3fcu);
    SparxOf(this)->StartMoveUpdater(static_cast<CKMoveCpntUpdater*>(m_pMoveUpdater));
}

// 0x00450580 CKKLBCharacterSparx_SetTarget_maybe: CKHkS08Sparx_SetTarget_maybe 0x3f4268 with this character's beacon.
uint8_t CKKLBCharacterSparx::SetTarget() { return SparxOf(this)->SetTarget(m_pBeacon); }

// 0x004508c0 CKKLBCharacterSparx_vf94: hero 0's path-finding character (GetHeroByDragonIndex 0x2ca080 of the game
// manager's hero group, IKHkHero_GetPtr3E0_maybe 0x361a30: +0x3e0).
CPFCharacter* CKKLBCharacterSparx::Vf94() {
    IKHkHero* hero = static_cast<IKHkHero*>(static_cast<IKGrpHero*>(HeroGroup())->m_apHeros[0]);
    return &hero->m_PFCharacter;
}

// 0x004505b0 CKKLBCharacterSparx_vf98: with `reset`, the Sparx's goal reset to its position (0x3f47f8).
void CKKLBCharacterSparx::Vf98(int32_t reset) {
    if (reset != 0) SparxOf(this)->ResetMoveTargetToCurrentPosition();
}

// 0x00450aa8 CKKLBCharacterSparx_vf9C: the Sparx's target (+0xb8).
IKSerializable* CKKLBCharacterSparx::Vf9C() { return SparxOf(this)->m_pTargetB8; }

// 0x00450908 CKKLBCharacterSparx_vfA4: the node (+0x1c) of the hero group's Sparx (+0xad0), null without one.
IKSerializable* CKKLBCharacterSparx::VfA4() {
    IKSerializable* sparx = static_cast<CKGrpS08Hero*>(HeroGroup())->m_pUnkad0;
    if (sparx == nullptr) return nullptr;
    return static_cast<CKHkS08Sparx*>(sparx)->m_pKGLObject;
}

// 0x00450c18 CKKLBCharacterSparx_Load
int32_t CKKLBCharacterSparx::Load(IKFile* file, int32_t type) {
    CKKLBCharacterBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pMoveCpnt);
    IKFile_ReadRef(file, &m_pMoveUpdater);
    return 1;
}

// 0x00450938 CKKLBCharacterSparx_vfA0
const CMatrix34* CKKLBCharacterSparx::VfA0() {
    const CSGMovable* node = static_cast<CSGMovable*>(SparxOf(this)->m_pKGLObject);
    return reinterpret_cast<const CMatrix34*>(&node->m_pRwFrame->ltm);
}
