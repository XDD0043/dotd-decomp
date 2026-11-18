// CKS08HeroElementElectric.cpp - C2.8 port-final F08 (class in CKS08HeroElementElectric.h).
//
// Reconstructed original translation unit: 0x3cb878-0x3cff48 (GAME_TOC1, main_toc1), 32 functions, 28 live.
// Primary class: CKS08HeroElementElectric  key 0x8a0c  category Logic  size 0x3a4  vtable 0xb24150
// Other owners: CKS08HeroElementFear (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3cb878  CKS08HeroElementElectric_Delete  (C++ delete: DOTD_DECLARE_FACTORIES)
//   [ ] 0x3cb8c8  CKS08HeroElementElectric_ResetFields_maybe  [dead]
//   [x] 0x3cb918  CKS08HeroElementElectric_UpdateArcEndpoints
//   [ ] 0x3cb9e0  FUN_003cb9e0  [dead]
//   [x] 0x3cbb00  CKS08HeroElementElectric_UpdateSphereVisual_maybe
//   [ ] 0x3cbd28  CKS08HeroElementElectric_UpdateChargeLevel_maybe  [dead]
//   [x] 0x3cbe10  CKS08HeroElementElectric_RecursiveRegistration
//   [x] 0x3cbe38  CKS08HeroElementElectric_Destroy
//   [x] 0x3cbe60  CKS08HeroElementElectric_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3cbf00  CKS08HeroElementElectric_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x3cbf90  RegisterCKS08HeroElementElectricClass
//   [ ] 0x3cc018  _GLOBAL__D_3cc018
//   [ ] 0x3cc028  _GLOBAL__I_3cc028
//   [x] 0x3cc038  CKS08HeroElementElectric_Create  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3cc070  CKS08HeroElementElectric_UpdateArcFxFade_maybe
//   [x] 0x3cc330  CKS08HeroElementElectric_Update_maybe
//   [x] 0x3cc560  CKS08HeroElementElectric_PostLoad
//   [x] 0x3cc5e0  CKS08HeroElementElectric_UpdateRandomArc_maybe
//   [x] 0x3cc8d0  CKS08HeroElementElectric_TryCast_maybe
//   [x] 0x3ccb08  CKS08HeroElementElectric_UpdateRepeatCast_maybe
//   [x] 0x3ccda8  CKS08HeroElementElectric_Load
//   [ ] 0x3cd868  CKS08HeroElementElectric_Save
//   [x] 0x3ce3f8  CKS08HeroElementElectric_SpawnFx_2_maybe
//   [x] 0x3ce6b8  CKS08HeroElementElectric_SetArcFxActive_maybe
//   [x] 0x3cebd8  CKS08HeroElementElectric_vf80
//   [x] 0x3cebe0  CKS08HeroElementElectric_vf6C
//   [x] 0x3cec70  CKS08HeroElementElectric_SpawnFx_maybe
//   [x] 0x3cef30  CKS08HeroElementElectric_SetSparkFxActive_maybe
//   [x] 0x3cfd20  CKS08HeroElementElectric_vf7C
//   [x] 0x3cfd90  CKS08HeroElementElectric_vf68
//   [x] 0x3cfef0  CKS08HeroElementFear_Delete  (C++ delete: DOTD_DECLARE_FACTORIES(CKS08HeroElementFear))
//   [ ] 0x3cff40  KStub_Nop_3cff40  [dead]
//
//   [x] 0x9c0410  CKS08HeroElementElectric_IsKindOfClass  (CKS08HeroElementElectric.h)
//   [x] 0x9c0448  CKS08HeroElementElectric_GetClassType  (DOTD_CLASS_KEY)
//   [x] 0x9c0450  CKS08HeroElementElectric_GetClassID  (DOTD_CLASS_KEY)
//   [x] 0x9c0458  CKS08HeroElementElectric_vf138  (CKS08HeroElementElectric.h Vf138)
//   [x] 0x9c0460  CKS08HeroElementElectric_Destructor  (~CKS08HeroElementElectric)
//   [x] 0x9c0480  CKS08HeroElementElectric_DeletingDestructor  (~CKS08HeroElementElectric)
#include "Spyro2008/logic/CKS08HeroElementElectric.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/hooks/IKHkEnemy.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKElectricArcNodeFx.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/fx/CKSparkNodeFx.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvFx.h"

