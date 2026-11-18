// Reconstructed original translation unit: 0x34f9f0-0x354538 (GAME_TOC1, main_toc1), 53 functions, 14 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: IKHkHero (5), CKHkS08HeroBase (2), ResolveHeroContactMovement (1), Vec3 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x34f9f0  FUN_0034f9f0  [dead]
//   [ ] 0x34fa78  KStub_Return1_34fa78  [dead]
//   [ ] 0x34fa80  FUN_0034fa80  [dead]
//   [ ] 0x34fb78  FUN_0034fb78  [dead]
//   [ ] 0x34fbc0  CKHkS08Hero_GetFlag358Bit10_maybe  [dead]
//   [ ] 0x34fbd0  CKHkS08Hero_GetFlag35CBit8_maybe  [dead]
//   [ ] 0x34fbe0  FUN_0034fbe0  [dead]
//   [ ] 0x34fc00  FUN_0034fc00  [dead]
//   [ ] 0x34fc10  FUN_0034fc10  [dead]
//   [ ] 0x34fc28  FUN_0034fc28  [dead]
//   [ ] 0x34fc40  FUN_0034fc40  [dead]
//   [ ] 0x34fc50  CKHkS08Hero_GetAnimTimeRemapped_maybe  [dead: no pointer to its descriptor 0xba0998, no call]
//   [ ] 0x34fd38  FUN_0034fd38  [dead]
//   [ ] 0x34fe30  FUN_0034fe30  [dead]
//   [ ] 0x34ff18  FUN_0034ff18  [dead]
//   [ ] 0x350010  FUN_00350010  [dead]
//   [ ] 0x350170  FUN_00350170  [dead]
//   [ ] 0x350268  FUN_00350268  [dead]
//   [ ] 0x350368  FUN_00350368  [dead]
//   [ ] 0x350538  FUN_00350538  [dead]
//   [ ] 0x350698  FUN_00350698  [dead]
//   [ ] 0x3506e0  FUN_003506e0  [dead]
//   [ ] 0x350790  FUN_00350790  [dead]
//   [ ] 0x350818  FUN_00350818  [dead]
//   [ ] 0x350918  FUN_00350918  [dead]
//   [ ] 0x350a58  FUN_00350a58  [dead]
//   [ ] 0x350bc0  FUN_00350bc0  [dead]
//   [x] 0x350c48  CKHkS08Hero_AdvanceInnerBlenderAnimTime_maybe
//   [ ] 0x350c88  FUN_00350c88  [dead]
//   [ ] 0x350e38  FUN_00350e38  [dead]
//   [ ] 0x350f70  FUN_00350f70  [dead]
//   [x] 0x351450  CKHkS08HeroBase_SkipAnimToEnd_maybe
//   [x] 0x351570  CKHkS08HeroBase_PlayAnim
//   [x] 0x3516e8  CKHkS08Hero_PlayAnimOnInnerBlender_maybe
//   [x] 0x351908  CKHkS08Hero_ResetInactiveBlendLayers_maybe
//   [ ] 0x351a20  FUN_00351a20  [dead]
//   [ ] 0x352100  FUN_00352100  [dead]
//   [x] 0x352468  CKHkS08Hero_UpdateAnimStateMachine_maybe
//   [x] 0x352bf8  IKHkHero_CallRestoreDefaultVolumes  (inlined at its callers: vt+0x130)
//   [x] 0x352c38  CKHkS08Hero_ResetBoundingSpheresAtDelta_maybe
//   [ ] 0x352da8  IKHkHero_SetVolumeMaskBits_maybe  [dead]
//   [x] 0x352dd0  IKHkHero_UpdateSpeedScaledVolumeRadius_maybe
//   [x] 0x352f10  CKHkS08Hero_SetCollisionVolumeEnabled
//   [x] 0x352f78  CKHkS08Hero_AttachVolumeToHotspot
//   [ ] 0x3531e0  IKHkHero_vf190  [dead: only in the abstract IKHkHero vtable 0xb22f10 (vt+0x190), which only IKHkHero's destructors 0x9be9a8 / 0x9bea98 install; CKHkS08Hero, the only hero, has 0x30d688 HandleHeroDamageAndReaction in that slot of its vtable 0xb22c98 (C2.8 port-final F07)]
//   [x] 0x353528  ResolveHeroContactMovement_maybe
//   [ ] 0x354350  KStub_Return1_354350  [dead]
//   [ ] 0x354358  FUN_00354358  [dead]
//   [ ] 0x354400  CKHkS08Hero_GetFlag358Bit18_maybe  [dead]
//   [ ] 0x354410  CKHkS08Hero_GetFlag358Bit28_maybe  [dead]
//   [ ] 0x354420  FUN_00354420  [dead]
//   [ ] 0x354470  IKHkHero_ContactPointToHeroPosition_maybe  [dead]
//   [ ] 0x3544c0  Vec3_AddScaledOrSubtract_maybe  [dead]
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/math/Quat.h"
#include "k2000/logic/CSGHotSpot.h"
#include <cmath>
#include "k2000/math/Math.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/core/Stub.h"
#include "crt/ppc_ops.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "k2000/misc/Engine.h"
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"

