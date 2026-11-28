// CKHkS08ClampGun.cpp - reconstructed original translation unit 0x486570-0x48c7a0 (GAME_TOC1, main_toc1), 58 functions, 45 live.
// Primary class: CKHkS08ClampGun  key 0x2c42  category Hook  size 0x158  vtable 0xb27df0
// Other owners: Vec3 (2), HeroGroup (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x486570  CKHkS08ClampGun_Delete
//   [x] 0x4865c0  CKHkS08ClampGun_vfC8  (ApplyStatePreset, vt+0xc8)
//   [ ] 0x4865f8  CKHkS08ClampGun_CountAttachedClamps_maybe  [dead]
//   [ ] 0x486650  CKHkS08ClampGun_AnyEntryFlagged_maybe  [dead]
//   [x] 0x4866c8  CKHkS08ClampGun_GetTriggerProp96  (GetInfo's value 0x96 accessor)
//   [x] 0x4866f0  CKHkS08ClampGun_vfCC
//   [ ] 0x4866f8  CKHkS08ClampGun_ReleaseFlaggedClampsWithFx_maybe  [dead]
//   [ ] 0x4867f8  CKHkS08ClampGun_ReleaseClampAt_maybe  [dead]
//   [ ] 0x486868  HeroGroup_IsExternallyLockedOrMissing_maybe  [dead]
//   [ ] 0x4868b8  CKHkS08ClampGun_GetRandomSpreadAngle_maybe  [dead]
//   [ ] 0x486920  CKHkS08ClampGun_AreAllHeroesWithinRadius_maybe  [dead: no pointer to its descriptor 0xbc3128, no call]
//   [ ] 0x486a48  CKHkS08ClampGun_AreAllHeroesBeyondRadius_maybe  [dead: no pointer to its descriptor 0xbc3130, no call]
//   [ ] 0x486b70  CKHkS08ClampGun_InitCollisionVolume_maybe  [dead]
//   [ ] 0x486c30  Vec3_YawDifferenceWrappedFromZ_maybe  [dead]
//   [x] 0x486cc0  CKHkS08ClampGun_UpdateTurnSound_maybe  (UpdateTurnSound)
//   [x] 0x486e60  CKHkS08ClampGun_TickTimerAndPlayImpactFx_maybe  (TakeDamage)
//   [x] 0x4871b0  CKHkS08ClampGun_ProcessContacts_maybe  (ProcessContacts)
//   [x] 0x4873f0  CKHkS08ClampGun_SetDefaultState  (SetDefaultState, vt+0x38)
//   [x] 0x487430  CKHkS08ClampGun_Resume  (inherited: IKHook's Resume)
//   [x] 0x487458  CKHkS08ClampGun_Pause  (inherited: IKHook's Pause)
//   [x] 0x487480  CKHkS08ClampGun_Start  (Start, vt+0x50)
//   [x] 0x4874d8  CKHkS08ClampGun_GetInfo  (GetInfo, vt+0x40)
//   [ ] 0x4875b8  CKHkS08ClampGun_Save
//   [x] 0x4875e0  CKHkS08ClampGun_RecursiveRegistration  (inherited: CKHkActorBase's)
//   [x] 0x487608  CKHkS08ClampGun_Construct  [dead]
//   [x] 0x487688  CKHkS08ClampGun_DeleteArray
//   [ ] 0x487728  RegisterCKHkS08ClampGunClass
//   [ ] 0x4877b0  _GLOBAL__D_4877b0
//   [ ] 0x4877c0  _GLOBAL__I_4877c0
//   [x] 0x4877d0  CKHkS08ClampGun_vfD0
//   [x] 0x487818  CKHkS08ClampGun_Destroy  (Destroy, vt+0x10)
//   [x] 0x487898  CKHkS08ClampGun_SM140_State1_Cooldown_maybe  (SalvoState1, the salvo table +0x140)
//   [x] 0x4878f8  CKHkS08ClampGun_OnDeactivate  (VfA4, vt+0xa4)
//   [x] 0x487a00  CKHkS08ClampGun_DeletingDestructor  (the destructor; delete)
//   [x] 0x487ac0  CKHkS08ClampGun_OnActivate  (VfA0, vt+0xa0)
//   [ ] 0x487cb8  CKHkS08ClampGun_Construct_2  [dead]
//   [ ] 0x487d38  CKHkS08ClampGun_SetupSound0_maybe  [dead]
//   [x] 0x487df8  CKHkS08ClampGun_Destructor  (~CKHkS08ClampGun)
//   [ ] 0x487ea8  CKHkS08ClampGun_BaseDestructor  [dead: no pointer to its descriptor 0xbc3278, no call]
//   [ ] 0x487f58  CKHkS08ClampGun_ReleaseUnflaggedClamps_maybe  [dead]
//   [ ] 0x488018  CKHkS08ClampGun_ReleaseAllClamps_maybe  [dead]
//   [x] 0x4880d0  CKHkS08ClampGun_Stop  (Stop, vt+0x68)
//   [x] 0x488190  CKHkS08ClampGun_CreateArray
//   [x] 0x4882a0  CKHkS08ClampGun_Create
//   [x] 0x488330  CKHkS08ClampGun_ComputeBallisticSpeed_maybe  (ComputeBallisticSpeed)
//   [x] 0x488490  CKHkS08ClampGun_PostLoad  (PostLoad, vt+0x30)
//   [x] 0x488558  CKHkS08ClampGun_MessageProc  (MessageProc, vt+0x1c)
//   [x] 0x488738  CKHkS08ClampGun_AimAtHeroesMidpoint_maybe  (AimAtHeroesMidpoint)
//   [x] 0x488b10  CKHkS08ClampGun_RotateTowardPresetYaw_maybe  (RotateTowardPresetYaw)
//   [x] 0x488f98  CKHkS08ClampGun_RotateTowardTarget_maybe  (RotateTowardTarget)
//   [ ] 0x4893c0  Vec3_RotateYawFlatNormalized_2_maybe  [dead: no pointer to its descriptor 0xbc3350, no call]
//   [x] 0x489690  CKHkS08ClampGun_Load
//   [x] 0x48a1c0  CKHkS08ClampGun_Restart  (Restart, vt+0x54)
//   [x] 0x48a560  CKHkS08ClampGun_Update  (Update, vt+0x7c)
//   [x] 0x48ab98  CKHkS08ClampGun_FireShot_maybe  (FireShot)
//   [x] 0x48b4f8  CKHkS08ClampGun_FireSalvoState_maybe  (SalvoState0, the salvo table +0x140)
//   [x] 0x48b680  CKHkS08ClampGun_SM128_State0  (State0, the table +0x128)
//   [x] 0x48bc30  CKHkS08ClampGun_SM128_State1  (State1, the table +0x128)
//
//   [ ] 0x9c48d0  CKHkS08ClampGun_IsKindOfClass  [inline]
//   [ ] 0x9c4928  CKHkS08ClampGun_GetClassType  [inline]
//   [ ] 0x9c4930  CKHkS08ClampGun_GetClassID  [inline]
//   [x] 0x9c4938  KStub_ReturnArg4_9c4938  (SalvoState2 in the header: the salvo machine's idle state)
#include "Spyro2008/hooks/CKHkS08ClampGun.h"
#include "k2000/scenegraph/CSGLeaf.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x00489690 CKHkS08ClampGun_Load: the actor base, then the level data (type 0 only). The trigger
// starter is loaded with type 0.
int32_t CKHkS08ClampGun::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fUnk44);
        ReadF32LE(file, &m_fUnk40);
        ReadF32LE(file, &m_fUnk48);
        ReadF32LE(file, &m_fUnk4C);
        ReadF32LE(file, &m_fUnk54);
        ReadF32LE(file, &m_fUnk58);
        ReadF32LE(file, &m_fUnk60);
        IKFile_ReadRef(file, &m_pUnk28);
        ReadU8(file, &m_unk5D);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        // BUG(original): a new block of capacity 1 replaces the old one (leaked); the length is not reset.
        m_vUnkB4.m_ui32NbElt = 1;
        m_vUnkB4.m_pBlock = static_cast<SElem**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(SElem*))));
        for (uint32_t i = 0; i < count; ++i) {
            SElem* elem = new SElem;  // OperatorNew(0xc)
            elem->m_fUnk0 = 0.0f;
            elem->m_unk4 = 0;
            elem->m_unk8 = 0;
            elem->m_pad9[0] = elem->m_pad9[1] = elem->m_pad9[2] = 0;
            ReadF32LE(file, &elem->m_fUnk0);
            elem->m_unk4 = 0;
            elem->m_unk8 = 0;
            const uint32_t used = m_vUnkB4.m_ui32NbUsedElt;
            if (m_vUnkB4.m_ui32NbElt == used) {
                uint32_t capacity = used + 1;
                uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(SElem*));
                if (capacity == 0) {
                    capacity = 1;
                    bytes = static_cast<uint32_t>(sizeof(SElem*));
                }
                m_vUnkB4.m_pBlock = static_cast<SElem**>(Mem_ReallocAligned16(m_vUnkB4.m_pBlock, bytes & ~3u));
                m_vUnkB4.m_ui32NbElt = capacity;
            }
            m_vUnkB4.m_pBlock[m_vUnkB4.m_ui32NbUsedElt] = elem;
            m_vUnkB4.m_ui32NbUsedElt = m_vUnkB4.m_ui32NbUsedElt + 1;
        }
        IKFile_ReadRef(file, &m_pUnkD8);
        IKFile_ReadRef(file, &m_pUnk38);
        m_unkDC.Load(file, K_LEVEL_PLATEFORMS);
        IKFile_ReadRef(file, &m_pUnk24);
        IKFile_ReadRef(file, &m_pUnkEC);
        IKFile_ReadRef(file, &m_pUnkF4);
        IKFile_ReadRef(file, &m_pUnk20);
        IKFile_ReadRef(file, &m_pUnkD4);
        ReadF32LE(file, &m_fUnk98);
        ReadF32LE(file, &m_fUnk9C);
        ReadF32LE(file, &m_fUnkA0);
        ReadF32LE(file, &m_fUnk84);
        IKFile_ReadRef(file, &m_pUnkFC);
        ReadF32LE(file, &m_fUnk8C);
        IKFile_ReadRef(file, &m_pUnk104);
        ReadF32LE(file, &m_fUnk10C);
        ReadU32LE(file, &m_unk110);
        ReadF32LE(file, &m_fUnk114);
        ReadF32LE(file, &m_fUnk90);
        ReadU8(file, &m_unk118);
        ReadU8(file, &m_unk119);
        ReadU8(file, &m_unk11A);
        ReadU8(file, &m_unk11C);
        ReadU8(file, &m_unk11D);
        ReadU8(file, &m_unk11E);
        IKFile_ReadRef(file, &m_pUnkE4);
    }
    return 1;
}

