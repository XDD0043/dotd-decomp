// CKHkMecaGround.h - a mechanism's ground hook (key 0x2dc2, vtable 0xb2a568, size 0x2c). Original unit:
// CKHkMecaGround.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"

class CKHkMecaGround : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb7)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c6390
        return key == 0x2dc2 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkMecaGround)

    // A node of the +0x28 reference list (8 bytes, FreeListPool at 0x00ceaa20 in the original).
    struct RefNode {
        IKSerializable* m_pObject;  // +0x00
        RefNode* m_pNext;           // +0x04
    };

    // 0x004e12f8 CKHkMecaGround_Create (Construct 0x4e0fe0): the CKHkActorBase defaults, then +0x28 = 0.
    CKHkMecaGround() { m_pRefList = nullptr; }  // 0x004e0fa0 CKHkMecaGround_Construct_2: the same
    // 0x004e0f28 CKHkMecaGround_Destructor (= 0x004e10c0 Destructor_2; 0x004e1138 the deleting form): the list's nodes
    // back to the pool (FreeListPool 0x00ceaa20), +0x28 = 0, then the actor base's destructor.
    ~CKHkMecaGround() override { FreeRefList(); }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004e1358 CKHkMecaGround_Load
    // vt+0x1c 0x004e0c18 CKHkMecaGround_MessageProc: the actor base's answer merged (3 and 2 stay, 0 stays, else 1).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x40 0x004e0c70 CKHkMecaGround_GetInfo: the actor base's answer (KStub_Return1 0x3f7140) merged.
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;
    // vt+0x38 0x004e0cc0 CKHkMecaGround_SetDefaultState: the actor base's (empty), then flag 0 sets +0x24 = 1.
    void SetDefaultState(int32_t flag) override;
    // vt+0x50 0x004e0e30 CKHkMecaGround_Start: the actor base's (empty), then vt+0x54 (Restart).
    void Start() override;
    // vt+0x54 0x004e0b28 CKHkMecaGround_Restart: unless bit 2 of +0x0c (m_bitArray), vt+0xcc (SetEnabled) with +0x24.
    void Restart() override;
    // vt+0xa0 0x004e0d60 CKHkMecaGround_OnActivate: the actor base's, then vt+0xcc (SetEnabled) with +0x24.
    void VfA0() override;
    // vt+0xc8 0x004e0b80 CKHkMecaGround_vfC8: +0x24 = !state (xori 1).
    void ApplyStatePreset(int32_t state) override { m_unk24 = static_cast<uint8_t>(state ^ 1); }

    // vt+0xcc 0x004e11c0 CKHkMecaGround_SetEnabled: +0x24 = `enabled`, the ground (+0x20) and the listed ones (+0x28)
    // switched (ICollisionMesh_SetActive).
    void SetEnabled(int32_t enabled) override;

    IKSerializable* m_unk20;  // +0x20
    uint8_t m_unk24;          // +0x24 runtime (not set by Create or Load): SetEnabled
    uint8_t m_pad25[3];
    RefNode* m_pRefList;      // +0x28 the list head: Load pushes each read reference at the head

private:
    void FreeRefList() {
        RefNode* node = m_pRefList;
        while (node != nullptr) {
            RefNode* next = node->m_pNext;
            delete node;
            node = next;
        }
        m_pRefList = nullptr;
    }
};
DOTD_ASSERT_SIZE(CKHkMecaGround, 0x2c);
DOTD_ASSERT_OFFSET(CKHkMecaGround, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkMecaGround, m_pRefList, 0x28);
