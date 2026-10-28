// GroundContact.h - the ground-contact pair the hooks embed (XXL2: CGroundContactDatasIn and
// CGroundContactDatasInOut, K/KServices/KServiceCollision). Same layout and constructor defaults as the
// copies nested in CKSrvCamera (+0x6c8): every hook constructor that embeds them sets masks {1, 8},
// ground 0, face -1, status 3, sector byte 0 (CKHkS08Weapon_Create 0x2b1198, CKHkS08Sparx_Construct
// 0x3f4158).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class IKSerializable;

struct CGroundContactDatasIn {         // 0x10
    float m_fDeltaMax;                 // +0x00
    float m_fObjectHeight;             // +0x04
    uint32_t m_MasksOfGrdForTest[2];   // +0x08 constructor 1, 8

    CGroundContactDatasIn() {
        m_MasksOfGrdForTest[0] = 1;
        m_MasksOfGrdForTest[1] = 8;
    }
};
DOTD_ASSERT_SIZE(CGroundContactDatasIn, 0x10);

struct CGroundContactDatasInOut {      // 0x2c
    IKSerializable* m_pGround;         // +0x00 CGround*; constructor 0
    int32_t m_i32FaceIndex;            // +0x04 constructor -1
    CVector3 m_Normal;                 // +0x08
    uint32_t m_eContactStatus;         // +0x14 constructor 3
    CVector3 m_ProjectionOnGround;     // +0x18
    float m_fdH;                       // +0x24
    uint8_t m_ui8SectorNumber;         // +0x28 constructor 0
    uint8_t m_pad29[3];

    CGroundContactDatasInOut() {
        m_ui8SectorNumber = 0;
        m_eContactStatus = 3;
        m_pGround = nullptr;
        m_i32FaceIndex = -1;
    }
};
DOTD_ASSERT_SIZE(CGroundContactDatasInOut, 0x2c);

// The contact helpers (XXL2 CGroundContactDatasInOut methods; original unit CKSrvDetect.cpp, the last one Math.cpp).
// 0x001a7090 GroundContact_GetTriangle_maybe (XXL2 GetGroundFace): the contact's face (three vertex indices) when it
// has a ground and a face index below the ground's triangle count, else null.
const uint16_t* GroundContact_GetTriangle(const CGroundContactDatasInOut* contact);
// 0x001a70e0 GroundContact_GetWorldPoint (XXL2 ComputeWorldProjectionOnGround): the projection, through the ground's
// world matrix for a moving ground (class id 0x13, CDynamicGround). The contact must have a ground.
void GroundContact_GetWorldPoint(const CGroundContactDatasInOut* contact, CVector3* out);
// 0x001a71d8 GroundContact_GetWorldNormal_maybe (XXL2 ComputeWorldNormalOfGroundFace): the normal, turned by a
// moving ground's world matrix.
void GroundContact_GetWorldNormal(const CGroundContactDatasInOut* contact, CVector3* out);
// 0x00582e08 GroundContact_GetWorldPoint_maybe: GroundContact_GetWorldPoint, or `fallback` without a ground.
void GroundContact_GetWorldPointOr(const CGroundContactDatasInOut* contact, const CVector3* fallback, CVector3* out);

// A ground contact copied member by member, in the original's order (the padding after the sector byte is not copied).
inline void CopyGroundContact(CGroundContactDatasInOut& to, const CGroundContactDatasInOut& from) {
    to.m_pGround = from.m_pGround;
    to.m_i32FaceIndex = from.m_i32FaceIndex;
    to.m_Normal.x = from.m_Normal.x;
    to.m_Normal.z = from.m_Normal.z;
    to.m_Normal.y = from.m_Normal.y;
    to.m_eContactStatus = from.m_eContactStatus;
    to.m_fdH = from.m_fdH;
    to.m_ProjectionOnGround.x = from.m_ProjectionOnGround.x;
    to.m_ProjectionOnGround.z = from.m_ProjectionOnGround.z;
    to.m_ProjectionOnGround.y = from.m_ProjectionOnGround.y;
    to.m_ui8SectorNumber = from.m_ui8SectorNumber;
}