// 0x004877d0 CKHkS08ClampGun_vfD0
void CKHkS08ClampGun::SetVisible(int32_t visible) {
    const uint32_t hidden = (static_cast<uint32_t>(visible) ^ 1u) << 2;
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | hidden;
    CSGLeaf* other = static_cast<CSGLeaf*>(m_pUnk20);
    other->m_sgProperties = hidden | (other->m_sgProperties & 0xfffffffbu);
}

// ==== P14 ===========================================================================================================
#include <cmath>

#include "crt/ppc_ops.h"
#include "k2000/core/IKInfo.h"
#include "k2000/scenegraph/CKAACylinder.h"

// 0x00488490 CKHkS08ClampGun_PostLoad
int32_t CKHkS08ClampGun::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);  // 0x3f6e70
    CKAACylinder* volume = static_cast<CKAACylinder*>(m_pUnk38);
    volume->m_ui8OwnerType = 1;
    volume->m_pOwner = this;
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0x7f) | 0x80);
    const float radius = m_fUnk40;
    volume->m_fCylinderRadius = radius;
    volume->m_fRadius = std::sqrt(ppc::fmadds(volume->m_fCylinderHalfHeight, volume->m_fCylinderHalfHeight, radius * radius));  // Math_Sqrtf
    const float half = m_fUnk44 * 0.5f;  // TOC1 +0x5d54
    const float r = volume->m_fCylinderRadius;
    volume->m_fCylinderHalfHeight = half;
    volume->m_fRadius = std::sqrt(ppc::fmadds(half, half, r * r));
    return 1;
}

// 0x004874d8 CKHkS08ClampGun_GetInfo: the actor base's answer (KStub_Return1_3f7140) folded with value 0x96's.
int32_t CKHkS08ClampGun::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);
    int32_t own = 1;
    if (request == kGetInfoValueAccessor && info->m_ui32Id == 0x96) {
        // 0x004866c8 CKHkS08ClampGun_GetTriggerProp96: fcmpu + cror lt|eq against 0 (TOC1 +0x5d30).
        own = AnswerInfo(info, [](IKSerializable* o, uint32_t) -> uint32_t {
            return static_cast<CKHkS08ClampGun*>(o)->m_fUnk50 <= 0.0f ? 1u : 0u;
        }, 0);
    }
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}

// ==== port-final F06: the run time ==================================================================================
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Clamp.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Clamp.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/xatan.h"
#include "crt/xfsin.h"
#include "crt/xsinf.h"
#include "crt/xtanf.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/CKDamage.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Math.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"

