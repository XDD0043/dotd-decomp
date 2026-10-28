// RpGeometryStream.cpp - the RpWorld stream readers (C2.4 step 1): atomic, geometry, material list, material,
// the bin mesh and the PS3 native mesh data, with the plugin chunks that LVL010's atomics carry.
//
// RenderWare 3.7.0.2 source (world/baclump.c ClumpAtomicStreamRead, world/bageomet.c RpGeometryStreamRead,
// world/bamateri.c, world/bamatlst.c, world/bamesh.c _rpMeshRead, core/src/plcore/batkbin.c the plugin
// registry's chunk loop) checked against the PS3 library code (TOC 0xc25974):
//   0x0069f0d8 ClumpAtomicStreamRead      0x0069ff28 RpAtomicStreamRead   0x006a2248 RpGeometryStreamRead
//   0x006a4ec8 _rpMaterialListStreamRead  0x006a40c0 RpMaterialStreamRead  0x006a6050 _rpMeshRead
//   0x006b3ee8 RpMeshPlugin_GeometryStreamRead_maybe   0x006b3ce0 RpGeometryNativeStreamReadCB_maybe
//   0x006b6fb0 RpGeometryNativeStreamRead_maybe        0x0069a388 MatFXMaterialStreamRead_maybe
//   0x006983f8 MatFX_StreamReadTexture_maybe           0x006a3bf0 MaterialPipelineStreamRead_maybe
//   0x0069c5e0 AtomicPipelineStreamRead_maybe
// RenderWare streams are little-endian here (the loader reads KP3 files as they are); the PS3 native chunk
// (0x510) is big-endian data for the GPU and stays so.
//
// Plugin chunks (everything else is skipped, as the plugin registry does for chunks without a reader):
//   atomic extension:   0x130 RpPrtStd (the emitters; reads 8 bytes past its chunk, see below), 0x1f right to
//                       render (plugin id and extra data: 0x116 for the 19 skinned atomics)
//   geometry extension: 0x50e bin mesh, 0x510 native data, 0x116 skin (RpSkinGeometryStreamRead, rpskin/RpSkin.cpp)
//   material extension: 0x120 MatFX, 0x1f right to render
//   texture extension:  skipped (RwTextureStreamRead's plugin chunks; none is read)
// After an atomic's extension the plugins' always callbacks run (the skin plugin's), then the rights callback of the
// 0x1f chunk's plugin (0x116: the skin pipeline by type, rpskin/RpSkin.h).
#include <cstdint>
#include <cstring>
#include <vector>

#include "Renderware/rpmatfx/RpMatFX.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpskin/RpSkin.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwSList.h"
#include "Renderware/rwcore/RwStream.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/io/IKFile.h"

namespace {
constexpr uint32_t kIdStruct = 0x1;
constexpr uint32_t kIdString = 0x2;
constexpr uint32_t kIdExtension = 0x3;
constexpr uint32_t kIdTexture = 0x6;
constexpr uint32_t kIdMaterial = 0x7;
constexpr uint32_t kIdMatList = 0x8;
constexpr uint32_t kIdGeometry = 0xf;
constexpr uint32_t kIdRightToRender = 0x1f;
constexpr uint32_t kIdSkin = 0x116;
constexpr uint32_t kIdMatFX = 0x120;
constexpr uint32_t kIdPrtStd = 0x130;
constexpr uint32_t kIdBinMesh = 0x50e;
constexpr uint32_t kIdNative = 0x510;
constexpr uint32_t kNativeMeshBytes = 0x78;  // the PS3 record: 30 words (RpNativeMesh has a host pointer in its place)
constexpr uint32_t kNativeMeshWords = kNativeMeshBytes / 4;

bool ReadBytes(RwStream* stream, void* data, uint32_t length) { return RwStreamRead(stream, data, length) == length; }

bool ReadInt32(RwStream* stream, int32_t* value) { return ReadBytes(stream, value, 4); }  // RwStreamReadInt32 (LE file, LE host)

bool ReadReal(RwStream* stream, float* value) { return ReadBytes(stream, value, 4); }  // RwStreamReadReal

uint32_t BigEndian32(const uint8_t* b) {
    return (static_cast<uint32_t>(b[0]) << 24) | (static_cast<uint32_t>(b[1]) << 16) |
           (static_cast<uint32_t>(b[2]) << 8) | static_cast<uint32_t>(b[3]);
}

uint32_t LittleEndian32(const uint8_t* b) {
    return static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) | (static_cast<uint32_t>(b[2]) << 16) |
           (static_cast<uint32_t>(b[3]) << 24);
}

