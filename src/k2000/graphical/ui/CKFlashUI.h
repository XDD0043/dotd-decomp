// CKFlashUI.h - one Flash interface: a Maestro movie with the Flash animations, texts, messages and hot
// spots bound to it (key 0x6cd, vtable 0xb16070, size 0x23c). Original unit: CKFlashUI.cpp
// (0x6d460-0x722f8). XXL2: K/KModules/KGL/2d/Maestro/Manager/CKFlashUI.h (base IKUObjectInfos, which
// DotD does not register: the PS3 chain is IKSerializable). XXL2's Load reads the same members in the
// same order; DotD adds the words at +0x218..+0x234 and reads 40 input label ids instead of 16.
//
// Method names: XXL2's where the PS3 function does the same thing (the Ghidra name follows in the
// comment); the PS3 address is on each.
#pragma once
#include <cstdint>

#include "Renderware/rt2d/Rt2dTypes.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKSector;
class IKFlashObject;
class IKTime;
class CKFlashMessageIn;

// XXL2 CRt2dObjectInfos (16 bytes there; here the 12 bytes of a TMapItem value on the PS3).
struct CRt2dObjectInfos {
    uint8_t m_bIsVisible;   // +0x00
    Rt2dObject* m_pParent;  // +0x04
};

// XXL2 TMapItem<Rt2dObject*, CRt2dObjectInfos> (0x10 bytes on the PS3, OperatorNew(0x10)).
struct CKFlashUI_ObjectInfosItem {
    Rt2dObject* m_key;                   // +0x00
    CRt2dObjectInfos m_val;              // +0x04 (visible byte +0x04, parent +0x08)
    CKFlashUI_ObjectInfosItem* m_pNext;  // +0x0c
};
DOTD_ASSERT_SIZE(CKFlashUI_ObjectInfosItem, 0x10);
DOTD_ASSERT_OFFSET(CKFlashUI_ObjectInfosItem, m_pNext, 0x0c);

// XXL2 TMap<Rt2dObject*, CRt2dObjectInfos> (Ghidra HashTableU32; own vtable 0xb160c8: +0x00/+0x04 the
// destructors 0x998d50 / 0x998e90, +0x08 KeyToHashIndex 0x998cf8, +0x0c IsKeysEqual 0x998d10,
// +0x10 SetValue 0x998d30, +0x14 ClearValue 0x998cf0). Filled by the PostLoad and the per-frame
// visibility refresh. SetAt and GetPtrToAssoc are inlined by every user (one copy here).
struct CKFlashUI_ObjectInfosMap {
    virtual ~CKFlashUI_ObjectInfosMap();  // 0x00998d50 HashTableU32_Destructor_5: the items, then the buckets
    // 0x00998cf8 HashTableU32_HashKey_5: key % bucket count (divwu). The key is the object's address: on
    // a host the buckets (and so the iteration order) differ from the PS3's; no ported user depends on
    // the order (each entry is updated independently).
    virtual uint32_t KeyToHashIndex(Rt2dObject* key) const;
    // 0x00998d10 HashTableU32_KeysEqual_5
    virtual uint8_t IsKeysEqual(Rt2dObject* a, Rt2dObject* b) const { return a == b ? 1 : 0; }
    // 0x00998d30 HashTableU32_InitNode_5: key, then the visible byte and the parent.
    virtual void SetValue(CKFlashUI_ObjectInfosItem* item, Rt2dObject* key, CRt2dObjectInfos value) {
        item->m_key = key;
        item->m_val.m_bIsVisible = value.m_bIsVisible;
        item->m_val.m_pParent = value.m_pParent;
    }
    virtual void ClearValue(CKFlashUI_ObjectInfosItem* /*item*/) {}  // 0x00998cf0 KStub_Nop_998cf0

    // Inlined (XXL2 TMap::GetPtrToAssoc): the item of key, or null.
    CKFlashUI_ObjectInfosItem* GetPtrToAssoc(Rt2dObject* key) const;
    // Inlined (XXL2 TMap::SetAt): replaces the value of key (ClearValue, SetValue), or makes a new item
    // (OperatorNew(0x10)) at the head of its bucket.
    void SetAt(Rt2dObject* key, CRt2dObjectInfos value);

    uint32_t m_ui32Count;                       // +0x04 XXL2 m_ui32Count (0 from the constructor)
    uint32_t m_ui32HashSize;                    // +0x08 XXL2 m_ui32HashSize (0x25)
    CKFlashUI_ObjectInfosItem** m_ppHashTable;  // +0x0c OperatorNewArray(0x94), zeroed
};
DOTD_ASSERT_SIZE(CKFlashUI_ObjectInfosMap, 0x10);