namespace {
// DOTD: the state handlers by descriptor (k2000/core/Ps3MemberFn.h; the tables Restart fills at +0x128 and +0x140).
Ps3MemberFnEntry<CKHkS08ClampGun::StateFn> g_clampGunStates[] = {
    {0x00bc3420u, &CKHkS08ClampGun::State0, "CKHkS08ClampGun_SM128_State0 0x48b680", false},
    {0x00bc3428u, &CKHkS08ClampGun::State1, "CKHkS08ClampGun_SM128_State1 0x48bc30", false},
    {0x00bc3418u, &CKHkS08ClampGun::SalvoState0, "CKHkS08ClampGun_FireSalvoState_maybe 0x48b4f8", false},
    {0x00bc31e8u, &CKHkS08ClampGun::SalvoState1, "CKHkS08ClampGun_SM140_State1_Cooldown_maybe 0x487898", false},
    {0x00bc2f60u, &CKHkS08ClampGun::SalvoState2, "KStub_ReturnArg4_9c4938", false},
};

// TOC1 constants (compared by their bits).
constexpr float kGunZero = 0.0f;                  // +0x5d30
constexpr float kGunOne = 1.0f;                   // +0x5d8c
constexpr float kGunHalf = 0.5f;                  // +0x5d54
constexpr float kGunQuarter = 0.25f;              // +0x5dac
constexpr float kGunMinusOne = -1.0f;             // +0x5d6c
constexpr float kGunTwo = 2.0f;                   // +0x5e18
constexpr float kGunFifteen = 15.0f;              // +0x5d98 (gravity / 2)
constexpr float kGunGravity = 30.0f;              // +0x5e14
constexpr float kGunContactTime = -1000.0f;       // +0x5d5c
constexpr float kGunRandMax = 65535.0f;           // +0x5d48 (0x477fff00)
constexpr float kGunDegToRad = 0.0174532905f;     // +0x5d4c (0x3c8efa34)
constexpr float kGunMinusDegToRad = -0.0174532905f;  // +0x5d50 (0xbc8efa34)
constexpr float kGunPi = 3.14159274f;             // +0x5dd4 (0x40490fdb)
constexpr float kGunTwoPi = 6.28318548f;          // +0x5d58 (0x40c90fdb)
constexpr float kGunTurnLeft = -0.1f;             // +0x5dd8 (0xbdcccccd)
constexpr float kGunTurnRight = 0.1f;             // +0x5ddc (0x3dcccccd)
// The shared Y axis 0x00c50d40 (TOC1 +0x5e10; filled by a static initialiser in the original).
const CVector3 kGunAxisY = {0.0f, 1.0f, 0.0f};

// The game's inlined cosf / sinf with the library call for a negative argument (the sign bit tested as an integer).
bool GunSignBit(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
float GunCos(float x) { return GunSignBit(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
float GunSin(float x) { return GunSignBit(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }

// The inlined wrap into [0, 2 pi): below 0, 2 pi added until it is not; then 2 pi taken while not below 2 pi (fcmpu with
// cror gt|eq: a NaN stays).
float WrapTwoPi(float a) {
    if (a < kGunZero) {
        do {
            a = a + kGunTwoPi;
        } while (a < kGunZero);
    }
    while (a >= kGunTwoPi) a = a - kGunTwoPi;
    return a;
}

CSGMovable* MovableOf(IKSerializable* node) { return static_cast<CSGMovable*>(node); }
RwFrame* FrameOf(IKSerializable* node) { return MovableOf(node)->m_pRwFrame; }
const CVector3* AsVector(const RwV3d* v) { return reinterpret_cast<const CVector3*>(v); }
// The frame's LTM position (RwFrame +0x80) as the sounds take it.
const CVector3* LtmPosition(IKSerializable* node) { return AsVector(&FrameLtm(FrameOf(node))->pos); }
// The hidden bit (+0x10 bit 2) of a node: cleared, then `hidden` ORed in (the original's rlwinm pair and or).
void SetHiddenBits(IKSerializable* node, uint32_t hidden) {
    CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
    leaf->m_sgProperties = (leaf->m_sgProperties & 0xfffffffbu) | hidden;
}

CKGrpS08Hero* GunHeroGroup() { return static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]); }
IKBaseGroup* GunContextGroup() { return static_cast<IKBaseGroup*>(g_pEngine->m_gameManager->m_unk04[2]); }
CKSrvFx* GunFxService() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }
CKSrvCollision* GunCollisionService() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }

// The inlined hero tests (CKHkS08ClampGun_AreAllHeroesBeyondRadius_maybe 0x486a48 / WithinRadius 0x486920, dead as
// functions): the hero group's count (vt+0xf4) and how many heroes' node (modelling position, RwFrame +0x40) are beyond
// (d^2 > r^2: ble skips, a NaN counts) or within (d^2 < r^2: bge skips, a NaN does not) `radius` of the node +0x20's.
// BUG(original): without a hero group the count register keeps a stale value; the group always exists, 0 here.
uint32_t CountHeroes(const CKHkS08ClampGun* gun, float radius, bool beyond, uint32_t* passing) {
    CKGrpS08Hero* group = GunHeroGroup();
    *passing = 0;
    if (group == nullptr) return 0;
    const uint32_t count = group->GetHeroCount();  // 0x002ca038 (vt+0xf4)
    uint32_t n = 0;
    for (uint32_t i = 0; i != count; i = static_cast<uint8_t>(i + 1)) {
        IKHook* hero = static_cast<IKHook*>(group->m_apHeros[i]);  // GetHeroByDragonIndex 0x2ca080
        const RwV3d& h = FrameOf(hero->m_pKGLObject)->modelling.pos;
        const RwV3d& g = FrameOf(gun->m_pUnk20)->modelling.pos;
        const float r2 = radius * radius;
        const float dy = h.y - g.y;
        const float dx = h.x - g.x;
        const float dz = h.z - g.z;
        const float d2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (beyond) {
            if (!(d2 <= r2)) ++n;
        } else {
            if (d2 < r2) ++n;
        }
    }
    *passing = n;
    return count;
}
}  // namespace

// 0x00487df8 CKHkS08ClampGun_Destructor (0x00487a00 CKHkS08ClampGun_DeletingDestructor: the same, then delete)
CKHkS08ClampGun::~CKHkS08ClampGun() {
    if (m_vUnkB4.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnkB4.m_pBlock);
    m_vUnkB4.m_ui32NbUsedElt = 0;
    m_vUnkB4.m_pBlock = nullptr;
    for (ContactHistoryNode* node = m_pContactHistory; node != nullptr;) {
        ContactHistoryNode* next = node->m_pNext;  // +0x14
        ContactHistory_FreeNode(node);             // the FreeListPool's 0x18-byte list (+0x54)
        node = next;
    }
    m_pContactHistory = nullptr;
}

uint8_t CKHkS08ClampGun::CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_clampGunStates, pair, "CKHkS08ClampGun state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

void CKHkS08ClampGun::SwitchState(uint8_t* state, const uint32_t* table, uint8_t next, IKTime* clock, uint8_t leaveOther) {
    const uint8_t old = *state;
    if (old != 0xff) CallState(&table[old * 2u], clock, 2, leaveOther);
    *state = next;
    if (next != 0xff) CallState(&table[next * 2u], clock, 1, old);
}

void CKHkS08ClampGun::RunStateMachine(uint8_t* state, const uint32_t* table, IKTime* clock) {
    const uint8_t current = *state;
    if (current == 0xff) return;
    const uint8_t next = CallState(&table[current * 2u], clock, 0, current);
    const uint8_t now = *state;
    if (next == now) return;
    if (now != 0xff) CallState(&table[now * 2u], clock, 2, next);
    *state = next;
    if (next != 0xff) CallState(&table[next * 2u], clock, 1, now);
}

// 0x00487480 CKHkS08ClampGun_Start
void CKHkS08ClampGun::Start() {
    CKHkActorBase::Start();  // 0x003f6e48 (empty)
    Restart();               // vt+0x54
}

