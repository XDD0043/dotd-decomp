// Reconstructed original translation unit: 0x30aa78-0x30cb30 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x30aa78  CKHkS08Hero_AnimState10_LocomotionGround
//   [x] 0x30aec0  CKHkS08Hero_ShowArmorPieceMesh_maybe
//   [x] 0x30b0b8  CKHkS08Hero_ClearArmorBonusFlags_maybe
//   [x] 0x30b0d0  CKHkS08Hero_GetAbilityDamageScale  (inline in its caller: CKS08HeroAbilityHost::GetDamageScale)
//   [x] 0x30b0f0  CKHkS08Hero_GetAbilityEffectScale  (inline in its caller: CKS08HeroAbilityHost::GetEffectScale)
//   [x] 0x30b110  CKHkS08Hero_GetAbilityManaCostScale  (inline in its caller: CKS08HeroAbilityHost::GetManaCostScale)
//   [ ] 0x30b130  FUN_0030b130  [dead]
//   [ ] 0x30b2f0  FUN_0030b2f0  [dead]
//   [x] 0x30b340  CKHkS08Hero_SetArmorBonusFlags_maybe
//   [x] 0x30b668  StaticInitAndDestruction_30b668  (the two file statics at the end)
//   [ ] 0x30b698  _GLOBAL__D_30b698
//   [ ] 0x30b6a8  _GLOBAL__I_30b6a8
//   [x] 0x30b6b8  CKHkS08Hero_UpdateRegenAndElementTimeout_maybe
//   [x] 0x30c700  CKHkS08Hero_ApplyEquippedArmor_maybe
//   [x] 0x30cab8  CKHkS08Hero_vf138  (CKHkS08Hero.h)
//   [x] 0x30cac0  CKHkS08Hero_GetBoundingSphere1_maybe  (inline in its caller: CKHkS08Hero_2.cpp HandleClimbZoneContact)
//   [x] 0x30cad0  CKHkS08Hero_ActivateAttackSphere
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "Spyro2008/logic/CKS08Damage.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/KBase201.h"
#include "k2000/components/CKBonusData.h"
#include <cmath>

namespace {
// A regeneration accumulator's whole part (fctidz; the low word is passed on) and the accumulator less it (fcfid of the
// 64-bit value, frsp, fsubs).
int64_t TakeWholePart(float& accumulator) {
    const int64_t whole = ppc::fctidz(accumulator);
    accumulator = accumulator - static_cast<float>(static_cast<double>(whole));
    return whole;
}

// One of the regeneration's random periods: `base` + `spread` (fadds) plus spread times -2 times a draw in [0, 1]
// (Rand_Int's low 16 bits over 65535, TOC +0x2184 / +0x2188), fused.
float RandomPeriod(float base, float spread) {
    const float sum = base + spread;
    const uint32_t draw = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
    const float unit = static_cast<float>(static_cast<double>(draw)) / 65535.0f;
    return ppc::fmadds(unit * -2.0f, spread, sum);
}

// The armour mesh entries of the hero's objects (+0x58) the armour code hides: per dragon (0x00a706c0 / 0x00a706f0, TOC
// +0x2128) three groups of four.
const uint32_t kArmorMeshes[2][12] = {{2, 5, 6, 0xb, 3, 7, 8, 0xc, 4, 9, 0xa, 0xd},
                                      {2, 5, 6, 0xb, 3, 7, 8, 0xc, 4, 9, 0xa, 0xd}};

void ShowMesh(IKSerializable* object) {
    if (object != nullptr) static_cast<CSGLeaf*>(object)->m_sgProperties &= 0xfffffffbu;
}
}  // namespace