namespace {

CKS08GameManager* GameManager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }  // TOC +0x3e08 -> +0x8c

// 0x00010690 Math_Sqrtf
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }

// 0x00011500 Rand_Int's low 16 bits as a float (rldicl 0x30 / fcfid / frsp).
float RandDraw() { return static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu); }

constexpr float kRandMax = 65535.0f;            // TOC +0x3e18 (0x477fff00)
constexpr float kUnitDraw = -3.05180438e-05f;   // TOC +0x3e50 (0xb8000080): 1 + draw x this = 1 .. -1

// The inlined geometry alpha walk (as CKS08HeroElementEarth.cpp's / CKBeamBreath's SetMeshAlpha).
void SetMeshAlpha(CNode* node, uint8_t alpha) {
    for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
        uint32_t blend = 0;
        uint8_t value = 0xff;
        if (alpha != 0xff) {
            blend = 1;
            value = alpha;
            if ((geometry->m_BitProperties & 0x1000u) != 0) {
                const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
                if (mode != 0 && mode <= 6) {
                    blend = 0;
                    value = 0xff;
                }
            }
        }
        geometry->m_cGeometryColor[3] = value;
        const uint32_t bits = geometry->m_BitProperties;
        if (((bits >> 11) & 1u) != blend) {
            geometry->m_BitProperties = (bits & 0xfffff7ffu) | (blend << 11);
            geometry->UpdateProperties();  // vt+0x60
        }
    }
}

// The explosion spawn of SpawnFx / SpawnFx2 (and CKS08HeroElementEarth's): the inlined CKSrvFx::AcquireFx, the effect
// put at the hero's position, triggered and let go.
void SpawnExplosionAtHero(CKS08HeroElement* element, IKSerializable* data) {
    if (element->GetHero() == nullptr) return;  // vt+0x134
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // +0x60
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx->AcquireFx(static_cast<IKFxData*>(data), element));
    if (explosion == nullptr) return;
    explosion->SetTranslation(reinterpret_cast<const CVector3*>(element->m_pHero->GetPositionPtr()), element);  // 0x00361968, 0x001b66e8
    explosion->Trigger(element, nullptr);    // 0x001b82a8 (r5 / r6 0)
    explosion->ReleaseReservation(element);  // vt+0x54
}

CKElectricArcNodeFx* Arc(IKFx* fx) { return static_cast<CKElectricArcNodeFx*>(fx); }

void StopAndDrop(IKFx*& fx, const IKSerializable* owner) {
    if (fx == nullptr) return;
    fx->StopAndRelease(owner);  // vt+0x58
    fx = nullptr;
}

void StopSpark(IKFx*& fx, const IKSerializable* owner) {
    if (fx == nullptr) return;
    StopOwnedSparkEffect(reinterpret_cast<CKSparkNodeFx*>(fx), owner);  // 0x001d4698
    fx->ReleaseReservation(owner);                                    // vt+0x54
    fx = nullptr;
}

}  // namespace

// 0x003cbe38 CKS08HeroElementElectric_Destroy (vt+0x10)
void CKS08HeroElementElectric::Destroy() { CKS08HeroElement::Destroy(); }  // 0x00371580

// 0x003cbe10 CKS08HeroElementElectric_RecursiveRegistration (vt+0x24)
void CKS08HeroElementElectric::RecursiveRegistration(int32_t type) { CKS08HeroElement::RecursiveRegistration(type); }  // 0x00371578

// 0x003ccda8 CKS08HeroElementElectric_Load (vt+0x2c): the base's, then (level data only) the three level arrays
// interleaved, the presses per step, six references, three floats, two references, the sphere alphas, its divisor and
// flag, two references and side B's duration and reaches.
int32_t CKS08HeroElementElectric::Load(IKFile* file, int32_t type) {
    CKS08HeroElement::Load(file, type);  // 0x00372158
    if (type != 0) return 1;
    for (int32_t i = 0; i < 4; ++i) {
        ReadF32LE(file, &m_unk2cc[i]);
        ReadS32LE(file, &m_unk2dc[i]);
        ReadS32LE(file, &m_unk2ec[i]);
    }
    ReadS32LE(file, &m_unk30c);
    IKFile_ReadRef(file, &m_unk338);
    IKFile_ReadRef(file, &m_unk33c);
    for (int32_t i = 0; i < 4; ++i) IKFile_ReadRef(file, &m_apUnk340[i]);
    ReadF32LE(file, &m_unk310);
    ReadF32LE(file, &m_unk314);
    ReadF32LE(file, &m_unk32c);
    IKFile_ReadRef(file, &m_unk364);
    IKFile_ReadRef(file, &m_unk368);
    for (int32_t i = 0; i < 4; ++i) ReadS32LE(file, &m_unk2fc[i]);
    ReadF32LE(file, &m_unk330);
    ReadU8(file, &m_unk334);
    IKFile_ReadRef(file, &m_unk380);
    IKFile_ReadRef(file, &m_unk384);
    ReadF32LE(file, &m_unk390);
    for (int32_t i = 0; i < 4; ++i) ReadF32LE(file, &m_unk394[i]);
    return 1;
}

