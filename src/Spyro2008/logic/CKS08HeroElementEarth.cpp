// CKS08HeroElementEarth.cpp - C2.8 port-final F08 (class in CKS08HeroElementEarth.h).
//
// Reconstructed original translation unit: 0x3c9f90-0x3cb878 (GAME_TOC1, main_toc1), 19 functions, 18 live.
// Primary class: CKS08HeroElementEarth  key 0x89cc  category Logic  size 0x328  vtable 0xb24008
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3c9f90  CKS08HeroElementEarth_Delete  (C++ delete: DOTD_DECLARE_FACTORIES)
//   [ ] 0x3c9fe0  CKS08HeroElementEarth_ResetFields_maybe  [dead]
//   [x] 0x3ca028  CKS08HeroElementEarth_SpawnFx_maybe
//   [x] 0x3ca2e8  CKS08HeroElementEarth_vf68
//   [x] 0x3ca468  CKS08HeroElementEarth_RecursiveRegistration
//   [x] 0x3ca490  CKS08HeroElementEarth_Destroy
//   [x] 0x3ca4b8  CKS08HeroElementEarth_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3ca558  CKS08HeroElementEarth_Create  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x3ca590  RegisterCKS08HeroElementEarthClass
//   [ ] 0x3ca618  _GLOBAL__D_3ca618
//   [ ] 0x3ca628  _GLOBAL__I_3ca628
//   [x] 0x3ca638  CKS08HeroElementEarth_vf88
//   [x] 0x3ca670  CKS08HeroElementEarth_vf7C
//   [x] 0x3ca6f8  CKS08HeroElementEarth_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3ca788  CKS08HeroElementEarth_PostLoad
//   [x] 0x3ca800  CKS08HeroElementEarth_UpdateNodeAlphaFade_maybe
//   [x] 0x3cacf8  CKS08HeroElementEarth_vf74
//   [x] 0x3cade8  CKS08HeroElementEarth_Load
//   [ ] 0x3cb360  CKS08HeroElementEarth_Save
//
//   [x] 0x9c0350  CKS08HeroElementEarth_IsKindOfClass  (CKS08HeroElementEarth.h)
//   [x] 0x9c0388  CKS08HeroElementEarth_GetClassType  (DOTD_CLASS_KEY)
//   [x] 0x9c0390  CKS08HeroElementEarth_GetClassID  (DOTD_CLASS_KEY)
//   [x] 0x9c0398  CKS08HeroElementEarth_vf84  (CKS08HeroElementEarth.h Vf84)
//   [x] 0x9c03a0  CKS08HeroElementEarth_vf138  (CKS08HeroElementEarth.h Vf138)
//   [x] 0x9c03a8  CKS08HeroElementEarth_DeletingDestructor  (~CKS08HeroElementEarth)
//   [x] 0x9c03f0  CKS08HeroElementEarth_Destructor  (~CKS08HeroElementEarth)
#include "Spyro2008/logic/CKS08HeroElementEarth.h"

#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/ppc_ops.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/services/CKSrvFx.h"

namespace {

// The inlined geometry alpha walk (as CKBeamBreath's SetMeshAlpha): every geometry of the mesh takes `alpha` (colour
// byte +0x23) and the "alpha blended" property bit 11 (vt+0x60 UpdateProperties when it changes); 0xff clears the bit,
// and a geometry with property bit 12 and a material of mode 1..6 keeps 0xff without blending.
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

// An alpha word as a float (rldicl / std / lfd / fcfid / frsp: unsigned).
float AlphaToFloat(uint32_t alpha) { return static_cast<float>(static_cast<double>(alpha)); }

// The faded alpha: fctiwz of (`to` x t / T + `from` x (T - t) / T) (fmadds), its low byte (stfiwx / lbz +3).
uint8_t FadeAlpha(uint32_t to, uint32_t from, float t, float duration) {
    const float rest = (duration - t) / duration;
    const float done = t / duration;
    return static_cast<uint8_t>(ppc::fctiwz(ppc::fmadds(AlphaToFloat(to), done, AlphaToFloat(from) * rest)));
}

// BUG(original) guard (CKS08HeroElementEarth.h): a null mesh reads as one without geometry.
bool HasGeometry(const CNode* node) { return node != nullptr && node->m_lGeometryList != nullptr; }

void HideNode(CNode* node) {
    if (node == nullptr) return;  // BUG(original) guard: the original writes through the null mesh
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
}

}  // namespace

// 0x003ca490 CKS08HeroElementEarth_Destroy (vt+0x10)
void CKS08HeroElementEarth::Destroy() { CKS08HeroElement::Destroy(); }  // 0x00371580

// 0x003ca468 CKS08HeroElementEarth_RecursiveRegistration (vt+0x24)
void CKS08HeroElementEarth::RecursiveRegistration(int32_t type) { CKS08HeroElement::RecursiveRegistration(type); }  // 0x00371578

// 0x003cade8 CKS08HeroElementEarth_Load (vt+0x2c): the base's, then (level data only) two references, eleven words,
// one more word and two more references.
int32_t CKS08HeroElementEarth::Load(IKFile* file, int32_t type) {
    CKS08HeroElement::Load(file, type);  // 0x00372158
    if (type != 0) return 1;
    IKFile_ReadRef(file, &m_unk300);
    IKFile_ReadRef(file, &m_unk304);
    ReadU32LE(file, &m_unk2cc);
    ReadU32LE(file, &m_unk2d0);
    ReadU32LE(file, &m_unk2d4);
    ReadU32LE(file, &m_unk2d8);
    ReadU32LE(file, &m_unk2dc);
    ReadU32LE(file, &m_unk2e0);
    ReadU32LE(file, &m_unk2e4);
    ReadU32LE(file, &m_unk2e8);
    ReadU32LE(file, &m_unk2ec);
    ReadF32LE(file, &m_unk2f0);
    ReadF32LE(file, &m_unk2f4);
    ReadU32LE(file, &m_unk310);
    IKFile_ReadRef(file, &m_unk308);
    IKFile_ReadRef(file, &m_unk2f8);
    return 1;
}

