// RpLight.h - the RenderWare light as the light manager's rig uses it (C2.4 step 6). The manager keeps five lights
// (one ambient, four directional) and writes their colours and directions; the shaders read them back through the
// manager (LightRig_GetNextDistinctLight 0x9ae28, ShaderPassState_FillAmbientColorUniform 0xf52f0). RenderWare's
// own lighting of the world is not used by the PSGL shader path, so only the fields the game code touches are modelled
// (PS3 offsets): the object header (+0x00, parent = the frame of a directional light), the colour (+0x18, an
// RwRGBAReal) and the membership in the world (RenderWare keeps it in the inWorld link at +0x2c).
// The lights are added to the renderer's RpWorld (+0x34, RpWorld.h): its directional light list (ambient and directional
// lights) through the inWorld link; the world itself is the world plugin's light extension.
#pragma once
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwTypes.h"

struct RpWorld;

enum RpLightType : RwInt32 {
    rpLIGHTDIRECTIONAL = 1,
    rpLIGHTAMBIENT = 2,
    rpLIGHTPOINT = 0x80,     // the positional lights (RwPSGL_SetLocalLight_maybe; the game makes none)
    rpLIGHTSPOT = 0x81,
    rpLIGHTSPOTSOFT = 0x82,
};

// RpLight (RW 3.7 balight.h), then the world plugin's extension.
struct RpLight {
    RwObject object;      // +0x00 type 3 (rpLIGHT), subType = RpLightType, flags (+2: rpLIGHTLIGHTATOMICS 1),
                          //       privateFlags (+3: 1 for a grey colour), parent (+4) = the light's RwFrame
    RwLLLink lFrame;      // +0x08
    RwUInt32 sync;        // +0x10
    RwReal radius;        // +0x14
    RwReal color[4];      // +0x18 red, green, blue, alpha
    RwReal minusCosAngle; // +0x28
    RwLLLink WorldSectorsInLight;  // +0x2c RwLinkList of the sectors a positional light touches (empty here)
    RwLLLink inWorld;     // +0x34 the link in the world's light list (directional list for ambient / directional lights)
    RwUInt16 lightFrame;  // +0x3c
    RwUInt16 pad;         // +0x3e
    // The world plugin's light extension (PS3: light + [0xcec5c8]): the world the light is in, or null.
    RpWorld* world;
    // The PSGL driver's light extension (PS3: light + [0xcec628], registered by 0x6bae80; Ghidra PS3LightPlugin_*): the
    // soft spot's exponent (+0x00) and the attenuation coefficients (+0x04 constant, +0x08 linear, +0x0c quadratic),
    // which RwPSGL_SetLocalLight_maybe divides by the radius / its square. Its constructor 0x6ba398 gives 5, 1, 0, 5.
    RwReal psglSoftSpotExponent;
    RwReal psglAttenuation[3];
};
DOTD_ASSERT_OFFSET(RpLight, inWorld, 0x34);
DOTD_ASSERT_OFFSET(RpLight, color, 0x18);

// RWSRCGLOBAL(lightFrame) (the engine's +0xa): the lighting pass counter (RwPSGL_AtomicLightingCallback_maybe advances
// it, a light's lightFrame (+0x3c) remembers the pass that used it).
extern RwUInt16 g_rwLightFrame;
// 0x006a2970 RpLightCreate (through TocBridge 0x98e280): a white light of `type` lighting atomics and the world (flags
// 3), private flags 1, its light frame one behind the engine's.
RpLight* RpLightCreate(RwInt32 type);
// RpLightDestroy
RwBool RpLightDestroy(RpLight* light);
// 0x006b2e50 RpLightGetWorld: the world the light was added to, null when it is in none.
RpWorld* RpLightGetWorld(const RpLight* light);
// 0x006b2e68 RpWorldAddLight / 0x006b52d8 RpWorldRemoveLight
RpWorld* RpWorldAddLight(RpWorld* world, RpLight* light);
RpWorld* RpWorldRemoveLight(RpWorld* world, RpLight* light);
// 0x006a2be8 RpLightGetConeAngle: the arc cosine of -minusCosAngle (+0x28), the float acos inlined (fdlibm's
// reduction, the RW square root 0x75e738).
RwReal RpLightGetConeAngle(const RpLight* light);
// RwObjectHasFrameSetFrame: the object's frame (parent).
inline void RpLightSetFrame(RpLight* light, RwFrame* frame) { light->object.parent = frame; }
inline RwFrame* RpLightGetFrame(const RpLight* light) { return static_cast<RwFrame*>(light->object.parent); }
