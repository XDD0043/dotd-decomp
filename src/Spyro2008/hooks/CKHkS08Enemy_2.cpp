// Reconstructed original translation unit: 0x285340-0x2866d0 (GAME_TOC1, main_toc1), 24 functions, 16 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x285340  CKHkS08Enemy_RequestAnim
//   [x] 0x285388  CKHkS08Enemy_GetAnimLayerTime_maybe
//   [ ] 0x2853d0  CKHkS08Enemy_IsLayerSlotWord18Zero_maybe  [dead]
//   [x] 0x285408  CKHkS08Enemy_GetCurrentAnim
//   [ ] 0x285430  CKHkS08Enemy_GetLayerSlotByte25_maybe  [dead]
//   [ ] 0x285458  CKHkS08Enemy_SetLayerSlotByte26_maybe  [dead]
//   [ ] 0x285480  CKHkS08Enemy_GetLayerSlotByte26_maybe  [dead]
//   [ ] 0x2854a8  CKHkS08Enemy_SetLayerSlotByte27_maybe  [dead]
//   [ ] 0x2854d0  CKHkS08Enemy_GetLayerSlotByte27_maybe  [dead]
//   [x] 0x2854f8  CKHkS08Enemy_GetLayerSlotAnimDuration_maybe
//   [x] 0x285558  CKHkS08Enemy_IsAnimEndReached_maybe
//   [x] 0x285638  CKHkS08Enemy_GetAnimDuration_maybe
//   [ ] 0x285710  CKHkS08Enemy_AdvanceLayerSlotInactiveTrack_maybe  [dead]
//   [x] 0x285768  StaticInitAndDestruction_285768 (static init: nothing to port)
//   [x] 0x285798  _GLOBAL__D_285798
//   [x] 0x2857a8  _GLOBAL__I_2857a8
//   [x] 0x2857b8  CKHkS08Enemy_ResetLayer0Slot0StateByMode_maybe
//   [ ] 0x285a88  CKHkS08Enemy_IsAnimEndReachedForAnim_maybe  [dead]
//   [x] 0x285b98  CKHkS08Enemy_ForceAnimSlot_maybe
//   [x] 0x285c10  CKHkS08Enemy_SetSignedBlendAnimPair_maybe
//   [x] 0x285d88  CKHkS08Enemy_GetAnimSpeedScale_maybe
//   [x] 0x285ec8  CKHkS08Enemy_AdvanceTrackTime_maybe
//   [x] 0x286060  CKHkS08Enemy_AdvanceBlendSlotTime_maybe
//   [x] 0x286220  CKHkS08Enemy_AdvanceAnimLayer_maybe
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include <cstring>

#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKEnemySectorCpnt.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/groups/CKGrpSquad.h"

namespace {
// The sign bit of a stored float cleared (the original's clrlwi 1 on the word in memory).
float AbsBits(float value) {
    uint32_t bits;
    std::memcpy(&bits, &value, 4);
    bits &= 0x7fffffffu;
    std::memcpy(&value, &bits, 4);
    return value;
}
}  // namespace

// DOTD: the layer slot's active track: the blend slot's controller (a CKBlenderController) and its child +0x10 (the
// original's `*(slot + 0x08) + *(slot + 0x14) * 4 + 0x50`).
CKAnmKeyFrameController* CKHkS08Enemy::ActiveTrack(SEnemyAnimLayerSlot& slot) {
    CKBlenderController* blender = static_cast<CKBlenderController*>(slot.m_blendSlot.m_pController);
    return static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot.m_blendSlot.m_unk10]);
}

// DOTD: CKEnemySectorCpnt_GetAnimDictionary 0x2b3128 of the sector component `sector` (+0x18c): its +0x08 entry `layer`.
CAnimationDictionary* CKHkS08Enemy::AnimDictionary(uint32_t sector, uint32_t layer) const {
    CKEnemySectorCpnt* cpnt = static_cast<CKEnemySectorCpnt*>(m_unk18C[sector]);
    return static_cast<CAnimationDictionary*>(cpnt->m_apUnk08[layer]);
}

// DOTD: the duration of the animation a dictionary entry names, the TOC 1.0f (0xc0c) for none: the original's
// `entry != 0 ? entry->duration : 1.0f` (dotd keeps the entries as words, 0xffffffff for none).
float CKHkS08Enemy::AnimEntryDuration(uint32_t sector, uint32_t layer, uint32_t index) const {
    return CKAnmKeyFrameController::GetDurationOf(static_cast<uint32_t>(AnimDictionary(sector, layer)->m_apAnimations[index]));
}

