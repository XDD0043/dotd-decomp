// CKProjectileElement.cpp - reconstructed original translation unit 0x3bc818-0x3c1f38 (GAME_TOC1, main_toc1), 29 functions, 28 live.
// Primary class: CKProjectileElement  key 0x934c  category Logic  size 0x214  vtable 0xb23dd8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3bc818  CKProjectileElement_Delete
//   [x] 0x3bc868  CKProjectileElement_Construct
//   [ ] 0x3bc878  CKProjectileElement_Construct_2  [dead]
//   [x] 0x3bc888  CKProjectileElement_GetAbilityId
//   [x] 0x3bc890  CKProjectileElement_GetFamilyId
//   [x] 0x3bc898  CKProjectileElement_Start
//   [x] 0x3bca10  CKProjectileElement_Stop
//   [x] 0x3bca60  CKProjectileElement_End
//   [x] 0x3bcb48  CKProjectileElement_ApplyHeroControl
//   [x] 0x3bd1b0  CKProjectileElement_ResetRuntime
//   [x] 0x3bd1f8  CKProjectileElement_SetAimControl_maybe
//   [x] 0x3bd598  CKProjectileElement_ApplyDamageParams
//   [x] 0x3bdbe8  CKProjectileElement_DeleteArray
//   [x] 0x3bdc88  CKProjectileElement_StartEmitterFx
//   [ ] 0x3bdf50  RegisterCKProjectileElementClass
//   [ ] 0x3bdfd8  _GLOBAL__D_3bdfd8
//   [ ] 0x3bdfe8  _GLOBAL__I_3bdfe8
//   [x] 0x3bdff8  CKProjectileElement_GetLaunchPosDir_maybe
//   [x] 0x3be178  CKProjectileElement_Update
//   [x] 0x3bf1b8  CKProjectileElement_CreateArray
//   [x] 0x3bf248  CKProjectileElement_Create
//   [x] 0x3bf280  CKProjectileElement_PostLoad
//   [x] 0x3bf2c8  CKProjectileElement_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x3bf2d0  CKProjectileElement_Destroy  (empty)
//   [x] 0x3bf2d8  CKProjectileElement_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3bf2f8  CKProjectileElement_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3bf318  CKProjectileElement_DeletingDestructor  (the destructor; delete)
//   [x] 0x3bf360  CKProjectileElement_Load
//   [ ] 0x3c0a98  CKProjectileElement_Save
//
//   [x] 0x9bff30  CKProjectileElement_UpdateCharge  [inline]
//   [ ] 0x9c0158  CKProjectileElement_GetClassType  [inline]
//   [ ] 0x9c0160  CKProjectileElement_GetClassID  [inline]
//   [x] 0x9c0168  CKProjectileElement_Fire  [inline]
//   [x] 0x9c0170  CKProjectileElement_IsChargeDisabled_maybe  [inline]
//   [ ] 0x9c0178  CKProjectileElement_IsKindOfClass  [inline]
#include "k2000/logic/CKProjectileElement.h"

#include <cstring>

#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "crt/ppc_ops.h"
#include "k2000/misc/ClassRegistry.h"

#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

