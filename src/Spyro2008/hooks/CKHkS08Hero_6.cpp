// Reconstructed original translation unit: 0x30cb30-0x30f588 (GAME_TOC1, main_toc1), 14 functions, 13 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: HandleHeroContactDamageAndImpulse (1), HandleHeroDamageAndReaction (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x30cb30  FUN_0030cb30  [dead]
//   [x] 0x30cc40  CKHkS08Hero_SetupHitSphere
//   [x] 0x30cde0  StaticInitAndDestruction_30cde0  (the two file statics at the end)
//   [ ] 0x30ce10  _GLOBAL__D_30ce10
//   [ ] 0x30ce20  _GLOBAL__I_30ce20
//   [x] 0x30ce30  CKHkS08Hero_GetCollisionVolumeFromObj54_maybe
//   [x] 0x30ce40  HandleHeroContactDamageAndImpulse
//   [x] 0x30d458  CKHkS08Hero_vfF4
//   [x] 0x30d528  CKHkS08Hero_RestoreDefaultVolumes_maybe
//   [x] 0x30d688  HandleHeroDamageAndReaction
//   [x] 0x30e990  CKHkS08Hero_ArmPendingHitSpheres
//   [x] 0x30ec40  CKHkS08Hero_SetupTrailHitSpheres2
//   [x] 0x30ee78  CKHkS08Hero_SetupTrailHitSpheres4_maybe
//   [x] 0x30f220  CKHkS08Hero_UpdateComboHitSpheres
#include <cmath>
#include "k2000/scenegraph/CTrailNodeFx.h"
#include "k2000/logic/CSGHotSpot.h"
#include "Spyro2008/logic/CKS08HeroCombo.h"
#include "Spyro2008/logic/CKS08HeroBlow.h"
#include "k2000/scenegraph/IKBoundingVolume.h"

#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include <cstring>
#include "k2000/services/CTriggerStarter.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "Spyro2008/logic/CKS08GolemDamage.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08Damage.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "k2000/math/Math.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/core/Stub.h"
#include "k2000/services/CKSrvCollision.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/IKBoundingBox.h"

// 0x0030d528 CKHkS08Hero_RestoreDefaultVolumes_maybe (vt+0x130): the four melee volumes off, the four body volumes
// on, and the box of the ninth volume back to its default extent (2.0, y, 0.1) with the radius of that box.
void CKHkS08Hero::RestoreDefaultVolumes() {
    if (m_ui8Hero != 0 && m_ui8Hero != 1) {
        m_unk1ac4 = 0;
        return;
    }
    CKSrvCollision* service = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    c22spyro::CollisionDisableVolume(service, static_cast<IKBoundingVolume*>(m_apBoundings[4]));
    c22spyro::CollisionDisableVolume(service, static_cast<IKBoundingVolume*>(m_apBoundings[5]));
    c22spyro::CollisionDisableVolume(service, static_cast<IKBoundingVolume*>(m_apBoundings[6]));
    c22spyro::CollisionDisableVolume(service, static_cast<IKBoundingVolume*>(m_apBoundings[7]));
    c22spyro::CollisionEnableVolume(service, static_cast<IKBoundingVolume*>(m_apBoundings[0]));
    c22spyro::CollisionEnableVolume(service, static_cast<IKBoundingVolume*>(m_apBoundings[2]));
    c22spyro::CollisionEnableVolume(service, static_cast<IKBoundingVolume*>(m_apBoundings[3]));
    c22spyro::CollisionEnableVolume(service, static_cast<IKBoundingVolume*>(m_apBoundings[1]));
    IKBoundingBox* box = static_cast<IKBoundingBox*>(m_apBoundings[8]);
    const float halfDepth = 0.1f;  // 0x00c17bb8 (TOC1 +0x21e0)
    box->m_Extent.x = 2.0f;        // 0x00c17bb4 (TOC1 +0x21dc)
    box->m_Extent.z = halfDepth;
    const float y = box->m_Extent.y;
    box->m_fRadius = std::sqrt(halfDepth * halfDepth + 2.0f * 2.0f + y * y);
    m_unk1ac4 = 0;
}

// 0x0030d458 CKHkS08Hero_vfF4 (vt+0xf4): the radii of the volumes 1..3 from the file (+0x1c4), 0.001 when not positive.
void CKHkS08Hero::VfF4() {
    for (uint32_t i = 1; i <= 3; ++i) {
        const float radius = m_afBoundingsRadius[i];
        static_cast<IKBoundingVolume*>(m_apBoundings[i])->m_fRadius = !(radius <= 0.0f) ? radius : 0.001f;  // ble; TOC +0x21bc / +0x21b8
    }
}

