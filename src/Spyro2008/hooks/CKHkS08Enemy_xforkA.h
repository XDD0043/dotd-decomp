// CKHkS08Enemy_xforkA.h - DOTD (C2.7 enemy family, fork A): functions of other files the fight zones, squads and the
// enemy group call, declared here until their owners port them (stubs in CKHkS08Enemy_xforkA.cpp). To be merged into
// their real homes; each one names its original.
#pragma once
#include <cstdint>

class IKSerializable;
class IKTime;

// 0x002c78e0 CKS08AccessoryManager_UpdateActiveItems_maybe (vt+0x5c of CKS08AccessoryManager): the accessory manager's
// frame (UpdateCKGrpS08Enemy calls it every frame).
void CKS08AccessoryManager_UpdateActiveItems(IKSerializable* manager, IKTime* clock);
// CKHkS08Weapon vt+0xc8 then vt+0xcc (CKGrpS08Enemy_vf160 0x2681d0 calls them on every weapon of the pool whose
// byte +0xa8 is 0 when a fight ends).
void CKHkS08Weapon_ReleaseAtFightEnd(IKSerializable* weapon);