// 0x003bf360 CKProjectileElement_Load: level data only (type 0 = K_LEVEL_PLATEFORMS; any other type reads
// nothing). Three levels of per-level parameters (a 3-iteration loop), then the shared settings and three
// object references. 482 bytes.
int32_t CKProjectileElement::Load(IKFile* file, int32_t type) {
    if (type != 0) return 1;
    for (int32_t i = 0; i < 3; ++i) {
        ReadS32LE(file, &m_unk08[i]);
        ReadF32LE(file, &m_unk38[i]);
        ReadS32LE(file, &m_unk50[i]);
        ReadF32LE(file, &m_unk68[i]);
        ReadF32LE(file, &m_unk88[i]);
        ReadF32LE(file, &m_unka0[i]);
        ReadU32LE(file, &m_unkb8[i]);
        ReadF32LE(file, &m_unkd0[i]);
        ReadU32LE(file, &m_unke8[i]);
        ReadU32LE(file, &m_unk100[i]);
        ReadF32LE(file, &m_unk118[i]);
        ReadU32LE(file, &m_unk130[i]);
        ReadU32LE(file, &m_unk148[i]);
        ReadU8(file, &m_unk178[i]);
        ReadU8(file, &m_unk17e[i]);
        ReadS32LE(file, &m_unk14[i]);
        ReadS32LE(file, &m_unk5c[i]);
        ReadF32LE(file, &m_unk94[i]);
        ReadF32LE(file, &m_unkac[i]);
        ReadU32LE(file, &m_unkc4[i]);
        ReadU32LE(file, &m_unkdc[i]);
        ReadU32LE(file, &m_unkf4[i]);
        ReadU32LE(file, &m_unk10c[i]);
        ReadF32LE(file, &m_unk124[i]);
        ReadU32LE(file, &m_unk13c[i]);
        ReadU32LE(file, &m_unk154[i]);
        ReadU8(file, &m_unk17b[i]);
        ReadU8(file, &m_unk181[i]);
    }
    ReadU8(file, &m_unk194);
    ReadU8(file, &m_unk195);
    ReadU8(file, &m_unk196);
    ReadF32LE(file, &m_unk198);
    ReadF32LE(file, &m_unk19c);
    ReadF32LE(file, &m_unk1ac);
    ReadU8(file, &m_unk1a0);
    ReadU8(file, &m_unk1a1);
    ReadU8(file, &m_unk1a2);
    ReadF32LE(file, &m_unk1a4);
    ReadF32LE(file, &m_unk1a8);
    ReadF32LE(file, &m_unk1b0);
    ReadF32LE(file, &m_unk74);
    ReadU8(file, &m_unk1d8);
    ReadU8(file, &m_unk1d9);
    ReadU8(file, &m_unk1db);
    ReadU8(file, &m_unk1dc);
    ReadF32LE(file, &m_unk1e0);
    ReadF32LE(file, &m_unk1e4);
    ReadU8(file, &m_unk1b4);
    ReadU8(file, &m_unk1b5);
    ReadF32LE(file, &m_unk1b8);
    ReadF32LE(file, &m_unk1bc);
    ReadU32LE(file, &m_unk160);
    ReadU32LE(file, &m_unk16c);
    ReadU32LE(file, &m_unk164);
    ReadU32LE(file, &m_unk170);
    ReadU32LE(file, &m_unk168);
    ReadU32LE(file, &m_unk174);
    IKFile_ReadRef(file, &m_unk20c);
    ReadU8(file, &m_unk1c0);
    ReadU8(file, &m_unk1c1);
    ReadU8(file, &m_unk1c2);
    ReadF32LE(file, &m_unk1c4);
    ReadF32LE(file, &m_unk1c8);
    ReadF32LE(file, &m_unk1cc);
    ReadU8(file, &m_unk1d0);
    ReadF32LE(file, &m_unk1d4);
    ReadU8(file, &m_unk1da);
    ReadU8(file, &m_unk1dd);
    ReadF32LE(file, &m_unk1e8);
    IKFile_ReadRef(file, &m_unk184);
    ReadU32LEWords(file, m_unk188, 3);
    ReadF32LE(file, &m_unk44[0]);
    ReadF32LE(file, &m_unk44[1]);
    ReadF32LE(file, &m_unk44[2]);
    IKFile_ReadRef(file, &m_unk1ec);
    ReadF32LE(file, &m_unk20);
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk30);
    ReadF32LE(file, &m_unk28);
    ReadF32LE(file, &m_unk34);
    ReadU32LE(file, &m_unk78);
    ReadU32LE(file, &m_unk80);
    ReadU32LE(file, &m_unk7c);
    ReadU32LE(file, &m_unk84);
    return 1;
}