// 0x0030aec0 CKHkS08Hero_ShowArmorPieceMesh_maybe: the mesh(es) of armour `armor` (0..2; 3 none) in `slot` shown (the
// objects +0x58 [2 + armor] in slot 0, [5 + 2 armor] and the next in slot 1, [0xb + armor] in slot 2).
void CKHkS08Hero::ShowArmorPieceMesh(uint8_t armor, uint8_t slot) {
    if (armor == 3 || armor > 2) return;
    if (slot == 1) {
        ShowMesh(m_apObjects[5 + armor * 2]);
        ShowMesh(m_apObjects[6 + armor * 2]);
    } else if (slot == 0) {
        ShowMesh(m_apObjects[2 + armor]);
    } else if (slot == 2) {
        ShowMesh(m_apObjects[0xb + armor]);
    }
}

// 0x0030b0b8 CKHkS08Hero_ClearArmorBonusFlags_maybe: +0xed0 bits 6..27.
void CKHkS08Hero::ClearArmorBonusFlags() { m_unked0 &= 0xf000003fu; }

// 0x0030b340 CKHkS08Hero_SetArmorBonusFlags_maybe: the +0xed0 bonus bit of armour `armor` in `slot` (Spyro and Cynder
// differ for armour 0); with the whole set (`count` 3) its set bit too, and the bit shared with the partner when the
// partner wears the whole set as well.
void CKHkS08Hero::SetArmorBonusFlags(uint8_t armor, uint8_t slot, int32_t count) {
    if (armor == 3) return;
    uint32_t setBit;
    uint32_t sharedBit;
    if (armor == 1) {
        if (slot == 1) {
            m_unked0 |= 0x80000u;
        } else if (slot == 0) {
            m_unked0 |= 0x2c000u;
        } else if (slot == 2) {
            m_unked0 |= 0x200000u;
        }
        setBit = 0x800000u;
        sharedBit = 0x10000u;
    } else if (armor == 0) {
        if (m_ui8Hero == 0) {
            if (slot == 1) {
                m_unked0 |= 0x200u;
            } else if (slot == 0) {
                m_unked0 |= 0x40u;
            } else if (slot == 2) {
                m_unked0 |= 0x800u;
            }
        } else {
            if (slot == 1) {
                m_unked0 |= 0x400u;
            } else if (slot == 0) {
                m_unked0 |= 0x1000u;
            } else if (slot == 2) {
                m_unked0 |= 0x40u;
            }
        }
        setBit = 0x2000u;
        sharedBit = 0x400000u;
    } else if (armor == 2) {
        if (slot == 1) {
            m_unked0 |= 0x100u;
        } else if (slot == 0) {
            m_unked0 |= 0x1000000u;
        } else if (slot == 2) {
            m_unked0 |= 0x4000000u;
        }
        setBit = 0x8000000u;
        sharedBit = 0x2000000u;
    } else {
        return;
    }
    if (count != 3) return;
    m_unked0 |= setBit;
    if ((GetPartnerHero()->m_unked0 & setBit) != 0) m_unked0 |= sharedBit;  // 0x002f85f8
}

