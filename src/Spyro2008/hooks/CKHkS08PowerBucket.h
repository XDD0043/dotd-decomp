// CKHkS08PowerBucket.h - a power bucket hook (key 0x30c2, vtable 0xb29c50, size 0x20c). Original unit:
// CKHkS08PowerBucket.cpp. No XXL2 class. Derives from CKHkS08TransportableWeight (its Load 0x4d4018 calls
// CKHkS08TransportableWeight_Load first). Field names are placeholders.
#pragma once
#include <cstdint>

#include "Spyro2008/hooks/CKHkS08TransportableWeight.h"
#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/core/Stub.h"
#include "k2000/fx/IKFx.h"

class CKHkS08PowerBucket : public CKHkS08TransportableWeight {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc3)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c5e20
        return key == 0x30c2 || key == 0x3142 || key == 0x3002 || key == 0x3082 || key == 0xd82 || key == 0x2 ||
               key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08PowerBucket)

    // 0x004d3fc0 CKHkS08PowerBucket_Create: the CKHkS08TransportableWeight constructor (0x4b4a98), then
    // this vtable; nothing of its own.
    CKHkS08PowerBucket() {}
    ~CKHkS08PowerBucket() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004d4018 CKHkS08PowerBucket_Load
    // C2.8 port-rest R10, the bucket's own runtime (LVL040; no power bucket in LVL010).
    // vt+0x30 0x004d3670 CKHkS08PowerBucket_PostLoad: the Weight's; with a hot spot (+0x1cc) the particles data +0x1e0
    // follows it (+0x14 = hot spot, +0x10 = 0). 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x50 0x004d3e00 CKHkS08PowerBucket_Start: the Weight's, no effect (+0x1e4), the node +0x1d8 under sector 0's root
    // (the game manager's level) and hidden, then vt+0x54 (Restart).
    void Start() override;
    // vt+0x7c 0x004d4628 CKHkS08PowerBucket_Update: the Weight's; carried (state 0) and filled (vt+0x190) a swing that
    // passes 0.5 and turns back sets off the effect (TriggerFx), else the effect is let go; the node +0x1d8 follows the
    // hot spot +0x1cc (else this node's world position, +0x1dc above); the swing kept for the next frame (+0x1fc..).
    void Update(IKTime* clock) override;
    // vt+0xf8 0x004d3ae8 CKHkS08PowerBucket_vfF8: the carrier held (+0x48) is asked (vt+0x5c) alone, then the Key's let-go.
    uint8_t VfF8(IKSerializable* carrier, const CVector3* velocity) override;
    // vt+0x154 0x004d48c0 CKHkS08PowerBucket_OnImpact_maybe: the impact feedback (vt+0x168), then on a ground that is not a
    // dead slide: hard enough (+0x1f8) and not on engine bit 1: the explosion (+0x1d4 filled, else the Weight's +0x1b0) at
    // the grip's matrix (a filled one hurts: damage owner = the bucket, category 1, flags 8), shown off, vt+0x108 and back
    // into the pool; on engine bit 1: the surface effect 3 / 2 and the sound 0 of +0x130 at the contact, shown off,
    // vt+0x108 and back into the pool.
    void Vf154(const CGroundContactDatasInOut* contact) override;
    // vt+0x168 0x004d34e8 CKHkS08PowerBucket_vf168: the Key's impact feedback (0x4ae250), not the Weight's explosion.
    void Vf168() override { CKHkS08TransportableKey::Vf168(); }
    // vt+0x18c 0x004d4fc0 CKHkS08PowerBucket_SpawnAltImpactFx_maybe: the explosion +0x1d4 (filled, else +0x1b0) at the
    // grip's world position facing Y.
    void Vf18C() override;
    // 0x004d4358 CKHkS08PowerBucket_TriggerFx_maybe: the particles data +0x1e0 on the hot spot +0x1cc, an effect acquired
    // (+0x1e4) and its reservation let go (vt+0x54); BUG(original): +0x1e4 is then overwritten with the effect's reserved
    // bit as it was found (0), so Update never stops it. The sound 6 of +0x1d0 at the node.
    void TriggerFx();
    // vt+0xec 0x004d3510 CKHkS08PowerBucket_vfEC: the Weight's (0x4b4bf0) when vt+0x190 answers nonzero, else null.
    IKSerializable* VfEC() override { return Vf190() != 0 ? CKHkS08TransportableWeight::VfEC() : nullptr; }
    // vt+0x190 0x004d33a8 CKHkS08PowerBucket_vf190: the byte +0x1f0 (the word's first byte, as SetCarriedShown writes it).
    // Not virtual here (only the bucket has the slot).
    uint8_t Vf190() const { return static_cast<uint8_t>(m_unk1f0 >> 24); }
    // C2.8 port-all P16. vt+0x120 0x004d3490 / vt+0x124 0x004d3438: the Key's vt+0x120 / vt+0x124 (not the Weight's),
    // then vt+0x194 with 0 (SetCarriedShown).
    void Vf120() override {
        CKHkS08TransportableKey::Vf120();  // 0x004ac5d0
        SetCarriedShown(0);
    }
    void Vf124() override {
        CKHkS08TransportableKey::Vf124();  // 0x004ac580
        SetCarriedShown(0);
    }
    // vt+0x54 0x004d35b0 CKHkS08PowerBucket_Restart: the Key's (0x4adb08), the node +0x1d8 hidden, +0x1e8 cleared,
    // vt+0x194 with 0, +0x208 and +0x1fc..+0x204 cleared.
    void Restart() override;
    // vt+0x68 0x004d3cf8 CKHkS08PowerBucket_Stop: the Weight's (the Key's empty one), the node +0x1d8 hidden.
    void Stop() override {
        CKHkS08TransportableWeight::Stop();
        CSGLeaf* node = static_cast<CSGLeaf*>(m_unk1d8);
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    }
    // vt+0x16c 0x004d3a58 / vt+0x170 0x004d39c8 / vt+0x174 0x004d3938: the sounds 3 / 4 / 5 of the dictionary +0x1d0 when
    // vt+0x190 answers nonzero, else 0 / 1 / 2.
    CKSound* Vf16C() override;
    CKSound* Vf170() override;
    CKSound* Vf174() override;
    // vt+0x194 0x004d3d48 CKHkS08PowerBucket_vf194: the byte +0x1f0 (the first byte of the word: stb) = `on`; the node
    // +0x1d8 shown (+0x10 bit 2 cleared) when on, hidden when off. Not virtual here (the hero group's message 0xc11).
    void SetCarriedShown(uint8_t on) {
        m_unk1f0 = (m_unk1f0 & 0x00ffffffu) | (static_cast<uint32_t>(on) << 24);
        CSGLeaf* node = static_cast<CSGLeaf*>(m_unk1d8);
        node->m_sgProperties = on != 0 ? (node->m_sgProperties & 0xfffffffbu) : ((node->m_sgProperties & 0xfffffffbu) | 4u);
    }

    // +0x1cc reference (LVL040: a CSGHotSpot). PostLoad 0x4d3670 stores it at +0x14 of the +0x1e0 object
    // (and clears that object's +0x10) when it is set.
    IKSerializable* m_unk1cc;
    IKSerializable* m_unk1d0;   // +0x1d0 reference (LVL040: a CKSoundDictionaryID)
    IKSerializable* m_unk1d4;   // +0x1d4 reference (LVL040: a CKExplosionFxData)
    IKSerializable* m_unk1d8;   // +0x1d8 reference
    float m_unk1dc;             // +0x1dc (LVL040: 0): the height of the node +0x1d8 above this node (Update)
    IKSerializable* m_unk1e0;   // +0x1e0 reference: a CKParticlesEffectFxData (TriggerFx)
    IKFx* m_pEffect;            // +0x1e4 runtime: the effect TriggerFx acquired (see its BUG)
    uint32_t m_unk1e8;          // +0x1e8 runtime
    float m_unk1ec;             // +0x1ec
    uint32_t m_unk1f0;          // +0x1f0 runtime
    float m_unk1f4;             // +0x1f4
    float m_unk1f8;             // +0x1f8
    // +0x1fc..+0x20b runtime: the Weight's swing (+0x1a0..+0x1ac) of the last frame (Update).
    float m_fPrevSwingRight;       // +0x1fc
    float m_fPrevSwingAt;          // +0x200
    float m_fPrevSwingRightSpeed;  // +0x204
    float m_fPrevSwingAtSpeed;     // +0x208
};
DOTD_ASSERT_SIZE(CKHkS08PowerBucket, 0x20c);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1d0, 0x1d0);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1dc, 0x1dc);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1f4, 0x1f4);
DOTD_ASSERT_OFFSET(CKHkS08PowerBucket, m_unk1f8, 0x1f8);
