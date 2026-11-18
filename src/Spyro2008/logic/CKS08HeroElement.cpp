// CKS08HeroElement.cpp - C2.8 port-final F07 (class in CKS08HeroElement.h).
//
// Reconstructed original translation unit: 0x36ffa0-0x374d00 (GAME_TOC1, main_toc1), 37 functions, 36 live.
// Primary class: CKS08HeroElement  key 0x890c  category Logic  size 0x2cc  vtable 0xb231f8
// Other owners: IKSerializable (16)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x36ffa0  CKS08HeroElement_Delete  (C++ delete)
//   [ ] 0x36fff0  CKS08HeroElement_ResetFields_maybe  [dead]
//   [x] 0x370018  KBaseC_vfFC  (CKS08HeroElement.h GetDamageA)
//   [x] 0x370020  KBaseC_vf100  (CKS08HeroElement.h GetDamageB)
//   [x] 0x370028  KBaseC_vf104
//   [x] 0x3701a0  KBaseC_vf68
//   [x] 0x370210  KBaseC_vf74
//   [x] 0x3702f8  KStub_Return0_3702f8  (CKS08HeroElement.h Vf118)
//   [x] 0x370300  KStub_Return0_370300  (CKS08HeroElement.h Vf11C)
//   [x] 0x370308  CKS08HeroElement_GetAnimId  (CKS08HeroElement.h)
//   [x] 0x370318  KBaseC_vf90  (CKS08HeroElement.h)
//   [x] 0x370328  KBaseC_vf94  (CKS08HeroElement.h)
//   [x] 0x370338  KBaseC_vf60
//   [x] 0x370398  CKS08HeroElement_HasEnoughMana
//   [x] 0x370408  KBaseC_vfF8
//   [x] 0x370738  CKS08HeroElement_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3707d8  CKS08HeroElement_Create  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x370810  RegisterCKS08HeroElementClass
//   [ ] 0x370898  _GLOBAL__D_370898
//   [ ] 0x3708a8  _GLOBAL__I_3708a8
//   [x] 0x3708b8  KBaseC_vf50
//   [x] 0x370a28  CKS08HeroElement_GetHero
//   [x] 0x370ac8  CKS08HeroElement_UpdateChannel_maybe
//   [x] 0x370cc0  KBaseC_vf120
//   [x] 0x370d08  KBaseC_vf58
//   [x] 0x370f88  CKS08HeroElement_SetCastFxActive_maybe
//   [x] 0x3712a0  KBaseC_vf5C
//   [x] 0x3714e8  CKS08HeroElement_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x371578  CKS08HeroElement_RecursiveRegistration  (CKS08HeroElement.h)
//   [x] 0x371580  CKS08HeroElement_Destroy
//   [x] 0x3715d8  CKS08HeroElement_PostLoad
//   [x] 0x371608  KBaseC_vf80
//   [x] 0x371710  KBaseC_vf64
//   [x] 0x371ab8  KBaseC_vf6C
//   [x] 0x371e58  CKS08HeroElement_FireProjectile
//   [x] 0x372158  CKS08HeroElement_Load
//   [ ] 0x373818  CKS08HeroElement_Save
//
//   [ ] 0x990b28  IKSerializable_IsKindOf  [inline]
//   [ ] 0x990b40  KStub_Nop_990b40  [inline]
//   [ ] 0x990cf0  IKSerializable_DeletingDestructor  [inline]
//   [ ] 0x990d20  IKSerializable_Destructor  [inline]
//   [x] 0x990d58  IKSerializable_GetName  [inline]
//   [x] 0x9bede0  CKS08HeroElement_GetClassType  (DOTD_CLASS_KEY)
//   [x] 0x9bede8  CKS08HeroElement_GetClassID  (DOTD_CLASS_KEY)
//   [x] 0x9bedf0  KStub_Nop_9bedf0  (CKS08HeroElement.h Vf7C)
//   [x] 0x9bedf8  KStub_Return0_9bedf8  (CKS08HeroElement.h Vf84)
//   [x] 0x9bee00  KStub_Nop_9bee00  (CKS08HeroElement.h Vf88)
//   [x] 0x9bee08  KBaseC_vf98  (CKS08HeroElement.h)
//   [x] 0x9bee10  KBaseC_vf9C  (CKS08HeroElement.h)
//   [x] 0x9bee18  KBaseC_vfA0  (CKS08HeroElement.h)
//   [x] 0x9bee20  KBaseC_vfA4  (CKS08HeroElement.h)
//   [x] 0x9bee28  KBaseC_vfA8  (CKS08HeroElement.h)
//   [x] 0x9bee30  KBaseC_vfAC  (CKS08HeroElement.h)
//   [x] 0x9bee38  KBaseC_vfB0  (CKS08HeroElement.h)
//   [x] 0x9bee40  KBaseC_vfB4  (CKS08HeroElement.h)
//   [x] 0x9bee48  KBaseC_vfB8  (CKS08HeroElement.h)
//   [x] 0x9bee50  KBaseC_vfBC  (CKS08HeroElement.h)
//   [x] 0x9bee58  KBaseC_vfC0  (CKS08HeroElement.h)
//   [x] 0x9bee60  KBaseC_vfC4  (CKS08HeroElement.h)
//   [x] 0x9bee68  KBaseC_vfC8  (CKS08HeroElement.h)
//   [x] 0x9bee70  KBaseC_vfCC  (CKS08HeroElement.h)
//   [x] 0x9bee78  KBaseC_vfD0  (CKS08HeroElement.h)
//   [x] 0x9bee80  KBaseC_vfD4  (CKS08HeroElement.h)
//   [x] 0x9bee88  KBaseC_vfD8  (CKS08HeroElement.h)
//   [x] 0x9bee90  KBaseC_vfDC  (CKS08HeroElement.h)
//   [x] 0x9bee98  KBaseC_vfE0  (CKS08HeroElement.h)
//   [x] 0x9beea0  KBaseC_vfE4  (CKS08HeroElement.h)
//   [x] 0x9beea8  KBaseC_vfE8  (CKS08HeroElement.h)
//   [x] 0x9beeb0  KBaseC_vfEC  (CKS08HeroElement.h)
//   [x] 0x9beeb8  KBaseC_vfF0  (CKS08HeroElement.h)
//   [x] 0x9beec0  KBaseC_vfF4  (CKS08HeroElement.h)
//   [x] 0x9beec8  KBaseC_vf108  (CKS08HeroElement.h)
//   [x] 0x9beed0  KBaseC_vf10C  (CKS08HeroElement.h)
//   [x] 0x9beed8  KBaseC_vf110  (CKS08HeroElement.h)
//   [x] 0x9beee0  KBaseC_vf114  (CKS08HeroElement.h)
//   [x] 0x9beee8  KBaseC_vf124  (CKS08HeroElement.h)
//   [x] 0x9beef0  KBaseC_vf128  (CKS08HeroElement.h)
//   [x] 0x9bef00  KBaseC_vf12C  (CKS08HeroElement.h)
//   [x] 0x9bef08  KStub_Return0_9bef08  (CKS08HeroElement.h Vf138)
//   [x] 0x9bef10  CKS08HeroElement_IsKindOfClass  (CKS08HeroElement.h)
//   [x] 0x9bf0a8  BreathSegmentChain_Build_maybe  (BuildSegments in this file)
//   [x] 0x9bf7a8  CKS08HeroElement_DeletingDestructor  (~CKS08HeroElement)
//   [x] 0x9bf7e8  CKS08HeroElement_Destructor  (~CKS08HeroElement)
//   [ ] 0x9bf800  CKAbilityElement_maybe_vf8  [inline]
//   [ ] 0x9bf828  CKAbilityElement_maybe_vf14  [inline]
//   [ ] 0x9bf830  CKAbilityElement_maybe_vf18  [inline]
//   [ ] 0x9bfc00  KBaseC_vf90_2  [inline]
//   [ ] 0x9bfc98  KBaseC_vf8C  [inline]
//   [ ] 0x9bfed8  KBaseC_vf74_2  [inline]
//   [ ] 0x9bfef0  KBaseC_vf94_2  [inline]
//   [ ] 0x9c5578  KBaseC_vf64_3  [inline]
//   [ ] 0x9c55c8  KBaseC_vf7C_2  [inline]
//   [ ] 0x9c55d0  KBaseC_vf90_3  [inline]
//   [ ] 0x9cd320  KBaseC_vf60_2  [inline]
//   [ ] 0x9cd328  KStub_Return0_9cd328  [inline]
//   [ ] 0x9cd380  KBaseC_vf50_2  [inline]
//   [ ] 0x9cd388  KBaseC_vf54_2  [inline]
//   [ ] 0x9cd390  KBaseC_vf58_2  [inline]
//   [ ] 0x9cd398  KBaseC_vf5C_2  [inline]
//   [ ] 0x9cd3a0  KBaseC_vf70_4  [inline]
//   [ ] 0x9cd3a8  KBaseC_vf74_5  [inline]
//   [ ] 0x9cd3b0  KBaseC_vf78_4  [inline]
//   [ ] 0x9cd3b8  KBaseC_vf7C_3  [inline]
#include "Spyro2008/logic/CKS08HeroElement.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/hooks/IKHkEnemy.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/DirectionController.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CKProjectileTypeBallisticPFX.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKSparkNodeFx.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/IKProjectileType.h"
#include "k2000/system/BreathSegmentChain.h"
#include "k2000/system/IKTime.h"