// DOTD: the frame rate factor of the main state 1 (inlined in AdvanceTrackTime 0x285ec8 and AdvanceAnimLayer 0x286220):
// layer 0 slot 0 playing row 0x37, 0x38 or 0x3a scales by that row's duration (layer 0's dictionary of the current
// sector) times the kind's anim scale ratio (+0x88 of the config), any other row by the ratio alone.
float CKHkS08Enemy::ScaleRateInState1(float rate) {
    const uint8_t row = m_unk164[0][0].m_unk24;
    if (static_cast<uint8_t>(row - 0x37) <= 1 || row == 0x3a) {
        const float duration = AnimEntryDuration(GetSectorIndex(), 0, row);
        return rate * (duration * m_unk884->m_MoveCpnt.m_fAnimScaleRatio);
    }
    return rate * m_unk884->m_MoveCpnt.m_fAnimScaleRatio;
}

// 0x00285340 CKHkS08Enemy_RequestAnim (the original passes two unused registers r5 / r6): the slot's next animation,
// crossfade length and start time (the layer update applies them); +0x350 / +0x34c cleared, +0x794 = the height.
void CKHkS08Enemy::RequestAnim(uint8_t anim, uint8_t restart, uint32_t layer, uint32_t slot, float blend, float start) {
    SEnemyAnimLayerSlot& s = m_unk164[layer][slot];
    s.m_unk27 = restart;
    s.m_unk25 = anim;
    s.m_unk20 = blend;
    s.m_unk1c = start;
    m_unk350 = 0.0f;
    m_unk794 = m_v3Position.y;
    m_unk34c = 0.0f;
}

// 0x00285388 CKHkS08Enemy_GetAnimLayerTime_maybe: the active track's time (+0x50).
float CKHkS08Enemy::GetAnimLayerTime(uint32_t layer, uint32_t slot) {
    return ActiveTrack(m_unk164[layer][slot])->m_unk50;
}

// 0x00285408 CKHkS08Enemy_GetCurrentAnim
uint8_t CKHkS08Enemy::GetCurrentAnim(uint32_t layer, uint32_t slot) {
    return m_unk164[layer][slot].m_unk24;
}

// 0x002854f8 CKHkS08Enemy_GetLayerSlotAnimDuration_maybe: Anim_GetDuration of the active track.
float CKHkS08Enemy::GetLayerSlotAnimDuration(uint32_t layer, uint32_t slot) {
    return ActiveTrack(m_unk164[layer][slot])->GetDuration();
}

// 0x00285558 CKHkS08Enemy_IsAnimEndReached_maybe (r4 unused): the active track has an animation and its time wrapped
// into the duration plus `dt` reaches the duration (float throughout: fdivs, fctiwz, fmuls, fsubs, fadds).
bool CKHkS08Enemy::IsAnimEndReached(float dt, uint32_t layer, uint32_t slot) {
    return ActiveTrack(m_unk164[layer][slot])->HasEnded(dt);
}

// 0x00285638 CKHkS08Enemy_GetAnimDuration_maybe: the duration of row `anim`, column `slot` of the current sector's
// dictionary of `layer` (1.0 for none).
float CKHkS08Enemy::GetAnimDuration(uint8_t anim, uint32_t layer, uint32_t slot) {
    CAnimationDictionary* dictionary = AnimDictionary(GetSectorIndex(), layer);
    return CKAnmKeyFrameController::GetDurationOf(
        static_cast<uint32_t>(dictionary->m_apAnimations[anim + slot * dictionary->m_ui32NbAnimations]));
}

