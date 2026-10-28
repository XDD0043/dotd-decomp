// Reconstructed original translation unit: 0x30cb30-0x30f588 (GAME_TOC1, main_toc1), 14 functions, 13 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: HandleHeroContactDamageAndImpulse (1), HandleHeroDamageAndReaction (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x30cb30  FUN_0030cb30  [dead]
//   [ ] 0x30cc40  CKHkS08Hero_SetupHitSphere
//   [ ] 0x30cde0  StaticInitAndDestruction_30cde0
//   [ ] 0x30ce10  _GLOBAL__D_30ce10
//   [ ] 0x30ce20  _GLOBAL__I_30ce20
//   [x] 0x30ce30  CKHkS08Hero_GetCollisionVolumeFromObj54_maybe
//   [x] 0x30ce40  HandleHeroContactDamageAndImpulse
//   [x] 0x30d458  CKHkS08Hero_vfF4
//   [x] 0x30d528  CKHkS08Hero_RestoreDefaultVolumes_maybe
//   [ ] 0x30d688  HandleHeroDamageAndReaction
//   [ ] 0x30e990  CKHkS08Hero_ArmPendingHitSpheres
//   [ ] 0x30ec40  CKHkS08Hero_SetupTrailHitSpheres2
//   [ ] 0x30ee78  CKHkS08Hero_SetupTrailHitSpheres4_maybe
//   [ ] 0x30f220  CKHkS08Hero_UpdateComboHitSpheres
#include <cmath>

#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/math/Math.h"
#include "crt/ppc_ops.h"
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
        IKSerializable* damage = other->m_unk1c;
        if (damage != nullptr && damage->IsKindOfClass(0x970c) != 0) {  // CKS08Damage
            // STUB(C2.7): the damage objects (CKS08Damage / CKS08GolemDamage 0xad4c: their bytes +0x0c / +0x26 / +0x30 pick
            // the touch history's times and owner) and the hit (vt+0x190). Only the attacks of the fight have them.
            DOTD_STUB_ONCE("HandleHeroContactDamageAndImpulse 0x30ce40: a damage object's hit (C2.7)");
        } else if (m_unk1ac4 == 0 &&
                   ContactHistory_Touch(-1000.0f, 1.0f, &m_unk10c, other, other->m_pOwner) != 0) {  // 0x005830f8
            // STUB(C2.7): the hit, vt+0x190 (this, the owner, the contact point, the volume, 0): the hero's damage.
            DOTD_STUB_ONCE("HandleHeroContactDamageAndImpulse 0x30ce40: the hit vt+0x190 (C2.7)");
        }
    }
    if ((other->m_ui16PropertiesFlags & 0x100u) == 0) return;
    if (collision->AreResponseParamsActive(2) == 0) return;  // vt+0x0c
    uint8_t ownerType = other->m_ui8OwnerType;
    if (ownerType == 2) {
        if ((own->m_ui16PropertiesFlags & 0x10u) == 0) return;
        // STUB(C2.7): an enemy's push (1 - the enemy's +0x254) * interpenetration against the normal into +0x5e4, the
        // knock data +0x1d64..+0x1d78 cleared; then the owner type is read again (2: no further case).
        DOTD_STUB_ONCE("HandleHeroContactDamageAndImpulse 0x30ce40: an enemy's push (C2.7)");
        ownerType = other->m_ui8OwnerType;
    }
    if (ownerType == 3) {
        if (PartnerShouldStayClimbing() != 0 && m_ui8Hero == m_ui8TrackedLeader) {  // 0x002f8628
            if (other->m_ui8OwnerType == 3) {
                if ((m_unk354 & 0x40u) != 0) return;
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
        m_unked4 = (m_unked4 & 0xfffffffdu) | 2u;  // CKHkGolem
    }
}