// core/src/plcore/batkbin.c _rwPluginRegistryReadDataChunks: the extension chunk, then each plugin chunk
// header; `handler(type, size)` reads exactly the chunk (or skips it). RW counts the extension's length down
// by each chunk's size + 12.
template <class Handler>
bool ReadExtension(RwStream* stream, Handler handler) {
    uint32_t length = 0, version = 0;
    if (RwStreamFindChunk(stream, kIdExtension, &length, &version) == 0) return false;
    while (length > 0) {
        uint32_t type = 0, size = 0;
        if (_rwStreamReadChunkHeader(stream, &type, &size, nullptr, nullptr) == 0) return false;
        if (!handler(type, size)) return false;
        length -= size + 12;
    }
    return true;
}

// _rwPluginRegistrySkipDataChunks: the extension chunk skipped whole.
bool SkipExtension(RwStream* stream) {
    uint32_t length = 0, version = 0;
    if (RwStreamFindChunk(stream, kIdExtension, &length, &version) == 0) return false;
    return RwStreamSkip(stream, length) != nullptr;
}

// _rwStringStreamFindAndRead: the next string chunk (2), its bytes up to the first zero.
bool StringStreamFindAndRead(RwStream* stream, char* out, uint32_t capacity) {
    uint32_t length = 0, version = 0;
    if (RwStreamFindChunk(stream, kIdString, &length, &version) == 0) return false;
    std::vector<char> bytes(length + 1, 0);
    if (!ReadBytes(stream, bytes.data(), length)) return false;
    std::strncpy(out, bytes.data(), capacity - 1);
    out[capacity - 1] = 0;
    return true;
}

// RwTextureStreamRead (core/src/babintex.c) after the texture chunk (6) was found: the filter / addressing
// struct, the name and the mask, then RwTextureRead(name, mask): here the texture of that name in the loaded
// dictionaries (FindTextureByName, a reference added). Its extension chunk is skipped (the plugin chunks of a
// texture are not read; RW reads them only for a texture it just created). The mipmapping state RW switches
// around the read is not modelled (no rasters are created here). Null when the texture is not loaded.
RwTexture* TextureStreamRead(RwStream* stream) {
    uint32_t size = 0, version = 0;
    if (RwStreamFindChunk(stream, kIdStruct, &size, &version) == 0) return nullptr;
    if (RwStreamSkip(stream, size) == nullptr) return nullptr;  // the filter and addressing word
    char name[0x80] = {};
    char mask[0x80] = {};
    if (!StringStreamFindAndRead(stream, name, sizeof name)) return nullptr;
    if (!StringStreamFindAndRead(stream, mask, sizeof mask)) return nullptr;
    RwTexture* texture = static_cast<RwTexture*>(FindTextureByName(name));
    SkipExtension(stream);
    return texture;
}

// 0x006983f8 MatFX_StreamReadTexture_maybe: a flag word, then (when set) a texture chunk. False only for a
// stream error; a texture that is not loaded gives a null texture.
bool MatFXStreamReadTexture(RwStream* stream, RwTexture** out) {
    int32_t present = 0;
    if (!ReadInt32(stream, &present)) return false;
    if (present == 0) {
        *out = nullptr;
        return true;
    }
    uint32_t length = 0, version = 0;
    if (RwStreamFindChunk(stream, kIdTexture, &length, &version) == 0) return false;
    *out = TextureStreamRead(stream);
    return true;
}

void TextureAddRef(RwTexture* texture) { ++texture->refCount; }
void TextureRelease(RwTexture* texture) {
    if (texture != nullptr) --texture->refCount;
}

