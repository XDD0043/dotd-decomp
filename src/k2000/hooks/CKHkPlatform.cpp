// CKHkPlatform.cpp - reconstructed original translation unit 0x41e248-0x425b98 (GAME_TOC1, main_toc1), 51 functions, 41 live.
// Primary class: CKHkPlatform  key 0x3a42  category Hook  size 0x1f4  vtable 0xb26000
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x41e248  CKHkPlatform_Delete
//   [ ] 0x41e298  CKHkPlatform_SetFlagBit4_maybe  [dead]
//   [ ] 0x41e2b8  CKHkPlatform_ResetMotionState_maybe  [dead]
//   [ ] 0x41e430  FUN_0041e430  [dead]
//   [ ] 0x41e478  CKHkPlatform_GetFloat34_maybe  [dead]
//   [ ] 0x41e480  CKHkPlatform_SetFloat34_maybe  [dead]
//   [ ] 0x41e488  CKHkPlatform_GetFloat7C_maybe  [dead]
//   [ ] 0x41e490  CKHkPlatform_SetFloat7C_maybe  [dead]
//   [ ] 0x41e498  CKHkPlatform_IsAtStartProperty_maybe
//   [ ] 0x41e4c0  CKHkPlatform_IsAtEndProperty_maybe
//   [ ] 0x41e4e8  CKHkPlatform_vfF0
//   [ ] 0x41e4f0  RegisterCKHkPlatformClass
//   [ ] 0x41e568  _GLOBAL__I_41e568
//   [ ] 0x41e578  CKHkPlatform_SetNavBlocking_maybe
//   [ ] 0x41ea08  CKHkPlatform_StopLoopSound_2_maybe
//   [ ] 0x41ea98  CKHkPlatform_StopLoopSound_maybe
//   [ ] 0x41eb18  CKHkPlatform_StartMoveSounds_maybe
//   [ ] 0x41ec28  CKHkPlatform_EnsureLoopSoundPlaying_maybe
//   [ ] 0x41ecd8  CKHkPlatform_PlayWaypointFx_maybe
//   [ ] 0x41ef68  CKHkPlatform_Stop
//   [ ] 0x41ef90  CKHkPlatform_Start
//   [ ] 0x41efb8  CKHkPlatform_RecursiveRegistration
//   [x] 0x41f1d8  CKHkPlatform_DeleteArray
//   [x] 0x41f278  CKHkPlatform_Create
//   [ ] 0x41f310  CKHkPlatform_AttachSounds
//   [ ] 0x41f3a0  CKHkPlatform_IsMovingForwardProperty_maybe
//   [ ] 0x41f428  CKHkPlatform_IsMovingProperty_maybe
//   [ ] 0x41f468  CKHkPlatform_SetFloat80MaxOne_maybe  [dead]
//   [ ] 0x41f480  CKHkPlatform_SetInitialPathRatio_maybe  [dead]
//   [ ] 0x41f498  CKHkPlatform_GetInfo
//   [ ] 0x41f650  CKHkPlatform_Destroy
//   [ ] 0x41f698  CKHkPlatform_OnActivate
//   [ ] 0x41f8b8  CKHkPlatform_SetFlagBit20_maybe  [dead]
//   [ ] 0x41f8d8  CKHkPlatform_IsMovingBackwardProperty_maybe
//   [ ] 0x41f958  CKHkPlatform_vfD0
//   [x] 0x41fab0  CKHkPlatform_CreateArray
//   [ ] 0x41fbd0  CKHkPlatform_PostLoad
//   [ ] 0x41fc78  CKHkPlatform_OnDeactivate
//   [ ] 0x41fde0  CKHkPlatform_Restart
//   [ ] 0x41ffe8  CKHkPlatform_EvaluatePathPosition_maybe
//   [ ] 0x420270  CKHkPlatform_OrientAlongDirection_maybe
//   [ ] 0x4204a8  CKHkPlatform_SetPathDistance_maybe
//   [ ] 0x420630  CKHkPlatform_vfC8
//   [ ] 0x4207c0  CKHkPlatform_SimulateSwaySpring_maybe
//   [ ] 0x421020  CKHkPlatform_SetDefaultState
//   [x] 0x4212a0  CKHkPlatform_Load
//   [ ] 0x422518  CKHkPlatform_Save
//   [ ] 0x423620  CKHkPlatform_UpdateMotion_maybe
//   [ ] 0x423f70  CKHkPlatform_AdvanceAlongPath_maybe
//   [ ] 0x424690  CKHkPlatform_Update
//   [ ] 0x425378  CKHkPlatform_MessageProc
//
//   [ ] 0x9c2ff8  CKHkPlatform_IsKindOfClass  [inline]
//   [ ] 0x9c3050  CKHkPlatform_GetClassType  [inline]
//   [ ] 0x9c3058  CKHkPlatform_GetClassID  [inline]
//   [ ] 0x9c3060  CKHkPlatform_Destructor  [inline]
//   [ ] 0x9c3090  CKHkPlatform_DeletingDestructor  [inline]
#include "k2000/hooks/CKHkPlatform.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// 0x00c50d64 (TOC1 +0x4d18 points at it): the null vector (statically and live (0, 0, 0)).
const CVector3 kVectorZero = {0.0f, 0.0f, 0.0f};