// 0x003cc560 CKS08HeroElementElectric_PostLoad (vt+0x30): the base's, the runtime cleared, the shots' hot spot 1.
int32_t CKS08HeroElementElectric::PostLoad(int32_t type) {
    CKS08HeroElement::PostLoad(type);  // 0x003715d8
    m_unk374 = 0;
    m_unk37c = 0;
    m_unk378 = 0;
    m_unk80 = 1;
    m_unk328 = 0.0f;  // stw 0
    m_unk38c = nullptr;
    m_apUnk350[0] = nullptr;
    m_apUnk350[1] = nullptr;
    m_apUnk350[2] = nullptr;
    m_apUnk350[3] = nullptr;
    m_unk360 = nullptr;
    m_unk36c = nullptr;
    m_unk370 = nullptr;
    m_unk388 = nullptr;
    return 1;
}

// 0x003cfd90 CKS08HeroElementElectric_vf68 (vt+0x68). The arcs are dropped without being let go (as the original).
void CKS08HeroElementElectric::StartRepeatFire(int8_t level) {
    const uint8_t index = static_cast<uint8_t>(level);
    if (GetHero() == nullptr) return;  // vt+0x134
    m_unk2b8 = 0.5f / (static_cast<float>(m_unk2dc[index]) + 1.0f);  // TOC +0x3e10, +0x3e0c
    if (m_unk374 == 0) {
        m_apUnk350[3] = nullptr;
        m_unk378 = 0;
        m_unk37c = 0;
        m_apUnk350[0] = nullptr;
        m_apUnk350[1] = nullptr;
        m_apUnk350[2] = nullptr;
        if (m_unk334 != 0 && m_unk360 != nullptr) {  // BUG(original) guard (CKS08HeroElementElectric.h)
            m_unk360->m_sgProperties = m_unk360->m_sgProperties & 0xfffffffbu;  // shown
        }
        m_unk318[3] = -1.0f;  // TOC +0x3e28
        m_unk318[0] = -1.0f;
        m_unk318[1] = -1.0f;
        m_unk318[2] = -1.0f;
        SpawnFx();             // 0x003cec70
        SetSparkFxActive(1);   // 0x003cef30
    }
    m_unk374 = 1;
    m_unk2bc = m_unk2dc[index];
    m_unk328 = 0.5f / (static_cast<float>(m_unk2dc[index]) + 1.0f);
}

// 0x003cebe0 CKS08HeroElementElectric_vf6C (vt+0x6c)
void CKS08HeroElementElectric::StartBeam(float /*speed*/, int8_t level) {
    if (GetHero() == nullptr) return;  // vt+0x134
    m_unk328 = 0.0f;  // stw 0
    m_unk2c0 = 0.0f;  // stw 0
    SetArcFxActive(static_cast<uint8_t>(level), 1);  // 0x003ce6b8
    m_pHero->ValidateOrAcquireTarget();              // 0x0032a580 (the thunk of 0x002ff978)
}

