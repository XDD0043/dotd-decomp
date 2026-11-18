// CKPxContainer.h - (key 0x46cc, vtable 0xb1ff18, size 0x28). Original unit: CKPxContainer.cpp. No XXL2
// class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase468C.h"

class CKPxContainer : public KBase468C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x11b)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b3f88
        return key == 0x46cc || key == 0x468c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPxContainer)

    CKPxContainer() {}  // 0x0021cd30 CKPxContainer_Construct: the base, then the vtable
    ~CKPxContainer() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0021cf58 CKPxContainer_Load

    // The CKPx core's inlined list insert (C2.8 port-last Z7): `element` linked at the head (previous 0, owner this,
    // next the old head; the old head's previous, or the tail without one), the count up.
    void PushFront(KBase468C* element) {
        element->m_unk0c = nullptr;
        element->m_unk08 = this;
        element->m_unk10 = m_unk1c;
        if (m_unk1c != nullptr) {
            static_cast<KBase468C*>(m_unk1c)->m_unk0c = element;
        } else {
            m_unk20 = element;
        }
        m_unk1c = element;
        ++m_unk24;
    }
    // The inlined list splice: every element of `from` (which holds some) owned by this, appended after this list's tail;
    // `from` emptied.
    void AppendAll(CKPxContainer* from) {
        for (IKSerializable* e = from->m_unk1c; e != nullptr; e = static_cast<KBase468C*>(e)->m_unk10) {
            static_cast<KBase468C*>(e)->m_unk08 = this;
        }
        m_unk24 = static_cast<uint16_t>(from->m_unk24 + m_unk24);
        if (m_unk20 != nullptr) {
            static_cast<KBase468C*>(m_unk20)->m_unk10 = from->m_unk1c;
        } else {
            m_unk1c = from->m_unk1c;
        }
        static_cast<KBase468C*>(from->m_unk1c)->m_unk0c = m_unk20;
        from->m_unk24 = 0;
        m_unk20 = from->m_unk20;
        from->m_unk1c = nullptr;
        from->m_unk20 = nullptr;
    }
    // The same with the owner given (the joints' slots unlink from the physics service's joint container +0x54).
    static void Unlink(CKPxContainer* owner, KBase468C* element) {
        element->m_unk08 = nullptr;
        if (element->m_unk0c != nullptr) {
            static_cast<KBase468C*>(element->m_unk0c)->m_unk10 = element->m_unk10;
        } else {
            owner->m_unk1c = element->m_unk10;
        }
        if (element->m_unk10 != nullptr) {
            static_cast<KBase468C*>(element->m_unk10)->m_unk0c = element->m_unk0c;
        } else {
            owner->m_unk20 = element->m_unk0c;
        }
        element->m_unk10 = nullptr;
        element->m_unk0c = nullptr;
        --owner->m_unk24;
    }
    // The inlined unlink: `element` taken out of its owner's list (the owner cleared first; the original does not test
    // it), its links cleared, the owner's count down.
    static void Unlink(KBase468C* element) {
        CKPxContainer* owner = static_cast<CKPxContainer*>(element->m_unk08);
        element->m_unk08 = nullptr;
        if (element->m_unk0c != nullptr) {
            static_cast<KBase468C*>(element->m_unk0c)->m_unk10 = element->m_unk10;
        } else {
            owner->m_unk1c = element->m_unk10;
        }
        if (element->m_unk10 != nullptr) {
            static_cast<KBase468C*>(element->m_unk10)->m_unk0c = element->m_unk0c;
        } else {
            owner->m_unk20 = element->m_unk0c;
        }
        element->m_unk0c = nullptr;
        element->m_unk10 = nullptr;
        --owner->m_unk24;
    }

    IKSerializable* m_unk18;  // +0x18 three references
    IKSerializable* m_unk1c;  // +0x1c
    IKSerializable* m_unk20;  // +0x20
    uint16_t m_unk24;         // +0x24
    uint16_t m_pad26;
};
DOTD_ASSERT_SIZE(CKPxContainer, 0x28);
DOTD_ASSERT_OFFSET(CKPxContainer, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKPxContainer, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKPxContainer, m_unk24, 0x24);
