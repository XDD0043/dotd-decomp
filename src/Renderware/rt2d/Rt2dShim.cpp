// Rt2d.cpp - the Rt2d stream readers' stand-ins (C1.3 shim). See Rt2d.h.
#include "Renderware/rt2d/Rt2dShim.h"

#include <cstring>
#include <vector>

#include "Renderware/rwcore/RwStream.h"

namespace {

// Appends size bytes read from the stream; false on a short read.
bool Take(RwStream* stream, std::vector<uint8_t>& bytes, uint32_t size) {
    const size_t at = bytes.size();
    bytes.resize(at + size);
    return size == 0 || RwStreamRead(stream, bytes.data() + at, size) == size;
}

// The little-endian word at offset at of bytes.
int32_t WordAt(const std::vector<uint8_t>& bytes, size_t at) {
    int32_t v = 0;
    std::memcpy(&v, bytes.data() + at, 4);
    return v;
}

}  // namespace

Rt2dShimBrush* RwShim_Rt2dBrushCreate() {
    Rt2dShimBrush* brush = new Rt2dShimBrush();
    std::memset(brush->record, 0, sizeof(brush->record));
    brush->streamedTexture = nullptr;
    brush->texture = nullptr;
    return brush;
}

RwShim_Blob* RwShim_Rt2dFontStreamRead(RwStream* stream) {
    std::vector<uint8_t> bytes;
    if (!Take(stream, bytes, 4)) return nullptr;
    if ((static_cast<uint32_t>(WordAt(bytes, 0)) >> 24) == 0) return nullptr;  // local_80[0] of the native word
    // type, three reals, +0x10, +0x124, the glyph count (+0x130), the u16 table size (+0x128)
    if (!Take(stream, bytes, 4 * 8)) return nullptr;
    const int32_t fontType = WordAt(bytes, 4);
    const int32_t glyphCount = WordAt(bytes, 4 + 4 * 6);
    const int32_t tableCount = WordAt(bytes, 4 + 4 * 7);
    if (tableCount > 0 && !Take(stream, bytes, static_cast<uint32_t>(tableCount) * 2)) return nullptr;
    if (!Take(stream, bytes, 0x100)) return nullptr;  // the character map (+0x24, 128 u16)
    if (fontType != 0) {
        for (int32_t i = 0; i < glyphCount; ++i) {
            if (!Take(stream, bytes, 12)) return nullptr;
            if (WordAt(bytes, bytes.size() - 4) == 5) {
                RwShim_Blob* path = RwShim_ReadChunkBlob(stream, 0x1a1);  // Rt2dPathStreamRead: STUB(C1.4)
                if (path == nullptr) return nullptr;
                RwShim_FreeBlob(path);
                if (!Take(stream, bytes, 4)) return nullptr;
            }
            if (!Take(stream, bytes, 4)) return nullptr;
        }
    } else {
        for (int32_t i = 0; i < glyphCount; ++i) {
            if (!Take(stream, bytes, 0x10 + 4 + 1)) return nullptr;
        }
        if (!Take(stream, bytes, 4)) return nullptr;
        const int32_t textureCount = WordAt(bytes, bytes.size() - 4);
        for (int32_t i = 0; i < textureCount; ++i) {
            if (!Take(stream, bytes, 0x20)) return nullptr;  // the name RwTextureRead looks up
        }
    }
    RwShim_Blob* blob = new RwShim_Blob();
    blob->type = 0x199;
    blob->version = 0;
    blob->length = static_cast<uint32_t>(bytes.size());
    blob->data = new uint8_t[bytes.size()];
    std::memcpy(blob->data, bytes.data(), bytes.size());
    return blob;
}

