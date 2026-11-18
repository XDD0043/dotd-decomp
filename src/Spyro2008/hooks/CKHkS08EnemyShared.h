// CKHkS08EnemyShared.h - helpers the enemy units share (C2.7): the enemy and hero groups (the original's GetEnemyGroup /
// GetHeroGroup), CKGrpS08Enemy's per-kind constants and the squad's fight-zone index.
//
// CKGrpS08Enemy answers its per-kind virtuals (vt+0x104..+0x140, inline copies 0x9bb4e8..0x9bb5f8) from one table,
// 0x00a6fec8 (TOC1 +0x504), 16 bytes per row and one byte per kind (nine kinds). CKGrpS08Enemy is the only enemy group,
// so DOTD reads the table directly (the same values as the virtual calls).
#pragma once
#include <cmath>
#include <cstdint>


#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGrpEnemy.h"

namespace enemy {

// 0x00a6fec8 (the 0x110 bytes from there; the last row is the next object's).
inline constexpr uint8_t kGrpKindTable[0x110] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // +0x00
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // +0x10
    0x32, 0x38, 0x36, 0x3a, 0x36, 0x36, 0x34, 0x33, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // +0x20
    0x07, 0x0a, 0x0e, 0x0d, 0x0e, 0x11, 0x19, 0x11, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // +0x30
    0x04, 0x05, 0x0a, 0x09, 0x0a, 0x0e, 0x10, 0x05, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // +0x40
    0x02, 0x03, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // +0x50
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // +0x60
    0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // +0x70
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // +0x80
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // +0x90
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x01, 0x01, 0x02, 0x02,  // +0xa0
    0x02, 0x01, 0x07, 0x07, 0x02, 0x01, 0x07, 0x07, 0x01, 0x01, 0x07, 0x07, 0x02, 0x01, 0x0a, 0x0a,  // +0xb0
    0x03, 0x01, 0x0d, 0x0d, 0x02, 0x01, 0x02, 0x02, 0x02, 0x01, 0x06, 0x06, 0x02, 0x00, 0x01, 0x01,  // +0xc0
    0x03, 0x00, 0x01, 0x01, 0x03, 0x00, 0x01, 0x01, 0x08, 0x00, 0x01, 0x01, 0x08, 0x00, 0x01, 0x01,  // +0xd0
    0x08, 0x00, 0x01, 0x01, 0x0b, 0x00, 0x01, 0x01, 0x0e, 0x00, 0x01, 0x01, 0x03, 0x00, 0x01, 0x01,  // +0xe0
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // +0xf0
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0x00, 0x00, 0x00, 0x9b, 0x00, 0x00, 0x00, 0x9b,  // +0x100
};

// Per enemy kind, the weapon kinds it can hold (= the enemy group's weapon pool indices, +0x180) and their number. Two
// copies in the EBOOT with the same values: 0x00a70170 / 0x00b00fc8 (TOC +0xf78 +0x30 / +0xfac: AttachRandomWeapon,
// CanSpawnFromSquad) and 0x00a70220 / 0x00b00fec (TOC +0x1134 / +0x1138: FindFreeWeapon). Kind 1's list is a zero word
// nothing writes (0x00ceacfc / 0x00cead18).
inline constexpr uint32_t kWeaponPoolCount[9] = {1, 1, 2, 1, 1, 1, 2, 0, 0};
inline constexpr uint32_t kWeaponPools0[1] = {1};
inline constexpr uint32_t kWeaponPools1[1] = {0};
inline constexpr uint32_t kWeaponPools2[2] = {2, 8};
inline constexpr uint32_t kWeaponPools3[1] = {3};
inline constexpr uint32_t kWeaponPools4[1] = {4};
inline constexpr uint32_t kWeaponPools5[1] = {7};
inline constexpr uint32_t kWeaponPools6[2] = {5, 6};
inline constexpr const uint32_t* kWeaponPools[9] = {kWeaponPools0, kWeaponPools1, kWeaponPools2, kWeaponPools3,
                                                    kWeaponPools4, kWeaponPools5, kWeaponPools6, nullptr, nullptr};

// 0x00a70130 (TOC +0xee0) and 0x00a70300 (TOC +0x11ec +0xb8): per enemy kind, its number of hot spots (the same bytes
// as CKGrpS08Enemy's vt+0x114 row).
inline constexpr uint8_t kHotSpotCount[9] = {0x07, 0x0a, 0x0e, 0x0d, 0x0e, 0x11, 0x19, 0x11, 0x0c};

// 0x00c50d40 (TOC1 +0xa84 points at it): the Y axis (a run-time constant (0, 1, 0)).
inline constexpr CVector3 kAxisY = {0.0f, 1.0f, 0.0f};

// 0x00010690 Math_Sqrtf: the double square root rounded to float, as a double (the same as C22SpyroShims' copy).
inline double MathSqrtf(double x) { return static_cast<double>(static_cast<float>(std::sqrt(x))); }

