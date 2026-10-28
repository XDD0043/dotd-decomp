// KBase42C2.h - the unregistered base of CKHkS08SpawnableMushroom (key 0x42c2; its only registered child).
// Its functions sit in the KBase1944.cpp unit (0x443bb8-0x445dc8), which the groups family owns, so the Load
// is inline here (as IKHook's). No XXL2 class of this key. Size: at least 0x34 (the last field its Load
// reads); the exact size is not known (no Create of its own).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/misc/CKHkActorBase.h"

class KBase42C2 : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x10b)

    // Inlined in 0x004d89b0 CKHkS08SpawnableMushroom_Construct (between the two vtable stores): four
    // halfwords = 0xffff, in this order.
    KBase42C2() {
        m_aUnk28[0] = 0xffff;
        m_aUnk28[3] = 0xffff;
        m_aUnk28[1] = 0xffff;
        m_aUnk28[2] = 0xffff;
    }
    ~KBase42C2() override {}

    // vt+0x2c 0x00445a90 KBase42C2_Load: calls IKHook's Load directly (0x19900 CKHook_Load), not
    // CKHkActorBase's (which only forwards to it).
    int32_t Load(IKFile* file, int32_t type) override {
        IKHook::Load(file, type);
        if (type != K_LEVEL_PLATEFORMS) return 1;
        ReadU32LE(file, &m_unk20);
        IKFile_ReadRef(file, &m_pUnk30);
        return 1;
    }

    // vt+0x30 0x00445a68 KBase42C2_PostLoad: IKLife_PostLoad 0x19f68 (level type only: bit 2 of the bit array).
    int32_t PostLoad(int32_t type) override {
        if (type == K_LEVEL_PLATEFORMS) m_bitArray = (m_bitArray & 0xfffffffbu) | 4u;
        return 1;
    }

    void Start() override;       // vt+0x50 0x00445c70 KBase42C2_ResetRuntime_maybe (C2.2)

    uint32_t m_unk20;            // +0x20
    uint32_t m_unk24;            // +0x24 not set by the constructor or Load
    uint16_t m_aUnk28[4];        // +0x28..+0x2f constructor 0xffff (indices_maybe)
    IKSerializable* m_pUnk30;    // +0x30
};
DOTD_ASSERT_SIZE(KBase42C2, 0x34);
DOTD_ASSERT_OFFSET(KBase42C2, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(KBase42C2, m_aUnk28, 0x28);
DOTD_ASSERT_OFFSET(KBase42C2, m_pUnk30, 0x30);