Rt2dShimBrush* RwShim_Rt2dBrushStreamRead(RwStream* stream) {
    Rt2dShimBrush* brush = RwShim_Rt2dBrushCreate();
    if (RwStreamRead(stream, brush->record, sizeof(brush->record)) != sizeof(brush->record)) return brush;
    uint32_t version = 0, textureFollows = 0;
    std::memcpy(&version, brush->record + 0x00, 4);
    std::memcpy(&textureFollows, brush->record + 0x6c, 4);
    // _rt2dBrushStreamReadData_maybe 0x70a940: only with a texture flag does it read on.
    if (version == 1 && textureFollows != 0) brush->streamedTexture = RwShim_ReadChunkBlob(stream, 6);
    return brush;
}

// ---------------------------------------------------------------------------------------------------
// Maestro movies. The file words are little-endian and so is the host, so RwMemNative32 (and the swap in
// RwStreamReadInt32 / RwStreamReadReal) is a plain copy here.
namespace {

// 0x00757128 RwStreamReadInt32 / 0x00757200 RwStreamReadReal: fails only when RwStreamRead returns 0
// (so a zero-length read fails too; a short read does not).
bool ReadInt32s(RwStream* stream, void* dst, uint32_t size) { return RwStreamRead(stream, dst, size) != 0; }

// RwStreamRead of exactly size bytes (the readers that compare the count).
bool ReadExact(RwStream* stream, void* dst, uint32_t size) { return RwStreamRead(stream, dst, size) == size; }

// 0x007572e0 RwMatrixStreamRead: RwStreamFindChunk(rwID_STRUCT), the version check, a read of the chunk
// length into the 0x34-byte stream matrix. STUB(C1.4): RwMatrixOrthoNormalize when the flags are 3.
bool MatrixStreamRead(RwStream* stream, Rt2dShimMatrix* matrix) {
    uint32_t length = 0, version = 0;
    if (RwStreamFindChunk(stream, 1, &length, &version) == 0) return false;
    if (version - 0x35000u > 0x2002u) return false;
    std::vector<uint8_t> bytes(length);
    if (RwStreamRead(stream, bytes.data(), length) != length) return false;
    uint32_t w[13] = {};
    std::memcpy(w, bytes.data(), length < sizeof(w) ? length : sizeof(w));
    std::memcpy(matrix->right, &w[0], 12);
    std::memcpy(matrix->up, &w[3], 12);
    std::memcpy(matrix->at, &w[6], 12);
    std::memcpy(matrix->pos, &w[9], 12);
    matrix->flags = w[12] & 3;
    return true;
}

// 0x0070ac38 _rt2dBrushStreamReadTo: the 0x70-byte record; version 1 goes on to
// _rt2dBrushStreamReadData (0x70a940), whose only stream read is the texture when +0x6c is set.
Rt2dShimBrush* BrushStreamReadTo(Rt2dShimBrush* brush, RwStream* stream) {
    if (!ReadExact(stream, brush->record, sizeof(brush->record))) return nullptr;
    uint32_t version = 0, textureFollows = 0;
    std::memcpy(&version, brush->record + 0x00, 4);
    std::memcpy(&textureFollows, brush->record + 0x6c, 4);
    if (version != 1) return nullptr;
    if (textureFollows != 0) {
        brush->streamedTexture = RwShim_ReadChunkBlob(stream, 6);  // RwStreamFindChunk(6) + RwTextureStreamRead
        if (brush->streamedTexture == nullptr) return nullptr;
    }
    return brush;
}

// 0x007181f8 _rt2dSubPathStreamReadData (header already read).
Rt2dShimPath* SubPathStreamReadData(Rt2dShimPath* path, const int32_t header[4], RwStream* stream) {
    path->next.reset();
    path->numPoints = header[1];
    path->closed = static_cast<uint32_t>(header[2]) & 1;
    path->flat = (static_cast<uint32_t>(header[2]) >> 1) & 1;
    path->unk10 = header[3];
    const uint32_t size = static_cast<uint32_t>(path->numPoints) * 0x18;
    path->points.assign(size, 0);
    if (path->numPoints != 0 && !ReadExact(stream, path->points.data(), size)) return nullptr;
    if ((static_cast<uint32_t>(header[2]) & 4) != 0) {
        if (RwStreamFindChunk(stream, 0x1a1, nullptr, nullptr) == 0) return nullptr;
        std::unique_ptr<Rt2dShimPath> next(new Rt2dShimPath());
        int32_t nextHeader[4] = {};
        if (ReadExact(stream, nextHeader, 0x10)) {
            Rt2dShimPath* read = next.get();
            if (nextHeader[0] == 1) read = SubPathStreamReadData(next.get(), nextHeader, stream);
            if (read != nullptr) path->next = std::move(next);  // otherwise Rt2dPathDestroy
        }
    }
    return path;
}

// 0x00718540 _rt2dPathStreamReadTo: the 0x10-byte header, then the subpath data for version 1.
Rt2dShimPath* PathStreamReadTo(Rt2dShimPath* path, RwStream* stream) {
    int32_t header[4] = {};
    if (!ReadExact(stream, header, 0x10)) return nullptr;
    if (header[0] == 1) return SubPathStreamReadData(path, header, stream);
    return path;
}

// 0x0071ce08 _rt2dShapeRepStreamRead. STUB(C1.4): _rt2dShapeRepCreateGeometry.
std::shared_ptr<Rt2dShimShapeRep> ShapeRepStreamRead(RwStream* stream) {
    int32_t header[2] = {};
    if (!ReadExact(stream, header, 8)) return nullptr;
    std::shared_ptr<Rt2dShimShapeRep> rep(new Rt2dShimShapeRep());
    rep->streamWord0 = header[0];
    rep->nodes.resize(header[1] > 0 ? static_cast<size_t>(header[1]) : 0);
    for (Rt2dShimShapeNode& node : rep->nodes) {
        uint32_t flag = 0;
        if (!ReadExact(stream, &flag, 4)) return nullptr;
        if ((flag & 4) == 0) continue;  // path and brush stay null
        ReadInt32s(stream, &node.flag, 4);
        if (RwStreamFindChunk(stream, 0x1a1, nullptr, nullptr) == 0) return nullptr;
        node.path.reset(new Rt2dShimPath());  // Rt2dPathCreate + Rt2dPathUnlock
        PathStreamReadTo(node.path.get(), stream);
        if (RwStreamFindChunk(stream, 0x1a2, nullptr, nullptr) == 0) return nullptr;
        node.brush = RwShim_Rt2dBrushCreate();
        BrushStreamReadTo(node.brush, stream);
    }
    return rep;
}

// 0x00713aa8 _rt2dObjectBaseStreamRead: an 0x2c-byte record {word 0, type, depth, colorMult[4],
// colorOffs[4]}, then RwStreamFindChunk(rwID_MATRIX 0xd) and the MTM (its result is not checked).
Rt2dShimObject* ObjectBaseStreamRead(Rt2dShimObject* object, RwStream* stream) {
    int32_t record[11] = {};
    if (!ReadExact(stream, record, 0x2c)) return nullptr;
    if (RwStreamFindChunk(stream, 0xd, nullptr, nullptr) == 0) return nullptr;
    MatrixStreamRead(stream, &object->MTM);
    object->streamWord0 = record[0];
    object->type = record[1];
    object->depth = record[2];
    std::memcpy(object->colorMult, &record[3], 16);
    std::memcpy(object->colorOffs, &record[7], 16);
    object->flag = 6;
    return object;
}

// The shape reps a scene reads before its children (the {reps, count} its children's context points to).
using ShapeReps = std::vector<std::shared_ptr<Rt2dShimShapeRep>>;

Rt2dShimObject* SceneStreamReadData(Rt2dShimObject* scene, RwStream* stream, ShapeReps* reps);

// 0x0071d0c0 _rt2dShapeStreamReadData. STUB(C1.4): the colour cache, frame and atomic.
Rt2dShimObject* ShapeStreamReadData(Rt2dShimObject* shape, RwStream* stream, ShapeReps* reps) {
    std::shared_ptr<Rt2dShimShapeRep> rep;
    if (reps == nullptr) {
        rep = ShapeRepStreamRead(stream);
        if (rep == nullptr) return nullptr;  // the PS3 dereferences it
    } else {
        int32_t index = 0;
        if (!ReadExact(stream, &index, 4)) return nullptr;
        shape->repIndex = index;
        rep = (*reps)[static_cast<size_t>(index)];
    }
    shape->flag &= ~1u;
    shape->rep = rep;
    ++rep->refCount;
    shape->flag |= 1;
    return shape;
}

// 0x00718d88 _rt2dPickRegionStreamReadData.
Rt2dShimObject* PickRegionStreamReadData(Rt2dShimObject* region, RwStream* stream) {
    region->pickPath.reset(new Rt2dShimPath());
    region->flag &= ~1u;
    if (RwStreamFindChunk(stream, 0x1a1, nullptr, nullptr) == 0) return nullptr;
    if (PathStreamReadTo(region->pickPath.get(), stream) == nullptr) return nullptr;
    return region;
}

// 0x00709bf8 _rt2dObjectStringStreamReadData: the text length, a word (the height), the text, the font
// name length and name, then (after _rt2dObjectStringInit 0x709a20, which reads nothing) the brush.
Rt2dShimObject* ObjectStringStreamReadData(Rt2dShimObject* string, RwStream* stream) {
    int32_t textLength = 0, height = 0, fontLength = 0;
    if (!ReadExact(stream, &textLength, 4)) return nullptr;
    if (!ReadExact(stream, &height, 4)) return nullptr;
    const uint32_t textBytes = static_cast<uint32_t>(textLength) + 1;
    string->text.assign(static_cast<size_t>(textLength) + 3, 0);
    if (!ReadExact(stream, string->text.data(), textBytes)) return nullptr;
    if (!ReadExact(stream, &fontLength, 4)) return nullptr;
    if (fontLength != 0) {
        const uint32_t fontBytes = static_cast<uint32_t>(fontLength) + 1;
        string->fontName.assign(fontBytes, 0);
        if (!ReadExact(stream, string->fontName.data(), fontBytes)) return nullptr;
    }
    string->heightRaw = 0x3f800000;  // _rt2dObjectStringInit: 1.0f
    string->flag &= ~1u;
    string->stringBrush = RwShim_Rt2dBrushCreate();
    if (RwStreamFindChunk(stream, 0x1a2, nullptr, nullptr) == 0) return nullptr;
    if (BrushStreamReadTo(string->stringBrush, stream) == nullptr) return nullptr;
    string->heightRaw = height;
    return string;
}

// 0x00713838 _rt2dObjectStreamReadData: by type.
Rt2dShimObject* ObjectStreamReadData(Rt2dShimObject* object, RwStream* stream, ShapeReps* reps) {
    switch (object->type) {
        case 2: ShapeStreamReadData(object, stream, reps); return object;
        case 1: SceneStreamReadData(object, stream, reps); return object;
        case 3: PickRegionStreamReadData(object, stream); return object;
        case 4: ObjectStringStreamReadData(object, stream); return object;
        default: return nullptr;
    }
}

// 0x0071a808 _rt2dSceneStreamReadData: the child count; at the top (no reps yet) the shape reps; then
// every child through _rt2dSceneStreamReadChildCB (0x7194b8: the base read, then the data), whose results
// the loop ignores. STUB(C1.4): Rt2dSceneUnlock, the depth list and its sort.
Rt2dShimObject* SceneStreamReadData(Rt2dShimObject* scene, RwStream* stream, ShapeReps* reps) {
    int32_t childCount = 0;
    if (!ReadExact(stream, &childCount, 4)) return nullptr;
    scene->objects.clear();
    scene->objects.resize(childCount > 0 ? static_cast<size_t>(childCount) : 0);  // zeroed (memset)
    scene->flag |= 1;
    ShapeReps ownReps;
    ShapeReps* childReps = reps;
    if (reps == nullptr) {
        int32_t repCount = 0;
        if (!ReadInt32s(stream, &repCount, 4)) return nullptr;
        for (uint32_t i = 0; i < static_cast<uint32_t>(repCount); ++i) {
            std::shared_ptr<Rt2dShimShapeRep> rep = ShapeRepStreamRead(stream);
            if (rep == nullptr) return nullptr;
            ownReps.push_back(rep);
        }
        childReps = &ownReps;
    }
    for (Rt2dShimObject& child : scene->objects) {
        if (ObjectBaseStreamRead(&child, stream) != nullptr) ObjectStreamReadData(&child, stream, childReps);
    }
    for (std::shared_ptr<Rt2dShimShapeRep>& rep : ownReps) --rep->refCount;  // _rt2dShapeRepDestroy
    scene->flag &= ~1u;
    return scene;
}

// 0x0071acc0 Rt2dSceneStreamRead (after the caller's RwStreamFindChunk(0x1a5)).
Rt2dShimObject* SceneStreamRead(RwStream* stream, std::unique_ptr<Rt2dShimObject>& out) {
    std::unique_ptr<Rt2dShimObject> scene(new Rt2dShimObject());  // _rt2dObjectAlloc + _rt2dObjectInit(scene)
    scene->type = 1;
    if (ObjectBaseStreamRead(scene.get(), stream) == nullptr) return nullptr;  // the PS3 leaks the scene
    if (SceneStreamReadData(scene.get(), stream, nullptr) == nullptr) return nullptr;  // destroyed
    out = std::move(scene);
    return out.get();
}

// 0x00701278 Rt2dStringLabel_StreamRead: the name length and name (into the maestro's string bucket),
// then entityType and internalData.
bool StringLabelStreamRead(Rt2dShimMaestro* maestro, Rt2dShimStringLabel* label, RwStream* stream) {
    int32_t length = 0;
    if (!ReadInt32s(stream, &length, 4)) return false;
    if (length < 1) {
        label->nameIndex = -1;
    } else {
        // Rt2dStringBuffer_Append(bucket, 0, length) / _GetString. STUB(C1.4): the bucket's own layout.
        const size_t at = maestro->stringBucket.size();
        maestro->stringBucket.resize(at + static_cast<size_t>(length) + 1, 0);
        if (RwStreamRead(stream, maestro->stringBucket.data() + at, static_cast<uint32_t>(length)) !=
            static_cast<uint32_t>(length))
            return false;
        label->nameIndex = static_cast<int32_t>(at);
    }
    if (!ReadInt32s(stream, &label->entityType, 4)) return false;
    return ReadInt32s(stream, &label->internalData, 4);
}

// 0x00702090 Rt2dShimButton stream read: three words and the action list (count words of the list header).
bool ButtonStreamRead(Rt2dShimButton* button, RwStream* stream, int32_t transitionCount) {
    if (!ReadInt32s(stream, &button->strLabelIndex, 4)) return false;
    if (!ReadInt32s(stream, &button->objectIndex, 4)) return false;
    if (!ReadInt32s(stream, &button->stateFlag, 4)) return false;
    return ReadInt32s(stream, button->actionListForStateTransition,
                      (static_cast<uint32_t>(transitionCount) & 0x3fffffffu) << 2);
}

// 0x006feff8 Rt2dShimMessage stream read: four words, then the message type's stream-read callback (the
// table at TOC2-0x3b20, 0xc4d468; every type has _rt2dMessageStreamReadDefaultCallBack 0x6fe758, which
// reads nothing, in the file and in the running game).
bool MessageStreamRead(Rt2dShimMessage* message, RwStream* stream) {
    return ReadInt32s(stream, &message->messageType, 4) && ReadInt32s(stream, &message->index, 4) &&
           ReadInt32s(stream, &message->intParam1, 4) && ReadInt32s(stream, &message->intParam2, 4);
}

// 0x00702c68 Rt2dShimCel stream read ("Rt2dAnimNodeGroup_StreamRead").
bool CelStreamRead(Rt2dShimCel* cel, RwStream* stream) {
    if (!ReadInt32s(stream, &cel->strLabelIndex, 4)) return false;
    if (!ReadInt32s(stream, &cel->celIndex, 4)) return false;
    int32_t count = 0;
    if (!ReadInt32s(stream, &count, 4)) return false;
    if (count > 0) {
        cel->buttonIndices.assign(static_cast<size_t>(count), 0);
        if (!ReadInt32s(stream, cel->buttonIndices.data(), static_cast<uint32_t>(count) << 2)) return false;
    }
    return ReadInt32s(stream, &cel->messageListIndex, 4);
}

// 0x00703838 Rt2dShimCelList stream read ("Rt2dAnimNodeGroupList_StreamRead").
bool CelListStreamRead(Rt2dShimCelList* list, RwStream* stream) {
    int32_t count = 0;
    if (!ReadInt32s(stream, &count, 4)) return false;
    for (int32_t i = 0; i < count; ++i) {
        list->cel.emplace_back();
        if (!CelStreamRead(&list->cel.back(), stream)) return false;
    }
    return true;
}

// 0x006face8 Rt2dAnimFrameState_StreamRead: a 0xc-byte header {word 0, time, count}, then per object
// an 8-byte {flag, objectIdx} and the parts the flag names. STUB(C1.4): the compact array it builds.
bool FrameStateStreamRead(Rt2dShimKeyFrameList* list, RwStream* stream) {
    int32_t header[3] = {};
    if (!ReadExact(stream, header, 0xc)) return false;
    list->stateWord0 = header[0];
    std::memcpy(&list->stateTime, &header[1], 4);
    const int32_t count = header[2];
    for (int32_t i = 0; i < count; ++i) {
        list->updates.emplace_back();
        Rt2dShimAnimObjectUpdate& update = list->updates.back();
        uint32_t head[2] = {};
        if (!ReadExact(stream, head, 8)) return false;
        update.streamFlag = head[0];
        update.objectIdx = static_cast<int32_t>(head[1]);
        if ((head[0] & 1) != 0) {
            if (RwStreamFindChunk(stream, 0xd, nullptr, nullptr) == 0) return false;
            if (!MatrixStreamRead(stream, &update.transform)) return false;
            update.hasTransform = 1;
        }
        if ((head[0] & 2) != 0) {
            if (!ReadExact(stream, update.colorOffs, 0x10)) return false;
            update.hasColorOffs = 1;
        }
        if ((head[0] & 4) != 0) {
            if (!ReadExact(stream, update.colorMult, 0x10)) return false;
            update.hasColorMult = 1;
        }
        if ((head[0] & 8) != 0) {
            int32_t show[2] = {};
            if (!ReadExact(stream, show, 8)) return false;
            update.show = show[0] != 0 ? 1 : 0;
            update.showWord1 = show[1];
            update.hasShow = 1;
        }
        if ((head[0] & 0x10) != 0) {
            if (!ReadExact(stream, update.morph, 0x10)) return false;
            update.hasMorph = 1;
        }
    }
    return true;
}

// 0x006f68c8 Rt2dAnim stream read ("Rt2dAnim_InitFromStream"): the keyframe-list count, then per list
// its time, RwStreamFindChunk(0x1b0) and the frame state (0x6fb7e0 -> 0x6face8).
bool AnimStreamRead(Rt2dShimAnimNode* node, RwStream* stream) {
    int32_t count = 0;
    if (!ReadExact(stream, &count, 4)) return false;
    for (int32_t i = 0; i < count; ++i) {
        node->keyframeLists.emplace_back();
        Rt2dShimKeyFrameList& list = node->keyframeLists.back();
        if (!ReadExact(stream, &list.time, 4)) return false;
        if (RwStreamFindChunk(stream, 0x1b0, nullptr, nullptr) == 0) return false;
        if (!FrameStateStreamRead(&list, stream)) return false;
    }
    return true;
}

}  // namespace

