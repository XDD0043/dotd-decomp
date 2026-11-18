// CKScrapShowerCpnt.h - a scrap shower's emitters (key 0x5c6, vtable 0xb286c0, size 0x20; an IKMecaCpnt).
// Original unit: CKScrapShowerCpnt.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKMecaCpntBase.h"

struct CKShadowGround;
struct CVector3;

class CKScrapShowerCpnt : public IKMecaCpnt {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x17)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c4ec8
        return key == 0x5c6 || key == 0xa06 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKScrapShowerCpnt)

    // 8 bytes (OperatorNewArray(n * 8), no cookie): a reference and a byte the Load sets to 1.
    struct Entry {
        IKSerializable* m_pRef;  // +0x00 (LVL060: refs of key 0x486, CKShadowCpnt)
        uint8_t m_bEnabled;      // +0x04 _maybe; 1 after the Load
        uint8_t m_pad05[3];
    };

    CKScrapShowerCpnt() {}  // 0x004a6de0 CKScrapShowerCpnt_Create: the base, the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004a7138 CKScrapShowerCpnt_Load
    // vt+0x10 0x004a6a40 CKScrapShowerCpnt_Destroy: the mechanism base's (vt+0x54), then the entry array freed (not
    // cleared). PostLoad 0x4a69f0 is the base's (vt+0x50, 1), RecursiveRegistration 0x4a6a18 the base's (returns 1) and
    // the destructors 0x4a6ac8 / 0x4a6af8 / 0x4a6a80 the base's (vtable stores only).
    void Destroy() override;

    // ---- C2.8 port-all P18: the scrap shower hook's helpers (CKHkScrapShower.cpp calls them with its component +0x30).
    // 0x004a67a8 CKHkScrapShower_SetPieceShadowScale_maybe: entry `index`'s shadow component gets `scale` as its length
    // and width (CKShadowCpnt_SetFloat04_maybe / _SetFloat08_maybe).
    void SetPieceShadowScale(uint8_t index, float scale);
    // 0x004a6820 CKHkScrapShower_RegisterPieceShadow_maybe: with the ground not in use yet and entries, the first free
    // entry's shadow component registered for `node` on `ground` (CKSrvShadow_RegisterCaster) and taken; its index, -1
    // when there is none.
    int32_t RegisterPieceShadow(IKSerializable* node, CKShadowGround* ground);
    // 0x004a6928 CKHkScrapShower_TryCameraShake_maybe: within +0x1c of the piece (`distanceSq` <= +0x1c squared) and a
    // draw below +0x18 percent, the quake launcher (+0x10) is placed at `position` and triggered and the pad vibration
    // +0x14 played.
    void TryCameraShake(float distanceSq, const CVector3* position);
    // 0x004a6c38 CKHkScrapShower_LaunchScrapAtPoint_maybe: with a projectile type, the accessor (+0x0c) launches from
    // `pos` to `target` (CKProjectileAccessor_LaunchAtPoint, the owner the hook).
    void LaunchScrapAtPoint(const CVector3* pos, const CVector3* target, float speed, IKSerializable* owner);
    // 0x004a6cb0 CKHkScrapShower_UnregisterPieceShadow_maybe: a ground in use gives entry `index`'s shadow back
    // (CKSrvShadow_UnregisterCaster) and frees the entry. `node` is not read.
    void UnregisterPieceShadow(uint8_t index, IKSerializable* node, CKShadowGround* ground);

    Entry* m_aEntries;         // +0x04
    uint8_t m_ui8NbEntries;    // +0x08
    uint8_t m_pad09[3];
    IKSerializable* m_pUnk0c;  // +0x0c reference, read first
    IKSerializable* m_pUnk10;  // +0x10 reference
    IKSerializable* m_pUnk14;  // +0x14 reference, read last
    float m_unk18;             // +0x18 (LVL060: 0.5)
    float m_unk1c;             // +0x1c (LVL060: 5.0)
};
DOTD_ASSERT_SIZE(CKScrapShowerCpnt::Entry, 0x8);
DOTD_ASSERT_SIZE(CKScrapShowerCpnt, 0x20);
DOTD_ASSERT_OFFSET(CKScrapShowerCpnt, m_aEntries, 0x04);
DOTD_ASSERT_OFFSET(CKScrapShowerCpnt, m_ui8NbEntries, 0x08);
DOTD_ASSERT_OFFSET(CKScrapShowerCpnt, m_pUnk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKScrapShowerCpnt, m_unk18, 0x18);