// 0x0069a388 MatFXMaterialStreamRead_maybe: the effect word (RpMatFXMaterialSetEffects), then the two effect
// slots: type 2 env map (coefficient, frame buffer alpha, texture), 4 dual (two blend modes, texture), 1 bump
// map (coefficient, two textures); other types carry nothing.
bool MatFXMaterialStreamRead(RwStream* stream, RpMaterial* material) {
    int32_t effects = 0;
    if (!ReadInt32(stream, &effects)) return false;
    RpMatFXMaterialSetEffects(material, static_cast<uint32_t>(effects));
    auto find = [material](uint32_t type) -> RpMatFXEffect* {
        RpMatFXMaterialData* data = material->matfx;
        return data->effects[0].type == type ? &data->effects[0] : (data->effects[1].type == type ? &data->effects[1] : nullptr);
    };
    for (int i = 0; i < 2; ++i) {
        int32_t type = 0;
        if (!ReadInt32(stream, &type)) return false;
        if (type == 2) {
            float coefficient = 0.0f;
            int32_t fbAlpha = 0;
            RwTexture* texture = nullptr;
            if (!ReadReal(stream, &coefficient) || !ReadInt32(stream, &fbAlpha)) return false;
            if (!MatFXStreamReadTexture(stream, &texture)) return false;
            RpMatFXEffect* slot = find(2);
            slot->env.coefficient = coefficient;
            slot->env.useFrameBufferAlpha = fbAlpha;
            if (texture != nullptr) {  // RpMatFXMaterialSetEnvMapTexture: a reference, the old one released
                TextureAddRef(texture);
                TextureRelease(slot->env.texture);
                slot->env.texture = texture;
                TextureRelease(texture);  // the stream's own reference
            }
        } else if (type == 4) {
            int32_t blend[2] = {0, 0};
            RwTexture* texture = nullptr;
            if (!ReadBytes(stream, blend, 8)) return false;
            if (!MatFXStreamReadTexture(stream, &texture)) return false;
            RpMatFXEffect* slot = find(4);
            if (texture != nullptr) {  // RpMatFXMaterialSetDualTexture
                TextureAddRef(texture);
                TextureRelease(slot->dual.texture);
                slot->dual.texture = texture;
                TextureRelease(texture);
            }
            slot->dual.srcBlendMode = blend[0];
            slot->dual.dstBlendMode = blend[1];
        } else if (type == 1) {
            float coefficient = 0.0f;
            RwTexture* first = nullptr;
            RwTexture* second = nullptr;
            if (!ReadReal(stream, &coefficient)) return false;
            if (!MatFXStreamReadTexture(stream, &first)) return false;
            if (!MatFXStreamReadTexture(stream, &second)) {
                TextureRelease(first);
                return false;
            }
            RpMatFXEffect* slot = find(1);
            if (first != nullptr) {
                slot->bump.texture4 = first;
                slot->bump.texture8 = second;
                // 1 / the raster width (fdivs 1.0f, width). STUB(C2.4 step 4): the raster is a shim DDS raster.
                slot->bump.invWidth = 1.0f / static_cast<float>(first->raster != nullptr ? first->raster->width : 1);
            } else if (second != nullptr) {
                // RpMatFXMaterialSetBumpMapTexture 0x697a48: STUB(C2.4 step 4) (the bumped texture is built there).
                slot->bump.texture8 = second;
            } else {
                slot->bump.texture8 = nullptr;
                slot->bump.texture4 = nullptr;
            }
            slot->bump.coefficient = -coefficient;
        }
    }
    return true;
}

// Plugin chunk 0x1f (MaterialPipelineStreamRead_maybe 0x6a3bf0 / AtomicPipelineStreamRead_maybe 0x69c5e0): the
// plugin id, and the extra data when the chunk is 8 bytes long.
bool RightToRenderRead(RwStream* stream, uint32_t size, uint32_t* pluginId, uint32_t* extraData) {
    int32_t id = 0;
    if (!ReadInt32(stream, &id)) return false;
    *pluginId = static_cast<uint32_t>(id);
    if (size == 8) {
        int32_t extra = 0;
        if (!ReadInt32(stream, &extra)) return false;
        *extraData = static_cast<uint32_t>(extra);
    }
    return true;
}

