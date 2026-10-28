// KBaseE8D.h - an unregistered DotD-only base (key 0xe8d, vtable 0xb2b9c8, no members; no XXL2
// counterpart, so it keeps its placeholder name). Its only registered class is CFlashMessageBox2d (0xd0d).
// Its methods are inline (out-of-line copies at 0x9c84e8..0x9c8658). The pure slots hold
// __cxa_pure_virtual in the original; their signatures are CFlashMessageBox2d's (C1.6: from its code and
// its callers), the slot names are in CFlashMessageBox2d.h.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKLocText;
class IKTime;
struct SFlashMessageRequest;

class KBaseE8D : public IKSerializable {
public:
    // The interrupt callback of a message (XXL2 KpFnInterrupt, bool (*)()): a PS3 function descriptor.
    typedef uint8_t (*InterruptFn)();

    ~KBaseE8D() override {}                                                 // vt+0x00 / +0x04  0x9c8658 / 0x9c8618
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xe8d || key == 0xc; }  // vt+0x08 0x9c84e8
    int32_t GetClassType() override { return kCategoryGraphical; }          // vt+0x14 0x9c8508
    int32_t GetClassID() override { return 0x3a; }                          // vt+0x18 0x9c8510
    virtual int32_t ShowMessageModalLoc(CKLocText* text, int32_t type, int32_t button, InterruptFn interrupt,
                                        float unk, float timeout) = 0;      // vt+0x50
    virtual int32_t ShowMessageModal(const uint16_t* text, int32_t type, int32_t button, InterruptFn interrupt,
                                     float unk, float timeout, uint8_t timer) = 0;  // vt+0x54
    // vt+0x58 0x9c8520 / +0x5c 0x9c8528: 0xb (no answer yet).
    virtual int32_t ShowMessageLoc(CKLocText* /*text*/, int32_t /*type*/, int32_t /*button*/, InterruptFn /*interrupt*/,
                                   float /*unk*/, float /*timeout*/) {
        return 0xb;
    }
    virtual int32_t ShowMessage(const uint16_t* /*text*/, int32_t /*type*/, int32_t /*button*/, InterruptFn /*interrupt*/,
                                float /*unk*/, float /*timeout*/, uint8_t /*timer*/) {
        return 0xb;
    }
    virtual int32_t Vf60() { return 0xb; }                                  // vt+0x60 0x9c8530 (Ghidra: CFlashMessageBox2d_vf60; no caller found)
    virtual void ShowMessageBox() = 0;                                      // vt+0x64
    virtual void HideMessageBox() = 0;                                      // vt+0x68
    virtual int32_t IsMessageBoxShown() = 0;                                // vt+0x6c
    virtual void StopMessageBox(int32_t resetFade) = 0;                     // vt+0x70
    virtual void Render(IKTime* time) = 0;                                  // vt+0x74
    virtual void Vf78() = 0;                                                // vt+0x78
    virtual uint8_t UpdateMessage() { return 1; }                           // vt+0x7c 0x9c8538
    virtual uint8_t SetMessageText(CKLocText* /*text*/) { return 1; }       // vt+0x80 0x9c8540
    virtual uint8_t IsReady() = 0;                                          // vt+0x84
    virtual uint8_t IsFading() = 0;                                         // vt+0x88
    virtual IKSerializable* GetFlashInterface() { return nullptr; }         // vt+0x8c 0x9c8548
    virtual int32_t ProcessRequest(SFlashMessageRequest* request) = 0;      // vt+0x90
};
DOTD_ASSERT_SIZE(KBaseE8D, 0x4);