// 0x0048a1c0 CKHkS08ClampGun_Restart
void CKHkS08ClampGun::Restart() {
    m_aStateTable[0] = 0x00bc3420u;  // State0 (TOC1 +0x5e00)
    m_aStateTable[2] = 0x00bc3428u;  // State1 (TOC1 +0x5dfc)
    m_aStateTable[3] = 0;
    m_aStateTable[1] = 0;
    m_unk125 = 2;
    m_unk124 = 0;
    m_pStateTable = m_aStateTable;
    CallState(&m_pStateTable[0], nullptr, 1, 0xff);  // State0 entered (the state already 0)
    m_aSalvoTable[5] = 0;
    m_aSalvoTable[2] = 0x00bc31e8u;  // Cooldown (TOC1 +0x5e04)
    m_aSalvoTable[3] = 0;
    m_aSalvoTable[1] = 0;
    m_aSalvoTable[0] = 0x00bc3418u;  // FireSalvoState (TOC1 +0x5e08)
    m_aSalvoTable[4] = 0x00bc2f60u;  // KStub_ReturnArg4_9c4938 (TOC1 +0x5e0c)
    m_unk13C = 2;
    m_unk13D = 3;
    m_pSalvoTable = m_aSalvoTable;
    CallState(&m_pSalvoTable[4], nullptr, 1, 0xff);  // the idle state 2 entered
    for (uint32_t i = 0; i < m_vUnkB4.m_ui32NbUsedElt; ++i) m_vUnkB4.m_pBlock[i]->m_unk8 = 0;
    SetObjectActiveInContext(g_pEngine->m_coreManager, this, 1, GunContextGroup());  // 0x0001cb10
    m_fUnk50 = m_fUnk54;
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_pUnk38);
    if ((m_bitArray & 4u) == 0) {
        SetHiddenBits(m_pKGLObject, 0);
        SetHiddenBits(m_pUnk20, 0);
        Mat4_OrthoNormalizeInPlace(reinterpret_cast<CMatrix34*>(&FrameOf(m_pKGLObject)->modelling));  // 0x0023f648
        m_fYaw = 0.0f;  // stw 0
        if (m_unk11F != 0) GunCollisionService()->AddVolume(volume);  // 0x00192b80
    } else {
        GunCollisionService()->RemoveVolume(volume);  // 0x00192bc0
    }
    m_pWarmFx = nullptr;
    m_pIdleFx = nullptr;
    for (uint32_t i = 0; i < m_vUnkB4.m_ui32NbUsedElt; ++i) {
        IKSerializable* clamp = m_vUnkB4.m_pBlock[i]->m_unk4;
        if (clamp != nullptr) {
            static_cast<CKGrpS08Clamp*>(m_pUnkD8)->ReturnClampToPool(clamp);  // 0x00491ba0
            m_vUnkB4.m_pBlock[i]->m_unk4 = nullptr;
        }
    }
    if ((m_bitArray & 4u) == 0) {
        SetHiddenBits(m_pKGLObject, static_cast<uint32_t>(m_unk11F ^ 1u) << 2);
        SetHiddenBits(m_pUnk20, static_cast<uint32_t>(m_unk11F ^ 1u) << 2);
    }
}

// 0x004880d0 CKHkS08ClampGun_Stop
void CKHkS08ClampGun::Stop() {
    CKHkActorBase::Stop();  // CKHkActorBase_d82_maybe_Stop 0x3f6e50 (empty)
    for (uint32_t i = 0; i < m_vUnkB4.m_ui32NbUsedElt; ++i) {
        IKSerializable* clamp = m_vUnkB4.m_pBlock[i]->m_unk4;
        if (clamp != nullptr) {
            static_cast<CKGrpS08Clamp*>(m_pUnkD8)->ReturnClampToPool(clamp);  // 0x00491ba0
            m_vUnkB4.m_pBlock[i]->m_unk4 = nullptr;
        }
    }
}

// 0x00487ac0 CKHkS08ClampGun_OnActivate
void CKHkS08ClampGun::VfA0() {
    const RwV3d& at = FrameOf(m_pKGLObject)->modelling.at;  // RwFrame +0x30
    m_vInitialAt.x = at.x;
    m_vInitialAt.z = at.z;
    m_vInitialAt.y = at.y;
    CSGBranch* node = static_cast<CSGBranch*>(m_pKGLObject);
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_pUnk38);
    if (volume->m_pParent != nullptr) node->RemoveChild(volume);  // vt+0x78
    node->AddChild(volume);                                       // vt+0x70
    RwMatrix identity;
    std::memset(&identity, 0, sizeof(identity));
    identity.flags = 0x20003;
    identity.right.x = 1.0f;  // TOC1 +0x5d8c
    identity.at.z = 1.0f;
    identity.up.y = 1.0f;
    MovableOf(m_pKGLObject)->SetLocalMatrix(&identity);  // 0x000d0be8
    m_fYaw = 0.0f;  // stw 0
    SetHiddenBits(m_pKGLObject, 0);
    SetHiddenBits(m_pUnk20, 0);
    uint8_t shown = 0;
    if (m_unk11F != 0) {
        GunCollisionService()->AddVolume(volume);  // 0x00192b80
        shown = m_unk11F;
    }
    m_pWarmFx = nullptr;
    m_pIdleFx = nullptr;
    SetHiddenBits(m_pKGLObject, (static_cast<uint32_t>(shown ^ 1u) << 2) & 0x3fcu);
    SetHiddenBits(m_pUnk20, static_cast<uint32_t>(m_unk11F ^ 1u) << 2);
}

// 0x004878f8 CKHkS08ClampGun_OnDeactivate
void CKHkS08ClampGun::VfA4() {
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_pUnk38);
    if (volume->m_pParent != nullptr) static_cast<CSGBranch*>(m_pKGLObject)->RemoveChild(volume);  // vt+0x78
    if (m_pIdleFx != nullptr) {
        m_pIdleFx->StopAndRelease(this);  // vt+0x58
        m_pIdleFx = nullptr;
    }
    if (m_pWarmFx != nullptr) {
        m_pWarmFx->StopAndRelease(this);
        m_pWarmFx = nullptr;
    }
    GunCollisionService()->RemoveVolume(volume);  // 0x00192bc0
}

// 0x00488558 CKHkS08ClampGun_MessageProc
int32_t CKHkS08ClampGun::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    if (message == 0x900) {
        for (uint32_t i = 0; i < m_vUnkB4.m_ui32NbUsedElt; ++i) {
            SElem* elem = m_vUnkB4.m_pBlock[i];
            if (elem->m_unk4 == static_cast<IKSerializable*>(data)) elem->m_unk8 = 0;
        }
    } else if (message == 0x996) {
        for (uint32_t i = 0; i < m_vUnkB4.m_ui32NbUsedElt; ++i) {
            SElem* elem = m_vUnkB4.m_pBlock[i];
            CKHkS08Clamp* clamp = static_cast<CKHkS08Clamp*>(elem->m_unk4);
            if (clamp == nullptr || elem->m_unk8 == 0) continue;
            if (clamp->m_ui8State == 2) continue;  // CKHkS08Clamp_IsInState2 0x0048d568
            static_cast<CKHkS08Clamp*>(m_vUnkB4.m_pBlock[i]->m_unk4)->PlaySound1AndSpawnFx();         // 0x0048ddc8
            static_cast<CKGrpS08Clamp*>(m_pUnkD8)->ReturnClampToPool(m_vUnkB4.m_pBlock[i]->m_unk4);  // 0x00491ba0
        }
    }
    // The actor base's answer only (srawi / xor / subf: 0 stays 0, anything else but 2 / 3 is 1).
    if (base == 3) return 3;
    if (base == 2) return 2;
    return base == 0 ? 0 : 1;
}

