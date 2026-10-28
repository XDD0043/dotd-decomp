// CMenuManager.h - the menu scene and the flash message box (key 0x44d, vtable 0xb15c20, size 0x10).
// Original unit: CMenuManager.cpp (0x64208..). XXL2: K/KModules/KGL/2d/CMenuManager.h, the same members and
// Load. Created by CManager2d (its +0xa78); the global 13:17.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CMenuManager : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x11)
    DOTD_DECLARE_FACTORIES(CMenuManager)

    CMenuManager();                  // 0x00064618 CMenuManager_Create (inlined)
    ~CMenuManager() override {}      // STUB(C1.6): 0x997cc0 / 0x997c80
    // vt+0x08 0x997c60
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x44d || key == 0xc; }
    void Destroy() override { m_bEnabled = 0; }  // vt+0x10 0x64298 CMenuManager_Destroy
    // vt+0x2c 0x00064880 CMenuManager_Load: reads for every type (no type check), as XXL2.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x50 0x000642c8 DrawActiveUIMenu (the class's only slot past the root): the menu scene (+0x04)
    // rendered (its vt+0x5c; the original passes the frame context along) when enabled (+0x0c).
    virtual uint8_t DrawActiveUIMenu();

    // 0x00064538 CMenuManager_BroadcastEvent_maybe: the menu scene's nodes get the event.
    void BroadcastEvent(uint8_t event, void* data);

    IKSerializable* m_pMenuSceneContainers;  // +0x04 CScene2d reference
    IKSerializable* m_pFlashMessageBox;      // +0x08 CFlashMessageBox2d reference
    uint8_t m_bEnabled;                      // +0x0c
    uint8_t m_pad0d[3];                      // +0x0d never written
};
DOTD_ASSERT_SIZE(CMenuManager, 0x10);
DOTD_ASSERT_OFFSET(CMenuManager, m_pMenuSceneContainers, 0x04);
DOTD_ASSERT_OFFSET(CMenuManager, m_pFlashMessageBox, 0x08);
DOTD_ASSERT_OFFSET(CMenuManager, m_bEnabled, 0x0c);