class CKFlashUI : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x1b)
    DOTD_DECLARE_FACTORIES(CKFlashUI)

    // m_baFlags bits (XXL2 CBitArray; the meanings are from the PS3 users).
    enum : uint32_t {
        kStateMask = 0x3,          // XXL2 EInterfaceState: 0 stopped, 1 paused (0x6d510), 2 started (0x6e418)
        kDontUpdate = 0x8,         // skipped by the manager's update, render and visit loops
        kForceInputWhenLocked = 0x10,  // XXL2 GetInterfaceForceInputUpdateWhenLocked
        kNeverRender = 0x20,       // XXL2 SetUpdateButNeverRender; cleared by the Load
        kHotSpotsHidden = 0x40,    // set when the hot spots were hidden; Update clears it _maybe
        kFixedTimeStep = 0x80,     // Update steps the movie by 0x0aa948's 0.02 s instead of the frame time
        kOneInputPerFrame = 0x100, // Update stops scanning the input labels after the first press
    };

    CKFlashUI();  // 0x0006e820 CKFlashUI_Construct (inlined in 0x6edc8 CKFlashUI_Create)
    // vt+0x00 / +0x04 0x000705b8 / 0x70478: the message queue emptied, then the map's destructor. The
    // tables and the maestro (Rt2dMaestroDestroy) are freed by Destroy (vt+0x10, 0x6f030), not here.
    ~CKFlashUI() override { m_ui32FlashMessageInQueuedNb = 0; }
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x6cd || key == 0xc; }  // vt+0x08 0x998e70
    void Destroy() override;                                // vt+0x10 0x0006f030 CKFlashUI_Destroy
    int32_t MessageProc(uint16_t, void*) override { return 1; }            // vt+0x1c 0x6d4b0 CKFlashUI_MessageProc
    void RecursiveRegistration(int32_t /*type*/) override {}  // vt+0x24 0x6e520 (returns 1)
    int32_t Save(IKFile* /*file*/, int32_t /*type*/) override { return 1; }   // vt+0x28 0x6e518
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x0006fc48 CKFlashUI_Load
    int32_t PostLoad(int32_t type) override;                // vt+0x30 0x00071f48 CKFlashUI_PostLoad

    // --- the interface state (XXL2 names) -------------------------------------------------------------
    void PreUpdate(IKTime* /*time*/) {}       // 0x0006d508 KStub_Nop_6d508 (XXL2 PreUpdate)
    void Update(IKTime* time);                 // 0x00071040 CKFlashUI_Update_maybe
    void Render(IKTime* time);                 // 0x0006f280 DrawFlashUISceneAndSynchronizeWidgets
    void StartInterface(uint8_t visible);      // 0x0006f6e0 CKFlashUI_Show_maybe
    void StopInterface(uint8_t hide);          // 0x0006f8b0 CKFlashUI_Hide_maybe
    void PauseInterface();                     // 0x0006d510 CKFlashUI_SetPaused_maybe
    void ResumeInterface();                    // 0x0006e418 CKFlashUI_SetPlaying_maybe
    void HideInterfaceHierarchy(uint8_t hide); // 0x0006f3d0 CKFlashUI_SetHidden_maybe
    void HideAllHotSpotHierarchy();            // 0x0006dff0 CKFlashUI_HideLinkedWidgets_maybe
    uint8_t IsInterfaceVisible();              // 0x0006daa0 CKFlashUI_IsSceneVisible_maybe
    void PostMessage(int32_t labelId);         // 0x0006dce0 CKFlashUI_SendMaestroMessage_maybe
    void TranslateMessageIn(int32_t labelId);  // 0x0006d820 CKFlashUI_QueueMessageIn_maybe
    void UpdateRt2dObjectInfo();               // 0x00070cc0 CKFlashUI_RefreshVisibilityCache_maybe
    uint8_t IsRt2dObjectVisible(Rt2dObject* object);  // 0x0006ecc0 CKFlashUI_IsObjectVisible_maybe
    // 0x00070ac0 CKFlashUI_RegisterObjectOwnerInHashTable_maybe: SetAt(object, {0, parent}).
    void SetRt2dObjectParent(Rt2dObject* object, Rt2dObject* parent);
    void InitializeMaestroScenePosition();     // 0x0006ea78 CKFlashUI_UpdateScreenTransform_maybe
    void RefreshSceneLTM();                    // 0x0006ec78 CKFlashUI_RefreshSceneLTM_maybe
    // 0x0006d7a0 CKFlashUI_GetScreenScaleAndRect_maybe (XXL2 GetMaestroScaleWidthAndHeight)
    void GetMaestroScaleWidthAndHeight(float* scaledWidth, float* scaledHeight, Rt2dBBox* bbox) const;
    void GetMovieSize(float* width, float* height) const;  // 0x0006d7d8 CKFlashUI_GetMovieSize_maybe
    void ResetElements();                      // 0x0006d5e0 CKFlashUI_ResetElements_maybe
    void RefreshTexts();                       // 0x0006dc58 FlashTextGroup_RefreshAll_maybe (XXL2 RefreshTexts)
    void ReloadTextFonts();                    // 0x0006e3a8 FlashUI_ReapplyTextFonts_maybe
    void ApplyFontsToTexts();                  // 0x0006dbe8 CKFlashUI_ApplyFontsToTexts_maybe
    void ApplyFontsToTexts2();                 // 0x0006e8f8 CKFlashUI_ApplyFontsToTexts_2_maybe
    void SyncHotSpotAttachedObjects();         // 0x0006ded0 CKFlashUI_SyncWidgetBindings_maybe
    void UpdateHotSpots();                     // 0x0006df70 CKFlashUI_UpdateWidgetBindings_maybe (XXL2 UpdateHotSpot)
    void StopAndNotifyElements();              // 0x0006f9e8 CKFlashUI_ProcessMaestroMessagesAndNotifyElements_maybe
    Rt2dObject* GetMaestroScene();             // inlined everywhere: the maestro's scene, or null without one
    void BindSceneObjects();                   // 0x0006e608 CKFlashUI_BindSceneObjects_maybe (XXL2 CheckAndInitializeAllFlashObjects)
    void CreateRt2dObjectMapFromAllObjects();  // 0x00071720 CKFlashUI_ResolveElementsAndIndexScene_maybe

    IKSerializable** m_apFlashAnimation;   // +0x04 CKFlashAnimation references (Mem_AllocAligned16)
    IKSerializable** m_apFlashText;        // +0x08 CKFlashText references
    IKSerializable** m_apFlashMessageIn;   // +0x0c CKFlashMessageIn references
    IKSerializable** m_apFlashMessageOut;  // +0x10 CKFlashMessageOut references
    IKSerializable** m_apObjectsToWarn;    // +0x14 the objects Update sends message 0x2300 to
    IKSerializable** m_apHotSpot;          // +0x18 CFlashHotSpot references
    uint32_t m_ui32FlashAnimNb;            // +0x1c
    uint32_t m_ui32FlashTextNb;            // +0x20
    uint32_t m_ui32FlashMessageInNb;       // +0x24
    uint32_t m_ui32FlashMessageOutNb;      // +0x28
    uint32_t m_ui32FlashObjectToWarnNb;    // +0x2c
    uint32_t m_ui32HotSpotNb;              // +0x30
    CKFlashUI_ObjectInfosMap m_mMap;       // +0x34 XXL2 m_mMap: the scene objects the flash objects use
    uint32_t m_baFlags;                    // +0x44 (XXL2 CBitArray): read, then bit 5 cleared (XXL2 and 0xdf)
    int32_t m_ai32InputLabelId[40];        // +0x48 (XXL2 Int32[16]) the button label sent per input action
    int32_t m_i32RestartInterfaceButton;   // +0xe8 the label StopInterface sends
    Rt2dMaestro* m_pMaestro;               // +0xec Rt2dMaestroStreamRead, only when the 0x1b1 chunk is found
    IKSerializable* m_pSoundDico;          // +0xf0 CKSoundDictionaryID reference
    CKFlashMessageIn* m_vpFlashMessageIn[64];  // +0xf4 XXL2 TVectorStatic<CKFlashMessageIn*, 64> (not read)
    uint32_t m_ui32FlashMessageInQueuedNb; // +0x1f4 its count (0 from the constructor)
    // +0x1f8 XXL2 m_MaestroBbox: the movie in screen-height units (0, 0, width / height, 1); set by
    // InitializeMaestroScenePosition.
    Rt2dBBox m_MaestroBbox;
    float m_fScaledWidth;                  // +0x208 XXL2: 1 / movie height (the scene's x scale)
    float m_fScaledHeight;                 // +0x20c XXL2: 1 / movie height (the scene's y scale)
    float m_fMovieWidth_maybe;             // +0x210 (DotD) 1 / m_fScaledWidth (600.0 for the menus)
    float m_fMovieHeight_maybe;            // +0x214 (DotD) 1 / m_fScaledHeight (600.0)
    IKSerializable* m_pUnk218;             // +0x218 a reference (passed to 0xaa948 with kFixedTimeStep)
    // +0x21c (DotD) a colour multiplier applied to every shape and string of the scene by Update when its
    // alpha (+0x228) is not -1 (StartInterface and Update set the alpha to -1). Not set otherwise.
    RwRGBAReal m_cColorMult_maybe;
    uint32_t m_ui32Unk22c;                 // +0x22c (-1 from the constructor; PostLoad applies the fonts when not 0)
    CKSector* m_pSector;                   // +0x230 a reference: the interface runs only while its bit 0 is set
    uint32_t m_ui32Alignment_maybe;        // +0x234 0 left, 1 centred, 2 right (InitializeMaestroScenePosition)
    float m_fOffsetX_maybe;                // +0x238 (0 from the constructor) the centring offset in movie pixels
};
DOTD_ASSERT_SIZE(CKFlashUI, 0x23c);
DOTD_ASSERT_OFFSET(CKFlashUI, m_apFlashAnimation, 0x04);
DOTD_ASSERT_OFFSET(CKFlashUI, m_apFlashText, 0x08);
DOTD_ASSERT_OFFSET(CKFlashUI, m_apFlashMessageIn, 0x0c);
DOTD_ASSERT_OFFSET(CKFlashUI, m_apFlashMessageOut, 0x10);
DOTD_ASSERT_OFFSET(CKFlashUI, m_apObjectsToWarn, 0x14);
DOTD_ASSERT_OFFSET(CKFlashUI, m_apHotSpot, 0x18);
DOTD_ASSERT_OFFSET(CKFlashUI, m_ui32FlashAnimNb, 0x1c);
DOTD_ASSERT_OFFSET(CKFlashUI, m_ui32HotSpotNb, 0x30);
DOTD_ASSERT_OFFSET(CKFlashUI, m_mMap, 0x34);
DOTD_ASSERT_OFFSET(CKFlashUI, m_baFlags, 0x44);
DOTD_ASSERT_OFFSET(CKFlashUI, m_ai32InputLabelId, 0x48);
DOTD_ASSERT_OFFSET(CKFlashUI, m_i32RestartInterfaceButton, 0xe8);
DOTD_ASSERT_OFFSET(CKFlashUI, m_pMaestro, 0xec);
DOTD_ASSERT_OFFSET(CKFlashUI, m_pSoundDico, 0xf0);
DOTD_ASSERT_OFFSET(CKFlashUI, m_vpFlashMessageIn, 0xf4);
DOTD_ASSERT_OFFSET(CKFlashUI, m_ui32FlashMessageInQueuedNb, 0x1f4);
DOTD_ASSERT_OFFSET(CKFlashUI, m_MaestroBbox, 0x1f8);
DOTD_ASSERT_OFFSET(CKFlashUI, m_fScaledWidth, 0x208);
DOTD_ASSERT_OFFSET(CKFlashUI, m_fScaledHeight, 0x20c);
DOTD_ASSERT_OFFSET(CKFlashUI, m_fMovieWidth_maybe, 0x210);
DOTD_ASSERT_OFFSET(CKFlashUI, m_fMovieHeight_maybe, 0x214);
DOTD_ASSERT_OFFSET(CKFlashUI, m_pUnk218, 0x218);
DOTD_ASSERT_OFFSET(CKFlashUI, m_cColorMult_maybe, 0x21c);
DOTD_ASSERT_OFFSET(CKFlashUI, m_ui32Unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKFlashUI, m_pSector, 0x230);
DOTD_ASSERT_OFFSET(CKFlashUI, m_ui32Alignment_maybe, 0x234);
DOTD_ASSERT_OFFSET(CKFlashUI, m_fOffsetX_maybe, 0x238);

// 0x0006e500 CameraContext_GetReferenceAspect_maybe: the camera context's +0x80 (4:3 = 1.3333).
float CameraContext_GetReferenceAspect();
// 0x0006da18 Rt2dScene_ApplyColorMultiplierToChildren_maybe: the colour multiplier on every string and shape below
// `scene` (Rt2dSceneForAllChildren with Rt2dObject_SetColorMultiplierRecursiveCB_maybe 0x6db28 and {ui, multiply}).
// CKFlashAnimation_ApplyColorMultiplier_maybe 0x73fd0 calls it; CKFlashUI's own copy is inline in its update.
void Rt2dScene_ApplyColorMultiplierToChildren(CKFlashUI* ui, struct Rt2dObject* scene, struct RwRGBAReal* multiply);