// 0x0030b6b8 CKHkS08Hero_UpdateRegenAndElementTimeout_maybe: the armour bonuses that run every frame (all off without
// armour, as at the start of LVL010): health regeneration (+0xed0 bit 19: +0xe88 per second into +0x1b78, whole points
// restored), mana regeneration (bit 10, no ability running: +0xe8c into +0x1b7c), fury (bit 26 with bit 4 while +0x354
// bit 25: +0xea4 per frame into +0x1b80); the element timeout (+0x1cc4 4 without bit 27 or bit 4: the abilities
// cancelled, the next element +0x1cc8, its HUD); the combo hits' poison / explosion (bit 13), the aura particles and
// explosions (bit 25 with bit 4, the period +0x1b84 drawn around +0xea8 +- +0xeac), the bonus drops (bit 20: chance
// +0xe98 percent) and the bonus thrown at the nearest enemy within +0xec0 (bit 22, the period +0x1b88 drawn around
// +0xeb8 +- +0xebc).
void CKHkS08Hero::UpdateRegenAndElementTimeout() {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x2180 -> +0x8c
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    uint32_t flags = m_unked0;
    if ((flags & 0x80000u) != 0) {
        const uint32_t health = manager->GetDragonHealth(m_ui8Hero);  // 0x004fd9c8
        if (health < manager->GetDragonHealthCapacity(m_ui8Hero)) {   // 0x004fd940
            m_unk1b78 = ppc::fmadds(m_unk88c, m_unke88, m_unk1b78);
            if (m_unk1b78 >= 1.0f) {  // TOC +0x2124; cror gt|eq
                const int64_t whole = ppc::fctidz(m_unk1b78);
                manager->RestoreDragonHealth(m_ui8Hero, static_cast<int32_t>(whole), 1);  // 0x004fdef8
                m_unk1b78 = m_unk1b78 - static_cast<float>(static_cast<double>(whole));
            }
        }
        flags = m_unked0;
    }
    if ((flags & 0x400u) != 0 && m_unk1ac6 == 0 && m_unk1ac5 == 0) {
        const uint32_t mana = manager->GetDragonMana(m_ui8Hero);  // 0x004fd7c8
        if (mana < manager->GetDragonManaCapacity(m_ui8Hero)) {   // 0x004fd740
            m_unk1b7c = ppc::fmadds(m_unk88c, m_unke8c, m_unk1b7c);
            if (m_unk1b7c >= 1.0f) {
                const int64_t whole = ppc::fctidz(m_unk1b7c);
                manager->RestoreDragonMana(m_ui8Hero, static_cast<int32_t>(whole), 1);  // 0x004fdca8
                m_unk1b7c = m_unk1b7c - static_cast<float>(static_cast<double>(whole));
            }
        }
        flags = m_unked0;
    }
    if ((flags & 0x4000000u) != 0 && (m_unk354 & 0x2000000u) != 0 && (flags & 0x10u) != 0) {
        m_unk1b80 = m_unk1b80 + m_unkea4;
        if (m_unk1b80 >= 1.0f) {
            // The whole part (its low word: rldicl 0,32, then fcfid of that word) goes to the fury; the rest stays.
            const uint32_t whole = static_cast<uint32_t>(ppc::fctidz(m_unk1b80));
            manager->AddDragonFury(m_ui8Hero, whole);  // 0x004fd528
            m_unk1b80 = m_unk1b80 - static_cast<float>(static_cast<double>(whole));
            flags = m_unked0;
        }
    }
    if ((flags & 0x8000000u) == 0 && m_unk1cc4 == 4 && (flags & 0x10u) == 0) {
        if (m_unk1ac6 != 0) CancelAbilityB(0);  // 0x003272d8
        if (m_unk1ac5 != 0) CancelAbilityA(0);  // 0x00326ee0
        m_unk1cc4 = m_unk1cc8 == 4 ? (flags & 0x10u) : m_unk1cc8;
        if (m_ui8Hero == 0 || m_ui8Hero == 1) {
        CKS08GameManager* hudManager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
        const uint8_t shown = static_cast<uint8_t>(m_unk1cc4);  // the byte +0x1cc7
        if (m_ui8Hero == 0) hudManager->ShowSpyroSelectedElementHud(shown);    // 0x5039e8
        else hudManager->ShowCynderSelectedElementHud(shown);                 // 0x5024d8
        }
        flags = m_unked0;
    }
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // engine +0x60
    if ((flags & 0x2000u) != 0 && (m_unk354 & 0x2000000u) != 0 && m_unke4 != nullptr) {
        // The combo hit on the touched volume's enemy (+0x24, key 0x26c2, a valid target): Cynder adds +0xe90 to its
        // poison gauge, Spyro sets off an explosion of +0x1b58 at +0xe8 (the inlined CKSrvFx::AcquireFx) dealing +0x1b54
        // as the volume's owner (its owner type, flags 0x2a). No rand.
        if (IsComboKindFlagSet() != 0) {  // 0x002fc1b0
            IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_unke4);
            IKSerializable* enemy = volume->m_pOwner;
            if (enemy != nullptr && enemy->IsKindOfClass(0x26c2) != 0 &&
                static_cast<CKHkS08Enemy*>(enemy)->IsValidCombatTarget() != 0) {  // vt+0x08, 0x00289278
                if (m_ui8Hero == 1) {
                    static_cast<CKHkS08Enemy*>(enemy)->AddPoisonGauge2(m_unke90);  // 0x002890f8
                } else {
                    CKExplosionNodeFx* explosion =
                        static_cast<CKExplosionNodeFx*>(fx->AcquireFx(static_cast<IKFxData*>(m_unk1b58), this));
                    if (explosion != nullptr) {
                        IKBoundingVolume* touched = static_cast<IKBoundingVolume*>(m_unke4);
                        explosion->SetDamageOwner(touched->m_pOwner, this);           // 0x001b6340
                        explosion->SetDamageCategory(touched->m_ui8OwnerType, this);  // 0x001b6318
                        explosion->SetDamageFlags(0x2a, this);                        // 0x001b62f0
                        explosion->SetDamage(m_unk1b54, this);                        // 0x001b62c8
                        explosion->SetTranslation(reinterpret_cast<const CVector3*>(&m_unke8), this);  // 0x001b66e8
                        explosion->Trigger(this, 0);                                  // 0x001b82a8
                        explosion->ReleaseReservation(this);                          // vt+0x54
                    }
                }
            }
        }
        flags = m_unked0;
    }
    if ((flags & 0x2000000u) != 0 && (flags & 0x10u) != 0) {
        if (m_unk1b68 == nullptr) {
            // The aura particles on hot spot 5 (the data +0x1b64's attach owner the null +0x1b68), from the FX pool.
            CKParticlesEffectFxData* aura = static_cast<CKParticlesEffectFxData*>(m_unk1b64);
            aura->m_pAttachOwner = nullptr;
            aura->m_pAttachHotSpot = m_apHotSpots[5];
            m_unk1b68 = fx->AcquireFx(static_cast<CKParticlesEffectFxData*>(m_unk1b64), this);
        }
        if ((group->m_unkf8 & 0x400u) != 0) {
            m_unk1b84 = m_unk1b84 - m_unk88c;
            if (m_unk1b84 <= 0.0f) {  // TOC +0x21a0; cror lt|eq
                // An explosion of +0x1b5c at hot spot 5 along the node's up row, dealing +0x1b60 (its +0x24 set) as the
                // hero's (category 3, flags 0x2a).
                CKExplosionNodeFx* explosion =
                    static_cast<CKExplosionNodeFx*>(fx->AcquireFx(static_cast<IKFxData*>(m_unk1b5c), this));
                if (explosion != nullptr) {
                    CVector3 position;
                    static_cast<CSGHotSpot*>(m_apHotSpots[5])->GetWorldPosition(&position);  // 0x000ce790
                    explosion->SetDamageOwner(this, this);
                    explosion->SetDamageCategory(3, this);
                    explosion->SetDamageFlags(0x2a, this);
                    static_cast<CKS08Damage*>(m_unk1b60)->m_unk24 = 1;
                    explosion->SetDamage(m_unk1b60, this);
                    explosion->SetTranslation(&position, this);
                    const RwV3d& up = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling.up;  // +0x1c -> +0x04 -> +0x20
                    const CVector3 direction{up.x, up.y, up.z};
                    explosion->SetDirection(&direction, this);  // 0x001b5e20
                    explosion->Trigger(this, 0);
                    explosion->ReleaseReservation(this);
                }
                const float first = std::fabs(RandomPeriod(m_unkea8, m_unkeac));  // the sign bit cleared on the stack
                float period = 999.9999f;  // TOC +0x2190 (0x4479ffff)
                if (first >= 1.0e-3f) period = 1.0f / std::fabs(RandomPeriod(m_unkea8, m_unkeac));  // TOC +0x218c
                m_unk1b84 = period;
            }
        }
        flags = m_unked0;
    }
    if (m_unk1b68 != nullptr && ((flags & 0x2000000u) == 0 || (flags & 0x10u) == 0)) {
        StopOwnedParticleEffect(static_cast<IKFx*>(m_unk1b68), this);  // 0x001cdde8
        static_cast<IKFx*>(m_unk1b68)->ReleaseReservation(this);       // vt+0x54
        m_unk1b68 = nullptr;
        flags = m_unked0;
    }
    if ((flags & 0x100000u) != 0 && (m_unk354 & 0x2000000u) != 0) {
        const uint32_t draw = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
        const float chance = m_unke98 / 100.0f;  // TOC +0x2194
        if (!(static_cast<float>(static_cast<double>(draw)) / 65535.0f >= chance)) {  // bge
            const uint32_t which = (static_cast<uint32_t>(Rand_Int()) >> 15) & 1u;
            // The drop table +0x1b6c / +0x1b70 (the draw's bit 15) at +0xe8 along the node's LTM at row, from +0x54c.
            const RwV3d& at = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame)->at;  // +0x1c -> +0x04 -> +0x70
            const CVector3 direction{at.x, at.y, at.z};
            static_cast<KBase201*>(g_pEngine->m_srvBonus)
                ->SpawnBonuses(static_cast<CKBonusData*>(which == 0 ? m_unk1b6c : m_unk1b70),
                               reinterpret_cast<const CVector3*>(&m_unke8), &direction,
                               reinterpret_cast<const CVector3*>(&m_unk54c), 0);  // 0x00126278
        }
        flags = m_unked0;
    }
    if ((flags & 0x400000u) != 0 && (group->m_unkf8 & 0x400u) != 0) {
        m_unk1b88 = m_unk1b88 - m_unk88c;
        if (m_unk1b88 <= 0.0f) {
            const float first = RandomPeriod(m_unkeb8, m_unkebc);
            float period = 999.9999f;
            if (first >= 1.0e-3f) period = 1.0f / RandomPeriod(m_unkeb8, m_unkebc);
            m_unk1b88 = period;
            // The nearest valid enemy of the enemy group (the game manager's +0x04 entry 0) within +0xec0 (and closer than
            // the global 0x00c4acb8 +0x28, FLT_MAX); with one, a Rand_Int draw (its value unused) and a bonus thrown at it.
            IKGrpEnemy* enemies = static_cast<IKGrpEnemy*>(manager->m_unk04[0]);
            const uint32_t count = enemies != nullptr ? enemies->m_ui32NbActiveEnemies : 0u;
            IKSerializable* nearest = nullptr;
            float best = 3.40282347e+38f;  // TOC +0x2198 -> 0x00c4acb8 +0x28
            for (uint32_t i = 0; i < count; ++i) {
                CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(enemies->m_apActiveEnemies[i]);
                if (enemy->IsValidCombatTarget() == 0) continue;  // 0x00289278
                const float dy = enemy->m_v3Position.y - m_unk550;
                const float dx = enemy->m_v3Position.x - m_unk54c;
                const float dz = enemy->m_v3Position.z - m_unk554;
                const float distance =
                    static_cast<float>(std::sqrt(static_cast<double>(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)))));
                if (!(m_unkec0 >= distance)) continue;
                if (!(best > distance)) continue;
                best = distance;
                nearest = enemy;
            }
            if (nearest != nullptr) {
                Rand_Int();  // 0x00011500
                // STUB(C2.9, armour bonuses: LVL010 gives no armour): BonusPool_SpawnBonusObject 0x5b0df8 (TocBridge 0x98f370) of the game manager's
                // bonus pool (+0x8c -> +0x10; kind 1 at the enemy's +0x134, 1) and the bonus's vt+0xe4 (the y axis, the
                // hero): CKGrpBonus is not ported (an armour bonus; LVL010 has no armour).
                DOTD_STUB_ONCE("UpdateRegenAndElementTimeout 0x30b6b8: BonusPool_SpawnBonusObject (C2.9)");
            }
        }
    }
}