namespace {

CKS08GameManager* GameManager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }  // TOC +0x3030 -> +0x8c

constexpr CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x3060)
constexpr uint8_t kWhite[4] = {0xff, 0xff, 0xff, 0xff};  // 0x00c50dfc (TOC +0x305c)

// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }

bool SignBit(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}

// The standard property block of a particle node's emitter (its class's property table, entry 1).
RpPrtStdEmitterStandard* EmitterStandard(IKSerializable* particleNode) {
    RpPrtStdEmitter* emitter = static_cast<CParticlesNodeFx*>(particleNode)->m_pRpPrtStdEmitter;  // +0x58
    return reinterpret_cast<RpPrtStdEmitterStandard*>(reinterpret_cast<uint8_t*>(emitter) +
                                                      emitter->emtClass->propTab->propOffset[1]);
}

// 0x009bf0a8 BreathSegmentChain_Build_maybe (inlined COMDAT; the original unrolls the recursion nine segments deep):
// `node` set up as the segment after `parent` (no target, not turning, timer -1, `segment` long, its length the
// parent's plus `segment` or 0 without a parent, its vector `direction` times that length), then `count` more after it.
void BuildSegments(float segment, DirectionController* node, const CVector3* direction, int8_t count,
                   DirectionController* parent) {
    node->m_pParent = parent;
    node->m_bTurning = 0;
    node->m_fSpeed = 0.0f;
    node->m_v3Target = kNullVector;
    node->m_fTimer = -1.0f;
    node->m_fSegment = segment;
    float length;
    if (node->m_pParent == nullptr) {
        node->m_fLength = 0.0f;
        length = node->m_fLength;
    } else {
        length = segment + node->m_pParent->m_fLength;
        node->m_fLength = length;
    }
    node->m_v3Vector.x = length * direction->x;
    node->m_v3Vector.z = length * direction->z;
    node->m_v3Vector.y = length * direction->y;
    if (count < 1) {
        node->m_pNext = nullptr;
        return;
    }
    DirectionController* next = static_cast<DirectionController*>(Mem_AllocAligned16(sizeof(DirectionController)));
    node->m_pNext = next;
    BuildSegments(segment, next, direction, static_cast<int8_t>(count - 1), node);
}

}  // namespace