// 0x0048a560 CKHkS08ClampGun_Update
void CKHkS08ClampGun::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // CKHkActorBase_d82_maybe_Update 0x3f6e68 (empty)
    if (m_unk11B == 0) return;
    if (m_pIdleFx != nullptr) {
        m_pIdleFx->StopAndRelease(this);  // vt+0x58
        m_pIdleFx = nullptr;
    }
    if (m_pWarmFx != nullptr) {
        m_pWarmFx->StopAndRelease(this);
        m_pWarmFx = nullptr;
    }
    RunStateMachine(&m_unk124, m_pStateTable, clock);
    ProcessContacts(clock);  // 0x004871b0
    if (!(m_fUnk50 <= kGunZero)) return;  // fcmpu, cror lt|eq
    GunCollisionService()->RemoveVolume(static_cast<IKBoundingVolume*>(m_pUnk38));  // 0x00192bc0
    CKSound* turn = static_cast<CKSoundDictionaryID*>(m_pUnk24)->GetSound(4);  // 0x00112bc0
    if (turn != nullptr && turn->CountInstances() != 0) turn->Stop(0);       // Sound_Stop 0x001111b0
    SetHiddenBits(m_pKGLObject, 4);
    SetHiddenBits(m_pUnk20, 4);
    SetObjectActiveInContext(g_pEngine->m_coreManager, this, 0, GunContextGroup());  // 0x0001cb10
    // CKSrvFx::AcquireFx inlined: the destruction's explosion at the node +0x20 (its modelling position, RwFrame +0x40).
    m_pDestroyFx = GunFxService()->AcquireFx(static_cast<IKFxData*>(m_pUnkF4), this);
    if (m_pDestroyFx == nullptr) return;
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(m_pDestroyFx);
    fx->SetTranslation(AsVector(&FrameOf(m_pUnk20)->modelling.pos), this);  // 0x001b66e8
    static_cast<CKExplosionNodeFx*>(m_pDestroyFx)->Trigger(this, nullptr);  // 0x001b82a8
    m_pDestroyFx->ReleaseReservation(this);                                // vt+0x54
}

// 0x00486cc0 CKHkS08ClampGun_UpdateTurnSound_maybe. Both callers leave the turn step at +0x6c (RotateTowardTarget's;
// RotateTowardPresetYaw's step is +0xac): the original reads +0x6c either way.
void CKHkS08ClampGun::UpdateTurnSound(uint8_t click) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pUnk24);
    CKSound* turn = sounds->GetSound(4);  // 0x00112bc0
    if (turn != nullptr) {
        if (m_afAimTurn[2] == kGunZero) {
            if (static_cast<uint8_t>(turn->IsPlaying()) != 0) turn->Stop(0);  // 0x00111568, 0x001111b0
        } else if (static_cast<uint8_t>(turn->IsPlaying()) == 0) {
            turn->SetLoop(1);                      // 0x00110fd0
            turn->SetPosition(LtmPosition(m_pUnk20));  // 0x00110fa0
            turn->Play(kGunZero);                  // 0x00111230
        }
    }
    if (click == 0) return;
    CKSound* tick = sounds->GetSound(5);
    if (tick == nullptr) return;
    tick->SetPosition(LtmPosition(m_pUnk20));
    tick->Play(kGunZero);
}

// 0x00486e60 CKHkS08ClampGun_TickTimerAndPlayImpactFx_maybe (`damage` the low word of fctidz: fcfid of it, frsp)
void CKHkS08ClampGun::TakeDamage(uint32_t damage, const CVector3* point) {
    const float amount = static_cast<float>(static_cast<double>(damage));
    m_fUnk50 = m_fUnk50 - amount;
    if (m_fUnk50 <= kGunZero) {  // cror lt|eq
        m_fUnk50 = kGunZero;
        return;
    }
    // CKSrvFx::AcquireFx inlined: the impact at the contact point.
    IKFx* impact = GunFxService()->AcquireFx(static_cast<IKFxData*>(m_pUnkE4), this);
    if (impact != nullptr) {
        CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(impact);
        fx->SetTranslation(point, this);  // 0x001b66e8
        fx->Trigger(this, nullptr);       // 0x001b82a8
        fx->ReleaseReservation(this);     // vt+0x54
    }
    CKSound* hit = static_cast<CKSoundDictionaryID*>(m_pUnk24)->GetSound2(3);  // 0x00112bd8
    if (hit == nullptr) return;
    hit->SetPosition(LtmPosition(m_pKGLObject));
    hit->SetLoop(0);
    hit->Play(kGunZero);
}

// 0x004871b0 CKHkS08ClampGun_ProcessContacts_maybe
void CKHkS08ClampGun::ProcessContacts(IKTime* clock) {
    for (ICollision* c = static_cast<ICollision*>(static_cast<IKBoundingVolume*>(m_pUnk38)->m_CollisionResList); c != nullptr;
         c = c->m_pNext) {
        IKBoundingVolume* other;
        if (static_cast<IKBoundingVolume*>(c->GetBoundingVolume1())->m_pOwner == this) {  // vt+0x00
            c->GetBoundingVolume1();
            other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2());  // vt+0x04
        } else {
            c->GetBoundingVolume2();
            other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume1());
        }
        if (c->HasContactSet() == 0 || (other->m_ui16PropertiesFlags & 8u) == 0) continue;  // vt+0x08
        if (ContactHistory_Touch(kGunContactTime, kGunContactTime, &m_pContactHistory, other, other->m_pOwner) == 0) {
            continue;  // TocBridge 0x98f380
        }
        CKDamage* hit = static_cast<CKDamage*>(other->m_unk1c);
        if (hit->m_i32DamageKind != 0) continue;
        const CVector3 point = *c->GetWorldContactPoint();  // vt+0x20
        TakeDamage(static_cast<uint32_t>(ppc::fctidz(hit->m_fAmount)), &point);  // 0x00486e60
    }
    ContactHistory_Update(&m_pContactHistory, clock);  // TocBridge 0x98f430
}

// 0x00488330 CKHkS08ClampGun_ComputeBallisticSpeed_maybe
float CKHkS08ClampGun::ComputeBallisticSpeed(float angle, const CVector3* from, const CVector3* to) {
    float dx = to->x - from->x;
    float dz = to->z - from->z;
    // BUG(original): the cosine of the turret's yaw is computed and thrown away.
    (void)crt::FSinf(Vec3_GetYawAngleFromX(AsVector(&FrameOf(m_pKGLObject)->modelling.at)), 1);  // 0x00244638, 0x98f2a0
    dx = ppc::fmadds(dx, dx, kGunZero);
    float c = crt::FSinf(angle, 1);  // TocBridge__FSin_maybe 0x98f2a0: the cosine
    const float d2 = ppc::fmadds(dz, dz, dx);
    c = c * c;
    const float t = crt::Tanf(angle);  // TocBridge_tanf_maybe 0x98f660
    const float dy = to->y - from->y;
    const float a = std::sqrt(d2);  // Math_Sqrtf 0x10690
    const float b = std::sqrt(d2);
    const float ab = a * b;
    const float d = std::sqrt(d2);
    const float rise = ppc::fmsubs(t, d, dy);
    float speed2 = ab / c;
    speed2 = speed2 * kGunFifteen;
    const float k = kGunOne / rise;
    speed2 = speed2 * k;
    if (speed2 <= kGunZero) return kGunZero;  // cror lt|eq: a NaN takes the root
    return std::sqrt(speed2);
}

