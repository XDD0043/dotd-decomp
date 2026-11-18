// CinematicCameraTrack.cpp - reconstructed original translation unit 0x7e318-0x7e978 (GAME_TOC1, main_toc1), 2 functions, 2 live.
// Primary owner: CinematicCameraTrack (not a registered class): the cinematic stream's channel type 1 (the camera).
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x7e318  CinematicCameraTrack_Update_maybe
//   [x] 0x7e878  CinematicCameraTrack_Release_maybe
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/components/CKCinematicStreamCpnt.h"
#include "k2000/misc/Engine.h"
#include "crt/ppc_ops.h"
#include "crt/xlround.h"

namespace {

// The camera leaves the cinematic owners (+0xe14, the last one moved into its place) and, when one is current, the
// service is told to switch back (+0x470 cleared; unless +0x46c bit 4, the transition reset and bit 22 set).
void ReleaseCamera(CKSrvCamera* service, IKSerializable* camera) {
    const uint32_t count = service->m_unke24;
    for (uint32_t i = 0; i < count; ++i) {
        if (service->m_apCinematicOwner[i] != camera) continue;
        const uint32_t last = count - 1;
        service->m_unke24 = last;
        if (i != last) service->m_apCinematicOwner[i] = service->m_apCinematicOwner[last];
        break;
    }
    if (service->m_pCurrentCamera == nullptr) return;
    service->m_pNextCamera = nullptr;
    if ((service->m_baTemporaryFlags & 0x10) != 0) return;
    service->m_ui8TransitionMode = 0;
    service->m_fSwitchTimer = 0.0f;
    service->m_baTemporaryFlags = (service->m_baTemporaryFlags & 0xffbfffffu) | 0x400000u;
}

}  // namespace

// 0x0007e878 CinematicCameraTrack_Release_maybe (type 1's slot +0x14, Finish)
void CinematicCameraTrack_Release(SCinematicStreamTrackType* type, uint32_t /*withMedia*/) {
    ReleaseCamera(static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera), type->m_pChannel->m_pUnk04);
}

// 0x0007e318 CinematicCameraTrack_Update_maybe (type 1's slot +0x20): on the segment's first frame the stream camera is
// switched to and owned; then its position, target, fov and roll interpolated between the track's two keys around the
// segment time. 1 while keys are left; stopped, the camera is released.
uint8_t CinematicCameraTrack_Update(SCinematicStreamTrackType* type) {
    IKCamera* camera = static_cast<IKCamera*>(type->m_pChannel->m_pUnk04);
    CKSrvCamera* service = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    if (type->m_bStopped != 0) {
        ReleaseCamera(service, camera);
        return 0;
    }
    if (type->m_bFirst != 0 && service->m_pCurrentCamera != camera) {
        service->m_pNextCamera = camera;
        if ((service->m_baTemporaryFlags & 0x10) == 0) {
            service->m_ui8TransitionMode = 0;
            service->m_fSwitchTimer = 0.0f;
            service->m_baTemporaryFlags = (service->m_baTemporaryFlags & 0xffbfffffu) | 0x400000u;
        }
        bool owned = false;
        for (uint32_t i = 0; i < service->m_unke24; ++i) {
            if (service->m_apCinematicOwner[i] == camera) {
                owned = true;
                break;
            }
        }
        if (!owned) service->m_apCinematicOwner[service->m_unke24++] = camera;
        camera->Vf9C(0);  // vt+0x9c
        camera->VfA4(0);  // vt+0xa4
        camera->VfAC(1);  // vt+0xac
    }
    if (type->m_bPlaying == 0 || camera == nullptr) return 0;
    const SCinematicCameraTrack* track = static_cast<const SCinematicCameraTrack*>(type->m_pChunk->m_pData);
    if (track == nullptr) return 0;
    double time;
    uint32_t index;
    if (type->m_ui32FrameRate != 0) {
        index = type->m_ui32FrameInSegment;
        time = static_cast<double>(index) / static_cast<double>(type->m_ui32FrameRate);  // fdiv
    } else {
        time = type->m_dSegmentTime;
        index = static_cast<uint32_t>(crt::lroundf(static_cast<float>(time * static_cast<double>(track->m_ui32NbFrames))));
    }
    if (index >= track->m_ui32NbKeys) return 0;
    const SCinematicCameraKey* key0 = &track->m_pKeys[index];
    const SCinematicCameraKey* key1 = index + 1 < track->m_ui32NbKeys ? key0 + 1 : key0;
    float a;      // f4: the weight of the second key
    float minusA; // f5
    float oneMinusA;  // f27
    if (type->m_ui32FrameRate != 0) {
        a = 0.0f;
        minusA = -0.0f;
        oneMinusA = 1.0f;
    } else {
        const float span = key1->m_af[8] - key0->m_af[8];  // fsubs
        if (span <= 0.0f) {
            a = 0.0f;
            minusA = -0.0f;
            oneMinusA = 1.0f;
        } else {
            a = static_cast<float>((time - static_cast<double>(key0->m_af[8])) / static_cast<double>(span));
            minusA = -a;
            oneMinusA = 1.0f - a;
        }
    }
    float fov = ppc::fmadds(oneMinusA, key0->m_af[3], a * key1->m_af[3]);
    if (fov < 179.0f) {
        if (!(fov > 1.0f)) fov = 1.0f;
    } else {
        fov = 179.0f;  // TOC -0x69e8 (also NaN)
    }
    camera->m_WorldPosition.x = ppc::fmadds(a, key1->m_af[0], ppc::fmadds(key0->m_af[0], minusA, key0->m_af[0]));
    camera->m_WorldPosition.y = ppc::fmadds(a, key1->m_af[1], ppc::fmadds(key0->m_af[1], minusA, key0->m_af[1]));
    camera->m_WorldPosition.z = ppc::fmadds(a, key1->m_af[2], ppc::fmadds(key0->m_af[2], minusA, key0->m_af[2]));
    camera->m_WorldTarget.x = ppc::fmadds(a, key1->m_af[4], ppc::fmadds(key0->m_af[4], minusA, key0->m_af[4]));
    camera->m_WorldTarget.y = ppc::fmadds(a, key1->m_af[5], ppc::fmadds(key0->m_af[5], minusA, key0->m_af[5]));
    camera->m_WorldTarget.z = ppc::fmadds(a, key1->m_af[6], ppc::fmadds(key0->m_af[6], minusA, key0->m_af[6]));
    camera->Vf88(ppc::fmadds(oneMinusA, key0->m_af[7], a * key1->m_af[7]));  // vt+0x88 (fmuls, fmadds)
    camera->m_unk18 = fov;
    return index + 1 < track->m_ui32NbKeys ? 1 : 0;
}