// 0x00371580 CKS08HeroElement_Destroy: the two damage blocks freed (the pointers are kept).
void CKS08HeroElement::Destroy() {
    if (m_pDamageA != nullptr) Mem_FreeAligned16(m_pDamageA);  // 0x00052fb8
    if (m_pDamageB != nullptr) Mem_FreeAligned16(m_pDamageB);
}

// 0x00372158 CKS08HeroElement_Load: the damage blocks dropped (+0x2ac, +0x2a8), then (level data only) the four levels
// of both sides interleaved, then the single values; +0x2b0 / +0x2b4 are read as raw bytes (colours).
int32_t CKS08HeroElement::Load(IKFile* file, int32_t type) {
    m_pDamageB = nullptr;
    m_pDamageA = nullptr;
    if (type == 0) {
        for (int32_t i = 0; i < 4; ++i) {
            ReadS32LE(file, &m_unk10[i]);
            ReadS32LE(file, &m_unk20[i]);
            ReadS32LE(file, &m_unk30[i]);
            ReadU32LE(file, &m_unk40[i]);
            ReadF32LE(file, &m_unk50[i]);
            ReadU32LE(file, &m_unk60[i]);
            ReadF32LE(file, &m_unk70[i]);
            for (int32_t k = 0; k < 9; ++k) ReadF32LE(file, &m_unk84[k][i]);  // +0x84 .. +0x104
            ReadU8(file, &m_unk114[i]);
            ReadU8(file, &m_unk118[i]);
            ReadU32LE(file, &m_unk130[i]);
            ReadS32LE(file, &m_unk16c[i]);
            ReadU32LE(file, &m_unk17c[i]);
            ReadF32LE(file, &m_unk18c[i]);
            ReadS32LE(file, &m_unk19c[i]);
            ReadF32LE(file, &m_unk1ac[i]);
            for (int32_t k = 0; k < 9; ++k) ReadF32LE(file, &m_unk1c0[k][i]);  // +0x1c0 .. +0x240
            ReadU8(file, &m_unk250[i]);
            ReadU8(file, &m_unk254[i]);
        }
        ReadU8(file, &m_unk80);
        ReadU8(file, &m_unk140);
        ReadS32LE(file, &m_unk144);
        ReadU8(file, &m_unk1bc);
        ReadU8(file, &m_unk268);
        ReadS32LE(file, &m_unk274);
        ReadF32LE(file, &m_unk11c);
        for (int32_t i = 0; i < 4; ++i) {
            IKFile_ReadRef(file, &m_apUnk120[i]);
            IKFile_ReadRef(file, &m_apUnk258[i]);
        }
        IKFile_ReadRef(file, &m_unk26c);
        ReadRaw(file, m_unk2b0.m_aRgba, 4);
        ReadRaw(file, m_unk2b4.m_aRgba, 4);
        ReadS32LE(file, &m_unk278);
        ReadU32LE(file, &m_unk2a0);
        ReadF32LE(file, &m_unk2a4);
        ReadU8(file, &m_unk148);
        ReadU8(file, &m_unk149);
        ReadU8(file, &m_unk27c);
        ReadU8(file, &m_unk27d);
        ReadU8(file, &m_unk14a);
        ReadU8(file, &m_unk27e);
        ReadF32LE(file, &m_unk14c);
        ReadF32LE(file, &m_unk150);
        ReadF32LE(file, &m_unk280);
        ReadF32LE(file, &m_unk284);
        ReadU8(file, &m_unk154);
        ReadU8(file, &m_unk155);
        ReadU8(file, &m_unk288);
        ReadU8(file, &m_unk289);
        ReadU8(file, &m_unk156);
        ReadU8(file, &m_unk28a);
        ReadF32LE(file, &m_unk158);
        ReadF32LE(file, &m_unk15c);
        ReadF32LE(file, &m_unk28c);
        ReadF32LE(file, &m_unk290);
        ReadF32LE(file, &m_unk160);
        ReadF32LE(file, &m_unk164);
        ReadF32LE(file, &m_unk294);
        ReadF32LE(file, &m_unk298);
    }
    return 1;
}

