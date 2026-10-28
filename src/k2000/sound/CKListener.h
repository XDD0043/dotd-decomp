// CKListener.h - the sound listener (vtable 0xb197c8, 0x44 bytes; not a registered class). Original
// unit: SoundListener.cpp (0x110108-0x110e40; Ghidra names it SoundListener_*). XXL2:
// K/KModules/KSL/CKListener.h: DotD's Load reads the last three values XXL2's CKListener::Load reads
// (m_fDopplerScale, m_fRolloffFactor, m_fRatioVelocity, in that order) and the members before them sit
// in XXL2's order. SoundVoiceManager_Init_maybe creates it; SoundVoiceManager_Load_maybe loads it.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class IKFile;
class IKSerializable;
class IKTime;
struct RwaListener;

class CKListener {
public:
    CKListener();                                // 0x00110be0 SoundListener_Construct_maybe
    virtual ~CKListener() {}                     // STUB(C1.6): 0x9a6968
    int32_t Load(IKFile* file, int32_t type);    // 0x00110890 SoundListener_Load_maybe
    void Reset();                                // 0x00110108 SoundListener_Reset_maybe
    // 0x00110330 SoundListener_SetFollowCamera_maybe: the position follows the camera (non-zero) or the object.
    void SetFollowCamera(int32_t follow) { m_unk38 = follow != 0 ? 0u : 1u; }
    const CVector3* GetPosition();               // 0x001101a8 SoundListener_GetPosition_maybe
    void Update(IKTime* clock);                  // 0x00110368 SoundListener_Update_maybe
    CMatrix34* GetMatrix();                      // 0x001106f0 SoundListener_GetMatrix_maybe

    // +0x04 RwaListener_Create_maybe(4, 0, 0), handed to RwaPS3Driver_SetListener_maybe
    RwaListener* m_pRwaListener;
    IKSerializable* m_pLeafObjectAttachedForPosition;     // +0x08 SoundListener_SetPositionObject_maybe (a CSGLeaf in XXL2)
    IKSerializable* m_pLeafObjectAttachedForOrientation;  // +0x0c SoundListener_SetOrientationObject_maybe
    float m_fDopplerScale;    // +0x10 the constructor sets 1.0
    float m_fRolloffFactor;   // +0x14 1.0
    float m_fRatioVelocity;   // +0x18 1.0
    CVector3 m_vOldPosition;  // +0x1c the zero vector
    CVector3 m_unk28;         // +0x28 the zero vector; Update: the listener's velocity (panned sounds take it)
    // +0x34 RwMatrixCreate_Thunk, set to identity (flags 0x20003). STUB(RW): a plain allocation until the
    // RenderWare matrix pool exists.
    CMatrix34* m_pMatrix;
    uint32_t m_unk38;         // +0x38 position source: 1 object (SetPositionObject), 0 camera (SetFollowCamera)
    uint32_t m_unk3c;         // +0x3c orientation source, likewise (SetOrientationObject / SetOrientationFollowCamera)
    uint8_t m_unk40;          // +0x40 the constructor sets 1
    uint8_t m_pad41[3];
};
DOTD_ASSERT_SIZE(CKListener, 0x44);
DOTD_ASSERT_OFFSET(CKListener, m_pRwaListener, 0x04);
DOTD_ASSERT_OFFSET(CKListener, m_fDopplerScale, 0x10);
DOTD_ASSERT_OFFSET(CKListener, m_fRolloffFactor, 0x14);
DOTD_ASSERT_OFFSET(CKListener, m_fRatioVelocity, 0x18);
DOTD_ASSERT_OFFSET(CKListener, m_vOldPosition, 0x1c);
DOTD_ASSERT_OFFSET(CKListener, m_pMatrix, 0x34);
DOTD_ASSERT_OFFSET(CKListener, m_unk40, 0x40);
