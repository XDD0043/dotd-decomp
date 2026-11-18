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
// 0x00582b08 Math_SolveQuadratic_maybe: the real roots of a x^2 + b x + c into *root1 / *root2 and their count (0, 1, 2).
// All three 0: 0. a = 0: 0 when b is 0 too, else 1 with both roots 0 (BUG(original): not -c / b). A negative
// discriminant: 0; a zero one: 1, both b / (-2 a); else 2, (sqrt(d) - b) / 2a and (-b - sqrt(d)) / 2a. A NaN
// discriminant gives 1 (ble 0x582b44 is taken when not greater).
int32_t Math_SolveQuadratic(float a, float b, float c, float* root1, float* root2);
// 0x00582bc8 Math_SmoothStep_maybe: 3t^2 - 2t^3 inside (0, 1), else t (NaN: t).
float Math_SmoothStep(float t);

// 0x00582c60 SceneNode_SetAlphaRecursive_maybe: the node (a CNode; null does nothing) and its geometries take `alpha`
// (255: blending off); with `hide` the node is hidden at alpha 0.
void SceneNode_SetAlphaRecursive(IKSerializable* object, uint8_t alpha, int32_t hide);

// 0x005832a8 SceneNode_SetVisibleInLayer_maybe: bit 2 of the node's scene properties takes `visible` (a byte), and
// the node moves under the root of the sector `layer` unless it is there already (`keepWorldTransform` picks
// vt+0x74 instead of vt+0x70 of that root). A null node does nothing.
void SceneNode_SetVisibleInLayer(CSGLeaf* node, uint32_t visible, int32_t keepWorldTransform, int32_t layer);

// A contact history entry (0x18 bytes on the PS3, from the FreeListPool 0x00ceaa70 (FreeListPool, Vec3.h)):
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
// The pool's two operations inlined by CKCrumblyZoneState (0x00403c20 / 0x00404050): an entry taken (FreeListPool_Grow when
// empty) / given back (in front of the free list).
ContactHistoryNode* ContactHistory_AllocNode();
void ContactHistory_FreeNode(ContactHistoryNode* node);

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
// 0x005841a8 Vec3_RotateTowardByAngle_maybe: `v` and `axis` normalised in place; the basis with `v` as up and `axis` as at
// (Mat4_SetBasisFromUpAt) turned `radians` about its own x, its up row into `out`; `v` itself when there is no basis.
void Vec3_RotateTowardByAngle(CVector3* out, CVector3* v, CVector3* axis, float radians);

// The rest of the unit (C2.8 port-rest R01).
class CNode;
struct CMatrix34;
struct RwTexture;
// 0x00582a48 Math_WrapAngleTo2Pi_maybe: the angle brought into [0, 2 pi) by whole turns (dead in the original).
float Math_WrapAngleTo2Pi(float angle);
// The CKCounterNodeFx helpers of the unit (R06's CKCounterNodeFx.cpp calls them; they only touch the node's geometries).
// 0x00583028 CKCounterNodeFx_SetDigitTexture_maybe: the node's first geometry's material takes `first`, the second's
// `second` (each material's property bits 0 and 1 set). No null test.
void CounterNode_SetDigitTextures(CNode* node, RwTexture* first, RwTexture* second);
// 0x00582f58 CKCounterNodeFx_SetDigitTexture_2_maybe: the same code (dead in the original).
void CounterNode_SetDigitTextures_2(CNode* node, RwTexture* first, RwTexture* second);
// 0x00583878 CKCounterNodeFx_SetDigitUVs_maybe: the first geometry's quad shows the cell `frame` of a cols x rows atlas.
void CounterNode_SetDigitUVs(CNode* node, uint8_t cols, uint8_t rows, uint8_t frame);
// 0x005845f8 CKCounterNodeFx_UpdateRadialGaugeGeometry_maybe: the first geometry's fan shows `fill` (0..1) of a circle
// from the Y axis, its texture coordinates in the atlas cell `frame` of cols x rows.
void CounterNode_UpdateRadialGauge(CNode* node, float fill, uint8_t cols, uint8_t rows, uint8_t frame);
// 0x005835c8 Mat4_InterpolateSlerp_maybe: out = a .. b at t (rotation slerped, position lerped; dead in the original).
void Mat4_InterpolateSlerp(float t, const CMatrix34* a, const CMatrix34* b, CMatrix34* out);
// 0x00583df8 Vec3_ProjectOntoPlaneOfVectors_maybe: `p` onto the plane spanned by `a` and `b` (dead in the original).
void Vec3_ProjectOntoPlaneOfVectors(CVector3* out, const CVector3* a, const CVector3* b, const CVector3* p);
// 0x00585220 Vec2_RotateNormalized_maybe: the 2D vector turned by `angle` and normalised (dead in the original).
void Vec2_RotateNormalized(float angle, float* v);