// 0x0030c700 CKHkS08Hero_ApplyEquippedArmor_maybe: every armour mesh of the dragon hidden, the bonus flags cleared, then
// per slot the equipped armour's bonus (and its mesh unless the meshes are hidden), the set count growing with each slot
// that wears the same armour as the one before; then the regeneration.
void CKHkS08Hero::ApplyEquippedArmor() {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    const uint32_t* meshes = kArmorMeshes[m_ui8Hero == 0 ? 0 : 1];
    for (uint32_t i = 0; i < 12; ++i) {
        IKSerializable* object = m_apObjects[meshes[i] & 0xffu];
        if (object != nullptr) static_cast<CSGLeaf*>(object)->m_sgProperties |= 4u;
    }
    ClearArmorBonusFlags();  // 0x0030b0b8
    const uint8_t hidden = manager->GetArmorMeshHiddenFlag(m_ui8Hero);  // 0x004fd628
    const uint8_t first = manager->GetEquippedArmor(m_ui8Hero, 0);      // 0x004fd658
    uint8_t second;
    if (hidden == 0) {
        ShowArmorPieceMesh(manager->GetEquippedArmor(m_ui8Hero, 0), 0);  // 0x0030aec0
        SetArmorBonusFlags(first, 0, 1);                                 // 0x0030b340
        second = manager->GetEquippedArmor(m_ui8Hero, 1);
        ShowArmorPieceMesh(manager->GetEquippedArmor(m_ui8Hero, 1), 1);
    } else {
        SetArmorBonusFlags(first, 0, 1);
        second = manager->GetEquippedArmor(m_ui8Hero, 1);
    }
    const int32_t same = first == second ? 1 : 0;
    SetArmorBonusFlags(second, 1, same + 1);
    const uint8_t third = manager->GetEquippedArmor(m_ui8Hero, 2);
    if (hidden == 0) ShowArmorPieceMesh(manager->GetEquippedArmor(m_ui8Hero, 2), 2);
    SetArmorBonusFlags(third, 2, third == second ? same + 2 : 1);
    UpdateRegenAndElementTimeout();  // 0x0030b6b8 (a tail call)
}

