// CKFireBallNodeFx.h - the fire-ball effect (key 0x33cc, vtable 0xb1cc58, size 0x38): a textured node that follows a
// projectile (CKProjectileTypeBallisticPFX, data flag 0x1000), scrolls its UV, turns with the flight, fades in and out
// and can drive a trail particle node. Original unit: CKFireBallNodeFx.cpp (0x1ba218-0x1bb408). Its data is
// CKFireBallFxData (0x338c). Not in XXL2; names ours. No game file holds the class (C2.8 port-rest R06).
//
// m_baFxData bits (IKFx's byte, read whole from the file by the Load): 0 stopped, 1 reserved, 2 fading in, 3 fading out
// (RequestStopForOwner), 4 follows the hot spot (+0x34; SetFollowNode clears it), 5 no trail particles, 6 the trail
// particles emit and follow.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

class CKFireBallFxData;
class CParticlesNodeFx;
class CSGHotSpot;
class CSGMovable;

class CKFireBallNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xcf)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ac0d8
        return key == 0x33cc || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKFireBallNodeFx)

    CKFireBallNodeFx() {}            // inlined in 0x001ba4d8 CKFireBallNodeFx_Create: the IKNodeFx part, the vtable
    ~CKFireBallNodeFx() override {}  // 0x009ac130 / 0x009ac150: the vtables only

    void Destroy() override { IKNodeFx::Destroy(); }  // vt+0x10 0x001ba408: CKNodeFx3d_Destroy (no node)
    // vt+0x24 0x001ba348 CKFireBallNodeFx_RecursiveRegistration: the saving manager's registration, IKNodeFx's (the node),
    // then the trail particles' when set.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001baa80 CKFireBallNodeFx_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x001ba2f0 CKFireBallNodeFx_PostLoad
    void Vf64() override;                               // vt+0x64 0x001ba958 CKFireBallNodeFx_Start
    void Stop() override;                               // vt+0x6c 0x001ba828 CKFireBallNodeFx_Stop
    void Update(IKTime* frameClock) override;           // vt+0x78 0x001babb8 CKFireBallNodeFx_Update
    IKFxData* GetFxData() override;                     // vt+0x80 0x009ac120 (+0x14)
    void SetFxData(IKFxData* data) override;            // vt+0x84 0x009ac128 (+0x14)

    // 0x001ba530 CKFireBallNodeFx_RequestStopForOwner_maybe: a reserved effect of this owner starts fading out (bit 3).
    void RequestStopForOwner(const IKSerializable* owner);
    // 0x001ba5a8 CKFireBallNodeFx_SetFollowNode: a reserved effect of this owner follows `node` (bit 4 cleared).
    void SetFollowNode(CSGMovable* node, const IKSerializable* owner);
    // 0x001ba5e0 CKFireBallNodeFx_SetDirection: a reserved effect of this owner points along -dir.
    void SetDirection(const CVector3* dir, const IKSerializable* owner);

    CKFireBallFxData* m_pData;      // +0x14 not set by the constructor or Load
    CSGMovable* m_pFollowNode;      // +0x18 PostLoad, Start and Stop set 0
    CVector3 m_vDirection;          // +0x1c the node's up axis (negated by SetDirection); (0, 0, 0): follow the matrix
    CParticlesNodeFx* m_pParticles; // +0x28 a reference (level files): the trail particles
    uint32_t m_unk2c;               // +0x2c a byte-swapped word (level files); not read in this unit
    uint8_t m_ui8Alpha;             // +0x30 the geometry's alpha (Start 0; the fades step it)
    uint8_t m_pad31[3];
    CSGHotSpot* m_pHotSpot;         // +0x34 Start and Stop set 0
};
static_assert(CKFireBallNodeFx::kClassKey == 0x33cc, "key");
DOTD_ASSERT_SIZE(CKFireBallNodeFx, 0x38);
DOTD_ASSERT_OFFSET(CKFireBallNodeFx, m_pData, 0x14);
DOTD_ASSERT_OFFSET(CKFireBallNodeFx, m_pFollowNode, 0x18);
DOTD_ASSERT_OFFSET(CKFireBallNodeFx, m_vDirection, 0x1c);
DOTD_ASSERT_OFFSET(CKFireBallNodeFx, m_pParticles, 0x28);
DOTD_ASSERT_OFFSET(CKFireBallNodeFx, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKFireBallNodeFx, m_ui8Alpha, 0x30);
DOTD_ASSERT_OFFSET(CKFireBallNodeFx, m_pHotSpot, 0x34);
