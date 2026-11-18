// CKS08HeroElementFear.cpp - C2.8 port-final F08 (class in CKS08HeroElementFear.h).
//
// Reconstructed original translation unit: 0x3cff48-0x3d0f88 (GAME_TOC1, main_toc1), 18 functions, 17 live.
// Primary class: CKS08HeroElementFear  key 0x8a4c  category Logic  size 0x2e4  vtable 0xb24298
// Other owners: CKS08HeroElement (1), CKS08HeroElementShadow (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3cff48  CKS08HeroElement_IsPointInAimCone_maybe
//   [x] 0x3d0148  CKS08HeroElementFear_AffectEnemiesInCone_maybe
//   [x] 0x3d0360  CKS08HeroElementFear_RecursiveRegistration
//   [x] 0x3d0388  CKS08HeroElementFear_Destroy
//   [x] 0x3d03b0  CKS08HeroElementFear_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3d0450  CKS08HeroElementFear_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x3d04e0  RegisterCKS08HeroElementFearClass
//   [ ] 0x3d0568  _GLOBAL__D_3d0568
//   [ ] 0x3d0578  _GLOBAL__I_3d0578
//   [x] 0x3d0588  CKS08HeroElementFear_Create  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3d05c0  CKS08HeroElementFear_PostLoad
//   [x] 0x3d05e8  CKS08HeroElementFear_PlayCastFx_maybe
//   [x] 0x3d08a0  CKS08HeroElementFear_TryCast_maybe
//   [x] 0x3d09c8  CKS08HeroElementFear_UpdateRepeatCast_maybe
//   [x] 0x3d0a90  CKS08HeroElementFear_Load
//   [ ] 0x3d0ce0  CKS08HeroElementFear_Save
//   [x] 0x3d0f30  CKS08HeroElementShadow_Delete  (C++ delete: DOTD_DECLARE_FACTORIES(CKS08HeroElementShadow))
//   [ ] 0x3d0f80  KStub_Nop_3d0f80  [dead]
//
//   [x] 0x9c04c8  CKS08HeroElementFear_IsKindOfClass  (CKS08HeroElementFear.h)
//   [x] 0x9c0500  CKS08HeroElementFear_GetClassType  (DOTD_CLASS_KEY)
//   [x] 0x9c0508  CKS08HeroElementFear_GetClassID  (DOTD_CLASS_KEY)
//   [x] 0x9c0510  CKS08HeroElementFear_Destructor  (~CKS08HeroElementFear)
//   [x] 0x9c0530  CKS08HeroElementFear_DeletingDestructor  (~CKS08HeroElementFear)
#include "Spyro2008/logic/CKS08HeroElementFear.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"

#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/components/CKQuakeCameraLauncher.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvFx.h"

namespace {

CKS08GameManager* GameManager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }  // TOC +0x3eb8 -> +0x8c

constexpr CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x3ebc)

// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }

// The sign bit cleared through memory (stfs / rlwinm / stw / lfs).
float ClearSign(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    bits &= 0x7fffffffu;
    std::memcpy(&x, &bits, sizeof(bits));
    return x;
}

}  // namespace

// 0x003d0388 CKS08HeroElementFear_Destroy (vt+0x10)
void CKS08HeroElementFear::Destroy() { CKS08HeroElement::Destroy(); }  // 0x00371580

// 0x003d0360 CKS08HeroElementFear_RecursiveRegistration (vt+0x24)
void CKS08HeroElementFear::RecursiveRegistration(int32_t type) { CKS08HeroElement::RecursiveRegistration(type); }  // 0x00371578

// 0x003d0a90 CKS08HeroElementFear_Load (vt+0x2c): the base's, then (level data only) the four cone angles and the two
// references.
int32_t CKS08HeroElementFear::Load(IKFile* file, int32_t type) {
    CKS08HeroElement::Load(file, type);  // 0x00372158
    if (type != 0) return 1;
    ReadF32LE(file, &m_unk2cc[0]);
    ReadF32LE(file, &m_unk2cc[1]);
    ReadF32LE(file, &m_unk2cc[2]);
    ReadF32LE(file, &m_unk2cc[3]);
    IKFile_ReadRef(file, &m_unk2dc);
    IKFile_ReadRef(file, &m_unk2e0);
    return 1;
}

// 0x003d05c0 CKS08HeroElementFear_PostLoad (vt+0x30)
int32_t CKS08HeroElementFear::PostLoad(int32_t type) {
    CKS08HeroElement::PostLoad(type);  // 0x003715d8
    return 1;
}

// 0x003d09c8 CKS08HeroElementFear_UpdateRepeatCast_maybe (vt+0x74)
void CKS08HeroElementFear::UpdateRepeatFire(float dt, int8_t level) {
    const float left = m_unk2b8 - dt;
    m_unk2b8 = left;
    if (!(left < 0.0f)) return;  // blt (TOC +0x3eb4)
    if (m_unk2bc <= 0) return;
    TryCast(static_cast<uint8_t>(level));  // 0x003d08a0
    m_unk2bc = m_unk2bc - 1;
    m_unk2b8 = 1.0f / static_cast<float>(m_unk20[level]);  // TOC +0x3ea4
}

