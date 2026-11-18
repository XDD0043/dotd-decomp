// CKPFGraphTransition.h - a transition of the path-finding graph: the portals from one graph node to
// another (key 0x8c, vtable 0xb1e670, size 0x24). Original units: CKPFGraphTransition.cpp (the portal,
// 0x1ea0a8-0x1ea3e0) and CKPFGraphTransition_2.cpp. XXL2: K/KServices/KServicePathfinding/
// CKPFGraphTransition.h (m_baFlags, m_pNode, m_AllowedChar, m_aPortals, m_ui32NbPortals).
#pragma once
#include <cstdint>

#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CBBox.h"

// XXL2 CPFPortal (vtable 0xb1e5f8, 0x38 bytes on the PS3): two boxes and a bitfield. Its vtable slot +4
// is the Load (slot +0 the destructor).
class CPFPortal {
public:
    CPFPortal();  // 0x001ea138 CKPFGraphTransition_Door_Init
    virtual ~CPFPortal() {}
    virtual int32_t Load(IKFile* file, int32_t type);  // vt+0x04 0x001ea1c8 PFGraphTransitionDoor_Load_maybe
    // The PS3 slot +0x00 (0x001ea0a0 KStub_Return1_1ea0a0, PFPathQuery.cpp's unit; XXL2 CPFPortal::Save): nothing written,
    // 1. Non-virtual here (slot 0 is the destructor in this port); nothing saves portals.
    int32_t Save(IKFile* /*file*/, int32_t /*type*/) { return 1; }

    CBBox m_DepartureBox;       // +0x04 XXL2 m_DepartureBox (m_sup, m_inf)
    CBBox m_ArrivalBox;         // +0x1c XXL2 m_ArrivalBox
    uint32_t m_baTypesAndFlags; // +0x34 XXL2 m_baTypesAndFlags
};

class CKPFGraphTransition : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x8c || key == 0xc; }  // vt+0x08 0x9b0628
    DOTD_DECLARE_FACTORIES(CKPFGraphTransition)

    CKPFGraphTransition();  // inlined in 0x001f0568 CKPFGraphTransition_Create
    ~CKPFGraphTransition() override {}
    // vt+0x10 0x001f07d0 CKPFGraphTransition_Destroy: the portals deleted (new[]), no node, no portals.
    void Destroy() override;
    // vt+0x24 0x001f03d0 CKPFGraphTransition_RecursiveRegistration: outside the memory-card types (4..7) it registers
    // with the saving manager (vt+0x24).
    void RecursiveRegistration(int32_t type) override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f0860 CKPFGraphTransition_Load
    // 0x001f06e8 CKPFGraphTransition_MessageProc (vt+0x1c): 0xa00 opens the transition (bit 2, enabled), 0xa01 closes
    // it (the rotate by 29 with mask 1..31 and back by 3 clears only bit 2); 0 handled, 1 not.
    int32_t MessageProc(uint16_t message, void* data) override;
    // 0x001f0768 CKPFGraphTransition_SetGameState (vt+0x3c): game state 0 opens, 1 closes (as the messages); 1 for
    // those, 0 for any other.
    int32_t SetGameState(const SApplyGameState* state) override;
    // 0x001f06d8 CKPFGraphTransition_Save, 0x001f06e0 CKPFGraphTransition_GetInfo, 0x001f0760
    // CKPFGraphTransition_PostLoad: return 1 (the base class's defaults do the same).
    // 0x001f0648 NavSectorFlags_AllowsAgent_maybe: whether `character` may take the transition: its type bits (>> 3)
    // meet the allowed ones (unless they are 0x80: any), its mode bits (& 7) meet them, and its radius (+0x04) is not
    // above the allowed one.
    uint8_t AllowsCharacter(const CPFCharacter* character) const;
    // 0x001f0600 CKPFGraphTransition_ResetEnabledToDefault_maybe: bit 2 (enabled) = bit 1 (enabled by default).
    void ResetEnabledToDefault() {
        if ((m_baFlags & 2u) != 0) {
            m_baFlags = (m_baFlags & ~4u) | 4u;
        } else {
            m_baFlags &= ~4u;
        }
    }

    uint32_t m_baFlags;            // +0x04 XXL2 m_baFlags; not set by the constructor
    IKSerializable* m_pNode;       // +0x08 XXL2 m_pNode (CKPFGraphNode); the constructor sets null
    CPFCharacter m_AllowedChar;    // +0x0c XXL2 m_AllowedChar (0x10 bytes in DotD)
    CPFPortal* m_aPortals;         // +0x1c XXL2 m_aPortals (new[]); not set by the constructor
    uint32_t m_ui32NbPortals;      // +0x20 XXL2 m_ui32NbPortals
};
DOTD_ASSERT_SIZE(CPFPortal, 0x38);
DOTD_ASSERT_OFFSET(CPFPortal, m_DepartureBox, 0x04);
DOTD_ASSERT_OFFSET(CPFPortal, m_ArrivalBox, 0x1c);
DOTD_ASSERT_OFFSET(CPFPortal, m_baTypesAndFlags, 0x34);
DOTD_ASSERT_SIZE(CKPFGraphTransition, 0x24);
DOTD_ASSERT_OFFSET(CKPFGraphTransition, m_baFlags, 0x04);
DOTD_ASSERT_OFFSET(CKPFGraphTransition, m_pNode, 0x08);
DOTD_ASSERT_OFFSET(CKPFGraphTransition, m_AllowedChar, 0x0c);
DOTD_ASSERT_OFFSET(CKPFGraphTransition, m_aPortals, 0x1c);
DOTD_ASSERT_OFFSET(CKPFGraphTransition, m_ui32NbPortals, 0x20);
