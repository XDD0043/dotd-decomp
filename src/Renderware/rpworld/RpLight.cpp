// RpLight.cpp - the light rig's RenderWare light (see RpLight.h).
#include "Renderware/rpworld/RpLight.h"

#include <cstring>

namespace {
// The one world every light is added to while the renderer has no RpWorld of its own.
RpWorld* const kSentinelWorld = reinterpret_cast<RpWorld*>(static_cast<uintptr_t>(1));
}  // namespace

// 0x006a2970 RpLightCreate
RpLight* RpLightCreate(RwInt32 type) {
    RpLight* light = new RpLight();
    std::memset(light, 0, sizeof(RpLight));
    light->object.type = 3;  // rpLIGHT
    light->object.subType = static_cast<RwUInt8>(type);
    light->radius = 0.0f;
    for (float& channel : light->color) channel = 1.0f;
    light->minusCosAngle = 0.0f;
    return light;
}

RwBool RpLightDestroy(RpLight* light) {
    delete light;
    return 1;
}

// 0x006b2e50 RpLightGetWorld
RpWorld* RpLightGetWorld(const RpLight* light) { return light->world; }

// 0x006b2e68 RpWorldAddLight
RpWorld* RpWorldAddLight(RpWorld* world, RpLight* light) {
    light->world = world != nullptr ? world : kSentinelWorld;
    return world;
}

// 0x006b52d8 RpWorldRemoveLight
RpWorld* RpWorldRemoveLight(RpWorld* world, RpLight* light) {
    light->world = nullptr;
    return world;
}
