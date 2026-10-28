// capture_camera.h - the main camera taken from an RPCS3 capture (C2.4 exit; new platform debug code, off by default).
//
// DOTD_CAMERA_FROM=<capture.json>:<moment> (the file `work/rpcs3_frame_capture.py` writes; <moment> is a target name such
// as video_endp120 or control) gives the main RwCamera of that frame: its frame's LTM (right / up / at / pos), view
// window, view offset, near, far and fog planes, as `cameras.at_render.main` has them (`after_present` when the render
// read is missing). The renderer puts them on the main camera before SyncSceneCamerasAndClipPlanes, every frame, so a
// dotd frame is drawn from exactly the camera of the RPCS3 frame it is compared with (since step 5 the game's own
// camera, CKSrvCamera_UpdateFrame, drives the main camera; this option overrides it for comparisons). The
// capture's scene (far) camera is kept too, to check what SyncSceneCamerasAndClipPlanes derives from the main one.
#pragma once

namespace dotd::platform::capturecam {

struct CameraState {
    float right[3], up[3], at[3], pos[3];  // the frame's LTM rows
    float viewWindow[2];
    float viewOffset[2];
    float nearPlane, farPlane, fogPlane;
};

// True when DOTD_CAMERA_FROM is set and was read; the main and scene cameras of the moment.
bool Get(CameraState* main, CameraState* scene);

}  // namespace dotd::platform::capturecam
