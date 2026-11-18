// KBase620C.h - the position input blocks' unregistered base (key 0x620c, vtable 0xb1f730, size 0x28; Ghidra
// CKInputBlockPositionBase_620c_maybe_*). Original unit: CKInputBlockPositionBase.cpp (0x20da38-0x20ddd8, k2000/input).
// Base: KBase628C. Its class is PS3_CKInputBlockPosition (in no game file, outputs/remake/kp3-class-usage.json): a
// normalised screen position the left stick moves. Names ours.
//
// C2.8 port-all P06 wrote this header for PS3_CKInputBlockPosition (its constructor, Load, Destroy and OnActivate /
// OnDeactivate need it); the bodies are inline here and CKInputBlockPositionBase.cpp's checklist (P21's file) is left as it
// was: Construct 0x20dda0 / 0x20dd68, Load 0x20db98, OnActivate 0x20da80, OnDeactivate 0x20da38, vf10 0x20dc48
// (KBase628C's Destroy), vf24 0x20dc20 / vf28 0x20dbf8 (KBase628C's), BaseDestructor 0x20dc70, and the static
// initialiser 0x20dca0 (the "no position" vector 0xcea9a8 = (-1, -1): kNoPosition here).
#pragma once
#include <cstdint>

#include "Renderware/rwcore/RwRaster.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/core/Layout.h"
#include "k2000/input/KBase628C.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/input/CKInputBlockSequential.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvInput.h"

class KBase620C : public KBase628C {
public:
    // 0x0020da38's / 0x0020db98's vector 0xcea9a8, set to (-1, -1) by the static initialiser 0x20dca0 (TOC -0xe30).
    static constexpr float kNoPosition = -1.0f;

    KBase620C() {}  // 0x0020dda0 CKInputBlockPositionBase_620c_maybe_Construct: KBase628C's, then the vtable
    ~KBase620C() override {}

    // vt+0x2c 0x0020db98 CKInputBlockPositionBase_620c_maybe_Load: KBase628C's, then (level data only) no position.
    int32_t Load(IKFile* file, int32_t type) override {
        KBase628C::Load(file, type);  // 0x00209b38
        if (type == K_LEVEL_PLATEFORMS) {
            m_fX = kNoPosition;
            m_fY = kNoPosition;
        }
        return 1;
    }
    // vt+0x50 0x0020da80 CKInputBlockPositionBase_620c_maybe_OnActivate_maybe: KBase628C's (Activate); the input service's
    // position block (+0x24) and every parent sequence's (+0x48) this one; the screen size from the camera context's
    // final colour raster (its width and height as floats, 0 without a raster), the position its centre (0.5).
    void OnActivate() override {
        KBase628C::OnActivate();  // 0x00209a10
        static_cast<CKSrvInput*>(g_pEngine->m_srvInput)->m_unk24 = this;
        for (IKSerializable* p = m_unk08; p != nullptr; p = static_cast<KBase60CC*>(p)->m_unk08) {
            static_cast<CKInputBlockSequential*>(p)->m_unk48 = this;
        }
        const RwRaster* raster = static_cast<CameraContext*>(g_pEngine->m_cameraContext)->m_pFinalColorRaster;
        if (raster != nullptr) {
            m_fWidth = static_cast<float>(static_cast<double>(raster->width));    // fcfid + frsp
            m_fHeight = static_cast<float>(static_cast<double>(raster->height));
        } else {
            m_fHeight = 0.0f;
            m_fWidth = 0.0f;
        }
        m_fX = 0.5f;  // TOC -0xe38
        m_fY = 0.5f;
    }
    // vt+0x54 0x0020da38 CKInputBlockPositionBase_620c_maybe_OnDeactivate_maybe: KBase628C's (Deactivate), no position.
    void OnDeactivate() override {
        KBase628C::OnDeactivate();  // 0x00209a50
        m_fX = kNoPosition;
        m_fY = kNoPosition;
    }

    float m_fX;       // +0x18 the position in [0, 1] of the width (-1: none)
    float m_fY;       // +0x1c the position in [0, 1] of the height (-1: none)
    float m_fWidth;   // +0x20 the screen width (OnActivate)
    float m_fHeight;  // +0x24 the screen height (OnActivate)
};
DOTD_ASSERT_SIZE(KBase620C, 0x28);
DOTD_ASSERT_OFFSET(KBase620C, m_fX, 0x18);
DOTD_ASSERT_OFFSET(KBase620C, m_fHeight, 0x24);