// 0x0030ce40 HandleHeroContactDamageAndImpulse: a volume that hurts (props 0x200) hurts the hero once per touch (the
// touch history +0x10c), then a solid volume (props 0x100) whose collision has the response bit 2 pushes the hero
// (+0x5e4): a hero partner (owner type 3, while the partner climb test holds and the hero leads) by the
// interpenetration along the normal, away from the partner; an enemy (owner type 2) is C2.7; a golem (owner type 1)
// sets +0xed4 bit 1 when the hero's own volume has props bit 0.
void CKHkS08Hero::HandleHeroContactDamageAndImpulse(ICollision* collision, IKBoundingVolume* own, IKBoundingVolume* other) {
    if ((other->m_ui16PropertiesFlags & 0x200u) != 0) {
        // The hit: vt+0x190 with the owner, the contact point (vt+0x20) and the volume.
        auto hit = [&]() { HandleHeroDamageAndReaction(other->m_pOwner, collision->GetWorldContactPoint(), other); };
        IKSerializable* object = other->m_unk1c;
        bool plain = true;  // the touch of a volume without a damage object (0x0030cebc)
        if (object != nullptr && object->IsKindOfClass(0x970c) != 0) {  // CKS08Damage
            const CKS08Damage* damage = static_cast<const CKS08Damage*>(object);
            const uint8_t lasting = damage->m_bContinuous;
            const uint8_t held = damage->m_unk26;
            const uint8_t golem = object->IsKindOfClass(0xad4c) != 0  // CKS08GolemDamage
                                      ? static_cast<const CKS08GolemDamage*>(object)->m_unk30
                                      : 0;
            if (lasting != 0) {
                plain = false;
                if (ContactHistory_Touch(-1000.0f, 0.0f, &m_pDamageContactHistory, other, other->m_pOwner) != 0) hit();  // 0x005830f8
            } else if (held != 0) {
                plain = false;
                if (ContactHistory_Touch(-1000.0f, 1.0f, &m_pDamageContactHistory, other, nullptr) != 0) hit();
            } else if (golem != 0) {
                plain = false;
                if (m_unk1ac4 == 0 && ContactHistory_Touch(-1000.0f, -1000.0f, &m_pDamageContactHistory, other, other->m_pOwner) != 0) {
                    hit();
                }
            }
        }
        if (plain && m_unk1ac4 == 0 &&
            ContactHistory_Touch(-1000.0f, 1.0f, &m_pDamageContactHistory, other, other->m_pOwner) != 0) {  // TOC +0x21cc / +0x21d0
            hit();
        }
    }
    if ((other->m_ui16PropertiesFlags & 0x100u) == 0) return;
    if (collision->AreResponseParamsActive(2) == 0) return;  // vt+0x0c
    uint8_t ownerType = other->m_ui8OwnerType;
    if (ownerType == 2) {
        if ((own->m_ui16PropertiesFlags & 0x10u) == 0) return;
        // 0x0030d19c: the enemy's push, (1 - its +0x254) * the interpenetration against the normal into +0x5e4, and the
        // knock data cleared; then the owner type is read again (2: no further case).
        const float share = 1.0f - static_cast<CKHkS08Enemy*>(other->m_pOwner)->m_unk254;  // TOC +0x21d0
        const float push = share * collision->GetdInterpenetration();                        // vt+0x18
        const CVector3* normal = collision->GetNormale12();                                  // vt+0x1c
        m_unk5e4 = ppc::fmadds(push, -normal->x, m_unk5e4);
        m_unk5e8 = ppc::fmadds(push, -normal->y, m_unk5e8);
        m_unk5ec = ppc::fmadds(push, -normal->z, m_unk5ec);
        const CVector3& zero = kHeroZeroVector;  // TOC +0x21d4 -> 0x00c50d64
        m_unk1d68 = zero.x;
        m_unk1d70 = zero.z;
        m_unk1d6c = zero.y;
        m_unk1d78 = 0;
        m_unk1d64 = 0;
        m_unk1d74 = 0;
        ownerType = other->m_ui8OwnerType;
    }
    if (ownerType == 3) {
        if (PartnerShouldStayClimbing() != 0 && m_ui8Hero == m_ui8TrackedLeader) {  // 0x002f8628
            if (other->m_ui8OwnerType == 3) {
                if ((m_ui32HeroFlags354 & 0x40u) != 0) return;
                const float penetration = collision->GetdInterpenetration();  // vt+0x18
                const CVector3* normal = collision->GetNormale12();           // vt+0x1c
                const float nz = normal->z, nx = normal->x, ny = normal->y;
                if (static_cast<IKBoundingVolume*>(collision->GetBoundingVolume1())->m_pOwner == this) {
                    m_unk5e4 = ppc::fmadds(penetration, -nx, m_unk5e4);
                    m_unk5e8 = ppc::fmadds(penetration, -ny, m_unk5e8);
                    m_unk5ec = ppc::fmadds(penetration, -nz, m_unk5ec);
                } else {
                    m_unk5e4 = ppc::fmadds(penetration, nx, m_unk5e4);
                    m_unk5e8 = ppc::fmadds(penetration, ny, m_unk5e8);
                    m_unk5ec = ppc::fmadds(penetration, nz, m_unk5ec);
                }
            }
        }
        ownerType = other->m_ui8OwnerType;
    }
    if (ownerType == 1 && (own->m_ui16PropertiesFlags & 1u) != 0 && other->m_pOwner->IsKindOfClass(0x3182) != 0) {
        m_ui32StatusFlagsED4 = (m_ui32StatusFlagsED4 & 0xfffffffdu) | 2u;  // CKHkGolem
    }
}

// 0x0030cc40 CKHkS08Hero_SetupHitSphere: the active spheres' count (+0x1bac) cleared and the four attack volumes
// (+0x1b8c..+0x1b98) switched off; `enable`: the first one attached to the hot spot with the radius and the damage
// (+0x1c), +0xec4 bit 0x20 set; else +0xec4 bits 0xe0 cleared and +0x1bb0 = 0.
void CKHkS08Hero::SetupHitSphere(float radius, uint8_t enable, int8_t hotspot, IKSerializable* damage) {
    m_ui32ActiveHitSphereCount = 0;
    IKBoundingVolume* volumes[4] = {static_cast<IKBoundingVolume*>(m_unk1b8c), static_cast<IKBoundingVolume*>(m_unk1b90),
                                    static_cast<IKBoundingVolume*>(m_unk1b94), static_cast<IKBoundingVolume*>(m_unk1b98)};
    for (IKBoundingVolume* volume : volumes) SetCollisionVolumeEnabled(volume, 0);  // 0x00352f10
    if (enable != 0) {
        AttachVolumeToHotspot(volumes[0], hotspot, radius);  // 0x00352f78
        static_cast<IKBoundingVolume*>(m_unk1b8c)->m_unk1c = damage;
        m_unkec4 = (m_unkec4 & ~0x20u) | 0x20u;
        return;
    }
    m_unkec4 &= ~0xe0u;
    m_unk1bb0 = enable;
}