// 0x003ccb08 CKS08HeroElementElectric_UpdateRepeatCast_maybe (vt+0x74)
void CKS08HeroElementElectric::UpdateRepeatFire(float dt, int8_t level) {
    const uint8_t index = static_cast<uint8_t>(level);
    if (GetHero() == nullptr) return;  // vt+0x134
    m_unk2b8 = m_unk2b8 - dt;
    m_unk328 = dt + m_unk328;
    CKS08GameManager* manager = GameManager();
    CKHkS08Hero* hero = m_pHero;
    const uint8_t player = hero->m_ui8Hero == hero->m_ui8TrackedLeader ? hero->m_ui8Leader : 0xff;  // 0x00362ac8
    if (manager->IsActionPressed(5, player) != 0) {  // vt+0x160
        const int32_t charge = m_unk37c;
        const int32_t presses = m_unk378 + 1;
        m_unk378 = presses;
        if (m_unk2ec[index] > charge && m_unk30c == presses) {  // cmpw ble / bne
            m_unk37c = charge + 1;
            m_unk378 = 0;
        }
    }
    if (m_unk2b8 < 0.0f && m_unk2bc > 0) {  // blt (TOC +0x3e4c), ble
        TryCast(dt, index);  // 0x003cc8d0
        m_unk2bc = m_unk2bc - 1;
        m_unk2b8 = 1.0f / (static_cast<float>(m_unk2dc[index]) + 1.0f);  // TOC +0x3e0c
    }
    const float t0 = m_unk318[0] - dt;
    const float t1 = m_unk318[1] - dt;
    const float t2 = m_unk318[2] - dt;
    const float t3 = m_unk318[3] - dt;
    m_unk318[0] = t0;
    m_unk318[1] = t1;
    m_unk318[2] = t2;
    m_unk318[3] = t3;
    UpdateRandomArc(m_apUnk350[0], index, &m_unk318[0]);  // 0x003cc5e0
    UpdateRandomArc(m_apUnk350[1], index, &m_unk318[1]);
    UpdateRandomArc(m_apUnk350[2], index, &m_unk318[2]);
    UpdateRandomArc(m_apUnk350[3], index, &m_unk318[3]);
    if (m_unk334 != 0) UpdateSphereVisual(dt, index);  // 0x003cbb00
}

// 0x003cc330 CKS08HeroElementElectric_Update_maybe (vt+0x78). The level comes in r5 as in the base's.
int32_t CKS08HeroElementElectric::UpdateChannel(float dt, float /*speed*/, float /*scale*/, uint8_t level) {
    if (GetHero() == nullptr) return 1;  // vt+0x134
    if (m_pHero->GetGrabTarget() == nullptr) {  // 0x00329df8
        if (m_unk328 > m_unk390) return 1;      // ble (NaN: goes on)
    }
    m_unk328 = m_unk328 + dt;
    CKS08GameManager* manager = GameManager();
    const uint32_t mana = manager->GetDragonMana(m_ui8Dragon);  // 0x004fd7c8
    const float owed = m_unk2c0;
    if (static_cast<uint32_t>(ppc::fctidz(owed)) >= mana) {  // fctidz, cmplw bge
        OnOutOfMana();  // vt+0x60
        return 1;
    }
    const float total = ppc::fmadds(dt, static_cast<float>(m_unk19c[level]), owed);
    m_unk2c0 = total;
    if (total >= 1.0f) {  // TOC +0x3e0c; cror gt|eq (NaN: kept)
        manager->ConsumeDragonMana(m_ui8Dragon, static_cast<uint32_t>(ppc::fctidz(total)));  // 0x004fd808
        const float now = m_unk2c0;
        const uint32_t whole = static_cast<uint32_t>(ppc::fctidz(now));
        m_unk2c0 = now - static_cast<float>(static_cast<double>(static_cast<uint64_t>(whole)));
    }
    UpdateArcEndpoints();          // 0x003cb918
    UpdateArcFxFade(dt, level);    // 0x003cc070
    return 0;
}

// 0x003cfd20 CKS08HeroElementElectric_vf7C (vt+0x7c)
void CKS08HeroElementElectric::Vf7C() {
    m_unk374 = 0;
    if (m_unk334 != 0 && m_unk360 != nullptr) {  // BUG(original) guard (CKS08HeroElementElectric.h)
        m_unk360->m_sgProperties = (m_unk360->m_sgProperties & 0xfffffffbu) | 4u;  // hidden
    }
    SetSparkFxActive(0);  // 0x003cef30
    SpawnFx2();           // 0x003ce3f8
}

// 0x003cebd8 CKS08HeroElementElectric_vf80 (vt+0x80)
void CKS08HeroElementElectric::StopBeam(uint8_t level) { SetArcFxActive(level, 0); }  // 0x003ce6b8