Rt2dShimMaestro* RwShim_Rt2dMaestroStreamRead(Rt2dShimMaestro* maestro, RwStream* stream) {
    std::unique_ptr<Rt2dShimMaestro> created;
    if (maestro == nullptr) {
        created.reset(new Rt2dShimMaestro());  // RwFreeListAlloc(0x301b1) + _rt2dMaestroInit (0x6fc678)
        maestro = created.get();
    }
    if (!ReadInt32s(stream, &maestro->streamVersion, 4)) return nullptr;
    if (!ReadInt32s(stream, maestro->bbox, 0x10)) return nullptr;  // RwStreamReadReal
    // 0x00701410 _rt2dMaestroStringLabelsStreamRead
    int32_t labelCount = 0;
    if (!ReadInt32s(stream, &labelCount, 4)) return nullptr;
    for (int32_t i = 0; i < labelCount; ++i) {
        maestro->labels.emplace_back();
        if (!StringLabelStreamRead(maestro, &maestro->labels.back(), stream)) return nullptr;
    }
    // _rt2dMaestroSceneStreamRead, inlined
    int32_t sceneCount = 0;
    if (!ReadInt32s(stream, &sceneCount, 4)) return nullptr;
    if (sceneCount > 0) {
        if (RwStreamFindChunk(stream, 0x1a5, nullptr, nullptr) == 0) return nullptr;
        if (SceneStreamRead(stream, maestro->scene) == nullptr) return nullptr;
    }
    // 0x007021f8 _rt2dMaestroButtonsStreamRead
    int32_t buttonCount = 0;
    if (!ReadInt32s(stream, &buttonCount, 4)) return nullptr;
    if (!ReadInt32s(stream, &maestro->buttonListWord1, 4)) return nullptr;
    if (!ReadInt32s(stream, &maestro->buttonTransitionCount, 4)) return nullptr;
    for (int32_t i = 0; i < buttonCount; ++i) {
        maestro->buttons.emplace_back();
        Rt2dShimButton& button = maestro->buttons.back();
        for (int32_t& action : button.actionListForStateTransition) action = -1;
        if (!ButtonStreamRead(&button, stream, maestro->buttonTransitionCount)) return nullptr;
    }
    // 0x006ffd68 _rt2dMaestroMessageListStreamRead
    int32_t listCount = 0;
    if (!ReadInt32s(stream, &listCount, 4)) return nullptr;
    if (listCount > 0) {
        maestro->messageList.assign(static_cast<size_t>(listCount), 0);
        if (!ReadInt32s(stream, maestro->messageList.data(), static_cast<uint32_t>(listCount) << 2))
            return nullptr;
    }
    // 0x006ffc08 _rt2dMaestroMessageStoreStreamRead
    int32_t messageCount = 0;
    if (!ReadInt32s(stream, &messageCount, 4)) return nullptr;
    for (int32_t i = 0; i < messageCount; ++i) {
        maestro->messageStore.emplace_back();
        if (!MessageStreamRead(&maestro->messageStore.back(), stream)) return nullptr;
    }
    // 0x006fcc20 _rt2dMaestroAnimationsStreamRead. STUB(C1.4): the node's scene (the maestro scene for
    // node 0, else the parent node's child posInParentScene) and Rt2dAnimState_Init (0x700628).
    int32_t animCount = 0;
    if (!ReadInt32s(stream, &animCount, 4)) return nullptr;
    for (int32_t i = 0; i < animCount; ++i) {
        maestro->animations.emplace_back();
        Rt2dShimAnimNode& node = maestro->animations.back();
        if (!CelListStreamRead(&node.celList, stream)) return nullptr;
        if (!ReadInt32s(stream, &node.parent, 4)) return nullptr;
        if (!ReadInt32s(stream, &node.posInParentScene, 4)) return nullptr;
        RwChunkHeaderInfo info{};
        if (RwStreamReadChunkHeaderInfo(stream, &info) == nullptr) return nullptr;
        node.chunkType = info.type;
        node.chunkLength = info.length;
        node.chunkVersion = info.version;
        if (!AnimStreamRead(&node, stream)) return nullptr;
    }
    // STUB(C1.4): _rt2dMaestroInitAnimNodePostRead for every node (currAnimIndex = its index meanwhile).
    maestro->currAnimIndex = -1;
    created.release();
    return maestro;
}