// 0x00276f58 GetEnemyGroup: the game manager's +0x04 (the CKGrpS08Enemy).
inline IKGrpEnemy* EnemyGroup() { return static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]); }
// 0x00276f70 GetHeroGroup: the game manager's +0x08 (the CKGrpS08Hero).
inline IKSerializable* HeroGroup() { return g_pEngine->m_gameManager->m_unk04[1]; }

inline uint8_t GroupKindFlag104(uint8_t kind) { return kGrpKindTable[kind]; }          // vt+0x104 0x9bb4e8 (0)
inline uint8_t GroupNbAnimLayers(uint8_t kind) { return kGrpKindTable[0x10 + kind]; }  // vt+0x108 0x9bb4f8 (animated nodes)
inline uint8_t GroupNbSectorVolumes(uint8_t /*kind*/) { return 0; }                    // vt+0x10c 0x9bb508
inline uint8_t GroupKindByte110(uint8_t kind) { return kGrpKindTable[0x20 + kind]; }   // vt+0x110 0x9bb510
inline uint8_t GroupKindByte114(uint8_t kind) { return kGrpKindTable[0x30 + kind]; }   // vt+0x114 0x9bb520
inline uint8_t GroupNbVolumes(uint8_t kind) { return kGrpKindTable[0x40 + kind]; }     // vt+0x118 0x9bb530 (+0x2c)
inline uint8_t GroupNbDynSpheres(uint8_t kind) { return kGrpKindTable[0x50 + kind]; }  // vt+0x11c 0x9bb540 (+0x44)
inline uint8_t GroupNbAttachments(uint8_t kind) { return kGrpKindTable[0x60 + kind]; } // vt+0x120 0x9bb550 (0)
inline uint8_t GroupNbParticles(uint8_t kind) { return kGrpKindTable[0x70 + kind]; }   // vt+0x124 0x9bb560 (+0x54)
inline uint8_t GroupNbTrails(uint8_t kind) { return kGrpKindTable[0x80 + kind]; }      // vt+0x128 0x9bb570 (+0x5c)
inline uint8_t GroupNbFogBoxes(uint8_t kind) { return kGrpKindTable[0x90 + kind]; }    // vt+0x12c 0x9bb580 (+0x64; 0)
inline uint8_t GroupNbAnimLayerSlots(uint8_t kind, uint8_t layer) {                     // vt+0x130 0x9bb590
    return kGrpKindTable[0xa0 + kind + layer];
}
inline uint8_t GroupKindByte138(uint8_t kind, uint32_t i) { return kGrpKindTable[0xa9 + kind * 4 + i]; }  // vt+0x138 0x9bb5b0
inline uint8_t GroupKindByte13C(uint8_t kind, uint32_t i) { return kGrpKindTable[0xcd + kind * 4 + i]; }  // vt+0x13c 0x9bb5c8
inline uint8_t GroupKindByte140(uint8_t kind) { return kGrpKindTable[0xf8 + kind]; }   // vt+0x140 0x9bb5e0

// The squad's fight zone (the squad group's parent, +0x1c) and its +0x3c: the variant of the enemy's sector components
// (inlined by every caller of GetSectorIndex's logic).
inline uint32_t SquadFightZoneIndex(IKSerializable* squad) {
    return static_cast<CKGrpFightZone*>(static_cast<IKGroup<IKHook>*>(squad)->m_pParent)->m_unk3c;
}

}  // namespace enemy

class IKHkEnemy;
class AnimMark;
// CKHkS08Enemy_3.cpp: a mark's vt+0x14 as an integer (r3), the largest value over [t0, t1].
uint32_t AnimMark_RangeValueR3(AnimMark* mark, float t0, float t1);
// Free functions of CKHkS08Enemy.cpp (C2.7 fork C).
// 0x0027cda8 EvalRampHoldRampDown_maybe
uint8_t EvalRampHoldRampDown(float t, float rampEnd, float hold, float rampDown, float base, float slope, float downSlope,
                             float* out);
namespace enemy {
// The enemy unit's own copies (the hero's Vec3_AngleBetween 0x2fbbf8 is another function).
float Vec3_AngleBetween(CVector3* a, CVector3* b);                       // 0x0027eb88 (normalises both in place)
float Vec3_SignedAngleBetween(CVector3* a, CVector3* b, CVector3* side); // 0x0027efc0 (normalises all three in place)
// 0x0027d460 Vec3_ForwardFromYaw_maybe: `v` turned about the Y axis by `angle` radians (a zeroed matrix with `v` as its
// at row, Mat4_RotateInPlace by angle x 57.29578 degrees; its at row).
CVector3 Vec3_RotateAboutY(float angle, const CVector3* v);
}  // namespace enemy

CVector3 GetActiveEnemyCentroid();                                       // 0x0027df10

// xfork: owned by fork A (IKGrpEnemy.cpp). 0x00265a50 AddActiveEncounterEnemy: the enemy appended to the group's active
// list (+0x58, count +0x120). 0x00265a78 RemoveActiveEncounterEnemy: the enemy found is replaced by the last one.
void AddActiveEncounterEnemy(IKGrpEnemy* group, IKHkEnemy* enemy);
void RemoveActiveEncounterEnemy(IKGrpEnemy* group, IKHkEnemy* enemy);