// 0x003cb918 CKS08HeroElementElectric_UpdateArcEndpoints
void CKS08HeroElementElectric::UpdateArcEndpoints() {
    CVector3 from;
    static_cast<CSGHotSpot*>(m_pHero->GetHotSpot(0x14))->GetWorldPosition(&from);  // 0x00361b70, 0x000ce790
    CVector3 to;
    static_cast<CSGHotSpot*>(m_pHero->GetHotSpot(0x15))->GetWorldPosition(&to);
    if (m_unk388 == nullptr) return;
    Arc(m_unk388)->SetStartPoint(&from, this);  // 0x001b1f80
    Arc(m_unk388)->SetEndPoint(&to, this);      // 0x001b1f40
}

// 0x003cbb00 CKS08HeroElementElectric_UpdateSphereVisual_maybe. The cast's progress: down from 1 over the first half of
// the cast's interval, then up again.
void CKS08HeroElementElectric::UpdateSphereVisual(float /*dt*/, uint8_t level) {
    const float interval = 1.0f / (static_cast<float>(m_unk2dc[level]) + 1.0f);  // TOC +0x3e0c
    const float half = interval * 0.5f;                                          // TOC +0x3e10
    const float t = m_unk328;
    float progress;
    if (t > half) {  // ble takes the other branch (NaN too)
        progress = ppc::fmadds(interval, -0.5f, t) / half;  // TOC +0x3e14
    } else {
        progress = (half - t) / half;
    }
    const float spread = m_unk32c + 1.0f;
    const float size = m_unk2cc[level] / m_unk330;
    const float draw = RandDraw();  // 0x00011500
    const float scale = size * ppc::fmadds((draw / kRandMax) * -2.0f, m_unk32c, spread);  // TOC +0x3e1c
    CNode* sphere = m_unk360;
    if (sphere == nullptr) return;  // BUG(original) guard (CKS08HeroElementElectric.h)
    sphere->SetIdentity();                    // 0x000d08f0
    sphere->ScaleXYZ(scale, scale, scale);    // 0x000d0d28
    if (sphere->m_lGeometryList == nullptr) return;
    SetMeshAlpha(sphere, static_cast<uint8_t>(ppc::fctiwz(progress * static_cast<float>(m_unk2fc[level]))));
}

// 0x003cc070 CKS08HeroElementElectric_UpdateArcFxFade_maybe
void CKS08HeroElementElectric::UpdateArcFxFade(float dt, uint8_t level) {
    CVector3 start;
    static_cast<CSGHotSpot*>(m_pHero->GetHotSpot(1))->GetWorldPosition(&start);  // 0x00361b70, 0x000ce790
    // BUG(original): with a grabbed enemy beyond +0x394[level] the end point is not written (a stack slot as it was);
    // natively it starts at 0.
    CVector3 end = {0.0f, 0.0f, 0.0f};
    if (m_pHero->GetGrabTarget() != nullptr) {  // 0x00329df8
        const CVector3& target = static_cast<IKHkEnemy*>(m_pHero->GetGrabTarget())->m_v3Position;  // +0x134
        const float dx = start.x - target.x;
        const float dy = start.y - target.y;
        const float dz = start.z - target.z;
        const float distance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // 0x00010690
        if (m_unk394[level] > distance) {  // bgt
            const CVector3& grabbed = static_cast<IKHkEnemy*>(m_pHero->GetGrabTarget())->m_v3Position;
            end.x = grabbed.x;
            end.y = grabbed.y;
            end.z = grabbed.z;
            end.y = end.y + 0.0f;  // TOC +0x3e4c
        }
    } else {
        const CVector3 aim = m_pHero->GetAimDirection();  // 0x0032a708
        const float reach = m_unk394[level];
        end.z = reach * aim.z;
        end.x = reach * aim.x;
        end.y = reach * aim.y;
        const float* position = m_pHero->GetPositionPtr();  // 0x00361968
        end.x = end.x + position[0];
        end.y = end.y + position[1];
        end.z = end.z + position[2];
    }
    const float elapsed = m_unk328 - dt;
    const float half = m_unk390 * 0.5f;  // TOC +0x3e10
    float startAlpha;
    float endAlpha;
    if (elapsed <= half) {  // cror eq|lt
        startAlpha = 1.0f;  // TOC +0x3e0c
        endAlpha = elapsed / half;
    } else if (!(elapsed <= m_unk390) || m_pHero->GetGrabTarget() != nullptr) {
        startAlpha = 1.0f;
        endAlpha = 1.0f;
    } else {
        const float duration = m_unk390;
        const float halfDuration = duration * 0.5f;
        endAlpha = 1.0f;
        startAlpha = (duration - elapsed) / halfDuration;
    }
    if (m_unk38c == nullptr) return;
    Arc(m_unk38c)->SetStartPoint(&start, this);  // 0x001b1f80
    Arc(m_unk38c)->SetEndPoint(&end, this);      // 0x001b1f40
    const uint8_t startByte = static_cast<uint8_t>(ppc::fctiwz(startAlpha * 254.0f));  // TOC +0x3e48
    const uint8_t endByte = static_cast<uint8_t>(ppc::fctiwz(endAlpha * 254.0f));
    Arc(m_unk38c)->SetStartAlpha(startByte, this);  // 0x001b1f18
    Arc(m_unk38c)->SetEndAlpha(endByte, this);      // 0x001b1ef0
}