// 0x00352f10 CKHkS08Hero_SetCollisionVolumeEnabled (the hero argument of the original is unused)
void CKHkS08Hero::SetCollisionVolumeEnabled(IKBoundingVolume* volume, int32_t enabled) {
    CKSrvCollision* service = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    if (enabled != 0) {
        c22spyro::CollisionEnableVolume(service, volume);  // 0x192090
        return;
    }
    c22spyro::CollisionDisableVolume(service, volume);  // 0x1920e8
}

// 0x00351908 CKHkS08Hero_ResetInactiveBlendLayers_maybe: unless the motion state keeps them (bit 10 of +0x368), every
// blend layer but the first and the group's active one plays nothing.
void CKHkS08Hero::ResetInactiveBlendLayers() {
    if ((m_unk368 & 0x400u) != 0) return;
    IKGrpHero* group = static_cast<IKGrpHero*>(m_pGrpHero);
    const uint32_t layers = group->GetNbAnimBlendSlots(m_ui8Hero);                         // vt+0x134
    const int8_t active = static_cast<int8_t>(group->GetActiveInnerBlendSlot(m_ui8Hero));  // vt+0x170
    for (uint32_t i = 1; i < layers; ++i) {
        if (i != static_cast<uint32_t>(active)) PlayAnimOnInnerBlender(0.0f, 0.0f, static_cast<uint8_t>(i), 0xfffd);
    }
}


namespace {
// The slot's crossfade dropped and the blender weighted on the active side (TOC +0x2b80 0.0f / +0x2b6c 1.0f), then the
// active controller's animation set (no restart).
void PlayOnActive(AnimBlendSlot* slot, float start, uint32_t word) {
    slot->m_unk14 = 0;
    if (slot->m_pController != nullptr) {
        static_cast<CKBlenderController*>(slot->m_pController)->m_unk58 = slot->m_unk10 != 0 ? 1.0f : 0.0f;
    }
    CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
    static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10])->SetAnim(start, word, false);
}
}  // namespace