namespace {
float GameClockNow() { return g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[0]; }  // TOC +0x3b8c -> +0x48 -> +0x04 -> +0x04
}  // namespace

// 0x003bc898 CKProjectileElement_Start
void CKProjectileElement::Start(CKS08AbilityHostBase* host) {
    if (m_bRunning != 0 || host == nullptr) return;
    m_unk200 = 0.0f;
    m_unk1fc = 0.0f;
    m_unk210 = 0;
    m_pHost = host;
    m_unk1f5 = 0;
    m_unk1f6 = 0;
    m_unk1f7 = 0;
    m_unk1f8 = 0;
    m_unk1fa = 0;
    m_bRunning = 1;
    m_unk04 = host->GetAbilityLevelIndex(this);  // vt+0xf4
    ApplyHeroControl(1);                          // vt+0x68
    if (m_pHost->PlayAbilityAnim(this, 0) != 0) {  // vt+0x7c
        m_unk1f5 = 1;
    } else if (m_pHost->PlayAbilityAnim(this, 1) != 0) {
        m_unk1f6 = 1;
    }
    m_fStartTime = GameClockNow();
}

// 0x003bca60 CKProjectileElement_End
void CKProjectileElement::End(int32_t forced) {
    ApplyHeroControl(0);  // vt+0x68
    m_bRunning = 0;
    const float cooldown = forced != 0 ? m_unk44[m_unk04] : m_unk38[m_unk04];
    m_pHost->SetAbilityCooldown(cooldown, this, static_cast<uint8_t>(forced ^ 1));  // vt+0x9c
    m_pHost = nullptr;
}

// 0x003bcb48 CKProjectileElement_ApplyHeroControl. The gates of +0x68 (SetAbilityParam11f8): a context's own byte when its
// permission 0 byte (+0x195 / +0x1a1 / +0x1c1) is clear.
void CKProjectileElement::ApplyHeroControl(uint8_t on) {
    CKS08AbilityHostBase* host = m_pHost;
    if (on != 0) {
        host->SetHeroActionPermission(0, m_unk195, m_unk1a1, m_unk1c1);  // vt+0x44
        host->SetHeroActionPermission(1, m_unk194, m_unk1a0, m_unk1c0);
        host->SetHeroActionPermission(3, 0, 1, 1);
        host->SetHeroActionPermission(4, 1, 1, 1);
        host->SetHeroActionPermission(5, 0, 0, 0);
        host->SetHeroActionPermission(6, 1, 1, 1);
        host->SetHeroActionPermission(8, 1, 1, 1);
        host->SetAbilityTurnParams(m_unk198, m_unk19c, m_unk1a4, m_unk1a8, m_unk1c4, m_unk1c8, m_unk196, m_unk1a2,
                                   m_unk1c2);  // vt+0x64
        const uint8_t gateAir = m_unk195 == 0 ? static_cast<uint8_t>(m_unk1b4 != 0) : 0;
        const uint8_t gateFly = m_unk1a1 == 0 ? static_cast<uint8_t>(m_unk1b5 != 0) : 0;
        const uint8_t gateGround = m_unk1c1 == 0 ? static_cast<uint8_t>(m_unk1d0 != 0) : 0;
        host->SetAbilityParam11f8(m_unk1b8, m_unk1bc, m_unk1d4, gateAir, gateFly, gateGround);  // vt+0x68
        host->SetAbilityMoveSpeed(m_unk1ac, m_unk1b0, m_unk1cc);                               // vt+0x50
        host->SetAbilityMoveSpeedEnabled(1);                                                   // vt+0x54
        const uint8_t grounded = static_cast<uint8_t>(host->IsAirborne() ^ 1);                 // vt+0x30
        m_unk1f9 = grounded;
        host->SetAbilityHeroMode(this, grounded);  // vt+0x70
        return;
    }
    host->SetHeroActionPermission(0, 0, 0, 0);
    host->SetHeroActionPermission(1, 0, 0, 0);
    host->SetHeroActionPermission(3, 0, 0, 0);
    host->SetHeroActionPermission(4, 0, 0, 0);
    host->SetHeroActionPermission(5, 0, 0, 0);
    host->SetHeroActionPermission(6, 0, 0, 0);
    host->SetHeroActionPermission(8, 0, 0, 0);
    host->SetHeroActionPermission(9, 0, 0, 0);
    host->SetAbilityTurnParams(m_unk198, m_unk19c, m_unk1a4, m_unk1a8, m_unk1c4, m_unk1c8, 0, 0, 0);
    host->SetAbilityParam11f8(m_unk1b8, m_unk1bc, m_unk1d4, 0, 0, 0);
    host->SetAbilityMoveSpeedEnabled(0);
    host->SetAbilityHeroMode(this, 0);
}