// 0x0030aa78 CKHkS08Hero_AnimState10_LocomotionGround: the animation state on foot runs the ground animation
// sub-machine (handlers +0x18d4 through +0x195c, current state +0x1960): entering restarts it in state 0 (standing),
// leaving exits it and clears +0x1838.
uint8_t CKHkS08Hero::AnimLocomotionGround(IKTime* clock, int32_t phase, uint8_t other) {
    const uint32_t* handlers = static_cast<const uint32_t*>(m_unk195c);
    if (phase == 1) {
        const uint8_t previous = m_unk1960;
        if (previous != 0xff) CallStateHandler(&handlers[previous * 2u], clock, 2, 0);
        m_unk1960 = 0;
        CallStateHandler(&handlers[0], clock, 1, previous);
        return other;
    }
    if (phase == 2) {
        if (m_unk1960 != 0xff) CallStateHandler(&handlers[m_unk1960 * 2u], clock, 2, 0xff);
        m_unk1960 = 0xff;
        m_unk1838 = 0;
        return other;
    }
    if (phase == 0) RunState(handlers, m_unk1960, clock);
    return other;
}

// 0x0030cad0 CKHkS08Hero_ActivateAttackSphere
void CKHkS08Hero::ActivateAttackSphere(IKSerializable* volume, int32_t enabled) {
    SetCollisionVolumeEnabled(static_cast<IKBoundingVolume*>(volume), enabled);  // 0x00352f10
    const uint32_t count = m_unk1bac;
    m_unk1bac = count + 1;
    m_apActiveHitSpheres[count] = volume;
}

// 0x0030b668 StaticInitAndDestruction_30b668: two file statics (0x00ceae0c, 0x00ceae10) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceae0c = -1.0f;
[[maybe_unused]] float s_unkceae10 = -1.0f;
}  // namespace
