// CKSrvFx.h - the effect service (key 0x381, vtable 0xb1c590, size 0x30). Original unit: CKSrvFx.cpp
// (0x1ab2b0-0x1ad058). XXL2: K/KServices/KServiceFx/CKSrvFx.h: the mapping table, the effect pool
// (built by PostLoad) and the particle emitters are read in the same order; DotD's counts are 32-bit,
// the impulse emitters are not read, and the unique effects come last. The names keep XXL2's with the
// PS3 widths.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"

class IKFx;
class IKFxData;

class CKSrvFx : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0xe)
    DOTD_DECLARE_FACTORIES(CKSrvFx)

    // XXL2 CKSrvFx::CUnderMappingindex: the effect nodes of one type, 0xc bytes on the PS3.
    struct CUnderMappingindex {
        int32_t m_i32FxTypeId;                  // +0x00 (XXL2 Int8 m_i8FxTypeId), read second
        uint32_t m_ui32MaxSize;                 // +0x04 (XXL2 UInt8 m_ui8MaxSize), read first
        IKSerializable** m_apFxArrayForTypeId;  // +0x08 IKFx* (Mem_AllocAligned16)
    };
    // XXL2 CKSrvFx::CMappingindex: one effect node class, 0xc bytes on the PS3.
    struct CMappingindex {
        uint32_t m_ui32ClassId;                 // +0x00 the node class's full key, read last
        CUnderMappingindex* m_aUnderMapping;    // +0x04 OperatorNewArray
        uint32_t m_ui32NbTypeFx;                // +0x08 (XXL2 UInt8 m_ui8NbTypeFx), read first
    };

    CKSrvFx();  // 0x001ab788 CKSrvFx_Construct
    ~CKSrvFx() override {}

    void Destroy() override;  // vt+0x10 0x001ab558 CKSrvFx_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001ac708 CKSrvFx_Load
    // vt+0x30 0x001ab990 CKSrvFx_PostLoad: the table's effects flattened into m_apFxArray (a level-start step
    // of the load), every effect of both pools marked stopped and its owner cleared.
    int32_t PostLoad(int32_t type) override;
    void Start() override {}                            // vt+0x50 0x1ab4e8  STUB(C1.6)
    void Stop() override;                               // vt+0x68 0x1abc50 CKSrvFx_Stop
    void Pause() override {}                            // vt+0x70 0x1ac210  STUB(C1.6)
    void Resume() override {}                           // vt+0x78 0x1ac3c0  STUB(C1.6)
    void Update(IKTime* frameClock) override;           // vt+0x7c 0x001ac000 UpdateCKSrvFx
    // The start of an effect from its data, inlined by every FX data's MessageProc (0x1b00, e.g. CKTimeScalingFxData_MessageProc
    // 0x1d7618) and by CKS08MenuPauseInfo_OnStatePhase 0x55fe00. Data of a pooled effect (vt+0x50 == 0): the mapping entry of
    // the data's node class (vt+0x54) and type (vt+0x58), its first free effect (stopped, not reserved) gets the data
    // (vt+0x84), the owner (vt+0x88) and starts (vt+0x64); a type with no effect, or no free one, ends the search. Data of a
    // unique effect: the unique effect of that class gets SetDataAndOwner (vt+0x8c) and starts if it was stopped and not
    // reserved. Returns the effect, null when none was found.
    IKFx* StartEffect(IKFxData* data, const IKSerializable* owner);
    // vt+0x8c 0x001ab848 CKSrvFx_SectorUnload: every pooled effect told (IKFx vt+0x7c StopIfLinkedTo with
    // the sector), then the particle components' queued emissions dropped.
    void SectorUnload(int32_t sector) override;
    int32_t InitializeService() override { return 1; }  // vt+0x94 0x1ab300
    void DestroyService() override {}                   // vt+0x98 0x1ab308 (empty)

    CMappingindex* m_apMappingIndexTable;  // +0x0c OperatorNewArray
    uint32_t m_ui32EltNb;                  // +0x10 (XXL2 UInt8 m_ui8EltNb)
    IKSerializable** m_apFxArray;          // +0x14 IKFx*: Load clears it, PostLoad flattens the table into it
    uint32_t m_ui32FxArraySize;            // +0x18 (XXL2 UInt8 m_ui8FxArraySize) PostLoad
    IKSerializable** m_apUniqueFxArray;    // +0x1c IKFx* (OperatorNewArray)
    uint32_t m_ui32UniqueFxArraySize;      // +0x20 (XXL2 UInt8 m_ui8UniqueFxArraySize)
    IKSerializable** m_apPartEmitter;      // +0x24 CParticlesNodeFx* in XXL2 (Mem_AllocAligned16)
    uint32_t m_ui32NbPartEmitter;          // +0x28
    uint32_t m_unk2c;                      // +0x2c not set by the constructor or Load
};
DOTD_ASSERT_SIZE(CKSrvFx::CUnderMappingindex, 0xc);
DOTD_ASSERT_SIZE(CKSrvFx::CMappingindex, 0xc);
DOTD_ASSERT_SIZE(CKSrvFx, 0x30);
DOTD_ASSERT_OFFSET(CKSrvFx, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvFx, m_apMappingIndexTable, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvFx, m_ui32EltNb, 0x10);
DOTD_ASSERT_OFFSET(CKSrvFx, m_apFxArray, 0x14);
DOTD_ASSERT_OFFSET(CKSrvFx, m_apUniqueFxArray, 0x1c);
DOTD_ASSERT_OFFSET(CKSrvFx, m_ui32UniqueFxArraySize, 0x20);
DOTD_ASSERT_OFFSET(CKSrvFx, m_apPartEmitter, 0x24);
DOTD_ASSERT_OFFSET(CKSrvFx, m_ui32NbPartEmitter, 0x28);
