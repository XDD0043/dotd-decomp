// KBase730C.h - the root of DotD's menu classes (key 0x730c: id 0x1cc, category Logic; vtable 0xb15ef0,
// 0x21 slots). DotD only: no XXL2 counterpart, so the name is descriptive (Ghidra: KBase730C_*).
//
// The chain, from the IsKindOfClass of each level (a leaf, e.g. 0x9ca830 CKS08MenuBonus_IsKindOfClass,
// tests its own key, 0x114c, 0x730c, 0xc in that order):
//   IKSerializable (0xc) -> KBase730C (0x730c) -> CKMenuBase114c (0x114c) -> the menus and HUD screens.
// No level tests 0x3fe: the menus are not IKUpdatables.
//
// KBase730C has no fields of its own and only trivial functions: Load/Save/LevelReset 0x67ea0..0x67eb0
// (return 1, in the CBillboard2d_2.cpp range) and the inline copies 0x9983f8..0x9984c0. Its vtable
// store is dropped from every constructor (each Create stores CKMenuBase114c's vtable first).
// The 0x51xxxx functions Ghidra names KBase730C_* sit only in the 0x114c and leaf vtables: they belong
// to CKMenuBase114c (see CKMenuBase114c.h).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class KBase730C : public IKSerializable {
public:
    // One entry of a menu's widget slots (vt+0x6c): a hot spot and the element it drives. 8 bytes on the
    // PS3. The classes are from the file references (keys 0xc0d CFlashHotSpot, 0x5cd CText2d) and the
    // struct drafts (menus: CText2d; the HUD screens, e.g. CKS08InGameInterfaceBoss: CBillboard2d).
    struct WidgetSlot {
        IKSerializable* m_pHotSpot;  // +0x00 CFlashHotSpot
        IKSerializable* m_pElement;  // +0x04 CText2d or CBillboard2d
    };

    ~KBase730C() override {}  // vt+0x00 / +0x04  0x9984c0 / 0x998460
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x730c || key == 0xc; }  // vt+0x08 0x9984a0
    void Destroy() override {}                                 // vt+0x10 0x67eb8
    int32_t GetClassType() override { return kCategoryLogic; }  // vt+0x14 0x9983f8
    int32_t GetClassID() override { return 0x1cc; }            // vt+0x18 0x998400
    // vt+0x24 0x67eb0 and vt+0x28 0x67ea8 return 1; the IKSerializable defaults do the same.
    int32_t Load(IKFile* /*file*/, int32_t /*type*/) override { return 1; }  // vt+0x2c 0x67ea0 KBase730C_Load
    // vt+0x24 0x67eb0 (Ghidra KBase730C_LevelReset): 1, registers nothing (CKMenuBase_114c's RecursiveRegistration
    // calls it).
    void RecursiveRegistration(int32_t /*type*/) override {}

    // Slots +0x50..+0x80 (CKMenuBase114c overrides most of them). Names ours, from the 0x114c bodies.
    virtual void Open() {}                         // vt+0x50 0x998408 (0x114c: 0x514a00 KBase730C_Open)
    virtual void Pause(int32_t /*stopVideo*/) {}   // vt+0x54 0x998410 (0x114c: 0x5139a0 KBase730C_vf54)
    virtual void Resume() {}                       // vt+0x58 0x998418 (0x114c: 0x513700 KBase730C_Open_maybe)
    virtual void Close() {}                        // vt+0x5c 0x998420 (0x114c: 0x513f88 KBase730C_Close)
    virtual IKSerializable* Vf60() = 0;            // vt+0x60 pure (0x114c: returns +0x0c, the CKFlashUI)
    virtual void Vf64(uint32_t flag) = 0;          // vt+0x64 pure (0x114c: bit 0 of +0x04)
    // vt+0x68 0x998428 / vt+0x6c 0x998430: the widget slots the 0x114c Load reads (the leaves override
    // both with a count and a fixed array; Ghidra: <Leaf>_GetWidgetSlotCount / _GetWidgetSlots).
    virtual uint32_t GetWidgetSlotCount() { return 0; }
    virtual WidgetSlot* GetWidgetSlots() { return nullptr; }
    // vt+0x70 / +0x74: a widget slot's element offset from its hot spot (0x114c: 0x512830 KBase730C_GetElementX_maybe /
    // 0x514e10 KBase730C_GetElementY_maybe); here 0.0 (lfs TOC1-0x6eec).
    virtual float GetElementX(uint32_t /*slot*/) { return 0.0f; }  // vt+0x70 0x998438
    virtual float GetElementY(uint32_t /*slot*/) { return 0.0f; }  // vt+0x74 0x998440
    // vt+0x78 0x998448 (empty; 0x114c: 0x512370 KBase730C_SetElementPosition_maybe): a widget slot's element offset
    // from its hot spot set to position[0..1].
    virtual void Vf78(uint32_t /*slot*/, const float* /*position*/) {}
    // vt+0x7c / +0x80: set it (0x114c: 0x512510 KBase730C_SetElementX_maybe / 0x5126a0 KBase730C_SetElementY_maybe).
    virtual void SetElementX(float /*x*/, uint32_t /*slot*/) {}   // vt+0x7c 0x998450
    virtual void SetElementY(float /*y*/, uint32_t /*slot*/) {}   // vt+0x80 0x998458
};
DOTD_ASSERT_SIZE(KBase730C, 0x4);
DOTD_ASSERT_SIZE(KBase730C::WidgetSlot, 0x8);
