// CKSrvInput.h - the input service (key 0x6c1, vtable 0xb1efb8, size 0x38). Original unit:
// CKSrvInput.cpp (0x202248-0x203460). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

class KBase60CC;

class CKSrvInput : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x1b)
    DOTD_DECLARE_FACTORIES(CKSrvInput)

    CKSrvInput();  // 0x00202700 CKSrvInput_Construct
    ~CKSrvInput() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00202d78 CKSrvInput_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x002025e8 CKSrvInput_PostLoad
    void Start() override {}                            // vt+0x50 0x00202298 CKSrvInput_Start (empty)
    void Stop() override;                               // vt+0x68 0x202898 CKSrvInput_Stop
    void Pause() override {}                            // vt+0x70 0x2022a0  STUB(C1.6)
    void Resume() override {}                           // vt+0x78 0x2022a8  STUB(C1.6)
    // vt+0x7c 0x002029b8 UpdateCKSrvInput: the active blocks (+0x20) updated with the fixed game time step.
    void Update(IKTime* frameClock) override;
    // vt+0x94 0x002026b8 CKSrvInput_InitializeService. Ported: Load grows the block it allocates.
    int32_t InitializeService() override;
    // C1.6 gm: 0x00202a50 CKSrvInput_GetInputBlock_maybe: block `index` of +0x14, null past the end.
    KBase60CC* GetInputBlock(uint32_t index);
    // 0x00202450 CKSrvInput_PushActiveBlock_maybe: `block` pushed onto the +0x20 list (KBase60CC_Activate_maybe).
    void PushActiveBlock(KBase60CC* block);
    // 0x00202460 CKSrvInput_RemoveActiveBlock_maybe
    void RemoveActiveBlock(KBase60CC* block);
    void DestroyService() override {}                   // vt+0x98 0x202660  STUB(C1.6)

    uint32_t m_unk0c;                    // +0x0c read (LVL000: 10)
    uint32_t m_unk10;                    // +0x10 read (LVL000: 16)
    TVector<IKSerializable*, 1> m_vRefs; // +0x14 read: references (LVL000: two CKInputBlockSequential)
    KBase60CC* m_unk20;                  // +0x20 the active top-level blocks (linked through +0x04); the constructor sets 0
    uint32_t m_unk24;                    // +0x24 PostLoad sets 0
    uint32_t m_unk28;                    // +0x28 PostLoad sets 0
    uint32_t m_unk2c;                    // +0x2c PostLoad sets 0
    KBase60CC* m_unk30;                  // +0x30 PostLoad sets 0; the last activated child of a top-level block (OnActivate)
    float m_unk34;                       // +0x34 read (LVL000: 2.0); PostLoad sets 2.0 (TOC1 -0x1060)
};
DOTD_ASSERT_SIZE(CKSrvInput, 0x38);
DOTD_ASSERT_OFFSET(CKSrvInput, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvInput, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvInput, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKSrvInput, m_vRefs, 0x14);
DOTD_ASSERT_OFFSET(CKSrvInput, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKSrvInput, m_unk34, 0x34);