// 0x003cc5e0 CKS08HeroElementElectric_UpdateRandomArc_maybe. Four Rand_Int draws after the timer's (the last one even
// without an arc).
void CKS08HeroElementElectric::UpdateRandomArc(IKFx* arc, uint8_t level, float* timer) {
    const float zero = 0.0f;  // TOC +0x3e4c
    if (*timer > zero) return;  // ble (NaN: redrawn)
    const float period = m_unk310 + m_unk314;
    const float draw = RandDraw();  // 0x00011500
    *timer = ppc::fmadds((draw / kRandMax) * -2.0f, m_unk314, period);  // TOC +0x3e1c
    if (GetHero() == nullptr) return;  // vt+0x134
    CVector3 spot;
    static_cast<CSGHotSpot*>(m_pHero->GetHotSpot(m_unk80))->GetWorldPosition(&spot);  // 0x00361b70, 0x000ce790
    float x = ppc::fmadds(RandDraw(), kUnitDraw, 1.0f);
    float y = ppc::fmadds(RandDraw(), kUnitDraw, 1.0f);
    float z = ppc::fmadds(RandDraw(), kUnitDraw, 1.0f);
    const float length = Sqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));  // 0x00010690
    if (length != zero) {  // beq (NaN: scaled)
        const float inverse = 1.0f / length;
        z = z * inverse;
        x = x * inverse;
        y = y * inverse;
    }
    const float reach = m_unk2cc[level];
    float dx = reach * x;
    float dz = reach * z;
    CVector3 from;
    from.y = ppc::fmadds(reach, y, spot.y);
    from.x = dx + spot.x;
    from.z = dz + spot.z;
    const float* target = m_pHero->GetTargetingPositionPtr();  // 0x00363c78
    const float tz = target[2];
    const float tx = target[0];
    const float ty = target[1];
    float dy = zero;
    const float flat = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, zero)));
    if (flat != zero) {  // beq (NaN: scaled)
        const float inverse = 1.0f / flat;
        dz = dz * inverse;
        dx = dx * inverse;
        dy = inverse * zero;
    }
    const float reach2 = m_unk2cc[level];
    const float push = RandDraw();  // 0x00011500
    if (arc == nullptr) return;
    const float distance = reach2 * ((push / kRandMax) + 1.5f);  // TOC +0x3e54
    CVector3 to;
    to.x = ppc::fmadds(distance, dx, tx);
    to.z = ppc::fmadds(distance, dz, tz);
    to.y = ppc::fmadds(distance, dy, ty);
    Arc(arc)->SetStartPoint(&from, this);  // 0x001b1f80
    Arc(arc)->SetEndPoint(&to, this);      // 0x001b1f40
}

