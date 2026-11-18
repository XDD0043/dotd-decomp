// CKMarkedSoundDico.h - the sounds of animation marks (DotD; not in XXL2) (key 0xab0c, vtable 0xb30180, size 0x30). Original unit: CKMarkedSoundDico.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/core/IKSerializable.h"

class IKFile;
class IKTime;
struct CVector3;

class CKMarkedSoundDico : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2ac)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xab0c || key == 0xc; }  // vt+0x08 0x9cd690
    DOTD_DECLARE_FACTORIES(CKMarkedSoundDico)

    CKMarkedSoundDico();  // 0x005ce5a8 CKMarkedSoundDico_Create (the constructor inlined)
    // 0x005cea98 CKMarkedSoundDico_Destructor (0x5cea18 deleting, 0x5ceb00 the same): the id vector's block freed, the
    // count and the block cleared.
    ~CKMarkedSoundDico() override;
    // vt+0x10 0x005ce608 CKMarkedSoundDico_Destroy: each listed id block deleted (the vector's block stays).
    void Destroy() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005ce678 CKMarkedSoundDico_Load

    // The position callback (+0x24 / +0x28, a PS3 pointer to member: +0x24 the function descriptor or the vtable offset
    // plus 1, +0x28 the adjustment of the owner +0x04): called with the owner and the sound index for each sound played.
    // Its only setter (CKBhvBlockAnimation_PostLoad) passes CKHkScriptedNPC_GetAnchorPosition_maybe 0x5c8c88 (the
    // descriptor 0x00bf45d8) and no adjustment: DotD keeps a plain function and the adjustment.
    using PositionCallback = CVector3* (*)(CVector3* out, IKSerializable* owner, uint32_t index);

    // 0x005cdf58 CKMarkedSoundDico_SetTimeline_maybe: the cinematic stream (+0x20).
    void SetTimeline(IKSerializable* stream) { m_unk20 = stream; }
    // 0x005cdf60 CKMarkedSoundDico_SetSourceMode_maybe: the marks from the stream (1) or the node's animation (0) (+0x18).
    void SetSourceMode(uint8_t fromStream) { m_unk18 = fromStream; }
    // 0x005cdf68 CKMarkedSoundDico_SetPositionCallback_maybe (the 8-byte pointer to member split into +0x24 / +0x28).
    void SetPositionCallback(PositionCallback callback, uint32_t adjust) {
        m_pfnPosition = callback;
        m_positionAdjust = adjust;
    }
    // vt+0x50 0x005ce268 CKMarkedSoundDico_UpdateFromAnimMarks_maybe: the sound mark (the game manager's vt+0x258, 0x1b)
    // crossed this frame, on the node's animation (+0x1c) or on the stream's channel 0 mark list (+0x20), plays its
    // sounds.
    virtual void UpdateFromAnimMarks(IKTime* clock);
    // 0x005cdfa0 CKMarkedSoundDico_PlaySoundsForMark_maybe: every listed id (+0x0c) equal to the mark value plays the
    // dictionary's (+0x08) sound value - 1 at the callback's position.
    void PlaySoundsForMark(uint32_t value);

    IKSerializable* m_unk04;  // +0x04 the callback's owner
    IKSerializable* m_unk08;  // +0x08 read first: a CKSoundDictionaryID
    uint32_t** m_apIds;       // +0x0c a vector of one-word blocks (operator new(4) each); 0
    uint32_t m_idsCapacity;   // +0x10 1
    uint32_t m_idsCount;      // +0x14 0
    uint8_t m_unk18;          // +0x18 the marks from the stream (SetSourceMode)
    uint8_t m_pad19[3];
    IKSerializable* m_unk1c;  // +0x1c a CAnimatedNode
    IKSerializable* m_unk20;  // +0x20 a CKCinematicStreamCpnt (SetTimeline)
    PositionCallback m_pfnPosition;  // +0x24 not set by the constructor nor the Load (SetPositionCallback)
    uint32_t m_positionAdjust;       // +0x28
    uint32_t m_idCount;       // +0x2c the number of words the Load reads
};
DOTD_ASSERT_SIZE(CKMarkedSoundDico, 0x30);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_unk04, +0x04);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_unk08, +0x08);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_apIds, +0x0c);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_idsCapacity, +0x10);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_idsCount, +0x14);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_unk18, +0x18);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_unk1c, +0x1c);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_unk20, +0x20);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_pfnPosition, +0x24);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_positionAdjust, +0x28);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_idCount, +0x2c);
