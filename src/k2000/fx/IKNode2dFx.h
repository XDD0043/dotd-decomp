// IKNode2dFx.h - an effect on a 2D node (key 0x158c, not registered; vtable 0xb1dd50; Ghidra calls it
// CKNode2dFx).
// Original unit: CKNode2dFx.cpp (0x1d84f0-0x1d8898). XXL2: K/KServices/KServiceFx/Effects/IKNode2dFx.h,
// member m_pNode.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKFx.h"

class IKNode2dFx : public IKFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x56)

    IKNode2dFx();  // 0x001d8840 CKNode2dFx_ConstructBase
    ~IKNode2dFx() override {}

    // vt+0x10 0x001d8508 CKNode2dFx_ClearReferences (Destroy): the node reference cleared (not IKFx's).
    void Destroy() override { m_pNode = nullptr; }
    // vt+0x24 0x001d8518 CKNode2dFx_LevelReset (RecursiveRegistration): the node's (its vt+0x24), when set; the effect
    // itself is not registered here (its subclasses register first, then call this).
    void RecursiveRegistration(int32_t type) override {
        if (m_pNode != nullptr) m_pNode->RecursiveRegistration(type);
    }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d85a8 CKNode2dFx_Load
    // vt+0x54 0x001d8858 CKNode2dFx_ReleaseReservation and vt+0x58 0x001d8768 CKNode2dFx_StopAndRelease are the 2D
    // unit's own copies of IKFx's (XXL2 IKNode2dFx::UnLockFx / ReleaseFx): the same tests and stores (the
    // reservation bit cleared through a rlwinm pair that keeps bit 0), so IKFx's bodies serve.
    // vt+0x5c 0x001d8570 CKNode2dFx_ShowSceneNode (XXL2 IKNode2dFx::Show): the node added to the 2D manager's scene
    // +0xa68 (CScene2d_AddChild_Thunk 0x65468).
    void Vf5C() override;
    // vt+0x60 0x001d8808 CKNode2dFx_HideSceneNode (XXL2 Hide): the node taken off that scene (0x650d8).
    void Vf60() override;
    // vt+0x64 0x009ad9a0 CKNode2dFx_Start [inline] (XXL2 StartFx): running and reserved (bits 0 / 1 = 0 / 1).
    void Vf64() override { m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfc) | 2); }
    // vt+0x6c 0x009ad980 CKNode2dFx_Stop: stopped and not reserved.
    void Stop() override { m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfc) | 1); }

    IKSerializable* m_pNode;  // +0x10 XXL2 IKNode2d* (LVL000: CBillboard2d); the constructor sets 0
};
static_assert(IKNode2dFx::kClassKey == 0x158c, "key");
DOTD_ASSERT_SIZE(IKNode2dFx, 0x14);
DOTD_ASSERT_OFFSET(IKNode2dFx, m_pNode, 0x10);
