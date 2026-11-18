// CKFlashUICinematicBloc.h - a cinematic bloc that shows a Flash interface for a sekens (key 0x8c8, vtable 0xb1b318, size
// 0x54). Original unit: CKFlashUICinematicBloc.cpp (0x17a760-0x17bfd8). XXL2: CKFlashUICinematicBloc with m_uiState,
// m_iSekens (a sekens reference here), m_pFlashUI and the four Flash messages in the same order. No level file holds the
// class: nothing exercises it.
//
// The state (+0x38): 0 opening (waiting for the opening-end message), 1 open (the sekens runs), 2 closing (waiting for the
// closing-end message). The bloc's flag bits (m_DataFlags): 0x100 the inputs of configuration 1 while it shows, 0x200 that
// configuration's state before (restored at the end), 0x400 the sekens to request, 0x800 the interface is linked to the
// subtitles (its hot spots hidden while they are off: CKSrvSekensor +0x2c bit 0).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;
class IKTime;
class CKFlashUI;
class CKFlashMessageIn;
class CKFlashMessageOut;
class CKSekens;

class CKFlashUICinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x23)
    DOTD_DECLARE_FACTORIES(CKFlashUICinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x0017b228 CKFlashUICinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKFlashUICinematicBloc() {}
    ~CKFlashUICinematicBloc() override {}

    // vt+0x10 0x0017b220 CKFlashUICinematicBloc_Destroy: empty (the default).
    // vt+0x1c 0x0017ade0 CKFlashUICinematicBloc_MessageProc: the element's (0x500 / 0x501), then 0x2300 (a Flash message
    // in, `data`) drives the states while the bloc runs; the two answers combined (3, then 2, else the element's 0 or this one).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x0017ac78 CKFlashUICinematicBloc_RecursiveRegistration: the base's; in a level load the interface and the four
    // messages with type 0.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0017ba18 CKFlashUICinematicBloc_Load
    // vt+0x30 0x0017ac10 CKFlashUICinematicBloc_PostLoad: the base's; in a level load the interface hidden.
    int32_t PostLoad(int32_t type) override;

    void Start() override;                 // vt+0x5c 0x0017b538 CKFlashUICinematicBloc_Start
    void Complete() override;              // vt+0x64 0x0017aa38 CKFlashUICinematicBloc_Complete: the completion
    void Update(IKTime* time) override;    // vt+0x68 0x0017b280 CKFlashUICinematicBloc_Update
    void Stop() override;                  // vt+0x6c 0x0017b1b0 CKFlashUICinematicBloc_Stop
    void Abort() override;                 // vt+0x70 0x0017b148 CKFlashUICinematicBloc_Abort
    void Pause() override;                 // vt+0x78 0x0017b9b0 CKFlashUICinematicBloc_OnPause
    void Resume() override;                // vt+0x7c 0x0017b8f0 CKFlashUICinematicBloc_OnResume

    // 0x0017a870 CKFlashUICinematicBloc_ReleaseUIIfUnshared_maybe: the interface stopped (hidden) and the input configuration
    // 1 put back (flag 0x200), unless (without `force`) another running Flash UI bloc of a playing scene shows the same one.
    void ReleaseUIIfUnshared(int32_t force);
    // The subtitle link (inlined in Start, Update and Resume): with flag 0x800 and the subtitles off the interface's flag 0x20
    // set and its hot spots hidden; else that flag cleared.
    void ApplySubtitleLink();

    uint8_t m_uiState;                         // +0x38 read raw
    uint8_t m_pad39[3];
    CKSekens* m_pSekens;                       // +0x3c a reference (XXL2 m_iSekens)
    CKFlashUI* m_pFlashUI;                     // +0x40
    CKFlashMessageOut* m_pOpeningStartMsgOut;  // +0x44
    CKFlashMessageIn* m_pOpeningEndMsgIn;      // +0x48
    CKFlashMessageOut* m_pClosingStartMsgOut;  // +0x4c
    CKFlashMessageIn* m_pClosingEndMsgIn;      // +0x50
};
DOTD_ASSERT_SIZE(CKFlashUICinematicBloc, 0x54);
DOTD_ASSERT_OFFSET(CKFlashUICinematicBloc, m_uiState, 0x38);
DOTD_ASSERT_OFFSET(CKFlashUICinematicBloc, m_pSekens, 0x3c);
DOTD_ASSERT_OFFSET(CKFlashUICinematicBloc, m_pFlashUI, 0x40);
DOTD_ASSERT_OFFSET(CKFlashUICinematicBloc, m_pClosingEndMsgIn, 0x50);