// 0x003d08a0 CKS08HeroElementFear_TryCast_maybe
void CKS08HeroElementFear::TryCast(uint8_t level) {
    CKS08GameManager* manager = GameManager();
    if (GetHero() == nullptr) return;  // vt+0x134
    const uint32_t cost = m_unk60[static_cast<int8_t>(level)];
    if (manager->GetDragonMana(m_ui8Dragon) < cost) {  // 0x004fd7c8; cmplw bge
        OnOutOfMana();  // vt+0x60
        return;
    }
    manager->ConsumeDragonMana(m_ui8Dragon, cost);  // 0x004fd808
    AffectEnemiesInCone(level);                      // 0x003d0148
    PlayCastFx();                                    // 0x003d05e8
}

// 0x003d0148 CKS08HeroElementFear_AffectEnemiesInCone_maybe
void CKS08HeroElementFear::AffectEnemiesInCone(uint8_t level) {
    IKGrpEnemy* enemies = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // +0x8c -> +0x04
    if (enemies == nullptr) return;
    CVector3 origin = kNullVector;
    if (m_ui8Dragon == 0) {
        static_cast<CSGHotSpot*>(m_pHero->GetHotSpot(0x12))->GetWorldPosition(&origin);  // 0x00361b70, 0x000ce790
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
        const float dy = ClearSign(frame->ltm.pos.y - origin.y);
        const CVector3 point = {frame->ltm.pos.x, frame->ltm.pos.y, frame->ltm.pos.z};
        const CVector3 from = origin;
        if (IsPointInAimCone(&point, &from, static_cast<int8_t>(level)) == 0) continue;  // 0x003cff48
        if (!(dy < 2.0f)) continue;  // TOC +0x3ec0; bge (NaN: skipped)
        // vt+0xfc with the level in r4: the base's GetDamageA, whose result nothing uses.
        (void)GetDamageA();
    } while (count != i);
}

// 0x003cff48 CKS08HeroElement_IsPointInAimCone_maybe. The cosine is taken over the first (x / z) distance; the
// direction is normalised in x / z (its y is 0, times the inverse when scaled).
uint8_t CKS08HeroElementFear::IsPointInAimCone(const CVector3* point, const CVector3* origin, int8_t level) {
    const float range = m_unk50[level];
    const float dz0 = point->z - origin->z;
    const float dx0 = point->x - origin->x;
    const float distance = Sqrtf(ppc::fmadds(dx0, dx0, dz0 * dz0));  // 0x00010690
    if (range < distance) return 0;  // bge goes on (NaN too)
    float dx = point->x - origin->x;
    const float zero = 0.0f;  // TOC +0x3eb4
    float dy = zero;
    float dz = point->z - origin->z;
    const float angle = m_unk2cc[static_cast<uint8_t>(level)];
    const float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, zero)));
    if (length != zero) {  // beq (NaN: scaled)
        const float inverse = 1.0f / length;  // TOC +0x3ea4
        dz = dz * inverse;
        dx = dx * inverse;
        dy = inverse * zero;
    }
    const CVector3 aim = m_pHero->GetHotspot4FlatDir();  // 0x0032ba68
    float cosine = ppc::fmadds(dz, aim.z, ppc::fmadds(dx, aim.x, dy * aim.y)) / distance;
    if (cosine <= -1.0f) {  // TOC +0x3ea8; cror eq|lt
        cosine = -1.0f;
    } else if (cosine >= 1.0f) {  // cror eq|gt
        cosine = 1.0f;
    }
    const float result = crt::Acosf(cosine);  // 0x0098e1a0
    return ((angle * 0.5f) * 0.0174532905f >= result) ? 1 : 0;  // TOC +0x3eac, +0x3eb0 pi / 180; cror eq|gt
}

// 0x003d05e8 CKS08HeroElementFear_PlayCastFx_maybe. The pooled lookup is the inlined CKSrvFx::AcquireFx; the effect it
// returns is dropped.
void CKS08HeroElementFear::PlayCastFx() {
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // +0x60
    CKSparkFxData* spark = static_cast<CKSparkFxData*>(m_unk2dc);
    if (m_ui8Dragon == 0) {
        spark->m_unk10 = m_pHero->GetHotSpot(0x12);  // 0x00361b70
        spark->m_unk0c = nullptr;
    } else {
        spark->m_unk10 = m_pHero->GetHotSpot(0x12);
        spark->m_unk0c = nullptr;
    }
    fx->AcquireFx(spark, this);
    static_cast<CKQuakeCameraLauncher*>(m_unk2e0)->Trigger();  // 0x001533c0
}
