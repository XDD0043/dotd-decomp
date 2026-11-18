// CContainer2d.h - a named group of 2D nodes in two scenes, the buttons and the others (key 0x4cd,
// vtable 0xb15ab0, size 0x38). Original unit: CContainer2d.cpp (0x600b0-0x61ab8). XXL2:
// K/KModules/KGL/2d/CContainer2d.h, the same members in the same order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/ui/IKNode2d.h"

class CContainer2d : public IKNode2d {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x13)
    DOTD_DECLARE_FACTORIES(CContainer2d)

    CContainer2d();  // inlined in 0x000614f0 CContainer2d_Create (out-of-line copy 0x60c70 unreferenced)
    ~CContainer2d() override {}                             // vt+0x00 / +0x04  0x997ae8 / 0x997aa0
    int32_t IsKindOfClass(uint32_t key) override {          // vt+0x08 0x997a78
        return key == 0x4cd || key == 0x24d || key == 0xc;
    }

    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x000611b0 CContainer2d_Load
    const char* GetName() override { return m_szName; }     // vt+0x4c 0x601d8
    // vt+0x80 0x00061820 CContainer2d_Scale: Scale on every node of the button scene, then of the others.
    void Scale(const CVector2& scale) override;
    // vt+0x58 0x00060bf0 CContainer2d_OnEvent_maybe: the event to both scenes.
    void RecursiveNodeReach(uint8_t what, void* data) override;
    // vt+0x84 0x00060db8 DrawUIContainerChildScenes: when enabled, both scenes' Render (+0x30 first)
    // inside a pushed Rt2d CTM.
    void Render(IKTime* frameClock) override;
    // vt+0x24 0x00060100 CContainer2d_RecursiveRegistration: unless the type is 4..7, registered with the saving manager,
    // then both scenes' (no null test).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x54 0x00060b10 CContainer2d_ResetRuntime_maybe (FreeMemory): IKNode2d's, the name freed, the button loop off.
    void FreeMemory() override;
    // vt+0x78 0x00061938 CContainer2d_GetBoundingRect: (1, 1, 0, 0), then every node's box of the button scene and of
    // the others (the walk of Scale) folded in. BUG(original): all four corners keep the smaller value (the maximum
    // too), and an unordered compare stores the node's value (ble).
    void GetBoundingBox(CBox2D* box) const override;

    // The container's own slots (XXL2 CContainer2d, shifted by DotD's +0x7c and one more slot after RemoveNode).
    // vt+0x88 0x00060b68 CContainer2d_SetNameString_maybe (XXL2 SetName): a copy of `name` (null keeps the old one).
    virtual void SetName(const char* name);
    // vt+0x8c 0x00060ee8 CContainer2d_vf8C (XXL2 SelectButton): the button at `index` selected (IKButton2d vt+0x88).
    virtual bool SelectButton(uint32_t index);
    // vt+0x90 0x000607d8 CContainer2d_vf90 (XXL2 AddNode): a button (type 2) into the button scene and selected, any
    // other node into the other scene.
    virtual uint8_t AddNode(IKNode2d* node);
    // vt+0x94 0x00060e70 CContainer2d_vf94 (XXL2 RemoveNode): out of the button scene (type 2) or the other.
    virtual IKNode2d* RemoveNode(IKNode2d* node);
    // vt+0x98 0x000607a8 / +0x9c 0x00060778 (XXL2 RemoveButton / RemoveNonButton): the node at `index` removed.
    virtual IKNode2d* RemoveButton(uint32_t index);
    virtual IKNode2d* RemoveNonButton(uint32_t index);
    // vt+0xa0 0x000606e8 / +0xa4 0x00060688: a button one place up / down (CScene2d SwapChildWithPrev / Next).
    virtual uint8_t ButtonGoUp(IKNode2d* node);
    virtual uint8_t ButtonGoDown(IKNode2d* node);
    // vt+0xa8 0x00060748 / +0xac 0x00060718: a non-button to the head / tail (MoveChildToHead / Tail). Names ours.
    virtual uint8_t NonButtonToHead(IKNode2d* node);
    virtual uint8_t NonButtonToTail(IKNode2d* node);
    // vt+0xb0 0x000606b8 / +0xb4 0x00060658: a non-button one place up / down.
    virtual uint8_t NonButtonGoUp(IKNode2d* node);
    virtual uint8_t NonButtonGoDown(IKNode2d* node);
    // vt+0xb8 0x000601e8 / +0xbc 0x000601f8 (XXL2 EnableButtonLoop / DisableButtonLoop): +0x34 = 1 / 0.
    virtual void EnableButtonLoop() { m_bButtonLoop = 1; }
    virtual void DisableButtonLoop() { m_bButtonLoop = 0; }
    // vt+0xc0 0x000616c0 / +0xc4 0x00061560 (XXL2 PreviousButton / NextButton): from the selected button, the
    // previous / next enabled one (wrapping with the button loop) selected; 1 when one was.
    virtual uint8_t PreviousButton();
    virtual uint8_t NextButton();
    // vt+0xc8 .. +0xdc (XXL2 HideButtons .. ShowAll): CScene2d HideChildren / ShowChildren of the button scene, the
    // other scene, or both (both run; 1 when both returned non-zero).
    virtual uint8_t HideButtons();
    virtual uint8_t HideNonButtons();
    virtual uint8_t HideAll();
    virtual uint8_t ShowButtons();
    virtual uint8_t ShowNonButtons();
    virtual uint8_t ShowAll();

    char* m_szName;                       // +0x28 Mem_AllocAligned16(length + 1); null for a negative length
    IKSerializable* m_pButtonObjects;     // +0x2c CScene2d (a reference)
    IKSerializable* m_pNonButtonObjects;  // +0x30 CScene2d (a reference)
    uint8_t m_bButtonLoop;                // +0x34 (+0x35..+0x37: padding the original never writes)
};
DOTD_ASSERT_SIZE(CContainer2d, 0x38);
DOTD_ASSERT_OFFSET(CContainer2d, m_szName, 0x28);
DOTD_ASSERT_OFFSET(CContainer2d, m_pButtonObjects, 0x2c);
DOTD_ASSERT_OFFSET(CContainer2d, m_pNonButtonObjects, 0x30);
DOTD_ASSERT_OFFSET(CContainer2d, m_bButtonLoop, 0x34);
