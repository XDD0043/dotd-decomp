// DirectionController.h - the segment chain of a hero element's beam (C2.8 port-final F07). No class: a 0x34-byte
// record (Mem_AllocAligned16) in a chain linked through +0x2c (the next segment) and +0x30 (the previous one).
// CKS08HeroElement's vt+0x6c (0x00371ab8) builds the chain (one root and the segments below it, the inlined builder
// 0x009bf0a8 BreathSegmentChain_Build_maybe), its vt+0x58 (0x00370d08) turns it towards the aim each frame
// (DirectionController_SetDirectionAndUpdate 0x00300120 -> DirectionController_Update 0x002fd0b8, both in the
// original unit CKHkS08Hero_3.cpp) and its vt+0x80 (0x00371608) frees it (BreathSegmentChain_Free 0x009bef38).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

struct DirectionController {
    CVector3 m_v3Vector;       // +0x00 the segment's vector from the root (the direction times m_fLength)
    CVector3 m_v3Target;       // +0x0c the direction it turns to (the null vector: none; the builder sets null)
    float m_fSpeed;            // +0x18 the turn speed of the last update (radians per second; the builder sets 0)
    float m_fSegment;          // +0x1c the length of one segment
    float m_fLength;           // +0x20 the distance from the root (the previous segment's plus m_fSegment; root 0)
    float m_fTimer;            // +0x24 the delay before it follows (-1: not started)
    uint8_t m_bTurning;        // +0x28 turning towards m_v3Target (the root: the update's flag)
    uint8_t m_pad29[3];
    DirectionController* m_pNext;    // +0x2c the next segment (BreathSegmentChain_Free's link)
    DirectionController* m_pParent;  // +0x30 the previous segment (null for the root)
};
DOTD_ASSERT_SIZE(DirectionController, 0x34);

// The beam (CKS08HeroElement +0x2c8, Mem_AllocAligned16(0x18)).
struct DirectionChain {
    CVector3 m_v3Direction;    // +0x00 the aim direction
    float m_f0c;               // +0x0c the second argument of the update (vt+0x58's f2)
    float m_f10;               // +0x10 the third (vt+0x58's f3; vt+0x6c: the element's vt+0x12c)
    DirectionController* m_pFirst;  // +0x14 the root segment (null without segments)
};
DOTD_ASSERT_SIZE(DirectionChain, 0x18);

// 0x002fd0b8 DirectionController_Update_maybe: the segments after `node` first (recursively), then `node` turns its
// vector towards its target (the previous segment's vector, or `direction` below the root) by at most dt * speed,
// after a delay of m_fSegment / followSpeed once its target changes. The root only keeps `flag` (m_bTurning).
void DirectionController_Update(float dt, float speed, float followSpeed, DirectionController* node,
                                const CVector3* direction, uint8_t flag);
// 0x00300120 DirectionController_SetDirectionAndUpdate_maybe: `direction` normalised in place (when not null), stored
// as the chain's direction with `speed` (+0x0c) and `followSpeed` (+0x10), then the root updated; the flag is 1 unless
// the new direction is within acos(0.75) of the old one or null.
void DirectionController_SetDirectionAndUpdate(float dt, float speed, float followSpeed, DirectionChain* chain,
                                               CVector3* direction);