// 0x003715d8 CKS08HeroElement_PostLoad: the runtime cleared (the beam pointer is dropped, not freed), +0x2c4 5.0.
int32_t CKS08HeroElement::PostLoad(int32_t /*type*/) {
    m_pBeam = nullptr;
    m_unk2c0 = 0.0f;  // stw 0
    m_unk2c4 = 5.0f;  // TOC +0x3014
    m_unk2bc = 0;
    m_unk270 = nullptr;
    m_pHero = nullptr;
    return 1;
}

// 0x003708b8 KBaseC_vf50 (vt+0x50)
void CKS08HeroElement::UpdateProjectiles(IKTime* clock, int32_t level) {
    if (static_cast<CKProjectileAccessor*>(m_apUnk120[level])->m_pProjectileType == nullptr) return;
    const uint8_t count =
        static_cast<IKProjectileType*>(static_cast<CKProjectileAccessor*>(m_apUnk120[level])->m_pProjectileType)
            ->m_ui8NbOfActiveProjectiles;  // +0x21
    if (count == 0) return;
    uint32_t moved = 0;
    do {
        IKProjectileType* type =
            static_cast<IKProjectileType*>(static_cast<CKProjectileAccessor*>(m_apUnk120[level])->m_pProjectileType);
        type->UpdateMotion(static_cast<uint8_t>(moved), clock->m_afDeltaTime[0]);  // vt+0x50, clock +0x1c
        ++moved;
    } while (count != moved);
    uint32_t index = 0;
    for (;;) {
        const uint8_t current = static_cast<uint8_t>(index);
        // vt+0xac: only CKProjectileTypeBallisticPFX has the slot (its GetProjectileAge).
        CKProjectileTypeBallisticPFX* type = static_cast<CKProjectileTypeBallisticPFX*>(
            static_cast<CKProjectileAccessor*>(m_apUnk120[level])->m_pProjectileType);
        const float age = type->GetProjectileAge(current) * m_unk11c;
        ++index;
        if (!(age <= m_unk50[level])) {  // ble (NaN: dies)
            static_cast<IKProjectileType*>(static_cast<CKProjectileAccessor*>(m_apUnk120[level])->m_pProjectileType)
                ->OnDeath(current);  // vt+0x5c
            return;
        }
        if (moved == index) return;
    }
}

// 0x00371e58 CKS08HeroElement_FireProjectile (vt+0x54): with the hero and mana for `level` (else vt+0x60), the mana
// spent and a projectile of the level's accessor launched from the hot spot (vt+0x124; 0xff: 1) along the aim (or
// towards the grabbed enemy), at the hero's speed plus +0x11c, with damage block A (vt+0xfc).
void CKS08HeroElement::FireProjectile(int8_t level) {
    CKS08GameManager* manager = GameManager();
    if (GetHero() == nullptr) return;  // vt+0x134
    if (manager->GetDragonMana(m_ui8Dragon) < m_unk60[level]) {  // 0x004fd7c8; cmplw blt
        OnOutOfMana();  // vt+0x60
        return;
    }
    manager->ConsumeDragonMana(m_ui8Dragon, m_unk60[level]);  // 0x004fd808
    uint8_t spot = GetHotSpotIndex();  // vt+0x124
    if (spot == 0xff) spot = 1;
    CVector3 position;
    static_cast<CSGHotSpot*>(m_pHero->GetHotSpot(spot))->GetWorldPosition(&position);  // 0x00361b70, 0x000ce790
    CVector3 direction;
    float squared;
    if (m_pHero->GetGrabTarget() == nullptr) {  // 0x00329df8
        direction = m_pHero->GetAimDirection();  // 0x0032a708
        squared = ppc::fmadds(direction.x, direction.x, direction.y * direction.y);
    } else {
        const CVector3& target = static_cast<IKHkEnemy*>(m_pHero->GetGrabTarget())->m_v3Position;  // +0x134
        direction.x = target.x - position.x;
        const float dy = target.y - position.y;
        direction.z = target.z - position.z;
        const float* hero = m_pHero->GetPositionPtr();  // 0x00361968
        direction.y = dy + (position.y - hero[1]);
        squared = ppc::fmadds(direction.x, direction.x, direction.y * direction.y);
    }
    const float length = Sqrtf(ppc::fmadds(direction.z, direction.z, squared));  // 0x00010690
    if (length != 0.0f) {  // bne (NaN: scaled)
        const float inverse = 1.0f / length;
        direction.z = direction.z * inverse;
        direction.x = direction.x * inverse;
        direction.y = direction.y * inverse;
    }
    CKProjectileAccessor* accessor = static_cast<CKProjectileAccessor*>(m_apUnk120[static_cast<uint8_t>(level)]);
    if (accessor->m_pProjectileType == nullptr) return;
    const float bonus = m_unk11c;
    const float speed = m_pHero->GetCurrentSpeed();  // 0x00329d90
    DamageParams* damage = GetDamageA();             // vt+0xfc
    // The projectile type gets the 0x40-byte block where a damage object is expected (vt+0x88's damage).
    accessor->LaunchEx(&position, &direction, bonus + speed, reinterpret_cast<IKSerializable*>(damage), m_pHero,
                       nullptr);  // 0x001f2988
}