// 0x003bd1b0 CKProjectileElement_ResetRuntime
void CKProjectileElement::ResetRuntime(int32_t /*type*/) {
    m_fStartTime = -1.0f;  // 0xbf800000
    m_unk1fa = 0;
    m_unk1fc = m_unk74;
    m_unk200 = 0.0f;
    m_unk209 = 0xff;
    m_pHost = nullptr;
    m_unk04 = 0;
    m_bRunning = 0;
    m_unk1f5 = 0;
    m_unk1f7 = 0;
    m_unk1f8 = 0;
    m_unk208 = 0xff;
}

// 0x003bd1f8 CKProjectileElement_SetAimControl_maybe
void CKProjectileElement::SetAimControl(uint8_t on) {
    CKS08AbilityHostBase* host = m_pHost;
    if (on != 0) {
        host->SetHero1d11(1);                        // vt+0x88
        host->SetHeroActionPermission(0, 0, 0, 0);   // vt+0x44
        host->SetHeroActionPermission(1, 0, 0, 0);
        host->SetAbilityMoveSpeedEnabled(0);         // vt+0x54
        const uint8_t gateAir = m_unk1d8 != 0 ? static_cast<uint8_t>(m_unk1db != 0) : 0;
        const uint8_t gateFly = m_unk1d9 != 0 ? static_cast<uint8_t>(m_unk1dc != 0) : 0;
        const uint8_t gateGround = m_unk1da != 0 ? static_cast<uint8_t>(m_unk1dd != 0) : 0;
        host->SetAbilityParam11f8(m_unk1e0, m_unk1e4, m_unk1e8, gateAir, gateFly, gateGround);  // vt+0x68
        return;
    }
    host->SetHero1d11(0);
    host->SetHeroActionPermission(0, m_unk195, m_unk1a1, m_unk1c1);
    host->SetHeroActionPermission(1, m_unk194, m_unk1a0, m_unk1c0);
    host->SetAbilityMoveSpeedEnabled(1);
    const uint8_t gateAir = m_unk195 == 0 ? static_cast<uint8_t>(m_unk1b4 != 0) : 0;
    const uint8_t gateFly = m_unk1a1 == 0 ? static_cast<uint8_t>(m_unk1b5 != 0) : 0;
    const uint8_t gateGround = m_unk1c1 == 0 ? static_cast<uint8_t>(m_unk1d0 != 0) : 0;
    m_pHost->SetAbilityParam11f8(m_unk1b8, m_unk1bc, m_unk1d4, gateAir, gateFly, gateGround);
}

// 0x003bdc88 CKProjectileElement_StartEmitterFx: the inlined pooled lookup (CKSrvFx::AcquireFx) of the explosion data's
// effect, owned by this element.
namespace {
// A word of the level data that holds a float (the arrays that are zero in every sample are typed uint32_t).
float WordF32(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof(value));
    return value;
}
// 0x00a70a58: the damage type of each ability id (21 words; the projectile base's id 22 reads the zero after them).
const uint32_t kAbilityDamageTypes[26] = {0, 0, 1, 1, 2, 2, 3, 3, 8, 8, 4, 4, 5, 5, 5, 6, 9, 7, 7, 9, 6, 0, 0, 0, 0, 0};
}  // namespace

