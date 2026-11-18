// CKFlashAnimation.h - a flash animation of an interface (key 0x78d, vtable 0xb16140, size 0x30; XXL2 has no
// class of this name). Original unit: CKFlashAnimation.cpp (0x73b10-0x74e30). No KP3 file of the game holds
// one (outputs/remake/kp3-class-usage.json), so CKFlashUI::m_ui32FlashAnimNb is always 0; the members here
// are the ones CKFlashUI_BindSceneObjects_maybe 0x6e608 reads and writes (its anim-label binding loop).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/ui/IKFlashObject.h"
#include "k2000/util/TVector.h"

struct Rt2dAnim;
struct Rt2dAnimProps;

// One animation instance (0x110 bytes; Ghidra CKFlashAnimEntry).
struct CKFlashAnimEntry {
    Rt2dAnim* m_pAnim;         // +0x00 Rt2dMaestroGetAnimationsByIndex of the label's entity
    Rt2dAnimProps* m_pProps;   // +0x04 the props FlashUI_FindMatchingAnimCB_maybe 0x6d528 finds for m_pAnim
    uint8_t m_unk08;           // +0x08 a byte (Load reads it; the new entries and vf54 set 0xff)
    uint8_t m_pad09[3];
    int32_t m_i32LabelIndex;   // +0x0c the anim label's index (Rt2dMaestroFindStringLabel); 0xffff until bound
    char m_szLabelName[0x100]; // +0x10 the anim label's name
};
DOTD_ASSERT_SIZE(CKFlashAnimEntry, 0x110);

class CKFlashAnimation : public IKFlashObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x1e)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x999128
        return key == 0x78d || key == 0x74d || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKFlashAnimation)

    // ---- C2.8 port-rest R02 (no game file holds one; ported from the disassembly).
    // 0x000749e8 CKFlashAnimation_Create: operator new(0x30), the vtable, the entry vector null, 1, 0 (the
    // IKFlashObject part is not set; zeroed here, the port's fresh heap).
    CKFlashAnimation();
    // 0x00074b90 CKFlashAnimation_Destructor (0x74b20 the deleting one): the entry block freed (not cleared).
    ~CKFlashAnimation() override;
    // vt+0x10 0x00999160 CKFlashAnimation_Destroy: IKFlashObject's, then the entry block freed and emptied.
    void Destroy() override;
    // vt+0x24 0x00073d98 CKFlashAnimation_RecursiveRegistration: IKFlashObject's (nothing); type 0: itself registered
    // with the saving manager (engine +0x50, vt+0x24, a null second argument).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x2c 0x00074bf8 CKFlashAnimation_Load: IKFlashObject's; one u32 count, a block of that many entries, each new
    // entry unbound (0xffff, no animation, byte 0xff, empty name); a level file then reads its byte and its label name
    // (length-prefixed) and clears its two pointers.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x00073d70 CKFlashAnimation_PostLoad: IKFlashObject's; 1 (inherited).
    // vt+0x50 0x00074598 CKFlashAnimation_vf50 (XXL2 GetRt2dObject): while the interface's sector is loaded, every entry's
    // animation scene (by its label's entity) appended.
    void GetRt2dObject(TVector<Rt2dObject*, 1>* objects) override;
    // vt+0x54 0x00073ec8 CKFlashAnimation_vf54: IKFlashObject's, then every entry unbound again (from the last one).
    void Vf54() override;
    // vt+0x60 0x00074720 CKFlashAnimation_GetFirstOnScreenObjectPos_maybe: the first shown entry scene whose anchor is
    // within [-3, 4] on both axes: its position and its size in movie pixels (the colour is not written); 1 when found.
    uint8_t GetScreenAnchor(CVector2* position, CVector2* size, uint8_t* rgba) override;
    // vt+0x64 0x00074108 CKFlashAnimation_vf64: every entry's scene into the interface's object map, without a parent.
    void RegisterObjects() override;
    // vt+0x68 0x00073fd0 CKFlashAnimation_ApplyColorMultiplier_maybe: the pending multiplier (alpha not -1) on the shown
    // entry scenes' children (from the last entry; the hidden ones skipped), then alpha = -1.
    void ApplyColorMultiplier() override;

    TVector<CKFlashAnimEntry, 1> m_vEntries;  // +0x24 (block, capacity +0x28, count +0x2c)
};
DOTD_ASSERT_SIZE(CKFlashAnimation, 0x30);
DOTD_ASSERT_OFFSET(CKFlashAnimation, m_vEntries, 0x24);
