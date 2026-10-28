// IKHook.h - base of every hook (key 0x2, vtable 0xb132f0, size 0x20; XXL2: K/KCore/Interfaces/IKHook.h).
//
// PS3 layout: IKLife (0x14) + XXL2's CSBaseNode<IKHook*> (+0x14 m_pNext, the group's hook list) +
// m_pHookLife (+0x18) + m_pKGLObject (+0x1c). XXL2's m_pEntity and m_pLockableEntityCpnt are not in the
// PS3 build (every hook Create sets +0x14..+0x1c to 0 and nothing more of the base).
//
// The Load body is inline here: its original sits in the CDefaultGameManager.cpp TU (0x19900), and the
// hook classes of several families need it.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKLife.h"
#include "k2000/io/IKFile.h"

class AnimBlendSlot;

class IKHook : public IKLife {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x0)

    // Inlined in every hook Create (CKHkS08Shield_Create 0x2ac5d8: +0x18, +0x14, +0x1c = 0).
    IKHook() {
        m_pHookLife = nullptr;
        m_pNextHook = nullptr;
        m_pKGLObject = nullptr;
    }
    ~IKHook() override {}

    // vt+0x2c 0x00019900 CKHook_Load (out-of-line copy 0x992690). XXL2 IKHook::HookBasicLoad reads the
    // same: IKLife's part, then m_pNext through ReadHandle and m_pHookLife/m_pKGLObject through one
    // ReadContiguousHandles of 2.
    int32_t Load(IKFile* file, int32_t type) override {
        IKLife::Load(file, type);
        if (type != K_LEVEL_PLATEFORMS) return 1;
        IKFile_ReadRef(file, &m_pNextHook);
        IKFile_ReadObjectRefArray(file, &m_pHookLife, 2);
        return 1;
    }

    // The IKUpdatable slots IKHook fills with empty bodies.
    void Start() override {}              // vt+0x50 0x992640 KStub_Nop_992640
    void Stop() override {}               // vt+0x68 0x992650 KStub_Nop_992650
    void Pause() override {}              // vt+0x70 0x992658 KStub_Nop_992658
    void Resume() override {}             // vt+0x78 0x992660 KStub_Nop_992660
    void Update(IKTime*) override {}      // vt+0x7c 0x992668 KStub_Nop_992668

    // vt+0xb0 (XXL2 IKHook::GetComponent(UInt32 key) at slot 41, shifted by DotD's 0x18): the hook's component of
    // that class key, or null. 0x992670 KStub_Return0 for most hooks; CKHkS08Hero 0x344d30 and
    // CKHkMovableCharacter 0x59df38 override it. (DotD adds nothing between +0xa8 and +0xb0.)
    virtual IKSerializable* GetComponent(uint32_t /*key*/) { return nullptr; }
    // vt+0xbc 0x00019a90 IKHook_vfBC: the hook's node's blend slot (CAnimatedNode_GetBlendSlot_maybe): *count 1 and *slot
    // for a node with one, 0 for a single controller. (The cinematic blocs' access to an actor's animation.)
    virtual void GetBlendSlot(AnimBlendSlot** slot, int32_t* count);
    IKHook* m_pNextHook;                  // +0x14 XXL2 CSBaseNode<IKHook*>::m_pNext (the group's hook list)
    // +0x18 / +0x1c are read as one array of two references (they must stay adjacent).
    IKSerializable* m_pHookLife;          // +0x18 XXL2 IKHookLife* m_pHookLife
    IKSerializable* m_pKGLObject;         // +0x1c XXL2 m_pKGLObject (the hook's scene node: PostLoads set its flags)
};
DOTD_ASSERT_SIZE(IKHook, 0x20);
DOTD_ASSERT_OFFSET(IKHook, m_pNextHook, 0x14);
DOTD_ASSERT_OFFSET(IKHook, m_pHookLife, 0x18);
DOTD_ASSERT_OFFSET(IKHook, m_pKGLObject, 0x1c);
