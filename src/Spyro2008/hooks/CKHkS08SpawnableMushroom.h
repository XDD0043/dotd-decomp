// CKHkS08SpawnableMushroom.h - a mushroom spawned by CKGrpS08SpawnableMushroom (key 0x3342, vtable 0xb2a168,
// size 0x60). Original unit: CKHkS08SpawnableMushroom.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "Spyro2008/groups/KBase42C2.h"
#include "k2000/core/Layout.h"

struct CVector3;

class CKHkS08SpawnableMushroom : public KBase42C2 {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xcd)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c61e0
        return key == 0x3342 || key == 0x42c2 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe ||
               key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08SpawnableMushroom)

    // 0x004d89b0 CKHkS08SpawnableMushroom_Construct (inlined in 0x004d9088 CKHkS08SpawnableMushroom_Create):
    // KBase42C2's part, then +0x58 = 0.
    CKHkS08SpawnableMushroom() { m_unk58 = 0; }
    // 0x004d92b0 CKHkS08SpawnableMushroom_Destructor: the contact history (+0x58) given back to its pool (0x00ceaa20 +0x54;
    // here ContactHistory_FreeNode) and cleared, then the actor base's (vtable only).
    ~CKHkS08SpawnableMushroom() override;
    // vt+0x10 0x004d8548 CKHkS08SpawnableMushroom_Destroy: KStub_Nop_445980 (the base's), both matrices destroyed.
    void Destroy() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004d9a98 CKHkS08SpawnableMushroom_Load
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x004d8490 CKHkS08SpawnableMushroom_PostLoad
    void Start() override;  // vt+0x50 0x004d8468 CKHkS08SpawnableMushroom_Start (C2.2)
    // vt+0x94 0x004d9330 CKHkS08SpawnableMushroom_vf94 (spawned on the beacon of its slot +0x28): shown, its variant
    // (+0x34) the beacon's 8 persistent bits after bit 0, the child node (+0x4c) shown and reset, the node at the beacon
    // (tenths) facing its yaw byte (x pi / 128), the volume (+0x54) on and raised to the group's +0x80, flag 8 set and
    // 0x10 cleared, the node's matrix kept in +0x48.
    void Vf94() override;
    // vt+0x98 0x004d8968 CKHkS08SpawnableMushroom_vf98: hidden, the volume off.
    void Vf98() override;
    // vt+0xb4 0x004d87d8 CKHkS08SpawnableMushroom_AttachSounds (IKHook::KGLObjectAttached, no live caller): the child node
    // (+0x4c) and the volume node (+0x54, when set) moved under the hook's node (out of their parents: vt+0x78, then
    // vt+0x70), the sounds 0 and 1 of the dictionary +0x50 attached to the node.
    void KGLObjectAttached(IKSerializable* node) override;
    // vt+0xf0 0x004d8230 CKHkS08SpawnableMushroom_vfF0: may go back to the group unless the bit array's bit 1 is set.
    uint8_t VfF0() override { return static_cast<uint8_t>(((m_bitArray ^ 2u) >> 1) & 1u); }
    // vt+0x1c 0x004d8240 CKHkS08SpawnableMushroom_MessageProc: KBase42C2's answer kept when 2 or 3, else 1 for any
    // non-zero answer and 0 for 0 ((|r| - 1) >> 31 ^ 1).
    int32_t MessageProc(uint16_t message, void* data) override {
        const int32_t result = KBase42C2::MessageProc(message, data);  // 0x00445ca0
        if (result == 3) return 3;
        if (result == 2) return 2;
        return result != 0 ? 1 : 0;
    }
    // vt+0x68 0x004d8440 CKHkS08SpawnableMushroom_Stop: KBase42C2_OnLevelExit_maybe 0x445988 (empty).
    // vt+0x7c 0x004da698 CKHkS08SpawnableMushroom_Update: the child node shown, the hits taken (ProcessDamageContacts),
    // the contact history aged, and while the quake updater (+0x5c) runs the shake: its outputs (ShakeSample_BuildMatrix
    // about the face matrix +0x44) post-concatenated with the spawn matrix +0x48 as the node's local matrix.
    void Update(IKTime* clock) override;
    // 0x004da360 CKHkS08SpawnableMushroom_ProcessDamageContacts_maybe: while the mushroom has hit points, every collision
    // of its volume (+0x54) with a hero's volume (owner type 3) that hurts (properties bit 2 or 3) and carries a hero /
    // element / Spyro damage (0x998c, 0x99cc, 0x970c): the contact history touched (-1000 s); a hero damage hits only on a
    // new touch, the others every frame when they are per second (+0x0c: amount x dt) or on a new touch; a positive
    // amount is applied at the contact point (ApplyDamage).
    void ProcessDamageContacts();
    // 0x004d9cd8 CKHkS08SpawnableMushroom_ApplyDamage_maybe: on a new touch the hit sound (0), the face towards `point`
    // (FaceTowards) and the group's hit effect (+0x6c) at `point`; then the hit points lose `amount`: at 0 or below the
    // mushroom is destroyed (DestroyMushroom), else the beacon's 8 persistent bits after bit 0 keep the whole hit points.
    void ApplyDamage(float amount, const CVector3* point, uint8_t touched);
    // 0x004d8298 CKHkS08SpawnableMushroom_FaceTowards_maybe: the face matrix +0x44 turned (in the horizontal plane) to
    // `point` (the X axis when the mushroom stands on it), relative to the node's local matrix, and the quake started.
    void FaceTowards(const CVector3* point);
    // 0x004d8a20 CKHkS08SpawnableMushroom_Destroy_maybe: the beacon's hit points cleared and its picked bit (0) set, the
    // group's gems (+0x78) at the node raised by +0x80, the child node hidden, the break sound (1), the group's break
    // effect (+0x70) there, the volume removed, the quake stopped and the mushroom given back to the group.
    void DestroyMushroom();

    float m_fHitPoints;          // +0x34 vf94: the beacon's 8 persistent bits after bit 0 (ApplyDamage lowers it)
    uint32_t m_unk38[3];         // +0x38..+0x43 not set by the constructor or Load
    void* m_pUnk44;              // +0x44 PostLoad: RwMatrixCreate
    void* m_pUnk48;              // +0x48 PostLoad: RwMatrixCreate
    IKSerializable* m_pUnk4C;    // +0x4c
    IKSerializable* m_pUnk50;    // +0x50
    IKSerializable* m_pUnk54;    // +0x54
    struct ContactHistoryNode* m_unk58;  // +0x58 the contact history (Update ages it); constructor 0
    IKSerializable* m_pUnk5C;    // +0x5c
};
DOTD_ASSERT_SIZE(CKHkS08SpawnableMushroom, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08SpawnableMushroom, m_fHitPoints, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08SpawnableMushroom, m_pUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08SpawnableMushroom, m_pUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08SpawnableMushroom, m_pUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08SpawnableMushroom, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkS08SpawnableMushroom, m_pUnk5C, 0x5c);