// 0x00370d08 KBaseC_vf58 (vt+0x58). The result of vt+0x5c is not used (the beam hits nothing in this design).
void CKS08HeroElement::UpdateBeam(float dt, float speed, float scale, uint8_t level) {
    ScaleDamageB(dt, level);                 // vt+0x104
    const float follow = GetFollowSpeed();   // vt+0x12c
    IKGrpEnemy* enemies = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);
    if (enemies == nullptr) return;
    DirectionChain* beam = m_pBeam;
    CVector3 aim = m_pHero->GetHotspot4FlatDir();  // 0x0032ba68
    DirectionController_SetDirectionAndUpdate(dt, speed, follow, beam, &aim);  // 0x00300120
    CVector3 origin = kNullVector;
    if (m_ui8Dragon == 0) {
        static_cast<CSGHotSpot*>(m_pHero->GetHotSpot(0x12))->GetWorldPosition(&origin);
    } else if (m_ui8Dragon == 1) {
        static_cast<CSGHotSpot*>(m_pHero->GetHotSpot(0x12))->GetWorldPosition(&origin);
    }
    const uint32_t count = enemies->m_ui32NbActiveEnemies;  // +0x120
    if (count == 0) return;
    uint32_t i = 0;
    do {
        IKSerializable* enemy = enemies->m_apActiveEnemies[i];  // +0x58
        ++i;
        const RwFrame* frame = static_cast<CSGMovable*>(static_cast<IKHook*>(enemy)->m_pKGLObject)->m_pRwFrame;
        // (The original also takes |point.y - origin.y| into a stack word nothing reads.)
        const CVector3 point = {frame->ltm.pos.x, frame->ltm.pos.y, frame->ltm.pos.z};
        const CVector3 from = origin;
        IsPointInBeam(scale, &point, &from, static_cast<int8_t>(level));  // vt+0x5c
    } while (count != i);
}

// 0x003712a0 KBaseC_vf5C (vt+0x5c): within the beam's reach (vt+0x12c times `scale`, at most +0x18c[level]) in x / z,
// and within half the cone angle (+0x1ac[level]) of the segment that spans the distance.
uint8_t CKS08HeroElement::IsPointInBeam(float scale, const CVector3* point, const CVector3* origin, int8_t level) {
    const float reach = GetFollowSpeed() * scale;  // vt+0x12c
    float limit = m_unk18c[level];
    if (!(reach > limit)) limit = reach;  // bgt keeps the length (NaN: the reach)
    const float dz = point->z - origin->z;
    const float dx = point->x - origin->x;
    const float distance = Sqrtf(ppc::fmadds(dx, dx, dz * dz));  // 0x00010690
    if (limit < distance) return 0;  // blt
    const float halfAngle = m_unk1ac[level] * 0.5f;
    DirectionController* node = m_pBeam->m_pFirst;
    uint32_t i = 1;
    DirectionController* next;
    for (;;) {
        const uint32_t segments = GetSegmentCount();  // vt+0x128
        if (static_cast<uint8_t>(i) >= segments) return 0;  // cmplw bge
        ++i;
        const float start = node->m_fLength;
        next = node->m_pNext;
        node = next;
        if (!(start <= distance)) continue;          // cror eq|lt
        if (distance >= next->m_fLength) continue;   // bge
        break;
    }
    const float ox = origin->x;
    const float oy = origin->y;
    const float oz = origin->z;
    const float sy = (oy + next->m_v3Vector.y) - oy;
    const float sx = (ox + next->m_v3Vector.x) - ox;
    const float sz = (oz + next->m_v3Vector.z) - oz;
    const float py = point->y - oy;
    const float px = point->x - ox;
    const float pz = point->z - oz;
    const float lengths = distance * next->m_fLength;
    float cosine = ppc::fmadds(pz, sz, ppc::fmadds(px, sx, py * sy)) / lengths;
    if (cosine <= -1.0f) {
        cosine = -1.0f;
    } else if (cosine >= 1.0f) {
        cosine = 1.0f;
    }
    const float angle = crt::Acosf(cosine);  // 0x0098e1a0
    return (halfAngle * 0.0174532905f >= angle) ? 1 : 0;  // TOC +0x3068 pi / 180
}