std::vector<RpGeometryReadRecord> g_readLog;  // DEV

uint16_t g_nextMeshSerial = 1;  // _rpMeshGetNextSerialNumber's counter (RPMESHGLOBAL(nextSerialNum), starts at 1)

// 0x006a6050 _rpMeshRead: the bin mesh header {flags, numMeshes, totalIndicesInMesh} and per mesh
// {numIndices, matIndex} followed by its indices (32-bit) unless the geometry is native.
RpMeshHeader* MeshRead(RwStream* stream, const RpGeometry* geometry) {
    int32_t header[3] = {0, 0, 0};
    if (!ReadBytes(stream, header, 12)) return nullptr;
    RpMeshHeader* mesh = new RpMeshHeader();
    mesh->flags = static_cast<uint32_t>(header[0]);
    mesh->numMeshes = static_cast<uint16_t>(header[1]);
    mesh->serialNum = g_nextMeshSerial++;
    mesh->totalIndicesInMesh = static_cast<uint32_t>(header[2]);
    mesh->firstMeshOffset = 0;
    const bool readIndices = (geometry->flags & rpGEOMETRYNATIVE) == 0;
    if (readIndices) mesh->indexStorage.resize(mesh->totalIndicesInMesh);
    mesh->meshes.resize(static_cast<size_t>(header[1]));
    RwUInt32* next = mesh->indexStorage.data();
    for (RpMesh& entry : mesh->meshes) {
        int32_t bm[2] = {0, 0};
        if (!ReadBytes(stream, bm, 8)) {
            delete mesh;
            return nullptr;
        }
        entry.numIndices = static_cast<uint32_t>(bm[0]);
        entry.material = geometry->matList.materials[bm[1]];  // _rpMaterialListGetMaterial
        entry.indices = next;
        if (readIndices) {
            if (!ReadBytes(stream, next, entry.numIndices * 4)) {
                delete mesh;
                return nullptr;
            }
            next += entry.numIndices;
        }
    }
    return mesh;
}