// 0x003516e8 CKHkS08Hero_PlayAnimOnInnerBlender_maybe: on the blend layer `layer` (+0x138, 0x18 bytes each), animation
// 0xfffe crossfades to none over `blend` s; 0xffff (and above) to none over the crossfade time left, or cuts to none
// when no crossfade runs; 0xfffd cuts to none; any other is the layer's entry `animation` of the dictionary +0x13c
// (row layer x the row count + animation), crossfaded over `blend` s from `start`, or cut to at `start` without a blend
// or with flag 0x1000 of +0x354.
void CKHkS08Hero::PlayAnimOnInnerBlender(float start, float blend, uint8_t layer, uint32_t animation) {
    AnimBlendSlot* slot = m_unk138 + layer;
    if (animation == 0xfffeu) {
        slot->CrossfadeToAnim(blend, 0.0, 0xffffffffu, 1);  // TOC +0x2b80: 0.0f start, no animation
        return;
    }
    if (animation > 0xfffeu) {
        if (slot->m_unk0c != 0.0f) {
            slot->CrossfadeToAnim(slot->m_unk0c, 0.0, 0xffffffffu, 1);
            return;
        }
        PlayOnActive(slot, 0.0f, 0xffffffffu);
        return;
    }
    if (animation == 0xfffdu) {
        PlayOnActive(slot, 0.0f, 0xffffffffu);
        return;
    }
    const CAnimationDictionary* dictionary = static_cast<const CAnimationDictionary*>(m_pAnimDico);
    const uint32_t word = static_cast<uint32_t>(dictionary->m_apAnimations[layer * dictionary->m_ui32NbAnimations + animation]);
    if (blend != 0.0f && (m_unk354 & 0x1000u) == 0) {
        slot->CrossfadeToAnim(blend, start, word, 1);
        return;
    }
    PlayOnActive(slot, start, word);
}

// 0x00351450 CKHkS08HeroBase_SkipAnimToEnd_maybe: the active controller's time (+0x50) wrapped into the duration (when
// past it), then the time advanced (vt+0x188) to 0.01 s before the end.
void CKHkS08Hero::SkipAnimToEndBase() {
    AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
    CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
    const float end = static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10])->GetDuration();  // 0x0007ab60
    CKAnmKeyFrameController* controller = static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10]);
    const float duration = controller->GetDuration();
    float time = controller->m_unk50;
    if (!(duration >= time)) {  // bge
        const int32_t loops = ppc::fctiwz(time / duration);
        const float whole = static_cast<float>(static_cast<double>(loops));  // fcfid, frsp
        time = time - duration * whole;
    }
    AdvanceAnimTime((end - time) - 1.0e-2f);  // vt+0x188; TOC +0x2b70
}

// 0x00351570 CKHkS08HeroBase_PlayAnim: entry `animation` of the dictionary (+0x13c) on the hero's active blend slot,
// cut to at `start` (no blend, or flags 0x1000 of +0x354 / 0x100 of +0x364) or crossfaded over `blend` s; the request is
// kept (+0x158 blend, +0x15c start, +0x160 animation) and +0x354 gets bit 13 and loses bit 15.
void CKHkS08Hero::PlayAnimBase(float start, float blend, uint16_t animation) {
    AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
    const CAnimationDictionary* dictionary = static_cast<const CAnimationDictionary*>(m_pAnimDico);
    const uint32_t word = static_cast<uint32_t>(dictionary->m_apAnimations[animation]);
    if (blend == 0.0f || (m_unk354 & 0x1000u) != 0 || (m_unk364 & 0x100u) != 0) {  // TOC +0x2b80
        PlayOnActive(slot, start, word);
    } else {
        slot->CrossfadeToAnim(blend, start, word, 1);  // 0x00079ea0
    }
    m_unk158 = blend;
    m_unk160 = animation;
    m_unk15c = start;
    m_unk354 = ((m_unk354 & 0xffffdfffu) | 0x2000u) & 0xffff7fffu;
}

