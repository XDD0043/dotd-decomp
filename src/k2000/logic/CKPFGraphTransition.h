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

    CBBox m_DepartureBox;       // +0x04 XXL2 m_DepartureBox (m_sup, m_inf)
    CBBox m_ArrivalBox;         // +0x1c XXL2 m_ArrivalBox
    uint32_t m_baTypesAndFlags; // +0x34 XXL2 m_baTypesAndFlags
};

class CKPFGraphTransition : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2)
    DOTD_DECLARE_FACTORIES(CKPFGraphTransition)

    CKPFGraphTransition();  // inlined in 0x001f0568 CKPFGraphTransition_Create
    ~CKPFGraphTransition() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f0860 CKPFGraphTransition_Load
    // 0x001f0648 NavSectorFlags_AllowsAgent_maybe: whether `character` may take the transition: its type bits (>> 3)
    // meet the allowed ones (unless they are 0x80: any), its mode bits (& 7) meet them, and its radius (+0x04) is not
    // above the allowed one.
    uint8_t AllowsCharacter(const CPFCharacter* character) const;

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