// 0x002857b8 CKHkS08Enemy_ResetLayer0Slot0StateByMode_maybe: layer 0 slot 0's request reset (crossfade 0.2) and its
// row chosen by the kind's movement mode (the config's CKHkMoveCpnt +0x7c): modes 0..7 rows 0/1, 3, 3/4, 7, 8, 2, 5, 6
// with the update flag 0x100 set; modes 8..11 rows 0x37..0x3a (0x3a with a 0.02 crossfade); else row 0.
void CKHkS08Enemy::ResetLayer0Slot0StateByMode() {
    SEnemyAnimLayerSlot& s = m_unk164[0][0];
    const uint32_t mode = m_unk884->m_MoveCpnt.m_eMvtAnim;
    s.m_unk26 = 0;
    s.m_unk1c = 0.0f;
    s.m_unk27 = 0;
    s.m_unk28 = 0;
    s.m_unk20 = 2.0e-1f;  // TOC 0xc1c 0x3e4ccccd
    uint8_t row = 0;
    switch (mode) {
    case 0: {
        // GetEnemyGroup 0x276f58 is called here and its result dropped.
        CKGrpSquad* squad = static_cast<CKGrpSquad*>(m_pGroupSquad);
        row = squad->m_vStates.m_pBlock[squad->m_unk55].m_unk30 == 1 ? 0 : 1;
        m_bitArray |= 0x100u;  // rlwinm 23 / rotlwi 9 clear bit 8, ori sets it
        break;
    }
    case 1: m_bitArray |= 0x100u; row = 3; break;
    case 2:
        m_bitArray |= 0x100u;
        if (m_unk884->m_unk4bd == 0) {
            s.m_unk26 = 1;
            row = 3;
        } else {
            row = 4;
        }
        break;
    case 3: m_bitArray |= 0x100u; row = 7; break;
    case 4: m_bitArray |= 0x100u; row = 8; break;
    case 5: m_bitArray |= 0x100u; row = 2; break;
    case 6: m_bitArray |= 0x100u; row = 5; break;
    case 7: m_bitArray |= 0x100u; row = 6; break;
    case 8: row = 0x37; break;
    case 9: row = 0x38; break;
    case 10: row = 0x39; break;
    case 11:
        s.m_unk20 = 2.0e-2f;  // TOC 0xc24 0x3ca3d70a
        row = 0x3a;
        break;
    default: row = 0; break;
    }
    s.m_unk25 = row;
}

// 0x00285b98 CKHkS08Enemy_ForceAnimSlot_maybe: slot (`layer`, `slot`) marked playing `anim` and forced; layer 0 slot 0
// requests `request` from 0 with no crossfade (+0x350 / +0x34c cleared, +0x794 = the height).
void CKHkS08Enemy::ForceAnimSlot(uint8_t anim, uint8_t request, uint32_t layer, uint32_t slot) {
    m_unk164[layer][slot].m_unk24 = anim;
    m_unk164[layer][slot].m_unk28 = 1;
    SEnemyAnimLayerSlot& s = m_unk164[0][0];
    s.m_unk27 = 0;
    s.m_unk25 = request;
    s.m_unk20 = 0.0f;
    s.m_unk1c = 0.0f;
    m_unk350 = 0.0f;
    m_unk794 = m_v3Position.y;
    m_unk34c = 0.0f;
}

// 0x00285c10 CKHkS08Enemy_SetSignedBlendAnimPair_maybe (the original: r4 = a, r5 = b, r6 = c, f1 = start, f2 = weight):
// on a stack copy of layer 0 slot 0's blend slot (only its controller keeps the result), both tracks at `start`:
// (`b`, `a`) weighted `weight` when it is above 0 (TOC 0xc28 0.0f), else (`b`, `c`) weighted |weight|.
void CKHkS08Enemy::SetSignedBlendAnimPair(float start, float weight, uint32_t a, uint32_t b, uint32_t c) {
    AnimBlendSlot copy = m_unk164[0][0].m_blendSlot;
    if (weight > 0.0f) {
        copy.SetAnimPairAndWeight(b, a, start, start, weight);
    } else {
        copy.SetAnimPairAndWeight(b, c, start, start, AbsBits(weight));
    }
}

// 0x00285d88 CKHkS08Enemy_GetAnimSpeedScale_maybe: for a slot playing row 0x37, 0x38 or 0x3a, the duration of layer 0
// slot 0's row in (`layer`, column `slot`) of the current sector's dictionary times the anim scale ratio (+0x88);
// otherwise the ratio.
float CKHkS08Enemy::GetAnimSpeedScale(uint32_t layer, uint32_t slot) {
    const uint8_t row = m_unk164[layer][slot].m_unk24;
    if (static_cast<uint8_t>(row - 0x37) > 1 && row != 0x3a) return m_unk884->m_MoveCpnt.m_fAnimScaleRatio;
    const uint8_t row0 = m_unk164[0][0].m_unk24;
    CAnimationDictionary* dictionary = AnimDictionary(GetSectorIndex(), layer);
    const float duration = CKAnmKeyFrameController::GetDurationOf(
        static_cast<uint32_t>(dictionary->m_apAnimations[row0 + slot * dictionary->m_ui32NbAnimations]));
    return duration * m_unk884->m_MoveCpnt.m_fAnimScaleRatio;
}

