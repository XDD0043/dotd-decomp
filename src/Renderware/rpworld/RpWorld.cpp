// RpWorld.cpp - RpWorldCreate / RpWorldDestroy / RpWorldAddCamera (RW 3.7 world/baworld.c, baworobj.c). See RpWorld.h.
#include "Renderware/rpworld/RpWorld.h"

#include <cstring>

#include "Renderware/rwcore/RwFrameList.h"
#include "Renderware/rwcore/RwSList.h"

namespace {
// rwLinkListInitialize
void LinkListInitialize(RwLinkList* list) {
    list->link.next = &list->link;
    list->link.prev = &list->link;
}
constexpr RwUInt32 kIdWorld = 0xb;          // rwID_WORLD
constexpr RwUInt32 kMemHintDurEvent = 0x30000;  // rwMEMHINTDUR_EVENT
}  // namespace

// RpWorldCreate (baworld.c)
RpWorld* RpWorldCreate(const RwBBox* boundingBox) {
    RpWorld* world = static_cast<RpWorld*>(RwMalloc(sizeof(RpWorld), kIdWorld | kMemHintDurEvent));
    if (world == nullptr) return nullptr;
    std::memset(world, 0, sizeof(RpWorld));
    // rwObjectInitialize(world, rpWORLD, 0)
    world->object.type = rpWORLD;
    world->object.subType = 0;
    world->object.flags = 0;
    world->object.privateFlags = 0;
    world->object.parent = nullptr;
    // _rpMaterialListInitialize
    world->matList.materials = nullptr;
    world->matList.numMaterials = 0;
    world->matList.space = 0;
    world->renderOrder = rpWORLDRENDERBACK2FRONT;  // RpWorldSetRenderOrder
    world->flags = 0;                              // RpWorldSetFlags
    RpWorldSector* sector = static_cast<RpWorldSector*>(RwMalloc(sizeof(RpWorldSector), kIdWorld | kMemHintDurEvent));
    if (sector == nullptr) {
        RwFree(world);
        return nullptr;
    }
    std::memset(sector, 0, sizeof(RpWorldSector));
    sector->type = rwSECTORATOMIC;
    sector->repEntry = nullptr;
    sector->mesh = nullptr;
    LinkListInitialize(&sector->collAtomicsInWorldSector);
    LinkListInitialize(&sector->lightsInWorldSector);
    sector->numVertices = 0;
    sector->numTriangles = 0;
    sector->vertices = nullptr;
    sector->triangles = nullptr;
    sector->normals = nullptr;
    std::memset(sector->texCoords, 0, sizeof(sector->texCoords));
    sector->preLitLum = nullptr;
    sector->boundingBox.inf = boundingBox->inf;
    sector->boundingBox.sup = boundingBox->sup;
    sector->tightBoundingBox.inf = boundingBox->inf;
    sector->tightBoundingBox.sup = boundingBox->sup;
    sector->pipeline = nullptr;
    world->rootSector = sector;
    world->numTexCoordSets = 0;
    world->worldOrigin = RwV3d{0.0f, 0.0f, 0.0f};
    world->boundingBox.inf = boundingBox->inf;
    world->boundingBox.sup = boundingBox->sup;
    LinkListInitialize(&world->clumpList);
    world->numClumpsInWorld = 0;
    world->currentClumpLink = &world->clumpList.link;
    LinkListInitialize(&world->lightList);
    LinkListInitialize(&world->directionalLightList);
    world->renderCallBack = nullptr;  // RpWorldSetSectorRenderCallBack(world, NULL): the default
    world->pipeline = nullptr;
    // _rpWorldRegisterWorld, the plugin constructors and _rpWorldUnlock (the device's look at the sectors: an empty
    // atomic sector has nothing to instance) leave nothing the game reads.
    return world;
}

// RpWorldDestroy (baworld.c), for the empty world RpWorldCreate makes.
RwBool RpWorldDestroy(RpWorld* world) {
    RwFree(world->rootSector);
    RwFree(world);
    return 1;
}

// RpWorldAddCamera (baworobj.c)
RpWorld* RpWorldAddCamera(RpWorld* world, RwCamera* camera) {
    RwFrame* frame = RwCameraGetFrame(camera);
    if (frame != nullptr) RwFrameUpdateObjects(frame);  // invalidate the frame: the camera is positioned again
    camera->worldExt = world;
    return world;
}

// RpWorldRemoveCamera (baworobj.c)
RpWorld* RpWorldRemoveCamera(RpWorld* world, RwCamera* camera) {
    camera->worldExt = nullptr;
    return world;
}
