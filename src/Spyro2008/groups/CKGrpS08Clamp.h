// CKGrpS08Clamp.h - the clamp group (key 0xc04, vtable 0xb27fe0, size 0x4c). Original unit:
// CKGrpS08Clamp.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/memory/KObjectRefList.h"
#include "k2000/memory/Mem.h"

class CKGrpS08Clamp : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x30)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c4be8
        return key == 0xc04 || key == 0x17e || key == 0x4 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGrpS08Clamp)

    // 0x00491f78 CKGrpS08Clamp_Create (the constructor 0x491748 inlined): the list zeroed.
    CKGrpS08Clamp() {
        m_list.m_pBlock = nullptr;
        m_list.m_pHead = nullptr;
        m_list.m_ui32Count = 0;
        m_list.m_ui32Count2 = 0;
    }

    // 0x00492320 CKGrpS08Clamp_Destructor: the list's block freed (Mem_FreeAligned16) and cleared, its count (+0x30) 0.
    ~CKGrpS08Clamp() override {
        if (m_list.m_pBlock != nullptr) {
            Mem_FreeAligned16(m_list.m_pBlock);
            m_list.m_pBlock = nullptr;
        }
        m_list.m_pHead = nullptr;
    }
    // vt+0x10 0x00491f18 CKGrpS08Clamp_Destroy: no child groups (+0x18), no members (vt+0xb0's head).
    void Destroy() override {
        m_lChilds = nullptr;
        *GetMemberListHead() = nullptr;  // vt+0xb0: this + 0x28
    }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00492170 CKGrpS08Clamp_Load
    // vt+0x30 0x00491888 CKGrpS08Clamp_PostLoad: IKLife_PostLoad 0x19f68, then 1.
    int32_t PostLoad(int32_t type) override {
        PostLoadLife(type);
        return 1;
    }
    void Start() override;  // vt+0x50 0x00491cf0 CKGrpS08Clamp_Start (C2.2)
    void Restart() override;  // vt+0x54 0x00491d90 CKGrpS08Clamp_Restart
    // 0x00491938 CKHkS08Clamp_SpawnFx_maybe (this = the group): a free pooled effect of the FX data +0x44 reserved for
    // `owner`, started, put at `position` and triggered (CKSrvFx::AcquireFx inlined; the reservation is kept). The
    // clamp passes its +0xf0 as a second argument the code never reads.
    void SpawnClampFx(const IKSerializable* owner, const CVector3* position);
    // port-all P22:
    // vt+0x1c 0x00491dc8 CKGrpS08Clamp_MessageProc: 0x997 with a target (the message's first word: its +0x04 a
    // position): a free clamp of the pool (+0x2c) put in state 1 at that position (its node's frame the identity, then
    // the modelling position, the identity bit cleared, the frame dirtied); 0 for 0x997, 1 for the others.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x00491ef0 CKGrpS08Clamp_RecursiveRegistration: IKGroup's (0x12a68) only, inherited. vt+0xb8 0x004917c0
    // CKGrpS08Clamp_vfB8 returns 0xb: IKBaseGroup models no slot there and no ported code calls it.
    // 0x00491ba0 CKHkS08ClampGun_ReturnClampToPool_maybe (this = the group): `clamp` in state 3, back among the free ones
    // (KObjectRefList::SwapIntoActivePartition).
    void ReturnClampToPool(IKSerializable* clamp);
    // 0x00491bf8 CKGrpS08Clamp_TakeFreeClamp_maybe: the pool's last free clamp (KObjectRefList::PopBack), null without.
    IKSerializable* TakeFreeClamp() { return m_list.PopBack(); }

    KObjectRefList m_list;     // +0x2c (LVL010: hook refs of key 0x2c82)
    uint32_t m_unk3c;          // +0x3c not set by the constructor or the Load
    IKSerializable* m_pUnk40;  // +0x40 reference
    IKSerializable* m_pUnk44;  // +0x44 reference (the FX data of SpawnClampFx)
    IKSerializable* m_pUnk48;  // +0x48 reference
};
DOTD_ASSERT_SIZE(CKGrpS08Clamp, 0x4c);
DOTD_ASSERT_OFFSET(CKGrpS08Clamp, m_list, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpS08Clamp, m_pUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKGrpS08Clamp, m_pUnk48, 0x48);