// 0x00352468 CKHkS08Hero_UpdateAnimStateMachine_maybe: the animation machine (rows +0x140 by the third byte of their
// key, handlers +0x148, current row +0x14c; no condition true is no state). With +0x358 bit 1 the hero leaves its
// animation state (and, unless +0x368 bit 10 keeps them, cuts its other inner layers to nothing) and only the root
// crossfade and (+0x360 bit 11) the active slot's inactive track run. Then vt+0x104 and every inner layer but the
// group's active one steps its inactive track.
void CKHkS08Hero::UpdateAnimStateMachine(IKTime* clock) {
    IKGrpHero* group = static_cast<IKGrpHero*>(m_pGrpHero);
    const float dt = clock->m_afDeltaTime[0];
    const uint8_t layers = group->GetNbAnimBlendSlots(m_ui8Hero);  // vt+0x134
    const uint32_t* handlers = reinterpret_cast<const uint32_t*>(m_unk148);
    if ((m_unk358 & 2u) != 0) {
        if (m_unk14c != 0xff) {
            SwitchState(handlers, m_unk14c, 0xff, clock);
            if ((m_unk368 & 0x400u) == 0) {
                const uint8_t count = group->GetNbAnimBlendSlots(m_ui8Hero);                     // vt+0x134
                const int8_t active = static_cast<int8_t>(group->GetActiveInnerBlendSlot(m_ui8Hero));  // vt+0x170
                for (uint32_t i = 1; i < count; ++i) {
                    if (static_cast<int32_t>(i) != active) PlayAnimOnInnerBlender(0.0f, 0.0f, static_cast<uint8_t>(i), 0xfffd);
                }
            }
        }
        UpdateSecondaryAnimCrossfade(clock);  // vt+0x108
        if ((m_unk360 & 0x800u) != 0) GetAnimBlendSlot()->AdvanceInactiveTrack(dt);  // vt+0x194, slot vt+0x10
        return;
    }
    const uint8_t count = group->GetNbHeroStatesD();  // vt+0x140
    uint8_t found = 0xff;  // no condition true: no state
    for (uint32_t row = 0; row < count; ++row) {
        if (CallStateCondition(m_unk140[row].m_aPtmf1, clock, static_cast<uint8_t>(row)) != 0) {
            found = static_cast<uint8_t>(row);
            break;
        }
    }
    m_unk354 &= 0xffffdfffu;
    if (found != m_unk14c) SwitchState(handlers, m_unk14c, found, clock);
    RunState(handlers, m_unk14c, clock);
    UpdateAnimation(clock);  // vt+0x104
    const int8_t active = static_cast<int8_t>(group->GetActiveInnerBlendSlot(m_ui8Hero));  // vt+0x170
    for (uint32_t i = 0; i < layers; ++i) {
        if (static_cast<int32_t>(i) != active) m_unk138[i].AdvanceInactiveTrack(dt);  // slot vt+0x10
    }
}

// 0x00352dd0 IKHkHero_UpdateSpeedScaledVolumeRadius_maybe: unless +0x360 bit 16 holds them, the hero's speed volume
// (the group's index for the hero, vt+0x164) grows by the frame's displacement (+0x5b4) over its file radius, at
// least 0.001; then vt+0xf4 sets the other volumes' radii.
void CKHkS08Hero::UpdateSpeedScaledVolumeRadius() {
    if ((m_unk360 & 0x10000u) != 0) return;
    const int8_t index = static_cast<int8_t>(CKGrpS08Hero::GetSpeedVolumeIndexOf(m_ui8Hero));  // vt+0x164
    if (index != -1) {
        IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_apBoundings[index]);
        const float radius = m_afBoundingsRadius[index];
        const float step = static_cast<float>(
            c22spyro::MathSqrtf(ppc::fmadds(m_unk5bc, m_unk5bc, ppc::fmadds(m_unk5b4, m_unk5b4, m_unk5b8 * m_unk5b8))));
        const float grown = radius + step;
        if (grown <= 0.0f) {  // TOC +0x2bd8
            volume->m_fRadius = 0.001f;  // TOC +0x2bd4
        } else {
            volume->m_fRadius = grown;
        }
    }
    VfF4();  // vt+0xf4
}

