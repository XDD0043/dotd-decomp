// RpLight.h - the RenderWare light as the light manager's rig uses it (C2.4 step 6). The manager keeps five lights
// (one ambient, four directional) and writes their colours and directions; the shaders read them back through the
// manager (LightRig_GetNextDistinctLight 0x9ae28, ShaderPassState_FillAmbientColorUniform 0xf52f0). RenderWare's
// own lighting of the world is not used by the PSGL shader path, so only the fields the game code touches are modelled
// (PS3 offsets): the object header (+0x00, parent = the frame of a directional light), the colour (+0x18, an
// RwRGBAReal) and the membership in the world (RenderWare keeps it in the inWorld link at +0x2c).
// STUB(M2): the renderer's RpWorld (+0x34) is not created (CRenderer::InitializeStages), so "the world" of a light is
// a sentinel: RpWorldAddLight / RpWorldRemoveLight / RpLightGetWorld keep the add/remove state the game code branches on.
#pragma once
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwTypes.h"

struct RpWorld;

enum RpLightType : RwInt32 {
    rpLIGHTDIRECTIONAL = 1,
    rpLIGHTAMBIENT = 2,
};

// RpLight (PS3 0x40 here: RW's is 0x3c, the world link is one pointer).
struct RpLight {
    RwObject object;      // +0x00 type 3 (rpLIGHT), subType = RpLightType, flags (+2: rpLIGHTLIGHTATOMICS 1),
                          //       privateFlags (+3: 1 for a grey colour), parent (+4) = the light's RwFrame
    RwLLLink lFrame;      // +0x08
    RwUInt32 sync;        // +0x10
    RwReal radius;        // +0x14
    RwReal color[4];      // +0x18 red, green, blue, alpha
    RwReal minusCosAngle; // +0x28
    RpWorld* world;       // +0x2c STUB(M2): the sentinel world while the light is in it
    RwUInt32 pad[3];      // +0x30
};
DOTD_ASSERT_OFFSET(RpLight, color, 0x18);

// 0x006a2970 RpLightCreate (through TocBridge 0x98e280): an unlit white light of `type`.
RpLight* RpLightCreate(RwInt32 type);
// RpLightDestroy
RwBool RpLightDestroy(RpLight* light);
// 0x006b2e50 RpLightGetWorld: the world the light was added to, null when it is in none.
RpWorld* RpLightGetWorld(const RpLight* light);
// 0x006b2e68 RpWorldAddLight / 0x006b52d8 RpWorldRemoveLight
RpWorld* RpWorldAddLight(RpWorld* world, RpLight* light);
RpWorld* RpWorldRemoveLight(RpWorld* world, RpLight* light);
// RwObjectHasFrameSetFrame: the object's frame (parent).
inline void RpLightSetFrame(RpLight* light, RwFrame* frame) { light->object.parent = frame; }
inline RwFrame* RpLightGetFrame(const RpLight* light) { return static_cast<RwFrame*>(light->object.parent); }
