// CKObjectManager.h - an object manager: a reference and two reference lists (key 0x538c, vtable 0xb2ee80, size 0x18).
// Original unit: CKObjectManager.cpp (0x5aeb88-0x5af6a8, GAME_TOC2). No XXL2 class of this name; no KP3 file of LVL000 /
// LVL010 holds one.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKObjectManager : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x14e)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x538c || key == 0xc; }  // vt+0x08 0x9cbf90
    DOTD_DECLARE_FACTORIES(CKObjectManager)

    // 0x005af120 CKObjectManager_Create / 0x005af038 CreateArray inline it: +0x04 cleared, then both lists emptied
    // (InitRefArray_2, InitRefArray).
    CKObjectManager() : m_unk04(nullptr) {
        InitRefArray2();
        InitRefArray();
    }
    ~CKObjectManager() override {}

    // vt+0x10 0x005aeff8 CKObjectManager_Destroy: both blocks freed (the pointers and counts kept).
    void Destroy() override;
    // vt+0x24 0x005aef90 CKObjectManager_RecursiveRegistration: outside the memory-card types (4..7) it registers with
    // the saving manager (vt+0x24).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x2c 0x005aeec0 CKObjectManager_Load: the reference +0x04, then the lists +0x08 and +0x10 (for every type).
    int32_t Load(IKFile* file, int32_t type) override;

    // 0x005af188 CKObjectManager_InitRefArray_maybe / 0x005af430 _2: the list +0x10 / +0x08 emptied (no block).
    void InitRefArray() {
        m_ui32NbUnk10 = 0;
        m_apUnk10 = nullptr;
    }
    void InitRefArray2() {
        m_ui32NbUnk08 = 0;
        m_apUnk08 = nullptr;
    }
    // 0x005af2b0 CKObjectManager_LoadRefArray_maybe / 0x005af558 _2: the count (little-endian), then a block of that
    // many references (none for 0) read through the resolver (or as raw ids).
    void LoadRefArray(IKFile* file);
    void LoadRefArray2(IKFile* file);
    // 0x005af198 CKObjectManager_SaveRefArray_maybe / 0x005af440 _2: the count (little-endian), then the references as
    // contiguous handles (the saving manager's vt+0x4c), or without one the block's raw words.
    void SaveRefArray(IKFile* file);
    void SaveRefArray2(IKFile* file);

    IKSerializable* m_unk04;     // +0x04 a reference
    IKSerializable** m_apUnk08;  // +0x08 references (Mem_AllocAligned16)
    uint32_t m_ui32NbUnk08;      // +0x0c
    IKSerializable** m_apUnk10;  // +0x10 references (Mem_AllocAligned16)
    uint32_t m_ui32NbUnk10;      // +0x14
};
DOTD_ASSERT_SIZE(CKObjectManager, 0x18);
DOTD_ASSERT_OFFSET(CKObjectManager, m_apUnk08, 0x08);
DOTD_ASSERT_OFFSET(CKObjectManager, m_apUnk10, 0x10);
