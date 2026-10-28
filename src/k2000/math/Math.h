// Math.h - the free functions of the unit Math.cpp (0x582a48-0x5854c8, GAME_TOC2): only what is ported so far.
#pragma once
#include <cstdint>

class CSGLeaf;
struct CGroundContactDatasIn;
struct CGroundContactDatasInOut;
struct CPFPoint;
struct CVector3;
class IKSerializable;
class IKTime;

// 0x00582c18 Math_WrapAngleToPi: the angle brought into [-pi, pi) by whole turns.
float Math_WrapAngleToPi(float angle);

// 0x005832a8 SceneNode_SetVisibleInLayer_maybe: bit 2 of the node's scene properties takes `visible` (a byte), and
// the node moves under the root of the sector `layer` unless it is there already (`keepWorldTransform` picks
// vt+0x74 instead of vt+0x70 of that root). A null node does nothing.
void SceneNode_SetVisibleInLayer(CSGLeaf* node, uint32_t visible, int32_t keepWorldTransform, int32_t layer);

// A contact history entry (0x18 bytes on the PS3, from the FreeListPool 0x00ceaa70; here a free list of its own):
// a volume touched by a hero (IKHkHero +0x10c / +0x110 hold the lists), its owner, two countdowns (-1000 = none) and
// whether it was touched this frame.
struct ContactHistoryNode {
    IKSerializable* m_pKey;       // +0x00 the volume
    IKSerializable* m_pOwner;     // +0x04 its owner (0: not checked)
    float m_fTime1;               // +0x08 kept while untouched, until it runs out
    float m_fTime2;               // +0x0c kept while touched, until it runs out
    uint8_t m_bTouched;           // +0x10
    ContactHistoryNode* m_pNext;  // +0x14
};
// 0x005830f8 ContactHistory_Touch_maybe: `key` touched this frame. Known: marked, 0. New: an entry at the head with
// the two times, 1 unless another entry of the same (non-null) owner is in the list (then 0).
uint8_t ContactHistory_Touch(float time1, float time2, ContactHistoryNode** head, IKSerializable* key, IKSerializable* owner);
// 0x005833c0 ContactHistory_Update_maybe: the countdowns run down by the clock's dt (+0x1c); an untouched entry goes
// when its first time is out (or none), a touched one when its second time is out; the touched marks are cleared.
// Without a clock the times are reset to -1000 first (the untouched entries go, the marks are cleared).
void ContactHistory_Update(ContactHistoryNode** head, IKTime* clock);

// 0x00583ef8 GroundContact_ProbeGroundPoint_maybe: the ground under `point` (CKSrvCollision GroundProbePoints with `in`,
// or with no reach and masks 1 / 8): when the contact's status is 0 or 1 the point moves to the projection (through a
// moving ground's matrix) less 0.01 in y and 1 is returned; else 0 (the point unchanged).
uint8_t GroundContact_ProbeGroundPoint(CGroundContactDatasInOut* contact, CVector3* point, const CGroundContactDatasIn* in);
// 0x00583a68 Math_EvalRampHoldDecay_maybe: a ramp / hold / decay curve at `t` from the six floats of `params`
// ({ramp time, hold time, decay time, offset, ramp slope, decay slope}): offset + slope * t while ramping, its end
// value while holding, less decay slope * the time past the hold while decaying; 0 (`out` untouched) after the decay,
// else 1.
int32_t Math_EvalRampHoldDecay(float* out, float t, const float* params);
// 0x005840d0 Vec3_ProjectOnPlane_maybe: `v` less its part along `normal` (normalised first, unless of length 0).
CVector3 Vec3_ProjectOnPlane(const CVector3* normal, const CVector3* v);
// 0x005843f0 GroundContact_SnapNavPoint_maybe: the nav point put on the ground under it and its sector found again;
// 1 when the ground was found and the sector did not change.
uint32_t GroundContact_SnapNavPoint(CGroundContactDatasInOut* contact, CPFPoint* point);
// 0x00582f28 CKSrvCamera_GetViewDirection_maybe: the camera service's view direction (+0x624, the heading direction).
void CKSrvCamera_GetViewDirection(CVector3* out);
// 0x005839d8 Vec3_YawDifferenceWrapped_maybe: the yaw of `to` less the yaw of `from` (both Vec3_GetYawAngleFromX),
// wrapped into [0, 2 pi).
float Vec3_YawDifferenceWrapped(const CVector3* from, const CVector3* to);
// 0x00584e40 Vec3_RotateYawFlatNormalized_maybe: `v` turned by `angle` radians about y, its y cleared, normalised (the
// zero vector and a zero angle leave it).
void Vec3_RotateYawFlatNormalized(float angle, CVector3* v);
// 0x00585110 Vec3_GenerateRadialPointsXZ_maybe: `count` points around `center` at `radius` in x / z (y kept), the
// direction turned by `angle` before each; the last direction into `lastDirection` when given.
void Vec3_GenerateRadialPointsXZ(float angle, float radius, const CVector3* center, const CVector3* direction,
                                 CVector3* points, int32_t count, CVector3* lastDirection);
