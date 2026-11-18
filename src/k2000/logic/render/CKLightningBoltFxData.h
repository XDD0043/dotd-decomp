// CKLightningBoltFxData.h - the data of a lightning-bolt effect (key 0xa64c, vtable 0xb2e048, size 0xa8).
// Original unit: CKLightningBoltFxData_2.cpp (0x5774e8-0x579b00); Create (0x56eec8) is in
// CKLightningBoltFxData.cpp. Its node is CKLightningBoltNodeFx (0xa60c). Not in XXL2; names ours.
//
// The segments (+0x60) are 60-byte records of fifteen byte-swapped words (CopyEntry60 0x577868 copies them).
// The decompiler shows three of them unswapped; the assembly swaps all fifteen (lwbrx).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/util/TVector.h"

class CKLightningBoltFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x299)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9caf08
        return key == 0xa64c || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKLightningBoltFxData)

    struct Segment {
        float m_values[15];  // +0x00 (LVL010: floats, 100.0, 1.0, 0.2, ...)
    };

    CKLightningBoltFxData();  // inlined in 0x0056eec8 CKLightningBoltFxData_Create

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00578158 CKLightningBoltFxData_Load
    // vt+0x30 0x005774f8 CKLightningBoltFxData_PostLoad: (type 0) the source and target cleared, the target point the
    // zero vector and unused, no reserved bolt.
    int32_t PostLoad(int32_t type) override;
    // vt+0x24 0x005776a8 CKLightningBoltFxData_RecursiveRegistration: the FX data base's (nothing), then (type 0) the four
    // references +0x40..+0x4c and +0x8c when set.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x10 0x00577b78 CKLightningBoltFxData_Destroy: the segment block freed, its count and pointer cleared. vt+0x40
    // GetInfo 0x577b70 returns 1.
    void Destroy() override;
    uint32_t GetAssociatedFxClassIdentifier() override { return 0xa60c; }  // vt+0x54 0x5774e8
    // vt+0x1c 0x00579a10 CKLightningBoltFxData_MessageProc: 0x1b00 starts a bolt at the marker beacon sent (no source
    // node), 0x1b02 from the node of the hook sent (+0x1c, a CNode: the source node); unless flag bit 0 or 1 is set the
    // bolt is reserved (+0x84; nothing when one is), else a free / the unique one starts (CKSrvFx::StartEffect). The bolt
    // is placed (0x1b00), aimed at the target point when there is one, and switched on (SetActiveForOwner). 0x1b01
    // releases the reserved bolt; 0x1b91 / 0x1b92 set the target (a point, or the node of the hook sent). 0 handled.
    int32_t MessageProc(uint16_t message, void* data) override;

    // The random values (rand & 0xffff mapped to [-1, 1]: / 65535 x -2, then fmadds with the half range):
    // 0x00577548 CKLightningBoltFxData_RandomValue6C_maybe: +0x6c + [-1, 1] x +0x70 (the roll speed, degrees per second).
    float RandomValue6C();
    // 0x00577bd0 CKLightningBoltFxData_EvaluateColor_maybe: the strip colour at `t` (0 start, 1 end) at the bolt's `time`
    // into `out` (RGBA bytes).
    void EvaluateColor(float time, float t, uint8_t* out) const;
    // 0x005775b8 / 0x00577630 CKLightningBoltFxData_RandomInterval58 / 50_maybe: 1 / (+0x58 / +0x50 + [-1, 1] x +0x5c / +0x54).
    float RandomInterval58();
    float RandomInterval50();
    // 0x00577868 CKLightningBoltFxData_CopyEntry60_maybe: segment `index` (0x3c bytes) into `out`; returns `out`.
    void* CopyEntry60(void* out, uint32_t index) const;
    // 0x00577ab8 CKLightningBoltNodeFx_GetBranchLevelScale_maybe: `length` x segment `level`'s +0x04, kept between its
    // +0x0c and +0x08; 1.0 past the segments (BUG(original): the level equal to the count reads one past them).
    float GetBranchLevelScale(float length, uint32_t level) const;

    // +0x08..+0x14 run time (not read): the bolt's source and target, set by its user (the heroes' partner link...).
    IKSerializable* m_pSourceNode;     // +0x08 a scene node (CSGMovable), else
    IKSerializable* m_pSourceHotSpot;  // +0x0c a CSGHotSpot
    IKSerializable* m_pTargetNode;     // +0x10
    IKSerializable* m_pTargetHotSpot;  // +0x14
    uint16_t m_unk18;          // +0x18 (lhbrx)
    uint8_t m_pad1a[2];
    float m_unk1c;             // +0x1c
    uint32_t m_unk20[3];       // +0x20 not read
    uint8_t m_unk2c[4];        // +0x2c read without a swap: the file's bytes (colours, _maybe)
    uint8_t m_unk30[4];        // +0x30 read without a swap
    uint8_t m_unk34[4];        // +0x34 read without a swap
    uint8_t m_unk38[4];        // +0x38 read without a swap
    float m_unk3c;             // +0x3c
    IKSerializable* m_unk40;   // +0x40 object references
    IKSerializable* m_unk44;   // +0x44
    IKSerializable* m_pSourceExplosion;  // +0x48 an explosion set off at the bolt's node now and then (UpdateImpactExplosions)
    IKSerializable* m_pEndExplosion;     // +0x4c the same at the end point
    float m_unk50;             // +0x50 RandomInterval50 (0x577630) _maybe reads +0x50/+0x54
    float m_unk54;             // +0x54
    float m_unk58;             // +0x58 RandomInterval58 (0x5775b8) _maybe reads +0x58/+0x5c
    float m_unk5c;             // +0x5c
    TVector<Segment, 1> m_segments;  // +0x60 the constructor: null, 1, 0
    float m_unk6c;             // +0x6c RandomValue6C (0x577548) _maybe reads +0x6c/+0x70
    float m_unk70;             // +0x70
    // +0x74..+0x87 not read (runtime, MessageProc 0x579a10): the target point messages 0x1b91 / 0x1b92 set (the object's
    // position, or zero with a target node) and whether it is used, then the effect the data reserved.
    float m_v3TargetPoint[3];  // +0x74
    uint8_t m_bHasTargetPoint; // +0x80
    uint8_t m_pad81[3];
    class IKFx* m_pReservedFx; // +0x84
    float m_unk88;             // +0x88 read last
    IKSerializable* m_unk8c;   // +0x8c an object reference
    int32_t m_i32ImpactsMin;   // +0x90 the impact count range (read as words; ResetImpactSlots draws in it)
    int32_t m_i32ImpactsMax;   // +0x94
    float m_unk98;             // +0x98
    float m_unk9c;             // +0x9c
    float m_unka0;             // +0xa0
    float m_unka4;             // +0xa4
};
static_assert(CKLightningBoltFxData::kClassKey == 0xa64c, "key");
DOTD_ASSERT_SIZE(CKLightningBoltFxData::Segment, 0x3c);
DOTD_ASSERT_SIZE(CKLightningBoltFxData, 0xa8);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_pEndExplosion, 0x4c);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_segments, 0x60);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk8c, 0x8c);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unka4, 0xa4);
