// CKHkS08SpawnableMushroom.h - a mushroom spawned by CKGrpS08SpawnableMushroom (key 0x3342, vtable 0xb2a168,
// size 0x60). Original unit: CKHkS08SpawnableMushroom.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "Spyro2008/groups/KBase42C2.h"
#include "k2000/core/Layout.h"

class CKHkS08SpawnableMushroom : public KBase42C2 {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xcd)
    DOTD_DECLARE_FACTORIES(CKHkS08SpawnableMushroom)

    // 0x004d89b0 CKHkS08SpawnableMushroom_Construct (inlined in 0x004d9088 CKHkS08SpawnableMushroom_Create):
    // KBase42C2's part, then +0x58 = 0.
    CKHkS08SpawnableMushroom() { m_unk58 = 0; }
    ~CKHkS08SpawnableMushroom() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004d9a98 CKHkS08SpawnableMushroom_Load
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x004d8490 CKHkS08SpawnableMushroom_PostLoad
    void Start() override;  // vt+0x50 0x004d8468 CKHkS08SpawnableMushroom_Start (C2.2)

    uint32_t m_unk34[4];         // +0x34..+0x43 not set by the constructor or Load
    void* m_pUnk44;              // +0x44 PostLoad: RwMatrixCreate
    void* m_pUnk48;              // +0x48 PostLoad: RwMatrixCreate
    IKSerializable* m_pUnk4C;    // +0x4c
    IKSerializable* m_pUnk50;    // +0x50
    IKSerializable* m_pUnk54;    // +0x54
    uint32_t m_unk58;            // +0x58 constructor 0
    IKSerializable* m_pUnk5C;    // +0x5c
};
DOTD_ASSERT_SIZE(CKHkS08SpawnableMushroom, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08SpawnableMushroom, m_pUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08SpawnableMushroom, m_pUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08SpawnableMushroom, m_pUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08SpawnableMushroom, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkS08SpawnableMushroom, m_pUnk5C, 0x5c);
