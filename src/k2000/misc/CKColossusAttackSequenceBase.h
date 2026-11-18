// CKColossusAttackSequenceBase.h - the colossus attack sequences' unregistered base (key 0x7c0c, vtable 0xb27708,
// 31 slots, size 0x18). Its out-of-line methods are in CKColossusAttackSequenceBase.cpp (0x470388-0x470778);
// CKColossusAttackSequence (0x7c8c, its first own member at +0x18) derives from it. No XXL2 class; names ours.
//
// C2.8 port-rest R08 (the base's owner) wrote the whole class; R06's minimal version (the slots +0x50..+0x68 and the
// members CKColossusSequenceManager's PostLoad sets) is the same class under the same names.
//
// A sequence lives in a CKColossusSequenceManager's list: the manager's PostLoad 0x46b568 gives it the colossus hook
// (+0x04), its place in the list (+0x0c, over the value the Load read) and the manager (+0x08). The manager starts it
// (vt+0x50, the timer restarted), stops it (vt+0x54), runs it every frame (vt+0x60, the timer advances), asks it
// whether it is over (vt+0x64) and which way to go next (vt+0x68).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/system/IKTime.h"

class CKColossusSequenceManager;
class IKFile;

class CKColossusAttackSequenceBase : public IKSerializable {
public:
    // vt+0x14 / +0x18 0x9c4530 / 0x9c4538: category 0xc (logic), id 0x1f0.
    DOTD_CLASS_KEY(kCategoryLogic, 0x1f0)
    // vt+0x08 0x9c4558 CKColossusAttackSequenceBase_7c0c_maybe_vf8: 0x7c0c or 0xc.
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x7c0c || key == 0xc; }

    // 0x00470410 CKColossusAttackSequence_ConstructBase_maybe (the dead 0x470388 _ConstructBase_2 copy): the vtable
    // only; the members are what the fresh heap leaves (zero).
    CKColossusAttackSequenceBase() {}
    // 0x00470680 _vf0 (= 0x470698 _BaseDestructor; 0x470640 _DeletingDestructor adds the operator delete 0xa3ce18):
    // the base vtables only.
    ~CKColossusAttackSequenceBase() override {}

    // vt+0x10 0x470478 KStub_Nop_470478 (the sequences' Destroy calls it first): empty.
    void Destroy() override {}
    // vt+0x24 0x470470 _vf24 (li r3,1): nothing to register.
    void RecursiveRegistration(int32_t /*type*/) override {}
    // vt+0x28 0x470420 _vf28: nothing saved, 1.
    int32_t Save(IKFile* /*file*/, int32_t /*type*/) override { return 1; }
    // vt+0x2c 0x00470560 _vf2C (= the non-virtual copy 0x470480 _vf2C_2 the sequences' Load calls first): with a
    // level file (type 0) two words, +0x0c then +0x14 (each read, then byte-swapped); 1.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x00470428 _vf30: vt+0x78 (the timer cleared), 1.
    int32_t PostLoad(int32_t /*type*/) override {
        Vf78();
        return 1;
    }

    virtual void Vf50() { m_fTimer = 0.0f; }  // vt+0x50 0x00470400 _vf50: the timer restarted (stw 0, the sequence's start)
    virtual void Vf54() {}                    // vt+0x54 0x009c4540 (the sequence's stop)
    virtual void Vf58() {}                    // vt+0x58 0x009c4548
    virtual void Vf5C() {}                    // vt+0x5c 0x009c4550
    // vt+0x60 0x004703e8 _vf60: the timer advances by the clock's IKTime +0x1c (fadds).
    virtual void Vf60(IKTime* frameClock) { m_fTimer = m_fTimer + frameClock->m_afDeltaTime[0]; }
    virtual uint8_t Vf64() = 0;           // vt+0x64 pure: the sequence is over (CKColossusAttackSequence 0x46d198: vt+0x6c)
    virtual uint8_t Vf68() { return 1; }  // vt+0x68 0x009c41f8: 1 = go on to the next sequence, 0 = back to the previous
    virtual uint8_t Vf6C() = 0;           // vt+0x6c pure (CKColossusAttackSequence 0x46d1e0: its end condition)
    virtual void Vf70() = 0;              // vt+0x70 pure (CKColossusAttackSequence 0x46d2e0: its +0x20 bit 3 set)
    // vt+0x74 0x004703b0 _vf74: the base reset: no owner, no manager, the index and +0x14 -1, the timer 0 (word stores).
    virtual void Vf74() {
        m_pManager = nullptr;
        m_fTimer = 0.0f;
        m_i32Unk14 = -1;
        m_pOwner = nullptr;
        m_ui32Index = 0xffffffffu;
    }
    virtual void Vf78() { m_fTimer = 0.0f; }  // vt+0x78 0x004703d8 _vf78: the timer cleared (stw 0)

    // 0x004703a8 KStub_Return1_4703a8: CKColossusAttackSequence_Load 0x46eec8 calls it with (an element, the file, 0)
    // inside its element loop and drops the answer; 1. No vtable holds it.
    static int32_t LoadNothing(void* /*object*/, IKFile* /*file*/, int32_t /*type*/) { return 1; }

    IKSerializable* m_pOwner;               // +0x04 the colossus hook (the manager's PostLoad)
    CKColossusSequenceManager* m_pManager;  // +0x08 the manager (its PostLoad)
    uint32_t m_ui32Index;                   // +0x0c read by the Load, then its place in the manager (its PostLoad)
    float m_fTimer;                         // +0x10 seconds since the start (vt+0x50 / +0x60)
    int32_t m_i32Unk14;                     // +0x14 read by the Load (vt+0x74: -1)
};
DOTD_ASSERT_OFFSET(CKColossusAttackSequenceBase, m_pOwner, 0x04);
DOTD_ASSERT_OFFSET(CKColossusAttackSequenceBase, m_pManager, 0x08);
DOTD_ASSERT_OFFSET(CKColossusAttackSequenceBase, m_ui32Index, 0x0c);
DOTD_ASSERT_OFFSET(CKColossusAttackSequenceBase, m_fTimer, 0x10);
DOTD_ASSERT_OFFSET(CKColossusAttackSequenceBase, m_i32Unk14, 0x14);
DOTD_ASSERT_SIZE(CKColossusAttackSequenceBase, 0x18);