// 0x003bd598 CKProjectileElement_ApplyDamageParams. The level data's [6] arrays are the normal values of the three
// levels followed by the charged ones (the members here: a normal and a charged array of 3 each); the charged ones
// when the charge time +0x200 reached the level's full charge time +0x68 (cror gt|eq; a NaN: normal).
void CKProjectileElement::ApplyDamageParams(uint8_t continuous) {
    const float damageScale = m_pHost->GetDamageScale();  // vt+0xc0
    const float effectScale = m_pHost->GetEffectScale();  // vt+0xc4
    const uint32_t level = m_unk04;
    const bool charged = m_unk200 >= m_unk68[level];
    CKS08ElementDamage* damage = static_cast<CKS08ElementDamage*>(m_unk20c);
    const float knockN[3] = {m_unk20, m_unk24, m_unk28};
    const float knockC[3] = {m_unk2c, m_unk30, m_unk34};
    const uint32_t value3N[3] = {m_unk160, m_unk164, m_unk168};
    const uint32_t value3C[3] = {m_unk16c, m_unk170, m_unk174};
    const int32_t amount = charged ? m_unk14[level] : m_unk08[level];
    damage->SetAmount(damageScale * static_cast<float>(static_cast<double>(amount)));  // vt+0x50
    damage->SetStun(charged ? m_unkac[level] : m_unka0[level]);                       // vt+0x5c
    damage->SetStunDuration(charged ? m_unk94[level] : m_unk88[level]);               // vt+0x60
    auto element = [&](uint32_t normal, uint32_t chargedValue) {
        return effectScale * WordF32(charged ? chargedValue : normal);
    };
    damage->SetElementValue(element(m_unkb8[level], m_unkc4[level]), 0);  // vt+0x58
    damage->SetElementValue(effectScale * (charged ? WordF32(m_unkdc[level]) : m_unkd0[level]), 1);
    damage->SetElementValue(element(m_unke8[level], m_unkf4[level]), 2);
    damage->SetElementValue(effectScale * (charged ? m_unk124[level] : m_unk118[level]), 6);
    damage->SetElementValue(element(m_unk100[level], m_unk10c[level]), 4);
    damage->SetElementValue(element(m_unk148[level], m_unk154[level]), 7);
    damage->SetElementValue(element(value3N[level], value3C[level]), 3);
    damage->SetElementValue(effectScale * WordF32(m_unk130[level]), 5);  // no charged value
    damage->SetUnk34(charged ? m_unk17b[level] : m_unk178[level]);       // vt+0x6c
    damage->SetUnk35(charged ? m_unk181[level] : m_unk17e[level]);       // vt+0x70
    damage->SetDamageType(kAbilityDamageTypes[GetAbilityId() & 0xffu]);  // vt+0x64; TOC +0x3ba4 0x00a70a58
    damage->SetAbilityId(GetAbilityId());                                 // vt+0x68
    damage->SetContinuous(continuous);                                    // vt+0x54
    damage->m_unk26 = 1;
    damage->m_unk10 = (charged ? knockC[level] : knockN[level]) / 0.2f;  // TOC +0x3ba8
    damage->m_unk14 = 0.2f;
    // The knock angle (+0x18, radians): the normal shot reads +0x80 and +0x78 (spread +0x80), the charged one +0x7c
    // and +0x84 (spread +0x84).
    float base;
    float spread;
    if (!charged) {
        base = WordF32(m_unk80) + WordF32(m_unk78);
        spread = WordF32(m_unk80);
    } else {
        base = WordF32(m_unk7c) + WordF32(m_unk84);
        spread = WordF32(m_unk84);
    }
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
    const float t = static_cast<float>(static_cast<double>(r)) / 65535.0f * -2.0f;  // TOC +0x3bac / +0x3bb0
    const float angle = ppc::fmadds(t, spread, base) * 0x1.1df468p-6f;            // TOC +0x3bb4 (0x3c8efa34)
    std::memcpy(&damage->m_unk18, &angle, sizeof(angle));
}

