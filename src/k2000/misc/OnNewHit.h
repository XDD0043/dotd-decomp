// OnNewHit.h - the game manager's combo hit counter (OnNewHit.cpp).
#pragma once
#include <cstdint>

#include "k2000/math/CMatrix34.h"

class CKS08GameManager;

// 0x004fe428 OnNewHit: one more hit in the dragon's combo (the counter, its timer, the HUD).
void OnNewHit(CKS08GameManager* manager, uint8_t dragon, CVector3 point);
// 0x004fe568 OnNewHitW: OnNewHit taking the point by address.
void OnNewHitW(CKS08GameManager* manager, uint8_t dragon, const CVector3* point);