namespace {
// The trail spheres' attach: off the parent unless already under the hot spot's node and bone, then hung under the hot
// spot; the radius kept for 0, 0.001 when not positive (TOC +0x21bc / +0x21b8).
void AttachTrailSphere(IKBoundingVolume* volume, CSGHotSpot* spot, float radius) {
    if (spot != nullptr && !(volume->m_pParent == spot->m_pParent && volume->m_ui8BoneParent == spot->m_ui8BoneNumber)) {
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
        spot->AttachVolume(volume);  // 0x000ce2b8
    }
    if (radius == 0.0f) return;
    volume->m_fRadius = radius > 0.0f ? radius : 0.001f;
}
}  // namespace

// 0x0030ec40 CKHkS08Hero_SetupTrailHitSpheres2
void CKHkS08Hero::SetupTrailHitSpheres2(float radius, CSGHotSpot* a, CSGHotSpot* b, IKSerializable* damage) {
    m_ui32ActiveHitSphereCount = 0;
    IKBoundingVolume* volumes[4] = {static_cast<IKBoundingVolume*>(m_unk1b8c), static_cast<IKBoundingVolume*>(m_unk1b90),
                                    static_cast<IKBoundingVolume*>(m_unk1b94), static_cast<IKBoundingVolume*>(m_unk1b98)};
    for (IKBoundingVolume* volume : volumes) SetCollisionVolumeEnabled(volume, 0);  // 0x00352f10
    AttachTrailSphere(static_cast<IKBoundingVolume*>(m_unk1b8c), a, radius);
    AttachTrailSphere(static_cast<IKBoundingVolume*>(m_unk1b90), b, radius);
    static_cast<IKBoundingVolume*>(m_unk1b8c)->m_unk1c = damage;
    static_cast<IKBoundingVolume*>(m_unk1b90)->m_unk1c = damage;
    m_unkec4 = (m_unkec4 & ~0x40u) | 0x40u;
}

// 0x0030ee78 CKHkS08Hero_SetupTrailHitSpheres4_maybe
void CKHkS08Hero::SetupTrailHitSpheres4(float radius, CSGHotSpot* a, CSGHotSpot* b, CSGHotSpot* c, CSGHotSpot* d,
                                        IKSerializable* damage) {
    m_ui32ActiveHitSphereCount = 0;
    IKBoundingVolume* volumes[4] = {static_cast<IKBoundingVolume*>(m_unk1b8c), static_cast<IKBoundingVolume*>(m_unk1b90),
                                    static_cast<IKBoundingVolume*>(m_unk1b94), static_cast<IKBoundingVolume*>(m_unk1b98)};
    for (IKBoundingVolume* volume : volumes) SetCollisionVolumeEnabled(volume, 0);
    CSGHotSpot* spots[4] = {a, b, c, d};
    for (int i = 0; i < 4; ++i) AttachTrailSphere(volumes[i], spots[i], radius);
    for (IKBoundingVolume* volume : volumes) volume->m_unk1c = damage;
    m_unkec4 = (m_unkec4 & ~0x80u) | 0x80u;
}

namespace {
// 0x003c9c08 CKS08HeroDamage_Assign (through CKS08StunDamage_Assign 0x3d16a0, CKS08Damage_Assign 0x4eba18 and
// CKDamage_Assign 0x253a88): the fields copied, nothing for the same object.
void AssignHeroDamage(CKS08HeroDamage* to, const CKS08HeroDamage* from) {
    if (to == from) return;
    to->m_bContinuous = from->m_bContinuous;
    to->m_fAmount = from->m_fAmount;
    to->m_i32DamageKind = from->m_i32DamageKind;
    to->m_unk26 = from->m_unk26;
    to->m_fKnockbackForce = from->m_fKnockbackForce;
    to->m_fKnockbackTime = from->m_fKnockbackTime;
    to->m_unk18 = from->m_unk18;
    to->m_unk1c = from->m_unk1c;
    to->m_ui32DamageType = from->m_ui32DamageType;
    to->m_unk24 = from->m_unk24;
    to->m_unk25 = from->m_unk25;
    to->m_fDisarmAmount = from->m_fDisarmAmount;
    to->m_fStunAmount = from->m_fStunAmount;
}
}  // namespace

