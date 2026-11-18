// CKEnemySectorCpnt.h - the reference lists an enemy keeps per sector (key 0x386, vtable 0xb22528, size
// 0x28). Original unit: CKEnemySectorCpnt.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CAnimationDictionary;

class CKEnemySectorCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0xe)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bcc40
        return key == 0x386 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKEnemySectorCpnt)

    CKEnemySectorCpnt() {}  // 0x002b3470 CKEnemySectorCpnt_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002b35c0 CKEnemySectorCpnt_Load
    // vt+0x10 0x002b33c0 CKEnemySectorCpnt_Destroy: a tail jump to 0x002b3298 CKEnemySectorCpnt_FreeBuffers_maybe: the
    // reference arrays freed and cleared (+0x04 .. +0x18, then +0x20 and +0x24; the sound dictionary is a reference).
    void Destroy() override;

    // The accessors (CKEnemySectorCpnt.cpp, not virtual; no range checks).
    IKSerializable* GetAnimatedNode(uint32_t i) const { return m_apUnk04[i]; }   // 0x002b3110 CKEnemySectorCpnt_GetAnimatedNode
    CAnimationDictionary* GetAnimDictionary(uint32_t i) const {                  // 0x002b3128 CKEnemySectorCpnt_GetAnimDictionary
        return reinterpret_cast<CAnimationDictionary*>(m_apUnk08[i]);
    }
    // 0x002b3140 CKEnemySectorCpnt_GetChainedEntryFromArray0C_maybe: the controller of slot `slot` of layer `layer`: from the
    // layer's blender (+0x0c), (columns of the layer's dictionary - slot - 1) times its first controller, then its second
    // one for a slot other than 0. A count of 0 loops 2^32 - 1 times, as the original's counter does.
    IKSerializable* GetChainedEntry(uint32_t layer, uint32_t slot) const;
    IKSerializable* GetCollisionVolume(uint32_t i) const { return m_apUnk10[i]; }  // 0x002b31b0 CKEnemySectorCpnt_GetCollisionVolume_maybe
    IKSerializable* GetArray18Entry(uint32_t i) const { return m_apUnk18[i]; }     // 0x002b31c8 CKEnemySectorCpnt_GetArray18Entry_maybe
    IKSerializable* GetHotSpot(uint32_t i) const { return m_apUnk14[i]; }          // 0x002b31e0 CKEnemySectorCpnt_GetHotSpot

    // Reference arrays (Mem_AllocAligned16 for their u8 counts; the counts are not stored). +0x04, +0x08
    // and +0x0c share one count, +0x20 and +0x24 another.
    IKSerializable** m_apUnk04;  // +0x04
    IKSerializable** m_apUnk08;  // +0x08
    IKSerializable** m_apUnk0c;  // +0x0c
    IKSerializable** m_apUnk10;  // +0x10
    IKSerializable** m_apUnk14;  // +0x14
    IKSerializable** m_apUnk18;  // +0x18
    IKSerializable* m_pUnk1c;    // +0x1c one reference: the sound dictionary (CKSoundDictionaryID; PlaySound)
    IKSerializable** m_apUnk20;  // +0x20
    IKSerializable** m_apUnk24;  // +0x24
};
DOTD_ASSERT_SIZE(CKEnemySectorCpnt, 0x28);
DOTD_ASSERT_OFFSET(CKEnemySectorCpnt, m_apUnk04, 0x04);
DOTD_ASSERT_OFFSET(CKEnemySectorCpnt, m_pUnk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKEnemySectorCpnt, m_apUnk24, 0x24);
