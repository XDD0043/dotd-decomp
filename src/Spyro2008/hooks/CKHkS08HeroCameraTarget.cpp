// CKHkS08HeroCameraTarget.cpp - C2.2 strict2: the hero's entry on the camera service's target stack. Not a translation
// unit of the original: it holds CKHkS08Hero_UpdateModeFlagsAndTetherTimers_maybe 0x2dd340 (a function of the
// CKHkS08Hero unit, whose name does not say what it does: it registers the hero's scene node as a camera target and
// derives the camera parameters from the hero group), and the group / game manager slots that call it. When the hero
// unit's file takes the function over, this file goes away.
#include <cfloat>
#include <cstring>

#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "crt/ppc_ops.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/animation/CKAnimatedCamera.h"
#include "k2000/logic/cameras/CKCameraConstraint.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {

// 0x00333618 Math_RemapClamped (k2000/math, another family): `value` mapped from [lo, hi] onto [out0, out1].
float RemapClamped(float lo, float hi, float value, float out0, float out1) {
    if (hi == lo) return (out0 + out1) * 0.5f;
    if (hi >= value && lo <= value) return out0 + ((out1 - out0) * (value - lo)) / (hi - lo);
    if (hi < value) return out1;
    if (lo <= value) return 0.0f;
    return out0;
}

float BitsToFloat(uint32_t bits) {
    float value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

uint32_t ConstraintFlags(const CKCameraConstraint* constraint) {  // the word at +0x20 (loaded as a float)
    uint32_t bits;
    std::memcpy(&bits, &constraint->m_unk20, sizeof(bits));
    return bits;
}

}  // namespace

// 0x00342fa8 CKHkS08Hero_ShouldStayClimbing: a climbing hero (mode 2) stays so while a climb holds it (+0x1677 climbing,
// +0x1676 a zone in reach, +0x1679 / +0x1678 the mount / the ledge, +0xec8 bit 0 the top) and it was not let go
// (+0x1629); otherwise it goes back to the ground mode (SetMovementMode inlined: +0x180a and the game manager told).
// Any other mode is 0.
uint8_t CKHkS08Hero::ShouldStayClimbing() {
    if (m_unk1808 != 2) return 0;
    if ((m_unk1677 != 0 || m_unk1676 != 0 || m_unk1679 != 0 || m_unk1678 != 0 || (m_unkec8 & 1u) != 0) && m_unk1629 == 0) {
        return 1;
    }
    SetMovementMode(0);  // inlined (from 2: no +0x1809)
    return 0;
}

// 0x002d52d8 CKGrpS08Hero_vf184
void CKGrpS08Hero::UpdateHeroCameraTargets() {
    for (uint32_t index = 0; index < GetHeroCount(); ++index) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_apHeros[index]);
        if (hero != nullptr) hero->UpdateModeFlagsAndTetherTimers();
    }
}

// 0x004eda80 CKS08GameManager_vf144
void CKS08GameManager::UpdateHeroCameraTargets() {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_unk04[1]);
    if (group != nullptr) group->UpdateHeroCameraTargets();
}

