// CKPlayVideoCinematicBloc.h - plays videos (key 0x888, vtable 0xb1b908, size 0x170). Original unit: CKPlayVideoCinematicBloc.cpp.
// XXL2: the same members in the same load order; DotD's path is 0x100 bytes and it adds +0x168/+0x16c.
// The three vectors are XXL2 TVector<T, 1, false> (block, capacity, count; Mem_AllocAligned16).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class CText2d;
class IKFile;
class IKTime;

class CKPlayVideoCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x22)
    DOTD_DECLARE_FACTORIES(CKPlayVideoCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    CKPlayVideoCinematicBloc();  // 0x001876c0 CKPlayVideoCinematicBloc_Create (the constructor inlined)
    ~CKPlayVideoCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001879f8 CKPlayVideoCinematicBloc_Load
    // The runtime slots (C2.3 step 2). PreActivate (vt+0x58 0x9a9f10) is empty.
    void Start() override;                              // vt+0x5c 0x00187ec8 CKPlayVideoCinematicBloc_Start
    void Complete() override;                           // vt+0x64 0x00188d38 CKPlayVideoCinematicBloc_Complete
    void Update(IKTime* time) override;                 // vt+0x68 0x001894b0 CKPlayVideoCinematicBloc_Update
    void Stop() override;                               // vt+0x6c 0x001887b0 CKPlayVideoCinematicBloc_Stop
    void Abort() override;                              // vt+0x70 0x00188628 CKPlayVideoCinematicBloc_Abort

    // 0x00188f88 CKPlayVideoCinematicBloc_PlayNextVideo_maybe: the current video's sekens stopped and its subtitle text
    // hidden; at the end of the list the bloc completes (after a screen fade when m_fFirstBlocFadeTime is set), else
    // the next video starts as a cutscene (flag 0x100000), the scene's picture blocs are told, and the video's sekens
    // (m_vi32SekIndex, subtitles) is requested.
    void PlayNextVideo();
    // 0x001882a8 CKPlayVideoCinematicBloc_UpdateSubtitles_maybe: the video's sekens follows the video's elapsed time.
    void UpdateSubtitles();
    // 0x00188b40 CKPlayVideoCinematicBloc_FinishVideo_maybe: the video (and its sekens) ended early (a skip): the current
    // video stopped, the sekens stopped, the pictures told.
    void FinishVideo();
    // 0x00187208 CKPlayVideoCinematicBloc_IsCurrentVideoSkippable_maybe
    uint8_t IsCurrentVideoSkippable() const;

    IKSerializable** m_vpVideo;            // +0x38 IKVideo references (GUID references in the files)
    uint32_t m_vpVideoCapacity;            // +0x3c 1 in the constructor
    uint32_t m_vpVideoCount;               // +0x40
    int32_t* m_vi32SekIndex;               // +0x44
    uint32_t m_vi32SekIndexCapacity;       // +0x48
    uint32_t m_vi32SekIndexCount;          // +0x4c
    uint8_t* m_vbSkipVideo;                // +0x50
    uint32_t m_vbSkipVideoCapacity;        // +0x54
    uint32_t m_vbSkipVideoCount;           // +0x58
    uint32_t m_ui32CurVideo;               // +0x5c runtime
    char m_szVideoPath[0x100];             // +0x60 runtime; the constructor clears the first byte
    uint16_t m_baInternalData;             // +0x160 0 in the constructor
    uint16_t m_pad162;
    float m_fFirstBlocFadeTime;            // +0x164
    CText2d* m_pSubtitleText;              // +0x168 DotD; every Load clears it; PlayNextVideo: the video's sekens' subtitle text
    IKSerializable* m_pColorizedScreenFx;  // +0x16c CColorizedScreenFx (Ghidra struct)
};
DOTD_ASSERT_SIZE(CKPlayVideoCinematicBloc, 0x170);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_vpVideo, +0x38);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_vpVideoCapacity, +0x3c);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_vpVideoCount, +0x40);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_vi32SekIndex, +0x44);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_vi32SekIndexCapacity, +0x48);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_vi32SekIndexCount, +0x4c);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_vbSkipVideo, +0x50);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_vbSkipVideoCapacity, +0x54);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_vbSkipVideoCount, +0x58);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_ui32CurVideo, +0x5c);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_szVideoPath, +0x60);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_baInternalData, +0x160);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_fFirstBlocFadeTime, +0x164);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_pSubtitleText, +0x168);
DOTD_ASSERT_OFFSET(CKPlayVideoCinematicBloc, m_pColorizedScreenFx, +0x16c);
