// RpGeometry.h - RenderWare 3.7 RpWorld geometry, material and atomic calls as the Rt2d shapes use them
// (tool/2d shape.c builds one RpGeometry per shape rep and renders each shape as an RpAtomic), in the
// PS3 layout. PS3 code: RpGeometryCreate 0x6a1388, RpGeometryTriangleSetVertexIndices 0x6a0230,
// RpGeometryTriangleSetMaterial 0x6a0ec0, RpMorphTargetCalcBoundingSphere 0x6a1248, RwBBoxCalculate
// 0x744b10, RpGeometryUnlock 0x6a0a28, RpGeometryDestroy 0x6a1830, RpMaterialCreate 0x6a3908,
// RpMaterialDestroy 0x6a3ca0, RpMaterialSetTexture 0x6a3890, _rpMaterialListFindMaterialIndex
// 0x6a45a0, _rpMaterialListAppendMaterial 0x6a4a60, RpAtomicCreate 0x69cb58, RpAtomicSetFrame 0x69c270,
// RpAtomicSetGeometry 0x69ccb8, RpAtomicDestroy 0x69ecb0.
//
// The data model is the PS3 layout. C2.4 step 1 adds what the stream readers fill (rpworld/RpGeometryStream.cpp):
// the bin mesh (RpMeshHeader at +0x54), the PS3 native mesh data (+0x58: the pre-instanced vertex and index
// buffers of the PS3 driver, kept as the file has them), the skin plugin's bytes and the MatFX plugin.
// STUB(C1.4): RpGeometryUnlock's mesh building for geometries without a bin mesh (RpMeshes, tristrips);
// an atomic's default render callback draws the triangles per material (rwcore/RwDevice.h) and records the
// draw (the atomic, its frame's LTM, its geometry, the material colours and render states at that moment)
// in the frame's atomic draw list.
#pragma once
#include <vector>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwTypes.h"

struct RwStream;
struct RwTexture;
struct RwFrame;
struct RpGeometry;
struct RwMatrix;
class CMaterial;

// RwSurfaceProperties
struct RwSurfaceProperties {
    RwReal ambient;
    RwReal specular;
    RwReal diffuse;
};

// RpMatFX material data (plugin/matfx, PS3 layout): two effect slots of 0x30 bytes, the effect type at +0x20
// of each slot (rpMATFXEFFECT*), the effects flag word at +0x60. MatFXMaterialStreamRead_maybe 0x69a388,
// RpMatFXMaterialSetEnvMapCoefficient 0x697440 (finds the slot of type 2; no null check), ...
enum : RwUInt32 {
    rpMATFXEFFECTNULL = 0,
    rpMATFXEFFECTBUMPMAP = 1,
    rpMATFXEFFECTENVMAP = 2,
    rpMATFXEFFECTBUMPENVMAP = 3,
    rpMATFXEFFECTDUAL = 4,
    rpMATFXEFFECTUVTRANSFORM = 5,
    rpMATFXEFFECTDUALUVTRANSFORM = 6,
};
struct RpMatFXEffect {
    // +0x00: the union of the effect types; the fields that apply to each type are named after the PS3 code.
    union {
        struct {  // rpMATFXEFFECTENVMAP: +0x00 frame, +0x04 texture, +0x08 coefficient, +0x0c useFBAlpha
            void* frame;
            RwTexture* texture;
            RwReal coefficient;
            RwBool useFrameBufferAlpha;
        } env;
        struct {  // rpMATFXEFFECTDUAL: +0x00 texture, +0x04 srcBlend, +0x08 dstBlend
            RwTexture* texture;
            RwInt32 srcBlendMode;
            RwInt32 dstBlendMode;
        } dual;
        struct {  // rpMATFXEFFECTUVTRANSFORM: +0x00 base, +0x04 dual matrix
            struct RwMatrix* baseTransform;
            struct RwMatrix* dualTransform;
        } uv;
        struct {  // rpMATFXEFFECTBUMPMAP: +0x00 frame, +0x04 / +0x08 the two textures the stream holds (the
                  // bump map and the bumped base), +0x0c coefficient, +0x10 1 / the first one's raster width
                  // (STUB(C2.4 step 4): MatFX_CreateBumpedTexture_maybe is not ported)
            void* frame;
            RwTexture* texture4;
            RwTexture* texture8;
            RwReal coefficient;
            RwReal invWidth;
        } bump;
        RwUInt32 raw[8];
    };
    RwUInt32 type;  // +0x20
};
struct RpMatFXMaterialData {
    RpMatFXEffect effects[2];  // +0x00, +0x30
    RwUInt32 flags;            // +0x60 RpMatFXMaterialGetEffects
};