// 0x00488738 CKHkS08ClampGun_AimAtHeroesMidpoint_maybe
void CKHkS08ClampGun::AimAtHeroesMidpoint() {
    CKGrpS08Hero* group = GunHeroGroup();
    group->GetHeroCount();  // 0x002ca038 (the result unused)
    CKHkS08Hero* hero0 = static_cast<CKHkS08Hero*>(group->m_apHeros[0]);  // GetHeroByDragonIndex 0x2ca080
    CKHkS08Hero* hero1 = static_cast<CKHkS08Hero*>(group->m_apHeros[1]);
    const float* p1 = hero1->GetTargetingPositionPtr();  // 0x00363c78
    const float p1z = p1[2];
    const float p1x = p1[0];
    const float p1y = p1[1];
    const float* p0 = hero0->GetTargetingPositionPtr();
    const float p0x = p0[0];
    const float p0z = p0[2];
    const float p0y = p0[1];
    const float midX = (p1x + p0x) * kGunHalf;
    const float midZ = (p1z + p0z) * kGunHalf;
    const RwV3d& base = FrameOf(m_pUnk20)->modelling.pos;  // RwFrame +0x40
    float fx = midX - base.x;
    float fz = midZ - base.z;
    float fx2 = fx * fx;
    float fz2 = fz * fz;
    float length = std::sqrt((fx2 + kGunZero) + fz2);
    if (length != kGunZero) {
        const float k = kGunOne / length;
        fz = fz * k;
        fx = fx * k;
        fz2 = fz * fz;
        fx2 = fx * fx;
    }
    // The flat direction raised by 0.5, normalised.
    float fy = kGunHalf;
    length = std::sqrt((fx2 + kGunQuarter) + fz2);
    if (length != kGunZero) {
        const float k = kGunOne / length;
        fz = fz * k;
        fx = fx * k;
        fy = k * kGunHalf;
        fz2 = fz * fz;
        fx2 = fx * fx;
    }
    // Its cosine with the flat direction.
    length = std::sqrt((fx2 + kGunZero) + fz2);
    float flatY = kGunZero;
    if (length != kGunZero) {
        const float k = kGunOne / length;
        const float flatZ = fz * k;
        const float flatX = fx * k;
        flatY = k * kGunZero;
        fz2 = fz * flatZ;
        fx2 = fx * flatX;
    }
    float cosine = ppc::fmadds(flatY, fy, fx2) + fz2;
    if (!(cosine > kGunZero)) {  // ble (a NaN takes it)
        if (cosine < kGunMinusOne) cosine = kGunMinusOne;  // bge (a NaN keeps itself)
    } else if (!(cosine < kGunOne)) {
        cosine = kGunOne;
    }
    const float pitch = crt::AcosfLib(cosine);  // TocBridge_Math_Acosf_2_maybe 0x98f670
    const float midY = (p1y + p0y) * kGunHalf;
    const RwV3d& muzzle = FrameLtm(FrameOf(m_pKGLObject))->pos;  // RwFrame +0x80
    const CVector3 from = {muzzle.x, muzzle.y, muzzle.z};
    const float baseZ = FrameOf(m_pUnk20)->modelling.pos.z;
    const float baseX = FrameOf(m_pUnk20)->modelling.pos.x;
    const CVector3 target = {midX, midY, midZ};
    const float speed = ComputeBallisticSpeed(pitch, &from, &target);  // 0x00488330
    if (speed == kGunZero) return;
    const float ex = midX - baseX;
    const float ez = midZ - baseZ;
    const float distance = std::sqrt(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, kGunZero)));
    const float c = crt::FSinf(pitch, 1);  // TocBridge__FSin_maybe 0x98f2a0: the cosine
    const float time = distance / (speed * c);
    const CVector3 v0 = hero0->GetDerivedVelocity();  // 0x0032a730
    const CVector3 v1 = hero1->GetDerivedVelocity();
    float x0 = time * v0.x;
    float z0 = time * v0.z;
    const float x1 = ppc::fmadds(time, v1.x, p1x);
    const float y1 = p1y + kGunZero;
    const float z1 = ppc::fmadds(time, v1.z, p1z);
    float y0 = p0y + kGunZero;
    x0 = p0x + x0;
    z0 = p0z + z0;
    y0 = y0 + y1;
    x0 = x0 + x1;
    z0 = z0 + z1;
    m_vAimPoint.x = x0 * kGunHalf;
    m_vAimPoint.z = z0 * kGunHalf;
    m_vAimPoint.y = y0 * kGunHalf;
    const RwV3d& muzzle2 = FrameLtm(FrameOf(m_pKGLObject))->pos;
    const CVector3 from2 = {muzzle2.x, muzzle2.y, muzzle2.z};
    const CVector3 target2 = {m_vAimPoint.x, m_vAimPoint.y, m_vAimPoint.z};
    m_fShotSpeed = ComputeBallisticSpeed(pitch, &from2, &target2);
}

// 0x00488b10 CKHkS08ClampGun_RotateTowardPresetYaw_maybe
void CKHkS08ClampGun::RotateTowardPresetYaw(IKTime* clock) {
    const float yaw = Vec3_GetYawAngleFromZ(AsVector(&FrameOf(m_pKGLObject)->modelling.at));  // 0x00244528
    m_fYaw = yaw;
    // BUG(original): a side other than 0 / 1 keeps the caller's f29 as the target; the side is only ever 0 or 1.
    float target = kGunZero;
    if (m_ui32PresetSide == 0) {
        target = m_fUnk98 * kGunDegToRad;
    } else if (m_ui32PresetSide == 1) {
        target = m_fUnk9C * kGunMinusDegToRad;
    }
    float delta = WrapTwoPi(target - yaw);
    if (delta > kGunPi) delta = delta - kGunTwoPi;  // ble skips (a NaN too)
    // A click when the turn starts: past -0.1 (or 0.1) while the last delta was not.
    uint8_t click;
    if (delta < kGunTurnLeft && m_afPresetTurn[0] > kGunTurnLeft) {  // bge / ble go on (a NaN too)
        click = 1;
    } else if (delta > kGunTurnRight) {  // ble (a NaN: no click)
        click = m_afPresetTurn[0] < kGunTurnRight ? 1 : 0;
    } else {
        click = 0;
    }
    m_afPresetTurn[0] = delta;
    m_afPresetTurn[2] = kGunZero;
    FloatApproach_StepAngle(clock->m_afDeltaTime[0], m_afPresetTurn);  // 0x00243748
    const float turned = WrapTwoPi(m_fYaw + m_afPresetTurn[2]);
    m_fYaw = turned;
    const float rest = WrapTwoPi(turned - target);
    if (rest == kGunZero) {
        if (m_ui32PresetSide == 0) {
            m_ui32PresetSide = 1;
        } else if (m_ui32PresetSide == 1) {
            m_ui32PresetSide = 0;
        }
    }
    const float facing = m_fYaw;
    const float cz = GunCos(facing);
    const float sx = GunSin(facing);
    const CVector3 at = {sx, 0.0f, cz};
    MovableOf(m_pKGLObject)->SetOrientationFromAtUp(&at, AsVector(&FrameOf(m_pKGLObject)->modelling.up));  // 0x000d0918
    UpdateTurnSound(click);  // 0x00486cc0
}

// 0x00488f98 CKHkS08ClampGun_RotateTowardTarget_maybe
void CKHkS08ClampGun::RotateTowardTarget(IKTime* clock) {
    const RwV3d& muzzle = FrameLtm(FrameOf(m_pKGLObject))->pos;  // RwFrame +0x80
    CVector3 dir;
    dir.y = m_vAimPoint.y - muzzle.y;
    dir.x = m_vAimPoint.x - muzzle.x;
    dir.z = m_vAimPoint.z - muzzle.z;
    const float length = std::sqrt(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, dir.y * dir.y)));
    if (length != kGunZero) {
        const float k = kGunOne / length;
        dir.z = dir.z * k;
        dir.x = dir.x * k;
        dir.y = dir.y * k;
    }
    m_fYaw = Vec3_GetYawAngleFromZ(AsVector(&FrameLtm(FrameOf(m_pKGLObject))->at));  // RwFrame +0x70
    float delta = WrapTwoPi(Vec3_GetYawAngleFromZ(&dir) - m_fYaw);
    if (delta > kGunPi) delta = delta - kGunTwoPi;
    m_afAimTurn[0] = delta;
    m_afAimTurn[2] = kGunZero;
    FloatApproach_StepAngle(clock->m_afDeltaTime[0], m_afAimTurn);  // 0x00243748
    const float turned = WrapTwoPi(m_fYaw + m_afAimTurn[2]);
    m_fYaw = turned;
    // The yaw relative to the base node +0x20's (its LTM at).
    const float local = turned - Vec3_GetYawAngleFromZ(AsVector(&FrameLtm(FrameOf(m_pUnk20))->at));
    m_fYaw = local;
    const float cz = GunCos(local);
    const float sx = GunSin(m_fYaw);
    const CVector3 at = {sx, 0.0f, cz};
    MovableOf(m_pKGLObject)->SetOrientationFromAtUp(&at, AsVector(&FrameOf(m_pKGLObject)->modelling.up));  // 0x000d0918
    UpdateTurnSound(0);  // 0x00486cc0
}