// 0x00370338 KBaseC_vf60 (vt+0x60)
void CKS08HeroElement::OnOutOfMana() {
    if (GetHero() != nullptr) m_pHero->EnableSubNode(0);  // 0x00329e00
}

// 0x00371710 KBaseC_vf64 (vt+0x64): with `on`, the hero's particle node 0 emits in a cone of half the angle
// +0x1ac[level]: its initial direction (0, 0, (1 + cos) / 2) and bias (sin, 0, 1 - (1 + cos) / 2) (the sine is 1 above
// pi / 2). The game's inlined sine / cosine, the library's for a negative angle.
void CKS08HeroElement::SetBeamFxActive(int8_t level, uint8_t on) {
    if (GetHero() == nullptr) return;
    if (on != 0) {
        const float x = (m_unk1ac[level] * 0.5f) * 0.0174532905f;  // TOC +0x3064, +0x3068
        float sine;
        if (x <= 1.57079613f) {  // TOC +0x3098; ble (NaN: 1)
            sine = SignBit(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x);  // 0x009a1390
        } else {
            sine = 1.0f;
        }
        const float cosine = SignBit(x) ? crt::LibCosf(-x) : crt::InlineCosf(x);  // 0x009a11d8
        const float half = (cosine + 1.0f) * 0.5f;
        const float rest = 1.0f - half;
        RpPrtStdEmitterStandard* standard = EmitterStandard(m_pHero->GetSubNode(0));  // 0x00329e80
        standard->prtInitDirBias.x = sine;  // +0x6c
        standard->prtInitDirBias.y = 0.0f;
        standard->prtInitDirBias.z = rest;
        standard = EmitterStandard(m_pHero->GetSubNode(0));
        standard->prtInitDir.x = 0.0f;  // +0x60
        standard->prtInitDir.y = 0.0f;
        standard->prtInitDir.z = half;
    }
    SetCastFxActive(on);  // vt+0x130
}

// 0x003701a0 KBaseC_vf68 (vt+0x68)
void CKS08HeroElement::StartRepeatFire(int8_t level) {
    if (m_ui8Dragon == 0 && m_unk0c == 0) {
        m_unk2b8 = 0.12f;  // TOC +0x3018
        m_unk2bc = m_unk30[level];
        return;
    }
    m_unk2b8 = 0.0f;  // stw 0
    m_unk2bc = m_unk30[level];
}

// 0x00371ab8 KBaseC_vf6C (vt+0x6c)
void CKS08HeroElement::StartBeam(float speed, int8_t level) {
    if (GetHero() == nullptr) return;
    m_unk2c0 = 0.0f;
    const float follow = GetFollowSpeed();  // vt+0x12c
    const float length = m_unk18c[level];
    const uint32_t count = GetSegmentCount();  // vt+0x128
    const uint32_t count2 = GetSegmentCount();
    DirectionChain* beam = static_cast<DirectionChain*>(Mem_AllocAligned16(sizeof(DirectionChain)));  // 0x00053198
    m_pBeam = beam;
    const CVector3 aim = m_pHero->GetAimDirection();  // 0x0032a708
    float x = aim.x;
    float y = aim.y;
    float z = aim.z;
    const float norm = Sqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
    if (norm != 0.0f) {  // bne (NaN: scaled)
        const float inverse = 1.0f / norm;
        z = z * inverse;
        x = x * inverse;
        y = y * inverse;
    }
    beam->m_v3Direction.x = kNullVector.x + x;
    beam->m_v3Direction.y = kNullVector.y + y;
    beam->m_v3Direction.z = kNullVector.z + z;
    beam->m_f0c = speed;
    beam->m_f10 = follow;
    if (static_cast<int8_t>(count2) <= 0) {
        beam->m_pFirst = nullptr;
    } else {
        const float segment = length / static_cast<float>(static_cast<double>(static_cast<uint32_t>(count - 1)));
        DirectionController* root = static_cast<DirectionController*>(Mem_AllocAligned16(sizeof(DirectionController)));
        beam->m_pFirst = root;
        const CVector3 direction = beam->m_v3Direction;
        root->m_pParent = nullptr;
        root->m_bTurning = 0;
        root->m_fSpeed = 0.0f;
        root->m_v3Target = kNullVector;
        root->m_fTimer = -1.0f;
        root->m_fSegment = segment;
        float rootLength;
        if (root->m_pParent == nullptr) {
            rootLength = 0.0f;
            root->m_fLength = 0.0f;
        } else {
            rootLength = segment + root->m_pParent->m_fLength;
            root->m_fLength = rootLength;
        }
        root->m_v3Vector.z = direction.z * rootLength;
        root->m_v3Vector.x = direction.x * rootLength;
        root->m_v3Vector.y = direction.y * rootLength;
        if (static_cast<int8_t>(count2 - 1) == 0) {
            root->m_pNext = nullptr;
        } else {
            DirectionController* next = static_cast<DirectionController*>(Mem_AllocAligned16(sizeof(DirectionController)));
            root->m_pNext = next;
            BuildSegments(segment, next, &direction, static_cast<int8_t>(count2 - 2), root);  // 0x009bf0a8
        }
    }
    SetBeamFxActive(level, 1);  // vt+0x64
}