// RpMaterial (PS3 0x1c) and its plugin data: the K material plugin and MatFX (the PS3 allocates them behind the
// 0x1c bytes at the plugin offsets).
struct RpMaterial {
    RwTexture* texture;                  // +0x00
    RwRGBA color;                        // +0x04
    void* pipeline;                      // +0x08
    RwSurfaceProperties surfaceProps;    // +0x0c
    RwInt16 refCount;                    // +0x18
    RwInt16 pad;                         // +0x1a
    // Plugin data (behind the PS3 struct).
    class CMaterial* kMaterial;          // the K plugin: +[0x00c297e8] (XXL2 CMaterial::m_sui32RpToKMaterialPlugingOffset)
    RpMatFXMaterialData* matfx;          // MatFX plugin (+[0x00cec448]), null until a matfx chunk or SetEffects
    RwUInt32 rightsPluginId;             // 0x1f RightToRender chunk: plugin id and extra data (0: none)
    RwUInt32 rightsExtraData;
};
DOTD_ASSERT_OFFSET(RpMaterial, refCount, 0x18);
DOTD_ASSERT_OFFSET(RpMaterial, kMaterial, 0x1c);

// RpTriangle (8 bytes).
struct RpTriangle {
    RwUInt16 vertIndex[3];  // +0x00
    RwUInt16 matIndex;      // +0x06
};
DOTD_ASSERT_SIZE(RpTriangle, 0x8);

struct RwTexCoords {
    RwReal u;
    RwReal v;
};

struct RwSphere {
    RwV3d center;
    RwReal radius;
};

// RwBBox: sup (the maxima) then inf (the minima).
struct RwBBox {
    RwV3d sup;
    RwV3d inf;
};

// RpMorphTarget (PS3 0x1c).
struct RpMorphTarget {
    RpGeometry* parentGeom;   // +0x00
    RwSphere boundingSphere;  // +0x04
    RwV3d* verts;             // +0x14
    RwV3d* normals;           // +0x18
};
DOTD_ASSERT_SIZE(RpMorphTarget, 0x1c);
DOTD_ASSERT_OFFSET(RpMorphTarget, verts, 0x14);

// RpMaterialList (PS3 0xc).
struct RpMaterialList {
    RpMaterial** materials;  // +0x00
    RwInt32 numMaterials;    // +0x04
    RwInt32 space;           // +0x08
};

// RpGeometry flags (rpGEOMETRY*).
enum : RwUInt32 {
    rpGEOMETRYTRISTRIP = 0x1,
    rpGEOMETRYPOSITIONS = 0x2,
    rpGEOMETRYTEXTURED = 0x4,
    rpGEOMETRYPRELIT = 0x8,
    rpGEOMETRYNORMALS = 0x10,
    rpGEOMETRYLIGHT = 0x20,
    rpGEOMETRYMODULATEMATERIALCOLOR = 0x40,
    rpGEOMETRYTEXTURED2 = 0x80,
};