// 0x00353528 ResolveHeroContactMovement_maybe: unless the hero ignores contacts (+0x354 bit 5, +0x35c bit 21), every
// collision of its volumes (the group's count, vt+0x100): a touch of a volume it reacts to (own props 0x6e) is kept in
// the touch history +0x110 (the volume +0xe4 and the contact point +0xe8 kept, +0x354 bit 25); a hurting volume
// (props 0x200) in +0x10c (the hit: vt+0xf8 is 0 for CKHkS08Hero); then a solid volume (props 0x100) marks the kind
// of contact (+0x354 bits 19 enemy, 21 hero, 20 golem; +0x108 its owner) and pushes: with the response bit 2 by the
// interpenetration along the normal (flat; the horizontal speed +0x530 slowed when moving into it, +0x347), else the
// rest of the move of a moving sphere (response 1, the earliest contact time) slid along the normal; halved when the
// contact is shared with the partner. Pushes of the first kind go to +0x5e4 at once, the others are summed and added
// after the walk (moving the hero's moving spheres with them). Then the touch histories run down.
void CKHkS08Hero::ResolveHeroContactMovement(IKTime* clock) {
    static const CVector3 kNull = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC1 +0x2bc0)
    if ((m_unk354 & 0x20u) != 0 || (m_unk35c & 0x200000u) != 0) return;
    if ((m_unk35c & 0x10u) != 0) {
        // A pending hit without a volume: its source +0xd4 at the point +0xd8 (vt+0x190, a fifth argument 0 unused).
        HandleHeroDamageAndReaction(m_unkd4, reinterpret_cast<const CVector3*>(&m_unkd8), nullptr);  // 0x0030d688
    }
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    const uint8_t count = group->GetNbBoundingVolumes(m_ui8Hero);  // vt+0x100
    if (count == 0) return;
    float pendX = kNull.x, pendY = kNull.y, pendZ = kNull.z;     // f25 / f24 / f23
    float slideX = pendX, slideY = pendY, slideZ = pendZ;        // f28 / f27 / f26
    float earliest = 3.4028235e+38f;                             // f22: 0x00c4acb8 +0x28 (FLT_MAX)
    for (uint32_t i = 0;;) {
        IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_apBoundings[i]);
        for (ICollision* collision = static_cast<ICollision*>(volume->m_CollisionResList); collision != nullptr;
             collision = collision->m_pNext) {
            IKBoundingVolume* own;
            IKBoundingVolume* other;
            if (static_cast<IKBoundingVolume*>(collision->GetBoundingVolume1())->m_pOwner == this) {
                own = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume1());
                other = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume2());
            } else {
                own = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume2());
                other = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume1());
            }
            if ((own->m_ui16PropertiesFlags & 0x6eu) != 0 &&
                ContactHistory_Touch(-1000.0f, -1000.0f, &m_unk110, other, other->m_pOwner) != 0) {  // 0x005830f8
                m_unke4 = other;
                const CVector3* point = collision->GetWorldContactPoint();  // vt+0x20
                m_unke8 = point->x;
                m_unkf0 = point->z;
                m_unkec = point->y;
                m_unk354 = (m_unk354 & 0xfdffffffu) | 0x2000000u;
            }
            if ((other->m_ui16PropertiesFlags & 0x200u) != 0) {
                // The hit needs vt+0xf8 (CKHkS08Hero_vfF8 0x9bd6d0: 0), so only the touch is kept.
                ContactHistory_Touch(-1000.0f, 1.0f, &m_unk10c, other, other->m_pOwner);
            }
            if ((m_unk358 & 4u) != 0 && (other->m_ui16PropertiesFlags & 0x100u) != 0) {
                const uint8_t type = other->m_ui8OwnerType;
                if (type == 2) {
                    m_unk354 = (m_unk354 & 0xfff7ffffu) | 0x80000u;
                } else if (type == 3) {
                    m_unk354 = (m_unk354 & 0xffdfffffu) | 0x200000u;
                } else if (type == 1) {
                    m_unk354 = (m_unk354 & 0xffefffffu) | 0x100000u;
                }
                m_unk108 = other->m_pOwner;
            }
            bool push = false;   // the response part (0x353b5c)
            bool shared = false;  // r29: the contact is shared with the partner (the push halved)
            if ((other->m_ui16PropertiesFlags & 0x100u) != 0) {
                const uint8_t type = other->m_ui8OwnerType;
                if ((own->m_ui16PropertiesFlags & 0x2000u) != 0 || type == 1) {
                    if (type == 1) {
                        m_unk354 = (m_unk354 & 0xffefffffu) | 0x100000u;
                        push = (own->m_ui16PropertiesFlags & 1u) != 0;
                    }
                } else if (type == 2) {
                    m_unk354 = (m_unk354 & 0xfff7ffffu) | 0x80000u;
                    m_unk108 = other->m_pOwner;
                    // Unless +0x354 bit 6, vt+0x15c (CKHkS08Hero_vf15C 0x9bd6d8) is asked: it returns 1, so an enemy's
                    // contact never pushes here (the enemy pushes: HandleHeroContactDamageAndImpulse, C2.7).
                } else if (type == 3) {
                    m_unk354 = (m_unk354 & 0xffdfffffu) | 0x200000u;
                    m_unk108 = other->m_pOwner;
                    CKHkS08Hero* partner = static_cast<CKHkS08Hero*>(other->m_pOwner);
                    if ((m_unk354 & 0x40u) == 0 && (m_unk364 & 0x1000u) == 0 && (own->m_ui16PropertiesFlags & 0x100u) != 0) {
                        if ((other->m_ui16PropertiesFlags & 0x2000u) != 0) {
                            push = true;
                        } else if (m_ui8Hero == m_ui8TrackedLeader) {
                            if (partner->m_ui8Hero == partner->m_ui8TrackedLeader) {
                                push = shared = true;
                            } else if (HasNonZeroSpeed530Or534() == 0 || partner->HasNonZeroSpeed530Or534() != 0) {
                                if ((partner->m_unk358 & 4u) != 0) push = shared = true;
                            } else {
                                push = shared = true;
                            }
                        } else if ((m_unk358 & 0x80u) == 0 && (m_unk354 & 0x40000u) == 0) {
                            if (partner->m_ui8Hero != partner->m_ui8TrackedLeader) {
                                push = shared = true;
                            } else if (HasNonZeroSpeed530Or534() == 0 && partner->HasNonZeroSpeed530Or534() != 0) {
                                push = shared = true;
                            } else {
                                push = true;
                            }
                        }
                    }
                }
            }
            if (push) {
                float x, y, z;
                bool pending;
                if (collision->AreResponseParamsActive(2) != 0) {  // vt+0x0c
                    pending = false;
                    x = kNull.x;
                    y = kNull.y;
                    z = kNull.z;
                    if (collision->AreResponseParamsActive(4) != 0) {
                        const CVector3* normal = collision->GetNormale12();  // vt+0x1c
                        z = normal->z;
                        x = normal->x;
                        float depth = collision->GetdInterpenetration();  // vt+0x18
                        if (own == static_cast<IKBoundingVolume*>(collision->GetBoundingVolume1())) depth = -depth;
                        z = z * depth;
                        x = x * depth;
                        float length = ppc::fmadds(x, x, 0.0f);
                        length = ppc::fmadds(z, z, length);
                        length = std::sqrt(length);  // Math_Sqrtf 0x10690
                        float nz = z, nx = x, ny = 0.0f;
                        if (length != 0.0f) {
                            const float inverse = 1.0f / length;
                            ny = inverse * 0.0f;
                            nz = z * inverse;
                            nx = x * inverse;
                        }
                        y = 0.0f;
                        float dot = ny * m_unk544;
                        dot = ppc::fmadds(nx, m_unk540, dot);
                        dot = ppc::fmadds(nz, m_unk548, dot);
                        if (dot < 0.0f) {
                            const float slow = ppc::fmadds(-dot * static_cast<float>(m_unk347), -0.01f, 1.0f);
                            m_unk530 = m_unk530 * slow;
                        }
                    }
                } else {
                    if (other->m_ui8OwnerType != 3) m_unk530 = 0.0f;
                    x = kNull.x;
                    y = kNull.y;
                    z = kNull.z;
                    pending = true;
                    slideX = kNull.x;
                    slideY = kNull.y;
                    slideZ = kNull.z;
                    if (collision->AreResponseParamsActive(1) != 0 && collision->GetUDeltaTime() < earliest &&
                        own->IsKindOfClass(0x3cb) != 0) {  // CKDynamicBoundingSphere
                        earliest = collision->GetUDeltaTime();
                        const CKDynamicBoundingSphere* sphere = static_cast<const CKDynamicBoundingSphere*>(own);
                        z = sphere->m_v3WorldMove.z;
                        x = sphere->m_v3WorldMove.x;
                        const float rest = collision->GetUDeltaTime() - 1.0f;
                        z = z * rest;
                        x = x * rest;
                        y = 0.0f;
                        if (collision->AreResponseParamsActive(4) != 0) {
                            const CVector3* normal = collision->GetNormale12();
                            const float mz = -z, mx = -x;
                            float along = normal->z * mz;
                            along = ppc::fnmadds(normal->x, mx, along);
                            slideZ = ppc::fmadds(normal->z, along, mz);
                            slideX = ppc::fmadds(normal->x, along, mx);
                            slideY = along * 0.0f;
                        }
                    }
                }
                if (shared) {
                    z = z * 0.5f;
                    x = x * 0.5f;
                    y = y * 0.5f;
                }
                if (!(kNull.x == x && kNull.y == y && kNull.z == z)) {
                    if (pending) {
                        pendY = y;
                        pendZ = z;
                        pendX = x;
                    } else {
                        m_unk5e4 = m_unk5e4 + x;
                        m_unk5e8 = m_unk5e8 + y;
                        m_unk5ec = m_unk5ec + z;
                    }
                }
            }
            Vf138(collision, own, other);  // vt+0x138 CKHkS08Hero_vf138 0x30cab8 (empty)
        }
        if (++i == count) break;
    }
    float x = m_unk5e4 + pendX;
    float y = m_unk5e8 + pendY;
    float z = pendZ + m_unk5ec;
    m_unk5e4 = x;
    m_unk5e8 = y;
    m_unk5ec = z;
    if (!(kNull.x == x && y == kNull.y && z == kNull.z)) {
        // The hero's moving spheres (class id 0xf) follow the push: no move this frame, the position pushed.
        const uint8_t volumes = group->GetNbBoundingVolumes(m_ui8Hero);
        for (uint32_t j = 0; j < volumes; ++j) {
            IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_apBoundings[j]);
            if (volume->GetClassID() != 0xf) continue;  // vt+0x18; CKDynamicBoundingSphere
            CKDynamicBoundingSphere* sphere = static_cast<CKDynamicBoundingSphere*>(volume);
            const RwV3d& position = FrameLtm(sphere->m_pRwFrame)->pos;  // RwFrame +0x80
            const float pz = z + position.z;
            const float px = x + position.x;
            const float py = y + position.y;
            sphere->m_v3WorldMove = kNull;
            sphere->m_v3OldPos.z = pz;
            sphere->m_v3OldPos.x = px;
            sphere->m_v3OldPos.y = py;
            sphere->m_v3LastWorldPos.x = px;
            sphere->m_v3LastWorldPos.z = pz;
            sphere->m_v3LastWorldPos.y = py;
        }
        x = m_unk5e4;
        y = m_unk5e8;
        z = m_unk5ec;
    }
    m_unk5e4 = x + slideX;
    m_unk5e8 = y + slideY;
    m_unk5ec = slideZ + z;
    ContactHistory_Update(&m_unk10c, clock);    // 0x005833c0
    ContactHistory_Update(&m_unk110, nullptr);
}