// 0x00370398 CKS08HeroElement_HasEnoughMana (vt+0x70)
uint8_t CKS08HeroElement::HasEnoughMana(uint8_t level) {
    return GameManager()->GetDragonMana(m_ui8Dragon) > m_unk60[level] ? 1 : 0;  // cmplw bgt
}

// 0x00370210 KBaseC_vf74 (vt+0x74)
void CKS08HeroElement::UpdateRepeatFire(float dt, int8_t level) {
    const float left = m_unk2b8 - dt;
    m_unk2b8 = left;
    if (!(left < 0.0f)) return;  // blt
    if (m_unk2bc <= 0) return;
    FireProjectile(level);  // vt+0x54
    m_unk2bc = m_unk2bc - 1;
    m_unk2b8 = 1.0f / static_cast<float>(m_unk20[level]);
}

// 0x00370ac8 CKS08HeroElement_UpdateChannel_maybe (vt+0x78)
int32_t CKS08HeroElement::UpdateChannel(float dt, float speed, float scale, uint8_t level) {
    if (GetHero() == nullptr) return 1;  // vt+0x134
    CKS08GameManager* manager = GameManager();
    const uint32_t mana = manager->GetDragonMana(m_ui8Dragon);  // 0x004fd7c8
    const float owed = m_unk2c0;
    if (static_cast<uint32_t>(ppc::fctidz(owed)) >= mana) {  // fctidz, cmplw bge
        OnOutOfMana();  // vt+0x60
        return 1;
    }
    const float total = ppc::fmadds(static_cast<float>(m_unk19c[level]), dt, owed);
    m_unk2c0 = total;
    if (total >= 1.0f) {  // cror gt|eq (NaN: kept)
        manager->ConsumeDragonMana(m_ui8Dragon, static_cast<uint32_t>(ppc::fctidz(total)));  // 0x004fd808
        const float now = m_unk2c0;
        const uint32_t whole = static_cast<uint32_t>(ppc::fctidz(now));
        m_unk2c0 = now - static_cast<float>(static_cast<double>(static_cast<uint64_t>(whole)));
    }
    UpdateBeam(dt, speed, scale, level);  // vt+0x58
    return 0;
}

// 0x00371608 KBaseC_vf80 (vt+0x80)
void CKS08HeroElement::StopBeam(uint8_t level) {
    if (GetHero() == nullptr) return;
    if (m_pBeam != nullptr) {
        DirectionChain* beam = m_pBeam;
        DirectionController* first = beam->m_pFirst;
        // BUG(original): a beam built without segments (vt+0x128 <= 0) has no root; the original reads its +0x2c
        // (address 0x2c) here. Natively the null root is skipped.
        if (first != nullptr && first->m_pNext != nullptr) {
            BreathSegmentChain_Free(first->m_pNext);  // 0x009bef38
            Mem_FreeAligned16(first->m_pNext);        // 0x00052fb8
        }
        Mem_FreeAligned16(beam->m_pFirst);
        Mem_FreeAligned16(m_pBeam);
        m_pBeam = nullptr;
    }
    SetBeamFxActive(static_cast<int8_t>(level), 0);  // vt+0x64
}