// RpMesh / RpMeshHeader (the bin mesh, chunk 0x50e; _rpMeshRead 0x6a6050). PS3: the header is 0x10 bytes and
// the RpMeshes (0xc each: indices, numIndices, material) follow it; the indices of a non-native geometry
// follow the meshes, 32-bit each (RxVertexIndex is 32-bit on the PS3). A native geometry's bin mesh has no
// indices (they are in the native data): there each mesh is {numIndices, material} (8 bytes in the file).
struct RpMesh {
    RwUInt32* indices;     // +0x00 (null for a native geometry)
    RwUInt32 numIndices;   // +0x04
    RpMaterial* material;  // +0x08
};
struct RpMeshHeader {
    RwUInt32 flags;               // +0x00 rpMESHHEADERTRISTRIP 1 ...
    RwUInt16 numMeshes;           // +0x04
    RwUInt16 serialNum;           // +0x06 _rpMeshGetNextSerialNumber
    RwUInt32 totalIndicesInMesh;  // +0x08
    RwUInt32 firstMeshOffset;     // +0x0c
    std::vector<RpMesh> meshes;   // (the PS3 keeps them behind the header)
    std::vector<RwUInt32> indexStorage;  // the indices the meshes point into
};

// The PS3 driver's per-mesh record in a native geometry (the resource entry's meshes at +0x1c, 0x78 bytes
// each = 30 words; the file stores them big-endian, they are converted here). Field meaning from
// DrawPSGLDefaultPipelineMesh 0x6bb340, RwPSGL_ComputeInterleavedVertexLayout_maybe 0x6b9ee0 and
// RpGeometryNativeStreamRead_maybe 0x6b6fb0. Interleaved vertex: position (3 floats), normal (3) when the
// format has rpGEOMETRYNORMALS, colour (4 bytes) when prelit, up to 8 uv sets (2 floats), then the trailing
// attribute at `tangentOffset`. The material slot and the two GL buffer names of the file are overwritten.
struct RpNativeMesh {
    RwUInt32 primType;       // [0]  GL primitive: 4 triangles, 5 triangle strip
    RwUInt32 format;         // [1]  the geometry's format flags with 0x02000000 (0x277, 0x25f, 0x4f, ...)
    RwUInt32 stride;         // [2]  bytes per vertex (0x2c, 0x30, 0x18, 0x24, ...)
    RwUInt32 numVertices;    // [3]
    RwUInt32 vertexBytes;    // [4]  stride * numVertices (the reader recomputes it)
    RwUInt32 firstIndex;     // [5]  glDrawRangeElements start (glDrawArrays first)
    RwUInt32 lastIndex;      // [6]  glDrawRangeElements end (the largest index)
    RwUInt32 numIndices;     // [7]  index count; 0 = not indexed
    RwUInt32 indexed;        // [8]  1 when an index buffer exists (set by the reader)
    RwUInt32 word9;          // [9]
    RpMaterial* material;    // [10] the geometry's first material (set by the reader)
    RwUInt32 vertexAlpha;    // [11] 0: the material colour's alpha is the alpha test
    RwUInt32 vertexBuffer;   // [12] GL buffer name (device side; here 0)
    RwUInt32 indexBuffer;    // [13] GL buffer name (device side; here 0)
    RwUInt32 word14;         // [14]
    RwUInt32 normalOffset;   // [15]
    RwUInt32 colorOffset;    // [16]
    RwUInt32 uvOffset[8];    // [17..24]
    RwUInt32 tangentOffset;  // [25] offset of the trailing 12-byte attribute (RwPSGL_ComputeVertexTangents)
    RwUInt32 word26;         // [26]
    RwUInt32 word27;         // [27]
    RwUInt32 word28;         // [28]
    RwUInt32 word29;         // [29]
};

// A native geometry's resource entry (RpGeometry +0x58): the header words and the buffers of mesh 0, as
// RpGeometryNativeStreamRead_maybe reads them (it reads buffers for the first mesh only; every LVL010
// native geometry has one mesh). The buffer bytes are as the file has them: PS3 big-endian (float
// vertices, 32-bit indices). RpAtomicPSGL_InstanceGeometry (C2.4 step 3) converts them for the host and makes the device mesh.
struct RpNativeGeometry {
    RwUInt32 platformId;                  // the first struct word (0xc)
    RwUInt16 serial;                      // header word 0 high half
    RwUInt16 numMeshes;                   // header word 0 low half (resource entry +0x1a)
    std::vector<RpNativeMesh> meshes;
    std::vector<RwUInt8> vertexData;      // meshes[0].stride * numVertices bytes
    std::vector<RwUInt8> indexData;       // meshes[0].numIndices * 4 bytes (empty when not indexed)
};