// 0x00285ec8 CKHkS08Enemy_AdvanceTrackTime_maybe (r4 unused): the active track's time advanced by dt x +0x774 (scaled in
// the main state 1, negated while layer 0 slot 0's +0x26 is set).
void CKHkS08Enemy::AdvanceTrackTime(uint32_t layer, uint32_t slot) {
    float rate = m_unk1fc * m_unk774;
    if (m_mainState == 1) rate = ScaleRateInState1(rate);
    if (m_unk164[0][0].m_unk26 != 0) rate = -rate;
    CKAnmKeyFrameController* track = ActiveTrack(m_unk164[layer][slot]);
    track->m_unk50 = rate + track->m_unk50;
}

// 0x00286060 CKHkS08Enemy_AdvanceBlendSlotTime_maybe: AdvanceTrackTime's body, then the blend slot's crossfade stepped
// by dt x +0x774 (AnimBlendSlot_AdvanceInactiveTrack_maybe).
void CKHkS08Enemy::AdvanceBlendSlotTime(uint32_t layer, uint32_t slot) {
    AdvanceTrackTime(layer, slot);
    m_unk164[layer][slot].m_blendSlot.AdvanceInactiveTrack(static_cast<double>(m_unk1fc * m_unk774));
}

// 0x00286220 CKHkS08Enemy_AdvanceAnimLayer_maybe (r6 unused): one layer slot per frame. A new request (another row, the
// restart flag or forced) crossfades (+0x20 long) to the requested row (column `slot` of `layer`'s dictionary of sector
// `sector`) from +0x1c, or with +0x26 from layer 0 slot 0's normalised time carried over (|time| / the old row's duration
// x the new row's) plus, in `state` 1, dt x +0x774 x the run scale (fmadds), else plus dt x +0x774; without one, the
// active track's time advances like AdvanceTrackTime (that test reads the enemy's main state, not `state`). Then the
// request flags clear and the crossfade steps (dt x +0x774).
void CKHkS08Enemy::AdvanceAnimLayer(uint8_t state, uint32_t sector, uint32_t layer, uint32_t slot) {
    SEnemyAnimLayerSlot& s = m_unk164[layer][slot];
    float rate = m_unk1fc * m_unk774;
    const float blend = s.m_unk20;
    float start = s.m_unk1c;
    if (s.m_unk24 != s.m_unk25 || s.m_unk27 != 0 || s.m_unk28 != 0) {
        // Row entries of `layer` (no column) for the durations; the crossfade uses column `slot`.
        const uint32_t oldWord = static_cast<uint32_t>(AnimDictionary(sector, layer)->m_apAnimations[s.m_unk24]);
        const uint32_t newWord = static_cast<uint32_t>(AnimDictionary(sector, layer)->m_apAnimations[s.m_unk25]);
        if (s.m_unk26 != 0) {
            const float time = AbsBits(ActiveTrack(m_unk164[0][0])->m_unk50);
            // BUG(original): the two entries are dereferenced without a null test (a missing row reads address 0x10);
            // dotd's word lookup gives 1.0 for none.
            start = (time / CKAnmKeyFrameController::GetDurationOf(oldWord)) * CKAnmKeyFrameController::GetDurationOf(newWord);
            if (state == 1) {
                const uint8_t row = m_unk164[0][0].m_unk24;
                if (static_cast<uint8_t>(row - 0x37) <= 1 || row == 0x3a) {
                    const float duration = AnimEntryDuration(GetSectorIndex(), 0, row);
                    const float scale = duration * m_unk884->m_MoveCpnt.m_fAnimScaleRatio;
                    start = ppc::fmadds(scale, rate, start);
                } else {
                    start = ppc::fmadds(m_unk884->m_MoveCpnt.m_fAnimScaleRatio, rate, start);
                }
            } else {
                start = rate + start;
            }
        }
        CAnimationDictionary* target = AnimDictionary(sector, layer);
        s.m_blendSlot.CrossfadeToAnim(static_cast<double>(blend), static_cast<double>(start),
                                      static_cast<uint32_t>(target->m_apAnimations[s.m_unk25 + slot * target->m_ui32NbAnimations]),
                                      1);
        s.m_unk24 = s.m_unk25;
    } else {
        if (m_mainState == 1) rate = ScaleRateInState1(rate);
        if (m_unk164[0][0].m_unk26 != 0) rate = -rate;
        CKAnmKeyFrameController* track = ActiveTrack(s);
        track->m_unk50 = rate + track->m_unk50;
    }
    s.m_unk26 = 0;
    s.m_unk27 = 0;
    s.m_unk28 = 0;
    m_unk164[layer][slot].m_blendSlot.AdvanceInactiveTrack(static_cast<double>(m_unk1fc * m_unk774));
}