// 0x00370408 KBaseC_vfF8 (vt+0xf8)
void CKS08HeroElement::SetDamageLevel(uint8_t level) {
    if (m_pDamageA == nullptr) m_pDamageA = static_cast<DamageParams*>(Mem_CallocAligned16(1, 0x40));  // 0x000531f8
    if (m_pDamageB == nullptr) m_pDamageB = static_cast<DamageParams*>(Mem_CallocAligned16(1, 0x40));
    m_pDamageA->m_fDamage = static_cast<float>(m_unk10[level]);
    m_pDamageA->m_af04[1] = m_unk84[1][level];  // +0x08 = +0x94
    m_pDamageA->m_af04[0] = m_unk84[0][level];  // +0x04 = +0x84
    m_pDamageA->m_af04[2] = m_unk84[2][level];
    m_pDamageA->m_af04[3] = m_unk84[3][level];
    m_pDamageA->m_af04[4] = m_unk84[4][level];
    m_pDamageA->m_af04[7] = m_unk84[7][level];  // +0x20 = +0xf4
    m_pDamageA->m_af04[6] = m_unk84[6][level];
    m_pDamageA->m_af04[5] = m_unk84[5][level];
    m_pDamageA->m_af04[8] = m_unk84[8][level];
    m_pDamageA->m_ui8_28 = m_unk114[level];
    m_pDamageA->m_ui8_29 = m_unk118[level];
    m_pDamageA->m_unk2c = 0;
    m_pDamageA->m_unk30 = 0;
    m_pDamageA->m_unk34 = 0;
    m_pDamageA->m_f38 = m_unk70[level];
    m_pDamageB->m_fDamage = static_cast<float>(m_unk16c[level]);
    m_pDamageB->m_af04[1] = m_unk1c0[1][level];
    m_pDamageB->m_af04[0] = m_unk1c0[0][level];
    m_pDamageB->m_af04[2] = m_unk1c0[2][level];
    m_pDamageB->m_af04[3] = m_unk1c0[3][level];
    m_pDamageB->m_af04[4] = m_unk1c0[4][level];
    m_pDamageB->m_af04[7] = m_unk1c0[7][level];
    m_pDamageB->m_af04[6] = m_unk1c0[6][level];
    m_pDamageB->m_af04[5] = m_unk1c0[5][level];
    m_pDamageB->m_af04[8] = m_unk1c0[8][level];
    m_pDamageB->m_ui8_28 = m_unk250[level];
    m_pDamageB->m_ui8_29 = m_unk254[level];
    m_pDamageB->m_unk2c = 0;
    m_pDamageB->m_unk30 = 0;
    m_pDamageB->m_unk34 = 0;
    std::memset(&m_pDamageB->m_f38, 0, 4);  // stw 0
}

// 0x00370028 KBaseC_vf104 (vt+0x104)
void CKS08HeroElement::ScaleDamageB(float scale, int32_t level) {
    m_pDamageB->m_fDamage = static_cast<float>(m_unk16c[level]) * scale;
    m_pDamageB->m_af04[1] = scale * m_unk1c0[1][level];
    m_pDamageB->m_af04[0] = scale * m_unk1c0[0][level];
    m_pDamageB->m_af04[2] = scale * m_unk1c0[2][level];
    m_pDamageB->m_af04[3] = scale * m_unk1c0[3][level];
    m_pDamageB->m_af04[4] = scale * m_unk1c0[4][level];
    m_pDamageB->m_af04[7] = scale * m_unk1c0[7][level];
    m_pDamageB->m_af04[6] = scale * m_unk1c0[6][level];
    m_pDamageB->m_af04[5] = scale * m_unk1c0[5][level];
    m_pDamageB->m_af04[8] = scale * m_unk1c0[8][level];
    m_pDamageB->m_ui8_28 = m_unk250[level];
    m_pDamageB->m_ui8_29 = m_unk254[level];
    m_pDamageB->m_unk2c = 0;
    m_pDamageB->m_unk30 = 0;
    m_pDamageB->m_unk34 = 0;
    std::memset(&m_pDamageB->m_f38, 0, 4);  // stw 0
}

// 0x00370cc0 KBaseC_vf120 (vt+0x120)
CKS08HeroElement::Color CKS08HeroElement::GetColor(int32_t side) {
    if (side == 0) return m_unk2b0;
    if (side == 1) return m_unk2b4;
    Color white;
    std::memcpy(white.m_aRgba, kWhite, 4);
    return white;
}

// 0x00370f88 CKS08HeroElement_SetCastFxActive_maybe (vt+0x130). The pooled lookup is the inlined CKSrvFx::AcquireFx.
void CKS08HeroElement::SetCastFxActive(uint8_t on) {
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    if (on == 0) {
        if (m_unk270 == nullptr) return;
        StopOwnedSparkEffect(reinterpret_cast<CKSparkNodeFx*>(m_unk270), this);  // 0x001d4698
        m_unk270->ReleaseReservation(this);  // vt+0x54
        m_unk270 = nullptr;
        return;
    }
    CKSparkFxData* spark = static_cast<CKSparkFxData*>(m_unk26c);
    if (m_ui8Dragon == 0) {
        spark->m_unk10 = m_pHero->GetHotSpot(0x12);
        spark->m_unk0c = nullptr;
    } else {
        spark->m_unk10 = m_pHero->GetHotSpot(0x12);
        spark->m_unk0c = nullptr;
    }
    m_unk270 = fx->AcquireFx(spark, this);
}

// 0x00370a28 CKS08HeroElement_GetHero (vt+0x134)
CKHkS08Hero* CKS08HeroElement::GetHero() {
    if (m_pHero != nullptr) return m_pHero;
    IKGrpHero* heroes = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);  // +0x08
    if (heroes == nullptr) {
        m_pHero = nullptr;
        return nullptr;
    }
    m_pHero = static_cast<CKHkS08Hero*>(heroes->m_apHeros[m_ui8Dragon]);  // 0x002ca080 GetHeroByDragonIndex
    return m_pHero;
}
