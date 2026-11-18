// RpWorld.h - the RenderWare 3.7 world (world/baworld.c, baworobj.c) as the renderer creates it: CRenderer's
// InitializeRendererStages 0x9f620 makes one empty world (RpWorldCreate with the box +-100000) at renderer +0x34 and adds
// the main, UI and scene cameras to it (RpWorldAddCamera). The level's geometry is not in the world: it hangs in the
// K scene graph and draws through the render queues, so the world keeps its single empty atomic sector. The lights of the
// light rig are added to it (RpWorldAddLight, RpLight.cpp).
//
// Layout: RW 3.7's (32-bit pointers, as on the PS3). The plugin registries of the world and the sector
// (worldTKList / sectorTKList: the collision, MatFX and PS3 driver extensions) carry no data the game reads.
#pragma once
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwTypes.h"

struct RpMaterial;
struct RpLight;

// RwLinkList (bacolor.h / balist.h): a link list's terminator.
struct RwLinkList {
    RwLLLink link;
};
DOTD_ASSERT_SIZE(RwLinkList, 0x8);

// RpWorldSector (basector.h), the atomic sector of a world without geometry (rwSECTORATOMIC -1).
struct RpWorldSector {
    RwInt32 type;                       // +0x00
    void* triangles;                    // +0x04
    RwV3d* vertices;                    // +0x08
    void* normals;                      // +0x0c
    void* texCoords[8];                 // +0x10 rwMAXTEXTURECOORDS
    RwRGBA* preLitLum;                  // +0x30
    void* repEntry;                     // +0x34
    RwLinkList collAtomicsInWorldSector;  // +0x38
    RwLinkList lightsInWorldSector;     // +0x40
    RwBBox boundingBox;                 // +0x48
    RwBBox tightBoundingBox;            // +0x60
    void* mesh;                         // +0x78
    void* pipeline;                     // +0x7c
    RwUInt16 matListWindowBase;         // +0x80
    RwUInt16 numVertices;               // +0x82
    RwUInt16 numTriangles;              // +0x84
    RwUInt16 pad;                       // +0x86
};
DOTD_ASSERT_SIZE(RpWorldSector, 0x88);

// RpTie (bapipew.h / baworld.h): an atomic's tie to a world sector, linked in the atomic's llWorldSectorsInAtomic (+0x64,
// RpAtomic.h) by lWorldSectorInAtomic (PS3 +0x0c). None exists here: the game adds no atomic to a world.
struct RpTie {
    RwLLLink lAtomicInWorldSector;   // +0x00
    RpAtomic* apAtom;                // +0x08
    RwLLLink lWorldSectorInAtomic;   // +0x0c
    RpWorldSector* worldSector;      // +0x14
};
// RpLightTie: a positional light's tie to a world sector, linked in the sector's lightsInWorldSector (+0x40) by
// lightInWorldSector (+0x00). None exists here: the game makes no positional light.
struct RpLightTie {
    RwLLLink lightInWorldSector;     // +0x00
    RpLight* light;                  // +0x08
    RwLLLink WorldSectorInLight;     // +0x0c
    RpWorldSector* sect;             // +0x14
};

enum : RwInt32 { rwSECTORATOMIC = -1 };
enum : RwUInt8 { rpWORLD = 7 };
enum RpWorldRenderOrder : RwInt32 { rpWORLDRENDERNARENDERORDER = 0, rpWORLDRENDERFRONT2BACK = 1, rpWORLDRENDERBACK2FRONT = 2 };

// RpWorld (baworld.h).
struct RpWorld {
    RwObject object;                    // +0x00 type rpWORLD
    RwUInt32 flags;                     // +0x08
    RwInt32 renderOrder;                // +0x0c RpWorldRenderOrder
    RpMaterialList matList;             // +0x10
    RpWorldSector* rootSector;          // +0x1c (an RpSector*: the atomic sector here)
    RwInt32 numTexCoordSets;            // +0x20
    RwInt32 numClumpsInWorld;           // +0x24
    RwLLLink* currentClumpLink;         // +0x28
    RwLinkList clumpList;               // +0x2c
    RwLinkList lightList;               // +0x34
    RwLinkList directionalLightList;    // +0x3c
    RwV3d worldOrigin;                  // +0x44
    RwBBox boundingBox;                 // +0x50
    void* renderCallBack;               // +0x68 RpWorldSectorCallBackRender
    void* pipeline;                     // +0x6c RxPipeline*
};
DOTD_ASSERT_SIZE(RpWorld, 0x70);
DOTD_ASSERT_OFFSET(RpWorld, rootSector, 0x1c);
DOTD_ASSERT_OFFSET(RpWorld, boundingBox, 0x50);

// RpWorldCreate (library, TocBridge 0x98e2d0): a world with one empty atomic sector of the box, render order back to
// front, no flags, no materials, clumps or lights.
RpWorld* RpWorldCreate(const RwBBox* boundingBox);
// RpWorldDestroy: the sector and the world freed (the world holds no clumps or lights by then).
RwBool RpWorldDestroy(RpWorld* world);
// RpWorldAddCamera (library, TocBridge 0x98e2e0; baworobj.c): the camera's frame marked dirty (RwFrameUpdateObjects:
// the camera is positioned again), the camera's world extension set to the world.
RpWorld* RpWorldAddCamera(RpWorld* world, RwCamera* camera);
// RpWorldRemoveCamera (baworobj.c): the camera's world extension cleared.
RpWorld* RpWorldRemoveCamera(RpWorld* world, RwCamera* camera);
// RwCameraGetWorld (baworobj.h macro): the camera's world extension.
inline RpWorld* RwCameraGetWorld(const RwCamera* camera) { return camera->worldExt; }
