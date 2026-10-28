// IKBaseGroup.h - base of the groups (key 0x4; XXL2: K/KCore/Interfaces/IKBaseGroup.h) and the
// IKGroup<T> template (key 0x17e for every T: IKGroup<IKHook>, IKGroup<IKHkBonus>, IKGroup<IKHkEnemy>).
//
// PS3 layout: IKLife (0x14) + XXL2's CSBaseNode<IKBaseGroup*> (+0x14) + m_lChilds (+0x18) + m_pParent,
// m_pGroupLife, m_pKBundle (+0x1c..+0x24); IKGroup<T> adds m_lHooks (+0x28).
//
// GroupBasicLoad's original (0x12ce8, Ghidra IKGroup_Load) is in the core TU CKCoreError.cpp; it is inline
// here so that the group classes of every family can use it.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/hooks/IKLife.h"
#include "k2000/io/IKFile.h"

class IKBaseGroup : public IKLife {
public:
    // Inlined in every Create (CKGroupRoot_Create 0x22a58).
    IKBaseGroup() {
        m_pNextGroup = nullptr;
        m_lChilds = nullptr;
        m_pParent = nullptr;
        m_pKBundle = nullptr;
        m_pGroupLife = nullptr;
    }

    // The IKUpdatable pure slots: empty in the groups' vtables (CKGroupRoot 0xb13990).
    void Start() override {}           // vt+0x50 0x990f88
    void Stop() override {}            // vt+0x68 0x990f98
    void Pause() override {}           // vt+0x70 0x990fa0
    void Resume() override {}          // vt+0x78 0x990fa8
    void Update(IKTime*) override {}   // vt+0x7c 0x990fb0

    virtual void Vf94() {}                 // vt+0x94 0x990c78 (empty; arguments unverified)
    virtual void Vf98() {}                 // vt+0x98 0x990c80 (empty; arguments unverified)
    virtual int32_t Vf9C() { return -1; }  // vt+0x9c 0x12960 IKGroup_vf9C
    virtual void VfA0() {}                 // vt+0xa0 0x990c88 (empty; arguments unverified)
    virtual void VfA4() {}                 // vt+0xa4 0x990c90
    // vt+0xa8 / +0xac 0x990c98 / 0x990ca0 (empty): IKLife::OnLock / OnUnlock (the hooks' own).
    // vt+0xb0 (IKGroup<T>: 0x992d50 IKGroup_GetMemberListHead, this + 0x28). XXL2 slot 41 (vt 0x148).
    virtual IKSerializable** GetMemberListHead() = 0;

    // 0x00012ce8 IKGroup_Load (XXL2 IKBaseGroup::GroupBasicLoad: the same reads in the same order).
    int32_t GroupBasicLoad(IKFile* file, int32_t type) {
        IKLife::Load(file, type);
        if (type != K_LEVEL_PLATEFORMS) return 1;
        IKFile_ReadRef(file, &m_pNextGroup);
        IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(&m_pParent), 3);  // +0x1c..+0x24
        IKFile_ReadRef(file, &m_lChilds);
        IKFile_ReadObjectRef(file, GetMemberListHead());  // vt+0xb0
        return 1;
    }

    IKBaseGroup* m_pNextGroup;   // +0x14 XXL2 CSBaseNode<IKBaseGroup*>::m_pNext
    IKBaseGroup* m_lChilds;      // +0x18 XXL2 GroupeList m_lChilds (its head)
    IKBaseGroup* m_pParent;      // +0x1c XXL2 m_pParent
    IKSerializable* m_pGroupLife;  // +0x20 XXL2 IKGroupLife* m_pGroupLife
    IKSerializable* m_pKBundle;    // +0x24 XXL2 CKBundle* m_pKBundle
};
DOTD_ASSERT_SIZE(IKBaseGroup, 0x28);
DOTD_ASSERT_OFFSET(IKBaseGroup, m_pNextGroup, 0x14);
DOTD_ASSERT_OFFSET(IKBaseGroup, m_lChilds, 0x18);
DOTD_ASSERT_OFFSET(IKBaseGroup, m_pParent, 0x1c);
DOTD_ASSERT_OFFSET(IKBaseGroup, m_pKBundle, 0x24);

// IKGroup<T> (XXL2 IKGroup<IKHook>: m_lHooks, a HookList).
template <class T>
class IKGroup : public IKBaseGroup {
public:
    IKGroup() { m_lHooks = nullptr; }
    IKSerializable** GetMemberListHead() override {  // vt+0xb0 0x992d50
        return reinterpret_cast<IKSerializable**>(&m_lHooks);
    }
    T* m_lHooks;  // +0x28 XXL2 HookList m_lHooks (its head)
};