// One read of count words, then each word byte-swapped (the PS3's Read(count * 4) + lwbrx per word).
void ReadFloatWords(IKFile* file, float* dst, uint32_t count) {
    uint32_t w[4];
    ReadU32LEWords(file, w, count);
    std::memcpy(dst, w, count * sizeof(uint32_t));
}

// Mem_AllocAligned16(count * 4) then one contiguous reference read (vt+0x28) of count references.
IKSerializable** AllocAndReadRefs(IKFile* file, uint8_t count) {
    IKSerializable** refs =
        static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(count * sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, refs, count);
    return refs;
}
}  // namespace

// 0x004212a0 CKHkPlatform_Load
int32_t CKHkPlatform::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_unk20);
        m_apUnk24 = AllocAndReadRefs(file, m_unk20);
        IKFile_ReadRef(file, &m_unk28);
        IKFile_ReadRef(file, &m_unk2C);
        for (float& value : m_unk30) ReadF32LE(file, &value);
        for (float& value : m_unk5C) ReadF32LE(file, &value);
        ReadFloatWords(file, &m_vPositionOffset.x, 3);
        ReadFloatWords(file, &m_vStartPath.x, 3);
        ReadFloatWords(file, &m_vDirPath.x, 3);
        ReadFloatWords(file, m_qBaseOrientation, 4);
        for (float& value : m_unk50) ReadF32LE(file, &value);
        ReadU8(file, &m_unk10D);  // read into a stack byte, then stored
        for (float& value : m_unk110) ReadF32LE(file, &value);
        ReadU8(file, &m_unk134);
        if (m_unk134 == 0) {
            m_apUnk138 = nullptr;
        } else {
            m_apUnk138 = AllocAndReadRefs(file, m_unk134);
        }
        ReadF32LE(file, &m_unk13C);
        ReadF32LE(file, &m_unk140);
        IKFile_ReadRef(file, &m_unkBC);
        m_unkFC.Load(file, K_LEVEL_PLATEFORMS);
        m_unk104.Load(file, K_LEVEL_PLATEFORMS);
        for (IKSerializable*& ref : m_unk144) IKFile_ReadRef(file, &ref);
        for (uint8_t& value : m_unk154) ReadU8(file, &value);
    }

    // Inlined InitVariables (XXL2 CKHkPlatform::InitVariables), for every serialization type.
    m_fTimer = 0.0f;
    m_fPositionOnPath = m_unk30[4] * m_unk5C[4];  // fmuls +0x40 * +0x6c
    m_pfPoint = kVectorZero;
    m_pfPointIndex = 0xffff;
    // m_bitArray: bit 27 cleared, bits 24..26 = bits 10..12, bit 9 = bit 13, bit 28 cleared, then bits 29..30
    // cleared (rlwinm sequence at 0x42136c..0x421490).
    uint32_t bits = m_bitArray & 0xf7ffffffu;
    bits = (bits & 0xf0ffffffu) | ((bits & 0x1c00u) << 14);
    bits = (bits & ~0x200u) | (((bits >> 13) & 1u) << 9);
    bits &= ~0x10000000u;
    m_qLastSlopeRotation[0] = 0.0f;
    m_qLastSlopeRotation[3] = 1.0f;
    m_qLastSlopeRotation[1] = 0.0f;
    m_qLastSlopeRotation[2] = 0.0f;
    m_qLastPathRotation[2] = m_qBaseOrientation[2];
    m_qLastPathRotation[0] = m_qBaseOrientation[0];
    m_qLastPathRotation[1] = m_qBaseOrientation[1];
    m_qLastPathRotation[3] = m_qBaseOrientation[3];
    m_vPosition = kVectorZero;
    m_unk1A8 = 0.0f;
    m_unk1AC = kVectorZero;
    m_unk1B8 = kVectorZero;
    m_unk1C4 = 0;
    m_unk1C8 = kVectorZero;
    m_unk1D4 = kVectorZero;
    m_bitArray = bits & 0x9fffffffu;
    return 1;
}