// 0x006b6fb0 RpGeometryNativeStreamRead_maybe: inside the chunk's struct (1): the platform word (0xc), the
// header size, the header (word 0: serial and mesh count, then 0x78 bytes per mesh), the first mesh's index
// buffer (numIndices x 4 bytes, when it has indices) and vertex buffer (stride x numVertices bytes). The
// original reads the buffers into GL buffers; here they are kept. The material slot gets the geometry's first
// material, the two GL buffer names are zeroed, and the index flag is set when there are indices.
bool NativeRead(RwStream* stream, RpGeometry* geometry) {
    uint32_t size = 0, version = 0;
    if (RwStreamFindChunk(stream, kIdStruct, &size, &version) == 0) return false;
    uint8_t word[4];
    if (!ReadBytes(stream, word, 4) || BigEndian32(word) != 0xc) return false;
    const uint32_t platformId = BigEndian32(word);
    if (!ReadBytes(stream, word, 4)) return false;
    const uint32_t headerSize = BigEndian32(word);
    std::vector<uint8_t> header(headerSize);
    if (!ReadBytes(stream, header.data(), headerSize)) return false;
    RpNativeGeometry* native = new RpNativeGeometry();
    native->platformId = platformId;
    native->serial = static_cast<uint16_t>(BigEndian32(header.data()) >> 16);
    native->numMeshes = static_cast<uint16_t>(BigEndian32(header.data()) & 0xffff);
    native->meshes.resize((headerSize - 4) / kNativeMeshBytes);
    for (size_t m = 0; m < native->meshes.size(); ++m) {
        uint32_t words[kNativeMeshWords];
        for (uint32_t w = 0; w < kNativeMeshWords; ++w) words[w] = BigEndian32(header.data() + 4 + m * kNativeMeshBytes + w * 4);
        // The record has a host pointer at [10] (the file's slot is overwritten): the words are copied one by one.
        RpNativeMesh& mesh = native->meshes[m];
        std::memset(&mesh, 0, sizeof mesh);
        mesh.primType = words[0];
        mesh.format = words[1];
        mesh.stride = words[2];
        mesh.numVertices = words[3];
        mesh.vertexBytes = words[4];
        mesh.firstIndex = words[5];
        mesh.lastIndex = words[6];
        mesh.numIndices = words[7];
        mesh.indexed = words[8];
        mesh.word9 = words[9];
        mesh.material = nullptr;  // [10] the file holds a pointer slot
        mesh.vertexAlpha = words[11];
        mesh.vertexBuffer = 0;    // [12], [13]: the file holds stale GL names
        mesh.indexBuffer = 0;
        mesh.word14 = words[14];
        mesh.normalOffset = words[15];
        mesh.colorOffset = words[16];
        for (int u = 0; u < 8; ++u) mesh.uvOffset[u] = words[17 + u];
        mesh.tangentOffset = words[25];
        mesh.word26 = words[26];
        mesh.word27 = words[27];
        mesh.word28 = words[28];
        mesh.word29 = words[29];
    }
    RpNativeMesh& first = native->meshes[0];
    first.material = geometry->matList.materials[0];
    if (first.numIndices != 0) {
        native->indexData.resize(static_cast<size_t>(first.numIndices) * 4);
        if (!ReadBytes(stream, native->indexData.data(), first.numIndices * 4)) {
            delete native;
            return false;
        }
        first.indexed = 1;
    }
    first.vertexBytes = first.numVertices * first.stride;
    native->vertexData.resize(first.vertexBytes);
    if (!ReadBytes(stream, native->vertexData.data(), first.vertexBytes)) {
        delete native;
        return false;
    }
    geometry->repEntry = native;
    return true;
}
}  // namespace

const std::vector<RpGeometryReadRecord>& RpGeometryReadLog() { return g_readLog; }

// 0x006a4ec8 _rpMaterialListStreamRead
RpMaterialList* _rpMaterialListStreamRead(RwStream* stream, RpMaterialList* matList) {
    uint32_t size = 0, version = 0;
    if (RwStreamFindChunk(stream, kIdStruct, &size, &version) == 0) return nullptr;
    int32_t numMaterials = 0;
    if (!ReadInt32(stream, &numMaterials)) return nullptr;
    matList->space = 0;
    matList->materials = nullptr;
    matList->numMaterials = 0;
    if (numMaterials == 0) return matList;
    matList->materials = static_cast<RpMaterial**>(RwMalloc(static_cast<uint32_t>(numMaterials) * sizeof(RpMaterial*), 0x1030008));
    matList->space = numMaterials;
    std::vector<int32_t> indices(static_cast<size_t>(numMaterials));
    if (!ReadBytes(stream, indices.data(), static_cast<uint32_t>(numMaterials) * 4)) return nullptr;
    for (int32_t i = 0; i < numMaterials; ++i) {
        RpMaterial* material;
        if (indices[i] < 0) {  // a new material follows
            uint32_t length = 0, materialVersion = 0;
            if (RwStreamFindChunk(stream, kIdMaterial, &length, &materialVersion) == 0) return nullptr;
            material = RpMaterialStreamRead(stream);
            if (material == nullptr) return nullptr;
        } else {  // an earlier material of this list, one more reference
            material = matList->materials[indices[i]];
            ++material->refCount;
        }
        _rpMaterialListAppendMaterial(matList, material);
        RpMaterialDestroy(material);
    }
    return matList;
}

