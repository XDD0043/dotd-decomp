// CKColossusAttackElement.h - the two hero-distance conditions at the head of the TU 0x9c4338.. (port-final F06).
// Original signature (owner, condition): the owner's hook (+0x04 for the radius test, +0x2c for the beyond test) and the
// condition's radius (+0x04). Callers: CKColossusAttackSequence vf6C 0x46d1e0 (case 3) and vf70 0x46d2e0 (F03 this round).
#pragma once

class IKHook;

// 0x009c4338 CKColossusAttackElement_IsSpyroWithinRadiusXZ_maybe: hero 0's node position against `hook`'s node position
// in XZ: dz * dz + (dx * dx + 0) < radius * radius (fmadds, TOC1 +0x587c = 0; blt: NaN gives 0).
bool ColossusCond_IsHeroWithinRadiusXZ(IKHook* hook, float radius);
// 0x009c43e8 CKColossusAttackElement_IsSpyroBeyondRadius_maybe: dz * dz + (dx * dx + dy * dy) > radius * radius
// (fmadds; bgt: NaN gives 0).
bool ColossusCond_IsHeroBeyondRadius(IKHook* hook, float radius);
