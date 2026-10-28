// CKSrvPhysics.h - the physics service (key 0x3c1, vtable 0xb1fcc0, size 0x154). Original unit:
// CKSrvPhysics.cpp (0x213028-0x218040). Not in XXL2; names ours. The references are CKPxContainer
// objects (live dump), the step fields derive from the read frequency.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

class CKSrvPhysics : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0xf)
    DOTD_DECLARE_FACTORIES(CKSrvPhysics)

    CKSrvPhysics();  // 0x002144a8 CKSrvPhysics_Construct
    ~CKSrvPhysics() override {}

    void Destroy() override;  // vt+0x10 0x002143c0 CKSrvPhysics_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002176f0 CKSrvPhysics_Load
    void Start() override {}                            // vt+0x50 0x216e28  STUB(C1.6)
    void Stop() override;                               // vt+0x68 0x214638 CKSrvPhysics_Stop
    void Pause() override {}                            // vt+0x70 0x213078  STUB(C1.6)
    void Resume() override {}                           // vt+0x78 0x213080  STUB(C1.6)
    void Update(IKTime* frameClock) override;           // vt+0x7c 0x216c88 UpdateCKSrvPhysics
    // vt+0x94 0x214460 CKSrvPhysics_InitializeService: the two RwMatrix at +0xdc/+0xe0 (RwMatrixCreate),
    // then 1.
    int32_t InitializeService() override;
    void DestroyService() override {}                   // vt+0x98 0x213088  STUB(C1.6)

    float m_unk0c;                     // +0x0c not set by the constructor or Load (live: 1/60)
    float m_unk10;                     // +0x10 1 / m_unk18
    float m_unk14;                     // +0x14 1 / m_unk1c
    float m_unk18;                     // +0x18 read (LVL000: 60.0, a step frequency _maybe)
    float m_unk1c;                     // +0x1c m_unk18^2 * 0.5
    uint32_t m_unk20;                  // +0x20 Load sets 0
    CVector3 m_unk24;                  // +0x24 read (LVL000: 0, -9.8, 0: the gravity _maybe)
    TVector<IKSerializable*, 1> m_unk30;  // +0x30 read: references (CKPxContainer)
    IKSerializable* m_unk3c;           // +0x3c CKPxContainer
    IKSerializable* m_unk40;           // +0x40 CKPxContainer
    IKSerializable* m_unk44;           // +0x44 CKPxContainer
    uint32_t m_unk48;                  // +0x48 read (LVL000: 100)
    IKSerializable* m_unk4c;           // +0x4c CKPxContainer
    IKSerializable* m_unk50;           // +0x50 CKPxContainer
    IKSerializable* m_unk54;           // +0x54 CKPxContainer
    uint32_t m_unk58[32];              // +0x58 read: one 0x80-byte read, then every word byte-swapped
    IKSerializable* m_unkd8;           // +0xd8 CKPxContainer
    void* m_unkdc;                     // +0xdc RwMatrix (InitializeService)
    void* m_unke0;                     // +0xe0 RwMatrix (InitializeService)
    uint32_t m_unke4[12];              // +0xe4 not set by the constructor or Load
    TVector<IKSerializable*, 1> m_unk114;  // +0x114 read: 100 references (CKPxContainer)
    uint16_t m_unk120;                 // +0x120 Load sets 0
    uint16_t m_unk122;                 // +0x122 not set by the constructor or Load
    IKSerializable* m_unk124;          // +0x124 CKPxContainer
    IKSerializable* m_unk128;          // +0x128 CKPxContainer
    float m_unk12c;                    // +0x12c read (LVL000: 0.01)
    float m_unk130;                    // +0x130 read (LVL000: 1.0)
    float m_unk134;                    // +0x134 read (LVL000: 2 pi)
    uint32_t m_unk138[5];              // +0x138 the constructor sets 0
    uint16_t m_unk14c;                 // +0x14c the constructor sets 0
    uint16_t m_unk14e;                 // +0x14e the constructor sets 0
    uint16_t m_unk150;                 // +0x150 Load sets 0
    uint16_t m_unk152;                 // +0x152 not set by the constructor or Load
};
DOTD_ASSERT_SIZE(CKSrvPhysics, 0x154);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unkd8, 0xd8);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk114, 0x114);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk120, 0x120);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk12c, 0x12c);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk134, 0x134);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk138, 0x138);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk14c, 0x14c);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk150, 0x150);