// 0x006a40c0 RpMaterialStreamRead
RpMaterial* RpMaterialStreamRead(RwStream* stream) {
    uint32_t size = 0, version = 0;
    if (RwStreamFindChunk(stream, kIdStruct, &size, &version) == 0) return nullptr;
    uint8_t raw[0x1c] = {};
    if (size > sizeof raw || RwStreamRead(stream, raw, size) != size) return nullptr;
    // _rpMaterial: flags, color (RwRGBA), unused, textured, surfaceProps (ambient, specular, diffuse)
    RpMaterial* material = RpMaterialCreate();
    material->color.red = raw[4];
    material->color.green = raw[5];
    material->color.blue = raw[6];
    material->color.alpha = raw[7];
    const uint32_t textured = LittleEndian32(raw + 12);
    uint32_t props[3] = {LittleEndian32(raw + 16), LittleEndian32(raw + 20), LittleEndian32(raw + 24)};
    std::memcpy(&material->surfaceProps, props, sizeof props);
    material->texture = nullptr;
    if (textured != 0) {
        uint32_t length = 0, textureVersion = 0;
        if (RwStreamFindChunk(stream, kIdTexture, &length, &textureVersion) == 0) {
            RpMaterialDestroy(material);
            return nullptr;
        }
        material->texture = TextureStreamRead(stream);
    }
    // The plugin chunks: MatFX (0x120) and the right to render (0x1f).
    uint32_t rightsId = 0, rightsExtra = 0;
    const bool ok = ReadExtension(stream, [&](uint32_t type, uint32_t chunkSize) {
        if (type == kIdMatFX) return MatFXMaterialStreamRead(stream, material);
        if (type == kIdRightToRender) return RightToRenderRead(stream, chunkSize, &rightsId, &rightsExtra);
        return RwStreamSkip(stream, chunkSize) != nullptr;
    });
    if (!ok) {
        RpMaterialDestroy(material);
        return nullptr;
    }
    material->rightsPluginId = rightsId;
    material->rightsExtraData = rightsExtra;
    return material;
}