// 0x003ca788 CKS08HeroElementEarth_PostLoad (vt+0x30): the base's, the runtime cleared, the shots' hot spot 5.
int32_t CKS08HeroElementEarth::PostLoad(int32_t type) {
    CKS08HeroElement::PostLoad(type);  // 0x003715d8
    m_unk2fc = 0;
    m_unk31c = 0;
    m_unk320 = 0;
    m_unk31a = 0;
    m_unk318 = 0;
    m_unk319 = 0;
    m_unk80 = 5;
    m_unk324 = m_unk2e4;
    m_unk314 = 0.0f;  // stw 0
    m_unk30c = nullptr;
    return 1;
}

// 0x003ca2e8 CKS08HeroElementEarth_vf68 (vt+0x68)
void CKS08HeroElementEarth::StartRepeatFire(int8_t /*level*/) {
    if (GetHero() == nullptr) return;  // vt+0x134
    if (m_unk318 == 0) {
        m_unk319 = 0;
        m_unk31c = 0;
        m_unk320 = 0;
        m_unk324 = m_unk2e4;
        CNode* node = m_unk30c;
        if (node != nullptr) {  // BUG(original) guard (CKS08HeroElementEarth.h)
            node->m_sgProperties = node->m_sgProperties & 0xfffffffbu;  // shown
            SetMeshAlpha(node, static_cast<uint8_t>(m_unk2e8));      // lbz +0x2eb: the word's low byte
        }
        m_unk314 = 0.0f;  // stw 0
        SpawnFx();        // 0x003ca028
    }
    m_unk318 = 1;
}

// 0x003cacf8 CKS08HeroElementEarth_vf74 (vt+0x74)
void CKS08HeroElementEarth::UpdateRepeatFire(float dt, int8_t /*level*/) {
    if (GetHero() == nullptr) return;  // vt+0x134
    const float t = dt + m_unk314;
    m_unk314 = t;
    if (m_unk31a != 0 && m_unk2f4 <= t) {  // cror eq|lt (NaN: the fade)
        m_unk31a = 0;
        HideNode(m_unk30c);
        return;
    }
    UpdateNodeAlphaFade();  // 0x003ca800
}

// 0x003ca670 CKS08HeroElementEarth_vf7C (vt+0x7c)
void CKS08HeroElementEarth::Vf7C() {
    CNode* node = m_unk30c;
    m_unk319 = 0;
    m_unk318 = 0;
    CGeometry* geometry = HasGeometry(node) ? static_cast<CGeometry*>(node->m_lGeometryList) : nullptr;
    m_unk324 = geometry != nullptr ? geometry->m_cGeometryColor[3] : m_unk2e4;
    m_unk314 = 0.0f;  // TOC +0x3dc0
    if (m_unk2f4 != 0.0f) {  // beq (NaN: fades out)
        m_unk31a = 1;
        return;
    }
    m_unk31a = 0;
    HideNode(node);
}

// 0x003ca638 CKS08HeroElementEarth_vf88 (vt+0x88)
void CKS08HeroElementEarth::Vf88() {
    m_unk31a = 0;
    if (m_unk30c == nullptr) return;
    m_unk30c->m_sgProperties = (m_unk30c->m_sgProperties & 0xfffffffbu) | 4u;
}

// 0x003ca028 CKS08HeroElementEarth_SpawnFx_maybe. The pooled lookup is the inlined CKSrvFx::AcquireFx.
void CKS08HeroElementEarth::SpawnFx() {
    if (GetHero() == nullptr) return;  // vt+0x134
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // TOC +0x3d94 -> +0x60
    CKExplosionNodeFx* explosion =
        static_cast<CKExplosionNodeFx*>(fx->AcquireFx(static_cast<IKFxData*>(m_unk300), this));
    if (explosion == nullptr) return;
    explosion->SetTranslation(reinterpret_cast<const CVector3*>(m_pHero->GetPositionPtr()), this);  // 0x00361968, 0x001b66e8
    explosion->Trigger(this, nullptr);    // 0x001b82a8 (r5 / r6 0)
    explosion->ReleaseReservation(this);  // vt+0x54
}

// 0x003ca800 CKS08HeroElementEarth_UpdateNodeAlphaFade_maybe. Active: the fade in (before +0x2f0), then the final alpha
// once (+0x319); not active and not faded in: the fade out over +0x2f4.
void CKS08HeroElementEarth::UpdateNodeAlphaFade() {
    const float t = m_unk314;
    if (t < m_unk2f0) {  // bge takes the second branch (NaN too)
        if (m_unk318 != 0) {
            if (!HasGeometry(m_unk30c)) return;
            SetMeshAlpha(m_unk30c, FadeAlpha(m_unk2e4, m_unk2e8, t, m_unk2f0));
            return;  // still active
        }
        if (m_unk319 != 0) return;
    } else {
        if (m_unk319 != 0) return;
        if (m_unk318 != 0) {
            if (HasGeometry(m_unk30c)) SetMeshAlpha(m_unk30c, static_cast<uint8_t>(ppc::fctiwz(AlphaToFloat(m_unk2e4))));
            m_unk319 = 1;
            return;  // still active
        }
    }
    if (!HasGeometry(m_unk30c)) return;
    SetMeshAlpha(m_unk30c, FadeAlpha(m_unk2ec, m_unk324, m_unk314, m_unk2f4));
}