// rpGEOMETRYNATIVE: the vertex data is in the native data chunk.
enum : RwUInt32 { rpGEOMETRYNATIVE = 0x01000000 };

// A mesh as the device draws it (C2.4 step 3, RpAtomicPSGL.cpp): the PS3 driver's per-mesh record (the native
// geometry's own, or the one the PSGL atomic pipeline would build from a generic geometry's bin mesh) and the
// device mesh made from its buffers (platform/gfx/mesh.h; the PS3 keeps GL buffer names in words 12 and 13).
struct RpDeviceMesh {
    RpNativeMesh record;         // little-endian words; the vertex layout offsets are into the interleaved vertex
    uint32_t gfxMesh = 0;        // platform/gfx mesh (vertex array, vertex and index buffers); 0: nothing to draw
};
struct RpGeometryDevice {
    std::vector<RpDeviceMesh> meshes;  // the resource entry's meshes (+0x1c, 0x78 bytes each on the PS3)
};

// RpGeometry (PS3 0x60) with the plugin data behind it.
struct RpGeometry {
    RwUInt8 objectType;           // +0x00 RwObject (type 8)
    RwUInt8 objectSubType;        // +0x01
    RwUInt8 objectFlags;          // +0x02
    RwUInt8 objectPrivateFlags;   // +0x03
    void* objectParent;           // +0x04
    RwUInt32 flags;               // +0x08
    RwUInt16 lockedSinceLastInst; // +0x0c
    RwInt16 refCount;             // +0x0e
    RwInt32 numTriangles;         // +0x10
    RwInt32 numVertices;          // +0x14
    RwInt32 numMorphTargets;      // +0x18
    RwInt32 numTexCoordSets;      // +0x1c
    RpMaterialList matList;       // +0x20
    RpTriangle* triangles;        // +0x2c
    RwRGBA* preLitLum;            // +0x30
    RwTexCoords* texCoords[8];    // +0x34
    RpMeshHeader* mesh;           // +0x54 the bin mesh (0x50e); null for geometries built in memory
    RpNativeGeometry* repEntry;   // +0x58 the PS3 native data (0x510), or null (the resource entry)
    RpMorphTarget* morphTarget;   // +0x5c
    // Plugin data (behind the PS3 struct).
    struct RpSkin* skin;          // the skin plugin's data (geometry + [0xcf075c]; RpSkinGeometryStreamRead, chunk 0x116)
    RpGeometryDevice* device;     // the instanced meshes (RpAtomicPSGL_InstanceGeometry), or null before the first draw
};
DOTD_ASSERT_OFFSET(RpGeometry, matList, 0x20);
DOTD_ASSERT_OFFSET(RpGeometry, mesh, 0x54);
DOTD_ASSERT_OFFSET(RpGeometry, triangles, 0x2c);
DOTD_ASSERT_OFFSET(RpGeometry, preLitLum, 0x30);
DOTD_ASSERT_OFFSET(RpGeometry, texCoords, 0x34);
DOTD_ASSERT_OFFSET(RpGeometry, morphTarget, 0x5c);