// The particle effect of State0 (+0xfc) / State1 (+0x104): the data attached to the node +0x20 (no hot spot: the
// effect word, null here), its matrix at (0, 2, 0) and no longer the identity; then CKSrvFx::AcquireFx inlined.
IKFx* CKHkS08ClampGun::StartParticles(IKSerializable* data, IKFx* current) {
    CKParticlesEffectFxData* fxData = static_cast<CKParticlesEffectFxData*>(data);
    fxData->m_pAttachOwner = static_cast<CSGLeaf*>(m_pUnk20);
    fxData->m_pAttachHotSpot = nullptr;  // the original stores the effect word (+0x100 / +0x108) there: null
    (void)current;
    RwMatrix* matrix = fxData->m_pLocalMatrix;
    matrix->pos.z = 0.0f;  // stw 0
    matrix->pos.y = kGunTwo;
    matrix->pos.x = 0.0f;
    matrix->flags = matrix->flags & 0xfffdffffu;
    return GunFxService()->AcquireFx(fxData, this);
}

// 0x0048b680 CKHkS08ClampGun_SM128_State0
uint8_t CKHkS08ClampGun::State0(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_ui32PresetSide = 0;
        m_afPresetTurn[1] = 0.0f;
        m_afPresetTurn[2] = 0.0f;
        m_afPresetTurn[0] = 0.0f;
        m_afPresetTurn[1] = m_fUnkA0;
        m_fFireTimer = 0.0f;
        return other;
    }
    if (phase != 0) return other;
    m_fFireTimer = m_fFireTimer + clock->m_afDeltaTime[0];
    if (m_fUnk84 <= m_fFireTimer) {  // cror lt|eq
        if (m_pIdleFx == nullptr) m_pIdleFx = StartParticles(m_pUnkFC, m_pIdleFx);
        CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pUnk24);
        if (sounds->GetSound(1) != nullptr) {  // 0x00112bc0
            sounds->GetSound(1)->m_SoundFlags &= 0xffffffbfu;
            sounds->GetSound(1)->SetLoop(0);
            sounds->GetSound(1)->SetPosition(LtmPosition(m_pUnk20));
            sounds->GetSound(1)->Play(kGunZero);
        }
        m_fFireTimer = 0.0f;  // stw 0
    }
    RotateTowardPresetYaw(clock);  // 0x00488b10
    uint32_t beyond = 0;
    const uint32_t count = CountHeroes(this, m_fUnk48, true, &beyond);
    if (count == 0 || beyond == count) {
        uint32_t within = 0;
        const uint32_t count2 = CountHeroes(this, m_fUnk4C, false, &within);
        if (count2 != 0 && within != count2) return other;
    }
    CKGrpS08Hero* group = GunHeroGroup();
    if (group != nullptr && group->IsExternalLockFree() != 0) return 1;  // 0x002d4c30
    return other;
}

// 0x0048bc30 CKHkS08ClampGun_SM128_State1
uint8_t CKHkS08ClampGun::State1(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        AimAtHeroesMidpoint();  // 0x00488738
        m_afAimTurn[1] = 0.0f;
        m_afAimTurn[0] = 0.0f;
        m_afAimTurn[2] = 0.0f;
        m_afAimTurn[1] = m_fUnk60;
        const uint32_t used = m_vUnkB4.m_ui32NbUsedElt;
        if (used == 0) {
            SwitchState(&m_unk13C, m_pSalvoTable, 1, clock, 1);
        } else {
            uint32_t held = 0;
            for (uint32_t i = 0; i < used; ++i) held += m_vUnkB4.m_pBlock[i]->m_unk4 != nullptr ? 1u : 0u;
            CKGrpS08Clamp* group = static_cast<CKGrpS08Clamp*>(m_pUnkD8);
            if (group != nullptr && group->m_list.m_ui32Count2 >= used - held) {  // cmplw, bge
                for (uint32_t i = 0; i < m_vUnkB4.m_ui32NbUsedElt; ++i) {
                    SElem* elem = m_vUnkB4.m_pBlock[i];
                    if (elem->m_unk4 != nullptr) continue;
                    elem->m_unk4 = group->TakeFreeClamp();  // 0x00491bf8
                    static_cast<CKHkS08Clamp*>(m_vUnkB4.m_pBlock[i]->m_unk4)->m_pUnk28 = this;
                }
            }
        }
        m_fWarmTimer = kGunZero;
        m_fStateTime = kGunZero;
        if (!(m_fUnk90 > kGunZero)) return other;  // ble (a NaN takes it)
        CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pUnk24);
        if (sounds->GetSound(2) == nullptr) return other;
        sounds->GetSound(2)->SetLoop(0);
        sounds->GetSound(2)->SetPosition(LtmPosition(m_pUnk20));
        sounds->GetSound(2)->Play(kGunZero);
        return other;
    }
    if (phase == 2) {
        for (uint32_t i = 0; i < m_vUnkB4.m_ui32NbUsedElt; ++i) {
            SElem* elem = m_vUnkB4.m_pBlock[i];
            const uint8_t fired = elem->m_unk8;
            if (fired != 0 || elem->m_unk4 == nullptr) continue;
            static_cast<CKGrpS08Clamp*>(m_pUnkD8)->ReturnClampToPool(elem->m_unk4);  // 0x00491ba0
            m_vUnkB4.m_pBlock[i]->m_unk4 = nullptr;  // (the fired byte, 0)
        }
        return other;
    }
    if (phase != 0) return other;
    if (!(m_fUnk90 < m_fStateTime)) {  // bge: the warm-up
        m_fStateTime = m_fStateTime + clock->m_afDeltaTime[0];
        m_fWarmTimer = m_fWarmTimer + clock->m_afDeltaTime[0];
        if (!(m_fUnk8C <= m_fWarmTimer)) return other;  // cror lt|eq
        if (m_pWarmFx == nullptr) m_pWarmFx = StartParticles(m_pUnk104, m_pWarmFx);
        m_fWarmTimer = 0.0f;  // stw 0
        return other;
    }
    if (m_unk13C == 2) SwitchState(&m_unk13C, m_pSalvoTable, 0, clock, 0);
    uint32_t beyond = 0;
    const uint32_t count = CountHeroes(this, m_fUnk48, true, &beyond);
    if (count != 0 && beyond != count) {
        CKGrpS08Hero* group = GunHeroGroup();
        if (group != nullptr && group->IsExternalLockFree() != 0) {  // 0x002d4c30
            AimAtHeroesMidpoint();  // 0x00488738
            RunStateMachine(&m_unk13C, m_pSalvoTable, clock);
            RotateTowardTarget(clock);  // 0x00488f98
            return other;
        }
    }
    SwitchState(&m_unk13C, m_pSalvoTable, 2, clock, 2);
    return 0;
}