void CKProjectileElement::StartEmitterFx() {
    IKFxData* data = reinterpret_cast<IKFxData*>(m_unk1ec);
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    if (fxService->m_ui32EltNb == 0) return;
    CKExplosionNodeFx* fx = static_cast<CKExplosionNodeFx*>(fxService->AcquireFx(data, this));
    if (fx == nullptr) return;
    const CVector3 position = m_pHost->GetHotspotPosition(m_unk208);  // vt+0xd0
    fx->SetTranslation(&position, this);  // 0x001b66e8
    fx->Trigger(this, 0);                 // 0x001b82a8
    fx->ReleaseReservation(this);         // vt+0x54
}

// 0x003bdff8 CKProjectileElement_GetLaunchPosDir_maybe: the hot spot's world matrix (host vt+0xcc, hot spot +0x208,
// CSGHotSpot_GetWorldMatrix 0x000ce970); its position moved along its at, up and right rows (in this order) by the
// element's launch offset +0x188 plus `offset`. The result is accumulated in place (each step a fused multiply-add).
// BUG(original): the matrix is the stack's when the hot spot has no node (zeros here).
CVector3 CKProjectileElement::GetLaunchPosDir(const CVector3* offset) {
    CMatrix34 matrix = {};
    static_cast<CSGHotSpot*>(m_pHost->GetHotspot(m_unk208))->GetWorldMatrix(&matrix);
    const float ox = WordF32(m_unk188[0]);
    const float oy = WordF32(m_unk188[1]);
    const float oz = WordF32(m_unk188[2]);
    CVector3 out = matrix.m_pos;
    const float along = oz + offset->z;
    out.x = ppc::fmadds(along, matrix.m_at.x, out.x);
    out.y = ppc::fmadds(along, matrix.m_at.y, out.y);
    out.z = ppc::fmadds(along, matrix.m_at.z, out.z);
    const float up = oy + offset->y;
    out.x = ppc::fmadds(up, matrix.m_up.x, out.x);
    out.y = ppc::fmadds(up, matrix.m_up.y, out.y);
    out.z = ppc::fmadds(up, matrix.m_up.z, out.z);
    const float right = ox + offset->x;
    out.x = ppc::fmadds(right, matrix.m_right.x, out.x);
    out.y = ppc::fmadds(right, matrix.m_right.y, out.y);
    out.z = ppc::fmadds(right, matrix.m_right.z, out.z);
    return out;
}