// 0x006a2248 RpGeometryStreamRead
RpGeometry* RpGeometryStreamRead(RwStream* stream) {
    uint32_t size = 0, version = 0;
    if (RwStreamFindChunk(stream, kIdStruct, &size, &version) == 0) return nullptr;
    uint32_t geom[4] = {};  // _rpGeometry: format, numTriangles, numVertices, numMorphTargets
    if (!ReadBytes(stream, geom, 16)) return nullptr;
    RpGeometry* geometry = RpGeometryCreate(static_cast<RwInt32>(geom[2]), static_cast<RwInt32>(geom[1]), geom[0]);
    if (geometry == nullptr) return nullptr;
    if (geom[3] > 1 && RpGeometryAddMorphTargets(geometry, static_cast<RwInt32>(geom[3]) - 1) < 0) {
        RpGeometryDestroy(geometry);
        return nullptr;
    }
    auto fail = [geometry]() -> RpGeometry* {
        RpGeometryDestroy(geometry);
        return nullptr;
    };
    if ((geometry->flags & rpGEOMETRYNATIVE) == 0 && geometry->numVertices != 0) {
        if ((geom[0] & rpGEOMETRYPRELIT) != 0) {  // the prelight colours: bytes, no conversion
            if (!ReadBytes(stream, geometry->preLitLum, static_cast<uint32_t>(geometry->numVertices) * 4)) return fail();
        }
        for (RwInt32 i = 0; i < geometry->numTexCoordSets; ++i) {  // the uv sets: reals
            if (!ReadBytes(stream, geometry->texCoords[i], static_cast<uint32_t>(geometry->numVertices) * 8)) return fail();
        }
        if (geometry->numTriangles != 0) {
            // The triangles: two words each, {vertex0 << 16 | vertex1, vertex2 << 16 | material} after the
            // little-endian word read ("unpacked in place" into the u16 fields).
            const uint32_t bytes = static_cast<uint32_t>(geometry->numTriangles) * 8;
            std::vector<uint32_t> packed(bytes / 4);
            if (!ReadBytes(stream, packed.data(), bytes)) return fail();
            for (RwInt32 t = 0; t < geometry->numTriangles; ++t) {
                const uint32_t vertex01 = packed[static_cast<size_t>(t) * 2];
                const uint32_t vertex2Mat = packed[static_cast<size_t>(t) * 2 + 1];
                RpTriangle& triangle = geometry->triangles[t];
                triangle.vertIndex[0] = static_cast<uint16_t>(vertex01 >> 16);
                triangle.vertIndex[1] = static_cast<uint16_t>(vertex01);
                triangle.vertIndex[2] = static_cast<uint16_t>(vertex2Mat >> 16);
                triangle.matIndex = static_cast<uint16_t>(vertex2Mat);
            }
        }
    }
    for (RwInt32 i = 0; i < geometry->numMorphTargets; ++i) {
        RpMorphTarget* morphTarget = &geometry->morphTarget[i];
        uint8_t kf[0x18];  // _rpMorphTarget: bounding sphere (4 reals), pointsPresent, normalsPresent
        if (!ReadBytes(stream, kf, sizeof kf)) return fail();
        std::memcpy(&morphTarget->boundingSphere, kf, 16);
        const uint32_t pointsPresent = LittleEndian32(kf + 16);
        const uint32_t normalsPresent = LittleEndian32(kf + 20);
        const uint32_t vectorBytes = static_cast<uint32_t>(geometry->numVertices) * sizeof(RwV3d);
        if (pointsPresent != 0 && !ReadBytes(stream, morphTarget->verts, vectorBytes)) return fail();
        if (normalsPresent != 0 && !ReadBytes(stream, morphTarget->normals, vectorBytes)) return fail();
    }
    uint32_t length = 0;
    if (RwStreamFindChunk(stream, kIdMatList, &length, &version) == 0) return nullptr;  // (RW leaks the geometry here)
    if (_rpMaterialListStreamRead(stream, &geometry->matList) == nullptr) return fail();
    uint32_t skinBytes = 0;  // DEV: the skin chunk's size for the read log
    const bool ok = ReadExtension(stream, [&](uint32_t type, uint32_t chunkSize) {
        if (type == kIdBinMesh) {
            geometry->mesh = MeshRead(stream, geometry);
            return geometry->mesh != nullptr;
        }
        if (type == kIdNative) return NativeRead(stream, geometry);
        if (type == kIdSkin) {
            skinBytes = chunkSize;  // DEV
            return RpSkinGeometryStreamRead(stream, static_cast<RwInt32>(chunkSize), geometry) != nullptr;
        }
        return RwStreamSkip(stream, chunkSize) != nullptr;
    });
    if (!ok) return fail();
    if (RpGeometryUnlock(geometry) == nullptr) return fail();
    RpGeometryReadRecord record = {};  // DEV
    record.flags = geometry->flags;
    record.numTriangles = geometry->numTriangles;
    record.numVertices = geometry->numVertices;
    record.numMorphTargets = geometry->numMorphTargets;
    record.numMaterials = geometry->matList.numMaterials;
    for (RwInt32 i = 0; i < geometry->matList.numMaterials; ++i) {
        if (geometry->matList.materials[i]->texture != nullptr) ++record.numTexturedMaterials;
    }
    record.numMeshes = geometry->mesh != nullptr ? geometry->mesh->numMeshes : 0;
    record.hasBinMesh = geometry->mesh != nullptr ? 1 : 0;
    if (geometry->repEntry != nullptr) {
        record.nativeMeshes = static_cast<RwUInt32>(geometry->repEntry->meshes.size());
        // The 0x510 chunk's size: the struct chunk header (12), the two words, the header, the buffers.
        record.nativeBytes = static_cast<RwUInt32>(12 + 8 + 4 + geometry->repEntry->meshes.size() * kNativeMeshBytes +
                                                    geometry->repEntry->vertexData.size() + geometry->repEntry->indexData.size());
    }
    record.skinBytes = skinBytes;
    if (geometry->repEntry != nullptr) {  // DEV: are the big-endian buffers what the header says
        const RpNativeMesh& mesh = geometry->repEntry->meshes[0];
        const std::vector<RwUInt8>& vertices = geometry->repEntry->vertexData;
        const std::vector<RwUInt8>& indices = geometry->repEntry->indexData;
        uint32_t largest = 0;
        for (size_t i = 0; i + 4 <= indices.size(); i += 4) {
            const uint32_t index = BigEndian32(indices.data() + i);
            if (index >= mesh.numVertices || index > mesh.lastIndex) ++record.nativeBadIndices;
            if (index > largest) largest = index;
        }
        if (!indices.empty() && largest != mesh.lastIndex) ++record.nativeBadRanges;
        for (uint32_t v = 0; v < mesh.numVertices; ++v) {
            for (int c = 0; c < 3; ++c) {
                const uint32_t bits = BigEndian32(vertices.data() + static_cast<size_t>(v) * mesh.stride + c * 4);
                float value;
                std::memcpy(&value, &bits, 4);
                if (!(value > -1.0e7f && value < 1.0e7f)) {
                    ++record.nativeBadVertices;
                    break;
                }
            }
        }
    }
    g_readLog.push_back(record);
    return geometry;
}