// 0x00352c38 CKHkS08Hero_ResetBoundingSpheresAtDelta_maybe (step 4 AI: TeleportTo's): the hero's moving
// spheres (class id 0xf, CKDynamicBoundingSphere) at their frame's position moved by `delta`, with no move this frame.
void CKHkS08Hero::ResetBoundingSpheresAtDeltaPos(const CVector3* delta) {
    const uint8_t volumes = static_cast<CKGrpS08Hero*>(m_pGrpHero)->GetNbBoundingVolumes(m_ui8Hero);  // vt+0x100
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2bc0 -> 0x00c50d64
    for (uint32_t i = 0; i < volumes; ++i) {
        IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_apBoundings[i]);
        if (volume->GetClassID() != 0xf) continue;  // vt+0x18
        CKDynamicBoundingSphere* sphere = static_cast<CKDynamicBoundingSphere*>(volume);
        const RwV3d& position = FrameLtm(sphere->m_pRwFrame)->pos;  // RwFrame +0x80
        const float pz = position.z + delta->z;
        const float px = position.x + delta->x;
        const float py = position.y + delta->y;
        sphere->m_v3WorldMove.z = zero.z;
        sphere->m_v3WorldMove.x = zero.x;
        sphere->m_v3WorldMove.y = zero.y;
        sphere->m_v3OldPos.z = pz;
        sphere->m_v3OldPos.x = px;
        sphere->m_v3OldPos.y = py;
        sphere->m_v3LastWorldPos.x = px;
        sphere->m_v3LastWorldPos.z = pz;
        sphere->m_v3LastWorldPos.y = py;
    }
}