// 0x002dd340 CKHkS08Hero_UpdateModeFlagsAndTetherTimers_maybe
void CKHkS08Hero::UpdateModeFlagsAndTetherTimers() {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    uint32_t& cameraFlags = camera->m_baTemporaryFlags;

    if (m_unkfb8 != nullptr) {
        // The carried hero's tether timers (+0x1780 / +0x1784): the carrier's vt+0x80 / +0x104, the partner's
        // climbing state and the group's maximum partner distance.
        // STUB(C2.8, moved from C2.6: the carrier hero is a scripted event, none exists at the level start).
        DOTD_STUB_ONCE("CKHkS08Hero_UpdateModeFlagsAndTetherTimers_maybe: carrier hero tether timers (C2.8, moved from C2.6)");
    }
    if (m_unk1784 != 0) m_unk1788 = 3.0f;

    // The movement mode picks the camera profile whose flag byte (CKS08GameManager vt+0x29c) is stored in the entry.
    const uint8_t mode = m_unk1808;
    uint32_t profile = 0;
    if (mode == 1) {
        profile = manager->GetPlayerCount() != 2 ? 2u : 5u;
    } else if (mode == 2) {
        profile = 1;
    }
    const uint8_t flagA = manager->m_unkAF4[profile];

    int64_t entryIndex;  // the hero's entry in the stack, -1 when it has none
    bool sameHero;       // iVar21: this hero is the one the player controls
    if (manager->GetPlayerCount() == 2) {
        if (m_ui8Hero == static_cast<int8_t>(group->m_unk66)) {  // the focused hero
            IKSerializable* leaf = m_unk1818;
            entryIndex = 0;
            if (leaf != nullptr) {
                if (camera->m_ui32NbStacked != 0) {
                    camera->RemoveStackDuplicates(leaf);
                    CKSrvCamera::StackEntry& first = camera->m_aStack[0];
                    if (first.m_pTarget != leaf || first.m_unk04 != flagA) cameraFlags |= 0x800000u;
                    first.m_pTarget = leaf;
                } else {
                    camera->AddStackEntry(leaf, flagA);
                    cameraFlags |= 0x800000u;
                }
                camera->m_aStack[0].m_unk04 = flagA;
                camera->m_aStack[0].m_unk05 = 1;
            }
        } else if (camera->m_pActiveConstraint == nullptr || (ConstraintFlags(camera->m_pActiveConstraint) & 0x400000u) == 0) {
            IKSerializable* leaf = m_unk1818;
            entryIndex = 0;
            if (leaf != nullptr) {
                const uint32_t found = camera->FindStackTarget(leaf);
                if (found < camera->m_ui32NbStacked) {
                    CKSrvCamera::StackEntry& entry = camera->m_aStack[found];
                    entryIndex = found;
                    if (entry.m_unk04 != flagA) {
                        cameraFlags |= 0x800000u;
                        entry.m_unk04 = flagA;
                    }
                    entry.m_unk05 = 1;
                } else {
                    cameraFlags |= 0x1000000u;
                    entryIndex = camera->m_ui32NbStacked;
                    camera->AddStackEntry(leaf, flagA);
                }
            }
        } else {  // a zone that takes the camera away from the non-focused hero: its entry goes
            const uint32_t found = camera->FindStackTarget(m_unk1818);
            if (found < camera->m_ui32NbStacked) camera->RemoveStackEntry(found);
            entryIndex = -1;
        }
        sameHero = m_ui8Hero == m_ui8TrackedLeader;
    } else if (manager->GetPlayerCount() > 1) {
        entryIndex = -1;
        sameHero = m_ui8Hero == m_ui8TrackedLeader;
    } else if (m_ui8Hero != m_ui8TrackedLeader) {  // the partner of a single player
        if ((m_unkec4 & 0x10000u) != 0 ||
            (camera->m_pActiveConstraint != nullptr && (ConstraintFlags(camera->m_pActiveConstraint) & 0x80u) != 0) ||
            0.0f < m_unk1788) {
            IKSerializable* leaf = m_unk1818;
            entryIndex = 0;
            if (leaf != nullptr) {
                const uint32_t found = camera->FindStackTarget(leaf);
                if (found < camera->m_ui32NbStacked) {
                    CKSrvCamera::StackEntry& entry = camera->m_aStack[found];
                    entryIndex = found;
                    if (entry.m_unk04 != flagA) {
                        cameraFlags |= 0x800000u;
                        entry.m_unk04 = flagA;
                    }
                    entry.m_unk05 = 1;
                } else {
                    cameraFlags |= 0x1000000u;
                    entryIndex = camera->m_ui32NbStacked;
                    camera->AddStackEntry(leaf, flagA);
                }
            }
        } else {  // not needed by the camera: its entry goes
            const uint32_t found = camera->FindStackTarget(m_unk1818);
            if (found < camera->m_ui32NbStacked) camera->RemoveStackEntry(found);
            entryIndex = -1;
        }
        sameHero = false;
    } else {  // the controlled hero
        IKSerializable* leaf = m_unk1818;
        entryIndex = 0;
        if (leaf != nullptr) {
            if (camera->m_ui32NbStacked == 0) {
                camera->AddStackEntry(leaf, flagA);
                cameraFlags |= 0x800000u;
            } else {
                camera->RemoveStackDuplicates(leaf);
                CKSrvCamera::StackEntry& first = camera->m_aStack[0];
                if (first.m_pTarget != leaf || first.m_unk04 != flagA) cameraFlags |= 0x800000u;
                first.m_pTarget = leaf;
                first.m_unk04 = flagA;
                first.m_unk05 = 1;
            }
        }
        sameHero = true;
    }

    // The entry's camera parameters from the hero group.
    const bool upperProfile = ((group->m_unkf8 >> 10) & 1u) != 0;
    float paramA = upperProfile ? group->m_unk1a8 : group->m_unk1ac;  // dVar42
    float paramD;                                                    // dVar43
    if (!sameHero) {
        paramD = upperProfile ? group->m_unk1a0 : group->m_unk1a4;
    } else {
        paramD = upperProfile ? group->m_unk198 : group->m_unk19c;
    }
    float paramB = sameHero ? 1.0f : group->m_unk194;  // dVar40
    if (m_unk1815 != 0 && m_unk1814 == 0) cameraFlags |= 0x800000u;
    if (manager->GetPlayerCount() >= 2) {
        const float scale = upperProfile ? 0.4f : group->m_unk1b8;
        paramD = paramD * scale;
        if (camera->m_pActiveConstraint != nullptr) {
            const float sum = BitsToFloat(group->m_unk318) + BitsToFloat(group->m_unk2d4[16]);
            if (8.0f <= sum) {
                const float factor = RemapClamped(8.0f, 16.0f, sum, 1.0f, 0.2f);
                paramD = paramD * factor;
            }
        }
    }
    const bool groupFlag = manager->GetPlayerCount() <= 1 && 0.0f <= group->m_unk36c;  // 0x2d4d48
    if (groupFlag || (m_unked4 & 0x40u) != 0) paramD = paramD * 0.05f;

    if (entryIndex != -1) {
        CKSrvCamera::StackEntry& entry = camera->m_aStack[entryIndex];
        const bool stayClimbing = ShouldStayClimbing();
        if (!stayClimbing && m_unk13d8 == 0) {
            float blend = 1.0f;
            float blendTarget = 1.0f;
            bool resetBlendTimer = false;
            if (m_ui8Hero == m_ui8TrackedLeader && groupFlag) {
                if (m_unk1b34 == 0.0f) {
                    blend = 1.0f;
                } else {
                    blend = ppc::fmadds(1.0f - m_unk1b3c, (m_unk1114 - m_unk111c) / m_unk1b34, m_unk1b3c);
                }
            } else if (m_unk1b34 == 0.0f || camera->m_pCurrentCamera == nullptr) {
                blend = 1.0f;
            } else {
                blend = ppc::fmadds(1.0f - m_unk1b3c, (camera->m_pCurrentCamera->m_unk18 - m_unk1b38) / m_unk1b34, m_unk1b3c);
                resetBlendTimer = (blend == blendTarget);
            }
            if (entry.m_unk10[1] != paramB) {
                entry.m_unk10[1] = paramB;
                if (entry.m_unk24[0] != FLT_MAX) cameraFlags |= 0x800000u;
            }
            if (entry.m_unk10[0] != paramA) {
                entry.m_unk10[0] = paramA;
                if (entry.m_unk24[0] != FLT_MAX) cameraFlags |= 0x800000u;
            }
            if (entry.m_unk10[3] != paramD) entry.m_unk10[3] = paramD;
            entry.m_unk10[2] = blend;
            entry.m_unk20 = -1.0f;
            if (resetBlendTimer) m_unk1b34 = 0.0f;
        } else {
            if (entry.m_unk10[1] != paramB) {
                entry.m_unk10[1] = paramB;
                if (entry.m_unk24[0] != FLT_MAX) cameraFlags |= 0x800000u;
            }
            if (entry.m_unk10[0] != paramA) {
                entry.m_unk10[0] = paramA;
                if (entry.m_unk24[0] != FLT_MAX) cameraFlags |= 0x800000u;
            }
            if (entry.m_unk10[3] != paramD) entry.m_unk10[3] = paramD;
            entry.m_unk10[2] = 1.0f;
            entry.m_unk20 = 0.0f;
        }
    }

    // The movement-mode history (+0x1813..+0x1815, newest first) and the time spent flying.
    if (m_unk1808 == 1) {
        if (m_unk13d1 == 0) {
            m_unk1815 = m_unk1814;
            m_unk13d4 = 0.0f;
            m_unk1814 = m_unk1813;
            m_unk1813 = 0;
        } else {
            m_unk13d4 = m_unk13d4 + m_unk550;
            if (m_unk13d4 < group->m_unk1b4 && m_unk88c < group->m_unk1b0) {
                if ((m_unkec4 & 0x4000u) != 0) {
                    m_unk1815 = m_unk1814;
                    m_unk1814 = m_unk1813;
                    m_unk1813 = 1;
                }
            } else {
                m_unk1815 = m_unk1814;
                m_unk1814 = m_unk1813;
                m_unk1813 = 0;
            }
        }
    } else {
        m_unk1815 = m_unk1814;
        m_unk1814 = m_unk1813;
        m_unk1813 = 0;
    }
    if (m_unk1378 != 0.0f && static_cast<int8_t>(group->m_unk66) == m_ui8Hero) cameraFlags |= 0x2000000u;
    const bool onGround = m_unk1808 == 0;
    bool joinPartnerFlight = false;
    if (onGround) joinPartnerFlight = ShouldJoinPartnerFlight() != 0;  // 0x00341fa0
    if (!onGround || joinPartnerFlight || m_unk1539 == 0 || (m_unkec8 & 0x400u) != 0) {
        cameraFlags &= 0xfbffffffu;
    } else {
        cameraFlags = (cameraFlags & 0xfbffffffu) | 0x4000000u;
    }
    if ((m_unkecc & 0x20u) != 0 && (m_unked0 & 0x40u) == 0) {
        // The animated camera (+0x1b28) vt+0x54 0x5bfad8 with the unscaled frame time (the frame clock's +0x20).
        static_cast<CKAnimatedCamera*>(m_unk1b28)->Update(g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[1]);
    }
    if (static_cast<int8_t>(group->m_unk66) == m_ui8Hero) {
        uint32_t cameraIndex = 1;
        if (!ShouldStayClimbing()) cameraIndex = joinPartnerFlight ? 2u : 0u;
        manager->SetActiveCameraIndex(cameraIndex);  // vt+0x294
    }
}