// 0x003be178 CKProjectileElement_Update. The phases: +0x1f5 the start animation (0), +0x1f6 the charge animation (1),
// +0x1f7 aiming (3), +0x1f8 the end animation (4). The mana cost (the full charge's past the level's charge time) is
// scaled (host vt+0xc8) and compared unsigned with the mana (vt+0xbc; -1 infinite): too much, the fizzle
// (StartEmitterFx) and the end; else a ground probe under the hot spot (0.25 lower): ground (status 0) launches (Fire)
// and spends the mana. All float tests are the original's ordered ones (cror: false on a NaN).
uint8_t CKProjectileElement::Update(float dt) {
    if (m_bRunning == 0) return 0;
    if (m_fStartTime == GameClockNow()) return 1;
    float held = 0.0f;
    if (m_unk1f8 != 0) {
        if (m_pHost->IsAbilityAnimPhaseDone(this, 4) == 0) return 1;  // vt+0x80
        End(m_unk210);
        return 0;
    }
    m_unk1fc = m_unk1fc + dt;
    if (m_pHost->IsAbilityButtonReleased(m_unk209) != 0 && m_unk1fa == 0) m_unk1fc = 0.0f;  // vt+0x90
    if (m_pHost->GetAbilityButtonHoldTime(m_unk209, &held) != 0 && IsChargeDisabled() == 0 && m_unk1fa == 0) {  // vt+0x94
        m_unk200 = dt + m_unk200;
    }

    if (m_unk1f5 != 0) {
        // The start animation.
        if (m_pHost->IsAbilityAnimPhaseDone(this, 0) == 0) return 1;
        if (m_pHost->GetAbilityButtonHoldTime(m_unk209, &held) == 0 || IsChargeDisabled() != 0) {
            m_pHost->PlayAbilityAnim(this, 1);
            m_unk1f6 = 1;
            m_unk1f5 = 0;
            return 1;
        }
        if (m_pHost->SelectByMovementContext(m_unk1d8, m_unk1da, m_unk1d9) != 0) {  // vt+0x3c
            SetAimControl(1);
        } else if (m_pHost->PlayAbilityAnim(this, 3) == 0) {
            m_pHost->PlayAbilityAnim(this, 1);
            m_unk1f6 = 1;
            m_unk1f5 = 0;
            return 1;
        }
        m_unk200 = 0.0f;
        m_unk1f7 = 1;
        m_unk1f5 = 0;
        return 1;
    }

    if (m_unk1f7 != 0) {
        // Aiming: the hero control follows the airborne state.
        if (m_unk1f9 != 0) {
            if (m_pHost->IsAirborne() != 0) {
                m_unk1f9 = 0;
                ApplyHeroControl(1);
                SetAimControl(1);
            }
        } else if (m_pHost->IsAirborne() == 0) {
            m_unk1f9 = 1;
            ApplyHeroControl(1);
            SetAimControl(1);
        }
        UpdateCharge(dt);  // vt+0x6c
        if (m_pHost->SelectByMovementContext(m_unk1d8, m_unk1da, m_unk1d9) != 0) {
            if (m_pHost->GetAbilityButtonHoldTime(m_unk209, &held) != 0) return 1;
            SetAimControl(0);
            m_pHost->PlayAbilityAnim(this, 1);
            m_unk1fa = 1;
            m_unk1f7 = 0;
            m_unk1f6 = 1;
            return 1;
        }
        if (m_pHost->IsAbilityAnimPhaseDone(this, 3) == 0) {
            if (m_pHost->GetAbilityButtonHoldTime(m_unk209, &held) != 0) return 1;
            m_pHost->PlayAbilityAnim(this, 1);
            m_unk1f6 = 1;
            m_unk1f7 = 0;
            return 1;
        }
        m_pHost->PlayAbilityAnim(this, 1);
        m_unk1f7 = 0;
        m_unk1f6 = 1;
        m_unk200 = m_unk68[m_unk04];
        return 1;
    }

    // The tap window: the press is still short (0 <= +0x1fc <= +0x74).
    const auto inTapWindow = [this]() { return m_unk74 >= m_unk1fc && m_unk1fc >= 0.0f; };
    bool checkMana = false;  // 0x3be8d0: the mana of a short charge (+0x50)
    bool release = false;    // 0x3be6a0: the release (the cost by the charge time, the probe)
    if (m_unk1f6 != 0 && m_pHost->IsProjectileChargeHeld(this) != 0) {  // vt+0x100
        if (m_pHost->GetAbilityButtonHoldTime(m_unk209, &held) != 0 && held >= 0.12f && IsChargeDisabled() == 0 &&
            m_unk1fa == 0) {
            if (m_pHost->SelectByMovementContext(m_unk1d8, m_unk1da, m_unk1d9) != 0) {
                SetAimControl(1);
                m_unk200 = 0.0f;
                m_unk1f7 = 1;
                m_unk1f5 = 0;
                return 1;
            }
            if (m_pHost->PlayAbilityAnim(this, 3) != 0) {
                m_unk200 = 0.0f;
                m_unk1f7 = 1;
                m_unk1f5 = 0;
                return 1;
            }
        }
        release = true;
    } else {
        bool settled = true;  // 0x3be884
        if (m_pHost->IsAbilityAnimPhaseDone(this, 1) != 0) {
            if (m_pHost->GetAbilityButtonHoldTime(m_unk209, &held) != 0) {
                if (IsChargeDisabled() == 0 && m_pHost->PlayAbilityAnim(this, 3) != 0) {
                    m_unk200 = 0.0f;
                    m_unk1f7 = 1;
                    m_unk1f6 = 0;
                    return 1;
                }
            } else if (!inTapWindow()) {
                settled = false;  // 0x3beac4: the end animation
            }
        }
        if (settled) {
            if (m_unk1f6 == 0) return 0;
            const bool wasGrounded = m_unk1f9 != 0;
            const uint8_t airborne = m_pHost->IsAirborne();
            if (wasGrounded && airborne != 0) {
                // Took off: the control again; outside the tap window and released, the end animation.
                m_unk1f9 = 0;
                ApplyHeroControl(1);
                if (inTapWindow() || m_pHost->GetAbilityButtonHoldTime(m_unk209, &held) != 0) {
                    m_pHost->PlayAbilityAnim(this, 1);
                    checkMana = true;
                } else {
                    settled = false;
                }
            } else if (!wasGrounded && airborne == 0) {
                // Landed.
                m_unk1f9 = 1;
                ApplyHeroControl(1);
                if (inTapWindow() || m_pHost->GetAbilityButtonHoldTime(m_unk209, &held) != 0) {
                    m_pHost->PlayAbilityAnim(this, 1);
                    checkMana = true;
                } else {
                    settled = false;
                }
            } else {
                checkMana = true;
            }
        }
        if (!settled) {
            // 0x3beac4
            if (m_pHost->PlayAbilityAnim(this, 4) != 0) {
                m_unk1f6 = 0;
                m_unk1f8 = 1;
                return 1;
            }
            End(0);
            return 0;
        }
    }

    if (checkMana) {
        const float scale = m_pHost->GetManaCostScale();  // vt+0xc8
        const uint32_t cost = static_cast<uint32_t>(static_cast<int64_t>(scale * static_cast<float>(m_unk50[m_unk04])));
        if (cost <= static_cast<uint32_t>(m_pHost->GetAbilityMana())) return 1;  // vt+0xbc
    } else if (release) {
        const uint32_t level = m_unk04;
        const uint32_t base = static_cast<uint32_t>(m_unk200 >= m_unk68[level] ? m_unk5c[level] : m_unk50[level]);
        const float scale = m_pHost->GetManaCostScale();
        const uint32_t cost = static_cast<uint32_t>(static_cast<int64_t>(static_cast<float>(base) * scale));
        if (!(cost > static_cast<uint32_t>(m_pHost->GetAbilityMana()))) {
            CGroundContactDatasIn in;
            in.m_fObjectHeight = 0.5f;  // TOC +0x3bdc
            in.m_fDeltaMax = 0.0f;
            CGroundContactDatasInOut contact;
            CVector3 point = m_pHost->GetHotspotPosition(m_unk208);  // vt+0xd0
            point.y = point.y - 0.25f;                                // TOC +0x3be0
            static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&in, &contact, &point.x, 1);
            if (contact.m_eContactStatus == 0) {
                if (Fire() != 0) {  // vt+0x78
                    m_pHost->ConsumeAbilityMana(this, cost);  // vt+0xb8
                    m_unk1fa = 0;
                    m_unk1fc = m_unk74;
                    m_unk200 = 0.0f;
                    return 1;
                }
            }
            if (m_pHost->PlayAbilityAnim(this, 4) != 0) {
                m_unk1f6 = 0;
                m_unk1f8 = 1;
                return 1;
            }
            End(0);
            return 0;
        }
    }

    // 0x3be960: not enough mana, the fizzle.
    StartEmitterFx();  // vt+0x80
    m_unk210 = 1;
    if (m_pHost->PlayAbilityAnim(this, 4) != 0) {
        m_unk1f8 = 1;
        return 1;
    }
    End(m_unk210);
    return 0;
}
