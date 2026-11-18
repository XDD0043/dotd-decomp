// CKSrvSekensor.h - the sekens (scripted speech/subtitle sequence) service (key 0x281, vtable 0xb1eb98,
// size 0x50). Original unit: CKSrvSekensor.cpp (0x1f8450-0x1fa758). XXL2:
// K/KServices/KServiceSekensor/CKSrvSekensor.h: the sekens list is read the same way (and loaded again
// for the localisation); the GAME.KP3 part (+0x30..+0x40) is DotD's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

class CKSekens;

class CKSrvSekensor : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0xa)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b0f18
        return key == 0x281 || key == 0x1 || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSrvSekensor)

    CKSrvSekensor();  // inlined in 0x001fa000 CKSrvSekensor_Create
    ~CKSrvSekensor() override {}

    void Destroy() override;  // vt+0x10 0x001f9028 CKSrvSekensor_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f9858 CKSrvSekensor_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x001f8fa0 CKSrvSekensor_PostLoad
    // vt+0x38 0x001f9350 CKSrvSekensor_SetDefaultState: every sekens' SetDefaultState(flag & 0xff).
    void SetDefaultState(int32_t flag) override;
    // vt+0x50 0x001f9418 CKSrvSekensor_Start: no sekens (current, pending, secondary; byte +0x28 cleared), bit 1 of
    // +0x2c cleared, +0x48 9999.99.
    void Start() override;
    void Restart() override;                            // vt+0x54 0x1f8880 CKSrvSekensor_Restart (Stop's body)
    void Stop() override;                               // vt+0x68 0x1f8810 CKSrvSekensor_Stop
    // vt+0x70 0x001f9128 CKSrvSekensor_Pause: the subtitle texts (CKSekens +0x2c) of the current and the secondary sekens
    // hidden (vt+0x68).
    void Pause() override;
    void Resume() override {}                           // vt+0x78 0x1f8808 CKSrvSekensor_Resume (empty)
    // vt+0x7c 0x001fa2a0 UpdateCKSrvSekensor: a pending request that waited too long dropped; the current sekens (and the
    // secondary one) updated: a line that is over starts the next, a sekens that is over is stopped and the pending one
    // takes its place; the subtitles shown or hidden.
    void Update(IKTime* time) override;
    // 0x001f8588 CKSrvSekensor_GetCurrentSekens_maybe / 0x001f8590 GetPendingSekens_maybe
    CKSekens* GetCurrentSekens() const { return m_unk1c; }
    CKSekens* GetPendingSekens() const { return m_pPendingSekens; }
    // 0x001f93e8 CKSrvSekensor_GetSekens: the list's sekens at `index`, or null.
    CKSekens* GetSekens(uint32_t index) const;
    // 0x001f4728 CKSrvSekensor_IsSekensDone_maybe: it is neither the current nor the pending sekens.
    uint8_t IsSekensDone(const CKSekens* sekens) const { return sekens != m_unk1c && sekens != m_pPendingSekens ? 1 : 0; }
    // 0x001f8610 CKSrvSekensor_GetSekensTypeDelay_maybe: the delay of sekens type `index` (GAME.KP3 table), 0 past it.
    float GetSekensTypeDelay(uint32_t index) const;
    // 0x001f89b0 CKSrvSekensor_RequestSekens_maybe: asks for `sekens` to run now: 1 when it was taken (it becomes the
    // current one and Begin runs), 0 when refused (it is the current one, too soon, a speech sekens while the speech
    // is busy, ...); a secondary sekens (flag 9) runs beside the current one, a pending one waits.
    uint8_t RequestSekens(CKSekens* sekens);
    // 0x001f8ce0 CKSrvSekensor_StopSekens_maybe: the sekens stopped whether it is the current, the pending or the
    // secondary one (1), else 0. The pending sekens takes the place of a stopped current one.
    uint8_t StopSekens(CKSekens* sekens);
    // 0x001fa0a8 CKSrvSekensor_CancelSekens_maybe: as StopSekens, but a current sekens that cannot be interrupted
    // (flag 6 and its line says so) is only marked to stop when its line ends (+0x2c bit 1).
    uint8_t CancelSekens(CKSekens* sekens);
    // 0x001f86c8 CKSrvSekensor_RefreshSubtitleVisibility_maybe: the current and the secondary sekens' subtitle texts shown or hidden.
    void RefreshSubtitleVisibility();
    // vt+0x1c 0x001f9d50 CKSrvSekensor_MessageProc: 0xf08 stops the current sekens, 0xf09 stops it when it may be
    // interrupted (else it waits); the secondary sekens is stopped in both.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x94 0x001f8f38 CKSrvSekensor_InitializeService: the engine's sekensor, subtitles on (+0x2c bit 0)
    // and m_unk4c (ClassRegistry_CreateObjectByKey(0x5a8c), a CKStreamWave); returns 1.
    int32_t InitializeService() override;
    // 0x001f95f0 CKSrvSekensor_SetSubtitlesEnabled_maybe (the options): +0x2c bit 0, then the two running sekens'
    // subtitle texts shown or hidden.
    void SetSubtitlesEnabled(uint32_t enabled);
    // vt+0x98 0x001f8ec0 CKSrvSekensor_DestroyService: the engine's sekensor cleared, the GAME.KP3 words freed (the
    // capacity kept), the stream wave of InitializeService destroyed.
    void DestroyService() override;
    // vt+0xa0 0x001f9c48 CKSrvSekensor_UpdateLocalizedData: the speech wave's file (the level and voice language).
    void UpdateLocalizedData() override;
    // vt+0xa8 0x001f9450 CKSrvSekensor_vfA8: CKSekens::ForEachLineCallVf54 on every sekens (no virtual call of this slot
    // found in the original).
    virtual void VfA8(uint8_t a, uint32_t b);
    // vt+0xac 0x001f9770 CKSrvSekensor_RegisterSekens_maybe: the sekens appended to the list; returns 1 (no virtual call of
    // this slot found in the original).
    virtual int32_t RegisterSekens(IKSerializable* sekens);
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x001f94e8: every sekens' RecursiveRegistration
    // 0x001f88f0 CKSrvSekensor_IsCurrentSekensRunningWithFlag14Bit4_maybe (CKFlashUICinematicBloc_Update 0x17b280):
    // the current sekens' flags bit 4 while it runs, else 0.
    uint32_t IsCurrentSekensRunningWithFlag14Bit4() const;
    uint8_t IsCurrentSekensDone() const;                     // 0x001f8970 CKSrvSekensor_IsCurrentSekensDone
    CKSekens* FindSekensByUuid(const uint32_t* uuid) const;  // 0x001f91d8 CKSrvSekensor_FindSekensByUuid_maybe

    // +0x0c CKSekens* (XXL2 TVector<CKSekens*, 5, true>; DotD grows by 8).
    TVector<IKSerializable*, 8> m_vSekensList;
    int32_t m_i32CurrentIndex;           // +0x18 not set by the constructor or Load; RequestSekens: the current sekens' index in the list, -1 none
    CKSekens* m_unk1c;                   // +0x1c the current sekens; the constructor sets 0
    CKSekens* m_pPendingSekens;          // +0x20 not set by the constructor or Load; the sekens waiting to run
    CKSekens* m_unk24;                   // +0x24 a running sekens _maybe; the constructor sets 0
    uint32_t m_unk28;                    // +0x28 not set by the constructor or Load (byte +0x28: Stop clears it)
    uint32_t m_unk2c;                    // +0x2c flags: InitializeService sets bit 0
    // +0x30 GAME.KP3: words, byte-swapped (GAME: 0, 10.0, 30.0, 120.0, 300.0 as floats _maybe).
    TVector<uint32_t, 8> m_unk30;
    float m_unk3c;                       // +0x3c GAME.KP3 (10.0)
    float m_unk40;                       // +0x40 GAME.KP3 (30.0)
    float m_fRequestTime;                // +0x44 not set by the constructor or Load; the clock time of the last pending request
    float m_unk48;                       // +0x48 the constructor sets 0
    IKSerializable* m_unk4c;             // +0x4c CKStreamWave (InitializeService): the level's speech file
};
DOTD_ASSERT_SIZE(CKSrvSekensor, 0x50);
DOTD_ASSERT_OFFSET(CKSrvSekensor, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvSekensor, m_vSekensList, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvSekensor, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKSrvSekensor, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKSrvSekensor, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKSrvSekensor, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKSrvSekensor, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKSrvSekensor, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKSrvSekensor, m_unk4c, 0x4c);

// 0x001f8518 Platform_GetFileTag_maybe: "PS2", "WIN", "GCN", "XBX", "PSP", "XEN", "REV", "PS3" for 0..7, else null
// (CKCinematicStreamCpnt's stream paths take 7).
const char* Platform_GetFileTag(int32_t index);
void FormatSpeechExportWavPath(char* out, const char* root, int32_t language, int32_t sekens, int32_t line);  // 0x001f8e40
void FormatSpeechExportDir(char* out, const char* root, int32_t language);                                  // 0x001f8e88
