// CKHkPxObject.h - an actor hook on a CKPx physics body that emits particles at the body's contacts (key 0x1ac2,
// vtable 0xb269d0, size 0x54). Original unit: CKHkPxObject.cpp (0x445dc8-0x4472f0). No XXL2 class; names ours. No game
// file holds one (work/level-class-keys.json). C2.8 port-rest R05 ported the Load and the slots; C2.8 port-last Z7
// Update and its two contact emitters.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"

class CKHkPxObject : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x6b)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x009c3ae0
        return key == 0x1ac2 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkPxObject)

    // 0x004468e0 CKHkPxObject_Create: the actor base's constructor, then the vtable (no member stores).
    // Out of line (CKHkPxObject.cpp): inline ones can fail the MSVC x64 Debug link with LNK1163.
    CKHkPxObject();
    // 0x00446378 / 0x00446330 / 0x004463a8 CKHkPxObject_Destructor / _DeletingDestructor / _BaseDestructor: the vtable, then
    // the actor base's.
    ~CKHkPxObject() override;

    // vt+0x2c 0x00446ef0 CKHkPxObject_Load: the actor base's, then (level data) the options byte, the body, the first
    // effect node and its two words, the second effect node and its two words, a reference and four words.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x7c 0x00446de0 CKHkPxObject_Update (C2.8 port-last Z7)
    void Update(IKTime* frameClock) override;
    // 0x00445e50 CKHkPxObject_AddContactPointsToFxNode28_maybe
    void AddContactPointsToFxNode28();
    // 0x00446938 CKHkPxObject_AddContactHistoryPointsToFxNode34_maybe
    void AddContactHistoryPointsToFxNode34();
    // vt+0x10 / +0x24 / +0x50 / +0x68 / +0x70 / +0x78 0x446308 / 0x4462e0 / 0x446290 / 0x446268 / 0x446240 / 0x446218
    // CKHkPxObject_Destroy / _RecursiveRegistration / _Start / _Stop / _Pause / _Resume: the actor base's (inherited).

    uint8_t m_ui8Options;      // +0x20 bit 0: particles at the contacts (+0x28), bit 1: at the contact history (+0x34)
    uint8_t m_pad21[3];
    IKSerializable* m_pBody;   // +0x24 reference: the CKPx body (its +0x20 bit 0x400000 gates the emitters)
    IKSerializable* m_unk28;   // +0x28 reference: the contacts' particle node
    float m_fUnk2c;            // +0x2c the contacts' speed threshold
    float m_fUnk30;            // +0x30 the contacts' particle speed factor
    IKSerializable* m_unk34;   // +0x34 reference: the contact history's particle node
    float m_fUnk38;            // +0x38 the history's speed threshold
    float m_fUnk3c;            // +0x3c the history's particle speed factor
    IKSerializable* m_unk40;   // +0x40 reference
    uint32_t m_unk44[4];       // +0x44..+0x53 four separate words
};
static_assert(CKHkPxObject::kClassKey == 0x1ac2, "key");
DOTD_ASSERT_SIZE(CKHkPxObject, 0x54);
DOTD_ASSERT_OFFSET(CKHkPxObject, m_ui8Options, 0x20);
DOTD_ASSERT_OFFSET(CKHkPxObject, m_pBody, 0x24);
DOTD_ASSERT_OFFSET(CKHkPxObject, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkPxObject, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkPxObject, m_unk44, 0x44);
