// Reconstructed original translation unit: 0x30aa78-0x30cb30 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x30aa78  CKHkS08Hero_AnimState10_LocomotionGround
//   [x] 0x30aec0  CKHkS08Hero_ShowArmorPieceMesh_maybe
//   [x] 0x30b0b8  CKHkS08Hero_ClearArmorBonusFlags_maybe
//   [ ] 0x30b0d0  CKHkS08Hero_GetAbilityDamageScale
//   [ ] 0x30b0f0  CKHkS08Hero_GetAbilityEffectScale
//   [ ] 0x30b110  CKHkS08Hero_GetAbilityManaCostScale
//   [ ] 0x30b130  FUN_0030b130  [dead]
//   [ ] 0x30b2f0  FUN_0030b2f0  [dead]
//   [x] 0x30b340  CKHkS08Hero_SetArmorBonusFlags_maybe
//   [ ] 0x30b668  StaticInitAndDestruction_30b668
//   [ ] 0x30b698  _GLOBAL__D_30b698
//   [ ] 0x30b6a8  _GLOBAL__I_30b6a8
//   [x] 0x30b6b8  CKHkS08Hero_UpdateRegenAndElementTimeout_maybe
//   [x] 0x30c700  CKHkS08Hero_ApplyEquippedArmor_maybe
//   [ ] 0x30cab8  CKHkS08Hero_vf138
//   [ ] 0x30cac0  CKHkS08Hero_GetBoundingSphere1_maybe
//   [ ] 0x30cad0  CKHkS08Hero_ActivateAttackSphere
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
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
            // STUB(C2.7: fury): AddDragonFury_maybe 0x4fd528 of the whole part (the accumulator keeps the rest).
            DOTD_STUB_ONCE("AddDragonFury_maybe 0x4fd528 (C2.7)");
            TakeWholePart(m_unk1b80);
            flags = m_unked0;
        }
    }
    if ((flags & 0x8000000u) == 0 && m_unk1cc4 == 4 && (flags & 0x10u) == 0) {
        // STUB(C2.7: abilities): CKHkS08Hero_CancelAbilityB 0x3272d8 (+0x1ac6) / CancelAbilityA 0x326ee0 (+0x1ac5).
        if (m_unk1ac6 != 0) DOTD_STUB_ONCE("CKHkS08Hero_CancelAbilityB 0x3272d8 (C2.7)");
        if (m_unk1ac5 != 0) DOTD_STUB_ONCE("CKHkS08Hero_CancelAbilityA 0x326ee0 (C2.7)");
        m_unk1cc4 = m_unk1cc8 == 4 ? (flags & 0x10u) : m_unk1cc8;
        // STUB(C2.7: HUD): ShowSpyroSelectedElementHud 0x5039e8 / ShowCynderSelectedElementHud 0x5024d8 (+0x1cc7).
        if (m_ui8Hero == 0 || m_ui8Hero == 1) DOTD_STUB_ONCE("Show*SelectedElementHud 0x5039e8 / 0x5024d8 (C2.7)");
        flags = m_unked0;
    }
    if ((flags & 0x2000u) != 0 && (m_unk354 & 0x2000000u) != 0 && m_unke4 != nullptr) {
        // STUB(C2.7: combat): with a combo kind flag (0x2fc1b0) and the touched volume's enemy (+0x24, key 0x26c2, a valid
        // target 0x289278): Cynder adds +0xe90 to its poison gauge (0x2890f8), Spyro sets off an explosion from the FX
        // pool of +0x1b58 (damage +0x1b54 at +0xe8). No rand.
        DOTD_STUB_ONCE("UpdateRegenAndElementTimeout 0x30b6b8: the combo hit's poison / explosion (C2.7)");
        flags = m_unked0;
    }
    if ((flags & 0x2000000u) != 0 && (flags & 0x10u) != 0) {
        if (m_unk1b68 == 0) {
            // STUB(C2.7: FX): the aura particles (+0x1b64's data on hot spot 5) taken from the FX service's pool into
            // +0x1b68 (0 when none is free).
            DOTD_STUB_ONCE("UpdateRegenAndElementTimeout 0x30b6b8: the aura particles (C2.7)");
            m_unk1b68 = 0;
        }
        if ((group->m_unkf8 & 0x400u) != 0) {
            m_unk1b84 = m_unk1b84 - m_unk88c;
            if (m_unk1b84 <= 0.0f) {  // TOC +0x21a0; cror lt|eq
                // STUB(C2.7: FX): an explosion from the pool of +0x1b5c at hot spot 5 (damage +0x1b60, the node's up axis).
                DOTD_STUB_ONCE("UpdateRegenAndElementTimeout 0x30b6b8: the aura explosion (C2.7)");
                const float first = std::fabs(RandomPeriod(m_unkea8, m_unkeac));  // the sign bit cleared on the stack
                float period = 999.9999f;  // TOC +0x2190 (0x4479ffff)
                if (first >= 1.0e-3f) period = 1.0f / std::fabs(RandomPeriod(m_unkea8, m_unkeac));  // TOC +0x218c
                m_unk1b84 = period;
            }
        }
        flags = m_unked0;
    }
    if (m_unk1b68 != 0 && ((flags & 0x2000000u) == 0 || (flags & 0x10u) == 0)) {
        // STUB(C2.7: FX): StopOwnedParticleEffect 0x1cdde8 and the effect's vt+0x54 (release).
        DOTD_STUB_ONCE("UpdateRegenAndElementTimeout 0x30b6b8: the aura particles' stop (C2.7)");
        m_unk1b68 = 0;
        flags = m_unked0;
    }
    if ((flags & 0x100000u) != 0 && (m_unk354 & 0x2000000u) != 0) {
        const uint32_t draw = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
        const float chance = m_unke98 / 100.0f;  // TOC +0x2194
        if (!(static_cast<float>(static_cast<double>(draw)) / 65535.0f >= chance)) {  // bge
            const uint32_t which = (static_cast<uint32_t>(Rand_Int()) >> 15) & 1u;
            (void)which;
            // STUB(C2.7: bonuses): CKSrvBonus_SpawnBonuses_maybe 0x126278 of +0x1b6c / +0x1b70 (the draw's bit 15) at
            // +0xe8 along the node's at axis, from the position +0x54c.
            DOTD_STUB_ONCE("UpdateRegenAndElementTimeout 0x30b6b8: the bonus drop (C2.7)");
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
            // STUB(C2.7: enemies, bonuses): the nearest valid enemy of the enemy group (+0x04 of the game manager) within
            // +0xec0 (closer than the global 0x00c4acb8 +0x28); with one, a Rand_Int draw and a bonus thrown at it
            // (BonusPool_SpawnBonusObject 0x98f370, vt+0xe4).
            DOTD_STUB_ONCE("UpdateRegenAndElementTimeout 0x30b6b8: the bonus thrown at an enemy (C2.7)");
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