RpGeometry* RpGeometryCreate(RwInt32 numVerts, RwInt32 numTriangles, RwUInt32 format);
RwBool RpGeometryDestroy(RpGeometry* geometry);
// 0x006a2248 RpGeometryStreamRead (rpworld/RpGeometryStream.cpp; RW 3.7 bageomet.c with the PS3 build's
// plugins: bin mesh 0x50e, native data 0x510, skin 0x116). The caller has found the geometry chunk (0xf).
RpGeometry* RpGeometryStreamRead(RwStream* stream);
// DEV (C2.4 step 1): one record per geometry RpGeometryStreamRead returned, in read order; Kp3_ReportLoadChecks
// notes the log's size per file, geometry_read_test counts what each file held.
struct RpGeometryReadRecord {
    RwUInt32 flags;            // the geometry's flags (format & 0xf00007b | texture bits; 0x1000000 native)
    RwInt32 numTriangles;
    RwInt32 numVertices;
    RwInt32 numMorphTargets;
    RwInt32 numMaterials;
    RwInt32 numTexturedMaterials;  // materials whose texture was found in the dictionaries
    RwUInt32 numMeshes;        // the bin mesh's meshes (0 for the empty geometries)
    RwUInt32 hasBinMesh;       // 1 when the geometry has a bin mesh (0x50e)
    RwUInt32 nativeMeshes;     // the native data's mesh records (0: no native data)
    RwUInt32 nativeBytes;      // the size of the 0x510 chunk (12 + 8 + header + index + vertex bytes)
    RwUInt32 skinBytes;
    // The native buffers decoded as PS3 big-endian data: indices >= the vertex count or above lastIndex, vertices
    // whose position is not finite, meshes whose lastIndex is not the largest index (all 0 for sound data).
    RwUInt32 nativeBadIndices;
    RwUInt32 nativeBadVertices;
    RwUInt32 nativeBadRanges;
};
const std::vector<RpGeometryReadRecord>& RpGeometryReadLog();
// RpGeometryAddMorphTargets (RW 3.7): `mtsToAdd` more morph targets with their vertices and normals.
RwInt32 RpGeometryAddMorphTargets(RpGeometry* geometry, RwInt32 mtsToAdd);
RpGeometry* RpGeometryUnlock(RpGeometry* geometry);
RpGeometry* RpGeometryTriangleSetVertexIndices(const RpGeometry* geometry, RpTriangle* triangle, RwUInt16 vert1,
                                               RwUInt16 vert2, RwUInt16 vert3);
RpGeometry* RpGeometryTriangleSetMaterial(RpGeometry* geometry, RpTriangle* triangle, RpMaterial* material);
RpMorphTarget* RpMorphTargetCalcBoundingSphere(const RpMorphTarget* morphTarget, RwSphere* boundingSphere);
RwBBox* RwBBoxCalculate(RwBBox* boundBox, const RwV3d* verts, RwInt32 numVerts);

RpMaterial* RpMaterialCreate();
// 0x006a40c0 RpMaterialStreamRead / 0x006a4ec8 _rpMaterialListStreamRead (rpworld/RpGeometryStream.cpp): the
// caller has found the material chunk (7) / the list chunk (8). The texture comes from the loaded dictionaries
// (FindTextureByName, as RwTextureRead(name, mask) does in the game).
RpMaterial* RpMaterialStreamRead(RwStream* stream);
RpMaterialList* _rpMaterialListStreamRead(RwStream* stream, RpMaterialList* matList);
RwBool RpMaterialDestroy(RpMaterial* material);
RpMaterial* RpMaterialSetTexture(RpMaterial* material, RwTexture* texture);
RwInt32 _rpMaterialListFindMaterialIndex(const RpMaterialList* matList, const RpMaterial* material);
RwInt32 _rpMaterialListAppendMaterial(RpMaterialList* matList, RpMaterial* material);

RpAtomic* RpAtomicCreate();
// 0x0069ff28 RpAtomicStreamRead (rpworld/RpGeometryStream.cpp), after RwStreamFindChunk(0x14): the atomic with its
// geometry and plugin data.
RpAtomic* RpAtomicStreamRead(RwStream* stream);
RpAtomic* RpAtomicSetFrame(RpAtomic* atomic, RwFrame* frame);
RpAtomic* RpAtomicSetGeometry(RpAtomic* atomic, RpGeometry* geometry, RwUInt32 flags);
RwBool RpAtomicDestroy(RpAtomic* atomic);

// DEV (C1.5): one recorded atomic render (C1.4: also drawn when it is recorded).
struct RpAtomicDraw {
    RpAtomic* atomic;
    RpGeometry* geometry;
    RwMatrix ltm;                       // the atomic frame's LTM at the call
    std::vector<RwRGBA> materialColors; // the geometry's material colours at the call
    RwIm3DRenderStates states;          // the render states in force at the call
};
const std::vector<RpAtomicDraw>& RpAtomicFrameDraws();
void RpAtomicBeginFrame();