// 0x0048b4f8 CKHkS08ClampGun_FireSalvoState_maybe (the salvo machine's state 0)
uint8_t CKHkS08ClampGun::SalvoState0(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 0) {
        if (m_bSalvoWait != 0) return 1;
        const uint32_t index = m_ui32ShotIndex;
        const float time = m_fShotTimer;
        if (!(m_vUnkB4.m_pBlock[index]->m_fUnk0 < time)) {  // bge
            m_fShotTimer = time + clock->m_afDeltaTime[0];
            return other;
        }
        if (m_vUnkB4.m_ui32NbUsedElt - 1 == index) return 1;
        m_fShotTimer = 0.0f;  // stw 0
        m_ui32ShotIndex = index + 1;
        FireShot(index + 1);  // 0x0048ab98
        return other;
    }
    if (phase == 1) {
        for (uint32_t i = 0; i < m_vUnkB4.m_ui32NbUsedElt; ++i) {
            if (m_vUnkB4.m_pBlock[i]->m_unk8 != 0) {
                m_bSalvoWait = 1;
                return other;
            }
        }
        m_bSalvoWait = 0;
        m_ui32ShotIndex = 0;
        m_fShotTimer = 0.0f;  // stw 0
        if (m_vUnkB4.m_ui32NbUsedElt > 0) FireShot(0);
    }
    return other;
}

// 0x00487898 CKHkS08ClampGun_SM140_State1_Cooldown_maybe (the salvo machine's state 1)
uint8_t CKHkS08ClampGun::SalvoState1(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 0) {
        m_fCooldownTimer = m_fCooldownTimer + clock->m_afDeltaTime[0];
        if (!(m_fUnk58 < m_fCooldownTimer)) return other;  // bge
        if (m_vUnkB4.m_ui32NbUsedElt != 0) return 0;
        return other;
    }
    if (phase == 1) m_fCooldownTimer = 0.0f;  // stw 0
    return other;
}

// 0x0048ab98 CKHkS08ClampGun_FireShot_maybe
uint8_t CKHkS08ClampGun::FireShot(uint32_t index) {
    if (m_vUnkB4.m_pBlock[index]->m_unk4 == nullptr) return 0;
    if (m_fShotSpeed == kGunZero) return 0;  // bne (a NaN fires)
    CMatrix34 hotSpot;
    static_cast<CSGHotSpot*>(m_pUnkD4)->GetWorldMatrix(&hotSpot);  // 0x000ce970
    float ay = hotSpot.m_at.y;
    float ax = hotSpot.m_at.x;
    float az = hotSpot.m_at.z;
    float length = std::sqrt(ppc::fmadds(az, az, ppc::fmadds(ax, ax, ay * ay)));  // Math_Sqrtf 0x10690
    if (length != kGunZero) {
        const float k = kGunOne / length;
        az = az * k;
        ax = ax * k;
        ay = ay * k;
    }
    const float speed = m_fShotSpeed;
    const float vx = ax * speed;
    const float vz = az * speed;
    const float vy = speed * ay;
    const float x2 = vx * vx;
    const float z2 = vz * vz;
    const float sum = ppc::fmadds(vy, vy, x2) + z2;
    // The pitch, spread by +-+0x10c degrees (Rand_Int: the low 16 bits over 65535).
    float pitch = crt::Asinf(vy / std::sqrt(sum));  // TocBridge_Math_Asinf 0x98f1d0
    {
        const uint16_t r = static_cast<uint16_t>(Rand_Int());  // 0x00011500
        const float spread = m_fUnk10C;
        const float scale = spread * kGunDegToRad;
        float t = static_cast<float>(static_cast<double>(r)) / kGunRandMax;
        t = t * scale;
        t = t + t;
        pitch = pitch + ppc::fmadds(spread, kGunMinusDegToRad, t);
    }
    const float length1 = std::sqrt(sum);
    float ny = GunSin(pitch) * length1;
    const float y2 = ny * ny;
    const float sum2 = z2 + (x2 + y2);
    // The yaw against x, spread the same way.
    float yaw = crt::Acosf(vx / std::sqrt(sum2));  // TocBridge_Math_Acosf 0x98e1a0
    {
        const uint16_t r = static_cast<uint16_t>(Rand_Int());
        const float spread = m_fUnk10C;
        const float scale = spread * kGunDegToRad;
        float t = static_cast<float>(static_cast<double>(r)) / kGunRandMax;
        t = t * scale;
        t = t + t;
        yaw = yaw + ppc::fmadds(spread, kGunMinusDegToRad, t);
    }
    const float length2 = std::sqrt(sum2);
    float nx = GunCos(yaw) * length2;
    float nz = vz;  // the depth keeps its unspread value
    uint32_t within = 0;
    const uint32_t count = CountHeroes(this, m_fUnk4C, false, &within);
    if (count == 0 || within == count) {
        if (m_fUnk114 > kGunZero) {  // ble skips (a NaN too)
            const float l = std::sqrt(z2 + ppc::fmadds(nx, nx, y2));
            if (l != kGunZero) {
                const float k = kGunOne / l;
                nz = nz * k;
                nx = nx * k;
                ny = ny * k;
            }
            const float s = m_fUnk114;
            nz = nz * s;
            nx = nx * s;
            ny = ny * s;
        }
    }
    const CVector3 acceleration = {-kGunAxisY.x * kGunGravity, -kGunAxisY.y * kGunGravity, -kGunAxisY.z * kGunGravity};
    const CVector3 position = {hotSpot.m_pos.x, hotSpot.m_pos.y, hotSpot.m_pos.z};
    const CVector3 velocity = {nx, ny, nz};
    static_cast<CKHkS08Clamp*>(m_vUnkB4.m_pBlock[index]->m_unk4)->Launch(&position, &velocity, &acceleration);  // 0x00490008
    m_vUnkB4.m_pBlock[index]->m_unk8 = 1;
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pUnk24);
    if (sounds->GetSound(0) != nullptr) {  // 0x00112bc0
        sounds->GetSound(0)->m_ui32MaxInstances = m_vUnkB4.m_ui32NbUsedElt;
        sounds->GetSound(0)->m_SoundFlags = (sounds->GetSound(0)->m_SoundFlags & 0xffffffbfu) | 0x40u;
        sounds->GetSound(0)->SetLoop(0);
        sounds->GetSound(0)->SetPosition(LtmPosition(m_pUnk20));
        sounds->GetSound(0)->Play(kGunZero);
    }
    // CKSrvFx::AcquireFx inlined: the shot effect at the hot spot, turned along its at axis.
    m_pShotFx = GunFxService()->AcquireFx(static_cast<IKFxData*>(m_pUnkEC), this);
    if (m_pShotFx == nullptr) return 1;
    CMatrix34 muzzle;
    static_cast<CSGHotSpot*>(m_pUnkD4)->GetWorldMatrix(&muzzle);
    static_cast<CKExplosionNodeFx*>(m_pShotFx)->SetTranslation(&muzzle.m_pos, this);  // 0x001b66e8
    static_cast<CKExplosionNodeFx*>(m_pShotFx)->SetDirection(&muzzle.m_at, this);    // 0x001b5e20
    static_cast<CKExplosionNodeFx*>(m_pShotFx)->Trigger(this, nullptr);              // 0x001b82a8
    m_pShotFx->ReleaseReservation(this);                                              // vt+0x54
    return 1;
}