// 0x0030e990 CKHkS08Hero_ArmPendingHitSpheres: a pending sphere request (+0xec4 bit 0x20: one volume, 0x40: two, 0x80:
// four, in that order) switches the attack volumes from +0x1b8c on and lists them as active (+0x1b9c, count +0x1bac);
// +0x1bb0 set, the request bit cleared.
void CKHkS08Hero::ArmPendingHitSpheres() {
    uint32_t count;
    uint32_t bit;
    if ((m_unkec4 & 0x20u) != 0) {
        count = 1;
        bit = 0x20u;
    } else if ((m_unkec4 & 0x40u) != 0) {
        count = 2;
        bit = 0x40u;
    } else if ((m_unkec4 & 0x80u) != 0) {
        count = 4;
        bit = 0x80u;
    } else {
        return;
    }
    IKSerializable* volumes[4] = {m_unk1b8c, m_unk1b90, m_unk1b94, m_unk1b98};
    m_unk1bb0 = 1;
    for (uint32_t i = 0; i < count; ++i) {
        SetCollisionVolumeEnabled(static_cast<IKBoundingVolume*>(volumes[i]), 1);  // 0x00352f10
        m_apActiveHitSpheres[m_ui32ActiveHitSphereCount] = volumes[i];
        m_ui32ActiveHitSphereCount = m_ui32ActiveHitSphereCount + 1;
    }
    m_unkec4 &= ~bit;
}

// 0x0030f220 CKHkS08Hero_UpdateComboHitSpheres: the pending spheres armed; while the hit window is open (+0xedc bit
// 0x10) and no sphere is set yet, the blow's damage copied into the hero's (+0x1dbc), scaled by +0xe78 (+0xed0 bit 0x40)
// and +0xeb0 (bit 0x10), its +0x2c by +0xe7c (bit 0x200), and the sphere set at the blow's hot spot and radius; once
// the window closes the sphere cleared.
void CKHkS08Hero::UpdateComboHitSpheres() {
    ArmPendingHitSpheres();  // 0x0030e990
    CKS08HeroBlow* blow = static_cast<CKS08HeroCombo*>(m_pCurrentComboNode)->GetBlow();  // vt+0x54
    (void)blow->GetAnimId();  // vt+0x8c (the result is not used)
    if ((m_unkedc & 0x10u) == 0) {
        if (m_unk1bb0 != 0) SetupHitSphere(1.0f, 0, -1, nullptr);  // TOC +0x21d0
        return;
    }
    if (m_unk1bb0 != 0) return;
    CKS08HeroDamage* damage = static_cast<CKS08HeroDamage*>(m_unk1dbc);
    AssignHeroDamage(damage, blow->GetDamage());  // 0x003c9c08
    float scale = (m_ui32StatusFlagsED0 & 0x40u) != 0 ? m_unke78 : 1.0f;
    if ((m_ui32StatusFlagsED0 & 0x10u) != 0) scale = scale * m_unkeb0;
    damage->m_fAmount = scale * damage->m_fAmount;
    if ((m_ui32StatusFlagsED0 & 0x200u) != 0) damage->m_fDisarmAmount = m_unke7c * damage->m_fDisarmAmount;
    if (m_unk1ad2 != 0 || m_unk1ad3 != 0) {
        // The trail spheres at the two hot spots of the swing trails' first ribbons (A: +0x5c[0], B: +0x5c[2]).
        auto ribbon = [this](int k) {
            return static_cast<CTrailNodeFx*>(m_apTrails[k])->m_apTrailData[0];
        };
        if (m_unk1ad2 != 0 && m_unk1ad3 != 0) {
            STrailNodeData* a = ribbon(0);
            STrailNodeData* b = ribbon(2);
            SetupTrailHitSpheres4(blow->GetHitRadius(), a->m_pHotSpot1, a->m_pHotSpot2, b->m_pHotSpot1, b->m_pHotSpot2,
                                  m_unk1dbc);  // vt+0x68, 0x0030ee78
            return;
        }
        STrailNodeData* a = ribbon(m_unk1ad2 != 0 ? 0 : 2);
        SetupTrailHitSpheres2(blow->GetHitRadius(), a->m_pHotSpot1, a->m_pHotSpot2, m_unk1dbc);  // 0x0030ec40
        return;
    }
    const int8_t hotspot = static_cast<int8_t>(blow->GetHotspotIndex());  // vt+0x64
    SetupHitSphere(blow->GetHitRadius(), 1, hotspot, damage);           // vt+0x68, 0x0030cc40
}

namespace {
// The message 0xc32's block (sp+0x8c in HandleHeroDamageAndReaction): the source of a hit without its own damage object
// fills in the damage, the knock direction, the origin and the kind (3: no hit). No LVL010 class answers it.
struct HazardHitQuery {
    IKSerializable* m_hero;      // +0x00
    IKBoundingVolume* m_volume;  // +0x04
    float m_dirX;                // +0x08 (the angle's cosine over the length with +0x0c)
    float m_dirZ;                // +0x0c
    uint32_t m_unk10;            // +0x10
    CVector3 m_point;            // +0x14 the origin (the zero vector: none)
    int32_t m_kind;              // +0x20
    uint8_t m_damage;            // +0x24
    uint8_t m_unk25;             // +0x25
};
HazardHitQuery MakeHazardHitQuery(IKSerializable* hero, IKBoundingVolume* volume) {
    HazardHitQuery query;
    query.m_hero = hero;
    query.m_volume = volume;
    query.m_dirX = 0.0f;  // stw 0
    query.m_dirZ = 0.0f;
    query.m_unk10 = 0;
    query.m_point = kHeroZeroVector;  // TOC +0x21d4 -> 0x00c50d64
    query.m_kind = 0;
    query.m_damage = 0;
    query.m_unk25 = 0;
    return query;
}
// A CKS08GolemDamage's +0x28 reference: an object whose position follows its vtable (its class is unknown: every
// LVL010 reference is null).
struct SPositionedObject : IKSerializable {
    CVector3 m_v3Position;  // +0x04
};
}  // namespace

