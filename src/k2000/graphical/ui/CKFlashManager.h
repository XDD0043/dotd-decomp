// CKFlashManager.h - the list of Flash interfaces (key 0x70d, vtable 0xb16018, size 0x14). Created by the
// renderer (InitializeRendererStages, then Rt2dDevice_Init_maybe), handed to the loader by CKGraphic.
// Original unit: CKFlashManager.cpp (0x6c6e8-0x6d460). XXL2: K/KModules/KGL/2d/Maestro/Manager/
// CKFlashManager.h, the same members in the same order (the first two read by Load in the same order).
// Method names: XXL2's where the PS3 function does the same thing.
#pragma once
#include <cstdint>

#include "Renderware/rt2d/Rt2dTypes.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKFlashUI;
class CKInputDico;
class IKTime;

class CKFlashManager : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x1c)
    DOTD_DECLARE_FACTORIES(CKFlashManager)

    CKFlashManager();  // inlined in 0x0006d268 CKFlashManager_Create (copy 0x6ca18 unreferenced)
    ~CKFlashManager() override;                                             // vt+0x00 / +0x04  0x6d3d0 / 0x6d370
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x70d || key == 0xc; }  // vt+0x08 0x998cc0
    void Destroy() override;                                                // vt+0x10 0x0006d130 CKFlashManager_Destroy
    int32_t MessageProc(uint16_t, void*) override { return 1; }                            // vt+0x1c 0x6c798
    // vt+0x24 0x6c738 CKFlashManager_RecursiveRegistration: with type 0, registers itself with the saving
    // manager (engine +0x50 vt+0x24). STUB(C1.6): the saving manager is not ported.
    int32_t Load(IKFile* file, int32_t type) override;                      // vt+0x2c 0x0006cfa0 CKFlashManager_Load
    int32_t GetSerializationFlags() override { return 0; }                  // vt+0x34 0x998cb8

    // 0x0006c9b8 Rt2dDevice_Init_maybe (XXL2 InitializeManager): Rt2dAnim opened, the curve flatness 500,
    // the default message queue 0x100; no interfaces yet. InitializeRendererStages calls it right after
    // the creation.
    void InitializeManager();
    // 0x0006c990 UI2D_DestroyRt2dFreeLists_maybe (XXL2 DestroyManager): Rt2dAnimClose.
    void DestroyManager();
    // 0x0006c878 CKFlashManager_BindPlayerInputMapping_maybe (XXL2 SetInputConfig): the "Flash Manager"
    // input project's dico of that player, with actions 0xe and 4..9 enabled.
    void SetInputConfig(uint8_t player);
    CKInputDico* GetInputDico() { return m_pInputDico; }  // 0x0006c7a0 CKFlashManager_GetInputMapping_maybe
    void PreUpdate(IKTime* time);         // 0x0006cb20 CKFlashManager_VisitVisibleUIs_maybe
    void Update(IKTime* time);            // 0x0006cef8 CKFlashManager_UpdateAllUIs_maybe
    void Render(IKTime* time);            // 0x0006ce58 DrawFlashUIManagerEntries
    void RefreshSize();                   // 0x0006cd30 CKFlashManager_UpdateScreenTransforms_maybe
    void RefreshAllTexts();               // 0x0006cbc0 FlashTextRegistry_RefreshAll_maybe
    void ReloadAllTextFonts();            // 0x0006cc30 FlashUIList_ReapplyTextFonts_maybe
    // 0x0006cca0 CKFlashManager_ApplyFontsToAllUIs_maybe (XXL2 UpdateLocalizedData; the arguments unused)
    void UpdateLocalizedData(uint8_t first, void* errors);
    void Stop();                          // 0x0006cda0 FlashUIList_HideAllShown_maybe (XXL2 Stop)
    CKFlashUI* GetInterfaceByIndex(uint32_t index) const;  // XXL2 (inlined on the PS3)

    // 0x0006d180 CKFlashUI_MaestroMessageHandler_maybe (XXL2 HandleMaestroEvent): every maestro's message
    // handler. getURL messages (type 7) queue the matching CKFlashMessageIn of the interface that owns the
    // maestro; every message then goes to the default handler.
    static Rt2dMessage* HandleMaestroEvent(Rt2dMaestro* maestro, Rt2dMessage* message);

    uint32_t m_ui32NbFlashUI;      // +0x04
    IKSerializable** m_apFlashUI;  // +0x08 CKFlashUI references (Mem_AllocAligned16)
    CKInputDico* m_pInputDico;     // +0x0c XXL2 m_pInputDico: set by SetInputConfig
    uint8_t m_bLockInputUpdate;    // +0x10 XXL2 m_bInputLocked/SetLockInputUpdate _maybe; InitializeManager clears it
};
DOTD_ASSERT_SIZE(CKFlashManager, 0x14);
DOTD_ASSERT_OFFSET(CKFlashManager, m_ui32NbFlashUI, 0x04);
DOTD_ASSERT_OFFSET(CKFlashManager, m_apFlashUI, 0x08);
DOTD_ASSERT_OFFSET(CKFlashManager, m_pInputDico, 0x0c);
DOTD_ASSERT_OFFSET(CKFlashManager, m_bLockInputUpdate, 0x10);