// 0x00352f78 CKHkS08Hero_AttachVolumeToHotspot: the volume under hot spot `hotspot` of the hero (-1: the hero's node,
// -2: the engine's dynamic scene root); already under that hot spot's node and bone, only its local transform reset to
// the hot spot's. The radius set when not 0 (0.001 for a negative one).
void CKHkS08Hero::AttachVolumeToHotspot(IKBoundingVolume* volume, int32_t hotspot, float radius) {
    CSGBranch* parent = volume->m_pParent;
    if (hotspot == -2 || hotspot == -1) {
        CSGBranch* target = hotspot == -2 ? static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)  // TOC +0x2be0 -> +0x14
                                          : static_cast<CSGBranch*>(m_pKGLObject);
        if (parent != target) {
            if (parent != nullptr) parent->RemoveChild(volume);  // vt+0x78
            target->AddChild(volume);                            // vt+0x70
        }
    } else {
        CSGHotSpot* spot = static_cast<CSGHotSpot*>(m_apHotSpots[hotspot]);
        if (parent == spot->m_pParent && volume->m_ui8BoneParent == spot->m_ui8BoneNumber) {
            RwFrame* frame = volume->m_pRwFrame;
            Quat_ToMatrix(spot->m_qUnitRelativeOrientation, reinterpret_cast<CMatrix34*>(&frame->modelling));  // 0x00241e48
            frame->modelling.pos.x = spot->m_v3RelativePosition.x;
            frame->modelling.pos.y = spot->m_v3RelativePosition.y;
            frame->modelling.pos.z = spot->m_v3RelativePosition.z;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);  // 0x00010698
        } else {
            if (parent != nullptr) parent->RemoveChild(volume);  // vt+0x78
            spot->AttachVolume(volume);                          // 0x000ce2b8
        }
    }
    if (radius == 0.0f) return;  // TOC +0x2bd8
    volume->m_fRadius = radius <= 0.0f ? 0.001f : radius;  // TOC +0x2bd4
}

// 0x00350c48 CKHkS08Hero_AdvanceInnerBlenderAnimTime_maybe
void CKHkS08Hero::AdvanceInnerBlenderAnimTime(float dt, uint32_t slot) {
    AnimBlendSlot& blend = m_unk138[slot];
    CKBlenderController* blender = static_cast<CKBlenderController*>(blend.m_pController);
    CKAnmKeyFrameController* controller = static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[blend.m_unk10]);
    controller->m_unk50 = dt + controller->m_unk50;  // fadds f1, f1, f0
}