// 0x003cc8d0 CKS08HeroElementElectric_TryCast_maybe. The original also measures each active enemy's distance to the
// hot spot and drops it.
void CKS08HeroElementElectric::TryCast(float /*dt*/, uint8_t level) {
    CKS08GameManager* manager = GameManager();
    if (GetHero() == nullptr) return;  // vt+0x134
    const uint32_t cost = m_unk60[static_cast<int8_t>(level)];
    if (manager->GetDragonMana(m_ui8Dragon) < cost) {  // 0x004fd7c8; cmplw blt
        OnOutOfMana();  // vt+0x60
        return;
    }
    manager->ConsumeDragonMana(m_ui8Dragon, cost);  // 0x004fd808
    CVector3 spot;
    static_cast<CSGHotSpot*>(m_pHero->GetHotSpot(m_unk80))->GetWorldPosition(&spot);  // 0x00361b70, 0x000ce790
    IKGrpEnemy* enemies = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // +0x8c -> +0x04
    if (enemies != nullptr) {
        m_pDamageA->m_fDamage = static_cast<float>(m_unk10[level]) + static_cast<float>(m_unk37c);
        const uint32_t count = enemies->m_ui32NbActiveEnemies;  // +0x120
        for (uint32_t i = 0; i < count; ++i) {
            IKSerializable* enemy = enemies->m_apActiveEnemies[i];  // +0x58
            const RwFrame* frame = static_cast<CSGMovable*>(static_cast<IKHook*>(enemy)->m_pKGLObject)->m_pRwFrame;
            const float dy = frame->ltm.pos.y - spot.y;
            const float dx = frame->ltm.pos.x - spot.x;
            const float dz = frame->ltm.pos.z - spot.z;
            (void)Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // 0x00010690, unused
        }
    }
    m_unk328 = 0.0f;  // stw 0
}

// 0x003cec70 CKS08HeroElementElectric_SpawnFx_maybe
void CKS08HeroElementElectric::SpawnFx() { SpawnExplosionAtHero(this, m_unk338); }

// 0x003ce3f8 CKS08HeroElementElectric_SpawnFx_2_maybe
void CKS08HeroElementElectric::SpawnFx2() { SpawnExplosionAtHero(this, m_unk33c); }

// 0x003ce6b8 CKS08HeroElementElectric_SetArcFxActive_maybe. The pooled lookups are the inlined CKSrvFx::AcquireFx.
void CKS08HeroElementElectric::SetArcFxActive(uint8_t /*level*/, uint8_t on) {
    if (GetHero() == nullptr) return;  // vt+0x134
    if (on == 0) {
        StopAndDrop(m_unk388, this);
        StopAndDrop(m_unk38c, this);
        return;
    }
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // +0x60
    m_unk388 = fx->AcquireFx(static_cast<IKFxData*>(m_unk380), this);
    m_unk38c = fx->AcquireFx(static_cast<IKFxData*>(m_unk384), this);
    if (m_unk38c == nullptr) return;
    Arc(m_unk38c)->SetStartAlpha(0, this);  // 0x001b1f18
    Arc(m_unk38c)->SetEndAlpha(0, this);    // 0x001b1ef0
}

// 0x003cef30 CKS08HeroElementElectric_SetSparkFxActive_maybe. The pooled lookups are the inlined CKSrvFx::AcquireFx.
void CKS08HeroElementElectric::SetSparkFxActive(uint8_t on) {
    if (GetHero() == nullptr) return;  // vt+0x134
    if (on == 0) {
        StopAndDrop(m_apUnk350[0], this);
        StopAndDrop(m_apUnk350[1], this);
        StopAndDrop(m_apUnk350[2], this);
        StopAndDrop(m_apUnk350[3], this);
        StopSpark(m_unk36c, this);
        StopSpark(m_unk370, this);
        return;
    }
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // +0x60
    m_apUnk350[0] = fx->AcquireFx(static_cast<IKFxData*>(m_apUnk340[0]), this);
    m_apUnk350[1] = fx->AcquireFx(static_cast<IKFxData*>(m_apUnk340[1]), this);
    m_apUnk350[2] = fx->AcquireFx(static_cast<IKFxData*>(m_apUnk340[2]), this);
    m_apUnk350[3] = fx->AcquireFx(static_cast<IKFxData*>(m_apUnk340[3]), this);
    CKSparkFxData* first = static_cast<CKSparkFxData*>(m_unk364);
    CKSparkFxData* second = static_cast<CKSparkFxData*>(m_unk368);
    if (m_ui8Dragon == 0) {
        first->m_unk10 = m_pHero->GetHotSpot(0x12);  // 0x00361b70
        first->m_unk0c = nullptr;
        second->m_unk10 = m_pHero->GetHotSpot(0x12);
        second->m_unk0c = nullptr;
    } else {
        first->m_unk10 = m_pHero->GetHotSpot(0x12);
        first->m_unk0c = nullptr;
        second->m_unk10 = m_pHero->GetHotSpot(0x12);
        second->m_unk0c = nullptr;
    }
    m_unk36c = fx->AcquireFx(first, this);
    m_unk370 = fx->AcquireFx(second, this);
}
