// IKModule.h - base of the engine modules (key 0x33e; XXL2: K/KCore/Interfaces/IKModule.h): CKGraphic,
// CKInput, CKSoundManager, CKServiceManager. Slots +0x94..+0xac are XXL2's slots 31..37 (CKGraphic,
// CKInput, CKSoundManager and CKServiceManager override the same ones in both games); +0xb0 is DotD's.
// The defaults at 0x993088..0x9930b0 are empty functions.
#pragma once
#include <cstdint>

#include "k2000/core/IKUpdatable.h"

class IKTime;

class IKModule : public IKUpdatable {
public:
    int32_t GetSerializationFlags() override { return 0; }  // vt+0x34 0x993090 (KStub_Return0)
    // vt+0x94. InitializeCKGameLoopSubsystems passes &AppConfig; 1 = ok. XXL2: InitializeModule(CKParams*)
    // returning a KError.
    virtual int32_t InitializeModule(void* params) = 0;
    virtual void DestroyModule() = 0;                // vt+0x98
    virtual void PreUpdate(IKTime* frameClock) = 0;  // vt+0x9c GameLoop, before UpdateGame (CKInput_PreUpdate)
    virtual void PostUpdate(IKTime* frameClock) = 0; // vt+0xa0 GameLoop, after the render
    virtual void UpdateInitialize() {}               // vt+0xa4 0x993088; UpdateGame's pending-reset path
    virtual void UpdateLocalizedData() {}            // vt+0xa8 0x9930a0 (XXL2: Bool, CKUErrorReporting*; PS3 arguments unverified)
    virtual void DestroyLocalizedData() {}           // vt+0xac 0x9930a8
    virtual void VfB0() {}                           // vt+0xb0 0x9930b0 (DotD)
};