// 0x0069f0d8 ClumpAtomicStreamRead as RpAtomicStreamRead calls it: no frame list, no geometry list, so the
// geometry chunk follows the atomic's struct. The struct: frame index, geometry index (both unused here),
// flags (the low byte is the RwObject flags), unused. The atomic takes a reference to the geometry; the
// stream's own reference is released; the bounding sphere is the first morph target's.
RpAtomic* RpAtomicStreamRead(RwStream* stream) {
    uint32_t size = 0, version = 0;
    if (RwStreamFindChunk(stream, kIdStruct, &size, &version) == 0) return nullptr;
    uint32_t atomicStruct[4] = {};  // _rpAtomicBinary: frameIndex, geomIndex, flags, unused
    if (size > sizeof atomicStruct || RwStreamRead(stream, atomicStruct, size) != size) return nullptr;
    RpAtomic* atomic = RpAtomicCreate();
    atomic->objectFlags = static_cast<uint8_t>(atomicStruct[2]);
    uint32_t length = 0;
    if (RwStreamFindChunk(stream, kIdGeometry, &length, &version) == 0) {
        RpAtomicDestroy(atomic);
        return nullptr;
    }
    RpGeometry* geometry = RpGeometryStreamRead(stream);
    if (geometry == nullptr) {
        RpAtomicDestroy(atomic);
        return nullptr;
    }
    RpAtomicSetGeometry(atomic, geometry, 0);
    RpGeometryDestroy(geometry);
    // The atomic's plugin chunks.
    const bool ok = ReadExtension(stream, [&](uint32_t type, uint32_t chunkSize) {
        if (type == kIdRightToRender) return RightToRenderRead(stream, chunkSize, &atomic->rightsPluginId, &atomic->rightsExtraData);
        if (type == kIdPrtStd) {
            // The RpPrtStd plugin (RpPrtStdAtomicStreamRead_maybe 0x7301e0, rpprtstd/RpPrtStd.cpp) reads the
            // emitters from the plugin chunk. Measured on all 73 LVL000 and the 620 LVL010 particle atomics:
            // the readers read 8 bytes past the chunk (the writer's size count is 8 short, in the atomic and
            // extension chunks too).
            std::vector<uint8_t> payload(chunkSize + 8);
            if (!ReadBytes(stream, payload.data(), chunkSize + 8)) return false;
            const uint32_t used = RpPrtStdAtomicStreamRead(atomic, payload.data(), chunkSize + 8);
            RpPrtStdShim_NoteStreamRead(used, chunkSize);  // DEV
            return true;
        }
        return RwStreamSkip(stream, chunkSize) != nullptr;
    });
    if (!ok) {
        RpAtomicDestroy(atomic);
        return nullptr;
    }
    // _rwPluginRegistryReadDataChunks' always callbacks: the skin plugin's 0x773b98 (the other plugins' choose RW
    // pipelines this port does not model).
    RpSkinAtomicAlwaysCallBack(atomic);
    // _rwPluginRegistryInvokeRights: the skin plugin's rights callback 0x773ae0 (the only plugin with one here).
    if (atomic->rightsPluginId == kIdSkin) RpSkinAtomicRightsCallBack(atomic, atomic->rightsExtraData);
    return atomic;
}