// 0x0030d688 HandleHeroDamageAndReaction (vt+0x190): the hit point kept (+0x1b44); nothing while the game manager's
// flags +0x64 bit 8 hold, while +0xecc bit 27 holds (but a hit of 10000 or more from a CKS08Damage of a 0xa40c source
// on the controlled hero), with +0x354 bit 26 or +0x35c bit 2. A hit sets +0x1ac4 (unless +0xed0 bit 23 or 4), signals
// the hero's trigger +0x1154 and, on the controlled hero, the group's +0xac0; the hit's origin +0xf8 (the point, or
// the hero's position at the zero vector), its kind +0x1ae8 (1 from a golem, else the damage's +0x20: a kind 0 ends
// here while the grab timer +0x1b30 runs). An enemy's volume (owner type 2): the enemy becomes the grab target +0x124
// (dropping a held one), the origin is its position; its damage (+0x04, times the kind's +0x554 for a CKHkS08Enemy;
// lasting damages (+0x0c) count by the frame through the fraction +0x1b40) goes to the dragon after the reduction,
// the hero leaving what it holds unless +0x360 bit 20 and the health is above the raw damage; with +0xed0 bit 21 the
// enemy takes the hero's damage +0x1b50 back. No damage makes the kind 2. Then +0x354 bit 30, the knock back
// (+0x1d7c: the damage's +0x10 / +0x14, the direction from the origin turned by its angles +0x18 / +0x1c), the hit
// explosion (the controlled hero, kind not 2) and a hurt sound (0x26 with +0xec8 bit 2, else 0x40..0x42).
// A hit without a volume (+0x35c bit 4) and the volumes of type 1 whose source is neither a golem nor a crumbly zone
// state ask the source (message 0xc32, HazardHitQuery): its reply gives the damage, the direction and the origin. A
// golem's volume (type 1) deals its damage unless a CKS08GolemDamage's height reach (+0x2c) excludes the hero, a crumbly
// zone state's (type 1) deals its damage at the hero's height, a volume of type 5 its damage (45 without a damage object).
void CKHkS08Hero::HandleHeroDamageAndReaction(IKSerializable* source, const CVector3* point, IKBoundingVolume* volume) {
    m_unk1b44 = point->x;
    m_unk1b48 = point->y;
    m_unk1b4c = point->z;
    if ((g_pEngine->m_gameManager->m_flags64 & 0x100u) != 0) return;  // TOC +0x21d8
    bool heavy = false;
    if (m_ui8Hero == m_ui8TrackedLeader && source->IsKindOfClass(0xa40c) != 0 && volume != nullptr &&
        volume->m_unk1c != nullptr && volume->m_unk1c->IsKindOfClass(0x970c) != 0) {
        heavy = static_cast<const CKS08Damage*>(volume->m_unk1c)->m_fAmount >= 10000.0f;  // TOC +0x21e4, cror gt / eq
    }
    if ((m_unkecc & 0x08000000u) != 0 && !heavy) return;
    if ((m_ui32HeroFlags354 & 0x04000000u) != 0) return;
    if ((m_ui32HeroFlags35C & 4u) != 0) return;
    if ((m_ui32StatusFlagsED0 & 0x00800000u) == 0 && (m_ui32StatusFlagsED0 & 0x10u) == 0) m_unk1ac4 = 1;
    QueueTriggerSignals(&m_tsHit);  // 0x00236338
    if (m_ui8Hero != m_ui8TrackedLeader) return;
    QueueTriggerSignals(&static_cast<CKGrpS08Hero*>(m_pGrpHero)->m_tsOnPlayerHeroHurt);
    const CVector3& zero = kHeroZeroVector;  // TOC +0x21d4 -> 0x00c50d64
    m_unk1ae8 = 0;
    if (zero.x == point->x && point->y == zero.y && point->z == zero.z) {
        m_unkf8 = m_unk54c;
        m_unkfc = m_unk550;
        m_unk100 = m_unk554;
    } else {
        m_unkf8 = point->x;
        m_unkfc = point->y;
        m_unk100 = point->z;
    }
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x21d8
    if (volume == nullptr) {
        if ((m_ui32HeroFlags35C & 0x10u) == 0) {
            // BUG(original): without +0x35c bit 4 the original goes on with the null volume (its +0x1c and +0x19 read at
            // address 0, a fault on the PS3). No caller passes a null volume without the bit.
            return;
        }
        // 0x0030de04: the source answers the message 0xc32 (how hard it hits); a reply of kind 3 ends the hit.
        m_pTargetedMecaHook = nullptr;
        HazardHitQuery query = MakeHazardHitQuery(this, nullptr);
        source->MessageProc(0xc32, &query);  // vt+0x1c
        if (query.m_kind == 3) {
            m_unk1ac4 = 0;
            return;
        }
        if (m_unk1acc != 0 && m_pTargetedEnemy != nullptr && m_unk1ac4 != 0) DropGrabbedEnemy();  // 0x002fc600
        // The original also takes the arc cosine of the reply's direction (+0x94 over its length, clamped to -1..1;
        // TocBridge_Math_Acosf 0x98e1a0) here and drops the result.
        const float reduced = ComputeHeroDamageAfterReduction(static_cast<float>(static_cast<double>(query.m_damage)), 1);
        const uint32_t amount = static_cast<uint32_t>(ppc::fctidz(reduced));
        manager->DamageDragon(m_ui8Hero, amount);  // 0x004fda08
        m_ui32HeroFlags354 = (m_ui32HeroFlags354 & 0xbfffffffu) | 0x40000000u;
        bool leave = true;
        if ((m_ui32HeroFlags360 & 0x00100000u) != 0) leave = !(query.m_damage < manager->GetDragonHealth(m_ui8Hero));  // cmplw; blt
        if (leave) LeaveAttachedObject();  // 0x00344e88
        if (!(query.m_point.x == zero.x && query.m_point.y == zero.y && query.m_point.z == zero.z)) {
            m_unkf8 = query.m_point.x;
            m_unkfc = query.m_point.y;
            m_unk100 = query.m_point.z;
        }
        // 0x0030dbb4: the random hurt sound only (no knock back, no explosion, no 0x26 sound).
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
        PlaySound(1.0f, 1.0f, static_cast<uint8_t>(((r * 3) >> 16) + 0x40), 0);  // 0x00334188
        return;
    }
    IKSerializable* object = volume->m_unk1c;
    if (source->IsKindOfClass(0x3182) != 0) {  // CKHkGolem
        m_unk1ae8 = 1;
    } else if (object != nullptr && object->IsKindOfClass(0x970c) != 0) {
        m_unk1ae8 = static_cast<const CKS08Damage*>(object)->m_ui32DamageType;
        if (m_unk1ae8 == 0 && m_unk1b30 > 0.0f) {  // ble: a NaN goes on
            m_unk1ac4 = 0;
            return;
        }
    }
    float angleX = 0.0f, angleY = 0.0f;  // f23 / f25: the damage's +0x18 / +0x1c in degrees
    float knock = 0.0f, knockUp = 0.0f;  // f24 / f27: the damage's +0x10 / +0x14
    float dealt = 0.0f;                  // f30
    const float speed = 1.0f;            // f26 (TOC +0x21d0)
    // The knock back data of a CKS08Damage (0x970c).
    auto takeKnockData = [&](IKSerializable* damageObject) {
        if (damageObject->IsKindOfClass(0x970c) == 0) return;
        const CKS08Damage* damage = static_cast<const CKS08Damage*>(damageObject);
        float word18;
        std::memcpy(&word18, &damage->m_unk18, sizeof(word18));
        angleX = word18 * 57.29578f;  // TOC +0x21e8
        angleY = damage->m_unk1c * 57.29578f;
        knock = damage->m_fKnockbackForce;
        knockUp = damage->m_fKnockbackTime;
    };
    // The whole points of `raw` (a lasting damage by the frame through the fraction +0x1b40), kept as dealt (f30).
    auto wholeDamage = [&](float raw, uint8_t lasting) -> uint32_t {
        uint32_t amount;
        if (lasting != 0) {
            float fraction = AsF32(m_unk1b40) + ComputeHeroDamageAfterReduction(raw * m_unk88c, 0);
            SetF32(m_unk1b40, fraction);
            amount = static_cast<uint32_t>(ppc::fctidz(fraction));
            dealt = static_cast<float>(static_cast<double>(amount));
            fraction = fraction - dealt;
            SetF32(m_unk1b40, fraction);
        } else {
            amount = static_cast<uint32_t>(ppc::fctidz(ComputeHeroDamageAfterReduction(raw, 1)));
            dealt = static_cast<float>(static_cast<double>(amount));
        }
        return amount;
    };
    // 0x0030dd30: a volume's damage to the dragon; the hero leaves what it holds unless +0x360 bit 20 and its health is
    // above the raw damage (a float compare here, cror lt|eq).
    auto volumeDamage = [&](const CKDamage* raw) {
        const float damage = raw->m_fAmount;
        const uint32_t amount = wholeDamage(damage, raw->m_bContinuous);
        bool leave = true;
        if ((m_ui32HeroFlags360 & 0x00100000u) != 0) {
            leave = static_cast<float>(static_cast<double>(manager->GetDragonHealth(m_ui8Hero))) <= damage;  // 0x4fd9c8
        }
        if (leave) LeaveAttachedObject();          // 0x00344e88
        manager->DamageDragon(m_ui8Hero, amount);  // 0x004fda08
    };
    // The volume's position (the stored LTM of its frame, +0x80) as the origin.
    auto volumeOrigin = [&]() {
        const RwV3d& pos = volume->m_pRwFrame->ltm.pos;
        m_unkf8 = pos.x;
        m_unkfc = pos.y;
        m_unk100 = pos.z;
    };
    if (volume->m_ui8OwnerType == 2) {
        IKSerializable* owner = volume->m_pOwner;
        if (owner == nullptr) return;
        CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(owner);
        if (m_unk1acc != 0 && m_pTargetedEnemy != nullptr) {
            if (m_unk1ac4 != 0) {
                DropGrabbedEnemy();  // 0x002fc600
                m_pTargetedEnemy = owner;
            }
        } else {
            m_pTargetedEnemy = owner;
        }
        m_unkf8 = enemy->m_v3Position.x;
        m_unkfc = enemy->m_v3Position.y;
        m_unk100 = enemy->m_v3Position.z;
        if (object != nullptr) {
            const CKDamage* raw = static_cast<const CKDamage*>(object);
            if (object->IsKindOfClass(0x970c) != 0) {
                const CKS08Damage* damage = static_cast<const CKS08Damage*>(object);
                float word18;
                std::memcpy(&word18, &damage->m_unk18, sizeof(word18));
                angleX = word18 * 57.29578f;           // TOC +0x21e8
                angleY = damage->m_unk1c * 57.29578f;
                knock = damage->m_fKnockbackForce;
                knockUp = damage->m_fKnockbackTime;
            }
            dealt = raw->m_fAmount;
            if (owner->IsKindOfClass(0x26c2) != 0) dealt = dealt * enemy->m_pActiveEnemyCpnt->m_unk554;
            uint32_t amount;
            int64_t whole;
            if (raw->m_bContinuous != 0) {
                float fraction = AsF32(m_unk1b40) + ComputeHeroDamageAfterReduction(dealt * m_unk88c, 0);
                SetF32(m_unk1b40, fraction);
                whole = ppc::fctidz(fraction);
                amount = static_cast<uint32_t>(whole);
                fraction = fraction - static_cast<float>(static_cast<double>(whole));
                SetF32(m_unk1b40, fraction);
            } else {
                whole = ppc::fctidz(ComputeHeroDamageAfterReduction(dealt, 1));
                amount = static_cast<uint32_t>(whole);
            }
            bool leave = true;
            if ((m_ui32HeroFlags360 & 0x00100000u) != 0) {
                const uint32_t health = manager->GetDragonHealth(m_ui8Hero);  // 0x004fd9c8
                whole = ppc::fctidz(dealt);
                leave = !(static_cast<uint32_t>(whole) < health);  // cmplw
            }
            if (leave) LeaveAttachedObject();          // 0x00344e88
            manager->DamageDragon(m_ui8Hero, amount);  // 0x004fda08
            dealt = static_cast<float>(static_cast<double>(whole));  // the last word stored at sp+0xc0
        }
        if ((m_ui32StatusFlagsED0 & 0x00200000u) != 0 && enemy->IsValidCombatTarget() != 0) {  // 0x00289278
            enemy->ReceiveDamage(m_unk1b50, this);                                 // 0x0028a6e0
        }
        if (dealt == 0.0f) m_unk1ae8 = 2;
    } else if (volume->m_ui8OwnerType == 1 && source->IsKindOfClass(0x3182) != 0) {
        // 0x0030e0a0: a golem's volume.
        if (object == nullptr) {
            m_unk1ae8 = 2;
        } else {
            if (object->IsKindOfClass(0xad4c) != 0) {
                const CKS08GolemDamage* golem = static_cast<const CKS08GolemDamage*>(object);
                if (golem->m_unk28 != nullptr) {
                    // The reference's position (its first fields after the vtable; LVL010's references are all null).
                    const CVector3& at = static_cast<const SPositionedObject*>(golem->m_unk28)->m_v3Position;
                    m_unkf8 = at.x;
                    m_unkfc = at.y;
                    m_unk100 = at.z;
                } else {
                    volumeOrigin();
                }
                float reach;
                std::memcpy(&reach, &golem->m_unk2c, sizeof(reach));
                if (reach > 0.0f) {  // ble: a NaN skips the test
                    const float height = std::fabs(volume->m_pRwFrame->ltm.pos.y - m_unk550);  // the sign bit cleared
                    if (reach <= height) {  // cror lt|eq
                        m_unk1ac4 = 0;
                        return;
                    }
                }
                takeKnockData(object);  // 0x0030e850
            }
            volumeDamage(static_cast<const CKDamage*>(object));
            if (dealt == 0.0f) m_unk1ae8 = 2;
        }
    } else if (volume->m_ui8OwnerType == 1 && source->IsKindOfClass(0xa40c) != 0) {
        // 0x0030e4e0: a crumbly zone state's volume: the origin at the hero's height, no leaving.
        if (object == nullptr) {
            m_unk1ae8 = 2;
        } else {
            takeKnockData(object);
            m_unkfc = m_unk550;
            const CKDamage* raw = static_cast<const CKDamage*>(object);
            const uint32_t amount = wholeDamage(raw->m_fAmount, raw->m_bContinuous);
            manager->DamageDragon(m_ui8Hero, amount);  // 0x004fda08
            if (dealt == 0.0f) m_unk1ae8 = 2;
        }
    } else if (volume->m_ui8OwnerType == 1) {
        // 0x0030e5ec: any other source of a volume of type 1 answers the message 0xc32; a reply of kind 3 ends the hit.
        HazardHitQuery query = MakeHazardHitQuery(this, volume);
        source->MessageProc(0xc32, &query);  // vt+0x1c
        if (query.m_kind == 3) {
            m_unk1ac4 = 0;
            return;
        }
        IKSerializable* owner = volume->m_pOwner;
        const RwV3d self = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->ltm.pos;
        if (m_unk1acc != 0 && m_pTargetedEnemy != nullptr && m_unk1ac4 != 0) DropGrabbedEnemy();  // 0x002fc600
        m_pTargetedMecaHook = owner;
        const float length = std::sqrt(ppc::fmadds(query.m_dirX, query.m_dirX, query.m_dirZ * query.m_dirZ));  // fsqrts
        if (length != 0.0f) {
            float c = query.m_dirX / length;
            if (c <= -1.0f) {  // cror lt|eq
                c = -1.0f;
            } else if (c >= 1.0f) {  // cror gt|eq
                c = 1.0f;
            }
            angleX = crt::Acosf(c) * 57.29578f;  // TocBridge_Math_Acosf 0x98e1a0; TOC +0x21e8
        }
        bool leave = true;
        if ((m_ui32HeroFlags360 & 0x00100000u) != 0) leave = !(query.m_damage < manager->GetDragonHealth(m_ui8Hero));  // cmplw; blt
        if (leave) LeaveAttachedObject();  // 0x00344e88
        if (m_pTargetedMecaHook->IsKindOfClass(0x2f42) != 0) {
            // A hazardous jet: the origin below the hero's node along the jet's up axis, moved by 0.3 of the aim
            // direction; +0x11ec the jet's down axis.
            const RwV3d& up = static_cast<CSGMovable*>(static_cast<IKHook*>(m_pTargetedMecaHook)->m_pKGLObject)->m_pRwFrame->ltm.up;
            const float nx = -up.x;
            const float nz = -up.z;
            const float ny = -up.y;
            const float ox = self.x + nx;
            const float oz = self.z + nz;
            const float oy = self.y + ny;
            m_unkf8 = ox;
            m_unkfc = oy;
            m_unk100 = oz;
            m_unkf8 = ppc::fmadds(m_unk135c, 0.3f, ox);  // TOC +0x21ec
            m_unk100 = ppc::fmadds(m_unk1364, 0.3f, oz);
            m_unkfc = ppc::fmadds(m_unk1360, 0.3f, oy);
            m_unk11ec = nx;
            m_unk11f4 = nz;
            m_unk11f0 = ny;
        } else if (query.m_point.x == zero.x && query.m_point.y == zero.y && query.m_point.z == zero.z) {
            if (m_unk1ae8 == 0) {
                const RwV3d& at = static_cast<CSGMovable*>(static_cast<IKHook*>(m_pTargetedMecaHook)->m_pKGLObject)->m_pRwFrame->ltm.pos;
                m_unkf8 = at.x;
                m_unkfc = at.y;
                m_unk100 = at.z;
            }
        } else {
            // The hit point argument (not the reply's point).
            m_unkf8 = point->x;
            m_unkfc = point->y;
            m_unk100 = point->z;
        }
        knockUp = 0.2f;  // TOC +0x21f0
        knock = length / 0.2f;
        const float reduced = ComputeHeroDamageAfterReduction(static_cast<float>(static_cast<double>(query.m_damage)), 1);
        angleY = 0.0f;
        const uint32_t amount = static_cast<uint32_t>(ppc::fctidz(reduced));
        manager->DamageDragon(m_ui8Hero, amount);  // 0x004fda08
        dealt = static_cast<float>(static_cast<double>(amount));
        if (dealt == 0.0f) m_unk1ae8 = 2;
    } else if (volume->m_ui8OwnerType == 5) {
        // 0x0030dc9c: a volume of type 5 at its own position.
        if (object == nullptr) {
            // 0x0030e1b0: 45 points.
            const uint32_t amount = static_cast<uint32_t>(ppc::fctidz(ComputeHeroDamageAfterReduction(45.0f, 1)));  // TOC +0x21f4
            volumeOrigin();
            bool leave = true;
            if ((m_ui32HeroFlags360 & 0x00100000u) != 0) {
                leave = static_cast<float>(static_cast<double>(manager->GetDragonHealth(m_ui8Hero))) <= 45.0f;  // cror lt|eq
            }
            if (leave) LeaveAttachedObject();  // 0x00344e88
            manager->DamageDragon(m_ui8Hero, amount);  // 0x004fda08
            dealt = static_cast<float>(static_cast<double>(amount));
        } else {
            takeKnockData(object);
            volumeOrigin();
            volumeDamage(static_cast<const CKDamage*>(object));
        }
        if (dealt == 0.0f) m_unk1ae8 = 2;
    } else {
        m_unk1ae8 = 2;
    }
    // 0x0030da3c: the knock back away from the origin.
    m_ui32HeroFlags354 = (m_ui32HeroFlags354 & 0xbfffffffu) | 0x40000000u;
    float dx = m_unkf8 - m_unk54c;
    float dy = m_unkfc - m_unk550;
    float dz = m_unk100 - m_unk554;
    if (dx == zero.x && zero.y == dy && zero.z == dz) {
        dx = m_unk12a0;
        dz = m_unk12a8;
        dy = m_unk12a4;
        m_unkf8 = zero.x;
        m_unk100 = zero.z;
        m_unkfc = zero.y;
    }
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf 0x10690
    if (length != 0.0f) {
        const float k = speed / length;
        dz = dz * k;
        dx = dx * k;
        dy = dy * k;
    }
    SetF32(m_unk1d80, knockUp);
    m_unk1d7c = knock;
    m_unk1d88 = zero.x;
    m_unk1d8c = zero.y;
    m_unk1d90 = zero.z;
    m_unk1d84 = 0;
    SetF32(m_unk1d94, 0.0f);
    SetF32(m_unk1d98, 0.0f);
    const CVector3 away{-dx, -dy, -dz};
    const CVector3 turned = ComputeFinisherCameraVector(0.0f, angleY, angleX, &away, 0);  // 0x003006f0
    m_unk1d88 = turned.x;
    m_unk1d90 = turned.z;
    m_unk1d8c = turned.y;
    SetF32(m_unk1d98, 0.0f);
    m_unk1d94 = m_unk1d80;
    m_unk1d84 = 1;
    if (m_ui8TrackedLeader == m_ui8Hero && m_unk1ae8 != 2) SpawnHitExplosionFx();  // 0x00334450
    if ((m_unkec8 & 4u) != 0) {
        PlaySound(speed, speed, 0x26, 0);  // 0x00334188
        return;
    }
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
    PlaySound(speed, speed, static_cast<uint8_t>(((r * 3) >> 16) + 0x40), 0);
}

// 0x0030cde0 StaticInitAndDestruction_30cde0: two file statics (0x00ceae14, 0x00ceae18) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceae14 = -1.0f;
[[maybe_unused]] float s_unkceae18 = -1.0f;
}  // namespace
